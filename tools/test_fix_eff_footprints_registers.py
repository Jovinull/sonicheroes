"""Synthetic ELF tests for the bounded footprints-register normalization."""

import contextlib
import hashlib
import io
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from tools import fix_eff_footprints_registers as fixer


SYNTHETIC_RELOCATIONS = [(16, 10, "synthetic_call", 0), (32, 109, "synthetic_constant", 4)]

def fixture():
    names = ["", ".text", ".data", ".symtab", ".strtab", ".rela.text", ".shstrtab"]
    name_offsets = {}
    shstrings = b""
    for name in names:
        name_offsets[name] = len(shstrings)
        shstrings += name.encode() + b"\0"
    strings = b"\0"
    symbols = [bytes(16)]
    symbols.append(struct.pack(">IIIBBH", len(strings), fixer.FUNCTION_OFFSET, fixer.FUNCTION_SIZE, 0x12, 0, 1))
    strings += fixer.FUNCTION_NAME.encode() + b"\0"
    target_ids = {}
    for _, _, name, _ in SYNTHETIC_RELOCATIONS:
        if name not in target_ids:
            target_ids[name] = len(symbols)
            symbols.append(struct.pack(">IIIBBH", len(strings), 0, 0, 0x10, 0, 0))
            strings += name.encode() + b"\0"
    text = bytearray()
    for i in range(fixer.TEXT_SIZE // 4):
        text += struct.pack(">I", (14 << 26) | (3 << 21) | (3 << 16) | (i & 0xFFFF))
    # Construct synthetic instructions from opcode and register operands only.
    # Unrelated fields deliberately contain no retail instruction payload.
    for offset, fields in fixer.FIELDS.items():
        word = fixer.EXPECTED_OPCODES[offset] << 26
        for shift, (old, _) in fields.items():
            word |= old << shift
        struct.pack_into(">I", text, fixer.FUNCTION_OFFSET + offset, word)
    rels = b"".join(struct.pack(">IIi", fixer.FUNCTION_OFFSET + offset, (target_ids[name] << 8) | kind, addend) for offset, kind, name, addend in SYNTHETIC_RELOCATIONS)
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


def metadata_contract(blob):
    """Independently describe the synthetic fixture's metadata for hash guards."""
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", blob)
    sections = [struct.unpack_from(">10I", blob, header[6] + i * 40) for i in range(header[12])]
    def payload(section):
        return blob[section[4]:section[4] + section[5]]
    def string(table, offset):
        return table[offset:table.index(0, offset)].decode()
    names_table = payload(sections[header[13]])
    names = [string(names_table, section[0]) for section in sections]
    symtab = sections[names.index(".symtab")]
    strings = payload(sections[symtab[6]])
    symbols = list(struct.iter_unpack(">IIIBBH", payload(symtab)))
    section_rows = [(name, s[1], s[2], s[3], s[5], s[6], s[7], s[8], s[9]) for name, s in zip(names, sections)]
    symbol_rows = [(string(strings, row[0]), *row[1:]) for row in symbols]
    relocation_rows = []
    for section in sections:
        if section[1] == 4:
            for offset, info, addend in struct.iter_unpack(">IIi", payload(section)):
                relocation_rows.append((names[section[7]], offset, info & 255, string(strings, symbols[info >> 8][0]), addend))
    digest = lambda rows: hashlib.sha256(json.dumps(rows, separators=(",", ":")).encode()).hexdigest()
    return {
        "EXPECTED_SECTIONS_SHA256": digest(section_rows),
        "EXPECTED_SYMBOLS_SHA256": digest(symbol_rows),
        "EXPECTED_ALL_RELOCATIONS_SHA256": digest(sorted(relocation_rows)),
    }


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
        expected_object = bytearray(self.blob)
        expected_object[self.offsets[".text"]:self.offsets[".text"] + fixer.TEXT_SIZE] = expected
        self.expected_object = bytes(expected_object)
        self.hashes = {
            "INPUT_OBJECT_SHA256": hashlib.sha256(self.blob).hexdigest(),
            "OUTPUT_OBJECT_SHA256": hashlib.sha256(self.expected_object).hexdigest(),
            "EXPECTED_RELOCATIONS_SHA256": hashlib.sha256(json.dumps(SYNTHETIC_RELOCATIONS, separators=(",", ":")).encode()).hexdigest(),
            "INPUT_TEXT_SHA256": hashlib.sha256(self.original_text).hexdigest(),
            "OUTPUT_TEXT_SHA256": hashlib.sha256(expected).hexdigest(),
            "INPUT_FUNCTION_SHA256": hashlib.sha256(self.original_text[fixer.FUNCTION_OFFSET:fixer.FUNCTION_OFFSET + fixer.FUNCTION_SIZE]).hexdigest(),
            "OUTPUT_FUNCTION_SHA256": hashlib.sha256(expected[fixer.FUNCTION_OFFSET:fixer.FUNCTION_OFFSET + fixer.FUNCTION_SIZE]).hexdigest(),
        }
        self.hashes.update(metadata_contract(self.blob))
        self.patcher = patch.multiple(fixer, **self.hashes)
        self.patcher.start()
        self.addCleanup(self.patcher.stop)

    def test_only_twelve_fields_change_and_second_application_is_noop(self):
        out = fixer.normalize(self.blob)
        expected = bytearray(self.blob)
        start = self.offsets[".text"]
        expected[start:start + fixer.TEXT_SIZE] = self.expected_text
        self.assertEqual(out, expected)
        self.assertEqual(fixer.normalize(out), out)
        self.assertEqual(len(fixer.FIELDS), 11)
        self.assertEqual(sum(len(fields) for fields in fixer.FIELDS.values()), 12)

    def test_instruction_corruption_is_rejected(self):
        for offset in (0, fixer.FUNCTION_OFFSET, fixer.FUNCTION_OFFSET + 0x11C):
            bad = bytearray(self.blob)
            bad[self.offsets[".text"] + offset] ^= 1
            with self.assertRaisesRegex(ValueError, "whole-text hash"):
                fixer.normalize(bad)

    def assert_metadata_rejected(self, blob, message, done=False):
        name = "OUTPUT_OBJECT_SHA256" if done else "INPUT_OBJECT_SHA256"
        with patch.object(fixer, name, hashlib.sha256(blob).hexdigest()):
            with self.assertRaisesRegex(ValueError, message):
                fixer.normalize(blob)

    def test_boundary_and_binding_are_guarded(self):
        for field_offset, value in ((4, fixer.FUNCTION_OFFSET + 4), (8, fixer.FUNCTION_SIZE - 4)):
            bad = bytearray(self.blob)
            struct.pack_into(">I", bad, self.offsets[".symtab"] + 16 + field_offset, value)
            self.assert_metadata_rejected(bad, "boundary")
        bad = bytearray(self.blob)
        bad[self.offsets[".symtab"] + 16 + 12] = 0x22
        self.assert_metadata_rejected(bad, "binding")

    def test_relocation_site_type_target_and_addend_are_guarded(self):
        for field, value in ((0, fixer.FUNCTION_OFFSET + 48), (4, (2 << 8) | 1), (4, (3 << 8) | 10), (8, 4)):
            bad = bytearray(self.blob)
            struct.pack_into(">I", bad, self.offsets[".rela.text"] + field, value)
            self.assert_metadata_rejected(bad, "relocations")
        out = bytearray(fixer.normalize(self.blob))
        struct.pack_into(">I", out, self.offsets[".rela.text"], fixer.FUNCTION_OFFSET + 48)
        self.assert_metadata_rejected(out, "relocations", done=True)

    def test_opcode_and_register_guards_independent_of_hashes(self):
        offset = min(fixer.FIELDS)
        shift = next(iter(fixer.FIELDS[offset]))
        for bit, message in ((26, "opcode"), (shift, "register")):
            bad = bytearray(self.blob)
            at = self.offsets[".text"] + fixer.FUNCTION_OFFSET + offset
            word = struct.unpack_from(">I", bad, at)[0] ^ (1 << bit)
            struct.pack_into(">I", bad, at, word)
            changed_text = bytes(bad[self.offsets[".text"]:self.offsets[".text"] + fixer.TEXT_SIZE])
            with patch.multiple(fixer,
                                INPUT_OBJECT_SHA256=hashlib.sha256(bad).hexdigest(),
                                INPUT_TEXT_SHA256=hashlib.sha256(changed_text).hexdigest(),
                                INPUT_FUNCTION_SHA256=hashlib.sha256(changed_text[fixer.FUNCTION_OFFSET:fixer.FUNCTION_OFFSET + fixer.FUNCTION_SIZE]).hexdigest()):
                with self.assertRaisesRegex(ValueError, message):
                    fixer.normalize(bad)

    def test_nontext_corruption_is_rejected(self):
        bad = bytearray(self.blob)
        bad[self.offsets[".data"]] ^= 1
        with self.assertRaisesRegex(ValueError, "whole-object hash"):
            fixer.normalize(bad)

    def test_relocation_on_rewrite_word_is_rejected(self):
        bad = bytearray(self.blob)
        offset = min(fixer.FIELDS)
        struct.pack_into(">I", bad, self.offsets[".rela.text"], fixer.FUNCTION_OFFSET + offset)
        rows = [(offset, 10, "synthetic_call", 0), SYNTHETIC_RELOCATIONS[1]]
        with patch.multiple(fixer, INPUT_OBJECT_SHA256=hashlib.sha256(bad).hexdigest(),
                            EXPECTED_RELOCATIONS_SHA256=hashlib.sha256(json.dumps(sorted(rows), separators=(",", ":")).encode()).hexdigest(),
                            EXPECTED_ALL_RELOCATIONS_SHA256=metadata_contract(bad)["EXPECTED_ALL_RELOCATIONS_SHA256"]):
            with self.assertRaisesRegex(ValueError, "overlaps"):
                fixer.normalize(bad)

    def test_other_symbol_inventory_is_guarded(self):
        bad = bytearray(self.blob)
        # An unrelated undefined symbol's value must not change either.
        struct.pack_into(">I", bad, self.offsets[".symtab"] + 32 + 4, 8)
        self.assert_metadata_rejected(bad, "symbol inventory")

    def test_section_alignment_flags_and_links_are_guarded(self):
        shoff = struct.unpack_from(">I", self.blob, 32)[0]
        for section_index, field, value in ((1, 8, 16), (2, 2, 2), (3, 6, 5)):
            bad = bytearray(self.blob)
            struct.pack_into(">I", bad, shoff + section_index * 40 + field * 4, value)
            self.assert_metadata_rejected(bad, "section inventory")

    def test_invalid_elf_machine_and_overlapping_text_are_guarded(self):
        bad = bytearray(self.blob)
        struct.pack_into(">H", bad, 18, 3)
        with self.assertRaisesRegex(ValueError, "PowerPC"):
            fixer.normalize(bad)
        bad = bytearray(self.blob)
        shoff = struct.unpack_from(">I", bad, 32)[0]
        struct.pack_into(">I", bad, shoff + 2 * 40 + 16, self.offsets[".text"] + 4)
        with self.assertRaisesRegex(ValueError, "overlapping text"):
            fixer.normalize(bad)

    def test_adjacent_halfword_relocation_and_crossing_word_relocation(self):
        offset = min(fixer.FIELDS) - 2
        for kind, should_pass in ((6, True), (10, False)):
            bad = bytearray(self.blob)
            struct.pack_into(">II", bad, self.offsets[".rela.text"], fixer.FUNCTION_OFFSET + offset, (2 << 8) | kind)
            rows = [(offset, kind, "synthetic_call", 0), SYNTHETIC_RELOCATIONS[1]]
            expected = bytearray(self.expected_object)
            struct.pack_into(">II", expected, self.offsets[".rela.text"], fixer.FUNCTION_OFFSET + offset, (2 << 8) | kind)
            with patch.multiple(fixer,
                                INPUT_OBJECT_SHA256=hashlib.sha256(bad).hexdigest(),
                                OUTPUT_OBJECT_SHA256=hashlib.sha256(expected).hexdigest(),
                                EXPECTED_RELOCATIONS_SHA256=hashlib.sha256(json.dumps(sorted(rows), separators=(",", ":")).encode()).hexdigest(),
                                EXPECTED_ALL_RELOCATIONS_SHA256=metadata_contract(bad)["EXPECTED_ALL_RELOCATIONS_SHA256"]):
                if should_pass:
                    self.assertEqual(fixer.normalize(bad), expected)
                else:
                    with self.assertRaisesRegex(ValueError, "overlaps"):
                        fixer.normalize(bad)

    def test_bad_output_contract_is_rejected(self):
        with patch.object(fixer, "OUTPUT_TEXT_SHA256", "0" * 64):
            with self.assertRaisesRegex(ValueError, "output text hash"):
                fixer.normalize(self.blob)

    def test_malformed_input_is_rejected(self):
        for bad in (b"", self.blob[:51], self.blob[:-1]):
            with self.assertRaises(ValueError):
                fixer.normalize(bad)

    def test_cli_failure_does_not_write_object_or_stamp(self):
        with tempfile.TemporaryDirectory(prefix="footprints-register-test-", dir="/tmp") as td:
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

    def test_failed_atomic_replace_preserves_input_and_cleans_temporary(self):
        with tempfile.TemporaryDirectory(prefix="footprints-register-test-", dir="/tmp") as td:
            obj, stamp = Path(td) / "sample.o", Path(td) / "success.stamp"
            obj.write_bytes(self.blob)
            with patch.object(fixer.os, "replace", side_effect=OSError("simulated write failure")):
                with self.assertRaises(OSError):
                    fixer.main([str(obj), str(stamp)])
            self.assertEqual(obj.read_bytes(), self.blob)
            self.assertFalse(stamp.exists())
            self.assertEqual(list(Path(td).iterdir()), [obj])


if __name__ == "__main__":
    unittest.main()
