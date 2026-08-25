#!/usr/bin/env python3

"""Restore TEndSPStage's retail data atom and stage-local link names.

MWCC emits the class vtable after its string pool when both use the ordinary
data section. The source gives the two trailing strings a temporary section so
MWCC can place its generated vtable first. This normalizer then appends that
atom to regular data without changing its bytes or relocation order.

The source also uses the recovered C++ names for inherited virtual functions.
Several implementations are stage-local stubs whose retail link names remain
address placeholders, so those undefined references are restored here.
"""

import argparse
import struct
import subprocess
import tempfile
from pathlib import Path


LINK_RENAMES = (
    ("TDisp__7TObjectFv", "sampleHook1"),
    ("ImmAftSetRaster__7TObjectFv", "sampleHook2"),
    ("Debug__7TObjectFv", "sampleHook3"),
    ("Render__7TObjectFv", "sampleHook4"),
    ("__dl__11TEndSPStageFPv", "__dl__10TObjSampleFPv"),
    ("PDisp__7TObjectFv", "fn_16_11640"),
    ("Disp__7TObjectFv", "fn_16_5F3B0"),
    ("__dt__7TObjectFv", "fn_16_5F55C"),
    ("__ct__12TObjGoalringFP11TEndSPStage", "fn_16_8DBF8"),
)


def section_headers(data: bytes) -> tuple[list[list[int]], int]:
    section_offset = struct.unpack_from(">I", data, 0x20)[0]
    section_size = struct.unpack_from(">H", data, 0x2E)[0]
    section_count = struct.unpack_from(">H", data, 0x30)[0]
    string_index = struct.unpack_from(">H", data, 0x32)[0]
    headers = [
        list(struct.unpack_from(">10I", data, section_offset + index * section_size))
        for index in range(section_count)
    ]
    return headers, string_index


def section_names(data: bytes, headers: list[list[int]], string_index: int) -> list[str]:
    string_header = headers[string_index]
    strings = data[string_header[4] : string_header[4] + string_header[5]]
    names = []
    for header in headers:
        end = strings.find(b"\0", header[0])
        names.append(strings[header[0] : end].decode("ascii"))
    return names


def retarget_symbols(
    data: bytearray,
    headers: list[list[int]],
    names: list[str],
    old_section: int,
    new_section: int,
    value_addend: int,
) -> None:
    symbol_header = headers[names.index(".symtab")]
    entry_size = symbol_header[9]
    for offset in range(
        symbol_header[4],
        symbol_header[4] + symbol_header[5],
        entry_size,
    ):
        section = struct.unpack_from(">H", data, offset + 14)[0]
        if section == old_section:
            value = struct.unpack_from(">I", data, offset + 4)[0]
            struct.pack_into(">I", data, offset + 4, value + value_addend)
            struct.pack_into(">H", data, offset + 14, new_section)


def symbol_names(data: bytes, headers: list[list[int]], names: list[str]) -> set[str]:
    symbol_header = headers[names.index(".symtab")]
    string_header = headers[symbol_header[6]]
    strings = data[string_header[4] : string_header[4] + string_header[5]]
    found = set()
    for offset in range(
        symbol_header[4],
        symbol_header[4] + symbol_header[5],
        symbol_header[9],
    ):
        name_offset = struct.unpack_from(">I", data, offset)[0]
        end = strings.find(b"\0", name_offset)
        found.add(strings[name_offset:end].decode("ascii"))
    return found


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    parser.add_argument("--objcopy", required=True, type=Path)
    args = parser.parse_args()

    object_data = bytearray(args.object.read_bytes())
    headers, string_index = section_headers(object_data)
    names = section_names(object_data, headers, string_index)
    data_index = names.index(".data")
    strings_index = names.index(".endsp_strings")
    data_header = headers[data_index]
    strings_header = headers[strings_index]

    retarget_symbols(
        object_data,
        headers,
        names,
        strings_index,
        data_index,
        data_header[5],
    )

    data_end = data_header[4] + data_header[5]
    strings_end = strings_header[4] + strings_header[5]
    strings = object_data[strings_header[4] : strings_end]
    removed_padding = strings_header[4] - data_end
    old_section_offset = struct.unpack_from(">I", object_data, 0x20)[0]

    normalized = object_data[:data_end] + strings + object_data[strings_end:]
    new_section_offset = old_section_offset - removed_padding
    struct.pack_into(">I", normalized, 0x20, new_section_offset)

    for index, header in enumerate(headers):
        header_offset = new_section_offset + index * 40
        if index == data_index:
            struct.pack_into(">I", normalized, header_offset + 20, data_header[5] + strings_header[5])
        elif index == strings_index:
            struct.pack_into(">I", normalized, header_offset + 16, data_end + strings_header[5])
            struct.pack_into(">I", normalized, header_offset + 20, 0)
        elif header[4] >= strings_end and header[1] != 8:
            struct.pack_into(">I", normalized, header_offset + 16, header[4] - removed_padding)

    # objcopy --redefine-sym is silent when the source symbol is absent, so a
    # rename that quietly stops applying would only surface as an artifact hash
    # mismatch much later. Check the table before handing it over.
    #
    # This step edits the object in place and is not idempotent, so ninja
    # re-running it after the script's own mtime changes sees an object whose
    # sources are all gone and whose targets are all present. That state is
    # already-applied, not broken, and must not fail the build.
    present = symbol_names(object_data, headers, names)
    missing = sorted(old for old, _ in LINK_RENAMES if old not in present)
    if missing:
        if all(new in present for _, new in LINK_RENAMES):
            args.stamp.parent.mkdir(parents=True, exist_ok=True)
            args.stamp.touch()
            return
        raise SystemExit(
            "TEndSPStage rename sources absent from the object: " + ", ".join(missing)
        )

    with tempfile.TemporaryDirectory() as directory:
        normalized_path = Path(directory) / "normalized.o"
        renamed_path = Path(directory) / "renamed.o"
        normalized_path.write_bytes(normalized)
        subprocess.run(
            [
                args.objcopy,
                *[
                    argument
                    for old, new in LINK_RENAMES
                    for argument in ("--redefine-sym", f"{old}={new}")
                ],
                normalized_path,
                renamed_path,
            ],
            check=True,
        )
        args.object.write_bytes(renamed_path.read_bytes())

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
