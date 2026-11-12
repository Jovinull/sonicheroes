"""extabnew: after building a unit, compare the RETAIL exception/ctor section sizes (the blocks dtk
wrote into config/G9SE8P/splits.txt) with the sizes in OUR compiled object.

Why it matters: a per-function comparison only checks .text. A unit whose every function is
EXACT can still make the DOL hash FAIL because
  * retail has extab but we compiled without -Cpp_exceptions  (or the opposite), or
  * retail extab is 24 bytes (a real `new T(...)` expression: Malloc + ctor guarded by delete-on-throw)
    while a plain `p = Malloc(); if (p) ctor(p);` gives only 8, or
  * the function is in .ctors (static initializer) and the unit has no .ctors entry.

usage: python3 .agents/scripts/extabnew.py UNIT [UNIT ...]       e.g. game/fn_8011927C.cpp  or  fn_8011927C
       python3 .agents/scripts/extabnew.py --module stage11D rel/x.cpp
Run it AFTER `ninja <obj>` / `ninja`, and READ the output for `<-- DIFF` (a count of 0 before
building means nothing). Rule of thumb: retail extab 8 -> flags `ns`
(-Cpp_exceptions on -opt noschedule,nopeephole); no retail extab -> default flags, even when the
function has calls.
"""

from __future__ import annotations

import os
import re
import sys
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import elfmini  # noqa: E402
ROOT = Path(__file__).resolve().parents[2]

SECTIONS = ("extab", "extabindex", ".ctors", ".dtors")


def retail_sizes(splits: Path, unit: str) -> dict[str, int] | None:
    text = splits.read_text(encoding="utf-8")
    m = re.search(r"(?m)^" + re.escape(unit) + r":[^\n]*\n((?:[ \t]+[^\n]*\n)+)", text)
    if not m:
        return None
    out = {}
    for line in m.group(1).splitlines():
        mm = re.match(r"\s+(\S+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)", line)
        if mm and mm.group(1) in SECTIONS:
            out[mm.group(1)] = int(mm.group(3), 16) - int(mm.group(2), 16)
    return out


def our_sizes(obj: Path) -> dict[str, int]:
    e = elfmini.load(str(obj))
    return {s: (e.section(s).size if e.section(s) else 0) for s in SECTIONS}


def main() -> int:
    a = sys.argv[1:]
    module = None
    if a[:1] == ["--module"]:
        module, a = a[1], a[2:]
    if not a:
        sys.exit(__doc__)
    bad = 0
    for q in a:
        unit = q if "/" in q else f"game/{q}"
        if not unit.endswith((".cpp", ".c")):
            unit += ".cpp"
        splits = ROOT / "config/G9SE8P" / (f"{module}/splits.txt" if module else "splits.txt")
        obj = ROOT / "build/G9SE8P" / ("src/" + unit).replace(".cpp", ".o").replace(".c", ".o")
        r = retail_sizes(splits, unit)
        if r is None:
            print(f"{unit}: no block in {splits.relative_to(ROOT)} (not placed yet?)")
            bad += 1
            continue
        if not obj.exists():
            print(f"{unit}: {obj.relative_to(ROOT)} missing: build it first")
            bad += 1
            continue
        o = our_sizes(obj)
        flags = []
        for s in SECTIONS:
            rs, os_ = r.get(s, 0), o[s]
            if rs or os_:
                flag = "" if rs == os_ else "   <-- DIFF"
                bad += bool(flag)
                flags.append(f"{s} retail {rs} ours {os_}{flag}")
        print(f"{unit}: " + ("; ".join(flags) if flags else "no extab/.ctors on either side"))
        if r.get("extab", 0) and not o["extab"]:
            print("   hint: retail has extab -> compile with -Cpp_exceptions on (preset `ns`)")
        if not r.get("extab", 0) and o["extab"]:
            print("   hint: retail has NO extab -> use default flags (no -Cpp_exceptions)")
        if r.get("extab", 0) == 24 and o["extab"] == 8:
            print("   hint: retail extab 24 = real `new T(...)` expression; a plain Malloc+if(p) ctor gives 8")
    return 1 if bad else 0


if __name__ == "__main__":
    raise SystemExit(main())
