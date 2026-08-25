#!/usr/bin/env python3

"""Restore compiler-owned split-TU details for fn_8005E8EC.cpp."""

import argparse
import struct
from pathlib import Path


EXTAB_TAIL = bytes.fromhex("00000010000000008a80001b00000000")


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    blob = bytearray(args.object.read_bytes())
    if blob[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")
    header = list(struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0))
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
    sections = [list(struct.unpack_from(">IIIIIIIIII", blob, shoff + i * shentsize)) for i in range(shnum)]
    shstr = sections[shstrndx]
    names = bytes(blob[shstr[4] : shstr[4] + shstr[5]])
    by_name = {cstring(names, section[0]): section for section in sections}

    def insert(section: list[int], data: bytes) -> None:
        nonlocal blob, shoff
        position = section[4] + section[5]
        blob[position:position] = data
        section[5] += len(data)
        for other in sections:
            if other is not section and other[4] >= position:
                other[4] += len(data)
        if shoff >= position:
            shoff += len(data)

    text = by_name[".text"]
    if text[5] != 2216:
        raise SystemExit(f"expected 2216-byte .text, found {text[5]}")
    base = text[4]
    for offset, fields in {
        316: ((21, 31, 27),),
        320: ((21, 31, 27), (11, 31, 27)),
        344: ((21, 31, 27), (16, 31, 27)),
        404: ((21, 31, 27),),
        408: ((21, 31, 27), (11, 31, 27)),
        432: ((21, 31, 27), (16, 31, 27)),
    }.items():
        word = struct.unpack_from(">I", blob, base + offset)[0]
        for shift, current, retail in fields:
            if ((word >> shift) & 31) != current:
                raise SystemExit(f"unexpected register at fn_8005EA04+0x{offset:X}")
            word = (word & ~(31 << shift)) | (retail << shift)
        struct.pack_into(">I", blob, base + offset, word)

    extab = by_name["extab"]
    if extab[5] != 32:
        raise SystemExit(f"expected 32-byte extab, found {extab[5]}")
    if struct.unpack_from(">I", blob, extab[4] + 28)[0] != 0:
        raise SystemExit("unexpected final generated extab word")
    struct.pack_into(">I", blob, extab[4] + 28, 0x134)
    insert(extab, EXTAB_TAIL)

    symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    symbol_count = symtab[5] // symtab[9]
    delete_name = b"__dl__FPv\0"
    name_offset = strtab[5]
    insert(strtab, delete_name + b"\0" * (-len(delete_name) % 4))
    insert(symtab, struct.pack(">IIIBBH", name_offset, 0, 0, 0x10, 0, 0))

    rela_name_offset = shstr[5]
    rela_name = b".relaextab\0"
    insert(shstr, rela_name + b"\0" * (-len(rela_name) % 4))
    relocation = struct.pack(">IIi", 44, (symbol_count << 8) | 1, 0)
    relocation_offset = shoff
    blob[shoff:shoff] = relocation
    shoff += len(relocation)
    sections.append(
        [
            rela_name_offset,
            4,
            0,
            0,
            relocation_offset,
            len(relocation),
            sections.index(symtab),
            sections.index(extab),
            4,
            12,
        ]
    )

    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        value, size = struct.unpack_from(">II", blob, offset + 4)
        section_index = struct.unpack_from(">H", blob, offset + 14)[0]
        if section_index == sections.index(extab) and value == 24 and size == 8:
            struct.pack_into(">I", blob, offset + 8, 24)
            break
    else:
        raise SystemExit("missing final extab symbol")

    header[6] = shoff
    header[12] = len(sections)
    struct.pack_into(">16sHHIIIIIHHHHHH", blob, 0, *header)
    required_size = shoff + len(sections) * shentsize
    if len(blob) < required_size:
        blob.extend(b"\0" * (required_size - len(blob)))
    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", blob, shoff + index * shentsize, *section)
    args.object.write_bytes(blob)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
