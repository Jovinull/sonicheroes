"""Local queries against the PS2 retail symbol table (SLUS_207.18, NTSC-U 1.00).

The PS2 ELF keeps a full Metrowerks .symtab (~49.7k symbols, ~21k functions, ~9k C++-mangled names,
one section per overlay). This is cross-platform EVIDENCE for names/classes/boundaries only: it never
proves a GameCube match, and everything it prints stays LOCAL (LEGAL.md, docs/language-policy.md):
no listings, dumps or addresses in the repository, pull requests or chat. Record only the minimum
symbolic fact in the evidence template of docs/language-policy.md.

Needs your own legally obtained copy at orig/ps2/SLUS_207.18 (gitignored). Standard library only.

usage (from the repository root):
  python3 .agents/scripts/ps2sym.py stats
  python3 .agents/scripts/ps2sym.py find REGEX [--section S] [--type func|object] [--demangle]
  python3 .agents/scripts/ps2sym.py class TObjFoo [--demangle]   # members Foo__<len>TObjFoo...
  python3 .agents/scripts/ps2sym.py around NAME [-n 12]          # same-section neighbours (source order)
  python3 .agents/scripts/ps2sym.py section STAGE11.BIN [--type func]
  python3 .agents/scripts/ps2sym.py files [--section S]          # .p__sinit_<file>.cpp unit markers
  python3 .agents/scripts/ps2sym.py missing [--top 30]           # PS2 C++ names the GameCube symbols lack
  python3 .agents/scripts/ps2sym.py export [--demangle]          # local JSONL index in build/ps2/

--demangle uses ccc's `demangle` ($CCC_DEMANGLE, else ~/tools/ccc/**/demangle). Modern c++filt cannot
read CodeWarrior (GNU v2) names.

Overlay map (PS2 section -> GameCube module): STAGEnn.BIN -> stagennD.rel, ADV.BIN -> advertiseD,
ASAVE.BIN -> autosaveD, MOVIE.BIN -> movieD, STAGE.BIN -> code shared by all stages (lives inside the
stage modules on GameCube), STAGE00.BIN -> stage00D (not in the GameCube build), main -> main.dol.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import elfmini  # noqa: E402
ROOT = Path(__file__).resolve().parents[2]

ELF = ROOT / "orig" / "ps2" / "SLUS_207.18"
def _find_demangle() -> str:
    """ccc's demangler: $CCC_DEMANGLE, else ~/tools/ccc/**/demangle, else PATH."""
    env = os.environ.get("CCC_DEMANGLE")
    if env:
        return env
    home = os.path.expanduser("~/tools/ccc/v2.1")
    for root, _dirs, files in os.walk(home):
        if "demangle" in files:
            return os.path.join(root, "demangle")
    import shutil
    return shutil.which("demangle") or "demangle"


DEMANGLE = _find_demangle()


def load():
    if not ELF.exists():
        sys.exit(f"{ELF} missing (extract SLUS_207.18 from your own PS2 disc into orig/ps2/)")
    e = elfmini.load(str(ELF))
    secname = {s.index: s.name for s in e.sections}
    syms = [s for s in e.symbols if s.name and s.type in ("func", "object", "notype") and s.shndx]
    for s in syms:
        # The 804 .p__sinit_* markers carry fixed-width padding plus leftover
        # buffer bytes after the real name; the first token is the name.
        if "  " in s.name:
            s.name = s.name.split()[0]
    return e, secname, syms


def demangle(names: list[str]) -> dict[str, str]:
    """ccc's demangle.exe takes one symbol per run, so fan out over threads."""
    if not os.path.exists(DEMANGLE):
        return {}
    from concurrent.futures import ThreadPoolExecutor

    def one(n: str):
        try:
            r = subprocess.run([DEMANGLE, n], capture_output=True, text=True, timeout=10)
            return n, r.stdout.strip()
        except (OSError, subprocess.TimeoutExpired):
            return n, ""

    with ThreadPoolExecutor(max_workers=16) as ex:
        return {n: d for n, d in ex.map(one, names) if d and d != n}


def show(rows, secname, dem: bool):
    names = {s.name: None for s in rows}
    dm = demangle(list(names)) if dem else {}
    for s in rows:
        extra = f"   {dm[s.name]}" if s.name in dm else ""
        print(f"{secname.get(s.shndx, s.shndx):12} {s.value:08x} {s.size:6x} {s.type:6} {s.bind:6} {s.name}{extra}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("cmd", choices=["find", "around", "section", "files", "class", "stats", "missing", "export"])
    ap.add_argument("arg", nargs="?")
    ap.add_argument("--section")
    ap.add_argument("--type")
    ap.add_argument("-n", type=int, default=12)
    ap.add_argument("--demangle", action="store_true")
    ap.add_argument("--top", type=int, default=30)
    a = ap.parse_args()
    e, secname, syms = load()

    def keep(s):
        if a.section and secname.get(s.shndx) != a.section:
            return False
        if a.type and s.type != a.type:
            return False
        return True

    if a.cmd == "missing":
        gc = set()
        for f in (ROOT / "config" / "G9SE8P").rglob("symbols.txt"):
            for line in f.read_text(encoding="utf-8", errors="replace").splitlines():
                if " = " in line:
                    gc.add(line.split(" = ", 1)[0].strip())
        mangled = re.compile(r"^(?P<fn>[~A-Za-z_][\w$]*?)__(?P<len>\d+)(?P<cls>[A-Za-z_]\w*)F")
        funcs = {s.name for s in syms if s.type == "func"}
        cpp = [n for n in funcs if mangled.match(n)]
        have = [n for n in cpp if n in gc]
        miss = [n for n in cpp if n not in gc]
        print(f"PS2 function symbols: {len(funcs)}; C++-mangled methods: {len(cpp)}")
        print(f"  already present in GameCube symbols.txt: {len(have)}")
        print(f"  NOT in GameCube symbols.txt: {len(miss)}  (candidate names; each still needs an independent GameCube correlation)")
        import collections
        by_class = collections.Counter()
        for n in miss:
            m = mangled.match(n)
            ln = int(m.group("len"))
            by_class[(m.group("len") + m.group("cls"))[len(m.group("len")):][:ln]] += 1
        print(f"  classes with the most missing methods (top {a.top}):")
        for cls, n in by_class.most_common(a.top):
            print(f"    {n:4} {cls}")
        return
    if a.cmd == "export":
        out = ROOT / "build" / "ps2" / "symbols.jsonl"
        out.parent.mkdir(parents=True, exist_ok=True)
        names = [s.name for s in syms if s.type == "func" and "__" in s.name]
        dm = demangle(names) if a.demangle else {}
        with out.open("w", encoding="utf-8") as fh:
            for s in sorted(syms, key=lambda s: (s.shndx, s.value)):
                rec = {"name": s.name, "section": secname.get(s.shndx), "addr": s.value, "size": s.size,
                       "type": s.type, "bind": s.bind}
                if s.name in dm:
                    rec["demangled"] = dm[s.name]
                fh.write(json.dumps(rec) + "\n")
        print(f"wrote {len(syms)} symbols to {out.relative_to(ROOT)} (local only: build/ is gitignored and hook-blocked)")
        return
    if a.cmd == "stats":
        import collections
        c = collections.Counter((secname.get(s.shndx), s.type) for s in syms)
        for sec in sorted({k[0] for k in c}, key=str):
            print(f"{sec:14} func {c[(sec, 'func')]:6}  object {c[(sec, 'object')]:6}")
        return
    if a.cmd == "find":
        rx = re.compile(a.arg)
        show(sorted([s for s in syms if rx.search(s.name) and keep(s)], key=lambda s: (s.shndx, s.value)),
             secname, a.demangle)
        return
    if a.cmd == "class":
        # members are <name>__<len><Class>[F<args>]; vtable is __vt__<len><Class>
        tag = f"{len(a.arg)}{a.arg}"
        rx = re.compile(rf"__{re.escape(tag)}(F|$)|^__vt__{re.escape(tag)}$")
        hits = [s for s in syms if rx.search(s.name) and keep(s)]
        show(sorted(hits, key=lambda s: (s.shndx, s.value)), secname, a.demangle)
        return
    if a.cmd == "section":
        show(sorted([s for s in syms if secname.get(s.shndx) == a.arg and keep(s)], key=lambda s: s.value),
             secname, a.demangle)
        return
    if a.cmd == "files":
        marks = [s for s in syms if s.name.startswith(".p__sinit_") and keep(s)]
        seen = set()
        for s in sorted(marks, key=lambda s: (s.shndx, s.value)):
            key = (s.shndx, s.name)
            if key in seen:
                continue
            seen.add(key)
            print(f"{secname.get(s.shndx):12} {s.value:08x} {s.name[len('.p__sinit_'):]}")
        return
    if a.cmd == "around":
        target = next((s for s in syms if s.name == a.arg), None)
        if target is None:
            sys.exit(f"{a.arg} not found")
        same = sorted([s for s in syms if s.shndx == target.shndx and (not a.type or s.type == a.type)],
                      key=lambda s: s.value)
        i = same.index(target)
        show(same[max(0, i - a.n) : i + a.n + 1], secname, a.demangle)


if __name__ == "__main__":
    try:
        main()
    except (BrokenPipeError, OSError):
        pass
