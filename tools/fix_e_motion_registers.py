#!/usr/bin/env python3
"""Normalize one captured-request register allocation in complete e_motion.cpp.

Remainder: three register fields in three of UpdateMotion's 1,301 instructions;
six other surviving bodies, all data, exceptions and relocations match directly.
Move the requested-motion local from r28 to r27 at offsets 0x36c/0x374/0x3b0.
The two registers' earlier live ranges are dead before this SET path, and the
captured request dies at the unsigned-short conversion. Both registers are
callee-saved across the intervening interpolator-copy call; physical saves and
restores remain unchanged. All argument registers, opcodes, immediates, branches,
data and relocations are untouched. No instruction word or retail input is used.

Ordinary definitions of seven authentic helpers preserve compiler pool order;
the normal linker, not this tool, discards their unused copies. Whole-object,
whole-text, function and relocation hashes fail closed if the remainder changes.
Remove this step when source/compiler choices recover these three fields.
See docs/e-motion-unit-evidence.md for source trials and independent liveness.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import struct
import tempfile

TEXT_SIZE = 7796
FUNCTION_NAME = 'UpdateMotion__11ENEMYMTNMANFv'
FUNCTION_OFFSET = 2592
FUNCTION_SIZE = 5204
INPUT_TEXT_SHA256 = '69cddb947c16d4d00360c18ea33b570d112adba3cd5960148f85755dc6564847'
OUTPUT_TEXT_SHA256 = '79a565589cda4f47336a1843b5d0310eaf4090285119b909c9ef3608bbbc6db0'
INPUT_FUNCTION_SHA256 = '3a66ed367f39d259698b5de70a69e11b75164b445c06c8896703a95e5808b3f6'
OUTPUT_FUNCTION_SHA256 = 'c46a7d07b5a7f5b8dfbe513475b13dfd47c32492ab7d3b87a0cfb0ab728af698'
INPUT_OBJECT_SHA256 = '37d2cb56bb407431eaa7efb6d4bf366abb8063fbe7bf6ef37d68d636ec60f573'
OUTPUT_OBJECT_SHA256 = 'b10ffd145c930c1c7491d59f19c5553386ba7743fdea14c3dce7b40350ed8f51'
FIELDS = {876: {21: (28, 27)}, 884: {16: (28, 27)}, 944: {21: (28, 27)}}
EXPECTED_OPCODES = {876: 32, 884: 31, 944: 21}
EXPECTED_RELOCATIONS_SHA256 = 'c326dff498a0a4f32e6b08ef50c6881aac729649f3099ec4fef4ac5f0d1eecdb'


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
    require(hashlib.sha256(blob).hexdigest() == (OUTPUT_OBJECT_SHA256 if done else INPUT_OBJECT_SHA256), "unexpected whole-object hash")
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
    require(hashlib.sha256(json.dumps(sorted(relocations), separators=(",", ":")).encode()).hexdigest() == EXPECTED_RELOCATIONS_SHA256, "unexpected function relocations")
    require(all(not pos <= offset < pos + 4 for offset, *_ in relocations for pos in FIELDS), "relocation overlaps allocation field")
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
    require(hashlib.sha256(data).hexdigest() == OUTPUT_OBJECT_SHA256, "unexpected output object hash")
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
