# Complete material.cpp unit

## Boundary and language evidence

Local symbolic metadata identifies `material.cpp` as C++, its `DealMaterial`
class, two constructor overloads, nonvirtual destructor, seven public state
operations, and nineteen internal callbacks. GameCube call targets and field
accesses independently establish the complete 29-function range
`0x80119588–0x80119FE8`. The neighboring routines operate on unrelated objects
and are excluded. No PS2 instruction bytes or generated decompiler output are
included.

`DealMaterial` is 20 bytes: clump pointer at 0, atomic pointer at 4, material
count at 8, saved colors at 12, and saved texture pointers at 16. The target
accesses also confirm atomic geometry at `0x18`, geometry material count at
`0x24`, material color at 4, and texture reference count at `0x54`. The private
RenderWare engine view leaves its unused prefix opaque and exposes only the
allocation and release callbacks observed at `0x134` and `0x138`.

The destructor restores saved colors and textures, frees both snapshot arrays,
then releases the retained texture references. C++ generates the ordinary
conditional deleting-destructor call. The constructors retain the original
clump and atomic paths, including the texture-geometry flag and reference-count
updates. Existing stage callers retain their interfaces; their symbol changes
are mechanical same-address renames.

## Compiler emission evidence

The unit uses C++ with `-inline auto,deferred,level=2`. With the same source and
ordinary automatic inlining, 28 of 29 bodies match; the destructor is 196 bytes
instead of 320 because the nested restoration calls are not expanded as in the
GameCube body. Deferred level 1 gives the same mismatch. Level 2 reproduces the
nested inlining and all 29 bodies, including the separately emitted public
methods. This is a unit-local override, not a project-wide setting.

Deferred compilation emits definitions in reverse lexical order. Listing the
complete definitions in reverse address order reproduces the retail function
and exception-table order directly from the compiler. This is a verified
reconstruction, not a claim about the lost original lexical source order. No
instruction patcher, object normalizer, fabricated padding, or extra function
is used.

## Owned sections and verification

| Section | GameCube range | Bytes |
| --- | --- | ---: |
| `.text` | `0x80119588–0x80119FE8` | 2656 |
| `extab` | `0x8000AA64–0x8000AB24` | 192 |
| `extabindex` | `0x80010B1C–0x80010C3C` | 288 |
| `.sbss` | `0x8042C6A0–0x8042C6A8` | 8 |
| `.sdata2` | `0x8042EAA8–0x8042EAB0` | 8 |

The two small globals are the material counter and current geometry. The only
owned floating payload is the integer-to-double conversion constant. The
RenderWare engine pointer is external storage, not part of this unit.

Independent complete-source checks verify all 29 instruction bodies, their
relocation targets and addends, every function offset, all 24 exception records,
48 exception-index relocations, both global offsets, and the complete conversion
constant. No additional allocated sections or surviving functions are emitted.

The native `Matching` build passes all 18 configured G9SE8P image hashes: the
main DOL and 17 RELs. All 62 relevant automated tests and the source-language
and object-postprocessor policy checks pass. These are compilation and binary
identity checks; no runtime or physical-hardware validation was performed.
