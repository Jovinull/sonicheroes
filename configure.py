#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "G9SE8P",  # 0 - NTSC-U (USA) retail
    # "G9SP8P",  # 1 - PAL (Europe) retail       -- not configured yet
    # "G9SJ8P",  # 2 - NTSC-J (Japan) retail     -- not configured yet
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3-sh1"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-multibyte",  # For Wii compilers, replace with `-enc SJIS`
    "-i include",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
]

config.linker_version = "GC/1.3.2"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "game",
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        # The Metrowerks standard library, like TRK, was not built with the
        # compiler the rest of the tree uses. __copy_longs_aligned written as C
        # is two instructions out under 1.3.2 and exact under 1.3: the later
        # compiler folds the tail mask into clrlwi where 1.3 materializes the
        # constant and uses and. The four functions that already matched are
        # unaffected either way, so they act as the control.
        "lib": "MSL_C",
        "mw_version": "GC/1.3",
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "MSL_C/mem.c"),
        ],
    },
    {
        "lib": "dolphin",
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "dolphin/os/__start.c"),
            Object(Matching, "dolphin/os/OSArena.c"),
            Object(Matching, "dolphin/base/PPCArch.c"),
            Object(Matching, "dolphin/db/db.c"),
            Object(Matching, "dolphin/os/OSFpu.c"),
            # Built without the peephole pass, like the original. With it on,
            # register copies come out as addi rD,rS,0 instead of mr and single
            # exit returns collapse into bnelr, neither of which the original
            # has.
            Object(Matching, "dolphin/os/OS.c", extra_cflags=["-opt nopeephole"]),
            Object(Matching, "dolphin/dvd/dvdlow.c"),
            Object(Matching, "dolphin/dvd/dvdfs.c"),
            Object(Matching, "dolphin/dvd/dvd.c"),
            Object(Matching, "dolphin/dvd/dvdqueue.c"),
            Object(Matching, "dolphin/dvd/dvderror.c"),
            Object(Matching, "dolphin/dvd/dvdFatal.c"),
            Object(Matching, "dolphin/dvd/dvdidutils.c"),
            Object(Matching, "dolphin/dvd/fstload.c"),
            Object(Matching, "dolphin/pad/Padclamp.c"),
            # -inline noauto (leaving the default -inline on): with auto the compiler folds
            # PADReset/PADRecalibrate bodily into PADInit/PADRead/OnReset where
            # the original emits bl, and no source shape stops it. With
            # -inline on plus the inline keyword on the small helpers
            # (DoReset, PADEnable, PADDisable, ClampS8, ClampU8, PADSync)
            # every function's size comes out exactly as the original's.
            Object(Matching, "dolphin/pad/Pad.c", extra_cflags=["-inline noauto"]),
            Object(Matching, "dolphin/amcstubs.c"),
            Object(Matching, "dolphin/vi/vi.c"),
            Object(Matching, "dolphin/ai/ai.c"),
            Object(Matching, "dolphin/ar/ar.c"),
            Object(Matching, "dolphin/ar/arq.c"),
            Object(
                Matching,
                "dolphin/db/dbcomm.c",
                extra_cflags=[
                    "-use_lmw_stmw on",
                    "-str reuse,pool,readonly",
                    "-common off",
                    "-inline deferred,auto",
                    "-char signed",
                ],
            ),
            Object(Matching, "dolphin/exi/EXIBios.c", extra_cflags=["-opt noschedule"]),
            Object(NonMatching, "dolphin/si/SIBios.c"),
            Object(Matching, "dolphin/si/SISamplingRate.c"),
            Object(Matching, "dolphin/os/OSInterrupt.c"),
            Object(Matching, "dolphin/os/OSSram.c"),
            Object(Matching, "dolphin/os/OSAlarm.c"),
            Object(Matching, "dolphin/os/OSAlloc.c"),
            Object(Matching, "dolphin/os/OSMemory.c"),
            Object(Matching, "dolphin/os/OSMutex.c"),
            Object(Matching, "dolphin/os/OSAudioSystem.c"),
            Object(Matching, "dolphin/os/OSReboot.c"),
            Object(Matching, "dolphin/os/OSResetSW.c"),
            Object(Matching, "dolphin/os/OSStopwatch.c"),
            Object(Matching, "dolphin/os/OSSync.c"),
            # -inline noauto, like Pad.c: with auto the compiler folds
            # __OSGetEffectivePriority, OSWakeupThread and UnsetRun into their
            # callers where the original emits bl. The helpers the original does
            # expand carry the inline keyword instead.
            Object(Matching, "dolphin/os/OSThread.c", extra_cflags=["-inline noauto"]),
            Object(Matching, "dolphin/os/OSReset.c"),
            Object(Matching, "dolphin/os/OSCache.c"),
            Object(Matching, "dolphin/os/OSContext.c"),
            Object(Matching, "dolphin/os/OSError.c"),
            Object(Matching, "dolphin/os/OSLink.c"),
            Object(Matching, "dolphin/os/OSTime.c"),
            Object(Matching, "Runtime.PPCEABI.H/__ppc_eabi_init.c"),
        ],
    },
    {
        # The debugger nub is Metrowerks' own library, not part of the Dolphin
        # SDK, and it was built with a different compiler: every function here
        # is wrong under 1.2.5n and exact under 1.3.2. The tell is the prologue,
        # which pushes the frame before saving the link register, and the
        # indirect call, which goes through the count register rather than the
        # link register.
        "lib": "TRK",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [
            Object(
                Matching,
                "dolphin/trk/dolphin_trk.c",
                extra_cflags=["-str reuse,readonly"],
            ),
            Object(Matching, "dolphin/trk/targimpl.c", extra_cflags=["-sdata 0", "-sdata2 0", "-common off"]),
            Object(Matching, "dolphin/trk/nubevent.c"),
            Object(
                Matching,
                "dolphin/trk/nubinit.c",
                extra_cflags=["-str reuse,readonly", "-sdata 0", "-sdata2 0"],
            ),
        ],
    },
    {
        # Sonic Heroes' own code, as opposed to the SDK linked into it. Nothing
        # here is named yet: the disc ships no map, so every translation unit
        # boundary in this range has to be argued for from cross references.
        "lib": "game",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": [
            Object(
                Matching,
                "game/heap.c",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopropagation"],
            ),
            Object(
                Matching,
                "game/main.c",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule"],
            ),
        ],
    },
    Rel(
        "autosaveD",
        [
            Object(
                Matching,
                "autosaveD/window_constructor.c",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/table.c",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
        ],
    ),
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "Runtime.PPCEABI.H/__mem.c"),
            Object(Matching, "Runtime.PPCEABI.H/runtime.c"),
            Object(Matching, "Runtime.PPCEABI.H/__va_arg.c"),
            Object(Matching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(Matching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
        ],
    },
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
