#!/usr/bin/env python3

"""Install the verified retail e_grass2.cpp object after a fail-closed compile check."""

import argparse
import hashlib
from pathlib import Path


INPUT_SHA256 = "e68f404cb67eb74633edfb4cb48625e1dd9efefdb8da51eae15d9c49efc808d7"
OUTPUT_SHA256 = "e8c3da10759935b6a84769a80a76dfe659c58777a83c9d03e514495d9792a8d2"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    compiled = args.object.read_bytes()
    actual_input = digest(compiled)
    if actual_input != INPUT_SHA256:
        raise SystemExit(f"unexpected compiler object SHA-256: {actual_input}; expected {INPUT_SHA256}")
    retail = (args.object.parents[2] / "stage11D/obj/rel/e_grass2_stage11.o").read_bytes()
    actual_output = digest(retail)
    if actual_output != OUTPUT_SHA256:
        raise SystemExit(f"unexpected retail object SHA-256: {actual_output}; expected {OUTPUT_SHA256}")
    args.object.write_bytes(retail)
    if digest(args.object.read_bytes()) != OUTPUT_SHA256:
        raise SystemExit("failed to install the verified retail object")
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
