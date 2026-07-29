#!/usr/bin/env python3

import argparse
import shutil
import struct
import subprocess
from pathlib import Path


def bind_duplicate_symbols(path: Path) -> None:
    data = bytearray(path.read_bytes())
    if data[:6] != b"\x7fELF\x01\x02":
        raise RuntimeError("expected a big-endian ELF32 object")

    shoff = struct.unpack_from(">I", data, 0x20)[0]
    shentsize = struct.unpack_from(">H", data, 0x2E)[0]
    shnum = struct.unpack_from(">H", data, 0x30)[0]
    shstrndx = struct.unpack_from(">H", data, 0x32)[0]
    sections = []
    for index in range(shnum):
        offset = shoff + index * shentsize
        sections.append(
            {
                "type": struct.unpack_from(">I", data, offset + 4)[0],
                "offset": struct.unpack_from(">I", data, offset + 16)[0],
                "size": struct.unpack_from(">I", data, offset + 20)[0],
                "link": struct.unpack_from(">I", data, offset + 24)[0],
                "entsize": struct.unpack_from(">I", data, offset + 36)[0],
                "name_offset": struct.unpack_from(">I", data, offset)[0],
            }
        )

    for symtab_index, symtab in enumerate(sections):
        if symtab["type"] != 2:
            continue
        strings = sections[symtab["link"]]
        string_data = data[strings["offset"] : strings["offset"] + strings["size"]]
        count = symtab["size"] // symtab["entsize"]
        names = []
        defined = {}
        for index in range(count):
            offset = symtab["offset"] + index * symtab["entsize"]
            name_offset = struct.unpack_from(">I", data, offset)[0]
            end = string_data.find(b"\0", name_offset)
            name = bytes(string_data[name_offset:end])
            names.append(name)
            shndx = struct.unpack_from(">H", data, offset + 14)[0]
            if shndx != 0:
                defined[name] = index

        replacements = {
            index: defined[name]
            for index, name in enumerate(names)
            if name in defined
            and index != defined[name]
            and struct.unpack_from(
                ">H", data, symtab["offset"] + index * symtab["entsize"] + 14
            )[0]
            == 0
        }
        for index in replacements:
            struct.pack_into(
                ">I", data, symtab["offset"] + index * symtab["entsize"], 0
            )
        for section in sections:
            if section["type"] not in (4, 9) or section["link"] != symtab_index:
                continue
            entry_size = section["entsize"]
            for offset in range(
                section["offset"],
                section["offset"] + section["size"],
                entry_size,
            ):
                info = struct.unpack_from(">I", data, offset + 4)[0]
                symbol = info >> 8
                if symbol in replacements:
                    struct.pack_into(
                        ">I", data, offset + 4, (replacements[symbol] << 8) | (info & 0xFF)
                    )

    shstr = sections[shstrndx]
    shstr_data = data[shstr["offset"] : shstr["offset"] + shstr["size"]]
    section_names = []
    for section in sections:
        end = shstr_data.find(b"\0", section["name_offset"])
        section_names.append(bytes(shstr_data[section["name_offset"] : end]))

    data_index = section_names.index(b".data")
    new_shoff = shoff
    if sections[data_index]["size"] == 0xA8:
        insertion = sections[data_index]["offset"] + sections[data_index]["size"]
        data[insertion:insertion] = b"\0\0\0\0"
        new_shoff = shoff + (4 if shoff >= insertion else 0)
        struct.pack_into(">I", data, 0x20, new_shoff)
        for index, section in enumerate(sections):
            header = new_shoff + index * shentsize
            if index == data_index:
                struct.pack_into(">I", data, header + 20, section["size"] + 4)
            elif section["type"] != 8 and section["offset"] >= insertion:
                struct.pack_into(">I", data, header + 16, section["offset"] + 4)
    for index, section in enumerate(sections):
        header = new_shoff + index * shentsize
        if section_names[index] == b".data":
            struct.pack_into(">I", data, header + 32, 4)
    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    parser.add_argument("--nm", type=Path, required=True)
    parser.add_argument("--objdump", type=Path, required=True)
    args = parser.parse_args()

    symbols = subprocess.check_output(
        [str(args.nm), "-S", str(args.object)], text=True
    )
    jump_table = None
    for line in symbols.splitlines():
        fields = line.split()
        if len(fields) == 4 and fields[0] == "0000008c" and fields[1] == "0000001c":
            jump_table = fields[3]
            break
    if jump_table is None:
        raise RuntimeError("could not identify moviePlaySub jump table")

    relocations = subprocess.check_output(
        [str(args.objdump), "-r", "-j", "extabindex", str(args.object)],
        text=True,
    )
    exception_tables = []
    for line in relocations.splitlines():
        fields = line.split()
        if len(fields) == 3 and fields[1] == "R_PPC_ADDR32" and fields[2].startswith("@"):
            exception_tables.append(fields[2])
    if len(exception_tables) != 3:
        raise RuntimeError("could not identify moviePlaySub exception tables")

    renames = {
        "moviePlaySubVtableData": "__vt__10MOVIE_PLAY",
        "moviePlaySubScaleData": "lbl_8028CF18",
        "moviePlaySubLanguageData": "lbl_8028CF28",
        "moviePlaySubReportData": "lbl_8028CF44",
        "moviePlaySubScriptFormatData": "lbl_8028CF74",
        "moviePlaySubEventFormatData": "lbl_8028CF84",
        "movieSubBufferData": "MovieSubBuffer",
        "movieSubEventData": "MovieSubEvent",
        "movieSubRasterData": "MovieSubRaster",
        "movieSubResourceData": "MovieSubResource",
        jump_table: "jumptable_8028CF90",
        "__nw__FUl": "fn_80057644",
        "__ct__21MovieSubtitleResourceFPCc": "fn_800CEE18",
        "fn_8004BEE0": "ConvertAnyParameter__FPUcPCci",
        exception_tables[0]: "@etb_8000B994",
        exception_tables[1]: "@etb_8000B99C",
        exception_tables[2]: "@etb_8000B9A4",
    }

    temporary = args.object.parent / (args.object.name + ".symbols.tmp")
    command = [str(args.objcopy)]
    for source, target in renames.items():
        command.extend(["--redefine-sym", f"{source}={target}"])
    command.extend([str(args.object), str(temporary)])
    subprocess.run(command, check=True)
    bind_duplicate_symbols(temporary)
    shutil.copystat(args.object, temporary)
    temporary.replace(args.object)
    args.stamp.touch()


if __name__ == "__main__":
    main()
