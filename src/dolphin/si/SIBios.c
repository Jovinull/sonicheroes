#include "dolphin/os.h"

// The serial interface driver: the transport the controllers, the memory cards
// and every other device on an SI channel are polled and read through.
//
// The translation unit runs from SIBusy at 0x801F8C20 to the end of
// SIGetTypeAsync at 0x801FA310. The bound is read rather than argued: it is
// bracketed by two units that were already placed, dbcomm.c ending at
// 0x801F8C20 and SISamplingRate.c starting at 0x801FA310.
//
// That it is SIBios.c and not some other SI file is settled by the .sbss block
// sitting in the matching gap at 0x8042CF18. It holds __PADFixBits, which the
// SDK declares here, and cmdTypeAndStatus$371, whose dollar suffix is how
// Metrowerks names a static declared inside a function rather than at file
// scope. Seventeen of the twenty two entry points were already spelled in the
// symbol table, which is why so little of this file had to be guessed at.
//
// The layouts come from the code rather than from a header. Si is the twenty
// byte control block in .data, read as chan, poll, inputBytes, input and
// callback in that order. Packet is four thirty two byte entries in .bss, and
// the alarm array beside it is four forty byte entries: the handler at
// 0x801F9B80 divides a pointer difference by forty to turn an alarm back into
// a channel index, and forty is sizeof(OSAlarm). The registers are three words
// per channel from 0xCC006400, with the poll register at index 12 and the
// control register at index 14.
//
// Seven of the twenty two functions match. SIEnablePolling is written and at
// 87%; the rest are not written yet. Nothing here is a transcription.

typedef void (*SICallback)(s32 chan, u32 error, OSContext* context);

typedef struct SIPacket {
	/* 0x00 */ s32 chan;
	/* 0x04 */ void* output;
	/* 0x08 */ u32 outputBytes;
	/* 0x0C */ void* input;
	/* 0x10 */ u32 inputBytes;
	/* 0x14 */ SICallback callback;
	/* 0x18 */ OSTime fire;
} SIPacket; // 0x20

#ifdef __MWERKS__
extern volatile u32 __SIRegs[64] : 0xCC006400;
#else
extern volatile u32 __SIRegs[64];
#endif

// Three registers per channel from 0xCC006400, then the shared ones: the poll
// register at index 12 and the control register at index 14.
#define SI_POLL 12
#define SI_COMM 14

static struct {
	/* 0x00 */ s32 chan;
	/* 0x04 */ u32 poll;
	/* 0x08 */ u32 inputBytes;
	/* 0x0C */ void* input;
	/* 0x10 */ SICallback callback;
} Si = { -1 };

static SIPacket Packet[4];

// Initialised, so it lives in .data rather than .bss.
static u32 Type[4] = { 0x08000000, 0x08000000, 0x08000000, 0x08000000 };

BOOL SIBusy(void)
{
	return (Si.chan != -1) ? TRUE : FALSE;
}

BOOL SIIsChanBusy(s32 chan)
{
	BOOL rc;

	rc = TRUE;
	if (Packet[chan].chan == -1 && Si.chan != chan) {
		rc = FALSE;
	}

	return rc;
}

void SISetCommand(s32 chan, u32 command)
{
	__SIRegs[chan * 3] = command;
}

void SITransferCommands(void)
{
	__SIRegs[SI_COMM] = 0x80000000;
}

u32 SISetXY(u32 x, u32 y)
{
	u32 reg;
	BOOL enabled;

	reg = x << 16;
	reg |= y << 8;

	enabled = OSDisableInterrupts();
	Si.poll &= ~0x03FFFF00;
	Si.poll |= reg;
	reg               = Si.poll;
	__SIRegs[SI_POLL] = reg;
	OSRestoreInterrupts(enabled);

	return reg;
}

u32 SIDisablePolling(u32 poll)
{
	BOOL enabled;
	u32 en;

	if (poll == 0) {
		return Si.poll;
	}

	enabled           = OSDisableInterrupts();
	poll              = (poll >> 24) & 0xF0;
	en                = Si.poll & ~poll;
	__SIRegs[SI_POLL] = en;
	Si.poll           = en;
	OSRestoreInterrupts(enabled);

	return en;
}

u32 SIGetStatus(s32 chan)
{
	BOOL enabled;
	u32 sr;

	enabled = OSDisableInterrupts();

	sr = __SIRegs[SI_COMM];
	sr >>= 8 * (3 - chan);
	if (sr & 0x08) {
		if (!(Type[chan] & 0x80)) {
			Type[chan] = 8;
		}
	}

	OSRestoreInterrupts(enabled);

	return sr;
}

u32 SIEnablePolling(u32 poll)
{
	BOOL enabled;
	u32 en;

	if (poll == 0) {
		return Si.poll;
	}

	enabled = OSDisableInterrupts();

	poll >>= 24;
	en = (poll >> 4) & 0x0F;
	Si.poll &= ~en;
	poll &= en | 0x03FFFFF0;
	poll &= ~0x03FFFF00;
	Si.poll |= poll;

	__SIRegs[SI_COMM] = 0x80000000;
	__SIRegs[SI_POLL] = Si.poll;
	en                = Si.poll;

	OSRestoreInterrupts(enabled);

	return en;
}
