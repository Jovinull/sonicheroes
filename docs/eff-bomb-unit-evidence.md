# Complete bomb-effect translation unit evidence

Positive symbolic metadata identifies effect/eff_bomb.cpp as C++ with eleven
file-origin definitions. Nine survive at 0x800BD1E8–0x800BDF30, totaling 3,400
bytes: team-to-collision-ID mapping, TDisp, Exec, destructor, constructor,
local callbackSetMaterial, EndEffBomb, InitEffBomb and SetEffectBomb. The ordinary
SetPosition and SetCollisionParameter methods inline into their callers.
No PS2 instructions were inspected.

The preceding hAnim unit is independently reconstructed. The right boundary
follows the complete nine-body inventory: its neighboring helper belongs to a
distinct celestial-sphere/refraction call graph with three pipeline pointers,
tikan128/tikan256 resource names and eight replacement records. This is a
GameCube call/storage inference, not a claim that the neighbor is the next
PS2 filename. No neighboring methods or storage are annexed.

Owned storage comprises 112 exception bytes, seven exception-index rows,
144 data bytes including three zero material pointers, 48-byte collision info,
class string, 44-byte vtable and two resource strings; 68-byte UV state with
four alignment bytes; sixteen small-data bytes including the class pointer and
ef_exp string; sixteen small-BSS bytes; and the 96-byte floating constant pool.
All storage references are confined to this complete unit. The three material
pointers are zero in the original initialized-data section. Named private
storage and the atomic rendering callback have positive local linkage evidence.

The GameCube and symbolic class layouts agree on 0x100 bytes: TObject and
C_COLLI bases, mode at 0xB0, two signed bytes, a signed-short timer, effect type,
position/angles, rotation, three scales, three alpha values and owned clump and
atomic pointers. callbackSetMaterial has one atomic pointer argument, unlike
the two-argument clump iterator callback. SetEffectBomb returns void. The
GameCube constructor handles an additional type value four; its semantic name
is unknown and remains provisional instead of reusing the older platform's
MAX interpretation.

Fifty-eight existing source consumers and five existing fixers receive only
same-address canonical renames and formatting, mechanically verified against
the base. The complete unit is enabled as Matching with the narrow allocation
normalization disclosed below.

The reconstruction retains all eleven ordinary definitions. Whole-unit
`auto,deferred` and reversed definition order restore forward inlining and
compiler-owned constant/string order. Grouping the three SetPosition frame
pointer declarations restores their lifetimes. TDisp captures and scales alpha
as an f32 before its two byte conversions; this local spelling is reconstructed,
not claimed as a symbolic-metadata variable.

Eight surviving bodies match directly from MWCC. The constructor differs only
in six of its 290 instruction words: eight register fields exchange r28/r31 for
the three-iteration atomic-instance loop counter and derived byte offset.
Twenty-eight bounded loop lifetime, scope, alias and increment trials did not
close this allocation difference. `tools/fix_eff_bomb_registers.py` exchanges
only these fields in our compiler output. It takes no retail input and changes
no opcode, immediate, branch, data, exception record or relocation. Its guards
and tests must fail if the source/compiler output changes. Improving the loop
allocation is the remaining path to deleting this step.

Independent review establishes both registers are freshly initialized, preserved
by calls, and dead at loop exit before later frame-pointer definitions. The EH
cleanup uses r29 object bases, not these loop values; the callee-save prologue
and epilogue stay unchanged. A scratch application of only this permutation
matches all nine bodies, eight owned sections and 209 effective relocations,
including natural trailing zero alignment.

The complete G9SE8P main DOL and all seventeen RELs compile in the documented
release configuration and pass all eighteen reference hashes. All 77 automated
tests pass, including fifteen synthetic normalizer tests; language and
post-processor policies pass. The final ELF/map proves all nine source bodies
retain their retail addresses and all eight owned ranges are byte-identical.
Two unused ordinary helpers (420 text bytes) and weak TObject delete (40 bytes),
plus their 24 exception/36 index bytes, are discarded normally. The strong
Task delete remains selected at 0x8001895C. Compilation and byte matching do
not establish runtime or physical-hardware validation.
