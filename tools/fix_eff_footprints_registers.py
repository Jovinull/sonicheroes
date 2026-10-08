#!/usr/bin/env python3
"""Normalize the bounded Disp register cycle in complete eff_footprints.cpp.

Remainder: twelve GPR fields in eleven of Disp's 105 instructions. Rotate
position cursor r6 to r9, green r7 to r6, blue r8 to r7 and alpha r9 to r8.
All four values have fresh definitions, unchanged consumers and no intervening
calls; they die before the first rendering call. Early return bypasses them.
The ABI, floating-point operands, opcodes, immediates, branches, calls, data,
exception records and relocations remain unchanged. No retail input or complete
instruction word is written. See docs/eff-footprints-unit-evidence.md for source
trials and independent liveness proof. Remove this step when a source/compiler
lifetime choice reproduces this allocation in src/game/effect/eff_footprints.cpp.

Complete object, text, function, section/symbol inventory and relocation
contracts fail closed on changed compiler output. Authentic unused ordinary
helper copies are discarded naturally by the linker, never altered here.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import struct
import tempfile

TEXT_SIZE = 3700
FUNCTION_NAME = 'Disp__13EffFootPrintsFv'
FUNCTION_OFFSET = 1336
FUNCTION_SIZE = 420
INPUT_TEXT_SHA256 = 'f8e0293fc9d736ed7b4b47593a23c623695e29beff7452021a9d7b69cbf95fad'
OUTPUT_TEXT_SHA256 = 'd78c5f034dc90d83fb285c040db8f6076db4f1563f961b466ad550e4e918d0ce'
INPUT_FUNCTION_SHA256 = '1796b6c0863d43a8db46c6b86e6236c3874a2e209a54127dd55ff813a77807f8'
OUTPUT_FUNCTION_SHA256 = '212f0924a875c3cb5bc932b8f44de588c71a556af67b21a62025f5e554574a00'
INPUT_OBJECT_SHA256 = '513a58d4a45a6449febd94c87c8040f560497c8fc915adfbe3ffb5e77b876c9f'
OUTPUT_OBJECT_SHA256 = 'a2f66eca460237ca4c63552233850746d873209aa9edf2087882faad18742f38'
FIELDS = {128: {16: (6, 9)}, 148: {16: (6, 9)}, 152: {16: (6, 9)}, 156: {16: (6, 9)}, 224: {21: (7, 6)}, 260: {21: (8, 7)}, 264: {21: (9, 8)}, 308: {21: (7, 6)}, 312: {21: (8, 7)}, 316: {21: (9, 8)}, 352: {21: (6, 9), 16: (6, 9)}}
EXPECTED_OPCODES = {128: 31, 148: 48, 152: 48, 156: 48, 224: 32, 260: 32, 264: 34, 308: 38, 312: 38, 316: 38, 352: 14}
EXPECTED_RELOCATIONS_SHA256 = 'cf346be142736bb6d4ee29ee6b448e53483a8c81c232ec1438e8e3768f535068'

EXPECTED_SECTIONS_SHA256 = '62563e0edecaa3376747ace428801545a7c8f2b19c1cffb9392b0fca40ad16e7'
EXPECTED_SYMBOLS_SHA256 = 'f912f98b330f654dc0e5110332024760cf17ec3f8a9cace2c8c849bbe6d24416'
EXPECTED_ALL_RELOCATIONS_SHA256 = '953d89b82b5b3a766c40ed01532652fe5c6a6c64eebe1053a0a23fa22e8e7d37'


def inventory_hash(rows):
    return hashlib.sha256(json.dumps(rows, separators=(",", ":")).encode()).hexdigest()


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
    section_names = []
    section_inventory = []
    for i, section in enumerate(sections):
        name = string(names, section[0])
        require(name not in named or not name, "duplicate section name")
        named[name] = (i, section)
        section_names.append(name)
        section_inventory.append((name, section[1], section[2], section[3], section[5], section[6], section[7], section[8], section[9]))
        if section[1] not in (0, 8):
            payload(section)
    require(".text" in named and ".symtab" in named, "missing text or symbols")
    text_index, text = named[".text"]
    require(text[1] == 1 and text[2] == 6 and text[5] == TEXT_SIZE, "unexpected text section")
    require(text[4] >= 52 and text[4] + text[5] <= shoff, "text overlaps ELF metadata")
    for i, section in enumerate(sections):
        if i != text_index and section[1] not in (0, 8) and section[5]:
            require(section[4] + section[5] <= text[4] or section[4] >= text[4] + text[5], "overlapping text payload")
    require(inventory_hash(section_inventory) == EXPECTED_SECTIONS_SHA256, "unexpected section inventory")
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
    symbol_inventory = []
    for index, symbol in enumerate(symbols):
        name, value, size, info, other, section = symbol
        symbol_name = string(strings, name)
        symbol_inventory.append((symbol_name, value, size, info, other, section))
        if symbol_name == FUNCTION_NAME:
            require((value, size, info, other, section) == (FUNCTION_OFFSET, FUNCTION_SIZE, 0x12, 0, text_index), "unexpected function boundary or binding")
            found.append(index)
        elif section == text_index and (info & 15) != 3:
            require(not FUNCTION_OFFSET <= value < FUNCTION_OFFSET + FUNCTION_SIZE, "unexpected interior function symbol")
            if size:
                require(value + size <= FUNCTION_OFFSET or value >= FUNCTION_OFFSET + FUNCTION_SIZE, "overlapping function symbol")
    require(len(found) == 1, "missing or duplicate function symbol")
    require(inventory_hash(symbol_inventory) == EXPECTED_SYMBOLS_SHA256, "unexpected symbol inventory")
    relocations = []
    all_relocations = []
    for section in sections:
        require(not (section[1] == 9 and section[7] == text_index), "unsupported REL text relocations")
        if section[1] != 4:
            continue
        require(section[9] == 12 and section[5] % 12 == 0 and section[7] < count and section[6] == sym_index, "invalid relocation section")
        for offset, info, addend in struct.iter_unpack(">IIi", payload(section)):
            require(info >> 8 < len(symbols), "invalid relocation symbol")
            symbol = symbols[info >> 8]
            all_relocations.append((section_names[section[7]], offset, info & 255, string(strings, symbol[0]), addend))
            if section[7] == text_index:
                require(offset < TEXT_SIZE, "relocation outside text")
                if FUNCTION_OFFSET - 3 <= offset < FUNCTION_OFFSET + FUNCTION_SIZE:
                    require(offset >= FUNCTION_OFFSET, "relocation crosses function boundary")
                    symbol = symbols[info >> 8]
                    relocations.append((offset - FUNCTION_OFFSET, info & 255, string(strings, symbol[0]), addend))
    require(hashlib.sha256(json.dumps(sorted(relocations), separators=(",", ":")).encode()).hexdigest() == EXPECTED_RELOCATIONS_SHA256, "unexpected function relocations")
    require(inventory_hash(sorted(all_relocations)) == EXPECTED_ALL_RELOCATIONS_SHA256, "unexpected complete relocation inventory")
    widths = {1: 4, 4: 2, 5: 2, 6: 2, 10: 4, 109: 4}
    require(all(kind in widths for _, kind, *_ in relocations), "unsupported relocation width")
    require(all(offset + widths[kind] <= pos or offset >= pos + 4
                for offset, kind, *_ in relocations for pos in FIELDS),
            "relocation overlaps allocation field")
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
        args.stamp.parent.mkdir(parents=True, exist_ok=True)
        args.stamp.touch()


if __name__ == "__main__":
    main()
