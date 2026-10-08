# Complete brim and fly-jump effect translation unit evidence

Positive symbolic metadata identifies effect/eff_brim.cpp as C++ with 35
file-origin definitions, including the local material callback. Three ordinary
constructors inline into callers. Six additional virtual accessors are
positively identified in header metadata, producing 38 surviving GameCube
bodies at 0x8010CE9C–0x8010F5D8, totaling 10,044 bytes. All 35 ordinary definitions
and all six accessors belong to the reconstruction. No PS2 instructions were
inspected.

The final two node accessors extend the complete boundary beyond four shorter
color accessors. Their names, vtable slots and node-index calls are independently
correlated. The preceding player-receiver operations use unrelated storage;
the following class has separate collision data and a distinct receiver layout.
No owned storage has a code reference outside the complete function range.
Boundaries follow metadata and the complete vtable/storage graph; no original
GameCube object-file debug provenance is claimed.

Nine owned ranges contain 10,044 code bytes, 420 exception bytes, 324 index
bytes, 24 read-only bytes, 648 data bytes, 136 BSS bytes, 24 small-data bytes,
40 small-BSS bytes and 128 constant bytes, with 625 relocations. Data includes
three twelve-entry defaults tables, two collision descriptors, the eight-color
Exec-local random table, resource/class strings and four vtables. The Brim
vtable has eighty logical bytes plus four alignment bytes. Two private UV
state objects have the verified GameCube 68-byte stride. Eight resource
pointers and two signed timestamps are private. Class-name pointers are global.
Metadata Brim2 and UVRotateSpeed entries at address zero are declarations and
do not justify adding storage or neighboring implementations.

GameCube allocation/access evidence confirms class sizes 0x60 (BrimS), 0xE8
(FlyJump2), 0x138 (FlyJump), and 0x1A74 (Brim). FlyJump differs from the PS2
0x150 layout because of matrix alignment; its GameCube matrix begins at 0xF4
and clump pointer at 0x134. Brim has 126 nodes of sixteen bytes at 0xC4 and 126
vertices of 36 bytes at 0x8A4, independently supported by bounds and offsets.

The complete source is reconstructed and independently reviewed. Ordinary
reversed definitions and whole-unit auto,deferred recover the surviving body
order. The FlyJump2 constructor is declared inline: ordinary, deferred, smart
and bounded depth variants otherwise retain an out-of-line call where retail
expands this genuine constructor. Its original qualifier is unknown; this is
a source hypothesis supported by the sole inlined call site and lack of a
surviving standalone body. All six virtual getters are ordinary out-of-class
definitions to retain global binding and final body order. GetPos/GetAng remain
metadata-backed reference accessors.

Two compiler layout differences remain after bounded source trials: a typed
literal-pool permutation after offset 84, and one eight-byte GetPreviousNode
exception record emitted late. Moving the getter definition recovers exception
order only by changing surviving function order; marking it inline additionally
changes binding. Named constants and constructor-order alternatives do not
recover both matching code and the pool layout.

The guarded fix_eff_brim_layout.py step permutes existing compiler atoms only.
It preserves every instruction, all relocation addends and all effective
references. It updates twenty local atom values and nine exception relocation
source offsets; no new atom, instruction or data payload is synthesized. Whole
input/output and section hashes, exact typed atom coverage, load widths,
bindings, visibility and relocation inventories reject unexpected compiler
output. Independent reconstruction produces the same complete object. Twenty
synthetic tests cover permitted mutation bounds, preserved atom/reference
meaning, corruption rejection, idempotence and failure-atomic CLI writes.

Color arithmetic retains the observed target compiler behavior. Compound
float-to-u8 conversion can exceed 255: for example, green 174 plus a random
increment approaching 128 becomes integer 301 and retail stores byte 45.
The configured Metrowerks fctiwz/stb sequence matches exactly; portable C++ does
not define this as modulo narrowing. Explicit intermediate integer conversion
is defined but emits three additional mask instructions. The original source
spelling remains unknown; neither portable conversion behavior nor unreachable
out-of-range inputs are claimed.

The complete unit passes strict production-object comparison: all 38 surviving
bodies and bindings, all 625 effective relocations, and all nine owned sections
including verified alignment. Same-address collision-class aliases are
propagated through existing consumers; independent comparison verifies those
consumer changes consist only of renaming and required formatting.
With the complete unit enabled as Matching, all-source compilation and the
G9SE8P release DOL plus all seventeen supported RELs pass. All eighteen
reference hashes match. Independent final-map/ELF comparison confirms all 38
original body addresses and all nine complete byte ranges. The ordinary
FlyJump/Brim constructors (368/284 bytes), weak delete (40 bytes), and their
104 exception/36 index bytes are naturally discarded; the original strong
TObject delete is retained. Objdiff reports 100% for all 38 functions; strict
surviving-object and final-link audits account for compiler-only helper/EH
records separately. All 82 automated tests and both policy checks pass.
Compilation and byte comparison do not establish runtime or physical-hardware
validation.
