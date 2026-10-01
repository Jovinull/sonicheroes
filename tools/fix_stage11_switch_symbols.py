#!/usr/bin/env python3
"""Rename compiler-generated enemy state tables to their retail symbols."""

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

TABLES = {
    "e_wall_stage11.o": ("@292", "jumptable_8_data_17338"),
    "e_turtle_stage11.o": ("@208", "jumptable_8_data_17BF0"),
}


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path, help="compiled enemy REL object")
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
    table = TABLES.get(args.object.name)
    if table is None:
        raise SystemExit(f"unexpected enemy object: {args.object.name}")
    anonymous, retail = table
    if f"00000040 {retail}" in symbols and anonymous not in symbols:
        args.stamp.touch()
        return
    if f"00000040 {anonymous}" not in symbols or retail in symbols:
        raise SystemExit(f"{args.object.name} dispatch table symbol layout changed")

    temporary = args.object.parent / (args.object.name + ".symbols.tmp")
    subprocess.run(
        [
            str(args.objcopy),
            "--redefine-sym",
            f"{anonymous}={retail}",
            str(args.object),
            str(temporary),
        ],
        check=True,
    )
    shutil.copystat(args.object, temporary)
    temporary.replace(args.object)
    updated = subprocess.run(
        [str(args.objdump), "-t", str(args.object)],
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    if f"00000040 {retail}" not in updated:
        raise SystemExit(f"failed to rename {args.object.name} dispatch table")
    args.stamp.touch()


if __name__ == "__main__":
    sys.exit(main())
