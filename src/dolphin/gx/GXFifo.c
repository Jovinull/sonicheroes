#include "types.h"
#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "__gx.h"

// GX write-gather-pipe / FIFO management, 0x801F1F60 to 0x801F275C. Transcribed
// from the Apr 2003 Dolphin SDK GXFifo.c (release build, no debugger, SDK
// revision < 2 -- the verify callbacks are inlined away and the rev>=2
// GXSaveFifo* helpers / breakpoint double-writes are absent). Only the FIFO
// entry points the game actually links survive dead-strip; the Save/Status/
// Redirect family is not referenced, so it is omitted here.

typedef s16 __OSInterrupt;

#define OS_BASE_CACHED            0x80000000
#define OSPhysicalToCached(paddr) ((void*)(OS_BASE_CACHED + (u32)(paddr)))

extern void PPCSync(void);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);
extern OSThread* OSGetCurrentThread(void);
extern void OSSuspendThread(OSThread* thread);
extern void OSResumeThread(OSThread* thread);
extern __OSInterruptHandler __OSSetInterruptHandler(
    __OSInterrupt interrupt, __OSInterruptHandler handler);
extern u32 __OSUnmaskInterrupts(u32 mask);

__GXFifoObj* CPUFifo = NULL;
__GXFifoObj* GPFifo  = NULL;
static OSThread* __GXCurrentThread;
static GXBool CPGPLinked;
static BOOL GXOverflowSuspendInProgress;
static GXBreakPtCallback BreakPointCB;
static u32 __GXOverflowCount;

void* __GXCurrentBP;

static void __GXFifoReadEnable(void);
static void __GXFifoReadDisable(void);
static void __GXFifoLink(u8 en);
static void __GXWriteFifoIntEnable(u8 hiWatermarkEn, u8 loWatermarkEn);
static void __GXWriteFifoIntReset(u8 hiWatermarkClr, u8 loWatermarkClr);

static void GXOverflowHandler(__OSInterrupt interrupt, OSContext* context)
{
	__GXOverflowCount++;
	__GXWriteFifoIntEnable(0, 1);
	__GXWriteFifoIntReset(1, 0);
	GXOverflowSuspendInProgress = TRUE;
	OSSuspendThread(__GXCurrentThread);
}

static void GXUnderflowHandler(s16 interrupt, OSContext* context)
{
	OSResumeThread(__GXCurrentThread);
	GXOverflowSuspendInProgress = FALSE;
	__GXWriteFifoIntReset(1, 1);
	__GXWriteFifoIntEnable(1, 0);
}

#define SOME_SET_REG_MACRO(reg, size, shift, val)                                                  \
	do {                                                                                           \
		(reg)                                                                                      \
		    = (u32)__rlwimi((u32)(reg), (val), (shift), (32 - (shift) - (size)), (31 - (shift)));  \
	} while (0);

static void GXBreakPointHandler(__OSInterrupt interrupt, OSContext* context)
{
	OSContext exceptionContext;

	SOME_SET_REG_MACRO(__GXData->cpEnable, 1, 5, 0);
	GX_SET_CP_REG(1, __GXData->cpEnable);
	if (BreakPointCB != NULL) {
		OSClearContext(&exceptionContext);
		OSSetCurrentContext(&exceptionContext);
		BreakPointCB();
		OSClearContext(&exceptionContext);
		OSSetCurrentContext(context);
	}
}

static void GXCPInterruptHandler(__OSInterrupt interrupt, OSContext* context)
{
	__GXData->cpStatus = GX_GET_CP_REG(0);
	if (GET_REG_FIELD(__GXData->cpEnable, 1, 3) && GET_REG_FIELD(__GXData->cpStatus, 1, 1)) {
		GXUnderflowHandler(interrupt, context);
	}
	if (GET_REG_FIELD(__GXData->cpEnable, 1, 2) && GET_REG_FIELD(__GXData->cpStatus, 1, 0)) {
		GXOverflowHandler(interrupt, context);
	}
	if (GET_REG_FIELD(__GXData->cpEnable, 1, 5) && GET_REG_FIELD(__GXData->cpStatus, 1, 4)) {
		GXBreakPointHandler(interrupt, context);
	}
}

void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size)
{
	__GXFifoObj* realFifo = (__GXFifoObj*)fifo;

	realFifo->base  = base;
	realFifo->top   = (u8*)base + size - 4;
	realFifo->size  = size;
	realFifo->count = 0;
	GXInitFifoLimits(fifo, size - 0x4000, (size >> 1) & ~0x1F);
	GXInitFifoPtrs(fifo, base, base);
}

void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr)
{
	__GXFifoObj* realFifo = (__GXFifoObj*)fifo;
	BOOL enabled;

	enabled         = OSDisableInterrupts();
	realFifo->rdPtr = readPtr;
	realFifo->wrPtr = writePtr;
	realFifo->count = (u8*)writePtr - (u8*)readPtr;
	if (realFifo->count < 0) {
		realFifo->count += realFifo->size;
	}
	OSRestoreInterrupts(enabled);
}

void GXInitFifoLimits(GXFifoObj* fifo, u32 hiWatermark, u32 loWatermark)
{
	__GXFifoObj* realFifo = (__GXFifoObj*)fifo;

	realFifo->hiWatermark = hiWatermark;
	realFifo->loWatermark = loWatermark;
}

void GXSetCPUFifo(GXFifoObj* fifo)
{
	__GXFifoObj* realFifo = (__GXFifoObj*)fifo;
	BOOL enabled          = OSDisableInterrupts();

	CPUFifo = realFifo;
	if (CPUFifo == GPFifo) {
		u32 reg = 0;

		GX_SET_PI_REG(3, (u32)realFifo->base & 0x3FFFFFFF);
		GX_SET_PI_REG(4, (u32)realFifo->top & 0x3FFFFFFF);

		SET_REG_FIELD(0, reg, 21, 5, (u32)realFifo->wrPtr >> 5);
		SET_REG_FIELD(0, reg, 1, 26, 0);
		GX_SET_PI_REG(5, reg);

		CPGPLinked = GX_TRUE;

		__GXWriteFifoIntReset(1, 1);
		__GXWriteFifoIntEnable(1, 0);
		__GXFifoLink(1);
	} else {
		u32 reg;

		if (CPGPLinked) {
			__GXFifoLink(0);
			CPGPLinked = GX_FALSE;
		}

		__GXWriteFifoIntEnable(0, 0);
		reg = 0;
		GX_SET_PI_REG(3, (u32)realFifo->base & 0x3FFFFFFF);
		GX_SET_PI_REG(4, (u32)realFifo->top & 0x3FFFFFFF);
		SET_REG_FIELD(0, reg, 21, 5, (u32)realFifo->wrPtr >> 5);
		SET_REG_FIELD(0, reg, 1, 26, 0);
		GX_SET_PI_REG(5, reg);
	}

	PPCSync();
	OSRestoreInterrupts(enabled);
}

void GXSetGPFifo(GXFifoObj* fifo)
{
	__GXFifoObj* realFifo = (__GXFifoObj*)fifo;
	BOOL enabled          = OSDisableInterrupts();

	__GXFifoReadDisable();
	__GXWriteFifoIntEnable(0, 0);
	GPFifo = realFifo;

	GX_SET_CP_REG(16, (u32)realFifo->base & 0xFFFF);
	GX_SET_CP_REG(18, (u32)realFifo->top & 0xFFFF);
	GX_SET_CP_REG(24, realFifo->count & 0xFFFF);
	GX_SET_CP_REG(26, (u32)realFifo->wrPtr & 0xFFFF);
	GX_SET_CP_REG(28, (u32)realFifo->rdPtr & 0xFFFF);
	GX_SET_CP_REG(20, (u32)realFifo->hiWatermark & 0xFFFF);
	GX_SET_CP_REG(22, (u32)realFifo->loWatermark & 0xFFFF);
	GX_SET_CP_REG(17, ((u32)realFifo->base & 0x3FFFFFFF) >> 16);
	GX_SET_CP_REG(19, ((u32)realFifo->top & 0x3FFFFFFF) >> 16);
	GX_SET_CP_REG(25, realFifo->count >> 16);
	GX_SET_CP_REG(27, ((u32)realFifo->wrPtr & 0x3FFFFFFF) >> 16);
	GX_SET_CP_REG(29, ((u32)realFifo->rdPtr & 0x3FFFFFFF) >> 16);
	GX_SET_CP_REG(21, (u32)realFifo->hiWatermark >> 16);
	GX_SET_CP_REG(23, (u32)realFifo->loWatermark >> 16);

	PPCSync();

	if (CPUFifo == GPFifo) {
		CPGPLinked = GX_TRUE;
		__GXWriteFifoIntEnable(1, 0);
		__GXFifoLink(1);
	} else {
		CPGPLinked = GX_FALSE;
		__GXWriteFifoIntEnable(0, 0);
		__GXFifoLink(0);
	}

	__GXWriteFifoIntReset(1, 1);
	__GXFifoReadEnable();
	OSRestoreInterrupts(enabled);
}

#define SOME_MACRO1(fifo)                                                                          \
	do {                                                                                           \
		u32 temp = GX_GET_CP_REG(29) << 16;                                                        \
		temp |= GX_GET_CP_REG(28);                                                                 \
		fifo->rdPtr = OSPhysicalToCached(temp);                                                    \
	} while (0)

#define SOME_MACRO2(fifo)                                                                          \
	do {                                                                                           \
		u32 temp = GX_GET_CP_REG(25) << 16;                                                        \
		temp |= GX_GET_CP_REG(24);                                                                 \
		fifo->count = temp;                                                                        \
	} while (0)

void GXGetFifoPtrs(GXFifoObj* fifo, void** readPtr, void** writePtr)
{
	__GXFifoObj* realFifo = (__GXFifoObj*)fifo;

	if (realFifo == CPUFifo) {
		realFifo->wrPtr = OSPhysicalToCached(GX_GET_PI_REG(5) & 0xFBFFFFFF);
	}

	if (realFifo == GPFifo) {
		SOME_MACRO1(realFifo);
		SOME_MACRO2(realFifo);
	} else {
		realFifo->count = (u8*)realFifo->wrPtr - (u8*)realFifo->rdPtr;
		if (realFifo->count < 0) {
			realFifo->count += realFifo->size;
		}
	}

	*readPtr  = realFifo->rdPtr;
	*writePtr = realFifo->wrPtr;
}

GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb)
{
	GXBreakPtCallback oldcb = BreakPointCB;
	BOOL enabled            = OSDisableInterrupts();

	BreakPointCB = cb;
	OSRestoreInterrupts(enabled);
	return oldcb;
}

void GXEnableBreakPt(void* break_pt)
{
	BOOL enabled = OSDisableInterrupts();

	__GXFifoReadDisable();
	GX_SET_CP_REG(30, (u32)break_pt);
	GX_SET_CP_REG(31, ((u32)break_pt >> 16) & 0x3FFF);
	SOME_SET_REG_MACRO(__GXData->cpEnable, 1, 1, 1);
	SOME_SET_REG_MACRO(__GXData->cpEnable, 1, 5, 1);
	GX_SET_CP_REG(1, __GXData->cpEnable);
	__GXCurrentBP = break_pt;
	__GXFifoReadEnable();
	OSRestoreInterrupts(enabled);
}

void GXDisableBreakPt(void)
{
	BOOL enabled = OSDisableInterrupts();

	SOME_SET_REG_MACRO(__GXData->cpEnable, 1, 1, 0);
	SOME_SET_REG_MACRO(__GXData->cpEnable, 1, 5, 0);
	GX_SET_CP_REG(1, __GXData->cpEnable);
	__GXCurrentBP = NULL;
	OSRestoreInterrupts(enabled);
}

void __GXFifoInit(void)
{
	__OSSetInterruptHandler(0x11, (__OSInterruptHandler)GXCPInterruptHandler);
	__OSUnmaskInterrupts(0x4000);
	__GXCurrentThread           = OSGetCurrentThread();
	GXOverflowSuspendInProgress = FALSE;
	CPUFifo                     = NULL;
	GPFifo                      = NULL;
}

static void __GXFifoReadEnable(void)
{
	SET_REG_FIELD(0, __GXData->cpEnable, 1, 0, 1);
	GX_SET_CP_REG(1, __GXData->cpEnable);
}

static void __GXFifoReadDisable(void)
{
	SET_REG_FIELD(0, __GXData->cpEnable, 1, 0, 0);
	GX_SET_CP_REG(1, __GXData->cpEnable);
}

static void __GXFifoLink(u8 en)
{
	SET_REG_FIELD(0, __GXData->cpEnable, 1, 4, (en != 0) ? 1 : 0);
	GX_SET_CP_REG(1, __GXData->cpEnable);
}

static void __GXWriteFifoIntEnable(u8 hiWatermarkEn, u8 loWatermarkEn)
{
	SET_REG_FIELD(0, __GXData->cpEnable, 1, 2, hiWatermarkEn);
	SET_REG_FIELD(0, __GXData->cpEnable, 1, 3, loWatermarkEn);
	GX_SET_CP_REG(1, __GXData->cpEnable);
}

static void __GXWriteFifoIntReset(u8 hiWatermarkClr, u8 loWatermarkClr)
{
	SET_REG_FIELD(0, __GXData->cpClr, 1, 0, hiWatermarkClr);
	SET_REG_FIELD(0, __GXData->cpClr, 1, 1, loWatermarkClr);
	GX_SET_CP_REG(2, __GXData->cpClr);
}

OSThread* GXSetCurrentGXThread(void)
{
	BOOL enabled;
	OSThread* prev;

	enabled           = OSDisableInterrupts();
	prev              = __GXCurrentThread;
	__GXCurrentThread = OSGetCurrentThread();
	OSRestoreInterrupts(enabled);
	return prev;
}

GXFifoObj* GXGetCPUFifo(void)
{
	return (GXFifoObj*)CPUFifo;
}

GXFifoObj* GXGetGPFifo(void)
{
	return (GXFifoObj*)GPFifo;
}
