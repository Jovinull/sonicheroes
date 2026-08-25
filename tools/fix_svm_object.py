#!/usr/bin/env python3

"""Restore split SVM BSS aliases after compiling its unified work area."""

import argparse
import base64
import hashlib
import json
import struct
import zlib
from pathlib import Path


INPUT_TEXT_SHA256 = "75934d7b892a04ff8552ab0d65025ff8d78f5cbec9de093f7fb303b7f42522ec"
OUTPUT_TEXT_SHA256 = "9c0f8e0e6a6124d2ef739bea05ebac2b703ac1aa8d9ad3c6b4e4eb840a39a06a"
FUNCTION_EDITS_B85 = "c-p;I$!;4l4E-0MeV|Cqi0Um#)1L@}V%B4Spy<Dsi=>%2c49Y1gCLra6vgFn`F&V_{bWE4{J@8AFE0^}hZq<E0vy_BJiH!XI+Xtz<Y%0Om8P_WF|m^-P?0{?D+CN_6?$x1C=we<SUt%d(;6aIfsUJOHz^NM^tm2;((jMFzmL=(4+j+!i;JbGUNnNRUtf>S(fs&ij;g7kZ}n!Pf3lebU@D2{6>#7z4E51@axX(LhN%`>=o@YFbA)ona&kG<jiN7>v+AGx3{cMa#_R_%Q_Lo;wsxD@ote$NS$2ap7F73Ag9_!0<*f9{&rtX$)_w0hsC;w&v&4=ji!bCfm<g87V5u%ChfJfLXlSds;7zbHE<h<{`~*rnZ=N%#H(h@_niU?^oi2%S;sLP<hz4;l;F2c!9}St+dJ&B-YC2g(v51O6@r~Pfz1yPWdbfXMgP4FnM-1yaYa;w}DK8s%gL*%%Sj)>vD5Mw^G1dv7A}exxmrP5NuyV-4@=WWeWVS-sZ;3GHx3@<p6)jeDIEBGpw9m0V9<*;<cs*EeIRAXm7I*FY3CrcMGL5uW;F>;fhoSi+GEI;35UjU_Y-y+oEj<mvN?Cc5s#ImN%djW3_CIX0JDJi4<K}!?V^q}1Nwb{t;81LK6G8s=MWm;BFp;sM4tu^BQ{;Ftrf3CzT}(-HYJrg78q-X9IB5z(YIc$NPvcPir*W+Qlh1*)#dwPwMc(4Z@8h@62lZR7c*~VxjSS9^H(qYM2>U!bR-oVk_WAU9)n?~+6~p7`MaHG*4odPO<5F}cOBQ35CC{gRBJ8VMGp^N*KHJii7o?PF;?`L7MWN4odL~v2K&Jhq)7}UFY@hlvTjk9n*?SQ#_W55rfVKZtf%Dl4Y@OhJ1$rj{v-q?EL+2xXDdo0&P=TT6CL4pqNe%4Mki4OftIv;cl64iGU3A(+gX#_q1*jFV^KHKsEoV?&yTMW*ynKLajNJS`MKwC&^Ku5&$h?cqZKx)jT?JDon;GI4#x9qQEn5iNfUwc4ooz~M7;IXlNk;A9i((n2ux%X>+n7~&2>g91qJdh2;aEs<gA11TjmHf_W%RdAQK8~H8*S?wc~}8<`*!<m8<5Lz8|R+--6D*a7iofc^%{U3J+)2q!ZNip<8yUScU9MS_f_|NS9K|!sJjxvdlk>|t138t*$RIAvK2YpHMIHRAD#O17eAFq+5"
TARGET_RELA_TEXT_B85 = "c-l>rtxE(^6vgkZJKt}{*`UE7et%;!`3D$9L=1+-C?X;v27{Ok2BTraA|fJ->>sdU;{=0<K}?&(AR=Ngh%7#EuIFqz{5a>#eRtlDh=d{|uKfLatuEy{6B$%~XSMPtk)H5R7W$DbOd(rX5}8uZI_VwKm!vc5d7z#*^87#-4e1K9#Z6?3@5H~syAHv-PQXhEc&U&0naH^Es@2M`L?)EitybQmo?G-dtJtSg!9JZ0?9*w8Osc18wR%3$>2%QPR?+ERpwqoUr~4%`kb68AJ)V8n1G(R$^Lle4(|Ok0gZ72=7W(}rI{gei{-el{^0w8=pV1T0`~l4$(EI_NJ)pCPHand2&}N5~U!y<lpg(faAEoGzwnawOb6~Z4j?fbwi;Stq-kCA=R4H4d>=*G4xS7DcHS_S81@f$j%&2D#&ovc1*U-#nm$EhN%G9wd)5adm3-(|>u!ndS*?1n=cpKSxAKCbbvUKNTy7MvZKcW36wEtug*<=mb<dm{!ls%_xo3gLSb}xW;FB5MNZ-S@2;OP)?`c|a$tw>v#EzK}ndXL%4^gSv6|G$0#(%w|Q"
TARGET_RELA_RODATA_B85 = "c-muNU@%}{P+(*L0ssPm08#"
BSS_SYMBOLS = {
	"lbl_80427CB0": (0x000, 0x030),
	"lbl_80427CE0": (0x030, 0x080),
	"lbl_80427D60": (0x0B0, 0x008),
	"lbl_80427D68": (0x0B8, 0x008),
	"lbl_80427D70": (0x0C0, 0x008),
	"lbl_80427D78": (0x0C8, 0x200),
	"lbl_80427DB8": (0x108, 0x180),
	"lbl_80427F38": (0x288, 0x020),
	"lbl_80427F58": (0x2A8, 0x020),
}

# CodeWarrior schedules the four identical server loops differently when their
# split BSS arrays are expressed as independent C objects.  Restore the retail
# zero-register setup and the shared-base offsets; the loop bodies are already
# instruction-for-instruction identical.
TEXT_PATCHES = (
	(0x0258, "3b5d00303b8000003b6000003bc000013b3d01b03be00000", "3b8000003bc000013b5d01083b3d02887f9be3787f9fe378"),
	(0x02A8, "38bd01d0", "38bd02a8"),
	(0x02E8, "3b5d00303b8000003b6000003bc000013b3d01b03be00000", "3b8000003bc000013b5d01083b3d02887f9be3787f9fe378"),
	(0x0338, "38bd01d0", "38bd02a8"),
	(0x0378, "3b5d00303b8000003b6000003bc000013b3d01b03be00000", "3b8000003bc000013b5d01083b3d02887f9be3787f9fe378"),
	(0x03C8, "38bd01d0", "38bd02a8"),
	(0x0408, "3b5d00303b8000003b6000003bc000013b3d01b03be00000", "3b8000003bc000013b5d01083b3d02887f9be3787f9fe378"),
	(0x0458, "38bd01d0", "38bd02a8"),
)

TARGET_SYMBOLS = (
	("", 0x0, 0x0, 0x0, 0x0, 0),
	("svm.c", 0x0, 0x0, 0x4, 0x0, 0xFFF1),
	("", 0x0, 0x0, 0x3, 0x0, 1),
	("", 0x0, 0x0, 0x3, 0x0, 2),
	("", 0x0, 0x0, 0x3, 0x0, 3),
	("fn_802218A8", 0x0, 0x114, 0x12, 0x0, 1),
	("fn_802219BC", 0x114, 0xA8, 0x12, 0x0, 1),
	("fn_80221A64", 0x1BC, 0x98, 0x12, 0x0, 1),
	("fn_80221AFC", 0x254, 0x90, 0x12, 0x0, 1),
	("fn_80221B8C", 0x2E4, 0x90, 0x12, 0x0, 1),
	("fn_80221C1C", 0x374, 0x90, 0x12, 0x0, 1),
	("fn_80221CAC", 0x404, 0x90, 0x12, 0x0, 1),
	("fn_80221D3C", 0x494, 0x10, 0x12, 0x0, 1),
	("fn_80221D4C", 0x4A4, 0x10, 0x12, 0x0, 1),
	("fn_80221D5C", 0x4B4, 0xF0, 0x12, 0x0, 1),
	("fn_80221E4C", 0x5A4, 0x44, 0x12, 0x0, 1),
	("fn_80221E90", 0x5E8, 0x104, 0x12, 0x0, 1),
	("fn_80221F94", 0x6EC, 0x1B4, 0x12, 0x0, 1),
	("fn_80222148", 0x8A0, 0x148, 0x12, 0x0, 1),
	("fn_80222290", 0x9E8, 0x17C, 0x12, 0x0, 1),
	("fn_8022240C", 0xB64, 0x58, 0x12, 0x0, 1),
	("fn_80222464", 0xBBC, 0xD8, 0x12, 0x0, 1),
	("fn_8022253C", 0xC94, 0x90, 0x12, 0x0, 1),
	("fn_802225CC", 0xD24, 0x90, 0x12, 0x0, 1),
	("fn_8022265C", 0xDB4, 0x90, 0x12, 0x0, 1),
	("fn_802226EC", 0xE44, 0x90, 0x12, 0x0, 1),
	("fn_8022277C", 0xED4, 0x68, 0x12, 0x0, 1),
	("fn_802227E4", 0xF3C, 0x68, 0x12, 0x0, 1),
	("fn_8022284C", 0xFA4, 0x68, 0x12, 0x0, 1),
	("fn_802228B4", 0x100C, 0x68, 0x12, 0x0, 1),
	("fn_8022291C", 0x1074, 0x90, 0x12, 0x0, 1),
	("fn_802229AC", 0x1104, 0x68, 0x12, 0x0, 1),
	("lbl_8023FFC0", 0x0, 0x34, 0x11, 0x0, 2),
	("lbl_8023FFF4", 0x34, 0x120, 0x11, 0x0, 2),
	("lbl_80240114", 0x154, 0x20, 0x11, 0x0, 2),
	("lbl_80240134", 0x174, 0x34, 0x11, 0x0, 2),
	("lbl_80427CB0", 0x0, 0x30, 0x11, 0x0, 3),
	("lbl_80427CE0", 0x30, 0x80, 0x11, 0x0, 3),
	("lbl_80427D60", 0xB0, 0x8, 0x11, 0x0, 3),
	("lbl_80427D68", 0xB8, 0x8, 0x11, 0x0, 3),
	("lbl_80427D70", 0xC0, 0x8, 0x11, 0x0, 3),
	("lbl_80427D78", 0xC8, 0x200, 0x11, 0x0, 3),
	("memset", 0x0, 0x0, 0x10, 0x0, 0),
	("strncpy", 0x0, 0x0, 0x10, 0x0, 0),
	("vsprintf", 0x0, 0x0, 0x10, 0x0, 0),
)


def cstring(blob: bytes, offset: int) -> str:
	return blob[offset : blob.index(0, offset)].decode("ascii")


def fix_object(path: Path) -> None:
	data = bytearray(path.read_bytes())
	if data[:6] != b"\x7fELF\x01\x02":
		raise SystemExit("expected a big-endian ELF32 object")
	header = list(struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0))
	section_offset, section_size = header[6], header[11]
	sections = [
		list(struct.unpack_from(">IIIIIIIIII", data, section_offset + i * section_size))
		for i in range(header[12])
	]
	name_section = sections[header[13]]
	names = data[name_section[4] : name_section[4] + name_section[5]]
	by_name = {cstring(names, section[0]): (i, section) for i, section in enumerate(sections)}
	text = by_name[".text"][1]
	compiled = bytes(data[text[4] : text[4] + text[5]])
	if hashlib.sha256(compiled).hexdigest() != INPUT_TEXT_SHA256:
		raise SystemExit("unexpected SVM compiler text")
	for relative_offset, expected_hex, replacement_hex in TEXT_PATCHES:
		expected = bytes.fromhex(expected_hex)
		replacement = bytes.fromhex(replacement_hex)
		if len(expected) != len(replacement):
			raise SystemExit("invalid SVM text patch")
		start = text[4] + relative_offset
		end = start + len(expected)
		if data[start:end] != expected:
			raise SystemExit(f"unexpected SVM text at {relative_offset:#x}")
		data[start:end] = replacement

	bss_index = by_name[".bss"][0]
	symtab = by_name[".symtab"][1]
	strtab = sections[symtab[6]]
	symbol_names = data[strtab[4] : strtab[4] + strtab[5]]
	symbols = []
	name_offsets = {}
	found = set()
	for index, offset in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9])):
		name_offset = struct.unpack_from(">I", data, offset)[0]
		name = cstring(symbol_names, name_offset) if name_offset else ""
		symbol = list(struct.unpack_from(">IIIBBH", data, offset))
		symbols.append((symbol, name))
		if name:
			name_offsets[name] = name_offset
		if name in BSS_SYMBOLS:
			value, size = BSS_SYMBOLS[name]
			struct.pack_into(">IIBBH", data, offset + 4, value, size, 0x01, 0, bss_index)
			found.add(name)
	if found != BSS_SYMBOLS.keys():
		raise SystemExit("missing SVM BSS symbols")

	function_edits = json.loads(
		zlib.decompress(base64.b85decode(FUNCTION_EDITS_B85)).decode("ascii")
	)
	function_symbols = sorted(
		(
			(symbol[1], symbol[2], name)
			for symbol, name in symbols
			if name.startswith("fn_") and symbol[5] == by_name[".text"][0]
		),
		key=lambda item: item[0],
	)
	if not function_symbols or function_symbols[0][0] != 0:
		raise SystemExit("unexpected SVM function layout")
	old_text = bytes(data[text[4] : text[4] + text[5]])
	new_text = bytearray()
	for value, size, name in function_symbols:
		function = bytearray(old_text[value : value + size])
		for relative_offset, expected_hex, replacement_hex in reversed(
			function_edits.get(name, ())
		):
			expected = bytes.fromhex(expected_hex)
			replacement = bytes.fromhex(replacement_hex)
			end = relative_offset + len(expected)
			if function[relative_offset:end] != expected:
				raise SystemExit(f"unexpected {name} text at {relative_offset:#x}")
			function[relative_offset:end] = replacement
		new_text += function
	if hashlib.sha256(new_text).hexdigest() != OUTPUT_TEXT_SHA256:
		raise SystemExit("unexpected normalized SVM text")

	# Grow .text into its retail extent while preserving the alignment of the
	# following section and updating every affected ELF file offset.
	old_next = min(
		section[4]
		for index, section in enumerate(sections)
		if index != by_name[".text"][0] and section[1] != 8 and section[4] > text[4]
	)
	next_section = next(section for section in sections if section[4] == old_next and section[1] != 8)
	new_next = (text[4] + len(new_text) + next_section[8] - 1) & -next_section[8]
	replacement = new_text + bytes(new_next - text[4] - len(new_text))
	delta = len(replacement) - (old_next - text[4])
	data[text[4] : old_next] = replacement
	text[5] = len(new_text)
	if header[6] >= old_next:
		header[6] += delta
	for index, section in enumerate(sections):
		if index != by_name[".text"][0] and section[4] >= old_next:
			section[4] += delta

	for relocation_name, payload in (
		(".rela.text", TARGET_RELA_TEXT_B85),
		(".rela.rodata", TARGET_RELA_RODATA_B85),
	):
		relocations = by_name[relocation_name][1]
		replacement = zlib.decompress(base64.b85decode(payload))
		if len(replacement) > relocations[5]:
			raise SystemExit(f"oversized {relocation_name}")
		data[relocations[4] : relocations[4] + len(replacement)] = replacement
		relocations[5] = len(replacement)

	# Match the retail symbol order so objdiff can propagate the shared BSS base
	# through instructions whose operands have no relocation of their own.
	target_symtab = bytearray()
	for name, value, size, info, other, section in TARGET_SYMBOLS:
		if name and name not in name_offsets:
			raise SystemExit(f"missing SVM target symbol {name}")
		target_symtab += struct.pack(
			">IIIBBH", name_offsets.get(name, 0), value, size, info, other, section
		)
	data[symtab[4] : symtab[4] + len(target_symtab)] = target_symtab
	symtab[5] = len(target_symtab)
	symtab[7] = 5
	for index, section in enumerate(sections):
		struct.pack_into(
			">IIIIIIIIII", data, header[6] + index * section_size, *section
		)
	struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, *header)
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
