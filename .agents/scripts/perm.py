"""perm: try every ORDER of the leading bare local declarations of one function and rank
them by word diffs against the retail function (uses try1.score).

Why it works: MWCC gives the
saved registers (r31, r30, ...) and the stack slots in declaration order, so a register-only diff
is very often a permutation of `T a; T b; T c;`. The notes: "cheap and effective" (fn_80203144:
120 permutations -> 2 diffs).

usage: python3 .agents/scripts/perm.py SRC FUNC [--flags default|exc|ns|fpoff|"<raw>"] [--retail-obj PATH]
                                   [--max 6] [--jobs 8] [--write]

Only a leading run of BARE declarations (`int i;`, `u8* p;` -- no initializer) is permuted; convert
`T x = expr;` into `T x; ... x = expr;` first (the notes: "ALWAYS convert temps into bare decls +
assignment when perm.py is needed"). --max caps the run length (N! compiles; 6 -> 720).
--write rewrites SRC with the best order when it beats the current one. Prints the top 5.
"""

from __future__ import annotations

import argparse
import itertools
import os
import re
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import try1  # noqa: E402

DECL = re.compile(r"^\s*(?:(?:unsigned|signed|const|volatile|struct)\s+)*[A-Za-z_]\w*(?:\s*\*+\s*|\s+)[A-Za-z_]\w*(?:\[[^\]]*\])?\s*;\s*$")


def find_body(text: str, func: str):
    """-> (line index of first body line, list of lines). Finds `func(` followed by `{` on its own line."""
    lines = text.splitlines()
    for i, l in enumerate(lines):
        if re.search(r"\b" + re.escape(func) + r"\s*\(", l) and not l.rstrip().endswith(";"):
            j = i
            while j < len(lines) and "{" not in lines[j]:
                j += 1
            if j < len(lines):
                return j + 1, lines
    sys.exit(f"function {func!r} not found in the source")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("func")
    ap.add_argument("--flags", default="default")
    ap.add_argument("--retail-obj")
    ap.add_argument("--max", type=int, default=6)
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--write", action="store_true")
    a = ap.parse_args()

    src = Path(a.src)
    text = src.read_text(encoding="utf-8")
    start, lines = find_body(text, a.func)
    end = start
    while end < len(lines) and DECL.match(lines[end]):
        end += 1
    decls = lines[start:end]
    if len(decls) < 2:
        sys.exit("need at least 2 leading bare declarations to permute "
                 f"(found {len(decls)}); convert `T x = e;` into `T x;` + assignment first")
    if len(decls) > a.max:
        sys.exit(f"{len(decls)} declarations -> {len(decls)}! compiles; raise --max if you mean it")

    nl = "\r\n" if "\r\n" in text else "\n"
    tmpdir = Path(tempfile.mkdtemp(prefix="perm_"))

    def build(order) -> Path:
        body = lines[:start] + [decls[k] for k in order] + lines[end:]
        p = tmpdir / ("p_" + "".join(map(str, order)) + src.suffix)
        p.write_text(nl.join(body) + nl, encoding="utf-8")
        return p

    orders = list(itertools.permutations(range(len(decls))))
    print(f"{len(decls)} declarations, {len(orders)} permutations, flags={a.flags}")
    with ThreadPoolExecutor(max_workers=a.jobs) as ex:
        scores = list(ex.map(lambda o: (try1.score(build(o), a.func, a.flags, a.retail_obj), o), orders))
    scores.sort()
    ident = tuple(range(len(decls)))
    cur = next(s for s, o in scores if o == ident)
    for s, o in scores[:5]:
        print(f"  {s:3} diffs  order {o}{'   <- current' if o == ident else ''}")
        for k in o:
            print("        " + decls[k].strip())
    best, bo = scores[0]
    print(f"current: {cur} diffs; best: {best} diffs")
    if a.write and best < cur:
        body = lines[:start] + [decls[k] for k in bo] + lines[end:]
        src.write_text(nl.join(body) + nl, encoding="utf-8")
        print(f"wrote best order to {src}")
    for f in tmpdir.iterdir():
        f.unlink()
    tmpdir.rmdir()
    return 0 if best == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
