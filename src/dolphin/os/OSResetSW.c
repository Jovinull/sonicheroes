#include "types.h"

#define NULL  0
#define FALSE 0
#define TRUE  1

typedef int BOOL;
typedef s64 OSTime;
typedef struct OSContext OSContext;
typedef void (*OSResetCallback)(void);

#define OSPhysicalToCached(paddr)   ((void*)((u32)(paddr) + 0x80000000))
#define OS_BUS_CLOCK                __OSBusClock
#define OS_TIMER_CLOCK              (OS_BUS_CLOCK / 4)
#define OSMicrosecondsToTicks(usec) ((usec) * (OS_TIMER_CLOCK / 125000) / 8)
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSSecondsToTicks(sec)       ((OSTime)(sec) * OS_TIMER_CLOCK)
#define OSTicksToSeconds(ticks)     ((ticks) / OS_TIMER_CLOCK)

#ifdef __MWERKS__
volatile u32 __PIRegs[] : 0xCC003000;
u32 __OSBusClock : 0x800000F8;
u8 GameChoice : 0x800030E3;
#else
extern volatile u32 __PIRegs[];
extern u32 __OSBusClock;
extern u8 GameChoice;
#endif

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 __OSMaskInterrupts(u32 mask);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern OSTime __OSGetSystemTime(void);
extern OSTime __OSStartTime;

static OSResetCallback ResetCallback;
static BOOL Down;
static BOOL LastState;
static OSTime HoldUp;
static OSTime HoldDown;

void __OSResetSWInterruptHandler(s16 interrupt, OSContext* context)
{
	u32 debounce;
	OSResetCallback callback;

	HoldDown = __OSGetSystemTime();
	debounce = OSMicrosecondsToTicks(100);
	for (;;) {
		if (__OSGetSystemTime() - HoldDown >= debounce) {
			break;
		}
		if (__PIRegs[0] & 0x00010000) {
			break;
		}
	}
	if (!(__PIRegs[0] & 0x00010000)) {
		LastState = Down = TRUE;
		__OSMaskInterrupts(0x200);
		if (ResetCallback) {
			callback      = ResetCallback;
			ResetCallback = NULL;
			callback();
		}
	}
	__PIRegs[0] = 2;
}

OSResetCallback OSSetResetCallback(OSResetCallback callback)
{
	BOOL enabled;
	OSResetCallback prevCallback;

	enabled       = OSDisableInterrupts();
	prevCallback  = ResetCallback;
	ResetCallback = callback;
	if (callback) {
		__PIRegs[0] = 2;
		__OSUnmaskInterrupts(0x200);
	} else {
		__OSMaskInterrupts(0x200);
	}
	OSRestoreInterrupts(enabled);
	return prevCallback;
}

BOOL OSGetResetButtonState(void)
{
	BOOL enabled = OSDisableInterrupts();
	int state;
	u32 reg;
	OSTime now;

	now = __OSGetSystemTime();
	reg = __PIRegs[0];
	if (!(reg & 0x00010000)) {
		if (!Down) {
			Down     = TRUE;
			state    = HoldUp ? TRUE : FALSE;
			HoldDown = now;
		} else {
			state = HoldUp || (OSMicrosecondsToTicks(100) < now - HoldDown) ? TRUE : FALSE;
		}
	} else if (Down) {
		Down  = FALSE;
		state = LastState;
		if (state) {
			HoldUp = now;
		} else {
			HoldUp = 0;
		}
	} else if (HoldUp && (now - HoldUp < OSMillisecondsToTicks(40))) {
		state = TRUE;
	} else {
		state  = FALSE;
		HoldUp = 0;
	}

	LastState = state;

	if (GameChoice & 0x1F) {
		OSTime fire = (GameChoice & 0x1F) * 60;
		fire        = __OSStartTime + OSSecondsToTicks(fire);
		if (fire < now) {
			now -= fire;
			now = OSTicksToSeconds(now) / 2;
			if ((now & 1) == 0) {
				state = TRUE;
			} else {
				state = FALSE;
			}
		}
	}

	OSRestoreInterrupts(enabled);
	return state;
}

BOOL OSGetResetSwitchState(void)
{
	return OSGetResetButtonState();
}
