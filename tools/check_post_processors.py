#!/usr/bin/env python3

"""Enforce the object post-processor criteria in docs/object-post-processors.md.

A post-processor may permute what our own compiler produced. It may not carry
bytes taken from the retail object: a hex literal that is *compared* is a guard,
the same literal *written* is the answer copied into the tool, and the artifact
hash gate can no longer tell the reconstruction from the patch.

This checks the properties that can be decided mechanically:

  no retail content  a module-level bytes.fromhex() constant must never reach a
                     write -- pack_into, insert, or a slice assignment
  fails closed       a step that writes must validate something first, so a
                     stale table stops the build instead of quietly not applying
  no retail input    no build step in configure.py may name a dtk target object,
                     because a step that is handed one does not have to carry a
                     copy -- it can just write the file it was given
"""

from __future__ import annotations

import ast
import re
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parent
CONFIGURE = TOOLS.parent / "configure.py"

# dtk writes the target object for every split: build/<version>/obj/<unit>.o for
# the DOL, build/<version>/<module>/obj/<unit>.o for a REL. Those are retail's
# bytes under our own path. Nothing in the build graph has a reason to read one.
TARGET_OBJECT_PATH = re.compile(r"(?:\A|/)build/[^/]+/(?:[^/]+/)?obj/")
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


def embedded_object_writers(tree: ast.Module) -> set[str]:
    """Module-level constants that get decoded and written as object content.

    The most direct way to fake a match is to carry a compressed copy of the
    retail object and write it over whatever the compiler produced. The source
    then has no bearing on the result, the artifact hashes because it *is* the
    artifact, and every percentage the project reports for that unit is the
    original measured against itself.

    A blob is neither a hex literal nor an integer table, so the earlier rules
    do not see it. This one looks for a decode or decompress call anywhere in
    the module and reports the constants that feed it.
    """
    decoders = {"b85decode", "b64decode", "a85decode", "b32decode", "b16decode",
                "decompress", "unhexlify", "decodebytes"}
    found = set()
    for node in ast.walk(tree):
        if not isinstance(node, ast.Call):
            continue
        func = node.func
        name = func.attr if isinstance(func, ast.Attribute) else getattr(func, "id", "")
        if name not in decoders:
            continue
        for argument in node.args:
            found |= names_in(argument)
    literals = set()
    for node in tree.body:
        if isinstance(node, ast.Assign) and isinstance(node.value, ast.Constant):
            if isinstance(node.value.value, (str, bytes)) and len(node.value.value) > 256:
                for target in node.targets:
                    if isinstance(target, ast.Name):
                        literals.add(target.id)
    return found & literals


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

    for name in sorted(embedded_object_writers(tree) - allowed):
        problems.append(
            f"{path.name}: {name} is an encoded blob that gets decoded and "
            "written. A post-processor may permute what our compiler produced; "
            "carrying a copy of the retail object replaces it, and the unit "
            "then measures the original against itself. "
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


def target_object_inputs(tree: ast.Module) -> list[str]:
    """Path constants in configure.py that name a dtk target object.

    The five rules above all ask what a step *carries*, which is the wrong
    question once the step is handed the answer. A build step whose inputs
    include `build/<version>/.../obj/<unit>.o` needs no embedded blob and no
    hex table: it can copy the file ninja put in front of it, and the unit then
    measures the original against itself exactly as if it had.

    `fix_tenkyu_goalring_object.py` did this and passed every other rule here.

    Compiler output lives under `build/<version>/src/`, so no legitimate step
    loses anything by this being absolute.
    """
    found = []
    for node in ast.walk(tree):
        if isinstance(node, ast.Constant) and isinstance(node.value, str):
            if TARGET_OBJECT_PATH.search(node.value):
                found.append(node.value)
    return sorted(set(found))


def check_configure(path: Path) -> list[str]:
    if not path.exists():
        return []
    problems = []
    for reference in target_object_inputs(ast.parse(path.read_text())):
        problems.append(
            f"{path.name}: {reference} is a dtk target object. A build step may "
            "permute what our compiler produced; being handed retail's object "
            "lets it write that instead, and no rule about embedded constants "
            "can see it. See docs/object-post-processors.md."
        )
    return problems


def main() -> int:
    scripts = sorted(TOOLS.glob("fix_*.py"))
    if not scripts:
        print("no object post-processors found", file=sys.stderr)
        return 1
    problems = [problem for script in scripts for problem in check(script)]
    problems += check_configure(CONFIGURE)
    if problems:
        print("object post-processor violations:")
        for problem in problems:
            print(f"  - {problem}")
        return 1
    print(f"object post-processors OK: {len(scripts)} steps checked")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
