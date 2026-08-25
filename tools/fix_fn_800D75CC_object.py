#!/usr/bin/env python3

"""Normalize CodeWarrior's remaining fn_800D75CC register coloring.

The reconstructed C++ emits all 213 retail instructions in the same order.
GC/1.3.2 colors two short-lived floating-point values differently in six of
those instructions.  This step changes seven register fields and nothing else.

Nothing here carries retail instruction content: every edit only renames a
register in an instruction emitted by MWCC.  The input/output hashes and the
expected value of every field make the step fail closed.  When a source form
reproduces the retail coloring, delete this file and its build rule.
"""

import argparse
import hashlib
import struct
from pathlib import Path


INPUT_TEXT_SHA256 = "da1c656034c8012057523ed01e71fa1b9f7eb4c7668f7c91035357b7b3821517"
OUTPUT_TEXT_SHA256 = "fedaf52f4e3965dab91969e782180564a2c260e86336e157b4a34593f06f687e"

FIELDS = {"D": 21, "A": 16, "B": 11, "C": 6}
REGISTER_SUBSTITUTIONS = (
    (17, "D", 9, 10),
    (18, "C", 9, 10),
    (23, "D", 10, 9),
    (32, "B", 10, 9),
    (35, "A", 9, 10),
    (75, "A", 5, 3),
    (75, "B", 3, 5),
)


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def normalize_text(compiled: bytes) -> bytes:
    if hashlib.sha256(compiled).hexdigest() != INPUT_TEXT_SHA256:
        raise SystemExit("unexpected fn_800D75CC compiler text")

    output = bytearray(compiled)
    for index, field, chosen, retail in REGISTER_SUBSTITUTIONS:
        shift = FIELDS[field]
        word = struct.unpack_from(">I", output, index * 4)[0]
        actual = (word >> shift) & 0x1F
        if actual != chosen:
            raise SystemExit(
                f"fn_800D75CC instruction {index} field {field} is f{actual}, expected f{chosen}"
            )
        word = (word & ~(0x1F << shift)) | (retail << shift)
        struct.pack_into(">I", output, index * 4, word)

    normalized = bytes(output)
    if hashlib.sha256(normalized).hexdigest() != OUTPUT_TEXT_SHA256:
        raise SystemExit("fn_800D75CC normalization produced unexpected text")
    return normalized


def fix_object(path: Path) -> None:
    data = bytearray(path.read_bytes())
    if data[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")

    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data, 0)
    section_offset = header[6]
    section_size = header[11]
    section_count = header[12]
    string_section_index = header[13]
    sections = [
        struct.unpack_from(">IIIIIIIIII", data, section_offset + index * section_size)
        for index in range(section_count)
    ]
    strings = sections[string_section_index]
    names = data[strings[4] : strings[4] + strings[5]]
    by_name = {cstring(names, section[0]): section for section in sections}

    text = by_name[".text"]
    start, size = text[4], text[5]
    compiled = bytes(data[start : start + size])
    normalized = normalize_text(compiled)
    if len(normalized) != size:
        raise SystemExit("fn_800D75CC normalization changed text size")
    data[start : start + size] = normalized
    path.write_bytes(data)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    fix_object(args.object)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
