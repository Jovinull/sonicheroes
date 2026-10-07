# Complete crash effect translation unit evidence

Positive symbolic metadata identifies effect/eff_crash3d.cpp as C++ with 25
file-origin definitions across four effect classes and factories. Twenty
survive in GameCube code, plus one GameCube-only factory overload: 21 bodies
occupy 0x80100D4C–0x80103178, totaling 9,260 bytes. Five ordinary methods inline:
both child position setters, frame-atomic lookup, node-frame lookup, and the
normal parent constructor. The callback retains local binding. All 26 ordinary
definitions belong to the reconstruction. No PS2 instructions were inspected.

The left boundary is positively established by the preceding sEnemyCommandEx
and sEnemyCommand Send wrappers, already reconstructed in enemy/e_communication.
Their metadata origin and manager-dispatch calls exclude them from this unit.
The right boundary is the independently completed enemy search utility.
Four class vtables anchor crash-effect ownership.

Seven owned ranges comprise 9,260 text bytes, 380 exception bytes, 228 index
bytes, 216 data bytes, 24 small-data bytes, eight small-BSS bytes and 104 constant
bytes. The complete inventory contains 504 relocations. Initialized data holds
two class strings and four vtables. Small data holds movement/blink controls
and two class-name pointers. The final class pointer and private atomic search
cache each have four logical bytes plus four alignment bytes. The final pool
entry is a four-byte 360.0 float plus four alignment bytes, independently
verified from floating-point load widths; only the conversion constant at
0x8042E710 is a double.

The normal metadata factory corresponds to 0x80102FB4. The preceding factory
at 0x80102DEC adds a light-selection argument; its original spelling is unknown.
The normal child constructor also adds a signed-short light parameter beyond
the PS2 signature. These ABI differences must be preserved rather than copying
the metadata mangling unchanged. Four class layouts independently agree with
GameCube allocation and accesses.

The complete source has been reconstructed. Independent review confirms the
borrowed-frame/atomic lifetime of the R child, owned clump cleanup, the local
callback's zero return on a match, and node lookup through nodeIndex rather
than nodeID. Existing null preconditions and distinct near-zero velocity paths
are preserved. The GameCube-only factory retains an honest raw address alias.

The direct cube random-angle expressions compile with all fifty constructor
call sites in the original order, including coarse random value before angular
perturbation. Their original source spelling remains unknown; C++ permits the
compiler to choose operand evaluation order, and the configured compiler's
emission is verified. Random-value bounds keep the integer arithmetic within
signed range. Strict production-object comparison passes all 21 surviving
bodies, 504 relocation meanings and seven owned sections.

The source uses ordinary reversed definition order and whole-unit
auto,deferred inlining. The only remaining compiler difference is the location
of the existing 1500.0f literal: native offset 36 versus reference offset zero.
Reviewed source-order, local-value, const and aggregate forms did not recover
that ordering while retaining the matching instruction streams.

The fail-closed fix_eff_crash3d_pool.py step rotates only the first forty bytes
of the existing 100-byte pool and adjusts ten local atom symbol values. It
does not change instructions, relocation bytes, addends or other object data.
All 156 pool references retain their exact effective bytes. Whole input/output
hashes, complete atom coverage, ELF bounds, bindings, sizes and relocation
kinds guard the operation. Four linked zero alignment bytes are separately
verified. Fourteen synthetic tests cover idempotence, unchanged code and
relocations, preserved effective addresses, malformed input rejection, and
atomic CLI/stamp behavior. Two independent reviews found no blocker.

Two unrelated literal words needed relocation-analysis exclusions when native
private exception records replaced exported reference labels. At 0x8027D5A4,
0x8000FF16 lies within an embedded ONEFILE archive payload: the resource table
at 0x80288B28 supplies its base 0x80279060 and length 0x5490 to SetOneFile.
At 0x80289CDC, 0x8000FF40 is the first RGBA in a three-color table; the spotlight
constructor reads its four bytes into color fields. Neither is a pointer to a
crash exception record. Only those two source relocations are blocked; their
literal bytes are retained unchanged.

Verification passes with the unit enabled as Matching: all-source compilation,
the G9SE8P release DOL and all seventeen supported RELs, and all eighteen
reference hashes. Final-link/map checks confirm all 21 original addresses and
all seven complete byte ranges, with ordinary inline helpers and weak delete
naturally discarded and the existing strong TObject delete retained. All 76
automated tests and both language/post-processor policies pass. Compilation
and byte comparison do not establish runtime or physical-hardware validation.
