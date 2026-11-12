"""try1: compile a scratch source with the project's real MWCC command and compare ONE
function with the retail function, word by word.

Replaces the untracked build/_x/try1.py. This version compares MACHINE WORDS, not text, so
the false diffs the old asmcmp had (clrlwi/rlwinm, subic./addic., extrwi, lis -32768 vs 32768)
cannot happen, and branch targets ARE compared (the old one ignored them: "0 differ" could still
be a different CFG and fail exato).

usage:
  python3 .agents/scripts/try1.py SRC FUNC [--flags default|exc|ns|fpoff|"<raw mwcc flags>"]
                              [--retail-obj PATH] [--show]

--flags   default = the DOL's base flags (no extra_cflags)
          exc     = -Cpp_exceptions on
          ns      = -Cpp_exceptions on -opt noschedule,nopeephole   (units whose retail has extab)
          fpoff   = ns + -fp_contract off -pooldata off
          Rule from the notes: pick by RETAIL extab -- extab present -> ns, absent -> default.
--retail-obj  compare with a dtk target object instead of the retail .s (needed for functions
          that are already carved; they have no .s). Default: look in build/G9SE8P/asm/*.s, then
          build/G9SE8P/obj/game/<FUNC>.o.
--show    also print our disassembly (objdump).

Words are compared with the fields an R_PPC_* relocation fills masked out (REL24 target, @ha/@l/@h
immediates, SDA21 rA+offset). Relocation symbol names are compared separately and reported as
`sym` lines (an anonymous @NN literal on our side is informational). Exit 0 only when sizes and
all words agree. After placing the unit, the full build (`18 files OK`) plus objdiff are still the final judge
(extab, data, function order).

Retail asm is read locally and never written anywhere; do not paste it into the repo.
"""

from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import elfmini  # noqa: E402
ROOT = Path(__file__).resolve().parents[2]

WIN = sys.platform == "win32"
BASE_ANCHOR = "build/G9SE8P/src/game/fn_800898F0.o"  # a unit with NO extra_cflags
PRESETS = {
    "default": "",
    "exc": "-Cpp_exceptions on",
    "ns": "-Cpp_exceptions on -opt noschedule,nopeephole",
    "fpoff": "-Cpp_exceptions on -opt noschedule,nopeephole -fp_contract off -pooldata off",
}
# bits of the instruction word that the linker fills in for each relocation type
MASK = {
    1: 0xFFFFFFFF,  # ADDR32
    2: 0x03FFFFFC,  # ADDR24
    3: 0x0000FFFF,  # ADDR16
    4: 0x0000FFFF,  # ADDR16_LO
    5: 0x0000FFFF,  # ADDR16_HI
    6: 0x0000FFFF,  # ADDR16_HA
    7: 0x0000FFFC,  # ADDR14
    10: 0x03FFFFFC,  # REL24
    11: 0x0000FFFC,  # REL14
    109: 0x001FFFFF,  # EMB_SDA21 (rA + 16-bit offset)
    116: 0x001FFFFF,
}


def base_command() -> str:
    r = subprocess.run(["ninja", "-t", "commands", BASE_ANCHOR], cwd=ROOT, capture_output=True, text=True)
    lines = [l for l in r.stdout.splitlines() if "mwcceppc" in l]
    if not lines:
        sys.exit(f"cannot get the compile command of {BASE_ANCHOR}: run `python3 configure.py && ninja` first")
    cmd = lines[-1].split(" && ")[0]  # drop the dep-file transform step
    return cmd


def compile_scratch(src: Path, flags: str, tmp: Path) -> Path:
    cmd = base_command()
    c_src = re.search(r"-c (\S+)", cmd).group(1)
    o_dir = re.search(r"-o (\S+)", cmd).group(1)
    cmd = re.sub(r"-MMD\s+", ("%s " % flags) if flags else "", cmd)
    cmd = cmd.replace(f"-c {c_src}", f"-c {src.resolve()}").replace(f"-o {o_dir}", f"-o {tmp}")
    r = subprocess.run(cmd, cwd=ROOT, shell=True, capture_output=True, text=True)
    obj = tmp / (src.stem + ".o")
    if r.returncode or not obj.exists():
        sys.stdout.write((r.stdout + r.stderr)[-3500:])
        sys.exit("compile failed")
    if "Error" in r.stdout and "###" in r.stdout:
        sys.stdout.write(r.stdout[-1500:])
    return obj


def words_from_elf(path: Path, func: str):
    """-> (words, {index: symname}, {index: reloc_type}) for FUNC in the object's .text."""
    e = elfmini.load(str(path))
    sym = next((s for s in e.symbols if s.name == func and s.type == "func" and s.shndx), None)
    if sym is None:
        sys.exit(f"{path}: no function symbol {func!r} (static? name mangled? extern \"C\"?)")
    sec = e.sections[sym.shndx]
    blob = sec.data[sym.value : sym.value + sym.size]
    big = e.endian == ">"
    words = [int.from_bytes(blob[i : i + 4], "big" if big else "little") for i in range(0, len(blob), 4)]
    names, types = {}, {}
    for r in e.relocs_for(sec.index):
        if sym.value <= r.offset < sym.value + sym.size:
            i = (r.offset - sym.value) // 4
            names[i] = e.symbols[r.sym].name
            types[i] = r.type
    return words, names, types


LINE = re.compile(r"^/\*\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s+((?:[0-9A-Fa-f]{2}\s+){4})\*/\s*(.*)$")


def words_from_asm(func: str):
    """Find `.fn FUNC` in build/G9SE8P/asm/*.s -> (words, names, texts) or None."""
    asm_dir = ROOT / "build" / "G9SE8P" / "asm"
    needle = f".fn {func},"
    for f in sorted(asm_dir.glob("*.s")):
        txt = f.read_text(errors="replace")
        if needle not in txt:
            continue
        m = re.search(r"\.fn " + re.escape(func) + r", \w+\n(.*?)\.endfn", txt, re.S)
        if not m:
            continue
        words, names, texts = [], {}, []
        for line in m.group(1).splitlines():
            mm = LINE.match(line)
            if not mm:
                continue
            words.append(int(mm.group(2).replace(" ", ""), 16))
            text = mm.group(3)
            texts.append(text)
            sym = re.search(r"([A-Za-z_.@][\w.@$<>]*?)(?:@(?:ha|h|l|sda21))\b", text)
            if sym:
                names[len(words) - 1] = sym.group(1)
            else:  # bl/b to a named function: last operand token that is not a register/number/.L_ label
                if re.match(r"b(l|a|la)?\s", text):
                    tok = text.split()[-1]
                    if not tok.startswith(".L_") and not re.fullmatch(r"-?(0x)?[0-9a-fA-F]+", tok):
                        names[len(words) - 1] = tok
        return words, names, texts
    return None


def score(src: Path, func: str, flags: str = "default", retail_obj: str | None = None) -> int:
    """Number of differing words (+ length difference). 10**6 when it does not compile.

    Library entry point for perm.py and variant searches; no output, no exit."""
    flags = PRESETS.get(flags, flags)
    tmp = Path(tempfile.mkdtemp(prefix="try1_"))
    try:
        base = base_command()
        c_src = re.search(r"-c (\S+)", base).group(1)
        o_dir = re.search(r"-o (\S+)", base).group(1)
        cmd = re.sub(r"-MMD\s+", ("%s " % flags) if flags else "", base)
        cmd = cmd.replace(f"-c {c_src}", f"-c {Path(src).resolve()}").replace(f"-o {o_dir}", f"-o {tmp}")
        r = subprocess.run(cmd, cwd=ROOT, shell=True, capture_output=True, text=True)
        obj = tmp / (Path(src).stem + ".o")
        if r.returncode or not obj.exists():
            return 10**6
        try:
            ours, onames, otypes = words_from_elf(obj, func)
        except SystemExit:
            return 10**6
        retail = None if retail_obj else words_from_asm(func)
        if retail is None:
            cand = Path(retail_obj) if retail_obj else ROOT / "build/G9SE8P/obj/game" / f"{func}.o"
            rw, rnames, rtypes = words_from_elf(cand, func)
        else:
            rw, rnames, rtypes = retail[0], retail[1], {}
        bad = abs(len(ours) - len(rw))
        for i in range(min(len(ours), len(rw))):
            mask = 0
            for t in (otypes.get(i), rtypes.get(i)):
                if t is not None:
                    mask |= MASK.get(t, 0xFFFFFFFF)
            if i in rnames and i in onames and not rtypes:
                mask |= MASK.get(otypes.get(i), 0xFFFFFFFF)
            bad += (ours[i] & ~mask) != (rw[i] & ~mask)
        return bad
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("func")
    ap.add_argument("--flags", default=os.environ.get("TRY1_FLAGS", "default"))
    ap.add_argument("--retail-obj")
    ap.add_argument("--show", action="store_true")
    a = ap.parse_args()
    flags = PRESETS.get(a.flags, a.flags)

    tmp = Path(tempfile.mkdtemp(prefix="try1_"))
    try:
        obj = compile_scratch(Path(a.src), flags, tmp)
        ours, onames, otypes = words_from_elf(obj, a.func)

        retail = None
        if not a.retail_obj:
            retail = words_from_asm(a.func)
        if retail is None:
            cand = Path(a.retail_obj) if a.retail_obj else ROOT / "build/G9SE8P/obj/game" / f"{a.func}.o"
            if not cand.exists():
                sys.exit(f"{a.func}: not in build/G9SE8P/asm/*.s and no target object at {cand}\n"
                         "(carved functions need --retail-obj PATH to the dtk object)")
            rw, rnames, rtypes = words_from_elf(cand, a.func)
            retail = (rw, rnames, [""] * len(rw))
            rtypes_obj = rtypes
        else:
            rtypes_obj = {}
        rwords, rnames, rtexts = retail

        bad = 0
        n = max(len(ours), len(rwords))
        for i in range(n):
            if i >= len(ours) or i >= len(rwords):
                bad += 1
                print(f"{i * 4:4X}: {'ours  --------' if i >= len(ours) else f'ours  {ours[i]:08X}'}  "
                      f"{'retail --------' if i >= len(rwords) else f'retail {rwords[i]:08X}'}  (length differs)")
                continue
            mask = 0
            for t in (otypes.get(i), rtypes_obj.get(i)):
                if t is not None:
                    mask |= MASK.get(t, 0xFFFFFFFF)
            # retail .s has no relocation types: a symbol operand there means the same fields are linker-filled
            if i in rnames and i in onames and not rtypes_obj:
                mask |= MASK.get(otypes.get(i), 0xFFFFFFFF)
            if (ours[i] & ~mask) != (rwords[i] & ~mask):
                bad += 1
                print(f"{i * 4:4X}: ours {ours[i]:08X}  retail {rwords[i]:08X}  {rtexts[i]}")
        syms = 0
        for i in sorted(set(onames) | set(rnames)):
            o, r = onames.get(i), rnames.get(i)
            if o is None or r is None:
                if i < len(ours) and i < len(rwords):
                    print(f"{i * 4:4X}: sym  ours={o!r} retail={r!r}  (reloc on one side only)")
                    syms += 1
            elif o != r and not o.startswith("@") and not r.startswith("lbl_"):
                print(f"{i * 4:4X}: sym  ours={o} retail={r}")
                syms += 1
        print(f"{len(ours)} vs {len(rwords)} instructions, {bad} word diffs, {syms} symbol diffs "
              f"[flags: {a.flags}]")
        if a.show:
            od = ROOT / "build" / "binutils" / ("powerpc-eabi-objdump.exe" if WIN else "powerpc-eabi-objdump")
            print(subprocess.run([str(od), "-dr", f"--disassemble={a.func}", str(obj)], capture_output=True,
                                 text=True).stdout)
        return 1 if bad or len(ours) != len(rwords) else 0
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


if __name__ == "__main__":
    raise SystemExit(main())
