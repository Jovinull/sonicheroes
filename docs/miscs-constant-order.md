# miscs.cpp compiler constant ordering

All eleven surviving functions are reconstructed in C++, using the language,
API and boundary evidence recorded in `docs/language-audit.md`. Their complete
4,144 instruction bytes already match before normalization. The remaining
compiler difference is the order of six scalar constants in the 64-byte
`.sdata2` pool, affecting 32 bytes of existing compiler output.

## Source investigation and remaining uncertainty

Deferred inlining and reversed external definitions reproduce the function and
exception order. Ordinary automatic inlining moves the drawing routine after
the later angle helpers. Deferred depths 2, 3, 4 and 8 preserve the same remaining
pool permutation; depth 1 loses nested inlining. Source-level literal ownership
trials did not recover the pool order without changing matching function bodies.
No unused helper or artificial data object was introduced to force ordering.

The compiler emits the projectile functions' float half and two constants after
the segment-distance square-root constants; the target places them before.
The lost original declaration or compiler choice responsible for that difference
is not established. `tools/fix_miscs_object.py` keeps this remainder explicit;
remove it when source/compiler settings reproduce the full native pool order.
This is not a source-only byte-match claim.

## Bounded normalization

The step accepts only the measured ELF32 big-endian PowerPC object. It preserves
all instruction bytes, section payload extents, alignment bytes, symbol names,
and relocation records. It permutes existing compiler bytes as follows:

| Input range | Output range |
| --- | --- |
| `0–24` | `0–24` |
| `52–56` | `24–28` |
| `48–52` | `28–32` |
| `24–48` | `32–56` |
| `56–64` | `56–64` |

Six scalar symbol values move with their complete four- or eight-byte atoms.
All 66 pool references use named scalar symbols with zero addends, so those
symbol updates preserve their destinations without changing relocation records.
The other 37 relocations remain untouched. No retail object is an input, and no
instruction or scalar payload is synthesized or copied from retail.

Input/output pool hashes and unchanged text/exception hashes guard the measured
shape. Symbol extents, function inventory, section metadata and all relocation
sites/types/effective targets are checked before any write. Already-normalized
objects must satisfy the corresponding output contract. A rejected object is
left unchanged; successful replacement is atomic.

## Verification scope

An independent audit compares normalized owned section payloads and all 103
resolved relocation destinations directly to the reference, with no exception
for pool permutations. It also checks that normalization changes only existing
pool bytes and the six symbol-value fields, preserves every referenced scalar
payload, and leaves all instructions and relocation records unchanged. The raw
object fails the same exact comparison as a negative control.

Owned payloads are `.text` 4,144 bytes, `extab` 56 bytes, `extabindex` 84 bytes,
`.bss` 262,216 bytes, and `.sdata2` 64 bytes. The compiler marks `.sdata2`
WRITE|ALLOC while the reference object's flags are ALLOC; the normalizer leaves
that compiler metadata unchanged. Its eight-byte alignment agrees. Native image
comparison, rather than object flags alone, establishes the linked result.

The configured native `Matching` build passes the complete documented G9SE8P
matrix: main DOL and 17 RELs, with all eighteen reference image hashes exact.
All 62 relevant automated tests pass, including seven normalizer tests covering
mutation boundaries, scalar-reference preservation, corruption rejection,
idempotence, atomic replacement failure and success-only stamp creation.
Source-language and postprocessor policy checks also pass. These are compile
and binary-identity results; runtime and physical hardware were not tested.
