# Enemy material-texture translation unit evidence

Symbolic metadata identifies `enemy/e_material.cpp` as C++ and supplies the
complete TEnemyMatTexture class and local material callback. GameCube class
construction, the paralysis effect's material-texture instance, texture
lookup calls, material setters and the two-pass search independently establish
the correlation. No PS2 instructions were inspected. This is distinct from
`game/material.cpp` and its DealMaterial class.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| `TEnemyMatTexture::PreDisp(s32)` | `0x8011398C` | 220 |
| `TEnemyMatTexture::End()` | `0x80113A68` | 64 |
| `TEnemyMatTexture::Init(...)` | `0x80113AA8` | 388 |
| `TEnemyMatTexture::~TEnemyMatTexture()` | `0x80113C2C` | 80 |
| `TEnemyMatTexture::TEnemyMatTexture()` | `0x80113C7C` | 36 |
| local `callbackMaterial` | `0x80113CA0` | 44 |

All six bodies occupy `0x8011398C–0x80113CCC` (832 bytes). Metadata Clear()
is fully inlined into construction and initialization; no seventh retail body
is claimed. The preceding complete render utility ends at the first method;
the following RingLaser task methods and parameter/string data are excluded.
The full class/callback inventory closes the boundary independently of the
exception-record grouping.

Owned exception records occupy `0x8000A830–0x8000A850` (32 bytes), their index
occupies `0x8001093C–0x8001096C` (48 bytes), and the destructor-only vtable owns
`0x80288CF0–0x80288D00` (12 payload bytes plus four natural alignment bytes).
No other data, strings, literal pool, BSS or constructor list belongs here.
The metadata's zero-address crash-vector declaration contributes no storage.
The callback's local binding follows its metadata subroutine classification.

The class is 20 bytes: vptr at zero, material-pointer array at four, supplied
texture table at eight, texture count at twelve and material count at sixteen.
Each supplied texture record holds filename, texture pointer and enum in twelve
bytes. Initialization resolves named textures, counts materials for the first
matching texture name, allocates the pointer array, and fills it with a second
search. The callback receives the twelve-byte OBJ_SearchMaterials wrapper and
unwraps its user data at offset eight before counting or collecting materials.
It does not receive the counting record directly.

PreDisp retains the native strict-greater-than index test, null texture/material
checks and switch cases for base, environment, bump and dual texture setters.
It adds no negative-index check or combined bump/environment case. End deletes
only the material-pointer array and clears that pointer. The destructor does
not call End; Init clears state without first releasing a prior array. These
are native ownership/lifecycle contracts, not opportunities for unrelated
behavior changes. Textures and materials themselves remain borrowed.

All six functions match directly with ordinary automatic inlining, including
genuine C++ array new/delete and the virtual destructor. No deferred override
or object normalizer is used. Canonical method/vtable/array-operator symbols
are propagated mechanically through existing callers, retaining their
provisional signatures and arguments. Debug.cpp metadata independently
identifies the array operators; GameCube uses unsigned long for allocation size.
All six function identities/bindings/boundaries, all 31 effective relocations,
text, exception records and vtable payload match. The sole data projection is
the vtable's four trailing alignment bytes. All eleven caller-file changes are
mechanical symbol substitutions. The supported G9SE8P main DOL and all 17 RELs
compile and pass all 18 reference hashes. All 62 automated tests, both language/
post-processor policies and source-format hooks pass. Compilation and binary comparison do not establish runtime validation.
