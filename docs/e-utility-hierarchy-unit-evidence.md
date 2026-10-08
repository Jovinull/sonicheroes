# Enemy hierarchy utility translation unit evidence

C++ symbolic metadata identifies `enemy/e_utility_hierarchy.cpp` and exactly
three functions in `nHierarchy`. Their signatures have no implicit object
parameter. GameCube motion-manager calls, callback-address references and
recursive child traversal independently corroborate the namespace inventory.
No PS2 instructions were inspected.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| `nHierarchy::SetHierarchyForSkinAtomic` | `0x800FF8B8` | 84 |
| `nHierarchy::GetHierarchy` | `0x800FF90C` | 92 |
| `nHierarchy::GetChildFrameHierarchy` | `0x800FF968` | 100 |

All 276 surviving text bytes occupy `0x800FF8B8–0x800FF9CC`. Owned exception
records occupy `0x800097E0–0x800097F8` (24 bytes), with their index at
`0x8000FDE4–0x8000FE08` (36 bytes). There are no owned data, literal, BSS or
constructor sections. The metadata's zero-address ENEMY_CRASH_POWER entry is
a declaration, not a storage definition. The callback's function-pointer
metadata is not a separate data object.

The preceding ENEMYMTNMAN motion update ends at the first callback. It calls
GetHierarchy and passes SetHierarchyForSkinAtomic to clump traversal. The
following body starts an unrelated task allocation/construction sequence.
Those callers, all three metadata roles and the recursive callback address
establish boundaries independently of the exception-record grouping.

The source exposes only accessed RenderWare prefixes: clump frame parent at
`+4`, atomic geometry at `+0x18`. It does not allocate those partial views.
Frames, skins and hierarchies remain opaque. The frame-hierarchy getter returns
`RpHAnimHierarchy*`; it does not return a frame. Skin assignment is conditional
on the geometry having skin. Root lookup initializes its output to null, and
the callback stores a found hierarchy and returns null to stop that traversal.
The no-hierarchy path recurses and returns its original frame, preserving the
native callback contract and search behavior. No extra null guards are added.

All three bodies match directly with ordinary automatic inlining. No deferred
override, assembly implementation or object normalizer is added. Canonical
namespace symbols replace the three address labels; no decompiled caller
required a source update. All three function identities/bindings/offsets/sizes, every allocated section
and all 16 effective relocations match exactly. The supported G9SE8P main
DOL and all 17 RELs compile and pass all 18 reference hashes. All 62 automated
tests, both language/post-processor policies and source-format hooks pass. Compilation and binary comparison do not
establish runtime validation.
