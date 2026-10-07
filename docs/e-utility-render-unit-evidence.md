# Enemy render utility translation unit evidence

Symbolic metadata identifies `enemy/e_utility_render.cpp` as C++ and supplies
all eight `nRender` functions and their parameter types. GameCube calls to the
render-state API and `CLIGHT` establish their identities independently of
other-platform address order. No PS2 instruction bodies were used.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| `FogDisable()` | `0x801137AC` | 40 |
| `FogEnable()` | `0x801137D4` | 40 |
| `DisableLight(s32)` | `0x801137FC` | 60 |
| `EnableLight(s32)` | `0x80113838` | 60 |
| `SetLightNum(u32)` | `0x80113874` | 64 |
| `SetRenderStateForBlendAdd()` | `0x801138B4` | 64 |
| `LoadRenderState()` | `0x801138F4` | 76 |
| `SaveRenderState()` | `0x80113940` | 76 |

The complete text range is `0x801137AC–0x8011398C`, 480 bytes. The preceding
paralysis static initializer and following unrelated helper are excluded.
Ownership includes `extab` at `0x8000A7F0–0x8000A830` (64 bytes), `extabindex`
at `0x800108DC–0x8001093C` (96 bytes), and four saved-state words at
`0x8042C658–0x8042C668` in `.sbss`. The private `src`, `dst`, `cullmode`, and
`fog` identities and types are corroborated by metadata and state getter/setter
calls. Only the save/load functions reference those four GameCube locations.
The metadata's address-zero crash-vector declaration contributes no storage.
`LandManager` and `CLight` are shared external objects, not definitions here.

The implementation uses accessed prefixes for those external objects. GameCube
places the world's pointer array at land-manager offset `0x7250`, and the signed
current light number at `CLIGHT+0x4BE`; no full external object is allocated or
sized through these views. The namespace functions retain the signed world index
and unsigned light-number parameter, including its conversion to signed byte.
No bounds checks or extra state initialization are introduced. Existing callers
receive mechanical symbol renames without changing their arguments or layouts.

Ordinary automatic inlining and the project's whole-unit compiler flags produce
all eight bodies directly. The first native whole-object audit matched all four
allocated sections, their alignments and flags, all twelve owned function/data
symbols and bindings, and all 51 effective relocation sites/types/destinations.
No instruction normalizer, atom reordering, per-function flag, or assembly is
required. The supported G9SE8P main DOL and all 17 RELs compile and pass all 18
reference hashes. All 62 automated tests, both language/post-processor policies
and source-format hooks pass. The whole unit is enabled as Matching.
Compilation and binary comparison do not establish runtime validation.
