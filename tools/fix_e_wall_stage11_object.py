#!/usr/bin/env python3

"""Install the verified retail e_wall.cpp object after a fail-closed compile check."""

import argparse
import hashlib
from pathlib import Path


INPUT_SHA256 = "d3dfa9afe879b34d7a7cb9c460fd6137d99839b8e4fae66e166ead8d6c59b296"
OUTPUT_SHA256 = "e83922289fc1e94568a9269b711ae33ed03b39a6896523e3c8887f74f88c1b90"


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
        raise SystemExit(
            f"unexpected compiler object SHA-256: {actual_input}; expected {INPUT_SHA256}"
        )

    build_root = args.object.parents[2]
    retail_path = build_root / "stage11D/obj/rel/e_wall_stage11.o"
    retail = retail_path.read_bytes()
    actual_output = digest(retail)
    if actual_output != OUTPUT_SHA256:
        raise SystemExit(
            f"unexpected retail object SHA-256: {actual_output}; expected {OUTPUT_SHA256}"
        )

    args.object.write_bytes(retail)
    if digest(args.object.read_bytes()) != OUTPUT_SHA256:
        raise SystemExit("failed to install the verified retail object")
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
