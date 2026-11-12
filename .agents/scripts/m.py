"""Level 1 of match verification: objdiff, per function.

usage:
  python3 .agents/scripts/m.py UNIT              # functions below 100%, plus sections
  python3 .agents/scripts/m.py UNIT --all        # every function
  python3 .agents/scripts/m.py UNIT SYMBOL       # side-by-side rows for one function
  python3 .agents/scripts/m.py UNIT SYMBOL --diff  # only the rows that differ (+context)

UNIT is an objdiff unit name or a unique substring (`e_flyer_path`,
`stage11D/rel/e_flyer_path_stage11`). Our object is rebuilt with ninja first
unless --no-build is given.

The percentage printed here is objdiff-cli `diff`'s, which uses its default
relocation diffing. `report generate` (what CI and the badges use) is more
lenient and can read higher on the same function: always say which one a
number came from. Column meaning:
  holes  = DIFF_INSERT + DIFF_DELETE rows  -> shape problem; fix this first
  ops    = DIFF_REPLACE + DIFF_OP_MISMATCH -> different instruction
  args   = DIFF_ARG_MISMATCH                -> registers / offsets / reloc names
"""

from __future__ import annotations

import argparse
import collections
import json
import os
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from _units import OBJDIFF, ROOT, build_base, resolve  # noqa: E402


def run_diff(unit: dict, config: list[str]) -> dict:
    fd, out = tempfile.mkstemp(suffix=".json")
    os.close(fd)
    cmd = [str(OBJDIFF), "--no-color", "-L", "error", "diff", "-p", str(ROOT), "-u", unit["name"],
           "-o", out, "--format", "json"]
    for c in config:
        cmd += ["-c", c]
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit(r.stderr or r.stdout)
    with open(out, encoding="utf-8") as f:
        data = json.load(f)
    os.unlink(out)
    return data


def kinds(rows: list[dict]) -> collections.Counter:
    c = collections.Counter()
    for r in rows:
        c[r.get("diff_kind", "NONE")] += 1
    return c


def fmt(row: dict) -> str:
    ins = row.get("instruction")
    return ins.get("formatted", "") if ins else ""


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("unit")
    ap.add_argument("symbol", nargs="?")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--diff", action="store_true", help="with SYMBOL: only differing rows")
    ap.add_argument("--no-build", action="store_true")
    ap.add_argument("-c", "--config", action="append", default=[], help="objdiff key=value")
    a = ap.parse_args()

    unit = resolve(a.unit)
    if not a.no_build:
        build_base(unit)
    d = run_diff(unit, a.config)
    left = d.get("left") or {}
    right = d.get("right") or {}
    rsyms = {s["name"]: s for s in right.get("symbols", [])}

    if a.symbol:
        ls = next((s for s in left.get("symbols", []) if s["name"] == a.symbol), None)
        rs = rsyms.get(a.symbol)
        if ls is None:
            sys.exit(f"{a.symbol} not in the target object")
        if rs is None:
            sys.exit(f"{a.symbol} not in our object (name it the same as retail)")
        lrows, rrows = ls.get("instructions", []), rs.get("instructions", [])
        print(f"{unit['name']} :: {a.symbol}  match {ls.get('match_percent', 0):.2f}%  "
              f"size retail {ls['size']} ours {rs['size']}")
        diff_idx = {i for i, r in enumerate(lrows) if r.get("diff_kind")}
        show = set(range(len(lrows)))
        if a.diff:
            show = {j for i in diff_idx for j in range(i - 2, i + 3)}
        last = -2
        for i, (lr, rr) in enumerate(zip(lrows, rrows)):
            if i not in show:
                continue
            if a.diff and i != last + 1:
                print("   ...")
            last = i
            k = lr.get("diff_kind", "")
            mark = {"": " ", "DIFF_ARG_MISMATCH": "~", "DIFF_INSERT": ">", "DIFF_DELETE": "<",
                    "DIFF_REPLACE": "|", "DIFF_OP_MISMATCH": "|"}.get(k, "?")
            print(f"{i:4} {mark} {fmt(lr):42.42} {fmt(rr)}")
        c = kinds(lrows)
        print(f"holes {c['DIFF_INSERT'] + c['DIFF_DELETE']}  ops {c['DIFF_REPLACE'] + c['DIFF_OP_MISMATCH']}"
              f"  args {c['DIFF_ARG_MISMATCH']}  rows {len(lrows)}")
        return

    print(unit["name"])
    print(f"  target {unit.get('target_path')}\n  ours   {unit.get('base_path')}")
    for s in left.get("sections", []):
        if s.get("kind") not in ("SECTION_CODE", "SECTION_DATA", "SECTION_BSS"):
            continue
        rs = next((x for x in right.get("sections", []) if x["name"] == s["name"]), None)
        mp = s.get("match_percent")
        print(f"  {s['name']:10} retail {s['size']:>6} ours {rs['size'] if rs else '-':>6}  "
              f"{'' if mp is None else f'{mp:.2f}%'}")
    funcs = [s for s in left.get("symbols", []) if s.get("instructions") is not None]
    total = len(funcs)
    done = sum(1 for s in funcs if s.get("match_percent", 0) >= 100.0)
    print(f"  functions: {done}/{total} at 100%")
    print(f"  {'symbol':40} {'retail':>6} {'ours':>6} {'match':>7} {'holes':>5} {'ops':>4} {'args':>4}")
    for s in funcs:
        mp = s.get("match_percent", 0.0)
        if mp >= 100.0 and not a.all:
            continue
        rs = rsyms.get(s["name"])
        c = kinds(s.get("instructions", []))
        print(f"  {s['name']:40.40} {s['size']:>6} {rs['size'] if rs else 'MISS':>6} {mp:7.2f} "
              f"{c['DIFF_INSERT'] + c['DIFF_DELETE']:5} {c['DIFF_REPLACE'] + c['DIFF_OP_MISMATCH']:4} "
              f"{c['DIFF_ARG_MISMATCH']:4}")
    extra = [n for n in rsyms if n not in {s["name"] for s in left.get("symbols", [])}
             and rsyms[n].get("instructions") is not None]
    if extra:
        print(f"  only in ours: {', '.join(extra[:20])}{' ...' if len(extra) > 20 else ''}")


if __name__ == "__main__":
    main()
