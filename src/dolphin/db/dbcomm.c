#include "types.h"

// Serial link to the debugger, over EXI channel 1. WORK IN PROGRESS: the two
// init functions and the two interrupt handlers are written. DBWrite, DBRead,
// DBQueryData and the five static helpers below them are still assembly in the
// build.
//
// The translation unit boundary was settled by looking at who calls what.
// Everything from DBWrite at 0x801F81A8 through the helper at 0x801F8988 is
// private to this file: the five anonymous helpers are only ever called from
// DBWrite, DBRead and DBQueryData, and EXIHandler and DBGHandler are never
// called at all, they are installed as interrupt handlers by DBInitInterrupts.
// The first function past the end, at 0x801F8C20, is called from outside, which
// is where the file stops.
//
// Functions are in the order the original emits them. DBInitInterrupts comes
// before DBInitComm, and both handlers come after the pair, which is why they
// need the forward declarations below.
//
// What is left here:
//   DBInitComm  93.3%  the zero and the address of the EXI register are
//                      materialized in the opposite order. Twenty forms of the
//                      store and of the statements around it were tried and
//                      none of them move it.
//   EXIHandler  87.5%  right instructions in the right order except for the
//                      acknowledge write, which the original schedules after
//                      the handler load and ours emits before it. Reordering
//                      the statements moves it past the null test instead, and
//                      volatile does not pin it.

#define NULL 0

typedef int BOOL;

// Debugger interrupt, and the EXI channel the link runs on.
#define DB_INTERRUPT_MASK 0x00018000
#define EXI_INTERRUPT_MASK 0x40

#define EXI_CHANNEL1_CR (*(u32*)0xCC006828)

// Interrupt cause at the processor interface. Writing the bit back is how the
// EXI interrupt gets acknowledged before it is handed on.
#define PI_INTERRUPT_CAUSE (*(u32*)0xCC003000)
#define PI_DEBUG_INTERRUPT 0x1000

typedef void (*__OSInterruptHandler)(s16 interrupt, void* context);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32  __OSMaskInterrupts(u32 mask);
extern u32  __OSUnmaskInterrupts(u32 mask);
extern __OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, __OSInterruptHandler handler);

// Both live in this file. DBInitInterrupts installs them and the original emits
// them after it, so they have to be declared up here.
// EXIHandler takes the interrupt as a full word, not as the s16 the handler
// type uses: the original narrows it with extsh on the way into the call, which
// only happens if the parameter is wider than what it is being passed to.
static void EXIHandler(int interrupt, void* context);
static void DBGHandler(s16 interrupt, void* context);

static __OSInterruptHandler BBAInterruptHandler; // 0x8042CF00
static __OSInterruptHandler DBCommHandler;       // 0x8042CF04
static u32                  lbl_8042CF08;
static u32                  lbl_8042CF0C;
static u8*                  BufferPtr;           // 0x8042CF10
static u8                   Buffer;              // 0x8042CF14

void DBInitInterrupts(void)
{
	__OSMaskInterrupts(DB_INTERRUPT_MASK);
	__OSMaskInterrupts(EXI_INTERRUPT_MASK);

	DBCommHandler = DBGHandler;
	__OSSetInterruptHandler(0x19, (__OSInterruptHandler)EXIHandler);

	__OSUnmaskInterrupts(EXI_INTERRUPT_MASK);
}

void DBInitComm(u8** mailbox, __OSInterruptHandler handler)
{
	BOOL enabled;

	enabled   = OSDisableInterrupts();
	BufferPtr = &Buffer;
	*mailbox  = BufferPtr;

	BBAInterruptHandler = handler;

	__OSMaskInterrupts(DB_INTERRUPT_MASK);
	EXI_CHANNEL1_CR = 0;

	OSRestoreInterrupts(enabled);
}

// Front of the debugger link: acknowledge the interrupt at the processor
// interface, then pass it to whatever DBInitInterrupts installed.
static void EXIHandler(int interrupt, void* context)
{
	PI_INTERRUPT_CAUSE = PI_DEBUG_INTERRUPT;

	if (DBCommHandler != NULL) {
		DBCommHandler(interrupt, context);
	}
}

// The debugger side. Flags the mailbox byte the other end polls, then forwards
// to the handler DBInitComm was given. The interrupt number is not passed on,
// the caller gets zero.
static void DBGHandler(s16 interrupt, void* context)
{
	Buffer = 1;

	if (BBAInterruptHandler != NULL) {
		BBAInterruptHandler(0, context);
	}
}
