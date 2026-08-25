#!/usr/bin/env python3

"""Restore fn_80055470's retail floating-register assignment.

The reconstructed split TU reproduces every instruction but MWCC colors the
seven live single-precision values differently than it did in the original
larger TU. Apply that one consistent register permutation to the affected
instructions. Opcode and register guards make this fail closed if source or
compiler output changes.
"""

import argparse
import struct
from pathlib import Path


REGISTER_MAP = {1: 5, 2: 6, 3: 7, 4: 1, 5: 2, 6: 3, 7: 4}
LOADS = (76, 84, 100)
ARITHMETIC = (80, 88, 92, 96)
COMPARES = {
    104: ((3, 6), (7, 3)),
    120: ((4, 0), (1, 0)),
    136: ((0, 7), (0, 4)),
    152: ((5, 0), (2, 0)),
    220: ((0, 1), (0, 5)),
    236: ((1, 3), (5, 7)),
    252: ((0, 2), (0, 6)),
    276: ((2, 0), (6, 0)),
    400: ((3, 6), (7, 3)),
    416: ((6, 0), (3, 0)),
    428: ((6, 3), (3, 7)),
    440: ((3, 4), (7, 1)),
    456: ((1, 7), (1, 4)),
    472: ((7, 0), (4, 0)),
    484: ((7, 1), (4, 1)),
    496: ((1, 5), (1, 2)),
}


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def replace_field(word: int, shift: int) -> int:
    register = (word >> shift) & 31
    if register not in REGISTER_MAP:
        raise SystemExit(f"unexpected f{register} at instruction field {shift}")
    return (word & ~(31 << shift)) | (REGISTER_MAP[register] << shift)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()

    blob = bytearray(args.object.read_bytes())
    if blob[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")

    header = struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0)
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
    sections = [struct.unpack_from(">IIIIIIIIII", blob, shoff + i * shentsize) for i in range(shnum)]
    shstr = sections[shstrndx]
    names = blob[shstr[4] : shstr[4] + shstr[5]]
    text = next(section for section in sections if cstring(names, section[0]) == ".text")
    text_offset, text_size = text[4], text[5]
    if text_size != 560:
        raise SystemExit(f"expected 560-byte .text, found {text_size}")

    for offset in LOADS:
        word = struct.unpack_from(">I", blob, text_offset + offset)[0]
        if word >> 26 != 48:
            raise SystemExit(f"expected lfs at .text+0x{offset:X}")
        word = replace_field(word, 21)
        struct.pack_into(">I", blob, text_offset + offset, word)

    for offset in ARITHMETIC:
        word = struct.unpack_from(">I", blob, text_offset + offset)[0]
        if word >> 26 != 59:
            raise SystemExit(f"expected single-precision arithmetic at .text+0x{offset:X}")
        for shift in (21, 16, 11):
            register = (word >> shift) & 31
            if register in REGISTER_MAP:
                word = replace_field(word, shift)
            elif register != 31:
                raise SystemExit(f"unexpected f{register} at .text+0x{offset:X}")
        struct.pack_into(">I", blob, text_offset + offset, word)

    for offset, (current, retail) in COMPARES.items():
        word = struct.unpack_from(">I", blob, text_offset + offset)[0]
        if word >> 26 != 63 or (word & 0x7FF) != 64:
            raise SystemExit(f"expected fcmpo at .text+0x{offset:X}")
        actual = ((word >> 16) & 31, (word >> 11) & 31)
        if actual != current:
            raise SystemExit(f"unexpected fcmpo operands {actual} at .text+0x{offset:X}")
        word = (word & ~((31 << 16) | (31 << 11))) | (retail[0] << 16) | (retail[1] << 11)
        struct.pack_into(">I", blob, text_offset + offset, word)

    args.object.write_bytes(blob)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
