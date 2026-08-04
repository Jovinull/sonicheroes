#!/usr/bin/env python3

"""Normalize the slot thunk and discard its compiler-only weak vtable tail."""

import argparse
import struct
import shutil
import subprocess
import sys
from pathlib import Path


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def trim_compiler_vtable(path: Path) -> None:
    data = bytearray(path.read_bytes())
    if data[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")

    ehdr = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
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

    data_index, data_section = by_name[".data"]
    if data_section[5] != 0xF8:
        raise SystemExit(
            f"unexpected slot .data size 0x{data_section[5]:X}; expected 0xF8"
        )

    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    symbols = []
    symbol_by_name = {}
    for index, offset in enumerate(
        range(symtab[4], symtab[4] + symtab[5], symtab[9])
    ):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        symbols.append((offset, symbol, name))
        if name:
            symbol_by_name[name] = index

    generated_adjustor = symbol_by_name[
        "@40@EditOnChange__9SlotThunkFP13SETDATA_PARAM"
    ]
    declared_adjustor = symbol_by_name[
        "AdjustorEditOnChange__11TObjS33SlotFP13SETDATA_PARAM"
    ]

    vtable = next(
        (symbol for _, symbol, name in symbols if name == "__vt__9SlotThunk"),
        None,
    )
    if vtable is None or vtable[5] != data_index or vtable[1:3] != [0xDC, 0x1C]:
        raise SystemExit("unexpected compiler-only SlotThunk vtable layout")

    _, relocations = by_name[".rela.data"]
    kept = []
    removed_offsets = []
    for offset in range(
        relocations[4], relocations[4] + relocations[5], relocations[9]
    ):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        if relocation[0] == 0xAC:
            if relocation[1] >> 8 != declared_adjustor:
                raise SystemExit("unexpected slot adjustor relocation target")
            relocation[1] = (generated_adjustor << 8) | (relocation[1] & 0xFF)
        if relocation[0] >= 0xE0:
            removed_offsets.append(relocation[0])
        else:
            kept.append(relocation)
    if removed_offsets != [0xE4, 0xF0, 0xF4]:
        raise SystemExit(
            f"unexpected SlotThunk vtable relocations: {removed_offsets!r}"
        )
    old_relocation_size = relocations[5]
    new_relocation_size = len(kept) * relocations[9]
    for offset, relocation in zip(
        range(
            relocations[4],
            relocations[4] + new_relocation_size,
            relocations[9],
        ),
        kept,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)
    data[
        relocations[4] + new_relocation_size : relocations[4] + old_relocation_size
    ] = b"\0" * (old_relocation_size - new_relocation_size)
    relocations[5] = new_relocation_size

    data_section[5] = 0xE0
    for offset, symbol, name in symbols:
        if name == "__vt__9SlotThunk":
            symbol[1] = 0
            symbol[2] = 0
            symbol[5] = 0
        elif name == "AdjustorEditOnChange__11TObjS33SlotFP13SETDATA_PARAM":
            if symbol[1:3] != [0, 0] or symbol[5] != 0:
                raise SystemExit("unexpected declared slot adjustor layout")
            symbol[0] = 0
        elif (symbol[3] & 0xF) == 3 and symbol[5] == data_index:
            symbol[2] = data_section[5]
        if name == "@40@EditOnChange__9SlotThunkFP13SETDATA_PARAM":
            if symbol[3] != 0x22:
                raise SystemExit("unexpected weak slot adjustor binding")
            symbol[3] = 0x12
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path, help="object file to fix up in place")
    parser.add_argument("stamp", type=Path, help="stamp file to write on success")
    parser.add_argument("--objcopy", type=Path, required=True, help="path to objcopy")
    args = parser.parse_args()

    trim_compiler_vtable(args.object)
    temporary = args.object.parent / (args.object.name + ".symbols.tmp")
    subprocess.run(
        [
            str(args.objcopy),
            "--redefine-sym",
            (
                "@40@EditOnChange__9SlotThunkFP13SETDATA_PARAM="
                "AdjustorEditOnChange__11TObjS33SlotFP13SETDATA_PARAM"
            ),
            "--strip-symbol",
            "__vt__9SlotThunk",
            "--strip-symbol",
            "PrimarySlot__16SlotThunkPrimaryFv",
            str(args.object),
            str(temporary),
        ],
        check=True,
    )
    shutil.copystat(args.object, temporary)
    temporary.replace(args.object)
    args.stamp.touch()


if __name__ == "__main__":
    sys.exit(main())
