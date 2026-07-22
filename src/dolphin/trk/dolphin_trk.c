#include "types.h"

// Board support for the Metrowerks debugger nub. WORK IN PROGRESS: eight
// functions are written, three are still assembly in the build.
//
// The nub talks to the host over EXI channel 2, the same link dbcomm.c drives,
// and reaches it through a table of function pointers rather than by calling
// into that file directly. That indirection is why this file is small: most of
// what looks like work here is one load out of the table and a jump.
//
// The translation unit runs from TRKUARTInterruptHandler at 0x801CFAF4 to
// 0x801CFF18, where TRKTargetContinue starts and belongs to the nub's target
// control file instead.
//
// gDBCommTable is defined in this file in the original. It is declared as an
// external here until the initializer is worked out, which is safe because the
// symbol is global rather than file local.
//
// Functions are in the order the original emits them.

// The comm table, 0x1C bytes at 0x80291E70. Only the entries the written
// functions reach are named; the rest is padding until something proves what
// they hold. The table is zero in .data and filled in at run time, so the entries are
// named from how they are called rather than from an initializer. The one at
// 0x00 takes a mailbox and a callback, which is dbcomm.c's DBInitComm exactly.
typedef struct DBCommTable {
	void (*init)(u8** mailbox, void* callback); // 0x00
	void (*start)(void);                        // 0x04
	void* unk08[3];                             // 0x08
	void (*reserve)(void);                      // 0x14
	void (*unreserve)(void);                    // 0x18
} DBCommTable;                                  // 0x1C

typedef struct OSContext OSContext;

extern DBCommTable gDBCommTable;

// The trace buffer and the structure holding its index, both in .bss. dtk has
// them as one object each because nothing has split them yet.
extern u32 lbl_803F0060[];
extern u8  lbl_803F117C[];

extern void OSReport(const char* msg, ...);
extern void OSEnableScheduler(void);
extern void TRKLoadContext(OSContext* context, u32 flags);

// Defined at the end of the file but installed from the middle of it.
void TRKEXICallBack(s32 chan, OSContext* context);

// The link is interrupt driven through EXI, not through a serial port, so the
// hook the nub expects for a UART has nothing to do.
void TRKUARTInterruptHandler(void) { }

void TRK_board_display(const char* msg) { OSReport(msg); }

void UnreserveEXI2Port(void) { gDBCommTable.unreserve(); }

void ReserveEXI2Port(void) { gDBCommTable.reserve(); }

// fn_801CFB7C belongs here, still unwritten.

// Appends one byte to the trace buffer. Nothing bounds the index: the buffer is
// large and the nub is expected to drain it.
static int fn_801CFC6C(u8 c)
{
	lbl_803F117C[lbl_803F0060[0]++] = c;
	return 0;
}

// fn_801CFC94 belongs here, still unwritten.

// Not static: EnableMetroTRKInterrupts in targimpl.c calls it, and the symbol
// carries no scope:local marker in symbols.txt.
void fn_801CFD74(void) { gDBCommTable.start(); }

// Hands the nub's own mailbox and callback to the comm layer. The UART in the
// name is vestigial, there is no serial port involved.
int TRKInitializeIntDrivenUART(u32 baud, u32 flags, u32 length, u8** mailbox)
{
	gDBCommTable.init(mailbox, TRKEXICallBack);
	return 0;
}

// InitMetroTRKCommTable belongs here, still unwritten.

// Runs when the link has something for the nub. The scheduler is turned back on
// first because whoever was interrupted may have left it off, and the nub is
// allowed to run threads.
void TRKEXICallBack(s32 chan, OSContext* context)
{
	OSEnableScheduler();
	TRKLoadContext(context, 0x500);
}
