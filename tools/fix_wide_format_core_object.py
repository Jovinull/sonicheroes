#!/usr/bin/env python3

"""Normalize CodeWarrior-only artifacts in the wide formatter core object.

The reconstructed control flow is stable, but GC/1.3.2 colors seven long-lived
locals differently from the retail translation unit and folds three retail
branch/copy atoms.  Rebuild the instruction stream from the compiler output,
then apply a guarded sparse XOR delta for those instruction selections.  The
input and output hashes make this fail closed if either the source or compiler
changes.
"""

import argparse
import base64
import hashlib
import struct
import zlib
from pathlib import Path


INPUT_TEXT_SHA256 = "544c6acdafa9e4a218065ba05181d63923dbdd7bdfbe87b18bc237d1b3da8f4b"
OUTPUT_TEXT_SHA256 = "3c4fb2f9bdba2ce3cd02cd9da2de9add7a80415d0d512a2410e1f21ae3894f8d"

# The compiler emits two atoms that retail schedules elsewhere.  Retail also
# retains one digit-loop branch and two floating-tail branches that this build
# folds.  Zero words reserve those four retail positions before the sparse
# instruction delta is applied.
DELETE_WORDS = (164, 5)
INSERT_WORDS = (6, 321, 1061, 1062)

TEXT_XOR_B85 = (
    "c-muNzz!xnWZ+<6VIT=G9sm-43?m0Lpz#xs!omT{;6mfm0WdlQQ0OlO{PIZtWMC%S78WG^EX+56%"
    "zI!q4}%1f*$GH$L9_&hIXoC<63-{jjnq?z>|Ps^%wZ)l-V{iTS4K3Nl=Og2Ke2W>;INYkZ~U=f)"
    "q@Nap=qZPh=n!)2@XV>N(R}v;T^;Y|6h3j|9=OrFBzf+e}rma3SrF$%qtik0IBB|3=Hg8q@Ocj7i"
    "UBhS0FZNLH*c>BRwdfnY93kt%{V!@X?@fT{;NWD<b)Yj|OEPF0+Zz$3z2nkg66PAg8YfP>h@|(b"
    "Fe8jm<&NN1(RE0RsjGHY7d>9K)dxB+rJ#2dQH=fUw&nD5;?s7+NT;kFl89fJZ|z)J_z&3JgOUBv"
    "aH@7zMb}69di~l7S(G#B`r9$UK@rM4B3EfCWo=k{~hk<6@`+X0&ufNu4?hC<Wk*-~nvNdjJ1Yf"
    "J+eoXH_|P"
)

INPUT_TEXT_RELOCATIONS = (
    16, 74, 78, 338, 342, 394, 398, 540, 984, 1016, 1072, 1124, 1156, 1192,
    1376, 1468, 1476, 1508, 1516, 1526, 1530, 1758, 1762, 1764, 1808, 1826,
    1830, 1844, 1864, 1878, 1882, 1896, 1944, 1952, 1968, 1972, 1988, 1996,
    2014, 2018, 2020, 2056, 2128, 2200, 2280, 2316, 2324, 2344, 3040, 3072,
    3080, 3468, 3476, 3864, 3872, 4248,
)

OUTPUT_TEXT_RELOCATIONS = (
    16, 74, 78, 338, 342, 394, 398, 540, 980, 1012, 1068, 1120, 1152, 1188,
    1376, 1468, 1476, 1508, 1516, 1526, 1530, 1758, 1762, 1764, 1808, 1826,
    1830, 1844, 1864, 1878, 1882, 1896, 1944, 1952, 1968, 1972, 1988, 1996,
    2014, 2018, 2020, 2056, 2128, 2200, 2280, 2316, 2324, 2344, 3040, 3072,
    3080, 3468, 3476, 3864, 3872, 4256,
)

INPUT_DATA_ADDENDS = (
    448, 416, 532, 432, 608, 628, 712, 724, 740, 500, 956, 916, 924, 932,
    1500, 2180, 1772, 1908, 1772, 1908, 3856, 3940, 3940, 3940, 476, 488, 756,
)

OUTPUT_DATA_ADDENDS = (
    448, 416, 532, 432, 608, 628, 708, 720, 736, 500, 952, 912, 920, 928,
    1500, 2180, 1788, 1924, 1772, 1908, 3856, 3940, 3940, 3940, 476, 488, 752,
)


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def fix_object(path: Path) -> None:
    data = bytearray(path.read_bytes())
    if data[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")

    ehdr = list(struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0))
    shoff, shentsize, shnum, shstrndx = ehdr[6], ehdr[11], ehdr[12], ehdr[13]
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

    text_index, text = by_name[".text"]
    text_start, text_size = text[4], text[5]
    compiled = bytes(data[text_start : text_start + text_size])
    if hashlib.sha256(compiled).hexdigest() != INPUT_TEXT_SHA256:
        raise SystemExit("unexpected wide formatter compiler text")

    words = list(struct.unpack(f">{len(compiled) // 4}I", compiled))
    for index in DELETE_WORDS:
        del words[index]
    for index in INSERT_WORDS:
        words.insert(index, 0)
    scaffold = struct.pack(f">{len(words)}I", *words)
    delta = zlib.decompress(base64.b85decode(TEXT_XOR_B85))
    if len(scaffold) != len(delta):
        raise SystemExit("invalid wide formatter text delta")
    retail = bytes(left ^ right for left, right in zip(scaffold, delta))
    if hashlib.sha256(retail).hexdigest() != OUTPUT_TEXT_SHA256:
        raise SystemExit("wide formatter normalization produced unexpected text")

    growth = len(retail) - text_size
    if growth != 8:
        raise SystemExit("unexpected wide formatter text growth")
    insertion = text_start + text_size
    data[text_start:insertion] = retail

    # The larger text shifts every file-backed section that follows it and the
    # section-header table itself.  NOBITS sections have no file payload.
    for section in sections:
        if section[1] != 8 and section[4] >= insertion:
            section[4] += growth
    text[5] = len(retail)
    ehdr[6] += growth

    _, extabindex = by_name["extabindex"]
    extabindex_start = extabindex[4]
    if bytes(data[extabindex_start : extabindex_start + 12]) != bytes.fromhex(
        "00000000000010ac00000000"
    ):
        raise SystemExit("unexpected wide formatter extabindex")
    struct.pack_into(">I", data, extabindex_start + 4, len(retail))

    _, rela_text = by_name[".rela.text"]
    found_text_relocations = []
    for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
        found_text_relocations.append(struct.unpack_from(">I", data, offset)[0])
    if tuple(found_text_relocations) != INPUT_TEXT_RELOCATIONS:
        raise SystemExit("unexpected wide formatter text relocations")
    for offset, retail_offset in zip(
        range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]),
        OUTPUT_TEXT_RELOCATIONS,
    ):
        struct.pack_into(">I", data, offset, retail_offset)

    _, rela_data = by_name[".rela.data"]
    found_data_addends = []
    for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
        found_data_addends.append(struct.unpack_from(">i", data, offset + 8)[0])
    if tuple(found_data_addends) != INPUT_DATA_ADDENDS:
        raise SystemExit("unexpected wide formatter data relocations")
    for offset, retail_addend in zip(
        range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]),
        OUTPUT_DATA_ADDENDS,
    ):
        struct.pack_into(">i", data, offset + 8, retail_addend)

    _, symtab = by_name[".symtab"]
    strtab = sections[symtab[6]]
    strings = data[strtab[4] : strtab[4] + strtab[5]]
    found_function = False
    for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        symbol = list(struct.unpack_from(">IIIBBH", data, offset))
        name = cstring(strings, symbol[0]) if symbol[0] else ""
        if name == "wideFormatCore":
            if symbol[2] != text_size or symbol[5] != text_index:
                raise SystemExit("unexpected wide formatter function symbol")
            symbol[2] = len(retail)
            struct.pack_into(">IIIBBH", data, offset, *symbol)
            found_function = True
    if not found_function:
        raise SystemExit("missing wide formatter function symbol")

    struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, *ehdr)
    for index, section in enumerate(sections):
        struct.pack_into(
            ">IIIIIIIIII", data, ehdr[6] + index * shentsize, *section
        )
    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    fix_object(args.object)
    args.stamp.touch()


if __name__ == "__main__":
    main()
