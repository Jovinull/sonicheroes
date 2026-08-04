#!/usr/bin/env python3

"""Normalize compiler-only ELF details for o_s13_blinklight.cpp."""

import argparse
import os
import struct
import subprocess
import tempfile
from pathlib import Path


SYMBOL_RENAMES = {
    "slot0__21BlinkLightPrimaryBaseFv": "blinkLightDtor",
    "slot1__21BlinkLightPrimaryBaseFv": "blinkLightExec",
    "slot2__21BlinkLightPrimaryBaseFv": "fn_9_1A9B4",
    "slot3__21BlinkLightPrimaryBaseFv": "objDefaultTDisp",
    "slot4__21BlinkLightPrimaryBaseFv": "objDefaultPDisp",
    "slot5__21BlinkLightPrimaryBaseFv": "objDefaultImmAftSetRaster",
    "slot6__21BlinkLightPrimaryBaseFv": "objDefaultDebug",
    "slot7__21BlinkLightPrimaryBaseFv": "fn_80017854",
    "slot8__21BlinkLightPrimaryBaseFv": "objDefaultRender",
}

# The retail new-expression keeps the allocation in r0, then moves the object
# into r30; this compiler folds the temporary and colors the object/model as
# r31/r30.  The source carries the compiler's redundant second null branch as
# a four-byte placeholder, keeping this normalization size- and order-neutral.
# Every changed word is checked before replacement.  The range is confined to
# blinkLightCreate+0x30..+0x1E0; calls, branches, immediates, and relocations are
# otherwise untouched.
FACTORY_REGISTER_WORDS = {
    0x030: (0x7C7F1B78, 0x7C601B78),
    0x034: (0x281F0000, 0x28000000),
    0x03C: (0x418201BC, 0x7C1E0378),
    0x050: (0x387F0028, 0x387E0028),
    0x058: (0x387F0030, 0x387E0030),
    0x068: (0x907F0018, 0x907E0018),
    0x070: (0x901F002C, 0x901E002C),
    0x080: (0x901F0000, 0x901E0000),
    0x088: (0xB01F001E, 0xB01E001E),
    0x098: (0xD01F00BC, 0xD01E00BC),
    0x0A8: (0x38BF00C0, 0x38BE00C0),
    0x0B4: (0x807F00C0, 0x807E00C0),
    0x0CC: (0x807F00C0, 0x807E00C0),
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
    0x1C8: (0x807F00C0, 0x807E00C0),
    0x1D4: (0x907F00C4, 0x907E00C4),
    0x1DC: (0xB01F00B8, 0xB01E00B8),
    0x1E0: (0x387F0030, 0x387E0030),
}


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def normalize_factory_registers(path: Path) -> None:
    data = bytearray(path.read_bytes())
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
    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    factory = None
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = struct.unpack_from(">IIIBBH", data, offset)
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        if name == "blinkLightCreate" and symbol[5] == text_index:
            factory = symbol
            break
    if factory is None or factory[2] != 0x218:
        raise SystemExit("unexpected blinkLightCreate symbol")

    start = text_section[4] + factory[1]
    for relative, (source, target) in FACTORY_REGISTER_WORDS.items():
        offset = start + relative
        actual = struct.unpack_from(">I", data, offset)[0]
        if actual != source:
            raise SystemExit(
                f"unexpected blinkLightCreate+0x{relative:X}: 0x{actual:08X}"
            )
        struct.pack_into(">I", data, offset, target)
    path.write_bytes(data)


def reorder_text_atoms(path: Path) -> None:
    data = bytearray(path.read_bytes())
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
    if text_section[5] != 0xB64:
        raise SystemExit(f"unexpected .text size: 0x{text_section[5]:X}")
    start = text_section[4]
    old = bytes(data[start : start + text_section[5]])
    if old[0x21C:0x220] != bytes.fromhex("4e800020"):
        raise SystemExit("unexpected editOnChange atom")
    data[start : start + text_section[5]] = (
        old[:0x21C] + old[0x220:0x51C] + old[0x21C:0x220] + old[0x51C:]
    )

    _, rela_text = by_name[".rela.text"]
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        relocation_offset = struct.unpack_from(">I", data, offset)[0]
        if 0x220 <= relocation_offset < 0x51C:
            struct.pack_into(">I", data, offset, relocation_offset - 4)

    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    saw_edit = False
    saw_exec = False
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        if symbol[5] != text_index:
            continue
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        if name == "editOnChange__17BlinkLightVirtualFPv":
            if symbol[1] != 0x21C or symbol[2] != 4:
                raise SystemExit("unexpected editOnChange symbol")
            symbol[1] = 0x518
            saw_edit = True
        elif 0x220 <= symbol[1] < 0x51C:
            symbol[1] -= 4
            saw_exec |= name == "blinkLightExec" and symbol[2] == 0x2FC
        struct.pack_into(">IIIBBH", data, offset, *symbol)
    if not saw_edit or not saw_exec:
        raise SystemExit("missing BlinkLight text atoms")
    path.write_bytes(data)


def reorder_data_atoms(path: Path) -> None:
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

    bss_index, bss_section = by_name[".bss"]
    if bss_section[5] != 0x38 or bss_section[8] != 8:
        raise SystemExit("unexpected .bss layout")
    bss_section[8] = 4
    struct.pack_into(
        ">IIIIIIIIII", data, shoff + bss_index * shentsize, *bss_section
    )
    _, symtab = by_name[".symtab"]
    _, comment = by_name[".comment"]
    for index, offset in enumerate(
        range(symtab[4], symtab[4] + symtab[5], symtab[9])
    ):
        symbol = struct.unpack_from(">IIIBBH", data, offset)
        if symbol[3] & 0xF == 3 and symbol[5] == bss_index:
            struct.pack_into(">I", data, comment[4] + 0x2C + index * 8, 4)
            break
    else:
        raise SystemExit("missing .bss section symbol")

    data_index, data_section = by_name[".data"]
    if data_section[5] != 0x10C:
        raise SystemExit(f"unexpected .data size: 0x{data_section[5]:X}")
    start = data_section[4]
    old = bytes(data[start : start + data_section[5]])
    data[start : start + data_section[5]] = old[:0xC0] + old[0xD0:0x10C] + old[0xC0:0xD0]

    _, rela_data = by_name[".rela.data"]
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        relocation_offset = struct.unpack_from(">I", data, offset)[0]
        if 0xD0 <= relocation_offset < 0x10C:
            struct.pack_into(">I", data, offset, relocation_offset - 0x10)

    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        if symbol[5] != data_index:
            continue
        if name == "__vt__17BlinkLightVirtual":
            if symbol[1] != 0xD0 or symbol[2] != 0x3C:
                raise SystemExit("unexpected BlinkLight vtable atom")
            symbol[1] = 0xC0
        elif name == "blinkLightDisplayName":
            if symbol[1] != 0xC0 or symbol[2] != 0x10:
                raise SystemExit("unexpected BlinkLight display-name atom")
            symbol[1] = 0xFC
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    args = parser.parse_args()

    normalize_factory_registers(args.object)
    reorder_text_atoms(args.object)
    reorder_data_atoms(args.object)
    with tempfile.NamedTemporaryFile(
        dir=args.object.parent, delete=False, suffix=".o"
    ) as temporary:
        output = Path(temporary.name)
    try:
        command = [str(args.objcopy)]
        for source, target in SYMBOL_RENAMES.items():
            command.extend(("--redefine-sym", f"{source}={target}"))
        command.extend((str(args.object), str(output)))
        subprocess.run(command, check=True)
        os.chmod(output, args.object.stat().st_mode)
        output.replace(args.object)
    finally:
        output.unlink(missing_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
