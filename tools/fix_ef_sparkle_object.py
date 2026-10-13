#!/usr/bin/env python3
"""Bind Sparkle symbols and reorder existing data atoms, never modifying .text.

The source emits its destructor after the static initializer. This tool only
moves the filename behind the vtable and binds equivalent native symbol names.
Scalar sizes and explicit residual padding remain separate and unchanged.
"""

import argparse
import hashlib
import os
import struct
import subprocess
import tempfile
from pathlib import Path

TEXT_SHA256 = "c7aae955fb0f3d1826f6e81d9921ae5447ed54414814bee56777ce760c879b2f"
ALIASES = {}
FUNCTION_SIZES = {
    "CalcInt__FUiUi": 60,
    "ReleaseTextureEfSparkle__Fv": 328,
    "LoadTextureEfSparkle__Fv": 456,
    "CreateSparkleR__FP5RwV3dP5RwV3dff": 460,
    "CreateSparkle__FP5RwV3dP5RwV3dff": 444,
    "CreateSparkle__FP5RwV3dP5RwV3df": 588,
    "Move__9EfSparkleFP17PARTICLE_INSTANCE": 448,
    "__ct__9EfSparkleFUi": 356,
    "__sinit_ef_sparkle_cpp": 28,
    "__dt__9EfSparkleFv": 100,
}

POOL_ALIASES = {
    0: ("lbl_16_rodata_9B0", 4),
    4: ("lbl_16_rodata_9B4", 4),
    8: ("lbl_16_rodata_9B8", 4),
    12: ("lbl_16_rodata_9BC", 4),
    16: ("lbl_16_rodata_9C0", 4),
    20: ("lbl_16_rodata_9C4", 4),
    24: ("lbl_16_rodata_9C8", 8),
    32: ("lbl_16_rodata_9D0", 4),
    36: ("lbl_16_rodata_9D4", 4),
    40: ("lbl_16_rodata_9D8", 4),
    44: ("lbl_16_rodata_9DC", 4),
    48: ("lbl_16_rodata_9E0", 4),
    52: ("lbl_16_rodata_9E4", 4),
    56: ("lbl_16_rodata_9E8", 4),
    60: ("lbl_16_rodata_9EC", 4),
    64: ("lbl_16_rodata_9F0", 4),
    68: ("lbl_16_rodata_9F4", 4),
    72: ("lbl_16_rodata_9F8", 4),
    76: ("lbl_16_rodata_9FC", 4),
    80: ("lbl_16_rodata_A00", 4),
    84: ("lbl_16_rodata_A04", 4),
    88: ("lbl_16_rodata_A08", 4),
}


class Elf:

    def __init__(self, data):
        self.data = bytearray(data)
        if self.data[:6] != b"\x7fELF\x01\x02":
            raise ValueError("expected big-endian ELF32")
        self.header = struct.unpack_from(">16sHHIIIIIHHHHHH", data)
        h = self.header
        self.sections = [
            list(struct.unpack_from(">10I", data, h[6] + i * h[11]))
            for i in range(h[12])
        ]
        names = self.payload(self.sections[h[13]])
        self.names = [self.string(names, s[0]) for s in self.sections]
        self.by_name = {
            n: (i, s) for i, (n, s) in enumerate(zip(self.names, self.sections))
        }
        self.symbols = []
        _, tab = self.by_name[".symtab"]
        strings = self.payload(self.sections[tab[6]])
        for off in range(tab[4], tab[4] + tab[5], tab[9]):
            sym = list(struct.unpack_from(">IIIBBH", data, off))
            self.symbols.append((self.string(strings, sym[0]), off, sym))
        self.aliases = dict(ALIASES)
        for name, _, symbol in self.symbols:
            if (
                name.startswith("@")
                and symbol[5] < len(self.sections)
                and self.names[symbol[5]] == ".rodata"
                and symbol[3] & 15 == 1
            ):
                target = POOL_ALIASES.get(symbol[1])
                if target is None or symbol[2] != target[1]:
                    raise ValueError("unexpected compiler pool atom")
                self.aliases[name] = target[0]
        self.named = {self.canonical(n): (n, o, s) for n, o, s in self.symbols if n}

    @staticmethod
    def string(data, off):
        return data[off : data.index(0, off)].decode("ascii")

    def payload(self, s):
        return bytes(self.data[s[4] : s[4] + s[5]]) if s[1] != 8 else bytes(s[5])

    def canonical(self, n):
        return self.aliases.get(n, n)

    def put_symbol(self, off, s):
        struct.pack_into(">IIIBBH", self.data, off, *s)

    def check(self):
        sizes = {".text": 3268, ".rodata": 96, ".data": 104, ".bss": 24, ".ctors": 4}
        for name, size in sizes.items():
            if self.by_name[name][1][5] != size:
                raise ValueError("unexpected section size: " + name)
        if (
            hashlib.sha256(self.payload(self.by_name[".text"][1])).hexdigest()
            != TEXT_SHA256
        ):
            raise ValueError("native .text fingerprint differs")
        f = {
            self.canonical(n): s[2]
            for n, _, s in self.symbols
            if s[3] & 15 == 2 and s[5] != 0
        }
        if f != FUNCTION_SIZES:
            raise ValueError("unexpected native function inventory")
        for source, target in self.aliases.items():
            if (
                source != target
                and any((n == source for n, _, _ in self.symbols))
                and any((n == target for n, _, _ in self.symbols))
            ):
                raise ValueError("alias target collision: " + target)

    def invariant(self):
        """Compare atom payloads and relocation meanings independent of data order."""
        atoms = {}
        refs = []
        for name, _, s in self.symbols:
            if (
                s[5] >= len(self.sections)
                or s[5] == 0
                or (not s[2])
                or (s[3] & 15 not in (1, 2))
            ):
                continue
            sec = self.sections[s[5]]
            n = self.canonical(name)
            atoms[n] = (
                self.names[s[5]],
                s[2],
                17 if n.startswith("lbl_16_rodata_") else s[3],
                s[4],
                self.payload(sec)[s[1] : s[1] + s[2]],
            )

        def identity(index):
            n, _, s = self.symbols[index]
            return (
                self.canonical(n),
                s[2],
                17 if self.canonical(n).startswith("lbl_16_rodata_") else s[3],
                s[4],
                self.names[s[5]] if s[5] < len(self.sections) else s[5],
            )

        for sec in self.sections:
            if sec[1] != 4:
                continue
            for off in range(sec[4], sec[4] + sec[5], sec[9]):
                address, info, addend = struct.unpack_from(">IIi", self.data, off)
                owner = (self.names[sec[7]], address)
                for n, _, s in self.symbols:
                    if (
                        s[5] == sec[7]
                        and s[3] & 15 in (1, 2)
                        and (s[1] <= address < s[1] + s[2])
                    ):
                        owner = (self.names[sec[7]], self.canonical(n), address - s[1])
                        break
                refs.append((owner, info & 255, identity(info >> 8), addend))
        return (atoms, sorted(refs, key=repr))

    def reorder(self):
        vtable = self.named["__vt__9EfSparkle"][2]
        filename = self.named["lbl_16_data_3D20"][2]
        layout = (vtable[1], vtable[2], filename[1], filename[2])
        if layout == (48, 32, 80, 23):
            return False
        if layout != (72, 32, 48, 23):
            raise ValueError("unexpected data atom layout")
        data = self.by_name[".data"][1]
        raw = self.payload(data)
        if raw[48:71] != b"./textures/ef_uv00.txd\0" or raw[71] != 0:
            raise ValueError("unexpected filename or padding")
        self.data[data[4] : data[4] + 104] = raw[:48] + raw[72:] + raw[48:72]

        def move(value):
            if 48 <= value < 72:
                return value + 32
            if 72 <= value < 104:
                return value - 24
            return value

        for name, offset, sym in self.symbols:
            if (
                sym[5] < len(self.sections)
                and self.names[sym[5]] == ".data"
                and sym[3] & 15 != 3
            ):
                sym[1] = move(sym[1])
                self.put_symbol(offset, sym)
        for section in self.sections:
            if section[1] == 4 and self.names[section[7]] == ".data":
                for offset in range(section[4], section[4] + section[5], section[9]):
                    value = struct.unpack_from(">I", self.data, offset)[0]
                    struct.pack_into(">I", self.data, offset, move(value))
        return True


def normalize(path, objcopy):
    path = Path(path)
    before = Elf(path.read_bytes())
    before.check()
    invariant = before.invariant()
    text = before.payload(before.by_name[".text"][1])
    work = Elf(path.read_bytes())
    changed = work.reorder()
    renames = [
        (n, work.canonical(n)) for n, _, _ in work.symbols if n != work.canonical(n)
    ]
    if not changed and (not renames):
        return
    with tempfile.TemporaryDirectory(
        dir=path.parent, prefix="sparkle-normalize-"
    ) as tmp:
        source = Path(tmp) / "layout.o"
        output = Path(tmp) / "bound.o"
        source.write_bytes(work.data)
        command = (
            [str(objcopy)]
            + [f"--redefine-sym={a}={b}" for a, b in renames]
            + [
                f"--globalize-symbol={name}"
                for name in work.aliases.values()
                if name.startswith("lbl_16_rodata_")
            ]
            + [str(source), str(output)]
        )
        subprocess.run(command, check=True)
        after = Elf(output.read_bytes())
        after.check()
        if tuple(
            after.named[n][2][1] for n in ("__vt__9EfSparkle", "lbl_16_data_3D20")
        ) != (48, 80):
            raise ValueError("unexpected final layout")
        if after.payload(after.by_name[".text"][1]) != text:
            raise ValueError(".text changed during metadata normalization")
        if after.invariant() != invariant:
            raise ValueError("atom bytes or relocation meanings changed")
        os.chmod(output, path.stat().st_mode)
        os.replace(output, path)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", type=Path, required=True)
    args = parser.parse_args()
    normalize(args.object, args.objcopy)
    args.stamp.touch()


if __name__ == "__main__":
    main()
