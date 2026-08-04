#!/usr/bin/env python3

"""Remove compiler-only ABI data from o_s01_taihostull.cpp.

The isolated multiple-inheritance model makes CodeWarrior emit the retail
eight-byte this-adjusting thunk. It also emits an unused model vtable. This
pass redirects the real Stull vtable to that compiler-generated thunk,
removes only the compiler-model data, and renames the two retail methods.
It does not alter any retail function instruction.
"""

import argparse
import struct
import subprocess
from pathlib import Path


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def set_atom_alignments(path: Path, names: tuple[str, ...], alignment: int) -> None:
    data = bytearray(path.read_bytes())
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
    sections = [
        struct.unpack_from(">IIIIIIIIII", data, header[6] + i * header[11])
        for i in range(header[12])
    ]
    shstr = sections[header[13]]
    shstr_data = data[shstr[4] : shstr[4] + shstr[5]]
    by_name = {
        cstring(shstr_data, section[0]): section for section in sections
    }
    symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    comment = by_name[".comment"]
    wanted = set(names)
    for index, offset in enumerate(
        range(symtab[4], symtab[4] + symtab[5], symtab[9])
    ):
        symbol = struct.unpack_from(">IIIBBH", data, offset)
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        if name in wanted:
            struct.pack_into(
                ">I", data, comment[4] + 0x2C + index * 8, alignment
            )
            wanted.remove(name)
    if wanted:
        raise SystemExit(f"missing atoms after objcopy: {sorted(wanted)}")
    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", required=True, type=Path)
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

    data_index, data_section = by_name[".data"]
    model_name = "__vt__10StullThunk"
    model_index = symbols_by_name[model_name]
    model_offset, model_symbol, _ = symbols[model_index]
    if model_symbol[1] != 0x74 or model_symbol[2] != 0x1C:
        raise SystemExit("unexpected Stull ABI-model vtable")

    thunk_name = "@40@EditOnChange__10StullThunkFP13SETDATA_PARAM"
    placeholder_name = "AdjustorEditOnChange__10StullThunkFP13SETDATA_PARAM"
    thunk_index = symbols_by_name[thunk_name]
    placeholder_index = symbols_by_name[placeholder_name]
    _, rela_data = by_name[".rela.data"]
    relocations = []
    for offset in range(
        rela_data[4], rela_data[4] + rela_data[5], rela_data[9]
    ):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        if relocation[0] >= 0x74:
            continue
        if relocation[1] >> 8 == placeholder_index:
            relocation[1] = (thunk_index << 8) | (relocation[1] & 0xFF)
        relocations.append(relocation)
    relocations.sort(key=lambda relocation: relocation[0])

    old_rela_size = rela_data[5]
    new_rela_size = len(relocations) * rela_data[9]
    for offset, relocation in zip(
        range(rela_data[4], rela_data[4] + new_rela_size, rela_data[9]),
        relocations,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)
    data[
        rela_data[4] + new_rela_size : rela_data[4] + old_rela_size
    ] = b"\0" * (old_rela_size - new_rela_size)
    rela_data[5] = new_rela_size

    data[data_section[4] + 0x74 : data_section[4] + data_section[5]] = b"\0" * (
        data_section[5] - 0x74
    )
    data_section[5] = 0x74
    data_section[8] = 4
    model_symbol[1] = 0
    model_symbol[2] = 0
    model_symbol[5] = 0

    _, comment = by_name[".comment"]
    field_index = symbols_by_name["stullFieldName"]
    struct.pack_into(">I", data, comment[4] + 0x2C + field_index * 8, 4)
    for name in ("@92", "@93", "stullTrailingZero"):
        index = symbols_by_name[name]
        struct.pack_into(">I", data, comment[4] + 0x2C + index * 8, 4)
    for index, (_, symbol, _) in enumerate(symbols):
        if (symbol[3] & 0xF) == 3 and symbol[5] == data_index:
            struct.pack_into(">I", data, comment[4] + 0x2C + index * 8, 4)

    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
    for offset, symbol, _ in symbols:
        struct.pack_into(">IIIBBH", data, offset, *symbol)
    args.object.write_bytes(data)

    output = args.object.with_suffix(".fixed.o")
    subprocess.run(
        [
            str(args.objcopy),
            "--strip-symbol",
            placeholder_name,
            "--strip-symbol",
            "PrimarySlot__17StullThunkPrimaryFv",
            "--strip-symbol",
            model_name,
            "--globalize-symbol",
            "stullVector1",
            "--globalize-symbol",
            "stullVector2",
            "--globalize-symbol",
            "stullTrailingZero",
            "--redefine-sym",
            "EditOnChange__10StullThunkFP13SETDATA_PARAM="
            "EditOnChange__12TObjS01StullFP13SETDATA_PARAM",
            "--redefine-sym",
            f"{thunk_name}=StullEditAdjustor",
            str(args.object),
            str(output),
        ],
        check=True,
    )
    set_atom_alignments(
        output,
        ("@92", "@93", "stullTrailingZero", "stullFieldName"),
        4,
    )
    output.replace(args.object)
    args.stamp.touch()


if __name__ == "__main__":
    main()
