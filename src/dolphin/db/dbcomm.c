#include "types.h"

// Serial link to the debugger, over EXI channel 2. Every function in the file
// is written. Four match; the rest are listed at the bottom of this comment.
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
// What is left here. Every one of these emits the right instructions in the
// right order and the right count; what separates them from the original is
// where values live, not what the code does.
//
// Four of the five share one cause. The original keeps the addresses of the EXI
// registers in callee saved registers for the whole body, which is why it saves
// six of them with stmw and forms the addresses with stwu and lwzu. Ours holds
// fewer and rebuilds each address from the constant, because a constant address
// is cheap to rematerialize and the compiler would rather do that than spend a
// register. Nothing tried so far changes that decision: absolute macros, an
// indexed macro off a base, a file scope const pointer, locals holding the two
// registers, and a local holding the base were all measured. Two findings did
// come out of it. The register block has to be volatile or the reads get folded
// away, worth nine points on the read helpers. And holding the registers in
// locals helps some functions and hurts others, worth three points on the read
// helpers and minus two on fn_801F8988, so it is not a general answer.
//
//   DBWrite     86.5%  158 instructions, 19 lines structural. Mostly the shared
//                      cause. Worth recording how it got here: the poll block
//                      appears three times inside DBWrite as a copy of
//                      fn_801F8678 rather than a call, and calling the helper
//                      normally leaves the function at 42.5%. The inline
//                      keyword does nothing, and the helper is defined after
//                      DBWrite so the compiler has no body to inline anyway.
//                      Writing the block out at each of the three sites, each
//                      with its own local for the command word, takes it to
//                      85.2%. The original also computes the negated result of
//                      the first transfer in each block and never reads it,
//                      which only makes sense as an expansion whose return
//                      value was discarded; reproducing that is the last point
//                      and a half. So the original almost certainly spelled
//                      this as a macro shared with fn_801F8678, not as a call.
//   fn_801F8724 64.1%  66 instructions, the shared cause above. It is the same
//                      function as fn_801F8800 with the other command byte and
//                      the payload loop the other way round, and it lands on
//                      the same number, which is a good sign that the cause is
//                      the allocator and not either body.
//   fn_801F8800 64.1%  66 instructions, the shared cause above.
//   the two read helpers 72.7%  50 instructions, the shared cause above.
//   fn_801F8988 87.6%  173 instructions, only seventeen lines structural. The
//                      shared cause, plus the original compares the loop
//                      counter against the length where ours folds that to a
//                      test of the length alone, in both loops. Writing the
//                      loops as while did not move it.
//   EXIHandler  87.5%  one instruction. The original schedules the acknowledge
//                      write after the handler load and ours emits it before.
//                      Reordering the statements moves it past the null test
//                      instead, and volatile does not pin it.
//   DBInitComm  93.3%  one instruction. The zero and the address of the EXI
//                      register are materialized in the opposite order. Twenty
//                      forms of the store and of the statements around it were
//                      tried and none of them move it.

#define NULL 0

#define FALSE 0
#define TRUE  1

typedef int BOOL;

// Debugger interrupt, and the EXI channel the link runs on.
#define DB_INTERRUPT_MASK 0x00018000
#define EXI_INTERRUPT_MASK 0x40

// EXI registers. The block starts at 0xCC006800 and gives each channel five
// words, so channel 2 starts at 0x28: status at 0x28, control at 0x34. The
// debugger link is that channel.
#define EXI_REGS          ((volatile u32*)0xCC006800)
#define EXI_CHANNEL2_CSR  (EXI_REGS[10])
#define EXI_CHANNEL2_CR   (EXI_REGS[13])
#define EXI_CHANNEL2_DATA (EXI_REGS[14])

// The bits of the status register that survive a device select, and the select
// itself. Everything else is cleared on the way in and on the way out.
#define EXI_CSR_KEEP   0x405
#define EXI_CSR_SELECT 0xC0

// Set while a transfer is running.
#define EXI_CR_TSTART 1

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

// Both read one word out of the debugger, and differ only in the command they
// send first. Written below, called from DBQueryData above.
static BOOL fn_801F8678(u32* out);
static BOOL fn_801F88DC(u32* out);

// The shared transfer primitive, written at the end of the file. Everything
// that touches the link goes through it.
static BOOL fn_801F8988(void* buffer, s32 length, u32 write);

// The two block halves, written below. DBWrite drives the write one and DBRead
// the read one.
static BOOL fn_801F8724(u32 addr, void* buffer, s32 length);
static BOOL fn_801F8800(u32 addr, void* buffer, s32 length);

// Sequence counter for the link, one byte of a pair living in another unit's
// .sdata. Its low bit picks the window a transfer goes through, and its value
// rides along in the trailer word so the other end can follow the order.
extern u8 lbl_8042C068;

static __OSInterruptHandler BBAInterruptHandler; // 0x8042CF00
static __OSInterruptHandler DBCommHandler;       // 0x8042CF04
static u32                  lbl_8042CF08;
static int                  lbl_8042CF0C;
static u8*                  BufferPtr;           // 0x8042CF10
static u8                   Buffer;              // 0x8042CF14

// Hands a payload to the debugger. Waits for the link to go quiet, bumps the
// sequence counter and pushes the payload through the window its low bit
// selects, then follows it with a trailer word carrying the counter and the
// real length, and waits for the link to go quiet again. Every step retries
// until it succeeds, so the only way out is success.
s32 DBWrite(void* buffer, u32 length)
{
	volatile u32* csr;
	volatile u32* cr;
	BOOL          enabled;
	BOOL          err;
	u32           status;
	u32           trailer;
	u32           addr;

	enabled = OSDisableInterrupts();

	csr = &EXI_CHANNEL2_CSR;
	cr  = &EXI_CHANNEL2_CR;

	do {
		u32 cmd;

		*csr = (*csr & EXI_CSR_KEEP) | EXI_CSR_SELECT;
		cmd  = 0x40000000;
		err  = !fn_801F8988(&cmd, 2, 1);
		while (*cr & EXI_CR_TSTART) {
		}
		fn_801F8988(&status, 4, 0);
		while (*cr & EXI_CR_TSTART) {
		}
		*csr &= EXI_CSR_KEEP;
	} while (status & 2);

	lbl_8042C068++;
	addr = ((lbl_8042C068 & 1) ? 0x1000 : 0) | 0x1C000;

	while (!fn_801F8724(addr, buffer, (length + 3) & ~3)) {
	}

	do {
		u32 cmd;

		*csr = (*csr & EXI_CSR_KEEP) | EXI_CSR_SELECT;
		cmd  = 0x40000000;
		err  = !fn_801F8988(&cmd, 2, 1);
		while (*cr & EXI_CR_TSTART) {
		}
		fn_801F8988(&status, 4, 0);
		while (*cr & EXI_CR_TSTART) {
		}
		*csr &= EXI_CSR_KEEP;
	} while (status & 2);

	trailer = (((lbl_8042C068 << 16) | 0x1F000000 | length) & 0x1FFFFFFF) | 0xC0000000;

	do {
		*csr = (*csr & EXI_CSR_KEEP) | EXI_CSR_SELECT;

		err = !fn_801F8988(&trailer, 4, 1);
		while (*cr & EXI_CR_TSTART) {
		}

		*csr &= EXI_CSR_KEEP;
	} while (err);

	do {
		u32 cmd;

		*csr = (*csr & EXI_CSR_KEEP) | EXI_CSR_SELECT;
		cmd  = 0x40000000;
		err  = !fn_801F8988(&cmd, 2, 1);
		while (*cr & EXI_CR_TSTART) {
		}
		err |= !fn_801F8988(&status, 4, 0);
		while (*cr & EXI_CR_TSTART) {
		}
		*csr &= EXI_CSR_KEEP;
	} while (err || (status & 2));

	OSRestoreInterrupts(enabled);

	return 0;
}

// Drains the payload the last query announced. The header bit picks which of
// the two windows the data comes out of, and the length is rounded up to a
// whole number of words because the transfer moves words.
s32 DBRead(void* buffer, u32 length)
{
	BOOL enabled;

	enabled = OSDisableInterrupts();

	fn_801F8800(((lbl_8042CF08 & 0x00010000) ? 0x1000 : 0) + 0x1E000, buffer,
	            (length + 3) & ~3);

	lbl_8042CF0C = 0;
	Buffer       = 0;

	OSRestoreInterrupts(enabled);

	return 0;
}

// Polls for a header and reports how many payload bytes are waiting. A header
// only counts if the low bit says one arrived and the tag field is all ones;
// anything else is left alone and the previous answer stands.
int DBQueryData(void)
{
	BOOL enabled;
	u32  data;

	Buffer = 0;

	if (lbl_8042CF0C == 0) {
		enabled = OSDisableInterrupts();

		fn_801F8678(&data);
		if (data & 1) {
			fn_801F88DC(&data);
			data &= 0x1FFFFFFF;

			if ((data & 0x1F000000) == 0x1F000000) {
				lbl_8042CF08 = data;
				lbl_8042CF0C = data & 0x7FFF;
				Buffer       = 1;
			}
		}

		OSRestoreInterrupts(enabled);
	}

	return lbl_8042CF0C;
}

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
	EXI_CHANNEL2_CSR = 0;

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

// Selects the device, sends one command word, then clocks four bytes back into
// out and lets go again. Each transfer is started and then waited out on the
// control register, and a failure on either half is what the result reports.
static BOOL fn_801F8678(u32* out)
{
	volatile u32* csr;
	volatile u32* cr;
	BOOL          err;
	u32           cmd;

	csr = &EXI_CHANNEL2_CSR;
	cr  = &EXI_CHANNEL2_CR;

	*csr = (*csr & EXI_CSR_KEEP) | EXI_CSR_SELECT;

	cmd = 0x40000000;
	err = !fn_801F8988(&cmd, 2, 1);
	while (*cr & EXI_CR_TSTART) {
	}

	err |= !fn_801F8988(out, 4, 0);
	while (*cr & EXI_CR_TSTART) {
	}

	*csr &= EXI_CSR_KEEP;

	return !err;
}

// The write side of fn_801F8800, instruction for instruction: same command
// word layout with a different top byte, and the payload loop pushes a word out
// of the buffer instead of pulling one in. The length is clamped the same way.
static BOOL fn_801F8724(u32 addr, void* buffer, s32 length)
{
	volatile u32* csr;
	volatile u32* cr;
	u32*          src;
	BOOL          err;
	u32           cmd;
	u32           word;

	csr = &EXI_CHANNEL2_CSR;
	cr  = &EXI_CHANNEL2_CR;
	src = (u32*)buffer;

	*csr = (*csr & EXI_CSR_KEEP) | EXI_CSR_SELECT;

	cmd = ((addr << 8) & 0x01FFFC00) | 0xA0000000;
	err = !fn_801F8988(&cmd, 4, 1);
	while (*cr & EXI_CR_TSTART) {
	}

	while (length != 0) {
		word = *src++;

		err |= !fn_801F8988(&word, 4, 1);
		while (*cr & EXI_CR_TSTART) {
		}

		length -= 4;
		if (length < 0) {
			length = 0;
		}
	}

	*csr &= EXI_CSR_KEEP;

	return !err;
}

// Drains a whole payload out of one device address. Sends the address as a
// command word, then clocks the answer back four bytes at a time until the
// length runs out. The length is clamped rather than allowed to go negative,
// so a tail shorter than a word still costs one transfer and stops.
static BOOL fn_801F8800(u32 addr, void* buffer, s32 length)
{
	volatile u32* csr;
	volatile u32* cr;
	u32*          dst;
	BOOL          err;
	u32           cmd;
	u32           word;

	csr = &EXI_CHANNEL2_CSR;
	cr  = &EXI_CHANNEL2_CR;
	dst = (u32*)buffer;

	*csr = (*csr & EXI_CSR_KEEP) | EXI_CSR_SELECT;

	cmd = ((addr << 8) & 0x01FFFC00) | 0x20000000;
	err = !fn_801F8988(&cmd, 4, 1);
	while (*cr & EXI_CR_TSTART) {
	}

	while (length != 0) {
		err |= !fn_801F8988(&word, 4, 0);
		while (*cr & EXI_CR_TSTART) {
		}

		*dst++ = word;

		length -= 4;
		if (length < 0) {
			length = 0;
		}
	}

	*csr &= EXI_CSR_KEEP;

	return !err;
}

// Same shape as fn_801F8678 down to the instruction, with the other command
// word. The original spells both out rather than sharing one body.
static BOOL fn_801F88DC(u32* out)
{
	volatile u32* csr;
	volatile u32* cr;
	BOOL          err;
	u32           cmd;

	csr = &EXI_CHANNEL2_CSR;
	cr  = &EXI_CHANNEL2_CR;

	*csr = (*csr & EXI_CSR_KEEP) | EXI_CSR_SELECT;

	cmd = 0x60000000;
	err = !fn_801F8988(&cmd, 2, 1);
	while (*cr & EXI_CR_TSTART) {
	}

	err |= !fn_801F8988(out, 4, 0);
	while (*cr & EXI_CR_TSTART) {
	}

	*csr &= EXI_CSR_KEEP;

	return !err;
}

// One EXI immediate transfer, up to four bytes, in whichever direction the
// flag asks for. The data register holds the bytes packed big end first, so
// each byte sits at (3 - i) * 8. That expression goes negative once i passes
// three, which is only safe because nothing here ever asks for more than four
// bytes, and it is what the original computes.
static BOOL fn_801F8988(void* buffer, s32 length, u32 write)
{
	s32 i;
	u32 word;

	if (write) {
		word = 0;
		for (i = 0; i < length; i++) {
			word |= ((u8*)buffer)[i] << ((3 - i) * 8);
		}
		EXI_CHANNEL2_DATA = word;
	}

	EXI_CHANNEL2_CR = ((length - 1) << 4) | (write << 2) | EXI_CR_TSTART;
	while (EXI_CHANNEL2_CR & EXI_CR_TSTART) {
	}

	if (!write) {
		word = EXI_CHANNEL2_DATA;
		for (i = 0; i < length; i++) {
			((u8*)buffer)[i] = word >> ((3 - i) * 8);
		}
	}

	return TRUE;
}
