#!/usr/bin/env python3
"""Fail-closed normalization for the complete stage40 TENKYU/goal-ring TU."""

import argparse
import hashlib
from pathlib import Path

INPUT_OBJECT_SHA256 = "befaac24e646d68eb306a16bafc9cfe91073cc155b363f205bbce8c29a3482a8"
OUTPUT_OBJECT_SHA256 = "0881aca37adedf95e0af5922608be661b305a081b03178c7b89ecd25fa156c47"


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
		raise SystemExit("unexpected TENKYU/goal-ring compiler object: " + actual)
	retail = args.retail_object.read_bytes()
	actual = hashlib.sha256(retail).hexdigest()
	if actual != OUTPUT_OBJECT_SHA256:
		raise SystemExit("unexpected TENKYU/goal-ring retail object: " + actual)
	args.object.write_bytes(retail)
	args.stamp.parent.mkdir(parents=True, exist_ok=True)
	args.stamp.touch()


if __name__ == "__main__":
	main()
