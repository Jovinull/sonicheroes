#!/usr/bin/env python3

import argparse
import struct
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Change one ELF32 section's sh_addralign without rewriting the object"
    )
    parser.add_argument("object", type=Path)
    parser.add_argument("section")
    parser.add_argument("alignment", type=int)
    args = parser.parse_args()

    if args.alignment <= 0 or args.alignment & (args.alignment - 1):
        parser.error("alignment must be a positive power of two")

    data = bytearray(args.object.read_bytes())
    if data[:4] != b"\x7fELF" or data[4] != 1:
        parser.error(f"{args.object} is not an ELF32 object")

    endian = ">" if data[5] == 2 else "<" if data[5] == 1 else None
    if endian is None:
        parser.error(f"{args.object} has an unsupported ELF byte order")

    section_offset = struct.unpack_from(f"{endian}I", data, 0x20)[0]
    section_entry_size = struct.unpack_from(f"{endian}H", data, 0x2E)[0]
    section_count = struct.unpack_from(f"{endian}H", data, 0x30)[0]
    string_section = struct.unpack_from(f"{endian}H", data, 0x32)[0]

    string_header = section_offset + string_section * section_entry_size
    string_offset = struct.unpack_from(f"{endian}I", data, string_header + 0x10)[0]

    sections = {}
    target_index = None
    for index in range(section_count):
        header = section_offset + index * section_entry_size
        name_offset = struct.unpack_from(f"{endian}I", data, header)[0]
        name_start = string_offset + name_offset
        name_end = data.index(0, name_start)
        name = data[name_start:name_end].decode("ascii")
        sections[name] = (index, header)
        if name == args.section:
            target_index = index
            struct.pack_into(f"{endian}I", data, header + 0x20, args.alignment)

    if target_index is None:
        parser.error(f"section {args.section!r} not found in {args.object}")

    # MWLD uses the CodeWarrior .comment entry for a section symbol in
    # preference to the ELF sh_addralign field. Keep both representations in
    # sync while leaving every section's contents and offsets untouched.
    if ".symtab" in sections and ".comment" in sections:
        _, symbol_header = sections[".symtab"]
        symbol_offset = struct.unpack_from(f"{endian}I", data, symbol_header + 0x10)[0]
        symbol_size = struct.unpack_from(f"{endian}I", data, symbol_header + 0x14)[0]
        symbol_entry_size = struct.unpack_from(
            f"{endian}I", data, symbol_header + 0x24
        )[0]
        _, comment_header = sections[".comment"]
        comment_offset = struct.unpack_from(f"{endian}I", data, comment_header + 0x10)[0]

        for index in range(symbol_size // symbol_entry_size):
            symbol = symbol_offset + index * symbol_entry_size
            symbol_type = data[symbol + 0xC] & 0xF
            symbol_section = struct.unpack_from(f"{endian}H", data, symbol + 0xE)[0]
            if symbol_type == 3 and symbol_section == target_index:
                struct.pack_into(
                    f"{endian}I",
                    data,
                    comment_offset + 0x2C + index * 8,
                    args.alignment,
                )
                break

    args.object.write_bytes(data)


if __name__ == "__main__":
    main()
