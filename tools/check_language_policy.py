#!/usr/bin/env python3

"""Enforce the reviewed C/C++ and inline policy for game-owned sources."""

from __future__ import annotations

import argparse
import ast
import json
import re
import subprocess
import sys
from pathlib import Path, PurePosixPath
from typing import Any


ROOT = Path(__file__).resolve().parent.parent
DEFAULT_POLICY = ROOT / "config/G9SE8P/language_policy.json"
CONFIGURE = ROOT / "configure.py"
PROTECTED_PREFIXES = ("advertiseD/", "autosaveD/")
CPP_STYLE_SUFFIXES = {".cc", ".cp", ".cpp", ".cxx", ".c++"}


def load_policy(path: Path) -> dict[str, Any]:
    with path.open(encoding="utf-8") as stream:
        policy = json.load(stream)

    list_keys = (
        "managed_prefixes",
        "library_prefixes",
        "confirmed_c_sources",
        "pending_c_evidence",
        "protected_cpp_c_sources",
        "c_sources_compiled_as_cpp",
        "legacy_cpp_c_sources",
        "deferred_sources",
    )
    for key in list_keys:
        values = policy.get(key)
        if not isinstance(values, list) or not all(isinstance(value, str) for value in values):
            raise ValueError(f"{path}: {key} must be a list of strings")
        if values != sorted(set(values)):
            raise ValueError(f"{path}: {key} must be sorted and contain no duplicates")

    for key in ("managed_prefixes", "library_prefixes"):
        for prefix in policy[key]:
            if (
                not prefix
                or not prefix.endswith("/")
                or not is_canonical_relative_path(prefix.removesuffix("/"))
            ):
                raise ValueError(
                    f"{path}: {key} entries must be relative directory prefixes: {prefix!r}"
                )

    managed_prefixes = policy["managed_prefixes"]
    library_prefixes = policy["library_prefixes"]
    for managed_prefix in managed_prefixes:
        for library_prefix in library_prefixes:
            if (
                managed_prefix.startswith(library_prefix)
                or library_prefix.startswith(managed_prefix)
            ):
                raise ValueError(
                    f"{path}: managed and library prefixes overlap: "
                    f"{managed_prefix}, {library_prefix}"
                )

    if policy["pending_c_evidence"]:
        raise ValueError(
            f"{path}: pending C evidence is not permitted; resolve the classification "
            "before changing the source policy"
        )

    source_keys = (
        "confirmed_c_sources",
        "pending_c_evidence",
        "protected_cpp_c_sources",
        "c_sources_compiled_as_cpp",
        "legacy_cpp_c_sources",
        "deferred_sources",
    )
    for key in source_keys:
        for source in policy[key]:
            if not is_canonical_relative_path(source):
                raise ValueError(f"{path}: {key} contains a non-canonical path: {source!r}")
            if not is_managed(source, managed_prefixes):
                raise ValueError(f"{path}: {key} entry is outside managed game code: {source}")

    groups = (
        set(policy["confirmed_c_sources"]),
        set(policy["pending_c_evidence"]),
        set(policy["protected_cpp_c_sources"]),
        set(policy["c_sources_compiled_as_cpp"]),
        set(policy["legacy_cpp_c_sources"]),
    )
    labels = (
        "confirmed C",
        "pending C",
        "protected C++/C-mode debt",
        "reviewed C/C++ mode",
        "legacy C++",
    )
    for index, group in enumerate(groups):
        for other_index in range(index + 1, len(groups)):
            overlap = group & groups[other_index]
            if overlap:
                joined = ", ".join(sorted(overlap))
                raise ValueError(f"{path}: {labels[index]} and {labels[other_index]} overlap: {joined}")

    for source in policy["protected_cpp_c_sources"]:
        if not source.startswith(PROTECTED_PREFIXES):
            raise ValueError(
                f"{path}: protected C++/C-mode debt is outside a protected area: {source}"
            )

    for source in policy["legacy_cpp_c_sources"]:
        if not source.startswith(PROTECTED_PREFIXES):
            raise ValueError(f"{path}: legacy C++/.c debt is outside a protected area: {source}")

    return policy


def is_managed(source: str, prefixes: list[str]) -> bool:
    return any(source.startswith(prefix) for prefix in prefixes)


def is_canonical_relative_path(value: str) -> bool:
    path = PurePosixPath(value)
    return (
        bool(value)
        and "\\" not in value
        and not path.is_absolute()
        and ".." not in path.parts
        and path.as_posix() == value
    )


def is_cpp_style_suffix(suffix: str) -> bool:
    return suffix == ".C" or suffix.lower() in CPP_STYLE_SUFFIXES


def inline_mode_enabled(value: str, mode: str) -> bool:
    """Return whether an exact comma-separated inline mode is enabled."""
    modes = {part for part in re.sub(r"\s+", "", value).split(",") if part}
    return mode in modes


def parse_source_commands() -> dict[str, dict[str, Any]]:
    try:
        result = subprocess.run(
            ["ninja", "-t", "commands", "all_source"],
            cwd=ROOT,
            check=True,
            capture_output=True,
            text=True,
        )
    except FileNotFoundError as exc:
        raise RuntimeError("ninja was not found; run this check in a configured build tree") from exc
    except subprocess.CalledProcessError as exc:
        detail = exc.stderr.strip() or exc.stdout.strip()
        raise RuntimeError(f"could not read Ninja commands: {detail}") from exc

    commands: dict[str, dict[str, Any]] = {}
    source_pattern = re.compile(r"(?:^|\s)-c\s+src/([^\s\"']+)")
    language_pattern = re.compile(r"(?:^|\s)-lang=(c\+\+|c)(?=\s|$)")
    inline_pattern = re.compile(r"(?:^|\s)-inline\s+(.+?)(?=\s+-[A-Za-z]|\s+&&|$)")

    for line in result.stdout.splitlines():
        source_match = source_pattern.search(line)
        if source_match is None or "mwcceppc.exe" not in line:
            continue

        source = source_match.group(1)
        languages = language_pattern.findall(line)
        if languages:
            language = languages[-1]
        elif is_cpp_style_suffix(Path(source).suffix):
            language = "c++"
        else:
            language = "c"

        inline_modes = [
            re.sub(r"\s+", "", mode.strip("\"' "))
            for mode in inline_pattern.findall(line)
        ]
        record = {"language": language, "inline_modes": inline_modes}
        previous = commands.get(source)
        if previous is not None and previous != record:
            raise RuntimeError(f"{source}: conflicting compiler commands")
        commands[source] = record

    if not commands:
        raise RuntimeError("no Metrowerks source commands found; run python configure.py first")
    return commands


def physical_source_paths() -> set[str]:
    source_root = ROOT / "src"
    return {
        path.relative_to(source_root).as_posix()
        for path in source_root.rglob("*")
        if path.is_file()
        and (path.suffix == ".c" or is_cpp_style_suffix(path.suffix))
    }


def static_inline_overrides(errors: list[str], policy: dict[str, Any]) -> None:
    tree = ast.parse(CONFIGURE.read_text(encoding="utf-8"), filename=str(CONFIGURE))
    prefixes = policy["managed_prefixes"]
    deferred = set(policy["deferred_sources"])

    for node in ast.walk(tree):
        if not isinstance(node, ast.Call) or not isinstance(node.func, ast.Name):
            continue
        if node.func.id != "Object" or len(node.args) < 2:
            continue

        source_node = node.args[1]
        if not isinstance(source_node, ast.Constant) or not isinstance(source_node.value, str):
            continue
        source = source_node.value
        if not is_managed(source, prefixes):
            continue

        flags: list[str] = []
        for keyword in node.keywords:
            if keyword.arg != "extra_cflags" or not isinstance(keyword.value, (ast.List, ast.Tuple)):
                continue
            for element in keyword.value.elts:
                if isinstance(element, ast.Constant) and isinstance(element.value, str):
                    flags.append(element.value.strip())

        inline_flags = [flag for flag in flags if flag.startswith("-inline ")]
        if len(inline_flags) > 1:
            errors.append(f"{source}: multiple object-level -inline overrides: {inline_flags}")
        if any(
            inline_mode_enabled(flag.removeprefix("-inline "), "deferred")
            for flag in inline_flags
        ) and source not in deferred:
            errors.append(f"{source}: uses deferred inline without reviewed policy evidence")


def audit_configured_build(policy: dict[str, Any]) -> list[str]:
    errors: list[str] = []
    commands = parse_source_commands()
    prefixes = policy["managed_prefixes"]
    library_prefixes = policy["library_prefixes"]
    confirmed_c = set(policy["confirmed_c_sources"])
    pending_c = set(policy["pending_c_evidence"])
    protected_cpp_c = set(policy["protected_cpp_c_sources"])
    allowed_c = confirmed_c | pending_c | protected_cpp_c
    cpp_mode_c = set(policy["c_sources_compiled_as_cpp"])
    legacy_cpp = set(policy["legacy_cpp_c_sources"])
    deferred = set(policy["deferred_sources"])

    managed = {source: record for source, record in commands.items() if is_managed(source, prefixes)}
    physical_sources = physical_source_paths()
    for source in sorted(physical_sources - commands.keys()):
        errors.append(f"{source}: source file has no configured compiler command")
    for source in sorted(commands.keys() - physical_sources):
        errors.append(f"{source}: compiler command does not reference a source file")

    for source in sorted(commands):
        if not is_canonical_relative_path(source):
            errors.append(f"{source}: configured source path is not canonical")
            continue
        if not is_managed(source, prefixes) and not is_managed(source, library_prefixes):
            errors.append(
                f"{source}: configured source is outside reviewed game/library prefixes"
            )
    actual_legacy: set[str] = set()
    actual_deferred: set[str] = set()

    for source, record in sorted(managed.items()):
        language = record["language"]
        inline_modes = record["inline_modes"]

        if language == "c":
            if source not in allowed_c:
                errors.append(f"{source}: game-owned C source is not in the reviewed allowlist")
            if not source.endswith(".c"):
                errors.append(f"{source}: compiles as C but does not use the .c extension")
        elif language == "c++":
            if source.endswith(".c"):
                actual_legacy.add(source)
                if source not in legacy_cpp and source not in cpp_mode_c:
                    errors.append(f"{source}: new C++ source uses .c; new game code must use .cpp")
            elif not source.endswith(".cpp"):
                errors.append(f"{source}: game-owned C++ source must use the .cpp extension")
        else:
            errors.append(f"{source}: unknown effective language {language!r}")

        if len(inline_modes) > 2:
            errors.append(f"{source}: ambiguous inline flags in compiler command: {inline_modes}")
        effective_inline = inline_modes[-1] if inline_modes else ""
        if inline_mode_enabled(effective_inline, "deferred"):
            actual_deferred.add(source)
            if source not in deferred:
                errors.append(f"{source}: effective deferred inline mode has no reviewed evidence")

    for source in sorted(allowed_c):
        record = managed.get(source)
        if record is None:
            errors.append(f"{source}: C policy entry has no configured source")
        elif record["language"] != "c":
            errors.append(f"{source}: C policy entry now compiles as {record['language']}; update the policy")

    missing_legacy = legacy_cpp - actual_legacy
    for source in sorted(missing_legacy):
        errors.append(f"{source}: legacy C++/.c entry no longer exists; remove or update the policy entry")

    missing_cpp_mode_c = cpp_mode_c - actual_legacy
    for source in sorted(missing_cpp_mode_c):
        errors.append(
            f"{source}: reviewed C/C++-mode entry is not a configured .c source compiled as C++"
        )

    missing_deferred = deferred - actual_deferred
    for source in sorted(missing_deferred):
        errors.append(f"{source}: approved deferred entry is not effectively compiled with deferred")

    static_inline_overrides(errors, policy)

    if not errors:
        cpp_count = sum(record["language"] == "c++" for record in managed.values())
        c_count = sum(record["language"] == "c" for record in managed.values())
        print(
            "language policy OK: "
            f"{len(managed)} managed sources "
            f"({cpp_count} C++, {c_count} C, "
            f"{len(pending_c)} pending evidence, "
            f"{len(protected_cpp_c)} protected C++/C-mode debt, "
            f"{len(cpp_mode_c)} reviewed C/C++-mode, "
            f"{len(actual_deferred)} deferred)"
        )
    return errors


def audit_staged_sources(policy: dict[str, Any]) -> list[str]:
    errors: list[str] = []
    result = subprocess.run(
        ["git", "diff", "--cached", "--name-only", "--diff-filter=ACMR"],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    )
    prefixes = policy["managed_prefixes"]
    library_prefixes = policy["library_prefixes"]
    confirmed_c = set(policy["confirmed_c_sources"])
    pending_c = set(policy["pending_c_evidence"])
    protected_cpp_c = set(policy["protected_cpp_c_sources"])
    cpp_mode_c = set(policy["c_sources_compiled_as_cpp"])
    legacy_cpp = set(policy["legacy_cpp_c_sources"])

    for path in result.stdout.splitlines():
        if not path.startswith("src/"):
            continue
        source = path.removeprefix("src/")
        suffix = Path(source).suffix
        if not is_managed(source, prefixes):
            if (
                not is_managed(source, library_prefixes)
                and (suffix == ".c" or is_cpp_style_suffix(suffix))
            ):
                errors.append(
                    f"{source}: source path is outside reviewed game/library prefixes"
                )
            continue
        if suffix != ".cpp" and is_cpp_style_suffix(suffix):
            errors.append(f"{source}: game-owned C++ source must use the .cpp extension")
            continue
        if suffix != ".c":
            continue
        if source in pending_c:
            errors.append(
                f"{source}: a staged source cannot remain pending C evidence; "
                "resolve the classification before changing it"
            )
        elif source in protected_cpp_c:
            errors.append(
                f"{source}: protected C++/C-mode work must be coordinated and "
                "migrated to .cpp"
            )
        elif source in legacy_cpp:
            errors.append(
                f"{source}: staged legacy C++ work must migrate from .c to .cpp"
            )
        elif source not in confirmed_c and source not in cpp_mode_c:
            errors.append(
                f"{source}: new game-owned .c source is forbidden; use .cpp or add reviewed C evidence"
            )

    static_inline_overrides(errors, policy)
    if not errors:
        print("staged language policy OK")
    return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--policy", type=Path, default=DEFAULT_POLICY)
    parser.add_argument(
        "--staged",
        action="store_true",
        help="check newly staged source paths without requiring a configured build",
    )
    args = parser.parse_args()

    try:
        policy = load_policy(args.policy)
        errors = audit_staged_sources(policy) if args.staged else audit_configured_build(policy)
    except (OSError, ValueError, RuntimeError, subprocess.CalledProcessError) as exc:
        print(f"language policy check failed: {exc}", file=sys.stderr)
        return 1

    if errors:
        print("language policy violations:", file=sys.stderr)
        for error in errors:
            print(f"  - {error}", file=sys.stderr)
        print("See docs/language-policy.md.", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
