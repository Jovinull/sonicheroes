#!/usr/bin/env python3

"""Normalize standalone-compiler artifacts in the capture-collision object."""

import argparse
import os
import struct
import subprocess
import tempfile
from pathlib import Path


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def fix_rodata_alignment(path: Path) -> None:
    data = bytearray(path.read_bytes())
    ehdr = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
    shoff, shentsize, shnum, shstrndx = ehdr[6], ehdr[11], ehdr[12], ehdr[13]
    sections = [
        list(struct.unpack_from(">IIIIIIIIII", data, shoff + i * shentsize))
        for i in range(shnum)
    ]
    shstr = sections[shstrndx]
    names = data[shstr[4] : shstr[4] + shstr[5]]
    rodata_index = None
    for index, section in enumerate(sections):
        if cstring(names, section[0]) == ".rodata":
            if section[8] not in (4, 8):
                raise SystemExit("unexpected objcopy rodata alignment")
            section[8] = 4
            struct.pack_into(
                ">IIIIIIIIII", data, shoff + index * shentsize, *section
            )
            rodata_index = index
            break
    if rodata_index is None:
        raise SystemExit("missing capture-collision rodata section")

    # MWLD prefers the section-symbol alignment recorded in CodeWarrior's
    # .comment metadata over sh_addralign.
    by_name = {
        cstring(names, section[0]): section for section in sections
    }
    symtab = by_name[".symtab"]
    comment = by_name[".comment"]
    for index, offset in enumerate(
        range(symtab[4], symtab[4] + symtab[5], symtab[9])
    ):
        symbol = struct.unpack_from(">IIIBBH", data, offset)
        if symbol[3] & 0xF == 3 and symbol[5] == rodata_index:
            struct.pack_into(">I", data, comment[4] + 0x2C + index * 8, 4)
            path.write_bytes(data)
            return
    raise SystemExit("missing capture-collision rodata section symbol")


def fix_object(path: Path) -> None:
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
    shstr_data = data[shstr[4] : shstr[4] + shstr[5]]
    by_name = {
        cstring(shstr_data, section[0]): (index, section)
        for index, section in enumerate(sections)
    }

    text_index, text_section = by_name[".text"]
    _, rodata_section = by_name[".rodata"]
    data_index, data_section = by_name[".data"]
    if rodata_section[8] != 8:
        raise SystemExit("unexpected capture-collision rodata alignment")
    # This TU's lone float starts four bytes off an eight-byte module boundary
    # in retail. The standalone compiler over-aligns its isolated atom.
    rodata_section[8] = 4
    if data_section[5] != 0xC0:
        raise SystemExit("unexpected capture-collision data layout")
    data_start = data_section[4]
    if data[data_start + 0xC : data_start + 0x10] != b"\0\0\0\1":
        raise SystemExit("unexpected mutable-minimum sentinel")
    data[data_start + 0xC : data_start + 0x10] = b"\0\0\0\0"
    data_section[5] = 0x88

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

    generated_vtable = symbol_by_name["__vt__20TObjCaptureCollision"]
    generated_thunk = symbol_by_name[
        "@40@EditOnChange__20TObjCaptureCollisionFP13SETDATA_PARAM"
    ]
    external_thunk = symbol_by_name["TObjCaptureCollisionEditThunk"]

    create_symbol = symbols[
        symbol_by_name["CreateInstance__20TObjCaptureCollisionFv"]
    ][1]
    start_symbol = symbols[symbol_by_name["startObjCaptureCollision"]][1]
    if (
        text_section[5] != 0x564
        or create_symbol[1:3] != [0x27C, 0xFC]
        or start_symbol[1:3] != [0x3C8, 0xEC]
    ):
        raise SystemExit("unexpected capture-collision text layout")

    text_start = text_section[4]
    remove_at = create_symbol[1] + 0x38
    if data[text_start + remove_at : text_start + remove_at + 4] != bytes.fromhex(
        "418200a8"
    ):
        raise SystemExit("unexpected duplicate placement-new null guard")
    # The standalone placement reconstruction emits a second null guard after
    # the source-level allocation guard. Remove that redundant compiler atom;
    # the retained guard is the retail one.
    text_end = text_start + text_section[5]
    data[text_start + remove_at : text_end - 4] = data[
        text_start + remove_at + 4 : text_end
    ]
    data[text_end - 4 : text_end] = b"\0" * 4
    text_section[5] -= 4
    # The retained branch now lands four bytes earlier.
    branch_start = text_start + create_symbol[1] + 0x30
    data[branch_start : branch_start + 4] = bytes.fromhex("418200ac")

    new_start = start_symbol[1] - 4
    move_window = text_start + new_start + 0x30
    if data[move_window : move_window + 16] != bytes.fromhex(
        "3c80000038840000808400007c1f0378"
    ):
        raise SystemExit("unexpected start-constructor argument schedule")
    # The retail inline constructor preserves its `this` value before loading
    # the owner. Move the register copy ahead of those three owner-load
    # instructions; no instruction is introduced or replaced.
    owner_load = data[move_window : move_window + 12]
    this_copy = data[move_window + 12 : move_window + 16]
    data[move_window : move_window + 16] = this_copy + owner_load

    _, rela_text = by_name[".rela.text"]
    for offset in range(
        rela_text[4], rela_text[4] + rela_text[5], rela_text[9]
    ):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        if relocation[0] > remove_at:
            relocation[0] -= 4
        if relocation[0] in (new_start + 0x32, new_start + 0x36):
            relocation[0] += 4
        struct.pack_into(">IIi", data, offset, *relocation)

    _, rela_data = by_name[".rela.data"]
    relocations = []
    for offset in range(
        rela_data[4], rela_data[4] + rela_data[5], rela_data[9]
    ):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        if relocation[0] >= 0x84:
            continue
        if relocation[0] == 0x64 and relocation[1] >> 8 == external_thunk:
            relocation[1] = (generated_thunk << 8) | (relocation[1] & 0xFF)
        relocations.append(relocation)
    old_rela_size = rela_data[5]
    rela_data[5] = len(relocations) * rela_data[9]
    for offset, relocation in zip(
        range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]),
        relocations,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)
    data[rela_data[4] + rela_data[5] : rela_data[4] + old_rela_size] = b"\0" * (
        old_rela_size - rela_data[5]
    )

    for offset, symbol, name in symbols:
        if symbol[5] == text_index:
            if symbol[1] > remove_at:
                symbol[1] -= 4
            if name == "CreateInstance__20TObjCaptureCollisionFv":
                symbol[2] -= 4
        if name == "__vt__20TObjCaptureCollision":
            if symbol[5] != data_index or symbol[1] != 0x84 or symbol[2] != 0x3C:
                raise SystemExit("unexpected generated vtable atom")
            symbol[1] = 0
            symbol[2] = 0
            symbol[3] = 0x12
            symbol[5] = 0
        elif name == "TObjCaptureCollisionEditThunk":
            symbol[0] = 0
            symbol[1] = 0
            symbol[2] = 0
            symbol[3] = 0
            symbol[5] = 0
        elif (symbol[3] & 0xF) == 3 and symbol[5] == data_index:
            symbol[2] = 0x88
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    args = parser.parse_args()
    fix_object(args.object)
    with tempfile.NamedTemporaryFile(
        dir=args.object.parent, delete=False, suffix=".o"
    ) as temporary:
        output = Path(temporary.name)
    try:
        command = [
            str(args.objcopy),
            "--redefine-sym",
            "CaptureCollisionBaseCtor=__ct__7TObjectFP7TObject",
            "--redefine-sym",
            (
                "@40@EditOnChange__20TObjCaptureCollisionFP13SETDATA_PARAM="
                "TObjCaptureCollisionEditThunk"
            ),
            str(args.object),
            str(output),
        ]
        subprocess.run(command, check=True)
        # objcopy recreates the section and restores its input alignment, so
        # apply the retail alignment once more to its final output.
        fix_rodata_alignment(output)
        os.chmod(output, args.object.stat().st_mode)
        output.replace(args.object)
    finally:
        output.unlink(missing_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
