#!/usr/bin/env python3

"""Normalize MWCC's generated Dice method and adjustor symbol names."""

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
            (
                "EditOnChange__9DiceThunkFP13SETDATA_PARAM="
                "EditOnChange__11TObjS33DiceFP13SETDATA_PARAM"
            ),
            "--redefine-sym",
            (
                "@40@EditOnChange__9DiceThunkFP13SETDATA_PARAM="
                "AdjustorEditOnChange__11TObjS33DiceFP13SETDATA_PARAM"
            ),
            "--redefine-sym",
            "diceDisplayNameRef=diceDisplayName",
            "--redefine-sym",
            "diceFieldTypesRef=diceFieldTypes",
            "--redefine-sym",
            "diceFieldNamesRef=diceFieldNames",
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
