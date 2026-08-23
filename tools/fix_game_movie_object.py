#!/usr/bin/env python3

"""Finalize movie.cpp's compiler object to the retail linker-input layout."""

import argparse
import os
import struct
import subprocess
import tempfile
from pathlib import Path

from fix_sp_adv_stg_failed_object import cstring, fix_object


SYMBOL_RENAMES = {
    "Exec__7TObjectFv": "fn_80018984",
    "Disp__7TObjectFv": "fn_80018988",
    "ImmAftSetRaster__7TObjectFv": "fn_80018950",
    "Debug__7TObjectFv": "fn_80018954",
    "Render__7TObjectFv": "fn_80018958",
}


def elf_symbols(path: Path):
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
    for index, offset in enumerate(
        range(symtab[4], symtab[4] + symtab[5], symtab[9])
    ):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        symbols.append((index, offset, symbol, name))
    return data, sections, symbols


def assert_unused_delete_labels(path: Path) -> None:
    data, sections, symbols = elf_symbols(path)
    by_name = {name: (index, symbol) for index, _, symbol, name in symbols}
    label_indices = set()
    for name in ("@44", "@45"):
        index, symbol = by_name.get(name, (None, None))
        if index is None or symbol[1:3] != [0, 0] or symbol[3] != 1 or symbol[5] != 0:
            raise SystemExit(f"unexpected removed weak-delete label {name}")
        label_indices.add(index)
    for section in sections:
        if section[1] != 4:  # SHT_RELA
            continue
        for offset in range(section[4], section[4] + section[5], section[9]):
            _, info, _ = struct.unpack_from(">IIi", data, offset)
            if info >> 8 in label_indices:
                raise SystemExit("removed weak-delete label still has relocation users")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    args = parser.parse_args()

    fix_object(args.object)
    assert_unused_delete_labels(args.object)
    with tempfile.NamedTemporaryFile(
        dir=args.object.parent, delete=False, suffix=".o"
    ) as temporary:
        output = Path(temporary.name)
    try:
        command = [str(args.objcopy)]
        command.extend(["--strip-symbol", "@44", "--strip-symbol", "@45"])
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
