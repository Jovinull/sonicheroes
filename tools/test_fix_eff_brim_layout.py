"""Synthetic ELF tests; no game object, instructions or asset payloads."""
from contextlib import ExitStack, redirect_stderr
import hashlib
from io import StringIO
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from tools import fix_eff_brim_layout as fix


def digest(data):
    return hashlib.sha256(data).hexdigest()


def fixture():
    names = ['', '.text', '.sdata2', 'extab', 'extabindex', '.symtab', '.strtab',
             '.rela.text', '.relaextab', '.relaextabindex', '.shstrtab']
    shstrings = bytearray(b'\0')
    name_offsets = {'': 0}
    for name in names[1:]:
        name_offsets[name] = len(shstrings)
        shstrings.extend(name.encode() + b'\0')
    strings = bytearray(b'\0')
    symbols = [bytes(16)]
    symbol_indices, symbol_offsets = {}, {}
    for name in ('.sdata2', 'extab'):
        index = names.index(name)
        symbols.append(struct.pack('>IIIBBH', 0, 0, 0, 3, 0, index))
        for atom, (old, new, size) in fix.ATOMS[name].items():
            symbol_indices[atom] = len(symbols)
            symbol_offsets[atom] = len(symbols) * 16 + 4
            offset = len(strings)
            strings.extend(atom.encode() + b'\0')
            symbols.append(struct.pack('>IIIBBH', offset, old, size, 1, 2 if name == 'extab' else 0, index))
    external_index = len(symbols)
    strings.extend(b'external\0')
    symbols.append(struct.pack('>IIIBBH', len(strings) - 9, 0, 0, 16, 0, 0))
    pool = bytes((i * 7 + 13) % 256 for i in range(128))
    eh = bytes((i * 11 + 29) % 256 for i in range(524))
    text, pool_relocations = bytearray(), bytearray()
    atoms = list(fix.ATOMS['.sdata2'])
    for i in range(95):
        atom = atoms[i % len(atoms)]
        width = fix.ATOMS['.sdata2'][atom][2]
        text.extend(struct.pack('>I', (48 if width == 4 else 50) << 26))
        pool_relocations.extend(struct.pack('>IIi', i * 4, symbol_indices[atom] << 8 | 109, 0))
    eh_sites = [44, 48, 52, 56, 60, 64, 324, 336, 368, 412, 424, 432, 476, 488, 496]
    eh_relocations = b''.join(struct.pack('>IIi', off, external_index << 8 | 1, 0) for off in eh_sites)
    index_relocations = b''.join(struct.pack('>IIi', i * 12 + 8, symbol_indices[atom] << 8 | 1, 0)
                                  for i, atom in enumerate(fix.ATOMS['extab']))
    payloads = [b'', bytes(text), pool, eh, bytes(360), b''.join(symbols), bytes(strings),
                bytes(pool_relocations), eh_relocations, index_relocations, bytes(shstrings)]
    types = [0, 1, 1, 1, 1, 2, 3, 4, 4, 4, 3]
    flags = [0, 6, 3, 2, 2, 0, 0, 0, 0, 0, 0]
    aligns = [0, 4, 8, 4, 4, 4, 1, 4, 4, 4, 1]
    blob, headers, offsets = bytearray(52), [], {}
    for i, (name, data) in enumerate(zip(names, payloads)):
        align = aligns[i] or 1
        blob.extend(bytes((-len(blob)) % align))
        offset = len(blob) if i else 0
        offsets[name] = offset
        blob.extend(data)
        link = 6 if i == 5 else 5 if i in (7, 8, 9) else 0
        info = external_index if i == 5 else {7: 1, 8: 3, 9: 4}.get(i, 0)
        entsize = 16 if i == 5 else 12 if i in (7, 8, 9) else 0
        headers.append((name_offsets[name], types[i], flags[i], 0, offset, len(data), link, info, aligns[i], entsize))
    blob.extend(bytes((-len(blob)) % 4))
    shoff = len(blob)
    for header in headers:
        blob.extend(struct.pack('>10I', *header))
    ident = b'\x7fELF\x01\x02\x01' + bytes(9)
    struct.pack_into('>16sHHIIIIIHHHHHH', blob, 0, ident, 1, 20, 1, 0, 0, shoff, 0, 52, 0, 0, 40, len(names), 10)
    # Independent expected permutation, expressed as source slices rather than
    # invoking the normalizer's atom loop or coordinate mapping.
    out = bytearray(blob)
    newpool = pool[:84] + pool[104:108] + pool[100:104] + pool[108:120] + pool[124:128] + pool[84:100] + pool[120:124]
    neweh = eh[:268] + eh[508:516] + eh[268:508] + eh[516:]
    out[offsets['.sdata2']:offsets['.sdata2'] + 128] = newpool
    out[offsets['extab']:offsets['extab'] + 524] = neweh
    moves = {'@603': 108, '@604': 112, '@605': 116, '@606': 120, '@607': 88, '@608': 84,
             '@609': 92, '@612': 96, '@678': 124, '@693': 104,
             '@627': 276, '@680': 284, '@687': 292, '@694': 300, '@697': 348,
             '@704': 356, '@720': 380, '@733': 444, '@751': 508, '@758': 268}
    for atom, value in moves.items():
        struct.pack_into('>I', out, offsets['.symtab'] + symbol_offsets[atom], value)
    for i in range(6, 15):
        struct.pack_into('>I', out, offsets['.relaextab'] + i * 12, eh_sites[i] + 8)
    return bytes(blob), bytes(out), offsets, headers, symbol_indices, symbol_offsets


class LayoutTests(unittest.TestCase):
    def setUp(self):
        self.raw, self.expected, self.offsets, self.headers, self.indices, self.symoffs = fixture()
        self.stack = ExitStack()
        self.addCleanup(self.stack.close)
        self.stack.enter_context(patch.object(fix, 'INPUT_SHA256', digest(self.raw)))
        self.stack.enter_context(patch.object(fix, 'OUTPUT_SHA256', digest(self.expected)))
        hashes = {}
        for name, size in (('.sdata2', 128), ('extab', 524)):
            off = self.offsets[name]
            hashes[name] = (digest(self.raw[off:off + size]), digest(self.expected[off:off + size]))
        self.stack.enter_context(patch.object(fix, 'SECTION_HASHES', hashes))

    def rejected(self, data, message, bypass_hash=True):
        with patch.object(fix, 'INPUT_SHA256', digest(data) if bypass_hash else digest(self.raw)):
            with self.assertRaisesRegex(ValueError, message):
                fix.normalize(data)

    def test_expected_output_and_idempotence(self):
        self.assertEqual(fix.normalize(self.raw), self.expected)
        self.assertEqual(fix.normalize(self.expected), self.expected)

    def test_only_permitted_bytes_change(self):
        allowed = set()
        for name, start, size in (('.sdata2', 84, 44), ('extab', 268, 248)):
            allowed.update(range(self.offsets[name] + start, self.offsets[name] + start + size))
        for name, atoms in fix.ATOMS.items():
            for atom, (old, new, size) in atoms.items():
                if old != new:
                    off = self.offsets['.symtab'] + self.symoffs[atom]
                    allowed.update(range(off, off + 4))
        for i in range(6, 15):
            off = self.offsets['.relaextab'] + i * 12
            allowed.update(range(off, off + 4))
        out = fix.normalize(self.raw)
        self.assertTrue(all(i in allowed for i, (a, b) in enumerate(zip(self.raw, out)) if a != b))
        self.assertEqual(len(out), len(self.raw))

    def test_effective_atom_bytes_and_exception_sites_preserved(self):
        out = fix.normalize(self.raw)
        for name, atoms in fix.ATOMS.items():
            base = self.offsets[name]
            for old, new, size in atoms.values():
                self.assertEqual(self.raw[base + old:base + old + size], out[base + new:base + new + size])
        base = self.offsets['extab']
        for i in range(15):
            off = self.offsets['.relaextab'] + i * 12
            old, info, addend = struct.unpack_from('>IIi', self.raw, off)
            new, newinfo, newaddend = struct.unpack_from('>IIi', out, off)
            self.assertEqual((info, addend), (newinfo, newaddend))
            self.assertEqual(self.raw[base + old:base + old + 4], out[base + new:base + new + 4])

    def test_changed_compiler_output_rejected(self):
        self.rejected(self.raw[:-1] + bytes([self.raw[-1] ^ 1]), 'whole-object hash', False)

    def test_wrong_endian_rejected(self):
        data = bytearray(self.raw); data[5] = 1
        self.rejected(data, 'PowerPC ELF32')

    def test_truncated_header_rejected(self):
        self.rejected(self.raw[:40], 'truncated ELF')

    def test_overlapping_sections_rejected(self):
        data = bytearray(self.raw); shoff = struct.unpack_from('>I', data, 32)[0]
        struct.pack_into('>I', data, shoff + 2 * 40 + 16, self.offsets['.text'])
        self.rejected(data, 'overlapping')

    def test_changed_atom_payload_rejected(self):
        data = bytearray(self.raw); data[self.offsets['extab']] ^= 1
        self.rejected(data, 'section hash')

    def test_changed_visibility_rejected(self):
        data = bytearray(self.raw); data[self.offsets['.symtab'] + self.symoffs['@758'] + 9] = 0
        self.rejected(data, 'local atom')

    def test_changed_atom_size_rejected(self):
        data = bytearray(self.raw)
        struct.pack_into('>I', data, self.offsets['.symtab'] + self.symoffs['@612'] + 4, 4)
        self.rejected(data, 'local atom')

    def test_section_relative_target_rejected(self):
        data = bytearray(self.raw)
        struct.pack_into('>I', data, self.offsets['.rela.text'] + 4, 1 << 8 | 109)
        self.rejected(data, 'managed target')

    def test_literal_load_width_rejected(self):
        data = bytearray(self.raw); struct.pack_into('>I', data, self.offsets['.text'], 48 << 26)
        self.rejected(data, 'load width')

    def test_nonzero_exception_addend_rejected(self):
        data = bytearray(self.raw); struct.pack_into('>i', data, self.offsets['.relaextabindex'] + 8, 1)
        self.rejected(data, 'exception reference')

    def test_wrong_exception_relocation_kind_rejected(self):
        data = bytearray(self.raw); off = self.offsets['.relaextab'] + 4
        struct.pack_into('>I', data, off, struct.unpack_from('>I', data, off)[0] | 2)
        self.rejected(data, 'relocation site')

    def test_changed_exception_site_rejected(self):
        data = bytearray(self.raw); struct.pack_into('>I', data, self.offsets['.relaextab'] + 6 * 12, 328)
        self.rejected(data, 'sites changed')

    def test_relocation_outside_source_rejected(self):
        data = bytearray(self.raw)
        struct.pack_into('>I', data, self.offsets['.rela.text'], 380)
        self.rejected(data, 'relocation bounds')

    def test_exception_relocation_crosses_permutation_boundary(self):
        data = bytearray(self.raw)
        struct.pack_into('>I', data, self.offsets['.relaextab'] + 6 * 12, 507)
        self.rejected(data, 'crosses moved atom')

    def test_replace_failure_preserves_original_and_cleans_temporary(self):
        with tempfile.TemporaryDirectory(dir='/tmp') as tmp:
            obj, stamp = Path(tmp) / 'synthetic.o', Path(tmp) / 'stamp'
            obj.write_bytes(self.raw)
            with patch.object(fix.os, 'replace', side_effect=OSError('synthetic failure')):
                with self.assertRaisesRegex(OSError, 'synthetic failure'):
                    fix.main([str(obj), str(stamp)])
            self.assertEqual(obj.read_bytes(), self.raw)
            self.assertFalse(stamp.exists())
            self.assertEqual([p.name for p in Path(tmp).iterdir()], ['synthetic.o'])

    def test_cli_atomic_write_permissions_and_stamp(self):
        with tempfile.TemporaryDirectory(dir='/tmp') as tmp:
            obj, stamp = Path(tmp) / 'synthetic.o', Path(tmp) / 'stamp'
            obj.write_bytes(self.raw); obj.chmod(0o640)
            fix.main([str(obj), str(stamp)])
            self.assertEqual(obj.read_bytes(), self.expected)
            self.assertEqual(obj.stat().st_mode & 0o777, 0o640)
            self.assertTrue(stamp.exists())
            fix.main([str(obj), str(stamp)])
            self.assertEqual(sorted(p.name for p in Path(tmp).iterdir()), ['stamp', 'synthetic.o'])

    def test_cli_reject_does_not_write_or_stamp(self):
        with tempfile.TemporaryDirectory(dir='/tmp') as tmp:
            obj, stamp = Path(tmp) / 'synthetic.o', Path(tmp) / 'stamp'
            obj.write_bytes(b'bad input')
            with redirect_stderr(StringIO()), self.assertRaises(SystemExit):
                fix.main([str(obj), str(stamp)])
            self.assertEqual(obj.read_bytes(), b'bad input')
            self.assertFalse(stamp.exists())
            self.assertEqual([p.name for p in Path(tmp).iterdir()], ['synthetic.o'])


if __name__ == '__main__':
    unittest.main()
