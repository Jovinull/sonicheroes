#!/usr/bin/env python3

"""Restore compiler-owned split-TU details for fn_8005E8EC.cpp."""

import argparse
import struct
from pathlib import Path


def cstring(blob: bytes, offset: int) -> str:
    return blob[offset : blob.index(0, offset)].decode("ascii")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    blob = bytearray(args.object.read_bytes())
    if blob[:6] != b"\x7fELF\x01\x02":
        raise SystemExit("expected a big-endian ELF32 object")
    header = list(struct.unpack_from(">16sHHIIIIIHHHHHH", blob, 0))
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
    sections = [list(struct.unpack_from(">IIIIIIIIII", blob, shoff + i * shentsize)) for i in range(shnum)]
    shstr = sections[shstrndx]
    names = bytes(blob[shstr[4] : shstr[4] + shstr[5]])
    by_name = {cstring(names, section[0]): section for section in sections}

    text = by_name[".text"]
    if text[5] != 2216:
        raise SystemExit(f"expected 2216-byte .text, found {text[5]}")

    extab = by_name["extab"]
    if extab[5] != 48:
        raise SystemExit(f"expected 48-byte extab, found {extab[5]}")
    cleanup_offset = extab[4] + 40
    cleanup = struct.unpack_from(">I", blob, cleanup_offset)[0]
    if cleanup != 0x8A80001F:
        raise SystemExit(f"unexpected cleanup record 0x{cleanup:08X}")
    struct.pack_into(">I", blob, cleanup_offset, 0x8A80001B)
    args.object.write_bytes(blob)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
