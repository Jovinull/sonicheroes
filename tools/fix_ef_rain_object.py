#!/usr/bin/env python3

"""Restore the retail order of ef_rain's compiler-generated tail functions."""

import argparse
import struct
from pathlib import Path


DTOR_START = 0x338
SINIT_START = 0x39C
TEXT_END = 0x3B8
DTOR_SHIFT = TEXT_END - SINIT_START
SINIT_SHIFT = SINIT_START - DTOR_START


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()

    data = bytearray(args.object.read_bytes())
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
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

    _, text = by_name[".text"]
    if text[5] != TEXT_END:
        raise SystemExit(f"unexpected .text size: {text[5]:#x}")
    start = text[4]
    dtor = bytes(data[start + DTOR_START : start + SINIT_START])
    sinit = bytes(data[start + SINIT_START : start + TEXT_END])
    data[start + DTOR_START : start + TEXT_END] = sinit + dtor

    _, rela_text = by_name[".rela.text"]
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        relocation_offset = struct.unpack_from(">I", data, offset)[0]
        if DTOR_START <= relocation_offset < SINIT_START:
            relocation_offset += DTOR_SHIFT
        elif SINIT_START <= relocation_offset < TEXT_END:
            relocation_offset -= SINIT_SHIFT
        struct.pack_into(">I", data, offset, relocation_offset)

    _, symtab = by_name[".symtab"]
    _, strtab = by_name[".strtab"]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    found = set()
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        name_offset, value = struct.unpack_from(">II", data, offset)
        name = cstring(strings, name_offset) if name_offset else ""
        if name == "__dt__6EfRainFv":
            if value != DTOR_START:
                raise SystemExit(f"unexpected destructor offset: {value:#x}")
            struct.pack_into(">I", data, offset + 4, DTOR_START + DTOR_SHIFT)
            found.add(name)
        elif name == "__sinit_ef_rain_cpp":
            if value != SINIT_START:
                raise SystemExit(f"unexpected initializer offset: {value:#x}")
            struct.pack_into(">I", data, offset + 4, DTOR_START)
            found.add(name)
    if found != {"__dt__6EfRainFv", "__sinit_ef_rain_cpp"}:
        raise SystemExit(f"missing tail symbols: {found}")

    args.object.write_bytes(data)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
