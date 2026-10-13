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

The complete unit is enabled as Matching with native compiler output and no
object postprocessor.

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

All seven surviving bodies now match directly from MWCC. The display method
uses the existing `RwRGBA` type for its green, blue and alpha temporaries;
red is written directly to the vertex as before. Grouping the color values in
their native aggregate reproduces the original register allocation without
changing calculations, access order, branches or compiler settings. The unused
local red member is never read. This is a source reconstruction choice, not a
claim to have recovered the original local declaration.

The raw object audit verifies all seven instruction bodies and their 119 text
relocations. All other emitted functions, non-text section bytes, alignments and
relocations remain unchanged. Owned data includes four zero alignment bytes
following the 1,396 initialized bytes and another four following the four-byte
small-data class pointer. The compiler still emits eight unused helpers; their
code and exception entries are unchanged and discarded normally by the linker.
The register postprocessor and its synthetic tests have been removed.

An independent final-ELF audit verifies all seven owned ranges, all seven
function addresses and sizes, and all 155 resolved relocation sites against
the original DOL. This also verifies that the extra helper exception entries
are discarded correctly.

The supported G9SE8P all-source and release builds pass. A freshly linked main
DOL and all seventeen RELs match all eighteen reference hashes. All 189 automated
tests, the language policy and all 64 remaining postprocessor checks pass.
Formatting and diff checks pass. Compilation and byte matching do not establish
runtime or physical-hardware validation.
