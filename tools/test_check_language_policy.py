#!/usr/bin/env python3

from __future__ import annotations

import contextlib
import io
import json
import os
import subprocess
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import tools.check_language_policy as checker


REPOSITORY_ROOT = Path(__file__).resolve().parent.parent


def make_policy(**overrides: list[str]) -> dict[str, list[str]]:
    policy = {
        "managed_prefixes": ["game/"],
        "library_prefixes": ["dolphin/"],
        "confirmed_c_sources": [],
        "pending_c_evidence": [],
        "protected_cpp_c_sources": [],
        "c_sources_compiled_as_cpp": [],
        "legacy_cpp_c_sources": [],
        "deferred_sources": [],
    }
    policy.update(overrides)
    return policy


def clean_git_environment() -> dict[str, str]:
    """Keep nested repositories isolated from a calling Git hook."""
    return {
        key: value for key, value in os.environ.items() if not key.startswith("GIT_")
    }


class PolicyValidationTests(unittest.TestCase):
    def load_policy(self, policy: dict[str, list[str]]) -> dict[str, list[str]]:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "language_policy.json"
            path.write_text(json.dumps(policy), encoding="utf-8")
            return checker.load_policy(path)

    def test_empty_pending_evidence_is_allowed(self) -> None:
        policy = make_policy()
        self.assertEqual(self.load_policy(policy), policy)

    def test_pending_evidence_is_rejected(self) -> None:
        policy = make_policy(pending_c_evidence=["game/unit.c"])
        with self.assertRaisesRegex(ValueError, "pending C evidence is not permitted"):
            self.load_policy(policy)

    def test_managed_and_library_prefixes_cannot_overlap(self) -> None:
        policy = make_policy(library_prefixes=["game/vendor/"])
        with self.assertRaisesRegex(ValueError, "managed and library prefixes overlap"):
            self.load_policy(policy)

    def test_policy_source_paths_must_be_canonical(self) -> None:
        policy = make_policy(confirmed_c_sources=["game/../escape.c"])
        with self.assertRaisesRegex(ValueError, "contains a non-canonical path"):
            self.load_policy(policy)

    def test_policy_sources_must_be_managed_game_code(self) -> None:
        policy = make_policy(confirmed_c_sources=["dolphin/unit.c"])
        with self.assertRaisesRegex(ValueError, "outside managed game code"):
            self.load_policy(policy)

    def test_policy_lists_must_be_sorted_and_unique(self) -> None:
        policy = make_policy(
            confirmed_c_sources=["game/z.c", "game/a.c", "game/a.c"]
        )
        with self.assertRaisesRegex(ValueError, "must be sorted and contain no duplicates"):
            self.load_policy(policy)

    def test_source_classifications_cannot_overlap(self) -> None:
        policy = make_policy(
            confirmed_c_sources=["game/unit.c"],
            c_sources_compiled_as_cpp=["game/unit.c"],
        )
        with self.assertRaisesRegex(ValueError, "confirmed C and reviewed C/C\\+\\+ mode overlap"):
            self.load_policy(policy)

    def test_protected_debt_must_stay_in_protected_areas(self) -> None:
        policy = make_policy(protected_cpp_c_sources=["game/unit.c"])
        with self.assertRaisesRegex(ValueError, "outside a protected area"):
            self.load_policy(policy)

    def test_legacy_debt_must_stay_in_protected_areas(self) -> None:
        policy = make_policy(legacy_cpp_c_sources=["game/unit.c"])
        with self.assertRaisesRegex(ValueError, "outside a protected area"):
            self.load_policy(policy)


class HookContractTests(unittest.TestCase):
    def test_rename_only_commit_reaches_language_policy_check(self) -> None:
        hook = (REPOSITORY_ROOT / ".githooks/pre-commit").read_text(encoding="utf-8")
        self.assertIn(
            "staged=$(git diff --cached --name-only --diff-filter=ACMR)",
            hook,
        )


class StagedPolicyTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary.name)
        self.configure = self.root / "configure.py"
        self.configure.write_text("", encoding="utf-8")
        self.run_git("init", "-q")
        self.run_git("config", "user.name", "Policy Test")
        self.run_git("config", "user.email", "policy@example.invalid")
        self.root_patch = patch.object(checker, "ROOT", self.root)
        self.configure_patch = patch.object(checker, "CONFIGURE", self.configure)
        self.root_patch.start()
        self.configure_patch.start()

    def tearDown(self) -> None:
        self.configure_patch.stop()
        self.root_patch.stop()
        self.temporary.cleanup()

    def run_git(self, *arguments: str) -> None:
        subprocess.run(
            ["git", "-c", "core.hooksPath=/dev/null", *arguments],
            cwd=self.root,
            check=True,
            capture_output=True,
            text=True,
            env=clean_git_environment(),
        )

    def write_source(self, relative: str, content: str = "void unit(void) {}") -> Path:
        path = self.root / "src" / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(content, encoding="utf-8")
        return path

    def staged_errors(self, policy: dict[str, list[str]]) -> list[str]:
        with (
            patch.dict(os.environ, clean_git_environment(), clear=True),
            contextlib.redirect_stdout(io.StringIO()),
        ):
            return checker.audit_staged_sources(policy)

    def test_rename_from_cpp_to_c_is_checked(self) -> None:
        source = self.write_source("game/unit.cpp")
        self.run_git("add", ".")
        self.run_git("commit", "-q", "-m", "baseline")
        source.rename(source.with_suffix(".c"))
        self.run_git("add", "-A")

        self.assertEqual(
            self.staged_errors(make_policy()),
            [
                "game/unit.c: new game-owned .c source is forbidden; "
                "use .cpp or add reviewed C evidence"
            ],
        )

    def test_noncanonical_cpp_extensions_are_rejected(self) -> None:
        self.write_source("game/one.cc")
        self.write_source("game/two.cxx")
        self.write_source("game/three.C")
        self.run_git("add", ".")

        self.assertEqual(
            self.staged_errors(make_policy()),
            [
                "game/one.cc: game-owned C++ source must use the .cpp extension",
                "game/three.C: game-owned C++ source must use the .cpp extension",
                "game/two.cxx: game-owned C++ source must use the .cpp extension",
            ],
        )

    def test_canonical_cpp_addition_is_allowed(self) -> None:
        self.write_source("game/unit.cpp")
        self.run_git("add", ".")
        self.assertEqual(self.staged_errors(make_policy()), [])

    def test_source_outside_reviewed_prefixes_is_rejected(self) -> None:
        self.write_source("new_module/unit.cpp")
        self.run_git("add", ".")

        self.assertEqual(
            self.staged_errors(make_policy()),
            [
                "new_module/unit.cpp: source path is outside reviewed "
                "game/library prefixes"
            ],
        )

    def test_known_library_source_is_outside_game_policy(self) -> None:
        self.write_source("dolphin/unit.c")
        self.run_git("add", ".")
        self.assertEqual(self.staged_errors(make_policy()), [])

    def test_reviewed_c_rename_is_allowed(self) -> None:
        source = self.write_source("game/unit.cpp")
        self.run_git("add", ".")
        self.run_git("commit", "-q", "-m", "baseline")
        source.rename(source.with_suffix(".c"))
        self.run_git("add", "-A")

        policy = make_policy(confirmed_c_sources=["game/unit.c"])
        self.assertEqual(self.staged_errors(policy), [])

    def test_nodeferred_is_not_treated_as_deferred(self) -> None:
        self.configure.write_text(
            'Object(Matching, "game/unit.cpp", extra_cflags=["-inline nodeferred"])\n',
            encoding="utf-8",
        )
        self.assertEqual(self.staged_errors(make_policy()), [])

    def test_deferred_still_requires_reviewed_policy(self) -> None:
        self.configure.write_text(
            'Object(Matching, "game/unit.cpp", '
            'extra_cflags=["-inline noauto,deferred"])\n',
            encoding="utf-8",
        )
        self.assertEqual(
            self.staged_errors(make_policy()),
            ["game/unit.cpp: uses deferred inline without reviewed policy evidence"],
        )

    def test_reviewed_deferred_is_allowed(self) -> None:
        self.configure.write_text(
            'Object(Matching, "game/unit.cpp", '
            'extra_cflags=["-inline noauto,deferred"])\n',
            encoding="utf-8",
        )
        policy = make_policy(deferred_sources=["game/unit.cpp"])
        self.assertEqual(self.staged_errors(policy), [])

    def test_modified_protected_c_debt_is_blocked_until_migration(self) -> None:
        source = self.write_source("autosaveD/unit.c")
        self.run_git("add", ".")
        self.run_git("commit", "-q", "-m", "baseline")
        source.write_text("void unit(void) { int changed = 1; }\n", encoding="utf-8")
        self.run_git("add", "-A")

        policy = make_policy(
            managed_prefixes=["autosaveD/"],
            protected_cpp_c_sources=["autosaveD/unit.c"],
        )
        self.assertEqual(
            self.staged_errors(policy),
            [
                "autosaveD/unit.c: protected C++/C-mode work must be "
                "coordinated and migrated to .cpp"
            ],
        )

    def test_modified_legacy_cpp_c_path_is_blocked_until_migration(self) -> None:
        source = self.write_source("advertiseD/unit.c")
        self.run_git("add", ".")
        self.run_git("commit", "-q", "-m", "baseline")
        source.write_text("void unit(void) { int changed = 1; }\n", encoding="utf-8")
        self.run_git("add", "-A")

        policy = make_policy(
            managed_prefixes=["advertiseD/"],
            legacy_cpp_c_sources=["advertiseD/unit.c"],
        )
        self.assertEqual(
            self.staged_errors(policy),
            [
                "advertiseD/unit.c: staged legacy C++ work must migrate "
                "from .c to .cpp"
            ],
        )


class ConfiguredPolicyTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary = tempfile.TemporaryDirectory()
        self.configure = Path(self.temporary.name) / "configure.py"
        self.configure.write_text("", encoding="utf-8")
        self.configure_patch = patch.object(checker, "CONFIGURE", self.configure)
        self.configure_patch.start()

    def tearDown(self) -> None:
        self.configure_patch.stop()
        self.temporary.cleanup()

    def configured_errors(
        self,
        commands: dict[str, dict[str, object]],
        policy: dict[str, list[str]] | None = None,
        physical_sources: set[str] | None = None,
    ) -> list[str]:
        if physical_sources is None:
            physical_sources = set(commands)
        with (
            patch.object(checker, "parse_source_commands", return_value=commands),
            patch.object(
                checker,
                "physical_source_paths",
                return_value=physical_sources,
            ),
            contextlib.redirect_stdout(io.StringIO()),
        ):
            return checker.audit_configured_build(policy or make_policy())

    def test_configured_cpp_requires_cpp_extension(self) -> None:
        errors = self.configured_errors(
            {"game/unit.cc": {"language": "c++", "inline_modes": ["auto"]}}
        )
        self.assertEqual(
            errors,
            ["game/unit.cc: game-owned C++ source must use the .cpp extension"],
        )

    def test_configured_source_outside_reviewed_prefixes_is_rejected(self) -> None:
        errors = self.configured_errors(
            {"new_module/unit.cpp": {"language": "c++", "inline_modes": ["auto"]}}
        )
        self.assertEqual(
            errors,
            [
                "new_module/unit.cpp: configured source is outside reviewed "
                "game/library prefixes"
            ],
        )

    def test_configured_known_library_is_outside_game_policy(self) -> None:
        errors = self.configured_errors(
            {"dolphin/unit.c": {"language": "c", "inline_modes": ["auto"]}}
        )
        self.assertEqual(errors, [])

    def test_physical_source_without_compiler_command_is_rejected(self) -> None:
        errors = self.configured_errors(
            {"game/unit.cpp": {"language": "c++", "inline_modes": ["auto"]}},
            physical_sources={"game/dormant.cpp", "game/unit.cpp"},
        )
        self.assertEqual(
            errors,
            ["game/dormant.cpp: source file has no configured compiler command"],
        )

    def test_compiler_command_without_source_file_is_rejected(self) -> None:
        errors = self.configured_errors(
            {"game/missing.cpp": {"language": "c++", "inline_modes": ["auto"]}},
            physical_sources=set(),
        )
        self.assertEqual(
            errors,
            ["game/missing.cpp: compiler command does not reference a source file"],
        )

    def test_noncanonical_configured_path_is_rejected(self) -> None:
        source = "dolphin/../new_module/unit.cpp"
        errors = self.configured_errors(
            {source: {"language": "c++", "inline_modes": ["auto"]}},
            physical_sources={source},
        )
        self.assertEqual(
            errors,
            [f"{source}: configured source path is not canonical"],
        )

    def test_effective_nodeferred_does_not_require_allowlist(self) -> None:
        errors = self.configured_errors(
            {
                "game/unit.cpp": {
                    "language": "c++",
                    "inline_modes": ["auto", "nodeferred"],
                }
            }
        )
        self.assertEqual(errors, [])

    def test_effective_deferred_requires_allowlist(self) -> None:
        errors = self.configured_errors(
            {
                "game/unit.cpp": {
                    "language": "c++",
                    "inline_modes": ["auto", "deferred,noauto"],
                }
            }
        )
        self.assertEqual(
            errors,
            [
                "game/unit.cpp: effective deferred inline mode has no "
                "reviewed evidence"
            ],
        )

    def test_unreviewed_configured_c_source_is_rejected(self) -> None:
        errors = self.configured_errors(
            {"game/unit.c": {"language": "c", "inline_modes": ["auto"]}}
        )
        self.assertEqual(
            errors,
            ["game/unit.c: game-owned C source is not in the reviewed allowlist"],
        )

    def test_stale_confirmed_c_entry_is_rejected(self) -> None:
        errors = self.configured_errors(
            {"game/unit.cpp": {"language": "c++", "inline_modes": ["auto"]}},
            policy=make_policy(confirmed_c_sources=["game/missing.c"]),
        )
        self.assertEqual(
            errors,
            ["game/missing.c: C policy entry has no configured source"],
        )

    def test_stale_deferred_entry_is_rejected(self) -> None:
        errors = self.configured_errors(
            {"game/unit.cpp": {"language": "c++", "inline_modes": ["auto"]}},
            policy=make_policy(deferred_sources=["game/unit.cpp"]),
        )
        self.assertEqual(
            errors,
            [
                "game/unit.cpp: approved deferred entry is not effectively "
                "compiled with deferred"
            ],
        )

    def test_multiple_object_inline_overrides_are_rejected(self) -> None:
        self.configure.write_text(
            'Object(Matching, "game/unit.cpp", '
            'extra_cflags=["-inline auto", "-inline deferred"])\n',
            encoding="utf-8",
        )
        errors = self.configured_errors(
            {
                "game/unit.cpp": {
                    "language": "c++",
                    "inline_modes": ["auto", "deferred"],
                }
            },
            policy=make_policy(deferred_sources=["game/unit.cpp"]),
        )
        self.assertEqual(
            errors,
            [
                "game/unit.cpp: multiple object-level -inline overrides: "
                "['-inline auto', '-inline deferred']"
            ],
        )


if __name__ == "__main__":
    unittest.main()
