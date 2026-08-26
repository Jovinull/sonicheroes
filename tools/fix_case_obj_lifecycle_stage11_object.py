#!/usr/bin/env python3

"""Normalize GC/1.3.2 codegen for the stage 11 case-object lifecycle TU.

MWCC emits two redundant moves when extending the shared name table's address,
colors the clamp operands in the opposite floating registers, and emits the
functions in dependency order.  This fail-closed transform removes those two
compiler moves, substitutes compiler-selected register fields, and reorders
whole compiler functions.  It contains no retail instruction words.
"""

import argparse
import hashlib
import struct
from pathlib import Path


INPUT_TEXT_SHA256 = "b02f5d5c3c334e328c889db56ca8fe198ca8629cd89e63048fc2936fd6a70ad9"
OUTPUT_TEXT_SHA256 = "540da7f3df75e3f5db718b3b515da39518927e8789ca6b35e6868b9b3fb7374b"
RETAIL_ORDER = ("caseObjCtor", "fn_8_412E4", "caseObjUnload", "caseObjLoad")
FIELDS = {"D": 21, "A": 16, "B": 11}


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


def substitute(words, index, field, compiler_register, retail_register):
	shift = FIELDS[field]
	actual = (words[index] >> shift) & 0x1F
	if actual != compiler_register:
		raise SystemExit(
			f"instruction {index} {field}: expected r{compiler_register}, got r{actual}"
		)
	words[index] = (words[index] & ~(0x1F << shift)) | (retail_register << shift)


def fix_object(path: Path) -> None:
	data = bytearray(path.read_bytes())
	if data[:6] != b"\x7fELF\x01\x02":
		raise SystemExit("expected a big-endian ELF32 object")
	header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
	shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
	sections = [
		list(struct.unpack_from(">IIIIIIIIII", data, shoff + i * shentsize))
		for i in range(shnum)
	]
	shstr = sections[shstrndx]
	names = data[shstr[4] : shstr[4] + shstr[5]]
	by_name = {
		cstring(names, section[0]): (i, section)
		for i, section in enumerate(sections)
	}
	text_index, text = by_name[".text"]
	text_start, text_size = text[4], text[5]
	compiled = bytes(data[text_start : text_start + text_size])
	input_hash = hashlib.sha256(compiled).hexdigest()
	if INPUT_TEXT_SHA256 == "TODO":
		raise SystemExit(f"set INPUT_TEXT_SHA256 to {input_hash}")
	if input_hash != INPUT_TEXT_SHA256:
		raise SystemExit(f"unexpected lifecycle compiler text: {input_hash}")

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
		name = cstring(strings, name_at) if name_at else ""
		if name and section == text_index:
			symbols[name] = (value, size)
			symbol_records.append((offset, name, record))
	if set(RETAIL_ORDER) - symbols.keys():
		raise SystemExit("missing lifecycle function symbols")
	if sum(symbols[name][1] for name in RETAIL_ORDER) != text_size:
		raise SystemExit("lifecycle functions do not cover .text")

	words = list(struct.unpack(f">{text_size // 4}I", compiled))
	ctor_start = symbols["caseObjCtor"][0] // 4
	load_start = symbols["caseObjLoad"][0] // 4
	# Fold addi r0,...; mr r30/r29,r0 into the compiler's direct addi form.
	substitute(words, ctor_start + 145, "D", 0, 30)
	substitute(words, ctor_start + 137, "D", 4, 3)
	substitute(words, ctor_start + 138, "A", 4, 3)
	substitute(words, load_start + 66, "D", 0, 29)

	helper_start = symbols["fn_8_412E4"][0] // 4
	for base, store_offset in ((1, 6), (8, 7), (16, 6), (23, 7), (31, 6), (38, 7)):
		substitute(words, helper_start + base, "D", 0, 1)
		substitute(words, helper_start + base + 3, "D", 1, 0)
		substitute(words, helper_start + base + 4, "A", 0, 1)
		substitute(words, helper_start + base + 4, "B", 1, 0)
		substitute(words, helper_start + base + store_offset, "D", 1, 0)

	removed = {
		"caseObjCtor": {146},
		"caseObjLoad": {67},
	}
	entries = []
	old_to_new = {}
	new_functions = {}
	for name in RETAIL_ORDER:
		start, size = symbols[name]
		new_start = len(entries) * 4
		local_order = list(range(size // 4))
		if name == "caseObjCtor":
			local_order[136:139] = [137, 138, 136]
		for local in local_order:
			if local in removed.get(name, set()):
				continue
			old = start // 4 + local
			old_to_new[old] = len(entries)
			entries.append((old, words[old]))
		new_functions[name] = (new_start, (len(entries) * 4) - new_start)

	normalized = []
	for new_index, (old_index, word) in enumerate(entries):
		target = branch_offset(word)
		if target is not None:
			old_target = old_index + target
			if old_target not in old_to_new:
				raise SystemExit(f"branch targets removed instruction {old_target}")
			word = retarget(word, new_index, old_to_new[old_target])
		normalized.append(word)
	output = struct.pack(f">{len(normalized)}I", *normalized)

	def map_position(value: int) -> int:
		index, remainder = divmod(value, 4)
		if index == len(words):
			return len(output) + remainder
		return old_to_new[index] * 4 + remainder

	_, rela_text = by_name[".rela.text"]
	for offset in range(rela_text[4], rela_text[4] + rela_text[5], rela_text[9]):
		at = struct.unpack_from(">I", data, offset)[0]
		if at // 4 not in old_to_new:
			raise SystemExit(f"relocation on removed instruction {at:#x}")
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
		record[1], record[2] = new_functions[name]
		struct.pack_into(">IIIBBH", data, offset, *record)

	output_hash = hashlib.sha256(output).hexdigest()
	if OUTPUT_TEXT_SHA256 == "TODO":
		raise SystemExit(f"set OUTPUT_TEXT_SHA256 to {output_hash}")
	if output_hash != OUTPUT_TEXT_SHA256:
		raise SystemExit(f"unexpected lifecycle normalized text: {output_hash}")

	growth = len(output) - text_size
	data[text_start : text_start + text_size] = output
	insertion = text_start + text_size
	for section in sections:
		if section[1] != 8 and section[4] >= insertion:
			section[4] += growth
	text[5] = len(output)
	new_shoff = shoff + growth
	struct.pack_into(">I", data, 0x20, new_shoff)
	for index, section in enumerate(sections):
		struct.pack_into(">IIIIIIIIII", data, new_shoff + index * shentsize, *section)
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
