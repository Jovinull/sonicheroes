#include "types.h"
#include "dolphin/ppc.h"

// Alarms, driven by the decrementer exception. WORK IN PROGRESS: three
// functions are written, five are still assembly in the build.
//
// The translation unit runs from OSInitAlarm at 0x801D1204 to 0x801D18C0. The
// boundary is not a guess: OS.c owns .data up to 0x802920A0 and the next word
// there is this file's ResetFunctionInfo, while DSPInitCode at 0x802920B0
// starts another unit again. In .sbss this file owns AlarmQueue and nothing
// else, since the next word belongs to a unit that sits between here and
// OSArena.c.
//
// The end of the range came from the same evidence. ResetFunctionInfo at
// 0x802920A0 holds the address of the reset callback, and reading those sixteen
// bytes off the disc gave 0x801D18C0, which is the function immediately after
// the decrementer handler. So that function belongs here too and the unit runs
// one function further than the first guess.
//
// Functions are in the order the original emits them.

// The decrementer is exception 8.
#define __OS_EXCEPTION_DECREMENTER 8

typedef struct OSAlarm OSAlarm;

typedef void (*OSAlarmHandler)(OSAlarm* alarm, void* context);

struct OSAlarm {
	OSAlarmHandler handler; // 0x00
	u32            tag;     // 0x04
};

typedef struct OSAlarmQueue {
	OSAlarm* head; // 0x00
	OSAlarm* tail; // 0x04
} OSAlarmQueue;

typedef void (*__OSExceptionHandler)(u8 exception, void* context);

extern __OSExceptionHandler __OSGetExceptionHandler(u8 exception);
extern __OSExceptionHandler __OSSetExceptionHandler(u8 exception, __OSExceptionHandler handler);
extern void                 OSRegisterResetFunction(void* info);

// Written below, installed by OSInitAlarm above it.
static void DecrementerExceptionHandler(void);

// The reset callback and its registration record live in this file but are not
// written yet, so the record is reached as an external for now. It has to be
// declared with its real type: as a bare pointer it is small enough for the
// small data area and the address comes out through r13 instead of as a pair.
typedef struct OSResetFunctionInfo {
	void*                       func;     // 0x00
	u32                         priority; // 0x04
	struct OSResetFunctionInfo* next;     // 0x08
	struct OSResetFunctionInfo* prev;     // 0x0C
} OSResetFunctionInfo;                    // 0x10

// OnReset is this file's reset callback, at 0x801D18C0. It walks the queue and
// cancels what is still pending. It is not written yet, so it is reached as an
// external declaration; in the original it is static like everything else here.
extern void OnReset(void);

// Read from the disc rather than guessed: 801d18c0 ffffffff 00000000 00000000.
// The priority is the lowest there is, so alarms are torn down last.
static OSResetFunctionInfo ResetFunctionInfo = { (void*)OnReset, 0xFFFFFFFF, NULL, NULL };

// The queue is empty until OSInitAlarm clears it.
static OSAlarmQueue AlarmQueue;

// Installs the decrementer handler once. Calling it twice is harmless: the
// handler already being in place is what the test at the top is for.
void OSInitAlarm(void)
{
	if (__OSGetExceptionHandler(__OS_EXCEPTION_DECREMENTER)
	    != (__OSExceptionHandler)DecrementerExceptionHandler) {
		AlarmQueue.head = AlarmQueue.tail = NULL;
		__OSSetExceptionHandler(__OS_EXCEPTION_DECREMENTER,
		                        (__OSExceptionHandler)DecrementerExceptionHandler);
		OSRegisterResetFunction(&ResetFunctionInfo);
	}
}

void OSCreateAlarm(OSAlarm* alarm)
{
	alarm->handler = NULL;
	alarm->tag     = 0;
}

// InsertAlarm, OSSetAlarm, fn_801D1524 and DecrementerExceptionCallback belong
// here, still unwritten.

extern void DecrementerExceptionCallback(void);

// Saves the part of the register file the callback is allowed to disturb, then
// tail branches into it. There is no prologue and no return: the callback runs
// on the frame this leaves behind and unwinds the exception itself.
ASM static void DecrementerExceptionHandler(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	stw     r0, 0x0(r4)
	stw     r1, 0x4(r4)
	stw     r2, 0x8(r4)
	stmw    r6, 0x18(r4)
	mfspr   r0, SPR_GQR1
	stw     r0, 0x1a8(r4)
	mfspr   r0, SPR_GQR2
	stw     r0, 0x1ac(r4)
	mfspr   r0, SPR_GQR3
	stw     r0, 0x1b0(r4)
	mfspr   r0, SPR_GQR4
	stw     r0, 0x1b4(r4)
	mfspr   r0, SPR_GQR5
	stw     r0, 0x1b8(r4)
	mfspr   r0, SPR_GQR6
	stw     r0, 0x1bc(r4)
	mfspr   r0, SPR_GQR7
	stw     r0, 0x1c0(r4)
	stwu    r1, -0x8(r1)
	b       DecrementerExceptionCallback
#endif // clang-format on
}
