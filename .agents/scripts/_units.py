"""Shared helpers: repository root, objdiff.json unit lookup, tool paths."""

from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BUILD = ROOT / "build"
OBJDIFF = BUILD / "tools" / ("objdiff-cli.exe" if sys.platform == "win32" else "objdiff-cli")


def units() -> list[dict]:
    path = ROOT / "objdiff.json"
    if not path.exists():
        sys.exit("objdiff.json missing: run `python configure.py` and `ninja` first")
    return json.loads(path.read_text(encoding="utf-8"))["units"]


def resolve(query: str, need_base: bool = True) -> dict:
    """Exact unit name, else a unique substring match (e.g. `e_flyer_path`)."""
    all_units = [u for u in units() if not need_base or u.get("base_path")]
    for u in all_units:
        if u["name"] == query:
            return u
    hits = [u for u in all_units if query in u["name"]]
    exact_tail = [u for u in hits if u["name"].split("/")[-1] == query.split("/")[-1]]
    if len(exact_tail) == 1:
        return exact_tail[0]
    if len(hits) == 1:
        return hits[0]
    if not hits:
        sys.exit(f"no unit matches {query!r}")
    sys.exit(f"{query!r} is ambiguous:\n  " + "\n  ".join(u["name"] for u in hits[:30]))


def _norm(p: str) -> str:
    return p.replace("\\", "/")


def post_steps(base_path: str) -> list[str]:
    """Post-compile stamps (tools/fix_*.py) that edit this object in place.

    Building only the .o target recompiles it and silently discards those edits,
    so the object you diff is not the one that gets linked. Always build the
    stamps too.
    """
    text = (ROOT / "build.ninja").read_text(encoding="utf-8").replace("$\n", " ")
    want = _norm(base_path)
    steps = []
    for line in text.splitlines():
        if not line.startswith("build "):
            continue
        head, _, rest = line[6:].partition(":")
        parts = rest.split()
        if not parts or not parts[0].startswith("fix_"):
            continue
        explicit = []
        for tok in parts[1:]:
            if tok in ("|", "||"):
                break
            explicit.append(_norm(tok))
        if want in explicit:
            steps.append(head.strip())
    return steps


def build_base(unit: dict) -> None:
    """Recompile our object for the unit, then rerun its post-processors."""
    target = unit["base_path"]
    targets = [target] + post_steps(target)
    if sys.platform == "win32":
        targets = [t.replace("/", "\\") for t in targets]
    r = subprocess.run(["ninja", *targets], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        sys.stdout.write(r.stdout[-4000:])
        sys.stderr.write(r.stderr[-4000:])
        sys.exit(f"build of {target} failed")
