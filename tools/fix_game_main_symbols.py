#!/usr/bin/env python3

"""Restore main.cpp's data-symbol names after compilation.

The original object addresses its four writable strings as externally visible
symbols.  Giving their definitions those names in the C++ source lets
CodeWarrior fold their addresses into one local base, changing AppEventHandler's
register allocation.  The staging names preserve the original declaration
order while the retail names at each use preserve the original code.  Renaming
the definitions afterward changes only ELF symbol metadata.
"""

import argparse
import shutil
import subprocess
import sys
from pathlib import Path


RENAMES = (
    ("mainAppName", "lbl_802409C8"),
    ("mainRenderWareError", "lbl_802409F4"),
    ("mainRasterCharsetError", "lbl_80240A14"),
    ("mainStringTableName", "lbl_80240A80"),
    ("__nw__9TMainTaskFUl", "fn_80057644"),
    ("__ct__9TMainTaskFv", "fn_8001F5A0"),
)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path, help="object file to fix in place")
    parser.add_argument("stamp", type=Path, help="stamp file to write")
    parser.add_argument("--objcopy", type=Path, required=True)
    args = parser.parse_args()

    temporary = args.object.parent / (args.object.name + ".symbols.tmp")
    command = [str(args.objcopy)]
    for source, target in RENAMES:
        command.extend(("--redefine-sym", f"{source}={target}"))
    command.extend((str(args.object), str(temporary)))
    subprocess.run(command, check=True)
    shutil.copystat(args.object, temporary)
    temporary.replace(args.object)
    args.stamp.touch()


if __name__ == "__main__":
    sys.exit(main())
