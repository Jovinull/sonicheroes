# Source-language migration audit

This file records decisions and validation results for the C/C++ migration.
It contains only the minimum symbolic facts needed for review. It must not
contain proprietary executables, extracted code or complete symbol dumps.

The GameCube build `G9SE8P` is authoritative. PS2 metadata is used only as a
cross-platform classification lead and every completed batch must preserve the
GameCube artifacts.

## Baseline

The initial configured-command audit found 134 game-owned sources:

- 115 compiled as C++ through `.c` plus `-lang=c++`;
- 19 compiled as C;
- 9 of those C sources were initially pending stronger language evidence;
- no approved `-inline deferred` source.

Those nine initial decisions are now closed: `game/main.c` has positive C
source evidence and the other eight are explicitly recorded as reviewed C ABI
boundaries whose historical file language remains unresolved. The current
policy therefore has no `pending_c_evidence` entry.

The coordinated `advertiseD` reconstruction has now replaced all 30 of its
legacy C++/`.c` fragments. AutoSaveD remains protected while PR #116 is a
draft: its 12 legacy C++/`.c` fragments and four C-mode fragments with direct
C++ evidence remain in the queue.

### Integrated-link invariant

A 100% object diff is necessary but not sufficient for integration. Object
comparison can correlate relocations by target address while two reconstructed
objects still spell the same external ELF symbol differently. A completed
batch must therefore run `ninja progress`, which links the DOL and every REL
and verifies all 18 hashes through `build/G9SE8P/ok`; `all_source` or a green
per-function diff alone is not the completion gate.

Post-compile rename targets for externally visible symbols must use the current
canonical name in `config/G9SE8P/symbols.txt`. The combined C++ batch exposed
stale address-label aliases for the `TObject` constructor, destructor and
delete routine, RenderWare callbacks, `RsGlobal`, pathname helpers and endian
converter. Replacing those aliases changed only source or ELF symbol names,
not instructions; every matching source object remained complete in objdiff.

## Completed batches

### GameCube ARAM pool translation unit

`game/aram_pool.cpp` reconstructs the seven-function GameCube range
`0x800D0624`–`0x800D0B08`: two synchronous transfers, their completion callback,
release, allocation, cleanup and initialization. The three contiguous small
BSS objects are the reserved base, list head, and volatile completion flag.
This is an inferred whole-unit boundary from the shared allocation lifecycle,
callback and data family: it follows `link.cpp` and ends before unrelated
scalar interpolation routines. Exception entries corroborate the individual
ranges, not an original source-file boundary. The four trailing small-BSS bytes
are linker alignment.

The source follows the project's C++ default. Native allocation/deletion
paths exhibit the inlined constructor/destructor pattern reproduced by the
local class. `aram_pool.cpp` and `AramAllocation` are descriptive names;
original file/class names are unknown, and no PS2 metadata is asserted for
these GameCube-specific ARAM operations. Exported functions retain their
address names. Existing SDK headers supply AR/ARQ interfaces; the OS declarations
are included with C linkage. No shared-header change is needed.

The class stores next/previous links, address and size. The head is a zero-size
sentinel whose previous pointer initially points to itself. Removing a final
node updates that pointer; cleanup follows it exactly as in the executable.
Allocation rounds stored
sizes to 32 bytes, while the final capacity check uses the original requested
size, matching the executable. Cleanup releases nodes and calls ARFree without
resetting the stored base. Transfer code preserves the retail cache operations
and volatile callback wait. Ordinary automatic inlining produces the complete
object without extra helper bodies, deferred emission or postprocessing.

Independent ELF comparison verifies all four allocated sections, including
bytes, sizes, types, flags and alignment: 1,252 text bytes, 48 exception-table
bytes, 72 exception-index bytes and 12 small-BSS bytes. All seven function
symbols and 50 normalized relocations match. The sole supported release target,
G9SE8P, passed full native all-source/link/report builds, all 18 artifact hashes,
55 automated tests and both policy checkers. Runtime and physical-hardware
behavior have not been tested.

### Invincibility-effect translation unit

`game/eff_muteki.cpp` reconstructs all twelve surviving functions at GameCube
`0x800CF5E4`–`0x800D03A0`. Local PS2 PAL metadata (`SLES_519.50`, CCC v2.2,
commit `c025ca94735d75cd366b29a10f924010ce43353d`, `stdump symbols --section
.debug dwarf`) identifies `effect/eff_muteki.cpp` as `C_PLUS_PLUS` and
corroborates `EffMuteki`, `EffMutekiManager`, `TObjPlayerMuteki`, their layouts,
methods, and the static ribbon factory `Create`. The following list operations
belong to the separately reconstructed `link.cpp`.

Deferred emission permits the factory, manager updates, and destruction paths
to inline later definitions before emitting the retail function order. With
automatic emission, the factory compared at 83.80198% and manager update at
99.00944%; deferred emission makes both exact after canonical symbol naming.
The position-copy helper uses scalar float loads, and the drawing loop uses
the metadata-corroborated float UV pointer and indexed position array. The
existing single-flag dispatch retains the retail conditional/unconditional
branch pair. No new object or instruction postprocessor is used.

All owned bytes match: 3,516 text, 176 exception table, 132 exception index,
272 data, 15 small data, 8 small BSS, and 76 constants. All 180 normalized
relocations match. The link map marks seven unused out-of-line helpers (796
text bytes and their exception metadata) as discarded; an additional 40-byte
inline TObject delete duplicate resolves to the existing Task definition.
These are ordinary compiler emissions, not dummy functions. The constant
section's final four bytes and small-data final byte are linker alignment.
The compiler's writable constant-section flag differs from the reference;
bytes, placement and final artifacts match.

Native vtables and allocation calls now use canonical names for five TObject
virtual methods and THeapCtrl allocation/free. Existing callers and four
existing metadata rename maps use the same names. The symbol updates are
mechanical; touched source files retain repository formatting. Updating the
legacy `autosaveD/task_runtime.c` caller also migrates it to `.cpp`, retaining
its existing reviewed C++ classification and removing only the redundant
language flag. This is not a new claim of historical source-file identity.
Its complete text remains 100% in objdiff. The protected AutoSaveD paths are
unchanged.

The sole supported release target, G9SE8P, passed the full native all-source,
link and report builds, all 18 artifact hashes, 55 automated tests, and both
policy checkers. The first packaging passes exposed stale allocator names in
two shared spring includes; both were updated and all consumers rebuilt.
Runtime and physical-hardware behavior have not been tested.

### CLASS_LINK translation unit

`game/link.cpp` reconstructs the complete six-method unit at GameCube
`0x800D03A0`–`0x800D0624`. Local PS2 PAL metadata (`SLES_519.50`, CCC v2.2,
commit `c025ca94735d75cd366b29a10f924010ce43353d`, `stdump symbols --section
.debug dwarf`) identifies `link.cpp` as `C_PLUS_PLUS`, the `CLASS_LINK` and
`CLASS_LINK_MANAGER` layouts, their constructors/destructors and both link
operations. `link.h` metadata corroborates the pointer accessors. The six
methods occur in the same order in the GameCube build. They form a separate
unit from the preceding invincibility effect and following ARAM operations.

Ordinary automatic inlining reproduces the unlink operation inside both
destructors. Its two function-scope temporary pointers and inline accessors
reproduce the native register allocation. No deferred override, assembly or
object postprocessor is required. The head's previous pointer stores the tail;
the list is otherwise terminated by a null next pointer. Destruction unlinks
members without destroying their payloads, and leaves `pData` untouched.

Independent ELF comparison verifies all three allocated sections, including
section types/flags/alignment: 644 text bytes, 16 exception-table bytes and
24 exception-index bytes. All six function symbols and all six normalized
relocations match. The sole supported release target, G9SE8P, passed the full
`all_source`, `progress` and report builds, all 18 artifact hashes, 55 tests,
and both policy checkers. Runtime/hardware behavior has not been tested.

### EffWink translation unit

`game/eff_wink.cpp` reconstructs all ten surviving methods at GameCube
`0x800CF070`–`0x800CF5E4`. Local PS2 PAL metadata (`SLES_519.50`, CCC v2.2,
commit `c025ca94735d75cd366b29a10f924010ce43353d`, `stdump symbols --section
.debug dwarf`) identifies `effect/eff_wink.cpp` as `C_PLUS_PLUS`, the `EffWink`
class, its 0x28-byte member layout and the corresponding ten method names.
The GameCube methods follow the same API sequence. The following empty
function is referenced by another class's vtable, so it is excluded.

The unit uses deferred emission: constructor, destructor, update, setters,
getter and synchronization definitions emit in reverse order. This also lets
`Exec` inline the later `SetMode` definition. With automatic inlining, `Exec`
compares at 97.85577%, exception metadata at 87.5%/30%, and constants at
57.692307%; deferred emission makes every method and all owned sections exact.
The header's two simple mode getters inline naturally. No instruction or
object postprocessor is used for this unit.

Independent ELF comparison verifies 1,396 text bytes, 48 exception-table
bytes, 72 exception-index bytes, 28 constant bytes and all 41 normalized
relocations. The compiler marks `.sdata2` writable while the split reference
marks it read-only; section bytes and eight-byte alignment are identical.
The four bytes after the final float are linker alignment, excluded from the
owned range rather than represented by a dummy object. Existing AdvertiseD
references use the recovered method symbols without changing their ABI.

Validation passed for the sole supported release target, G9SE8P: full
`all_source`, `progress` and report builds, all 18 artifact hashes, 55 automated
tests and both policy checkers. Compilation and matching do not establish
runtime or physical-hardware validation.

### CRI RNARES translation unit

`game/cri/rnares.c` retains a reviewed vendor C ABI boundary and compiles with
`-lang=c++`. The original source language remains unproved. No RNARES counterpart
was found in the inspected PS2 PAL symbol table; the GameCube-specific ARAM API
and the GameCube object provide the evidence for this reconstruction.

Five independent scalar globals followed by 32 twelve-byte resource handles
reproduce CodeWarrior's native pooled BSS accesses. C mode emits these objects
in first-reference order, placing the handle array first. C++ mode preserves
declaration order, matching the reference count, external-allocation flag,
handle count, ARAM size, ARAM address, and handle array at offsets 0, 4, 8, 12,
16, and 20. These names describe observed accesses; they are not recovered
historical names. A prefix structure suppresses native pooling and fails to
reproduce the shared base addressing.

The supported full boundary is `.text` `0x80224CD0`–`0x80225100`, encompassing
six functions. The size getter, address getter, and handle destroy routine
precede create, finish, and initialize. AXRNA calls even the tiny accessors out
of line; RNARES finish instead inlines the same null-check-and-clear destroy
operation. The contiguous API family follows AXRNA's error-callback adapter.
Together these observations support moving the three accessors from the prior
AXRNA carve into RNARES. This is a strong GameCube-supported inference, not a
source-file marker or direct debug-metadata proof.

All six functions, 1,072 bytes of text, 79 bytes of read-only data, and 404
bytes of BSS match. The BSS pool anchor and first scalar have the same address;
all 18 relocations have identical offsets, types, and resolved destinations.
The one read-only byte and four BSS bytes before the following raster unit are
linker alignment, excluded from the owned ranges rather than emitted as dummy
objects. No additional helper, padding object, assembly, or instruction
postprocessor is used. The initialization loop's signed index, unsigned
`0x2000U` byte stride, and pointer increment in the loop update reproduce its
native induction variables and register allocation.

Validation passed for the sole configured release target, `G9SE8P`:
`ninja all_source progress build/G9SE8P/report.json`, all 54 policy/postprocessor
unit tests, both policy checkers, and all 18 artifact hashes. The link uses the
reconstructed RNARES object. Independent ELF comparison also verifies every
allocated section's type, flags, alignment, size and bytes, all 14 sized
function/data symbols, and all 18 resolved relocations. The adjacent raster
target object remains byte-identical. These checks do not establish runtime
or hardware validation.

### AdvertiseD overlay

PR #125 replaces the legacy AdvertiseD fragments with 21 C++ source objects
covering the complete overlay. Its retained `prolog.c` stays in the reviewed C
ABI-boundary category.

Language and boundary evidence:

- the correlated PS2 prototype retains the AdvertiseD class, method and source
  names used to reconstruct the logical C++ units;
- GameCube constructors, destructors, vtables and exception metadata
  independently establish C++ for the class-owned code;
- the GameCube REL remains the authority for every boundary, instruction,
  relocation and owned data range.

Validation:

- all 434 reconstructed source functions and all 21 source objects match;
- the linked AdvertiseD REL is byte-identical to retail;
- `adv_2p.cpp` and `adv_draw.cpp` retain their reviewed
  `-inline deferred,noauto` modes because natural emission does not reproduce
  the target order and data layout;
- all 30 obsolete AdvertiseD paths and the completed protected
  `anim_handle.c` entry were removed from the language-policy debt lists.

### Spring translation unit

`rel/o_spring.cpp` reconstructs the complete shared retail translation unit.
The implementation includes are organizational only; the build has one source
command, one compiler object and one contiguous split in each of the thirteen
stage modules that share this revision. Stage40D contains a different revision
and remains outside this claim.

Language evidence:

- the corresponding PS2 symbol metadata retains an `o_spring.cpp` source
  marker;
- the same metadata identifies the `TObjSpring` constructor, destructor,
  methods and vtable as C++ symbols;
- the GameCube constructor, destructor, methods, two-base vtable layout and
  adjustor thunk independently establish the same C++ object family;
- the contiguous GameCube range fixes the complete unit at `.text`
  `0x88C`–`0x18A4`, including all thirteen functions.

Validation:

- `.text`, `.ctors`, `.rodata` and `.data` all match byte-for-byte, including
  every relocation;
- `-inline auto` emits the transform helper before `springExec`, while
  `-inline deferred,auto` emits the retail `springExec`-then-helper order. The
  PS2 `o_spring.cpp` marker, class relationships and contiguous GameCube object
  establish that these routines belong to one natural source family rather
  than unrelated fragments, and deferred mode reproduces the complete retail
  function and section order;
- ordinary multiple-inheritance C++ emits the retail eight-byte secondary-base
  adjustor. The post-compile normalizer removes only the compiler-only
  standalone forwarding method and duplicate class vtable, then retargets and
  names that generated adjustor; it does not add or replace instructions;
- the unreferenced transform helper is explicitly retained by each affected
  module's linker configuration;
- the complete build relinked all thirteen affected stage modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- the language-policy check passes with `rel/o_spring.cpp` recorded as an
  approved deferred source.

### Stage11 key object

`rel/e_s11_key_stage11.cpp` reconstructs `TObjS11Key`, the Stage 11 goal key.

Language evidence:

- the corresponding PS2 symbol metadata names `TObjS11Key` and its C++ method
  family (`SearchCage`, `Disappear`, `CheckTouchedByLeader`, `TDisp`, `Disp`,
  `Exec`, `GetWaitAngY`, `GetWaitPosY`, `SetPosition`, destructor, `TObject*`
  constructor) plus the `initObj`/`endObj`/`startObj` lifecycle functions, in
  the same order as the GameCube text;
- the GameCube two-base vtable, constructor and destructor independently
  establish the same C++ object family.

Validation:

- `Exec` inlines `SetPosition`, `GetWaitPosY`, `GetWaitAngY` and
  `CheckTouchedByLeader`, all of which retail emits after it, and
  `startObjS11Key` inlines the constructor emitted before it. Under
  `-inline auto` MWCC neither inlines a body defined after its caller nor emits
  functions out of definition order, so no source order reproduces both the
  retail inlining and the PS2/GameCube method order. `-inline deferred,auto`
  inlines across the whole unit and emits in reverse definition order; with the
  methods defined from the lifecycle functions back to `SearchCage` it
  reproduces every function, relocation and owned section;
- the inlined, otherwise unreferenced method bodies are retained by the
  module's linker configuration;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts.

### Stage11 mask object

`rel/e_mask_stage11.cpp` reconstructs `TObjMask`. The PS2 symbol metadata names
the class and its C++ method family (`DestroyClump`, `CloneClump`,
`SetParameter`, `Exec`, `SetPosition`, destructor, `TObject*` constructor,
`EditOnChange`, `initObj`/`endObj`/`startObj`), and the GameCube two-base
vtable and adjustor thunk establish the same C++ class. `Exec` inlines
`SetPosition` and `CloneClump` inlines `GetHierarchy`, both emitted after their
callers, and the compiler-generated vtable must sit between the named data and
the string literals; `-inline deferred,auto` with reverse definition order
reproduces every function, relocation and owned section, and all 18 hashes.
`rel/o_s12_celestial_sphere.cpp` (`TObjS12Celestial`, PS2 method family
`DestroyClump`, `CloneClump(int)`, `SetPosition`, `SetParameter`, `Disp`,
`Exec`, destructor, constructor) needs the same mode for the same vtable
placement, and matches the same way. So does
`rel/e_capture_collision_stage11.cpp` (`TObjCaptureCollision`, PS2 family
`KillMyself`, `TDisp`, `Exec`, `SetParameter`, `ResetVariable`, destructor,
constructor, `CreateInstance`, `EditOnChange`).

### Tri-spring and switch fragments

Migrated 13 `rel/tri_spring_*`, `rel/switch_*` and
`rel/push_pull_switch_register.cpp` paths.

Language evidence:

- the corresponding PS2 metadata retains `o_3spring.cpp` and `o_switch.cpp`
  source markers;
- it identifies `TObj3Spring`, `TObjTriSpring`, `TObjSwitch` and
  `TObjSwitchPushPull` constructors, destructors, methods and vtables;
- the GameCube fragments implement those object/vtable families and were
  already compiled with `-lang=c++`.

Validation:

- all 13 configured commands remained C++ with the object-level language
  overrides removed;
- the complete build relinked the affected stage modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### Dashpanel and set-collision fragments

Migrated five `rel/dashpanel_*` and `rel/set_collision_*` paths.

Language evidence:

- the corresponding PS2 metadata retains `o_dashpanel.cpp` and
  `o_set_collision.cpp` source markers;
- it identifies `TObjDashpanel` and `TObjSetCollision` constructors,
  destructors, methods and vtables;
- the GameCube fragments implement those object/vtable families and were
  already compiled with `-lang=c++`.

Validation:

- all five configured commands remained C++ with the object-level language
  overrides removed;
- the complete build relinked the affected stage modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### Object registration fragments

Migrated 14 `rel/*_register` paths for propeller, light/invoke collision,
cannon, ironball, jump panel, checkpoint, container, weight, lens-flare and
goal-ring families.

Language evidence:

- the local PS2 metadata retains the corresponding C++ unit markers,
  including `o_propeller.cpp`, `o_light_colli.cpp`, `o_invoke_colli.cpp`,
  `o_weight.cpp`, `o_weight_ext.cpp`, `ef_lensflare.cpp` and
  `o_goalring.cpp`;
- the same metadata identifies the associated `TObj*` class, constructor,
  method, class-record and vtable families;
- the GameCube fragments register those same object families, contain C++
  linkage declarations and were already compiled with `-lang=c++`.

Validation:

- all 14 configured commands remained C++ with the object-level language
  overrides removed;
- the complete build relinked every affected stage module;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### Object asset fragments

Migrated 13 `rel/*_assets` paths for pawn, item box, pole, case, roll door,
signal, dash ring, reel, laser fence, big rings, cage, target and fan
families.

Language evidence:

- local PS2 metadata retains the corresponding C++ unit markers
  (`e_pawn.cpp` and the relevant `o_*.cpp` units);
- it also identifies the associated constructors, methods, class records and
  vtables, including `TObjEnemyPawn`, `TObjItembox`, `TObjDashring`,
  `TObjLaserfence`, `TObjBigrings` and the remaining object families;
- the GameCube fragments provide data/factory portions of those same families
  and were already compiled with `-lang=c++`.

Validation:

- all 13 configured commands remained C++ without per-object language
  overrides;
- the complete build relinked every affected stage module;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### System and sample fragments

Migrated the 12 object/registration fragments for system objects 1-4 and
sample objects 1-2.

Language evidence:

- local PS2 metadata retains `o_system1.cpp` through `o_system4.cpp`,
  `o_sample.cpp` and `o_sample2.cpp` unit markers;
- it identifies the matching `TObjSystem1` through `TObjSystem4`,
  `TObjSample` and `TObjSample2` class-record/vtable families;
- the GameCube fragments split those same six units into object and
  registration portions, all already compiled with `-lang=c++`.

Validation:

- all 12 configured commands remained C++ without per-object language
  overrides;
- the complete build relinked every affected stage module;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### Shared object-family fragments

Migrated ten small `rel/obj_*` and `rel/scroll_ring_*` fragments.

Language evidence:

- these are artificial GameCube split fragments located inside already
  identified C++ object-family runs, not standalone C translation units;
- their neighboring runs correspond to local PS2 C++ markers such as
  `o_sample.cpp`, `o_switch.cpp`, `o_set_collision.cpp`, `o_ironball.cpp`,
  `o_dashpanel.cpp` and `o_ring.cpp`;
- the PS2 metadata also retains the matching `TObject` and `TObjScrollRing`
  class/vtable families;
- the GameCube fragments require C++ linkage or language features (including
  inheritance and a virtual call) and were already compiled with `-lang=c++`.

Validation:

- all ten configured commands remained C++ without per-object language
  overrides;
- the complete build relinked every affected stage module;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### RenderWare platform callback fragments

Migrated `game/object_dispatch.cpp`, `game/path.cpp`, `game/time.cpp` and
`game/task_create.cpp`. These remain separate reconstruction fragments because
the GameCube evidence establishes each function range but not the original
translation-unit boundaries.

Language evidence:

- their implementations correlate with the RenderWare platform callbacks
  `psPathnameDestroy`, `psPathnameCreate`, `psTimer` and
  `psCameraShowRaster`;
- the corresponding PS2 callbacks retain C linkage in the same platform-code
  run as the private C++-mangled `TimerHandler__Fi`, establishing C++ compiler
  mode with a C ABI for that counterpart;
- the GameCube fragments now express that distinction with `.cpp` paths and
  explicit `extern "C"` boundaries rather than treating an unmangled symbol as
  proof of C source.

Validation:

- controlled C and C++ compiles produced identical `.text` for three fragments;
- the pathname-create fragment required only the explicit `void *` conversion
  that C++ requires;
- the complete build relinked `main.dol` and all modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### Game endian-conversion translation unit

Reconstructed `game/Endian.cpp` (`.text` `0x8004BECC`–`0x8004C160`) as C++.

Language and boundary evidence:

- the PS2 debug symbols independently retain the neighboring
  `TEndianCnv::ConvAnyParameter`, `TEndianCnv::ps2uNtoHS` and
  `TEndianCnv::ps2uNtoHL` C++ conversion family;
- the five-function GameCube conversion run terminates in its own static
  initializer and corresponding `.ctors` word at `0x802398D0`; the preceding
  object's initializer ends immediately before `0x8004BECC`, establishing
  both ends of the object independently of instruction similarity.

Validation:

- all six functions, 660 bytes of `.text`, and the four-byte `.ctors` section
  match exactly in objdiff;
- the fresh build linked every configured artifact;
- `config/G9SE8P/build.sha1` verified all 18 artifacts;
- the language-policy check passed with the source compiled in C++ mode.

### GameCube platform heap

Migrated `game/heap.cpp` while preserving explicit C linkage for the public
memory boundary and C++ linkage for its private helpers.

Language evidence:

- the GameCube unit provides the same memory-function boundary represented on
  PS2 by `psGetMemoryFunctions`, `Free_BW` and `MAlloc_BW`;
- those PS2 public entries retain C linkage, while their neighboring private
  allocator helpers are C++-mangled;
- a controlled GameCube C++ compile preserved all function code;
- CodeWarrior C++ declaration-order `.sbss` emission reproduces the target
  variable order directly. The former C reconstruction declared the variables
  in reverse to compensate for C first-reference emission.

Validation:

- all eleven functions, exception records, relocations and 32 bytes of `.sbss`
  match the GameCube target;
- the complete build relinked `main.dol` and all modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### GameCube platform main

`game/main.c` remains a confirmed C source. This is a platform-specific
decision based on the matching target, not an inference from its unmangled
entry points.

Evidence and validation:

- the natural C reconstruction matches all seven functions, exception records,
  relocations and the unit-owned 16-byte `.bss`;
- a direct C++ compile makes `main` eight bytes larger;
- C++ with the public C ABI and equivalent typed structures restores the exact
  size but changes six instructions through register allocation;
- the PS2 platform startup run is C++-compiled, demonstrating why its language
  cannot be copied blindly to a platform-specific GameCube unit;
- the reviewed C form keeps all 18 configured artifact hashes exact without a
  deferred-inline override or register-forcing workaround.

### Game-owned main loop

Added `game/main/main.cpp`, corresponding to the original game-owned
`main.cpp` rather than the unrelated GameCube platform entry point above.
The extra directory prevents the two basenames from resolving to the same
build object.

Language evidence:

- local PS2 beta DWARF identifies the correlated unit as `main.cpp`;
- the same metadata identifies `MAIN::Init()` and signed
  `MAIN::Loop()` methods and the local `MOBJECT_RETURN` enum;
- the GameCube functions reproduce those method relationships and call the
  neighboring `TMainTask` class constructor.

Validation:

- all three functions, exception records, relocations, strings, jump table,
  small data and small BSS match the GameCube target;
- CodeWarrior's four writable-string definitions use staging names so their
  declaration order remains original without triggering a local-address-base
  optimization absent from the target; a post-compile symbol-only rename
  restores the retail labels;
- the complete build relinked the DOL and all modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts and the DOL
  retained SHA-1 `9214426b8a3fb1d6fe3dcff09bcc1a959e1e04a8`.

### RenderWare skeleton

Added `game/skeleton.cpp` for the complete GameCube RenderWare skeleton range,
including camera sizing, initialization and shutdown, pathname forwarding,
event dispatch, raster presentation and error reporting.

Language evidence:

- the corresponding PS2 symbols retain the same `RsInitialize`,
  `RsRwInitialize`, `RsRwTerminate`, `RsEventHandler`,
  `RsCameraShowRaster` and `RsErrorMessage` interface;
- that PS2 platform-code run uses C linkage for the public RenderWare
  callbacks alongside a private C++-mangled timer handler;
- the GameCube unit is therefore reconstructed in C++ mode with explicit C
  linkage at the RenderWare boundary, consistent with the adjacent callback
  fragments.

Validation:

- all ten functions in `.text` `0x80011C20` through `0x8001234C` match
  byte-for-byte;
- the complete `extab`, `extabindex`, `.data`, `.bss` and `.sdata` sections
  and their relocations match;
- the complete build relinked `main.dol` and all modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts.

### HAnim helpers

Added `game/hAnim.cpp` for the complete HAnim helper unit, including hierarchy
node lookup, animation-key conversion, skin hierarchy attachment and
recursive frame discovery.

Language evidence:

- the PS2 beta symbols identify the same ordered run as methods of
  `HAnimClass`, followed by its constructor, destructor and
  `__sinit_hAnim.cpp`;
- the GameCube unit contains the corresponding C++-mangled class methods,
  global-object destructor registration and `.ctors` entry;
- the source is therefore reconstructed as C++ rather than relying on a
  C-path/C++-mode exception.

Validation:

- all eleven functions in `.text` `0x800BCE78` through `0x800BD1E8` match
  byte-for-byte;
- the complete `extab`, `extabindex`, `.ctors`, `.bss`, `.sbss` and
  `.sdata2` sections and their relocations match;
- the four-byte linker-alignment gap following the unit's 12-byte destructor
  record is explicitly excluded from its `.bss` object;
- the language-policy check and all independent object-level gates pass;
- a clean full link currently stops in pre-existing upstream code:
  `dvd.c` references the missing `__DVDIsBlockInWaitingQueue`, while the
  in-progress GX sources reference the unconfigured `__gxVerif`; this unit
  introduces neither reference.

### Reviewed C ABI and middleware boundaries

The policy distinguishes positive C source evidence from an existing boundary
that is reviewed in C mode but cannot be assigned a historical file language
honestly. `game/main.c` is the sole `confirmed_c_sources` entry. The following
eight paths are instead `reviewed_c_boundary_sources`:

- `advertiseD/prolog.c`
- `autosaveD/prolog.c`
- `movieD/prolog.c`
- `rel/prolog.c`
- `movieD/cri/sfxahn.c`
- `movieD/cri/sfxcnv.c`
- `movieD/cri/sfxset.c`
- `movieD/cri/sud.c`

GameCube validation:

- all eight compile in the configured C mode and match their owned GameCube
  code, data and relocations;
- the four module prologs were also compiled as C++ inside an explicit
  `extern "C"` boundary in an isolated output directory;
- for every prolog, `.text`, owned `.data`, relocation entries and functional
  symbols were identical to the C object; only the local ELF `STT_FILE` source
  marker changed;
- therefore the linked GameCube binary cannot distinguish C source from C++
  source with C linkage for those prologs.

Cross-platform validation used only local symbol metadata from the North
American retail PS2 executable and `stdump` v2.1:

- `stdump identify` found `.symtab` but no `.mdebug`/DWARF source-file table,
  and `stdump files` returned no file records;
- the PS2 overlay exposes mangled prolog names for the advertise, autosave and
  movie modules, establishing C++ linkage for those PS2 counterparts but not
  for the platform-specific GameCube entry stubs;
- the SFX/SUD symbols expose a C ABI and correlate the middleware families, but
  without a source-file/language record they do not prove a historical `.c`
  filename.

The result is intentionally conservative. These paths remain matching C ABI
boundaries and are not silently relabeled as historically confirmed C. A new
entry in this category still requires a reviewed rationale and complete
GameCube validation; the category is not a general escape hatch for new C
files.

## Remaining queue

After the GameCube platform-main decision:

- 12 legacy `.c` paths still compile as C++;
- none of them are outside the protected areas;
- all 12 belong to the protected `autosaveD` area;
- 4 protected sources have direct C++ evidence but remain in C mode until their
  active changes are coordinated;
- no C-compiled game source is silently unclassified: one has positive C
  evidence and eight are explicitly reviewed C ABI boundaries that do not
  claim a historical source extension;
- `movieD/cri/sfx.c` is a reviewed C-path/C++-compiler-mode exception, not a
  migration candidate;
- the reviewed deferred-inline modes are `game/skyfs_adx.c`,
  `game/modeswitch.cpp`, `game/e_paralysis.cpp`, `advertiseD/adv_2p.cpp`,
  `advertiseD/adv_draw.cpp`, `rel/e_s11_key_stage11.cpp`,
  `rel/e_mask_stage11.cpp`, `rel/o_s12_celestial_sphere.cpp`,
  `rel/e_capture_collision_stage11.cpp` and the CRI ADX core units listed under
  "CRI ADX core library units".

### Reviewed inline exceptions

`game/skyfs_adx.c` needs `-inline deferred`: correlated PS2 metadata establishes
the unified translation-unit order, and the controlled GameCube comparison
shows that ordinary auto inlining changes accessor emission and call sites.
The deferred form reproduces all 19 functions, relocations and owned sections.

`advertiseD/adv_2p.cpp` and `advertiseD/adv_draw.cpp` need the combined
`deferred,noauto` mode to preserve their reviewed function emission and linked
data layout. Both remain exact as part of the complete AdvertiseD object and
REL validation. The policy treats comma-separated inline modes as exact tokens
and rejects unreviewed deferred use.

`game/modeswitch.cpp` also keeps an object-level `-inline deferred` override.
The PS2 beta debug symbols identify the original C++ source and its
`MODESWITCH` constructor, destructor, and setter. Declaring those three
functions in constructor/destructor/setter order under ordinary
`-inline auto` emits the exception records in that same order, while the
GameCube object records setter/destructor/constructor. Deferred emission
reverses the source order and reproduces the target `.text`, `extab`, and
`extabindex`, including every function and exception-table relocation. Its
initializer arrays must remain writable at the same time: const qualification
under deferred emission moves them to `.rodata`, whereas the writable
declarations reproduce the target `.data` byte-for-byte.

`game/e_paralysis.cpp` keeps an object-level `-inline deferred` override for the
same reason. The PS2 beta debug symbols name the original translation unit and
its `TEnemyParalysis` and `sParalysisParam` methods, and the GameCube vtable,
constructor/destructor cleanup records, `TEnemyParalysis` string, private
resource data and static initializer establish the retail unit boundary
independently. Deferred emission reproduces the PS2 method order in the
GameCube object and preserves the retail constructor and destructor exception
metadata. All ten functions and every owned section match byte for byte.

The following sources are classified in `protected_cpp_c_sources` without
changing their source, split or object configuration:

- `autosaveD/menu_selectors.c`
- `autosaveD/table.c`
- `autosaveD/widget_rendering.c`
- `autosaveD/window_input.c`

Language evidence:

- the correlated PS2 metadata retains C++-mangled constructors, destructors and
  methods for `ADV_MENU`, `ADV_WINDOW` and `sADV_WINDOW_PARAM`;
- it retains the `ADV_WINDOW` vtable and class record;
- the methods cover the selection, lifecycle, update and rendering behavior
  reconstructed by these four GameCube fragments;
- `table.c` already identifies its deleting-destructor-shaped function and its
  call to CodeWarrior C++ `operator delete`.

These facts prove that the corresponding code belongs to C++ class
implementations; the current matching C fragments do not prove original C
source. PR #116 is an active draft reconstructing the same AutoSaveD classes.
Migration must be coordinated with its owner, reviewed against the final class
layout and accepted only after the GameCube object diffs and all 18 artifact
hashes remain exact.

### AutoSaveD draft inline audit

PR #116 commit `e78d889` was compiled in an isolated temporary tree against
the proposed GameCube splits. This is evidence for revising the draft, not
approval to edit or integrate the protected area:

- `ADV_MENU.cpp` needs both halves of one `-inline noauto,deferred` override.
  `noauto` preserves the out-of-line `Commit` calls and matching function
  bodies; `deferred` emits the 13 functions in the target order. Twelve
  functions match exactly, while `UpdateQUAD2` remains four bytes short and
  97.273% matching.
- `ADV_WINDOW.cpp` needs `deferred` to reproduce its 147-byte `.data` and put
  the vtable at offset `0x4C`; `noauto` independently preserves the matching
  call structure. The draft still duplicates six functions owned by
  `ADV_WINDOW_DISP.cpp`, omits the 140-byte parameter assignment operator,
  emits 24 rather than 40 bytes of `.bss`, and has incomplete rodata and
  `InitializeCore`.
- The six implemented `ADV_WINDOW_DISP.cpp` functions need `noauto` for their
  bodies and `deferred` for target order. The proposed unit remains incomplete:
  it supplies 1,260 of 5,228 text bytes and 8 of 680 rodata bytes.
- `autosaveD/prolog.c` needs no override. Inherited auto reproduces all 196
  text bytes and all 72 data bytes exactly. Deferred reverses `_prolog`,
  `_epilog` and `_unresolved`, producing a different raw text section even
  though a per-symbol diff can still report each body as matching.

No AutoSaveD path is added to `deferred_sources` until the draft removes its
blanket and duplicate overrides, completes the proposed logical units, records
their final boundaries and relocation results, and preserves all artifacts.

### AutoSaveD draft header provenance

The public-header comparison for PR #116 commit `e78d889` resolved the
provenance question with reproducible CC0 sources:

- 15 RenderWare headers are exact blobs from BFBB commit
  `ea82f4f521ab87b035728d64ab60c08a40aac2e6`; `rwcore.h` adds the local
  `rsglobal.h` include, and `rsglobal.h` is a small project-specific
  declaration;
- the MSL headers correlate with SMS commit
  `b1cfdf687911c5bcc51a5e3715f132600ab32272`; `stdarg.h`, `stddef.h` and
  `fdlibm.h` add only source comments, while `float.h` and `math.h` also adapt
  include or declaration scope;
- BFBB, SMS and the lm-decomp repository named by the `fdlibm.h` comment all
  declare CC0-1.0.

Before the draft leaves draft status, replace the informal `rwsdk/README.md`
wording with a pinned attribution table and identify those local adaptations.
No binary, SDK archive or extracted proprietary source is needed.

### Protected C++ dry run

The four AutoSaveD C-mode paths with direct C++ evidence were also compiled in C++ mode
in an isolated temporary output directory. No protected source, split or
configuration was changed.

| current fragment | C++-mode result | integration consequence |
| --- | --- | --- |
| `autosaveD/menu_selectors.c` | raw `.text` is identical; all 53 relocation types and offsets are retained | absorb into the reconstructed `ADV_MENU` logical unit rather than preserve C-shaped free functions |
| `autosaveD/table.c` | raw `.text` is identical; its one relocation is retained | absorb into `ADV_MENU`; the current pre-mangled `__dl__FPv` placeholder is double-mangled by a naive C++ compile |
| `autosaveD/window_input.c` | raw `.text` is identical; all 11 relocation types and offsets are retained | absorb into the reconstructed `ADV_WINDOW` logical unit and resolve its member/external ABI names together |
| `autosaveD/widget_rendering.c` | does not compile as C++ because the C-only `fn_2_25A8()` non-prototype is called with both three and four arguments | reconstruct the typed member/overload interface in `ADV_WINDOW_DISP`, then repeat the object and relocation comparison |

The matching raw instructions show that four bodies do not need semantic
rewrites merely to enter C++ mode. They do not make a mechanical flag switch
safe: C++ changes the free-function and external symbol names, and wrapping
everything in `extern "C"` would preserve the current C-shaped reconstruction
instead of expressing the evidenced classes. The protected logical-unit
reconstruction must establish the final member names, boundaries and C ABI
edges before the paths are renamed.

### Protected integration plan

The 12 remaining `legacy_cpp_c_sources` already compile as C++. Cross-platform
metadata retains the C++ unit marker `as_overlay.cpp`, plus the `TAutoSave`,
`ADV_WINDOW`, `ADV_MENU`, `TAS_EMBLEM`, `TAS_CONG` and `TAS_SAVE` class
families. This establishes the module language, but not every original
GameCube translation-unit boundary: many current paths are artificial matching
fragments.

Complete the protected migration in this order:

1. Integrate the reconstructed logical AutoSaveD units from PR #116 after its
   language flags, target diffs and header provenance pass review. Remove every
   absorbed path from the two debt lists in the same change.
2. Re-audit the remaining AutoSaveD list after that integration. Rename only
   fragments that remain independent; merge fragments only where class, data
   and ordering evidence establishes one logical unit.

Each completed batch must leave no stale policy entry, no `.c` path compiled as
C++ outside a reviewed vendor exception, and no newly introduced C-mode game
source. The final checkpoint is an empty `legacy_cpp_c_sources`,
`protected_cpp_c_sources` and `pending_c_evidence`, together with a clean
language-policy check and all 18 artifact hashes exact.

Until the AutoSaveD owner coordinates integration, the checker permits this
debt only under `autosaveD/`. A legacy C++/`.c` entry anywhere else is a policy
error.

### GetSpParam

Added `game/GetSpParam.cpp` as a C++ translation unit.

Language and boundary evidence:

- local PS2 debug metadata retains the `GetSpParam.cpp` source marker and the
  `GetSpParam` constructor, destructor and method family;
- the correlated GameCube range has the same ordered 11-method family,
  destructor and static initializer;
- the GameCube object requires C++ exception metadata and global construction.

Validation:

- all 13 functions and the complete `.text`, exception, constructor, BSS and
  floating-constant sections match the GameCube target byte-for-byte;
- the complete build relinked and verified all 18 configured artifacts;
- the language-policy check passes without an exception.

### `game/dAnim.cpp`

`game/dAnim.cpp` and its constructor emission fragment are C++.

Evidence and rationale:

- the PS2 beta metadata retains the `dAnim.cpp` source marker together with
  `DAnimClass` methods, its constructor and its destructor;
- the GameCube run has the same method sequence and RenderWare morph-animation
  calls, followed by the `DAnimClass` global-object initializer;
- both configured C++ objects match their complete text and owned section
  ranges byte-for-byte.

The four-byte constructor is compiled as a separate reconstruction object.
Keeping its empty definition visible in the body object suppresses a constructor
call in the static initializer, while emitting the definition separately
preserves the original constructor-after-initializer text order.

### `game/eventCore.cpp`

`game/eventCore.cpp` is C++.

Evidence and rationale:

- the PS2 beta metadata retains the `eventCore.cpp` source marker,
  `EventVoiceList::GetTopVoiceOffset(int)` and the class-owned
  `eventVoiceTopList` table;
- the GameCube function performs the same event-number lookup against the
  corresponding 64-entry table;
- the configured C++ object matches its complete text and read-only-data ranges
  byte-for-byte.

### `game/SeqFlagCtrl.cpp`

`game/SeqFlagCtrl.cpp` is C++.

Evidence and rationale:

- the PS2 beta metadata retains the `SeqFlagCtrl.cpp` source marker, the
  `TQuestSeqCtrl::CheckSequenceVars(int)` and
  `TQuestSeqCtrl::SetSequenceVars(int)` methods, and the class-owned `seqVars`
  array;
- the GameCube pair performs the same bounded bit lookup and update against the
  corresponding 128-byte array;
- the configured C++ object matches its complete text and uninitialized-data
  ranges byte-for-byte.

### `game/expasm.cpp`

`game/expasm.cpp` is C++.

Evidence and rationale:

- the PS2 beta metadata retains the `expasm.cpp` source marker and
  `Expand2(void*, void*)` symbol;
- the GameCube function is the corresponding bitstream decompressor, including
  the same literal-byte, short-back-reference and long-back-reference forms;
- the configured C++ object matches its complete text range byte-for-byte.

### Movie playback controller

Added `game/moviePlay.cpp` as a C++ translation unit.

Language and boundary evidence:

- local PS2 debug metadata retains the `moviePlay.cpp` marker, the
  `MOVIE_PLAY` method family, `MovieLists` static member and `MoviePlay`
  instance;
- the correlated GameCube range has the same ordered conversion, loop, end and
  initialization methods and the same 29-entry movie table;
- the mangled member functions and static member require C++ linkage.

Validation:

- all five GameCube-emitted functions and every owned code, exception and data
  section match byte-for-byte;
- the complete build relinked and verified all 18 configured artifacts;
- the language-policy check passes without an exception.
### CRI SFX compiler-mode exception

`movieD/cri/sfx.c` remains a `.c` source and retains `-lang=c++`.

Evidence and rationale:

- it is part of the CRI SFX vendor middleware boundary and sits beside the
  C-compiled `sfxahn.c`, `sfxcnv.c` and `sfxset.c` units;
- its externally visible API retains C linkage;
- the matching GameCube object requires CodeWarrior C++ declaration-order
  `.bss` emission; C mode emits those declarations in first-reference order;
- renaming a vendor C-path source without positive C++ source evidence would
  overstate what the binary match proves.

The policy therefore tracks it in `c_sources_compiled_as_cpp`. New game-owned
sources may not use this exception as an escape hatch.

### CRI SVM compiler-mode exception and complete unit

`game/cri/svm.c` retains the reviewed CRI C ABI boundary and uses
`-lang=c++`, following the same vendor exception as SFX. This does not claim
that the unavailable original source had a C++ extension.

The GameCube unit covers `.text` `0x802218A8`–`0x80222A14`, `.rodata`
`0x8023FFC0`–`0x80240168`, and `.bss` `0x80427CB0`–`0x80427F78`.
Its SVM/GC version string, diagnostic strings, callback tables, and private
state correlate all 27 functions within the existing CRI middleware boundary.
The following MFCI unit begins at those adjacent section boundaries.

Minimal cross-platform evidence from a legally held PAL PS2 build:

- ELF symbols name the individual `svm_init_level`, `svm_lock_level`, and
  `svm_locking_type` globals, the `svm_tas_fptr` callback, and distinct
  lock/unlock/error callbacks and server tables.
- GameCube initialization, nested locking, callback dispatch, and test-and-set
  accesses independently identify those same roles. The scalar state is not
  an aggregate containing every subsequent global.
- PS2 also names `svm_reset_variable` and `SVM_ExecSvrFunc`; shared inline
  reset and dispatch helpers reproduce the repeated GameCube expansions.
- These facts support names, source structure, and the middleware boundary;
  they do not establish the historical source language. Only filtered symbol
  metadata was inspected, with no imported code or published symbol dump.

CodeWarrior C mode allocates tentative globals in first-reference order.
C++ mode retains declaration order and pools their addresses, reproducing the
observed independent callback/table bases and every scalar offset. The prior
synthetic ordering function and out-of-bounds state overlays are removed.
The 32-byte unreferenced BSS object and final read-only word remain explicit
owned data, without inventing a purpose for them. Symbol sizes now distinguish
the scalar state, callback tables, diagnostic strings, and version pointer;
alignment bytes remain compiler-generated.

All 27 functions and all three owned sections match natively, including
relocations, with no object postprocessor or extra emitted function. The
original callback-registration upper-bound test compares the callback ID,
not the server type; this behavior is retained.

Validation passed for G9SE8P, the only configured release target: all-source
compilation, the complete linked build, 54 checker tests, both policy checks,
and all 18 artifact hashes. Independent ELF comparison also verifies identical
allocated section bytes/layout, all 117 normalized relocations, and all 27
function offsets/sizes with no extras. PAL and Japanese builds remain planned,
not configured. Compilation does not establish runtime or hardware validation.

Update this file after every migration batch. A path leaves the queue only
after its configured command, GameCube objdiff and final artifact hashes pass.

### Game Task translation unit

`game/Task.cpp` is reconstructed as C++.

Evidence and rationale:

- PS2 beta DWARF positively identifies the original translation unit as
  `Task.cpp` and supplies the `TMainTask`, `TObject`, heap, task-list, and sleep
  flag names;
- the GameCube virtual-table order, constructor record, exception tables, and
  mangled member symbols independently establish C++ classes and linkage;
- the retail GameCube object and the following PS2 `Memory.cpp` method order fix
  the boundary at `0x80016514`–`0x800189A4`;
- all 34 functions and every owned section match byte-for-byte in objdiff.

CodeWarrior must see mutually recursive inline and destructor bodies before
their retail call sites, but then emits their out-of-line copies in dependency
order. The post-compile normalizer moves those already-matching function and
exception-record units into the retail order and restores split symbol names;
it does not synthesize or alter instructions.

### Game memory translation unit

`game/Memory.cpp` is reconstructed as C++.

PS2 beta DWARF positively identifies `Memory.cpp`, the `THeapCtrl` and `sHeap`
types, all member fields, and all six methods. The contiguous GameCube method
order fixes the original boundary at `0x800189A4`–`0x80018C0C`. All six
functions and every owned section match byte-for-byte in objdiff.

As in `Task.cpp`, CodeWarrior emits the deleting operator before the destructor
whose cleanup uses it. The post-compile normalizer moves the already-matching
function and exception records into retail source order without changing
instructions.

### Game action translation unit

`game/action.cpp` is reconstructed as C++.

The GameCube object directly establishes the language through its mangled
`ACTION` and `FADESCREEN` member symbols, virtual calls, static initializer and
exception metadata. The preceding `Memory.cpp` boundary and the contiguous
retail symbols fix this unit at `0x80018C0C`–`0x8001D764`. All 61 functions
across the five retail split objects match byte-for-byte in objdiff.

`ACTION::Loop` needs `opt_lifetimes off` and a function-scope iterator aggregate
to reproduce CodeWarrior's original register interference graph. Its task loops
remain ordinary indexed C++ and compile to the retail pointer walks. The
post-compile helper restores split symbols, uses the existing retail
switch-table data, and removes a duplicate weak inline-destructor atom that
GC/1.3.2 emits only because the reconstructed unit is compiled in isolation.
It does not alter the instruction bytes of any retail function.

The five entries in `splits.txt` are build fragments of this one C++ source,
not evidence for five original translation units. The four continuation files
contain only an include of `action.cpp`; their purpose is to preserve the
retail object boundaries required by the MetroWerks linker.

### `game/SpAdvStgFailed.cpp`

The PS2 beta debug symbols identify the `SpAdvStgFailed` class, its
`StartFadeOut`, `Disp`, `Exec`, constructor, destructor, and `GoStageFailed`
family. The GameCube virtual table independently fixes the class relationship
and method ordering. The contiguous resource table, resource globals, exception
records, and seven-function code range establish the code object's owned
sections.

The 112-byte animation workspace at `0x80303EC8` is deliberately emitted by the
data-only build fragment `game/SpAdvStgFailed_bss.cpp`. A controlled GameCube
compile showed that the code object emits regular BSS after `hAnim.cpp`'s BSS,
while the retail workspace precedes it. Assigning both the code and workspace
to `SpAdvStgFailed.cpp` therefore creates a linker-order cycle; correlated PS2
names identify the data, but do not override this GameCube ownership evidence.

All seven functions and every assigned section, including the separate BSS
fragment, match byte-for-byte. GC/1.3.2 emits a duplicate weak copy of
`TObject::operator delete` when this reconstruction is compiled independently;
the post-compile normalizer removes that compiler-only atom and leaves
exception cleanup bound to the existing retail `TObject` delete routine. It
does not alter any retail function instruction bytes.

### CRI AXRNA compiler-mode exception

`game/cri/axrna.c` retains its reviewed vendor C boundary and explicitly uses
the existing GC/1.3.2 compiler in C++ mode. The AXRNA 1.02 banner, CRI stream
interfaces, adapter calls and GameCube AX/ARAM interfaces identify the module.
No correlated PS2 source marker establishes the historical language of this
GameCube-specific implementation; C linkage and compiler mode are separate
conclusions.

The seven private BSS objects are a reference count, aligned-buffer pointer,
two-word configuration, scalar configuration, 32-word workspace, 4,160-byte
buffer and sixteen 232-byte handles. Native C mode orders this storage by first
reference. Native C++ mode emits the required declaration-order pool, without
an unused ordering function or a postprocessor. The exception follows the
already reviewed CRI SFX vendor-boundary policy rather than asserting C++
source from a byte match. The signed `long` clamp/volume temporaries are 32-bit
target values; their recovered code generation does not establish an original
CRI typedef spelling.

The nineteen-function boundary is `0x80223500` through `0x80224CD0`, ending
with the error-callback setter. The following size/address getters and handle
destructor are grouped with RNARES's allocator, shutdown and initialization
by their GameCube data and call relationships. This is an inferred source
boundary, not direct filename metadata. AXRNA owns 500 bytes of `.rodata`,
128 bytes of `.data` and 8,020 bytes of `.bss`; the four bytes before the next
rodata/BSS units are linker alignment, not synthetic source padding. Internal
data names and local bindings record their recovered private roles, not
historical symbol spellings.

Chunk copies use CodeWarrior's `__memcpy` intrinsic for the actual eight-byte
descriptor operation. It emits only the native loads/stores, with no runtime
helper. Typed channel-array access and `slot * 2 + channel` let the compiler
derive the original constructor induction variables. The AX sample-rate
record contains the seven halfwords consumed by its native callee, and ARQ
request/callback declarations agree with the existing ARQ implementation.

The rate conversion uses a typed inline record-filling helper, with an explicit
signed-to-unsigned conversion for the adjusted rate. Signed 32-bit `long`
constants preserve the normal-rate calculation's native scheduling. This
replaces the inherited per-function `opt_loop_invariants off` override; the
completed unit needs no such optimization override or artificial barrier.

Initialization deliberately reads the version-banner pointer before testing
the reference count, even when already initialized. The value is subsequently
discarded. Independent native LSC and SJ initializers likewise load their
version anchors before initialization checks. The volatile pointer models this
observable read; the original qualifier and source spelling remain unknown.
It is not inferred to be mutable hardware state.

Validation covers all nineteen functions, all four allocated sections (bytes,
type, flags and alignment), 33 sized symbols and 166 resolved relocations.
The source-linked `G9SE8P` release/all-source build, 54 automated policy tests,
both policy checkers and all eighteen artifact hashes pass. This is build and
binary verification, not runtime or physical-hardware testing.

### CRI SJ family boundary correction

The previous `game/cri/sjrbf.c` fragment combined the preceding ring-buffer
implementation's error callback, SJUNI initialization state, and shared SJ
utilities. The corrected boundaries are inferred from GameCube code/data
relationships, with limited corroborating PS2 symbol metadata; no SJ source
filename marker was found. A shared version banner alone is not treated as
evidence to merge the neighboring SJCRS and SJMEM objects.

- `game/cri/sjrbf.c`, `0x80220BF0`–`0x80221574`: seventeen ring-buffer
  functions, including the error callback installed by its creator. Its
  256-entry, 64-byte object pool, reference count, UUID and vtable identify
  this implementation. PS2 `sjrbf_obj` is likewise 16,384 bytes; the SJRBF
  API and private data names corroborate these roles. The callback's error
  string belongs here.
- `game/cri/sjuni.c`, `0x80221574`–`0x80221610`: two surviving GameCube
  initialization functions, owning a separate reference count and 3,072-byte
  workspace. PS2 `sjuni_init_cnt` and `sjuni_obj` corroborate these objects.
  GameCube references to this state occur only in these two functions; the
  preceding ring-buffer vtable and pool are not SJUNI's. This does not
  reconstruct or claim the presence of the other PS2 SJUNI methods.
- `game/cri/sj.c`, `0x80221610`–`0x802218A8`: three shared tag-search,
  chunk-split and error-dispatch functions. The search owns the 448-byte
  hexadecimal lookup table, corroborated by `sj_hexstr_to_val_tbl` in PS2
  metadata. Both SJMEM and SJRBF call the error dispatcher.

The reviewed vendor C boundaries remain distinct from historical source
language. SJRBF uses the existing GC/1.3.2 compiler in C++ mode: native C
emits the object pool before the reference count, whereas C++ emits the
declaration-order storage required by the GameCube references. The removed
postprocessor had silently rewritten those symbol offsets. This is a
compiler-mode exception, not proof of original C++ source. SJUNI and the
shared SJ utilities retain C compilation.

Natural buffer-address association and record-pointer advancement replace
the instruction-reordering patches. The availability query uses explicit
integer success/failure returns; implicit C++ Boolean conversion produces a
different mask. No instruction patch, artificial storage pad, unused ordering
helper or per-function optimization override remains in these three units.
The four-byte gaps after SJRBF rodata and the two BSS groups are linker
alignment, not owned source objects. The initializer's version-anchor read is
observable in the native object; its historical qualifier remains unknown.

The shared creator contract takes a buffer pointer, which the implementation
stores and uses for byte-address arithmetic. The initial correction retained
`void*` chunk addresses; the subsequent SJMEM audit below supplies positive
signed-byte type evidence. The corresponding
AXRNA integer-address-to-pointer conversion preserves its complete native
object, including all nineteen functions and 166 relocations.

All twenty-two functions and all allocated sections are native-exact. The
independent audit compares section bytes, size, type, flags and alignment,
32 sized symbols and 79 normalized relocations across the three objects.
The source-linked G9SE8P release/all-source build, 54 automated tests, both
policy checks and all eighteen artifact hashes pass. Neighboring SJMEM and
SJCRS target objects are unchanged and their configured builds remain exact.
This is binary/build verification, not runtime or hardware testing.

### CRI SJMEM native reconstruction audit

The thirteen-function run `0x802205DC`–`0x80220BF0` is the memory-backed
stream implementation. Its creator installs the final error callback at
`0x80220BC8`; the UUID, twelve-slot vtable, reference count and 32-entry,
36-byte object pool belong to this same family. Limited PS2 symbols
corroborate `sjmem_uuid` (16 bytes), `sjmem_vtbl` (48 bytes), `sjmem_obj`
(1,152 bytes) and `sjmem_init_cnt`. No direct SJMEM source filename marker
has been established, so the boundary and historical language remain inferred.

The GameCube references require the reference count before the object pool.
Native C mode instead emits the pool at its first use, before the counter;
the prior object patcher rewrote the resulting BSS symbol offsets. As with
SJRBF, GC/1.3.2 C++ mode supplies declaration-order private BSS without
changing the vendor C boundary. The four-byte gaps after the 28-byte rodata
and 1,156-byte BSS regions are linker alignment, not synthetic source objects.

A narrow local PS2 `SLES_519.50` DWARF query with `stdump symbols --section
.debug dwarf` identifies `SJCK` at DIE `0x45bb75`: size eight, `data` at
offset zero with `pointer_to,signed_char`, and `len` at offset four with
`signed_integer`. `SJ_OBJ` at DIE `0x45b819` has size four and a vtable
pointer at offset zero. These are type facts only, not source or code
recovered from that platform. They support `CriChunk.addr` as `s8*` and
`size` as `s32`; historical GameCube qualifiers are not independently proven.
The corrected address type compiles throughout the source set and preserves
all allocated sections, 32 sized symbols and 79 normalized relocations of
the completed SJRBF, SJUNI and shared utility objects.

UngetChunk saves the original position and chunk length, computes a working
rewind value with compound subtraction, and selects that value only when the
original position-minus-length is positive. Both the condition and the
computed result participate in the stored position; there is no dead read,
empty condition or unused assignment. The compiler merges the repeated
subtraction. This expression shape is a reconstruction inference, not proven
historical source. Simplifying it to a direct ternary, or testing only the
working value, changes the native operand allocation or load ordering. Two
search candidates requiring empty conditions were rejected, not incorporated.

All thirteen functions now match natively. The independent whole-object
audit compares every allocated section's bytes, size, type, flags and
alignment: `.text` 1,556 bytes, `.rodata` 28, `.data` 48 and `.bss` 1,156.
All eighteen sized function/object symbols and 43 normalized relocations
match, with no extra emitted helper or import. The old instruction/symbol
postprocessor and synthetic storage pads are removed. The completed three
neighboring SJ units also pass their complete section/symbol/relocation audit.

The source-linked G9SE8P release and all-source builds, 54 automated tests,
both policy checks and all eighteen artifact hashes pass. The linker input
query selects the reconstructed SJMEM source object. The only configured
release target is G9SE8P; this is not runtime or physical-hardware validation.

### Complete native LSC family correction

The old error fragment and API slice are reconstructed as four coordinated
LSC source groups, collectively covering all 26 surviving functions and their
owned data. Independent state/constant atoms, public-call relationships and
minimal correlated PS2 symbol ordering support the inferred boundaries; no
source-file marker was found. All four remain reviewed CRI C boundaries,
compiled as ordinary C with the existing default auto-inlining settings.
No compiler/language exception or instruction postprocessor is introduced.

The complete allocated sections, 44 meaningful symbols and 150 normalized
relocations match. Undefined imports and defined zero-sized function/object
symbols are audited too. The source-linked release, all-source build,
54 tests, both policy checks and all eighteen hashes pass. See
[the LSC audit](cri-lsc-native-audit.md) for exact ownership, source-shape
inferences, observable banner read, shared type evidence and residual boundary
uncertainty.

### CRI ADX core library units

The CRI ADX core (ADXT/GC 8.84, ADXF/GC 7.07, SKG/GC 0.63, ADXGC 1.21,
ADXGCSDK 05Sep2002Patch2, CVFS/GC 2.33) is middleware compiled from CRI's C
sources. Its units are reviewed C boundaries: the exported API is plain C
linkage and the correlated PS2 symbol metadata carries no source-file record,
so no historical extension is claimed.

The library was built with deferred inlining. Three independent observations
agree for every unit that uses it: the GameCube text order is the exact
reverse of the per-file function order in the PS2 symbol metadata; the
string pools follow the GameCube (emission) order; and the uninitialised
private `.bss` objects appear in reverse declaration order. Ordinary
`-inline auto` reproduces none of these without invented helper code, while
`-inline deferred` reproduces the complete owned sections. Units that do not
depend on emission order keep the default CRI flags.

- `game/cri/cri_cvfs.c`: CVFS, 12 surviving functions, owned `.rodata` and
  `.bss`, `-inline deferred`. The GCCI read callback directly above it
  belongs to `game/cri/gcci.c`, whose lower bound moves down by four bytes.
- `game/cri/adx_mgc.c`, `game/cri/adx_sugc.c`, `game/cri/adx_gc.c` and
  `game/cri/adx_rnaa.c`: the ADXGC 1.21 thread manager, the ADXGCSDK DVD
  file-system glue, the sampling-rate switch and the nineteen ADXRNA wrappers
  over AXRNA, `-inline deferred`. Each opens with its own banner or follows
  the object order of the later CRI GameCube link map; all owned data is
  referenced only from inside the unit.
- `game/cri/adx_stmc.c`, `game/cri/adx_tlk.c`, `game/cri/adx_tlk2.c` and
  `game/cri/adx_xpnd.c` use `-inline deferred`; `game/cri/adx_tsvr.c` keeps
  the default CRI flags because its seven functions do not depend on emission
  order. `adx_tlk.c` keeps eighteen linker-stripped API entry points as short
  parameter-checking bodies: their messages survive in the retail string pool
  interleaved with compiler-generated floating-point constants, which only
  literal emission order reproduces. They are named from the PS2 symbol
  metadata and do not reach the linked executable.
- `game/cri/adx_inis.c`, `adx_amp.c`, `adx_crs.c`, `adx_errs.c`,
  `adx_fsvr.c`, `adx_insh.c`, `adx_lsc.c`, `adx_sfa.c` and `adx_dcd3.c` (all under
  `game/cri/`): ADXT initialisation, amplitude meter, critical section, error
  reporting, file server, SFA header insertion, seamless-entry API and SFA
  stubs and the stereo-as-mono decode switch, `-inline deferred`. `adx_lsc.c` keeps the linker-stripped
  `ADXT_StartFnameLp` (a PS2 symbol) because its inlined calls fix the order
  of the unit's string pool.
- `game/cri/adx_sje.c`: the ADX encoder (ADXSJE), sixteen functions,
  `-inline deferred`. The older 8.84 encoder has no CINF chunk and inlines
  the header writer, which is why `adxsje_output_header` is 0x13E8 bytes.

## message.cpp

The European PS2 debug metadata identifies `message.cpp` as C++ and gives the
`MESSAGE` class, font members, constructor/destructor and language-change APIs.
The GameCube member offsets, font paths, table lookup and call relationships
independently correlate the nine surviving functions at `0x800CE010`–`0x800CF070`.
The next function operates on an unrelated interpolation structure. GameCube's
`DisplayMessage` has two additional floating-point offset arguments; the PS2
signature is not substituted for this platform's ABI.

The source groups construction, destruction, font loading/release, rendering,
conversion and language-change entry points. Default `-inline auto` emits them
in source order and leaves the destructor out of the language-change paths.
`-inline deferred` reverses their emission into the observed GameCube order
and reproduces the inlined destructor/release loops and their exception records.
This is a caller/callee and exception-handling requirement, not just a function
permutation. Separate multiply/add instructions and the full-width comparison
result in the rendering code establish `-fp_contract off` and `-bool off`.

All nine surviving functions, exception records, relocation targets and owned
data now match natively in objdiff. `setupBBox` is an ordinary method whose
call is inlined and whose unused out-of-line body is stripped at link time;
retaining its definition also reproduces the original floating-point constant
order. Explicitly marking it inline instead places the constructor's height
constant before the bounding-box constants.

The language-change allocation uses global `operator new`. The existing subtitle
constructor mapping already identified the same allocation entry point, paired
with global `operator delete` and using the RenderWare allocator callback. Its
canonical name is now `__nw__FUl`; keeping a provisional class-specific wrapper
introduced an extra temporary register move. Existing callers and metadata
renames follow the canonical global symbol. No instruction post-processor is
used for message.cpp.

Validation for message.cpp: the native G9SE8P all-source build passes, including
the main DOL and all seventeen REL hashes. The object audit matches all eight
owned sections and 141 normalized relocations after excluding the 32-byte
`setupBBox` body that the linker map explicitly marks UNUSED. All 55 language,
post-processor and ELF metadata regression tests pass. This is compilation and
binary verification; no runtime or hardware validation was performed.


## pathctrl.cpp

Symbolic PS2 metadata positively identifies this whole translation unit as C++
and describes CLASS_PATH methods and private path-control helpers. GameCube
member accesses independently establish the 88-byte class and callback ABI.
All eight surviving GameCube bodies are reconstructed together; the metadata-named pathCalcRoughArea helper inlines into its three callers.
The metadata-named pathCheckRangeWithinArea2 also inlines into Seeing.
The remaining private range-helper operations stay inside their caller.

The unit uses ordinary C++ methods and default automatic inlining. Exception
handling is enabled for its six owned exception records; separate multiply/add
instructions motivate disabling floating-point contraction. Scheduling and
peephole optimization are disabled for the current native comparison, and
constant pooling is disabled. These settings remain subject to matching work.
No deferred-inline override, assembly stub or instruction patcher is used.
Four lifecycle bodies and Gliding instruction bytes are exact; three larger
routines, constant relocation offsets, constant order and
exception metadata remain NonMatching. See `pathctrl-unit-evidence.md` for
whole-unit boundaries, comparison results and complete build verification.

## c_colli_react.cpp

PS2 symbolic metadata positively identifies the complete collision reactor unit
as C++. GameCube virtual-base pointer accesses, four 60-byte allocations, and
fourteen adjusting thunks independently confirm virtual inheritance. The source
reconstructs all 42 surviving bodies and five inlined constructors using C++
classes; the compiler emits the thunks. Metadata also identifies the inline
CheckReactor and reference-count methods. No instruction post-processor is used.

All 42 bodies match instructions and normalized relocations. The deferred-inline
recipe uses base-first class definition groups and reproduces the five vtable
groups, fourteen compiler-generated thunk orderings, and extab records.
Original source line order remains unproven. Derived override declaration order
comes from GameCube vtable slots, not PS2 method-order metadata. A fail-closed
object step moves only the compiler-produced 28-byte weak SetDirection body to
the tail; it preserves every instruction and relocation meaning. With that
explicit layout normalization the complete linked DOL is byte-identical and all
18 supported output hashes pass. The whole unit is enabled as Matching.
See `c-colli-react-unit-evidence.md` for the inventory, evidence and remaining
compiler-emission gap.

## setObj.cpp

PS2 symbolic metadata identifies this complete unit as C++ and TObjSetObj as a
standalone eight-byte polymorphic class with SETOBJ_PARAM* at offset zero.
GameCube constructor/destructor vtable accesses and the sole EditOnChange slot
confirm the class correlation. Nine surviving bodies span 0x8005B8B8–0x8005BEC4;
SetDestroy and SetInit inline into lifecycle methods. No PS2 instructions were
inspected. All nine bodies and owned sections match, and the complete native-linked DOL
is byte-identical. The unit is enabled as Matching with no object normalizer. The destructor is nonvirtual; the class does not inherit
TObject. The previously reversed CheckMustKill/CheckRangeOut labels in three stage
wrappers are corrected with their call sites, preserving call order and targets.
See `setobj-unit-evidence.md` for the inventory and verification.

## Enemy render utility (`enemy/e_utility_render.cpp`)

Positive symbolic metadata identifies the complete eight-function `nRender`
unit as `C_PLUS_PLUS`. GC fog/light/state calls and four private saved-state
words independently establish ownership: text `0x801137AC–0x8011398C`, all
exception records, and `.sbss` `0x8042C658–0x8042C668`. Standard whole-unit
C++ automatic inlining produces eight exact bodies and all 51 effective
relocations, with no object postprocessor. The accessed external object views
use GC offsets and do not import PS2 alignment or layout. See
[e-utility-render-unit-evidence.md](e-utility-render-unit-evidence.md).
