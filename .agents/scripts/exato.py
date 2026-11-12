"""Level 2 of match verification: raw words and relocations, no percentages.

usage:
  python3 .agents/scripts/exato.py UNIT            # every retail function in the unit
  python3 .agents/scripts/exato.py UNIT SYMBOL     # one function, detailed
  python3 .agents/scripts/exato.py UNIT --data     # also compare data sections

Reads both ELF objects directly (elfmini.py). A function is EXACT
only if its size, every instruction word and every relocation (offset, type,
target, addend) agree. objdiff can show two lines as identical while their
relocations point at different data (it prints a nearby symbol name, not the
target), so the target is resolved here: when the names differ the bytes behind
both targets are compared, and the line says whether they at least hold the
same contents.

Remember: a NonMatching unit is not linked, so `18 files OK` says nothing about
it. Flip it to Matching in configure.py and run plain `ninja` for level 3.
"""

from __future__ import annotations

import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from _units import ROOT, build_base, resolve  # noqa: E402
import elfmini  # noqa: E402


def same_jumptable(t: elfmini.Elf, tj: elfmini.Symbol, tf: elfmini.Symbol,
                   o: elfmini.Elf, oj: elfmini.Symbol, of: elfmini.Symbol) -> bool:
    """A switch's jump table in .data is all relocations into its function: equal
    when both tables have the same words and the same entries (offset, type and
    destination relative to the function), using the retail table's size."""
    size = tj.size
    if not size or not (0 < tj.shndx < len(t.sections)) or not (0 < oj.shndx < len(o.sections)):
        return False

    def entries(elf: elfmini.Elf, j: elfmini.Symbol, f: elfmini.Symbol) -> list[tuple] | None:
        out = []
        for r in elf.relocs_for(j.shndx):
            if not (j.value <= r.offset < j.value + size):
                continue
            s = elf.symbols[r.sym]
            if s.shndx != f.shndx:
                return None
            base = 0 if s.type == "section" else s.value
            out.append((r.offset - j.value, r.type, base + r.addend - f.value))
        return out

    te, oe = entries(t, tj, tf), entries(o, oj, of)
    tw = t.sections[tj.shndx].data[tj.value : tj.value + size]
    ow = o.sections[oj.shndx].data[oj.value : oj.value + size]
    return te is not None and te == oe and len(te) == size // 4 and tw == ow


def target_desc(elf: elfmini.Elf, r: elfmini.Reloc) -> tuple[str, bytes]:
    s = elf.symbols[r.sym]
    if s.type == "section" or not s.name:
        sec = elf.sections[s.shndx] if 0 < s.shndx < len(elf.sections) else None
        name = f"{sec.name if sec else '?'}+{r.addend:#x}"
        data = sec.data[r.addend : r.addend + 8] if sec else b""
        return name, data
    name = s.name + (f"+{r.addend:#x}" if r.addend else "")
    data = b""
    if 0 < s.shndx < len(elf.sections):
        sec = elf.sections[s.shndx]
        start = s.value + r.addend
        n = s.size if s.size else 8
        data = sec.data[start : start + min(n, 16)]
    return name, data

DATA_SECTIONS = (".data", ".rodata", ".sdata", ".sdata2", ".ctors", ".dtors", "extab", "extabindex")
RELOC_WIDTH = {1: 4, 2: 4, 3: 2, 4: 2, 5: 2, 6: 2, 10: 4, 11: 4, 109: 4}


def masked(elf: elfmini.Elf, sec: elfmini.Section) -> tuple[bytearray, list[elfmini.Reloc]]:
    """Section bytes with every relocated field zeroed. dtk leaves the original
    pointer value in those fields while MWCC writes zero, so the raw bytes of a
    relocated word never agree; the relocation itself is compared instead."""
    data = bytearray(sec.data)
    rel = elf.relocs_for(sec.index)
    for r in rel:
        w = RELOC_WIDTH.get(r.type, 4)
        off = r.offset & ~1 if w == 2 and r.type in (4, 5, 6) else r.offset
        data[off : off + w] = bytes(w)
    return data, rel


def compare_data(t: elfmini.Elf, o: elfmini.Elf, tsec: elfmini.Section, osec: elfmini.Section) -> None:
    tb, tr = masked(t, tsec)
    ob, orr = masked(o, osec)
    notes = []
    if tsec.size != osec.size:
        notes.append(f"size retail {tsec.size:#x} ours {osec.size:#x}")
    n = min(len(tb), len(ob))
    bad = [i for i in range(n) if tb[i] != ob[i]]
    if bad:
        notes.append(f"{len(bad)} differing bytes, first at +{bad[0]:#x}")
    tset = {(r.offset, r.type) for r in tr}
    oset = {(r.offset, r.type) for r in orr}
    if tset != oset:
        notes.append(f"relocation shape differs at {len(tset ^ oset)} sites "
                     f"(first +{min(x[0] for x in tset ^ oset):#x})")
    else:
        names = sum(1 for a, b in zip(tr, orr) if target_desc(t, a)[0] != target_desc(o, b)[0])
        if names:
            notes.append(f"{names} relocations name a different target (often only fn_ vs real names)")
    print(f"  {tsec.name}: " + ("; ".join(notes) if notes else f"EXACT ({tsec.size:#x} bytes, {len(tr)} relocations)"))


def compare(t: elfmini.Elf, o: elfmini.Elf, name: str, verbose: bool) -> bool:
    ts, os_ = t.sym(name), o.sym(name)
    if ts is None:
        print(f"  {name}: not in retail object")
        return False
    paired = ""
    if os_ is None:
        # symbols.txt often still says fn_XXXXXXXX where the source has the
        # real (mangled) name; fall back to the function at the same place.
        tsec_name = t.sections[ts.shndx].name
        os_ = next((s for s in o.symbols if s.type == "func" and s.shndx
                    and o.sections[s.shndx].name == tsec_name and s.value == ts.value), None)
        if os_ is None:
            print(f"  {name}: MISSING in ours (no function of that name or at {tsec_name}+{ts.value:#x})")
            return False
        paired = f" [paired by address with {os_.name}]"
    tsec, osec = t.sections[ts.shndx], o.sections[os_.shndx]
    tb = tsec.data[ts.value : ts.value + ts.size]
    ob = osec.data[os_.value : os_.value + os_.size]
    problems = []
    if ts.size != os_.size:
        problems.append(f"size retail {ts.size:#x} ours {os_.size:#x}")
    nwords = min(len(tb), len(ob)) // 4
    tr = [r for r in t.relocs_for(ts.shndx) if ts.value <= r.offset < ts.value + ts.size]
    orr = [r for r in o.relocs_for(os_.shndx) if os_.value <= r.offset < os_.value + os_.size]
    # A branch back into the function itself (a loop whose head is the first
    # instruction) is a relocation against the function's symbol in the split
    # original and a resolved displacement in ours. Accept it only when ours has
    # no relocation there and our word is the retail word with exactly that
    # displacement filled in.
    ours_at = {r.offset - os_.value for r in orr}
    self_ok = set()
    for r in tr:
        s = t.symbols[r.sym]
        off = r.offset - ts.value
        if r.type not in (10, 11) or s.shndx != ts.shndx or off in ours_at or off % 4:
            continue
        base = s.value if s.type != "section" else 0
        disp = base + r.addend - r.offset
        tw = int.from_bytes(tb[off : off + 4], "big")
        ow = int.from_bytes(ob[off : off + 4], "big") if off + 4 <= len(ob) else None
        mask = 0x03FFFFFC if r.type == 10 else 0x0000FFFC
        if ow is not None and (tw & mask) == 0 and (ow & ~mask) == (tw & ~mask) and (ow & mask) == (disp & mask):
            self_ok.add(off)
    tr = [r for r in tr if r.offset - ts.value not in self_ok]
    bad_words = [i for i in range(nwords) if tb[i * 4 : i * 4 + 4] != ob[i * 4 : i * 4 + 4] and i * 4 not in self_ok]
    if bad_words:
        problems.append(f"{len(bad_words)} differing words, first at +{bad_words[0] * 4:#x}")
    reloc_lines = []
    if len(tr) != len(orr):
        problems.append(f"relocation count retail {len(tr)} ours {len(orr)}")
    for a, b in zip(tr, orr):
        ao, bo = a.offset - ts.value, b.offset - os_.value
        an, ad = target_desc(t, a)
        bn, bd = target_desc(o, b)
        if ao != bo or a.type != b.type:
            reloc_lines.append(f"    +{ao:#x} type {a.type} {an}  vs  +{bo:#x} type {b.type} {bn}")
        elif an != bn and an.startswith("jumptable_") and bn.startswith("@") \
                and same_jumptable(t, t.symbols[a.sym], ts, o, o.symbols[b.sym], os_):
            # the switch's table: dtk names it, the compiler keeps it local; the
            # entries (relocations into this function) were compared instead
            pass
        elif an != bn:
            same = "same bytes" if ad and ad == bd else "DIFFERENT bytes"
            reloc_lines.append(f"    +{ao:#x} {elfmini.PPC_RELOC.get(a.type, a.type)}: retail {an}  ours {bn}"
                               f"  ({same}: {ad.hex()} / {bd.hex()})")
    if reloc_lines:
        problems.append(f"{len(reloc_lines)} relocation target/shape differences")
        print(chr(10).join(reloc_lines))
    if not problems:
        if verbose or paired:
            print(f"  {name}: EXACT ({ts.size:#x} bytes, {len(tr)} relocations){paired}")
        return True
    print(f"  {name}{paired}: " + "; ".join(problems))
    if verbose:
        for i in bad_words[:40]:
            print(f"    +{i * 4:#06x} retail {tb[i * 4:i * 4 + 4].hex()} ours {ob[i * 4:i * 4 + 4].hex()}")
        for line in reloc_lines[:40]:
            print(line)
    return False


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("unit")
    ap.add_argument("symbol", nargs="?")
    ap.add_argument("--data", action="store_true")
    ap.add_argument("--no-build", action="store_true")
    a = ap.parse_args()
    unit = resolve(a.unit)
    if not a.no_build:
        build_base(unit)
    t = elfmini.load(str(ROOT / unit["target_path"]))
    o = elfmini.load(str(ROOT / unit["base_path"]))
    print(unit["name"])
    if a.symbol:
        ok = compare(t, o, a.symbol, True)
        sys.exit(0 if ok else 1)
    funcs = [s for s in t.symbols if s.type == "func" and s.shndx and s.size]
    funcs.sort(key=lambda s: (s.shndx, s.value))
    exact = sum(compare(t, o, s.name, False) for s in funcs)
    print(f"  EXACT {exact}/{len(funcs)} functions")
    if a.data:
        for tsec in t.sections:
            if tsec.type == elfmini.SHT_NOBITS or tsec.name not in DATA_SECTIONS:
                continue
            osec = o.section(tsec.name)
            if osec is None:
                print(f"  {tsec.name}: missing in ours")
                continue
            compare_data(t, o, tsec, osec)
    sys.exit(0 if exact == len(funcs) else 1)


if __name__ == "__main__":
    main()
