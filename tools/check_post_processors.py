#!/usr/bin/env python3

"""Enforce the object post-processor criteria in docs/object-post-processors.md.

A post-processor may permute what our own compiler produced. It may not carry
bytes taken from the retail object: a hex literal that is *compared* is a guard,
the same literal *written* is the answer copied into the tool, and the artifact
hash gate can no longer tell the reconstruction from the patch.

This checks the two properties that can be decided mechanically:

  no retail content  a module-level bytes.fromhex() constant must never reach a
                     write -- pack_into, insert, or a slice assignment
  fails closed       a step that writes must validate something first, so a
                     stale table stops the build instead of quietly not applying
"""

from __future__ import annotations

import ast
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parent
WRITE_CALLS = {"pack_into", "insert", "write_bytes", "pack_into_"}

# Known debt, recorded rather than hidden. fix_game_action_object.py overwrites
# the whole extab section with TARGET_EXTAB, a hex table of retail's exception
# records. It predates these criteria and covers action.cpp, a 77 KB source
# compiled into five split objects, so producing that table from source is its
# own piece of work. Listed here so the rule can be enforced for everything else
# and this one stays visible instead of passing silently.
#
# Nothing may be added to this list. A new step gets the bytes from source.
CARRIED_RETAIL_DEBT = {
    "fix_game_action_object.py": {"TARGET_EXTAB"},
}


def hex_constants(tree: ast.Module) -> set[str]:
    """Module-level names bound to a bytes.fromhex(...) literal."""
    found = set()
    for node in tree.body:
        if not isinstance(node, ast.Assign):
            continue
        call = node.value
        if not isinstance(call, ast.Call):
            continue
        func = call.func
        if (
            isinstance(func, ast.Attribute)
            and func.attr == "fromhex"
            and isinstance(func.value, ast.Name)
            and func.value.id == "bytes"
        ):
            for target in node.targets:
                if isinstance(target, ast.Name):
                    found.add(target.id)
    return found


def names_in(node: ast.AST) -> set[str]:
    return {n.id for n in ast.walk(node) if isinstance(n, ast.Name)}


def written_names(tree: ast.Module) -> set[str]:
    """Names that flow into a write."""
    written = set()
    for node in ast.walk(tree):
        if isinstance(node, ast.Call):
            func = node.func
            name = func.attr if isinstance(func, ast.Attribute) else getattr(func, "id", "")
            if name in WRITE_CALLS:
                for argument in node.args:
                    written |= names_in(argument)
        elif isinstance(node, ast.Assign):
            # blob[a:b] = CONST
            for target in node.targets:
                if isinstance(target, ast.Subscript):
                    written |= names_in(node.value)
    return written


def validates(tree: ast.Module) -> bool:
    for node in ast.walk(tree):
        if isinstance(node, ast.Raise):
            return True
        if isinstance(node, ast.Assert):
            return True
        if isinstance(node, ast.Call):
            func = node.func
            name = func.attr if isinstance(func, ast.Attribute) else getattr(func, "id", "")
            if name in {"check_output", "index"}:
                continue
    return False


def writes_anything(tree: ast.Module) -> bool:
    for node in ast.walk(tree):
        if isinstance(node, ast.Call):
            func = node.func
            name = func.attr if isinstance(func, ast.Attribute) else getattr(func, "id", "")
            if name in WRITE_CALLS:
                return True
        if isinstance(node, ast.Assign):
            for target in node.targets:
                if isinstance(target, ast.Subscript):
                    return True
    return False


def check(path: Path) -> list[str]:
    tree = ast.parse(path.read_text())
    problems = []
    carried = hex_constants(tree) & written_names(tree)
    carried -= CARRIED_RETAIL_DEBT.get(path.name, set())
    for name in sorted(carried):
        problems.append(
            f"{path.name}: {name} is a hex literal that gets written. "
            "A post-processor may compare retail bytes, never carry them. "
            "See docs/object-post-processors.md."
        )
    if writes_anything(tree) and not validates(tree):
        problems.append(
            f"{path.name}: edits the object but never validates what it found. "
            "A stale table has to stop the build, not quietly not apply."
        )
    return problems


def main() -> int:
    scripts = sorted(TOOLS.glob("fix_*.py"))
    if not scripts:
        print("no object post-processors found", file=sys.stderr)
        return 1
    problems = [problem for script in scripts for problem in check(script)]
    if problems:
        print("object post-processor violations:")
        for problem in problems:
            print(f"  - {problem}")
        return 1
    print(f"object post-processors OK: {len(scripts)} steps checked")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
