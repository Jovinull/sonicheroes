# Collision compiler constant order

The complete `calc_colli.cpp` C++ unit emits all eight instruction bodies exactly
(6,860 bytes), together with the 56-byte exception table, its 84-byte index and
28 bytes of owned data. Its remaining compiler difference is the ordering of
three floating-point scalar constants.

Using an opaque named external zero changes floating-point register allocation
in the sphere intersection function. Literal zero gives the native instruction
bytes. All zero uses share that compiler-owned atom; the separate named zero
definition is removed, so storage is not duplicated. Component caches in the
point-to-line distance function reconstruct the GameCube register lifetimes;
the PS2 symbol metadata does not establish identical platform-local temporaries.
The original source/compiler detail responsible for pool order remains unknown.

`tools/fix_calc_colli_pool.py` makes the remaining difference explicit. This is
not a source-only constant-pool match claim. Remove this step when native source
and compiler emission recover the pool order.

## Permitted transformation

The 24-byte compiler pool contains four four-byte scalar atoms and one eight-byte
double atom, with the same payloads as the reference. The transform permutes
three complete existing scalar atoms:

| Native range | Output range | Atom |
| --- | --- | --- |
| 0–4 | 0–4 | named epsilon |
| 4–8 | 8–12 | named one |
| 8–12 | 12–16 | anonymous minus one |
| 12–16 | 4–8 | anonymous zero |
| 16–24 | 16–24 | anonymous double |

The three moved symbols follow their atoms. All 50 pool references name atom
symbols, so instruction bytes, relocation records and addends remain unchanged.
The other 27 relocations are untouched. No instruction, constant value, padding
or original-game payload is synthesized. The original object is never a
build-step input. Pool size, alignment and section flags are preserved.

Whole-object and pool hashes guard both native and normalized states. ELF
layout, the complete named atom inventory, sizes, binding, placement and
pool-reference shapes are checked before mutation. Rejected inputs remain
unchanged. Successful writes replace the object atomically; the optional build
stamp appears only after success. An already normalized object is accepted
without rewriting it.

## Verification

Independent comparison against the locally supplied original confirms every
owned section and all 77 normalized relocation destinations after reordering.
The raw object's instruction and non-pool data bytes already match; only pool
order and the affected symbol destinations differ. All five owned payloads have
identical lengths and require no synthesized alignment tail.

Nine synthetic ELF tests cover exact output, idempotence, permitted mutation
ranges, preservation of the fixed atoms and double, reference-value preservation
(including an interior double reference), corrupt objects and unsupported shapes,
atomic-write failure cleanup, and success-only stamps. Test payloads contain no
original-game bytes. A fresh native object also passes the guarded transform,
idempotence check and independent section/relocation comparison.

Full release-build and hash results belong in the unit evidence and pull request;
these checks do not establish runtime or physical-console validation.
