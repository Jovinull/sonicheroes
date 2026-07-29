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
    "restartStage__6ACTIONFv": "fn_80019034",
    "SetPlayMode__6ACTIONFii": "fn_800191F8",
    "SetTeam__6ACTIONFii": "fn_8001934C",
    "SetStageConnect__6ACTIONFii": "fn_8001936C",
    "InitStageAndTeamInfo__6ACTIONFv": "fn_8001938C",
    "GetBGColor__Fv": "fn_80019470",
    "EnableDistantWorldAlpha__Fv": "fn_80019478",
    "DisableDistantWorldAlpha__Fv": "fn_80019490",
    "GetCurrentStageNumber__6ACTIONFv": "fn_800194A8",
    "GetCurrentStageName__6ACTIONFv": "fn_800194C4",
    "FreezeStage__6ACTIONFv": "fn_800194E0",
    "GiveUpStage__6ACTIONFv": "fn_80019540",
    "InitRestartStage__6ACTIONFv": "fn_8001963C",
    "BackToBeginningOfStage__6ACTIONFv": "fn_800196AC",
    "RestartStage__6ACTIONFv": "fn_80019720",
    "ContinueStage__6ACTIONFv": "fn_80019778",
    "EndPose__6ACTIONFv": "fn_800197D4",
    "StartPose__6ACTIONFv": "fn_80019830",
    "SetGoalAction__6ACTIONFi": "fn_80019898",
    "StepStage__6ACTIONFv": "fn_80019A20",
    "ExitPauseMode__6ACTIONFv": "fn_80019A68",
    "EnterPauseMode__6ACTIONFv": "fn_80019BFC",
    "CheckPauseOff__6ACTIONFv": "fn_80019F80",
    "dispAlpha__6ACTIONFPv7BitFlag": "fn_8001A518",
    "dispPunch__6ACTIONFPv7BitFlag": "fn_8001A730",
    "dispOpeq__6ACTIONFPv7BitFlag": "fn_8001A950",
    "Exec__6ACTIONFv": "fn_8001AB48",
    "Loop__6ACTIONFv": "fn_8001B120",
    "fn_8019CC28_noarg": "fn_8019CC28",
    "fn_8019CC00_noarg": "fn_8019CC00",
    "fn_800122B4_noarg": "fn_800122B4",
    "fn_80177C50_noarg": "fn_80177C50",
    "Action": "lbl_8029C310",
    "@160": "jumptable_80240E40",
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
