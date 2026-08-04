#!/usr/bin/env python3

"""Restore the retail o_invoke_colli.cpp ABI atom layout.

The isolated multiple-inheritance model makes CodeWarrior emit the retail
adjustor thunk.  It also emits an unused model implementation and vtable, and
the source-level loop leaves two unreachable instructions after
SetCommuicateFlag.  This pass keeps every compiler-emitted retail instruction,
retargets the compiler thunk to the retail callback, removes only those
compiler-model/unreachable atoms, and restores retail atom ordering.
"""

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
    thunk_name = "@40@BaseSlot__11InvokeThunkFv"
    _, thunk, _ = symbols[symbols_by_name[thunk_name]]
    _, set_flag, _ = symbols[
        symbols_by_name["SetCommuicateFlag__18TObjSetInvokeColliFUci"]
    ]
    _, check_hit, _ = symbols[
        symbols_by_name["CheckHitPlayer__18TObjSetInvokeColliFv"]
    ]
    _, register, _ = symbols[symbols_by_name["invokeCollisionRegister"]]
    if (thunk[1], thunk[2], set_flag[1], set_flag[2], check_hit[1]) != (
        0x934,
        8,
        0x20,
        0x68,
        0x88,
    ):
        raise SystemExit("unexpected compiler text atom layout")

    old_text_size = text[5]
    thunk_start = thunk[1]
    set_start = set_flag[1]
    check_start = check_hit[1]
    retail_end = register[1] + register[2]
    new_text = (
        data[text[4] + thunk_start : text[4] + thunk_start + thunk[2]]
        + data[text[4] + set_start : text[4] + set_start + 0x60]
        + data[text[4] + check_start : text[4] + retail_end]
    )
    if len(new_text) != 0x914:
        raise SystemExit(f"retail text is {len(new_text):#x}, expected 0x914")
    data[text[4] : text[4] + len(new_text)] = new_text
    data[text[4] + len(new_text) : text[4] + old_text_size] = b"\0" * (
        old_text_size - len(new_text)
    )
    text[5] = len(new_text)

    def map_text_offset(value: int) -> int:
        if thunk_start <= value < thunk_start + thunk[2]:
            return value - thunk_start
        if set_start <= value < set_start + 0x60:
            return 8 + value - set_start
        if check_start <= value < retail_end:
            return 0x68 + value - check_start
        if value == retail_end:
            return 0x914
        raise ValueError(f"unmapped text offset {value:#x}")

    removed_text_symbols = {"BaseSlot__11InvokeThunkFv"}
    for offset, symbol, name in symbols:
        if symbol[5] == text_index and (symbol[3] & 0xF) != 3:
            if name in removed_text_symbols:
                symbol[1] = symbol[2] = symbol[5] = 0
            else:
                try:
                    symbol[1] = map_text_offset(symbol[1])
                except ValueError:
                    symbol[1] = symbol[2] = symbol[5] = 0
            if name == "SetCommuicateFlag__18TObjSetInvokeColliFUci":
                symbol[2] = 0x60
            struct.pack_into(">IIIBBH", data, offset, *symbol)

    base_slot_index = symbols_by_name["BaseSlot__11InvokeThunkFv"]
    callback_index = symbols_by_name["fn_3_4EE40"]
    _, rela_text = by_name[".rela.text"]
    text_relocations = []
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        try:
            relocation[0] = map_text_offset(relocation[0])
        except ValueError:
            continue
        if relocation[1] >> 8 == base_slot_index:
            relocation[1] = (callback_index << 8) | (relocation[1] & 0xFF)
        text_relocations.append(relocation)
    text_relocations.sort(key=lambda item: item[0])
    old_size = rela_text[5]
    rela_text[5] = len(text_relocations) * rela_text[9]
    for offset, relocation in zip(
        range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]),
        text_relocations,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)
    data[rela_text[4] + rela_text[5] : rela_text[4] + old_size] = b"\0" * (
        old_size - rela_text[5]
    )

    data_index, data_section = by_name[".data"]
    model_index = symbols_by_name["__vt__11InvokeThunk"]
    model_offset, model_symbol, _ = symbols[model_index]
    if model_symbol[1] != 0x15C:
        raise SystemExit("unexpected compiler ABI-model vtable")
    data[data_section[4] + 0x15C : data_section[4] + data_section[5]] = b"\0" * (
        data_section[5] - 0x15C
    )
    data_section[5] = 0x15C
    data_section[8] = 4
    model_symbol[1] = model_symbol[2] = model_symbol[5] = 0
    struct.pack_into(">IIIBBH", data, model_offset, *model_symbol)

    _, rela_data = by_name[".rela.data"]
    data_relocations = []
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        if relocation[0] < 0x15C:
            data_relocations.append(relocation)
    old_size = rela_data[5]
    rela_data[5] = len(data_relocations) * rela_data[9]
    for offset, relocation in zip(
        range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]),
        data_relocations,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)
    data[rela_data[4] + rela_data[5] : rela_data[4] + old_size] = b"\0" * (
        old_size - rela_data[5]
    )

    thunk_offset, thunk_symbol, old_name = symbols[symbols_by_name[thunk_name]]
    replacement = b"InvokeEditThunk\0"
    name_offset = strtab[4] + thunk_symbol[0]
    data[name_offset : name_offset + len(old_name) + 1] = replacement.ljust(
        len(old_name) + 1, b"\0"
    )

    _, bss = by_name[".bss"]
    bss[8] = 4
    _, comment = by_name[".comment"]
    for index, (_, symbol, _) in enumerate(symbols):
        if symbol[5] in (data_index, by_name[".bss"][0]):
            struct.pack_into(">I", data, comment[4] + 0x2C + index * 8, 4)
    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
    for offset, symbol, _ in symbols:
        struct.pack_into(">IIIBBH", data, offset, *symbol)
    args.object.write_bytes(data)
    args.stamp.touch()


if __name__ == "__main__":
    main()
