#include "types.h"

// Serial link to the debugger, over EXI channel 1. WORK IN PROGRESS: only the
// two init functions are written. DBWrite, DBRead, DBQueryData and the six
// static helpers below them are still assembly in the build.
//
// The translation unit boundary was settled by looking at who calls what.
// Everything from DBWrite at 0x801F81A8 through the helper at 0x801F8988 is
// private to this file: the five anonymous helpers are only ever called from
// DBWrite, DBRead and DBQueryData, and the two at 0x801F85FC and 0x801F863C are
// never called at all, they are installed as interrupt handlers by
// DBInitInterrupts. The first function past the end, at 0x801F8C20, is called
// from outside, which is where the file stops.

#define NULL 0

typedef int BOOL;

// Debugger interrupt, and the EXI channel the link runs on.
#define DB_INTERRUPT_MASK 0x00018000
#define EXI_INTERRUPT_MASK 0x40

#define EXI_CHANNEL1_CR (*(u32*)0xCC006828)

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32  __OSMaskInterrupts(u32 mask);
extern u32  __OSUnmaskInterrupts(u32 mask);
extern void (*__OSSetInterruptHandler(s16 interrupt, void (*handler)(s16, void*)))(s16, void*);

extern void DBGHandler(s16 interrupt, void* context);
extern void EXIHandler(s16 interrupt, void* context);

static void*    BBAInterruptHandler; // 0x8042CF00
static void*    DBCommHandler;       // 0x8042CF04
static u32      lbl_8042CF08;
static u32      lbl_8042CF0C;
static u8*      BufferPtr;           // 0x8042CF10
static u8       Buffer;              // 0x8042CF14

void DBInitComm(u8** mailbox, void* handler)
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

void DBInitInterrupts(void)
{
	__OSMaskInterrupts(DB_INTERRUPT_MASK);
	__OSMaskInterrupts(EXI_INTERRUPT_MASK);

	DBCommHandler = (void*)DBGHandler;
	__OSSetInterruptHandler(0x19, EXIHandler);

	__OSUnmaskInterrupts(EXI_INTERRUPT_MASK);
}
