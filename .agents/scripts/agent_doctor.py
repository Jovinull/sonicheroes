#!/usr/bin/env python3
"""Read-only environment check for coding agents (Codex, Claude Code) and people.

Run it at the start of a session and before reporting a build as verified:

    python3 .agents/scripts/agent_doctor.py            # fast checks
    python3 .agents/scripts/agent_doctor.py --verify   # also check the 18 artifact hashes

It reads state and prints PASS / WARN / FAIL with the command that fixes each problem. It never
writes, downloads, builds or changes Git settings. Standard library only.

What it checks, and why each matters here:
  * Git: you are on a work branch of THIS clone (not `main`), no extra worktrees, and the
    pre-commit hook is enabled (`core.hooksPath=.githooks`; it refuses game data and unformatted code).
  * Original inputs: orig/G9SE8P holds a GameCube G9SE8P disc image or extracted sys/main.dol. A
    PlayStation 2 image there is a FAIL (the build would read it as a GameCube disc).
  * Build tree: tools, compilers, binutils, build.ninja, objdiff.json and a linked main.dol.
  * Optional local tools: ninja, clang-format, llvm-objcopy (without it 35 post-processor tests skip).
  * Nothing under orig/ or build/ is staged.
"""

from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
GAME_ID = b"G9SE8P"
results: list[tuple[str, str, str]] = []


def add(level: str, msg: str, fix: str = "") -> None:
    results.append((level, msg, fix))


def git(*args: str) -> str:
    r = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True)
    return r.stdout.strip()


def check_git() -> None:
    if not (ROOT / ".git").exists():
        add("FAIL", "not a Git clone", "")
        return
    branch = git("branch", "--show-current")
    if not branch:
        add("WARN", "detached HEAD", "git switch -c <type>/<topic>-YYYYMMDD")
    elif branch == "main":
        add("WARN", "on `main`: do code work on a branch of this clone", "git switch -c <type>/<topic>-YYYYMMDD")
    else:
        add("PASS", f"on work branch `{branch}`")
    dirty = [l for l in git("status", "--short").splitlines() if l.strip()]
    add("PASS" if not dirty else "WARN", "working tree clean" if not dirty else f"{len(dirty)} changed path(s)",
        "" if not dirty else "git status --short")
    trees = [l for l in git("worktree", "list").splitlines() if l.strip()]
    if len(trees) > 1:
        add("WARN", f"{len(trees)} worktrees: this repository works on branches in place; remove extras",
            "git worktree list  # then: git worktree remove <path>")
    hooks = git("config", "core.hooksPath")
    if hooks == ".githooks":
        add("PASS", "pre-commit hook enabled (core.hooksPath=.githooks)")
    else:
        add("FAIL", f"pre-commit hook not enabled (core.hooksPath={hooks!r})", "git config core.hooksPath .githooks")
    staged = [p for p in git("diff", "--cached", "--name-only").splitlines() if p.startswith(("orig/", "build/"))]
    if staged:
        add("FAIL", f"staged files under orig/ or build/: {staged[:3]}", "git restore --staged <file>")


def disc_kind(path: Path) -> str:
    """-> 'gc-g9se8p' | 'gc-other' | 'ps2' | 'unknown' from the file's own bytes."""
    try:
        with path.open("rb") as f:
            head = f.read(0x100)
            if head[:4] == b"RVZ\x01" or head[:4] == b"WIA\x01":
                return "gc-g9se8p" if head[0x58:0x5E] == GAME_ID else "gc-other"
            if len(head) >= 0x20 and head[0x1C:0x20] == b"\xc2\x33\x9f\x3d":
                return "gc-g9se8p" if head[:6] == GAME_ID else "gc-other"
            f.seek(0x8000)
            pvd = f.read(0x30)
            if pvd[1:6] == b"CD001" and b"PLAYSTATION" in pvd:
                return "ps2"
    except OSError:
        pass
    return "unknown"


def check_orig() -> None:
    d = ROOT / "orig" / "G9SE8P"
    dol = d / "sys" / "main.dol"
    images = [p for p in d.glob("*") if p.suffix.lower() in {".rvz", ".iso", ".gcm", ".wia", ".ciso", ".gcz", ".tgc"}]
    bad = False
    for img in images:
        kind = disc_kind(img)
        if kind == "ps2":
            add("FAIL", f"{img.name} is a PlayStation 2 image: it does not belong in orig/G9SE8P",
                "move it to orig/ps2/ and extract only SLUS_207.18 + overlays")
            bad = True
        elif kind == "gc-g9se8p":
            add("PASS", f"GameCube G9SE8P disc image: {img.name}")
        elif kind == "gc-other":
            add("FAIL", f"{img.name} is a GameCube image of another game/region (expected G9SE8P)", "")
            bad = True
        else:
            add("WARN", f"{img.name}: could not identify the image format", "")
    if dol.exists():
        add("PASS", "extracted orig/G9SE8P/sys/main.dol present")
    elif not images and not bad:
        add("FAIL", "no original input in orig/G9SE8P (disc image or extracted files)",
            "place your own G9SE8P image there; it is gitignored")
    if (ROOT / "orig" / "ps2" / "SLUS_207.18").exists():
        add("PASS", "optional PS2 executable present in orig/ps2 (local symbol evidence only; never commit)")
    else:
        add("WARN", "no PS2 executable in orig/ps2 (optional: improves name/class evidence)", "")


def check_build() -> None:
    need = {
        "build/tools/dtk": "dtk", "build/tools/objdiff-cli": "objdiff-cli", "build/tools/wibo": "wibo",
        "build/compilers/GC/1.3.2/mwcceppc.exe": "CodeWarrior 1.3.2", "build/binutils/powerpc-eabi-objdump": "binutils",
        "build.ninja": "build.ninja", "objdiff.json": "objdiff.json", "build/G9SE8P/main.dol": "linked main.dol",
    }
    missing = [name for rel, name in need.items() if not (ROOT / rel).exists()]
    if missing:
        add("FAIL", f"build tree incomplete, missing: {', '.join(missing)}", "python3 configure.py && ninja")
    else:
        add("PASS", "build tree present (tools, compilers, binutils, build.ninja, objdiff.json, main.dol)")


def check_tools() -> None:
    for exe, level, why in (("ninja", "FAIL", "required"), ("python3", "FAIL", "required"),
                            ("clang-format", "WARN", "the hook checks formatting"),
                            ("llvm-objcopy", "WARN", "without it 35 post-processor tests skip")):
        if shutil.which(exe):
            add("PASS", f"{exe} available")
        else:
            add(level, f"{exe} not found ({why})", "")


def verify_hashes() -> None:
    dtk = ROOT / "build" / "tools" / "dtk"
    if not dtk.exists():
        add("FAIL", "cannot verify hashes: build/tools/dtk missing", "python3 configure.py && ninja")
        return
    r = subprocess.run([str(dtk), "shasum", "-c", "config/G9SE8P/build.sha1"], cwd=ROOT, capture_output=True, text=True)
    ok = r.stdout.count("OK")
    total = len([l for l in (ROOT / "config/G9SE8P/build.sha1").read_text().splitlines() if l.strip()])
    if r.returncode == 0 and ok == total:
        add("PASS", f"all {total} artifact hashes match config/G9SE8P/build.sha1 (state of the CURRENT build/, not the source)")
    else:
        add("FAIL", f"artifact hashes: {ok}/{total} OK", "ninja   # then rerun with --verify")


def main() -> int:
    ap = argparse.ArgumentParser(description="read-only environment check")
    ap.add_argument("--verify", action="store_true", help="also verify the artifact hashes of the current build")
    a = ap.parse_args()
    check_git()
    check_orig()
    check_build()
    check_tools()
    if a.verify:
        verify_hashes()
    width = {"PASS": "PASS", "WARN": "WARN", "FAIL": "FAIL"}
    for level, msg, fix in results:
        print(f"[{width[level]}] {msg}" + (f"\n       fix: {fix}" if fix and level != "PASS" else ""))
    fails = sum(1 for l, _, _ in results if l == "FAIL")
    warns = sum(1 for l, _, _ in results if l == "WARN")
    print(f"\n{len(results) - fails - warns} pass, {warns} warn, {fails} fail")
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main())
