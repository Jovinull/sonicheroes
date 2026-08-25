#!/usr/bin/env python3

"""Restore the shared integer-conversion bias in fn_8005438C's split object.

The retail function belonged to a larger translation unit, so its compiler-
generated u16-to-float bias atom is shared and appears here as an undefined
symbol. Compiling the reconstructed split TU creates an identical private
atom. Retarget that one relocation to the retail symbol, then remove the
private atom and the source-level anchor used to make the undefined symbol
available to the ELF symbol table. No instruction byte is changed.
"""

import argparse
import struct
from pathlib import Path


BIAS_SYMBOL = "lbl_8042D3A0"
ANCHOR_SYMBOL = "fn_8005438C_bias_anchor"


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()

    blob = bytearray(args.object.read_bytes())
    if blob[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")

    header = list(struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0))
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
    sections = [
        list(struct.unpack_from(">IIIIIIIIII", blob, shoff + i * shentsize))
        for i in range(shnum)
    ]
    shstr = sections[shstrndx]
    section_names = blob[shstr[4] : shstr[4] + shstr[5]]
    by_name = {
        cstring(section_names, section[0]): (index, section)
        for index, section in enumerate(sections)
    }

    sdata2_index, sdata2 = by_name[".sdata2"]
    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = blob[strtab[4] : strtab[4] + strtab[5]]
    private_bias_index = None
    private_bias_offset = None
    shared_bias_index = None
    anchor_offset = None
    symbol_offsets = range(symtab[4], symtab[4] + symtab[5], symtab[9])
    for index, offset in enumerate(symbol_offsets):
        name_offset, value, size, info, _, section_index = struct.unpack_from(
            ">IIIBBH", blob, offset
        )
        name = cstring(strings, name_offset) if name_offset else ""
        if section_index == sdata2_index and size == 8 and value == 0 and (info & 0xF) == 1:
            private_bias_index = index
            private_bias_offset = offset
        elif name == BIAS_SYMBOL and section_index == 0:
            shared_bias_index = index
        elif name == ANCHOR_SYMBOL:
            anchor_offset = offset

    if sdata2[5] != 8 or private_bias_index is None:
        raise SystemExit("unexpected private conversion-bias atom")
    if shared_bias_index is None or anchor_offset is None:
        raise SystemExit("missing shared bias or source anchor symbol")

    _, rela_text = by_name[".rela.text"]
    replacements = 0
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        relocation_offset, info, addend = struct.unpack_from(">IIi", blob, offset)
        if info >> 8 == private_bias_index:
            info = (shared_bias_index << 8) | (info & 0xFF)
            struct.pack_into(">IIi", blob, offset, relocation_offset, info, addend)
            replacements += 1
    if replacements != 1:
        raise SystemExit(f"expected one conversion-bias relocation, found {replacements}")

    # Keep MWCC's object metadata and file layout intact so MWLink preserves
    # the original exception-table packing. Remove only the section headers
    # for the two temporary source atoms and their relocation section.
    removed_indices = {
        by_name[".sdata"][0],
        by_name[".sdata2"][0],
        by_name[".rela.sdata"][0],
    }
    for offset in (private_bias_offset, anchor_offset):
        name_offset = struct.unpack_from(">I", blob, offset)[0]
        struct.pack_into(">IIIBBH", blob, offset, name_offset, 0, 0, 0, 0, 0xFFF1)
    symtab[7] = shared_bias_index

    kept_indices = [index for index in range(shnum) if index not in removed_indices]
    old_to_new = {old: new for new, old in enumerate(kept_indices)}
    for offset in symbol_offsets:
        section_index = struct.unpack_from(">H", blob, offset + 14)[0]
        if section_index in removed_indices:
            struct.pack_into(">H", blob, offset + 14, 0xFFF1)
        elif 0 < section_index < shnum:
            struct.pack_into(">H", blob, offset + 14, old_to_new[section_index])

    kept_sections = []
    for old_index in kept_indices:
        section = sections[old_index].copy()
        if section[6]:
            section[6] = old_to_new[section[6]]
        if section[1] == 4:  # SHT_RELA
            section[7] = old_to_new[section[7]]
        kept_sections.append(section)
    for index, section in enumerate(kept_sections):
        struct.pack_into(">IIIIIIIIII", blob, shoff + index * shentsize, *section)
    header[12] = len(kept_sections)
    header[13] = old_to_new[shstrndx]
    struct.pack_into(">16sHHIIIIIHHHHHH", blob, 0, *header)
    args.object.write_bytes(blob)

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
