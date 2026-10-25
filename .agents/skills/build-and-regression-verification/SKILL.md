---
name: build-and-regression-verification
description: Validate Sonic Heroes source, tool or configuration changes with the repository's tests, CodeWarrior build, objdiff reports and DOL/REL hash checks.
---

# Build and regression verification

Use this skill when independently validating a code, build, language-policy or
object post-processor change. The project targets GameCube `G9SE8P`; do not
assume an original disc image, extracted files or private build container are
available.

## Establish the baseline

1. Confirm the worktree, commit and changed paths. Check that the comparison
   report and build inputs correspond to the same commit and `G9SE8P` target.
2. Check locally whether a legally obtained original is already present under
   ignored `orig/G9SE8P/`. Never copy an image, DOL, REL, assets, extracted
   assembly or private files into this worktree. If the input is absent, run
   only the independent public checks below and label the full build unavailable.
3. Preserve a baseline report/object for any comparison. Distinguish the
   compiler-produced object, post-processed object, linked image and objdiff
   progress report. Do not use final hashes as a substitute for source-match
   evidence.

## Independent public checks

These commands do not require the original game input:

```text
python -m unittest discover -s tools -p "test_*.py" -t .
python tools/check_post_processors.py
```

Record test totals and skips with their reasons. A skip caused by a missing
optional tool is not a pass for that test. The focused language-policy and
post-processor unittest modules are also run by CI:

```text
python -m unittest tools.test_check_language_policy
python -m unittest tools.test_check_post_processors
```

The full `python tools/check_language_policy.py` check reads effective source
compiler commands from the generated Ninja graph. Run it only after a valid
project configuration exists; report it unavailable if configuration or
original input is missing. Do not create a false build by copying original
artifacts.

## Full GameCube verification

With lawful local inputs and the configured toolchain available, follow the
repository's setup and build flow:

```text
python configure.py
python tools/check_language_policy.py
python tools/check_post_processors.py
python -m unittest discover -s tools -p "test_*.py" -t .
ninja all_source progress build/G9SE8P/report.json
build/tools/dtk shasum -c config/G9SE8P/build.sha1
```

The expected configured hashes cover `main.dol` and seventeen RELs. Confirm
objdiff's per-unit code, owned data, symbols, relocations and applicable
exception/section metadata for changed units. For a post-processed unit inspect
both sides of the step and determine which bytes or metadata it changes. Run
the workflow's baseline report comparison and examine any regressions. If a
report baseline is unavailable, state that the comparison was skipped.

CI's `build_gate` is required by the documented repository policy. The
`progress_report` job compares a pull request's objdiff report to the latest
successful `main` report, but the workflow comments identify that job as
informational and it may skip comparison if no baseline artifact is available.
The fork path intentionally cannot run with private game inputs; follow the
maintainer-reviewed integration path in `CONTRIBUTING.md` rather than weakening
that boundary.

## Interpret results correctly

- Passing `build.sha1` establishes that the configured linked artifacts match
  the reference. Unreconstructed regions may still be linked from extracted
  objects, so this does not establish 100% source reconstruction.
- `Matching` in `configure.py` is configuration state. Confirm the actual
  object against objdiff for the current commit.
- A function's instruction match does not alone establish correct names,
  source language, translation-unit boundary, data layout or portability.
- Compilation is not runtime equivalence. Runtime or hardware results must be
  reported separately.

## Acceptance and stop conditions

Accept only checks actually run against the relevant commit and target. If
configuration, compiler, original input, reference object, or test dependency
is absent, do not configure it as a passing check; stop that check and report
what is needed. Any mismatch, unexplained change to a section/relocation, or
processor that does not fail closed blocks a matching claim until resolved.

Report each check as `PASS`, `FAIL`, `NOT RUN`, or `BLOCKED`, with a short
reason. Include the commit, target, toolchain, focused object result, full
artifact hash result and regression comparison when available.
