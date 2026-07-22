#include "types.h"

// Board support for the Metrowerks debugger nub. WORK IN PROGRESS: five
// functions are written, the rest are still assembly in the build.
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

// The comm table, 0x1C bytes at 0x80291E70. Only the two entries the written
// functions reach are named; the rest is padding until something proves what
// they hold.
typedef struct DBCommTable {
	void* unk00[5];          // 0x00
	void (*reserve)(void);   // 0x14
	void (*unreserve)(void); // 0x18
} DBCommTable;               // 0x1C

typedef struct OSContext OSContext;

extern DBCommTable gDBCommTable;

extern void OSReport(const char* msg, ...);
extern void OSEnableScheduler(void);
extern void TRKLoadContext(OSContext* context, u32 flags);

// The link is interrupt driven through EXI, not through a serial port, so the
// hook the nub expects for a UART has nothing to do.
void TRKUARTInterruptHandler(void) { }

void TRK_board_display(const char* msg) { OSReport(msg); }

void UnreserveEXI2Port(void) { gDBCommTable.unreserve(); }

void ReserveEXI2Port(void) { gDBCommTable.reserve(); }

// fn_801CFB7C, fn_801CFC6C, fn_801CFC94, fn_801CFD74,
// TRKInitializeIntDrivenUART and InitMetroTRKCommTable belong here, still
// unwritten.

// Runs when the link has something for the nub. The scheduler is turned back on
// first because whoever was interrupted may have left it off, and the nub is
// allowed to run threads.
void TRKEXICallBack(s32 chan, OSContext* context)
{
	OSEnableScheduler();
	TRKLoadContext(context, 0x500);
}
