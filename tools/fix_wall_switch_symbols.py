#!/usr/bin/env python3
"""Rename the compiler's wall-state dispatch table to its retail symbol."""

import argparse
import shutil
import subprocess
import sys
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path, help="compiled e_wall_stage11 object")
    parser.add_argument("stamp", type=Path, help="stamp file to write on success")
    parser.add_argument("--objcopy", type=Path, required=True)
    parser.add_argument("--objdump", type=Path, required=True)
    args = parser.parse_args()

    symbols = subprocess.run(
        [str(args.objdump), "-t", str(args.object)],
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    if "00000040 @292" not in symbols or "jumptable_8_data_17338" in symbols:
        raise SystemExit("e_wall_stage11 dispatch table symbol layout changed")

    temporary = args.object.parent / (args.object.name + ".symbols.tmp")
    subprocess.run(
        [
            str(args.objcopy),
            "--redefine-sym",
            "@292=jumptable_8_data_17338",
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
