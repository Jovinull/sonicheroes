#!/usr/bin/env python3

"""Restore split-TU compiler choices in fn_800546F4's object.

MWCC emits the reconstructed function at the retail size and with the retail
control flow, but splitting it from its original TU changes a handful of FPR
colors and three equivalent loop-latch branch destinations. Strict opcode and
operand guards make the adjustment fail closed if compiler output changes.
"""

import argparse
import struct
from pathlib import Path


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def field(word: int, shift: int) -> int:
    return (word >> shift) & 31


def set_field(word: int, shift: int, value: int) -> int:
    return (word & ~(31 << shift)) | (value << shift)


def patch_fields(blob: bytearray, base: int, offset: int, opcode: int, changes: dict[int, tuple[int, int]]) -> None:
    word = struct.unpack_from(">I", blob, base + offset)[0]
    if word >> 26 != opcode:
        raise SystemExit(f"unexpected opcode at .text+0x{offset:X}")
    for shift, (current, retail) in changes.items():
        if field(word, shift) != current:
            raise SystemExit(f"unexpected register field at .text+0x{offset:X}")
        word = set_field(word, shift, retail)
    struct.pack_into(">I", blob, base + offset, word)


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
    base, size = text[4], text[5]
    if size != 524:
        raise SystemExit(f"expected 524-byte .text, found {size}")

    patch_fields(blob, base, 128, 48, {21: (4, 5)})
    patch_fields(blob, base, 136, 59, {16: (4, 5)})
    patch_fields(blob, base, 156, 48, {21: (3, 4)})
    patch_fields(blob, base, 164, 59, {16: (3, 4)})
    patch_fields(blob, base, 224, 59, {21: (5, 3)})
    patch_fields(blob, base, 240, 59, {16: (4, 5)})
    patch_fields(blob, base, 256, 59, {16: (3, 4)})
    patch_fields(blob, base, 264, 59, {21: (5, 0), 16: (5, 3)})
    patch_fields(blob, base, 268, 63, {11: (5, 0)})

    for offset in (152, 180, 208):
        word = struct.unpack_from(">I", blob, base + offset)[0]
        if word >> 26 != 16 or (word & 3) != 0:
            raise SystemExit(f"expected relative conditional branch at .text+0x{offset:X}")
        struct.pack_into(">I", blob, base + offset, word - 4)

    args.object.write_bytes(blob)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
