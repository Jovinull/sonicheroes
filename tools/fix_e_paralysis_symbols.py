#!/usr/bin/env python3

"""
Rename TObject references to the historical names used by the current project.

e_paralysis.cpp reconstructs the C++ inheritance needed for the retail
exception tables, so mwcc emits the real TObject constructor and destructor
names. The surrounding reconstruction still exports those two addresses under
temporary address-based names. This changes ELF symbol names only.
"""

import argparse
import shutil
import subprocess
import sys
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path, help="object file to fix up in place")
    parser.add_argument("stamp", type=Path, help="stamp file to write on success")
    parser.add_argument("--objcopy", type=Path, required=True, help="path to objcopy")
    args = parser.parse_args()

    temporary = args.object.parent / (args.object.name + ".symbols.tmp")
    subprocess.run(
        [
            str(args.objcopy),
            "--redefine-sym",
            "__ct__7TObjectFP7TObject=fn_80018818",
            "--redefine-sym",
            "__dt__7TObjectFv=dtor_800186D0",
            str(args.object),
            str(temporary),
        ],
        check=True,
    )
    shutil.copystat(args.object, temporary)
    temporary.replace(args.object)
    args.stamp.touch()


if __name__ == "__main__":
    sys.exit(main())
