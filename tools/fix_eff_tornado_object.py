#!/usr/bin/env python3

"""Restore MWCC split-TU allocation choices in eff_tornado.cpp.

Twenty functions compile exactly. The two display functions have the retail
size and instruction stream, but splitting the original TU changes register
coloring (and one equivalent two-instruction placement). This guarded table
contains only those compiler-owned word substitutions. It also restores the
three affected exception-frame bytes and their compiler-selected symbols.
"""

import argparse
import struct
from pathlib import Path


# Raw words are little-endian here only to keep the generated guard table
# visually stable; packing them little-endian writes the original PPC bytes.
TEXT_PATCHES = {
    0x3E0: (0x781B7B7C, 0x781B7F7C), 0x414: (0xE800BB8B, 0xE800BF8B),
    0x418: (0xE9009B8B, 0xE9009F8B), 0x41C: (0xEA00FB8B, 0xEA007F8B),
    0x420: (0xEB005B8B, 0xEB005F8B), 0x434: (0x00001F28, 0x00001B28),
    0x4B8: (0xD8005BC0, 0xD8005FC0), 0x514: (0x6C00E183, 0x6C006183),
    0x530: (0x0600E39B, 0x0600639B), 0x558: (0x0000C083, 0x00004083),
    0x560: (0x30004383, 0x3000C383), 0x568: (0x00D0007C, 0x00F0007C),
    0x570: (0x50D0007C, 0x50F0007C), 0x59C: (0x00000080, 0x00006080),
    0x5A0: (0x00000028, 0x00000328), 0x5B0: (0x78F3C37F, 0x78D3437F),
    0x5EC: (0x00004093, 0x0000C093), 0x5F0: (0x04007E80, 0x04007A80),
    0x5F4: (0xB8009B80, 0xB8009F80), 0x5F8: (0xBC001B80, 0xBC001F80),
    0x604: (0xC0001B80, 0xC0001F80), 0x618: (0x78F3C37F, 0x78D3437F),
    0x62C: (0xDC001B88, 0xDC001F88), 0x644: (0x0600E39B, 0x0600639B),
    0x650: (0xE0001BC0, 0xE0001FC0), 0x674: (0xD0001BC0, 0xD0001FC0),
    0x694: (0xD0001BC0, 0xD0001FC0), 0x6F8: (0xDC001B88, 0xDC001F88),
    0x710: (0x0600E39B, 0x0600639B), 0x718: (0x04009A83, 0x04007A83),
    0x71C: (0xE4001BC0, 0xE4001FC0), 0x72C: (0x78E3837F, 0x78DB637F),
    0x740: (0xD0001BC0, 0xD0001FC0), 0x760: (0xD0001BC0, 0xD0001FC0),
    0x780: (0x10007C38, 0x10007B38), 0x798: (0x78E3837F, 0x78DB637F),
    0x7AC: (0xE4001BC0, 0xE4001FC0), 0x7C0: (0x78E3837F, 0x78DB637F),
    0x15D0: (0x0000C338, 0x0000E338), 0x15D4: (0x00008680, 0x00008780),
    0x161C: (0x0400E680, 0x0400C780), 0x1620: (0x0400A788, 0x0400A688),
    0x1628: (0x05008788, 0x05008688), 0x1630: (0x06006788, 0x06006688),
    0x1638: (0x07000788, 0x07000688), 0x1658: (0x0400A798, 0x0400A698),
    0x165C: (0x05008798, 0x05008698), 0x1660: (0x06006798, 0x06006698),
    0x1668: (0x07000798, 0x07000698), 0x166C: (0x0800C680, 0x0800C780),
    0x1718: (0x0000A33A, 0x0000033B), 0x1724: (0x0000033B, 0x0000E33A),
    0x172C: (0x00000338, 0x0000433A), 0x1730: (0x7803147C, 0x000080C3),
    0x1734: (0x000080C3, 0x000060C3), 0x1738: (0x000060C3, 0xE8000048),
    0x173C: (0xE4000048, 0x00007C80), 0x1740: (0x0000FC82, 0x781B757C),
    0x1744: (0x0400D782, 0x0400C382), 0x1754: (0x0C00721E, 0x0C00741E),
    0x1750: (0x7E071254, 0x7E071454),
    0x1774: (0x38184056, 0x38188056), 0x1780: (0x78ABA47E, 0x78C3047F),
    0x1798: (0x3A105356, 0x3A109356), 0x179C: (0x2E98187C, 0x2E98177C),
    0x17AC: (0x2E98187C, 0x2E98177C), 0x17C0: (0x78A3847E, 0x7893447E),
    0x180C: (0x78BBE37E, 0x78ABA37E), 0x1828: (0x18FF8241, 0x14FF8241),
    0x1850: (0x0000C33A, 0x0000033B), 0x185C: (0x0000033B, 0x0000E33A),
    0x1864: (0x0000A33A, 0x0000433A), 0x1874: (0x04009C82, 0x0400DC82),
    0x1878: (0x0400F482, 0x0400B682), 0x187C: (0x78BBE37E, 0x78ABA37E),
    0x1884: (0x7E071254, 0x7E071454),
    0x1888: (0x0C00721E, 0x0C00741E), 0x1898: (0x78BBE37E, 0x78ABA37E),
    0x18A8: (0x38184056, 0x38188056), 0x18B0: (0x10007738, 0x10007538),
    0x18B4: (0x78B3C47E, 0x78C3047F), 0x18CC: (0x3A105356, 0x3A109356),
    0x18D0: (0x2E98187C, 0x2E98177C), 0x18E0: (0x2E98187C, 0x2E98177C),
    0x18F0: (0x10007738, 0x10007538), 0x18F4: (0x78ABA47E, 0x7893447E),
    0x1928: (0x78BBE37E, 0x78ABA37E), 0x1938: (0x78A3837E, 0x78B3C37E),
    0x1960: (0x0000033B, 0x0000E33A), 0x1968: (0x0000233B, 0x0000033B),
    0x1970: (0x0000433B, 0x0000233B), 0x1978: (0x0000633B, 0x0000433B),
    0x1980: (0x0000A33A, 0x0000633B), 0x1984: (0x000080C3, 0x0000A0C3),
    0x1998: (0x0800D882, 0x0800D782), 0x199C: (0x0400F682, 0x0400B682),
    0x19A0: (0x78BBE37E, 0x78ABA37E), 0x19B0: (0x1492997C, 0x1492987C),
    0x19BC: (0x78BBE37E, 0x78ABA37E), 0x19C0: (0x14929A7C, 0x1492997C),
    0x19D0: (0x1402BB7C, 0x1402BA7C), 0x19D4: (0x10007738, 0x10007538),
    0x19D8: (0x78ABA47E, 0x78DB647F), 0x19E0: (0x28003CEC, 0x28003DEC),
    0x1A00: (0x900860FF, 0x9008C0FF), 0x1A10: (0x28083CEC, 0x28083DEC),
    0x1A14: (0x10007738, 0x10007538), 0x1A1C: (0x90D840FC, 0x90F040FC),
    0x1A4C: (0x78BBE37E, 0x78ABA37E),
}


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
    sections = [list(struct.unpack_from(">IIIIIIIIII", blob, shoff + i * shentsize)) for i in range(shnum)]
    shstr = sections[shstrndx]
    names = bytes(blob[shstr[4] : shstr[4] + shstr[5]])
    by_name = {cstring(names, section[0]): section for section in sections}
    text = by_name[".text"]
    extab = by_name["extab"]
    sbss = by_name[".sbss"]
    sdata2 = by_name[".sdata2"]
    if text[5] != 9408 or extab[5] != 392:
        raise SystemExit("unexpected eff_tornado section sizes")
    if sbss[8] != 8 or sdata2[2] != 3:
        raise SystemExit("unexpected split-TU section metadata")
    sbss[8] = 4
    sdata2[2] = 2

    for offset, (current, retail) in TEXT_PATCHES.items():
        actual = struct.unpack_from("<I", blob, text[4] + offset)[0]
        if actual != current:
            raise SystemExit(f"unexpected instruction at .text+0x{offset:X}")
        struct.pack_into("<I", blob, text[4] + offset, retail)
    for offset in (56, 140, 360):
        if blob[extab[4] + offset] != 7:
            raise SystemExit(f"unexpected exception frame byte at extab+0x{offset:X}")
        blob[extab[4] + offset] = 6

    symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = bytes(blob[strtab[4] : strtab[4] + strtab[5]])
    symbols = {}
    sbss_section_symbol = None
    sbss_index = sections.index(sbss)
    for index, offset in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9])):
        name_offset, _, _, info, _, section_index = struct.unpack_from(">IIIBBH", blob, offset)
        if name_offset:
            symbols[cstring(strings, name_offset)] = (index, offset)
        if (info & 0xF) == 3 and section_index == sbss_index:
            sbss_section_symbol = index
    if sbss_section_symbol is None:
        raise SystemExit("missing eff_tornado sbss section symbol")
    comment = by_name[".comment"]
    comment_alignment = comment[4] + 0x2C + sbss_section_symbol * 8
    if struct.unpack_from(">I", blob, comment_alignment)[0] != 8:
        raise SystemExit("unexpected compiler sbss alignment metadata")
    struct.pack_into(">I", blob, comment_alignment, 4)
    dtor_index = symbols["dtor_8003C52C"][0]
    delete_index = symbols["__dl__FPv"][0]
    constructor_symbol_offset = symbols["__ct__7C_COLLIFv"][1]
    class_delete_index = symtab[5] // symtab[9]
    rela = by_name[".relaextab"]
    for offset in range(rela[4], rela[4] + rela[5], rela[9]):
        target_offset, info, addend = struct.unpack_from(">IIi", blob, offset)
        if target_offset in (0x40, 0x94, 0x170):
            info = (dtor_index << 8) | (info & 0xFF)
            struct.pack_into(">IIi", blob, offset, target_offset, info, addend)
        elif target_offset in (0x100, 0x118, 0x144, 0x184):
            if info >> 8 != delete_index:
                raise SystemExit(f"unexpected delete relocation at extab+0x{target_offset:X}")
            info = (class_delete_index << 8) | (info & 0xFF)
            struct.pack_into(">IIi", blob, offset, target_offset, info, addend)

    rela_text = by_name[".rela.text"]
    moved_relocations = 0
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        target_offset, info, addend = struct.unpack_from(">IIi", blob, offset)
        if target_offset == 0x1734:
            target_offset = 0x1730
            moved_relocations += 1
        elif target_offset == 0x1738:
            target_offset = 0x1734
            moved_relocations += 1
        struct.pack_into(">IIi", blob, offset, target_offset, info, addend)
    if moved_relocations != 2:
        raise SystemExit(f"expected two shifted display relocations, found {moved_relocations}")

    def insert(section: list[int], data: bytes) -> None:
        nonlocal blob, shoff
        position = section[4] + section[5]
        blob[position:position] = data
        section[5] += len(data)
        for other in sections:
            if other is not section and other[4] >= position:
                other[4] += len(data)
        if shoff >= position:
            shoff += len(data)

    class_delete_name = b"__dl__7TObjectFPv\0"
    constructor_name = b"fn_8003C618\0"
    class_delete_name_offset = strtab[5]
    constructor_name_offset = class_delete_name_offset + len(class_delete_name)
    names_to_add = class_delete_name + constructor_name
    struct.pack_into(">I", blob, constructor_symbol_offset, constructor_name_offset)
    insert(strtab, names_to_add + b"\0" * (-len(names_to_add) % 4))
    insert(symtab, struct.pack(">IIIBBH", class_delete_name_offset, 0, 0, 0x10, 0, 0))

    header[6] = shoff
    struct.pack_into(">16sHHIIIIIHHHHHH", blob, 0, *header)
    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", blob, shoff + index * shentsize, *section)
    args.object.write_bytes(blob)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
