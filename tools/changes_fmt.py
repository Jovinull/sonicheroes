#!/usr/bin/env python3

from argparse import ArgumentParser
import os
import json
from pathlib import Path
from typing import Optional, Tuple

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.abspath(os.path.join(script_dir, ".."))


UNIT_KEYS_TO_DIFF = [
    "fuzzy_match_percent",
    "matched_code_percent",
    "matched_data_percent",
    "complete_code_percent",
    "complete_data_percent",
]

FUNCTION_KEYS_TO_DIFF = [
    "fuzzy_match_percent",
]

Change = Tuple[str, str, float, float]


def format_float(value: float) -> str:
    if value < 100.0 and value > 99.99:
        value = 99.99
    return "%6.2f" % value


def get_changes(changes_file: str) -> Tuple[list[Change], list[Change]]:
    changes_file = os.path.relpath(changes_file, root_dir)
    with open(changes_file, "r") as f:
        changes_json = json.load(f)

    regressions = []
    progressions = []

    # Where each function of the new report lives: carving a unit out of an
    # auto-generated range (or absorbing a unit into a bigger one) moves its
    # functions to another unit at the same address, often under a new name.
    moved_to = {}
    for unit in changes_json.get("units", []):
        module = unit.get("metadata", {}).get("module_name")
        for func in unit.get("functions", []):
            address = func.get("metadata", {}).get("virtual_address")
            if "to" in func and address is not None:
                value = func["to"].get("fuzzy_match_percent", 0.0)
                key = (module, address)
                moved_to[key] = max(value, moved_to.get(key, 0.0))

    def found_elsewhere(module: Optional[str], func: dict) -> bool:
        address = func.get("metadata", {}).get("virtual_address")
        from_value = func.get("from", {}).get("fuzzy_match_percent", 0.0)
        return address is not None and moved_to.get((module, address), -1.0) >= from_value

    def diff_key(object_name: Optional[str], object: dict, key: str):
        from_value = object.get("from", {}).get(key, 0.0)
        to_value = object.get("to", {}).get(key, 0.0)
        key = key.removesuffix("_percent")
        change = (object_name, key, from_value, to_value)
        if from_value > to_value:
            regressions.append(change)
        elif to_value > from_value:
            progressions.append(change)

    for key in UNIT_KEYS_TO_DIFF:
        diff_key(None, changes_json, key)

    for unit in changes_json.get("units", []):
        unit_name = unit["name"]
        module = unit.get("metadata", {}).get("module_name")
        functions = unit.get("functions", [])
        # A unit gone from the new report with no data of its own and whose
        # every function is at the same address elsewhere, at least as well
        # matched, lost nothing: its percentages (data at a vacuous 100%)
        # would otherwise read as a drop to 0%.
        moved = (
            "to" not in unit
            and int(unit.get("from", {}).get("total_data", 0)) == 0
            and all(found_elsewhere(module, func) for func in functions)
        )
        if not moved:
            for key in UNIT_KEYS_TO_DIFF:
                diff_key(unit_name, unit, key)
        # Ignore sections
        for func in functions:
            if "to" not in func and found_elsewhere(module, func):
                continue
            func_name = func["name"]
            for key in FUNCTION_KEYS_TO_DIFF:
                diff_key(func_name, func, key)

    return regressions, progressions


def generate_changes_plaintext(changes: list[Change]) -> str:
    if len(changes) == 0:
        return ""

    table_total_width = 136
    percents_max_len = 7 + 4 + 7
    key_max_len = max(len(key) for _, key, _, _ in changes)
    name_max_len = max(len(name or "Total") for name, _, _, _ in changes)
    max_width_for_name_col = table_total_width - 3 - key_max_len - 3 - percents_max_len
    name_max_len = min(max_width_for_name_col, name_max_len)

    out_lines = []
    for name, key, from_value, to_value in changes:
        if name is None:
            name = "Total"
        if len(name) > name_max_len:
            name = name[: name_max_len - len("[...]")] + "[...]"
        out_lines.append(
            f"{name:>{name_max_len}} | {key:<{key_max_len}} | {format_float(from_value)}% -> {format_float(to_value)}%"
        )

    return "\n".join(out_lines)


def generate_changes_markdown(changes: list[Change], description: str) -> str:
    if len(changes) == 0:
        return ""

    out_lines = []
    name_max_len = 100

    out_lines.append("<details>")
    out_lines.append(
        f"<summary>Detected {len(changes)} {description} compared to the base:</summary>"
    )
    out_lines.append("")  # Must include a blank line before a table
    out_lines.append("| Name | Type | Before | After |")
    out_lines.append("| ---- | ---- | ------ | ----- |")

    for name, key, from_value, to_value in changes:
        if name is None:
            name = "Total"
        else:
            if len(name) > name_max_len:
                name = name[: name_max_len - len("...")] + "..."
            name = f"`{name}`"  # Surround with backticks
        key = key.replace("_", " ").capitalize()
        out_lines.append(
            f"| {name} | {key} | {format_float(from_value)}% | {format_float(to_value)}% |"
        )

    out_lines.append("</details>")

    return "\n".join(out_lines)


def main():
    parser = ArgumentParser(description="Format objdiff-cli report changes.")
    parser.add_argument(
        "report_changes_file",
        type=Path,
        help="""path to the JSON file containing the changes, generated by objdiff-cli.""",
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        help="""Output file (prints to console if unspecified)""",
    )
    parser.add_argument(
        "--all",
        action="store_true",
        help="""Includes progressions as well.""",
    )
    args = parser.parse_args()

    regressions, progressions = get_changes(args.report_changes_file)

    if args.output:
        markdown_output = generate_changes_markdown(regressions, "regressions")
        if args.all:
            markdown_output += generate_changes_markdown(progressions, "progressions")
        with open(args.output, "w", encoding="utf-8") as f:
            f.write(markdown_output)
    else:
        if args.all:
            changes = progressions + regressions
        else:
            changes = regressions
        text_output = generate_changes_plaintext(changes)
        print(text_output)


if __name__ == "__main__":
    main()
