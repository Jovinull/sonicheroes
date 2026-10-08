# Complete enemy-link translation unit evidence

Positive C++ metadata identifies enemy/e_link.cpp and eighteen file-origin
definitions. Ten bodies survive in GameCube, including the key-node constructor
and manager operations. The remaining link/loop/chain helpers and manager
constructor are inlined. No PS2 instructions were inspected.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| UnlinkKey__11ObjEnemyKeyFv | 0x800fd6f0 | 432 |
| __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID | 0x800fd8a0 | 348 |
| __dt__12TObjEnemyManFv | 0x800fd9fc | 544 |
| CreateEffect__12TObjEnemyManFUiUi | 0x800fdc1c | 292 |
| TaskResume__12TObjEnemyManFUi | 0x800fdd40 | 280 |
| TaskSleep__12TObjEnemyManFUi | 0x800fde58 | 280 |
| SendCommand__12TObjEnemyManFUiP15sEnemyCommandEx | 0x800fdf70 | 288 |
| SendCommand__12TObjEnemyManFUiP13sEnemyCommand | 0x800fe090 | 248 |
| DestroyInstance__12TObjEnemyManFv | 0x800fe188 | 72 |
| CreateInstance__12TObjEnemyManFv | 0x800fe1d0 | 120 |

The complete text occupies 0x800FD6F0–0x800FE248 (2,904 bytes). The preceding
stub belongs to the separate TObjEnemy class and vtable; the following body
begins the independently reconstructed motion unit. Owned exception records
occupy 0x80009768–0x800097B8 (80 bytes), with eight index rows at
0x8000FD60–0x8000FDC0. Data at 0x8025A850–0x8025A890 contains the manager
class string, its 44-byte vtable and alignment. The class-name pointer at
0x8042B728 and singleton at 0x8042C578 are each four-byte objects followed by
four-byte alignment. The singleton's original name is unknown, so its
address-based label is retained. A twelve-byte local zero-angle initializer in
CreateEffect owns read-only data at 0x8023A760–0x8023A770, including four trailing
alignment bytes. The only code reference is inside CreateEffect; adjacent data
belongs to functions outside this unit, and the metadata-backed sAngle is three
signed integers. No floating-point constants, large BSS or static constructors
are annexed.

ObjEnemyKey is 0x20 bytes and TObjEnemyMan is 0x2C bytes, matching metadata
and GameCube accesses. Public manager commands are static and return void;
incidental values left in r3 do not establish a return value. The referenced
TObjEnemy layout and virtual slots require GameCube correlation rather than
copying older platform offsets. The local TObjEnemy view exposes only fields accessed here: ObjParam at 0xB0,
EnemyID at 0x13C, position at 0x140 and pKey at 0x228. The latter is four bytes
later than the older platform metadata. Unidentified virtual slots retain
explicit provisional names rather than invented original method names.

Loop mutations during dispatch preserve the original order of pointer reads.
The extended command dispatch uses distanceSquared < radiusSquared: the
GameCube branch skips the callback when the comparison is unordered, including
NaN. An initial reconstruction using !(distanceSquared >= radiusSquared) was
rejected during instruction comparison because it changes that behavior.
The key constructor searches only an existing manager loop and chooses LoopKey
for a missing link group or LinkKey for an existing one before ChainKey.
CreateInstance stores the allocation result into the singleton even on failure.

The normal whole-TU automatic-inlining recipe enables exceptions and disables
scheduling, peephole optimization, contraction and constant pooling. All ten
surviving bodies match directly from C++ with no object normalizer. Reproducing
the command loop requires checking the manager loop before introducing the
search-result local and retaining the null check at the top of the inner loop.
No deferred-inline override, assembly body or per-function compiler setting is
used; these are reconstruction settings, not recovered historical flags.

Independent object comparison verifies all ten bodies, their layout and
bindings, all sixty effective surviving relocations, the eighty exception bytes,
eight exception-index rows, and all owned storage payloads. Ordinary definitions
of the eight authentic inlined methods also produce 692 bytes of unused code;
a weak TObject delete adds forty bytes. Two additional exception/index records
belong to the unused manager constructor and weak delete. The final map confirms all eight helpers are unused, the weak delete is an
unreferenced duplicate of the strong Task definition at 0x8001895C, and their
extra exception/index records are discarded by the normal linker. Four-byte tails in read-only
data, data, small data and small BSS are natural final section alignment.

Nine existing source consumers and three existing symbol fixers receive only
canonical same-address renames and formatting, independently checked against
the base. The unit is enabled as Matching. The first full link exposed the inherited
TObject::Exec symbol still under its address label; the symbols and existing
fixers now use its canonical name, and all affected targets were rebuilt.

All supported G9SE8P targets compile: the main DOL and seventeen RELs pass all
eighteen expected output hashes. Independent final ELF/map comparison verifies
every owned linked byte, body address, section flag and alignment, including
natural tails and discarded-helper accounting. All 62 automated tests and the
language/post-processor checks pass. This is compilation and binary comparison;
no runtime or hardware validation was performed.
