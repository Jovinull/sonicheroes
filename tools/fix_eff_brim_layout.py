#!/usr/bin/env python3
"""Normalize existing literal and exception atom order in complete eff_brim.cpp.

Permute compiler-produced pool atoms and move the existing eight-byte
GetPreviousNode exception record. Update local atom values and nine exception
relocation sites, preserving all instruction bytes and relocation meanings.
No atoms, instructions or retail payload bytes are added. Whole-object and
section hashes reject changed compiler output. Remove when native emission
recovers both orders. Ordinary unreferenced helpers remain for linker GC.
"""
import argparse
import hashlib
import os
from pathlib import Path
import struct
import tempfile

INPUT_SHA256 = '119debc444b35837218dd67c0ca511325245af52408394b75c28672cf9b3e3e4'
OUTPUT_SHA256 = 'ec950fe5394a3d5c818f9b73dc2d62057e82dea455c926c4c3d6072977c605e9'
ATOMS = {
    '.sdata2': {
        '@335': (0, 0, 8),
        '@347': (8, 8, 4),
        '@348': (12, 12, 4),
        '@349': (16, 16, 4),
        '@350': (20, 20, 4),
        '@351': (24, 24, 4),
        '@355': (28, 28, 4),
        '@356': (32, 32, 4),
        '@357': (36, 36, 4),
        '@399': (40, 40, 4),
        '@400': (44, 44, 4),
        '@401': (48, 48, 4),
        '@402': (52, 52, 4),
        '@403': (56, 56, 4),
        '@404': (60, 60, 4),
        '@406': (64, 64, 4),
        '@407': (68, 68, 4),
        '@429': (72, 72, 4),
        '@430': (76, 76, 4),
        '@521': (80, 80, 4),
        '@603': (84, 108, 4),
        '@604': (88, 112, 4),
        '@605': (92, 116, 4),
        '@606': (96, 120, 4),
        '@607': (100, 88, 4),
        '@608': (104, 84, 4),
        '@609': (108, 92, 4),
        '@612': (112, 96, 8),
        '@678': (120, 124, 4),
        '@693': (124, 104, 4),
    },
    'extab': {
        '@336': (0, 0, 8),
        '@341': (8, 8, 8),
        '@352': (16, 16, 8),
        '@364': (24, 24, 8),
        '@371': (32, 32, 8),
        '@412': (40, 40, 28),
        '@419': (68, 68, 8),
        '@424': (76, 76, 8),
        '@431': (84, 84, 8),
        '@436': (92, 92, 8),
        '@443': (100, 100, 8),
        '@460': (108, 108, 8),
        '@499': (116, 116, 64),
        '@502': (180, 180, 8),
        '@524': (188, 188, 8),
        '@531': (196, 196, 8),
        '@539': (204, 204, 48),
        '@544': (252, 252, 8),
        '@620': (260, 260, 8),
        '@627': (268, 276, 8),
        '@680': (276, 284, 8),
        '@687': (284, 292, 8),
        '@694': (292, 300, 48),
        '@697': (340, 348, 8),
        '@704': (348, 356, 24),
        '@720': (372, 380, 64),
        '@733': (436, 444, 64),
        '@751': (500, 508, 8),
        '@758': (508, 268, 8),
        '@761': (516, 516, 8),
    },
}
SECTION_LAYOUT = {'.sdata2': (128, 3, 8), 'extab': (524, 2, 4)}
SECTION_HASHES = {
    '.sdata2': ('59adc498f2f7fcecacef009b3759c9a2cbb6fb001b4483f92df511b6e7f4d1b1', '0896f4eeb7565ed0a3ec192609d214cbb1fc00128e64b86042dd8f823543bf0a'),
    'extab': ('e88af0b53e31bb39bf48ac41b9b1469a8933b371846b400abf03c3f2e8c5c5d1', '1cc5440b756f2a32fdf9ad1aaf0d2cd9b280a2c4a7b62556bf4a92a03f0b1fd8'),
}
EH_MOVED_SITES = (324, 336, 368, 412, 424, 432, 476, 488, 496)

def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


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
    require(all(n in named for n in (*ATOMS, '.symtab', '.text', 'extabindex')), 'missing managed sections or symbols')
    sym_index, symtab = named['.symtab']
    require(symtab[1] == 2 and symtab[9] == 16 and symtab[5] % 16 == 0 and symtab[6] < count, 'invalid symbol table')
    strings = payload(sections[symtab[6]])
    symbols = list(struct.iter_unpack('>IIIBBH', payload(symtab)))
    managed, updates = {}, []
    for name, definitions in ATOMS.items():
        index, section = named[name]
        size, flags, align = SECTION_LAYOUT[name]
        require((section[1], section[2], section[5], section[8]) == (1, flags, size, align), 'unexpected managed section layout')
        require(digest(payload(section)) == SECTION_HASHES[name][int(done)], 'unexpected managed section hash')
        found, section_symbols = set(), 0
        spans = []
        for i, (string_offset, value, atom_size, info, other, owner) in enumerate(symbols):
            if owner != index:
                continue
            if info == 3:
                require((value, atom_size, other) == (0, 0, 0), 'invalid section symbol')
                section_symbols += 1
                continue
            atom_name = string(strings, string_offset)
            require(atom_name in definitions and atom_name not in found, 'unexpected atom identity')
            old, new, expected_size = definitions[atom_name]
            require((value, atom_size, info, other) == (new if done else old, expected_size, 1, 2 if name == 'extab' else 0), 'unexpected local atom contract')
            require(value % (expected_size if name == '.sdata2' else 4) == 0, 'misaligned atom')
            found.add(atom_name)
            spans.append((value, value + atom_size))
            if old != new:
                updates.append((symtab[4] + i * 16 + 4, new))
        spans.sort()
        require(section_symbols == 1 and found == set(definitions), 'incomplete atom inventory')
        require(spans[0][0] == 0 and spans[-1][1] == size and all(x[1] == y[0] for x, y in zip(spans, spans[1:])), 'invalid atom coverage')
        managed[index] = (name, definitions)

    def moved_offset(index, offset):
        name, definitions = managed[index]
        for old, new, size in definitions.values():
            if old <= offset < old + size:
                return new + offset - old
        raise ValueError('offset outside managed atoms')

    pool_refs, eh_refs, eh_sites, changed_sites = 0, 0, 0, []
    for section in sections:
        require(section[1] != 9, 'unsupported REL relocations')
        if section[1] != 4:
            continue
        require(section[9] == 12 and section[5] % 12 == 0 and section[6] == sym_index and section[7] < count, 'invalid relocation section')
        source = sections[section[7]]
        for i, (offset, info, addend) in enumerate(struct.iter_unpack('>IIi', payload(section))):
            require(info >> 8 < len(symbols) and offset + 4 <= source[5], 'invalid relocation bounds')
            symbol = symbols[info >> 8]
            if section[7] in managed:
                require(managed[section[7]][0] == 'extab' and info & 255 == 1, 'unexpected managed relocation site')
                eh_sites += 1
                old = offset - 8 if done and offset in {x + 8 for x in EH_MOVED_SITES} else offset
                new = moved_offset(section[7], old)
                require(moved_offset(section[7], old + 3) == new + 3, 'relocation crosses moved atom')
                if old != new:
                    changed_sites.append(old)
                    updates.append((section[4] + i * 12, new))
            if symbol[5] not in managed:
                continue
            require(symbol[3] == 1 and 0 <= addend < symbol[2], 'unsupported managed target')
            target_name = managed[symbol[5]][0]
            if target_name == '.sdata2':
                require(section[7] == named['.text'][0] and info & 255 == 109, 'unsupported literal reference')
                instruction = struct.unpack_from('>I', payload(source), offset)[0]
                width = {48: 4, 50: 8}.get(instruction >> 26)
                require(width == symbol[2] and addend == 0, 'literal load width changed')
                pool_refs += 1
            else:
                require(section[7] == named['extabindex'][0] and info & 255 == 1 and addend == 0 and offset % 12 == 8, 'unsupported exception reference')
                eh_refs += 1
    require((pool_refs, eh_refs, eh_sites) == (95, 30, 15), 'relocation inventory changed')
    require(tuple(sorted(changed_sites)) == EH_MOVED_SITES, 'exception relocation sites changed')
    if done:
        return blob
    data = bytearray(blob)
    for name, definitions in ATOMS.items():
        section = named[name][1]
        original = payload(section)
        for old, new, size in definitions.values():
            data[section[4] + new:section[4] + new + size] = original[old:old + size]
    for offset, value in updates:
        struct.pack_into('>I', data, offset, value)
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
