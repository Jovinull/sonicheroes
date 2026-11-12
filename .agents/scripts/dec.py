"""Run m2c on a retail function straight from dtk's assembly.

usage:
  python3 .agents/scripts/dec.py UNIT FUNC [FUNC...]      # plain m2c output
  python3 .agents/scripts/dec.py UNIT FUNC --ctx           # with decompctx context of the unit's source
  python3 .agents/scripts/dec.py UNIT --list               # functions in the unit's .s

UNIT resolves like m.py. The .s lives at build/G9SE8P/<module>/asm/<path>.s
(DOL units: build/G9SE8P/asm/<path>.s). Output goes to stdout only: m2c output
is a starting point, never something to commit as-is (and the .s itself is
extracted retail code: never copy it into src/).

--ctx feeds m2c the flattened headers of the unit's source. m2c's parser is C
only (pycparser), so C++ sources usually fail to parse; then run without it.
Target defaults to ppc-mwcc-c; `-t ppc-mwcc-c++` changes the output style.
"""

from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from _units import ROOT, resolve  # noqa: E402

# m2c (https://github.com/matt-kempster/m2c) is not part of this repository: set M2C to its m2c.py
# (default ~/tools/m2c/m2c.py) and, if it needs a virtualenv, M2C_PYTHON (default ~/tools/venv/bin/python,
# else the current interpreter).
M2C = os.environ.get("M2C", os.path.expanduser("~/tools/m2c/m2c.py"))
M2C_PYTHON = os.environ.get("M2C_PYTHON", os.path.expanduser("~/tools/venv/bin/python"))


def asm_path(unit: dict) -> str:
    # target_path build/G9SE8P/<mod>/obj/<p>.o  ->  build/G9SE8P/<mod>/asm/<p>.s
    t = unit["target_path"].replace("\\", "/")
    return str(ROOT / re.sub(r"/obj/(.*)\.o$", r"/asm/\1.s", t))


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("unit")
    ap.add_argument("funcs", nargs="*")
    ap.add_argument("--ctx", action="store_true")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("-t", "--target", default="ppc-mwcc-c")
    a = ap.parse_args()
    unit = resolve(a.unit, need_base=False)
    s = asm_path(unit)
    if not os.path.exists(s):
        sys.exit(f"{s} missing: run ninja once so dtk writes the assembly")
    if a.list or not a.funcs:
        for line in open(s, encoding="utf-8"):
            m = re.match(r"\.fn (\S+), (\w+)", line)
            if m:
                print(m.group(1), m.group(2))
        return
    cmd = [M2C_PYTHON if os.path.exists(M2C_PYTHON) else sys.executable, M2C, "-t", a.target]
    ctx_file = None
    if a.ctx:
        src = (unit.get("metadata") or {}).get("source_path")
        if not src:
            sys.exit("unit has no source_path")
        fd, ctx_file = tempfile.mkstemp(suffix=".c")
        os.close(fd)
        subprocess.run([sys.executable, str(ROOT / "tools" / "decompctx.py"), str(ROOT / src), "-o", ctx_file],
                       cwd=ROOT, check=True)
        cmd += ["--context", ctx_file]
    for f in a.funcs:
        cmd += ["-f", f]
    cmd.append(s)
    r = subprocess.run(cmd, cwd=ROOT)
    if ctx_file:
        os.unlink(ctx_file)
    sys.exit(r.returncode)


if __name__ == "__main__":
    main()
