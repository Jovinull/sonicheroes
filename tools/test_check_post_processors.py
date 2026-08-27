#!/usr/bin/env python3

from __future__ import annotations

import ast
import tempfile
import unittest
from pathlib import Path

import tools.check_post_processors as checker


def parse(source: str) -> ast.Module:
    return ast.parse(source)


class HexLiteralTests(unittest.TestCase):
    def test_a_compared_hex_literal_is_allowed(self) -> None:
        tree = parse(
            "import struct\n"
            "GUARD = bytes.fromhex('deadbeef')\n"
            "def main(data, section):\n"
            "    if data[0:4] != GUARD:\n"
            "        raise SystemExit('changed')\n"
            "    struct.pack_into('>I', data, 0, 1)\n"
        )
        self.assertEqual(checker.hex_constants(tree) & checker.written_names(tree), set())

    def test_a_written_hex_literal_is_rejected(self) -> None:
        tree = parse(
            "RETAIL = bytes.fromhex('deadbeef')\n"
            "def main(data):\n"
            "    raise_if = 1\n"
            "    data[0:4] = RETAIL\n"
        )
        self.assertEqual(checker.hex_constants(tree) & checker.written_names(tree), {"RETAIL"})

    def test_a_hex_literal_passed_to_insert_is_rejected(self) -> None:
        tree = parse(
            "TAIL = bytes.fromhex('00ff')\n"
            "def main(section):\n"
            "    insert(section, TAIL)\n"
        )
        self.assertEqual(checker.hex_constants(tree) & checker.written_names(tree), {"TAIL"})


class InstructionSizedTests(unittest.TestCase):
    def test_a_table_of_instruction_words_is_rejected(self) -> None:
        tree = parse(
            "import struct\n"
            "PATCHES = {0x10: (0x7C7F1B78, 0x7C601B78)}\n"
            "def main(blob, text):\n"
            "    for offset, (current, retail) in PATCHES.items():\n"
            "        struct.pack_into('>I', blob, text + offset, retail)\n"
        )
        sized = checker.instruction_sized_constants(tree)
        self.assertEqual(sized, {"PATCHES"})
        self.assertIn("retail", checker.unpacked_from(tree, sized) & checker.value_argument_names(tree))

    def test_a_table_of_register_numbers_is_allowed(self) -> None:
        tree = parse(
            "import struct\n"
            "FIELDS = {0x10: ((21, 31, 27), (11, 31, 27))}\n"
            "def main(blob, text):\n"
            "    for offset, fields in FIELDS.items():\n"
            "        word = 0\n"
            "        for shift, current, retail in fields:\n"
            "            word = word | (retail << shift)\n"
            "        struct.pack_into('>I', blob, text + offset, word)\n"
        )
        self.assertEqual(checker.instruction_sized_constants(tree), set())

    def test_a_name_in_offset_position_is_not_a_value(self) -> None:
        tree = parse(
            "import struct\n"
            "def main(blob, offset, word):\n"
            "    struct.pack_into('>I', blob, offset, word)\n"
        )
        values = checker.value_argument_names(tree)
        self.assertIn("word", values)
        self.assertNotIn("offset", values)


class EmbeddedBlobTests(unittest.TestCase):
    def test_a_decoded_blob_written_as_the_object_is_rejected(self) -> None:
        tree = parse(
            "import base64, zlib\n"
            "RETAIL = '" + "x" * 300 + "'\n"
            "def main(path):\n"
            "    path.write_bytes(zlib.decompress(base64.b85decode(RETAIL)))\n"
        )
        self.assertEqual(checker.embedded_object_writers(tree), {"RETAIL"})

    def test_a_short_constant_is_not_a_blob(self) -> None:
        tree = parse(
            "import base64\n"
            "TAG = 'abc'\n"
            "def main(path):\n"
            "    path.write_bytes(base64.b64decode(TAG))\n"
        )
        self.assertEqual(checker.embedded_object_writers(tree), set())

    def test_a_step_that_decodes_nothing_is_untouched(self) -> None:
        tree = parse(
            "import struct\n"
            "def main(blob):\n"
            "    struct.pack_into('>I', blob, 0, 1)\n"
        )
        self.assertEqual(checker.embedded_object_writers(tree), set())


class ValidationTests(unittest.TestCase):
    def test_a_step_that_writes_without_validating_is_rejected(self) -> None:
        tree = parse(
            "import struct\n"
            "def main(data):\n"
            "    struct.pack_into('>I', data, 0, 1)\n"
        )
        self.assertTrue(checker.writes_anything(tree))
        self.assertFalse(checker.validates(tree))

    def test_a_step_that_raises_counts_as_validating(self) -> None:
        tree = parse(
            "import struct\n"
            "def main(data):\n"
            "    if len(data) != 4:\n"
            "        raise SystemExit('bad')\n"
            "    struct.pack_into('>I', data, 0, 1)\n"
        )
        self.assertTrue(checker.validates(tree))

    def test_a_step_that_writes_nothing_needs_no_validation(self) -> None:
        tree = parse("def main(path):\n    print(path)\n")
        self.assertFalse(checker.writes_anything(tree))


class TargetObjectInputTests(unittest.TestCase):
    def test_a_rel_target_object_input_is_rejected(self) -> None:
        tree = parse(
            'config.custom_build_steps = {\n'
            '    "pre-compile": [\n'
            '        {\n'
            '            "inputs": [\n'
            '                "build/G9SE8P/src/rel/unit.o",\n'
            '                "build/G9SE8P/stage40D/obj/rel/unit.o",\n'
            '            ],\n'
            '        },\n'
            '    ],\n'
            '}\n'
        )
        self.assertEqual(
            checker.target_object_inputs(tree),
            ["build/G9SE8P/stage40D/obj/rel/unit.o"],
        )

    def test_a_dol_target_object_input_is_rejected(self) -> None:
        tree = parse('INPUT = "build/G9SE8P/obj/game/unit.o"\n')
        self.assertEqual(
            checker.target_object_inputs(tree),
            ["build/G9SE8P/obj/game/unit.o"],
        )

    def test_compiler_output_is_allowed(self) -> None:
        tree = parse(
            'A = "build/G9SE8P/src/rel/unit.o"\n'
            'B = "build/G9SE8P/stage40D/stage40D.rel"\n'
            'C = "build/G9SE8P/unit-object.stamp"\n'
        )
        self.assertEqual(checker.target_object_inputs(tree), [])


class RepositoryTests(unittest.TestCase):
    def test_every_shipped_step_passes(self) -> None:
        scripts = sorted(checker.TOOLS.glob("fix_*.py"))
        self.assertGreater(len(scripts), 0)
        problems = [problem for script in scripts for problem in checker.check(script)]
        self.assertEqual(problems, [], "\n".join(problems))

    def test_configure_names_no_target_object(self) -> None:
        problems = checker.check_configure(checker.CONFIGURE)
        self.assertEqual(problems, [], "\n".join(problems))

    def test_the_debt_list_is_not_grown(self) -> None:
        # A new step gets its bytes from source. This list only ever shrinks.
        self.assertEqual(
            checker.CARRIED_RETAIL_DEBT,
            {
                "fix_game_action_object.py": {"TARGET_EXTAB"},
                "fix_eff_tornado_object.py": {"TEXT_PATCHES"},
                "fix_stage13_3way_colli_object.py": {"WORD_FIXES"},
                "fix_stage13_antenna_object.py": {"FACTORY_REGISTER_WORDS"},
                "fix_stage13_blinklight_object.py": {"FACTORY_REGISTER_WORDS"},
            },
        )


if __name__ == "__main__":
    unittest.main()
