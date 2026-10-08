"""Regression coverage for removing the compiler's temporary bias sections."""

import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from tools.fix_fn_8005438C_object import ANCHOR_SYMBOL, BIAS_SYMBOL


class RemovedSectionSymbolsTest(unittest.TestCase):
    def test_removed_sections_leave_valid_symbols_and_relocations(self):
        names = ["", ".text", ".sdata", ".sdata2", ".rela.text", ".rela.sdata",
                 ".symtab", ".strtab", ".shstrtab"]
        section_names = b"\0"
        name_offsets = [0]
        for name in names[1:]:
            name_offsets.append(len(section_names))
            section_names += name.encode() + b"\0"
        strings = b"\0private_bias\0" + ANCHOR_SYMBOL.encode() + b"\0" + BIAS_SYMBOL.encode() + b"\0"
        symbol = struct.Struct(">IIIBBH")
        # Null; three section symbols; private bias; anchor; external shared bias.
        symbols = b"".join(symbol.pack(*entry) for entry in [
            (0, 0, 0, 0, 0, 0),
            (0, 0, 0, 3, 0, 1),
            (0, 0, 0, 3, 0, 2),
            (0, 0, 0, 3, 0, 3),
            (strings.index(b"private_bias"), 0, 8, 1, 0, 3),
            (strings.index(ANCHOR_SYMBOL.encode()), 0, 4, 0x11, 0, 2),
            (strings.index(BIAS_SYMBOL.encode()), 0, 0, 0x10, 0, 0),
        ])
        text = bytes(range(12))  # Synthetic payload, never retail instructions.
        payloads = [b"", text, bytes(4), bytes(8),
                    struct.pack(">IIi", 0, (4 << 8) | 109, 0),
                    struct.pack(">IIi", 0, (6 << 8) | 1, 0),
                    symbols, strings, section_names]
        blob = bytearray(52)
        sections = []
        for index, payload in enumerate(payloads):
            blob.extend(bytes((-len(blob)) % 4))
            offset = len(blob)
            blob.extend(payload)
            kind = 0 if index == 0 else 4 if index in (4, 5) else 2 if index == 6 else 3 if index in (7, 8) else 1
            link = 6 if index in (4, 5) else 7 if index == 6 else 0
            info = 1 if index == 4 else 2 if index == 5 else 5 if index == 6 else 0
            entsize = 12 if index in (4, 5) else 16 if index == 6 else 0
            sections.append([name_offsets[index], kind, 0, 0, offset, len(payload), link, info, 4, entsize])
        blob.extend(bytes((-len(blob)) % 4))
        shoff = len(blob)
        for section in sections:
            blob.extend(struct.pack(">10I", *section))
        struct.pack_into(">16sHHIIIIIHHHHHH", blob, 0,
                         b"\x7fELF\x01\x02\x01" + bytes(9), 1, 20, 1, 0, 0,
                         shoff, 0, 52, 0, 0, 40, len(sections), 8)
        with tempfile.TemporaryDirectory(dir="/tmp") as scratch:
            obj, stamp = Path(scratch) / "test.o", Path(scratch) / "test.stamp"
            obj.write_bytes(blob)
            subprocess.run([sys.executable, str(Path(__file__).with_name("fix_fn_8005438C_object.py")),
                            str(obj), str(stamp)], check=True)
            result = obj.read_bytes()
            self.assertTrue(stamp.exists())
        header = struct.unpack_from(">16sHHIIIIIHHHHHH", result)
        self.assertEqual(header[12], 6)
        kept = [struct.unpack_from(">10I", result, shoff + i * 40) for i in range(header[12])]
        self.assertEqual(result[sections[1][4]:sections[1][4] + len(text)], text)
        rewritten = [symbol.unpack_from(result, sections[6][4] + i * 16) for i in range(7)]
        self.assertEqual(rewritten[1][3:6], (3, 0, 1))  # Retained .text section.
        for entry in rewritten[2:6]:
            self.assertEqual(entry[3] & 15, 0)
            self.assertEqual(entry[5], 0xFFF1)
        self.assertEqual(rewritten[6], symbol.unpack_from(symbols, 6 * 16))
        self.assertEqual(struct.unpack_from(">IIi", result, kept[2][4]), (0, (6 << 8) | 109, 0))
        self.assertEqual(kept[2][6:8], (3, 1))  # Relocation links remapped.
        self.assertEqual(kept[3][6:8], (4, 6))  # String table and local/global boundary.


if __name__ == "__main__":
    unittest.main()
