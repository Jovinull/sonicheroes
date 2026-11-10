# Codex engineering rules

## Project and objective

This repository reconstructs the North American GameCube release `G9SE8P` of
Sonic Heroes. Code compiled with the configured CodeWarrior toolchain must
reproduce the retail DOL and configured REL modules. Matching is necessary
evidence; it does not by itself prove that every unreconstructed source region
has been recovered. The project is not a port and does not distribute game
assets or binaries.

Work in both engineering quality (build, tooling, tests, CI and documentation)
and decompilation quality (types, source structure, semantics and ABI). Keep
changes scoped and supported by evidence.

## Evidence and matching

- Treat the GameCube target and its objdiff results as authoritative. PS2/PC
  symbols and public references may corroborate names, language, types or
  boundaries; they cannot establish a GameCube match on their own.
- Label claims `VERIFIED`, `CORROBORATED`, `HYPOTHESIS` or `UNKNOWN`. A comment,
  old report or successful link is not independent verification.
- Record the commit, compiler flags and report/build used. Distinguish native
  compiler output from post-processed objects and final artifact hashes from
  source coverage.
- Preserve ABI, instruction streams, owned data, symbols, relocations, exception
  metadata and section layout when claiming a completed unit. Do not edit an
  already matching function for style alone; make a change only for a
  demonstrated improvement to source meaning or structure, and prove it keeps
  the relevant match.
- Keep `NonMatching` work visible. A final DOL/REL hash can pass while an
  unreconstructed region is still supplied by the split retail object; consult
  the objdiff report and unit diff before claiming source completion.

## C and C++ conventions

- Follow `docs/language-policy.md` and `config/G9SE8P/language_policy.json`.
  Game-owned code is C++ by default; use `.cpp` unless a reviewed C boundary or
  known C library justifies C. Do not infer original language from a byte match.
- Put shared declarations in `include/`; keep genuinely private declarations
  in their translation unit. Preserve documented offsets, widths, alignment,
  class/vtable shape, linkage and CodeWarrior-specific behavior. Mark unknown
  fields and names as unknown or inferred rather than presenting guesses as
  facts.
- Format touched C/C++ source with the repository's `.clang-format` policy.

## Object post-processors

Post-processors may describe measured compiler/object-layout gaps and make
fail-closed transformations of compiler-produced output. Do not add retail
instruction/data content, target-object inputs, opaque replacements or new
exceptions to the recorded debt. Review both pre- and post-processor objects,
and keep the documented remainder and exit path current. See
`docs/object-post-processors.md` and `tools/check_post_processors.py`.

## Safety and collaboration

- Start by checking Git status and worktrees. Use a separate Codex worktree and
  branch; never change another contributor's worktree, branch, index, shared
  Git settings or hooks to make progress. Do not push or merge unless asked.
- Keep legally obtained original inputs only in ignored local `orig/` paths.
  Never copy or commit disc images, DOL/REL files, assets, extracted assembly,
  complete proprietary symbol dumps, credentials or private reports. Follow
  `LEGAL.md` for cross-platform evidence and publication limits.
- Treat `configure.py`, `.github/workflows/` and `tools/` as executable build
  paths. Review their data flow and private-input boundary before changing
  them. Do not weaken private-build or fork protections.
- Do not commit logs, screenshots, generated reports, build outputs or other
  disposable evidence. Add durable documentation only for reviewed facts or a
  reusable process.

## Validation and modernization boundary

- Run relevant public tests and policy checks. With lawful original inputs and
  the configured toolchain, also build all source, generate objdiff reports,
  compare code/data/relocations and verify every configured artifact hash in
  `config/G9SE8P/build.sha1`. Report unavailable checks as unavailable; a
  partial build is not a pass.
- Changes intended to preserve the original GameCube binary belong in this
  repository. Portability, new platform APIs, changed runtime behavior and
  modding features belong in a separate future project; record recommendations
  without implementing them here.

## Reusable procedures

- Use `.agents/skills/decomp-quality-review/SKILL.md` for translation-unit
  semantic review and matching-preserving experiments.
- Use `.agents/skills/build-and-regression-verification/SKILL.md` for
  independent build and regression validation.
- Use `.agents/skills/portability-readiness-review/SKILL.md` for a read-only
  porting-readiness assessment.
- Start with `docs/README.md`, `docs/getting_started.md`, `CONTRIBUTING.md`,
  `LEGAL.md`, and `docs/decomp-work-tracking.md`; check live ownership because
  tracking entries can age. See `docs/symbols.md`, `docs/splits.md`,
  `docs/language-audit.md`, and unit evidence notes for specialized evidence.
- Read `docs/codex-engineering-baseline.md` for the commit-scoped quality
  snapshot and prioritized audit queue; refresh its measurements when the base
  commit changes.
