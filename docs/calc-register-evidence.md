# Calc native compiler matching

The complete `calc.cpp` C++ unit reconstructs eight interpolation, vector-angle
and matrix-rotation functions across GameCube `0x800D0B08–0x800D1408`.
[language-audit.md](language-audit.md) records the correlated symbolic metadata,
inferred unit boundary, shared declarations, emission order and constant pool.
No PS2 instructions were used.

## Compiler settings

All eight functions now match directly from compiler output. Scoped
`#pragma optimization_level 1` around the 384-byte `GetRotYXZ`, followed
immediately by a reset, reproduces its sine/cosine register allocation.
The other seven functions retain the existing unit settings and exact output.
The compiler accepts this directive without warnings. Disabling dead-assignment
elimination is unnecessary. These settings are reconstruction choices; the
historical presence of this pragma is not established.

The former post-processor changed ten floating-point register fields in
`GetRotYXZ`. That instruction normalizer, its build rule and obsolete synthetic
tests have been removed. No instruction bytes are patched after compilation.
Deferred inlining, source definition order, headers and layout remain unchanged.

## Verification

Direct object comparison verifies all eight functions, all 2,304 text bytes,
all 85 normalized relocations, the 56-byte exception table, 84-byte exception
index and 20-byte constant pool. Export offsets, sizes and section alignments
agree, with exactly eight emitted function bodies and no extra sections.
No layout rewriting or synthetic padding is required.

All-source compilation and a fresh main ELF/DOL release link pass. All eighteen
G9SE8P image hashes (main DOL plus seventeen RELs), 196 automated tests, language
policy, all 64 remaining post-processor checks and formatting pass.
G9SE8P is the sole supported build target; compilation and image matching do
not establish runtime or physical-hardware validation.
