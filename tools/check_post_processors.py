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
    "fix_eff_tornado_object.py": {"TEXT_PATCHES"},
    "fix_stage13_3way_colli_object.py": {"WORD_FIXES"},
    "fix_stage13_antenna_object.py": {"FACTORY_REGISTER_WORDS"},
    "fix_stage13_blinklight_object.py": {"FACTORY_REGISTER_WORDS"},
}


def instruction_sized_constants(tree: ast.Module) -> set[str]:
    """Module-level names bound to a literal holding instruction-sized values.

    A step may carry register numbers, bit shifts and offsets; those are small.
    A 32-bit value in a table is an instruction word, and writing one is
    carrying retail content whether it is spelled as hex bytes or as an int.
    """
    found = set()
    for node in tree.body:
        if not isinstance(node, ast.Assign):
            continue
        big = False
        for child in ast.walk(node.value):
            if isinstance(child, ast.Constant) and isinstance(child.value, int):
                if not isinstance(child.value, bool) and child.value >= 0x10000:
                    big = True
        if not big:
            continue
        for target in node.targets:
            if isinstance(target, ast.Name):
                found.add(target.id)
    return found


def value_argument_names(tree: ast.Module) -> set[str]:
    """Names used as the *value* being written, not as an offset or a buffer.

    struct.pack_into(fmt, buffer, offset, *values) -> args[3:]
    insert(section, data)                          -> args[1]
    blob[a:b] = value                              -> the right-hand side
    """
    values = set()
    for node in ast.walk(tree):
        if isinstance(node, ast.Call):
            func = node.func
            name = func.attr if isinstance(func, ast.Attribute) else getattr(func, "id", "")
            if name == "pack_into":
                for argument in node.args[3:]:
                    values |= names_in(argument)
            elif name == "insert" and len(node.args) >= 2:
                values |= names_in(node.args[1])
        elif isinstance(node, ast.Assign):
            for target in node.targets:
                if isinstance(target, ast.Subscript):
                    values |= names_in(node.value)
    return values


def unpacked_from(tree: ast.Module, sources: set[str]) -> set[str]:
    """Names bound by iterating one of `sources`. One hop, no fixpoint.

    Catches `for offset, (current, retail) in TABLE.items(): ... retail ...`,
    which is how an instruction table reaches a write without the constant
    itself appearing at the call. Deliberately shallow: a wider walk floods on
    ordinary names like `offset` and `index` that every step reuses.
    """
    bound = set()
    for node in ast.walk(tree):
        if isinstance(node, ast.For) and names_in(node.iter) & sources:
            bound |= names_in(node.target)
    return bound


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
    allowed = CARRIED_RETAIL_DEBT.get(path.name, set())
    written = written_names(tree)

    carried = (hex_constants(tree) & written) - allowed
    for name in sorted(carried):
        problems.append(
            f"{path.name}: {name} is a hex literal that gets written. "
            "A post-processor may compare retail bytes, never carry them. "
            "See docs/object-post-processors.md."
        )

    sized = instruction_sized_constants(tree) - allowed
    values = value_argument_names(tree)
    for name in sorted(sized & values):
        problems.append(
            f"{path.name}: {name} holds instruction-sized values and is written "
            "as a value. Register numbers, shifts and offsets are fine to carry; "
            "a 32-bit word is retail content. See docs/object-post-processors.md."
        )
    for name in sorted(unpacked_from(tree, sized) & values):
        origin = ", ".join(sorted(sized))
        problems.append(
            f"{path.name}: {name} is unpacked from {origin}, which holds "
            "instruction-sized values, and is written as a value. "
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
