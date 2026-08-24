#!/usr/bin/env python3

"""Restore the retail alignment of this TU's compiler-emitted .rodata atom."""

import argparse
import shutil
import struct
import subprocess
import tempfile
from pathlib import Path


RENAMES = {
    "__dl__24TEnemyAppearChaosEmeraldFPv": "__dl__10TObjSampleFPv",
    "__dt__7TObjectFv": "fn_16_5F55C",
    "TDisp__7TObjectFv": "sampleHook1",
    "ImmAftSetRaster__7TObjectFv": "sampleHook2",
    "Debug__7TObjectFv": "sampleHook3",
    "Render__7TObjectFv": "sampleHook4",
    "PDisp__7TObjectFv": "fn_16_11640",
    "Disp__7TObjectFv": "fn_16_5F3B0",
}


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    args = parser.parse_args()

    with tempfile.TemporaryDirectory() as temp_dir:
        output = Path(temp_dir) / args.object.name
        command = [str(args.objcopy)]
        for old, new in RENAMES.items():
            command.extend(["--redefine-sym", f"{old}={new}"])
        command.extend([str(args.object), str(output)])
        subprocess.run(command, check=True)
        shutil.copyfile(output, args.object)

    data = bytearray(args.object.read_bytes())
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
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
    for index, section in enumerate(sections):
        if cstring(names, section[0]) == ".rodata":
            if section[5] != 12 or section[8] != 8:
                raise SystemExit(
                    f"unexpected .rodata size/alignment: {section[5]}/{section[8]}"
                )
            section[8] = 4
            struct.pack_into(
                ">IIIIIIIIII", data, shoff + index * shentsize, *section
            )
            break
    else:
        raise SystemExit("missing .rodata")

    # MWLD consults CodeWarrior's parallel section-symbol metadata in
    # .comment instead of relying only on ELF sh_addralign.
    rodata_index, _ = by_name[".rodata"]
    _, symtab = by_name[".symtab"]
    _, comment = by_name[".comment"]
    for symbol_index, offset in enumerate(
        range(symtab[4], symtab[4] + symtab[5], symtab[9])
    ):
        symbol = struct.unpack_from(">IIIBBH", data, offset)
        if symbol[3] & 0xF == 3 and symbol[5] == rodata_index:
            struct.pack_into(">I", data, comment[4] + 0x2C + symbol_index * 8, 4)
            break
    else:
        raise SystemExit("missing .rodata section symbol")

    args.object.write_bytes(data)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
