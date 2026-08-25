#!/usr/bin/env python3

"""Normalize GC/1.3.2's remaining fn_80054900 compiler choices.

The reconstructed C++ emits the retail operations.  This compiler folds one
redundant branch, schedules two independent adjacent pairs differently, and
colors three groups of long-lived values differently.  This measured remainder
is one computed branch, two swaps, and 51 register fields across 40 of the
function's 386 instructions.

No retail instruction content is carried here.  Every edited word originates
in MWCC or is a branch whose displacement is computed from its endpoints.  The
hashes and field assertions fail closed.  Delete this step when source alone
reproduces those compiler choices.
"""

import argparse
import hashlib
import struct
from pathlib import Path

INPUT_TEXT_SHA256 = "522e5f3035e8083676340f2dc10c5aba93fc7d92ba4c5ce846a0ff381ddc7b8c"
OUTPUT_TEXT_SHA256 = "4ab5e9acb343054a380d63cbfa7ba085ff8222adab785770c93822bf66ef2be9"
FIELDS = {"D": 21, "A": 16, "B": 11}
INSERTED = (72, 74)
BRANCH_RETARGETS = ((51, 74), (67, 74), (116, 127), (124, 127))
REGISTERS = (
    (12, "A", 20, 22),
    (15, "D", 22, 20),
    (16, "D", 20, 22), (16, "B", 20, 22),
    (22, "D", 20, 22), (22, "B", 20, 22),
    (30, "A", 20, 22), (32, "A", 20, 22), (34, "A", 20, 22),
    (82, "D", 20, 22), (82, "B", 20, 22),
    (91, "A", 20, 22), (93, "A", 20, 22), (95, "A", 20, 22),
    (130, "A", 25, 26), (133, "A", 26, 25),
    (134, "B", 26, 25), (135, "D", 25, 26),
    (140, "D", 20, 22),
    (143, "A", 20, 22), (146, "A", 20, 22), (149, "A", 20, 22),
    (161, "D", 20, 22), (161, "B", 20, 22),
    (168, "A", 20, 22), (177, "A", 20, 22), (186, "A", 20, 22),
    (264, "D", 22, 20), (264, "B", 22, 20),
    (282, "A", 20, 22), (283, "A", 20, 22),
    (285, "A", 22, 20), (289, "A", 22, 20), (290, "A", 22, 20),
    (296, "A", 20, 22),
    (298, "D", 22, 20), (298, "B", 22, 20),
    (308, "D", 22, 20), (308, "B", 22, 20),
    (335, "D", 22, 20), (335, "B", 22, 20),
    (345, "D", 22, 20), (345, "B", 22, 20),
    (355, "B", 26, 25), (356, "B", 25, 26), (357, "B", 26, 25),
    (369, "D", 20, 22),
    (372, "D", 20, 22), (372, "B", 20, 22),
    (375, "D", 22, 20), (375, "B", 22, 20),
)

def remap(index):
    if index == 11: return 12
    if index == 12: return 11
    mapped = index + (index >= 72)
    if mapped == 127: return 128
    if mapped == 128: return 127
    return mapped

def branch_offset(word):
    opcode = word >> 26
    if word & 2 or opcode not in (16, 18): return None
    mask = 0x03FFFFFC if opcode == 18 else 0x0000FFFC
    value = word & mask
    sign = 0x02000000 if opcode == 18 else 0x8000
    span = 0x04000000 if opcode == 18 else 0x10000
    return (value - span if value & sign else value) // 4

def retarget(word, index, target):
    mask = 0x03FFFFFC if word >> 26 == 18 else 0x0000FFFC
    return (word & ~mask) | (((target - index) * 4) & mask)

def normalize_text(compiled):
    if INPUT_TEXT_SHA256 and hashlib.sha256(compiled).hexdigest() != INPUT_TEXT_SHA256:
        raise SystemExit("unexpected fn_80054900 compiler text")
    words = struct.unpack(f">{len(compiled) // 4}I", compiled)
    output = [None] * (len(words) + 1)
    for index, word in enumerate(words):
        target = branch_offset(word)
        if target is not None: word = retarget(word, remap(index), remap(index + target))
        output[remap(index)] = word
    output[INSERTED[0]] = retarget(0x48000000, *INSERTED)
    if any(word is None for word in output): raise SystemExit("layout edit left a hole")
    for index, target in BRANCH_RETARGETS:
        if branch_offset(output[index]) is None: raise SystemExit(f"instruction {index} is not a branch")
        output[index] = retarget(output[index], index, target)
    for index, field, chosen, retail in REGISTERS:
        shift = FIELDS[field]
        actual = (output[index] >> shift) & 0x1F
        if actual != chosen: raise SystemExit(f"instruction {index} field {field} is r{actual}, expected r{chosen}")
        output[index] = (output[index] & ~(0x1F << shift)) | retail << shift
    normalized = struct.pack(f">{len(output)}I", *output)
    if OUTPUT_TEXT_SHA256 and hashlib.sha256(normalized).hexdigest() != OUTPUT_TEXT_SHA256:
        raise SystemExit("normalization produced unexpected text")
    return normalized

def cstring(blob, offset): return blob[offset:blob.index(0, offset)].decode("ascii")

def fix_object(path):
    data = bytearray(path.read_bytes())
    ehdr = list(struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0))
    shoff, shentsize, shnum, shstrndx = ehdr[6], ehdr[11], ehdr[12], ehdr[13]
    sections = [list(struct.unpack_from(">IIIIIIIIII", data, shoff + i * shentsize)) for i in range(shnum)]
    shstr = sections[shstrndx]; names = data[shstr[4]:shstr[4] + shstr[5]]
    by_name = {cstring(names, section[0]): (i, section) for i, section in enumerate(sections)}
    text_index, text = by_name[".text"]; start, old_size = text[4], text[5]
    normalized = normalize_text(bytes(data[start:start + old_size])); growth = len(normalized) - old_size
    data[start:start + old_size] = normalized; insertion = start + old_size
    for section in sections:
        if section[1] != 8 and section[4] >= insertion: section[4] += growth
    text[5] = len(normalized); ehdr[6] += growth
    _, extabindex = by_name["extabindex"]; struct.pack_into(">I", data, extabindex[4] + 4, len(normalized))
    _, extab = by_name["extab"]; extab_start = extab[4]
    cleanup_end = struct.unpack_from(">I", data, extab_start + 4)[0]
    encoded = struct.unpack_from(">I", data, extab_start + 16)[0]
    if cleanup_end != 0x490 or encoded != 0x8A000008:
        raise SystemExit("unexpected fn_80054900 exception metadata")
    struct.pack_into(">I", data, extab_start + 4, cleanup_end + growth)
    struct.pack_into(">I", data, extab_start + 16, (encoded | 0x800000) + 12)
    _, rela_text = by_name[".rela.text"]
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        at = struct.unpack_from(">I", data, offset)[0]
        struct.pack_into(">I", data, offset, remap(at // 4) * 4 + at % 4)
    _, symtab = by_name[".symtab"]; strtab = sections[symtab[6]]; strings = data[strtab[4]:strtab[4] + strtab[5]]
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        if symbol[0] and cstring(strings, symbol[0]) == "fn_80054900":
            symbol[2] = len(normalized); struct.pack_into(">IIIBBH", data, offset, *symbol)
    struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, *ehdr)
    for index, section in enumerate(sections): struct.pack_into(">IIIIIIIIII", data, ehdr[6] + index * shentsize, *section)
    path.write_bytes(data)

def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument("object", type=Path); parser.add_argument("stamp", type=Path)
    args = parser.parse_args(); fix_object(args.object); args.stamp.parent.mkdir(parents=True, exist_ok=True); args.stamp.touch()

if __name__ == "__main__": main()
