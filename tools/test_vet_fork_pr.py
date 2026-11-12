"""Tests for tools/vet_fork_pr.py: the filter that decides whether a fork pull request may be built
next to the original game files. Each test builds a throwaway Git repository."""

import os
import subprocess
import tempfile
import unittest
from pathlib import Path

from tools import vet_fork_pr

CONFIGURE_BASE = """config.libs = [
    {
        "lib": "game",
        "objects": [
            Object(Matching, "game/a.cpp"),
            Object(Matching, "game/b.cpp", extra_cflags=["-Cpp_exceptions on"]),
        ],
    },
]
"""


class VetForkPrTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = Path(self.tmp.name)
        self.prev = os.getcwd()
        os.chdir(self.root)
        self.git("init", "-q", "-b", "main")
        self.git("config", "user.email", "t@example.invalid")
        self.git("config", "user.name", "t")
        self.write("configure.py", CONFIGURE_BASE)
        self.write("config/G9SE8P/splits.txt", "Sections:\n")
        self.write("src/game/a.cpp", "int a;\n")
        self.git("add", "-A")
        self.git("commit", "-q", "-m", "base")
        self.git("switch", "-q", "-c", "pr")

    def tearDown(self):
        os.chdir(self.prev)
        self.tmp.cleanup()

    def git(self, *args):
        return subprocess.run(["git", *args], capture_output=True, text=True, check=True).stdout

    def write(self, rel, text):
        p = self.root / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text, encoding="utf-8")

    def vet(self):
        self.git("add", "-A")
        self.git("commit", "-q", "-m", "pr")
        head = self.git("rev-parse", "HEAD").strip()
        return vet_fork_pr.vet("main", head)

    def assertRefused(self, needle):
        bad, _ = self.vet()
        self.assertTrue(any(needle in b for b in bad), (needle, bad))

    # --- accepted ---------------------------------------------------------------------------
    def test_additive_decompilation_pr_passes(self):
        self.write("src/game/fn_80000000.cpp", 'extern "C" void fn_80000000() {}\n')
        self.write("config/G9SE8P/splits.txt", "Sections:\ngame/fn_80000000.cpp:\n\t.text start:0x1 end:0x2\n")
        cfg = CONFIGURE_BASE.replace(
            '            Object(Matching, "game/b.cpp", extra_cflags=["-Cpp_exceptions on"]),\n',
            '            Object(Matching, "game/b.cpp", extra_cflags=["-Cpp_exceptions on"]),\n'
            '            Object(Matching, "game/fn_80000000.cpp", extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"]),\n',
        )
        self.write("configure.py", cfg)
        bad, _ = self.vet()
        self.assertEqual(bad, [])

    def test_docs_and_headers_pass(self):
        self.write("docs/note.md", "text\n")
        self.write("include/game/x.h", "struct X { int a; };\n")
        bad, _ = self.vet()
        self.assertEqual(bad, [])

    # --- refused paths ----------------------------------------------------------------------
    def test_workflow_change_refused(self):
        self.write(".github/workflows/build.yml", "name: x\n")
        self.assertRefused(".github/workflows/build.yml")

    def test_tools_change_refused(self):
        self.write("tools/fix_evil.py", "print(1)\n")
        self.assertRefused("tools/fix_evil.py")

    def test_hooks_and_agent_files_refused(self):
        self.write(".githooks/pre-commit", "#!/bin/sh\n")
        self.write("AGENTS.md", "x\n")
        self.write(".agents/scripts/x.py", "x\n")
        bad, _ = self.vet()
        for p in (".githooks/pre-commit", "AGENTS.md", ".agents/scripts/x.py"):
            self.assertTrue(any(p in b for b in bad), p)

    def test_config_yml_and_hashes_refused(self):
        self.write("config/G9SE8P/config.yml", "object_base: /\n")
        self.write("config/G9SE8P/build.sha1", "0  x\n")
        bad, _ = self.vet()
        self.assertEqual(len(bad), 2)

    def test_assembly_file_refused(self):
        self.write("src/game/evil.s", ".incbin \"/orig/G9SE8P/sys/main.dol\"\n")
        self.assertRefused("src/game/evil.s")

    def test_path_traversal_and_odd_names_refused(self):
        self.write("src/game/ok name.cpp", "int x;\n")
        self.assertRefused("src/game/ok name.cpp")

    def test_binary_refused(self):
        (self.root / "src/game").mkdir(parents=True, exist_ok=True)
        (self.root / "src/game/blob.cpp").write_bytes(b"\x00\x01\x02\xff" * 20)
        self.assertRefused("binary")

    def test_symlink_refused(self):
        (self.root / "src/game").mkdir(parents=True, exist_ok=True)
        os.symlink("/etc/passwd", self.root / "src/game/link.cpp")
        self.assertRefused("mode")

    def test_executable_bit_refused(self):
        self.write("src/game/exec.cpp", "int x;\n")
        os.chmod(self.root / "src/game/exec.cpp", 0o755)
        self.assertRefused("mode")

    def test_rename_is_seen_as_delete_plus_add(self):
        self.git("mv", "src/game/a.cpp", "src/game/c.cpp")
        # --no-renames turns it into delete+add, both on the allowlist: this must stay acceptable
        bad, _ = self.vet()
        self.assertEqual(bad, [])

    # --- configure.py rules -----------------------------------------------------------------
    def test_configure_edit_of_existing_line_refused(self):
        self.write("configure.py", CONFIGURE_BASE.replace('"game/a.cpp"', '"game/a2.cpp"'))
        self.assertRefused("removes or edits")

    def test_configure_arbitrary_python_refused(self):
        self.write("configure.py", CONFIGURE_BASE + "import os\nos.system('id')\n")
        self.assertRefused("not a plain Object")

    def test_configure_object_with_shell_in_flags_refused(self):
        evil = CONFIGURE_BASE.replace(
            '            Object(Matching, "game/a.cpp"),\n',
            '            Object(Matching, "game/a.cpp"),\n'
            '            Object(Matching, "game/n.cpp", extra_cflags=["-i ../../orig"]),\n',
        )
        self.write("configure.py", evil)
        self.assertRefused("not a plain Object")

    def test_configure_flag_with_output_override_refused(self):
        evil = CONFIGURE_BASE.replace(
            '            Object(Matching, "game/a.cpp"),\n',
            '            Object(Matching, "game/a.cpp"),\n'
            '            Object(Matching, "game/n.cpp", extra_cflags=["-o x"]),\n',
        )
        self.write("configure.py", evil)
        self.assertRefused("not a plain Object")

    def test_configure_path_traversal_in_object_refused(self):
        evil = CONFIGURE_BASE.replace(
            '            Object(Matching, "game/a.cpp"),\n',
            '            Object(Matching, "game/a.cpp"),\n            Object(Matching, "game/$(id).cpp"),\n',
        )
        self.write("configure.py", evil)
        self.assertRefused("not a plain Object")

    # --- source content rules ---------------------------------------------------------------
    def test_include_of_absolute_or_orig_path_refused(self):
        for line in ('#include "/orig/G9SE8P/sys/main.dol"\n', '#include "../../orig/x"\n',
                     '#include <build/G9SE8P/x>\n', '#include_next <x.h>\n', '#import "x"\n'):
            with self.subTest(line=line):
                self.git("reset", "-q", "--hard", "main")
                self.write("src/game/x.cpp", line)
                self.assertRefused("src/game/x.cpp")
                self.git("reset", "-q", "--hard", "main")

    def test_normal_includes_pass(self):
        self.write("src/game/x.cpp", '#include "types.h"\n#include "game/object.h"\n')
        bad, _ = self.vet()
        self.assertEqual(bad, [])

    def test_empty_pr_refused(self):
        self.git("commit", "-q", "--allow-empty", "-m", "nothing")
        head = self.git("rev-parse", "HEAD").strip()
        bad, _ = vet_fork_pr.vet("main", head)
        self.assertTrue(bad)

    def test_requires_full_sha(self):
        with self.assertRaises(SystemExit):
            import sys
            sys.argv = ["vet", "--base", "main", "--head", "abc123"]
            vet_fork_pr.main()


if __name__ == "__main__":
    unittest.main()
