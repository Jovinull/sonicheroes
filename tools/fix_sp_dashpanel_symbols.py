#!/usr/bin/env python3
"""Bind native C++ references to the dash panel's module-local base methods.

Only undefined symbol names change. The original GameCube vtable selects
these REL-local hooks rather than the identically named main.dol methods.
Allocated section bytes and relocation referents must remain unchanged.
"""

import argparse
import os
import shutil
import struct
import subprocess
import tempfile
from pathlib import Path

ALIASES = {
    "Disp__7TObjectFv": "fn_16_11640",
    "PDisp__7TObjectFv": "sampleHook1",
    "Debug__7TObjectFv": "sampleHook3",
    "Render__7TObjectFv": "sampleHook4",
    "__ct__17CSetObjAutoRemoveFv": "fn_16_93C3C",
}


def inspect(path):
    data = path.read_bytes()
    if data[:6] != b"\x7fELF\x01\x02":
        raise ValueError("expected a big-endian ELF32 object")
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data)
    sections = [
        struct.unpack_from(">IIIIIIIIII", data, header[6] + i * header[11])
        for i in range(header[12])
    ]

    def payload(section):
        return data[section[4] : section[4] + section[5]]

    def string(table, offset):
        return table[offset : table.index(0, offset)].decode("ascii")

    section_strings = payload(sections[header[13]])
    section_names = [string(section_strings, s[0]) for s in sections]
    allocated = {}
    symbols = {}
    tables = {}
    for index, section in enumerate(sections):
        if section[2] & 2:
            contents = b"" if section[1] == 8 else payload(section)
            allocated[section_names[index]] = (
                section[1], section[2], section[5], section[8], contents
            )
        if section[1] != 2:
            continue
        names = payload(sections[section[6]])
        table = []
        for offset in range(section[4], section[4] + section[5], section[9]):
            name_offset, value, size, info, other, shndx = struct.unpack_from(
                ">IIIBBH", data, offset
            )
            name = string(names, name_offset)
            symbols[name] = shndx
            if shndx == 0:
                destination = ("undefined", ALIASES.get(name, name))
            elif shndx < len(sections):
                destination = ("section", section_names[shndx], value)
            else:
                destination = ("special", shndx, value, name)
            table.append((destination, size, info, other))
        tables[index] = table
    relocations = []
    for section in sections:
        if section[1] not in (4, 9):
            continue
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info = struct.unpack_from(">II", data, offset)
            addend = struct.unpack_from(">i", data, offset + 8)[0] if section[1] == 4 else None
            relocations.append((
                section_names[section[7]], address, info & 0xFF, addend,
                tables[section[6]][info >> 8],
            ))
    return allocated, symbols, sorted(relocations, key=repr)


def bind_symbols(path, objcopy):
    before, symbols, relocations = inspect(path)
    command = [str(objcopy)]
    for source, target in ALIASES.items():
        if target in symbols and symbols[target] != 0:
            raise ValueError(f"alias target is already defined: {target}")
        if source not in symbols:
            if symbols.get(target) != 0:
                raise ValueError(f"missing undefined reference: {source}")
            continue
        if symbols[source] != 0:
            raise ValueError(f"refusing to rename defined symbol: {source}")
        command.extend(("--redefine-sym", f"{source}={target}"))
    if len(command) == 1:
        return
    descriptor, filename = tempfile.mkstemp(dir=path.parent, prefix=path.name + ".", suffix=".tmp")
    os.close(descriptor)
    output = Path(filename)
    try:
        subprocess.run(command + [str(path), str(output)], check=True)
        after, _, new_relocations = inspect(output)
        if before != after or relocations != new_relocations:
            raise ValueError("symbol binding changed section bytes or relocation referents")
        shutil.copystat(path, output)
        output.replace(path)
    finally:
        output.unlink(missing_ok=True)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", required=True)
    args = parser.parse_args()
    bind_symbols(args.object, args.objcopy)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
