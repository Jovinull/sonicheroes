#include "types.h"
#include "dolphin/os.h"

// Serial link to the debugger over EXI channel 2.
//
// The translation unit boundary was settled by looking at who calls what.
// Everything from DBWrite at 0x801F81A8 through the helper at 0x801F8988 is
// private to this file. The helpers are called only by DBWrite, DBRead and
// DBQueryData; DBGHandler and MWCallback are installed by DBInitInterrupts.
// The first function past the end, at 0x801F8C20, is called from outside, which
// is where the file stops.
//
// This is Nintendo's OdemuExi2 runtime object. Its deferred-inline source order
// is significant: helpers are defined first, then emitted where their exported
// callers first require them. The transfer primitive keeps C long parameters
// because this SDK defined s32/u32 with long; changing them to the project's
// int-based aliases changes MetroWerks' loop optimization despite equal width.

// Debugger interrupt, and the EXI channel the link runs on.
#define DB_INTERRUPT_MASK  0x00018000
#define EXI_INTERRUPT_MASK 0x40

// EXI registers. The block starts at 0xCC006800 and gives each channel five
// words, so channel 2 starts at 0x28: status at 0x28, control at 0x34. The
// debugger link is that channel.
#ifdef __MWERKS__
extern volatile u32 __EXIRegs[] : 0xCC006800;
extern volatile u32 __PIRegs[] : 0xCC003000;
#else
extern volatile u32 __EXIRegs[];
extern volatile u32 __PIRegs[];
#endif

#define EXI_REGS          __EXIRegs
#define EXI_CHANNEL2_CSR  (EXI_REGS[10])
#define EXI_CHANNEL2_CR   (EXI_REGS[13])
#define EXI_CHANNEL2_DATA (EXI_REGS[14])

// Word offsets of the two channel 2 registers from the start of the block. The
// helpers below reach them by bumping a pointer rather than by indexing, which
// is what the original does: the update forms (stwu, lwzu) only appear for
// *(p += n), while a plain EXI_REGS[n] folds the offset into a displacement and
// rebuilds the address at every use.
#define EXI_CSR_WORD 10
#define EXI_CR_WORD  13

// The bits of the status register that survive a device select, and the select
// itself. Everything else is cleared on the way in and on the way out.
#define EXI_CSR_KEEP   0x405
#define EXI_CSR_SELECT 0xC0

// Set while a transfer is running.
#define EXI_CR_TSTART 1

// Interrupt cause at the processor interface. Writing the bit back is how the
// EXI interrupt gets acknowledged before it is handed on.
#define PI_INTERRUPT_CAUSE (__PIRegs[0])
#define PI_DEBUG_INTERRUPT 0x1000

// Both live in this file. DBInitInterrupts installs them and the original emits
// them after it, so they have to be declared up here.
// EXIHandler takes the interrupt as a full word, not as the s16 the handler
// type uses: the original narrows it with extsh on the way into the call, which
// only happens if the parameter is wider than what it is being passed to.
static void DBGHandler(int interrupt, void* context);
static void MWCallback(s16 interrupt, void* context);

// Both read one word out of the debugger, and differ only in the command they
// send first. Written below, called from DBQueryData above.
static BOOL DBGReadStatus(u32* out);
static BOOL DBGReadMailbox(u32* out);

// The shared transfer primitive, written at the end of the file. Everything
// that touches the link goes through it.
static BOOL DBGEXIImm(void* buffer, signed long length, unsigned long write);

static inline u32 DBGEXISelect(u32 value)
{
	u32 regs = EXI_CHANNEL2_CSR;
	regs &= EXI_CSR_KEEP;
	regs |= 0x80 | (value << 4);
	EXI_CHANNEL2_CSR = regs;
	return TRUE;
}

static inline BOOL DBGEXIDeselect(void)
{
	EXI_CHANNEL2_CSR &= EXI_CSR_KEEP;
	return TRUE;
}

static inline BOOL DBGEXISync(void)
{
	while (EXI_CHANNEL2_CR & EXI_CR_TSTART) {
	}
	return TRUE;
}

// The two block halves, written below. DBWrite drives the write one and DBRead
// the read one.
static BOOL DBGWrite(u32 addr, void* buffer, s32 length);
static BOOL DBGRead(u32 addr, void* buffer, s32 length);

// Sequence counter for the link, one byte of a pair living in another unit's
// .sdata. Its low bit picks the window a transfer goes through, and its value
// rides along in the trailer word so the other end can follow the order.
extern u8 lbl_8042C068;

static __OSInterruptHandler BBAInterruptHandler; // 0x8042CF00
static __OSInterruptHandler DBCommHandler;       // 0x8042CF04
static u32 lbl_8042CF08;
static int lbl_8042CF0C;
static u8* BufferPtr; // 0x8042CF10
static u8 Buffer;     // 0x8042CF14

// Hands a payload to the debugger. Waits for the link to go quiet, bumps the
// sequence counter and pushes the payload through the window its low bit
// selects, then follows it with a trailer word carrying the counter and the
// real length, and waits for the link to go quiet again. Every step retries
// until it succeeds, so the only way out is success.
static BOOL DBGEXIImm(void* buffer, signed long length, unsigned long write)
{
	u8* tempPointer;
	unsigned long word;
	int i;

	if (write) {
		tempPointer = buffer;
		word        = 0;
		for (i = 0; i < length; i++) {
			u8* temp = (u8*)buffer + i;
			word |= *temp << ((3 - i) << 3);
		}
		EXI_CHANNEL2_DATA = word;
	}

	EXI_CHANNEL2_CR = EXI_CR_TSTART | (write << 2) | ((length - 1) << 4);
	DBGEXISync();

	if (!write) {
		word        = EXI_CHANNEL2_DATA;
		tempPointer = buffer;
		for (i = 0; i < length; i++) {
			*tempPointer++ = word >> ((3 - i) << 3);
		}
	}
	return TRUE;
}

static inline BOOL DBGWriteMailbox(u32 value)
{
	u32 cmd = 0xC0000000;
	u32 data;
	u32 base   = value;
	BOOL total = FALSE;

	DBGEXISelect(4);
	data = (base & 0x1FFFFFFF) | cmd;
	total |= !DBGEXIImm(&data, 4, 1);
	total |= !DBGEXISync();
	total |= !DBGEXIDeselect();
	return !total;
}

#pragma dont_inline on
static BOOL DBGReadMailbox(u32* out)
{
	BOOL total = FALSE;
	u32 cmd;

	DBGEXISelect(4);
	cmd = 0x60000000;
	total |= !DBGEXIImm(&cmd, 2, 1);
	total |= !DBGEXISync();
	total |= !DBGEXIImm(out, 4, 0);
	total |= !DBGEXISync();
	total |= !DBGEXIDeselect();
	return !total;
}
#pragma dont_inline reset

static BOOL DBGRead(u32 addr, void* buffer, s32 length)
{
	BOOL total = FALSE;
	u32* dst   = buffer;
	u32 cmd;
	u32 word;

	DBGEXISelect(4);
	cmd = ((addr & 0x1FFFC) << 8) | 0x20000000;
	total |= !DBGEXIImm(&cmd, 4, 1);
	total |= !DBGEXISync();
	while (length) {
		total |= !DBGEXIImm(&word, 4, 0);
		total |= !DBGEXISync();
		*dst++ = word;
		length -= 4;
		if (length < 0) {
			length = 0;
		}
	}
	total |= !DBGEXIDeselect();
	return !total;
}

static BOOL DBGWrite(u32 addr, void* buffer, s32 length)
{
	BOOL total = FALSE;
	u32* src   = buffer;
	u32 cmd;
	u32 word;

	DBGEXISelect(4);
	cmd = ((addr & 0x1FFFC) << 8) | 0xA0000000;
	total |= !DBGEXIImm(&cmd, 4, 1);
	total |= !DBGEXISync();
	while (length != 0) {
		word = *src++;
		total |= !DBGEXIImm(&word, 4, 1);
		total |= !DBGEXISync();
		length -= 4;
		if (length < 0) {
			length = 0;
		}
	}
	total |= !DBGEXIDeselect();
	return !total;
}

static inline BOOL ReadStatus(u32* out)
{
	BOOL total = FALSE;
	u32 cmd;

	DBGEXISelect(4);
	cmd = 0x40000000;
	total |= !DBGEXIImm(&cmd, 2, 1);
	total |= !DBGEXISync();
	total |= !DBGEXIImm(out, 4, 0);
	total |= !DBGEXISync();
	total |= !DBGEXIDeselect();
	return !total;
}

#pragma dont_inline on
static BOOL DBGReadStatus(u32* out)
{
	return ReadStatus(out);
}
#pragma dont_inline reset

static void MWCallback(s16 interrupt, void* context)
{
	Buffer = 1;
	if (BBAInterruptHandler != NULL) {
		BBAInterruptHandler(0, context);
	}
}

static void DBGHandler(int interrupt, void* context)
{
	PI_INTERRUPT_CAUSE = PI_DEBUG_INTERRUPT;
	if (DBCommHandler != NULL) {
		DBCommHandler(interrupt, context);
	}
}

void DBInitComm(u8** mailbox, __OSInterruptHandler handler)
{
	BOOL enabled = OSDisableInterrupts();

	BufferPtr           = (u8*)Buffer;
	BufferPtr           = &Buffer;
	*mailbox            = BufferPtr;
	BBAInterruptHandler = handler;
	__OSMaskInterrupts(DB_INTERRUPT_MASK);
	EXI_CHANNEL2_CSR = 0;
	OSRestoreInterrupts(enabled);
}

void DBInitInterrupts(void)
{
	__OSMaskInterrupts(DB_INTERRUPT_MASK);
	__OSMaskInterrupts(EXI_INTERRUPT_MASK);
	DBCommHandler = MWCallback;
	__OSSetInterruptHandler(0x19, (__OSInterruptHandler)DBGHandler);
	__OSUnmaskInterrupts(EXI_INTERRUPT_MASK);
}

static inline void CheckMailBox(void)
{
	u32 data;

	DBGReadStatus(&data);
	if (data & 1) {
		DBGReadMailbox(&data);
		data &= 0x1FFFFFFF;
		if ((data & 0x1F000000) == 0x1F000000) {
			lbl_8042CF08 = data;
			lbl_8042CF0C = data & 0x7FFF;
			Buffer       = 1;
		}
	}
}

int DBQueryData(void)
{
	Buffer = 0;
	if (!lbl_8042CF0C) {
		BOOL enabled = OSDisableInterrupts();
		CheckMailBox();
		OSRestoreInterrupts(enabled);
	}
	return lbl_8042CF0C;
}

s32 DBRead(void* buffer, u32 length)
{
	u32 enabled = OSDisableInterrupts();
	u32 offset  = (lbl_8042CF08 & 0x10000) ? 0x1000 : 0;

	DBGRead(offset + 0x1E000, buffer, (length + 3) & ~3);
	lbl_8042CF0C = 0;
	Buffer       = 0;
	OSRestoreInterrupts(enabled);
	return 0;
}

s32 DBWrite(void* buffer, u32 length)
{
	u32 value;
	u32 status;
	BOOL enabled = OSDisableInterrupts();

	do {
		ReadStatus(&status);
	} while (status & 2);

	lbl_8042C068++;
	value = (lbl_8042C068 & 1) ? 0x1000 : 0;
	while (!DBGWrite(value | 0x1C000, buffer, (length + 3) & ~3)) {
	}

	do {
		ReadStatus(&status);
	} while (status & 2);

	value = lbl_8042C068;
	while (!DBGWriteMailbox(0x1F000000 | (value << 16) | length)) {
	}

	do {
		while (!ReadStatus(&status)) {
		}
	} while (status & 2);

	OSRestoreInterrupts(enabled);
	return 0;
}
