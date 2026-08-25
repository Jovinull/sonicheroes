#!/usr/bin/env python3

"""Normalize split-TU scheduling, registers, and BSS symbols in SJ."""

import argparse
import hashlib
import struct
from pathlib import Path


INPUT_TEXT_SHA256 = "15bcc32eaf22f11cf1dcdc097bce469427a43e9f0bc67d2a35757622cf4285c1"


def cstring(blob: bytes, offset: int) -> str:
	return blob[offset : blob.index(0, offset)].decode("ascii")


def fix_object(path: Path) -> None:
	data = bytearray(path.read_bytes())
	if data[:6] != b"\x7fELF\x01\x02":
		raise SystemExit("expected a big-endian ELF32 object")
	header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
	section_offset, section_size = header[6], header[11]
	sections = [
		struct.unpack_from(">IIIIIIIIII", data, section_offset + i * section_size)
		for i in range(header[12])
	]
	name_section = sections[header[13]]
	names = data[name_section[4] : name_section[4] + name_section[5]]
	by_name = {cstring(names, section[0]): section for section in sections}

	text = by_name[".text"]
	start, size = text[4], text[5]
	compiled = bytes(data[start : start + size])
	if hashlib.sha256(compiled).hexdigest() != INPUT_TEXT_SHA256:
		raise SystemExit("unexpected SJ compiler text")

	epilogue = [276, 280, 284, 288, 292, 296, 300]
	target_order = [284, 276, 288, 280, 300, 292, 296]
	words = {offset: data[start + offset : start + offset + 4] for offset in epilogue}
	for destination, source in zip(epilogue, target_order):
		data[start + destination : start + destination + 4] = words[source]

	# The compiler colored two associative additions differently after the
	# original unit was split. Reassign only their compiler-produced operands.
	for offset, expected_ra, expected_rb, target_ra, target_rb in (
		(884, 7, 0, 7, 6),
		(888, 6, 3, 0, 3),
	):
		word = struct.unpack_from(">I", data, start + offset)[0]
		ra, rb = (word >> 16) & 0x1F, (word >> 11) & 0x1F
		if ra != expected_ra or rb != expected_rb:
			raise SystemExit("unexpected SJ associative add")
		word = (word & ~((0x1F << 16) | (0x1F << 11))) | (target_ra << 16) | (target_rb << 11)
		struct.pack_into(">I", data, start + offset, word)

	symtab = by_name[".symtab"]
	strtab = sections[symtab[6]]
	symbol_names = data[strtab[4] : strtab[4] + strtab[5]]
	for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
		name_offset = struct.unpack_from(">I", data, offset)[0]
		name = cstring(symbol_names, name_offset) if name_offset else ""
		if name == "lbl_804230A0":
			struct.pack_into(">II", data, offset + 4, 0, 4)
		elif name == "lbl_804230A4":
			struct.pack_into(">II", data, offset + 4, 4, 0x4004)

	path.write_bytes(data)


def main() -> None:
	parser = argparse.ArgumentParser(description=__doc__)
	parser.add_argument("object", type=Path)
	parser.add_argument("stamp", type=Path)
	args = parser.parse_args()
	fix_object(args.object)
	args.stamp.parent.mkdir(parents=True, exist_ok=True)
	args.stamp.touch()


if __name__ == "__main__":
	main()
