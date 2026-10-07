# Calc floating-point register evidence

The complete `calc.cpp` C++ unit reconstructs eight interpolation, vector-angle
and matrix-rotation functions across GameCube `0x800D0B08–0x800D1408`.
[language-audit.md](language-audit.md) records the correlated symbolic metadata,
inferred unit boundary, shared declarations, emission order and constant-pool
evidence. Seven bodies match directly; `GetRotYXZ` retains the allocation
remainder below. No PS2 instructions were used.

## Published remainder

Ten register fields in ten of `GetRotYXZ`'s 96 instructions exchange f30 and
f31 for sine and cosine. The function is 384 bytes in a 2,304-byte text section.
The normalizer substitutes only those register fields in compiler output. It
carries no retail instruction words, changes no operation or operand order,
and leaves physical save/restore instructions untouched. This is not a
source-only byte-match claim.

The sine and cosine values are defined at offsets 0x68 and 0x74. Multiplication
consumers occur at 0x8c, 0xcc, 0x114, 0x11c, 0x128 and 0x130; ordered comparisons
consume them at 0xb4 and 0xf8. No other body instruction uses either value.
Both physical FPRs are nonvolatile and saved/restored, including paired state.
All arithmetic here is scalar. Calls between the definitions and final uses
preserve these scalar registers, and the two conditional paths join before the
last four consumers. Neither value is used after the final atan2 call. There
is one return and no alternate failure path.

The same scalar values therefore reach the same operations and comparisons,
with unchanged rounding and NaN behavior. Existing exception metadata still
describes the unchanged physical saves. Only ten file bytes change; all other
instructions, symbols, section metadata and relocation records remain intact.

## Guards and removal path

The tool checks ELF32 big-endian PowerPC shape, complete raw/output text and
function hashes, the global function binding, boundary and size, all fourteen
target relocation records, instruction forms and each register field. Repeated
application rechecks all guards and leaves the object unchanged. Atomic file
replacement and success-only stamps prevent failed runs from publishing output.
Eight synthetic tests cover bounds, idempotence, malformed input and metadata,
instruction corruption and failed replacement cleanup.

Source investigations compared declaration/initialization orders, local copies,
arrays/structures/references, helper expansion, precision and final-expression
lifetimes, plus compiler options. Destructively consuming either trig local
into the final numerator/denominator did not change the allocation. These
trials do not prove every source spelling exhausted. The unexplained compiler
allocation remains explicit; remove the tool and build step when source
reproduces it. Exact input hashes intentionally reject changed compiler output.

## Verification

Independent object comparison verifies all eight normalized bodies, all 85
effective relocations, the 56-byte exception table, 84-byte exception index and
20-byte constant pool. All export offsets and sizes agree. No layout rewriting
or synthetic padding is required.

A fresh native build with calc marked Matching compiles G9SE8P main DOL and
all seventeen RELs; all eighteen retail image hashes pass. All-source
compilation, progress/report generation, 63 automated tests, both policies
and formatting pass. No runtime or physical-hardware validation was performed.
