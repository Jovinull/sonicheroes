#include "types.h"
#include "dolphin/os.h"
#include "dolphin/ppc.h"

// Alarms, driven by the decrementer exception.
//
// The translation unit runs from OSInitAlarm at 0x801D1204 to the end of
// OnReset at 0x801D1960, with the queue heads in .sbss and its reset
// registration in .data. The boundary is not a guess: OS.c owns .data up to
// 0x802920A0 and the next word there is this file's ResetFunctionInfo, while
// DSPInitCode at 0x802920B0 starts another unit again. ResetFunctionInfo
// holds the address of the reset callback, and reading those sixteen bytes
// off the disc gave 0x801D18C0, which is OnReset. The Dolphin SDK calls it
// OnReset and hands it a flag saying whether this is the final pass, which is
// how zeldaret/tww has it too.
//
// OnReset consults __DVDTestAlarm before it cancels an alarm, as in the
// corresponding Dolphin SDK source. SetTimer exists in the source but not in
// the binary: a small
// static defined before every caller, inlined at all five sites.
//
// Functions are in the order the original emits them.

// The decrementer is exception 8.
#define __OS_EXCEPTION_DECREMENTER 8

typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

struct OSAlarm {
	OSAlarmHandler handler; // 0x00
	u32 tag;                // 0x04
	OSTime fire;            // 0x08
	OSAlarm* prev;          // 0x10
	OSAlarm* next;          // 0x14
	OSTime period;          // 0x18
	OSTime start;           // 0x20
};

typedef struct OSAlarmQueue {
	OSAlarm* head; // 0x00
	OSAlarm* tail; // 0x04
} OSAlarmQueue;

typedef struct OSResetFunctionInfo {
	BOOL (*func)(BOOL final);         // 0x00
	u32 priority;                     // 0x04
	struct OSResetFunctionInfo* next; // 0x08
	struct OSResetFunctionInfo* prev; // 0x0C
} OSResetFunctionInfo;                // 0x10

typedef u8 __OSException;

extern void OSDisableScheduler(void);
extern void OSEnableScheduler(void);
extern void __OSReschedule(void);
extern void OSLoadContext(OSContext* context);
extern OSTime __OSGetSystemTime(void);
extern void PPCMtdec(u32 value);
extern void OSRegisterResetFunction(OSResetFunctionInfo* info);

extern BOOL __DVDTestAlarm(OSAlarm* alarm);

void OSCancelAlarm(OSAlarm* alarm);
static BOOL OnReset(BOOL final);
static void DecrementerExceptionCallback(__OSException exception, OSContext* context);
static void DecrementerExceptionHandler(
    register __OSException exception, register OSContext* context);

// The pending alarms, soonest first. File local, in the unit's .sbss.
static OSAlarmQueue AlarmQueue;

// Read from the disc rather than guessed: 801d18c0 ffffffff 00000000 00000000.
// The priority is the lowest there is, so alarms are torn down last.
static OSResetFunctionInfo ResetFunctionInfo = {
	OnReset,
	0xFFFFFFFF,
};

// Arms the decrementer for the alarm at the head of the queue. Inlined into
// every caller, so it has no body in the binary — which requires the
// `inline` keyword: MWCC emits an out-of-line body for a plain static even
// when every call site is inlined, and that body is 152 stray .text bytes.
static inline void SetTimer(OSAlarm* alarm)
{
	OSTime delta;

	delta = alarm->fire - __OSGetSystemTime();
	if (delta < 0) {
		PPCMtdec(0);
	} else if (delta < 0x80000000) {
		PPCMtdec((u32)delta);
	} else {
		PPCMtdec(0x7FFFFFFF);
	}
}

// Installs the decrementer handler once. Calling it twice is harmless: the
// handler already being in place is what the test at the top is for.
void OSInitAlarm(void)
{
	if (__OSGetExceptionHandler(__OS_EXCEPTION_DECREMENTER)
	    != (__OSExceptionHandler)DecrementerExceptionHandler) {
		AlarmQueue.head = AlarmQueue.tail = NULL;
		__OSSetExceptionHandler(
		    __OS_EXCEPTION_DECREMENTER, (__OSExceptionHandler)DecrementerExceptionHandler);
		OSRegisterResetFunction(&ResetFunctionInfo);
	}
}

void OSCreateAlarm(OSAlarm* alarm)
{
	alarm->handler = 0;
	alarm->tag     = 0;
}

static void InsertAlarm(OSAlarm* alarm, OSTime fire, OSAlarmHandler handler)
{
	OSAlarm* next;
	OSAlarm* prev;

	if (0 < alarm->period) {
		OSTime time = __OSGetSystemTime();

		fire = alarm->start;
		if (alarm->start < time) {
			fire += alarm->period * ((time - alarm->start) / alarm->period + 1);
		}
	}

	alarm->handler = handler;
	alarm->fire    = fire;

	for (next = AlarmQueue.head; next; next = next->next) {
		if (next->fire <= fire) {
			continue;
		}

		alarm->prev = next->prev;
		next->prev  = alarm;
		alarm->next = next;
		prev        = alarm->prev;
		if (prev) {
			prev->next = alarm;
		} else {
			AlarmQueue.head = alarm;
			SetTimer(alarm);
		}
		return;
	}

	alarm->next     = NULL;
	prev            = AlarmQueue.tail;
	AlarmQueue.tail = alarm;
	alarm->prev     = prev;
	if (prev) {
		prev->next = alarm;
	} else {
		AlarmQueue.head = AlarmQueue.tail = alarm;
		SetTimer(alarm);
	}
}

void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler)
{
	BOOL enabled;

	enabled = OSDisableInterrupts();

	alarm->period = 0;
	InsertAlarm(alarm, __OSGetSystemTime() + tick, handler);

	OSRestoreInterrupts(enabled);
}

// OSCancelAlarm in the SDK.
void OSCancelAlarm(OSAlarm* alarm)
{
	BOOL enabled;
	OSAlarm* next;

	enabled = OSDisableInterrupts();

	if (alarm->handler == 0) {
		OSRestoreInterrupts(enabled);
		return;
	}

	next = alarm->next;
	if (next == NULL) {
		AlarmQueue.tail = alarm->prev;
	} else {
		next->prev = alarm->prev;
	}
	if (alarm->prev) {
		alarm->prev->next = next;
	} else {
		AlarmQueue.head = next;
		if (next) {
			SetTimer(next);
		}
	}

	alarm->handler = 0;

	OSRestoreInterrupts(enabled);
}

static void DecrementerExceptionCallback(__OSException exception, OSContext* context)
{
	OSAlarm* alarm;
	OSAlarm* next;
	OSAlarmHandler handler;
	OSTime time;
	OSContext exceptionContext;

	time  = __OSGetSystemTime();
	alarm = AlarmQueue.head;
	if (alarm == NULL) {
		OSLoadContext(context);
	}

	if (time < alarm->fire) {
		SetTimer(alarm);
		OSLoadContext(context);
	}

	next            = alarm->next;
	AlarmQueue.head = next;
	if (next == NULL) {
		AlarmQueue.tail = NULL;
	} else {
		next->prev = NULL;
	}

	handler        = alarm->handler;
	alarm->handler = 0;

	if (0 < alarm->period) {
		InsertAlarm(alarm, 0, handler);
	}

	if (AlarmQueue.head) {
		SetTimer(AlarmQueue.head);
	}

	OSDisableScheduler();
	OSClearContext(&exceptionContext);
	OSSetCurrentContext(&exceptionContext);

	handler(alarm, context);

	OSClearContext(&exceptionContext);
	OSSetCurrentContext(context);

	OSEnableScheduler();
	__OSReschedule();
	OSLoadContext(context);
}

// Saves the caller-saved half of the register file into the context the
// exception glue picked, then falls through into the callback. Assembly in
// the original source too.
// clang-format off
static ASM void DecrementerExceptionHandler(register __OSException exception, register OSContext* context)
{
#ifdef __MWERKS__
	nofralloc
	stw     r0, 0x0(context)
	stw     r1, 0x4(context)
	stw     r2, 0x8(context)
	stmw    r6, 0x18(context)
	mfspr   r0, SPR_GQR1
	stw     r0, 0x1A8(context)
	mfspr   r0, SPR_GQR2
	stw     r0, 0x1AC(context)
	mfspr   r0, SPR_GQR3
	stw     r0, 0x1B0(context)
	mfspr   r0, SPR_GQR4
	stw     r0, 0x1B4(context)
	mfspr   r0, SPR_GQR5
	stw     r0, 0x1B8(context)
	mfspr   r0, SPR_GQR6
	stw     r0, 0x1BC(context)
	mfspr   r0, SPR_GQR7
	stw     r0, 0x1C0(context)
	stwu    r1, -0x8(r1)
	b       DecrementerExceptionCallback
#endif
} // clang-format on

// Cancels every alarm the DVD code does not claim on the final pass of a
// reset.
static BOOL OnReset(BOOL final)
{
	OSAlarm* alarm;
	OSAlarm* next;

	if (final != FALSE) {
		alarm = AlarmQueue.head;
		next  = alarm ? alarm->next : NULL;
		while (alarm != NULL) {
			if (!__DVDTestAlarm(alarm)) {
				OSCancelAlarm(alarm);
			}
			alarm = next;
			next  = alarm ? alarm->next : NULL;
		}
	}
	return TRUE;
}
