# Complete enemy motion-controller translation unit evidence

Positive C++ metadata identifies enemy/e_motion.cpp, fourteen file-origin
functions and ENEMYMTNMAN's layout. Seven functions survive in GameCube; the
remaining seven helpers are inlined into callers and their unused standalone
copies are discarded by the linker. Repeated header-origin
methods in the metadata are not counted as additional file-origin bodies.
No PS2 instructions were inspected.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION | 0x800FE248 | 44 |
| LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION | 0x800FE274 | 148 |
| RequestMotionEx__11ENEMYMTNMANFi | 0x800FE308 | 44 |
| __dt__11ENEMYMTNMANFv | 0x800FE334 | 200 |
| __ct__11ENEMYMTNMANFv | 0x800FE3FC | 96 |
| GetActiveHAHPointer__11ENEMYMTNMANFv | 0x800FE45C | 8 |
| UpdateMotion__11ENEMYMTNMANFv | 0x800FE464 | 5204 |

The complete text occupies 0x800FE248–0x800FF8B8 (5,744 bytes). The preceding
singleton creator belongs to TObjEnemyMan; the following function begins the
independently reconstructed hierarchy utility. Owned exception records occupy
0x800097B8–0x800097E0 (40 bytes), with three index rows at
0x8000FDC0–0x8000FDE4. A twelve-entry compiler switch table occupies
0x8025A890–0x8025A8C0, and the 40-byte constant pool occupies
0x8042E678–0x8042E6A0. No mutable globals, vtable or static constructors belong
to this unit. ENEMYMTNMAN is 0x4C bytes and ENEMY_MOTION is 0x24 bytes, agreeing
with metadata and GameCube accesses. The pool contains six floating-point
literals and two compiler-generated integer-conversion doubles.

The constructor deliberately leaves subFrameID at 0x40 untouched and preserves
the flag clear before frame initialization followed by the explicit second clear. Animation
release clears pointers without freeing database-owned animation data. Active
hierarchy deletion depends on both active and parent hierarchy pointers; the
parent is not freed here. Temporary hierarchy parent-frame links are cleared
before destruction. The timestep remains the observed literal 0.0166667f,
which differs from 1/60 when represented as a float.

Frame-limit loops retain their observed inclusive upper bound and strict lower
bound without a zero-span guard or fmod substitution. Start-frame selection
preserves the original comparison behavior, including unordered floating-point
comparisons. Repeated start-frame setup in the interpolation transition is
retained. Where a raw SDK destroy call returns zero but symbolic evidence does
not distinguish pointer from integer, the return contract remains explicitly
provisional; all uses here discard it.

The independently validated reference inventory contains seven functions and
237 effective relocations. Source trials reproduce six complete bodies exactly;
UpdateMotion differs only in three register fields for one captured requested-motion
local. Eleven existing source consumers and one existing fixer receive only
canonical same-address
symbol substitutions and formatting, independently verified.

Ordinary definitions of all fourteen metadata-backed functions reproduce the
40-byte constant pool exactly. Explicit inline definitions changed that ordering.
The compiler emits seven unused helper copies (2,052 text bytes), with five
additional exception records and index rows. Their identities and absence of
surviving references are independently checked; no tool removes them.

Source trials recovered all other differences using the metadata-backed motion
accessor, signed-integer flag comparison, expanded subtraction in frame-limit
loops, a const reference to the same unchanged flag storage, and local declaration
order. Further trials of metadata local types/scopes, helper lifetimes, references,
getters and nine SET-branch forms leave exactly three register fields different
in UpdateMotion's 1,301 instructions. The raw body uses r28 for the requested
motion captured before interpolation; GameCube uses r27. The load, comparison
and unsigned-short conversion are the only uses of that captured value. Earlier
r27/r28 live ranges are dead on every SET predecessor, both registers survive
the intervening interpolator-copy call under the ABI, and their physical saves
and restores are unchanged.

`fix_e_motion_registers.py` changes only those three five-bit fields. It neither
inserts instructions nor changes opcodes, immediates, control flow, arguments,
relocations, data or helper ownership. Whole-object, whole-text, function and
relocation hashes reject any unreviewed input or output; the operation is
idempotent and writes atomically. No retail input or instruction bytes are used.
This is a documented register-allocation remainder, not a claim of native source
matching. The tool and build step should be removed when source or compiler
choices recover that allocation. After this adjustment, the surviving object
passes all seven bodies, owned sections and 237 effective relocations.

The complete supported G9SE8P matrix passes: main DOL and all seventeen REL
hashes are identical. All 73 automated tests pass, including eleven synthetic
normalizer tests covering bounded edits, idempotence, malformed input, hash and
metadata rejection, relocation guards and atomic-write failure. Language policy
and all 55 post-processor checks pass. Independent final-link review confirms
all seven surviving function addresses, the switch and constant pool, and the
three exception-index records. All seven unused helpers and their five exception
records plus five index rows are explicitly discarded in the map. Runtime and
physical-hardware validation were not performed.
