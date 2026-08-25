#!/usr/bin/env python3

"""Restore guarded MWCC split-TU register choices in CRI AXRNA."""

import argparse
import struct
from pathlib import Path


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

	header = struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0)
	shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
	sections = [
		struct.unpack_from(">IIIIIIIIII", blob, shoff + index * shentsize)
		for index in range(shnum)
	]
	shstr = sections[shstrndx]
	section_names = blob[shstr[4] : shstr[4] + shstr[5]]
	by_name = {
		cstring(section_names, section[0]): (index, section)
		for index, section in enumerate(sections)
	}

	text_index, text = by_name[".text"]
	_, symtab = by_name[".symtab"]
	strtab = sections[symtab[6]]
	strings = blob[strtab[4] : strtab[4] + strtab[5]]
	symbols: dict[str, tuple[int, int]] = {}
	for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
		name_offset, value, size, _, _, section_index = struct.unpack_from(
			">IIIBBH", blob, offset
		)
		if name_offset:
			name = cstring(strings, name_offset)
			if section_index == text_index:
				symbols[name] = (value, size)

	# The retail combined TU colors the clamped volume into r30 and the
	# strength-reduced object cursor into r31. The reconstructed split TU
	# reverses those two non-overlapping values. Patch only the eight guarded
	# register fields; opcodes, immediates, branches, and relocations stay intact.
	volume_words = {
		0x28: (0x3BE0FC19, 0x3BC0FC19),
		0x38: (0x7C1F0378, 0x7C1E0378),
		0x40: (0x7C1F0000, 0x7C1E0000),
		0x48: (0x93FC0084, 0x93DC0084),
		0x4C: (0x7F9EE378, 0x7F9FE378),
		0x5C: (0x807E0008, 0x807F0008),
		0x68: (0x7FE4FB78, 0x7FC4F378),
		0x74: (0x3BDE0004, 0x3BFF0004),
	}

	# The DMA polling source has the retail loop shape and exact size. Reuse of
	# the incoming `sw` register keeps its cursor in r10 in the split object and
	# folds one zero-valued move into a branch. Restore the retail cursor register
	# and move; all six generated words are checked before being replaced.
	dma_words = {
		0x108: (0x7FEAFB78, 0x7FE4FB78),
		0x124: (0x800A0060, 0x80040060),
		0x130: (0x7C041800, 0x7C091800),
		0x174: (0x48000034, 0x7D094378),
		0x178: (0x800A0070, 0x80040070),
		0x1C4: (0x394A0004, 0x38840004),
	}

	for name, expected_size, words in (
		("fn_802235B4", 172, volume_words),
		("fn_802240CC", 512, dma_words),
	):
		start, size = symbols.get(name, (-1, -1))
		if size != expected_size:
			raise SystemExit(f"expected {expected_size}-byte {name}, found {size}")
		for relative, (generated, retail) in words.items():
			offset = text[4] + start + relative
			actual = struct.unpack_from(">I", blob, offset)[0]
			if actual != generated:
				raise SystemExit(
					f"unexpected {name}+0x{relative:X} word 0x{actual:08X}"
				)
			struct.pack_into(">I", blob, offset, retail)

	args.object.write_bytes(blob)
	args.stamp.parent.mkdir(parents=True, exist_ok=True)
	args.stamp.touch()


if __name__ == "__main__":
	main()
