#!/usr/bin/env python3

"""Normalize MWCC's e_appear_spboss_pos compiler atoms to retail order."""

import argparse
import os
import struct
import subprocess
import tempfile
from pathlib import Path


SYMBOL_RENAMES = {
    "__vt__21TEnemyAppearSPBossPos": "TEnemyAppearSPBossPosVtable",
    "@40@EditOnChange__21TEnemyAppearSPBossPosFP13SETDATA_PARAM": (
        "TEnemyAppearSPBossPosEditThunk"
    ),
    "Virtual2__28TEnemyAppearSPBossPosPrimaryFv": "fn_16_11640",
    "Virtual3__28TEnemyAppearSPBossPosPrimaryFv": "fn_16_5F3B0",
    "Virtual4__28TEnemyAppearSPBossPosPrimaryFv": "fn_16_F4",
    "Virtual5__28TEnemyAppearSPBossPosPrimaryFv": "fn_16_F8",
    "Virtual6__28TEnemyAppearSPBossPosPrimaryFv": "fn_16_FC",
    "Virtual7__28TEnemyAppearSPBossPosPrimaryFv": "fn_80017854",
    "Virtual8__28TEnemyAppearSPBossPosPrimaryFv": "fn_16_100",
}


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def remap_data_offset(offset: int) -> int:
    if 0x40 <= offset < 0x70:
        return offset + 0x10
    if 0x70 <= offset < 0x80:
        return offset - 0x30
    if 0x80 <= offset < 0x98:
        return offset + 0x3C
    if 0x98 <= offset < 0xD4:
        return offset - 0x18
    return offset


def fix_object(path: Path) -> None:
    blob = bytearray(path.read_bytes())
    if blob[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")

    ehdr = struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0)
    shoff, shentsize, shnum, shstrndx = ehdr[6], ehdr[11], ehdr[12], ehdr[13]
    sections = [
        list(struct.unpack_from(">IIIIIIIIII", blob, shoff + i * shentsize))
        for i in range(shnum)
    ]
    shstr = sections[shstrndx]
    shstr_data = blob[shstr[4] : shstr[4] + shstr[5]]
    by_name = {
        cstring(shstr_data, section[0]): (index, section)
        for index, section in enumerate(sections)
    }

    data_index, data_section = by_name[".data"]
    if data_section[5] != 0xD4:
        raise SystemExit("unexpected e_appear_spboss_pos data size")
    start = data_section[4]
    original = bytes(blob[start : start + 0xD4])
    reordered = bytearray(0xD8)
    reordered[0x00:0x40] = original[0x00:0x40]
    reordered[0x40:0x50] = original[0x70:0x80]
    reordered[0x50:0x80] = original[0x40:0x70]
    reordered[0x80:0xBC] = original[0x98:0xD4]
    reordered[0xBC:0xD4] = original[0x80:0x98]
    blob[start : start + 0xD8] = reordered
    data_section[5] = 0xD8

    _, rela_data = by_name[".rela.data"]
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        relocation = list(struct.unpack_from(">IIi", blob, offset))
        relocation[0] = remap_data_offset(relocation[0])
        struct.pack_into(">IIi", blob, offset, *relocation)

    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = blob[strtab[4] : strtab[4] + strtab[5]]
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", blob, offset))
        if symbol[5] == data_index:
            symbol[1] = remap_data_offset(symbol[1])
            struct.pack_into(">IIIBBH", blob, offset, *symbol)

    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", blob, shoff + index * shentsize, *section)
    path.write_bytes(blob)


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
