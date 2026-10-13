"""Guard native code and semantic relocation identity during data normalization."""

import hashlib
import os
import shutil
import struct
import subprocess
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import fix_ef_sparkle_object as fix


def fixture(collision=False):
    names = [
        "",
        ".text",
        ".rodata",
        ".data",
        ".bss",
        ".ctors",
        ".comment",
        ".symtab",
        ".strtab",
        ".rela.text",
        ".rela.data",
        ".rela.ctors",
        ".shstrtab",
    ]
    symbols = [("", 0, 0, 0, 0)]
    symbols.append(("", 0, 0, 3, 4))
    symbols.append(("@43", 0, 4, 1, 2))
    reverse = {v: k for k, v in fix.ALIASES.items()}
    offset = 0
    for name, size in fix.FUNCTION_SIZES.items():
        symbols.append((reverse.get(name, name), offset, size, 0x12, 1))
        offset += size
    symbols.extend(
        [
            ("__vt__9EfSparkle", 72, 32, 0x11, 3),
            ("lbl_16_data_3D20", 48, 23, 0x11, 3),
            ("prefix", 0, 48, 0x11, 3),
            ("floats", 4, 88, 0x11, 2),
            ("efSparkleRodataPadding", 92, 4, 0x11, 2),
            ("bss", 0, 24, 0x11, 4),
            ("ctor", 0, 4, 0x11, 5),
        ]
    )
    if collision:
        symbols.append(("lbl_16_rodata_9B0", 0, 4, 0x11, 2))
    strings = bytearray(b"\0")
    table = bytearray()
    for name, value, size, info, section in symbols:
        index = len(strings) if name else 0
        if name:
            strings.extend(name.encode() + b"\0")
        table.extend(struct.pack(">IIIBBH", index, value, size, info, 0, section))
    idx = {n: i for i, (n, *_) in enumerate(symbols)}
    rela = lambda offset, name, kind: struct.pack(
        ">IIi", offset, (idx[name] << 8) | kind, 0
    )
    data = bytearray(104)
    data[:48] = bytes(range(48))
    data[48:71] = b"./textures/ef_uv00.txd\0"
    rodata = bytes(4) + bytes(range(88)) + bytes(4)
    comment = bytearray(0x2C + len(symbols) * 8)
    struct.pack_into(">I", comment, 0x2C + 8, 8)
    section_strings = bytearray(b"\0")
    name_offsets = [0]
    for name in names[1:]:
        name_offsets.append(len(section_strings))
        section_strings.extend(name.encode() + b"\0")
    payloads = [
        b"",
        bytes(3268),
        rodata,
        data,
        bytes(24),
        bytes(4),
        comment,
        table,
        strings,
        rela(0, "__vt__9EfSparkle", 6) + rela(4, "@43", 4),
        rela(80, "__ct__9EfSparkleFUi", 1),
        rela(0, "__sinit_ef_sparkle_cpp", 1),
        section_strings,
    ]
    # type, flags, link, info, alignment, entry size
    metadata = [
        (0, 0, 0, 0, 0, 0),
        (1, 6, 0, 0, 4, 0),
        (1, 2, 0, 0, 8, 0),
        (1, 3, 0, 0, 8, 0),
        (8, 3, 0, 0, 8, 0),
        (1, 3, 0, 0, 4, 0),
        (1, 0, 0, 0, 1, 0),
        (2, 0, 8, 3, 4, 16),
        (3, 0, 0, 0, 1, 0),
        (4, 0, 7, 1, 4, 12),
        (4, 0, 7, 3, 4, 12),
        (4, 0, 7, 5, 4, 12),
        (3, 0, 0, 0, 1, 0),
    ]
    blob = bytearray(52)
    headers = []
    for i, (payload, (kind, flags, link, info, align, entsize)) in enumerate(
        zip(payloads, metadata)
    ):
        blob.extend(bytes((-len(blob)) % max(align, 1)))
        headers.append(
            (
                name_offsets[i],
                kind,
                flags,
                0,
                len(blob),
                len(payload),
                link,
                info,
                align,
                entsize,
            )
        )
        if kind != 8:
            blob.extend(payload)
    blob.extend(bytes((-len(blob)) % 4))
    shoff = len(blob)
    for h in headers:
        blob.extend(struct.pack(">10I", *h))
    struct.pack_into(
        ">16sHHIIIIIHHHHHH",
        blob,
        0,
        b"\x7fELF\x01\x02\x01" + bytes(9),
        1,
        20,
        1,
        0,
        0,
        shoff,
        0,
        52,
        0,
        0,
        40,
        len(headers),
        12,
    )
    return bytes(blob)


class SparkleNormalizationTests(unittest.TestCase):
    def setUp(self):
        tmp = tempfile.TemporaryDirectory(dir="/tmp", prefix="sparkle-test-")
        self.addCleanup(tmp.cleanup)
        self.path = Path(tmp.name) / "test.o"
        self.path.write_bytes(fixture())
        self.objcopy = shutil.which("llvm-objcopy")
        if not self.objcopy:
            self.skipTest("llvm-objcopy not installed")
        guard = patch.object(
            fix, "TEXT_SHA256", hashlib.sha256(bytes(3268)).hexdigest()
        )
        guard.start()
        self.addCleanup(guard.stop)

    def normalize(self):
        fix.normalize(self.path, self.objcopy)

    def test_permutation_aliases_relocations_and_idempotence(self):
        before = fix.Elf(self.path.read_bytes())
        self.normalize()
        after = fix.Elf(self.path.read_bytes())
        self.assertEqual(before.invariant(), after.invariant())
        self.assertEqual(
            before.payload(before.by_name[".text"][1]),
            after.payload(after.by_name[".text"][1]),
        )
        self.assertEqual(after.named["lbl_16_data_3D20"][2][1:3], [80, 23])
        self.assertEqual(after.named["__vt__9EfSparkle"][2][1], 48)
        self.assertEqual(after.by_name[".bss"][1][8], 8)
        os.utime(self.path, ns=(1000000000, 2000000000))
        result = self.path.read_bytes()
        self.normalize()
        self.assertEqual(result, self.path.read_bytes())
        self.assertEqual(self.path.stat().st_mtime_ns, 2000000000)

    def reject_mutation(self, mutate, expected):
        obj = fix.Elf(self.path.read_bytes())
        mutate(obj)
        self.path.write_bytes(obj.data)
        original = self.path.read_bytes()
        with self.assertRaisesRegex(ValueError, expected):
            self.normalize()
        self.assertEqual(original, self.path.read_bytes())

    def test_wrong_text_rejected(self):
        self.reject_mutation(
            lambda e: e.data.__setitem__(e.by_name[".text"][1][4], 1), "fingerprint"
        )

    def test_bad_padding_rejected(self):
        self.reject_mutation(
            lambda e: e.data.__setitem__(e.by_name[".data"][1][4] + 71, 1), "padding"
        )

    def test_bad_layout_rejected(self):
        def mutate(e):
            _, off, sym = e.named["lbl_16_data_3D20"]
            sym[1] += 1
            e.put_symbol(off, sym)

        self.reject_mutation(mutate, "layout")

    def test_defined_alias_collision_rejected(self):
        self.path.write_bytes(fixture(collision=True))
        original = self.path.read_bytes()
        with self.assertRaisesRegex(ValueError, "alias target collision"):
            self.normalize()
        self.assertEqual(original, self.path.read_bytes())

    def test_objcopy_text_corruption_is_atomic(self):
        original = self.path.read_bytes()
        run = subprocess.run

        def corrupt(command, **kwargs):
            result = run(command, **kwargs)
            path = Path(command[-1])
            e = fix.Elf(path.read_bytes())
            e.data[e.by_name[".text"][1][4]] = 1
            path.write_bytes(e.data)
            return result

        with patch.object(fix.subprocess, "run", side_effect=corrupt):
            with self.assertRaisesRegex(ValueError, "fingerprint|text changed"):
                self.normalize()
        self.assertEqual(original, self.path.read_bytes())

    def test_objcopy_binding_corruption_is_atomic(self):
        original = self.path.read_bytes()
        run = subprocess.run

        def corrupt(command, **kwargs):
            result = run(command, **kwargs)
            path = Path(command[-1])
            e = fix.Elf(path.read_bytes())
            _, off, sym = e.named["__ct__9EfSparkleFUi"]
            sym[3] = (
                0x22  # Weak instead of global: code bytes alone cannot detect this.
            )
            e.put_symbol(off, sym)
            path.write_bytes(e.data)
            return result

        with patch.object(fix.subprocess, "run", side_effect=corrupt):
            with self.assertRaisesRegex(ValueError, "relocation meanings"):
                self.normalize()
        self.assertEqual(original, self.path.read_bytes())
        self.assertEqual(list(self.path.parent.iterdir()), [self.path])

    def test_objcopy_retarget_corruption_is_atomic(self):
        original = self.path.read_bytes()
        run = subprocess.run

        def corrupt(command, **kwargs):
            result = run(command, **kwargs)
            path = Path(command[-1])
            e = fix.Elf(path.read_bytes())
            off = e.by_name[".rela.text"][1][4]
            info = struct.unpack_from(">I", e.data, off + 4)[0]
            struct.pack_into(">I", e.data, off + 4, (info & 255))
            path.write_bytes(e.data)
            return result

        with patch.object(fix.subprocess, "run", side_effect=corrupt):
            with self.assertRaisesRegex(ValueError, "relocation meanings"):
                self.normalize()
        self.assertEqual(original, self.path.read_bytes())


if __name__ == "__main__":
    unittest.main()
