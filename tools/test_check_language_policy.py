#!/usr/bin/env python3

from __future__ import annotations

import contextlib
import io
import os
import subprocess
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import tools.check_language_policy as checker


def make_policy(**overrides: list[str]) -> dict[str, list[str]]:
    policy = {
        "managed_prefixes": ["game/"],
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
    ) -> list[str]:
        with (
            patch.object(checker, "parse_source_commands", return_value=commands),
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


if __name__ == "__main__":
    unittest.main()
