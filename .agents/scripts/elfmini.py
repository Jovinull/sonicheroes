"""Minimal ELF32 reader shared by the notes/tools scripts.

Reads sections, symbols and RELA/REL relocations for both endiannesses:
big-endian PowerPC objects (our MWCC output and dtk's retail objects) and the
little-endian MIPS PS2 executable. No dependencies beyond the standard library.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass, field

SHT_SYMTAB = 2
SHT_RELA = 4
SHT_NOBITS = 8
SHT_REL = 9

STT = {0: "notype", 1: "object", 2: "func", 3: "section", 4: "file"}
STB = {0: "local", 1: "global", 2: "weak"}

PPC_RELOC = {
    0: "R_PPC_NONE", 1: "R_PPC_ADDR32", 2: "R_PPC_ADDR24", 3: "R_PPC_ADDR16",
    4: "R_PPC_ADDR16_LO", 5: "R_PPC_ADDR16_HI", 6: "R_PPC_ADDR16_HA",
    7: "R_PPC_ADDR14", 10: "R_PPC_REL24", 11: "R_PPC_REL14",
    109: "R_PPC_EMB_SDA21", 116: "R_PPC_EMB_SDA21",
}


@dataclass
class Section:
    index: int
    name: str
    type: int
    flags: int
    addr: int
    offset: int
    size: int
    link: int
    info: int
    entsize: int
    data: bytes = b""


@dataclass
class Symbol:
    index: int
    name: str
    value: int
    size: int
    type: str
    bind: str
    shndx: int


@dataclass
class Reloc:
    offset: int
    type: int
    sym: int
    addend: int


@dataclass
class Elf:
    path: str
    endian: str
    sections: list[Section] = field(default_factory=list)
    symbols: list[Symbol] = field(default_factory=list)

    def section(self, name: str) -> Section | None:
        return next((s for s in self.sections if s.name == name), None)

    def sym(self, name: str) -> Symbol | None:
        best = None
        for s in self.symbols:
            if s.name == name and s.shndx != 0:
                if best is None or (best.type != "func" and s.type == "func"):
                    best = s
        return best

    def relocs_for(self, shndx: int) -> list[Reloc]:
        out: list[Reloc] = []
        for s in self.sections:
            if s.type not in (SHT_RELA, SHT_REL) or s.info != shndx:
                continue
            e = self.endian
            if s.type == SHT_RELA:
                for off in range(0, s.size, 12):
                    r_off, info, add = struct.unpack_from(e + "IIi", s.data, off)
                    out.append(Reloc(r_off, info & 0xFF, info >> 8, add))
            else:
                for off in range(0, s.size, 8):
                    r_off, info = struct.unpack_from(e + "II", s.data, off)
                    out.append(Reloc(r_off, info & 0xFF, info >> 8, 0))
        out.sort(key=lambda r: r.offset)
        return out


def _cstr(blob: bytes, off: int) -> str:
    end = blob.index(b"\0", off)
    return blob[off:end].decode("latin-1")


def load(path: str) -> Elf:
    with open(path, "rb") as f:
        raw = f.read()
    if raw[:4] != b"\x7fELF" or raw[4] != 1:
        raise ValueError(f"{path}: not an ELF32 file")
    e = "<" if raw[5] == 1 else ">"
    shoff, = struct.unpack_from(e + "I", raw, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from(e + "HHH", raw, 0x2E)
    elf = Elf(path, e)
    hdrs = []
    for i in range(shnum):
        hdrs.append(struct.unpack_from(e + "10I", raw, shoff + i * shentsize))
    shstr = hdrs[shstrndx]
    shstr_blob = raw[shstr[4] : shstr[4] + shstr[5]]
    for i, h in enumerate(hdrs):
        name_off, typ, flags, addr, off, size, link, info, _align, entsize = h
        data = b"" if typ == SHT_NOBITS else raw[off : off + size]
        elf.sections.append(
            Section(i, _cstr(shstr_blob, name_off), typ, flags, addr, off, size, link, info, entsize, data)
        )
    for s in elf.sections:
        if s.type != SHT_SYMTAB:
            continue
        strtab = elf.sections[s.link].data
        for i in range(s.size // 16):
            name, value, size, info, _other, shndx = struct.unpack_from(e + "IIIBBH", s.data, i * 16)
            elf.symbols.append(
                Symbol(i, _cstr(strtab, name), value, size, STT.get(info & 0xF, str(info & 0xF)),
                       STB.get(info >> 4, str(info >> 4)), shndx)
            )
    return elf
