#!/usr/bin/env python3

"""Restore Memory.cpp's retail deferred-code order and split symbol names."""

import argparse
import shutil
import struct
import subprocess
from pathlib import Path


TEXT_ORDER = (
    "Free__9THeapCtrlFPv",
    "Malloc__9THeapCtrlFUi",
    "__dt__9THeapCtrlFv",
    "__ct__9THeapCtrlFUiUi",
    "__dl__9THeapCtrlFPv",
    "__nw__9THeapCtrlFUl",
)

EXCEPTION_ORDER = (
    "__dt__9THeapCtrlFv",
    "__ct__9THeapCtrlFUiUi",
    "__dl__9THeapCtrlFPv",
    "__nw__9THeapCtrlFUl",
)

RENAMES = {
    "Free__9THeapCtrlFPv": "fn_800189A4",
    "Malloc__9THeapCtrlFUi": "fn_80018A34",
    "__dt__9THeapCtrlFv": "fn_80018AB0",
    "__ct__9THeapCtrlFUiUi": "fn_80018B24",
    "__dl__9THeapCtrlFPv": "dtor_80018BB4",
    "__nw__9THeapCtrlFUl": "fn_80018BE0",
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

    symtab_index, symtab = by_name[".symtab"]
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
    intervals = []
    new_text = bytearray()
    for name in TEXT_ORDER:
        _, symbol, _ = symbols[symbols_by_name[name]]
        old_start, size = symbol[1], symbol[2]
        new_start = len(new_text)
        intervals.append((old_start, old_start + size, new_start))
        new_text += data[text[4] + old_start : text[4] + old_start + size]
    if len(new_text) != text[5]:
        raise SystemExit("function order does not cover .text")
    data[text[4] : text[4] + text[5]] = new_text

    def map_offset(value: int, ranges) -> int:
        for old_start, old_end, new_start in ranges:
            if old_start <= value < old_end:
                return new_start + value - old_start
        raise ValueError(f"unmapped offset {value:#x}")

    for offset, symbol, _ in symbols:
        if symbol[5] == text_index and (symbol[3] & 0xF) != 3:
            symbol[1] = map_offset(symbol[1], intervals)
            struct.pack_into(">IIIBBH", data, offset, *symbol)

    def reorder_relocations(name: str, ranges) -> None:
        _, section = by_name[name]
        entries = []
        for offset in range(section[4], section[4] + section[5], section[9]):
            reloc = list(struct.unpack_from(">IIi", data, offset))
            reloc[0] = map_offset(reloc[0], ranges)
            entries.append(reloc)
        entries.sort(key=lambda item: item[0])
        for offset, reloc in zip(
            range(section[4], section[4] + section[5], section[9]), entries
        ):
            struct.pack_into(">IIi", data, offset, *reloc)

    reorder_relocations(".rela.text", intervals)

    extabindex_index, extabindex = by_name["extabindex"]
    _, rela_index = by_name[".relaextabindex"]
    relocs = [
        list(struct.unpack_from(">IIi", data, offset))
        for offset in range(
            rela_index[4], rela_index[4] + rela_index[5], rela_index[9]
        )
    ]
    records = {}
    for record_offset in range(0, extabindex[5], 12):
        record_relocs = [r for r in relocs if record_offset <= r[0] < record_offset + 12]
        function_reloc = next(r for r in record_relocs if r[0] == record_offset)
        function_name = symbols[function_reloc[1] >> 8][2]
        record = bytes(
            data[
                extabindex[4] + record_offset : extabindex[4] + record_offset + 12
            ]
        )
        records[function_name] = (record, record_relocs)

    new_relocs = []
    for index, name in enumerate(EXCEPTION_ORDER):
        record, record_relocs = records[name]
        record_offset = index * 12
        data[
            extabindex[4] + record_offset : extabindex[4] + record_offset + 12
        ] = record
        for reloc in record_relocs:
            reloc[0] = record_offset + reloc[0] % 12
            new_relocs.append(reloc)
    new_relocs.sort(key=lambda item: item[0])
    for offset, reloc in zip(
        range(rela_index[4], rela_index[4] + rela_index[5], rela_index[9]),
        new_relocs,
    ):
        struct.pack_into(">IIi", data, offset, *reloc)

    extab_index, extab = by_name["extab"]
    extab_ranges = []
    new_extab = bytearray()
    for name in EXCEPTION_ORDER:
        _, record_relocs = records[name]
        extab_reloc = next(r for r in record_relocs if r[0] % 12 == 8)
        symbol_index = extab_reloc[1] >> 8
        symbol_offset, symbol, _ = symbols[symbol_index]
        old_start, size = symbol[1], symbol[2]
        new_start = len(new_extab)
        extab_ranges.append((old_start, old_start + size, new_start))
        new_extab += data[extab[4] + old_start : extab[4] + old_start + size]
        symbol[1] = new_start
        struct.pack_into(">IIIBBH", data, symbol_offset, *symbol)
    data[extab[4] : extab[4] + extab[5]] = new_extab

    args.object.write_bytes(data)
    temporary = args.object.parent / (args.object.name + ".memory.tmp")
    command = [str(args.objcopy)]
    for source, target in RENAMES.items():
        command.extend(("--redefine-sym", f"{source}={target}"))
    command.extend((str(args.object), str(temporary)))
    subprocess.run(command, check=True)
    shutil.copystat(args.object, temporary)
    temporary.replace(args.object)
    args.stamp.touch()


if __name__ == "__main__":
    main()
