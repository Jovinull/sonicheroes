# Complete dash-effect translation unit evidence

Positive symbolic metadata identifies effect/eff_dush.cpp as C++ with eleven
file-origin definitions. Seven survive at 0x800FF9CC–0x801001DC, totaling
2,064 bytes: factory, display, execution, destructor, primitive render and
resource initialization/shutdown. Four ordinary methods inline into callers:
EffDash and EffDush constructors, EffDush destructor and color setter. No PS2
instructions were inspected.

The actual C++ classes are EffDash and EffDush; the independent runtime class
string is TObjEffDash. GameCube allocation and field accesses confirm the
0x40-byte task and eight-byte primitive. The preceding three hierarchy methods
and following database GetAnimationNum are separate, already reconstructed
translation units and are excluded.

Nine owned ranges cover 2,064 text bytes, 84 exception bytes, 72 index bytes,
128 data bytes, 16 read-only bytes, 72 BSS bytes, 16 small-data bytes,
16 small-BSS bytes and 48 constant bytes. The 12-entry default color array,
class string, vtable and resource names are owned here. UV state is 68 bytes
plus alignment; the local zero vector is 12 bytes plus alignment. Shared axis
vectors are excluded. All 154 reference relocations are inventoried.

The complete unit is enabled as Matching.

The clump query at 0x8014FEF4 counts lights: its callback increments a counter
while iterating the metadata-confirmed light list at clump+0x10. A positive
result reaches a local infinite self-branch at 0x80100030. This is retained as
original behavior; there is no evidence of an assertion message or a different
atomic-count guard. Render-state save, set and restore ordering is preserved.
Resource initialization nests both load attempts under the clump guard;
shutdown clears cached pointers without destroying resources or resetting time.
The task constructor indexes player data using the full incoming index before
storing the signed-byte player field. No angle initialization is invented.

All seven bodies match directly from source. Whole-unit `auto,deferred` with
reversed ordinary definition order restores forward-inlined constructors and
base cleanup, along with vtable/resource-string order. Ordinary `auto` with
metadata definition order leaves required helpers out of line. This is a
reconstruction recipe, not a claim about the original source order or flags.

Explicit f32 locals capture the double asin/atan2 results before the original
integer angle quantization and degree conversion. A signed local alpha value
with compound subtraction and the ordinary aggregate color setter preserve
byte assignments without an extra mask. A signed player-index local captured
immediately before the lookup and first history call resolves the remaining
allocation difference; the second history call still reloads the member.
No call or write occurs between that capture and its first uses. These local
lifetime spellings are reconstructed, not claimed metadata variable names.
No object normalizer or injected instructions are used.

The complete G9SE8P main DOL and all seventeen RELs compile in the documented
release configuration and pass all eighteen reference hashes. All 62 automated
tests and both language/post-processor policy checks pass. Final ELF/map audit
confirms every surviving body address and every byte of all nine owned ranges.
Four unused ordinary helper copies (556 text bytes), weak TObject delete
(40 bytes), and their 52 exception/48 index bytes are discarded normally;
the existing strong Task delete is selected at 0x8001895C. Four source consumers
and three existing fixers have mechanically verified same-address renames and
formatting only. No runtime or physical-hardware validation is claimed.
