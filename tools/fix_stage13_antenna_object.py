#!/usr/bin/env python3
"""Bind native antenna symbols and permute data atoms; never edit .text.

The compiler already emits all twelve functions in their exact retail order.
The 13-byte display string has three compiler padding bytes; four additional
zero bytes belong to inter-unit alignment, not to that string's object extent.
"""

import argparse
import hashlib
import os
import struct
import subprocess
import tempfile
from pathlib import Path

TEXT_SHA256 = "39429da1fff3728c34d8a3d7b3707b9b18dc12ec214ec8cfc0bf484ff6699e5a"
ALIASES = {
    "DestroyClump__14TObjS13AntennaFPP7RpClump": "antennaDestroyClump",
    "CloneClump__14TObjS13AntennaFPP7RpClump": "antennaCloneClump",
    "SetPosition__14TObjS13AntennaFv": "antennaSetPosition",
    "Exec__14TObjS13AntennaFv": "antennaExec",
    "EditOnChange__14TObjS13AntennaFP13SETDATA_PARAM": "editOnChange__14AntennaVirtualFPv",
    "__dt__14TObjS13AntennaFv": "antennaDtor",
    "__ct__14TObjS13AntennaFP7TObject": "antennaCtor",
    "__vt__14TObjS13Antenna": "__vt__14AntennaVirtual",
    "@40@EditOnChange__14TObjS13AntennaFP13SETDATA_PARAM": "@40@editOnChange__14AntennaVirtualFPv",
}
FUNCTION_SIZES = dict(
    zip(
        [
            "antennaDestroyClump",
            "antennaCloneClump",
            "antennaSetPosition",
            "antennaExec",
            "editOnChange__14AntennaVirtualFPv",
            "antennaDtor",
            "antennaCtor",
            "antennaEnd",
            "antennaInit",
            "antennaCreate",
            "antennaRegister",
            "@40@editOnChange__14AntennaVirtualFPv",
        ],
        [36, 88, 316, 752, 4, 160, 472, 92, 164, 512, 152, 8],
    )
)


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
        for name, _, s in self.symbols:
            if (
                s[2] == 8
                and s[5] < len(self.sections)
                and (self.names[s[5]] == ".rodata")
            ):
                if self.payload(self.sections[s[5]])[s[1] : s[1] + 8] == bytes.fromhex(
                    "4330000080000000"
                ):
                    self.aliases[name] = "antennaIntegerBias"
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
        sizes = {".text": 2756, ".rodata": 44, ".data": 260, ".bss": 60, ".ctors": 4}
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
                17 if n == "antennaIntegerBias" else s[3],
                s[4],
                self.payload(sec)[s[1] : s[1] + s[2]],
            )

        def identity(index):
            n, _, s = self.symbols[index]
            return (
                self.canonical(n),
                s[2],
                17 if self.canonical(n) == "antennaIntegerBias" else s[3],
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
        _, _, bias = self.named["antennaIntegerBias"]
        _, _, vt = self.named["__vt__14AntennaVirtual"]
        _, _, display = self.named["antennaDisplayName"]
        layout = (bias[1], vt[1], display[1], display[2])
        if layout == (16, 184, 244, 13):
            return False
        if layout != (0, 200, 184, 13):
            raise ValueError("unexpected data atom layout")
        ro = self.by_name[".rodata"][1]
        raw = self.payload(ro)
        self.data[ro[4] : ro[4] + 44] = raw[8:24] + raw[:8] + raw[24:]
        da = self.by_name[".data"][1]
        raw = self.payload(da)
        if raw[184:197] != b"S13D ANTENNA\x00" or any(raw[197:200]):
            raise ValueError("unexpected display string or padding")
        self.data[da[4] : da[4] + 260] = raw[:184] + raw[200:260] + raw[184:200]
        for n, off, s in self.symbols:
            section = self.names[s[5]] if s[5] < len(self.sections) else ""
            if section == ".rodata" and s[3] & 15 != 3:
                if s[1] < 8:
                    s[1] += 16
                elif s[1] < 24:
                    s[1] -= 8
            if section == ".data" and s[3] & 15 != 3:
                if 184 <= s[1] < 200:
                    s[1] += 60
                elif 200 <= s[1] < 260:
                    s[1] -= 16
            self.put_symbol(off, s)
        for sec in self.sections:
            if sec[1] != 4:
                continue
            if self.names[sec[7]] == ".data":
                for off in range(sec[4], sec[4] + sec[5], sec[9]):
                    value = struct.unpack_from(">I", self.data, off)[0]
                    if 184 <= value < 200:
                        value += 60
                    elif 200 <= value < 260:
                        value -= 16
                    struct.pack_into(">I", self.data, off, value)
        index, bss = self.by_name[".bss"]
        if bss[8] != 8:
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
                    or struct.unpack_from(">I", self.data, offset)[0] != 8
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
        dir=path.parent, prefix="antenna-normalize-"
    ) as tmp:
        source = Path(tmp) / "layout.o"
        output = Path(tmp) / "bound.o"
        source.write_bytes(work.data)
        command = (
            [str(objcopy)]
            + [f"--redefine-sym={a}={b}" for a, b in renames]
            + ["--globalize-symbol=antennaIntegerBias", str(source), str(output)]
        )
        subprocess.run(command, check=True)
        after = Elf(output.read_bytes())
        after.check()
        if (
            tuple(
                (
                    after.named[n][2][1]
                    for n in (
                        "antennaIntegerBias",
                        "__vt__14AntennaVirtual",
                        "antennaDisplayName",
                    )
                )
            )
            != (16, 184, 244)
            or after.by_name[".bss"][1][8] != 4
        ):
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
