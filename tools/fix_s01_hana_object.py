#!/usr/bin/env python3

"""Remove compiler-only ABI data from o_s01_hana.cpp.

The small multiple-inheritance model makes CodeWarrior generate the retail
eight-byte this-adjusting thunk.  It also emits an unused model vtable.  Point
the real flower vtable at that generated thunk and remove only the compiler-
model vtable; no retail instruction or owned data byte is changed.
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
    for index, offset in enumerate(
        range(symtab[4], symtab[4] + symtab[5], symtab[9])
    ):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        symbols.append((offset, symbol, name))
        if name:
            symbols_by_name[name] = index

    data_index, data_section = by_name[".data"]
    model_name = "__vt__11FlowerThunk"
    model_index = symbols_by_name[model_name]
    model_offset, model_symbol, _ = symbols[model_index]
    model_start, model_size = model_symbol[1], model_symbol[2]
    if model_start != 0x1D8 or model_size != 0x1C:
        raise SystemExit(
            f"unexpected compiler-only vtable at {model_start:#x}, size {model_size:#x}"
        )
    if model_start + model_size != data_section[5]:
        raise SystemExit("compiler-only vtable is not the final data atom")

    thunk_name = "@40@EditOnChange__11FlowerThunkFP5Frame"
    placeholder_name = "AdjustorEditOnChange__11FlowerThunkFP5Frame"
    thunk_index = symbols_by_name[thunk_name]
    placeholder_index = symbols_by_name[placeholder_name]
    _, rela_data = by_name[".rela.data"]
    relocations = []
    for offset in range(
        rela_data[4], rela_data[4] + rela_data[5], rela_data[9]
    ):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        if relocation[0] >= model_start:
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
    data[rela_data[4] + new_rela_size : rela_data[4] + old_rela_size] = b"\0" * (
        old_rela_size - new_rela_size
    )
    rela_data[5] = new_rela_size

    data[data_section[4] + model_start : data_section[4] + data_section[5]] = (
        b"\0" * model_size
    )
    data_section[5] = model_start
    model_symbol[1] = 0
    model_symbol[2] = 0
    model_symbol[5] = 0
    struct.pack_into(">IIIBBH", data, model_offset, *model_symbol)

    for offset, symbol, _ in symbols:
        if (symbol[3] & 0xF) == 3 and symbol[5] == data_index:
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
            "PrimarySlot__18FlowerThunkPrimaryFv",
            "--strip-symbol",
            model_name,
            "--redefine-sym",
            f"EditOnChange__11FlowerThunkFP5Frame=flowerEditOnChange",
            "--redefine-sym",
            f"{thunk_name}=flowerEditAdjustor",
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
