# Set-object base translation unit evidence

PS2 symbolic metadata identifies `setObj.cpp` as C++. The GameCube constructor
and destructor reference one three-slot vtable whose sole method is
`TObjSetObj::EditOnChange`. Their field accesses corroborate the metadata's
eight-byte standalone class: `SETOBJ_PARAM* ObjParam` at zero and the compiler's
vptr at four. The class does not inherit TObject, and its destructor is not
virtual. No PS2 instructions were inspected.

| GameCube address | Bytes | Method |
| --- | ---: | --- |
| `0x8005B8B8` | 4 | `TObjSetObj::EditOnChange` |
| `0x8005B8BC` | 28 | `TObjSetObj::CheckMustKill` |
| `0x8005B8D8` | 8 | `TObjSetObj::OnEdit` |
| `0x8005B8E0` | 272 | `TObjSetObj::CheckRangeOutWithoutIgnorRangeFlag` |
| `0x8005B9F0` | 304 | `TObjSetObj::CheckRangeOut` |
| `0x8005BB20` | 228 | `setobjCheckRangeOut2(const RwV3d*, f32)` |
| `0x8005BC04` | 312 | `TObjSetObj::SetEnd` |
| `0x8005BD3C` | 304 | `TObjSetObj::~TObjSetObj` |
| `0x8005BE6C` | 88 | `TObjSetObj::TObjSetObj` |

All nine surviving bodies occupy `0x8005B8B8–0x8005BEC4` (1,548 bytes).
Metadata-named `SetDestroy` and `SetInit` inline into lifecycle methods.
The preceding body operates on another object's fields, while the following
body uses a clump/atomic layout; both are excluded.

| Owned section | Start | End | Bytes |
| --- | --- | --- | ---: |
| extab | `0x800067AC` | `0x800067D4` | 40 |
| extabindex | `0x8000D0FC` | `0x8000D138` | 60 |
| .text | `0x8005B8B8` | `0x8005BEC4` | 1548 |
| .data | `0x80243408` | `0x80243418` | 16 |
| .sdata2 | `0x8042D448` | `0x8042D460` | 24 |

The vtable occupies 12 bytes followed by four alignment bytes. All 24 bytes of
the constant pool match. No BSS or small-BSS ownership is inferred from external
references. In particular, `0x8042C298` is the generator pointer `SetGenTp`,
created by the preceding generator implementation; it is not StageObjTop.

`SETDATA_PARAM` occupies 48 bytes and `SETOBJ_PARAM` 64. The latter embeds set
parameters, an opaque original-work pointer, linked-list pointers and an object
pointer. The bit-flag wrapper contains one unsigned word. Metadata identifies
`PlayerMaster::GetPlayerPositionHistory(s32, u8)`,
`TObjTeam::GetLeaderPlayerNo() const`, and
`TObjSetGen::RebuildCommunicateIdList(u8)`; GameCube accesses and caller behavior
corroborate those interfaces. Inline leader lookup reproduces argument
preparation, and a local bit-flag reference preserves the separate condition
reads in destruction. The range methods cache the set parameter and assign a
single result through ordinary conditional branches.

Canonical symbol names replace address names in existing callers and object
metadata tools. Three stage wrappers previously labeled the must-kill and
range-out methods in reverse; their wrapper names and call sites are corrected
together, preserving call targets and evaluation order. Other existing
provisional caller layouts are not claimed to be fully reconstructed here.

All nine bodies match instructions and normalized relocations, and all direct
game/SDK call targets and counts agree. No object post-processor is added for
this unit. The complete main DOL is byte-identical with the source unit enabled as
Matching. The supported G9SE8P main DOL and all 17 RELs compile and pass all 18
reference hashes. Relevant policy/ELF tests and language/post-processor policy
checks pass. Compilation and binary comparison do not claim runtime validation.
