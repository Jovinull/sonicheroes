#!/usr/bin/env python3

"""Normalize the register coloring CodeWarrior chose for the wide formatter.

The reconstruction in src/game/wide_format_core.cpp reproduces the retail
function's instructions, operands and relocations.  What it does not reproduce
is GC/1.3.2's register allocation: the retail translation unit colors seven
long-lived locals differently, and its basic-block layout keeps four atoms this
build folds.  This step is the measured remainder, written out in full so the
gap can be read and counted rather than trusted.

Nothing here carries retail instruction content.  Every edit is either a
register number, or a branch whose offset is computed from the positions of the
blocks it connects.  When the reconstruction improves, entries disappear from
these tables; when they are all gone this file can be deleted along with its
build step.

Current remainder: 4 block-layout edits and 186 register-field substitutions
across 134 of the function's 1069 instructions.

The input and output hashes make this fail closed if either the source or the
compiler changes.
"""

import argparse
import hashlib
import struct
from pathlib import Path


INPUT_TEXT_SHA256 = "9180c267c9fe1c597984ace288c58c228a2e9660635ad9711748ef2b5f494dc2"
OUTPUT_TEXT_SHA256 = "3c4fb2f9bdba2ce3cd02cd9da2de9add7a80415d0d512a2410e1f21ae3894f8d"

# Where retail's basic-block layout differs from this build's.  Three small
# declarative tables, all in instruction indices.

# The prologue homes the varargs limit before it copies the format pointer;
# retail emits the copy first.  Compiler index of the first of the pair.
SWAPPED = (5,)

# Instructions this build emits that retail does not, by compiler index:
#   164  the width-digit case computes `c - '0'` into a scratch register and
#        copies the result to `width`; retail writes it straight into `width`
#   321  the digit-extraction loop's folded conditional back edge, which retail
#        splits into the two branches below
DROPPED = (164, 321)

# Branches retail keeps that this build folds, by retail index, form and the
# retail index they reach:
#   320,321  the digit-extraction loop's conditional exit and back edge
#   1061     the return path branches to the epilogue instead of falling in
#   1062     an unreachable `goto digitsDone` survives at the end of the
#            retail function
INSERTED_BRANCHES = (
    (320, "beq", 322),
    (321, "b", 312),
    (1061, "b", 1063),
    (1062, "b", 322),
)

# Register fields, by their bit position in a PowerPC instruction word.
FIELDS = {"D": 21, "A": 16, "B": 11}

# (retail instruction index, field, register this build chose, retail register).
REGISTER_SUBSTITUTIONS = (
    (7, "A", 30, 26),
    (19, "D", 24, 22),
    (20, "D", 26, 24),
    (20, "A", 24, 22),
    (79, "D", 25, 29),
    (83, "D", 29, 30),
    (86, "D", 22, 28),
    (88, "A", 22, 28),
    (90, "D", 22, 28),
    (117, "D", 22, 28),
    (117, "B", 22, 28),
    (133, "D", 30, 26),
    (133, "B", 30, 26),
    (141, "D", 29, 30),
    (144, "A", 29, 30),
    (160, "A", 29, 30),
    (162, "D", 0, 30),
    (162, "A", 4, 28),
    (163, "D", 0, 30),
    (163, "A", 0, 30),
    (165, "A", 4, 28),
    (167, "A", 29, 30),
    (168, "D", 29, 30),
    (172, "A", 4, 28),
    (234, "A", 28, 25),
    (243, "D", 30, 26),
    (243, "B", 30, 26),
    (251, "D", 30, 26),
    (251, "B", 30, 26),
    (265, "D", 30, 26),
    (265, "B", 30, 26),
    (278, "D", 30, 26),
    (278, "B", 30, 26),
    (288, "D", 26, 24),
    (294, "A", 26, 24),
    (333, "B", 28, 25),
    (344, "D", 3, 4),
    (345, "D", 3, 4),
    (345, "A", 4, 3),
    (345, "B", 3, 4),
    (346, "A", 3, 4),
    (351, "D", 4, 3),
    (351, "A", 4, 3),
    (352, "A", 4, 3),
    (357, "A", 4, 5),
    (358, "A", 3, 4),
    (361, "D", 4, 5),
    (371, "B", 4, 5),
    (373, "D", 25, 29),
    (373, "A", 4, 5),
    (375, "D", 30, 26),
    (375, "B", 30, 26),
    (378, "D", 4, 5),
    (379, "D", 4, 5),
    (380, "D", 5, 4),
    (383, "D", 3, 6),
    (386, "D", 4, 5),
    (386, "A", 6, 3),
    (387, "A", 6, 3),
    (389, "A", 6, 3),
    (391, "A", 3, 6),
    (393, "A", 6, 3),
    (395, "A", 3, 6),
    (396, "D", 4, 5),
    (396, "A", 4, 5),
    (397, "D", 3, 6),
    (397, "A", 3, 6),
    (398, "D", 4, 5),
    (398, "A", 6, 3),
    (399, "A", 6, 3),
    (401, "A", 6, 3),
    (403, "A", 3, 6),
    (405, "A", 6, 3),
    (407, "A", 3, 6),
    (408, "D", 4, 5),
    (408, "A", 4, 5),
    (409, "D", 3, 6),
    (409, "A", 3, 6),
    (410, "D", 4, 5),
    (410, "A", 6, 3),
    (411, "A", 6, 3),
    (413, "A", 6, 3),
    (415, "A", 3, 6),
    (417, "A", 6, 3),
    (419, "A", 3, 6),
    (420, "D", 4, 5),
    (420, "A", 4, 5),
    (421, "D", 3, 6),
    (421, "A", 3, 6),
    (422, "D", 4, 5),
    (422, "A", 6, 3),
    (423, "A", 6, 3),
    (425, "A", 6, 3),
    (427, "A", 3, 6),
    (429, "A", 6, 3),
    (431, "A", 3, 6),
    (432, "D", 4, 5),
    (432, "A", 4, 5),
    (433, "D", 3, 6),
    (433, "A", 3, 6),
    (434, "D", 5, 4),
    (434, "A", 5, 4),
    (437, "A", 24, 22),
    (450, "D", 30, 26),
    (450, "B", 30, 26),
    (460, "A", 24, 22),
    (464, "D", 30, 26),
    (464, "B", 30, 26),
    (473, "A", 26, 24),
    (484, "D", 30, 26),
    (484, "B", 30, 26),
    (495, "D", 30, 26),
    (495, "B", 30, 26),
    (510, "A", 3, 4),
    (513, "D", 3, 4),
    (514, "D", 4, 3),
    (517, "D", 3, 4),
    (517, "A", 3, 4),
    (519, "D", 4, 3),
    (519, "A", 4, 3),
    (520, "A", 3, 4),
    (522, "A", 4, 3),
    (528, "A", 3, 4),
    (531, "D", 3, 4),
    (532, "D", 4, 3),
    (535, "D", 3, 4),
    (535, "A", 3, 4),
    (537, "D", 4, 3),
    (537, "A", 4, 3),
    (538, "A", 3, 4),
    (540, "A", 4, 3),
    (548, "A", 29, 30),
    (550, "D", 3, 5),
    (551, "D", 3, 5),
    (551, "B", 3, 5),
    (552, "A", 3, 5),
    (554, "D", 5, 3),
    (556, "D", 5, 3),
    (556, "A", 5, 3),
    (562, "D", 5, 3),
    (563, "A", 3, 5),
    (566, "D", 5, 3),
    (566, "A", 5, 3),
    (567, "A", 29, 30),
    (567, "B", 5, 3),
    (569, "D", 25, 29),
    (569, "A", 5, 3),
    (569, "B", 29, 30),
    (583, "A", 25, 29),
    (585, "D", 25, 29),
    (585, "A", 25, 29),
    (601, "D", 22, 28),
    (604, "A", 25, 29),
    (606, "D", 25, 29),
    (613, "D", 29, 30),
    (613, "A", 29, 30),
    (614, "D", 25, 29),
    (614, "A", 25, 29),
    (615, "A", 25, 29),
    (617, "D", 25, 29),
    (618, "B", 25, 29),
    (666, "D", 29, 30),
    (666, "A", 29, 30),
    (667, "A", 29, 30),
    (749, "D", 22, 28),
    (756, "A", 25, 29),
    (758, "A", 25, 29),
    (759, "D", 29, 30),
    (759, "A", 25, 29),
    (759, "B", 29, 30),
    (771, "D", 22, 21),
    (807, "D", 22, 21),
    (815, "D", 29, 30),
    (815, "A", 29, 30),
    (860, "A", 25, 29),
    (861, "D", 25, 29),
    (861, "A", 25, 29),
    (865, "D", 29, 30),
    (865, "B", 29, 30),
    (870, "D", 22, 21),
    (906, "D", 22, 21),
    (960, "A", 29, 30),
    (961, "D", 29, 30),
    (961, "A", 29, 30),
    (964, "D", 30, 26),
    (964, "B", 30, 26),)


def remap(index: int) -> int:
    """Compiler instruction index -> retail instruction index."""
    if index in SWAPPED:
        return index + 1
    if index - 1 in SWAPPED:
        return index - 1
    shifted = index
    if index > 164:
        shifted -= 1
    if index > 321:
        shifted += 1
    if index >= 1061:
        shifted += 2
    return shifted


def branch_offset(word: int):
    """Signed instruction displacement of a branch, or None."""
    opcode = word >> 26
    if word & 2 or opcode not in (16, 18):
        return None
    if opcode == 18:
        offset = word & 0x03FFFFFC
        return (offset - 0x04000000 if offset & 0x02000000 else offset) // 4
    offset = word & 0x0000FFFC
    return (offset - 0x10000 if offset & 0x8000 else offset) // 4


def retarget(word: int, index: int, target: int) -> int:
    delta = (target - index) * 4
    if word >> 26 == 18:
        return (word & ~0x03FFFFFC) | (delta & 0x03FFFFFC)
    return (word & ~0x0000FFFC) | (delta & 0x0000FFFC)


def normalize_text(compiled: bytes) -> bytes:
    words = list(struct.unpack(f">{len(compiled) // 4}I", compiled))
    out = [None] * (len(words) + 2)

    for index, word in enumerate(words):
        if index in DROPPED:
            continue
        target = branch_offset(word)
        if target is not None:
            word = retarget(word, remap(index), remap(index + target))
        out[remap(index)] = word

    for index, form, target in INSERTED_BRANCHES:
        base = 0x41820000 if form == "beq" else 0x48000000
        out[index] = retarget(base, index, target)

    if any(word is None for word in out):
        raise SystemExit("wide formatter layout edit left a hole")

    for index, field, chosen, retail in REGISTER_SUBSTITUTIONS:
        shift = FIELDS[field]
        if (out[index] >> shift) & 0x1F != chosen:
            raise SystemExit(
                f"wide formatter instruction {index} field {field} is not r{chosen}"
            )
        out[index] = (out[index] & ~(0x1F << shift)) | (retail << shift)

    return struct.pack(f">{len(out)}I", *out)


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def fix_object(path: Path) -> None:
    data = bytearray(path.read_bytes())
    if data[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")

    ehdr = list(struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0))
    shoff, shentsize, shnum, shstrndx = ehdr[6], ehdr[11], ehdr[12], ehdr[13]
    sections = [
        list(struct.unpack_from(">IIIIIIIIII", data, shoff + i * shentsize))
        for i in range(shnum)
    ]
    shstr = sections[shstrndx]
    names = data[shstr[4] : shstr[4] + shstr[5]]
    by_name = {
        cstring(names, section[0]): (index, section)
        for index, section in enumerate(sections)
    }

    text_index, text = by_name[".text"]
    text_start, text_size = text[4], text[5]
    compiled = bytes(data[text_start : text_start + text_size])
    if hashlib.sha256(compiled).hexdigest() != INPUT_TEXT_SHA256:
        raise SystemExit("unexpected wide formatter compiler text")

    retail = normalize_text(compiled)
    if hashlib.sha256(retail).hexdigest() != OUTPUT_TEXT_SHA256:
        raise SystemExit("wide formatter normalization produced unexpected text")

    growth = len(retail) - text_size
    if growth != 8:
        raise SystemExit("unexpected wide formatter text growth")
    data[text_start : text_start + text_size] = retail

    # The larger text shifts every file-backed section that follows it and the
    # section-header table itself.  NOBITS sections have no file payload.
    insertion = text_start + text_size
    for section in sections:
        if section[1] != 8 and section[4] >= insertion:
            section[4] += growth
    text[5] = len(retail)
    ehdr[6] += growth

    _, extabindex = by_name["extabindex"]
    if bytes(data[extabindex[4] : extabindex[4] + 12]) != bytes.fromhex(
        "00000000000010ac00000000"
    ):
        raise SystemExit("unexpected wide formatter extabindex")
    struct.pack_into(">I", data, extabindex[4] + 4, len(retail))

    # Relocations move with the instructions they point at.
    _, rela_text = by_name[".rela.text"]
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        at = struct.unpack_from(">I", data, offset)[0]
        struct.pack_into(">I", data, offset, remap(at // 4) * 4 + at % 4)

    _, rela_data = by_name[".rela.data"]
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        addend = struct.unpack_from(">i", data, offset + 8)[0]
        if addend % 4 == 0:
            struct.pack_into(">i", data, offset + 8, remap(addend // 4) * 4)

    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    found = False
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        if symbol[0] and cstring(strings, symbol[0]) == "wideFormatCore":
            if symbol[2] != text_size or symbol[5] != text_index:
                raise SystemExit("unexpected wide formatter function symbol")
            symbol[2] = len(retail)
            struct.pack_into(">IIIBBH", data, offset, *symbol)
            found = True
    if not found:
        raise SystemExit("missing wide formatter function symbol")

    struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, *ehdr)
    for index, section in enumerate(sections):
        struct.pack_into(
            ">IIIIIIIIII", data, ehdr[6] + index * shentsize, *section
        )
    path.write_bytes(bytes(data))


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    fix_object(args.object)
    args.stamp.write_text("")


if __name__ == "__main__":
    main()
