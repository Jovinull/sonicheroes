#!/usr/bin/env python3

"""Normalize compiler-only ELF details for o_s13_antenna.cpp."""

import argparse
import os
import struct
import subprocess
import tempfile
from pathlib import Path


SYMBOL_RENAMES = {
    "slot0__18AntennaPrimaryBaseFv": "antennaDtor",
    "slot1__18AntennaPrimaryBaseFv": "antennaExec",
    "slot2__18AntennaPrimaryBaseFv": "fn_9_1A9B4",
    "slot3__18AntennaPrimaryBaseFv": "objDefaultTDisp",
    "slot4__18AntennaPrimaryBaseFv": "PDisp__7TObjectFv",
    "slot5__18AntennaPrimaryBaseFv": "ImmAftSetRaster__7TObjectFv",
    "slot6__18AntennaPrimaryBaseFv": "Debug__7TObjectFv",
    "slot7__18AntennaPrimaryBaseFv": "Error__7TObjectFPc",
    "slot8__18AntennaPrimaryBaseFv": "Render__7TObjectFv",
    "@59": "antennaIntegerBias",
}


FACTORY_REGISTER_WORDS = {
    0x030: (0x7C7F1B78, 0x7C601B78),
    0x034: (0x281F0000, 0x28000000),
    0x03C: (0x418201A4, 0x7C1E0378),
    0x050: (0x387F0028, 0x387E0028),
    0x058: (0x387F0030, 0x387E0030),
    0x068: (0x907F0018, 0x907E0018),
    0x070: (0x901F002C, 0x901E002C),
    0x080: (0x901F0000, 0x901E0000),
    0x088: (0xB01F001E, 0xB01E001E),
    0x098: (0xD01F00B8, 0xD01E00B8),
    0x0A8: (0x38BF00BC, 0x38BE00BC),
    0x0B4: (0x807F00BC, 0x807E00BC),
    0x0CC: (0x807F00BC, 0x807E00BC),
    0x0D0: (0x83C30004, 0x83E30004),
    0x0D4: (0x807F0028, 0x807E0028),
    0x0E4: (0x807F0028, 0x807E0028),
    0x100: (0x387E0010, 0x387F0010),
    0x118: (0x7FC3F378, 0x7FE3FB78),
    0x120: (0x807F0028, 0x807E0028),
    0x130: (0x807F0028, 0x807E0028),
    0x14C: (0x387E0010, 0x387F0010),
    0x164: (0x7FC3F378, 0x7FE3FB78),
    0x16C: (0x807F0028, 0x807E0028),
    0x17C: (0x807F0028, 0x807E0028),
    0x198: (0x387E0010, 0x387F0010),
    0x1B0: (0x7FC3F378, 0x7FE3FB78),
    0x1B8: (0x7FC3F378, 0x7FE3FB78),
    0x1BC: (0x809F0028, 0x809E0028),
    0x1C8: (0x387F0030, 0x387E0030),
}


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def elf_sections(data: bytearray):
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
    return shoff, shentsize, sections, by_name


def symbols(data, sections, by_name):
    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        yield offset, symbol, name


def normalize_factory_registers(path: Path) -> None:
    data = bytearray(path.read_bytes())
    _, _, sections, by_name = elf_sections(data)
    text_index, text_section = by_name[".text"]
    factory = None
    for _, symbol, name in symbols(data, sections, by_name):
        if name == "antennaCreate" and symbol[5] == text_index:
            factory = symbol
            break
    if factory is None or factory[2] != 0x200:
        raise SystemExit("unexpected antennaCreate symbol")

    start = text_section[4] + factory[1]
    for relative, (source, target) in FACTORY_REGISTER_WORDS.items():
        offset = start + relative
        actual = struct.unpack_from(">I", data, offset)[0]
        if actual != source:
            raise SystemExit(
                f"unexpected antennaCreate+0x{relative:X}: 0x{actual:08X}"
            )
        struct.pack_into(">I", data, offset, target)
    path.write_bytes(data)


def reorder_text_atoms(path: Path) -> None:
    data = bytearray(path.read_bytes())
    _, _, sections, by_name = elf_sections(data)
    text_index, text_section = by_name[".text"]
    if text_section[5] != 0xAC4:
        raise SystemExit(f"unexpected .text size: 0x{text_section[5]:X}")
    start = text_section[4]
    old = bytes(data[start : start + text_section[5]])
    if old[0x1B8:0x1BC] != bytes.fromhex("4e800020"):
        raise SystemExit("unexpected editOnChange atom")
    data[start : start + text_section[5]] = (
        old[:0x1B8] + old[0x1BC:0x4AC] + old[0x1B8:0x1BC] + old[0x4AC:]
    )

    _, rela_text = by_name[".rela.text"]
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        relocation_offset = struct.unpack_from(">I", data, offset)[0]
        if 0x1BC <= relocation_offset < 0x4AC:
            struct.pack_into(">I", data, offset, relocation_offset - 4)

    saw_edit = False
    saw_exec = False
    for offset, symbol, name in symbols(data, sections, by_name):
        if symbol[5] != text_index:
            continue
        if name == "editOnChange__14AntennaVirtualFPv":
            if symbol[1] != 0x1B8 or symbol[2] != 4:
                raise SystemExit("unexpected editOnChange symbol")
            symbol[1] = 0x4A8
            saw_edit = True
        elif 0x1BC <= symbol[1] < 0x4AC:
            symbol[1] -= 4
            saw_exec |= name == "antennaExec" and symbol[2] == 0x2F0
        struct.pack_into(">IIIBBH", data, offset, *symbol)
    if not saw_edit or not saw_exec:
        raise SystemExit("missing Antenna text atoms")
    path.write_bytes(data)


def reorder_rodata_atoms(path: Path) -> None:
    data = bytearray(path.read_bytes())
    _, _, sections, by_name = elf_sections(data)
    rodata_index, rodata = by_name[".rodata"]
    if rodata[5] != 0x2C:
        raise SystemExit(f"unexpected .rodata size: 0x{rodata[5]:X}")
    start = rodata[4]
    old = bytes(data[start : start + rodata[5]])
    data[start : start + rodata[5]] = old[0x8:0x18] + old[0:0x8] + old[0x18:]

    expected = {
        "antennaOne": (0x08, 0x00),
        "antennaFrameStep": (0x0C, 0x04),
        "antennaFullTurn": (0x10, 0x08),
        "antennaRodataPad": (0x14, 0x0C),
        "@59": (0x00, 0x10),
    }
    seen = set()
    for offset, symbol, name in symbols(data, sections, by_name):
        if symbol[5] != rodata_index or name not in expected:
            continue
        source, target = expected[name]
        if symbol[1] != source:
            raise SystemExit(f"unexpected {name} offset: 0x{symbol[1]:X}")
        symbol[1] = target
        struct.pack_into(">IIIBBH", data, offset, *symbol)
        seen.add(name)
    if seen != set(expected):
        raise SystemExit("missing Antenna rodata atoms")
    path.write_bytes(data)


def reorder_data_atoms(path: Path) -> None:
    data = bytearray(path.read_bytes())
    shoff, shentsize, sections, by_name = elf_sections(data)

    bss_index, bss = by_name[".bss"]
    if bss[5] != 0x3C or bss[8] != 8:
        raise SystemExit("unexpected .bss layout")
    bss[8] = 4
    struct.pack_into(">IIIIIIIIII", data, shoff + bss_index * shentsize, *bss)
    _, comment = by_name[".comment"]
    for index, (_, symbol, _) in enumerate(symbols(data, sections, by_name)):
        if symbol[3] & 0xF == 3 and symbol[5] == bss_index:
            struct.pack_into(">I", data, comment[4] + 0x2C + index * 8, 4)
            break
    else:
        raise SystemExit("missing .bss section symbol")

    data_index, data_section = by_name[".data"]
    if data_section[5] != 0x108:
        raise SystemExit(f"unexpected .data size: 0x{data_section[5]:X}")
    if data_section[8] not in (4, 8):
        raise SystemExit("unexpected .data alignment")
    if data_section[8] == 4:
        data_section[8] = 8
        struct.pack_into(
            ">IIIIIIIIII", data, shoff + data_index * shentsize, *data_section
        )
        for index, (_, symbol, _) in enumerate(symbols(data, sections, by_name)):
            if symbol[3] & 0xF == 3 and symbol[5] == data_index:
                struct.pack_into(">I", data, comment[4] + 0x2C + index * 8, 8)
                break
        else:
            raise SystemExit("missing .data section symbol")
    start = data_section[4]
    old = bytes(data[start : start + data_section[5]])
    data[start : start + data_section[5]] = (
        old[:0xB8] + old[0xCC:0x108] + old[0xB8:0xCC]
    )

    _, rela_data = by_name[".rela.data"]
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        relocation_offset = struct.unpack_from(">I", data, offset)[0]
        if 0xCC <= relocation_offset < 0x108:
            struct.pack_into(">I", data, offset, relocation_offset - 0x14)

    saw_vtable = False
    saw_display = False
    for offset, symbol, name in symbols(data, sections, by_name):
        if symbol[5] != data_index:
            continue
        if name == "__vt__14AntennaVirtual":
            if symbol[1] != 0xCC or symbol[2] != 0x3C:
                raise SystemExit("unexpected Antenna vtable atom")
            symbol[1] = 0xB8
            saw_vtable = True
        elif name == "antennaDisplayName":
            if symbol[1] != 0xB8 or symbol[2] != 0x11:
                raise SystemExit("unexpected Antenna display-name atom")
            symbol[1] = 0xF4
            symbol[2] = 0x0D
            saw_display = True
        struct.pack_into(">IIIBBH", data, offset, *symbol)
    if not saw_vtable or not saw_display:
        raise SystemExit("missing Antenna data atoms")
    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    args = parser.parse_args()

    normalize_factory_registers(args.object)
    reorder_text_atoms(args.object)
    reorder_rodata_atoms(args.object)
    reorder_data_atoms(args.object)
    with tempfile.NamedTemporaryFile(
        dir=args.object.parent, delete=False, suffix=".o"
    ) as temporary:
        output = Path(temporary.name)
    try:
        command = [str(args.objcopy)]
        for source, target in SYMBOL_RENAMES.items():
            command.extend(("--redefine-sym", f"{source}={target}"))
        command.extend(("--globalize-symbol", "antennaIntegerBias"))
        command.extend((str(args.object), str(output)))
        subprocess.run(command, check=True)
        os.chmod(output, args.object.stat().st_mode)
        output.replace(args.object)
    finally:
        output.unlink(missing_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
