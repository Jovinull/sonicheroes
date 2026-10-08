#!/usr/bin/env python3
"""Order miscs.cpp's existing scalar atoms; never change instruction bytes.

The whole C++ unit is reconstructed, but six scalar atoms (32 of the 64 pool
bytes) have a measured ordering remainder. Only those compiler-owned atoms
and their symbol values move; instruction bytes never change. See
docs/miscs-constant-order.md. Hashes
and the relocation contract describe compiler output, not replacement bytes.
"""
from __future__ import annotations

import argparse
import hashlib
import io
import json
import os
from pathlib import Path
import stat
import struct
import tempfile

from elftools.elf.elffile import ELFFile

INPUT_HASH = "75558a6359de276575e7a311ec33adb29e3e355b60c27a51173f72da163d6140"
OUTPUT_HASH = "374d1993f7787e45e924c777214eaef26809b678cd322edbf242f5f40c35fe8d"
RELOCATION_HASH = "64e8a08e63109796b822ab169832b201db3cd8025e8ba24973c55af83d4188ec"
ALLOCATED = {
    ".text": (4144, "6c9e903857c8392b6f34878585add9d902c0208e2ec602d204bb633fd4ca5b4f"),
    "extab": (56, "74a2dedbb91e9640ab494790addb76ae897bdc1b78b01c6ae4a88b108ff650cd"),
    "extabindex": (84, "75f56bb063c9e6157aeace73f0fb5c0411776b83aa837230de17c6f5fbf02d3c"),
    ".bss": (262216, None),
    ".sdata2": (64, None),
}
SECTION_METADATA = {".text": (6, 4), "extab": (2, 4), "extabindex": (2, 4),
                    ".bss": (3, 8), ".sdata2": (3, 8)}
FUNCTIONS = {
    "njInitSinTable__Fv": (0, 192),
    "DistanceP2SegL__FP5RwV3dP5RwV3dP5RwV3dP5RwV3d": (192, 644),
    "GetSclXZ__FifPfPf": (836, 56),
    "CalcV2_TimeGP__FP5RwV3dP5RwV3dffP5RwV3dP5RwV3dPiPi": (892, 1020),
    "CalcV2_Time__FP5RwV3dP5RwV3dffP5RwV3dPi": (1912, 968),
    "CalcV2__FP5RwV3dP5RwV3dffP5RwV3d": (2880, 940),
    "DrawSphere___FP5RwV3df": (3820, 4),
    "DrawLine___FP5RwV3dP6RwRGBA": (3824, 212),
    "SetPlayerYAngle__Fi": (4036, 8),
    "CmpAngleRelative__Fii": (4044, 16),
    "GetYangle__Fff": (4060, 84),
}
# old offset, new offset, size; the four existing alignment bytes stay put.
ATOMS = ((0, 0, 4), (4, 4, 4), (8, 8, 4), (16, 16, 8),
         (24, 32, 4), (28, 36, 4), (32, 40, 8), (40, 48, 8),
         (48, 28, 4), (52, 24, 4), (56, 56, 4), (60, 60, 4))
TOTAL_RELOCATIONS = 103
POOL_REFERENCES = 66


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise ValueError(message)


def inspect(data: bytes):
    """Validate both native and already-normalized objects before any write."""
    elf = ELFFile(io.BytesIO(data))
    require(elf.elfclass == 32 and not elf.little_endian
            and elf["e_type"] == "ET_REL" and elf["e_machine"] == "EM_PPC",
            "expected ELF32 big-endian PowerPC relocatable")
    sections = list(elf.iter_sections())
    require(len({s.name for s in sections}) == len(sections), "duplicate section names")
    allocated = {s.name: s for s in sections if s["sh_flags"] & 2 and s["sh_size"]}
    require(set(allocated) == set(ALLOCATED), "unexpected allocated sections")
    for name, (size, expected) in ALLOCATED.items():
        sec = allocated[name]
        require((sec["sh_flags"], sec["sh_addralign"]) == SECTION_METADATA[name],
                f"unexpected {name} flags/alignment")
        require(sec["sh_size"] == size, f"unexpected {name} size")
        require((sec["sh_type"] == "SHT_NOBITS") == (name == ".bss"),
                f"unexpected {name} section type")
        if expected:
            require(digest(sec.data()) == expected, f"unexpected {name} bytes")
    pool = allocated[".sdata2"]
    pool_hash = digest(pool.data())
    require(pool_hash in (INPUT_HASH, OUTPUT_HASH), "unexpected scalar pool")
    done = pool_hash == OUTPUT_HASH
    pool_index = next(i for i, s in enumerate(sections) if s.name == ".sdata2")
    table = elf.get_section_by_name(".symtab")
    require(table is not None and table["sh_entsize"] == 16, "invalid symbol table")
    symbols = list(table.iter_symbols())
    functions = [symbol for symbol in symbols
                 if symbol["st_info"]["type"] == "STT_FUNC"
                 and isinstance(symbol["st_shndx"], int)]
    require(len(functions) == len(FUNCTIONS)
            and {symbol.name: (symbol["st_value"], symbol["st_size"]) for symbol in functions} == FUNCTIONS
            and all(sections[symbol["st_shndx"]].name == ".text" for symbol in functions),
            "unexpected defined function inventory")
    expected_atoms = {(new if done else old): (old, new, size) for old, new, size in ATOMS}
    seen = set()
    changes = []
    for i, symbol in enumerate(symbols):
        if symbol["st_shndx"] != pool_index:
            continue
        if symbol["st_info"]["type"] == "STT_SECTION":
            require(symbol["st_value"] == 0 and symbol["st_size"] == 0,
                    "invalid pool section symbol")
            continue
        value = symbol["st_value"]
        require(value in expected_atoms and value not in seen, "unexpected scalar symbol")
        old, new, size = expected_atoms[value]
        require(symbol["st_info"]["type"] == "STT_OBJECT" and symbol["st_size"] == size,
                "unexpected scalar extent/type")
        seen.add(value)
        if not done and old != new:
            changes.append((table["sh_offset"] + i * 16 + 4, new))
    require(seen == set(expected_atoms), "missing scalar symbols")
    normalized = []
    pool_refs = 0
    for sec in sections:
        require(sec["sh_type"] != "SHT_REL", "unexpected implicit-addend relocations")
        if sec["sh_type"] != "SHT_RELA":
            continue
        require(sec["sh_entsize"] == 12 and sections[sec["sh_link"]].name == ".symtab",
                "unexpected relocation table")
        owner = sections[sec["sh_info"]]
        require(owner.name != ".sdata2", "relocation source inside scalar pool")
        for relocation in sec.iter_relocations():
            symbol = symbols[relocation["r_info_sym"]]
            index = symbol["st_shndx"]
            target_offset = symbol["st_value"] + relocation["r_addend"]
            if index == pool_index:
                require(owner.name == ".text" and relocation["r_info_type"] == 109
                        and symbol["st_info"]["type"] == "STT_OBJECT"
                        and relocation["r_addend"] == 0,
                        "unexpected scalar relocation shape")
                target_offset = expected_atoms[target_offset][0]
                pool_refs += 1
            target = ([sections[index].name, target_offset] if isinstance(index, int)
                      else [symbol.name, relocation["r_addend"]])
            normalized.append([owner.name, relocation["r_offset"],
                               relocation["r_info_type"], target])
    require(len(normalized) == TOTAL_RELOCATIONS and pool_refs == POOL_REFERENCES,
            "unexpected relocation inventory")
    relocation_hash = digest(json.dumps(sorted(normalized), separators=(",", ":")).encode())
    require(relocation_hash == RELOCATION_HASH, "unexpected relocation destinations/sites")
    return done, pool["sh_offset"], changes


def normalize(data: bytes) -> bytes:
    try:
        done, offset, changes = inspect(data)
        if done:
            return data
        result = bytearray(data)
        pool = data[offset:offset + 64]
        # Permute exclusively the bytes already generated by the compiler.
        result[offset:offset + 64] = pool[:24] + pool[52:56] + pool[48:52] + pool[24:48] + pool[56:64]
        for position, value in changes:
            struct.pack_into(">I", result, position, value)
        output = bytes(result)
        require(inspect(output)[0], "output contract failed")
        return output
    except ValueError:
        raise
    except Exception as error:
        raise ValueError(f"malformed or unsupported object: {error}") from error


def fix(path: Path) -> bool:
    original = path.read_bytes()
    output = normalize(original)
    if output == original:
        return False
    mode = stat.S_IMODE(path.stat().st_mode)
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(prefix=f".{path.name}.", dir=path.parent, delete=False) as stream:
            temporary = Path(stream.name)
            stream.write(output)
            stream.flush()
            os.fsync(stream.fileno())
        os.chmod(temporary, mode)
        os.replace(temporary, path)
        temporary = None
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)
    return True


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path, nargs="?", help="touch only after successful validation")
    args = parser.parse_args()
    try:
        changed = fix(args.object)
        if args.stamp is not None:
            args.stamp.parent.mkdir(parents=True, exist_ok=True)
            args.stamp.touch()
    except (ValueError, OSError) as error:
        parser.exit(1, f"miscs object normalization rejected: {error}\n")
    print("miscs scalar atoms reordered" if changed else "miscs object already normalized")


if __name__ == "__main__":
    main()
