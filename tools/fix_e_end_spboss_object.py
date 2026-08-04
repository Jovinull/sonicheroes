#!/usr/bin/env python3

"""Normalize compiler-emitted e_end_spboss atoms to their retail object order."""

import argparse
import os
import struct
import subprocess
import tempfile
from pathlib import Path


SYMBOL_RENAMES = {
    "__vt__15TEnemyEndSPBoss": "TEnemyEndSPBossVtable",
    "@40@EditOnChange__15TEnemyEndSPBossFP13SETDATA_PARAM": (
        "TEnemyEndSPBossEditThunk"
    ),
    "Virtual2__22TEnemyEndSPBossPrimaryFv": "fn_16_11640",
    "Virtual3__22TEnemyEndSPBossPrimaryFv": "fn_16_5F3B0",
    "Virtual4__22TEnemyEndSPBossPrimaryFv": "fn_16_F4",
    "Virtual5__22TEnemyEndSPBossPrimaryFv": "fn_16_F8",
    "Virtual6__22TEnemyEndSPBossPrimaryFv": "fn_16_FC",
    "Virtual7__22TEnemyEndSPBossPrimaryFv": "fn_80017854",
    "Virtual8__22TEnemyEndSPBossPrimaryFv": "fn_16_100",
}


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def remap_data_offset(offset: int) -> int:
    # MWCC emits explicit data before its synthesized vtable. Retail placed the
    # registration atom after that vtable.
    if 0x14 <= offset < 0x24:
        return offset + 0x3C
    if 0x24 <= offset < 0x60:
        return offset - 0x10
    return offset


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

    data_index, data_section = by_name[".data"]
    if data_section[5] != 0x60:
        raise SystemExit("unexpected e_end_spboss data size")
    start = data_section[4]
    original = bytes(data[start : start + 0x60])
    data[start : start + 0x60] = original[:0x14] + original[0x24:] + original[0x14:0x24]

    _, rela_data = by_name[".rela.data"]
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        relocation = list(struct.unpack_from(">IIi", data, offset))
        relocation[0] = remap_data_offset(relocation[0])
        struct.pack_into(">IIi", data, offset, *relocation)

    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        if symbol[5] == data_index:
            symbol[1] = remap_data_offset(symbol[1])
            struct.pack_into(">IIIBBH", data, offset, *symbol)

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
