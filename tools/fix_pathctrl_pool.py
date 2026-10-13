#!/usr/bin/env python3
"""Restore pathctrl.cpp's compiler-emitted constant order without changing code.

Move the existing four-byte 9.0f atom from pool +0 to +48, shifting the
intervening twelve atoms down four bytes. Only pool bytes and thirteen
symbol values move; all instructions, relocation records and other data stay
unchanged. Whole-object and pool hashes reject changed compiler output.
See docs/pathctrl-constant-order.md for the native matching evidence.
"""
import argparse
import hashlib
import os
from pathlib import Path
import struct
import tempfile

INPUT_SHA256 = '50b1f88238410847f2cbd9043d784e82f5b52023cb0877fde22278f2885e5592'
OUTPUT_SHA256 = 'f216b96e2aa6ba3539a5e5139bcaf5ff327fffed9080cb8e6e2aa7a465703c4d'
INPUT_POOL_SHA256 = 'b50350171cd4149ad0da7b161ad355c6b3345933218e72e41b63204322eda08d'
OUTPUT_POOL_SHA256 = '3d104160c0a3be7922f6e91391da747469d91ceceac45801c4b7c5af6d297146'
MOVED_SYMBOLS = {'@402': (0, 48), 'lbl_8042DC38': (20, 16), 'lbl_8042DC28': (4, 0), 'lbl_8042DC3C': (24, 20), 'lbl_8042DC2C': (8, 4), 'lbl_8042DC44': (32, 28), 'lbl_8042DC48': (36, 32), 'lbl_8042DC4C': (40, 36), 'lbl_8042DC50': (44, 40), 'lbl_8042DC54': (48, 44), 'lbl_8042DC40': (28, 24), 'lbl_8042DC30': (12, 8), 'lbl_8042DC34': (16, 12)}
POOL_SIZE = 56
POOL_REFERENCES = 36


def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def move(offset):
    require(0 <= offset < POOL_SIZE, 'pool offset out of range')
    return offset + 48 if offset < 4 else offset - 4 if offset < 52 else offset


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
        require(info in (1, 17) and other == 0 and size == 4 and value % size == 0 and value + size <= POOL_SIZE, 'invalid pool atom')
        atoms.append((value, value + size))
        if name in MOVED_SYMBOLS:
            old, new = MOVED_SYMBOLS[name]
            require(name not in found and size == 4 and value == (new if done else old), 'unexpected moved atom')
            found[name] = i
    atoms.sort()
    require(section_symbols == 1 and len(atoms) == 14 and atoms[0][0] == 0 and atoms[-1][1] == POOL_SIZE and all(a[1] == b[0] for a, b in zip(atoms, atoms[1:])), 'pool atom coverage changed')
    require(set(found) == set(MOVED_SYMBOLS), 'missing moved symbols')
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
    data[pool[4]:pool[4] + POOL_SIZE] = source[4:52] + source[:4] + source[52:]
    for name, index in found.items():
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
