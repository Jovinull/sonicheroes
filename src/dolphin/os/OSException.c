#include "types.h"

// WORK IN PROGRESS. Marked NonMatching in configure.py until the two remaining
// functions are written. Everything below is transcribed and believed correct,
// but the unit does not link yet.
//
// Still to do:
//   OSExceptionInit    0x801D0DA4  0x280 bytes
//   OSExceptionVector  0x801D107C  0x9C bytes, asm with the global labels
//                      __OSEVStart, __DBVECTOR, __OSEVSetNumber, __OSEVEnd
//
// Note dtk named the first one OSExceptionInit_801D0DA4, so symbols.txt will
// need renaming to plain OSExceptionInit once it is written.

#define SPR_GQR1 913
#define SPR_GQR2 914
#define SPR_GQR3 915
#define SPR_GQR4 916
#define SPR_GQR5 917
#define SPR_GQR6 918
#define SPR_GQR7 919

typedef void (*__OSExceptionHandler)(u8 exception, void* context);

extern void __OSUnhandledException(void);

static __OSExceptionHandler* OSExceptionTable;

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
