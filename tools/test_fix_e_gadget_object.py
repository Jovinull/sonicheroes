"""Synthetic ELF tests; no retail or compiler instruction bytes are fixtures."""
import contextlib
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import fix_e_gadget_object as fix


def fixture():
    names = ["", ".text", "extab", "extabindex", ".data", ".rela.text",
             ".relaextabindex", ".rela.data", ".symtab", ".strtab", ".shstrtab", ".comment"]
    ids = {n: i for i, n in enumerate(names)}
    strings = bytearray(b"\0")
    def string(s):
        at = len(strings)
        strings.extend(s.encode() + b"\0")
        return at
    symbols = [(0, 0, 0, 0, 0, 0)]
    desc_to_index = {}
    def binding(d):
        if d[0] in ("file", "section"):
            return 0
        return d[-1] >> 4
    descriptors = [d for d in fix.SYMBOL_INVENTORY if d != ("undefined", "", 0, 0, 0)]
    descriptors.sort(key=lambda d: (binding(d) != 0, repr(d)))
    for d in descriptors:
        if d[0] == "file":
            sym = (string("synthetic.cpp"), 0, 0, 4, 0, 0xfff1)
        elif d[0] == "section":
            sym = (0, 0, 0, d[2], 0, ids[d[1]])
        elif d[0] == "defined":
            name = fix.DEFINED_NAMES.get(d[1:], "local_" + d[1] + str(d[2]))
            other = 2 if d[1] in ("extab", "extabindex") else 0
            sym = (string(name), d[2], d[3], d[4], other, ids[d[1]])
        else:
            sym = (string(d[1]), d[2], d[3], d[4], 0, 0)
        desc_to_index[d] = len(symbols)
        symbols.append(sym)
    local_count = 1 + sum(binding(d) == 0 for d in descriptors)
    undefined = next(i for d, i in desc_to_index.items() if d[0] == "undefined")
    funcs = sorted((d[2], d[3], i) for d, i in desc_to_index.items()
                   if d[0] == "defined" and d[1] == ".text")
    eh = sorted((d[2], i) for d, i in desc_to_index.items()
                if d[0] == "defined" and d[1] == "extab")
    rows = [funcs[0], *[f for f in funcs if f[0] >= 148]]
    def rela(off, sym, kind=1, addend=0):
        return struct.pack(">IIi", off, sym << 8 | kind, addend)
    payloads = {
        ".text": b"".join(struct.pack(">I", 0x60000000 | i) for i in range(162)),
        "extab": b"".join(struct.pack(">II", i, i + 10) for i in range(6)),
        "extabindex": b"".join(struct.pack(">III", 0, f[1], 0) for f in rows),
        ".data": bytes(80),
        ".rela.text": b"".join(rela(i * 4, undefined, 10) for i in range(12)),
        ".relaextabindex": b"".join(rela(i * 12, f[2]) + rela(i * 12 + 8, eh[i][1])
                                    for i, f in enumerate(rows)),
        ".rela.data": b"".join(rela(8 + i * 4, funcs[i % 14][2]) for i in range(17)),
        ".symtab": b"".join(struct.pack(">IIIBBH", *s) for s in symbols),
        ".strtab": bytes(strings),
        ".comment": b"synthetic fixture\0",
    }
    shstrings = bytearray(b"\0")
    offsets = {"": 0}
    for n in names[1:]:
        offsets[n] = len(shstrings)
        shstrings.extend(n.encode() + b"\0")
    payloads[".shstrtab"] = bytes(shstrings)
    data = bytearray(52)
    sections = [(0,) * 10]
    for n in names[1:]:
        typ, flags, align, link, info, entsize = 1, 0, 4, 0, 0, 0
        if n in fix.ALLOCATED_LAYOUT:
            typ, flags, _, align = fix.ALLOCATED_LAYOUT[n]
        elif n.startswith(".rela"):
            typ, link, entsize = 4, ids[".symtab"], 12
            target = {".rela.text": ".text", ".relaextabindex": "extabindex", ".rela.data": ".data"}[n]
            info = ids[target]
        elif n == ".symtab":
            typ, link, info, entsize = 2, ids[".strtab"], local_count, 16
        elif n in (".strtab", ".shstrtab"):
            typ, align, entsize = 3, 1, 1
        elif n == ".comment":
            align, entsize = 1, 1
        data.extend(bytes((-len(data)) % align))
        start = len(data)
        data.extend(payloads[n])
        sections.append((offsets[n], typ, flags, 0, start, len(payloads[n]), link, info, align, entsize))
    data.extend(bytes((-len(data)) % 4))
    shoff = len(data)
    for s in sections:
        data.extend(struct.pack(">10I", *s))
    ident = b"\x7fELF\x01\x02\x01" + bytes(9)
    struct.pack_into(">16sHHIIIIIHHHHHH", data, 0, ident, 1, 20, 1, 0, 0, shoff,
                     0x80000000, 52, 0, 0, 40, 12, ids[".shstrtab"])
    return bytes(data)


@contextlib.contextmanager
def contract(blob):
    e = fix.Elf(blob)
    inv, rels = e.descriptors(False)
    hashes = {}
    for n in fix.ALLOCATED_LAYOUT:
        b = e.payload(e.named[n])
        prefix = 148 if n == ".text" else 12 if n == "extabindex" else 0
        hashes[n] = (fix.digest(b), fix.digest(b[prefix:] + b[:prefix]))
    with patch.object(fix, "SECTION_HASHES", hashes), patch.object(fix, "SYMBOL_INVENTORY", tuple(inv)), \
            patch.object(fix, "RELOCATION_HASH", fix.signature(rels)):
        yield e


class NormalizeTests(unittest.TestCase):
    def setUp(self):
        self.raw = fixture()

    def test_permutation_preserves_every_body_and_relocation_identity(self):
        with contract(self.raw) as before:
            out = fix.normalize(self.raw)
            after = fix.Elf(out)
            self.assertEqual(fix.normalize(out), out)
            self.assertEqual(before.descriptors(False), after.descriptors(True))
            for n, prefix in ((".text", 148), ("extabindex", 12)):
                old = before.payload(before.named[n])
                self.assertEqual(after.payload(after.named[n]), old[prefix:] + old[:prefix])
            for n in ("extab", ".data", ".strtab", ".comment", ".shstrtab"):
                self.assertEqual(before.payload(before.named[n]), after.payload(after.named[n]))
            for s in before.symbols:
                if s[5] == before.named[".text"] and s[3] & 15 == 2:
                    start = fix.move(s[1], 648, 148)
                    self.assertEqual(before.payload(1)[s[1]:s[1] + s[2]], after.payload(1)[start:start + s[2]])

    def test_corrupt_allocated_payloads_reject(self):
        with contract(self.raw) as e:
            for name in fix.ALLOCATED_LAYOUT:
                with self.subTest(section=name):
                    b = bytearray(self.raw)
                    b[e.sections[e.named[name]][4]] ^= 1
                    with self.assertRaises(ValueError):
                        fix.normalize(b)

    def test_symbol_and_relocation_mutations_reject(self):
        with contract(self.raw) as e:
            symtab = e.sections[e.named[".symtab"]][4]
            fn = next(i for i, s in enumerate(e.symbols) if s[5] == 1 and s[3] & 15 == 2)
            mutations = [(symtab + fn * 16 + 4, ">I", 4),
                         (symtab + fn * 16 + 8, ">I", 4),
                         (symtab + fn * 16 + 12, ">B", 0x12),
                         (symtab + fn * 16 + 13, ">B", 2),
                         (e.relocations[0][0], ">I", 100),
                         (e.relocations[0][0] + 8, ">i", 4)]
            for pos, fmt, value in mutations:
                b = bytearray(self.raw)
                # Ensure mutation differs even if the selected function is already global.
                if struct.unpack_from(fmt, b, pos)[0] == value:
                    value ^= 1
                struct.pack_into(fmt, b, pos, value)
                with self.subTest(offset=pos), self.assertRaises(ValueError):
                    fix.normalize(b)

    def test_malformed_elf_and_layout_reject(self):
        with contract(self.raw):
            for cut in (0, 20, 51, len(self.raw) - 1):
                with self.subTest(cut=cut), self.assertRaises(ValueError):
                    fix.normalize(self.raw[:cut])
            for pos, fmt, value in ((5, ">B", 1), (18, ">H", 3), (32, ">I", 0xfffffff0),
                                    (48, ">H", 0xffff)):
                b = bytearray(self.raw)
                struct.pack_into(fmt, b, pos, value)
                with self.assertRaises(ValueError):
                    fix.normalize(b)
            shoff = struct.unpack_from(">I", self.raw, 32)[0]
            for field, value in ((8, 7), (16, 0), (24, 1), (32, 8)):
                b = bytearray(self.raw)
                struct.pack_into(">I", b, shoff + 40 + field, value)
                with self.assertRaises(ValueError):
                    fix.normalize(b)

    def test_unrelocated_branch_must_stay_inside_function(self):
        e = fix.Elf(self.raw)
        b = bytearray(self.raw)
        # Synthetic branch from byte100 to108 crosses the first function boundary.
        struct.pack_into(">I", b, e.sections[1][4] + 100, 0x48000008)
        with contract(bytes(b)), self.assertRaisesRegex(ValueError, "crosses function"):
            fix.normalize(b)
        struct.pack_into(">I", b, e.sections[1][4] + 100, 0x48000004)
        with contract(bytes(b)):
            self.assertNotEqual(fix.normalize(b), b)

    def test_section_symbol_addends_are_rebased(self):
        e = fix.Elf(self.raw)
        b = bytearray(self.raw)
        section_symbol = next(i for i, s in enumerate(e.symbols) if s[5] == 1 and s[3] & 15 == 3)
        pos = next(p for p, target, *_ in e.relocations if target == ".data")
        struct.pack_into(">Ii", b, pos + 4, section_symbol << 8 | 1, 112)
        with contract(bytes(b)):
            out = fix.normalize(b)
            self.assertEqual(struct.unpack_from(">i", out, pos + 8)[0], 612)
            self.assertEqual(fix.normalize(out), out)

    def test_cli_failure_is_atomic_and_success_is_idempotent(self):
        with tempfile.TemporaryDirectory(prefix="gadget-test-", dir="/tmp") as d:
            obj, stamp = Path(d) / "fixture.o", Path(d) / "stamps" / "ok"
            obj.write_bytes(self.raw)
            with contract(self.raw):
                damaged = bytearray(self.raw)
                damaged[fix.Elf(self.raw).sections[1][4]] ^= 1
                obj.write_bytes(damaged)
                with self.assertRaises(ValueError):
                    fix.main([str(obj), str(stamp)])
                self.assertEqual(obj.read_bytes(), damaged)
                self.assertFalse(stamp.exists())
                obj.write_bytes(self.raw)
                with self.assertRaises(ValueError):
                    fix.main([str(obj), str(obj)])
                self.assertEqual(obj.read_bytes(), self.raw)
                fix.main([str(obj), str(stamp)])
                result = obj.read_bytes()
                self.assertTrue(stamp.exists())
                fix.main([str(obj), str(stamp)])
                self.assertEqual(obj.read_bytes(), result)
                self.assertEqual(sorted(p.name for p in Path(d).iterdir()), ["fixture.o", "stamps"])


if __name__ == "__main__":
    unittest.main()
