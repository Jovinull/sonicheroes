#ifndef DOLPHIN_OS_H
#define DOLPHIN_OS_H

#include "types.h"

// Shared OS types and the prototypes that more than one translation unit needs.
//
// This header exists because the same declarations were being repeated per file
// and had already drifted apart: OSContext had three different shapes in three
// files, and OSDumpContext was declared with two different parameter types.
// Anything genuinely private to one file still belongs in that file.

typedef s64 OSTime;

typedef void (*__OSExceptionHandler)(u8 exception, void* context);
typedef void (*__OSInterruptHandler)(s16 interrupt, void* context);

// The saved machine state, 0x2C8 bytes.
//
// The tail past srr1 is not a guess. EXTIntrruptHandler takes a 0x2E8 byte
// frame to hold one of these plus its own spill, and TRKLoadContext reads the
// half word at 0x1A2, which is where state lands only if mode sits at 0x1A0.
// The 32 paired single halves then run to exactly 0x2C8.
typedef struct OSContext {
	u32 gpr[32];   // 0x000
	u32 cr;        // 0x080
	u32 lr;        // 0x084
	u32 ctr;       // 0x088
	u32 xer;       // 0x08C
	f64 fpr[32];   // 0x090
	u32 fpscr_pad; // 0x190
	u32 fpscr;     // 0x194
	u32 srr0;      // 0x198
	u32 srr1;      // 0x19C
	u16 mode;      // 0x1A0
	u16 state;     // 0x1A2
	u32 gqr[8];    // 0x1A4
	u32 psf_pad;   // 0x1C4
	f64 psf[32];   // 0x1C8
} OSContext;       // 0x2C8

// Interrupts. The disable and restore pair nests: hand the result of a disable
// back to restore rather than assuming interrupts can simply be enabled again.
BOOL OSDisableInterrupts(void);
BOOL OSEnableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);

u32 __OSMaskInterrupts(u32 mask);
u32 __OSUnmaskInterrupts(u32 mask);

__OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, __OSInterruptHandler handler);
__OSExceptionHandler __OSGetExceptionHandler(u8 exception);
__OSExceptionHandler __OSSetExceptionHandler(u8 exception, __OSExceptionHandler handler);

// Context handling.
void OSClearContext(OSContext* context);
void OSSetCurrentContext(OSContext* context);
void OSDumpContext(OSContext* context);

// Reporting, and the debugger's variant of it.
void OSReport(const char* msg, ...);

// Defined as assembly in OSTime.c; the timebase read has no C spelling.
OSTime OSGetTime(void);
void DBPrintf(const char* msg, ...);

// Cache maintenance, called from more than one unit.
void DCInvalidateRange(void* addr, u32 nBytes);
void DCFlushRangeNoSync(void* addr, u32 nBytes);
void ICInvalidateRange(void* addr, u32 nBytes);

void __OSCacheInit(void);

#endif
