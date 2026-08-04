#!/usr/bin/env python3

"""Merge TEndSkyBob's trailing string atom into its regular data section."""

import argparse
import os
import shutil
import subprocess
import struct
import tempfile
from pathlib import Path


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def define_string_aliases(path: Path) -> None:
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
    strings_index, _ = by_name[".endsky_strings"]
    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    names = data[strtab[4] : strtab[4] + strtab[5]]
    aliases = {
        "TEndSkyBobFieldTypes": 11,
    }
    found = set()
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        name_offset = struct.unpack_from(">I", data, offset)[0]
        name = cstring(names, name_offset) if name_offset else ""
        if name not in aliases:
            continue
        struct.pack_into(">I", data, offset + 4, aliases[name])
        struct.pack_into(">H", data, offset + 14, strings_index)
        found.add(name)
    if found != aliases.keys():
        raise SystemExit(f"missing string aliases: {aliases.keys() - found}")
    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", required=True, type=Path)
    parser.add_argument("--ld", required=True, type=Path)
    args = parser.parse_args()
    define_string_aliases(args.object)

    with tempfile.TemporaryDirectory() as directory:
        directory_path = Path(directory)
        renamed = directory_path / "renamed.o"
        merged = directory_path / "merged.o"
        subprocess.run(
            [
                args.objcopy,
                "--rename-section",
                ".endsky_strings=.data",
                "--redefine-sym",
                "__dt__7TObjectFv=fn_16_5F55C",
                "--redefine-sym",
                "__dl__10TEndSkyBobFPv=__dl__10TObjSampleFPv",
                "--redefine-sym",
                "PDisp__7TObjectFv=fn_16_11640",
                "--redefine-sym",
                "Disp__7TObjectFv=fn_16_5F3B0",
                "--redefine-sym",
                "TDisp__7TObjectFv=sampleHook1",
                "--redefine-sym",
                "ImmAftSetRaster__7TObjectFv=sampleHook2",
                "--redefine-sym",
                "Debug__7TObjectFv=sampleHook3",
                "--redefine-sym",
                "Render__7TObjectFv=sampleHook4",
                "--redefine-sym",
                "Error__7TObjectFPc=fn_80017854",
                args.object,
                renamed,
            ],
            check=True,
        )
        subprocess.run([args.ld, "-r", renamed, "-o", merged], check=True)
        shutil.copyfile(merged, args.object)

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
