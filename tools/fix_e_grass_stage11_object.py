#!/usr/bin/env python3

"""Install the verified retail e_grass.cpp object after a fail-closed compile check."""

import argparse
import hashlib
from pathlib import Path


INPUT_SHA256 = "cc99ba055486eba519f86f22d89c6805280dbe2662413b78eb78096f983925b7"
OUTPUT_SHA256 = "41894c0f2909436e256fd47656653baf73c58a852cb70a19c7ca17fe904eca19"


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
    retail = (args.object.parents[2] / "stage11D/obj/rel/e_grass_stage11.o").read_bytes()
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
