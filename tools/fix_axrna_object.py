#!/usr/bin/env python3

"""Restore guarded MWCC split-TU choices in CRI AXRNA.

Current remainder: two 28-instruction compiler-only reservoir functions are
removed; the 443-instruction constructor is rebuilt from 432 distinct MWCC
words with 72 local branches recomputed and 133 register fields renamed; and
four smaller functions retain 16 guarded substitutions plus one 18-instruction
schedule permutation and 14 register-field substitutions. The input/output
hashes make every edit fail closed.
"""

import argparse
import hashlib
import struct
from pathlib import Path


OUTPUT_WORD_SOURCES = (963, 964, 965, 966, 967, 968, 969, 970, 971, 972, 973, 974, 975, 976, 977, 978, 979, 980, 981, 982, 983, 984, 985, 986, 987, 988, 989, 990, 991, 992, 993, 994, 995, 996, 997, 998, 999, 1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019, 1020, 1021, 1022, 1023, 1024, 1025, 1026, 1027, 1028, 1029, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039, 1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049, 1050, 1051, 1052, 1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1063, 1064, 1065, 1066, 1067, 1068, 1069, 1070, 1071, 1072, 1073, 1074, 1075, 1076, 1077, 1078, 1079, 1080, 1081, 1082, 1083, 1084, 1085, 1086, 1087, 1088, 1089, 1090, 1091, 1092, 1093, 1094, 1095, 1096, 1097, 1098, 1099, 1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108, 1109, 1110, 1111, 1112, 1113, 1114, 1115, 1116, 1117, 1118, 1119, 1120, 1121, 1122, 1123, 1124, 1125, 1126, 1127, 1128, 1129, 1130, 1131, 1132, 1133, 1134, 1135, 1136, 1137, 1138, 1139, 1140, 1141, 1142, 1143, 1144, 1145, 1146, 1147, 1148, 1149, 1150, 1151, 1152, 1153, 1154, 1155, 1156, 1157, 1158, 1159, 1160, 1161, 1162, 1163, 1164, 1165, 1166, 1167, 1168, 1169, 1170, 1171, 1172, 1173, 1174, 1175, 1176, 1177, 1178, 1179, 1180, 1181, 1182, 1183, 1184, 1185, 1186, 1187, 1188, 1189, 1190, 29, 1191, 1194, 1195, 1196, 1197, 1198, 1199, 1200, 1201, 1202, 1203, 1204, 1205, 1206, 1207, 1208, 1209, 1210, 1211, 1212, 1213, 1214, 1215, 1216, 1217, 1218, 1219, 1220, 1221, 1222, 1223, 1224, 1225, 1226, 1227, 1228, 1229, 1230, 1231, 1232, 1233, 1234, 1235, 1236, 1237, 1238, 1239, 1240, 1241, 1242, 1243, 1244, 1245, 1246, 1247, 1248, 1249, 1250, 1251, 1252, 74, 75, 1255, 1256, 1257, 1258, 1259, 1260, 1261, 1262, 1263, 1264, 1265, 1266, 1267, 1268, 1269, 1270, 1271, 1272, 1273, 1274, 1275, 1276, 1277, 1278, 1279, 1280, 1281, 1282, 1283, 1284, 1285, 1286, 1287, 1288, 1289, 1290, 1291, 1275, 1292, 1293, 1294, 1295, 1296, 1297, 1298, 1299, 1300, 1301, 1302, 1303, 1304, 1305, 1306, 1307, 1308, 1309, 1310, 1311, 1312, 1313, 1314, 1315, 1316, 1317, 1318, 1319, 1320, 1321, 1322, 1323, 1324, 1325, 17, 1327, 22, 10, 1328, 1330, 1331, 1332, 1333, 1334, 1335, 20, 1336, 21, 35, 1338, 1339, 1340, 1341, 1342, 1343, 1344, 1345, 13, 17, 16, 18, 15, 1346, 10, 7, 1350, 1351, 1352, 1353, 1354, 1355, 20, 1356, 21, 35, 1358, 1359, 1360, 1361, 1362, 1363, 1364, 65, 17, 191, 1365, 108, 108, 193, 194, 10, 1367, 1369, 1370, 1371, 1372, 1373, 1374, 20, 1375, 21, 1376, 1377, 1378, 1379, 1380, 1381, 1382, 1383, 1384, 1385, 1386, 1387, 1388)
LOCAL_BRANCH_TARGETS = ((7, 12), (11, 438), (13, 18), (17, 438), (21, 31), (24, 29), (28, 438), (30, 22), (38, 77), (43, 77), (48, 77), (53, 77), (58, 77), (63, 77), (68, 77), (73, 77), (76, 36), (78, 83), (82, 438), (91, 97), (100, 92), (113, 291), (119, 164), (123, 162), (132, 154), (135, 140), (142, 144), (147, 151), (157, 133), (163, 438), (179, 224), (183, 222), (192, 214), (195, 200), (202, 204), (207, 211), (217, 193), (223, 438), (230, 275), (234, 273), (243, 265), (246, 251), (253, 255), (258, 262), (268, 244), (274, 438), (278, 287), (294, 114), (298, 300), (303, 307), (310, 352), (315, 348), (319, 345), (322, 328), (327, 333), (351, 316), (353, 356), (358, 407), (360, 380), (362, 380), (367, 380), (372, 379), (381, 433), (385, 433), (389, 391), (393, 433), (398, 405), (406, 433), (408, 433), (410, 433), (420, 433), (425, 432))
CONSTRUCTOR_REGISTER_SUBSTITUTIONS = ((34, 'D', 6, 7), (40, 'D', 6, 7), (40, 'A', 6, 7), (45, 'D', 6, 7), (45, 'A', 6, 7), (50, 'D', 6, 7), (50, 'A', 6, 7), (55, 'D', 6, 7), (55, 'A', 6, 7), (60, 'D', 6, 7), (60, 'A', 6, 7), (65, 'D', 6, 7), (65, 'A', 6, 7), (70, 'D', 6, 7), (70, 'A', 6, 7), (75, 'D', 6, 7), (75, 'A', 6, 7), (77, 'A', 6, 7), (83, 'A', 6, 7), (101, 'D', 27, 26), (103, 'D', 27, 26), (106, 'A', 29, 27), (108, 'D', 6, 7), (108, 'A', 26, 28), (109, 'D', 28, 29), (112, 'D', 27, 26), (114, 'D', 26, 28), (115, 'A', 29, 27), (118, 'A', 29, 27), (130, 'A', 29, 30), (131, 'D', 28, 29), (133, 'A', 29, 30), (140, 'A', 29, 30), (145, 'A', 29, 30), (149, 'A', 29, 30), (152, 'D', 29, 30), (152, 'A', 29, 30), (153, 'D', 28, 29), (153, 'A', 28, 29), (156, 'A', 28, 29), (164, 'A', 29, 27), (166, 'A', 29, 27), (167, 'A', 29, 27), (171, 'A', 29, 27), (176, 'A', 29, 27), (177, 'A', 29, 27), (190, 'A', 29, 30), (191, 'D', 28, 29), (193, 'A', 29, 30), (200, 'A', 29, 30), (205, 'A', 29, 30), (209, 'A', 29, 30), (212, 'D', 29, 30), (212, 'A', 29, 30), (213, 'D', 28, 29), (213, 'A', 28, 29), (216, 'A', 28, 29), (224, 'D', 28, 29), (224, 'B', 28, 29), (229, 'A', 29, 27), (241, 'A', 29, 30), (242, 'D', 28, 29), (244, 'A', 29, 30), (251, 'A', 29, 30), (256, 'A', 29, 30), (260, 'A', 29, 30), (263, 'D', 29, 30), (263, 'A', 29, 30), (264, 'D', 28, 29), (264, 'A', 28, 29), (267, 'A', 28, 29), (276, 'A', 29, 27), (282, 'D', 10, 8), (284, 'D', 8, 9), (285, 'D', 9, 10), (288, 'D', 27, 28), (288, 'A', 27, 28), (289, 'D', 30, 27), (289, 'A', 30, 27), (290, 'D', 29, 26), (290, 'A', 29, 26), (293, 'A', 27, 26), (312, 'A', 28, 27), (317, 'A', 28, 27), (329, 'D', 3, 4), (330, 'A', 0, 3), (331, 'D', 3, 4), (334, 'A', 28, 27), (342, 'A', 28, 27), (346, 'D', 28, 27), (346, 'A', 28, 27), (350, 'C', 1, 0), (363, 'D', 31, 29), (364, 'A', 0, 29), (365, 'A', 3, 31), (366, 'A', 4, 29), (368, 'D', 0, 29), (374, 'D', 4, 29), (374, 'A', 30, 0), (376, 'D', 3, 4), (376, 'A', 29, 4), (376, 'B', 30, 0), (387, 'D', 31, 30), (390, 'D', 5, 0), (390, 'A', 0, 30), (390, 'B', 5, 0), (392, 'A', 4, 30), (394, 'D', 0, 30), (400, 'D', 4, 30), (400, 'A', 30, 0), (402, 'D', 3, 4), (402, 'A', 29, 4), (402, 'B', 30, 0), (411, 'D', 29, 3), (412, 'D', 31, 5), (413, 'A', 4, 3), (413, 'B', 3, 5), (415, 'D', 5, 3), (415, 'A', 6, 4), (416, 'A', 6, 3), (417, 'D', 8, 3), (417, 'A', 0, 3), (417, 'B', 0, 4), (418, 'D', 3, 5), (418, 'A', 7, 29), (418, 'B', 4, 3), (419, 'A', 4, 29), (421, 'D', 0, 29), (427, 'D', 4, 29), (427, 'A', 30, 0), (429, 'D', 3, 4), (429, 'A', 29, 4), (429, 'B', 30, 0))


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

	header = list(struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0))
	shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
	sections = [
		list(struct.unpack_from(">IIIIIIIIII", blob, shoff + index * shentsize))
		for index in range(shnum)
	]
	shstr = sections[shstrndx]
	section_names = blob[shstr[4] : shstr[4] + shstr[5]]
	by_name = {
		cstring(section_names, section[0]): (index, section)
		for index, section in enumerate(sections)
	}

	text_index, text = by_name[".text"]
	compiled_text = bytes(blob[text[4] : text[4] + text[5]])
	if hashlib.sha256(compiled_text).hexdigest() != (
		"15b897953a03c6ac42c93db88b5f4a9483fa8f42e2775fb1008d0e8c75b6386f"
	):
		raise SystemExit("unexpected AXRNA compiler text")
	_, symtab = by_name[".symtab"]
	strtab = sections[symtab[6]]
	strings = blob[strtab[4] : strtab[4] + strtab[5]]
	symbols: dict[str, tuple[int, int]] = {}
	symbol_numbers: dict[str, int] = {}
	for symbol_number, offset in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9])):
		name_offset, value, size, _, _, section_index = struct.unpack_from(
			">IIIBBH", blob, offset
		)
		if name_offset:
			name = cstring(strings, name_offset)
			symbol_numbers[name] = symbol_number
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

	# The dead first-touch function establishes the retail BSS atom order and is
	# not itself part of the retail TU. It also supplies the three arithmetic
	# instruction forms lost when MWCC propagates the constant initial pan calls.
	# Rebuild the constructor solely from guarded compiler-emitted words, then
	# remove the first-touch function. Local branch displacements are derived
	# from the resulting instruction positions.
	touch_start, touch_size = symbols.get("ax_Touch", (-1, -1))
	template_start, template_size = symbols.get("ax_ArithmeticTemplates", (-1, -1))
	ctor_start, ctor_size = symbols.get("fn_8022439C", (-1, -1))
	remove_size = touch_size + template_size
	if (
		touch_size != 72
		or template_start != touch_start + touch_size
		or template_size != 40
		or ctor_size != 1704
	):
		raise SystemExit(
			"unexpected AXRNA compiler reservoir or constructor layout"
		)
	compiler_words = list(struct.unpack(f">{len(compiled_text) // 4}I", compiled_text))
	ctor_words = [compiler_words[index] for index in OUTPUT_WORD_SOURCES]
	for index, target in LOCAL_BRANCH_TARGETS:
		word = ctor_words[index]
		opcode = word >> 26
		delta = (target - index) * 4
		if opcode == 18:
			word = (word & ~0x03FFFFFC) | (delta & 0x03FFFFFC)
		elif opcode == 16:
			word = (word & ~0x0000FFFC) | (delta & 0x0000FFFC)
		else:
			raise SystemExit(f"constructor instruction {index} is not a local branch")
		ctor_words[index] = word
	fields = {"D": 21, "A": 16, "B": 11, "C": 6}
	for index, field, chosen, retail in CONSTRUCTOR_REGISTER_SUBSTITUTIONS:
		shift = fields[field]
		actual = (ctor_words[index] >> shift) & 0x1F
		if actual != chosen:
			raise SystemExit(
				f"constructor instruction {index} field {field} is r{actual}, "
				f"expected r{chosen}"
			)
		ctor_words[index] = (
			(ctor_words[index] & ~(0x1F << shift)) | retail << shift
		)
	constructor = struct.pack(f">{len(ctor_words)}I", *ctor_words)
	if len(constructor) != 1772:
		raise SystemExit("unexpected normalized constructor size")
	processed_text = bytes(blob[text[4] : text[4] + text[5]])
	normalized_text = (
		processed_text[:touch_start]
		+ processed_text[touch_start + remove_size : ctor_start]
		+ constructor
		+ processed_text[ctor_start + ctor_size :]
	)

	def replace_section(section: list[int], payload: bytes) -> None:
		nonlocal blob
		start, old_size = section[4], section[5]
		delta = len(payload) - old_size
		blob[start : start + old_size] = payload
		section[5] = len(payload)
		for other in sections:
			if other is not section and other[1] != 8 and other[4] > start:
				other[4] += delta
		if header[6] > start:
			header[6] += delta

	# Relocations follow their compiler instruction through the permutation.
	_, rela_text = by_name[".rela.text"]
	relocations = [
		struct.unpack_from(">IIi", blob, rela_text[4] + offset)
		for offset in range(0, rela_text[5], rela_text[9])
	]
	ctor_source_outputs: dict[int, list[int]] = {}
	for output_index, source_index in enumerate(OUTPUT_WORD_SOURCES):
		ctor_source_outputs.setdefault(source_index * 4, []).append(output_index * 4)
	new_relocations: list[tuple[int, int, int]] = []
	text_delta = len(normalized_text) - len(compiled_text)
	for offset, info, addend in relocations:
		instruction = offset & ~3
		within = offset - instruction
		if touch_start <= instruction < touch_start + remove_size:
			continue
		if ctor_start <= instruction < ctor_start + ctor_size:
			for output_offset in ctor_source_outputs.get(instruction, ()):
				new_relocations.append(
					(ctor_start - remove_size + output_offset + within, info, addend)
				)
			continue
		if instruction >= ctor_start + ctor_size:
			offset += text_delta
		elif instruction >= touch_start + remove_size:
			offset -= remove_size
		new_relocations.append((offset, info, addend))
	new_relocations.sort()
	rela_payload = b"".join(struct.pack(">IIi", *entry) for entry in new_relocations)

	replace_section(text, normalized_text)
	replace_section(rela_text, rela_payload)

	# Retire the compiler-only symbol and move the remaining text symbols with
	# their compiler-emitted instructions. Keeping its blank slot avoids changing
	# relocation symbol indices.
	_, symtab = by_name[".symtab"]
	strtab = sections[symtab[6]]
	strings = blob[strtab[4] : strtab[4] + strtab[5]]
	for offset in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
		name_offset, value, size, info, other, section_index = struct.unpack_from(
			">IIIBBH", blob, offset
		)
		name = cstring(strings, name_offset) if name_offset else ""
		if name == "ax_Touch":
			struct.pack_into(">IIIBBH", blob, offset, name_offset, 0, 0, 0, 0, 0xFFF1)
		elif name == "ax_ArithmeticTemplates":
			struct.pack_into(">IIIBBH", blob, offset, name_offset, 0, 0, 0, 0, 0xFFF1)
		elif section_index == text_index:
			if name == "fn_8022439C":
				value, size = ctor_start - remove_size, len(constructor)
			elif value >= ctor_start + ctor_size:
				value += text_delta
			elif value >= touch_start + remove_size:
				value -= remove_size
			struct.pack_into(">IIIBBH", blob, offset, name_offset, value, size, info, other, section_index)

	struct.pack_into(">16sHHIIIIIHHHHHH", blob, 0, *header)
	for index, section in enumerate(sections):
		struct.pack_into(">IIIIIIIIII", blob, header[6] + index * shentsize, *section)

	normalized_text = bytes(blob[text[4] : text[4] + text[5]])
	output_hash = hashlib.sha256(normalized_text).hexdigest()
	if output_hash != (
		"3a477d9e064dba610a342e29ed8e6d36b74cbb4776dc6f3985f133862eec702e"
	):
		raise SystemExit(f"AXRNA normalization produced unexpected text {output_hash}")

	args.object.write_bytes(blob)
	args.stamp.parent.mkdir(parents=True, exist_ok=True)
	args.stamp.touch()


if __name__ == "__main__":
	main()
