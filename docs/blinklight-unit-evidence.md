# Stage13 blink-light native matching evidence

`stage13D/o_s13_blinklight.cpp` emits all thirteen functions in target order:
2,916 native instruction bytes. The former factory instruction patch and text
permutation are removed. The remaining normalizer only binds native symbols,
permutes existing data atoms, and sets BSS alignment.

## Source and class evidence

Optional local PS2 symbolic metadata identifies
`stage/stage13_SkyEgg/o_s13_blinklight.cpp` as C++ and records
`TObjS13BlinkLight`, size 200, with `TObject`, `TObjSetObj`, and `C_COLLI`
bases at offsets 0, 40, and 48. The timer, animation time, clump pointer, and
particle-frame pointer are members of the derived class.

Its eight methods are particle creation, clump destruction/cloning,
positioning, execution, editor callback, destructor, and constructor. Together
with shutdown, initialization, and factory, these correspond to eleven
GameCube bodies. Registration and the compiler editor-adjustor thunk bring
the complete inventory to thirteen. The source restores the native particle
and clump methods and `RpClump` type name as well as the actual class hierarchy.
Private storage structs remain ABI views for partially recovered helper APIs;
they are not claims about alternative inheritance. No PS2 instructions are used.

Native allocation, direct member construction, and a reference conversion to
the collision base reproduce the factory's instruction order and lifetime.
No instruction or register patch is involved.

## Data scope and uncertainty

The complete existing configured GameCube ranges are preserved:

| Section | Start | End | Bytes |
| --- | --- | --- | ---: |
| `.text` | `0x8B058` | `0x8BBBC` | 2916 |
| `.ctors` | `0x114` | `0x118` | 4 |
| `.rodata` | `0x16D0` | `0x1704` | 52 |
| `.data` | `0x17A70` | `0x17B7C` | 268 |
| `.bss` | `0x165C` | `0x1694` | 56 |

The registration record is 44 bytes. The following 12 zero BSS bytes and the
last 40 bytes of the zero constant pool are retained as opaque residual
storage. Their original declarations and historical ownership remain
unestablished. They are not recovered class fields or known linker padding.
A scan of every Stage13 target-object relocation finds references only to the
first scalar of the zero pool and none to the BSS tail. Metadata and
registration code do not support calling the BSS tail a destructor-chain node.
Lack of references also does not prove that either tail belongs elsewhere.

This change therefore retains the full configured extents rather than
excluding uncertain bytes. The data boundary is an explicit reconstruction
hypothesis; a matching binary does not establish historical object-file
ownership or original source declarations.

## Guarded data normalization

The normalizer permutes the existing generated vtable and display-name atoms,
updates their symbol and data-relocation offsets, and binds native names to
the existing project link symbols. The synthetic `BlinkLightVirtual` spelling
is retained only as a link alias, not a source class. The compiler editor thunk
retains its native weak binding. BSS alignment becomes four; the existing
per-unit data-alignment setting remains unchanged.

The tool validates the text fingerprint, complete section and function
inventories, function offsets and bindings, and data atom positions. It then
checks that atom bytes, symbol properties, and relocation identities survive
unchanged, including exact preservation of the text and text-relocation
payloads. Output replacement is atomic and idempotent. Eleven tests cover the
permutation, corruption rejection, invariant preservation, and atomicity.
The obsolete instruction-patch policy exemption is removed.

## Verification

A fresh independent compile of the native methods preserves every allocated
payload. All five section payloads and all 217 object relocations match after
data-only normalization. The final REL ranges and complete Stage13 REL are
checked independently against the original. All 203 remaining relocation
records in the configured final REL ranges match, and the entire Stage13 REL
is byte-identical. Compiler-generated float-literal names are resolved to
section offsets when comparing relocation destinations; spelling alone is not
an address difference. The native data-alignment setting is four, while the
extracted target object records eight; final section placement and bytes are
exact.

`all_source` and the full release build pass. `main.dol` and all 17 REL hashes
match the manifest, independently rechecked. All 215 tool tests, language
policy, and 65 postprocessor checks pass. These are binary checks, not hardware
validation or proof of the historical declarations of residual zero storage.
