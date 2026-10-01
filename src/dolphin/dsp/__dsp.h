#ifndef DOLPHIN_DSP_INTERNAL_H
#define DOLPHIN_DSP_INTERNAL_H

#include <dolphin/dsp.h>

// Driver-private state and helpers shared by dsp.c, dsp_debug.c and
// dsp_task.c (after doldecomp/dolsdk2004 src/dsp/__dsp.h).

#ifdef __MWERKS__
volatile u16 __DSPRegs[] : 0xCC005000;
#else
extern volatile u16 __DSPRegs[];
#endif

#define OS_INTERRUPTMASK_DSP_DSP 0x01000000

extern void OSRegisterVersion(const char* version);

extern DSPTaskInfo* __DSP_first_task;
extern DSPTaskInfo* __DSP_last_task;
extern DSPTaskInfo* __DSP_curr_task;
extern DSPTaskInfo* __DSP_tmp_task;
extern DSPTaskInfo* __DSP_rude_task;
extern int __DSP_rude_task_pending;

void __DSPHandler(s16 interrupt, OSContext* context);
void __DSP_exec_task(DSPTaskInfo* curr, DSPTaskInfo* next);
void __DSP_boot_task(DSPTaskInfo* task);
void __DSP_insert_task(DSPTaskInfo* task);
void __DSP_add_task(DSPTaskInfo* task);
void __DSP_remove_task(DSPTaskInfo* task);
void __DSP_debug_printf(const char* fmt, ...);
DSPTaskInfo* __DSPGetCurrentTask(void);

#endif
