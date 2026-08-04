#!/usr/bin/env python3

"""Restore the retail o_s01_iwamizu.cpp ABI atom layout.

The isolated multiple-inheritance model makes CodeWarrior emit the retail
adjustor thunk, but also emits its unused model method and vtable.  This pass
keeps the compiler-emitted thunk instructions, retargets its relocation to the
retail implementation, removes only compiler-model atoms, and restores retail
section/atom ordering.  It never changes retail function instructions.
"""

import argparse
import struct
from pathlib import Path


TEXT_ORDER = (
    "SetIwamizuCallback",
    "fn_3_816D8",
    "CaptureIwamizuCallback",
    "fn_3_81858",
    "SetPosition__14TObjS01IwamizuFv",
    "Disp__14TObjS01IwamizuFv",
    "Exec__14TObjS01IwamizuFv",
    "__dt__14TObjS01IwamizuFv",
    "__ct__14TObjS01IwamizuFP7TObject",
    "EditOnChange__14TObjS01IwamizuFP13SETDATA_PARAM",
    "endObjS01Iwamizu",
    "initObjS01Iwamizu",
    "startObj_S01_Iwamizu",
    "__sinit_o_s01_iwamizu_cpp",
    "@40@BaseSlot__12IwamizuThunkFP7SetData",
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
    old_text_size = text[5]
    intervals = []
    new_text = bytearray()
    for name in TEXT_ORDER:
        _, symbol, _ = symbols[symbols_by_name[name]]
        old_start, size = symbol[1], symbol[2]
        new_start = len(new_text)
        intervals.append((old_start, old_start + size, new_start))
        new_text += data[text[4] + old_start : text[4] + old_start + size]
    if len(new_text) != 0xCCC:
        raise SystemExit(f"retail text is {len(new_text):#x}, expected 0xccc")
    data[text[4] : text[4] + len(new_text)] = new_text
    data[text[4] + len(new_text) : text[4] + text[5]] = b"\0" * (
        text[5] - len(new_text)
    )
    text[5] = len(new_text)

    def map_text_offset(value: int) -> int:
        for old_start, old_end, new_start in intervals:
            if old_start <= value < old_end:
                return new_start + value - old_start
        if value == old_text_size:
            return 0xCCC
        raise ValueError(f"unmapped text offset {value:#x}")

    removed_text_symbols = {
        "BaseSlot__12IwamizuThunkFP7SetData",
        "PrimarySlot__19IwamizuThunkPrimaryFv",
    }
    for offset, symbol, name in symbols:
        if symbol[5] == text_index and (symbol[3] & 0xF) != 3:
            if name in removed_text_symbols:
                symbol[1] = 0
                symbol[2] = 0
                symbol[5] = 0
            else:
                symbol[1] = map_text_offset(symbol[1])
            struct.pack_into(">IIIBBH", data, offset, *symbol)

    base_slot_index = symbols_by_name["BaseSlot__12IwamizuThunkFP7SetData"]
    retail_slot_index = symbols_by_name[
        "EditOnChange__14TObjS01IwamizuFP13SETDATA_PARAM"
    ]
    _, rela_text = by_name[".rela.text"]
    text_relocations = []
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        old_symbol = relocation[1] >> 8
        try:
            relocation[0] = map_text_offset(relocation[0])
        except ValueError:
            continue
        if old_symbol == base_slot_index:
            relocation[1] = (retail_slot_index << 8) | (relocation[1] & 0xFF)
        text_relocations.append(relocation)
    text_relocations.sort(key=lambda item: item[0])
    old_rela_text_size = rela_text[5]
    new_rela_text_size = len(text_relocations) * rela_text[9]
    for offset, relocation in zip(
        range(rela_text[4], rela_text[4] + new_rela_text_size, rela_text[9]),
        text_relocations,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)
    data[
        rela_text[4] + new_rela_text_size : rela_text[4] + old_rela_text_size
    ] = b"\0" * (old_rela_text_size - new_rela_text_size)
    rela_text[5] = new_rela_text_size

    data_index, data_section = by_name[".data"]
    id_offset, id_symbol, _ = symbols[symbols_by_name["IwamizuId"]]
    if id_symbol[1] != 0x10E or id_symbol[2] != 2:
        raise SystemExit("unexpected compiler IwamizuId atom")
    id_value = bytes(data[data_section[4] + 0x10E : data_section[4] + 0x110])
    id_symbol[1] = 0x110
    struct.pack_into(">IIIBBH", data, id_offset, *id_symbol)

    model_index = symbols_by_name["__vt__12IwamizuThunk"]
    model_offset, model_symbol, _ = symbols[model_index]
    if model_symbol[1] != 0x110 or model_symbol[2] != 0x1C:
        raise SystemExit("unexpected Iwamizu ABI-model vtable")
    data[data_section[4] + 0x110 : data_section[4] + data_section[5]] = b"\0" * (
        data_section[5] - 0x110
    )
    data[data_section[4] + 0x10E : data_section[4] + 0x110] = b"\0\0"
    data[data_section[4] + 0x110 : data_section[4] + 0x112] = id_value
    data_section[5] = 0x114
    model_symbol[1] = 0
    model_symbol[2] = 0
    model_symbol[5] = 0
    struct.pack_into(">IIIBBH", data, model_offset, *model_symbol)

    _, rela_data = by_name[".rela.data"]
    data_relocations = []
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        if relocation[0] < 0x110:
            data_relocations.append(relocation)
    old_rela_data_size = rela_data[5]
    new_rela_data_size = len(data_relocations) * rela_data[9]
    for offset, relocation in zip(
        range(rela_data[4], rela_data[4] + new_rela_data_size, rela_data[9]),
        data_relocations,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)
    data[
        rela_data[4] + new_rela_data_size : rela_data[4] + old_rela_data_size
    ] = b"\0" * (old_rela_data_size - new_rela_data_size)
    rela_data[5] = new_rela_data_size

    rodata_index, rodata = by_name[".rodata"]
    old_rodata = bytes(data[rodata[4] : rodata[4] + rodata[5]])
    new_rodata = (
        old_rodata[0x08:0x18]
        + old_rodata[0x20:0x24]
        + old_rodata[0x00:0x08]
        + old_rodata[0x20:0x28]
    )
    if len(new_rodata) != 0x24:
        raise SystemExit("unexpected rebuilt rodata size")
    data[rodata[4] : rodata[4] + len(new_rodata)] = new_rodata
    data[rodata[4] + len(new_rodata) : rodata[4] + rodata[5]] = b"\0" * (
        rodata[5] - len(new_rodata)
    )
    rodata[5] = len(new_rodata)
    rodata[8] = 4

    rodata_offsets = {
        "IwamizuZeroVector": 0x00,
        "IwamizuMinimum": 0x0C,
        "IwamizuIntBias": 0x14,
        "IwamizuZero": 0x1C,
        "IwamizuOne": 0x20,
    }
    for name, value in rodata_offsets.items():
        offset, symbol, _ = symbols[symbols_by_name[name]]
        symbol[1] = value
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    literal_index = symbols_by_name["@66"]
    bias_index = symbols_by_name["IwamizuIntBias"]
    for _, section in by_name.values():
        if section[1] != 4 or section[9] != 12:
            continue
        for offset in range(section[4], section[4] + section[5], section[9]):
            relocation = list(struct.unpack_from(">IIi", data, offset))
            if relocation[1] >> 8 == literal_index:
                relocation[1] = (bias_index << 8) | (relocation[1] & 0xFF)
                struct.pack_into(">IIi", data, offset, *relocation)

    literal_offset, literal_symbol, _ = symbols[literal_index]
    literal_symbol[1] = 0
    literal_symbol[2] = 0
    literal_symbol[5] = 0
    struct.pack_into(">IIIBBH", data, literal_offset, *literal_symbol)

    thunk_offset, thunk_symbol, thunk_name = symbols[
        symbols_by_name["@40@BaseSlot__12IwamizuThunkFP7SetData"]
    ]
    replacement_name = b"fn_3_82320\0"
    if len(replacement_name) > len(thunk_name) + 1:
        raise SystemExit("replacement thunk name does not fit string-table atom")
    name_offset = strtab[4] + thunk_symbol[0]
    data[name_offset : name_offset + len(thunk_name) + 1] = replacement_name.ljust(
        len(thunk_name) + 1, b"\0"
    )

    bss_index, bss = by_name[".bss"]
    bss[8] = 4
    _, comment = by_name[".comment"]
    struct.pack_into(
        ">I",
        data,
        comment[4] + 0x2C + symbols_by_name["IwamizuZeroVector"] * 8,
        4,
    )
    struct.pack_into(">I", data, comment[4] + 0x2C + symbols_by_name["IwamizuId"] * 8, 4)
    for index, (_, symbol, _) in enumerate(symbols):
        if (symbol[3] & 0xF) == 3 and symbol[5] in (rodata_index, bss_index):
            struct.pack_into(">I", data, comment[4] + 0x2C + index * 8, 4)

    for _, symbol, _ in symbols:
        if (symbol[3] & 0xF) == 3 and symbol[5] in (
            text_index,
            rodata_index,
            data_index,
        ):
            symbol[2] = sections[symbol[5]][5]

    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
    for offset, symbol, _ in symbols:
        struct.pack_into(">IIIBBH", data, offset, *symbol)
    args.object.write_bytes(data)
    args.stamp.touch()


if __name__ == "__main__":
    main()
