#include "types.h"
#include "dolphin/os.h"

// Board support for the Metrowerks debugger nub.
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
// Functions are in the order the original emits them.

// The comm table, 0x1C bytes at 0x80291E70. It is zero in .data and filled in
// at run time with either the DB or EXI2 transport.
typedef struct DBCommTable {
	void (*init)(u8** mailbox, void* callback);  // 0x00
	void (*start)(void);                         // 0x04
	int (*peek)(void);                           // 0x08
	int (*read)(void* bytes, int length);        // 0x0C
	int (*write)(const void* bytes, int length); // 0x10
	void (*reserve)(void);                       // 0x14
	void (*unreserve)(void);                     // 0x18
} DBCommTable;                                   // 0x1C

typedef enum UARTError {
	kUARTNoError = 0,
	kUARTError   = -1,
} UARTError;

DBCommTable gDBCommTable = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };

// Descriptive names inferred from use; no surviving symbol map names these
// framing buffers.
u32 gTRKUARTState[0x447];
u8 gTRKUARTOutputBuffer[0x110C];

extern void OSEnableScheduler(void);
extern void TRKLoadContext(OSContext* context, u32 flags);
extern int Hu_IsStub(void);
extern int AMC_IsStub(void);
extern void DBInitComm(u8** mailbox, void* callback);
extern void DBInitInterrupts(void);
extern int DBQueryData(void);
extern int DBRead(void* bytes, int length);
extern int DBWrite(const void* bytes, int length);
extern void DBOpen(void);
extern void DBClose(void);
extern void EXI2_Init(void);
extern void EXI2_EnableInterrupts(void);
extern int EXI2_Poll(void);
extern int EXI2_ReadN(void* bytes, int length);
extern int EXI2_WriteN(const void* bytes, int length);
extern void EXI2_Reserve(void);
extern void EXI2_Unreserve(void);

// Defined at the end of the file but installed from the middle of it.
void TRKEXICallBack(s32 chan, OSContext* context);

// The link is interrupt driven through EXI, not through a serial port, so the
// hook the nub expects for a UART has nothing to do.
void TRKUARTInterruptHandler(void) { }

void TRK_board_display(const char* msg)
{
	OSReport(msg);
}

void UnreserveEXI2Port(void)
{
	gDBCommTable.unreserve();
}

void ReserveEXI2Port(void)
{
	gDBCommTable.reserve();
}

int TRKReadUART1(u8* byte)
{
	u32* state = gTRKUARTState;
	int result = 4;

	if ((int)state[1] >= (int)state[2]) {
		state[1] = 0;
		state[2] = gDBCommTable.peek();
		if ((int)state[2] > 0) {
			if ((int)state[2] > 0x110A) {
				state[2] = 0x110A;
			}
			result = gDBCommTable.read((u8*)state + 0x10, state[2]) ? -1 : 0;
			if (result != 0) {
				state[2] = 0;
			}
		}
	}

	if ((int)state[1] < (int)state[2]) {
		int position = state[1];
		u8* current  = (u8*)state;
		current += position;
		state[1] = position + 1;
		*byte    = current[0x10];
		result   = 0;
	}
	return result;
}

// Appends one byte to the trace buffer. Nothing bounds the index: the buffer is
// large and the nub is expected to drain it.
int TRKWriteUART1(u8 c)
{
	gTRKUARTOutputBuffer[gTRKUARTState[0]++] = c;
	return 0;
}

static inline UARTError TRK_WriteUARTN(const void* bytes, int length)
{
	int writeResult = gDBCommTable.write(bytes, length);
	return !writeResult ? kUARTNoError : kUARTError;
}

UARTError TRKFlushUART(void)
{
	UARTError result = kUARTNoError;
	int length       = gTRKUARTState[0];
	u8 zero;
	u8* cursor;

	zero   = 0;
	cursor = gTRKUARTOutputBuffer + length;
	while (length < 0x800) {
		*cursor++ = zero;
		length++;
	}
	gTRKUARTState[0] = length;

	if (length != 0) {
		result           = TRK_WriteUARTN(gTRKUARTOutputBuffer, length);
		gTRKUARTState[0] = 0;
	}
	return result;
}

// Not static: EnableMetroTRKInterrupts in targimpl.c calls it, and the symbol
// carries no scope:local marker in symbols.txt.
void EnableEXI2Interrupts(void)
{
	gDBCommTable.start();
}

// Hands the nub's own mailbox and callback to the comm layer. The UART in the
// name is vestigial, there is no serial port involved.
int TRKInitializeIntDrivenUART(u32 baud, u32 flags, u32 length, u8** mailbox)
{
	gDBCommTable.init(mailbox, TRKEXICallBack);
	return 0;
}

int InitMetroTRKCommTable(int hardware)
{
	int isStub;

	if (hardware == 1) {
		OSReport("MetroTRK : Set to GDEV hardware\n");
		isStub                 = Hu_IsStub();
		gDBCommTable.init      = DBInitComm;
		gDBCommTable.start     = DBInitInterrupts;
		gDBCommTable.peek      = DBQueryData;
		gDBCommTable.read      = DBRead;
		gDBCommTable.write     = DBWrite;
		gDBCommTable.reserve   = DBOpen;
		gDBCommTable.unreserve = DBClose;
	} else {
		OSReport("MetroTRK : Set to AMC DDH hardware\n");
		isStub                 = AMC_IsStub();
		gDBCommTable.init      = (void (*)(u8**, void*))EXI2_Init;
		gDBCommTable.start     = EXI2_EnableInterrupts;
		gDBCommTable.peek      = EXI2_Poll;
		gDBCommTable.read      = EXI2_ReadN;
		gDBCommTable.write     = EXI2_WriteN;
		gDBCommTable.reserve   = EXI2_Reserve;
		gDBCommTable.unreserve = EXI2_Unreserve;
	}
	return isStub;
}

// Runs when the link has something for the nub. The scheduler is turned back on
// first because whoever was interrupted may have left it off, and the nub is
// allowed to run threads.
void TRKEXICallBack(s32 chan, OSContext* context)
{
	OSEnableScheduler();
	TRKLoadContext(context, 0x500);
}
