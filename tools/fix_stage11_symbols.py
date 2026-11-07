#!/usr/bin/env python3
"""Rename compiler-generated stage11 data symbols to their retail names.

An entry may carry a fourth item, True, when the literal is shared with code
left in the module's assembly: the renamed symbol is then made global.

SECTION_ALIGNMENTS lowers a section's alignment for objects whose literal
lands on an address the compiler's 8-byte .rodata alignment would move."""

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path

SYMBOL_RENAMES = {
    "e_capture.o": [("@560", "captureHalf", 0x4)],
    "e_flyer_strategy_stage11.o": [
        ("@97", "lbl_8_rodata_18B4", 0x4),
        ("@99", "lbl_8_rodata_18B8", 0x8),
    ],
    "e_strategy_wall_stage11.o": [("@288", "jumptable_8_data_17338", 0x40)],
    "e_wall_stage11.o": [("@86", "lbl_8_rodata_1D90", 0x8)],
    "e_wall_stage13.o": [("@86", "lbl_8_rodata_1D90", 0x8)],
    "e_strategy_turtle_stage11.o": [
        ("@204", "jumptable_8_data_17BF0", 0x40),
        ("@221", "jumptable_8_data_17C30", 0x28),
    ],
    "e_turtle_stage11.o": [
        # MWCC emits an anonymous copy of the shared integer-to-float bias.
        ("@895", "lbl_8_rodata_1E80", 0x8),
    ],
    "e_tree_stage11.o": [("@125", "lbl_8_rodata_1F28", 0x4)],
    # EventScript::dispEventMessage's literals, read by name by the module's
    # ScriptExec too.
    "event_script_disp_message.o": [
        ("@28", "eventMessageShadowX", 0x4, True),
        ("@29", "eventMessageShadowY", 0x4, True),
        ("@30", "eventMessageZero", 0x4, True),
        ("@31", "eventMessageY", 0x4, True),
    ],
    # TObjEnemyPawn::SearchPlayerForPawn's 0.0, which the module's other pawn
    # code reads as pawnZero.
    "pawn_search_player.o": [("@14", "pawnZero", 0x4, True)],
    # TObjPole::SetAngle3FromNormal's 1.0, which the module's other pole code
    # reads as poleOne.
    "pole_set_angle3.o": [("@31", "poleOne", 0x4, True)],
    # TObjFan::CheckAscend's 0.0, which its comparisons and the module's other fan
    # code read as fanStopSpeed.
    "fan_check_ascend.o": [("@107", "fanStopSpeed", 0x4, True)],
    "fan_check_ascend_stage13.o": [("@107", "fanStopSpeed", 0x4, True)],
    # TObjSetParticle::Exec's aggregate template for the speed it builds.
    "obj_set_particle_exec.o": [("@45", "setParticleSpeedTemplate", 0xC)],
}

SECTION_ALIGNMENTS = {
    "pawn_search_player.o": [(".rodata", 4)],
    "fan_check_ascend.o": [(".rodata", 4)],
    "fan_check_ascend_stage13.o": [(".rodata", 4)],
}


def symbol_names(symbol_table: str) -> set[str]:
    return {line.split()[-1] for line in symbol_table.splitlines() if line.split()}


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path, help="compiled stage11 REL object")
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
    names = symbol_names(symbols)
    renames = SYMBOL_RENAMES.get(args.object.name)
    if renames is None:
        raise SystemExit(f"unexpected enemy object: {args.object.name}")

    temporary = args.object.parent / (args.object.name + ".symbols.tmp")
    command = [str(args.objcopy)]
    pending = []
    for anonymous, retail, size, *exported in renames:
        if anonymous in names:
            if f"{size:08x} {anonymous}" not in symbols:
                raise SystemExit(f"unexpected {anonymous} size in {args.object.name}")
            pending.append((anonymous, retail, bool(exported and exported[0])))
        elif retail not in names or f"{size:08x} {retail}" not in symbols:
            raise SystemExit(f"missing {retail} in {args.object.name}")
    for anonymous, retail, exported in pending:
        command.extend(["--redefine-sym", f"{anonymous}={retail}"])
        if exported:
            command.extend(["--globalize-symbol", retail])
    if pending:
        subprocess.run(command + [str(args.object), str(temporary)], check=True)
        shutil.copystat(args.object, temporary)
        temporary.replace(args.object)
    # MWLD reads a section's alignment from the CodeWarrior .comment entry as
    # well as sh_addralign; set_elf_section_alignment.py keeps both in step.
    times = args.object.stat()
    for section, alignment in SECTION_ALIGNMENTS.get(args.object.name, []):
        subprocess.run(
            [
                sys.executable,
                str(Path(__file__).with_name("set_elf_section_alignment.py")),
                str(args.object),
                section,
                str(alignment),
            ],
            check=True,
        )
        os.utime(args.object, ns=(times.st_atime_ns, times.st_mtime_ns))

    updated = subprocess.run(
        [str(args.objdump), "-t", str(args.object)],
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    updated_names = symbol_names(updated)
    for anonymous, retail, size, *_exported in renames:
        if (
            anonymous in updated_names
            or retail not in updated_names
            or f"{size:08x} {retail}" not in updated
        ):
            raise SystemExit(f"failed to rename {anonymous} in {args.object.name}")
    args.stamp.touch()


if __name__ == "__main__":
    sys.exit(main())
