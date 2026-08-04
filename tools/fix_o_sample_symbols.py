#!/usr/bin/env python3

"""Normalize CodeWarrior's deferred atoms in o_sample.cpp.

The reconstructed C++ emits identical function bodies, but declaration visibility
causes three compiler-owned atoms to be placed differently: the vtable follows
the editor strings, the secondary-base adjustor follows the draw stub, and a
duplicate 1.0f literal is emitted at the end of .rodata.  Move those atoms as
indivisible units and canonicalize retail symbol identities.  No instruction is
changed; the final twelve text bytes are only reordered.
"""

import argparse
import struct
import subprocess
from pathlib import Path


RENAMES = {
    "EngineHook__16SampleObjectBaseFv": "fn_80017854",
    "Hook0__10TObjSampleFv": "sampleHook0",
    "Hook1__10TObjSampleFv": "sampleHook1",
    "Hook2__10TObjSampleFv": "sampleHook2",
    "Hook3__10TObjSampleFv": "sampleHook3",
    "Hook4__10TObjSampleFv": "sampleHook4",
    "Destroy__10TObjSampleFs": "__dt__10TObjSampleFv",
    "constructObjSample": "__ct__10TObjSampleFP7TObject",
    "@40@EditOnChange__10TObjSampleFP13SETDATA_PARAM": "sampleEditThunk",
    "@46": "lbl_16_rodata_0",
    "@47": "lbl_16_rodata_4",
    "@49": "lbl_16_rodata_8",
    "SampleMinimumRadius": "lbl_16_rodata_10",
    "SampleLimits": "lbl_16_rodata_14",
}


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", required=True)
    args = parser.parse_args()

    command = [args.objcopy]
    for old, new in RENAMES.items():
        command.extend(["--redefine-sym", f"{old}={new}"])
    command.append(args.object)
    subprocess.run(command, check=True)

    blob = bytearray(args.object.read_bytes())
    if blob[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")

    ehdr = struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0)
    shoff, shentsize, shnum, shstrndx = ehdr[6], ehdr[11], ehdr[12], ehdr[13]
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

    symtab_index, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = blob[strtab[4] : strtab[4] + strtab[5]]
    symbols = []
    symbol_by_name = {}
    for index, offset in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9])):
        symbol = list(struct.unpack_from(">IIIBBH", blob, offset))
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        symbols.append((offset, symbol, name))
        if name:
            symbol_by_name[name] = index

    text_index, text = by_name[".text"]
    data_index, data = by_name[".data"]
    _, rodata = by_name[".rodata"]

    # Retail tail: adjustor thunk (8 bytes), then the empty draw stub (4 bytes).
    text_start = text[4]
    tail = bytes(blob[text_start + 0x664 : text_start + 0x670])
    blob[text_start + 0x664 : text_start + 0x670] = tail[4:12] + tail[0:4]

    # Retail data: declarations through the scales, vtable, then editor strings.
    data_start = data[4]
    old_data = bytes(blob[data_start : data_start + data[5]])
    new_data = old_data[:0x38] + old_data[0x50:0x8C] + old_data[0x3C:0x4D] + b"\0" * 3
    if len(new_data) != 0x88:
        raise AssertionError("bad normalized .data size")
    blob[data_start : data_start + 0x88] = new_data
    data[5] = 0x88
    rodata[5] = 0x28  # discard only the compiler's duplicate trailing 1.0f

    text_values = {"sampleEditThunk": 0x664, "drawSample": 0x66C}
    data_values = {
        "__vt__10TObjSample": 0x38,
        "TObjSampleDisplayName": 0x74,
        "TObjSampleFieldTypes": 0x82,
    }
    for offset, symbol, name in symbols:
        if name == "@91":
            symbol[1] = 0x10
        if name in {
            "lbl_16_rodata_0",
            "lbl_16_rodata_4",
            "lbl_16_rodata_8",
            "lbl_16_rodata_10",
            "lbl_16_rodata_14",
        }:
            symbol[3] = 0x11  # STB_GLOBAL | STT_OBJECT, as in the retail object
        if name in text_values:
            symbol[1] = text_values[name]
        if name in data_values:
            symbol[1] = data_values[name]
        struct.pack_into(">IIIBBH", blob, offset, *symbol)

    # Relocation identities and offsets follow the moved atoms.
    duplicate_literal = symbol_by_name.get("@91")
    canonical_literal = symbol_by_name["lbl_16_rodata_10"]
    for reloc_name in (".rela.text", ".rela.data"):
        _, reloc_section = by_name[reloc_name]
        relocs = []
        for offset in range(
            reloc_section[4], reloc_section[4] + reloc_section[5], reloc_section[9]
        ):
            reloc = list(struct.unpack_from(">IIi", blob, offset))
            symbol_index = reloc[1] >> 8
            reloc_type = reloc[1] & 0xFF
            if reloc_name == ".rela.text":
                if reloc[0] == 0x66C:
                    reloc[0] = 0x668
                if duplicate_literal is not None and symbol_index == duplicate_literal:
                    reloc[1] = (canonical_literal << 8) | reloc_type
            elif 0x58 <= reloc[0] <= 0x88:
                reloc[0] -= 0x18
            relocs.append(reloc)
        relocs.sort(key=lambda item: item[0])
        for offset, reloc in zip(
            range(reloc_section[4], reloc_section[4] + reloc_section[5], reloc_section[9]),
            relocs,
        ):
            struct.pack_into(">IIi", blob, offset, *reloc)

    # Persist the two changed section sizes in the section-header table.
    for _, section in (by_name[".data"], by_name[".rodata"]):
        index = sections.index(section)
        struct.pack_into(">IIIIIIIIII", blob, shoff + index * shentsize, *section)

    args.object.write_bytes(blob)
    args.stamp.touch()


if __name__ == "__main__":
    main()
