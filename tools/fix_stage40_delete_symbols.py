#!/usr/bin/env python3

import argparse
import subprocess
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("objects", nargs="+")
    parser.add_argument("--objcopy", required=True)
    args = parser.parse_args()

    canonical = "__dl__10TObjSampleFPv"
    for object_name in args.objects:
        path = Path(object_name)
        class_name = path.stem.removeprefix("o_").capitalize()
        old_name = f"__dl__11TObj{class_name}FPv"
        subprocess.run(
            [args.objcopy, "--redefine-sym", f"{old_name}={canonical}", path],
            check=True,
        )


if __name__ == "__main__":
    main()
