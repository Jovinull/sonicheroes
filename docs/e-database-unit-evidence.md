# Enemy database translation unit evidence

Symbolic metadata identifies `enemy/e_database.cpp` (CU `0x56196c`) as
C++ and supplies TEnemyDataBase, its enums, record layouts and methods.
GameCube resource-loader calls, extension dispatch, fourteen-record constructor
and singleton independently establish the correlation. No PS2 instructions
were inspected. This unit uses the completed ONEFILE interface from PR #569.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| `GetAnimationNum` | `0x801001DC` | 64 |
| `GetFileNum` | `0x8010021C` | 16 |
| `SearchCameraMotion` | `0x8010022C` | 84 |
| `SearchUVAnim` | `0x80100280` | 84 |
| `SearchHAnim` | `0x801002D4` | 84 |
| `SearchTexDictonary` | `0x80100328` | 84 |
| `SearchClump` | `0x8010037C` | 84 |
| `SetUpFiles` | `0x801003D0` | 1060 |
| `Delete` | `0x801007F4` | 376 |
| `Add` | `0x8010096C` | 136 |
| destructor | `0x801009F4` | 184 |
| constructor | `0x80100AAC` | 124 |

All twelve bodies occupy `0x801001DC–0x80100B28` (2,380 bytes).
Header singleton helpers have no surviving out-of-line bodies in this unit.
The original SearchTexDictonary spelling is retained. Owned exception records
occupy `0x8000984C–0x8000987C` (48 bytes), their index occupies
`0x8000FE50–0x8000FE80` (48 bytes), strings occupy
`0x8042B740–0x8042B778` (49 payload bytes plus seven alignment bytes), and
singleton storage occupies `0x8042C590–0x8042C598` (four bytes plus four
alignment bytes). The singleton symbol size is corrected to four bytes.
There are no other owned allocated sections, vtable or constructor list.
The Action global and RenderWare globals remain external; the metadata's
zero-address crash-vector declaration contributes no storage.

The class is 0x70 bytes: fourteen eight-byte records, each holding a resource
array pointer and signed file count. Each resource entry contains a kind enum
and pointer. Construction zeros the records and publishes the singleton.
Destruction only zeros the records: it neither releases resources nor clears
the singleton. Delete releases resources in reverse order, releases texture
dictionaries in a second reverse pass, then frees the entry array; it does
not clear the containing pointer/count. These observed lifecycle contracts
are preserved. Search indices are unsigned and retain the resource-kind gate.

SetUpFiles scans 256 archive filename slots, allocates two spare records,
loads the first available texture dictionary before other resources, then
processes clumps, animations, UV animations, splines and camera motions.
Stages 27 and 28 use a 0x190000-byte temporary buffer; other stages use
0xAF000. Type-one animations are compressed and the original is destroyed.
Add constructs a genuine ONEFILE and preserves its C++ allocation/destruction
and exception cleanup. The filename helper uses the first dot and a four-byte
comparison, matching both symbolic inline-helper metadata and GameCube code.
No additional null guards or ownership changes are introduced.

## Caller ownership and failure paths

| Entry kind | ONEFILE loader | Database cleanup | Ownership evidence |
| --- | --- | --- | --- |
| `CLUMP` | `OneFileLoadClump` | `fn_80150958` | Database owns the loaded clump; `SearchClump` returns the stored pointer. |
| `ANIMATION` | `OneFileLoadHAnimation` | `fn_8020C2D8` | Database owns the stored or compressed animation; motion tables clear `pHAA` before unload. |
| `UVANIMATION` | `OneFileLoadUVAnim` | `fn_8011B7CC` | Database owns the animation; callers use returned pointers as references. |
| `SPLINE` | `OneFileLoadSpline` | `fn_8014D8A4` | Database owns the loaded spline. |
| `CAMERAMOTION` | `OneFileLoadCameraTmb` | `fn_80132750` | Loader allocates through the ONE memory-function table; the paired release helper is external. |
| `TEX` | `OneFileLoadTextureDictionay` | `fn_801A46D0` | Database owns the dictionary; `SetUpFiles` also installs it as the current dictionary. |

The public `Search*` methods return raw pointers without retaining them. The
searcher, pawn, capture, and stage enemy unload hooks end their texture wrappers
and clear motion-table references before deleting the corresponding database
entry. `TEnemyMtnPathData` retains database pointers; `TEnemyMtnPath` passes its
model through `fn_80150588` and later destroys its own `mpClump`. That copy
relationship is corroborated by the separate teardown, but the helper's exact
RenderWare contract is not recovered here.

Failure behavior remains retail behavior. `fn_80012994` can return null when
the game heap has no fitting high-pool block, but `SetUpFiles` does not check
its temporary buffer before passing it to `OpenData`/`Expand2`; the expander
writes through its destination for non-empty data. `OneFileLoadHAnimation` can
return null, while `SetUpFiles` dereferences `anim->interpInfo` immediately.
Other typed loaders store their result after setting the entry kind, so cleanup
may pass a null resource to an external destructor whose null contract is
unknown. `ONEFILE::LoadOneFile` separately leaves its opened stream unclosed if
its archive allocation fails; see `one-unit-evidence.md`.

`Delete` frees the entry array but retains its address and count. A second
delete or a query before a subsequent successful `SetUpFiles` would use stale
state; repeated unload was not found in the inspected caller paths, so this is
a verified state hazard with practical reachability unproven. `SetUpFiles`
counts all non-empty names, then processes only IDs `[0, count + 1]`; this
assumes archive IDs are densely populated from 2. A read-only inspection of
the local retail image resolved that assumption for the enemy package set
referenced by the DOL/REL filename strings: 16 static `en_*.one` packages and
nine stage-specific `%s_flyer.one` resolutions. All 25 packages had populated,
NUL-terminated names at dense IDs 2 through the last entry; each ID had an
in-bounds data chunk with the same ID, and the outer, directory, and data chunk
lengths consumed the archive exactly. This confirms only those 25 packages,
not every ONE archive on the disc.

Across those packages, 544 entries were inspected. Each of the 16 static
enemy packages contained one TXD, while the nine stage flyer packages
contained none; the first-successful-TXD break therefore skips no additional
TXD in this set. A bounded expansion matching `Expand2`'s bitstream rules
decoded all 544 entries with a 16 MiB per-entry cap. The 531 DFF/TXD/ANM/UVB
outputs had the expected RenderWare chunk type and declared length; 13 TMB
streams terminated within their chunk bounds but were not runtime-parsed. The
largest expanded resource was 649,470 bytes, below the `0xAF000` (716,800 byte)
scratch buffer. This validates the sampled file data and capacity comparison;
it does not prove allocator success, RenderWare object construction, or runtime
behavior. None of these failure cases are changed in the matching source.

The audit also replaced divergent local declarations of `TEnemyDataBase` and
`eEnemyDataBase` in the six game consumers with the canonical header. The two
translation-unit views of the accessed `RtAnimAnimation` prefix are now shared
in `game/rtanim.h`. A CodeWarrior build and direct object diffs against the
pre-change object snapshots preserved the relevant function, data, exception,
and relocation content; the complete G9SE8P build retained all 18 reference
hashes. The `e_database.cpp` object remained byte-identical after correcting
the local allocator declaration from signed to unsigned size.

The animation-destroy return is a pointer, corroborated by its GameCube body;
UV-animation destruction returns signed int, also corroborated by symbolic SDK
metadata. Camera-motion release remains a provisional void declaration whose
return is unused. Array allocation/deallocation names are supported by
Debug.cpp metadata. All fifteen canonical symbol substitutions in ten existing
caller files preserve token-level behavior apart from formatting.

All twelve functions match directly from C++ with automatic inlining. No
object normalizer or deferred-inlining override is introduced. All function
identities, offsets, sizes and bindings match; all 67 effective relocations
and section flags/alignments match. Text and exception sections are byte-exact;
string and singleton sections agree including natural linker tail alignment.

Validation: the supported G9SE8P main DOL and all seventeen RELs compile and
all eighteen reference hashes pass. All-source compilation, progress/report
generation, 55 automated tests and both language/post-processor policies pass.
Independent code/layout and ELF audits agree. Compilation and binary comparison
do not establish runtime or physical-hardware validation.
