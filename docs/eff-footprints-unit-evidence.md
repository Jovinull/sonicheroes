# Complete footprint-effect translation unit evidence

Positive symbolic metadata identifies effect/eff_footprints.cpp as C++ with
fourteen file-origin definitions. Seven survive at 0x801102B0–0x80110C18,
totaling 2,408 bytes: public factory, footprint display, manager display,
manager execution/destructor, resource shutdown and initialization. The local
Create helper, footprint execution/constructor/destructor and manager
insertion/removal/constructor inline into those bodies. No PS2 instructions
were inspected.

The public factory returns void. Its local Create helper returns a footprint
pointer; the GameCube wrapper compares the inlined result in r0 and does not
return it through r3. Both original definitions are retained. The preceding
helper accesses a receiver larger than either footprint class, and the following
helper uses a separate singleton. Their code and storage are excluded; their
original source filenames are not inferred from adjacency.

Seven owned ranges comprise 2,408 code bytes, 128 exception bytes, 84 index
bytes, 1,400 initialized data bytes, 48 BSS bytes, eight small-data bytes and
40 constant bytes, with 155 reference relocations. Data includes four resource
paths, four texture names, their local pointer tables, the runtime class string,
12-by-4 UV and position tables, twelve size vectors and a 44-byte vtable.
The three BSS arrays each contain four pointers. The class pointer is four
bytes with four alignment bytes; the constant pool includes four alignment
bytes before its double. Shared axes, action state and team pointers remain
external. All owned storage code references occur within the seven bodies.

GameCube code and metadata agree on the nonvirtual 0x4C-byte EffFootPrints
class and 0x38-byte EffFootPrintsManager. The existing CLASS_LINK and
CLASS_LINK_MANAGER declarations are reused. GameCube immediate-mode vertices
have position at zero, normal at 0x0C, color at 0x18 and UV at 0x1C/0x20;
this differs from the older platform metadata. The source must preserve the
GameCube layout, original render ordering, list lifetimes and resource guards.

The complete unit is enabled as Matching with the narrow allocation
normalization disclosed below.

Independent review verifies all 276 table floats (1,104 bytes) against their
GameCube bit patterns. List execution advances the current pointer before
updating or deleting the footprint; display advances it after drawing. Shutdown
clears a texture pointer only when its dictionary was present. Initialization
preserves the stage gate and the original unguarded lookup after dictionary load.
The signed integer signatures of InsertEffect and EraseEffect are established
by metadata. Their results are discarded in every surviving GameCube use;
the reconstructed return values are explicitly marked as unknown original
semantics, while all observable insertion/removal effects are preserved.

Whole-unit deferred inlining and reversed ordinary definitions restore the
factory and manager call graph. Defining Init before global initialized tables
places its genuine function-local filename/texture tables in the observed order.
Paired UV reads with a single two-element advance remove an extra increment,
and separate texture-null/mode gates preserve the out-of-line display call.
No per-function inline barrier is introduced. Historical source order and
compiler flags remain unknown; these are source reconstruction choices.

Six surviving bodies match directly from MWCC. Disp has exactly the original
420-byte instruction sequence except for twelve GPR fields in eleven of its
105 instructions. The remaining allocation cycle is position cursor r6 to r9,
green r7 to r6, blue r8 to r7 and alpha r9 to r8. Bounded declaration, cursor,
index and read-only color lifetime trials did not recover that allocation.
`tools/fix_eff_footprints_registers.py` permutes only those compiler-produced
register fields, with no retail input or instruction-word injection. Complete
object/text/function and section/symbol/relocation contracts guard the input and
output; synthetic tests check bounds, corruption, idempotence and atomic failure.
Recovering the register allocation from source is the path to deleting the step.

Independent review proves the position cursor is freshly defined after its
previous uses, and each color temporary is defined before its sole store on
every iteration. The left-foot branch changes only the UV cursor. There are no
calls in this loop, and all mapped values die before transform/render calls.
All affected registers are caller-clobbered; callee-save state, stack layout,
exception records and instruction PCs remain unchanged. All 155 effective
relocations and every non-text section already match in the raw object.
All seven normalized bodies, their bindings and all owned sections match.
The complete G9SE8P main DOL and all seventeen RELs compile in the documented
release configuration and pass all eighteen reference hashes. All 77 tests
pass, including fifteen synthetic normalizer tests; language and post-processor
policies pass. Final ELF/map review confirms every surviving address and byte
of all seven owned ranges. Seven unused ordinary helpers (1,252 text bytes)
and weak TObject delete (40 bytes), with their 176 exception/96 index bytes,
are discarded normally. The existing strong Task delete remains selected at
0x8001895C. Four source consumers and three fixers contain only mechanically
verified same-address canonical renames and formatting. Compilation and byte
matching do not establish runtime or physical-hardware validation.
