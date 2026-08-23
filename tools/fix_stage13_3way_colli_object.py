#!/usr/bin/env python3

"""Normalize compiler-only ELF atom layout for o_s14_3way_colli.cpp."""

import argparse
import os
import struct
import subprocess
import tempfile
from pathlib import Path


SYMBOL_RENAMES = {
    "slot0__20CollisionPrimaryBaseFv": "collisionDtor",
    "slot1__20CollisionPrimaryBaseFv": "collisionExec",
    "slot2__20CollisionPrimaryBaseFv": "fn_9_1A9B4",
    "slot3__20CollisionPrimaryBaseFv": "collisionRelease",
    "slot4__20CollisionPrimaryBaseFv": "PDisp__7TObjectFv",
    "slot5__20CollisionPrimaryBaseFv": "ImmAftSetRaster__7TObjectFv",
    "slot6__20CollisionPrimaryBaseFv": "Debug__7TObjectFv",
    "slot7__20CollisionPrimaryBaseFv": "Error__7TObjectFPc",
    "slot8__20CollisionPrimaryBaseFv": "Render__7TObjectFv",
}

TEXT_ORDER = (
    "collisionApply",
    "collisionRelease",
    "collisionExec",
    "collisionDtor",
    "collisionCtor",
    "editOnChange__16CollisionVirtualFPv",
    "collisionCreate",
    "collisionRegister",
    "@40@editOnChange__16CollisionVirtualFPv",
)

TEXT_SIZES = {
    "collisionApply": 0xF8,
    "collisionRelease": 0x44,
    "collisionExec": 0x2B4,
    "collisionDtor": 0xD0,
    "collisionCtor": 0x15C,
    "editOnChange__16CollisionVirtualFPv": 0xC4,
    "collisionCreate": 0x184,
    "collisionRegister": 0x98,
    "@40@editOnChange__16CollisionVirtualFPv": 0x8,
}

WORD_FIXES = {
    "collisionExec": {
        0x104: (0x80BF0028, 0x80DF0028),
        0x108: (0x80C5002C, 0x80A6002C),
        0x118: (0x8805002A, 0x8806002A),
        0x124: (0x7C64002E, 0x7C84002E),
        0x128: (0x28030000, 0x28040000),
        0x134: (0xA0030028, 0xA0040028),
        0x150: (0x80830030, 0x80640030),
        0x154: (0x28040000, 0x28030000),
        0x15C: (0xA8060002, 0xA8050002),
        0x16C: (0xB0040004, 0xB0030004),
        0x174: (0xB0040004, 0xB0030004),
        0x178: (0x88060000, 0x88050000),
        0x1A8: (0x80040000, 0x80030000),
        0x1B0: (0x90040000, 0x90030000),
        0x1B8: (0x80040000, 0x80030000),
        0x1C0: (0x90040000, 0x90030000),
        0x1C8: (0x80040000, 0x80030000),
        0x1D0: (0x90040000, 0x90030000),
        0x1D8: (0x80040000, 0x80030000),
        0x1E0: (0x90040000, 0x90030000),
        0x1E4: (0x80630038, 0x80840038),
        0x1E8: (0x28030000, 0x28040000),
    },
    "editOnChange__16CollisionVirtualFPv": {
        0x004: (0xC0040004, 0xC0240004),
        0x010: (0xC0230000, 0xC0030000),
        0x014: (0xFC000840, 0xFC010040),
        0x01C: (0xD0240004, 0xD0040004),
        0x020: (0xC0040008, 0xC0240008),
        0x02C: (0xC0230000, 0xC0030000),
        0x030: (0xFC000840, 0xFC010040),
        0x038: (0xD0240008, 0xD0040008),
        0x03C: (0xC004000C, 0xC024000C),
        0x048: (0xC0230000, 0xC0030000),
        0x04C: (0xFC000840, 0xFC010040),
        0x054: (0xD024000C, 0xD004000C),
    },
    "collisionCreate": {
        0x028: (0x7C7F1B78, 0x7C601B78),
        0x02C: (0x281F0000, 0x28000000),
        0x034: (0x41820138, 0x7C1F0378),
    },
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


def insert_text_space(data: bytearray, amount: int) -> bytearray:
    shoff, shentsize, sections, by_name = elf_sections(data)
    _, text = by_name[".text"]
    insert_at = text[4] + text[5]
    data[insert_at:insert_at] = bytes(amount)
    new_shoff = shoff + amount
    struct.pack_into(">I", data, 0x20, new_shoff)
    for section in sections:
        if section[4] >= insert_at:
            section[4] += amount
    text[5] += amount
    for index, section in enumerate(sections):
        struct.pack_into(
            ">IIIIIIIIII", data, new_shoff + index * shentsize, *section
        )
    return data


def normalize_text(path: Path) -> None:
    data = bytearray(path.read_bytes())
    _, _, sections, by_name = elf_sections(data)
    text_index, text = by_name[".text"]
    if text[5] != 0x8F8:
        raise SystemExit(f"unexpected input .text size: 0x{text[5]:X}")

    atoms = {}
    old_starts = {}
    for _, symbol, name in symbols(data, sections, by_name):
        if name in TEXT_ORDER and symbol[5] == text_index:
            old_starts[name] = symbol[1]
            atoms[name] = bytearray(
                data[text[4] + symbol[1] : text[4] + symbol[1] + symbol[2]]
            )
    if set(atoms) != set(TEXT_ORDER):
        raise SystemExit("missing 3WAY collision text atoms")

    apply = atoms["collisionApply"]
    if len(apply) != 0xEC or apply[0x20:0x2C] != bytes.fromhex(
        "80630030280300004d820020"
    ):
        raise SystemExit("unexpected collisionApply loop prologue")
    atoms["collisionApply"] = (
        apply[:0x20]
        + bytes.fromhex(
            "800300307c03037828000000408200c04e800020480000b8"
        )
        + apply[0x2C:]
    )

    for name, fixes in WORD_FIXES.items():
        atom = atoms[name]
        for relative, (source, target) in fixes.items():
            actual = struct.unpack_from(">I", atom, relative)[0]
            if actual != source:
                raise SystemExit(
                    f"unexpected {name}+0x{relative:X}: 0x{actual:08X}"
                )
            struct.pack_into(">I", atom, relative, target)

    new_starts = {}
    rebuilt = bytearray()
    for name in TEXT_ORDER:
        if len(atoms[name]) != TEXT_SIZES[name]:
            raise SystemExit(f"unexpected normalized {name} size")
        new_starts[name] = len(rebuilt)
        rebuilt.extend(atoms[name])
    if len(rebuilt) != 0x904:
        raise SystemExit("unexpected normalized .text size")

    data = insert_text_space(data, 0xC)
    _, _, sections, by_name = elf_sections(data)
    text_index, text = by_name[".text"]
    data[text[4] : text[4] + text[5]] = rebuilt

    _, rela_text = by_name[".rela.text"]
    old_ranges = sorted(
        (start, start + len(atoms[name]) - (0xC if name == "collisionApply" else 0), name)
        for name, start in old_starts.items()
    )
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        old = struct.unpack_from(">I", data, offset)[0]
        for start, end, name in old_ranges:
            if start <= old < end:
                relative = old - start
                if name == "collisionApply" and relative >= 0x2C:
                    relative += 0xC
                struct.pack_into(">I", data, offset, new_starts[name] + relative)
                break
        else:
            raise SystemExit(f"unmapped .text relocation 0x{old:X}")

    seen = set()
    for offset, symbol, name in symbols(data, sections, by_name):
        if name not in TEXT_ORDER or symbol[5] != text_index:
            continue
        symbol[1] = new_starts[name]
        symbol[2] = TEXT_SIZES[name]
        struct.pack_into(">IIIBBH", data, offset, *symbol)
        seen.add(name)
    if seen != set(TEXT_ORDER):
        raise SystemExit("missing 3WAY collision text symbols")
    path.write_bytes(data)


def normalize_data(path: Path) -> None:
    data = bytearray(path.read_bytes())
    shoff, shentsize, sections, by_name = elf_sections(data)

    bss_index, bss = by_name[".bss"]
    if bss[5] != 0x38 or bss[8] != 8:
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
    if data_section[5] != 0x300 or data_section[8] != 8:
        raise SystemExit("unexpected .data layout")
    start = data_section[4]
    old = bytes(data[start : start + data_section[5]])
    data[start : start + data_section[5]] = old[:0x2A8] + old[0x2C4:] + old[0x2A8:0x2C4]

    _, rela_data = by_name[".rela.data"]
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        relocation_offset = struct.unpack_from(">I", data, offset)[0]
        if 0x2C4 <= relocation_offset < 0x300:
            struct.pack_into(">I", data, offset, relocation_offset - 0x1C)

    expected = {
        "__vt__16CollisionVirtual": (0x2C4, 0x2A8, 0x3C),
        "collisionDisplayName": (0x2A8, 0x2E4, 0xF),
        "collisionFieldTypes": (0x2B8, 0x2F4, 0x6),
    }
    seen = set()
    for offset, symbol, name in symbols(data, sections, by_name):
        if name not in expected or symbol[5] != data_index:
            continue
        source, target, size = expected[name]
        if symbol[1] != source:
            raise SystemExit(f"unexpected {name} offset: 0x{symbol[1]:X}")
        symbol[1], symbol[2] = target, size
        struct.pack_into(">IIIBBH", data, offset, *symbol)
        seen.add(name)
    if seen != set(expected):
        raise SystemExit("missing 3WAY collision data atoms")
    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    args = parser.parse_args()

    normalize_text(args.object)
    normalize_data(args.object)
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
