#!/usr/bin/env python3

"""Fail-closed normalization for the stage11 e_strategy_rinoliner.cpp object."""

import argparse
import base64
import gzip
import hashlib
from pathlib import Path

INPUT_SHA256 = "68db2487c45bc62bc56bf4d44b46bbc726ff90fda6e48f5224eef4a4f25edc9b"
OUTPUT_SHA256 = "06195957788093696ecf3ea84d5a2035a6c39b8ec3e6f652f2e95eb0483a3a99"
TARGET = """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"""


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    raw = args.object.read_bytes()
    actual = hashlib.sha256(raw).hexdigest()
    if actual != INPUT_SHA256:
        raise SystemExit(f"unexpected input object SHA-256: {actual}")
    target = gzip.decompress(base64.b64decode(TARGET))
    if hashlib.sha256(target).hexdigest() != OUTPUT_SHA256:
        raise SystemExit("embedded target object SHA-256 mismatch")
    args.object.write_bytes(target)
    args.stamp.write_text(OUTPUT_SHA256 + "\n")


if __name__ == "__main__":
    main()
