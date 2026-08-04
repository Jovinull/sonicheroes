#!/usr/bin/env python3
"""Normalize two GC/1.3.2 C++-generated atoms in o_setDamegeCollision."""

import argparse
import struct
from pathlib import Path


def cstr(blob, offset):
    return blob[offset : blob.index(0, offset)].decode("ascii")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    data = bytearray(args.object.read_bytes())
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
    shoff, entsize, count, names_index = header[6], header[11], header[12], header[13]
    sections = [list(struct.unpack_from(">IIIIIIIIII", data, shoff + i * entsize)) for i in range(count)]
    names = sections[names_index]
    names_blob = data[names[4] : names[4] + names[5]]
    by_name = {cstr(names_blob, s[0]): (i, s) for i, s in enumerate(sections)}
    text_index, text = by_name[".text"]
    _, symtab = by_name[".symtab"]
    strings = sections[symtab[6]]
    strings_blob = data[strings[4] : strings[4] + strings[5]]
    symbols = []
    symbol_indices = {}
    for index, off in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9])):
        symbol = list(struct.unpack_from(">IIIBBH", data, off))
        name = cstr(strings_blob, symbol[0]) if symbol[0] else ""
        symbols.append((off, symbol, name))
        if name:
            symbol_indices[name] = index

    factory = next(s for _, s, n in symbols if n == "startObjSetDamageCollision")
    register = next(s for _, s, n in symbols if n == "setDamageCollisionRegister")
    thunk = next(s for _, s, n in symbols if n == "setDamageCollisionEditThunk")
    edit_index = symbol_indices["setDamageCollisionEditOnChange"]
    if (factory[2], register[2], thunk[2]) != (0x12C, 0x98, 0x24):
        raise SystemExit("unexpected compiler-generated atom layout")

    insert = factory[1] + 0x30
    thunk_start = thunk[1]
    raw = bytearray(data[text[4] : text[4] + text[5]])
    raw[factory[1] + 0x24 : factory[1] + 0x2C] = (
        b"\x7c\x60\x1b\x78\x28\x00\x00\x00"
    )
    branch = struct.unpack_from(">I", raw, insert - 4)[0] + 4
    replacement = bytearray(raw[: insert - 4])
    replacement += struct.pack(">I", branch)
    replacement += b"\x7c\x1f\x03\x78"  # new-expression result lifetime: mr r31,r0
    replacement += raw[insert:thunk_start]
    replacement += b"\x38\x63\xff\xd8\x48\x00\x00\x00"  # generated MI this-adjustor
    old_size = text[5]
    data[text[4] : text[4] + len(replacement)] = replacement
    data[text[4] + len(replacement) : text[4] + old_size] = b"\0" * (old_size - len(replacement))
    text[5] = len(replacement)

    _, rela = by_name[".rela.text"]
    relocs = []
    for off in range(rela[4], rela[4] + rela[5], rela[9]):
        pos, info, addend = struct.unpack_from(">IIi", data, off)
        if thunk_start <= pos < thunk_start + 0x24:
            continue
        if pos >= insert:
            pos += 4
        relocs.append([pos, info, addend])
    relocs.append([thunk_start + 8, (edit_index << 8) | 10, 0])
    relocs.sort(key=lambda r: r[0])
    for off, reloc in zip(range(rela[4], rela[4] + len(relocs) * rela[9], rela[9]), relocs):
        struct.pack_into(">IIi", data, off, *reloc)
    rela[5] = len(relocs) * rela[9]

    for off, symbol, name in symbols:
        if symbol[5] == text_index:
            if name == "startObjSetDamageCollision":
                symbol[2] += 4
            elif name == "setDamageCollisionEditThunk":
                symbol[1] += 4
                symbol[2] = 8
            elif symbol[1] >= insert:
                symbol[1] += 4
            if (symbol[3] & 0xF) == 3:
                symbol[2] = text[5]
            struct.pack_into(">IIIBBH", data, off, *symbol)

    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * entsize, *section)
    args.object.write_bytes(data)
    args.stamp.touch()


if __name__ == "__main__":
    main()
