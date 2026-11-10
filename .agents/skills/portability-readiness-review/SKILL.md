---
name: portability-readiness-review
description: Assess which Sonic Heroes GameCube subsystems depend on PowerPC, CodeWarrior, Dolphin SDK, RenderWare, CRI or REL layout before a separate port is designed.
---

# Portability readiness review

Use this skill for a read-only assessment of porting constraints or modding
extension points. Do not implement a native port, replace platform APIs, alter
runtime behavior or loosen GameCube matching requirements in this repository.

## Review procedure

1. **Set scope.** Select a subsystem or a small connected set of translation
   units. Record the commit, supported target (`G9SE8P`) and evidence available.
   Read its source, shared headers, `configure.py` flags, split/symbol entries,
   unit notes and relevant `include/` platform definitions.
2. **Trace the boundary.** Follow direct and indirect dependencies into Dolphin
   SDK, PowerPC runtime, CodeWarrior libraries, RenderWare, CRI, OS/DVD/GX/ARAM
   APIs, shared game globals, and REL imports. Distinguish a proven boundary
   from an inferred one. Record call direction, owned data and where pointers
   or callbacks cross it.
3. **Check target assumptions.** Look for Gekko/PPC instructions and inline
   assembly; endianness; 32-bit pointer/integer assumptions; alignment and
   packed layouts; calling conventions; CodeWarrior mangling, vtables, thunks,
   exception metadata, static initialization and compiler-specific flags;
   allocator ownership; fixed addresses; overlay module IDs and relocations.
   Use actual source and build evidence, not a modern compiler's behavior, to
   establish the original constraint.
4. **Assess semantic risks.** Identify unchecked casts, pointer arithmetic,
   aliasing, lifetime/ownership contracts, allocation failures, integer
   overflow, floating-point rounding, concurrency/interrupt assumptions and
   any behavior that a future host compiler may interpret differently. Mark
   unproved undefined behavior as a hypothesis, not a diagnosis.
5. **Map possible seams.** Describe which gameplay or asset logic is separated
   from platform services and which is interwoven. Note existing callback,
   allocator, rendering, input, file/archive and timing boundaries that could
   inform a separate architecture. Identify potential modding surfaces only
   where symbol, format or call evidence supports them. Do not promise that a
   seam is safe or stable without a separate design and runtime validation.
6. **Separate the deliverables.** Keep all proposed adapters, modern APIs,
   changed behavior, host layouts and modding features as recommendations for
   a future project. Do not edit source, headers, build flags, symbols or
   post-processors as part of this review.

## Evidence labels

Use `VERIFIED` for direct source/build/layout observations, `CORROBORATED` for
consistent but incomplete evidence, `HYPOTHESIS` for plausible interpretations,
and `UNKNOWN` where the available artifacts do not decide. GameCube evidence is
authoritative for the original target. PS2/PC evidence can help identify shared
names or semantics after correlation, but cannot prove GameCube layout or
runtime behavior. A successful match is not proof of portability.

## Acceptance

The review should trace dependencies to concrete files and calls, identify
target-specific contracts and memory/ABI assumptions, and state the validation
still required. Every recommendation must preserve the existing decompilation
as the reference and name the separate porting question it would address.

Stop where a dependency's implementation or lawful evidence is unavailable.
Do not fill gaps with assumed API behavior or use a matching report as a
substitute for runtime evidence.

## Result format

- Scope, commit and evidence coverage
- Dependency map: subsystem/API, file boundary and evidence label
- PowerPC/CodeWarrior/endianness/layout/memory/exception constraints
- Existing separation points and tightly coupled areas
- Potential port or modding seams, with assumptions and risks
- Unknowns and runtime/platform checks still needed
- Recommendations for a separate future project; confirm no code was changed
