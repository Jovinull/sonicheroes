#include "types.h"

// System reset. The translation unit runs from OSRegisterResetFunction at
// 0x801D4BD8 to the end of OSGetResetCode at 0x801D4FFC, with the reset
// function queue and the boot-DOL flag as its .sbss. Before it is OSReboot,
// after it is OSResetSW.
//
// __OSDoHotReset performs the same three steps OSResetSystem uses inline for a
// hot reset, callable on its own. The SDK's KillThreads
// appears twice inside OSResetSystem; writing it as a separate static matches
// every instruction but lands its scratch register one off, so the walks are
// written out in place, which is byte exact.
//
// Reset is kept as assembly. The original is a chain of straight-line blocks
// threaded together by forward branches that fall back to the top, and no C
// arrangement tried reproduces that thread; the body is the SDK's usual HID0
// flash-invalidate, a timebase spin, and the PI reset strobe.

#define NULL  0
#define FALSE 0
#define TRUE  1

typedef int BOOL;

// Physical address zero is mirrored at 0x80000000 through the cache.
#define OSPhysicalToCached(paddr) ((void*)((u32)(paddr) + 0x80000000))

#ifdef __MWERKS__
volatile u16 __VIRegs[] : 0xCC002000;
volatile u32 __PIRegs[] : 0xCC003000;
#else
extern volatile u16 __VIRegs[];
extern volatile u32 __PIRegs[];
#endif

typedef struct OSResetFunctionInfo {
	BOOL (*func)(BOOL final);         // 0x00
	u32 priority;                     // 0x04
	struct OSResetFunctionInfo* next; // 0x08
	struct OSResetFunctionInfo* prev; // 0x0C
} OSResetFunctionInfo;

typedef struct OSResetFunctionQueue {
	OSResetFunctionInfo* head; // 0x00
	OSResetFunctionInfo* tail; // 0x04
} OSResetFunctionQueue;

// Only the two fields the thread killer touches are named; the rest of the
// thread block is padding until something proves what it holds.
typedef struct OSThread {
	u8 unk_0x00[0x2C8];    // 0x000
	u16 state;             // 0x2C8
	u8 unk_0x2CA[0x32];    // 0x2CA
	struct OSThread* next; // 0x2FC
} OSThread;

typedef struct OSThreadQueue {
	OSThread* head; // 0x00
	OSThread* tail; // 0x04
} OSThreadQueue;

#define OS_THREAD_STATE_READY     1
#define OS_THREAD_STATE_SUSPENDED 4

extern BOOL OSDisableInterrupts(void);
extern void OSDisableScheduler(void);
extern void OSEnableScheduler(void);
extern void OSCancelThread(OSThread* thread);
extern void __OSStopAudioSystem(void);
extern BOOL __PADDisableRecalibration(BOOL disable);
extern u8* __OSLockSram(void);
extern BOOL __OSUnlockSram(BOOL commit);
extern BOOL __OSSyncSram(void);
extern void ICFlashInvalidate(void);
extern void LCDisable(void);
extern void __OSReboot(u32 resetCode, BOOL forceMenu);
extern void* memset(void* dst, int val, u32 n);

static void Reset(register s32 code);

// The reset functions, kept sorted by priority, and the flag OSResetSystem
// uses to hand a DOL to the reboot path. Both file local, in the unit's .sbss.
static OSResetFunctionQueue ResetFunctionQueue;
static u32 bootThisDol;

void OSRegisterResetFunction(OSResetFunctionInfo* func)
{
	OSResetFunctionInfo* tmp;
	OSResetFunctionInfo* iter;

	for (iter = ResetFunctionQueue.head; iter && iter->priority <= func->priority;
	    iter  = iter->next) {
	}

	if (iter == NULL) {
		tmp = ResetFunctionQueue.tail;
		if (tmp == NULL) {
			ResetFunctionQueue.head = func;
		} else {
			tmp->next = func;
		}
		func->prev              = tmp;
		func->next              = NULL;
		ResetFunctionQueue.tail = func;
		return;
	}

	func->next = iter;
	tmp        = iter->prev;
	iter->prev = func;
	func->prev = tmp;
	if (tmp == NULL) {
		ResetFunctionQueue.head = func;
		return;
	}
	tmp->next = func;
}

// Invalidates the caches through HID0, waits out the pipeline on the
// timebase, then strobes the PI reset register with the requested code.
static ASM void Reset(register s32 code)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	b       chain1
block1:
	mfspr   r8, 1008
	ori     r8, r8, 0x8
	mtspr   1008, r8
	isync
	sync
	nop
	b       block2
chain1:
	b       chain2
block2:
	mftb    r5, 268
wait:
	mftb    r6, 268
	subf    r7, r5, r6
	cmplwi  r7, 0x1124
	blt     wait
	nop
	b       block3
chain2:
	b       chain3
block3:
	lis     r8, 0xCC00
	ori     r8, r8, 0x3000
	li      r4, 0x3
	stw     r4, 0x24(r8)
	stw     r3, 0x24(r8)
	nop
	b       hang
chain3:
	b       entry
hang:
	nop
	b       hang
entry:
	b       block1
#endif // clang-format on
}

// __OSDoHotReset in the SDK: blanks the display, drops the instruction cache
// and strobes the reset with the code shifted into the hardware's field.
void __OSDoHotReset(s32 code)
{
	OSDisableInterrupts();
	__VIRegs[1] = 0;
	ICFlashInvalidate();
	Reset(code * 8);
}

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu)
{
	BOOL rc;
	OSResetFunctionInfo* iter;
	BOOL err;
	u8* sram;
	BOOL done;
	OSThread* thread;
	OSThread* next;
	// Dead locals: the original frame is 0x10 bytes larger than the live
	// variables need.
	u32 pad[4];

	OSDisableScheduler();
	__OSStopAudioSystem();

	if (reset == 2 || (reset == 0 && bootThisDol != 0)) {
		rc = __PADDisableRecalibration(TRUE);
	}

	do {
		iter = ResetFunctionQueue.head;
		err  = FALSE;
		while (iter != NULL && !err) {
			err |= !iter->func(FALSE);
			iter = iter->next;
		}
		err |= !__OSSyncSram();
		done = err ? FALSE : TRUE;
	} while (!done);

	if (reset == 1 && forceMenu) {
		sram = __OSLockSram();
		sram[0x13] |= 0x40;
		__OSUnlockSram(TRUE);
		while (!__OSSyncSram()) {
		}
	}

	OSDisableInterrupts();

	iter = ResetFunctionQueue.head;
	err  = FALSE;
	while (iter != NULL && !err) {
		err |= !iter->func(TRUE);
		iter = iter->next;
	}
	__OSSyncSram();

	LCDisable();

	if (reset == 1) {
		OSDisableInterrupts();
		__VIRegs[1] = 0;
		ICFlashInvalidate();
		Reset(resetCode * 8);
	} else if (reset == 0) {
		if ((*(u32*)OSPhysicalToCached(0x30EC) = bootThisDol) != 0) {
			__PADDisableRecalibration(rc);
		}
		for (thread = ((OSThreadQueue*)OSPhysicalToCached(0xDC))->head; thread; thread = next) {
			next = thread->next;
			switch (thread->state) {
				case OS_THREAD_STATE_READY:
				case OS_THREAD_STATE_SUSPENDED:
					OSCancelThread(thread);
					break;
			}
		}
		OSEnableScheduler();
		__OSReboot(resetCode, forceMenu);
	}

	for (thread = ((OSThreadQueue*)OSPhysicalToCached(0xDC))->head; thread; thread = next) {
		next = thread->next;
		switch (thread->state) {
			case OS_THREAD_STATE_READY:
			case OS_THREAD_STATE_SUSPENDED:
				OSCancelThread(thread);
				break;
		}
	}
	memset(OSPhysicalToCached(0x40), 0, 0x8C);
	memset(OSPhysicalToCached(0xD4), 0, 0x14);
	memset(OSPhysicalToCached(0xF4), 0, 0x4);
	memset(OSPhysicalToCached(0x3000), 0, 0xC0);
	memset(OSPhysicalToCached(0x30C8), 0, 0xC);
	memset(OSPhysicalToCached(0x30E2), 0, 0x1);
	__PADDisableRecalibration(rc);
}

u32 OSGetResetCode(void)
{
	if (*(u8*)OSPhysicalToCached(0x30E2) != 0) {
		return 0x80000000;
	}

	return (__PIRegs[9] & ~7) >> 3;
}
