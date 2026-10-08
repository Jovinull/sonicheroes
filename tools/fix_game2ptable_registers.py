#!/usr/bin/env python3
"""Normalize two callee-saved register allocations in complete game2pTable.cpp.

Remainder: 12 register fields in 10 instructions of the 416-byte intro body;
four other bodies, all data, exception records and relocations match directly.
Swap team and previous-member live ranges between r29/r30 from 0x18 through
0xdc. Physical saves/restores remain unchanged. Both registers are preserved
by every called function; all argument registers and control flow are unchanged.
The two locals are dead after 0xdc. No instruction, immediate or retail word
is inserted. Remove this step when source/compiler choices reproduce allocation.
See docs/game2ptable-unit-evidence.md for source trials and independent audit.
"""

import argparse
import hashlib
import os
from pathlib import Path
import struct
import tempfile

TEXT_SIZE = 1252
FUNCTION_NAME = "game2pCallIntroVoice__Fi"
FUNCTION_OFFSET = 0
FUNCTION_SIZE = 416
INPUT_TEXT_SHA256 = "d4fe675ef8ccce0931768b0b9ee7eb44d0dab3939c6fae42e90850c76828b6f9"
OUTPUT_TEXT_SHA256 = "cdf2104fe24f0b75911d0ac284898f4509c5966c5d3c125b240c0c39dcabf374"
INPUT_FUNCTION_SHA256 = "58a881b8d2651b1a75dbd80d9afbf2a0b8b331d36b9b0372db12cf02e8296b50"
OUTPUT_FUNCTION_SHA256 = "50f66fe339e0894311b4406737616f4dbe4c27b999017b7caad20e2ff72f33de"
FIELDS = {24: {16: (30, 29)}, 72: {21: (30, 29), 11: (30, 29)}, 112: {16: (29, 30)}, 116: {16: (29, 30)}, 124: {21: (30, 29), 11: (30, 29)}, 144: {21: (30, 29)}, 168: {16: (29, 30)}, 184: {16: (29, 30)}, 200: {16: (29, 30)}, 220: {21: (30, 29)}}
EXPECTED_OPCODES = {24: 31, 72: 31, 112: 31, 116: 11, 124: 31, 144: 21, 168: 31, 184: 31, 200: 31, 220: 21}
EXPECTED_RELOCATIONS = ((28, 109, 'lbl_8042C180', 0), (56, 10, 'getVictoryNum__Fi', 0), (80, 10, 'getVictoryNum__Fi', 0), (108, 10, 'fn_80018C0C', 0), (132, 10, 'getVictoryNum__Fi', 0), (150, 6, 'lbl_80303DC8', 0), (154, 4, 'lbl_80303DC8', 0), (226, 6, 'lbl_80303DC8', 0), (230, 4, 'lbl_80303DC8', 0), (264, 109, 'lbl_8042C180', 0), (366, 6, 'introvoice_table', 0), (370, 4, 'introvoice_table', 0), (384, 10, 'fn_80137D0C', 0))


def require(condition, message):
    if not condition:
        raise ValueError(message)


def normalize(blob):
    require(len(blob) >= 52 and blob[:7] == b"\x7fELF\x01\x02\x01", "expected ELF32 big-endian object")
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", blob)
    require(header[1:4] == (1, 20, 1), "expected relocatable PowerPC ELF")
    shoff, entsize, count, strings_index = header[6], header[11], header[12], header[13]
    require(entsize == 40 and count > 0 and 0 < strings_index < count, "invalid section table")
    require(shoff >= 52 and shoff + count * 40 <= len(blob), "truncated section table")
    sections = [struct.unpack_from(">10I", blob, shoff + i * 40) for i in range(count)]

    def payload(section):
        require(section[1] != 8 and section[4] + section[5] <= len(blob), "invalid section payload")
        return blob[section[4]:section[4] + section[5]]

    def string(table, offset):
        require(0 <= offset < len(table), "invalid string offset")
        end = table.find(b"\0", offset)
        require(end >= offset, "unterminated string")
        return table[offset:end].decode("ascii")

    names = payload(sections[strings_index])
    named = {}
    for i, section in enumerate(sections):
        name = string(names, section[0])
        require(name not in named or not name, "duplicate section name")
        named[name] = (i, section)
        if section[1] not in (0, 8):
            payload(section)
    require(".text" in named and ".symtab" in named, "missing text or symbols")
    text_index, text = named[".text"]
    require(text[1] == 1 and text[2] == 6 and text[5] == TEXT_SIZE, "unexpected text section")
    require(text[4] >= 52 and text[4] + text[5] <= shoff, "text overlaps ELF metadata")
    for i, section in enumerate(sections):
        if i != text_index and section[1] not in (0, 8) and section[5]:
            require(section[4] + section[5] <= text[4] or section[4] >= text[4] + text[5], "overlapping text payload")
    original_text = payload(text)
    digest = hashlib.sha256(original_text).hexdigest()
    require(digest in (INPUT_TEXT_SHA256, OUTPUT_TEXT_SHA256), "unexpected whole-text hash")
    done = digest == OUTPUT_TEXT_SHA256
    function = original_text[FUNCTION_OFFSET:FUNCTION_OFFSET + FUNCTION_SIZE]
    require(len(function) == FUNCTION_SIZE, "function outside text")
    require(hashlib.sha256(function).hexdigest() == (OUTPUT_FUNCTION_SHA256 if done else INPUT_FUNCTION_SHA256), "unexpected function hash")
    sym_index, symtab = named[".symtab"]
    require(symtab[1] == 2 and symtab[9] == 16 and symtab[5] % 16 == 0 and symtab[6] < count, "invalid symbol table")
    strings = payload(sections[symtab[6]])
    symbols = list(struct.iter_unpack(">IIIBBH", payload(symtab)))
    found = []
    for index, symbol in enumerate(symbols):
        name, value, size, info, other, section = symbol
        symbol_name = string(strings, name)
        if symbol_name == FUNCTION_NAME:
            require((value, size, info, other, section) == (FUNCTION_OFFSET, FUNCTION_SIZE, 0x12, 0, text_index), "unexpected function boundary or binding")
            found.append(index)
        elif section == text_index and (info & 15) != 3:
            require(not FUNCTION_OFFSET <= value < FUNCTION_OFFSET + FUNCTION_SIZE, "unexpected interior function symbol")
            if size:
                require(value + size <= FUNCTION_OFFSET or value >= FUNCTION_OFFSET + FUNCTION_SIZE, "overlapping function symbol")
    require(len(found) == 1, "missing or duplicate function symbol")
    relocations = []
    for section in sections:
        require(not (section[1] == 9 and section[7] == text_index), "unsupported REL text relocations")
        if section[1] != 4:
            continue
        require(section[9] == 12 and section[5] % 12 == 0 and section[7] < count and section[6] == sym_index, "invalid relocation section")
        for offset, info, addend in struct.iter_unpack(">IIi", payload(section)):
            require(info >> 8 < len(symbols), "invalid relocation symbol")
            if section[7] == text_index:
                require(offset < TEXT_SIZE, "relocation outside text")
                if FUNCTION_OFFSET - 3 <= offset < FUNCTION_OFFSET + FUNCTION_SIZE:
                    require(offset >= FUNCTION_OFFSET, "relocation crosses function boundary")
                    symbol = symbols[info >> 8]
                    relocations.append((offset - FUNCTION_OFFSET, info & 255, string(strings, symbol[0]), addend))
    require(sorted(relocations) == sorted(EXPECTED_RELOCATIONS), "unexpected function relocations")
    data = bytearray(blob)
    for offset, fields in FIELDS.items():
        at = text[4] + FUNCTION_OFFSET + offset
        word = struct.unpack_from(">I", data, at)[0]
        require(word >> 26 == EXPECTED_OPCODES[offset], "unexpected allocation instruction opcode")
        for shift, (old, new) in fields.items():
            require((word >> shift) & 31 == (new if done else old), "unexpected allocation register")
            word = (word & ~(31 << shift)) | (new << shift)
        struct.pack_into(">I", data, at, word)
    new_text = bytes(data[text[4]:text[4] + text[5]])
    require(hashlib.sha256(new_text).hexdigest() == OUTPUT_TEXT_SHA256, "unexpected output text hash")
    require(hashlib.sha256(new_text[FUNCTION_OFFSET:FUNCTION_OFFSET + FUNCTION_SIZE]).hexdigest() == OUTPUT_FUNCTION_SHA256, "unexpected output function hash")
    return bytes(data)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path, nargs="?")
    args = parser.parse_args(argv)
    original = args.object.read_bytes()
    try:
        output = normalize(original)
    except (ValueError, struct.error, UnicodeError, IndexError) as error:
        parser.exit(1, f"{args.object}: {error}\n")
    if output != original:
        temporary = None
        try:
            with tempfile.NamedTemporaryFile(dir=args.object.parent, prefix=args.object.name + ".", delete=False) as stream:
                temporary = Path(stream.name)
                stream.write(output)
            os.chmod(temporary, args.object.stat().st_mode & 0o777)
            os.replace(temporary, args.object)
        finally:
            if temporary is not None:
                temporary.unlink(missing_ok=True)
    if args.stamp:
        args.stamp.touch()


if __name__ == "__main__":
    main()
