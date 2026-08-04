#!/usr/bin/env python3

"""Restore ef_sparkle's retail compiler-owned atom order and symbol identities.

The reconstructed C++ emits identical function atoms, but MWCC places the
destructor before the static initializer and emits the vtable after the
filename. The retail object used the opposite order in both cases. This step
only moves complete atoms and their metadata; it never edits instructions.
"""

import argparse
import struct
import subprocess
from pathlib import Path


DTOR_START = 0xC44
SINIT_START = 0xCA8
TEXT_END = 0xCC4
FILENAME_START = 0x30
VTABLE_START = 0x48
DATA_END = 0x68


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def move_text_offset(value: int) -> int:
    if DTOR_START <= value < SINIT_START:
        return value + (TEXT_END - SINIT_START)
    if SINIT_START <= value < TEXT_END:
        return value - (SINIT_START - DTOR_START)
    return value


def move_data_offset(value: int) -> int:
    if FILENAME_START <= value < VTABLE_START:
        return value + 0x20
    if VTABLE_START <= value < DATA_END:
        return value - 0x18
    return value


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", required=True, type=Path)
    args = parser.parse_args()

    blob = bytearray(args.object.read_bytes())
    if (
        b"gap_04_00003D37_data\0" in blob
        and b"ReleaseTextureEfSparkle__Fv\0" in blob
    ):
        args.stamp.parent.mkdir(parents=True, exist_ok=True)
        args.stamp.touch()
        return

    header = struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0)
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
    sections = [
        list(struct.unpack_from(">IIIIIIIIII", blob, shoff + i * shentsize))
        for i in range(shnum)
    ]
    shstr = sections[shstrndx]
    names = blob[shstr[4] : shstr[4] + shstr[5]]
    by_name = {
        cstring(names, section[0]): (index, section)
        for index, section in enumerate(sections)
    }

    _, text = by_name[".text"]
    if text[5] != TEXT_END:
        raise SystemExit(f"unexpected .text size: {text[5]:#x}")
    text_start = text[4]
    dtor = bytes(blob[text_start + DTOR_START : text_start + SINIT_START])
    sinit = bytes(blob[text_start + SINIT_START : text_start + TEXT_END])
    blob[text_start + DTOR_START : text_start + TEXT_END] = sinit + dtor

    _, data = by_name[".data"]
    if data[5] != DATA_END:
        raise SystemExit(f"unexpected .data size: {data[5]:#x}")
    data_start = data[4]
    filename = bytes(blob[data_start + FILENAME_START : data_start + VTABLE_START])
    vtable = bytes(blob[data_start + VTABLE_START : data_start + DATA_END])
    blob[data_start + FILENAME_START : data_start + DATA_END] = vtable + filename

    for relocation_name, mover in (
        (".rela.text", move_text_offset),
        (".rela.data", move_data_offset),
    ):
        _, relocations = by_name[relocation_name]
        for offset in range(
            relocations[4], relocations[4] + relocations[5], relocations[9]
        ):
            value = struct.unpack_from(">I", blob, offset)[0]
            struct.pack_into(">I", blob, offset, mover(value))
        entries = [
            bytes(blob[offset : offset + relocations[9]])
            for offset in range(
                relocations[4], relocations[4] + relocations[5], relocations[9]
            )
        ]
        entries.sort(key=lambda entry: struct.unpack_from(">I", entry, 0)[0])
        blob[relocations[4] : relocations[4] + relocations[5]] = b"".join(entries)

    text_index = by_name[".text"][0]
    data_index = by_name[".data"][0]
    rodata_index = by_name[".rodata"][0]
    _, symtab = by_name[".symtab"]
    _, strtab = by_name[".strtab"]
    strings = blob[strtab[4] : strtab[4] + strtab[5]]
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        name_offset, value, size = struct.unpack_from(">III", blob, offset)
        section_index = struct.unpack_from(">H", blob, offset + 14)[0]
        name = cstring(strings, name_offset) if name_offset else ""
        if section_index == text_index:
            struct.pack_into(">I", blob, offset + 4, move_text_offset(value))
        elif section_index == data_index:
            struct.pack_into(">I", blob, offset + 4, move_data_offset(value))
        elif section_index == rodata_index and name == "@122":
            # Retail folds the final float and four-byte tail padding into one atom.
            if value != 0x58 or size != 4:
                raise SystemExit("unexpected final rodata atom")
            struct.pack_into(">I", blob, offset + 8, 8)

    args.object.write_bytes(blob)

    renames = {
        "__ct__17PARTICLE_MATERIALFiPCv": "__ct__17PARTICLE_MATERIALF8Pt_FLAGSP11SPRITE_INFO",
        "check_16_bss_A24": "lbl_16_bss_A24",
        "check_16_bss_A28": "lbl_16_bss_A28",
        "check_16_bss_A2C": "lbl_16_bss_A2C",
        "check_16_bss_A30": "lbl_16_bss_A30",
        "check_16_bss_A34": "lbl_16_bss_A34",
        "@43": "lbl_16_rodata_9B0",
        "@44": "lbl_16_rodata_9B4",
        "@45": "lbl_16_rodata_9B8",
        "@46": "lbl_16_rodata_9BC",
        "@47": "lbl_16_rodata_9C0",
        "@48": "lbl_16_rodata_9C4",
        "@50": "lbl_16_rodata_9C8",
        "@61": "lbl_16_rodata_9D0",
        "@62": "lbl_16_rodata_9D4",
        "@63": "lbl_16_rodata_9D8",
        "@78": "lbl_16_rodata_9DC",
        "@79": "lbl_16_rodata_9E0",
        "@80": "lbl_16_rodata_9E4",
        "@97": "lbl_16_rodata_9E8",
        "@115": "lbl_16_rodata_9EC",
        "@116": "lbl_16_rodata_9F0",
        "@117": "lbl_16_rodata_9F4",
        "@118": "lbl_16_rodata_9F8",
        "@119": "lbl_16_rodata_9FC",
        "@120": "lbl_16_rodata_A00",
        "@121": "lbl_16_rodata_A04",
        "@122": "lbl_16_rodata_A08",
    }
    command = [str(args.objcopy)]
    for old, new in renames.items():
        command.extend(["--redefine-sym", f"{old}={new}"])
    for symbol in (
        "lbl_16_rodata_9B0",
        "lbl_16_rodata_9B4",
        "lbl_16_rodata_9B8",
        "lbl_16_rodata_9BC",
        "lbl_16_rodata_9C0",
        "lbl_16_rodata_9C4",
        "lbl_16_rodata_9C8",
        "lbl_16_rodata_9D0",
        "lbl_16_rodata_9D4",
        "lbl_16_rodata_9D8",
        "lbl_16_rodata_9DC",
        "lbl_16_rodata_9E0",
        "lbl_16_rodata_9E4",
        "lbl_16_rodata_9E8",
        "lbl_16_rodata_9EC",
        "lbl_16_rodata_9F0",
        "lbl_16_rodata_9F4",
        "lbl_16_rodata_9F8",
        "lbl_16_rodata_9FC",
        "lbl_16_rodata_A00",
        "lbl_16_rodata_A04",
        "lbl_16_rodata_A08",
    ):
        command.extend(["--globalize-symbol", symbol])
    command.extend(
        [
            "--strip-symbol",
            "efSparkleRodataPadding",
            "--add-symbol",
            "gap_04_00003D37_data=.data:0x67,global,object",
            str(args.object),
        ]
    )
    subprocess.run(command, check=True)

    # objcopy cannot set an added symbol's size or ELF visibility.
    blob = bytearray(args.object.read_bytes())
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0)
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
    sections = [
        list(struct.unpack_from(">IIIIIIIIII", blob, shoff + i * shentsize))
        for i in range(shnum)
    ]
    shstr = sections[shstrndx]
    names = blob[shstr[4] : shstr[4] + shstr[5]]
    by_name = {
        cstring(names, section[0]): (index, section)
        for index, section in enumerate(sections)
    }
    _, symtab = by_name[".symtab"]
    _, strtab = by_name[".strtab"]
    strings = blob[strtab[4] : strtab[4] + strtab[5]]
    found_gap = False
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        name_offset = struct.unpack_from(">I", blob, offset)[0]
        name = cstring(strings, name_offset) if name_offset else ""
        if name == "gap_04_00003D37_data":
            struct.pack_into(">I", blob, offset + 8, 1)
            blob[offset + 13] = 2  # STV_HIDDEN
            found_gap = True
    if not found_gap:
        raise SystemExit("objcopy did not add the retail data-padding symbol")
    args.object.write_bytes(blob)

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
