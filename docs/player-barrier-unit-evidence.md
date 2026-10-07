# Complete player barrier translation unit evidence

Symbolic metadata identifies player/player_barrier.cpp as C++ with seven
file-origin definitions: transparent display, execution, destructor,
constructor, factory, shutdown and initialization. Six bodies survive at
0x8010C220–0x8010CACC, totaling 2,220 bytes. The constructor inlines into the
factory. No PS2 instructions were inspected.

The class vtable identifies the display, execution and destructor bodies.
Allocation of 0x48 bytes agrees with the GameCube field accesses and symbolic
class layout. The left neighbor uses a different resource set and UV state;
the right neighbor accesses large player fields incompatible with this class.
Neither neighbor is annexed based on proximity.

Eight owned ranges hold 2,220 text bytes, 76 exception bytes, 60 exception-index
bytes, 328 data bytes, 72 BSS bytes, 16 small-data bytes, 16 small-BSS bytes and
48 constant bytes. The complete inventory contains 132 relocations. All owned
storage references occur within these six functions. Shared player/team
arrays, axes and the land manager remain external.

The execution method owns three static tables: nine RGBA entries, twelve
positions and twelve scalar scales. Runtime class/resource strings and the
44-byte vtable complete ordinary data. UV state has 68 logical bytes followed
by four alignment bytes. Small BSS contains three resource pointers and the
previous frame timestamp. The class-name pointer and texture string occupy
small data. The three method-local table symbols retain local binding; their
numeric suffixes are compiler-generated identifiers, not historical names.

All seven ordinary definitions have been reconstructed. Six surviving bodies,
all eight owned sections and all 132 relocations match directly from C++.
Whole-unit automatic deferred inlining with reversed ordinary definitions
reproduces body, vtable, string and constant order. This documents the matching
recipe; the historical source order and compiler flags remain unknown. The
ordinary constructor and weak delete copies remain for normal linker discard.
No object normalizer is used.

Fieldwise initialization of the metadata-backed display color temporary
preserves byte load order, followed by aggregate material-color assignment.
Execution retains its nine-entry color interpolation, alpha fade, complete
matrix copies and paired frame operations. The GameCube team field at 0x206
is explicitly provisional: its barrier flag behavior is observed, but PS2
metadata gives that offset a different identity. No unsupported field name or
full PS2 player layout is copied. Constructor angle fields remain uninitialized
as in the original. Shutdown clears cached pointers without freeing resources.

Verification: the full documented G9SE8P matrix compiles: main DOL and all
seventeen REL targets. All eighteen output hashes match the reference. Final
ELF/map inspection confirms every surviving function address and all owned
bytes, plus natural discard of the 244-byte ordinary constructor and 40-byte
weak delete, their exception records and index rows. The strong TObject delete
remains at 0x8001895C. All 62 automated tests, language policy and object-step
checks pass. No runtime or physical-hardware validation is claimed.
