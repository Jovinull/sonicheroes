#!/usr/bin/env python3
"""Bind native laser-collision symbols and reorder data atoms without editing .text.

The naturally sized field-format string leaves four linker-alignment bytes at
its configured unit boundary. Residual zero storage remains explicitly inferred.
"""

import argparse
import hashlib
import os
import struct
import subprocess
import tempfile
from pathlib import Path

TEXT_SHA256 = "9889134e53d881754493c568d6ccd4352aa21c8274a2782c149acf273e3face5"
ALIASES = {
    "SetCommuicateStrage__17TObjS14LaserColliFUc": "collisionApply",
    "TDisp__17TObjS14LaserColliFv": "collisionRelease",
    "Exec__17TObjS14LaserColliFv": "collisionExec",
    "__dt__17TObjS14LaserColliFv": "collisionDtor",
    "__ct__17TObjS14LaserColliFP7TObject": "collisionCtor",
    "EditOnChange__17TObjS14LaserColliFP13SETDATA_PARAM": "editOnChange__16CollisionVirtualFPv",
    "@40@EditOnChange__17TObjS14LaserColliFP13SETDATA_PARAM": "@40@editOnChange__16CollisionVirtualFPv",
    "__vt__17TObjS14LaserColli": "__vt__16CollisionVirtual",
}
ALIASES.update(
    {"colli_color": "collisionDescriptor", "prim_colli": "collisionPrimitive"}
)
FUNCTION_SIZES = {
    "collisionApply": 248,
    "collisionRelease": 68,
    "collisionExec": 692,
    "collisionDtor": 208,
    "collisionCtor": 348,
    "editOnChange__16CollisionVirtualFPv": 196,
    "collisionCreate": 388,
    "collisionRegister": 152,
    "@40@editOnChange__16CollisionVirtualFPv": 8,
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
        for name, _, sym in self.symbols:
            if (
                name.startswith("@")
                and sym[2] == 4
                and sym[5] < len(self.sections)
                and self.names[sym[5]] == ".rodata"
            ):
                if self.payload(self.sections[sym[5]])[sym[1] : sym[1] + 4] == bytes(4):
                    self.aliases[name] = "collisionZero"
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
        sizes = {".text": 2308, ".rodata": 16, ".data": 764, ".bss": 56, ".ctors": 4}
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
                17 if n == "collisionZero" else s[3],
                s[4],
                self.payload(sec)[s[1] : s[1] + s[2]],
            )

        def identity(index):
            n, _, s = self.symbols[index]
            return (
                self.canonical(n),
                s[2],
                17 if self.canonical(n) == "collisionZero" else s[3],
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
        vt = self.named["__vt__16CollisionVirtual"][2]
        display = self.named["collisionDisplayName"][2]
        fields = self.named["collisionFieldTypes"][2]
        layout = (vt[1], display[1], display[2], fields[1], fields[2])
        if layout == (680, 740, 15, 756, 6):
            return False
        if layout != (704, 680, 15, 696, 6):
            raise ValueError("unexpected data atom layout")
        data = self.by_name[".data"][1]
        raw = self.payload(data)
        if (
            raw[680:695] != b"S14 3WAY COLLI\0"
            or any(raw[695:696])
            or raw[696:702] != b"csFFF\0"
            or any(raw[702:704])
        ):
            raise ValueError("unexpected display or field strings/padding")
        self.data[data[4] : data[4] + 764] = raw[:680] + raw[704:] + raw[680:704]
        for name, offset, sym in self.symbols:
            if (
                sym[5] < len(self.sections)
                and self.names[sym[5]] == ".data"
                and sym[3] & 15 != 3
            ):
                if 680 <= sym[1] < 704:
                    sym[1] += 60
                elif 704 <= sym[1] < 764:
                    sym[1] -= 24
                self.put_symbol(offset, sym)
        for section in self.sections:
            if section[1] == 4 and self.names[section[7]] == ".data":
                for offset in range(section[4], section[4] + section[5], section[9]):
                    value = struct.unpack_from(">I", self.data, offset)[0]
                    if 680 <= value < 704:
                        value += 60
                    elif 704 <= value < 764:
                        value -= 24
                    struct.pack_into(">I", self.data, offset, value)
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
        dir=path.parent, prefix="laser-colli-normalize-"
    ) as tmp:
        source = Path(tmp) / "layout.o"
        output = Path(tmp) / "bound.o"
        source.write_bytes(work.data)
        command = (
            [str(objcopy)]
            + [f"--redefine-sym={a}={b}" for a, b in renames]
            + ["--globalize-symbol=collisionZero", str(source), str(output)]
        )
        subprocess.run(command, check=True)
        after = Elf(output.read_bytes())
        after.check()
        if (
            tuple(
                (
                    after.named[n][2][1]
                    for n in (
                        "collisionZero",
                        "__vt__16CollisionVirtual",
                        "collisionDisplayName",
                    )
                )
            )
            != (0, 680, 740)
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
