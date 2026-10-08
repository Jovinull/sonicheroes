# Vertical collision translation unit evidence

Local PS2 symbolic metadata identifies `vertical_colli.cpp` as C++ and lists
`GetShadowPos(RwV3d*, sAngle*, s32)` plus two polygon callbacks. GameCube
`0x800D8BC4–0x800D8D2C` contains exactly those three surviving bodies (360 bytes).
The preceding unit is texture handling; the following player path-acceleration
code belongs to a separate unit and is excluded.

The unit owns eight exception bytes at `0x80008CA8–0x80008CB0`, twelve exception
index bytes at `0x8000F3DC–0x8000F3E8`, and sixteen constant bytes at
`0x8042E080–0x8042E090`. The external octree pointer is not owned here.

Metadata and GameCube accesses agree on the 32-byte POLYDATA layout, normal
vector at offset 12, and signed 32-bit angle components. The octree method
`DetectAxisYCollisionWithPolygons` receives the start point, a -250 vertical
extent, result point, and callback. Missing octree or collision returns
-1000000; valid collisions return the intersection height. Optional angles
update x and z, preserving y and the retail order of conversion and negation.

The callbacks both return 1 in this GameCube build. Their names are assigned
from the IgnoreWater branches: the callback at `0x800D8D24` corresponds to
IgnoreWater=1, and `0x800D8D1C` to IgnoreWater=0. This is a semantic inference
from metadata names and GameCube callers, not a surviving GameCube symbol or
a claim that callback emission order is identical across platforms.

All three bodies, normalized relocations, exception bytes, and constants
match with ordinary C++ and whole-unit compiler options. No post-processor
is added. Canonical symbols are propagated through existing callers and the
existing signal lifecycle relocation map; provisional caller types are retained.
The native Matching unit produces a byte-identical main DOL. The complete
supported G9SE8P build and all eighteen output hashes (main DOL and seventeen
RELs) pass, including a final rebuild after formatting. All 62 relevant tests
and both policy checks pass. No runtime or physical-hardware validation is
claimed.
