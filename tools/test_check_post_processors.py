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


class RepositoryTests(unittest.TestCase):
    def test_every_shipped_step_passes(self) -> None:
        scripts = sorted(checker.TOOLS.glob("fix_*.py"))
        self.assertGreater(len(scripts), 0)
        problems = [problem for script in scripts for problem in checker.check(script)]
        self.assertEqual(problems, [], "\n".join(problems))

    def test_the_debt_list_is_not_grown(self) -> None:
        # A new step gets its bytes from source. This list only ever shrinks.
        self.assertEqual(
            checker.CARRIED_RETAIL_DEBT,
            {"fix_game_action_object.py": {"TARGET_EXTAB"}},
        )


if __name__ == "__main__":
    unittest.main()
