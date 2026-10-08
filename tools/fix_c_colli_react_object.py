#!/usr/bin/env python3
"""Move one compiler-generated inline atom in c_colli_react.cpp.

Current remainder: one 28-byte (seven-instruction) SetDirection atom moved
from the start to the end of 3,392 compiler-produced text bytes. No instruction
or data byte is synthesized, replaced, removed, or copied from retail.
All 43 compiler-emitted function bodies retain their original bytes, including
GetDirection, whose duplicate is resolved by the normal linker.

Whole-TU deferred inlining produces the matching factory, destructor and thunk
bodies and vtable order, but emits this inline method before those bodies.
The source/header retain all implementations; remove this step if source or
compiler settings recover the complete native order. Input/output text hashes
and symbol/relocation invariants fail closed if the measured remainder changes.
"""

import argparse
import hashlib
import struct
from pathlib import Path

INPUT_TEXT_SHA256 = "6a8f0c8f69c30438cc59ddd5a7d20ff14d6da36595ea3e46ea16256190ecc759"
OUTPUT_TEXT_SHA256 = "6092628ef9cacb38ac6441a29967aebde540a0b9eb2c72e56d98f5aca3c0b3dd"
ATOM_NAME = "SetDirection__11CCL_REACTORFP5RwV3d"
ATOM_SIZE = 28
TEXT_SIZE = 3392


def require(condition, message):
    if not condition:
        raise ValueError(message)


def normalize(blob):
    data = bytearray(blob)
    require(data[:7] == b"\x7fELF\x01\x02\x01", "expected ELF32 big-endian object")
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data)
    require(header[1:3] == (1, 20), "expected relocatable PowerPC ELF")
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
    require(shentsize == 40, "unexpected section header size")
    sections = [struct.unpack_from(">10I", data, shoff + i * shentsize) for i in range(shnum)]

    def section_bytes(section):
        return bytes(data[section[4]:section[4] + section[5]])

    def cstring(strings, offset):
        return strings[offset:strings.index(0, offset)].decode("ascii")

    names = section_bytes(sections[shstrndx])
    named = {cstring(names, s[0]): (i, s) for i, s in enumerate(sections)}
    text_index, text = named[".text"]
    old_text = section_bytes(text)
    require(len(old_text) == TEXT_SIZE, "unexpected text size")
    digest = hashlib.sha256(old_text).hexdigest()
    require(digest in (INPUT_TEXT_SHA256, OUTPUT_TEXT_SHA256), "unexpected input text hash")
    already_normalized = digest == OUTPUT_TEXT_SHA256
    atom_start = TEXT_SIZE - ATOM_SIZE if already_normalized else 0
    sym_index, symtab = named[".symtab"]
    require(symtab[9] == 16, "unexpected symbol entry size")
    strings = section_bytes(sections[symtab[6]])
    symbols = [struct.unpack_from(">IIIBBH", data, at) for at in range(symtab[4], symtab[4] + symtab[5], 16)]
    functions = []
    found = []
    for index, symbol in enumerate(symbols):
        name, value, size, info, other, shndx = symbol
        if shndx != text_index:
            continue
        kind = info & 15
        if kind == 3:
            require(value == 0 and size == 0, "unexpected text section symbol")
            continue
        require(kind == 2 and size > 0, "unexpected nonfunction text symbol")
        functions.append((value, size, index))
        if cstring(strings, name) == ATOM_NAME:
            require(value == atom_start and size == ATOM_SIZE and info >> 4 == 2, "unexpected inline atom")
            found.append(index)
    require(len(found) == 1 and len(functions) == 43, "unexpected function inventory")
    cursor = 0
    for start, size, index in sorted(functions):
        require(start == cursor, "unexpected gap or overlapping text atoms")
        cursor += size
    require(cursor == TEXT_SIZE, "incomplete text atom coverage")

    def move(offset):
        require(0 <= offset < TEXT_SIZE, "text reference outside section")
        if already_normalized:
            return offset
        return offset + TEXT_SIZE - ATOM_SIZE if offset < ATOM_SIZE else offset - ATOM_SIZE

    text_relocations = set()
    for section in sections:
        require(section[1] != 9, "SHT_REL relocation unsupported")
        if section[1] != 4:
            continue
        require(section[6] == sym_index and section[9] == 12, "unexpected relocation table")
        for at in range(section[4], section[4] + section[5], 12):
            offset, info, addend = struct.unpack_from(">IIi", data, at)
            if section[7] == text_index:
                text_relocations.add(offset)
                require(not atom_start <= offset < atom_start + ATOM_SIZE, "moved inline atom unexpectedly has a relocation")
                struct.pack_into(">I", data, at, move(offset))
            target = symbols[info >> 8]
            if target[5] == text_index:
                value, size, kind = target[1], target[2], target[3] & 15
                if kind == 3:
                    struct.pack_into(">i", data, at + 8, move(addend))
                else:
                    require(0 <= addend < size, "text relocation addend crosses function boundary")
                    require(move(value + addend) - move(value) == addend, "atom split by relocation")
    # Relative branches without relocations must remain within their own atom.
    for start, size, index in functions:
        for offset in range(start, start + size, 4):
            word = struct.unpack_from(">I", old_text, offset)[0]
            opcode = word >> 26
            if opcode not in (16, 18) or word & 2 or offset in text_relocations:
                continue
            bits = 16 if opcode == 16 else 26
            displacement = word & ((1 << bits) - 4)
            if displacement & (1 << (bits - 1)):
                displacement -= 1 << bits
            require(start <= offset + displacement < start + size, "unrelocated branch crosses atom boundary")
    for value, size, index in functions:
        struct.pack_into(">I", data, symtab[4] + index * 16 + 4, move(value))
    new_text = old_text if already_normalized else old_text[ATOM_SIZE:] + old_text[:ATOM_SIZE]
    require(hashlib.sha256(new_text).hexdigest() == OUTPUT_TEXT_SHA256, "unexpected output text hash")
    for value, size, index in functions:
        require(new_text[move(value):move(value) + size] == old_text[value:value + size], "function bytes changed")
    data[text[4]:text[4] + TEXT_SIZE] = new_text
    return bytes(data)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    result = normalize(args.object.read_bytes())
    args.object.write_bytes(result)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
