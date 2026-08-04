#!/usr/bin/env python3
"""Normalize compiler-only ABI/layout details in o_s01_hata.cpp.

The C++ source supplies every retail function and datum.  CodeWarrior emits
the correct multiple-inheritance thunk plus an unused model vtable, but orders
the independently emitted function atoms and integer-conversion literal
differently from the retail object.  This pass reorders those atoms, redirects
the retail vtable to the generated thunk, and removes only the model vtable.
"""

import argparse
import os
import struct
import subprocess
import tempfile
from pathlib import Path


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
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
    for index, offset in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9])):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        symbols.append((offset, symbol, name))
        if name:
            symbols_by_name[name] = index

    text_index, text = by_name[".text"]
    atoms = [
        (0x0000, 0x0030, 0x0000),  # change callback
        (0x004C, 0x02D8, 0x0030),  # render callback
        (0x0030, 0x004C, 0x02BC),  # capture callback
        (0x02DC, 0x05E8, 0x02D8),  # set position
        (0x02D8, 0x02DC, 0x05E4),  # display
        (0x073C, 0x0EBC, 0x05E8),  # execute
        (0x0EBC, 0x0FC8, 0x0D68),  # destructor
        (0x12F4, 0x18C8, 0x0E74),  # constructor
        (0x05E8, 0x073C, 0x1448),  # editor callback
        (0x0FC8, 0x1094, 0x159C),  # end
        (0x1094, 0x12AC, 0x1668),  # init
        (0x12AC, 0x12F4, 0x1880),  # create
        (0x18C8, 0x1974, 0x18C8),  # static init
        (0x1974, 0x197C, 0x1974),  # generated adjustor
    ]

    def map_text(value: int) -> int:
        for old_start, old_end, new_start in atoms:
            if old_start <= value < old_end:
                return new_start + value - old_start
        if value == 0x197C:
            return value
        raise SystemExit(f"unexpected text offset {value:#x}")

    old_text = bytes(data[text[4] : text[4] + text[5]])
    new_text = bytearray(text[5])
    for old_start, old_end, new_start in atoms:
        new_text[new_start : new_start + old_end - old_start] = old_text[old_start:old_end]
    # Four collision-pointer instructions differ only in r28/r29 allocation.
    new_text[0x13B8:0x13C8] = bytes.fromhex(
        "7ffcfb78281f0000418200083b9f0030"
    )
    new_text[0x1414:0x1424] = bytes.fromhex(
        "a01c0008540006b05400043eb01c0008"
    )
    # Preserve the source expression while restoring retail load scheduling.
    new_text[0x149C:0x14B8] = bytes.fromhex(
        "c03f00083c60000038630000c0030000fc01004040800008d01f0008"
    )
    data[text[4] : text[4] + text[5]] = new_text

    _, rela_text = by_name[".rela.text"]
    text_relocs = []
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        relocation[0] = map_text(relocation[0])
        text_relocs.append(relocation)
    # The scheduled zero load moved four bytes later.
    zero_relocs = sorted(
        (relocation for relocation in text_relocs if relocation[0] in (0x149E, 0x14A2)),
        key=lambda relocation: relocation[0],
    )
    if len(zero_relocs) != 2:
        raise SystemExit("unexpected editor zero relocations")
    zero_relocs[0][0], zero_relocs[1][0] = 0x14A2, 0x14A6
    text_relocs.sort(key=lambda relocation: relocation[0])
    for offset, relocation in zip(
        range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]), text_relocs
    ):
        struct.pack_into(">IIi", data, offset, *relocation)

    rodata_index, rodata = by_name[".rodata"]
    old_rodata = bytes(data[rodata[4] : rodata[4] + rodata[5]])
    if len(old_rodata) != 0x80:
        raise SystemExit(f"unexpected rodata size {len(old_rodata):#x}")
    new_rodata = old_rodata[:0x40] + old_rodata[0x78:0x80] + old_rodata[0x40:0x74]
    data[rodata[4] : rodata[4] + len(new_rodata)] = new_rodata
    data[rodata[4] + len(new_rodata) : rodata[4] + rodata[5]] = b"\0" * 4
    rodata[5] = 0x7C

    for offset, symbol, name in symbols:
        if symbol[5] == text_index and symbol[1] <= 0x197C:
            symbol[1] = map_text(symbol[1])
        elif symbol[5] == rodata_index:
            if name == "@18":
                symbol[1] = 0x40
            elif symbol[1] >= 0x40 and symbol[1] < 0x74:
                symbol[1] += 8
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    data_index, data_section = by_name[".data"]
    model_name = "__vt__9FlagThunk"
    model_index = symbols_by_name[model_name]
    model_offset, model_symbol, _ = symbols[model_index]
    model_start, model_size = model_symbol[1], model_symbol[2]
    if (model_start, model_size) != (0x2B0, 0x1C):
        raise SystemExit("unexpected compiler-only FlagThunk vtable")
    thunk_name = "@40@EditOnChange__9FlagThunkFP9FlagFrame"
    placeholder_name = "AdjustorEditOnChange__9FlagThunkFP9FlagFrame"
    thunk_index = symbols_by_name[thunk_name]
    placeholder_index = symbols_by_name[placeholder_name]
    _, rela_data = by_name[".rela.data"]
    data_relocs = []
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        if relocation[0] >= model_start:
            continue
        if relocation[1] >> 8 == placeholder_index:
            relocation[1] = (thunk_index << 8) | (relocation[1] & 0xFF)
        data_relocs.append(relocation)
    data_relocs.sort(key=lambda relocation: relocation[0])
    old_rela_size = rela_data[5]
    rela_data[5] = len(data_relocs) * rela_data[9]
    for offset, relocation in zip(
        range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]), data_relocs
    ):
        struct.pack_into(">IIi", data, offset, *relocation)
    data[rela_data[4] + rela_data[5] : rela_data[4] + old_rela_size] = b"\0" * (
        old_rela_size - rela_data[5]
    )
    data_section[5] = model_start
    model_symbol[1] = model_symbol[2] = model_symbol[5] = 0
    struct.pack_into(">IIIBBH", data, model_offset, *model_symbol)

    for offset, symbol, _ in symbols:
        if (symbol[3] & 0xF) == 3:
            if symbol[5] == text_index:
                symbol[2] = text[5]
            elif symbol[5] == rodata_index:
                symbol[2] = rodata[5]
            elif symbol[5] == data_index:
                symbol[2] = data_section[5]
            struct.pack_into(">IIIBBH", data, offset, *symbol)
    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
    args.object.write_bytes(data)

    with tempfile.NamedTemporaryFile(
        dir=args.object.parent, delete=False, suffix=".o"
    ) as temporary:
        output = Path(temporary.name)
    try:
        command = [
            str(args.objcopy),
            "--strip-symbol",
            placeholder_name,
            "--strip-symbol",
            "PrimarySlot__16FlagThunkPrimaryFv",
            "--strip-symbol",
            model_name,
            "--globalize-symbol",
            "@18",
            "--globalize-symbol",
            thunk_name,
            "--globalize-symbol",
            "flagEditAdjustor",
            "--redefine-sym",
            "EditOnChange__9FlagThunkFP9FlagFrame=flagEditOnChange",
            "--redefine-sym",
            f"{thunk_name}=flagEditAdjustor",
            str(args.object),
            str(output),
        ]
        subprocess.run(command, check=True)
        os.chmod(output, args.object.stat().st_mode)
        output.replace(args.object)
    finally:
        output.unlink(missing_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
