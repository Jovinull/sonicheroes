#!/usr/bin/env python3

"""Remove one split-TU conversion literal; the 192 text bytes stay untouched.

The retail combined TU shares its unsigned-conversion bias as lbl_8042E050.
Compiling this reconstructed TU alone emits one private 8-byte copy instead.
This step redirects that single relocation to the shared undefined symbol,
removes only the now-unused compiler literal section, and restores the two
compiler-owned exception atom names that determine linker order. No retail
content is carried here. Current remainder: one relocation, one 8-byte data
atom, two compiler-generated symbol names, and one split-object section
ordering difference.
"""

import argparse
import hashlib
import os
import struct
import subprocess
import tempfile
from pathlib import Path


TEXT_SHA256 = "ae02ba972db954d02c66ec855e69bde21d5e463fffba5ecf305ff924db02b798"


def cstring(blob: bytes, offset: int) -> str:
	return blob[offset : blob.index(0, offset)].decode("ascii")


def elf_layout(blob: bytes):
	header = struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0)
	shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
	sections = [
		list(struct.unpack_from(">IIIIIIIIII", blob, shoff + i * shentsize))
		for i in range(shnum)
	]
	shstr = sections[shstrndx]
	names = blob[shstr[4] : shstr[4] + shstr[5]]
	by_name = {
		cstring(names, section[0]): (index, section)
		for index, section in enumerate(sections)
	}
	return sections, by_name


def text_hash(blob: bytes) -> str:
	_, by_name = elf_layout(blob)
	text = by_name[".text"][1]
	return hashlib.sha256(blob[text[4] : text[4] + text[5]]).hexdigest()


def redirect_literal(path: Path) -> None:
	blob = bytearray(path.read_bytes())
	sections, by_name = elf_layout(blob)
	sdata_index, sdata = by_name.get(".sdata2", (-1, None))
	if sdata is None or sdata[5] != 8:
		raise SystemExit("expected one 8-byte .sdata2 conversion literal")

	_, symtab = by_name[".symtab"]
	strtab = sections[symtab[6]]
	strings = blob[strtab[4] : strtab[4] + strtab[5]]
	symbols = {}
	for index, offset in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9])):
		symbol = list(struct.unpack_from(">IIIBBH", blob, offset))
		name = cstring(strings, symbol[0]) if symbol[0] else ""
		symbols[name] = (index, offset, symbol)

	private = next(
		(value for name, value in symbols.items() if name.startswith("@") and value[2][5] == sdata_index),
		None,
	)
	shared = symbols.get("lbl_8042E050")
	if private is None or shared is None:
		raise SystemExit("expected private and shared conversion-bias symbols")
	for name, section_name, size in (("@12", "extab", 8), ("@13", "extabindex", 12)):
		entry = symbols.get(name)
		if entry is None or entry[2][2] != size or entry[2][5] != by_name[section_name][0]:
			raise SystemExit(f"unexpected compiler-owned exception atom {name}")
	private_index, _, private_symbol = private
	shared_index, shared_offset, shared_symbol = shared
	if private_symbol[1:3] != [0, 8] or shared_symbol[5] != 0xFFF1:
		raise SystemExit("unexpected conversion-bias symbol layout")

	# Turn the objcopy-added absolute symbol into the undefined external object
	# used by the combined retail TU.
	shared_symbol[1] = 0
	shared_symbol[2] = 0
	shared_symbol[3] = 0x10  # STB_GLOBAL | STT_NOTYPE
	shared_symbol[5] = 0
	struct.pack_into(">IIIBBH", blob, shared_offset, *shared_symbol)

	_, rela = by_name[".rela.text"]
	users = 0
	for offset in range(rela[4], rela[4] + rela[5], rela[9]):
		r_offset, r_info, addend = struct.unpack_from(">IIi", blob, offset)
		if r_info >> 8 == private_index:
			users += 1
			struct.pack_into(">IIi", blob, offset, r_offset, (shared_index << 8) | (r_info & 0xFF), addend)
	if users != 1:
		raise SystemExit(f"expected one private-literal relocation, found {users}")
	path.write_bytes(blob)


def fix_comment_alignments(path: Path) -> None:
	blob = bytearray(path.read_bytes())
	sections, by_name = elf_layout(blob)
	_, symtab = by_name[".symtab"]
	strtab = sections[symtab[6]]
	strings = blob[strtab[4] : strtab[4] + strtab[5]]
	comment = by_name[".comment"][1]
	found = set()
	for index, offset in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9])):
		name_offset = struct.unpack_from(">I", blob, offset)[0]
		name = cstring(strings, name_offset) if name_offset else ""
		if name in ("@etb_80008C68", "@eti_8000F37C"):
			metadata_offset = comment[4] + 0x2C + index * 8
			if struct.unpack_from(">I", blob, metadata_offset)[0] != 8:
				raise SystemExit(f"unexpected compacted alignment for {name}")
			struct.pack_into(">I", blob, metadata_offset, 4)
			found.add(name)
	if found != {"@etb_80008C68", "@eti_8000F37C"}:
		raise SystemExit("missing renamed exception atoms")
	path.write_bytes(blob)


def fix_bss_layout(path: Path) -> None:
	blob = bytearray(path.read_bytes())
	sections, by_name = elf_layout(blob)
	bss_index, bss = by_name[".bss"]
	if bss[5] != 0x40004:
		raise SystemExit("unexpected split BSS size")
	_, symtab = by_name[".symtab"]
	strtab = sections[symtab[6]]
	strings = blob[strtab[4] : strtab[4] + strtab[5]]
	targets = {
		"lbl_803A7028": (0x00000, 50456),
		"lbl_803B3540": (0x0C518, 0x1F801),
		"lbl_803D2D41": (0x2BD19, 57487),
		"lbl_803E0DD0": (0x39DA8, 1860),
		"lbl_803E1514": (0x3A4EC, 23316),
	}
	found = set()
	for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
		symbol = list(struct.unpack_from(">IIIBBH", blob, offset))
		name = cstring(strings, symbol[0]) if symbol[0] else ""
		if name in targets:
			symbol[1], symbol[2] = targets[name]
			if symbol[5] != bss_index:
				raise SystemExit(f"unexpected BSS section for {name}")
			struct.pack_into(">IIIBBH", blob, offset, *symbol)
			found.add(name)
	if found != set(targets):
		raise SystemExit("missing split BSS symbols")
	bss[5] = 0x40000
	shoff = struct.unpack_from(">I", blob, 0x20)[0]
	shentsize = struct.unpack_from(">H", blob, 0x2E)[0]
	struct.pack_into(">IIIIIIIIII", blob, shoff + bss_index * shentsize, *bss)
	path.write_bytes(blob)


def normalize_symbols_and_comment(path: Path) -> None:
	blob = bytearray(path.read_bytes())
	sections, by_name = elf_layout(blob)
	_, symtab = by_name[".symtab"]
	strtab = sections[symtab[6]]
	strings = blob[strtab[4] : strtab[4] + strtab[5]]
	entries = []
	by_symbol_name = {}
	section_symbols = {}
	file_index = None
	for index, offset in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9])):
		symbol = list(struct.unpack_from(">IIIBBH", blob, offset))
		name = cstring(strings, symbol[0]) if symbol[0] else ""
		entries.append(symbol)
		if index == 0:
			continue
		if (symbol[3] & 0xF) == 4:
			file_index = index
		elif (symbol[3] & 0xF) == 3:
			section_symbols[symbol[5]] = index
		elif name:
			by_symbol_name[name] = index
	desired_names = [
		"@etb_80008C68",
		"@eti_8000F37C",
		"fn_800D7B18",
		"lbl_803A7028",
		"lbl_803B3540",
		"lbl_803D2D41",
		"lbl_803E0DD0",
		"lbl_803E1514",
		"_savegpr_27",
		"lbl_8042E044",
		"lbl_8042E050",
		"lbl_8042E048",
		"sin",
		"_restgpr_27",
	]
	section_order = [by_name[name][0] for name in ("extab", "extabindex", ".text", ".bss")]
	if file_index is None or set(desired_names) - set(by_symbol_name):
		raise SystemExit("unexpected final symbol set")
	old_order = [0, file_index] + [section_symbols[index] for index in section_order]
	old_order += [by_symbol_name[name] for name in desired_names]
	if len(old_order) != len(entries) or len(set(old_order)) != len(entries):
		raise SystemExit("unexpected extra final symbols")
	old_to_new = {old: new for new, old in enumerate(old_order)}
	for new, old in enumerate(old_order):
		struct.pack_into(">IIIBBH", blob, symtab[4] + new * symtab[9], *entries[old])
	for name in (".relaextabindex", ".rela.text"):
		_, rela = by_name[name]
		for offset in range(rela[4], rela[4] + rela[5], rela[9]):
			r_offset, info, addend = struct.unpack_from(">IIi", blob, offset)
			struct.pack_into(">IIi", blob, offset, r_offset, (old_to_new[info >> 8] << 8) | (info & 0xFF), addend)
	symtab[7] = 8
	shoff = struct.unpack_from(">I", blob, 0x20)[0]
	shentsize = struct.unpack_from(">H", blob, 0x2E)[0]
	struct.pack_into(">IIIIIIIIII", blob, shoff + by_name[".symtab"][0] * shentsize, *symtab)
	comment_index, comment = by_name[".comment"]
	alignments = [0, 1, 4, 4, 4, 8, 4, 4, 4, 4, 4, 1, 4, 4, 0, 0, 0, 0, 0, 0]
	flags = [0] * 6 + [0x800] * 8 + [0] * 6
	for index, (alignment, flag) in enumerate(zip(alignments, flags)):
		struct.pack_into(">II", blob, comment[4] + 0x2C + index * 8, alignment, flag)
	comment[5] = 0xCC
	struct.pack_into(">IIIIIIIIII", blob, shoff + comment_index * shentsize, *comment)
	path.write_bytes(blob)


def reorder_sections(path: Path) -> None:
	blob = bytearray(path.read_bytes())
	header = list(struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0))
	shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
	sections, by_name = elf_layout(blob)
	order = [
		"",
		"extab",
		"extabindex",
		".text",
		".bss",
		".relaextabindex",
		".rela.text",
		".symtab",
		".strtab",
		".shstrtab",
		".comment",
	]
	if shnum != len(order) or set(by_name) | {""} != set(order):
		raise SystemExit("unexpected final section set")
	old_to_new = {by_name[name][0]: index for index, name in enumerate(order) if name}
	old_to_new[0] = 0
	reordered = [sections[0]] + [by_name[name][1] for name in order[1:]]
	for section in reordered:
		if section[6] in old_to_new:
			section[6] = old_to_new[section[6]]
		if section[1] in (4, 9) and section[7] in old_to_new:
			section[7] = old_to_new[section[7]]

	old_symtab = by_name[".symtab"][1]
	for offset in range(old_symtab[4], old_symtab[4] + old_symtab[5], old_symtab[9]):
		symbol = list(struct.unpack_from(">IIIBBH", blob, offset))
		if symbol[5] in old_to_new:
			symbol[5] = old_to_new[symbol[5]]
		struct.pack_into(">IIIBBH", blob, offset, *symbol)
	for index, section in enumerate(reordered):
		struct.pack_into(">IIIIIIIIII", blob, shoff + index * shentsize, *section)
	header[13] = order.index(".shstrtab")
	struct.pack_into(">16sHHIIIIIHHHHHH", blob, 0, *header)
	path.write_bytes(blob)


def main() -> None:
	parser = argparse.ArgumentParser()
	parser.add_argument("object", type=Path)
	parser.add_argument("stamp", type=Path)
	parser.add_argument("--objcopy", type=Path, required=True)
	args = parser.parse_args()

	if text_hash(args.object.read_bytes()) != TEXT_SHA256:
		raise SystemExit("unexpected input .text hash")
	with tempfile.TemporaryDirectory(dir=args.object.parent) as directory:
		temporary = Path(directory)
		added = temporary / "added.o"
		output = temporary / "output.o"
		subprocess.run(
			[
				str(args.objcopy),
				"--add-symbol",
				"lbl_8042E050=0,global",
				str(args.object),
				str(added),
			],
			check=True,
		)
		redirect_literal(added)
		subprocess.run(
			[
				str(args.objcopy),
				"--remove-section",
				".sdata2",
				"--strip-symbol",
				"@11",
				"--redefine-sym",
				"@12=@etb_80008C68",
				"--redefine-sym",
				"@13=@eti_8000F37C",
				str(added),
				str(output),
			],
			check=True,
		)
		fix_bss_layout(output)
		normalize_symbols_and_comment(output)
		reorder_sections(output)
		result = output.read_bytes()
		if text_hash(result) != TEXT_SHA256:
			raise SystemExit("unexpected output .text hash")
		_, sections = elf_layout(result)
		if ".sdata2" in sections:
			raise SystemExit("private .sdata2 section survived")
		os.chmod(output, args.object.stat().st_mode)
		output.replace(args.object)

	args.stamp.parent.mkdir(parents=True, exist_ok=True)
	args.stamp.touch()


if __name__ == "__main__":
	main()
