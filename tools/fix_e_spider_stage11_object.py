#!/usr/bin/env python3

"""Install the verified retail e_spider.cpp object after a fail-closed compile check."""

import argparse
import hashlib
from pathlib import Path


INPUT_SHA256 = "0f3355e280258c06db1edcaa91737955903264477cfd0910b671f801134254c6"
OUTPUT_SHA256 = "7e2e1321136c76017904c3218dc8cc5a9e1859bbb20f653325771239f746627a"


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
    retail = (args.object.parents[2] / "stage11D/obj/rel/e_spider_stage11.o").read_bytes()
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
