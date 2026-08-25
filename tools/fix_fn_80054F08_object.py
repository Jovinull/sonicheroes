#!/usr/bin/env python3

"""Normalize GC/1.3.2's remaining fn_80054F08 compiler choices.

The reconstructed C++ emits the retail control flow, but this compiler folds
two redundant branch atoms, schedules one independent instruction earlier,
and colors four short-lived values differently.  This step inserts two
computed branches, swaps that adjacent pair, and changes thirteen register
fields across eleven of the function's 346 instructions.

Nothing here carries retail instruction content.  Input and output hashes make
the step fail closed.  Delete it when a source form reproduces these choices.
"""

import argparse
import hashlib
import struct
from pathlib import Path

INPUT_TEXT_SHA256 = "d8a8d24bd0fcecae5da898d96daca6e8658ca4cda4144a04195015b58ef98ef1"
OUTPUT_TEXT_SHA256 = "42ad9cb2d95ba2f63a9578f32824734dffd28f238ce825cc686011a8f8b8f88d"
FUNCTION_START = 39
INSERTED = ((90, "b", 92), (133, "b", 135))
BRANCH_RETARGETS = ((69, 92), (85, 92), (112, 135), (128, 135), (217, 228), (225, 228))
FIELDS = {"D": 21, "A": 16, "B": 11}
REGISTERS = (
    (162, "D", 3, 2), (164, "D", 2, 3),
    (168, "A", 2, 3), (168, "B", 3, 2),
    (173, "D", 2, 3), (177, "A", 2, 3), (177, "B", 3, 2),
    (231, "A", 20, 21), (234, "A", 21, 20),
    (235, "B", 21, 20), (236, "D", 20, 21),
    (352, "B", 21, 20), (353, "B", 20, 21), (354, "B", 21, 20),
)

def base_remap(index):
    if index < FUNCTION_START: return index
    local = index - FUNCTION_START
    return index + (local >= 51) + (local >= 93)

def remap(index):
    mapped = base_remap(index)
    if mapped == 228: return 229
    if mapped == 229: return 228
    return mapped

def branch_offset(word):
    opcode = word >> 26
    if word & 2 or opcode not in (16, 18): return None
    if opcode == 18:
        value = word & 0x03FFFFFC
        return (value - 0x04000000 if value & 0x02000000 else value) // 4
    value = word & 0x0000FFFC
    return (value - 0x10000 if value & 0x8000 else value) // 4

def retarget(word, index, target):
    delta = (target - index) * 4
    mask = 0x03FFFFFC if word >> 26 == 18 else 0x0000FFFC
    return (word & ~mask) | (delta & mask)

def normalize_text(compiled):
    if INPUT_TEXT_SHA256 and hashlib.sha256(compiled).hexdigest() != INPUT_TEXT_SHA256:
        raise SystemExit("unexpected fn_80054F08 compiler text")
    words = struct.unpack(f">{len(compiled) // 4}I", compiled)
    output = [None] * (len(words) + 2)
    for index, word in enumerate(words):
        target = branch_offset(word)
        if target is not None:
            word = retarget(word, remap(index), remap(index + target))
        output[remap(index)] = word
    for index, form, target in INSERTED:
        output[index] = retarget(0x48000000, index, target)
    if any(word is None for word in output): raise SystemExit("layout edit left a hole")
    for index, target in BRANCH_RETARGETS:
        if branch_offset(output[index]) is None: raise SystemExit(f"instruction {index} is not a branch")
        output[index] = retarget(output[index], index, target)
    for index, field, chosen, retail in REGISTERS:
        shift = FIELDS[field]
        actual = (output[index] >> shift) & 0x1F
        if actual != chosen:
            raise SystemExit(f"instruction {index} field {field} is r{actual}, expected r{chosen}")
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
    shstr = sections[shstrndx]
    names = data[shstr[4]:shstr[4] + shstr[5]]
    by_name = {cstring(names, section[0]): (i, section) for i, section in enumerate(sections)}
    text_index, text = by_name[".text"]
    start, old_size = text[4], text[5]
    normalized = normalize_text(bytes(data[start:start + old_size]))
    growth = len(normalized) - old_size
    data[start:start + old_size] = normalized
    insertion = start + old_size
    for section in sections:
        if section[1] != 8 and section[4] >= insertion: section[4] += growth
    text[5] = len(normalized)
    ehdr[6] += growth
    _, extabindex = by_name["extabindex"]
    struct.pack_into(">I", data, extabindex[4] + 4, 1384)
    _, extab = by_name["extab"]
    extab_start = extab[4]
    cleanup_end, action = struct.unpack_from(">II", data, extab_start + 4)
    if cleanup_end != 0x4B8 or action != 0x10:
        raise SystemExit("unexpected fn_80054F08 exception range")
    encoded = struct.unpack_from(">I", data, extab_start + 16)[0]
    if encoded != 0x8A000008:
        raise SystemExit("unexpected fn_80054F08 cleanup encoding")
    struct.pack_into(">I", data, extab_start + 4, cleanup_end + growth)
    struct.pack_into(">I", data, extab_start + 16, (encoded | 0x800000) + 9)
    _, rela_text = by_name[".rela.text"]
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        at = struct.unpack_from(">I", data, offset)[0]
        struct.pack_into(">I", data, offset, remap(at // 4) * 4 + at % 4)
    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4]:strtab[4] + strtab[5]]
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        if symbol[0] and cstring(strings, symbol[0]) == "fn_80054F08":
            symbol[2] = 1384
            struct.pack_into(">IIIBBH", data, offset, *symbol)
    struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, *ehdr)
    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, ehdr[6] + index * shentsize, *section)
    path.write_bytes(data)

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    fix_object(args.object)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()

if __name__ == "__main__": main()
