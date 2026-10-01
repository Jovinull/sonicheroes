# CRI completed-unit integration, 2026-09-25

## Scope and duplicate audit

Integration starts from upstream `main` at `4243c6c` (the repository has no
`master` branch). This consolidates existing completed work, not 162 newly
reconstructed functions. No partial raster, GCCI, MFCI, RenderWare compressed-key,
or stage-unit work is included. Existing dirty worktrees are preserved.

The following completed commits are represented once:

| Work | Original completion commit |
| --- | --- |
| SVM | `f79df80` |
| RNARES | `4fa6023` |
| AXRNA | `d70820f` |
| SJ / SJRBF / SJUNI | `f8d5566` |
| SJMEM | `90deef7` |
| LSC family | `e5ba8a5` |
| Adapter | `cb647b6` |
| SFXAHN | `44f2215` |
| SFXSET | `28abae1` |

The older partial `fn_8021F410.c` work is superseded by the complete `lsc_err.c`
in the LSC family. Do not reapply it. The LSC completion is already stacked on
RNARES, AXRNA, SJ and SJMEM; those commits must not be cherry-picked a second
time. The existing PRs #515–#523 were still open and unmerged at integration.
No new PR is required by this local workflow; upstream publication remains
subject to the repository's actual branch permissions.

## Integration changes

Overlapping symbol metadata and language-policy edits retain each unit's
completed boundaries. Shared MSL declarations are combined without dropping
prototypes. Adapter's recovered `CriErrFunc` signature is propagated through
AXRNA's forwarding setter and shared header. This removes the incompatible
`void*` callback contract. The entire AXRNA object remains exact.

A stricter symbol audit found ten SVM private rodata objects marked global in
the reconstructed target metadata while the compiler emits them as local.
Their `scope:local` declarations now agree. An all-native-object reference
scan checks that no relocation from another object reaches SVM's rodata,
including references formed through a different symbol plus an addend. This
corrects reconstruction metadata only: no addresses, bytes, symbol sizes,
section boundaries or compiler flags change. Historical symbol binding is
not independently recoverable from the stripped GameCube executable.

These are existing reviewed CRI vendor C boundaries. Their language evidence
and C++ compilation exceptions remain in `language-audit.md` and the checked
policy; no new game-owned C source or new exception is introduced. New game
reconstruction continues to default to C++.

## Verification

G9SE8P is the sole supported release target. PAL and Japanese builds are not
configured, and PS2 inputs are evidence only. Every configured source object
was deleted and recompiled with the documented release configuration. All
linked ELF/PLF intermediates and all eighteen checked DOL/REL outputs were
removed before the fresh build. Build scratch used `/tmp`, with two jobs.

The integrated source passes:

- All-source compilation, full release link, progress and objdiff report.
- All 54 language/postprocessor checker tests, language policy, and all 52
  remaining configured postprocessor policy checks.
- All 18 SHA-1 checks in `config/G9SE8P/build.sha1`.
- 162/162 functions and every owned data section at 100% in objdiff.
- Independent ELF comparison of allocated section bytes, sizes, types, flags
  and alignments; complete meaningful function/object symbol inventory,
  offsets, sizes, bindings and visibility; all 614 normalized relocations;
  and undefined imports. No extra emitted function or data atom is accepted.
- Formatting and whitespace checks, with repository commit hooks enabled.

| Unit | Functions | Relocations | Text bytes |
| --- | ---: | ---: | ---: |
| `game/cri/svm` | 27 | 117 | 4460 |
| `game/cri/rnares` | 6 | 18 | 1072 |
| `game/cri/axrna` | 19 | 166 | 6096 |
| `game/cri/sj` | 3 | 7 | 664 |
| `game/cri/sjrbf` | 17 | 60 | 2436 |
| `game/cri/sjuni` | 2 | 12 | 156 |
| `game/cri/sjmem` | 13 | 43 | 1556 |
| `game/cri/lsc_err` | 4 | 13 | 308 |
| `game/cri/lsc` | 19 | 99 | 3228 |
| `game/cri/lsc_ini` | 2 | 24 | 284 |
| `game/cri/lsc_svr` | 1 | 14 | 584 |
| `game/cri/adapter` | 8 | 9 | 220 |
| `movieD/cri/sfxahn` | 12 | 20 | 548 |
| `movieD/cri/sfxset` | 29 | 12 | 784 |

The ELF comparison excludes only DTK's hidden alignment-gap labels after
checking their zero bytes and lack of incoming references. Their bytes remain
in the whole-section comparison. The target ELF's reconstructed metadata is
not independent evidence of original source boundaries or symbol binding.
All fourteen units link from compiled source, with no instruction postprocessor
on these units. Other incomplete project units still use original fallbacks.
Existing compiler warnings elsewhere in the project remain; a successful build
does not mean a warning-free tree. No runtime or physical-hardware validation
is claimed.

Reproduce the repository gates after configuring tool paths:

```sh
TMPDIR=/tmp python -m unittest tools.test_check_language_policy tools.test_check_post_processors
TMPDIR=/tmp python tools/check_language_policy.py
TMPDIR=/tmp python tools/check_post_processors.py
TMPDIR=/tmp ninja -j2 all_source progress build/G9SE8P/report.json
build/tools/dtk shasum -c config/G9SE8P/build.sha1
```

The integration's independent object verifier, machine-readable summaries,
reference audit and concise build/test/hash logs are retained locally under
`~/.local/state/heroesdecomp/20260925-cri-integration/`. They contain verification
metadata, not extracted code or game binaries. No original/build artifact is
committed.
