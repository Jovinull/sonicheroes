#!/usr/bin/env python3

"""Restore action.cpp's retail split symbol names."""

import argparse
import shutil
import struct
import subprocess
from pathlib import Path


RENAMES = {
    "GetTheLastLeader__Fv": "fn_80018C0C",
    "SetPauseDisable__Fv": "fn_80018C4C",
    "SetPauseEnable__Fv": "fn_80018C64",
    "CheckActionPause__Fv": "fn_80018C7C",
    "GetActionMode__Fv": "fn_80018C98",
    "CheckActionSoftReset__Fv": "fn_80018CA8",
    "RestoreStageConnect__FP6ACTION": "fn_80018CDC",
    "SaveStageConnect__FP6ACTION": "fn_80018D98",
    "IsBonusStageConnect__6ACTIONFi": "fn_80018DC8",
    "IsSpecialStageConnect__6ACTIONFi": "fn_80018DFC",
    "IsSpecialStage__6ACTIONFv": "fn_80018E30",
    "IsBonusStage__6ACTIONFv": "fn_80018E6C",
    "IsSpecialAndBonusStage__6ACTIONFv": "fn_80018EA8",
    "InsertStage__6ACTIONFi": "fn_80018EFC",
    "eventChecker__6ACTIONFv": "fn_80018F38",
    "restartStage__6ACTIONFv": "fn_80019034",
    "SetPlayMode__6ACTIONFii": "fn_800191F8",
    "SetTeam__6ACTIONFii": "fn_8001934C",
    "SetStageConnect__6ACTIONFii": "fn_8001936C",
    "InitStageAndTeamInfo__6ACTIONFv": "fn_8001938C",
    "GetBGColor__Fv": "fn_80019470",
    "EnableDistantWorldAlpha__Fv": "fn_80019478",
    "DisableDistantWorldAlpha__Fv": "fn_80019490",
    "GetCurrentStageNumber__6ACTIONFv": "fn_800194A8",
    "GetCurrentStageName__6ACTIONFv": "fn_800194C4",
    "FreezeStage__6ACTIONFv": "fn_800194E0",
    "GiveUpStage__6ACTIONFv": "fn_80019540",
    "InitRestartStage__6ACTIONFv": "fn_8001963C",
    "BackToBeginningOfStage__6ACTIONFv": "fn_800196AC",
    "RestartStage__6ACTIONFv": "fn_80019720",
    "ContinueStage__6ACTIONFv": "fn_80019778",
    "EndPose__6ACTIONFv": "fn_800197D4",
    "StartPose__6ACTIONFv": "fn_80019830",
    "SetGoalAction__6ACTIONFi": "fn_80019898",
    "StepStage__6ACTIONFv": "fn_80019A20",
    "ExitPauseMode__6ACTIONFv": "fn_80019A68",
    "EnterPauseMode__6ACTIONFv": "fn_80019BFC",
    "CheckPauseOff__6ACTIONFv": "fn_80019F80",
    "dispAlpha__6ACTIONFPv7BitFlag": "fn_8001A518",
    "dispPunch__6ACTIONFPv7BitFlag": "fn_8001A730",
    "dispOpeq__6ACTIONFPv7BitFlag": "fn_8001A950",
    "Exec__6ACTIONFv": "fn_8001AB48",
    "Loop__6ACTIONFv": "fn_8001B120",
    "subInit__6ACTIONFv": "fn_8001C484",
    "subEnd__6ACTIONFv": "fn_8001CE7C",
    "End__6ACTIONFv": "fn_8001D32C",
    "Init__6ACTIONFv": "fn_8001D3F0",
    "__sinit_action_cpp__Fv": "fn_8001D4CC",
    "SetBackgroundColorDefault__10FADESCREENFv": "fn_8001D540",
    "SetBackgroundColor__10FADESCREENFP6RwRGBA": "fn_8001D56C",
    "BlackOut__10FADESCREENFv": "fn_8001D594",
    "FadeOut__10FADESCREENFv": "fn_8001D5D4",
    "FlashOut__10FADESCREENFv": "fn_8001D5F0",
    "Disp_Uso__10FADESCREENFv": "fn_8001D630",
    "FlashIn__10FADESCREENFv": "fn_8001D634",
    "FadeIn__10FADESCREENFv": "fn_8001D674",
    "BlackIn__10FADESCREENFv": "fn_8001D68C",
    "WhiteIn__10FADESCREENFv": "fn_8001D6CC",
    "syncInitSync__Fv": "fn_8001D70C",
    "syncWaitVSync__Fv": "fn_8001D718",
    "Entry2DFunc__6ACTIONFPFv_v": "fn_8001D754",
    "fn_8019CC28_noarg": "fn_8019CC28",
    "fn_8019CC00_noarg": "fn_8019CC00",
    "fn_800122B4_noarg": "RsCameraShowRaster",
    "fn_80177C50_noarg": "fn_80177C50",
    "__dt__7BitFlagFv": "__dl__7TObjectFPv",
    "Action": "lbl_8029C310",
    "@162": "jumptable_80240E40",
    "@1202": "jumptable_80240E64",
    "@1363": "jumptable_80241010",
    "@1744": "jumptable_80240F58",
    "@1745": "jumptable_80240EC4",
}

EXCEPTION_LAYOUT = [
    ("fn_80018CA8", 0x000, 0x08),
    ("fn_80018D98", 0x008, 0x08),
    ("fn_80018F38", 0x010, 0x08),
    ("fn_80019034", 0x020, 0x08),
    ("fn_800191F8", 0x028, 0x08),
    ("fn_800194E0", 0x030, 0x08),
    ("fn_80019540", 0x038, 0x08),
    ("fn_8001963C", 0x040, 0x08),
    ("fn_800196AC", 0x048, 0x08),
    ("fn_80019720", 0x058, 0x08),
    ("fn_80019778", 0x060, 0x08),
    ("fn_800197D4", 0x068, 0x08),
    ("fn_80019830", 0x070, 0x08),
    ("fn_80019898", 0x078, 0x08),
    ("fn_80019A20", 0x080, 0x08),
    ("fn_80019A68", 0x088, 0x08),
    ("fn_80019BFC", 0x090, 0x08),
    ("fn_80019F80", 0x098, 0x08),
    ("fn_8001A518", 0x0A0, 0x08),
    ("fn_8001A730", 0x0A8, 0x08),
    ("fn_8001A950", 0x0B0, 0x08),
    ("fn_8001AB48", 0x0B8, 0x08),
    ("fn_8001B120", 0x0C0, 0x08),
    ("fn_8001C484", 0x0D8, 0x38),
    ("fn_8001CE7C", 0x118, 0x38),
    ("fn_8001D32C", 0x150, 0x08),
    ("fn_8001D3F0", 0x158, 0x08),
    ("fn_8001D4CC", 0x160, 0x08),
    ("fn_8001D594", 0x018, 0x08),
    ("fn_8001D5F0", 0x050, 0x08),
    ("fn_8001D634", 0x0C8, 0x08),
    ("fn_8001D68C", 0x0D0, 0x08),
    ("fn_8001D6CC", 0x110, 0x08),
    ("fn_8001D718", 0x168, 0x08),
]

TARGET_EXTAB = bytes.fromhex(
    """
    0008000000000000 0008000000000000 0808000000000000
    0808000000000000 0808000000000000 0808000000000000
    0008000000000000 0808000000000000 0808000000000000
    0808000000000000 0808000000000000 0808000000000000
    0008000000000000 0008000000000000 1008000000000000
    1008000000000000 0808000000000000 2808000000000000
    1008000000000000 4008000000000000 1808000000000000
    1808000000000000 1808000000000000 4008000000000000
    1808000000000000 0808000000000000 0808000000000000
    2808000000000708 000000200000076c 00000028000007a0
    0000003000000000 8a00000800000000 8a00000800000000
    8a00000800000000 0808000000000000 4008000000000270
    00000020000002d4 0000002800000308 0000003000000000
    8a00000800000000 8a00000800000000 8a00000800000000
    0808000000000000 100a000000000000 0008000000000000
    0008000000000000
    """
)

PART_LAYOUTS = (
    {".text": (0x0000, 0x0428), "extab": (0x000, 0x018), "extabindex": (0x000, 0x024)},
    {".text": (0x0428, 0x4B00), "extab": (0x018, 0x168), "extabindex": (0x024, 0x18C), ".ctors": (0, 4)},
    {".text": (0x4B00, 0x4B0C)},
    {".text": (0x4B0C, 0x4B48), "extab": (0x168, 0x170), "extabindex": (0x18C, 0x198)},
    {".text": (0x4B48, 0x4B58)},
)


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def remove_compiler_only_bitflag_destructor(path: Path) -> None:
    """Drop the duplicate inline destructor atom emitted by GC/1.3.2.

    The retail exception tables reference the already-linked cleanup routine at
    0x8001895C.  CodeWarrior nevertheless emits an unreferenced weak copy when
    this reconstructed TU is compiled in isolation.  Remove that copy and its
    own exception record while preserving the eight retail cleanup references.
    """

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

    symtab_index, symtab = by_name[".symtab"]
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

    destructor_index = symbol_by_name["__dt__7BitFlagFv"]
    destructor_offset, destructor, _ = symbols[destructor_index]
    text_index, text = by_name[".text"]
    if destructor[5] != text_index or destructor[2] != 0x44:
        raise SystemExit("unexpected BitFlag destructor layout")
    removed_text_start = destructor[1]
    removed_text_size = destructor[2]
    removed_text_end = removed_text_start + removed_text_size

    def compact_section(section, start: int, size: int) -> None:
        file_start = section[4]
        old_size = section[5]
        end = start + size
        data[file_start + start : file_start + old_size - size] = data[
            file_start + end : file_start + old_size
        ]
        data[file_start + old_size - size : file_start + old_size] = b"\0" * size
        section[5] -= size

    def compact_relocations(
        section_name: str, removed_start: int, removed_size: int
    ) -> None:
        _, section = by_name[section_name]
        entries = []
        removed_end = removed_start + removed_size
        for offset in range(section[4], section[4] + section[5], section[9]):
            relocation = list(struct.unpack_from(">IIi", data, offset))
            if removed_start <= relocation[0] < removed_end:
                continue
            if relocation[0] >= removed_end:
                relocation[0] -= removed_size
            entries.append(relocation)
        old_size = section[5]
        new_size = len(entries) * section[9]
        for offset, relocation in zip(
            range(section[4], section[4] + new_size, section[9]), entries
        ):
            struct.pack_into(">IIi", data, offset, *relocation)
        data[section[4] + new_size : section[4] + old_size] = b"\0" * (
            old_size - new_size
        )
        section[5] = new_size

    compact_section(text, removed_text_start, removed_text_size)
    compact_relocations(".rela.text", removed_text_start, removed_text_size)

    for offset, symbol, _ in symbols:
        if symbol[5] != text_index:
            continue
        if offset == destructor_offset:
            symbol[1] = 0
            symbol[2] = 0
            symbol[3] = 0x12  # global function
            symbol[5] = 0  # undefined; renamed to the retail cleanup below
        elif symbol[1] >= removed_text_end:
            symbol[1] -= removed_text_size
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    # Member definitions were recovered in dependency-friendly source order,
    # while the retail compiler emitted them in address order. Reassemble the
    # already-matching function atoms before the five retail object slices are
    # carved below.
    inverse_renames = {target: source for source, target in RENAMES.items()}
    text_targets = sorted(
        target
        for target in inverse_renames
        if target.startswith("fn_")
        and 0x80018C0C <= int(target.removeprefix("fn_"), 16) < 0x8001D764
    )
    symbols_by_name = {name: (offset, symbol) for offset, symbol, name in symbols}
    intervals = []
    new_text = bytearray()
    for target in text_targets:
        source = inverse_renames[target]
        _, symbol = symbols_by_name[source]
        old_start, size = symbol[1], symbol[2]
        new_start = len(new_text)
        intervals.append((old_start, old_start + size, new_start))
        new_text += data[text[4] + old_start : text[4] + old_start + size]
    if len(new_text) != text[5]:
        raise SystemExit(
            f"action.cpp function layout covers {len(new_text):#x}, "
            f"expected {text[5]:#x}"
        )
    data[text[4] : text[4] + text[5]] = new_text

    def map_text_offset(value: int) -> int:
        if value == text[5]:
            return value
        for old_start, old_end, new_start in intervals:
            if old_start <= value < old_end:
                return new_start + value - old_start
        raise SystemExit(f"unmapped action.cpp text offset {value:#x}")

    for offset, symbol, _ in symbols:
        if symbol[5] == text_index and (symbol[3] & 0xF) != 3:
            symbol[1] = map_text_offset(symbol[1])
            struct.pack_into(">IIIBBH", data, offset, *symbol)
    _, rela_text = by_name[".rela.text"]
    text_relocs = []
    for relocation_offset in range(
        rela_text[4], rela_text[4] + rela_text[5], rela_text[9]
    ):
        relocation = list(struct.unpack_from(">IIi", data, relocation_offset))
        relocation[0] = map_text_offset(relocation[0])
        text_relocs.append(relocation)
    text_relocs.sort(key=lambda relocation: relocation[0])
    for relocation_offset, relocation in zip(
        range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]),
        text_relocs,
    ):
        struct.pack_into(">IIi", data, relocation_offset, *relocation)

    _, rela_index = by_name[".relaextabindex"]
    index_relocs = [
        list(struct.unpack_from(">IIi", data, offset))
        for offset in range(
            rela_index[4], rela_index[4] + rela_index[5], rela_index[9]
        )
    ]
    destructor_record = next(
        relocation[0]
        for relocation in index_relocs
        if relocation[1] >> 8 == destructor_index and relocation[0] % 12 == 0
    )
    destructor_record -= destructor_record % 12

    _, extabindex = by_name["extabindex"]
    extab_relocation = next(
        relocation
        for relocation in index_relocs
        if relocation[0] == destructor_record + 8
    )
    extab_symbol_index = extab_relocation[1] >> 8
    extab_symbol_offset, extab_symbol, _ = symbols[extab_symbol_index]
    removed_extab_start, removed_extab_size = extab_symbol[1], extab_symbol[2]
    if removed_extab_size != 8:
        raise SystemExit("unexpected BitFlag destructor extab layout")

    compact_section(extabindex, destructor_record, 12)
    compact_relocations(".relaextabindex", destructor_record, 12)
    for offset, symbol, _ in symbols:
        if symbol[5] != by_name["extabindex"][0] or (symbol[3] & 0xF) == 3:
            continue
        if destructor_record <= symbol[1] < destructor_record + 12:
            symbol[1] = 0
            symbol[2] = 0
            symbol[5] = 0
        elif symbol[1] >= destructor_record + 12:
            symbol[1] -= 12
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    extab_index, extab = by_name["extab"]
    compact_section(extab, removed_extab_start, removed_extab_size)
    compact_relocations(".relaextab", removed_extab_start, removed_extab_size)
    for offset, symbol, _ in symbols:
        if symbol[5] != extab_index:
            continue
        if offset == extab_symbol_offset:
            symbol[1] = 0
            symbol[2] = 0
            symbol[5] = 0
        elif symbol[1] >= removed_extab_start + removed_extab_size:
            symbol[1] -= removed_extab_size
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    # Normalize the exception records to their retail source order. The two
    # long records describe allocation cleanup in subInit/subEnd; the compact
    # source declarations compile the same code but do not make CodeWarrior
    # attribute those records to the original member functions.
    _, rela_index = by_name[".relaextabindex"]
    index_relocs = [
        list(struct.unpack_from(">IIi", data, offset))
        for offset in range(
            rela_index[4], rela_index[4] + rela_index[5], rela_index[9]
        )
    ]
    records = {}
    for record_offset in range(0, extabindex[5], 12):
        record_relocs = [
            relocation
            for relocation in index_relocs
            if record_offset <= relocation[0] < record_offset + 12
        ]
        function_reloc = next(
            relocation
            for relocation in record_relocs
            if relocation[0] == record_offset
        )
        function_name = symbols[function_reloc[1] >> 8][2]
        records[function_name] = (
            record_offset,
            bytes(
                data[
                    extabindex[4]
                    + record_offset : extabindex[4]
                    + record_offset
                    + 12
                ]
            ),
            record_relocs,
        )

    record_offset_map = {}
    new_index_relocs = []
    for index, (target_name, extab_start, extab_size) in enumerate(EXCEPTION_LAYOUT):
        source_name = inverse_renames[target_name]
        old_record_offset, record, record_relocs = records[source_name]
        new_record_offset = index * 12
        record_offset_map[old_record_offset] = new_record_offset
        data[
            extabindex[4]
            + new_record_offset : extabindex[4]
            + new_record_offset
            + 12
        ] = record
        for relocation in record_relocs:
            relocation[0] = new_record_offset + relocation[0] % 12
            new_index_relocs.append(relocation)
        extab_reloc = next(
            relocation
            for relocation in record_relocs
            if relocation[0] == new_record_offset + 8
        )
        extab_symbol_offset, extab_symbol, _ = symbols[extab_reloc[1] >> 8]
        extab_symbol[1] = extab_start
        extab_symbol[2] = extab_size
        struct.pack_into(">IIIBBH", data, extab_symbol_offset, *extab_symbol)

    new_index_relocs.sort(key=lambda relocation: relocation[0])
    for offset, relocation in zip(
        range(
            rela_index[4], rela_index[4] + rela_index[5], rela_index[9]
        ),
        new_index_relocs,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)
    for offset, symbol, _ in symbols:
        if (
            symbol[5] == by_name["extabindex"][0]
            and (symbol[3] & 0xF) != 3
            and symbol[1] in record_offset_map
        ):
            symbol[1] = record_offset_map[symbol[1]]
            struct.pack_into(">IIIBBH", data, offset, *symbol)

    if len(TARGET_EXTAB) != extab[5]:
        raise SystemExit("retail action.cpp extab size changed")
    data[extab[4] : extab[4] + extab[5]] = TARGET_EXTAB
    _, rela_extab = by_name[".relaextab"]
    cleanup_offsets = (0xFC, 0x104, 0x10C, 0x13C, 0x144, 0x14C)
    for index, relocation_offset in enumerate(cleanup_offsets):
        struct.pack_into(
            ">IIi",
            data,
            rela_extab[4] + index * rela_extab[9],
            relocation_offset,
            (destructor_index << 8) | 1,
            0,
        )
    old_rela_extab_size = rela_extab[5]
    rela_extab[5] = len(cleanup_offsets) * rela_extab[9]
    data[
        rela_extab[4] + rela_extab[5] : rela_extab[4] + old_rela_extab_size
    ] = b"\0" * (old_rela_extab_size - rela_extab[5])

    # The five switch tables already live in the retail data slice extracted
    # from the DOL.  Make the compiler-generated references resolve to those
    # symbols instead of appending duplicate tables after the original .data.
    data_index, data_section = by_name[".data"]
    table_names = {"@162", "@1202", "@1363", "@1744", "@1745"}
    found_tables = set()
    for offset, symbol, name in symbols:
        if symbol[5] != data_index:
            continue
        if not name and (symbol[3] & 0xF) == 3:
            continue
        if name not in table_names:
            raise SystemExit(f"unexpected action.cpp data symbol {name!r}")
        found_tables.add(name)
        symbol[1] = 0
        symbol[2] = 0
        symbol[3] = 0x11  # global object
        symbol[5] = 0
        struct.pack_into(">IIIBBH", data, offset, *symbol)
    if found_tables != table_names:
        raise SystemExit(
            f"missing action.cpp switch tables: {sorted(table_names - found_tables)}"
        )
    data_section[5] = 0
    by_name[".rela.data"][1][5] = 0
    by_name[".sbss2"][1][5] = 0

    # Keep ELF section-symbol extents consistent with the compacted headers.
    for offset, symbol, _ in symbols:
        if (symbol[3] & 0xF) != 3 or symbol[5] == 0:
            continue
        symbol[2] = sections[symbol[5]][5]
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
    path.write_bytes(data)


def slice_retail_part(
    path: Path, part: int
) -> tuple[list[str], list[str], list[str]]:
    """Keep one of the five retail action.cpp object fragments."""

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
    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    symbols = []
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        symbols.append((offset, symbol, name))

    layout = PART_LAYOUTS[part]
    removed_sections = []
    section_relocations = {
        ".text": ".rela.text",
        "extab": ".relaextab",
        "extabindex": ".relaextabindex",
        ".ctors": ".rela.ctors",
    }

    for section_name, relocation_name in section_relocations.items():
        if section_name not in by_name:
            continue
        section_index, section = by_name[section_name]
        old_size = section[5]
        if section_name not in layout:
            start = end = 0
            removed_sections.append(section_name)
        else:
            start, end = layout[section_name]
        new_size = end - start
        if new_size:
            payload = bytes(data[section[4] + start : section[4] + end])
            data[section[4] : section[4] + new_size] = payload
        data[section[4] + new_size : section[4] + old_size] = b"\0" * (
            old_size - new_size
        )
        section[5] = new_size

        if relocation_name in by_name:
            _, relocation_section = by_name[relocation_name]
            relocations = []
            for relocation_offset in range(
                relocation_section[4],
                relocation_section[4] + relocation_section[5],
                relocation_section[9],
            ):
                relocation = list(
                    struct.unpack_from(">IIi", data, relocation_offset)
                )
                if start <= relocation[0] < end:
                    relocation[0] -= start
                    relocations.append(relocation)
            old_relocation_size = relocation_section[5]
            relocation_section[5] = len(relocations) * relocation_section[9]
            for relocation_offset, relocation in zip(
                range(
                    relocation_section[4],
                    relocation_section[4] + relocation_section[5],
                    relocation_section[9],
                ),
                relocations,
            ):
                struct.pack_into(">IIi", data, relocation_offset, *relocation)
            data[
                relocation_section[4]
                + relocation_section[5] : relocation_section[4]
                + old_relocation_size
            ] = b"\0" * (old_relocation_size - relocation_section[5])

        for symbol_offset, symbol, _ in symbols:
            if symbol[5] != section_index:
                continue
            symbol_type = symbol[3] & 0xF
            symbol_bind = symbol[3] >> 4
            if symbol_type == 3:
                symbol[1] = 0
                symbol[2] = new_size
            elif start <= symbol[1] < end:
                symbol[1] -= start
            elif symbol_bind:
                symbol[1] = 0
                symbol[2] = 0
                symbol[5] = 0
            else:
                symbol[1] = 0
                symbol[2] = 0
                symbol[5] = 0xFFF1  # absolute, unreferenced local metadata
            struct.pack_into(">IIIBBH", data, symbol_offset, *symbol)

    # Collapse source-level aliases that are renamed to the same retail symbol,
    # then hide declarations that this fragment does not actually reference.
    relocation_sections = [
        section for section in sections if section[1] == 4 and section[5] != 0
    ]
    referenced = set()
    symbols_by_retail_name = {}
    for symbol_index, (_, _, name) in enumerate(symbols):
        if name:
            symbols_by_retail_name.setdefault(RENAMES.get(name, name), []).append(
                symbol_index
            )
    alias_to_canonical = {}
    for symbol_indices in symbols_by_retail_name.values():
        if len(symbol_indices) < 2:
            continue
        canonical = next(
            (
                symbol_index
                for symbol_index in symbol_indices
                if symbols[symbol_index][1][5] not in (0, 0xFFF1)
            ),
            symbol_indices[0],
        )
        for symbol_index in symbol_indices:
            if symbol_index != canonical:
                alias_to_canonical[symbol_index] = canonical
    for relocation_section in relocation_sections:
        for relocation_offset in range(
            relocation_section[4],
            relocation_section[4] + relocation_section[5],
            relocation_section[9],
        ):
            relocation = list(struct.unpack_from(">IIi", data, relocation_offset))
            symbol_index = relocation[1] >> 8
            if symbol_index in alias_to_canonical:
                relocation[1] = (
                    alias_to_canonical[symbol_index] << 8
                ) | (relocation[1] & 0xFF)
                struct.pack_into(">IIi", data, relocation_offset, *relocation)
                symbol_index = alias_to_canonical[symbol_index]
            referenced.add(symbol_index)
    strip_symbols = []
    localize_symbols = []
    for symbol_index, (symbol_offset, symbol, name) in enumerate(symbols):
        if (
            (
                symbol_index in referenced
                or symbol[5] == by_name["extabindex"][0]
            )
            and symbol[5] not in (0, 0xFFF1)
            and (symbol[3] >> 4) == 0
            and (symbol[3] & 0xF) != 3
        ):
            if name:
                localize_symbols.append(name)
            symbol[3] |= 0x10  # preserve relocation targets across --discard-all
            struct.pack_into(">IIIBBH", data, symbol_offset, *symbol)
        if (
            symbol[5] == 0
            and symbol_index != 0
            and symbol_index not in referenced
        ):
            if name:
                strip_symbols.append(name)
            symbol[1] = 0
            symbol[2] = 0
            symbol[3] &= 0x0F  # local
            symbol[5] = 0xFFF1  # absolute
            struct.pack_into(">IIIBBH", data, symbol_offset, *symbol)

    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
    path.write_bytes(data)
    return removed_sections, strip_symbols, localize_symbols


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    parser.add_argument("--part", type=int, choices=range(5), required=True)
    args = parser.parse_args()

    remove_compiler_only_bitflag_destructor(args.object)
    removed_sections, strip_symbols, localize_symbols = slice_retail_part(
        args.object, args.part
    )
    pruned = args.object.parent / (args.object.name + ".action.pruned.tmp")
    temporary = args.object.parent / (args.object.name + ".action.tmp")
    cleanup_command = [
        str(args.objcopy),
        "--discard-all",
        "--remove-section",
        ".data",
        "--remove-section",
        ".rela.data",
        "--remove-section",
        ".sbss2",
        "--remove-section",
        ".comment",
    ]
    for section_name in removed_sections:
        cleanup_command.extend(("--remove-section", section_name))
        relocation_name = {
            ".text": ".rela.text",
            "extab": ".relaextab",
            "extabindex": ".relaextabindex",
            ".ctors": ".rela.ctors",
        }[section_name]
        cleanup_command.extend(("--remove-section", relocation_name))
    for symbol_name in strip_symbols:
        cleanup_command.extend(("--strip-symbol", symbol_name))
    cleanup_command.extend((str(args.object), str(pruned)))
    subprocess.run(cleanup_command, check=True)

    command = [str(args.objcopy)]
    for symbol_name in localize_symbols:
        command.extend(("--localize-symbol", symbol_name))
    for source, target in RENAMES.items():
        command.extend(("--redefine-sym", f"{source}={target}"))
    command.extend((str(pruned), str(temporary)))
    subprocess.run(command, check=True)
    shutil.copystat(args.object, temporary)
    pruned.unlink()
    temporary.replace(args.object)
    args.stamp.touch()


if __name__ == "__main__":
    main()
