# Complete enemy ring-laser translation unit evidence

Positive symbolic metadata identifies enemy/e_ringlaser.cpp as C++ and gives
fourteen file-origin methods. Seven survive at 0x80113CCC–0x801143E0 (1,812
bytes): TDisp, Exec, destructor, Create, Finalize, Initialize, and the parameter
constructor. The remaining seven methods inline or are unused. No PS2
instructions were inspected. The preceding constructor/helper reference another
class; the following named SeqFlagCtrl function establishes the right boundary.

Owned sections include 128 exception bytes, five exception-index rows, a local
vector initializer, collision info, class name and vtable, UV effect storage,
three private state values, the class pointer and the floating constant pool.
UVFXInfo uses the GameCube matrix at offset four and is 68 bytes with four
trailing alignment bytes; older platform matrix alignment is not copied.
TObjEnemyRingLaser is 0xE4 bytes with TObject and C_COLLI bases, parameters at
0xB0 and clump pointer at 0xE0. The parameter structure is 0x30 bytes.

The referenced collision pause helper is positively identified as void
C_COLLI::ClearInfo by symbolic metadata and GameCube behavior. An incidental
register value used to clear hit slots is not treated as its return type.
Sixty-three existing source consumers and five existing fixers receive only
canonical same-address renames and formatting, mechanically verified against
the base. The unit is enabled as Matching after independent object and final-link
verification.

The source-only matching recipe uses whole-TU automatic deferred inlining and
reversed ordinary definition order. The first ordinary-auto trial retained
forward calls to authentic parameter helpers, shortening Exec and Create.
Deferred inlining restores those bodies; reversing the definitions restores
surviving function and constant emission order. The original source order and
historical flags are not claimed to be recovered. No object normalizer or
per-function compiler mode is used.

TDisp captures the global time in the metadata-backed signed local tmr before
comparing and updating the private timestamp. Exec uses a reconstructed inline
restart predicate and compares the authentic signed-integer Alive result as
long, preserving its integer materialization on this 32-bit target. These
source lifetime/type forms recover instruction allocation without assembly.
The parameter scale cap preserves unordered floating comparisons; pause clears
collision state without advancing parameters, and expired life sets the delete
signal before collision entry. The static collision initializer places 0x4000
in angx, as the GameCube data requires.

The frozen production object independently matches all seven bodies and 110
effective surviving relocations. All nine owned section payloads match,
including the 48-byte floating constant pool. Seven unused authentic methods
produce 804 extra text bytes, plus a forty-byte weak TObject delete. Their four
extra exception records and index rows occupy 72 and 48 bytes respectively.
These compiler-produced copies are left for the normal linker to discard;
the final map confirms their removal, with the strong Task delete retained at
0x8001895C. Final ELF comparison verifies all seven addresses and every owned
section byte, flag and alignment, including natural trailing padding.

All supported G9SE8P targets compile, and the main DOL plus seventeen RELs pass
all eighteen expected output hashes. All 62 automated tests and language and
post-processor checks pass. No runtime or hardware validation was performed.
