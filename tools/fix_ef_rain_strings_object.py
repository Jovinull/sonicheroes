#!/usr/bin/env python3

"""Restore the retail four-byte alignment of ef_rain's filename atom."""

import argparse
import struct
from pathlib import Path


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

    data_index, data_section = by_name[".data"]
    if data_section[5] != 21 or data_section[8] != 8:
        raise SystemExit(
            f"unexpected .data size/alignment: {data_section[5]}/{data_section[8]}"
        )
    data_section[8] = 4
    struct.pack_into(
        ">IIIIIIIIII", data, shoff + data_index * shentsize, *data_section
    )

    _, symtab = by_name[".symtab"]
    _, comment = by_name[".comment"]
    for symbol_index, offset in enumerate(
        range(symtab[4], symtab[4] + symtab[5], symtab[9])
    ):
        symbol = struct.unpack_from(">IIIBBH", data, offset)
        if symbol[3] & 0xF == 3 and symbol[5] == data_index:
            struct.pack_into(">I", data, comment[4] + 0x2C + symbol_index * 8, 4)
            break
    else:
        raise SystemExit("missing .data section symbol")

    args.object.write_bytes(data)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
