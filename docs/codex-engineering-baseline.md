# Engineering and decompilation quality baseline

Snapshot date: 2026-10-24. Repository baseline: `4ed1dd0a96f5a6fe50fd88fb9a8c8f29cd708b95` (`origin/main`). This is a commit-scoped reference, not a claim about later commits.

## Evidence and build model

The project targets GameCube `G9SE8P`, North American revision 0. `configure.py`
defines CodeWarrior versions and per-object flags; `tools/project.py` generates
the Ninja build and `objdiff.json`. decomp-toolkit uses `config/G9SE8P/config.yml`,
`splits.txt` and `symbols.txt` to extract target objects from a lawful local
copy. MWCC compiles reconstructed sources, while unwritten regions can remain
in the extracted objects. Object post-processors run where configured; MWLD and
dtk link/emit the DOL and RELs. ObjDiff compares target and source objects.
`build.sha1` checks the final `main.dol` and seventeen configured REL modules.
`stage00D` is excluded because its DOL relocations do not resolve to configured
sections and it shares a module ID with `stage01D`.

The configured linker is CodeWarrior GC/1.3.2 for Gekko/PowerPC. Base flags
include hardware floating point, C++ exceptions off by default, `-O4,p`,
automatic inlining, RTTI off and project-specific include/encoding options;
units override these settings. The pinned project tools include a decomp-toolkit
fork (`v1.8.3-sh1`) for REL section-index handling and objdiff-cli (`v3.6.1`).
Game-owned code is C++ by default under `docs/language-policy.md`; reviewed C
boundaries and known libraries remain explicit exceptions. PS2 symbols are
optional, correlated evidence for names/types/boundaries only. They do not
replace GameCube objdiff or establish GameCube behavior.

## Measured progress

The public ByteMatch project record reports this exact baseline commit. The
latest public GitHub Actions Build run for the same SHA completed successfully.
The metrics are from the [ByteMatch project record](https://bytematch.dev/Jovinull/sonicheroes.json),
not from this worktree's filesystem. The successful [Actions Build run](https://github.com/Jovinull/sonicheroes/actions/runs/40131214465)
is external CI evidence:

| Measure | Reported value |
| --- | ---: |
| Matched code | 4,618,108 / 13,039,060 bytes (35.42%) |
| Complete code | 4,596,104 / 13,039,060 bytes (35.25%) |
| Matched data | 679,064 / 7,167,586 bytes (9.47%) |
| Matched functions | 20,559 / 39,062 (52.63%) |
| Complete units | 11,012 / 16,538 |

By category, game code reports 95.72% matched code and 97.60% matched
functions; SDK code reports 100% code and function matches; configured modules
report 36.94% matched code and 1.90% matched data. These are objdiff report
categories, not runtime or port-readiness measures. Matched code and complete
code are separate measures.

## Verification observed

- The public `Build` workflow for the baseline commit completed successfully.
  Its configured steps run focused language/post-processor tests, policy
  checks, source compilation, progress/report generation and an explicit
  SHA-1 check for the configured artifacts. This is external CI evidence; this
  worktree did not have original-game inputs.
- Local public suite: `python -m unittest discover -s tools -p "test_*.py" -t .`
  ran 213 tests successfully with five skips: four require `llvm-objcopy` and
  one requires PowerPC binutils.
- Local `python tools/check_post_processors.py` passed and checked 60 configured
  steps. The repository contains 38 `fix_*_object.py` scripts.
- The full `python tools/check_language_policy.py` command was attempted but
  could not read Ninja commands because this worktree has no generated
  `build.ninja`. No original inputs were present beyond `orig/G9SE8P/.gitkeep`,
  so configuration, native build, local objdiff and local hash verification
  were not run. The language-policy unit tests did run in the suite.
- No gameplay/runtime or physical-console tests are defined by this baseline.

## Risks and next engineering work

| Priority | Evidence | Follow-up |
| --- | --- | --- |
| Private build trust boundary | The workflow copies `/orig` into the build container. `.github/CODEOWNERS` covers workflows and `tools/`, but deliberately excludes `configure.py`, which also runs in that container; `CONTRIBUTING.md` documents the review trade-off. | Review ways to reduce privileged code paths or strengthen review evidence without blocking normal unit work. No exploit is established by this observation. |
| Toolchain reproducibility | `configure.py` pins tool version tags, but `tools/download_tool.py` does not verify release hashes; the private build image uses the mutable `:main` tag. | Record/pin image digest and tool checksums where upstream artifacts support it; validate archive extraction boundaries. Treat as supply-chain/reproducibility work. |
| Regression gate coverage | CI runs focused policy tests. The progress comparison is explicitly informational and warns/skips if no successful main report artifact is available. | Assess an unprivileged CI job for the complete public tools suite and a reliable regression baseline. Keep fork jobs away from private inputs and credentials. |
| Post-processor source provenance | 38 scripts feed 60 configured steps. `tools/check_post_processors.py` permits two documented carried-content debts: `fix_game_action_object.py` (`TARGET_EXTAB`) and `fix_eff_tornado_object.py` (`TEXT_PATCHES`). | Keep these exceptions visible, report native versus transformed matches per affected unit, and remove debt only after source experiments preserve object and linked matches. |
| Source/runtime coverage | The 213 tests exercise tools and post-processors; they do not test game behavior. Aggregate reports do not distinguish direct compiler matches from transformed output. | Use per-unit object evidence for semantic claims. Treat runtime/port validation as separate work. |

## Semantic audit queue

1. `src/game/object.cpp` — 79-function resource/object unit. Its committed
   evidence describes all source functions and relocations, plus a remaining
   register normalizer affecting ten fields in six instructions. Review the
   two resource-scan cursor lifetimes and test whether source/compiler choices
   can remove that step without changing any other output.
2. `src/game/one.cpp` — 25-function ONEFILE archive/resource loader with
   matching exception metadata and 422 relocations. High value for archive
   ownership, stream arithmetic, allocation lifetimes and future asset-system
   boundaries; two GameCube-specific method names remain unknown.
3. `src/game/matrix.cpp` — 16-function matrix API with seven owned sections and
   104 relocations. Foundational for camera and transform code; its evidence
   still marks camera fields as partial and several callees/globals by address.
4. `src/game/pathctrl.cpp` — eight exact instruction bodies; the committed
   evidence describes a bounded scalar-pool permutation and callback/player
   layout. Review source fidelity and whether the remaining constant order is
   recoverable natively.
5. `src/game/calc.cpp` — eight direct compiler matches, including a scoped
   optimization setting for `GetRotYXZ`. Audit floating-point assumptions and
   distinguish reconstructed compiler settings from proven historical flags.

These are candidates, not reported defects. `matrix.cpp` and `one.cpp` are
appropriate completed-unit audits; neither needs a change merely because it is
selected. Confirm live ownership and obtain a current per-unit object baseline
before experimentation.

## Suggested next mission

Audit only `src/game/object.cpp`. Establish a same-commit raw-object and
post-processor baseline, explain the two scan-cursor live ranges from source
and target data flow, then test a small number of justified source/compiler
alternatives in isolation. Accept a source-only result only if all 79 function
bodies, owned data/exception sections, symbols and 800 relocation destinations
match directly, the register normalizer can be removed, and the complete
configured DOL/REL hashes still pass. If required original inputs are absent or
no better source is demonstrated, leave code unchanged and record the
limitation as unresolved.
