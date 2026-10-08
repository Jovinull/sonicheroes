# Complete enemy shock-wave translation unit evidence

Positive symbolic metadata identifies enemy/e_shockwave.cpp as C++ and thirteen
file-origin definitions. Eight bodies survive at 0x8011AACC–0x8011B5A8, totaling
2,780 bytes: UpdateShockWaveModelParam, TDisp, Exec, destructor, Finalize,
Initialize, Create and the sShockWave constructor. The remaining five authentic
methods inline or are unused. No PS2 instructions were inspected.

The preceding helper configures an unrelated atomic pipeline and is called by
the independently reconstructed material unit. The following function belongs
to the completed RenderWare utility unit. Owned sections include 116 exception
bytes, six exception-index rows, class string/vtable data, a full sixteen-byte
local RwRGBAReal initializer, 68-byte UV state plus alignment, the class pointer,
three private state variables and a 72-byte floating constant pool. Reference
scans confine this storage to the eight surviving functions.

The GameCube object is 0x9C bytes, established by its allocation and size store,
not the older platform's 0xA0-byte metadata size. It contains TObject, the
12-byte position parameter at 0x28, clump at 0x34, timer at 0x38, four 20-byte
model parameter records at 0x3C, and four frame pointers at 0x8C. UVFXInfo uses
its GameCube matrix offset four and 68-byte logical size. The rendering local
is four floats including alpha; its initializer has no trailing padding.

Create is static void. Its constructor initializes the position parameter
before copying the supplied value and cloning the clump. Source reconstruction
preserves model updates, frame IDs 3000–3003, collision-independent lifecycle,
and the owned clump cleanup. Eleven existing source consumers and three fixers
receive mechanically verified same-address canonical renames and formatting.
The unit is enabled as Matching after independent production-object
and complete supported build and final-link verification.

The ordinary automatic-inlining trial left a forward call to the parameter
constructor. Whole-TU deferred inlining removes that call, and reversing all
thirteen ordinary definitions restores the native body and constant emission
order. This is a reconstruction recipe, not a claim about historical flags or
source line order. No object normalizer or instruction rewriting is used.

Update uses a const signed-integer reference to mTimer for the upper bounds of
the four later intervals; the first interval retains direct member reads.
This asymmetric source spelling restores the original four timer reloads. It
is a reconstructed lifetime choice, not a metadata-backed original local.
The reference names the same nonvolatile member and introduces no stores or
other effects. Every earlier successful interval exits the entire chain, and
there are no calls or writes on the path to a later interval test, so the
alias preserves all integer comparisons and branch selection. Independent
comparison confirms all 64 ordered AdjustFloat calls, destination fields and
exact float arguments across the five timer intervals.

The frozen object matches all eight bodies and 297 effective surviving
relocations. All nine owned section payloads match, including the complete
72-byte pool and 16-byte color initializer. Five unused authentic helpers
produce 700 bytes of extra text, alongside a forty-byte weak TObject delete;
four extra exception records and index rows occupy 52 and 48 bytes. The final
map confirms normal removal of those copies and retention of the strong Task
delete at 0x8001895C. Independent final ELF comparison verifies all eight body
addresses and every owned section byte, flag and alignment, including padding.

All supported G9SE8P targets compile; the main DOL and seventeen RELs pass all
eighteen expected output hashes. All 62 automated tests and language and
post-processor checks pass. No runtime or hardware validation was performed.
