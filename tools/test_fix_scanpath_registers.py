"""Synthetic ELF tests for the bounded angle-register normalization."""

import contextlib
import hashlib
import io
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from tools import fix_scanpath_registers as fixer


def fixture():
    names = ["", ".text", ".data", ".symtab", ".strtab", ".rela.text", ".shstrtab"]
    name_offsets = {}
    shstrings = b""
    for name in names:
        name_offsets[name] = len(shstrings)
        shstrings += name.encode() + b"\0"
    strings = b"\0"
    symbols = [bytes(16)]
    symbols.append(struct.pack(">IIIBBH", len(strings), fixer.FUNCTION_OFFSET, fixer.FUNCTION_SIZE, 0x02, 0, 1))
    strings += fixer.FUNCTION_NAME.encode() + b"\0"
    target_ids = {}
    for _, _, name, _ in fixer.EXPECTED_RELOCATIONS:
        if name not in target_ids:
            target_ids[name] = len(symbols)
            symbols.append(struct.pack(">IIIBBH", len(strings), 0, 0, 0x10, 0, 0))
            strings += name.encode() + b"\0"
    text = bytearray()
    for i in range(fixer.TEXT_SIZE // 4):
        text += struct.pack(">I", (14 << 26) | (3 << 21) | (3 << 16) | (i & 0xFFFF))
    # Instructions synthesized from field definitions, not retail word literals.
    for offset in fixer.FIELDS:
        if offset == 0x128:
            word = (31 << 26) | (4 << 21) | (27 << 16) | (4 << 11) | (444 << 1)
        else:
            word = (42 << 26) | (4 << 21) | (31 << 16)
        struct.pack_into(">I", text, fixer.FUNCTION_OFFSET + offset, word)
    rels = b"".join(struct.pack(">IIi", fixer.FUNCTION_OFFSET + offset, (target_ids[name] << 8) | kind, addend) for offset, kind, name, addend in fixer.EXPECTED_RELOCATIONS)
    payloads = [b"", text, b"untouched data!!", b"".join(symbols), strings, rels, shstrings]
    kinds = [0, 1, 1, 2, 3, 4, 3]
    data = bytearray(52)
    headers = []
    offsets = {}
    for index, payload in enumerate(payloads):
        data.extend(bytes(-len(data) % 4))
        offsets[names[index]] = len(data)
        headers.append((name_offsets[names[index]], kinds[index], 6 if index == 1 else 3 if index == 2 else 0, 0, len(data), len(payload), 4 if index == 3 else 3 if index == 5 else 0, 1 if index == 5 else 0, 4, 16 if index == 3 else 12 if index == 5 else 0))
        data.extend(payload)
    data.extend(bytes(-len(data) % 4))
    shoff = len(data)
    for header in headers:
        data.extend(struct.pack(">10I", *header))
    struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, b"\x7fELF\x01\x02\x01" + bytes(9), 1, 20, 1, 0, 0, shoff, 0, 52, 0, 0, 40, len(headers), 6)
    return bytes(data), offsets


class RegisterNormalizationTests(unittest.TestCase):
    def setUp(self):
        self.blob, self.offsets = fixture()
        self.original_text = self.blob[self.offsets[".text"]:self.offsets[".text"] + fixer.TEXT_SIZE]
        # Independently compute expected output by applying the register
        # index delta in each field. No production-normalize call as oracle.
        expected = bytearray(self.original_text)
        for offset, fields in fixer.FIELDS.items():
            at = fixer.FUNCTION_OFFSET + offset
            word = struct.unpack_from(">I", expected, at)[0]
            struct.pack_into(">I", expected, at, word + sum((new - old) << shift for shift, (old, new) in fields.items()))
        self.expected_text = bytes(expected)
        self.hashes = {
            "INPUT_TEXT_SHA256": hashlib.sha256(self.original_text).hexdigest(),
            "OUTPUT_TEXT_SHA256": hashlib.sha256(expected).hexdigest(),
            "INPUT_FUNCTION_SHA256": hashlib.sha256(self.original_text[fixer.FUNCTION_OFFSET:fixer.FUNCTION_OFFSET + fixer.FUNCTION_SIZE]).hexdigest(),
            "OUTPUT_FUNCTION_SHA256": hashlib.sha256(expected[fixer.FUNCTION_OFFSET:fixer.FUNCTION_OFFSET + fixer.FUNCTION_SIZE]).hexdigest(),
        }
        self.patcher = patch.multiple(fixer, **self.hashes)
        self.patcher.start()
        self.addCleanup(self.patcher.stop)

    def test_only_four_fields_change_and_second_application_is_noop(self):
        out = fixer.normalize(self.blob)
        expected = bytearray(self.blob)
        start = self.offsets[".text"]
        expected[start:start + fixer.TEXT_SIZE] = self.expected_text
        self.assertEqual(out, expected)
        self.assertEqual(fixer.normalize(out), out)
        self.assertEqual(sum(a != b for a, b in zip(self.blob, out)), 5)

    def test_instruction_corruption_is_rejected(self):
        for offset in (0, fixer.FUNCTION_OFFSET, fixer.FUNCTION_OFFSET + 0x11C):
            bad = bytearray(self.blob)
            bad[self.offsets[".text"] + offset] ^= 1
            with self.assertRaisesRegex(ValueError, "whole-text hash"):
                fixer.normalize(bad)

    def test_boundary_and_binding_are_guarded(self):
        for field_offset, value in ((4, fixer.FUNCTION_OFFSET + 4), (8, fixer.FUNCTION_SIZE - 4)):
            bad = bytearray(self.blob)
            struct.pack_into(">I", bad, self.offsets[".symtab"] + 16 + field_offset, value)
            with self.assertRaisesRegex(ValueError, "boundary"):
                fixer.normalize(bad)
        bad = bytearray(self.blob)
        bad[self.offsets[".symtab"] + 16 + 12] = 0x22
        with self.assertRaisesRegex(ValueError, "binding"):
            fixer.normalize(bad)

    def test_relocation_site_type_target_and_addend_are_guarded(self):
        for field, value in ((0, fixer.FUNCTION_OFFSET + 0x11C), (4, (2 << 8) | 1), (4, (3 << 8) | 10), (8, 4)):
            bad = bytearray(self.blob)
            struct.pack_into(">I", bad, self.offsets[".rela.text"] + field, value)
            with self.assertRaisesRegex(ValueError, "relocations"):
                fixer.normalize(bad)
        out = bytearray(fixer.normalize(self.blob))
        struct.pack_into(">I", out, self.offsets[".rela.text"], fixer.FUNCTION_OFFSET + 0x11C)
        with self.assertRaisesRegex(ValueError, "relocations"):
            fixer.normalize(out)

    def test_malformed_input_is_rejected(self):
        for bad in (b"", self.blob[:51], self.blob[:-1]):
            with self.assertRaises(ValueError):
                fixer.normalize(bad)

    def test_cli_failure_does_not_write_object_or_stamp(self):
        with tempfile.TemporaryDirectory(prefix="scanpath-register-test-", dir="/tmp") as td:
            obj, stamp = Path(td) / "sample.o", Path(td) / "success.stamp"
            bad = bytearray(self.blob)
            bad[self.offsets[".text"]] ^= 1
            obj.write_bytes(bad)
            with contextlib.redirect_stderr(io.StringIO()), self.assertRaises(SystemExit):
                fixer.main([str(obj), str(stamp)])
            self.assertEqual(obj.read_bytes(), bad)
            self.assertFalse(stamp.exists())
            obj.write_bytes(self.blob)
            fixer.main([str(obj), str(stamp)])
            self.assertTrue(stamp.exists())
            self.assertEqual(obj.read_bytes(), fixer.normalize(self.blob))
            fixer.main([str(obj), str(stamp)])
            self.assertEqual(sorted(p.name for p in Path(td).iterdir()), ["sample.o", "success.stamp"])


if __name__ == "__main__":
    unittest.main()
