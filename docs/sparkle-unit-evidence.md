# Sparkle whole-unit evidence

`rel/ef_sparkle.cpp` emits all ten functions and all 3,268 instruction bytes in
the original GameCube order. Moving the destructor definition after static
initialization removes the former text permutation. Ordinary C++ `new` and
`delete` replace explicit calls to mangled lifecycle symbols without changing
instructions. The three-argument `CreateSparkle` overload replaces an anonymous
C-linkage function; the four-argument GameCube overload remains.

PS2 symbolic/debug metadata names `stage/effect/ef_sparkle.cpp`, its functions,
class hierarchy and data objects. The three-argument overload corresponds to
the GameCube mode-switch selection between the ordinary and item material
pointers. Metadata supplies names and types; GameCube bytes establish matching.
No PS2 program code, original game assets or binaries are included.

## Layout and owned data

`PARTICLE_MATERIAL` owns the position, angle and vector fields at offsets
`0x58`, `0x64` and `0x70`; its size is 124 bytes. `EfSparkle` adds only its
four-byte type field and has size 128. The storage-header adapter preserves the
GameCube vptr layout; it is an ABI representation, not a recovered historical
extra base class. `PARTICLE_INSTANCE` has size 72, including the previously
missing final two pointers. `SPRITE_INFO` has size 24; its signed 16-bit maximum
count and 32-bit color occupy separate fields. The base constructor now has its
metadata-backed `Pt_FLAGS, SPRITE_INFO*` signature.

The six metadata-identified pointer globals cover all BSS. The sprite descriptor,
texture entry/list, strings, filename and vtable cover initialized data. The UV
table is shared main-module data. The final four rodata zero bytes remain
explicit residual storage of unknown original declaration/ownership. They are
kept separate from the preceding four-byte float, correcting its former
eight-byte symbol extent. No configured bytes are excluded.

| Section | Start | End | Bytes |
| --- | --- | --- | ---: |
| `.text` | `0x2DD2C` | `0x2E9F0` | 3268 |
| `.ctors` | `0x84` | `0x88` | 4 |
| `.rodata` | `0x9B0` | `0xA10` | 96 |
| `.data` | `0x3CD0` | `0x3D38` | 104 |
| `.bss` | `0xA20` | `0xA38` | 24 |

The complete configured extent is 3,496 bytes. The GameCube boundary remains an
explicit reconstruction hypothesis correlated with source metadata, not a
recovered original object map.

## Normalization

The remaining guarded normalizer permutes the existing filename and vtable
atoms and binds compiler literal symbols by their checked offsets and sizes.
It preserves every instruction, the raw text relocation section and all 244
semantic object relocations. All allocated payloads, flags and alignments match.
It does not inflate the final float, invent a padding symbol, or rewrite code.
Eight tests cover idempotence, malformed input, symbol collisions and atomic
failure if objcopy corrupts instruction bytes, bindings or relocation targets.

## Release verification

`all_source` passes. Fresh `main.dol` and all 17 configured REL modules build,
and all 18 release SHA-1 values match. All 212 tool tests, the language policy
and 65 post-processor checks pass. The independent final audit verifies every
configured byte, ten function offsets/sizes/bindings, all 244 object relocations
and 228 final REL relocation records. There are no function-binding differences;
the complete rebuilt Stage40 REL is byte-identical to the original. Compilation
and byte equality do not establish physical-hardware validation.
