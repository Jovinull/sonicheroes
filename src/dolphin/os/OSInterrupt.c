#include "types.h"
#include "dolphin/os.h"
#include "dolphin/ppc.h"

// Interrupt dispatch. WORK IN PROGRESS: five functions are written, seven are
// still assembly in the build.
//
// The translation unit runs from 0x801D3278 to 0x801D3B3C. Before it is
// __OSUnhandledException, after it are three tiny stubs that belong to whatever
// comes next.
//
// The first four here are assembly in the original source too, and not as a
// shortcut: there is no C for reading or writing the machine state register, so
// enabling and disabling interrupts has to be written this way. The Dolphin SDK
// does the same.
//
// Functions are in the order the original emits them.

// A pointer to the table, not the table itself: the symbol is one word in
// .sbss and every access loads it and then indexes through it.
static __OSInterruptHandler* InterruptHandlerTable;

// fn_801D3278 belongs here, still unwritten.

// Turns external interrupts off and reports whether they had been on. The
// caller is expected to hand that answer back to OSRestoreInterrupts rather
// than assume it can just enable them again.
ASM BOOL OSDisableInterrupts(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mfmsr   r3
	rlwinm  r4, r3, 0, 17, 15
	mtmsr   r4
	extrwi  r3, r3, 1, 16
	blr
#endif // clang-format on
}

ASM BOOL OSEnableInterrupts(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mfmsr   r3
	ori     r4, r3, MSR_EE
	mtmsr   r4
	extrwi  r3, r3, 1, 16
	blr
#endif // clang-format on
}

// Puts the enable bit back the way the caller found it and reports what it was
// immediately before this call, so restores can nest.
ASM BOOL OSRestoreInterrupts(register BOOL level)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	cmpwi   r3, 0
	mfmsr   r4
	beq     disable
	ori     r5, r4, MSR_EE
	b       done
disable:
	rlwinm  r5, r4, 0, 17, 15
done:
	mtmsr   r5
	extrwi  r3, r4, 1, 16
	blr
#endif // clang-format on
}

__OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, __OSInterruptHandler handler)
{
	__OSInterruptHandler oldHandler;

	oldHandler                       = InterruptHandlerTable[interrupt];
	InterruptHandlerTable[interrupt] = handler;

	return oldHandler;
}

__OSInterruptHandler fn_801D3338(s16 interrupt)
{
	return InterruptHandlerTable[interrupt];
}

// __OSInterruptInit, fn_801D33C0, __OSMaskInterrupts, __OSUnmaskInterrupts,
// fn_801D37A8 and ExternalInterruptHandler belong here, still unwritten.
