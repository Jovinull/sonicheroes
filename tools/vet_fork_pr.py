#!/usr/bin/env python3
"""Decide whether a fork pull request may be built in the private container.

The private build runs with the original game files present, and its inputs include Python
(`configure.py`, `tools/`) and C/C++ sources compiled by the original toolchain. A fork pull request
is untrusted, so the maintainer-triggered workflow (`.github/workflows/fork-pr-build.yml`) only
builds one when this vetting passes. This script is run FROM THE TRUSTED CHECKOUT (the base branch),
never from the pull request.

    python3 tools/vet_fork_pr.py --base origin/main --head <40-hex SHA>

Exit 0: every changed path is on the allowlist and every added line passes the content rules.
Exit 1: something needs a human integration instead; the reasons are printed, one per line.

What is allowed (anything else is refused, not "looked at"):
  * `src/**` C/C++ sources and `include/**` headers (`.c .cpp .h .hpp`), regular files only
  * `config/G9SE8P/splits.txt`, `config/G9SE8P/<module>/splits.txt` and the matching `symbols.txt`
  * `docs/**/*.md`
  * `configure.py`, but ONLY by adding single-line `Object(Matching|NonMatching, "<lib>/<file>.c|cpp"
    [, extra_cflags=[...]])` entries: no removed line, no other added line, restricted flag characters
  Refused outright: `.github/`, `tools/`, `.githooks/`, `.agents/`, instruction files, workflows,
  `config.yml`, `build.sha1`, `language_policy.json`, assembly (`.s .S .inc`), binaries, symlinks,
  submodules, executable bits, renames, path tricks (`..`, absolute, backslash, odd characters).
  Added source lines may not `#include` an absolute/parent/`orig`/`build` path or use `incbin`/
  `#import`/`#include_next`, which would be ways to read game files into compiler output.

This reduces, it does not remove, the risk of running a stranger's code next to the game files:
the maintainer who approves the `private-build` environment is still the last gate and is expected
to read the diff summary the workflow prints. Standard library only.
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys

SRC_EXT = r"(?:c|cpp|h|hpp)"
ALLOWED = [
    re.compile(rf"^src/[A-Za-z0-9_+./-]+\.{SRC_EXT}$"),
    re.compile(rf"^include/[A-Za-z0-9_+./-]+\.{SRC_EXT}$"),
    re.compile(r"^config/G9SE8P/(?:[A-Za-z0-9_]+/)?(?:splits|symbols)\.txt$"),
    re.compile(r"^docs/[A-Za-z0-9_+./-]+\.md$"),
]
CONFIGURE = "configure.py"
SOURCE_FILE = re.compile(rf"^(?:src|include)/.*\.{SRC_EXT}$")

OBJECT_LINE = re.compile(
    r'^\s*Object\((?:Matching|NonMatching),\s*"[A-Za-z0-9_+./-]+\.(?:c|cpp)"'
    r'(?:,\s*extra_cflags=\[(?:"[-A-Za-z0-9_ ,=.]+"(?:,\s*)?)*\])?\),?\s*$'
)
BAD_FLAG = re.compile(r'(?:^|[\s"])-(?:o|c|M\w*|i\s*\.\.|I\s*\.\.)(?:[\s"=]|$)')
BAD_SOURCE_LINE = [
    (re.compile(r"#\s*(?:include_next|import|embed)\b"), "include_next/import/embed"),
    (re.compile(r'#\s*include\s*[<"]\s*(?:/|\\|\.\./|\.\.\\|[A-Za-z]:|[^">]*\borig\b|[^">]*\bbuild/)'),
     "#include of an absolute, parent, orig or build path"),
    (re.compile(r"\bincbin\b", re.I), "incbin"),
]


def git(*args: str) -> str:
    r = subprocess.run(["git", *args], capture_output=True, text=True)
    if r.returncode:
        sys.exit(f"git {' '.join(args)} failed: {r.stderr.strip()}")
    return r.stdout


def vet(base: str, head: str) -> tuple[list[str], list[str]]:
    """-> (violations, summary lines)."""
    bad: list[str] = []
    mb = git("merge-base", base, head).strip()
    raw = git("diff", "--raw", "-z", "--no-renames", "--no-abbrev", mb, head)
    fields = raw.split("\0")
    entries = []
    i = 0
    while i + 1 < len(fields) and fields[i].startswith(":"):
        meta = fields[i][1:].split()
        entries.append((meta[0], meta[1], meta[4][0], fields[i + 1]))  # old mode, new mode, status, path
        i += 2
    if not entries:
        bad.append("the pull request changes nothing")
    for old_mode, new_mode, status, path in entries:
        if status not in "AMD":
            bad.append(f"{path}: change type {status!r} (renames/copies/type changes need a human)")
            continue
        if new_mode not in ("100644", "000000") or old_mode not in ("100644", "000000"):
            bad.append(f"{path}: mode {old_mode}->{new_mode} (symlink, submodule or executable bit)")
            continue
        if any(part in ("", ".", "..", ".git") for part in path.split("/")) or path.startswith("/") or "\\" in path:
            bad.append(f"{path}: suspicious path")
            continue
        if path == CONFIGURE:
            if status != "M":
                bad.append(f"{path}: must be a modification")
            continue
        if not any(rx.match(path) for rx in ALLOWED):
            bad.append(f"{path}: not on the fork-build allowlist")
    numstat = git("diff", "--numstat", "--no-renames", mb, head)
    for line in numstat.splitlines():
        a, d, p = line.split("\t", 2)
        if a == "-" and d == "-":
            bad.append(f"{p}: binary change")
    # content rules, from the added/removed lines only
    patch = git("diff", "-U0", "--no-renames", "--no-color", mb, head)
    cur = None
    for line in patch.splitlines():
        if line.startswith("+++ "):
            cur = line[6:] if line.startswith("+++ b/") else None
            continue
        if line.startswith("--- ") or line.startswith("@@") or line.startswith("diff ") or not line:
            continue
        sign, text = line[0], line[1:]
        if cur == CONFIGURE:
            if sign == "-":
                bad.append(f"{CONFIGURE}: removes or edits an existing line: {text.strip()[:80]!r}")
            elif sign == "+":
                if not OBJECT_LINE.match(text) or BAD_FLAG.search(text):
                    bad.append(f"{CONFIGURE}: added line is not a plain Object(...) entry: {text.strip()[:100]!r}")
        elif cur and SOURCE_FILE.match(cur) and sign == "+":
            for rx, why in BAD_SOURCE_LINE:
                if rx.search(text):
                    bad.append(f"{cur}: {why}: {text.strip()[:100]!r}")
    summary = [f"{n} {status} {path}" for n, (_, _, status, path) in enumerate(entries, 1)]
    stat = git("diff", "--shortstat", "--no-renames", mb, head).strip()
    summary.append(stat)
    return bad, summary


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--base", required=True, help="trusted base ref, e.g. origin/main")
    ap.add_argument("--head", required=True, help="the exact pull request head commit")
    a = ap.parse_args()
    if not re.fullmatch(r"[0-9a-f]{40}", a.head):
        sys.exit("--head must be a full 40-hex commit SHA (pin the exact reviewed commit)")
    bad, summary = vet(a.base, a.head)
    print("changes:")
    for s in summary:
        print("  " + s)
    if bad:
        print("\nREFUSED, needs a manual integration branch:")
        for b in bad:
            print("  - " + b)
        return 1
    print("\nvetting passed: only allowlisted paths and plain Object(...) additions")
    return 0


if __name__ == "__main__":
    sys.exit(main())
