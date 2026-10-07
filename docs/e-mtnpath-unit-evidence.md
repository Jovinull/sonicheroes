# Enemy motion-path translation unit evidence

Symbolic metadata identifies `enemy/e_mtnpath.cpp` as C++ and supplies the
complete TEnemyMtnPath and TEnemyMtnPathData method inventory. GameCube callers,
class string, virtual table, constructor field accesses, model cloning and
animation-table setup independently corroborate this identity. No PS2
instructions were inspected. The GameCube object layout and update behavior
remain authoritative where the other platform differs.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| `TEnemyMtnPath::GetMtnPathMatrix` | `0x8011F894` | 28 |
| `TEnemyMtnPath::SetPath` | `0x8011F8B0` | 80 |
| `TEnemyMtnPath::ChangePath` | `0x8011F900` | 88 |
| `TEnemyMtnPath::Disp` | `0x8011F958` | 4 |
| `TEnemyMtnPath::Exec` | `0x8011F95C` | 36 |
| `TEnemyMtnPath::~TEnemyMtnPath` | `0x8011F980` | 204 |
| `TEnemyMtnPath::TEnemyMtnPath` | `0x8011FA4C` | 304 |
| `TEnemyMtnPathData::SetUpMotionTable` | `0x8011FB7C` | 536 |
| `TEnemyMtnPathData::~TEnemyMtnPathData` | `0x8011FD94` | 120 |
| `TEnemyMtnPathData::TEnemyMtnPathData` | `0x8011FE0C` | 64 |

These ten bodies occupy `0x8011F894–0x8011FE4C` (1,464 bytes). The three data
getters inline into the path constructor. The preceding complete game2pTable
inventory ends at the first getter; the following body uses unrelated globals
and strings. No remaining metadata method warrants annexing that next body.

| Owned section | Start | End | Bytes |
| --- | --- | --- | ---: |
| extab | `0x8000AF1C` | `0x8000AF94` | 120 |
| extabindex | `0x80010F3C` | `0x80010F9C` | 96 |
| .text | `0x8011F894` | `0x8011FE4C` | 1464 |
| .data | `0x80289A78` | `0x80289AB8` | 64 |
| .sdata | `0x8042B8F8` | `0x8042B900` | 8 |
| .sdata2 | `0x8042EBE0` | `0x8042EBF0` | 16 |

Data contains the class string and eleven-word virtual table; small data holds
the class-name pointer; constants are zero, one and negative one. Each of these
three data sections has four trailing alignment bytes beyond compiler payload.
There is no owned BSS or constructor list. The database singleton and task heap
remain external references.

TObject occupies `0x28`, with its primary vptr at `0x18`. ENEMYMTNMAN occupies
`0x4C` as the second nonvirtual base. GameCube path objects occupy `0xD0`:
clump/frame pointers at `0x74/0x78`, the plain four-aligned matrix at `0x7C`,
and path state at `0xBC–0xCC`. The PS2 matrix alignment and `0xE0` class extent
are not imported. The frame declaration exposes only the accessed prefix and
must not be used to allocate a full frame. The matrix identity operation
preserves the native flags OR, rather than initializing additional fields.

The path object owns its cloned model and optional path-position array. The
separate data object owns its motion array but borrows its model from the
database. Setup constructs the database singleton when absent, counts files
and animations, allocates one extra sentinel motion, and preserves the first
model found. Genuine C++ array allocation/deallocation produces native calls
and exception cleanup. Debug.cpp symbolic metadata positively identifies the
adjacent array/scalar allocation wrappers; the GameCube size parameter uses
its compiler's unsigned-long spelling.

The authentic ENEMYMTNMAN constructor, destructor and `UpdateMotion` declaration
produce base construction, cleanup and direct member calls. UpdateMotion's
identity is independently present in e_motion.cpp symbolic metadata and agrees
with native accesses to the motion manager. Ordinary automatic inlining emits
the complete unit in the observed order; no deferred override or object
post-processor is added.

Canonical names replace address labels for the recovered APIs, database
methods, array operators and inherited TObject::TDisp slot. Existing source
callers and metadata rename tools are updated together, preserving call
arguments and targets. Their older provisional class names/signatures are
outside this reconstruction and are not asserted corrected here.

All ten body identities, offsets, sizes and global bindings match, as do text,
exception tables and all 70 effective relocations. The compiler marks its
constant section writable in ELF metadata where the reference marks it
read-only; its payload is identical. The supported G9SE8P main DOL and all 17 RELs compile and pass all 18
reference hashes. All 62 automated tests and both language/post-processor
policies pass. The whole unit is enabled as Matching.
Compilation and binary comparison do not establish runtime validation.
