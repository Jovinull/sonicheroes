#!/usr/bin/env python3

"""Add the retail interior field-signature symbol to the combined data atom."""

import argparse
import shutil
import subprocess
import tempfile
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    args = parser.parse_args()

    with tempfile.TemporaryDirectory() as temp_dir:
        output = Path(temp_dir) / args.object.name
        subprocess.run(
            [
                str(args.objcopy),
                "--add-symbol",
                "TEnemyAppearChaosEmeraldFieldTypes=.data:0x15,global",
                str(args.object),
                str(output),
            ],
            check=True,
        )
        shutil.copyfile(output, args.object)

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
