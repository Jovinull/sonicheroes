"""Synthetic objects exercise literal ownership, relocation safety and atomic I/O."""
import contextlib
import hashlib
import io
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from tools import fix_eff_crash3d_pool as fixer


def fixture():
    names = ['', '.text', '.sdata2', '.symtab', '.strtab', '.rela.text', '.shstrtab']
    shstrings = b''
    name_offsets = {}
    for name in names:
        name_offsets[name] = len(shstrings)
        shstrings += name.encode() + b'\0'
    strings = b'\0'
    symbols = [bytes(16), struct.pack('>IIIBBH', 0, 0, 0, 3, 0, 2)]
    positions = list(range(0, 64, 4)) + [64] + list(range(72, 100, 4))
    for i, value in enumerate(positions):
        name = f'@{338 + i}' if i < 10 else f'synthetic_{i}'
        symbols.append(struct.pack('>IIIBBH', len(strings), value, 8 if value == 64 else 4, 1, 0, 2))
        strings += name.encode() + b'\0'
    # Distinct synthetic bytes, with no original-game instruction or data payload.
    pool = bytes(range(100))
    text = bytes([0xA5]) * (156 * 4)
    rels = b''.join(struct.pack('>IIi', i * 4, ((2 + i % 24) << 8) | 109, 0) for i in range(156))
    payloads = [b'', text, pool, b''.join(symbols), strings, rels, shstrings]
    kinds = [0, 1, 1, 2, 3, 4, 3]
    data = bytearray(52)
    headers = []
    offsets = {}
    for index, payload in enumerate(payloads):
        data.extend(bytes(-len(data) % 8))
        offsets[names[index]] = len(data)
        headers.append((name_offsets[names[index]], kinds[index], 6 if index == 1 else 3 if index == 2 else 0, 0, len(data), len(payload), 4 if index == 3 else 3 if index == 5 else 0, 1 if index == 5 else 0, 8, 16 if index == 3 else 12 if index == 5 else 0))
        data.extend(payload)
    data.extend(bytes(-len(data) % 8))
    offsets['headers'] = len(data)
    for row in headers:
        data.extend(struct.pack('>10I', *row))
    struct.pack_into('>16sHHIIIIIHHHHHH', data, 0, b'\x7fELF\x01\x02\x01' + bytes(9), 1, 20, 1, 0, 0, offsets['headers'], 0, 52, 0, 0, 40, len(headers), 6)
    expected = bytearray(data)
    order = [36] + list(range(0, 36, 4)) + list(range(40, 100, 4))
    expected[offsets['.sdata2']:offsets['.sdata2'] + 100] = b''.join(pool[n:n + 4] for n in order)
    for i, target in enumerate(list(range(4, 40, 4)) + [0]):
        struct.pack_into('>I', expected, offsets['.symtab'] + (i + 2) * 16 + 4, target)
    return bytes(data), bytes(expected), offsets


class PoolNormalizationTests(unittest.TestCase):
    def setUp(self):
        self.raw, self.expected, self.at = fixture()
        digest = lambda b: hashlib.sha256(b).hexdigest()
        start = self.at['.sdata2']
        self.patches = patch.multiple(fixer, INPUT_SHA256=digest(self.raw), OUTPUT_SHA256=digest(self.expected), INPUT_POOL_SHA256=digest(self.raw[start:start + 100]), OUTPUT_POOL_SHA256=digest(self.expected[start:start + 100]))
        self.patches.start()
        self.addCleanup(self.patches.stop)

    def guarded_reject(self, blob, message):
        with patch.object(fixer, 'INPUT_SHA256', hashlib.sha256(blob).hexdigest()):
            with self.assertRaisesRegex(ValueError, message):
                fixer.normalize(blob)

    def test_exact_output_and_idempotence(self):
        self.assertEqual(fixer.normalize(self.raw), self.expected)
        self.assertEqual(fixer.normalize(self.expected), self.expected)

    def test_code_and_relocations_unchanged(self):
        result = fixer.normalize(self.raw)
        for section, size in (('.text', 624), ('.rela.text', 1872)):
            at = self.at[section]
            self.assertEqual(result[at:at + size], self.raw[at:at + size])
        allowed = set(range(self.at['.sdata2'], self.at['.sdata2'] + 40))
        for i in range(2, 12):
            allowed.update(range(self.at['.symtab'] + i * 16 + 4, self.at['.symtab'] + i * 16 + 8))
        self.assertTrue(all(i in allowed for i, (a, b) in enumerate(zip(self.raw, result)) if a != b))

    def test_every_reference_retains_bytes(self):
        result = fixer.normalize(self.raw)
        for i in range(156):
            rel = self.at['.rela.text'] + i * 12
            _, info, addend = struct.unpack_from('>IIi', self.raw, rel)
            sym = self.at['.symtab'] + (info >> 8) * 16
            old, size = struct.unpack_from('>II', self.raw, sym + 4)
            new = struct.unpack_from('>I', result, sym + 4)[0]
            pool = self.at['.sdata2']
            self.assertEqual(self.raw[pool + old + addend:pool + old + size], result[pool + new + addend:pool + new + size])

    def test_changed_compiler_output_rejected(self):
        blob = bytearray(self.raw)
        blob[self.at['.text']] ^= 1
        with self.assertRaisesRegex(ValueError, 'whole-object'):
            fixer.normalize(blob)

    def test_changed_pool_rejected(self):
        blob = bytearray(self.raw)
        blob[self.at['.sdata2']] ^= 1
        self.guarded_reject(blob, 'pool hash')

    def test_wrong_endianness_rejected(self):
        blob = bytearray(self.raw)
        blob[5] = 1
        self.guarded_reject(blob, 'PowerPC')

    def test_truncated_header_rejected(self):
        self.guarded_reject(b'fake', 'truncated ELF')

    def test_section_overlap_rejected(self):
        blob = bytearray(self.raw)
        struct.pack_into('>I', blob, self.at['headers'] + 2 * 40 + 16, self.at['.text'])
        self.guarded_reject(blob, 'overlapping ELF')

    def test_changed_symbol_binding_rejected(self):
        blob = bytearray(self.raw)
        blob[self.at['.symtab'] + 2 * 16 + 12] = 17
        self.guarded_reject(blob, 'pool atom')

    def test_section_relative_reference_rejected(self):
        blob = bytearray(self.raw)
        struct.pack_into('>I', blob, self.at['.rela.text'] + 4, (1 << 8) | 109)
        self.guarded_reject(blob, 'pool reference')

    def test_cross_atom_addend_rejected(self):
        blob = bytearray(self.raw)
        struct.pack_into('>i', blob, self.at['.rela.text'] + 8, 4)
        self.guarded_reject(blob, 'pool reference')

    def test_unsupported_relocation_kind_rejected(self):
        blob = bytearray(self.raw)
        struct.pack_into('>I', blob, self.at['.rela.text'] + 4, (2 << 8) | 1)
        self.guarded_reject(blob, 'pool reference')

    def test_cli_success_preserves_permissions_and_stamps(self):
        with tempfile.TemporaryDirectory(dir='/tmp') as directory:
            path = Path(directory) / 'object.o'
            stamp = Path(directory) / 'output.stamp'
            path.write_bytes(self.raw)
            path.chmod(0o640)
            fixer.main([str(path), str(stamp)])
            self.assertEqual(path.read_bytes(), self.expected)
            self.assertEqual(path.stat().st_mode & 0o777, 0o640)
            self.assertTrue(stamp.exists())
            self.assertEqual(sorted(p.name for p in Path(directory).iterdir()), ['object.o', 'output.stamp'])

    def test_cli_failure_leaves_input_and_no_stamp(self):
        with tempfile.TemporaryDirectory(dir='/tmp') as directory:
            path = Path(directory) / 'object.o'
            stamp = Path(directory) / 'output.stamp'
            path.write_bytes(b'not an ELF object')
            with contextlib.redirect_stderr(io.StringIO()), self.assertRaises(SystemExit):
                fixer.main([str(path), str(stamp)])
            self.assertEqual(path.read_bytes(), b'not an ELF object')
            self.assertFalse(stamp.exists())
            self.assertEqual([p.name for p in Path(directory).iterdir()], ['object.o'])


if __name__ == '__main__':
    unittest.main()
