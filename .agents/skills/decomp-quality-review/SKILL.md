---
name: decomp-quality-review
description: Review or refine a Sonic Heroes GameCube translation unit for source structure, semantics, types, ownership, or ABI while preserving its matching requirements.
---

# Decompilation quality review

Use this workflow when a translation unit or completed function needs a
structural or semantic audit, or when a matching-preserving source experiment
has a specific technical hypothesis. Do not use it to modernize runtime
behavior or to claim a port is ready.

## Review procedure

1. **Scope and ownership.** Name one translation unit and its configured DOL or
   REL. Read its source header, `configure.py` object entry and flags,
   `config/G9SE8P/splits.txt`, relevant symbols, `docs/decomp-work-tracking.md`,
   and any linked unit evidence. Confirm the area is not being changed by
   another contributor. Tracking notes can be stale; do not infer live
   ownership from an old row.
2. **Set the baseline.** Record the worktree commit and status, toolchain
   version, effective CodeWarrior flags, compiler object and objdiff report used.
   Note whether the configured object is `Matching` or `NonMatching` and
   whether a post-processor runs. A public aggregate report cannot prove a
   particular unit's state. If exact local evidence is unavailable, state that
   matching is unverified and do not propose replacing the implementation.
3. **Collect independent evidence.** Inspect calls and data references,
   neighboring functions, split boundaries, mangled symbols, section ownership,
   relocations, exception records, vtables/thunks, and shared declarations.
   Read relevant notes in `docs/language-audit.md` and `docs/*-unit-evidence.md`.
   Use PS2 or PC material only for correlated symbolic evidence, under
   `LEGAL.md` and `docs/language-policy.md`; never publish local dumps.
4. **Reconstruct the contract.** Describe responsibilities, inputs/outputs,
   invariants and failure paths. Check field offsets and widths, signedness,
   alignment, pointer arithmetic, aliasing, ownership and lifetime, allocation
   and cleanup, exception behavior, virtual dispatch, calling convention and
   compiler-specific assumptions. Separate observed behavior from inferred
   original source spelling. Do not treat an original-game quirk as a bug
   without evidence.
5. **Identify a meaningful question.** Record a concrete defect, uncertainty or
   source-structure limitation and why improving it matters. A matching
   function may still merit review, but style alone is not a reason to change
   it. If there is no defensible improvement, say so.
6. **Experiment only when justified.** Preserve the source and object baseline.
   Try one isolated alternative in the Codex worktree, without changing another
   contributor's branch. Compare the raw compiler object and, where applicable,
   the post-processed object against the same reference. Inspect instructions,
   owned data, symbols, relocations, exception metadata and section layout; do
   not rely on a function percentage alone. Reject or revert an alternative
   that loses fidelity, relies on an unproved assumption, or does not improve
   the source reconstruction.
7. **Validate and conclude.** For an accepted source change, run the applicable
   policy/tests, full source compilation, objdiff, linked-artifact hash check
   and match-regression comparison when the original inputs and toolchain are
   available. See `build-and-regression-verification` for the exact project
   workflow. Do not claim runtime or hardware validation unless it was actually
   performed.

## Evidence labels

- **VERIFIED** — directly confirmed by the current build/object diff, test,
  symbol/section/relocation data or another reproducible primary observation.
- **CORROBORATED** — supported by multiple consistent facts, but not directly
  decisive for the claim.
- **HYPOTHESIS** — plausible interpretation or source spelling awaiting a
  discriminating test.
- **UNKNOWN** — the available artifacts do not answer the question.

Do not promote a hypothesis to fact because a comment or older audit repeats
it. A final image hash proves the configured image bytes, not the source
coverage of every region.

## Acceptance

A review is complete when its scope and baseline are identified, evidence and
unknowns are separated, semantics and ABI constraints are described, any
experiment is reproducible and compared at object level, and the verdict is
clear. Accept a code change only when it improves source meaning or structure
and preserves the required match; otherwise leave the correct implementation
unchanged.

## Stop conditions

Stop the experiment if ownership is unclear, lawful required input is absent,
the reference object/report does not correspond to the recorded commit, a
change would require copying proprietary artifacts, or the proposed result
depends on unsupported assumptions. Finish with an explicit limitation rather
than filling the gap by inference.

## Result format

- Scope, worktree commit and baseline status
- Evidence table with labels and source of each claim
- Reconstructed contract, types/layout and memory/ABI findings
- Confirmed issues, hypotheses and unknowns
- Alternatives tried and before/after object results, or why none were needed
- Verdict: accept, leave unchanged, or investigate further
- Tests and build checks run, failed, skipped or unavailable
