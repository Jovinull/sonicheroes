#include "types.h"
#include <dolphin/dsp.h>

#include "__dsp.h"

// DSP driver debug hooks, 0x801E9D44 to 0x801E9D94. The release build's
// printf is an empty variadic stub; __DSPGetCurrentTask was smart-stripped.
// Reference: doldecomp/dolsdk2004 src/dsp/dsp_debug.c (public reconstruction of the
// Dolphin SDK); this DOL carries the Apr 17 2003 release build of the DSP
// library ("<< Dolphin SDK - DSP ... Apr 17 2003 12:34:16 >>"). Compiled with
// GC/1.2.5n like the other SDK units. Functions the original linker
// smart-stripped are still defined, because their string literals survive in
// the unit's .data.

void __DSP_debug_printf(const char* fmt, ...) { }

DSPTaskInfo* __DSPGetCurrentTask(void)
{
	return __DSP_curr_task;
}
