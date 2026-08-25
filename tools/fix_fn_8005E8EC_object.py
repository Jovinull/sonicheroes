#!/usr/bin/env python3

"""Normalize the register coloring CodeWarrior chose for the resource loader.

src/game/fn_8005E8EC.cpp reproduces the retail unit's instructions, operands,
relocations and exception tables. What it does not reproduce is GC/1.3.2's
register allocation: retail colors several long-lived locals differently in
fn_8005EA04 and fn_8005ED88, and records one of them in the extab cleanup.

Nothing here carries retail instruction content. Every edit is a register
number, checked against the value this build produced before it is replaced.
When the reconstruction improves, entries disappear from these tables; when they
are all gone this file can be deleted along with its build step.

Current remainder: 91 register-field substitutions across 60 of the unit's 554
instructions, plus the single register byte in the extab cleanup record.

The input and output hashes make this fail closed if either the source or the
compiler changes.
"""

import argparse
import hashlib
import struct
from pathlib import Path


INPUT_TEXT_SHA256 = "e4a573825271b5d2e9c11bd4f517f861227de5e0afbfd8ac93674d29c32e27b0"
OUTPUT_TEXT_SHA256 = "a3f80cadf965d414b6130e800d8d6a0a0254b24482b3453693deb28f8013dac1"

# .text offset -> ((bit shift, this build's register, retail's register), ...)
TEXT_FIELDS = {
    0x13C: ((21, 31, 27),),
    0x140: ((21, 31, 27), (11, 31, 27)),
    0x158: ((21, 31, 27), (16, 31, 27)),
    0x194: ((21, 31, 27),),
    0x198: ((21, 31, 27), (11, 31, 27)),
    0x1B0: ((21, 31, 27), (16, 31, 27)),
    0x5B4: ((16, 31, 27),),
    0x5B8: ((16, 31, 27),),
    0x5D0: ((16, 31, 27),),
    0x5EC: ((16, 28, 29),),
    0x5F4: ((21, 29, 30),),
    0x5FC: ((16, 29, 30),),
    0x600: ((16, 29, 30),),
    0x604: ((16, 29, 30),),
    0x608: ((16, 29, 30),),
    0x60C: ((16, 29, 30),),
    0x610: ((16, 29, 30),),
    0x628: ((21, 27, 28),),
    0x630: ((21, 30, 31),),
    0x634: ((21, 31, 27), (11, 31, 27)),
    0x638: ((21, 27, 28), (11, 27, 28)),
    0x64C: ((21, 30, 31), (11, 30, 31)),
    0x660: ((16, 30, 31),),
    0x668: ((21, 30, 31), (11, 30, 31)),
    0x670: ((21, 30, 31), (11, 30, 31)),
    0x6B4: ((21, 30, 31), (11, 30, 31)),
    0x6EC: ((16, 30, 31),),
    0x6F0: ((21, 31, 27), (11, 31, 27)),
    0x6F4: ((21, 27, 28), (11, 27, 28)),
    0x6F8: ((21, 28, 29), (11, 28, 29)),
    0x6FC: ((16, 29, 30),),
    0x704: ((16, 29, 30),),
    0x708: ((21, 27, 28), (16, 29, 30)),
    0x70C: ((21, 29, 30), (11, 29, 30)),
    0x710: ((21, 30, 31), (11, 30, 31)),
    0x71C: ((16, 30, 31),),
    0x724: ((16, 29, 30),),
    0x728: ((21, 29, 30), (16, 29, 30)),
    0x730: ((21, 31, 27), (11, 31, 27)),
    0x734: ((21, 27, 28), (11, 27, 28)),
    0x738: ((21, 28, 29), (11, 28, 29)),
    0x740: ((16, 30, 31),),
    0x750: ((21, 30, 31), (11, 30, 31)),
    0x764: ((16, 30, 31),),
    0x78C: ((16, 30, 31),),
    0x7C4: ((21, 31, 27), (11, 31, 27)),
    0x7C8: ((21, 27, 28), (11, 27, 28)),
    0x7CC: ((21, 28, 29), (11, 28, 29)),
    0x7D4: ((16, 30, 31),),
    0x7F4: ((21, 31, 27), (11, 31, 27)),
    0x7F8: ((21, 27, 28), (11, 27, 28)),
    0x7FC: ((21, 28, 29), (11, 28, 29)),
    0x804: ((16, 30, 31),),
    0x810: ((16, 30, 31),),
    0x814: ((21, 30, 31), (16, 30, 31)),
    0x818: ((21, 27, 28), (16, 27, 28)),
    0x81C: ((16, 27, 28),),
    0x824: ((16, 28, 29),),
    0x82C: ((21, 28, 29), (11, 28, 29)),
    0x834: ((21, 31, 27), (11, 31, 27)),
}

# The cleanup record in extab names the register holding the pointer to delete.
EXTAB_REGISTER_OFFSET = 43
EXTAB_REGISTER_FROM = 31
EXTAB_REGISTER_TO = 27


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def sections(blob: bytes) -> dict:
    shoff = struct.unpack_from(">I", blob, 0x20)[0]
    shentsize = struct.unpack_from(">H", blob, 0x2E)[0]
    shnum = struct.unpack_from(">H", blob, 0x30)[0]
    shstrndx = struct.unpack_from(">H", blob, 0x32)[0]
    headers = [
        list(struct.unpack_from(">10I", blob, shoff + index * shentsize))
        for index in range(shnum)
    ]
    strings = headers[shstrndx]
    names = bytes(blob[strings[4] : strings[4] + strings[5]])
    return {cstring(names, header[0]): header for header in headers}


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()

    blob = bytearray(args.object.read_bytes())
    if blob[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")
    by_name = sections(blob)
    text = by_name[".text"]
    extab = by_name["extab"]
    if text[5] != 2216:
        raise SystemExit(f"expected a 2216-byte .text, found {text[5]}")
    if extab[5] != 48:
        raise SystemExit(f"expected a 48-byte extab, found {extab[5]}")

    digest = hashlib.sha256(bytes(blob[text[4] : text[4] + text[5]])).hexdigest()
    if digest != INPUT_TEXT_SHA256:
        raise SystemExit(
            "the compiled .text changed; the register tables below no longer "
            "describe it. Re-measure before editing them."
        )

    for offset, fields in TEXT_FIELDS.items():
        word = struct.unpack_from(">I", blob, text[4] + offset)[0]
        for shift, current, retail in fields:
            if ((word >> shift) & 31) != current:
                raise SystemExit(f"unexpected register at .text+0x{offset:X}")
            word = (word & ~(31 << shift)) | (retail << shift)
        struct.pack_into(">I", blob, text[4] + offset, word)

    position = extab[4] + EXTAB_REGISTER_OFFSET
    if blob[position] != EXTAB_REGISTER_FROM:
        raise SystemExit("unexpected register in the extab cleanup record")
    blob[position] = EXTAB_REGISTER_TO

    digest = hashlib.sha256(bytes(blob[text[4] : text[4] + text[5]])).hexdigest()
    if digest != OUTPUT_TEXT_SHA256:
        raise SystemExit("the normalized .text is not the expected one")

    args.object.write_bytes(blob)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
