# Sky Egg laser collision unit

`stage13D/o_s14_laser_colli.cpp` restores the original source filename and
`TObjS14LaserColli` class. PS2 symbolic/debug metadata identifies
`stage14_SkyEgg2/o_s14_laser_colli.cpp` and the 204-byte class, with `TObject`,
`TObjSetObj`, and `C_COLLI` bases at offsets 0, 40, and 48. The editor label
`S14 3WAY COLLI` remains unchanged. Only symbolic metadata was used; no PS2
program code or original game assets are included.

The GameCube configuration covers nine native function bodies in their original
order: the seven ordinary operations, static registration, and the editor
adjustment thunk. Genuine construction, destruction, allocation and multiple
inheritance replace the synthetic class implementation. `ApplyCommunicateList`
is an inline reconstruction helper, not a recovered original declaration: it
expresses the positive-guard loop used inside `Exec`, while the standalone
`SetCommuicateStrage` retains its early return. No extra helper body is emitted.
All 2,308 instruction bytes match before normalization.

## Data and boundaries

Metadata identifies the parameter comments, color names, 44-byte registration
entry, collision shape, 36 three-component vertices, 16-byte color array and
48-byte `IMPRIM_INFO` primitive descriptor. The latter two replace a previously
combined 64-byte object. The descriptor and vertices remain even though code
does not reference the descriptor; metadata and its vertex relocation identify
them as this unit's data.

The entire configured GameCube extent is retained:

| Section | Start | End | Bytes |
| --- | --- | --- | ---: |
| `.text` | `0x9EBAC` | `0x9F4B0` | 2308 |
| `.ctors` | `0x144` | `0x148` | 4 |
| `.rodata` | `0x18B8` | `0x18C8` | 16 |
| `.data` | `0x1A020` | `0x1A320` | 768 |
| `.bss` | `0x1B8C` | `0x1BC4` | 56 |

The format string occupies six bytes. Its compiler object contributes 764 bytes
of `.data`; the linker supplies the remaining four alignment bytes. The trailing
four zero bytes in `.rodata` and twelve bytes in `.bss` remain opaque residual
storage. Their original declarations and historical ownership are unknown.
The full GameCube boundary remains an explicitly inferred reconstruction, not a
recovered original object map; absence of references was not used to exclude
those bytes.

## Normalization and verification

The guarded post-processor binds reconstructed symbols, permutes existing
vtable/string data atoms, and changes BSS alignment metadata from eight to four.
It checks the native text fingerprint, function inventory, atom payloads and
semantic relocations before replacing the object atomically. It changes no
instructions or text order. The old instruction-word table and policy exemption
are removed. Eight tests cover repeat application, malformed input and atomic
failure when objcopy corrupts bytes, binding or relocation targets.

Local verification compiles `all_source`, freshly links `main.dol` and all 17
configured REL modules, and checks all 18 release SHA-1 values. All 212 tool tests,
the language policy and 65 post-processor checks pass. Object and final-REL audits
cover all five ranges, all nine bodies and 113 semantic object relocations,
including every final alignment byte and 112 final REL relocation records. The
complete rebuilt Stage13 REL equals the original. Section flags and alignments
match; the native eight-byte editor thunk retains the compiler's weak binding
where the extracted target uses global binding, with identical offset and size.
Compilation and byte equality do not
constitute hardware validation.
