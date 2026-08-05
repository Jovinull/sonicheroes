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

# The same without fused multiply-add, for units whose original was built that
# way. The flag is replaced rather than appended, which is how tww, pikmin2 and
# ogws carry the same override.
cflags_rel_nofma = [
    *[flag for flag in cflags_base if flag != "-fp_contract on"],
    "-fp_contract off",
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
            Object(Matching, "MSL_C/GCN_Mem_Alloc.c", extra_cflags=["-str nopool"]),
            Object(Matching, "MSL_C/abort_exit.c"),
            Object(Matching, "MSL_C/misc_io.c"),
            Object(Matching, "MSL_C/buffer_io.c"),
            Object(Matching, "MSL_C/char_io.c"),
            Object(Matching, "MSL_C/direct_io.c"),
            Object(Matching, "MSL_C/file_io.c"),
            Object(Matching, "MSL_C/FILE_POS.c"),
            Object(Matching, "MSL_C/mbstring.c", extra_cflags=["-char signed"]),
            Object(Matching, "MSL_C/printf.c"),
            Object(Matching, "MSL_C/string.c", extra_cflags=["-O3,p", "-opt schedule"]),
            Object(
                Matching,
                "MSL_C/strtold.c",
                extra_cflags=["-sdata 4", "-char signed", "-inline deferred,auto"],
            ),
            Object(Matching, "MSL_C/strtoul.c"),
            Object(Matching, "MSL_C/uart_console_io.c"),
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
            Object(Matching, "dolphin/gx/GXInit.c", extra_cflags=['-i src/dolphin/gx', '-opt nopeephole']),
            Object(Matching, "dolphin/gx/GXFifo.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
            Object(Matching, "dolphin/gx/GXAttr.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
            Object(Matching, "dolphin/gx/GXMisc.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
            Object(Matching, "dolphin/gx/GXGeometry.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
            Object(Matching, "dolphin/gx/GXFrameBuf.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
            Object(Matching, "dolphin/gx/GXLight.c", extra_cflags=['-i src/dolphin/gx', '-common off', '-fp_contract off']),
            Object(Matching, "dolphin/gx/GXTexture.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
            Object(Matching, "dolphin/gx/GXBump.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
            Object(Matching, "dolphin/gx/GXTev.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
            Object(Matching, "dolphin/gx/GXPixel.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
            Object(Matching, "dolphin/gx/GXDisplayList.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
            Object(Matching, "dolphin/gx/GXTransform.c", extra_cflags=['-i src/dolphin/gx', '-common off', '-fp_contract off']),
            Object(Matching, "dolphin/gx/GXPerf.c", extra_cflags=['-i src/dolphin/gx', '-common off']),
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
            Object(Matching, "dolphin/si/SIBios.c", extra_cflags=["-inline level=1"]),
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
            Object(Matching, "game/object_defaults.cpp"),
            Object(
                Matching,
                "game/skeleton.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/hAnim.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole", "-fp_contract off"],
            ),
            Object(
                Matching,
                "game/vibration.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/heap.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopropagation"],
            ),
            Object(
                Matching,
                "game/main.c",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule"],
            ),
            Object(
                Matching,
                "game/object_dispatch.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/path.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/time.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/task_create.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/skyfs_adx.c",
                extra_cflags=[
                    "-lang=c++",
                    "-Cpp_exceptions on",
                    "-opt noschedule,nopeephole",
                    "-inline deferred",
                ],
            ),
            Object(
                Matching,
                "game/Peripheral.cpp",
                extra_cflags=["-lang=c++", "-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/main/main.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/Task.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/Memory.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/movie.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/moviePlaySub.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
                data_section_alignment=4,
            ),
            Object(
                Matching,
                "game/moviePlay.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/Endian.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/GetSpParam.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/dAnim.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole", "-fp_contract off"],
            ),
            Object(
                Matching,
                "game/dAnim_ctor.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/eventCore.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/SeqFlagCtrl.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/expasm.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopropagation,nopeephole"],
            ),
            Object(
                Matching,
                "game/texture.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/camera_slot_update.cpp",
                extra_cflags=["-Cpp_exceptions on", "-fp_contract off", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/camera_slot_create.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/wide_format_core.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopropagation,nopeephole"],
            ),
            Object(
                Matching,
                "game/wide_format_write.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/SpAdvStgFailed.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/SpAdvStgFailed_bss.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/enemy_voice.cpp",
                extra_cflags=["-Cpp_exceptions on", "-bool off", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "game/action.cpp",
                extra_cflags=[
                    "-Cpp_exceptions on",
                    "-bool off",
                    "-opt noschedule,nopeephole",
                ],
            ),
            Object(
                Matching,
                "game/action_cont1.cpp",
                extra_cflags=[
                    "-Cpp_exceptions on",
                    "-bool off",
                    "-opt noschedule,nopeephole",
                ],
            ),
            Object(
                Matching,
                "game/action_cont2.cpp",
                extra_cflags=[
                    "-Cpp_exceptions on",
                    "-bool off",
                    "-opt noschedule,nopeephole",
                ],
            ),
            Object(
                Matching,
                "game/action_cont3.cpp",
                extra_cflags=[
                    "-Cpp_exceptions on",
                    "-bool off",
                    "-opt noschedule,nopeephole",
                ],
            ),
            Object(
                Matching,
                "game/action_cont4.cpp",
                extra_cflags=[
                    "-Cpp_exceptions on",
                    "-bool off",
                    "-opt noschedule,nopeephole",
                ],
            ),
            Object(
                Matching,
                "game/perf.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole", "-str nopool"],
            ),
            Object(
                Matching,
                "game/modeswitch.cpp",
                extra_cflags=[
                    "-Cpp_exceptions on",
                    "-inline deferred",
                    "-opt noschedule,nopeephole",
                ],
            ),
            Object(
                Matching,
                "game/e_paralysis.cpp",
                extra_cflags=[
                    "-Cpp_exceptions on",
                    "-inline deferred",
                    "-opt noschedule,nopeephole",
                ],
            ),
            Object(
                Matching,
                "game/voice_sequence.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
                data_section_alignment=4,
            ),
            Object(
                Matching,
                "game/obj_set_damage_collision.cpp",
                extra_cflags=["-Cpp_exceptions on", "-opt noschedule,nopeephole"],
            ),
        ],
    },
    Rel(
        "advertiseD",
        [
            Object(
                Matching,
                "advertiseD/adv_e3rom.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "advertiseD/adv_title.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
                data_section_alignment=4,
            ),
            Object(
                Matching,
                "advertiseD/adv_fileselect.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
                data_section_alignment=4,
            ),
            Object(
                Matching,
                "advertiseD/adv_mainmenu.cpp",
                extra_cflags=[
                    "-lang=c++",
                    "-opt noschedule,nopeephole",
                    "-inline noauto",
                ],
            ),
            Object(
                Matching,
                "advertiseD/adv_player.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "advertiseD/adv_progressive.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole", "-pool off"],
            ),
            Object(
                Matching,
                "advertiseD/adv_story.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole", "-pool off"],
            ),
            Object(
                Matching,
                "advertiseD/prolog.c",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "advertiseD/adv_story_tail.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole", "-pool off"],
            ),
            Object(
                Matching,
                "advertiseD/adv_challenge.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole", "-pool off"],
                data_section_alignment=4,
            ),
            Object(
                Matching,
                "advertiseD/adv_option.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole", "-pool off"],
                data_section_alignment=4,
            ),
            Object(
                Matching,
                "advertiseD/adv_audio.cpp",
                extra_cflags=[
                    "-lang=c++",
                    "-opt noschedule,nopeephole",
                    "-pool off",
                    "-inline noauto",
                ],
            ),
            Object(
                Matching,
                "advertiseD/adv_cg.cpp",
                extra_cflags=[
                    "-lang=c++",
                    "-opt noschedule,nopeephole",
                    "-pool off",
                    "-inline noauto",
                ],
            ),
            Object(
                Matching,
                "advertiseD/adv_2p.cpp",
                extra_cflags=[
                    "-lang=c++",
                    "-opt noschedule,nopeephole",
                    "-pool off",
                    "-inline deferred,noauto",
                ],
            ),
            Object(
                Matching,
                "advertiseD/adv_pal.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole", "-pool off"],
            ),
            Object(
                Matching,
                "advertiseD/adv_bar.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole", "-pool off"],
            ),
            Object(
                Matching,
                "advertiseD/adv_bg.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole", "-pool off"],
            ),
            Object(Matching, "advertiseD/adv_staffroll_data.cpp", extra_cflags=["-lang=c++"]),
            Object(
                Matching,
                "advertiseD/adv_staffroll.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole", "-pool off"],
            ),
            Object(
                Matching,
                "advertiseD/adv_draw.cpp",
                extra_cflags=[
                    "-lang=c++",
                    "-opt noschedule,nopeephole",
                    "-pool off",
                    "-inline deferred,noauto",
                ],
            ),
            Object(
                Matching,
                "advertiseD/adv_draw_constants.cpp",
                extra_cflags=["-lang=c++", "-pool off"],
            ),
            Object(
                Matching,
                "advertiseD/adv_window.cpp",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole", "-pool off"],
            ),
        ],
    ),
    Rel(
        "autosaveD",
        [
            Object(
                Matching,
                "autosaveD/line_count.c",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/task_runtime.c",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/emblem_task.c",
                cflags=cflags_rel_nofma,
                extra_cflags=["-lang=c++", "-pool off", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/task_callback_setters.c",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/prolog.c",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/task_object.c",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/task_system.c",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/quad_fill.c",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/widget_slices.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/quad_submit.c",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/widget_rendering.c",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/window_frame.c",
                cflags=cflags_rel_nofma,
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/window_input.c",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/window_lifecycle.c",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/state_selector.c",
                extra_cflags=["-lang=c++", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/menu_selectors.c",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "autosaveD/table.c",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
        ],
    ),
    {
        # One source, linked into every stage module. Each module's splits.txt
        # names it and its own symbols.txt renames that module's table, blocks
        # and init entry to the shared names below, so the same object resolves
        # per module at link time. The Wind Waker does this with
        # REL/executor.c, which its rels list the same way.
        "lib": "rel",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "game",
        "objects": [
            Object(
                Matching,
                "rel/prolog.c",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s33_dice.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s11_bob.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s33_roulet.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s33_slot.cpp",
                extra_cflags=["-pool off", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s33_chip.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s01_taihostull.cpp",
                extra_cflags=["-pool off", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s01_shachicolli.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/stage40_prolog.cpp",
                extra_cflags=[
                    "-O0",
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                ],
            ),
            Object(
                Matching,
                "rel/o_sample2.cpp",
                extra_cflags=[
                    "-O0",
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                    "-pool off",
                ],
            ),
            Object(
                Matching,
                "rel/o_system4.cpp",
                extra_cflags=[
                    "-O0",
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                    "-pool off",
                ],
            ),
            Object(
                Matching,
                "rel/ef_sparkle.cpp",
                extra_cflags=[
                    "-O0",
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                    "-pool off",
                    "-fp_contract off",
                ],
            ),
            Object(
                Matching,
                "rel/o_system3.cpp",
                extra_cflags=[
                    "-O0",
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                    "-pool off",
                ],
            ),
            Object(
                Matching,
                "rel/o_system2.cpp",
                extra_cflags=[
                    "-O0",
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                    "-pool off",
                ],
            ),
            Object(
                Matching,
                "rel/o_system1.cpp",
                extra_cflags=[
                    "-O0",
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                    "-pool off",
                ],
            ),
            Object(
                Matching,
                "rel/ef_rain.cpp",
                extra_cflags=[
                    "-O0",
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                    "-pool off",
                ],
            ),
            Object(Matching, "rel/ef_rain_strings.cpp"),
            Object(
                Matching,
                "rel/TEnemyAppearChaosEmerald.cpp",
                extra_cflags=[
                    "-O0",
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                    "-pool off",
                ],
            ),
            Object(Matching, "rel/TEnemyAppearChaosEmerald_strings.cpp"),
            Object(
                Matching,
                "rel/o_s01_ciseki.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/e_appear_spboss.cpp",
                extra_cflags=[
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                ],
            ),
            Object(
                Matching,
                "rel/TEndSkyBob.cpp",
                extra_cflags=[
                    "-inline noauto",
                    "-pool off",
                    "-opt noschedule,nopropagation,nopeephole",
                ],
            ),
            Object(
                Matching,
                "rel/TEndSPStage.cpp",
                extra_cflags=[
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                ],
            ),
            Object(
                Matching,
                "rel/o_setDamegeCollision.cpp",
                extra_cflags=["-opt noschedule,nopeephole", "-str nopool"],
                data_section_alignment=4,
            ),
            Object(
                Matching,
                "rel/o_sample.cpp",
                extra_cflags=[
                    "-O0",
                    "-inline noauto",
                    "-opt noschedule,nopropagation,nopeephole",
                    "-pool off",
                ],
            ),
            Object(
                Matching,
                "rel/o_s11_cloud.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/spring_object.cpp",
                cflags=cflags_rel_nofma,
                extra_cflags=["-pool off", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/spring_dtor.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/obj_transform.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/obj_set_mode.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/scroll_ring_create.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/tri_spring_reset.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/tri_spring_unload.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/tri_spring_load.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_update.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_direction.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_nearby.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_dtor.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_transform.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_hooks.cpp",
                extra_cflags=[],
            ),
            Object(
                Matching,
                "rel/set_collision_hooks.cpp",
                extra_cflags=[],
            ),
            Object(
                Matching,
                "rel/dashpanel_hooks.cpp",
                extra_cflags=[],
            ),
            Object(
                Matching,
                "rel/obj_group_query.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/obj_box_trigger.cpp",
                extra_cflags=["-pool off", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/obj_base_stubs.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/obj_apply_transform.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/ironball_dtor.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/scroll_ring_step.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/scroll_ring_touch.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/scroll_ring_disp.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/obj_reset_draw.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/propeller_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/push_pull_switch_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/light_collision_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_invoke_colli.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/system_object1_object.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/system_object1_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/system_object2_object.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/system_object2_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/system_object3_object.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/system_object3_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/system_object4_object.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/system_object4_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/cannon_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/cannon_hooks.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/sample1_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/sample2_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/ironball_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/jump_panel_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/checkpoint_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/wood_container_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/iron_container_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/iron_container_unload.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/unbreakable_container_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/unbreakable_container_unload.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/weight_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/breakable_weight_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/lens_flare_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/goal_ring_register.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/pawn_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/shield_splinter_dtor.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/item_box_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/pole_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/case_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/roll_door_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/signal_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/dash_ring_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/reel_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/laser_fence_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/big_rings_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/cage_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/target_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/fan_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/tri_spring_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/dashpanel_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/dashpanel_dtor.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/dashpanel_object.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/set_collision_dtor.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/set_collision_object.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_unload.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_load.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_guard.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/switch_object.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/spring_assets.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/spring_ctor.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/spring_clamp.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/sample1_object.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/sample2_object.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s01_hata.cpp",
                extra_cflags=[
                    "-pool off",
                    "-opt noschedule,nopeephole",
                ],
            ),
            Object(
                Matching,
                "rel/o_s01_object_a34c_create.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s01_object_a34c_dtor.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s01_base_collision.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s01_base.cpp",
                extra_cflags=["-pool off", "-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/o_s01_hana.cpp",
                extra_cflags=[
                    "-pool off",
                    "-opt noschedule,nopeephole",
                ],
            ),
            Object(
                Matching,
                "rel/o_s01_iwamizu.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/e_capture_collision.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/e_appear_spboss_pos.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "rel/e_end_spboss.cpp",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "stage13D/o_s13_blinklight.cpp",
                cflags=cflags_rel_nofma,
                data_section_alignment=4,
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "stage13D/o_s13_antenna.cpp",
                cflags=cflags_rel_nofma,
                data_section_alignment=8,
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "stage13D/o_s14_3way_colli.cpp",
                cflags=cflags_rel_nofma,
                data_section_alignment=8,
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
        ],
    },
    Rel(
        "movieD",
        [
            Object(
                Matching,
                "movieD/prolog.c",
                extra_cflags=["-opt noschedule,nopeephole"],
            ),
            Object(
                Matching,
                "movieD/cri/sud.c",
                extra_cflags=["-str readonly", "-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "movieD/cri/sfxset.c",
                extra_cflags=["-str readonly", "-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "movieD/cri/sfxcnv.c",
                extra_cflags=["-str readonly", "-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "movieD/cri/sfx.c",
                extra_cflags=[
                    "-lang=c++",
                    "-bool off",
                    "-str readonly",
                    "-use_lmw_stmw on",
                    "-common off",
                ],
            ),
            Object(
                Matching,
                "movieD/cri/sfxahn.c",
                extra_cflags=["-str readonly", "-use_lmw_stmw on"],
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
            Object(
                Matching,
                "Runtime.PPCEABI.H/NMWException.cpp",
            ),
            Object(Matching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
            Object(
                Matching,
                "Runtime.PPCEABI.H/Gecko_ExceptionPPC.cpp",
                extra_cflags=["-str reuse,nopool,readonly"],
                extab_padding=[0x25, 0x00],
            ),
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

# GNU objcopy, from the same binutils package used for GNU as (config.binutils_tag
# above): config.binutils_path if given on the command line, otherwise wherever
# project.py downloads config.binutils_tag to. Needed for --redefine-sym, which
# mwcc has no way to spell in C.
binutils_dir = config.binutils_path or (config.build_dir / "binutils")
objcopy_exe = "powerpc-eabi-objcopy.exe" if is_windows() else "powerpc-eabi-objcopy"
objcopy_path = binutils_dir / objcopy_exe
ld_path = binutils_dir / ("powerpc-eabi-ld.exe" if is_windows() else "powerpc-eabi-ld")
nm_path = binutils_dir / ("powerpc-eabi-nm.exe" if is_windows() else "powerpc-eabi-nm")
objdump_path = binutils_dir / (
    "powerpc-eabi-objdump.exe" if is_windows() else "powerpc-eabi-objdump"
)

config.custom_build_rules = [
    {
        "name": "fix_wide_format_core_object",
        "command": "$python tools/fix_wide_format_core_object.py $in $out",
        "description": "FIX wide_format_core.cpp compiler-only codegen",
    },
    {
        "name": "fix_ef_sparkle_object",
        "command": f"$python tools/fix_ef_sparkle_object.py $in $out --objcopy {objcopy_path}",
        "description": "FIX ef_sparkle compiler-owned atom order",
    },
    {
        "name": "fix_ef_rain_object",
        "command": f"$python tools/fix_ef_rain_object.py $in $out",
        "description": "FIX ef_rain generated function order",
    },
    {
        "name": "fix_stage40_delete_symbols",
        "command": f"$python tools/fix_stage40_delete_symbols.py $in --objcopy {objcopy_path}",
        "description": "FIX stage40 shared delete symbol",
    },
    {
        "name": "fix_ef_rain_strings_object",
        "command": f"$python tools/fix_ef_rain_strings_object.py $in $out",
        "description": "FIX ef_rain filename alignment",
    },
    {
        "name": "fix_enemy_appear_spboss_object",
        "command": (
            f"$python tools/fix_enemy_appear_spboss_object.py $in $out "
            f"--objcopy {objcopy_path} --ld {ld_path}"
        ),
        "description": "FIX e_appear_spboss.cpp data atom order",
    },
    {
        "name": "fix_end_sky_bob_object",
        "command": (
            f"$python tools/fix_end_sky_bob_object.py $in $out "
            f"--objcopy {objcopy_path} --ld {ld_path}"
        ),
        "description": "FIX TEndSkyBob.cpp data atom order",
    },
    {
        "name": "fix_sud_symbols",
        "command": f"$python tools/fix_sud_symbols.py $in $out --objcopy {objcopy_path}",
        "description": "FIX SUD symbols",
    },
    {
        "name": "fix_game_main_symbols",
        "command": f"$python tools/fix_game_main_symbols.py $in $out --objcopy {objcopy_path}",
        "description": "FIX main.cpp symbols",
    },
    {
        "name": "fix_game_task_object",
        "command": f"$python tools/fix_game_task_object.py $in $out --objcopy {objcopy_path}",
        "description": "FIX Task.cpp object layout",
    },
    {
        "name": "fix_tend_sp_stage_object",
        "command": (
            f"$python tools/fix_tend_sp_stage_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX TEndSPStage.cpp data atom order",
    },
    {
        "name": "fix_game_memory_object",
        "command": f"$python tools/fix_game_memory_object.py $in $out --objcopy {objcopy_path}",
        "description": "FIX Memory.cpp object layout",
    },
    {
        "name": "fix_game_action_object",
        "command": f"$python tools/fix_game_action_object.py $in $out --objcopy {objcopy_path} --part 0",
        "description": "FIX action.cpp part 0",
    },
    *[
        {
            "name": f"fix_game_action_object_{part}",
            "command": f"$python tools/fix_game_action_object.py $in $out --objcopy {objcopy_path} --part {part}",
            "description": f"FIX action.cpp part {part}",
        }
        for part in range(1, 5)
    ],
    {
        "name": "fix_sp_adv_stg_failed_object",
        "command": f"$python tools/fix_sp_adv_stg_failed_object.py $in $out --objcopy {objcopy_path}",
        "description": "FIX SpAdvStgFailed compiler-only atom",
    },
    {
        "name": "fix_set_damage_collision_object",
        "command": "$python tools/fix_set_damage_collision_object.py $in $out",
        "description": "FIX o_setDamegeCollision compiler-generated atoms",
    },
    {
        "name": "fix_game_movie_object",
        "command": f"$python tools/fix_game_movie_object.py $in $out --objcopy {objcopy_path}",
        "description": "FIX movie.cpp compiler-only atom",
    },
    {
        "name": "fix_e_appear_spboss_pos_object",
        "command": (
            f"$python tools/fix_e_appear_spboss_pos_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX e_appear_spboss_pos.cpp compiler atom order",
    },
    {
        "name": "fix_e_end_spboss_object",
        "command": f"$python tools/fix_e_end_spboss_object.py $in $out --objcopy {objcopy_path}",
        "description": "FIX e_end_spboss.cpp compiler atom order",
    },
    {
        "name": "fix_game_enemy_voice_object",
        "command": f"$python tools/fix_game_enemy_voice_object.py $in $out",
        "description": "FIX enemy_voice.cpp object layout",
    },
    {
        "name": "fix_s01_hata_object",
        "command": (
            f"$python tools/fix_s01_hata_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX o_s01_hata.cpp retail atom layout",
    },
    {
        "name": "fix_s01_taihostull_object",
        "command": (
            f"$python tools/fix_s01_taihostull_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX o_s01_taihostull.cpp compiler-only ABI data",
    },
    {
        "name": "fix_s01_hana_object",
        "command": (
            f"$python tools/fix_s01_hana_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX o_s01_hana.cpp compiler-only ABI data",
    },
    {
        "name": "fix_s01_iwamizu_object",
        "command": f"$python tools/fix_s01_iwamizu_object.py $in $out",
        "description": "FIX o_s01_iwamizu.cpp compiler-only ABI atoms",
    },
    {
        "name": "fix_s01_ciseki_object",
        "command": (
            f"$python tools/fix_s01_ciseki_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX o_s01_ciseki.cpp compiler-only ABI atoms",
    },
    {
        "name": "fix_e_capture_collision_object",
        "command": (
            f"$python tools/fix_e_capture_collision_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX e_capture_collision.cpp compiler-only atoms",
    },
    {
        "name": "fix_enemy_appear_chaos_emerald_object",
        "command": (
            f"$python tools/fix_enemy_appear_chaos_emerald_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX TEnemyAppearChaosEmerald rodata alignment",
    },
    {
        "name": "fix_enemy_appear_chaos_emerald_strings_object",
        "command": (
            f"$python tools/fix_enemy_appear_chaos_emerald_strings_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX TEnemyAppearChaosEmerald field-signature symbol",
    },
    {
        "name": "fix_o_invoke_colli_object",
        "command": f"$python tools/fix_o_invoke_colli_object.py $in $out",
        "description": "FIX o_invoke_colli.cpp compiler-only ABI atoms",
    },
    {
        "name": "fix_movie_play_sub_symbols",
        "command": (
            f"$python tools/fix_movie_play_sub_symbols.py $in $out "
            f"--objcopy {objcopy_path} --nm {nm_path} --objdump {objdump_path}"
        ),
        "description": "FIX moviePlaySub symbols",
    },
    {
        "name": "fix_s33_dice_symbols",
        "command": (
            f"$python tools/fix_s33_dice_symbols.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX o_s33_dice.cpp method and adjustor symbols",
    },
    {
        "name": "fix_s33_roulet_symbols",
        "command": (
            f"$python tools/fix_s33_roulet_symbols.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX o_s33_roulet.cpp method and adjustor symbols",
    },
    {
        "name": "fix_s33_chip_symbols",
        "command": (
            f"$python tools/fix_s33_chip_symbols.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX o_s33_chip.cpp adjustor symbol",
    },
    {
        "name": "fix_s33_slot_symbols",
        "command": (
            f"$python tools/fix_s33_slot_symbols.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX o_s33_slot.cpp adjustor symbol",
    },
    {
        "name": "fix_o_sample_symbols",
        "command": f"$python tools/fix_o_sample_symbols.py $in $out --objcopy {objcopy_path}",
        "description": "FIX o_sample.cpp shared virtual symbol",
    },
    {
        "name": "fix_s11_cloud_symbols",
        "command": (
            f"$python tools/fix_s11_cloud_symbols.py $in $out "
            f"--objcopy {objcopy_path} --ld {ld_path} "
            f"--script tools/s11_cloud_sections.ld"
        ),
        "description": "FIX o_s11_cloud symbols",
    },
    {
        "name": "fix_stage13_blinklight_object",
        "command": (
            f"$python tools/fix_stage13_blinklight_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX stage13 BlinkLight object metadata",
    },
    {
        "name": "fix_stage13_antenna_object",
        "command": (
            f"$python tools/fix_stage13_antenna_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX stage13 Antenna object metadata",
    },
    {
        "name": "fix_stage13_3way_colli_object",
        "command": (
            f"$python tools/fix_stage13_3way_colli_object.py $in $out "
            f"--objcopy {objcopy_path}"
        ),
        "description": "FIX stage13 3WAY collision compiler-only atoms",
    },
]
config.custom_build_steps = {
    "post-compile": [
        {
            "outputs": "build/G9SE8P/wide-format-core-object.stamp",
            "rule": "fix_wide_format_core_object",
            "inputs": "build/G9SE8P/src/game/wide_format_core.o",
            "implicit": ["tools/fix_wide_format_core_object.py"],
        },
        {
            "outputs": "build/G9SE8P/stage40D/ef-sparkle-object.stamp",
            "rule": "fix_ef_sparkle_object",
            "inputs": "build/G9SE8P/src/rel/ef_sparkle.o",
            "implicit": ["tools/fix_ef_sparkle_object.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/stage40D/ef-rain-object.stamp",
            "rule": "fix_ef_rain_object",
            "inputs": "build/G9SE8P/src/rel/ef_rain.o",
            "implicit": ["tools/fix_ef_rain_object.py"],
        },
        {
            "outputs": "build/G9SE8P/stage40D/ef-rain-strings-object.stamp",
            "rule": "fix_ef_rain_strings_object",
            "inputs": "build/G9SE8P/src/rel/ef_rain_strings.o",
            "implicit": ["tools/fix_ef_rain_strings_object.py"],
        },
        {
            "outputs": "build/G9SE8P/enemy-appear-spboss-object.stamp",
            "rule": "fix_enemy_appear_spboss_object",
            "inputs": "build/G9SE8P/src/rel/e_appear_spboss.o",
            "implicit": [
                "tools/fix_enemy_appear_spboss_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/end-sky-bob-object.stamp",
            "rule": "fix_end_sky_bob_object",
            "inputs": "build/G9SE8P/src/rel/TEndSkyBob.o",
            "implicit": [
                "tools/fix_end_sky_bob_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/movieD/sud-symbols.stamp",
            "rule": "fix_sud_symbols",
            "inputs": "build/G9SE8P/src/movieD/cri/sud.o",
            "implicit": ["tools/fix_sud_symbols.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/game-main-symbols.stamp",
            "rule": "fix_game_main_symbols",
            "inputs": "build/G9SE8P/src/game/main/main.o",
            "implicit": ["tools/fix_game_main_symbols.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/game-task-object.stamp",
            "rule": "fix_game_task_object",
            "inputs": "build/G9SE8P/src/game/Task.o",
            "implicit": ["tools/fix_game_task_object.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/tend-sp-stage-object.stamp",
            "rule": "fix_tend_sp_stage_object",
            "inputs": "build/G9SE8P/src/rel/TEndSPStage.o",
            "implicit": [
                "tools/fix_tend_sp_stage_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/game-memory-object.stamp",
            "rule": "fix_game_memory_object",
            "inputs": "build/G9SE8P/src/game/Memory.o",
            "implicit": ["tools/fix_game_memory_object.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/game-action-object.stamp",
            "rule": "fix_game_action_object",
            "inputs": "build/G9SE8P/src/game/action.o",
            "implicit": ["tools/fix_game_action_object.py", str(binutils_dir)],
        },
        *[
            {
                "outputs": f"build/G9SE8P/game-action-object-{part}.stamp",
                "rule": f"fix_game_action_object_{part}",
                "inputs": f"build/G9SE8P/src/game/action_cont{part}.o",
                "implicit": ["tools/fix_game_action_object.py", str(binutils_dir)],
            }
            for part in range(1, 5)
        ],
        {
            "outputs": "build/G9SE8P/game-sp-adv-stg-failed.stamp",
            "rule": "fix_sp_adv_stg_failed_object",
            "inputs": "build/G9SE8P/src/game/SpAdvStgFailed.o",
            "implicit": [
                "tools/fix_sp_adv_stg_failed_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/set-damage-collision-object.stamp",
            "rule": "fix_set_damage_collision_object",
            "inputs": "build/G9SE8P/src/rel/o_setDamegeCollision.o",
            "implicit": ["tools/fix_set_damage_collision_object.py"],
        },
        {
            "outputs": "build/G9SE8P/game-movie-object.stamp",
            "rule": "fix_game_movie_object",
            "inputs": "build/G9SE8P/src/game/movie.o",
            "implicit": [
                "tools/fix_game_movie_object.py",
                "tools/fix_sp_adv_stg_failed_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/game-enemy-voice-object.stamp",
            "rule": "fix_game_enemy_voice_object",
            "inputs": "build/G9SE8P/src/game/enemy_voice.o",
            "implicit": ["tools/fix_game_enemy_voice_object.py"],
        },
        {
            "outputs": "build/G9SE8P/stage01D-o-s01-hata-object.stamp",
            "rule": "fix_s01_hata_object",
            "inputs": "build/G9SE8P/src/rel/o_s01_hata.o",
            "implicit": [
                "tools/fix_s01_hata_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/stage01D-o-s01-taihostull-object.stamp",
            "rule": "fix_s01_taihostull_object",
            "inputs": "build/G9SE8P/src/rel/o_s01_taihostull.o",
            "implicit": [
                "tools/fix_s01_taihostull_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/stage01D-o-s01-hana-object.stamp",
            "rule": "fix_s01_hana_object",
            "inputs": "build/G9SE8P/src/rel/o_s01_hana.o",
            "implicit": [
                "tools/fix_s01_hana_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/stage01D-o-s01-iwamizu-object.stamp",
            "rule": "fix_s01_iwamizu_object",
            "inputs": "build/G9SE8P/src/rel/o_s01_iwamizu.o",
            "implicit": [
                "tools/fix_s01_iwamizu_object.py",
            ],
        },
        {
            "outputs": "build/G9SE8P/stage01D-o-s01-ciseki-object.stamp",
            "rule": "fix_s01_ciseki_object",
            "inputs": "build/G9SE8P/src/rel/o_s01_ciseki.o",
            "implicit": [
                "tools/fix_s01_ciseki_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/e-capture-collision-object.stamp",
            "rule": "fix_e_capture_collision_object",
            "inputs": "build/G9SE8P/src/rel/e_capture_collision.o",
            "implicit": [
                "tools/fix_e_capture_collision_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/stage40D/enemy-appear-chaos-emerald-object.stamp",
            "rule": "fix_enemy_appear_chaos_emerald_object",
            "inputs": "build/G9SE8P/src/rel/TEnemyAppearChaosEmerald.o",
            "implicit": [
                "tools/fix_enemy_appear_chaos_emerald_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/stage40D/e-end-spboss-object.stamp",
            "rule": "fix_e_end_spboss_object",
            "inputs": "build/G9SE8P/src/rel/e_end_spboss.o",
            "implicit": [
                "tools/fix_e_end_spboss_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/stage40D/enemy-appear-chaos-emerald-strings-object.stamp",
            "rule": "fix_enemy_appear_chaos_emerald_strings_object",
            "inputs": "build/G9SE8P/src/rel/TEnemyAppearChaosEmerald_strings.o",
            "implicit": [
                "tools/fix_enemy_appear_chaos_emerald_strings_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/stage40D/e-appear-spboss-pos-object.stamp",
            "rule": "fix_e_appear_spboss_pos_object",
            "inputs": "build/G9SE8P/src/rel/e_appear_spboss_pos.o",
            "implicit": [
                "tools/fix_e_appear_spboss_pos_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/o-invoke-colli-object.stamp",
            "rule": "fix_o_invoke_colli_object",
            "inputs": "build/G9SE8P/src/rel/o_invoke_colli.o",
            "implicit": ["tools/fix_o_invoke_colli_object.py"],
        },
        {
            "outputs": "build/G9SE8P/stage40D/shared-delete-symbols.stamp",
            "rule": "fix_stage40_delete_symbols",
            "inputs": [
                "build/G9SE8P/src/rel/o_system1.o",
                "build/G9SE8P/src/rel/o_system2.o",
                "build/G9SE8P/src/rel/o_system3.o",
                "build/G9SE8P/src/rel/o_system4.o",
                "build/G9SE8P/src/rel/o_sample2.o",
            ],
            "implicit": ["tools/fix_stage40_delete_symbols.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/main/movie-play-sub-symbols.stamp",
            "rule": "fix_movie_play_sub_symbols",
            "inputs": "build/G9SE8P/src/game/moviePlaySub.o",
            "implicit": ["tools/fix_movie_play_sub_symbols.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/stage33D/o-s33-dice-symbols.stamp",
            "rule": "fix_s33_dice_symbols",
            "inputs": "build/G9SE8P/src/rel/o_s33_dice.o",
            "implicit": ["tools/fix_s33_dice_symbols.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/stage33D/o-s33-roulet-symbols.stamp",
            "rule": "fix_s33_roulet_symbols",
            "inputs": "build/G9SE8P/src/rel/o_s33_roulet.o",
            "implicit": ["tools/fix_s33_roulet_symbols.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/stage33D/o-s33-chip-symbols.stamp",
            "rule": "fix_s33_chip_symbols",
            "inputs": "build/G9SE8P/src/rel/o_s33_chip.o",
            "implicit": ["tools/fix_s33_chip_symbols.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/stage33D/o-s33-slot-symbols.stamp",
            "rule": "fix_s33_slot_symbols",
            "inputs": "build/G9SE8P/src/rel/o_s33_slot.o",
            "implicit": ["tools/fix_s33_slot_symbols.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/stage40D/o-sample-symbols.stamp",
            "rule": "fix_o_sample_symbols",
            "inputs": "build/G9SE8P/src/rel/o_sample.o",
            "implicit": ["tools/fix_o_sample_symbols.py", str(binutils_dir)],
        },
        {
            "outputs": "build/G9SE8P/s11-cloud-symbols.stamp",
            "rule": "fix_s11_cloud_symbols",
            "inputs": "build/G9SE8P/src/rel/o_s11_cloud.o",
            "implicit": [
                "tools/fix_s11_cloud_symbols.py",
                "tools/s11_cloud_sections.ld",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/stage13-blinklight-object.stamp",
            "rule": "fix_stage13_blinklight_object",
            "inputs": "build/G9SE8P/src/stage13D/o_s13_blinklight.o",
            "implicit": [
                "tools/fix_stage13_blinklight_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/stage13-antenna-object.stamp",
            "rule": "fix_stage13_antenna_object",
            "inputs": "build/G9SE8P/src/stage13D/o_s13_antenna.o",
            "implicit": [
                "tools/fix_stage13_antenna_object.py",
                str(binutils_dir),
            ],
        },
        {
            "outputs": "build/G9SE8P/stage13-3way-colli-object.stamp",
            "rule": "fix_stage13_3way_colli_object",
            "inputs": "build/G9SE8P/src/stage13D/o_s14_3way_colli.o",
            "implicit": [
                "tools/fix_stage13_3way_colli_object.py",
                str(binutils_dir),
            ],
        },
    ],
}

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
