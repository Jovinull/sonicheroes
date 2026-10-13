# Stage13 antenna native matching evidence

`stage13D/o_s13_antenna.cpp` emits all twelve functions in their target order:
2,756 native instruction bytes and 198 code relocations. The former factory
instruction patch and text permutation are removed. The remaining normalizer
only binds symbols, permutes existing data atoms, and sets BSS alignment.

## Class and source evidence

Optional local PS2 symbolic metadata identifies
`stage/stage13_SkyEgg/o_s13_antenna.cpp` as C++. Its ten file-origin operations
correspond to the GameCube clump destruction/cloning, positioning, execution,
editor callback, destructor, constructor, shutdown, initialization, and factory.
The GameCube unit also contains registration and a compiler-generated editor
adjustor thunk, accounting for all twelve functions.

The recovered `TObjS13Antenna` uses the metadata-backed bases `TObject`,
`TObjSetObj`, and `C_COLLI`. The first two bases occupy offsets 0 and 40;
`C_COLLI` starts at 48. Native construction, direct member initialization,
and a reference conversion to the collision base reproduce the factory's
allocation lifetime and instruction order. No optimizer workaround or
post-compile instruction replacement is needed. Existing storage structs are
private ABI views used by external helper declarations, not alternate class
inheritance claims. No PS2 instructions are used.

## Data coverage and uncertainty

The complete existing configured GameCube ranges are retained:

| Section | Start | End | Bytes |
| --- | --- | --- | ---: |
| `.text` | `0x90DA0` | `0x91864` | 2756 |
| `.ctors` | `0x120` | `0x124` | 4 |
| `.rodata` | `0x1778` | `0x17A4` | 44 |
| `.data` | `0x18080` | `0x18188` | 264 |
| `.bss` | `0x194C` | `0x1988` | 60 |

The registration record is 44 bytes. The remaining 16 zero BSS bytes, the
unreferenced portion of the zero constant pool, and the explicit constant
padding are preserved as opaque residual storage. Their original declarations
and historical ownership have not been established. All Stage13 target-object
relocations were checked: only the first zero scalar is referenced, and the
BSS tail is unreferenced. That does not prove the tails belong elsewhere, so
this change does not narrow the configured unit to exclude them. The source
comments and these ranges describe an inferred reconstruction boundary, not
recovered original GameCube object metadata.

The display name is a 13-byte string. Its compiler atom includes three zero
alignment bytes; the linked output supplies four further zero bytes at the end
of the configured data range. The source does not invent a 17-byte string
object. Every byte of the complete range is checked in the final REL.

## Remaining normalization

The guarded tool permutes the compiler's integer-bias atom relative to the
float constants and its generated vtable relative to the display string.
It updates data relocation offsets and symbol metadata, and changes BSS
alignment from eight to four. Its aliases retain the project's current link
names; they do not describe the authentic source class as `AntennaVirtual`.

It checks the native text fingerprint and complete twelve-function inventory,
then verifies that atom payloads and relocation meanings survive unchanged.
Output replacement is atomic and repeated normalization is idempotent. Eight
tests cover permutations, aliases, relocation identities, input rejection,
and failures that must leave the original object untouched. The obsolete
instruction-patch exemption is removed from the postprocessor policy.

## Verification

All 213 object relocations match: 198 code, 14 data, and one constructor-table
entry. A fresh independent compile verifies the complete native text before
normalization. The integrated object and final REL are checked separately.
The compiler-generated editor thunk retains its native weak binding; its
address, size, bytes, and final linked behavior match the target. All five
configured ranges, 201 remaining final REL relocation records, and the complete
Stage13 REL file match the original.

`all_source` and the full release build pass; `main.dol` and all 17 REL hashes
match the manifest. All 212 tool tests, language policy, and postprocessor
checks pass. This establishes binary equivalence, not hardware validation or
certainty about the historical declarations of the residual zero storage.
