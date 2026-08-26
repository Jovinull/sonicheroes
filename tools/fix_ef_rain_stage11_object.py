#!/usr/bin/env python3

"""Restore the retail four-byte placement of stage11's EfRain data atom."""

import argparse
import struct
from pathlib import Path


def cstring(blob: bytes, offset: int) -> str:
	return blob[offset : blob.index(0, offset)].decode("ascii")


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
	names = data[shstr[4] : shstr[4] + shstr[5]]
	by_name = {
		cstring(names, section[0]): (index, section)
		for index, section in enumerate(sections)
	}

	data_index, data_section = by_name[".data"]
	if data_section[5] != 0x58 or data_section[8] != 8:
		raise SystemExit("unexpected stage11 EfRain data layout")
	data_start = data_section[4]
	filename = b"textures/ef_rain.txd\0\0\0\0"
	if bytes(data[data_start + 0x20 : data_start + 0x38]) != filename:
		raise SystemExit("unexpected stage11 EfRain filename atom")
	if any(data[data_start + 0x38 : data_start + 0x58]):
		raise SystemExit("unexpected stage11 EfRain vtable atom")
	current = bytes(data[data_start : data_start + 0x58])
	data[data_start : data_start + 0x58] = (
		current[:0x20] + current[0x38:0x58] + current[0x20:0x38]
	)
	data_section[8] = 4

	_, symtab = by_name[".symtab"]
	strtab = sections[symtab[6]]
	strings = data[strtab[4] : strtab[4] + strtab[5]]
	_, comment = by_name[".comment"]
	for index, offset in enumerate(
		range(symtab[4], symtab[4] + symtab[5], symtab[9])
	):
		symbol = list(struct.unpack_from(">IIIBBH", data, offset))
		name = cstring(strings, symbol[0]) if symbol[0] else ""
		if name == "__vt__6EfRain":
			symbol[1] = 0x20
			struct.pack_into(">IIIBBH", data, offset, *symbol)
		elif name == "rainTextureFilename":
			symbol[1] = 0x40
			struct.pack_into(">IIIBBH", data, offset, *symbol)
		if symbol[3] & 0xF == 3 and symbol[5] == data_index:
			struct.pack_into(">I", data, comment[4] + 0x2C + index * 8, 4)

	_, rela_data = by_name[".rela.data"]
	for offset in range(rela_data[4], rela_data[4] + rela_data[5], rela_data[9]):
		at = struct.unpack_from(">I", data, offset)[0]
		if 0x38 <= at < 0x58:
			struct.pack_into(">I", data, offset, at - 0x18)

	for index, section in enumerate(sections):
		struct.pack_into(">IIIIIIIIII", data, shoff + index * shentsize, *section)
	path.write_bytes(data)


def main() -> None:
	parser = argparse.ArgumentParser(description=__doc__)
	parser.add_argument("object", type=Path)
	parser.add_argument("stamp", type=Path)
	args = parser.parse_args()
	fix_object(args.object)
	args.stamp.write_text("")


if __name__ == "__main__":
	main()
