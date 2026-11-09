#!/usr/bin/env python3

from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path

import tools.changes_fmt as changes_fmt


def function(name: str, address: str, before: float | None, after: float | None) -> dict:
    func = {"name": name, "metadata": {"virtual_address": address}}
    if before is not None:
        func["from"] = {"fuzzy_match_percent": before, "size": "16"}
    if after is not None:
        func["to"] = {"fuzzy_match_percent": after, "size": "16"}
    return func


def section(name: str, address: str, before: str | None, after: str | None) -> dict:
    sec = {"name": name, "metadata": {"virtual_address": address}}
    if before is not None:
        sec["from"] = {"size": before}
    if after is not None:
        sec["to"] = {"size": after}
    return sec


def removed_unit(
    name: str,
    functions: list[dict],
    total_data: str | None = None,
    sections: list[dict] | None = None,
    generated: bool = False,
) -> dict:
    before = {"total_code": "32", "matched_data_percent": 100.0, "complete_data_percent": 100.0}
    if total_data is not None:
        before["total_data"] = total_data
    return {
        "name": name,
        "from": before,
        "functions": functions,
        "sections": sections or [],
        "metadata": {"module_name": "stage01D", "auto_generated": generated},
    }


def new_unit(
    name: str,
    functions: list[dict],
    module: str = "stage01D",
    sections: list[dict] | None = None,
    generated: bool = False,
) -> dict:
    after = {"fuzzy_match_percent": 100.0, "matched_code_percent": 100.0, "matched_data_percent": 100.0}
    return {
        "name": name,
        "to": after,
        "functions": functions,
        "sections": sections or [],
        "metadata": {"module_name": module, "auto_generated": generated},
    }


def regressions(units: list[dict]) -> list:
    with tempfile.TemporaryDirectory(dir=changes_fmt.root_dir) as tmp:
        path = Path(tmp) / "changes.json"
        path.write_text(json.dumps({"units": units}))
        return changes_fmt.get_changes(str(path))[0]


class MovedCodeTests(unittest.TestCase):
    def test_a_carved_auto_unit_is_not_a_regression(self) -> None:
        units = [
            removed_unit("stage01D/auto_00_00001000_text", [function("fn_3_1000", "4096", 0.0, None)]),
            new_unit("stage01D/rel/x_hooks", [function("xUnload", "4096", None, 100.0)]),
        ]
        self.assertEqual(regressions(units), [])

    def test_a_matched_function_moved_to_another_unit_is_not_a_regression(self) -> None:
        units = [
            removed_unit("stage01D/rel/x_register", [function("xRegister", "4096", 100.0, None)]),
            new_unit("stage01D/rel/x_assets", [function("xRegister", "4096", None, 100.0)]),
        ]
        self.assertEqual(regressions(units), [])

    def test_a_function_that_got_worse_where_it_moved_is_a_regression(self) -> None:
        units = [
            removed_unit("stage01D/rel/x_register", [function("xRegister", "4096", 100.0, None)]),
            new_unit("stage01D/rel/x_assets", [function("xRegister", "4096", None, 80.0)]),
        ]
        names = {name for name, _, _, _ in regressions(units)}
        self.assertEqual(names, {"stage01D/rel/x_register", "xRegister"})

    def test_a_function_found_only_in_another_module_is_a_regression(self) -> None:
        units = [
            removed_unit("stage01D/rel/x_register", [function("xRegister", "4096", 100.0, None)]),
            new_unit("stage03D/rel/x_register", [function("xRegister", "4096", None, 100.0)], "stage03D"),
        ]
        self.assertIn("xRegister", {name for name, _, _, _ in regressions(units)})

    def test_a_removed_unit_with_data_is_still_reported(self) -> None:
        units = [
            removed_unit("stage01D/auto_00_00001000_text", [function("fn_3_1000", "4096", 0.0, None)], "8"),
            new_unit("stage01D/rel/x_hooks", [function("xUnload", "4096", None, 100.0)]),
        ]
        self.assertIn("stage01D/auto_00_00001000_text", {name for name, _, _, _ in regressions(units)})

    def test_a_removed_unit_whose_data_is_covered_elsewhere_is_not_a_regression(self) -> None:
        units = [
            removed_unit(
                "stage01D/rel/x_register",
                [function("xRegister", "4096", 100.0, None)],
                "4",
                [section(".ctors", "352", "4", None), section(".text", "4096", "16", None)],
            ),
            new_unit(
                "stage01D/rel/x_all",
                [function("xRegister", "4096", None, 100.0)],
                sections=[section(".ctors", "348", None, "16")],
            ),
        ]
        self.assertEqual(regressions(units), [])

    def test_a_removed_data_only_unit_covered_by_two_neighbours_is_not_a_regression(self) -> None:
        units = [
            removed_unit("stage01D/auto_04_00000100_data", [], "32", [section(".data", "256", "32", None)]),
            new_unit("stage01D/rel/a", [], sections=[section(".data", "240", None, "32")]),
            new_unit("stage01D/rel/b", [], sections=[section(".data", "272", None, "32")]),
        ]
        self.assertEqual(regressions(units), [])

    def test_a_removed_unit_whose_data_is_not_covered_is_a_regression(self) -> None:
        for covering in (
            section(".data", "300", None, "64"),  # elsewhere
            section(".rodata", "256", None, "64"),  # wrong section
            section(".data", "256", None, "16"),  # only part of it
        ):
            with self.subTest(covering=covering):
                units = [
                    removed_unit("stage01D/auto_04_00000100_data", [], "32", [section(".data", "256", "32", None)]),
                    new_unit("stage01D/rel/a", [], sections=[covering]),
                ]
                self.assertIn("stage01D/auto_04_00000100_data", {n for n, _, _, _ in regressions(units)})

    def test_a_deleted_draft_left_as_uncompiled_code_is_not_a_regression(self) -> None:
        units = [
            removed_unit("stage01D/rel/x_draft", [function("fn_3_1000", "4096", 48.0, None)]),
            new_unit("stage01D/auto_00_00001000_text", [function("fn_3_1000", "4096", None, 0.0)], generated=True),
        ]
        self.assertEqual(regressions(units), [])

    def test_a_draft_that_keeps_its_unit_is_still_reported(self) -> None:
        units = [
            {
                "name": "stage01D/rel/x_draft",
                "from": {"fuzzy_match_percent": 48.0},
                "to": {"fuzzy_match_percent": 0.0},
                "functions": [function("fn_3_1000", "4096", 48.0, None)],
                "metadata": {"module_name": "stage01D"},
            },
            new_unit("stage01D/auto_00_00001000_text", [function("fn_3_1000", "4096", None, 0.0)], generated=True),
        ]
        self.assertIn("fn_3_1000", {name for name, _, _, _ in regressions(units)})

    def test_a_function_that_drops_in_place_is_a_regression(self) -> None:
        units = [
            {
                "name": "stage01D/rel/x",
                "from": {"fuzzy_match_percent": 100.0},
                "to": {"fuzzy_match_percent": 90.0},
                "functions": [function("xLoad", "4096", 100.0, 90.0)],
                "metadata": {"module_name": "stage01D"},
            }
        ]
        names = {name for name, _, _, _ in regressions(units)}
        self.assertEqual(names, {"stage01D/rel/x", "xLoad"})


if __name__ == "__main__":
    unittest.main()
