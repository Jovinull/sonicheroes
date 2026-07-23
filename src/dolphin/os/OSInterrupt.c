#include "types.h"
#include "dolphin/os.h"
#include "dolphin/ppc.h"

// Interrupt dispatch.
//
// The translation unit runs from 0x801D3278 to 0x801D3B3C. Before it is
// __OSUnhandledException, after it are three tiny stubs that belong to whatever
// comes next.
//
// OSDisableInterrupts, OSEnableInterrupts, OSRestoreInterrupts and
// ExternalInterruptHandler are assembly in the original source too, and not as
// a shortcut: there is no C for reading or writing the machine state register
// or for saving the register file on the way into an exception. The Dolphin
// SDK does the same.
//
// SetInterruptMask, __OSGetInterruptHandler and __OSDispatchInterrupt are the
// Dolphin SDK names for these functions; the structure matches the public SDK
// OSInterrupt.c exactly. The interrupt priority table differs from the stock
// SDK ordering, which is why its values are written out as hex.
//
// Functions are in the order the original emits them.

typedef u8 __OSException;
typedef s16 __OSInterrupt;
typedef u32 OSInterruptMask;

// Physical address zero is mirrored at 0x80000000 through the cache. Writing
// the OS globals this way keeps the compiler reusing one base register across
// a run of accesses, which is what the original does.
#define OSPhysicalToCached(paddr) ((void*)((u32)(paddr) + 0x80000000))

// The two interrupt mask words the OS keeps in low memory, and the handler
// table pointed at by InterruptHandlerTable.
#define OS_INTERRUPT_MASK_GLOBAL (*(OSInterruptMask*)OSPhysicalToCached(0x00C4))
#define OS_INTERRUPT_MASK_LOCAL  (*(OSInterruptMask*)OSPhysicalToCached(0x00C8))

// Hardware register blocks. These are the CodeWarrior absolute-address
// declarations the SDK itself uses: the compiler materialises the block base
// with lis/addi and folds the element offset into the access, which is the
// pattern the original emits. A cast-constant macro folds the whole address
// instead and does not match.
#ifdef __MWERKS__
volatile u16 __VIRegs[] : 0xCC002000;
volatile u32 __PIRegs[] : 0xCC003000;
volatile u16 __MEMRegs[] : 0xCC004000;
volatile u16 __DSPRegs[] : 0xCC005000;
volatile u32 __EXIRegs[] : 0xCC006800;
volatile u32 __AIRegs[] : 0xCC006C00;
#else
extern volatile u16 __VIRegs[];
extern volatile u32 __PIRegs[];
extern volatile u16 __MEMRegs[];
extern volatile u16 __DSPRegs[];
extern volatile u32 __EXIRegs[];
extern volatile u32 __AIRegs[];
#endif
#define VI_REGS  __VIRegs
#define PI_REGS  __PIRegs
#define MEM_REGS __MEMRegs
#define DSP_REGS __DSPRegs
#define EXI_REGS __EXIRegs
#define AI_REGS  __AIRegs

extern void OSLoadContext(OSContext* context);
extern OSTime OSGetTime(void);
extern void OSDisableScheduler(void);
extern void OSEnableScheduler(void);
extern void __OSReschedule(void);
extern void* memset(void* dst, int val, u32 n);

static u32 SetInterruptMask(OSInterruptMask mask, OSInterruptMask current);
static void ExternalInterruptHandler(register __OSException exception, register OSContext* context);

static u16 fontEncode[4] = { 0xFFFF };

// A pointer to the table, not the table itself: the symbol is one word in
// .sbss and every access loads it and then indexes through it.
static __OSInterruptHandler* InterruptHandlerTable;

volatile OSTime __OSLastInterruptTime;
volatile s16 __OSLastInterrupt;
volatile u32 __OSLastInterruptSrr0;

// Which hardware interrupts each dispatch pass considers, most urgent first,
// ending in a catch-all. The grouping differs from the stock SDK table, so the
// rows stay as hex.
static OSInterruptMask InterruptPrioTable[] = {
	0x00000100, // PI_ERROR
	0x00000040, // PI_DEBUG
	0xF8000000, // MEM
	0x00000200, // PI_RSW
	0x00000080, // PI_VI
	0x00003000, // PI_PE_TOKEN | PI_PE_FINISH
	0x00000020, // PI_HSP
	0x03FF8C00, // DSP_ARAM | DSP_DSP | AI | EXI | PI_SI | PI_DI
	0x04000000, // DSP_AI
	0x00004000, // PI_CP
	0xFFFFFFFF,
	0,
};

u16 OSGetFontEncode(void)
{
	if (fontEncode[0] <= 1) {
		return fontEncode[0];
	}

	switch (*(s32*)OSPhysicalToCached(0xCC)) {
		case 0:
			fontEncode[0] = (VI_REGS[0x37] & 0x2) ? 1 : 0;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		default:
			fontEncode[0] = 0;
			break;
	}

	return fontEncode[0];
}

// Turns external interrupts off and reports whether they had been on. The
// caller is expected to hand that answer back to OSRestoreInterrupts rather
// than assume it can just enable them again.
// clang-format off
ASM BOOL OSDisableInterrupts(void)
{
#ifdef __MWERKS__
	nofralloc
	mfmsr   r3
	rlwinm  r4, r3, 0, 17, 15
	mtmsr   r4
	extrwi  r3, r3, 1, 16
	blr
#endif
} // clang-format on

// clang-format off
ASM BOOL OSEnableInterrupts(void)
{
#ifdef __MWERKS__
	nofralloc
	mfmsr   r3
	ori     r4, r3, MSR_EE
	mtmsr   r4
	extrwi  r3, r3, 1, 16
	blr
#endif
} // clang-format on

// Puts the enable bit back the way the caller found it and reports what it was
// immediately before this call, so restores can nest.
// clang-format off
ASM BOOL OSRestoreInterrupts(register BOOL level)
{
#ifdef __MWERKS__
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
#endif
} // clang-format on

__OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, __OSInterruptHandler handler)
{
	__OSInterruptHandler oldHandler;

	oldHandler                       = InterruptHandlerTable[interrupt];
	InterruptHandlerTable[interrupt] = handler;

	return oldHandler;
}

__OSInterruptHandler __OSGetInterruptHandler(s16 interrupt)
{
	return InterruptHandlerTable[interrupt];
}

void __OSInterruptInit(void)
{
	InterruptHandlerTable = (__OSInterruptHandler*)OSPhysicalToCached(0x3040);
	memset(InterruptHandlerTable, 0, 0x20 * sizeof(__OSInterruptHandler));

	OS_INTERRUPT_MASK_GLOBAL = 0;
	OS_INTERRUPT_MASK_LOCAL  = 0;

	PI_REGS[1] = 0xF0;

	__OSMaskInterrupts(0xFFFFFFE0);

	__OSSetExceptionHandler(4, (__OSExceptionHandler)ExternalInterruptHandler);
}

// Writes the hardware mask registers for every interrupt named in mask,
// enabling each one whose bit is clear in current, and hands back the bits of
// mask it has not dealt with yet so the caller can loop.
static u32 SetInterruptMask(OSInterruptMask mask, OSInterruptMask current)
{
	u32 reg;

	switch (__cntlzw(mask)) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			reg = 0;
			if (!(current & 0x80000000)) {
				reg |= 0x1;
			}
			if (!(current & 0x40000000)) {
				reg |= 0x2;
			}
			if (!(current & 0x20000000)) {
				reg |= 0x4;
			}
			if (!(current & 0x10000000)) {
				reg |= 0x8;
			}
			if (!(current & 0x08000000)) {
				reg |= 0x10;
			}
			MEM_REGS[14] = (u16)reg;
			mask &= ~0xF8000000;
			break;
		case 5:
		case 6:
		case 7:
			reg = DSP_REGS[5];
			reg &= ~0x1F8;
			if (!(current & 0x04000000)) {
				reg |= 0x10;
			}
			if (!(current & 0x02000000)) {
				reg |= 0x40;
			}
			if (!(current & 0x01000000)) {
				reg |= 0x100;
			}
			DSP_REGS[5] = (u16)reg;
			mask &= ~0x07000000;
			break;
		case 8:
			reg = AI_REGS[0];
			reg &= ~0x2C;
			if (!(current & 0x00800000)) {
				reg |= 0x4;
			}
			AI_REGS[0] = reg;
			mask &= ~0x00800000;
			break;
		case 9:
		case 10:
		case 11:
			reg = EXI_REGS[0];
			reg &= ~0x2C0F;
			if (!(current & 0x00400000)) {
				reg |= 0x1;
			}
			if (!(current & 0x00200000)) {
				reg |= 0x4;
			}
			if (!(current & 0x00100000)) {
				reg |= 0x400;
			}
			EXI_REGS[0] = reg;
			mask &= ~0x00700000;
			break;
		case 12:
		case 13:
		case 14:
			reg = EXI_REGS[5];
			reg &= ~0xC0F;
			if (!(current & 0x00080000)) {
				reg |= 0x1;
			}
			if (!(current & 0x00040000)) {
				reg |= 0x4;
			}
			if (!(current & 0x00020000)) {
				reg |= 0x400;
			}
			EXI_REGS[5] = reg;
			mask &= ~0x000E0000;
			break;
		case 15:
		case 16:
			reg = EXI_REGS[10];
			reg &= ~0xF;
			if (!(current & 0x00010000)) {
				reg |= 0x1;
			}
			if (!(current & 0x00008000)) {
				reg |= 0x4;
			}
			EXI_REGS[10] = reg;
			mask &= ~0x00018000;
			break;
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
			reg = 0xF0;
			if (!(current & 0x00004000)) {
				reg |= 0x800;
			}
			if (!(current & 0x00000800)) {
				reg |= 0x8;
			}
			if (!(current & 0x00000400)) {
				reg |= 0x4;
			}
			if (!(current & 0x00000200)) {
				reg |= 0x2;
			}
			if (!(current & 0x00000100)) {
				reg |= 0x1;
			}
			if (!(current & 0x00000080)) {
				reg |= 0x100;
			}
			if (!(current & 0x00000040)) {
				reg |= 0x1000;
			}
			if (!(current & 0x00002000)) {
				reg |= 0x200;
			}
			if (!(current & 0x00001000)) {
				reg |= 0x400;
			}
			if (!(current & 0x00000020)) {
				reg |= 0x2000;
			}
			PI_REGS[1] = reg;
			mask &= ~0x00007FE0;
			break;
	}

	return mask;
}

OSInterruptMask __OSMaskInterrupts(OSInterruptMask global)
{
	int enabled;
	OSInterruptMask prev;
	OSInterruptMask local;
	OSInterruptMask mask;

	enabled = OSDisableInterrupts();
	prev    = OS_INTERRUPT_MASK_GLOBAL;
	local   = OS_INTERRUPT_MASK_LOCAL;
	mask    = ~(prev | local) & global;
	global |= prev;
	OS_INTERRUPT_MASK_GLOBAL = global;
	while (mask) {
		mask = SetInterruptMask(mask, global | local);
	}
	OSRestoreInterrupts(enabled);
	return prev;
}

OSInterruptMask __OSUnmaskInterrupts(OSInterruptMask global)
{
	int enabled;
	OSInterruptMask prev;
	OSInterruptMask local;
	OSInterruptMask mask;

	enabled                  = OSDisableInterrupts();
	prev                     = OS_INTERRUPT_MASK_GLOBAL;
	local                    = OS_INTERRUPT_MASK_LOCAL;
	mask                     = (prev | local) & global;
	global                   = prev & ~global;
	OS_INTERRUPT_MASK_GLOBAL = global;
	while (mask) {
		mask = SetInterruptMask(mask, global | local);
	}
	OSRestoreInterrupts(enabled);
	return prev;
}

void __OSDispatchInterrupt(__OSException exception, OSContext* context)
{
	u32 intsr;
	u32 reg;
	OSInterruptMask cause;
	OSInterruptMask unmasked;
	OSInterruptMask* prio;
	__OSInterruptHandler handler;
	__OSInterrupt interrupt;
	OSTime time;
	// Dead local. The original frame is eight bytes larger than the live
	// variables need, so the original source declared something here that its
	// compiler kept in registers; without it the frame is 0x20 instead of
	// 0x28 and nothing else changes.
	u32 pad[2];

	intsr = PI_REGS[0];
	intsr &= ~0x00010000;

	if (intsr == 0 || (intsr & PI_REGS[1]) == 0) {
		OSLoadContext(context);
	}

	cause = 0;

	if (intsr & 0x00000080) {
		reg = MEM_REGS[15];
		if (reg & 0x1) {
			cause |= 0x80000000;
		}
		if (reg & 0x2) {
			cause |= 0x40000000;
		}
		if (reg & 0x4) {
			cause |= 0x20000000;
		}
		if (reg & 0x8) {
			cause |= 0x10000000;
		}
		if (reg & 0x10) {
			cause |= 0x08000000;
		}
	}

	if (intsr & 0x00000040) {
		reg = DSP_REGS[5];
		if (reg & 0x8) {
			cause |= 0x04000000;
		}
		if (reg & 0x20) {
			cause |= 0x02000000;
		}
		if (reg & 0x80) {
			cause |= 0x01000000;
		}
	}

	if (intsr & 0x00000020) {
		reg = AI_REGS[0];
		if (reg & 0x8) {
			cause |= 0x00800000;
		}
	}

	if (intsr & 0x00000010) {
		reg = EXI_REGS[0];
		if (reg & 0x2) {
			cause |= 0x00400000;
		}
		if (reg & 0x8) {
			cause |= 0x00200000;
		}
		if (reg & 0x800) {
			cause |= 0x00100000;
		}

		reg = EXI_REGS[5];
		if (reg & 0x2) {
			cause |= 0x00080000;
		}
		if (reg & 0x8) {
			cause |= 0x00040000;
		}
		if (reg & 0x800) {
			cause |= 0x00020000;
		}

		reg = EXI_REGS[10];
		if (reg & 0x2) {
			cause |= 0x00010000;
		}
		if (reg & 0x8) {
			cause |= 0x00008000;
		}
	}

	if (intsr & 0x00002000) {
		cause |= 0x00000020;
	}
	if (intsr & 0x00001000) {
		cause |= 0x00000040;
	}
	if (intsr & 0x00000400) {
		cause |= 0x00001000;
	}
	if (intsr & 0x00000200) {
		cause |= 0x00002000;
	}
	if (intsr & 0x00000100) {
		cause |= 0x00000080;
	}
	if (intsr & 0x00000008) {
		cause |= 0x00000800;
	}
	if (intsr & 0x00000004) {
		cause |= 0x00000400;
	}
	if (intsr & 0x00000002) {
		cause |= 0x00000200;
	}
	if (intsr & 0x00000800) {
		cause |= 0x00004000;
	}
	if (intsr & 0x00000001) {
		cause |= 0x00000100;
	}

	unmasked = cause & ~(OS_INTERRUPT_MASK_GLOBAL | OS_INTERRUPT_MASK_LOCAL);
	if (unmasked != 0) {
		for (prio = InterruptPrioTable;; prio++) {
			if ((reg = unmasked & *prio) != 0) {
				interrupt = (__OSInterrupt)__cntlzw(reg);
				break;
			}
		}

		if ((handler = InterruptHandlerTable[interrupt]) != NULL) {
			if (interrupt > 4) {
				__OSLastInterrupt     = interrupt;
				time                  = OSGetTime();
				__OSLastInterruptTime = time;
				__OSLastInterruptSrr0 = context->srr0;
			}

			OSDisableScheduler();
			handler(interrupt, context);
			OSEnableScheduler();
			__OSReschedule();
			OSLoadContext(context);
		}
	}

	OSLoadContext(context);
}

// Saves the caller-saved half of the register file into the context the
// exception glue picked, then falls through into the dispatcher. Assembly in
// the original source too: C cannot store the register file it is itself
// running on.
// clang-format off
static ASM void ExternalInterruptHandler(register __OSException exception, register OSContext* context)
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
	b       __OSDispatchInterrupt
#endif
} // clang-format on
