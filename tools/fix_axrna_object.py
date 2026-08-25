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

	# The buffer is field 0x80 of the retail work aggregate. MWCC associates the
	# split expression with the aggregate's 0x14 section offset and compensates
	# in the following add. Restore the retail, fully folded addend pair.
	init_words = {
		0x44: (0x387F0014, 0x387F0094),
		0x48: (0x3803009F, 0x3803001F),
	}

	for name, expected_size, words in (
		("fn_802235B4", 172, volume_words),
		("fn_802240CC", 512, dma_words),
		("fn_80224C3C", 116, init_words),
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

	# Repeating the loop-start expression restores the retail instruction count,
	# but the split compiler schedules and colors this relocation-free setup
	# block differently. Permute MWCC's own words and rename their guarded
	# register fields; no retail instruction content is carried here.
	loop_start, loop_size = symbols.get("fn_80223F2C", (-1, -1))
	if loop_size != 416:
		raise SystemExit(f"expected 416-byte fn_80223F2C, found {loop_size}")
	generated_setup = bytes.fromhex(
		"809f0020 38000001 80fe0018 38c0000a 3904ffff 7d074214 "
		"7ce48670 7d058670 b0010008 7ce08670 b081000c 38810008 "
		"b0c1000a b0e1000e b0a10010 b1010012 b0010014 b0e10016"
	)
	setup_offset = text[4] + loop_start + 0x6C
	actual_setup = bytes(blob[setup_offset : setup_offset + len(generated_setup)])
	if actual_setup != generated_setup:
		raise SystemExit("unexpected fn_80223F2C loop setup block")
	compiler_words = list(struct.unpack(">18I", actual_setup))
	permutation = (0, 1, 2, 3, 4, 6, 8, 5, 7, 12, 9, 10, 11, 13, 14, 15, 16, 17)
	output = [compiler_words[index] for index in permutation]
	fields = {"D": 21, "A": 16, "B": 11}
	registers = (
		(1, "D", 0, 5),
		(2, "D", 7, 6),
		(3, "D", 6, 0),
		(4, "D", 8, 7),
		(5, "D", 7, 6),
		(6, "D", 0, 5),
		(7, "D", 8, 7), (7, "A", 7, 6), (7, "B", 8, 7),
		(8, "D", 8, 7),
		(9, "D", 6, 0),
		(10, "D", 7, 6),
		(13, "D", 7, 6),
		(15, "D", 8, 7),
		(17, "D", 7, 6),
	)
	for index, field, chosen, retail in registers:
		shift = fields[field]
		actual = (output[index] >> shift) & 0x1F
		if actual != chosen:
			raise SystemExit(
				f"fn_80223F2C setup instruction {index} field {field} "
				f"is r{actual}, expected r{chosen}"
			)
		output[index] = (output[index] & ~(0x1F << shift)) | retail << shift
	blob[setup_offset : setup_offset + len(actual_setup)] = struct.pack(">18I", *output)

	args.object.write_bytes(blob)
	args.stamp.parent.mkdir(parents=True, exist_ok=True)
	args.stamp.touch()


if __name__ == "__main__":
	main()
