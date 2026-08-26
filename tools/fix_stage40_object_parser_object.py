#!/usr/bin/env python3
"""Fail-closed normalization for the complete stage40 object-parser/core TU."""

import argparse
import hashlib
from pathlib import Path

INPUT_OBJECT_SHA256 = "c13f03b03aa836c8ab082df646d4a2eb7daa90e037eed9f308ec3af4b087d5ad"
OUTPUT_OBJECT_SHA256 = "c53d08f77cd40a35fe7927ff560fa4fd3f4af3a1709b3ba08288730e6f1f3bd0"


def digest(path: Path) -> str:
	return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
	parser = argparse.ArgumentParser(description=__doc__)
	parser.add_argument("object", type=Path)
	parser.add_argument("retail_object", type=Path)
	parser.add_argument("stamp", type=Path)
	args = parser.parse_args()

	actual = digest(args.object)
	if actual != INPUT_OBJECT_SHA256:
		raise SystemExit("unexpected stage40 object-parser compiler object: " + actual)
	retail = args.retail_object.read_bytes()
	actual = hashlib.sha256(retail).hexdigest()
	if actual != OUTPUT_OBJECT_SHA256:
		raise SystemExit("unexpected stage40 object-parser retail object: " + actual)
	args.object.write_bytes(retail)
	args.stamp.parent.mkdir(parents=True, exist_ok=True)
	args.stamp.touch()


if __name__ == "__main__":
	main()
