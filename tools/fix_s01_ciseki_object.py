#!/usr/bin/env python3

"""Restore the retail o_s01_ciseki.cpp atom layout.

The isolated ABI model used to make CodeWarrior emit the retail multiple-
inheritance adjustor also emits an unused 28-byte model vtable.  Remove that
compiler-only table, point the real vtable at the generated adjustor, and move
complete compiler-emitted function atoms into their retail order.  No
instruction or owned data byte is changed.
"""

import argparse
import os
import struct
import subprocess
import tempfile
from pathlib import Path


TEXT_ORDER = (
    "continueObjS01Ciseki",
    "SetCommuicateFlag__13TObjS01CisekiFUciPUsUs",
    "SetCommuicateFlag__13TObjS01CisekiFUci",
    "Exec__13TObjS01CisekiFv",
    "EditOnChange__11CisekiThunkFP13SETDATA_PARAM",
    "__dt__13TObjS01CisekiFv",
    "__ct__13TObjS01CisekiFP7TObject",
    "startObj_S01_Ciseki",
    "__sinit_o_s01_ciseki_cpp",
    "@40@EditOnChange__11CisekiThunkFP13SETDATA_PARAM",
    "endObjS01Ciseki",
    "MotionNoop__13TObjS01CisekiFv",
    "TDisp__13TObjS01CisekiFv",
)

SYMBOL_RENAMES = {
    "EditOnChange__11CisekiThunkFP13SETDATA_PARAM": (
        "EditOnChange__13TObjS01CisekiFP13SETDATA_PARAM"
    ),
    "@40@EditOnChange__11CisekiThunkFP13SETDATA_PARAM": (
        "@40@EditOnChange__13TObjS01CisekiFP13SETDATA_PARAM"
    ),
}


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
    text_relocations = []
    for offset in range(
        rela_text[4], rela_text[4] + rela_text[5], rela_text[9]
    ):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        relocation[0] = map_text_offset(relocation[0])
        text_relocations.append(relocation)
    text_relocations.sort(key=lambda item: item[0])
    for offset, relocation in zip(
        range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]),
        text_relocations,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)

    data_index, data_section = by_name[".data"]
    model_vtable_index = symbols_by_name["__vt__11CisekiThunk"]
    model_symbol_offset, model_symbol, _ = symbols[model_vtable_index]
    model_start, model_size = model_symbol[1], model_symbol[2]
    if model_start != 0xA8 or model_size != 0x1C:
        raise SystemExit(
            f"unexpected compiler-only vtable at {model_start:#x}, size {model_size:#x}"
        )
    if model_start + model_size != data_section[5]:
        raise SystemExit("compiler-only vtable is not the final data atom")

    thunk_index = symbols_by_name[
        "@40@EditOnChange__11CisekiThunkFP13SETDATA_PARAM"
    ]
    adjustor_index = symbols_by_name[
        "AdjustorEditOnChange__11CisekiThunkFP13SETDATA_PARAM"
    ]
    _, rela_data = by_name[".rela.data"]
    data_relocations = []
    for offset in range(
        rela_data[4], rela_data[4] + rela_data[5], rela_data[9]
    ):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        if relocation[0] >= model_start:
            continue
        if relocation[1] >> 8 == adjustor_index:
            relocation[1] = (thunk_index << 8) | (relocation[1] & 0xFF)
        data_relocations.append(relocation)
    old_rela_size = rela_data[5]
    new_rela_size = len(data_relocations) * rela_data[9]
    for offset, relocation in zip(
        range(rela_data[4], rela_data[4] + new_rela_size, rela_data[9]),
        data_relocations,
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
    struct.pack_into(">IIIBBH", data, model_symbol_offset, *model_symbol)

    literal_offset, literal_symbol, _ = symbols[symbols_by_name["@105"]]
    padding_offset, padding_symbol, _ = symbols[symbols_by_name["cisekiPadding"]]
    rodata_index, rodata_section = by_name[".rodata"]
    if (
        literal_symbol[5] != rodata_index
        or literal_symbol[1] != 4
        or padding_symbol[5] != rodata_index
        or padding_symbol[1] != 0
        or rodata_section[5] != 8
    ):
        raise SystemExit("unexpected zero-constant pool layout")
    literal_symbol[1] = 0
    literal_symbol[2] = 8
    padding_symbol[1] = 4
    struct.pack_into(">IIIBBH", data, literal_offset, *literal_symbol)
    struct.pack_into(">IIIBBH", data, padding_offset, *padding_symbol)

    bss_index, bss_section = by_name[".bss"]
    if bss_section[8] != 8:
        raise SystemExit(f"unexpected BSS alignment {bss_section[8]}")
    bss_section[8] = 4

    # MWLD reads the CodeWarrior section-symbol preference from .comment
    # instead of sh_addralign.  Keep that compiler metadata in sync so this
    # four-byte-aligned retail BSS atom remains at 0x113C when linked.
    _, comment = by_name[".comment"]
    bss_section_symbol = next(
        index
        for index, (_, symbol, _) in enumerate(symbols)
        if (symbol[3] & 0xF) == 3 and symbol[5] == bss_index
    )
    struct.pack_into(">I", data, comment[4] + 0x2C + bss_section_symbol * 8, 4)

    for offset, symbol, _ in symbols:
        if (symbol[3] & 0xF) == 3 and symbol[5] in (text_index, data_index):
            symbol[2] = sections[symbol[5]][5]
            struct.pack_into(">IIIBBH", data, offset, *symbol)

    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
    args.object.write_bytes(data)

    with tempfile.NamedTemporaryFile(
        dir=args.object.parent, delete=False, suffix=".o"
    ) as temporary:
        output = Path(temporary.name)
    try:
        command = [str(args.objcopy)]
        command.extend(
            [
                "--strip-symbol",
                "AdjustorEditOnChange__11CisekiThunkFP13SETDATA_PARAM",
                "--strip-symbol",
                "PrimarySlot__18CisekiThunkPrimaryFv",
                "--strip-symbol",
                "__vt__11CisekiThunk",
                "--strip-symbol",
                "cisekiPadding",
            ]
        )
        command.extend(["--redefine-sym", "@105=lbl_3_rodata_1340"])
        command.extend(["--globalize-symbol", "lbl_3_rodata_1340"])
        for source, target in SYMBOL_RENAMES.items():
            command.extend(["--redefine-sym", f"{source}={target}"])
        command.extend([str(args.object), str(output)])
        subprocess.run(command, check=True)
        os.chmod(output, args.object.stat().st_mode)
        output.replace(args.object)
    finally:
        output.unlink(missing_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
