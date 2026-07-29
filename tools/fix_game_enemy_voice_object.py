#!/usr/bin/env python3

"""Restore enemy_voice.cpp's retail function order.

CodeWarrior emits the two small entry helpers after the larger class methods
when this reconstructed translation unit is compiled in isolation.  The
retail object places them first.  Move complete function atoms and their
relocations without changing any instruction or data byte.
"""

import argparse
import struct
from pathlib import Path


TEXT_ORDER = (
    "fn_80139738",
    "fn_80139784",
    "fn_801397DC",
    "fn_801398E4",
    "fn_80139984",
    "fn_80139A24",
    "fn_80139BB8",
    "fn_80139C40",
    "fn_80139D28",
    "fn_80139E54",
    "fn_80139EDC",
)


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()

    data = bytearray(args.object.read_bytes())
    if data[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")

    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
    sections = [
        list(struct.unpack_from(">IIIIIIIIII", data, shoff + i * shentsize))
        for i in range(shnum)
    ]
    shstr = sections[shstrndx]
    shstr_data = data[shstr[4] : shstr[4] + shstr[5]]
    by_name = {
        cstring(shstr_data, section[0]): (index, section)
        for index, section in enumerate(sections)
    }

    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    symbols = []
    symbols_by_name = {}
    for index, offset in enumerate(
        range(symtab[4], symtab[4] + symtab[5], symtab[9])
    ):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        symbols.append((offset, symbol, name))
        if name:
            symbols_by_name[name] = index

    text_index, text = by_name[".text"]
    intervals = []
    new_text = bytearray()
    for name in TEXT_ORDER:
        _, symbol, _ = symbols[symbols_by_name[name]]
        old_start, size = symbol[1], symbol[2]
        new_start = len(new_text)
        intervals.append((old_start, old_start + size, new_start))
        new_text += data[text[4] + old_start : text[4] + old_start + size]
    if len(new_text) != text[5]:
        raise SystemExit(
            f"function layout covers {len(new_text):#x}, expected {text[5]:#x}"
        )
    data[text[4] : text[4] + text[5]] = new_text

    def map_text_offset(value: int) -> int:
        for old_start, old_end, new_start in intervals:
            if old_start <= value < old_end:
                return new_start + value - old_start
        if value == text[5]:
            return value
        raise ValueError(f"unmapped text offset {value:#x}")

    for offset, symbol, _ in symbols:
        if symbol[5] == text_index and (symbol[3] & 0xF) != 3:
            symbol[1] = map_text_offset(symbol[1])
            struct.pack_into(">IIIBBH", data, offset, *symbol)

    _, rela_text = by_name[".rela.text"]
    relocations = []
    for offset in range(
        rela_text[4], rela_text[4] + rela_text[5], rela_text[9]
    ):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        relocation[0] = map_text_offset(relocation[0])
        relocations.append(relocation)
    relocations.sort(key=lambda item: item[0])
    for offset, relocation in zip(
        range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]),
        relocations,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)

    args.object.write_bytes(data)
    args.stamp.touch()


if __name__ == "__main__":
    main()
