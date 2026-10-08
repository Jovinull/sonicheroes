"""Exercise atom relocation with generated ELF data, never a retail fixture."""

import hashlib
import struct
import unittest
from unittest.mock import patch

from tools import fix_c_colli_react_object as fixer


def fixture():
    names = ["", ".text", ".data", ".symtab", ".strtab", ".rela.text", ".rela.data", ".shstrtab"]
    shstrings = b"\0"
    name_offsets = {"": 0}
    for name in names[1:]:
        name_offsets[name] = len(shstrings)
        shstrings += name.encode() + b"\0"
    strings = b"\0"
    symbols = [bytes(16), struct.pack(">IIIBBH", 0, 0, 0, 3, 0, 1)]
    position = 0
    for index, size in enumerate([28] + [80] * 41 + [84]):
        name = fixer.ATOM_NAME if index == 0 else f"generated_{index}"
        symbols.append(struct.pack(">IIIBBH", len(strings), position, size, 0x22 if index == 0 else 0x12, 0, 1))
        strings += name.encode() + b"\0"
        position += size
    text = b"".join(struct.pack(">I", (14 << 26) | (3 << 21) | (3 << 16) | i) for i in range(848))
    rela_text = struct.pack(">IIiIIi", 28, (2 << 8) | 1, 0, 32, (1 << 8) | 1, 40)
    rela_data = struct.pack(">IIiIIiIIi", 0, (2 << 8) | 1, 4, 4, (1 << 8) | 1, 12, 8, (1 << 8) | 1, 100)
    payloads = [b"", text, b"synthetic-data!!", b"".join(symbols), strings, rela_text, rela_data, shstrings]
    kinds = [0, 1, 1, 2, 3, 4, 4, 3]
    data = bytearray(52)
    offsets = {}
    headers = []
    for index, payload in enumerate(payloads):
        data.extend(bytes((-len(data)) % 4))
        offsets[names[index]] = len(data)
        headers.append((name_offsets[names[index]], kinds[index], 6 if index == 1 else 0, 0, len(data), len(payload), 4 if index == 3 else 3 if index in (5, 6) else 0, 1 if index == 5 else 2 if index == 6 else 0, 4, 16 if index == 3 else 12 if index in (5, 6) else 0))
        data.extend(payload)
    data.extend(bytes((-len(data)) % 4))
    shoff = len(data)
    for header in headers:
        data.extend(struct.pack(">10I", *header))
    ident = b"\x7fELF\x01\x02\x01" + bytes(9)
    struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, ident, 1, 20, 1, 0, 0, shoff, 0, 52, 0, 0, 40, len(headers), 7)
    return bytes(data), offsets


class AtomMovementTests(unittest.TestCase):
    def setUp(self):
        self.blob, self.offsets = fixture()
        self.allow_text(self.blob)

    def allow_text(self, blob):
        start = self.offsets[".text"]
        text = blob[start:start + fixer.TEXT_SIZE]
        expected = text[fixer.ATOM_SIZE:] + text[:fixer.ATOM_SIZE]
        for name, value in (("INPUT_TEXT_SHA256", text), ("OUTPUT_TEXT_SHA256", expected)):
            mock = patch.object(fixer, name, hashlib.sha256(value).hexdigest())
            mock.start()
            self.addCleanup(mock.stop)

    def test_preserves_every_body_and_other_payloads(self):
        result = fixer.normalize(self.blob)
        self.assertEqual(len(result), len(self.blob))
        table, text = self.offsets[".symtab"], self.offsets[".text"]
        for index in range(2, 45):
            before = struct.unpack_from(">IIIBBH", self.blob, table + 16 * index)
            after = struct.unpack_from(">IIIBBH", result, table + 16 * index)
            self.assertEqual(before[:1] + before[2:], after[:1] + after[2:])
            self.assertEqual(after[1], before[1] + 3364 if index == 2 else before[1] - 28)
            self.assertEqual(self.blob[text + before[1]:text + before[1] + before[2]], result[text + after[1]:text + after[1] + after[2]])
        for name, end in ((".data", ".symtab"), (".strtab", ".rela.text"), (".shstrtab", None)):
            self.assertEqual(self.blob[self.offsets[name]:self.offsets[end] if end else None], result[self.offsets[name]:self.offsets[end] if end else None])

    def test_rebases_locations_and_section_addends(self):
        result = fixer.normalize(self.blob)
        self.assertEqual(struct.unpack_from(">IIiIIi", result, self.offsets[".rela.text"]), (0, 513, 0, 4, 257, 12))
        self.assertEqual(struct.unpack_from(">IIiIIiIIi", result, self.offsets[".rela.data"]), (0, 513, 4, 4, 257, 3376, 8, 257, 72))

    def test_idempotent(self):
        result = fixer.normalize(self.blob)
        self.assertEqual(fixer.normalize(result), result)

    def test_corrupt_text_rejected(self):
        bad = bytearray(self.blob)
        bad[self.offsets[".text"] + 100] ^= 1
        with self.assertRaisesRegex(ValueError, "input text hash"):
            fixer.normalize(bad)

    def test_cross_atom_branch_rejected_even_with_known_hash(self):
        bad = bytearray(self.blob)
        struct.pack_into(">I", bad, self.offsets[".text"], (18 << 26) | 28)
        self.allow_text(bad)
        with self.assertRaisesRegex(ValueError, "branch crosses atom"):
            fixer.normalize(bad)

    def test_relocation_inside_moved_atom_rejected(self):
        bad = bytearray(self.blob)
        struct.pack_into(">I", bad, self.offsets[".rela.text"], 0)
        with self.assertRaisesRegex(ValueError, "inline atom unexpectedly has a relocation"):
            fixer.normalize(bad)

    def test_section_reference_out_of_bounds_rejected(self):
        bad = bytearray(self.blob)
        struct.pack_into(">i", bad, self.offsets[".rela.data"] + 20, fixer.TEXT_SIZE)
        with self.assertRaisesRegex(ValueError, "outside section"):
            fixer.normalize(bad)


if __name__ == "__main__":
    unittest.main()
