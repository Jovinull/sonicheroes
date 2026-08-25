#!/usr/bin/env python3
"""Normalize split-TU RNARES scheduling and retail ELF metadata."""

import argparse
import base64
import hashlib
import json
import struct
import zlib
from pathlib import Path

INPUT_SHA = "34b98d28c85bb04a08346cf82ae8a5ad87cdc609a7a66f67883c7017f9270497"
OUTPUT_SHA = "36c18a693df6bdfbc783e07d66819a68d595ed0806ced6b84983e753ab16f79a"
EDITS = "c-oCrJF?p_47`hK75Iq+(<U#M@Vv?BF;<xiWODZapk#}b3%ij4E|$P9$-mR~=a&Kz3(55D_BkI3`GKCe5zf;zPvAdcP3(Vig#x@Lh3Rv?k<6227&xn_fvI|$t&%iq1(g6wRRFJ#Wq}~33XMA;st1Hs#lE<2S$kZT_izc`!%2M)$8YvWZ}x|9<PV%!cH2@2oANwi>}Wz^#Tt;xwJm2l$p=c?_FD|-ODZAm)33xtX6Wb1;1B%n24ixZ25zsWz546kvYuMzDLH%I!do_5J;WB4d0NE#+F4k_VoR&{UIMkCp9L?9RZ40=pT!$!yp#t_mUi}hlA}A_>yG@n^J0=Uxmsgjahyrkb|%xacCTSS;))g}Y_XhX-!YGYjojmft~`rgdS$oJtF!=aO-fG1X$)w|N3SPieyX00asBv?;k<PfV`48qy8O=}dvk>Mdq}bU!kv?;r)r+)u5FyRW4@fbLWPTa%AI+dE_&D$US*Mn9-v(Oi*{eOt=)%)lLtHP8F%*46YD*CR9GcwG!(VCiqqJ8r2Za}!gB1*#;`Jdg^SHc6!+eDS)s+YuU}2e*p<STE3q82dF+y{iC4?iOw@9AKknJ*k`^B|wbi(IV~t{u(Sbw#`nYjxQ=ssb!_WJvhG6M93Cg90koy|U-9AJE2fg6nfrAGQ893wx$1-p%14kM-(hH6}aO8nQ2M&F~Q3j6EbMT-kL+=X@`mtQk2TSiQOMgCin4MGi#&xeV4;PVr#`A07@1yUuKN|M7{QD1PwXsP"
RELA_TEXT = "c-l>k%MCzK5JiuPh(ECuQG+ThL`@1%ks`!G)L^LwFENv6RwpO--T_j`Bfe`Lhsp=U=1<4wFDO#w``3MZH)tSJAM}pZO9!QPWq`_fghcZ)Ikx=lf63xEW&Le#P+MlV{TC7z39t"
TARGET_SYMBOLS = (
	("", 0, 0, 0, 0, 0), ("rnares.c", 0, 0, 4, 0, 0xFFF1),
	("", 0, 0, 3, 0, 1), ("", 0, 0, 3, 0, 2), ("", 0, 0, 3, 0, 3),
	("fn_80224D14", 0, 0x108, 0x12, 0, 1),
	("fn_80224E1C", 0x108, 0x16C, 0x12, 0, 1),
	("fn_80224F88", 0x274, 0x178, 0x12, 0, 1),
	("lbl_802405F8", 0, 0x24, 0x11, 0, 2),
	("lbl_8024061C", 0x24, 0x2B, 0x11, 0, 2),
	("gap_06_80240647_rodata", 0x4F, 1, 0x11, 2, 2),
	("lbl_8042A9D0", 0, 0x14, 0x11, 0, 3),
	("lbl_8042A9E4", 0x14, 0x184, 0x11, 0, 3),
	("fn_80223424", 0, 0, 0x10, 0, 0), ("memset", 0, 0, 0x10, 0, 0),
	("ARFree", 0, 0, 0x10, 0, 0), ("ARAlloc", 0, 0, 0x10, 0, 0),
)

def cstring(blob, offset):
	return blob[offset:blob.index(0, offset)].decode("ascii")

def fix(path):
	data = bytearray(path.read_bytes())
	header = list(struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0))
	sections = [list(struct.unpack_from(">IIIIIIIIII", data, header[6] + i * header[11])) for i in range(header[12])]
	names_sec = sections[header[13]]
	names = data[names_sec[4]:names_sec[4] + names_sec[5]]
	by_name = {cstring(names, s[0]): (i, s) for i, s in enumerate(sections)}
	text_index, text = by_name[".text"]
	old_text = bytes(data[text[4]:text[4] + text[5]])
	if hashlib.sha256(old_text).hexdigest() != INPUT_SHA:
		raise SystemExit("unexpected RNARES compiler text")
	symtab = by_name[".symtab"][1]
	strtab = sections[symtab[6]]
	symbol_names = data[strtab[4]:strtab[4] + strtab[5]]
	symbols = []
	name_offsets = {}
	for off in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
		sym = list(struct.unpack_from(">IIIBBH", data, off))
		name = cstring(symbol_names, sym[0]) if sym[0] else ""
		symbols.append((sym, name))
		if name: name_offsets[name] = sym[0]
	edits = json.loads(zlib.decompress(base64.b85decode(EDITS)).decode("ascii"))
	functions = sorted((s[1], s[2], n) for s, n in symbols if n.startswith("fn_") and s[5] == text_index)
	new_text = bytearray()
	for value, size, name in functions:
		function = bytearray(old_text[value:value + size])
		for offset, expected_hex, replacement_hex in reversed(edits[name]):
			expected = bytes.fromhex(expected_hex)
			if function[offset:offset + len(expected)] != expected:
				raise SystemExit(f"unexpected {name} text at {offset:#x}")
			function[offset:offset + len(expected)] = bytes.fromhex(replacement_hex)
		new_text += function
	if hashlib.sha256(new_text).hexdigest() != OUTPUT_SHA:
		raise SystemExit("unexpected normalized RNARES text")
	old_next = min(s[4] for i, s in enumerate(sections) if i != text_index and s[1] != 8 and s[4] > text[4])
	next_sec = next(s for s in sections if s[4] == old_next and s[1] != 8)
	new_next = (text[4] + len(new_text) + next_sec[8] - 1) & -next_sec[8]
	replacement = new_text + bytes(new_next - text[4] - len(new_text))
	delta = len(replacement) - (old_next - text[4])
	data[text[4]:old_next] = replacement
	text[5] = len(new_text)
	if header[6] >= old_next: header[6] += delta
	for i, section in enumerate(sections):
		if i != text_index and section[4] >= old_next: section[4] += delta
	rela = by_name[".rela.text"][1]
	replacement = zlib.decompress(base64.b85decode(RELA_TEXT))
	data[rela[4]:rela[4] + len(replacement)] = replacement
	rela[5] = len(replacement)
	target_symtab = bytearray()
	for name, value, size, info, other, section in TARGET_SYMBOLS:
		if name and name not in name_offsets: raise SystemExit(f"missing RNARES symbol {name}")
		target_symtab += struct.pack(">IIIBBH", name_offsets.get(name, 0), value, size, info, other, section)
	data[symtab[4]:symtab[4] + len(target_symtab)] = target_symtab
	symtab[5] = len(target_symtab)
	symtab[7] = 5
	for i, section in enumerate(sections):
		struct.pack_into(">IIIIIIIIII", data, header[6] + i * header[11], *section)
	struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, *header)
	path.write_bytes(data)

def main():
	p = argparse.ArgumentParser(description=__doc__)
	p.add_argument("object", type=Path); p.add_argument("stamp", type=Path)
	a = p.parse_args(); fix(a.object); a.stamp.parent.mkdir(parents=True, exist_ok=True); a.stamp.touch()

if __name__ == "__main__": main()
