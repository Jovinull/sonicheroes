#!/usr/bin/env python3

"""Normalize CodeWarrior's Task.cpp deferred-code layout.

Task.cpp contains mutually recursive inline methods and destructors whose bodies
must be visible before their retail call sites.  CodeWarrior consequently emits
the out-of-line copies in dependency order, while the original object placed
them in source order.  This script changes only ELF layout and symbol metadata:
function bytes, relocations, and exception records are moved as indivisible
units.
"""

import argparse
import shutil
import struct
import subprocess
from pathlib import Path


TEXT_ORDER = (
    "Reset__9TMainTaskFv",
    "PauseChild__9TMainTaskFv",
    "ContinueChild__9TMainTaskFv",
    "Debug__9TMainTaskFv",
    "ImmAftSetRaster__9TMainTaskFv",
    "TDisp__9TMainTaskFv",
    "PDisp__9TMainTaskFv",
    "Disp__9TMainTaskFv",
    "Exec__9TMainTaskFv",
    "Finalize__9TMainTaskFv",
    "Initialize__9TMainTaskFv",
    "__dt__9TMainTaskFv",
    "CheckAlive__7TObjectFv",
    "GetChildCount__7TObjectFv",
    "Error__7TObjectFPc",
    "ImmAftSetRasterChild__7TObjectFv",
    "TDispChild__7TObjectFv",
    "PDispChild__7TObjectFv",
    "DispChild__7TObjectFv",
    "ExecChild__7TObjectFv",
    "KillChild__7TObjectFv",
    "DeleteChild__7TObjectFv",
    "__dt__7TObjectFv",
    "__ct__7TObjectFP7TObject",
    "__sinit_Task_cpp",
    "Exec__7TObjectFv",
    "ImmAftSetRaster__7TObjectFv",
    "Debug__7TObjectFv",
    "Render__7TObjectFv",
    "__dl__7TObjectFPv",
    "TDisp__7TObjectFv",
    "PDisp__7TObjectFv",
    "Disp__7TObjectFv",
    "Kill__7TObjectFv",
)

INDEX_ORDER = (
    "Reset__9TMainTaskFv",
    "Debug__9TMainTaskFv",
    "ImmAftSetRaster__9TMainTaskFv",
    "TDisp__9TMainTaskFv",
    "PDisp__9TMainTaskFv",
    "Disp__9TMainTaskFv",
    "Exec__9TMainTaskFv",
    "Finalize__9TMainTaskFv",
    "Initialize__9TMainTaskFv",
    "__dt__9TMainTaskFv",
    "Error__7TObjectFPc",
    "ImmAftSetRasterChild__7TObjectFv",
    "TDispChild__7TObjectFv",
    "PDispChild__7TObjectFv",
    "DispChild__7TObjectFv",
    "ExecChild__7TObjectFv",
    "KillChild__7TObjectFv",
    "DeleteChild__7TObjectFv",
    "__dt__7TObjectFv",
    "__sinit_Task_cpp",
    "__dl__7TObjectFPv",
)

EXTAB_ORDER = (
    "Reset__9TMainTaskFv",
    "Debug__9TMainTaskFv",
    "ImmAftSetRaster__9TMainTaskFv",
    "TDisp__9TMainTaskFv",
    "PDisp__9TMainTaskFv",
    "Disp__9TMainTaskFv",
    "Exec__9TMainTaskFv",
    "Finalize__9TMainTaskFv",
    "Initialize__9TMainTaskFv",
    "__dl__7TObjectFPv",
    "__dt__9TMainTaskFv",
    "Error__7TObjectFPc",
    "ImmAftSetRasterChild__7TObjectFv",
    "TDispChild__7TObjectFv",
    "PDispChild__7TObjectFv",
    "DispChild__7TObjectFv",
    "ExecChild__7TObjectFv",
    "KillChild__7TObjectFv",
    "DeleteChild__7TObjectFv",
    "__dt__7TObjectFv",
    "__sinit_Task_cpp",
)

RENAMES = {
    "Reset__9TMainTaskFv": "fn_80016514",
    "PauseChild__9TMainTaskFv": "fn_800166E8",
    "ContinueChild__9TMainTaskFv": "fn_80016778",
    "Debug__9TMainTaskFv": "fn_80016808",
    "ImmAftSetRaster__9TMainTaskFv": "fn_8001682C",
    "TDisp__9TMainTaskFv": "fn_80016910",
    "PDisp__9TMainTaskFv": "fn_800169F4",
    "Disp__9TMainTaskFv": "fn_80016AD8",
    "Exec__9TMainTaskFv": "fn_80016BBC",
    "Finalize__9TMainTaskFv": "fn_80016CA0",
    "Initialize__9TMainTaskFv": "fn_80016E88",
    "__dt__9TMainTaskFv": "fn_8001766C",
    "CheckAlive__7TObjectFv": "fn_80017800",
    "GetChildCount__7TObjectFv": "fn_80017830",
    "Error__7TObjectFPc": "fn_80017854",
    "ImmAftSetRasterChild__7TObjectFv": "fn_80017878",
    "TDispChild__7TObjectFv": "fn_80017AEC",
    "PDispChild__7TObjectFv": "fn_80017DF0",
    "DispChild__7TObjectFv": "fn_80018064",
    "ExecChild__7TObjectFv": "fn_80018368",
    "KillChild__7TObjectFv": "fn_800184C8",
    "DeleteChild__7TObjectFv": "fn_8001867C",
    "__sinit_Task_cpp": "fn_800188AC",
    "Exec__7TObjectFv": "fn_8001894C",
    "ImmAftSetRaster__7TObjectFv": "fn_80018950",
    "Debug__7TObjectFv": "fn_80018954",
    "Render__7TObjectFv": "fn_80018958",
    "TDisp__7TObjectFv": "fn_80018984",
    "PDisp__7TObjectFv": "fn_80018988",
    "Disp__7TObjectFv": "fn_8001898C",
    "Kill__7TObjectFv": "fn_80018990",
    "Free__9THeapCtrlFPv": "fn_800189A4",
    "Malloc__9THeapCtrlFUi": "fn_80018A34",
    "__dl__9THeapCtrlFPv": "dtor_80018BB4",
    "__nw__9THeapCtrlFUl": "fn_80018BE0",
    "__ct__9THeapCtrlFUiUi": "fn_80018B24",
    "MainTask": "lbl_8029C2E4",
    "__vt__9TMainTask": "lbl_80240AB4",
    "__vt__7TObject": "lbl_80240AE0",
    "CL_TObject": "lbl_8042ADA0",
    "CL_TMainTask": "lbl_8042ADA4",
    "CL_TL_SU": "lbl_8042ADB0",
    "CL_TL_00": "lbl_8042ADBC",
    "CL_TL_01": "lbl_8042ADC8",
    "CL_TL_02": "lbl_8042ADD4",
    "CL_TL_03": "lbl_8042ADE0",
    "CL_TL_04": "lbl_8042ADEC",
    "CL_TL_05": "lbl_8042ADF8",
    "CL_TL_06": "lbl_8042AE04",
    "CL_TL_07": "lbl_8042AE10",
    "CL_TL_PARTICLE": "lbl_8042AE14",
    "CL_TL_TIMESTOP": "lbl_8042AE18",
    "TL_SU": "lbl_8042C0F8",
    "TL_00": "lbl_8042C0FC",
    "TL_01": "lbl_8042C100",
    "TL_02": "lbl_8042C104",
    "TL_03": "lbl_8042C108",
    "TL_04": "lbl_8042C10C",
    "TL_05": "lbl_8042C110",
    "TL_06": "lbl_8042C114",
    "TL_07": "lbl_8042C118",
    "TL_PARTICLE": "lbl_8042C11C",
    "TL_TIMESTOP": "lbl_8042C120",
    "ObjectCount": "lbl_8042C124",
    "TaskNest": "lbl_8042C128",
    "ExecSleepFlag": "lbl_8042C12C",
    "ExecSleepFlagOld": "lbl_8042C130",
    "DispSleepFlag": "lbl_8042C134",
    "DispSleepFlagOld": "lbl_8042C138",
    "ImmAftSetRasterSleepFlag": "lbl_8042C13C",
    "ImmAftSetRasterSleepFlagOld": "lbl_8042C140",
    "TaskHeap": "lbl_8042C148",
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

    ehdr = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
    shoff, shentsize, shnum, shstrndx = ehdr[6], ehdr[11], ehdr[12], ehdr[13]
    sections = []
    for index in range(shnum):
        values = list(struct.unpack_from(">IIIIIIIIII", data, shoff + index * shentsize))
        sections.append(values)
    shstr = sections[shstrndx]
    shstr_data = data[shstr[4] : shstr[4] + shstr[5]]
    section_by_name = {
        cstring(shstr_data, section[0]): (index, section)
        for index, section in enumerate(sections)
    }

    sym_index, symtab = section_by_name[".symtab"]
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

    text_index, text = section_by_name[".text"]
    intervals = []
    new_offset = 0
    new_text = bytearray()
    for name in TEXT_ORDER:
        _, symbol, _ = symbols[symbols_by_name[name]]
        old_offset, size = symbol[1], symbol[2]
        intervals.append((old_offset, old_offset + size, new_offset))
        new_text += data[text[4] + old_offset : text[4] + old_offset + size]
        new_offset += size
    if new_offset != text[5]:
        raise SystemExit(f"function layout covers {new_offset:#x}, expected {text[5]:#x}")
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

    def reorder_relocations(section_name: str, mapper) -> None:
        _, section = section_by_name[section_name]
        entries = []
        for offset in range(section[4], section[4] + section[5], section[9]):
            reloc = list(struct.unpack_from(">IIi", data, offset))
            reloc[0] = mapper(reloc[0])
            entries.append(reloc)
        entries.sort(key=lambda item: item[0])
        for offset, reloc in zip(
            range(section[4], section[4] + section[5], section[9]), entries
        ):
            struct.pack_into(">IIi", data, offset, *reloc)

    reorder_relocations(".rela.text", map_text_offset)
    reorder_relocations(".rela.data", lambda value: value)
    reorder_relocations(".rela.sdata", lambda value: value)

    # Reorder twelve-byte exception-index records using their function
    # relocation as the stable identity.
    _, extabindex = section_by_name["extabindex"]
    _, rela_index = section_by_name[".relaextabindex"]
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
        record = bytes(data[extabindex[4] + record_offset : extabindex[4] + record_offset + 12])
        records[function_name] = (record, record_relocs)
    new_relocs = []
    for index, name in enumerate(INDEX_ORDER):
        record, record_relocs = records[name]
        record_offset = index * 12
        data[extabindex[4] + record_offset : extabindex[4] + record_offset + 12] = record
        for reloc in record_relocs:
            reloc[0] = record_offset + reloc[0] % 12
            new_relocs.append(reloc)
    new_relocs.sort(key=lambda item: item[0])
    for offset, reloc in zip(
        range(rela_index[4], rela_index[4] + rela_index[5], rela_index[9]),
        new_relocs,
    ):
        struct.pack_into(">IIi", data, offset, *reloc)

    # Exception-table blocks are named by the second relocation in each index
    # record.  Move them as units and update their symbols and relocation sites.
    extab_index, extab = section_by_name["extab"]
    extab_blocks = {}
    for name, (_, record_relocs) in records.items():
        extab_reloc = next(r for r in record_relocs if r[0] % 12 == 8)
        symbol_index = extab_reloc[1] >> 8
        _, symbol, _ = symbols[symbol_index]
        extab_blocks[name] = (symbol_index, symbol[1], symbol[2])
    extab_intervals = []
    new_extab = bytearray()
    for name in EXTAB_ORDER:
        symbol_index, old_offset, size = extab_blocks[name]
        new_start = len(new_extab)
        extab_intervals.append((old_offset, old_offset + size, new_start))
        new_extab += data[extab[4] + old_offset : extab[4] + old_offset + size]
        symbol_offset, symbol, _ = symbols[symbol_index]
        symbol[1] = new_start
        struct.pack_into(">IIIBBH", data, symbol_offset, *symbol)
    if len(new_extab) != extab[5]:
        raise SystemExit("exception layout does not cover extab")
    data[extab[4] : extab[4] + extab[5]] = new_extab

    def map_extab_offset(value: int) -> int:
        for old_start, old_end, new_start in extab_intervals:
            if old_start <= value < old_end:
                return new_start + value - old_start
        raise ValueError(f"unmapped extab offset {value:#x}")

    reorder_relocations(".relaextab", map_extab_offset)

    # The retail splitter owns the alignment tails in these sections.
    for name, size in ((".data", 0x80), (".sdata", 0x88), (".sbss", 0x58)):
        if name in section_by_name:
            index, section = section_by_name[name]
            section[5] = size
            struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)

    dynamic_renames = {}
    literal_names = {
        (".data", 0x00): "lbl_80240A90",
        (".data", 0x0C): "lbl_80240A9C",
        (".data", 0x18): "lbl_80240AA8",
        (".sdata", 0x00): "lbl_8042AD98",
        (".sdata", 0x10): "lbl_8042ADA8",
        (".sdata", 0x1C): "lbl_8042ADB4",
        (".sdata", 0x28): "lbl_8042ADC0",
        (".sdata", 0x34): "lbl_8042ADCC",
        (".sdata", 0x40): "lbl_8042ADD8",
        (".sdata", 0x4C): "lbl_8042ADE4",
        (".sdata", 0x58): "lbl_8042ADF0",
        (".sdata", 0x64): "lbl_8042ADFC",
        (".sdata", 0x70): "lbl_8042AE08",
    }
    for (section_name, value), target in literal_names.items():
        section_index, _ = section_by_name[section_name]
        for _, symbol, name in symbols:
            if symbol[5] == section_index and symbol[1] == value and name.startswith("@"):
                dynamic_renames[name] = target

    for offset, symbol, name in symbols:
        if name == "__vt__7TObject":
            symbol[2] = 0x30
        elif name == "ImmAftSetRasterSleepFlagOld":
            symbol[2] = 8
        elif name == "charSet_Debug":
            symbol[1] = 0
            symbol[5] = 0
        elif name == "TaskHeap":
            symbol[2] = 8
        elif name == "CL_TL_TIMESTOP":
            symbol[2] = 8
        else:
            continue
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    if ".bss" in section_by_name:
        bss_index, _ = section_by_name[".bss"]
        for offset, symbol, name in symbols:
            if symbol[5] != bss_index or (symbol[3] & 0xF) == 3:
                continue
            if symbol[1] == 0 and symbol[2] == 12:
                dynamic_renames[name] = "lbl_8029C2D8"
            symbol[1] = 0
            symbol[5] = 0
            struct.pack_into(">IIIBBH", data, offset, *symbol)

    args.object.write_bytes(data)

    temporary = args.object.parent / (args.object.name + ".task.tmp")
    command = [
        str(args.objcopy),
        "--remove-section",
        ".bss",
        "--strip-symbol",
        "charSet_Debug",
    ]
    for source in dynamic_renames:
        if source.startswith("@"):
            command.extend(("--globalize-symbol", dynamic_renames[source]))
    for address in (0x16, 0x22, 0x2E, 0x3A, 0x46, 0x52, 0x5E, 0x6A, 0x76):
        command.extend(
            (
                "--add-symbol",
                f"gap_09_8042{0xAD98 + address:04X}_sdata=.sdata:{address},global,object",
            )
        )
    for source, target in {**RENAMES, **dynamic_renames}.items():
        command.extend(("--redefine-sym", f"{source}={target}"))
    command.extend((str(args.object), str(temporary)))
    subprocess.run(command, check=True)
    shutil.copystat(args.object, temporary)
    temporary.replace(args.object)
    args.stamp.touch()


if __name__ == "__main__":
    main()
