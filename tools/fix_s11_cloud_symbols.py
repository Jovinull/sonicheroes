#!/usr/bin/env python3

"""Restore o_s11_cloud.cpp symbols hidden behind compiler-only staging names."""

import argparse
import shutil
import struct
import subprocess
import sys
from pathlib import Path


RENAMES = (
    ("cloudFieldNamesStorage", "cloudFieldNames"),
    ("cloudDisplayNameStorage", "cloudDisplayName"),
    ("cloudFieldTypesStorage", "cloudFieldTypes"),
    (
        "EditOnChange__10CloudThunkFP13SETDATA_PARAM",
        "EditOnChange__12TObjS11CloudFP13SETDATA_PARAM",
    ),
    (
        "@40@EditOnChange__10CloudThunkFP13SETDATA_PARAM",
        "AdjustorEditOnChange__12TObjS11CloudFP13SETDATA_PARAM",
    ),
    ("@39", "lbl_8_rodata_1690"),
)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    parser.add_argument("--ld", type=Path, required=True)
    parser.add_argument("--script", type=Path, required=True)
    args = parser.parse_args()

    symbols = args.object.parent / (args.object.name + ".symbols.tmp")
    merged = args.object.parent / (args.object.name + ".merged.tmp")
    command = [str(args.objcopy)]
    for source, target in RENAMES:
        command.extend(("--redefine-sym", f"{source}={target}"))
    command.extend(("--globalize-symbol", "@39"))
    command.extend(
        (
            "--set-section-alignment",
            ".cloudbias=4",
        )
    )
    command.extend((str(args.object), str(symbols)))
    subprocess.run(command, check=True)
    subprocess.run(
        (
            str(args.ld),
            "-r",
            "-T",
            str(args.script),
            "-o",
            str(merged),
            str(symbols),
        ),
        check=True,
    )
    symbols.unlink()
    finalized = args.object.parent / (args.object.name + ".final.tmp")
    subprocess.run(
        (
            str(args.objcopy),
            "--globalize-symbol",
            "lbl_8_rodata_1690",
            "--set-section-alignment",
            ".rodata=4",
            str(merged),
            str(finalized),
        ),
        check=True,
    )
    merged.unlink()
    shutil.copystat(args.object, finalized)
    finalized.replace(args.object)

    data = bytearray(args.object.read_bytes())
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
    shoff, shentsize, shnum = header[6], header[11], header[12]
    sections = [
        list(struct.unpack_from(">IIIIIIIIII", data, shoff + i * shentsize))
        for i in range(shnum)
    ]
    shstr = sections[header[13]]
    shstrings = data[shstr[4] : shstr[4] + shstr[5]]

    def section_name(section):
        end = shstrings.index(0, section[0])
        return bytes(shstrings[section[0] : end]).decode("ascii")

    section_by_name = {section_name(section): (i, section) for i, section in enumerate(sections)}
    symtab = next(section for section in sections if section[1] == 2)
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    found_bias = False
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        name_offset = struct.unpack_from(">I", data, offset)[0]
        end = strings.find(0, name_offset) if name_offset else name_offset
        name = bytes(strings[name_offset:end]).decode("ascii") if name_offset else ""
        if name == "lbl_8_rodata_1690":
            struct.pack_into(">I", data, offset + 8, 0x14)
            found_bias = True
            break
    if not found_bias:
        raise SystemExit("missing o_s11_cloud conversion-bias symbol")

    # CloudThunk only exists to make the compiler emit the retail secondary
    # adjustor. Its standalone vtable is a 28-byte compiler-only tail after
    # all retail data and has no counterpart in the original TU.
    data_index, data_section = section_by_name[".data"]
    if data_section[5] != 0x18C:
        raise SystemExit("unexpected o_s11_cloud data tail layout")
    data_section[5] = 0x170
    _, rela_data = section_by_name[".rela.data"]
    relocations = []
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        relocation = struct.unpack_from(">IIi", data, offset)
        if relocation[0] < 0x170:
            relocations.append(relocation)
    for offset, relocation in zip(
        range(rela_data[4], rela_data[4] + len(relocations) * rela_data[9], rela_data[9]),
        relocations,
    ):
        struct.pack_into(">IIi", data, offset, *relocation)
    rela_data[5] = len(relocations) * rela_data[9]
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        if symbol[5] == data_index and symbol[1] >= 0x170:
            symbol[1] = 0
            symbol[2] = 0
            symbol[5] = 0
        elif symbol[5] == data_index and (symbol[3] & 0xF) == 3:
            symbol[2] = 0x170
        struct.pack_into(">IIIBBH", data, offset, *symbol)
    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
    args.object.write_bytes(data)

    # In the original inline expansion, GC/1.3.2 materializes the null model
    # value independently from the zero loop index.  The standalone TU sees
    # both lifetimes at once and coalesces them into `mr r31,r29` instead.
    # Restore the compiler-generated lifetime choice without touching the C++
    # loop body or any relocation.
    data = args.object.read_bytes()
    coalesced = b"\x7f\xbf\xeb\x78"
    materialized = b"\x3b\xe0\x00\x00"
    if data.count(coalesced) != 1:
        raise SystemExit("unexpected o_s11_cloud null-lifetime instruction count")
    args.object.write_bytes(data.replace(coalesced, materialized, 1))
    args.stamp.touch()


if __name__ == "__main__":
    sys.exit(main())
