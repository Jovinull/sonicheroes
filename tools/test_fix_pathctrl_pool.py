"""Synthetic ELF coverage for the path-control pool's mutation boundary."""
import io
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from tools import fix_pathctrl_pool as fixer


def fixture():
    names = ['', '.text', '.sdata2', '.symtab', '.strtab', '.rela.text', '.shstrtab']
    strings = b'\0'
    symbols = [bytes(16), struct.pack('>IIIBBH', 0, 0, 0, 3, 0, 2)]
    atoms = sorted(fixer.MOVED_SYMBOLS, key=lambda n: fixer.MOVED_SYMBOLS[n][0])
    atoms.append('lbl_8042DC5C')
    for i, name in enumerate(atoms):
        symbols.append(struct.pack('>IIIBBH', len(strings), i * 4, 4,
                                   1 if i == 0 else 17, 0, 2))
        strings += name.encode() + b'\0'
    pool = bytes(range(56))
    text = bytes([0xA5]) * (36 * 4)
    relocs = b''.join(struct.pack('>IIi', i * 4, ((2 + i % 14) << 8) | 109, 0)
                      for i in range(36))
    shstrings = b''
    name_offsets = {}
    for name in names:
        name_offsets[name] = len(shstrings)
        shstrings += name.encode() + b'\0'
    payloads = [b'', text, pool, b''.join(symbols), strings, relocs, shstrings]
    kinds = [0, 1, 1, 2, 3, 4, 3]
    blob, headers, offsets = bytearray(52), [], {}
    for i, payload in enumerate(payloads):
        blob.extend(bytes(-len(blob) % 8))
        offsets[names[i]] = len(blob)
        headers.append((name_offsets[names[i]], kinds[i], 6 if i == 1 else 3 if i == 2 else 0,
                        0, len(blob), len(payload), 4 if i == 3 else 3 if i == 5 else 0,
                        1 if i == 5 else 0, 8, 16 if i == 3 else 12 if i == 5 else 0))
        blob.extend(payload)
    blob.extend(bytes(-len(blob) % 8))
    offsets['headers'] = len(blob)
    for header in headers:
        blob.extend(struct.pack('>10I', *header))
    struct.pack_into('>16sHHIIIIIHHHHHH', blob, 0, b'\x7fELF\x01\x02\x01' + bytes(9),
                     1, 20, 1, 0, 0, offsets['headers'], 0, 52, 0, 0, 40, len(headers), 6)
    expected = bytearray(blob)
    order = list(range(1, 13)) + [0, 13]
    at = offsets['.sdata2']
    expected[at:at + 56] = b''.join(pool[i * 4:i * 4 + 4] for i in order)
    for new, old in enumerate(order):
        struct.pack_into('>I', expected, offsets['.symtab'] + (old + 2) * 16 + 4, new * 4)
    return bytes(blob), bytes(expected), offsets


class PathctrlPoolTests(unittest.TestCase):
    def setUp(self):
        self.raw, self.expected, self.at = fixture()
        start = self.at['.sdata2']
        self.guard = patch.multiple(
            fixer, INPUT_SHA256=fixer.digest(self.raw), OUTPUT_SHA256=fixer.digest(self.expected),
            INPUT_POOL_SHA256=fixer.digest(self.raw[start:start + 56]),
            OUTPUT_POOL_SHA256=fixer.digest(self.expected[start:start + 56]))
        self.guard.start()
        self.addCleanup(self.guard.stop)

    def reject_shape(self, data, reason):
        with patch.object(fixer, 'INPUT_SHA256', fixer.digest(data)):
            with self.assertRaisesRegex(ValueError, reason):
                fixer.normalize(data)

    def test_exact_output_and_idempotence(self):
        self.assertEqual(fixer.normalize(self.raw), self.expected)
        self.assertEqual(fixer.normalize(self.expected), self.expected)

    def test_only_pool_and_moved_symbol_values_change(self):
        output = fixer.normalize(self.raw)
        allowed = set(range(self.at['.sdata2'], self.at['.sdata2'] + 52))
        for i in range(2, 15):
            allowed.update(range(self.at['.symtab'] + i * 16 + 4,
                                 self.at['.symtab'] + i * 16 + 8))
        self.assertEqual(len(output), len(self.raw))
        self.assertTrue(all(i in allowed for i, (a, b) in enumerate(zip(self.raw, output)) if a != b))
        for section, size in [('.text', 144), ('.rela.text', 432)]:
            at = self.at[section]
            self.assertEqual(output[at:at + size], self.raw[at:at + size])

    def test_every_reference_keeps_its_scalar_bytes(self):
        output = fixer.normalize(self.raw)
        for i in range(36):
            _, info, addend = struct.unpack_from('>IIi', self.raw, self.at['.rela.text'] + i * 12)
            pos = self.at['.symtab'] + (info >> 8) * 16
            old, size = struct.unpack_from('>II', self.raw, pos + 4)
            new = struct.unpack_from('>I', output, pos + 4)[0]
            pool = self.at['.sdata2']
            self.assertEqual(self.raw[pool + old + addend:pool + old + size],
                             output[pool + new + addend:pool + new + size])

    def test_changed_code_or_pool_rejected(self):
        for section in ['.text', '.sdata2']:
            changed = bytearray(self.raw)
            changed[self.at[section]] ^= 1
            with self.assertRaisesRegex(ValueError, 'whole-object'):
                fixer.normalize(changed)
        self.reject_shape(changed, 'pool hash')

    def test_bad_header_and_overlap_rejected(self):
        self.reject_shape(b'fake', 'truncated ELF')
        data = bytearray(self.raw)
        data[5] = 1
        self.reject_shape(data, 'PowerPC')
        data = bytearray(self.raw)
        struct.pack_into('>I', data, self.at['headers'] + 2 * 40 + 16, self.at['.text'])
        self.reject_shape(data, 'overlapping ELF')

    def test_symbol_and_relocation_shape_rejected(self):
        for offset, value, fmt, reason in [
            (self.at['.symtab'] + 2 * 16 + 12, 33, '>B', 'pool atom'),
            (self.at['.symtab'] + 2 * 16 + 8, 8, '>I', 'pool atom'),
            (self.at['.rela.text'] + 4, (1 << 8) | 109, '>I', 'pool reference'),
            (self.at['.rela.text'] + 8, 4, '>i', 'pool reference'),
        ]:
            data = bytearray(self.raw)
            struct.pack_into(fmt, data, offset, value)
            self.reject_shape(data, reason)

    def test_cli_atomic_write_failure_and_stamp(self):
        with tempfile.TemporaryDirectory(dir='/tmp') as directory:
            path, stamp = Path(directory) / 'object.o', Path(directory) / 'done'
            path.write_bytes(self.raw)
            path.chmod(0o640)
            with patch.object(fixer.os, 'replace', side_effect=OSError('test failure')):
                with self.assertRaises(OSError):
                    fixer.main([str(path), str(stamp)])
            self.assertEqual(path.read_bytes(), self.raw)
            self.assertEqual(list(Path(directory).iterdir()), [path])
            fixer.main([str(path), str(stamp)])
            self.assertEqual(path.read_bytes(), self.expected)
            self.assertEqual(path.stat().st_mode & 0o777, 0o640)
            self.assertTrue(stamp.exists())
            fixer.main([str(path), str(stamp)])
            self.assertEqual(path.read_bytes(), self.expected)

    def test_failed_validation_leaves_file_and_stamp_untouched(self):
        with tempfile.TemporaryDirectory(dir='/tmp') as directory:
            path, stamp = Path(directory) / 'object.o', Path(directory) / 'done'
            path.write_bytes(b'invalid')
            with patch('sys.stderr', io.StringIO()), self.assertRaises(SystemExit):
                fixer.main([str(path), str(stamp)])
            self.assertEqual(path.read_bytes(), b'invalid')
            self.assertFalse(stamp.exists())
            self.assertEqual(list(Path(directory).iterdir()), [path])


if __name__ == '__main__':
    unittest.main()
