#include "types.h"

// WORK IN PROGRESS, NonMatching in configure.py. Four of eleven functions are
// written; the rest are still assembly in the build.
//
// This was first split as OSException.c covering 0x801D0DA4..0x801D1170. That
// was wrong. The string pool at 0x80291EA8 holds both the OSInit banner
// ("<< Dolphin SDK - OS release build ... >>", "Console Type", "Arena : 0x%x")
// and the exception strings ("Installing OSDBIntegrator", "Exceptions
// initialized"), in one pooled object. A shared pool means one translation
// unit, and the Dolphin SDK does keep OSInit and __OSExceptionInit together in
// OS.c. The split now covers 0x801D0840..0x801D1170.
//
// State: 6 of 11 functions match, 3 more written and close.
//
// Written, logic believed correct, differing only in register allocation:
//   ClearArena         81%  structure matches, the original uses mr where we
//                           emit addi and assigns r3/r0 where we assign r0/r3.
//                           Tried: named locals for size and for the two saved
//                           region reads, reordered declarations, s32 vs u32,
//                           pointer difference instead of integer casts. None
//                           moved it off 81%.
//   OSGetConsoleType   84%  return shape, original converges to one trailing blr
//   InquiryCallback    96%
//
// Not started:
//   OSInit             0x801D09CC  0x3D8  uses pool offsets 0x0 to 0x11F
//   OSExceptionInit    0x801D0DA4  0x280  dtk calls it OSExceptionInit_801D0DA4,
//                                         rename in symbols.txt when written
//
// Pool offsets used by the exception half: 0x160, 0x17C, 0x1AC, 0x1DC.

#define SPR_GQR1 913
#define SPR_GQR2 914
#define SPR_GQR3 915
#define SPR_GQR4 916
#define SPR_GQR5 917
#define SPR_GQR6 918
#define SPR_GQR7 919

typedef void (*__OSExceptionHandler)(u8 exception, void* context);

extern void __OSUnhandledException(void);
extern u32 OSGetResetCode(void);
extern void* OSGetArenaHi(void);
extern void* OSGetArenaLo(void);
extern void* memset(void* dst, int val, u32 n);

extern void* __OSSavedRegionStart;
extern void* __OSSavedRegionEnd;

// The previous run leaves the region it wants preserved recorded just under the
// top of MEM1.
#define OS_SAVED_REGION_START (*(void**)0x812FDFF0)
#define OS_SAVED_REGION_END   (*(void**)0x812FDFEC)

#define OS_RESET_RESTART 0x80000000

// These four live in .sbss between db.c and OSFpu.c. They cannot be declared
// here: giving OS.c both 0x8042CAE0..0x8042CAF0 and 0x8042CB00..0x8042CB08 puts
// OSFpu.c's ZeroF and ZeroPS in the middle and dtk reports a cyclic link order.
// So they belong to some other unit and are referenced from here.
typedef struct OSBootInfo {
	u8 pad[0x2C];
	u32 consoleType;
} OSBootInfo;

extern OSBootInfo* BootInfo;
extern void* BI2DebugFlag;

// Declared at its real size. A small struct here makes the compiler reach it
// through sda21, while the original uses an absolute lis/addi pair.
typedef struct DVDDriveInfo {
	u16 revisionLevel;
	u16 deviceCode;
	u32 releaseDate;
	u8 pad[24];
} DVDDriveInfo;

typedef struct DVDCommandBlock {
	u8 pad[0xC];
	s32 state;
} DVDCommandBlock;

extern DVDDriveInfo DriveInfo;

// Set by the drive inquiry, read by the boot path out of the OS globals.
#define OS_DEVICE_CODE (*(u16*)0x800030E6)

static int AreWeInitialized;
static __OSExceptionHandler* OSExceptionTable;

static void ClearArena(void)
{
	void* start;
	void* end;
	u32 size;

	if (OSGetResetCode() != OS_RESET_RESTART) {
		__OSSavedRegionStart = 0;
		__OSSavedRegionEnd   = 0;
		size                 = (u32)OSGetArenaHi() - (u32)OSGetArenaLo();
		memset(OSGetArenaLo(), 0, size);
		return;
	}

	start = OS_SAVED_REGION_START;
	end   = OS_SAVED_REGION_END;

	__OSSavedRegionStart = start;
	__OSSavedRegionEnd   = end;

	if (start == 0) {
		size = (u32)OSGetArenaHi() - (u32)OSGetArenaLo();
		memset(OSGetArenaLo(), 0, size);
		return;
	}

	if (OSGetArenaLo() < __OSSavedRegionStart) {
		if (OSGetArenaHi() <= __OSSavedRegionStart) {
			size = (u32)OSGetArenaHi() - (u32)OSGetArenaLo();
			memset(OSGetArenaLo(), 0, size);
			return;
		}

		size = (u32)__OSSavedRegionStart - (u32)OSGetArenaLo();
		memset(OSGetArenaLo(), 0, size);

		if (OSGetArenaHi() > __OSSavedRegionEnd) {
			size = (u32)OSGetArenaHi() - (u32)__OSSavedRegionEnd;
			memset(__OSSavedRegionEnd, 0, size);
		}
	}
}

u32 OSGetConsoleType(void)
{
	u32 type;

	if (BootInfo == 0 || (type = BootInfo->consoleType) == 0) {
		type = 0x10000002;
	}
	return type;
}

static void InquiryCallback(s32 result, DVDCommandBlock* block)
{
	switch (block->state) {
	case 0:
		OS_DEVICE_CODE = DriveInfo.deviceCode | 0x8000;
		break;
	default:
		OS_DEVICE_CODE = 1;
		break;
	}
}

// Copied over the exception vector area at boot, so it runs from a fixed
// address rather than from wherever the linker put it.
asm void __OSDBIntegrator(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
__OSDBINTSTART:
	li      r5,0x40
	mflr    r3
	stw     r3,0xC(r5)
	lwz     r3,8(r5)
	oris    r3,r3,0x8000
	mtlr    r3
	li      r3,0x30
	mtmsr   r3
	blr
__OSDBINTEND:
#endif // clang-format on
}

__OSExceptionHandler __OSSetExceptionHandler(u8 exception, __OSExceptionHandler handler)
{
	__OSExceptionHandler oldHandler;

	oldHandler                 = OSExceptionTable[exception];
	OSExceptionTable[exception] = handler;
	return oldHandler;
}

__OSExceptionHandler __OSGetExceptionHandler(u8 exception) { return OSExceptionTable[exception]; }

asm void OSDefaultExceptionHandler(register u8 exception, register void* context) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	stw     r0,0(r4)
	stw     r1,4(r4)
	stw     r2,8(r4)
	stmw    r6,0x18(r4)
	mfspr   r0,SPR_GQR1
	stw     r0,0x1A8(r4)
	mfspr   r0,SPR_GQR2
	stw     r0,0x1AC(r4)
	mfspr   r0,SPR_GQR3
	stw     r0,0x1B0(r4)
	mfspr   r0,SPR_GQR4
	stw     r0,0x1B4(r4)
	mfspr   r0,SPR_GQR5
	stw     r0,0x1B8(r4)
	mfspr   r0,SPR_GQR6
	stw     r0,0x1BC(r4)
	mfspr   r0,SPR_GQR7
	stw     r0,0x1C0(r4)
	mfdsisr r5
	mfdar   r6
	stwu    r1,-8(r1)
	b       __OSUnhandledException
#endif // clang-format on
}

// Reached by a branch from __OSDBIntegrator's end label.
asm void __OSDBJump(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	bla     0x60
__OSDBJUMPEND:
#endif // clang-format on
}

asm void OSExceptionVector(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
__OSEVStart:
	mtsprg  0,r4
	lwz     r4,0xC0(r0)
	stw     r3,0xC(r4)
	mfsprg  r3,0
	stw     r3,0x10(r4)
	stw     r5,0x14(r4)
	lhz     r3,0x1A2(r4)
	ori     r3,r3,2
	sth     r3,0x1A2(r4)
	mfcr    r3
	stw     r3,0x80(r4)
	mflr    r3
	stw     r3,0x84(r4)
	mfctr   r3
	stw     r3,0x88(r4)
	mfxer   r3
	stw     r3,0x8C(r4)
	mfsrr0  r3
	stw     r3,0x198(r4)
	mfsrr1  r3
	stw     r3,0x19C(r4)
	mr      r5,r3
__DBVECTOR:
	nop
	mfmsr   r3
	ori     r3,r3,0x30
	mtsrr1  r3
__OSEVSetNumber:
	li      r3,0
	lwz     r4,0xD4(r0)
	rlwinm. r5,r5,0,30,30
	bne     dbvector
	lis     r5,OSDefaultExceptionHandler@ha
	addi    r5,r5,OSDefaultExceptionHandler@l
	mtsrr0  r5
	rfi
dbvector:
	clrlslwi r5,r3,24,2
	lwz     r5,0x3000(r5)
	mtsrr0  r5
	rfi
__OSEVEnd:
	nop
#endif // clang-format on
}
