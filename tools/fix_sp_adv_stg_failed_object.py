#!/usr/bin/env python3

"""Remove the compiler-only weak TObject delete atom from SpAdvStgFailed."""

import argparse
import os
import subprocess
import struct
import tempfile
from pathlib import Path

SYMBOL_RENAMES = {
    "Error__7TObjectFPc": "fn_80017854",
    "StartFadeOut__7TObjectFv": "fn_8001894C",
    "ImmAftSetRaster__7TObjectFv": "fn_80018950",
    "Debug__7TObjectFv": "fn_80018954",
    "Render__7TObjectFv": "fn_80018958",
    "Exec__7TObjectFv": "fn_80018984",
    "Disp__7TObjectFv": "fn_80018988",
    "Virtual1__7TObjectFv": "fn_8001898C",
    "FreeHeap": "fn_800189A4",
    "AllocHeap": "fn_80018A34",
    "GetAnimationPosition": "fn_800A9234",
    "GetAnimation": "fn_800A943C",
    "__dt__10FadeScreenFv": "dtor_800FE334",
    "__ct__10FadeScreenFv": "fn_800FE3FC",
    "Exec__10FadeScreenFv": "fn_800FE464",
    "SetStageFailed": "fn_80111578",
    "IsFadeOutDone__14SpAdvStgFailedFv": "fn_8013B76C",
    "Exec__14SpAdvStgFailedFv": "fn_8013B780",
    "Disp__14SpAdvStgFailedFv": "fn_8013B784",
    "StartFadeOut__14SpAdvStgFailedFv": "fn_8013B8E8",
    "__dt__14SpAdvStgFailedFv": "fn_8013B9D8",
    "GoStageFailed__FP7TObjectPv": "fn_8013BA88",
    "FinalizeStageFailed__Fv": "fn_8013BBE0",
    "DrawResource": "fn_8014FF2C",
    "AllocResource": "fn_80150588",
    "DestroyResource": "fn_80150958",
    "AttachResource": "fn_8015BB08",
    "ReleaseResourceHandle": "fn_8015BBF8",
    "GetResourceHandle": "fn_8015BD78",
    "SetRenderState": "fn_80194234",
    "GetRenderState": "fn_80194294",
    "StopResource": "fn_8019EB94",
    "DestroyAnimation": "fn_801A46D0",
    "DestroyStageFailedController": "fn_8020C2D8",
    "StageFailedResources": "lbl_8028D0EC",
    "StageFailedResourcesTail": "lbl_8028D0F0",
    "__vt__14SpAdvStgFailed": "lbl_8028D1A0",
    "StageFailedDrawList": "lbl_8042BCC8",
    "StageFailedResourceName": "lbl_8042BCCC",
    "TaskHeap": "lbl_8042C148",
    "StageController": "lbl_8042C610",
    "StageFailedArchive": "lbl_8042C810",
    "StageFailedController": "lbl_8042C814",
}


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


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

    delete_index = symbol_by_name["__dl__7TObjectFPv"]
    delete_offset, delete_symbol, _ = symbols[delete_index]
    text_index, text = by_name[".text"]
    if delete_symbol[5] != text_index or delete_symbol[2] != 0x28:
        raise SystemExit("unexpected compiler-only TObject delete layout")
    removed_text_start = delete_symbol[1]
    removed_text_size = delete_symbol[2]
    removed_text_end = removed_text_start + removed_text_size

    def compact_section(section: list[int], start: int, size: int) -> None:
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
        if offset == delete_offset:
            symbol[1] = 0
            symbol[2] = 0
            symbol[3] = 0x12
            symbol[5] = 0
        elif symbol[1] >= removed_text_end:
            symbol[1] -= removed_text_size
        struct.pack_into(">IIIBBH", data, offset, *symbol)

    _, rela_index = by_name[".relaextabindex"]
    index_relocations = [
        list(struct.unpack_from(">IIi", data, offset))
        for offset in range(
            rela_index[4], rela_index[4] + rela_index[5], rela_index[9]
        )
    ]
    delete_record = next(
        relocation[0]
        for relocation in index_relocations
        if relocation[1] >> 8 == delete_index and relocation[0] % 12 == 0
    )
    extab_relocation = next(
        relocation
        for relocation in index_relocations
        if relocation[0] == delete_record + 8
    )
    extab_symbol_index = extab_relocation[1] >> 8
    extab_symbol_offset, extab_symbol, _ = symbols[extab_symbol_index]
    removed_extab_start, removed_extab_size = extab_symbol[1], extab_symbol[2]
    if removed_extab_size != 8:
        raise SystemExit("unexpected compiler-only delete extab layout")

    extabindex_index, extabindex = by_name["extabindex"]
    compact_section(extabindex, delete_record, 12)
    compact_relocations(".relaextabindex", delete_record, 12)
    for offset, symbol, _ in symbols:
        if symbol[5] != extabindex_index or (symbol[3] & 0xF) == 3:
            continue
        if delete_record <= symbol[1] < delete_record + 12:
            symbol[1] = 0
            symbol[2] = 0
            symbol[5] = 0
        elif symbol[1] >= delete_record + 12:
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

    for offset, symbol, _ in symbols:
        if (symbol[3] & 0xF) != 3 or symbol[5] == 0:
            continue
        symbol[2] = sections[symbol[5]][5]
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
        command = [str(args.objcopy)]
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
