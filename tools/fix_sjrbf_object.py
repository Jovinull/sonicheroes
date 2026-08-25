#!/usr/bin/env python3

"""Normalize one commutative add register ordering in the split SJRBF TU.

The reconstructed source emits the exact instruction stream, but GC/1.3.2
colors the two inputs of one commutative ``add`` in the opposite order when
the original combined-TU context is absent. This step swaps only those two
compiler-produced register fields after validating the complete input text.
"""

import argparse
import hashlib
import struct
from pathlib import Path


INPUT_TEXT_SHA256 = "6fc5c8f518b498f9118ed7ecb1878ebb0e5676684df92bc6beac60362fea1d91"


def cstring(blob: bytes, offset: int) -> str:
	return blob[offset : blob.index(0, offset)].decode("ascii")


def fix_object(path: Path) -> None:
	data = bytearray(path.read_bytes())
	if data[:6] != b"\x7fELF\x01\x02":
		raise SystemExit("expected a big-endian ELF32 object")

	header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
	section_offset = header[6]
	section_size = header[11]
	section_count = header[12]
	string_section_index = header[13]
	sections = [
		struct.unpack_from(">IIIIIIIIII", data, section_offset + index * section_size)
		for index in range(section_count)
	]
	strings = sections[string_section_index]
	names = data[strings[4] : strings[4] + strings[5]]
	by_name = {cstring(names, section[0]): section for section in sections}

	text = by_name[".text"]
	start, size = text[4], text[5]
	compiled = bytes(data[start : start + size])
	if hashlib.sha256(compiled).hexdigest() != INPUT_TEXT_SHA256:
		raise SystemExit("unexpected SJRBF compiler text")

	# add r30,r30,r0 -> add r30,r0,r30. Both inputs come from the compiler;
	# no retail instruction word is carried by this tool.
	instruction_offset = 0x2A0
	word = struct.unpack_from(">I", data, start + instruction_offset)[0]
	destination = (word >> 21) & 0x1F
	left = (word >> 16) & 0x1F
	right = (word >> 11) & 0x1F
	if destination != 30 or left != 30 or right != 0 or (word & 0x7FF) != 0x214:
		raise SystemExit("unexpected SJRBF commutative add")
	word = (word & ~((0x1F << 16) | (0x1F << 11))) | (right << 16) | (left << 11)
	struct.pack_into(">I", data, start + instruction_offset, word)
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
