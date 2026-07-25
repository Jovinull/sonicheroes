#!/usr/bin/env python3

###
# Renames the SUD stream's anonymous ELF symbols to their real names.
# mwcc emits @52/@55 for two unnamed rodata labels, and sud_marker/sud_tail
# are local; objcopy has to run after compiling, since neither can be
# spelled in C.
###

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
            "--globalize-symbol=@52",
            "--globalize-symbol=@55",
            "--redefine-sym",
            "@52=lbl_17_rodata_3C8",
            "--redefine-sym",
            "@55=lbl_17_rodata_3D8",
            "--redefine-sym",
            "sud_marker=lbl_17_rodata_3E4",
            "--redefine-sym",
            "sud_tail=lbl_17_rodata_3E8",
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
