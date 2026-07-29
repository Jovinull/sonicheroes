#!/usr/bin/env python3

"""Restore action.cpp's retail split symbol names."""

import argparse
import shutil
import subprocess
from pathlib import Path


RENAMES = {
    "GetTheLastLeader__Fv": "fn_80018C0C",
    "SetPauseDisable__Fv": "fn_80018C4C",
    "SetPauseEnable__Fv": "fn_80018C64",
    "CheckActionPause__Fv": "fn_80018C7C",
    "GetActionMode__Fv": "fn_80018C98",
    "CheckActionSoftReset__Fv": "fn_80018CA8",
    "RestoreStageConnect__FP6ACTION": "fn_80018CDC",
    "SaveStageConnect__FP6ACTION": "fn_80018D98",
    "IsBonusStageConnect__6ACTIONFi": "fn_80018DC8",
    "IsSpecialStageConnect__6ACTIONFi": "fn_80018DFC",
    "IsSpecialStage__6ACTIONFv": "fn_80018E30",
    "IsBonusStage__6ACTIONFv": "fn_80018E6C",
    "IsSpecialAndBonusStage__6ACTIONFv": "fn_80018EA8",
    "InsertStage__6ACTIONFi": "fn_80018EFC",
    "eventChecker__6ACTIONFv": "fn_80018F38",
    "Action": "lbl_8029C310",
}


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    args = parser.parse_args()

    temporary = args.object.parent / (args.object.name + ".action.tmp")
    command = [str(args.objcopy)]
    for source, target in RENAMES.items():
        command.extend(("--redefine-sym", f"{source}={target}"))
    command.extend((str(args.object), str(temporary)))
    subprocess.run(command, check=True)
    shutil.copystat(args.object, temporary)
    temporary.replace(args.object)
    args.stamp.touch()


if __name__ == "__main__":
    main()
