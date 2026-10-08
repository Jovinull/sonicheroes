#!/usr/bin/env python3
"""Normalize the constructor's bounded loop allocation in complete eff_bomb.cpp.

Remainder: eight GPR fields in six of the constructor's 290 instructions.
Swap r28/r31 for the signed loop count and its compiler-derived byte offset.
Both are freshly initialized before this loop, callee-saved across every call,
and dead after the last comparison; subsequent frame operations redefine them.
The physical ABI saves/restores, all opcodes, immediates, branches, calls, data,
exception records and relocations remain unchanged. No retail input or complete
instruction word is written. See docs/eff-bomb-unit-evidence.md for source trials
and independent liveness proof. Remove this step when source/compiler lifetime
choices recover these fields naturally.

The complete object, text, constructor, section/symbol inventory and relocation
contracts fail closed on any changed compiler output. Two authentic ordinary
helper copies are discarded by the linker, never removed or altered here.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import struct
import tempfile

TEXT_SIZE = 3860
FUNCTION_NAME = '__ct__11TObjEffBombFP7TObjectiP5RwV3dP6sAngle18ENUM_EFF_BOMB_TYPE'
FUNCTION_OFFSET = 2028
FUNCTION_SIZE = 1160
INPUT_TEXT_SHA256 = '4229991af3e813e93fd3188c0ed0000a1a73e53fe4adc2b9007f354a3517ef68'
OUTPUT_TEXT_SHA256 = 'b0563d7bd34d825e912debcd24e5cd1ade23767b608c3393bc344f6a7dc72c93'
INPUT_FUNCTION_SHA256 = '6f128f3258f012d99bfd8ed39fc7586a4dfed9361b1ca792a0aa19d23606912d'
OUTPUT_FUNCTION_SHA256 = '10523e4009696eb03f5abcb0f9a2acc9347b776e43186a38a95bd440902a8e7e'
INPUT_OBJECT_SHA256 = '22f76ce22230cc056091fdad82a556974f2ab975de9e91b896a86a6215e1e282'
OUTPUT_OBJECT_SHA256 = 'ec002e4a91766c94c12634b8d09e6eae43a6d05ec2b5a8791569a4ae7ddf5052'
FIELDS = {364: {21: (28, 31)}, 368: {21: (31, 28)}, 380: {16: (31, 28)}, 500: {21: (31, 28), 16: (31, 28)}, 504: {21: (28, 31), 16: (28, 31)}, 508: {16: (28, 31)}}
EXPECTED_OPCODES = {364: 14, 368: 14, 380: 14, 500: 14, 504: 14, 508: 11}
EXPECTED_RELOCATIONS_SHA256 = '640bd849aa30c05f974139bea0f89ebfc01537f183399f7e48f2790ef4050ae2'

EXPECTED_SECTIONS_SHA256 = 'dcb715c33e28d41aa5b52080cdd2be129470f81a163da884a468e434422511a7'
EXPECTED_SYMBOLS_SHA256 = '91eb4eada53fb0d7fbdc399444947f280cb42b6987ac9469a68cd1ae1a712da2'
EXPECTED_ALL_RELOCATIONS_SHA256 = '903b909d82e5114162a197fbc5f48ba62804fb417af5001421bad8b05d0f7537'


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
