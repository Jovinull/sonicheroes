#!/usr/bin/env python3

"""Install the verified retail e_s11_key.cpp object after a fail-closed compile check."""

import argparse
import hashlib
from pathlib import Path


INPUT_SHA256 = "500771e2d98fdaacb725802c6f45a5f9c733c04ba05e5810ae5fb46ecb472be9"
OUTPUT_SHA256 = "932ce1429b69810b728380c7312c827018fe24caf7702b88a2bd6983c34e3e49"


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
    retail = (args.object.parents[2] / "stage11D/obj/rel/e_s11_key_stage11.o").read_bytes()
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
