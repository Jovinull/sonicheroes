# Path-control compiler constant order

The complete `pathctrl.cpp` C++ unit emits all eight instruction bodies exactly
(4,676 bytes), including the original exception records and indexes. Its owned
role table and fourteen floating-point constants are complete. The remaining
compiler difference is the position of the `9.0f` scalar emitted by
`pathGlidingReg`.

Using an opaque named external constant preserves the reference pool order but
changes floating-point register allocation. The literal produces exact native
instructions and one anonymous four-byte atom, `@402`. It does not duplicate
any scalar storage. Definition placement and source-level helper reconstruction
did not simultaneously recover its instruction allocation and pool placement.
The original declaration/compiler detail responsible remains unknown.

`tools/fix_pathctrl_pool.py` keeps this difference explicit. This is not a
source-only constant-pool match claim. Remove the step when native source and
compiler emission recover the pool order.

## Permitted transformation

The 56-byte compiler pool has the same fourteen scalar payloads as the reference.
The transform moves complete existing atoms:

| Native range | Output range |
| --- | --- |
| 0–4 | 48–52 |
| 4–52 | 0–48 |
| 52–56 | 52–56 |

Thirteen symbol values move with their atoms; the final atom stays in place.
All 36 pool references name scalar symbols, so instruction bytes, relocation
records and addends remain unchanged. The other 74 relocations are untouched.
No instruction, scalar value, padding or original-game payload is synthesized.
The original object is never a build-step input.

Whole-object and pool hashes guard both native and normalized states. ELF
layout, complete atom coverage, symbol extents and pool-reference shapes are
checked before mutation. Rejected inputs remain unchanged. Successful writes
replace the object atomically; the build stamp appears only after success.

## Verification

Independent comparison against the locally supplied original checks every
owned section and all 110 normalized relocation destinations. The raw object
fails that comparison on constant order, while the transformed object passes.
The transform preserves exact `.text`, `extab`, `extabindex` and role-table
payloads. The linker supplies the role table's four zero alignment bytes.

Synthetic ELF tests check exact output, idempotence, allowed byte mutations,
reference-value preservation, corruption and unsupported-shape rejection,
atomic-write failure cleanup, and success-only stamp creation. Test payloads
contain no original-game bytes. Full release-build and hash results are
recorded in the unit evidence and pull request; these do not establish runtime
or physical-console validation.
