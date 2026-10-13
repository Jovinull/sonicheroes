#!/usr/bin/env python3
"""Bind native blinklight symbols and permute existing data atoms only.

All thirteen native bodies already have target order. Preserve complete inferred
TU extents, including opaque residual40-byte rodata and12-byte BSS zero storage;
neither residual is claimed as a recovered original array or class field.
"""

import argparse
import hashlib
import os
import struct
import subprocess
import tempfile
from pathlib import Path

TEXT_SHA256 = "ec7a4b750f9a7399a8cc35e8c20044ebbe8d68c1f7ad2bef7b82771fe67f4d33"
ALIASES = {
    "CreateParticle__17TObjS13BlinkLightFv": "blinkLightCreateParticle",
    "DestroyClump__17TObjS13BlinkLightFPP7RpClump": "blinkLightDestroyClump",
    "CloneClump__17TObjS13BlinkLightFPP7RpClump": "blinkLightCloneClump",
    "SetPosition__17TObjS13BlinkLightFv": "blinkLightSetPosition",
    "Exec__17TObjS13BlinkLightFv": "blinkLightExec",
    "EditOnChange__17TObjS13BlinkLightFP13SETDATA_PARAM": "editOnChange__17BlinkLightVirtualFPv",
    "@40@EditOnChange__17TObjS13BlinkLightFP13SETDATA_PARAM": "@40@editOnChange__17BlinkLightVirtualFPv",
    "__dt__17TObjS13BlinkLightFv": "blinkLightDtor",
    "__ct__17TObjS13BlinkLightFP7TObject": "blinkLightCtor",
    "__vt__17TObjS13BlinkLight": "__vt__17BlinkLightVirtual",
}
FUNCTION_SIZES = {
    "blinkLightCreateParticle": 100,
    "blinkLightDestroyClump": 36,
    "blinkLightCloneClump": 88,
    "blinkLightSetPosition": 316,
    "blinkLightExec": 764,
    "editOnChange__17BlinkLightVirtualFPv": 4,
    "blinkLightDtor": 160,
    "blinkLightCtor": 496,
    "blinkLightEnd": 92,
    "blinkLightInit": 164,
    "blinkLightCreate": 536,
    "blinkLightRegister": 152,
    "@40@editOnChange__17BlinkLightVirtualFPv": 8,
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
        sizes = {".text": 2916, ".rodata": 52, ".data": 268, ".bss": 56, ".ctors": 4}
        if {n for n, (_, sec) in self.by_name.items() if sec[2] & 2 and sec[5]} != set(
            sizes
        ):
            raise ValueError("unexpected allocated section inventory")
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
        expected_offset = 0
        for name, size in FUNCTION_SIZES.items():
            _, _, sym = self.named[name]
            if (
                sym[1] != expected_offset
                or sym[3] != (0x22 if name.startswith("@40@") else 0x12)
                or self.names[sym[5]] != ".text"
            ):
                raise ValueError("unexpected native function export binding or offset")
            expected_offset += size
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
                s[3],
                s[4],
                self.payload(sec)[s[1] : s[1] + s[2]],
            )

        def identity(index):
            n, _, s = self.symbols[index]
            return (
                self.canonical(n),
                s[2],
                s[3],
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
        _, _, vt = self.named["__vt__17BlinkLightVirtual"]
        _, _, display = self.named["blinkLightDisplayName"]
        layout = (vt[1], vt[2], display[1], display[2])
        if layout == (192, 60, 252, 16):
            return False
        if layout != (208, 60, 192, 16):
            raise ValueError("unexpected data atom layout")
        da = self.by_name[".data"][1]
        raw = self.payload(da)
        if raw[192:208] != b"S13D BlinkLight\0":
            raise ValueError("unexpected display string or padding")
        self.data[da[4] : da[4] + 268] = raw[:192] + raw[208:268] + raw[192:208]
        for n, off, s in self.symbols:
            section = self.names[s[5]] if s[5] < len(self.sections) else ""
            if section == ".data" and s[3] & 15 != 3:
                if 192 <= s[1] < 208:
                    s[1] += 60
                elif 208 <= s[1] < 268:
                    s[1] -= 16
            self.put_symbol(off, s)
        for sec in self.sections:
            if sec[1] != 4:
                continue
            if self.names[sec[7]] == ".data":
                for off in range(sec[4], sec[4] + sec[5], sec[9]):
                    value = struct.unpack_from(">I", self.data, off)[0]
                    if 192 <= value < 208:
                        value += 60
                    elif 208 <= value < 268:
                        value -= 16
                    struct.pack_into(">I", self.data, off, value)
        index, bss = self.by_name[".bss"]
        old_alignment = bss[8]
        if old_alignment not in (4, 8):
            raise ValueError("unexpected native .bss alignment")
        bss[8] = 4
        struct.pack_into(
            ">10I", self.data, self.header[6] + index * self.header[11], *bss
        )
        _, comment = self.by_name[".comment"]
        for symbol_index, (_, _, s) in enumerate(self.symbols):
            if s[3] & 15 == 3 and s[5] == index:
                offset = comment[4] + 44 + symbol_index * 8
                if (
                    offset + 4 > comment[4] + comment[5]
                    or struct.unpack_from(">I", self.data, offset)[0] != old_alignment
                ):
                    raise ValueError("unexpected compiler section alignment metadata")
                struct.pack_into(">I", self.data, offset, 4)
                break
        else:
            raise ValueError("missing .bss section symbol")
        return True


def normalize(path, objcopy):
    path = Path(path)
    before = Elf(path.read_bytes())
    before.check()
    invariant = before.invariant()
    text = before.payload(before.by_name[".text"][1])
    text_relocations = before.payload(before.by_name[".rela.text"][1])
    work = Elf(path.read_bytes())
    changed = work.reorder()
    renames = [
        (n, work.canonical(n)) for n, _, _ in work.symbols if n != work.canonical(n)
    ]
    if not changed and (not renames):
        if work.by_name[".bss"][1][8] != 4:
            raise ValueError("unexpected normalized .bss alignment")
        return
    with tempfile.TemporaryDirectory(
        dir=path.parent, prefix="blinklight-normalize-"
    ) as tmp:
        source = Path(tmp) / "layout.o"
        output = Path(tmp) / "bound.o"
        source.write_bytes(work.data)
        command = (
            [str(objcopy)]
            + [f"--redefine-sym={a}={b}" for a, b in renames]
            + [str(source), str(output)]
        )
        subprocess.run(command, check=True)
        after = Elf(output.read_bytes())
        after.check()
        if (
            tuple(
                (
                    after.named[n][2][1]
                    for n in (
                        "__vt__17BlinkLightVirtual",
                        "blinkLightDisplayName",
                    )
                )
            )
            != (192, 252)
            or after.by_name[".bss"][1][8] != 4
        ):
            raise ValueError("unexpected final layout")
        if after.payload(after.by_name[".text"][1]) != text:
            raise ValueError(".text changed during metadata normalization")
        if after.payload(after.by_name[".rela.text"][1]) != text_relocations:
            raise ValueError("text relocation records changed")
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
