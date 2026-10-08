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
