# Collision reactor translation unit evidence

PS2 symbolic metadata identifies `c_colli_react.cpp` as C++. Four reactor
classes virtually inherit `CCL_REACTOR`; GameCube allocation, virtual-base
pointer adjustment and thunk instructions independently confirm this structure.
No PS2 instructions were inspected.

The candidate complete GameCube text range is `0x800B13EC–0x800B2110`:
42 bodies, 3,364 bytes. Five metadata-named constructors inline into factories.
Fourteen virtual-base thunks follow the base destructor. The final 28-byte
method sets the three components of the base direction vector; its vtable
position supports `CCL_REACTOR::SetDirection`. PS2 header metadata confirms the inline-method name.

| Address | Bytes | Correlation |
| --- | ---: | --- |
| `0x800B13EC` | 248 | `Construct_CCL_REACTOR_PUSHPULL__FP8CCL_INFO` |
| `0x800B14E4` | 68 | `React__20CCL_REACTOR_PUSHPULLFP5RwV3dP6sAngle` |
| `0x800B1528` | 52 | `GetDotProductOfDirection__20CCL_REACTOR_PUSHPULLFP5RwV3d` |
| `0x800B155C` | 64 | `AddParameter__20CCL_REACTOR_PUSHPULLFP5RwV3dP6sAngle` |
| `0x800B159C` | 32 | `SetParameter__20CCL_REACTOR_PUSHPULLFP5RwV3dP6sAngle` |
| `0x800B15BC` | 144 | `__dt__20CCL_REACTOR_PUSHPULLFv` |
| `0x800B164C` | 272 | `Construct_CCL_REACTOR_TURNTABLE__FP8CCL_INFO` |
| `0x800B175C` | 564 | `React__21CCL_REACTOR_TURNTABLEFP5RwV3dP6sAngle` |
| `0x800B1990` | 60 | `SetParameter__21CCL_REACTOR_TURNTABLEFP5RwV3dP6sAngle` |
| `0x800B19CC` | 144 | `__dt__21CCL_REACTOR_TURNTABLEFv` |
| `0x800B1A5C` | 272 | `Construct_CCL_REACTOR_TRANSROTS__FP8CCL_INFO` |
| `0x800B1B6C` | 92 | `React__21CCL_REACTOR_TRANSROTSFP5RwV3dP6sAngle` |
| `0x800B1BC8` | 60 | `SetParameter__21CCL_REACTOR_TRANSROTSFP5RwV3dP6sAngle` |
| `0x800B1C04` | 144 | `__dt__21CCL_REACTOR_TRANSROTSFv` |
| `0x800B1C94` | 272 | `Construct_CCL_REACTOR_TRANS__FP8CCL_INFO` |
| `0x800B1DA4` | 80 | `React__17CCL_REACTOR_TRANSFP5RwV3dP6sAngle` |
| `0x800B1DF4` | 32 | `SetParameter__17CCL_REACTOR_TRANSFP5RwV3dP6sAngle` |
| `0x800B1E14` | 144 | `__dt__17CCL_REACTOR_TRANSFv` |
| `0x800B1EA4` | 84 | `Destruct_CCL_REACTOR__FP8CCL_INFO` |
| `0x800B1EF8` | 8 | `React__11CCL_REACTORFP5RwV3dP6sAngle` |
| `0x800B1F00` | 8 | `GetDotProductOfDirection__11CCL_REACTORFP5RwV3d` |
| `0x800B1F08` | 20 | `ClrDirection__11CCL_REACTORFv` |
| `0x800B1F1C` | 68 | `GetParameter__11CCL_REACTORFP5RwV3dP6sAngle` |
| `0x800B1F60` | 4 | `AddParameter__11CCL_REACTORFP5RwV3dP6sAngle` |
| `0x800B1F64` | 36 | `ClrParameter__11CCL_REACTORFv` |
| `0x800B1F88` | 4 | `SetParameter__11CCL_REACTORFP5RwV3dP6sAngle` |
| `0x800B1F8C` | 80 | `__dt__11CCL_REACTORFv` |
| `0x800B1FDC` | 20 | `@8@48@SetParameter__17CCL_REACTOR_TRANSFP5RwV3dP6sAngle` |
| `0x800B1FF0` | 20 | `@8@48@React__17CCL_REACTOR_TRANSFP5RwV3dP6sAngle` |
| `0x800B2004` | 20 | `@8@48@__dt__17CCL_REACTOR_TRANSFv` |
| `0x800B2018` | 20 | `@8@48@SetParameter__21CCL_REACTOR_TRANSROTSFP5RwV3dP6sAngle` |
| `0x800B202C` | 20 | `@8@48@React__21CCL_REACTOR_TRANSROTSFP5RwV3dP6sAngle` |
| `0x800B2040` | 20 | `@8@48@__dt__21CCL_REACTOR_TRANSROTSFv` |
| `0x800B2054` | 20 | `@8@48@SetParameter__21CCL_REACTOR_TURNTABLEFP5RwV3dP6sAngle` |
| `0x800B2068` | 20 | `@8@48@React__21CCL_REACTOR_TURNTABLEFP5RwV3dP6sAngle` |
| `0x800B207C` | 20 | `@8@48@__dt__21CCL_REACTOR_TURNTABLEFv` |
| `0x800B2090` | 20 | `@8@48@AddParameter__20CCL_REACTOR_PUSHPULLFP5RwV3dP6sAngle` |
| `0x800B20A4` | 20 | `@8@48@SetParameter__20CCL_REACTOR_PUSHPULLFP5RwV3dP6sAngle` |
| `0x800B20B8` | 20 | `@8@48@GetDotProductOfDirection__20CCL_REACTOR_PUSHPULLFP5RwV3d` |
| `0x800B20CC` | 20 | `@8@48@React__20CCL_REACTOR_PUSHPULLFP5RwV3dP6sAngle` |
| `0x800B20E0` | 20 | `@8@48@__dt__20CCL_REACTOR_PUSHPULLFv` |
| `0x800B20F4` | 28 | `SetDirection__11CCL_REACTORFP5RwV3d` |

The four derived objects allocate 60 bytes. Their virtual base starts at offset
8; metadata fields are reference count 0, reaction 4, vector 8, angles 20,
and direction 32. The compiler adds the base vptr and displacement.
`CCL_INFO::pReactor` is at offset 32; CCL_INFO occupies 48 bytes.

The five vtable groups begin at `0x80253698`, `0x802536E4`, `0x80253728`,
`0x8025376C`, and `0x802537B0`. Their final virtual slot reuses the existing
28-byte `CCL_REACTOR::GetDirection` method at `0x80041C3C`; both its
GameCube three-component copy and PS2 header metadata confirm the name.
Assembly section records and constant references establish these candidate
owned ranges. Full linked-image comparison confirms the ranges below.

| Section | Start | End | Bytes |
| --- | --- | --- | ---: |
| extab | `0x80007F68` | `0x80008000` | 152 |
| extabindex | `0x8000E560` | `0x8000E5E4` | 132 |
| .rodata | `0x80239F70` | `0x80239F80` | 16 |
| .text | `0x800B13EC` | `0x800B2110` | 3364 |
| .data | `0x80253698` | `0x802537E0` | 328 |
| .sdata2 | `0x8042DCA0` | `0x8042DCD0` | 48 |

The following function changes to editor display work; it is excluded.
All 42 bodies are reconstructed in ordinary C++, together with the inlined
constructors, CheckReactor and reference-count methods. The compiler emits all
14 virtual-base thunks; no thunk implementation is written in assembly.
The turntable uses the GameCube reciprocal-square-root intrinsic and three
Newton iterations visible in the original instructions.

An isolated comparison normalizes symbol names in a temporary reference object
for analysis only. All 42 bodies now match instructions and normalized
relocations. The 48-byte constant pool and 12-byte zero-vector initializer also
match; the latter has four bytes of alignment in the retail image.

The integer factory checks require `-bool off` and comparison with `0L` to
preserve the retail integer result. TRANSROTS stores and checks reaction type 2,
although its React method returns type 1. With `-inline auto,deferred` and
reversed external definitions, the compiler emits the retail vtable and thunk
orders. The source groups base-class definitions first, followed by derived classes
TRANS, TRANSROTS, TURNTABLE and PUSHPULL. Class dependencies support a base-first
organization, but metadata describes emitted addresses, not original line
order; the original declaration order is not proven.

Without deferred emission, the compiler preserves external definition order,
reverses the derived vtable order relative to retail, and emits virtual-base
thunks in the wrong order. Deferred emission reverses the external definitions
and produces both the five retail vtable groups and all fourteen thunks in
retail order. These independently generated virtual-inheritance structures,
and the matching extab records, support the deferred recipe beyond its
public-function permutation. The remaining weak inline placement is an explicit
compiler-layout gap; it is not evidence for assigning the method to another TU.
Whole-TU inline-mode/compiler-version trials, direction-method definition
placement, class declaration reversal, and inline/defer pragmas did not close it.

The first native-link diagnostic isolated a 28-byte weak SetDirection placement
gap: it preceded the factories instead of following the thunks. The object
normalizer moves that one compiler-produced body, rebases symbols and relocation
offsets, and asserts input/output text hashes. It preserves all 43 emitted
function bodies and all 168 relocation meanings. No instruction or data byte is
injected. Duplicate GetDirection resolves normally to `0x80041C3C`.

Derived primary vtable slots are established directly by GameCube references:
PUSHPULL declares destructor, SetParameter, AddParameter,
GetDotProductOfDirection, React; the other derived classes declare destructor,
SetParameter, React. This declaration order produces all 64 retail data
relocations without changing function bodies or thunk order. PS2 type metadata
does not record member-method order and is not claimed as evidence for it.

With that declaration order and the single-atom normalization, all 42 surviving
bodies, owned sections and linked addresses match. The complete main DOL is
byte-identical. The supported G9SE8P main DOL and all 17 RELs compile and all 18
reference hashes pass. The unit is enabled as Matching. Language and object
post-processor policies pass; relevant automated tests cover those policies and
ELF handling. Corrupt-input rejection, relocation preservation and idempotence
are checked for the atom normalizer. No runtime validation is claimed.
