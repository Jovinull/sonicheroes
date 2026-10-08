"""Synthetic ELF tests for the permitted scalar-only mutation boundary."""
import io
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

from tools import fix_miscs_object as fix

try:  # an independent reader when available; the step itself is stdlib-only
    from elftools.elf.elffile import ELFFile
except ImportError:
    ELFFile = fix.ELFFile


def fixture():
    names = ["", ".text", ".sdata2", ".bss", ".symtab", ".strtab", ".rela.text", ".shstrtab"]
    strings = b"\0" + b"\0".join((f"atom{i}".encode() for i in range(12))) + b"\0"
    strings += b"leaf\0"
    string_offsets = [strings.index(f"atom{i}".encode()) for i in range(12)]
    symbols = bytes(16)
    for i, (old, new, size) in enumerate(fix.ATOMS):
        symbols += struct.pack(">IIIBBH", string_offsets[i], old, size, 1, 0, 2)
    symbols += struct.pack(">IIIBBH", strings.index(b"leaf"), 12, 4, 2, 0, 1)
    relocs = struct.pack(">IIi", 0, (5 << 8) | 109, 0) + struct.pack(">IIi", 4, (10 << 8) | 109, 0)
    sections = [b"", bytes(range(16)), bytes(range(64)), b"", symbols, strings, relocs,
                b"\0".join(n.encode() for n in names) + b"\0"]
    shstr = sections[-1]
    output = bytearray(52)
    headers = []
    offsets = {}
    types = [0, 1, 1, 8, 2, 3, 4, 3]
    for i, (name, payload) in enumerate(zip(names, sections)):
        output += bytes((-len(output)) % 8)
        offset = len(output)
        offsets[name] = offset
        output += payload
        headers.append((shstr.index(name.encode()) if name else 0, types[i],
                        6 if i == 1 else 3 if i in (2, 3) else 0, 0, offset,
                        8 if i == 3 else len(payload), 5 if i == 4 else 4 if i == 6 else 0,
                        1 if i in (4, 6) else 0, 8 if i in (2, 3) else 4,
                        16 if i == 4 else 12 if i == 6 else 0))
    shoff = len(output)
    for row in headers:
        output += struct.pack(">10I", *row)
    output[:16] = b"\x7fELF\x01\x02\x01" + bytes(9)
    struct.pack_into(">HHIIIIIHHHHHH", output, 16, 1, 20, 1, 0, 0, shoff, 0, 52, 0, 0, 40, 8, 7)
    pool = sections[2]
    contract = {
        "INPUT_HASH": fix.digest(pool),
        "OUTPUT_HASH": fix.digest(pool[:24] + pool[52:56] + pool[48:52] + pool[24:48] + pool[56:64]),
        "ALLOCATED": {".text": (16, fix.digest(sections[1])), ".sdata2": (64, None), ".bss": (8, None)},
        "SECTION_METADATA": {".text": (6, 4), ".sdata2": (3, 8), ".bss": (3, 8)},
        "FUNCTIONS": {"leaf": (12, 4)},
        "TOTAL_RELOCATIONS": 2,
        "POOL_REFERENCES": 2,
        "RELOCATION_HASH": fix.digest(json.dumps([
            [".text", 0, 109, [".sdata2", 24]],
            [".text", 4, 109, [".sdata2", 52]],
        ], separators=(",", ":")).encode()),
    }
    return bytes(output), offsets, contract


class NormalizeTests(unittest.TestCase):
    def setUp(self):
        self.raw, self.offsets, contract = fixture()
        self.guard = patch.multiple(fix, **contract)
        self.guard.start()
        self.addCleanup(self.guard.stop)

    def test_permutation_and_only_allowed_mutations(self):
        output = fix.normalize(self.raw)
        pool = self.offsets[".sdata2"]
        table = self.offsets[".symtab"]
        allowed = set(range(pool, pool + 64))
        for i, (old, new, size) in enumerate(fix.ATOMS, 1):
            if old != new:
                allowed.update(range(table + i * 16 + 4, table + i * 16 + 8))
            self.assertEqual(struct.unpack_from(">I", output, table + i * 16 + 4)[0], new)
            self.assertEqual(output[pool + new:pool + new + size], self.raw[pool + old:pool + old + size])
        self.assertEqual(len(self.raw), len(output))
        self.assertTrue(all(a == b or i in allowed for i, (a, b) in enumerate(zip(self.raw, output))))
        self.assertEqual(output[pool + 12:pool + 16], self.raw[pool + 12:pool + 16])
        self.assertEqual(fix.normalize(output), output)

    def test_relocation_meaning_follows_moved_literal(self):
        output = fix.normalize(self.raw)
        for blob in (self.raw, output):
            elf = ELFFile(io.BytesIO(blob))
            syms = elf.get_section_by_name(".symtab")
            pool = elf.get_section_by_name(".sdata2").data()
            values = []
            for rel in elf.get_section_by_name(".rela.text").iter_relocations():
                sym = syms.get_symbol(rel["r_info_sym"])
                pos = sym["st_value"] + rel["r_addend"]
                values.append(pool[pos:pos + sym["st_size"]])
            self.assertEqual(values, [bytes(range(24, 28)), bytes(range(52, 56))])

    def test_rejects_corruption_before_write(self):
        for offset in (0, self.offsets[".text"], self.offsets[".sdata2"],
                       self.offsets[".symtab"] + 16 + 8,
                       self.offsets[".rela.text"] + 7,
                       self.offsets[".symtab"] + 13 * 16 + 7,
                       struct.unpack_from(">I", self.raw, 32)[0] + 40 + 35):
            damaged = bytearray(self.raw)
            damaged[offset] ^= 1
            with self.subTest(offset=offset), tempfile.TemporaryDirectory(dir="/tmp") as directory:
                path = Path(directory) / "input.o"
                path.write_bytes(damaged)
                with self.assertRaises(ValueError):
                    fix.fix(path)
                self.assertEqual(path.read_bytes(), damaged)
                self.assertEqual(list(Path(directory).iterdir()), [path])

    def test_rejects_partial_normalization_and_nonzero_addend(self):
        output = bytearray(fix.normalize(self.raw))
        table = self.offsets[".symtab"]
        struct.pack_into(">I", output, table + 5 * 16 + 4, 24)
        with self.assertRaises(ValueError):
            fix.normalize(bytes(output))
        output = bytearray(self.raw)
        struct.pack_into(">i", output, self.offsets[".rela.text"] + 8, 1)
        with self.assertRaises(ValueError):
            fix.normalize(bytes(output))

    def test_atomic_replace_failure_and_success(self):
        with tempfile.TemporaryDirectory(dir="/tmp") as directory:
            path = Path(directory) / "input.o"
            path.write_bytes(self.raw)
            path.chmod(0o640)
            with patch.object(fix.os, "replace", side_effect=OSError("simulated failure")):
                with self.assertRaises(OSError):
                    fix.fix(path)
            self.assertEqual(path.read_bytes(), self.raw)
            self.assertEqual(list(Path(directory).iterdir()), [path])
            self.assertTrue(fix.fix(path))
            self.assertEqual(path.stat().st_mode & 0o777, 0o640)
            self.assertFalse(fix.fix(path))

    def test_cli_stamp_only_after_success(self):
        with tempfile.TemporaryDirectory(dir="/tmp") as directory:
            path = Path(directory) / "input.o"
            stamp = Path(directory) / "new" / "output.stamp"
            path.write_bytes(b"malformed")
            with patch.object(sys, "argv", ["fix_miscs_object.py", str(path), str(stamp)]):
                with patch.object(sys, "stderr", io.StringIO()), self.assertRaises(SystemExit):
                    fix.main()
            self.assertFalse(stamp.exists())
            self.assertEqual(path.read_bytes(), b"malformed")
            path.write_bytes(self.raw)
            with patch.object(sys, "argv", ["fix_miscs_object.py", str(path), str(stamp)]):
                with patch("builtins.print"):
                    fix.main()
                    fix.main()
            self.assertTrue(stamp.exists())
            self.assertEqual(path.read_bytes(), fix.normalize(self.raw))

    def test_truncated_file_rejected(self):
        for size in (0, 16, 51, len(self.raw) - 1):
            with self.subTest(size=size), self.assertRaises(ValueError):
                fix.normalize(self.raw[:size])


if __name__ == "__main__":
    unittest.main()
