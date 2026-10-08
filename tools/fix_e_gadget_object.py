#!/usr/bin/env python3
"""Reorder existing compiler atoms in the complete e_gadget.cpp object.

Remainder: move the leading 148-byte inline group (destructor and eight stubs)
after the 500-byte ordinary-function group, and move its 12-byte exception
index row after five rows. All 14 bodies and all EH/vtable bytes are preserved;
only their order, symbol values, relocation offsets and section addends change.
No retail instruction bytes are embedded or written. Remove this normalization
when a source/compiler form recovers the complete native emission order.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import stat
import struct
import tempfile

TEXT_SIZE = 648
TEXT_PREFIX = 148
INDEX_SIZE = 72
INDEX_PREFIX = 12
SECTION_HASHES = {'.text': ('62d018fc1b73c6caad43dd36fb49b0c353cc7eed2ce0a5f09b3675eaf88b9b3e',
           '46c0f4b01cb85db4e9950ff6ccc1d3fc4d9d3ca45379430096bbeff45abda04b'),
 'extab': ('fdf13ab834dc59d115dfd653c5dc0e98fb59379e2e28d5dfb4a673fef0ab3801',
           'fdf13ab834dc59d115dfd653c5dc0e98fb59379e2e28d5dfb4a673fef0ab3801'),
 'extabindex': ('1f15bfaaf045dfbf7335d3030fc9ab5d2f70c1236be73c8a1f971bf1d507ea3a',
                'e8aec203475d5145e691437c024fe0c834c4847f70a1c4f60b08d8df0f2818a9'),
 '.data': ('5b6fb58e61fa475939767d68a446f97f1bff02c0e5935a3ea8bb51e6515783d8',
           '5b6fb58e61fa475939767d68a446f97f1bff02c0e5935a3ea8bb51e6515783d8')}
SYMBOL_INVENTORY = (('defined', '.data', 0, 80, 17),
 ('defined', '.text', 0, 108, 34),
 ('defined', '.text', 108, 8, 34),
 ('defined', '.text', 116, 4, 34),
 ('defined', '.text', 120, 4, 34),
 ('defined', '.text', 124, 4, 34),
 ('defined', '.text', 128, 4, 34),
 ('defined', '.text', 132, 4, 34),
 ('defined', '.text', 136, 4, 34),
 ('defined', '.text', 140, 8, 34),
 ('defined', '.text', 148, 104, 18),
 ('defined', '.text', 252, 96, 18),
 ('defined', '.text', 348, 96, 18),
 ('defined', '.text', 444, 104, 18),
 ('defined', '.text', 548, 100, 18),
 ('defined', 'extab', 0, 8, 1),
 ('defined', 'extab', 16, 8, 1),
 ('defined', 'extab', 24, 8, 1),
 ('defined', 'extab', 32, 8, 1),
 ('defined', 'extab', 40, 8, 1),
 ('defined', 'extab', 8, 8, 1),
 ('defined', 'extabindex', 0, 12, 1),
 ('defined', 'extabindex', 12, 12, 1),
 ('defined', 'extabindex', 24, 12, 1),
 ('defined', 'extabindex', 36, 12, 1),
 ('defined', 'extabindex', 48, 12, 1),
 ('defined', 'extabindex', 60, 12, 1),
 ('file',),
 ('section', '.data', 3),
 ('section', '.text', 3),
 ('section', 'extab', 3),
 ('section', 'extabindex', 3),
 ('undefined', '', 0, 0, 0),
 ('undefined', 'Debug__7TObjectFv', 0, 0, 16),
 ('undefined', 'Error__7TObjectFPc', 0, 0, 16),
 ('undefined', 'Free__9THeapCtrlFPv', 0, 0, 16),
 ('undefined', 'ImmAftSetRaster__7TObjectFv', 0, 0, 16),
 ('undefined', 'PDisp__7TObjectFv', 0, 0, 16),
 ('undefined', 'Render__7TObjectFv', 0, 0, 16),
 ('undefined', '__ct__7TObjectFP7TObject', 0, 0, 16),
 ('undefined', '__dt__7TObjectFv', 0, 0, 16),
 ('undefined', 'fn_80017800', 0, 0, 16),
 ('undefined', 'fn_8019CE34', 0, 0, 16),
 ('undefined', 'lbl_8042C114', 0, 0, 16),
 ('undefined', 'lbl_8042C148', 0, 0, 16),
 ('undefined', 'lbl_8042C9A4', 0, 0, 16))
RELOCATION_HASH = 'dd4a263c55d19e4998e252c302fb3e92dab3ef86eafd10d9a45c15943b410bba'
DEFINED_NAMES = {('.data', 0, 80, 17): '__vt__12TEnemyGadget',
 ('.text', 140, 8, 34): 'CanDisp__12TEnemyGadgetFv',
 ('.text', 136, 4, 34): 'UnknownSlot48__12TEnemyGadgetFv',
 ('.text', 132, 4, 34): 'UnknownSlot44__12TEnemyGadgetFv',
 ('.text', 128, 4, 34): 'DelClump__12TEnemyGadgetFv',
 ('.text', 124, 4, 34): 'DispTrans__12TEnemyGadgetFv',
 ('.text', 120, 4, 34): 'DispOpaq__12TEnemyGadgetFv',
 ('.text', 116, 4, 34): 'Update__12TEnemyGadgetFv',
 ('.text', 108, 8, 34): 'SetClump__12TEnemyGadgetFP7RpClump',
 ('.text', 252, 96, 18): 'TDisp__12TEnemyGadgetFv',
 ('.text', 348, 96, 18): 'Disp__12TEnemyGadgetFv',
 ('.text', 444, 104, 18): 'Exec__12TEnemyGadgetFv',
 ('.text', 0, 108, 34): '__dt__12TEnemyGadgetFv',
 ('.text', 148, 104, 18): 'CheckCameraFrustum__12TEnemyGadgetFPC5RwV3df',
 ('.text', 548, 100, 18): '__ct__12TEnemyGadgetFP9TObjEnemy'}
ALLOCATED_LAYOUT = {".text": (1, 6, 648, 4), "extab": (1, 2, 48, 4),
                    "extabindex": (1, 2, 72, 4), ".data": (1, 3, 80, 8)}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def signature(value):
    return digest(json.dumps(value, separators=(",", ":")).encode())


def move(value, size, prefix):
    require(0 <= value < size, "reference outside moved section")
    return value + size - prefix if value < prefix else value - prefix


def unmove(value, size, prefix):
    return move(value, size, size - prefix)


class Elf:
    def __init__(self, blob):
        self.data = bytearray(blob)
        require(len(blob) >= 52, "truncated ELF header")
        h = struct.unpack_from(">16sHHIIIIIHHHHHH", blob)
        require(h[0][:7] == b"\x7fELF\x01\x02\x01", "expected ELF32 big-endian")
        require(h[1:6] == (1, 20, 1, 0, 0), "expected relocatable PowerPC object")
        require(h[7:12] == (0x80000000, 52, 0, 0, 40), "unexpected ELF header layout")
        offset, count, names = h[6], h[12], h[13]
        require(count == 12 and names < count, "unexpected section inventory")
        require(offset >= 52 and offset + count * 40 <= len(blob), "truncated section headers")
        self.sections = [struct.unpack_from(">10I", blob, offset + i * 40) for i in range(count)]
        require(self.sections[0] == (0,) * 10, "invalid null section")
        occupied = [(0, 52), (offset, offset + count * 40)]
        for s in self.sections[1:]:
            require(s[1] in (1, 2, 3, 4) and s[3] == 0, "unexpected section kind/address")
            require(s[8] > 0 and s[8] & (s[8] - 1) == 0, "invalid section alignment")
            require(s[4] % s[8] == 0, "misaligned section payload")
            require(s[4] >= 52 and s[4] + s[5] <= len(blob), "section outside file")
            occupied.append((s[4], s[4] + s[5]))
        occupied.sort()
        require(all(a[1] <= b[0] for a, b in zip(occupied, occupied[1:])), "overlapping ELF regions")
        strings = self.payload(names)
        self.named = {}
        for i, s in enumerate(self.sections):
            name = self.cstring(strings, s[0])
            require(name not in self.named, "duplicate section name")
            self.named[name] = i
        require(set(self.named) == {"", ".text", "extab", "extabindex", ".data",
                                  ".rela.text", ".relaextabindex", ".rela.data",
                                  ".symtab", ".strtab", ".shstrtab", ".comment"},
                "unexpected section names")
        require(names == self.named[".shstrtab"], "wrong section name table")
        require({n: (s[1], s[2], s[5], s[8]) for n, i in self.named.items()
                 if (s := self.sections[i])[2] & 2} == ALLOCATED_LAYOUT, "allocated section layout changed")
        for n in ALLOCATED_LAYOUT:
            s = self.sections[self.named[n]]
            require(s[6] == s[7] == s[9] == 0, "unexpected allocated section metadata")
        for n in (".strtab", ".shstrtab"):
            s = self.sections[self.named[n]]
            require(s[1:4] == (3, 0, 0) and s[6:10] == (0, 0, 1, 1), "invalid string table")
        comment = self.sections[self.named[".comment"]]
        require(comment[1:4] == (1, 0, 0) and comment[6:10] == (0, 0, 1, 1), "invalid comment section")
        sym = self.sections[self.named[".symtab"]]
        require(sym[1:4] == (2, 0, 0) and sym[6] == self.named[".strtab"]
                and sym[8:10] == (4, 16) and sym[5] % 16 == 0, "invalid symbol table")
        strings = self.payload(sym[6])
        self.symbols = [struct.unpack_from(">IIIBBH", blob, p)
                        for p in range(sym[4], sym[4] + sym[5], 16)]
        self.symbol_names = [self.cstring(strings, s[0]) for s in self.symbols]
        require(self.symbols[0] == (0,) * 6, "invalid null symbol")
        require(0 < sym[7] <= len(self.symbols), "invalid local symbol boundary")
        for i, s in enumerate(self.symbols[1:], 1):
            expected_other = 2 if s[3] == 1 and s[5] in (self.named["extab"], self.named["extabindex"]) else 0
            require(s[4] == expected_other and s[3] >> 4 in (0, 1, 2), "unexpected symbol visibility/binding")
            require((s[3] >> 4 == 0) == (i < sym[7]), "incorrect local symbol boundary")
            require(s[5] in (0, 0xfff1) or s[5] < count, "invalid symbol section")
        self.relocations = []
        for name, target, size in ((".rela.text", ".text", 144),
                                   (".relaextabindex", "extabindex", 144),
                                   (".rela.data", ".data", 204)):
            sec = self.sections[self.named[name]]
            require((sec[1], sec[2], sec[5], sec[6], sec[7], sec[8], sec[9])
                    == (4, 0, size, self.named[".symtab"], self.named[target], 4, 12),
                    "relocation section layout changed")
            sites = set()
            for pos in range(sec[4], sec[4] + sec[5], 12):
                off, info, addend = struct.unpack_from(">IIi", blob, pos)
                width = 2 if info & 255 in (4, 6) else 4
                require(info >> 8 < len(self.symbols) and info & 255 in (1, 4, 6, 10, 109),
                        "unexpected relocation kind/symbol")
                require(off % width == 0 and off + width <= self.sections[sec[7]][5],
                        "relocation outside target section")
                require(not any(p in sites for p in range(off, off + width)), "overlapping relocations")
                sites.update(range(off, off + width))
                self.relocations.append((pos, target, off, info, addend))

    @staticmethod
    def cstring(strings, offset):
        require(0 <= offset < len(strings), "string offset outside table")
        end = strings.find(b"\0", offset)
        require(end >= 0, "unterminated ELF string")
        try:
            return strings[offset:end].decode("ascii")
        except UnicodeDecodeError as error:
            raise ValueError("non-ASCII ELF name") from error

    def payload(self, index):
        s = self.sections[index]
        return bytes(self.data[s[4]:s[4] + s[5]])

    def descriptors(self, normalized):
        def original(section, value):
            if normalized and section in (".text", "extabindex"):
                return unmove(value, *({".text": (TEXT_SIZE, TEXT_PREFIX),
                                       "extabindex": (INDEX_SIZE, INDEX_PREFIX)}[section]))
            return value
        descriptors = []
        for index, s in enumerate(self.symbols):
            name, value, size, info, other, section = s
            if section == 0:
                desc = ("undefined", self.symbol_names[index], value, size, info)
            elif section == 0xfff1:
                require(info == 4 and value == size == 0, "unexpected absolute symbol")
                desc = ("file",)
            else:
                section = next(n for n, i in self.named.items() if i == section)
                if info & 15 == 3:
                    require(value == size == 0, "invalid section symbol")
                    desc = ("section", section, info)
                else:
                    require(section in ALLOCATED_LAYOUT and size > 0,
                            "unexpected defined symbol")
                    require(value + size <= self.sections[self.named[section]][5], "symbol outside section")
                    desc = ("defined", section, original(section, value), size, info)
            descriptors.append(desc)
        for i, desc in enumerate(descriptors):
            if desc[0] == "defined" and desc[1] in (".text", ".data"):
                require(self.symbol_names[i] == DEFINED_NAMES.get(desc[1:]), "defined symbol name changed")
        inventory = sorted(descriptors, key=repr)
        rels = []
        for pos, target, off, info, addend in self.relocations:
            sym = self.symbols[info >> 8]
            desc = descriptors[info >> 8]
            if desc[0] == "defined":
                require(0 <= addend < sym[2], "relocation crosses owned atom")
            elif desc[0] == "section":
                addend = original(desc[1], addend)
            else:
                require(desc[0] == "undefined" and addend == 0, "unexpected external relocation addend")
            rels.append((target, original(target, off), info & 255, desc, addend))
        return inventory, sorted(rels, key=repr)


def normalize(blob):
    elf = Elf(blob)
    normalized = digest(elf.payload(elf.named[".text"])) == SECTION_HASHES[".text"][1]
    for name, hashes in SECTION_HASHES.items():
        require(digest(elf.payload(elf.named[name])) == hashes[int(normalized)],
                "unexpected " + name + " hash")
    inventory, relocations = elf.descriptors(normalized)
    require(tuple(inventory) == SYMBOL_INVENTORY, "symbol inventory changed")
    require(signature(relocations) == RELOCATION_HASH, "relocation inventory changed")
    functions = sorted((s[1], s[2]) for s in elf.symbols
                       if s[5] == elf.named[".text"] and s[3] & 15 == 2)
    cursor = 0
    for start, size in functions:
        require(start == cursor and size % 4 == 0, "incomplete function coverage")
        cursor += size
    require(cursor == TEXT_SIZE and len(functions) == 14, "unexpected function coverage")
    text = elf.payload(elf.named[".text"])
    relocated = {off for _, target, off, _, _ in elf.relocations if target == ".text"}
    for start, size in functions:
        for off in range(start, start + size, 4):
            word = struct.unpack_from(">I", text, off)[0]
            opcode = word >> 26
            if opcode not in (16, 18) or off in relocated:
                continue
            require(word & 2 == 0, "absolute unrelocated branch")
            bits = 16 if opcode == 16 else 26
            disp = word & ((1 << bits) - 4)
            if disp & (1 << (bits - 1)):
                disp -= 1 << bits
            require(start <= off + disp < start + size, "unrelocated branch crosses function")
    if normalized:
        return bytes(elf.data)
    sizes = {elf.named[".text"]: (TEXT_SIZE, TEXT_PREFIX),
             elf.named["extabindex"]: (INDEX_SIZE, INDEX_PREFIX)}
    for _, (size, prefix) in sizes.items():
        require(size > prefix > 0, "invalid atom permutation")
    for pos, target, off, info, addend in elf.relocations:
        target_index = elf.named[target]
        if target_index in sizes:
            struct.pack_into(">I", elf.data, pos, move(off, *sizes[target_index]))
        sym = elf.symbols[info >> 8]
        if sym[5] in sizes:
            size, prefix = sizes[sym[5]]
            if sym[3] & 15 == 3:
                struct.pack_into(">i", elf.data, pos + 8, move(addend, size, prefix))
            else:
                require(move(sym[1] + addend, size, prefix) - move(sym[1], size, prefix) == addend,
                        "relocation splits atom")
    symtab = elf.sections[elf.named[".symtab"]]
    for i, sym in enumerate(elf.symbols):
        if sym[5] in sizes and sym[3] & 15 != 3:
            size, prefix = sizes[sym[5]]
            require(move(sym[1] + sym[2] - 1, size, prefix) - move(sym[1], size, prefix) == sym[2] - 1,
                    "symbol crosses permutation boundary")
            struct.pack_into(">I", elf.data, symtab[4] + i * 16 + 4, move(sym[1], size, prefix))
    for index, (size, prefix) in sizes.items():
        old = elf.payload(index)
        s = elf.sections[index]
        elf.data[s[4]:s[4] + size] = old[prefix:] + old[:prefix]
    new_text = elf.payload(elf.named[".text"])
    for start, size in functions:
        new_start = move(start, TEXT_SIZE, TEXT_PREFIX)
        require(text[start:start + size] == new_text[new_start:new_start + size], "function bytes changed")
    result = bytes(elf.data)
    # Reparse and validate the complete output contract before any filesystem write.
    require(normalize(result) == result, "output validation failed")
    return result


def atomic_write(path, data):
    mode = stat.S_IMODE(path.stat().st_mode) if path.exists() else 0o644
    fd, temp = tempfile.mkstemp(prefix=path.name + ".", dir=path.parent)
    try:
        with os.fdopen(fd, "wb") as stream:
            stream.write(data)
            stream.flush()
            os.fsync(stream.fileno())
        os.chmod(temp, mode)
        os.replace(temp, path)
    finally:
        if os.path.exists(temp):
            os.unlink(temp)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path, nargs="?")
    args = parser.parse_args(argv)
    if args.stamp:
        require(args.stamp.resolve() != args.object.resolve(), "stamp must differ from object")
    original = args.object.read_bytes()
    result = normalize(original)
    if result != original:
        atomic_write(args.object, result)
    if args.stamp:
        args.stamp.parent.mkdir(parents=True, exist_ok=True)
        atomic_write(args.stamp, b"e_gadget whole-atom order verified\n")


if __name__ == "__main__":
    main()
