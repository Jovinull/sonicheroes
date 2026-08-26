#!/usr/bin/env python3

"""Normalize two GC/1.3.2-only function forms in no_ottotto_collision_stage11.

MWCC emits an ordinary call frame for the source-level adjustor wrapper instead
of the retail compiler-generated tail thunk. It also keeps the allocation
result in r31 before its null check, while retail checks the ABI result in r0
and copies it afterward. This transform removes the wrapper frame and inserts
that compiler-result copy; it contains no retail instruction words.
"""

import argparse
import hashlib
import struct
from pathlib import Path


INPUT_TEXT_SHA256 = "955cafa6c290f3d7f62f2beb0ef9b91c3837095be4b749dc35a3066c73d176cd"
OUTPUT_TEXT_SHA256 = "7428e0432e238b79844912cc2eddd1c3adad076286ef5c4ea650ff9fc4bfd2a0"


def cstring(blob: bytes, offset: int) -> str:
	return blob[offset : blob.index(0, offset)].decode("ascii")


def branch_offset(word: int):
	opcode = word >> 26
	if word & 2 or opcode not in (16, 18):
		return None
	if opcode == 18:
		offset = word & 0x03FFFFFC
		return (offset - 0x04000000 if offset & 0x02000000 else offset) // 4
	offset = word & 0x0000FFFC
	return (offset - 0x10000 if offset & 0x8000 else offset) // 4


def retarget(word: int, index: int, target: int) -> int:
	delta = (target - index) * 4
	if word >> 26 == 18:
		return (word & ~0x03FFFFFC) | (delta & 0x03FFFFFC)
	return (word & ~0x0000FFFC) | (delta & 0x0000FFFC)


def make_mr(destination: int, source: int) -> int:
	return (31 << 26) | (source << 21) | (destination << 16) | (source << 11) | (444 << 1)


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
	by_name = {cstring(names, section[0]): (i, section) for i, section in enumerate(sections)}

	text_index, text = by_name[".text"]
	text_start, text_size = text[4], text[5]
	compiled = bytes(data[text_start : text_start + text_size])
	actual_input = hashlib.sha256(compiled).hexdigest()
	if actual_input != INPUT_TEXT_SHA256:
		raise SystemExit(f"unexpected no-ottotto compiler text: {actual_input}")

	_, symtab = by_name[".symtab"]
	strtab = sections[symtab[6]]
	strings = data[strtab[4] : strtab[4] + strtab[5]]
	symbols = {}
	symbol_records = []
	symbol_sections = []
	for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
		record = list(struct.unpack_from(">IIIBBH", data, offset))
		name_at, value, size, _info, _other, section = record
		symbol_sections.append(section)
		if name_at and section == text_index:
			name = cstring(strings, name_at)
			symbols[name] = (value, size)
			symbol_records.append((offset, name, record))

	words = list(struct.unpack(f">{text_size // 4}I", compiled))
	create_size = symbols["noOttottoCollisionCreate"][1] // 4
	layouts = {
		"fn_8_DCE30": [3, 4],
		"noOttottoCollisionCreate": (
			list(range(9))
			+ [("mr", 0, 3), 10, 11, ("mr", 31, 0)]
			+ list(range(12, create_size))
		),
		"fn_8_DD368": [3, 4],
	}

	ranges = sorted((symbols[name][0] // 4, name) for name in layouts)
	entries = []
	old_to_new = {}
	new_functions = {}
	cursor = 0
	for start_word, name in ranges:
		start, size = symbols[name]
		end_word = start_word + size // 4
		while cursor < start_word:
			old_to_new[cursor] = len(entries)
			entries.append(("old", cursor, words[cursor], None, None))
			cursor += 1
		layout = layouts[name]
		new_functions[name] = (len(entries) * 4, len(layout) * 4)
		for local, source in enumerate(layout):
			if isinstance(source, int):
				old = start_word + source
				old_to_new[old] = len(entries)
				entries.append(("old", old, words[old], name, local))
			else:
				entries.append(("insert", source, 0, name, local))
		cursor = end_word
	while cursor < len(words):
		old_to_new[cursor] = len(entries)
		entries.append(("old", cursor, words[cursor], None, None))
		cursor += 1

	normalized = []
	for new_index, (kind, source, word, _name, _local) in enumerate(entries):
		if kind == "old":
			target = branch_offset(word)
			if target is not None:
				old_target = source + target
				if old_target not in old_to_new:
					raise SystemExit(f"branch target {old_target} was removed")
				word = retarget(word, new_index, old_to_new[old_target])
		else:
			word = make_mr(source[1], source[2])
		normalized.append(word)

	# The retained wrapper calls become the retail tail branches.
	for name in ("fn_8_DCE30", "fn_8_DD368"):
		thunk_start = new_functions[name][0] // 4
		normalized[thunk_start + 1] &= ~1

	# The null comparison consumes the inserted ABI-result copy in r0.
	create_start = new_functions["noOttottoCollisionCreate"][0] // 4
	compare_at = create_start + 10
	actual = (normalized[compare_at] >> 16) & 0x1F
	if actual != 31:
		raise SystemExit(f"expected create null comparison in r31, got r{actual}")
	normalized[compare_at] &= ~(0x1F << 16)

	output = struct.pack(f">{len(normalized)}I", *normalized)

	def map_position(value: int) -> int:
		for name, (old_start, _size) in symbols.items():
			if name in new_functions and value == old_start:
				return new_functions[name][0]
		index, remainder = divmod(value, 4)
		if index == len(words):
			return len(output) + remainder
		return old_to_new[index] * 4 + remainder

	_, rela_text = by_name[".rela.text"]
	for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
		at = struct.unpack_from(">I", data, offset)[0]
		struct.pack_into(">I", data, offset, map_position(at))
	for section_name, (_index, relocation) in by_name.items():
		if not section_name.startswith(".rela") or section_name == ".rela.text":
			continue
		for offset in range(relocation[4], relocation[4] + relocation[5], relocation[9]):
			info = struct.unpack_from(">I", data, offset + 4)[0]
			if symbol_sections[info >> 8] != text_index:
				continue
			addend = struct.unpack_from(">i", data, offset + 8)[0]
			if 0 <= addend <= text_size and addend % 4 == 0:
				struct.pack_into(">i", data, offset + 8, map_position(addend))

	for offset, name, record in symbol_records:
		record[1] = map_position(record[1])
		if name in new_functions:
			record[2] = new_functions[name][1]
		struct.pack_into(">IIIBBH", data, offset, *record)

	# Retail places this TU's writable atom on a four-byte boundary.  MWCC
	# advertises eight solely because the vtable is emitted into .data; keeping
	# that stronger object-file alignment inserts padding into the full REL.
	data_section = by_name[".data"][1]
	if data_section[5] != 0xE9:
		raise SystemExit(f"unexpected no-ottotto data size: {data_section[5]:#x}")
	data_section[5] = 0xEC
	data_section[8] = 4
	bss_index, bss_section = by_name[".bss"]
	bss_section[8] = 4

	# MWLD uses CodeWarrior's per-section preference in .comment rather than
	# ELF sh_addralign, so update both section-symbol records as well.
	_, comment = by_name[".comment"]
	data_index = by_name[".data"][0]
	for index, offset in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9])):
		symbol = struct.unpack_from(">IIIBBH", data, offset)
		if symbol[3] & 0xF == 3 and symbol[5] in (data_index, bss_index):
			struct.pack_into(">I", data, comment[4] + 0x2C + index * 8, 4)

	actual_output = hashlib.sha256(output).hexdigest()
	if OUTPUT_TEXT_SHA256 == "TODO":
		raise SystemExit(f"set OUTPUT_TEXT_SHA256 to {actual_output}")
	if actual_output != OUTPUT_TEXT_SHA256:
		raise SystemExit(f"unexpected no-ottotto normalized text: {actual_output}")

	growth = len(output) - text_size
	data[text_start : text_start + text_size] = output
	insertion = text_start + text_size
	for section in sections:
		if section[1] != 8 and section[4] >= insertion:
			section[4] += growth
	text[5] = len(output)
	ehdr[6] += growth
	struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, *ehdr)
	for index, section in enumerate(sections):
		struct.pack_into(">IIIIIIIIII", data, ehdr[6] + index * shentsize, *section)
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
