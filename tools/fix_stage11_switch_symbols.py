#!/usr/bin/env python3
"""Rename compiler-generated enemy state tables to their retail symbols."""

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

SYMBOL_RENAMES = {
    "e_wall_stage11.o": [
        ("@292", "jumptable_8_data_17338", 0x40),
        ("@407", "lbl_8_rodata_1D90", 0x8),
    ],
    "e_turtle_stage11.o": [
        ("@208", "jumptable_8_data_17BF0", 0x40),
        # MWCC emits an anonymous copy of the shared integer-to-float bias.
        ("@372", "lbl_8_rodata_1E80", 0x8),
    ],
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
    renames = SYMBOL_RENAMES.get(args.object.name)
    if renames is None:
        raise SystemExit(f"unexpected enemy object: {args.object.name}")

    temporary = args.object.parent / (args.object.name + ".symbols.tmp")
    command = [str(args.objcopy)]
    pending = []
    for anonymous, retail, size in renames:
        if anonymous in symbols:
            if f"{size:08x} {anonymous}" not in symbols:
                raise SystemExit(f"unexpected {anonymous} size in {args.object.name}")
            pending.append((anonymous, retail, size))
        elif f"{size:08x} {retail}" not in symbols:
            raise SystemExit(f"missing {retail} in {args.object.name}")
    for anonymous, retail, _size in pending:
        command.extend(["--redefine-sym", f"{anonymous}={retail}"])
    if pending:
        subprocess.run(command + [str(args.object), str(temporary)], check=True)
        shutil.copystat(args.object, temporary)
        temporary.replace(args.object)

    updated = subprocess.run(
        [str(args.objdump), "-t", str(args.object)],
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    for anonymous, retail, size in renames:
        if anonymous in updated or f"{size:08x} {retail}" not in updated:
            raise SystemExit(f"failed to rename {anonymous} in {args.object.name}")
    args.stamp.touch()


if __name__ == "__main__":
    sys.exit(main())
