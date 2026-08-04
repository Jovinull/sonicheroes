#!/usr/bin/env python3

"""Merge e_appear_spboss.cpp's trailing string atom into regular data."""

import argparse
import os
import shutil
import subprocess
import struct
import tempfile
from pathlib import Path


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def define_string_alias(path: Path) -> None:
    data = bytearray(path.read_bytes())
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
    sections = [
        struct.unpack_from(">IIIIIIIIII", data, shoff + index * shentsize)
        for index in range(shnum)
    ]
    shstr = sections[shstrndx]
    section_names = data[shstr[4] : shstr[4] + shstr[5]]
    by_name = {
        cstring(section_names, section[0]): (index, section)
        for index, section in enumerate(sections)
    }
    strings_index, _ = by_name[".appear_strings"]
    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    names = data[strtab[4] : strtab[4] + strtab[5]]
    found = False
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        name_offset = struct.unpack_from(">I", data, offset)[0]
        name = cstring(names, name_offset) if name_offset else ""
        if name != "TEnemyAppearSPBossFieldTypes":
            continue
        struct.pack_into(">I", data, offset + 4, 14)
        struct.pack_into(">H", data, offset + 14, strings_index)
        found = True
    if not found:
        raise SystemExit("missing TEnemyAppearSPBossFieldTypes alias")
    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", required=True, type=Path)
    parser.add_argument("--ld", required=True, type=Path)
    args = parser.parse_args()
    define_string_alias(args.object)

    with tempfile.TemporaryDirectory() as directory:
        directory_path = Path(directory)
        renamed = directory_path / "renamed.o"
        merged = directory_path / "merged.o"
        command = [
            args.objcopy,
            "--rename-section",
            ".appear_strings=.data",
        ]
        renames = {
            "__dt__7TObjectFv": "fn_16_5F55C",
            "__dl__18TEnemyAppearSPBossFPv": "__dl__10TObjSampleFPv",
            "PDisp__7TObjectFv": "fn_16_11640",
            "Disp__7TObjectFv": "fn_16_5F3B0",
            "TDisp__7TObjectFv": "sampleHook1",
            "ImmAftSetRaster__7TObjectFv": "sampleHook2",
            "Debug__7TObjectFv": "sampleHook3",
            "Render__7TObjectFv": "sampleHook4",
            "Error__7TObjectFPc": "fn_80017854",
        }
        for source, target in renames.items():
            command.extend(["--redefine-sym", f"{source}={target}"])
        command.extend([args.object, renamed])
        subprocess.run(command, check=True)
        subprocess.run([args.ld, "-r", renamed, "-o", merged], check=True)
        shutil.copyfile(merged, args.object)

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
