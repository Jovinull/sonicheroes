"""Exercise native symbol binding, collision guards and atomic rejection."""

import os
import struct
import subprocess
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import fix_sp_dashpanel_symbols as fix


def elf_fixture(defined_source=False, defined_target=False):
    names = [""] + list(fix.ALIASES)
    if defined_target:
        names.append(next(iter(fix.ALIASES.values())))
    strings = bytearray()
    offsets = []
    for name in names:
        offsets.append(len(strings))
        strings.extend(name.encode() + b"\0")
    symbols = b"".join(
        struct.pack(
            ">IIIBBH", offset, 0, 0, 0 if i == 0 else 0x12, 0,
            1 if (defined_source and i == 1) or (defined_target and i == len(names) - 1) else 0,
        )
        for i, offset in enumerate(offsets)
    )
    section_names = b"\0.text\0.symtab\0.strtab\0.rela.text\0.shstrtab\0"
    payloads = [b"", bytes(20), symbols, bytes(strings), b"".join(
        struct.pack(">IIi", 4 * i, ((i + 1) << 8) | 10, 0) for i in range(5)
    ), section_names]
    metadata = [(0, 0, 0, 0, 0, 0, 0), (1, 1, 6, 0, 0, 4, 0),
                (7, 2, 0, 3, 1, 4, 16), (15, 3, 0, 0, 0, 1, 0),
                (23, 4, 0, 2, 1, 4, 12), (34, 3, 0, 0, 0, 1, 0)]
    data = bytearray(52)
    sections = []
    for contents, (name, kind, flags, link, info, alignment, size) in zip(payloads, metadata):
        data.extend(bytes((-len(data)) % 4))
        sections.append((name, kind, flags, 0, len(data), len(contents), link, info, alignment, size))
        data.extend(contents)
    data.extend(bytes((-len(data)) % 4))
    section_offset = len(data)
    for section in sections:
        data.extend(struct.pack(">10I", *section))
    struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, b"\x7fELF\x01\x02\x01" + bytes(9),
                     1, 20, 1, 0, 0, section_offset, 0, 52, 0, 0, 40, 6, 5)
    return bytes(data)


class SymbolBindingTests(unittest.TestCase):
    def setUp(self):
        self.scratch = tempfile.TemporaryDirectory(dir="/tmp", prefix="dashpanel-symbol-test-")
        self.addCleanup(self.scratch.cleanup)
        self.path = Path(self.scratch.name) / "test.o"
        self.objcopy = Path(__file__).resolve().parents[1] / "build/binutils/powerpc-eabi-objcopy"
        if not self.objcopy.exists():
            self.skipTest("PowerPC binutils is not installed")
        self.path.write_bytes(elf_fixture())
        os.utime(self.path, ns=(1_000_000_000, 2_000_000_000))

    def test_binding_preserves_bytes_relocations_and_idempotent_timestamp(self):
        before, _, relocations = fix.inspect(self.path)
        fix.bind_symbols(self.path, self.objcopy)
        after, symbols, new_relocations = fix.inspect(self.path)
        self.assertEqual(before, after)
        self.assertEqual(relocations, new_relocations)
        self.assertTrue(all(symbols.get(name) == 0 for name in fix.ALIASES.values()))
        first = self.path.read_bytes()
        modified = self.path.stat().st_mtime_ns
        fix.bind_symbols(self.path, self.objcopy)
        self.assertEqual(first, self.path.read_bytes())
        self.assertEqual(modified, self.path.stat().st_mtime_ns)

    def test_defined_source_is_rejected(self):
        self.path.write_bytes(elf_fixture(defined_source=True))
        original = self.path.read_bytes()
        with self.assertRaisesRegex(ValueError, "defined symbol"):
            fix.bind_symbols(self.path, self.objcopy)
        self.assertEqual(original, self.path.read_bytes())

    def test_defined_target_is_rejected(self):
        self.path.write_bytes(elf_fixture(defined_target=True))
        original = self.path.read_bytes()
        with self.assertRaisesRegex(ValueError, "already defined"):
            fix.bind_symbols(self.path, self.objcopy)
        self.assertEqual(original, self.path.read_bytes())

    def reject_corruption(self, relocation):
        original = self.path.read_bytes()
        run = subprocess.run

        def corrupt(command, **kwargs):
            result = run(command, **kwargs)
            output = Path(command[-1])
            data = bytearray(output.read_bytes())
            shoff = struct.unpack_from(">I", data, 32)[0]
            section = struct.unpack_from(">10I", data, shoff + 40 * (4 if relocation else 1))
            if relocation:
                old = struct.unpack_from(">I", data, section[4] + 4)[0]
                struct.pack_into(">I", data, section[4] + 4, old + 0x100)
            else:
                data[section[4]] ^= 1
            output.write_bytes(data)
            return result

        with patch.object(fix.subprocess, "run", side_effect=corrupt):
            with self.assertRaisesRegex(ValueError, "section bytes or relocation referents"):
                fix.bind_symbols(self.path, self.objcopy)
        self.assertEqual(original, self.path.read_bytes())
        self.assertEqual(list(self.path.parent.iterdir()), [self.path])

    def test_relocation_retargeting_is_rejected_atomically(self):
        self.reject_corruption(True)

    def test_payload_change_is_rejected_atomically(self):
        self.reject_corruption(False)


if __name__ == "__main__":
    unittest.main()
