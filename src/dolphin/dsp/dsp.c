#include "types.h"
#include <dolphin/dsp.h>

#include "__dsp.h"

// The DSP driver front end, 0x801E9AB4 to 0x801E9D44. Identified by the DSP
// version string and the "DSPInit(): Build Date" banner leading the unit's
// .data, and by the version pointer registered from DSPInit.
// Reference: doldecomp/dolsdk2004 src/dsp/dsp.c (public reconstruction of the
// Dolphin SDK); this DOL carries the Apr 17 2003 release build of the DSP
// library ("<< Dolphin SDK - DSP ... Apr 17 2003 12:34:16 >>"). Compiled with
// GC/1.2.5n like the other SDK units. Functions the original linker
// smart-stripped are still defined, because their string literals survive in
// the unit's .data.
//
// objdiff scores .data just under 100%: the bytes are identical, but the
// target's single dtk data symbol also covers the 0x80-byte section's
// alignment tail (0x7D bytes compiled, 0x80 in the DOL). The linked DOL matches.

#define BUILD_DATE "Apr 17 2003"
#define BUILD_TIME "12:34:16"

const char* __DSPVersion = "<< Dolphin SDK - DSP\trelease build: Apr 17 2003 12:34:16 (0x2301) >>";

static BOOL __DSP_init_flag;

u32 DSPCheckMailToDSP(void)
{
	return (__DSPRegs[0] & (1 << 15)) >> 15;
}

u32 DSPCheckMailFromDSP(void)
{
	return (__DSPRegs[2] & (1 << 15)) >> 15;
}

u32 DSPReadCPUToDSPMbox(void)
{
	return (__DSPRegs[0] << 16) | __DSPRegs[1];
}

u32 DSPReadMailFromDSP(void)
{
	return (__DSPRegs[2] << 16) | __DSPRegs[3];
}

void DSPSendMailToDSP(u32 mail)
{
	__DSPRegs[0] = mail >> 16;
	__DSPRegs[1] = mail & 0xFFFF;
}

void DSPAssertInt(void)
{
	BOOL old;
	u16 tmp;

	old          = OSDisableInterrupts();
	tmp          = __DSPRegs[5];
	tmp          = (tmp & ~0xA8) | 2;
	__DSPRegs[5] = tmp;
	OSRestoreInterrupts(old);
}

void DSPInit(void)
{
	BOOL old;
	u16 tmp;

	__DSP_debug_printf("DSPInit(): Build Date: %s %s\n", BUILD_DATE, BUILD_TIME);

	if (__DSP_init_flag == 1)
		return;

	OSRegisterVersion(__DSPVersion);

	old = OSDisableInterrupts();
	__OSSetInterruptHandler(7, (__OSInterruptHandler)__DSPHandler);
	__OSUnmaskInterrupts(OS_INTERRUPTMASK_DSP_DSP);

	tmp          = __DSPRegs[5];
	tmp          = (tmp & ~0xA8) | 0x800;
	__DSPRegs[5] = tmp;

	tmp          = __DSPRegs[5];
	__DSPRegs[5] = tmp = tmp & ~0xAC;

	__DSP_first_task = __DSP_last_task = __DSP_curr_task = __DSP_tmp_task = NULL;
	__DSP_init_flag                                                       = 1;

	OSRestoreInterrupts(old);
}

BOOL DSPCheckInit(void)
{
	return __DSP_init_flag;
}

void DSPReset(void)
{
	BOOL old;
	u16 tmp;

	old             = OSDisableInterrupts();
	tmp             = __DSPRegs[5];
	tmp             = (tmp & ~0xA8) | 0x800 | 1;
	__DSPRegs[5]    = tmp;
	__DSP_init_flag = 0;
	OSRestoreInterrupts(old);
}

void DSPHalt(void)
{
	BOOL old;
	u16 tmp;

	old          = OSDisableInterrupts();
	tmp          = __DSPRegs[5];
	tmp          = (tmp & ~0xA8) | 4;
	__DSPRegs[5] = tmp;
	OSRestoreInterrupts(old);
}

void DSPUnhalt(void)
{
	BOOL old;
	u16 tmp;

	old          = OSDisableInterrupts();
	tmp          = __DSPRegs[5];
	tmp          = (tmp & ~0xAC);
	__DSPRegs[5] = tmp;
	OSRestoreInterrupts(old);
}

u32 DSPGetDMAStatus(void)
{
	return (__DSPRegs[5] & (1 << 9));
}

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task)
{
	BOOL old;

	old = OSDisableInterrupts();

	__DSP_insert_task(task);
	task->state = 0;
	task->flags = 1;

	OSRestoreInterrupts(old);
	if (task == __DSP_first_task)
		__DSP_boot_task(task);
	return task;
}

DSPTaskInfo* DSPCancelTask(DSPTaskInfo* task)
{
	BOOL old;

	old = OSDisableInterrupts();

	task->flags |= 2;

	OSRestoreInterrupts(old);
	return task;
}

DSPTaskInfo* DSPAssertTask(DSPTaskInfo* task)
{
	s32 old;

	old = OSDisableInterrupts();

	if (__DSP_curr_task == task) {
		__DSP_rude_task         = task;
		__DSP_rude_task_pending = 1;
		OSRestoreInterrupts(old);
		return task;
	}

	if (task->priority < __DSP_curr_task->priority) {
		__DSP_rude_task         = task;
		__DSP_rude_task_pending = 1;
		if (__DSP_curr_task->state == 1) {
			DSPAssertInt();
		}
		OSRestoreInterrupts(old);
		return task;
	}

	OSRestoreInterrupts(old);
	return NULL;
}
