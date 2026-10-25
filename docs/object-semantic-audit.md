# object.cpp semantic audit

Audit snapshot: worktree branch `codex/semantic-object-audit`, based on
`2c13ed704899998206886ae6a594373b694e84a0` (preparation commits on top of
`4ed1dd0a96f5a6fe50fd88fb9a8c8f29cd708b95`). This is a static source and
metadata audit. No original game files, generated object, MWCC, DTK or objdiff
are present in this worktree, so this snapshot makes no fresh binary-match
claim.

## Evidence status

- **VERIFIED (repository snapshot):** `config/G9SE8P/symbols.txt` has 79
  function records in the configured `object.cpp` text interval
  `0x8005BEC4–0x8005F490`, a span of 13,772 bytes. The source, its effective
  public header, compile flags and post-processor edge were inspected.
- **CORROBORATED (historical measurement):**
  [`object-unit-evidence.md`](object-unit-evidence.md) records 78 raw-matching
  bodies, one 520-byte remainder, 800 relocations (655 text, 128 exception
  index, one exception payload, 16 data), and 18 final artifact hashes. The
  current worktree has none of the measured objects or original artifacts, so
  those counts were not independently reproduced in this audit.
- **VERIFIED (tool contract, not retail object):**
  [`fix_object_registers.py`](../tools/fix_object_registers.py) checks ELF32
  big-endian PowerPC structure, whole-text and function hashes, function
  boundary/binding, relocation inventory and instruction shape before changing
  ten register fields in six words. Its write path changes no complete
  instruction or relocation. The updated synthetic test has an independent
  test-owned manifest; that proves the script's bounded transformation on the
  synthetic fixture, not the current retail comparison.
- **UNKNOWN:** runtime behavior on GameCube or Dolphin, the exact recovered
  source history, unresolved `fn_...` call contracts, and whether an alternate
  MWCC spelling removes the remaining register allocation difference.

## Translation-unit inventory

All names below occur in the current configured symbol interval. The grouping
is by observed responsibilities and address order, not a claim about original
source-file grouping.

| Address interval | Count | Group |
| --- | ---: | --- |
| `0x8005BEC4–0x8005C0C8` | 7 | Custom material and UV effects |
| `0x8005C0C8–0x8005C0EC` | 1 | UV animation frame query |
| `0x8005C0EC–0x8005C16C` | 2 | Cannonball velocity helpers |
| `0x8005C16C–0x8005CC18` | 5 | Ground collision and movement |
| `0x8005CC18–0x8005D498` | 11 | Camera checks and near-camera rendering |
| `0x8005D498–0x8005D9A0` | 15 | Compression, shadow/light callbacks and visibility |
| `0x8005D9A0–0x8005DC30` | 9 | Hierarchy, geometry flags and material colors |
| `0x8005DC30–0x8005E8EC` | 22 | Animation, UV, frames, texture and material lookup |
| `0x8005E8EC–0x8005F194` | 5 | Resource cache and archive lifecycle |
| `0x8005F194–0x8005F490` | 2 | Player placement |
| **Total** | **79** | |

### Custom effects (7)

`AtomicSetMaterialEffect`, `MaterialSetEffect`, `SetClumpCustomFXTexture`,
`SetAtomicCustomFXData`, `SetUVAnimData`, `AtomicSetCustomFXTexture`,
`MaterialSetCustomFXTexture`.

They walk clumps, atomics and materials and attach effect/UV animation state or
custom textures. The traversal API and material callback state are visible in
source; the exact plugin payload ownership and the opaque RenderWare plugin
contracts remain **CORROBORATED**, not independently checked against SDK
headers here.

### UV animation query and motion (8)

`objRpUVAnimAnimationGetTotalFrame`;
`objCalculateVelocityAsCannonBall(RwV3d*)`,
`objCalculateVelocityAsCannonBall(RwV3d*, RwV3d*)`;
`OBJ_MoveOnGround::CheckGroundCollision`, `OBJ_MoveOnGround::CheckCollisionSub`,
`OBJ_MoveOnGround::CheckCollisionSub_MoveToPoly`,
`objCallbackCheckCollisionMoving`, and `OBJ_MoveOnGround::OBJ_MoveOnGround`.

The motion helpers update velocity/position and the ground helper consults the
octree collision list, filters moving-sphere candidates, resolves polygon
contacts, adjusts velocity and stores ground angles. This unit uses static
`OBJ_MoveOnGround::vMove`, a current-instance pointer and other shared
traversal state; reentrancy and multi-thread safety are not established. The
source constructor clears bits 0–3 and 8–11 of `flagMOG` with read/modify/write
operations, leaving bits 4–7 and 12–15 unchanged. Follow-up inspection found
`ENEMY_SHOT` embeds this base and is created with `new`; it has no class-specific
allocator, while inherited `TObject::operator new` uses `THeapCtrl::Malloc`,
which does not clear each returned block. The heap region is cleared when its
controller is constructed, but freed blocks are reused without being cleared;
whether a given shot receives an untouched or reused block is **UNKNOWN**.
Zero initialization of the preserved bits is therefore **not guaranteed**.
The shown readers use the result/request masks, and `CheckGroundCollision`
clears results and sets request bits before collision traversal; whether every
reader runs after the relevant initialization remains **UNKNOWN**. This
confirms partial initialization and a potential stale-value concern, not a
demonstrated gameplay failure. Do not change the matching constructor; a port
should define all flag bits explicitly after confirming which bits are
reserved.

### Camera and near-camera rendering (11)

`objRpAtomicToSetRenderCallbackToCheckFromCamera`,
`objRpClumpForAllAtomicsToSetRenderCallbackToCheckFromCamera`,
`objCallbackRpAtomicToSetRenderCallbackToCheckFromCamera`,
`objCallbackRpAtomicCheckFromCamera`,
`objRpClumpForAllAtomicsRenderNearCamera`,
`objRpAtomicCallBackRenderNearCamera`,
`objRpAtomicRenderNearCamera(RpAtomic*)`,
`objRpAtomicRenderNearCamera(RpAtomic*, f32, void*)`,
`objRpMaterialResetFlagsAndColor`, `objRpMaterialSaveFlagsAndColor`,
`objRpAtomicCheckFromCamera`.

These replace an atomic render callback while preserving the prior callback in
`OBJ_CUSTOMRENDER`, compare a camera-relative sphere distance, temporarily
adjust material colors/geometry flags, call the saved renderer, and restore
state. Allocation failure handling and the contract of all saved callbacks are
not proven by static inspection. `nearCameraColor` is a local constant whose
source-produced storage/order is described in the historical unit evidence.

### Compression, shadows, light and visibility (15)

`objRpAtomicCallbackSetCompressedGeometry`,
`objRpClumpForAllAtomicsToSetRenderCallbackToOptimizeShadow`,
`objCallbackRpAtomicToSetRenderCallbackToOptimizeShadow`,
`objCallbackRpAtomicRenderToOptimizeShadow`,
`objRpClumpForAllAtomicsToSetRenderCallbackToUseLight`,
`objCallbackRpAtomicToSetRenderCallbackToUseLight`,
`objCallbackRpAtomicRenderToUseLight`,
`objRpClumpForAllGeometriesToAffectAlphaToColor`,
`objCallbackRpAtomicToAffectAlphaToColor`,
`objRpClumpForTheAtomicsToHide`,
`objRpAtomicCallbackSetAtomicFlagToHide2`,
`objRpClumpForAllAtomicsToHide`,
`objRpAtomicCallbackSetAtomicFlagToHide`,
`objRpClumpForAllAtomicsToRender`,
`objRpAtomicCallbackSetAtomicFlagToRender`.

The source installs/removes render callbacks, sets RenderWare visibility flags,
modifies vertex pre-lighting using integer alpha arithmetic, invokes light and
shadow helpers, and hides atomics by frame ancestry or skin bone indices. The
bone callback loops while `i <= geometry->numVertices` and consumes four bytes
per iteration. Follow-up inspection of `rw_gcn_raster.c` found that
`fn_80226578` reads the plugin record's `+0x14` word (declared `u8*` at this
call site and `s32` at its definition), and `fn_80227AA8` processes one packed
word for each vertex count supplied by the geometry. This corroborates a
logical `numVertices`-word index array, but the allocation extent and any
sentinel remain **UNKNOWN**. The inclusive loop is therefore a **CORROBORATED
possible overread**, not a proven out-of-bounds access. Preserve it pending the
actual plugin allocation contract or target evidence.

### Hierarchy and material state (9)

`objRpHAnimHierarchyFindFrameFromBoneID`,
`objRpClumpForAllGeometrysToModulateMaterialColor`,
`objRpAtomicCallbackSetGeometryFlagToModulateMaterialColor`,
`objRpClumpForAllGeometrysToIgnoreLights`,
`objRpAtomicCallbackSetGeometryFlagToIgnoreLights`,
`objRpAtomicForAllMaterialsToChangeMaterialColor`,
`objRpClumpForAllMaterialsToChangeMaterialColor`,
`objRpAtomicForAllMaterialsToChangeMaterialColor`,
`objRpMaterialCallbackToChangeMaterialColor`.

These traverse hierarchy/material collections, look up a node ID, modify
geometry/material flags and apply color channels. The material callback keeps a
channel unchanged when its requested real-valued component is negative;
otherwise it scales by 255 and converts to `u8`. Conversion edge behavior for
out-of-range/NaN values is **UNKNOWN** and must not be normalized without
matching evidence.

### Animation, UV, frame and material lookup (22)

`objRpUVAnimAnimationStreamRead`, `objRpAtomicChangeUV`,
`objRwFrameSerchChildFrame`, `objCallbackSerchFrame`, `objRwFrameGetFrame`,
`objCallbackRwFrameGetChildFrame`, `objRwFrameGetChildFrame`,
`objCallbackGetFrame`, `objChangeTextureFilterMode`,
`objCallbackChangeTextureFilterMode`,
`objRpClumpGetAtomicWithGeometry(RpClump*, RpAtomic*, RpGeometry*)`,
`objRpClumpGetAtomicWithGeometry(RpAtomic*, void*)`,
`objRpClumpGetAtomicWithTexture`, `objCallbackGetAtomicWithTexture`,
`objCheckTextureRpMaterialCallback`, `objRpClumpGetAtomic`,
`objCallbackGetAtomic`, `objRpClumpGetMaterialWithSpecificTexture`,
`objCallBackGetRpMaterialWithTexture`,
`objRpClumpForAllMaterialsWithSpecificTexture`,
`objRpAtomicForAllMaterialsWithSpecificTexture`,
`objCheckCallbackForSpecificMaterialWithTexture`.

The group uses RenderWare visitor functions and file-local globals to return
matching frames, atomics, materials or animation textures. `objRpAtomicChangeUV`
locks geometry, updates UV coordinates and unlocks it. Search code handles a
material with no direct texture and may inspect UV animation textures. Callback
arguments carry pointers, integers and floating-point values through `void*`;
that representation assumes the original 32-bit ABI. Function-pointer/object-
pointer conversions and float-to-integer pointer payloads are not portable C++
contracts.

### Resource loading and release (5)

`objReleaseClumpAnimStoredInARAMFromMainRAM`, `objPointerReadFromClumpAnim`,
`objRwTexDictionaryGetPointer`, `objReleaseCommonObjectTextures`,
`objLoadCommonObjectTextures`.

The source declares 256 resource entries (`ResourceEntry`, 0x44 bytes on the
32-bit target) and ten compressed/request records. The loader opens the common
texture dictionary and `ONEFILE` archive, initializes request records, scans
archive slots, loads clumps/HAnim/UV animation, and defers selected clumps in
ARAM. The lazy reader first checks the resident cache, then request records;
for a deferred hit it expands data into allocated buffers, reads a RenderWare
chunk, closes the stream, frees the buffers, caches the object and applies
compressed-geometry callbacks. The release path dispatches destruction by file
extension and frees request data and shared dictionaries.

The cache/resource lifecycle is internally coherent from the call sequence,
but opaque allocator, decompressor, RenderWare stream and ARAM contracts are not
fully recoverable from this unit alone. The `objectBase` byte arithmetic
(`&entries[0].object` plus `slot * sizeof(ResourceEntry)`) is equivalent in
intent to addressing the object member of a resource entry, but exists in the
matching source form. Replacing it with direct member indexing is a plausible
source experiment; it was not compiled in this worktree and must not be treated
as matching.

### Player placement (2)

`OBJ_ReplacePlayer::objSetPlayerHandlingPosition`,
`OBJ_ReplacePlayer::objSetPlayerPosition`.

Both forward to the common position handler and update task position/angle for
frame zero. The handling variant computes a character-dependent hand offset,
composes rotations and transforms it before writing position. One method checks
`pno >= 8`; the other indexes the player tables without that upper-bound check.
Valid index range and caller preconditions are **UNKNOWN**; this asymmetry is
not by itself evidence of a decompilation error.

## Register-allocation remainder

`objPointerReadFromClumpAnim` calls both inlined scan helpers. Each helper walks
an array with a pointer cursor, compares a name with `strcmp`, advances the
cursor and returns an integer index. The cursor is no longer needed after the
loop result is established; later request and expanded-buffer values are
freshly defined. The historical audit reports both cursor lives surviving
`strcmp`, which preserves nonvolatile registers, and later definitions reusing
`r31` and `r27` respectively. The current normalizer records the same two
cursor changes: ten operand fields in six instructions; it does not modify
opcodes, branches, relocations or metadata.

Plausible causes, all **HYPOTHESES** until recompiled with the exact MWCC
version/flags:

1. Inlining merges the two helper live ranges with surrounding `i`, `request`,
   `name`, `input` and `expanded` values. A small lifetime/interference change
   can alter coloring among nonvolatile GPRs even though the cursors are dead
   after each search.
2. The optimizer's pseudo-register creation order, influenced by helper
   expansion order and source lexical order, may choose `r31` for the cursor
   value whose `i`/pointer dependency is formed first. Scope and declaration
   order are potential inputs only if they alter the generated tree/liveness;
   renaming alone is not evidence of a useful change.
3. Cursor post-increment versus indexed access may produce different address
   temporaries and interference with `strcmp` argument setup. Any rewrite must
   preserve the exact terminating condition and returned index.
4. Calls to `strcmp` require caller-visible arguments in `r3`/`r4`; retained
   loop state therefore competes with call setup. The frame already saves the
   nonvolatile register range needed by the observed code, so save/restore
   availability alone does not explain the choice.
5. The configured `-inline auto,deferred,level=2`, `-opt
   noschedule,nopeephole`, C++ exception support and other TU flags can affect
   inlining, CFG/lifetime construction and allocation. A different modern
   compiler cannot establish CodeWarrior's allocation cause.

Prior experiments recorded in `object-unit-evidence.md` cover helper/caller
order, loop forms, descriptor types, local scopes and historical spellings.
They did not isolate the root cause. In this worktree, no additional C++ variant
could be tested reproducibly because the MWCC package and its matching input
are absent. No source variant was placed in the production tree, and the
normalizer/configuration remain unchanged. The best next isolated experiment,
once an independent matching environment exists, is direct array-member
addressing for the slot loads/stores, followed by a single alternate cursor
form that changes the two inlined pointer live ranges without changing
semantics. Stop if both preserve the same coloring; do not make a combinatorial
search.

## Structural quality and port risks

- **VERIFIED:** `include/game/object.h` defines local RenderWare-shaped
  structures (`RwFrame`, `RpAtomic`, `RpGeometry`, `RpClump`, animation and
  plugin data) and the two C++ classes. Several fields are accessed by offset
  throughout this unit. The header has no explicit packing or offset assertions.
  Their completeness/correctness depends on the GameCube 32-bit layout and
  correlated accesses elsewhere; this audit did not independently measure
  every member offset from retail.
- **VERIFIED:** the source uses global callback/traversal state, raw `void*`
  callback payloads, opaque `fn_...` calls, fixed-capacity tables, fixed-size
  buffers, explicit `RwMatrix` padding, and 32-bit object/resource pointers.
  These are ABI-reconstruction constraints, not proposals for source changes.
- **CORROBORATED:** source declarations and symbol metadata support C++ member
  functions, overloads and C-linked globals. `object-unit-evidence.md` records
  how declaration order and deferred inlining reproduce function/data ordering;
  this audit cannot independently regenerate that ordering.
- **VERIFIED (source dataflow):** traversal wrappers assign file-local state
  such as `pSerchingFrame`, `pCurrentGeometry`, `pCurrentMaterialNum`, and
  `idBoneToHide` before passing callbacks to visitor functions. The callbacks
  read or update that state, and callers consume traversal results immediately
  after the visitor returns. Collision callbacks similarly read `pCurrentMOG`
  and static `vMove` established before the collision walk. This makes nested
  or overlapping calls non-reentrant without external serialization.
- **UNKNOWN (runtime scheduling):** `adx_mgc.c` creates and resumes audio
  threads, but the inspected call paths do not show those threads invoking
  `object.cpp` callbacks or collision functions. Actual concurrent access to
  this state is unproven; do not infer that the whole game is single-threaded.
- **CORROBORATED:** the skin loop may read beyond the logical per-vertex data;
  its actual allocation extent is not established. **VERIFIED:** the movement
  constructor preserves bits which it does not initialize, and the allocator
  can reuse payloads without clearing them on the `ENEMY_SHOT` path. Neither
  finding justifies changing matching source without target and lifecycle
  evidence.
- **UNKNOWN:** behavior of exception/allocator paths, malformed archive names,
  decompression failures, missing resources and malformed RenderWare objects.
  The source's calls and null checks do not reveal all callee contracts.

For a port, likely boundaries are RenderWare traversal/material/geometry,
`ONEFILE` and archive decompression, ARAM ownership, octree collision, task
tables and the light/shadow/effect callbacks. A port must replace or adapt these
platform services and revalidate behavior. A successful PowerPC rebuild alone
does not prove those adapters portable.

## Audit decision

No source or matching-pipeline change is accepted from this static audit. The
existing implementation has coherent resource, callback and collision group
boundaries, while its most consequential concerns depend on target layouts,
callee contracts or original behavior. The register allocation cannot be
resolved without the exact compiler and a legally available local target. The
post-processor remains the documented, bounded fallback until raw matching and
all object/section/relocation/artifact checks demonstrate a native replacement.
