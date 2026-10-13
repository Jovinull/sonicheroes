#!/usr/bin/env python3
"""Restore calc_colli.cpp's compiler-emitted constant order without changing code.

Permute the existing zero, one and minus-one scalar atoms and their symbol
values. Instructions, relocation records and all other data stay unchanged.
Whole-object and pool hashes reject changed compiler output.
See docs/calc-colli-constant-order.md for the native matching evidence.
"""
import argparse
import hashlib
import os
from pathlib import Path
import struct
import tempfile

INPUT_SHA256 = '304aec79eb1c2004cbc80c42092002bb27059072728c65bb1c7ab483d70b6e01'
OUTPUT_SHA256 = '5cb7ef08a2fa40408f0760b40d0b9b8a9c5ea85d7dbc26de805e2d8461baf380'
INPUT_POOL_SHA256 = '05a02f19ee5f34edc69935c08fab7487c76121b9e1e53e7b3897843e88c916ad'
OUTPUT_POOL_SHA256 = 'df311d5af132f5aca02961844d9749751a081d30ad51ae35086a3c5d11911812'
# name: (native offset, normalized offset, size, ELF symbol info)
POOL_SYMBOLS = {
    'lbl_8042DFD0': (0, 0, 4, 17),
    'lbl_8042DFD8': (4, 8, 4, 17),
    '@310': (8, 12, 4, 1),
    '@377': (12, 4, 4, 1),
    '@378': (16, 16, 8, 1),
}
MOVED_SYMBOLS = {name: (old, new) for name, (old, new, _, _) in POOL_SYMBOLS.items() if old != new}
POOL_SIZE = 24
POOL_REFERENCES = 50


def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def move(offset):
    require(0 <= offset < POOL_SIZE, 'pool offset out of range')
    return offset + 4 if 4 <= offset < 12 else offset - 8 if 12 <= offset < 16 else offset


def normalize(blob):
    checksum = digest(blob)
    require(checksum in (INPUT_SHA256, OUTPUT_SHA256), 'unexpected whole-object hash')
    done = checksum == OUTPUT_SHA256
    require(len(blob) >= 52, 'truncated ELF header')
    h = struct.unpack_from('>16sHHIIIIIHHHHHH', blob)
    require(h[0][:7] == b'\x7fELF\x01\x02\x01' and h[1:4] == (1, 20, 1), 'expected relocatable PowerPC ELF32 big-endian')
    shoff, entsize, count, names_index = h[6], h[11], h[12], h[13]
    require(entsize == 40 and 0 < names_index < count and shoff >= 52 and shoff + count * 40 <= len(blob), 'invalid section table')
    sections = [struct.unpack_from('>10I', blob, shoff + i * 40) for i in range(count)]

    def payload(section):
        require(section[1] != 8 and section[4] + section[5] <= len(blob), 'invalid section payload')
        return blob[section[4]:section[4] + section[5]]

    def string(table, offset):
        require(0 <= offset < len(table), 'invalid string offset')
        end = table.find(b'\0', offset)
        require(end >= offset, 'unterminated string')
        return table[offset:end].decode('ascii')

    occupied = [(0, 52), (shoff, shoff + count * 40)]
    for section in sections[1:]:
        if section[1] != 8 and section[5]:
            payload(section)
            occupied.append((section[4], section[4] + section[5]))
    occupied.sort()
    require(all(a[1] <= b[0] for a, b in zip(occupied, occupied[1:])), 'overlapping ELF regions')
    names = payload(sections[names_index])
    named = {}
    for i, section in enumerate(sections):
        name = string(names, section[0])
        require(name not in named, 'duplicate section name')
        named[name] = (i, section)
    require('.sdata2' in named and '.symtab' in named, 'missing pool or symbols')
    pool_index, pool = named['.sdata2']
    require((pool[1], pool[2], pool[5], pool[8]) == (1, 3, POOL_SIZE, 8), 'unexpected pool layout')
    require(digest(payload(pool)) == (OUTPUT_POOL_SHA256 if done else INPUT_POOL_SHA256), 'unexpected pool hash')
    sym_index, symtab = named['.symtab']
    require(symtab[1] == 2 and symtab[9] == 16 and symtab[5] % 16 == 0 and symtab[6] < count, 'invalid symbol table')
    strings = payload(sections[symtab[6]])
    symbols = list(struct.iter_unpack('>IIIBBH', payload(symtab)))
    atoms, found, section_symbols = [], {}, 0
    for i, (name_offset, value, size, info, other, section) in enumerate(symbols):
        if section != pool_index:
            continue
        name = string(strings, name_offset)
        if info == 3:
            require((value, size, other) == (0, 0, 0), 'invalid pool section symbol')
            section_symbols += 1
            continue
        require(name in POOL_SYMBOLS and name not in found, 'unexpected pool atom')
        old, new, expected_size, expected_info = POOL_SYMBOLS[name]
        require((value, size, info, other) == (new if done else old, expected_size, expected_info, 0), 'unexpected pool atom shape')
        atoms.append((value, value + size))
        found[name] = i
    atoms.sort()
    require(section_symbols == 1 and len(atoms) == 5 and atoms[0][0] == 0 and atoms[-1][1] == POOL_SIZE and all(a[1] == b[0] for a, b in zip(atoms, atoms[1:])), 'pool atom coverage changed')
    require(set(found) == set(POOL_SYMBOLS), 'missing pool symbols')
    references = 0
    for section in sections:
        require(section[1] != 9, 'unsupported REL relocations')
        if section[1] != 4:
            continue
        require(section[9] == 12 and section[5] % 12 == 0 and section[6] == sym_index and section[7] < count and section[7] != pool_index, 'invalid relocation section')
        for offset, info, addend in struct.iter_unpack('>IIi', payload(section)):
            require(info >> 8 < len(symbols) and offset < sections[section[7]][5], 'invalid relocation')
            symbol = symbols[info >> 8]
            if symbol[5] != pool_index:
                continue
            require(info & 255 == 109 and symbol[3] in (1, 17) and 0 <= addend < symbol[2], 'unsupported pool reference')
            require(offset + 4 <= sections[section[7]][5], 'pool relocation crosses section')
            if not done:
                require(move(symbol[1] + addend) == move(symbol[1]) + addend, 'reference crosses moved atom')
            references += 1
    require(references == POOL_REFERENCES, 'pool reference inventory changed')
    if done:
        return blob
    data = bytearray(blob)
    source = payload(pool)
    data[pool[4]:pool[4] + POOL_SIZE] = source[:4] + source[12:16] + source[4:12] + source[16:]
    for name in MOVED_SYMBOLS:
        index = found[name]
        struct.pack_into('>I', data, symtab[4] + index * 16 + 4, MOVED_SYMBOLS[name][1])
    require(digest(data) == OUTPUT_SHA256, 'unexpected output object hash')
    return bytes(data)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('stamp', type=Path, nargs='?')
    args = parser.parse_args(argv)
    original = args.object.read_bytes()
    try:
        output = normalize(original)
    except (ValueError, struct.error, UnicodeError, IndexError) as error:
        parser.exit(1, f'{args.object}: {error}\n')
    if output != original:
        temporary = None
        try:
            with tempfile.NamedTemporaryFile(dir=args.object.parent, prefix=args.object.name + '.', delete=False) as stream:
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


if __name__ == '__main__':
    main()
