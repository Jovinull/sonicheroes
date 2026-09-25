#ifndef DOLPHIN_DSP_H
#define DOLPHIN_DSP_H

#include <dolphin/os.h>

// The DSP driver interface, as declared by the Dolphin SDK (layout follows
// doldecomp/dolsdk2004 include/dolphin/dsp.h).

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*DSPCallback)(void* task);

typedef struct STRUCT_DSP_TASK DSPTaskInfo;

struct STRUCT_DSP_TASK {
	volatile u32 state;    // 0x00
	volatile u32 priority; // 0x04
	volatile u32 flags;    // 0x08
	u16* iram_mmem_addr;   // 0x0C
	u32 iram_length;       // 0x10
	u32 iram_addr;         // 0x14
	u16* dram_mmem_addr;   // 0x18
	u32 dram_length;       // 0x1C
	u32 dram_addr;         // 0x20
	u16 dsp_init_vector;   // 0x24
	u16 dsp_resume_vector; // 0x26
	DSPCallback init_cb;   // 0x28
	DSPCallback res_cb;    // 0x2C
	DSPCallback done_cb;   // 0x30
	DSPCallback req_cb;    // 0x34
	DSPTaskInfo* next;     // 0x38
	DSPTaskInfo* prev;     // 0x3C
	OSTime t_context;      // 0x40
	OSTime t_task;         // 0x48
}; // 0x50

u32 DSPCheckMailToDSP(void);
u32 DSPCheckMailFromDSP(void);
u32 DSPReadCPUToDSPMbox(void);
u32 DSPReadMailFromDSP(void);
void DSPSendMailToDSP(u32 mail);
void DSPAssertInt(void);
void DSPInit(void);
BOOL DSPCheckInit(void);
void DSPReset(void);
void DSPHalt(void);
void DSPUnhalt(void);
u32 DSPGetDMAStatus(void);
DSPTaskInfo* DSPAddTask(DSPTaskInfo* task);
DSPTaskInfo* DSPCancelTask(DSPTaskInfo* task);
DSPTaskInfo* DSPAssertTask(DSPTaskInfo* task);

#ifdef __cplusplus
}
#endif

#endif
