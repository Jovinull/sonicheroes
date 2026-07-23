#include "types.h"
#include "dolphin/os.h"

// The battery backed settings block.
//
// The translation unit runs from WriteSramCallback at 0x801D541C to the end
// of OSSetGbsMode at 0x801D60C0. Before it is game code, after it is
// OSStopwatch.c. An earlier upstream split started this unit at __OSInitSram
// (0x801D5594) and ran to 0x801D6264, but that range cuts WriteSramCallback
// and WriteSram off the front and slices through the stopwatch unit at the
// back; the boundaries here are the ones the matched functions prove.
//
// fn_801D541C is the SDK's WriteSramCallback, fn_801D547C is WriteSram and
// fn_801D5788 is UnlockSram. WriteSram is inlined into UnlockSram but called
// from WriteSramCallback: the callback sits before WriteSram's definition, so
// the single pass compiler has no body to inline there yet, which pins the
// original source order.
//
// The checksum covers counterBias through flags only, and UnlockSram zeroes
// the GBS halfword when it carries either of two patterns; both are as the
// code has them.

typedef void (*EXICallback)(s32 chan, void* context);

typedef struct OSSram {
	u16 checkSum;      // 0x00
	u16 checkSumInv;   // 0x02
	u32 ead0;          // 0x04
	u32 ead1;          // 0x08
	u32 counterBias;   // 0x0C
	s8 displayOffsetH; // 0x10
	u8 ntd;            // 0x11
	u8 language;       // 0x12
	u8 flags;          // 0x13
} OSSram;              // 0x14

typedef struct OSSramEx {
	u8 flashID[2][12];      // 0x00
	u32 wirelessKeyboardID; // 0x18
	u16 wirelessPadID[4];   // 0x1C
	u8 dvdErrorCode;        // 0x24
	u8 _padding0;           // 0x25
	u8 flashIDChecksum[2];  // 0x26
	u16 gbs;                // 0x28
	u8 _padding1[2];        // 0x2A
} OSSramEx;                 // 0x2C

typedef struct SramControl {
	OSSram sram;     // 0x00
	OSSramEx sramEx; // 0x14
	u32 offset;      // 0x40
	BOOL enabled;    // 0x44
	BOOL locked;     // 0x48
	BOOL sync;       // 0x4C
	// One more word in the original's block; nothing references it, the size
	// comes from the original object's .bss.
	u32 unk_0x50; // 0x50
} SramControl;    // 0x54

extern BOOL EXIImm(s32 chan, void* buf, s32 len, u32 type, EXICallback callback);
extern BOOL EXIDma(s32 chan, void* buf, s32 len, u32 type, EXICallback callback);
extern BOOL EXISync(s32 chan);
extern BOOL EXISelect(s32 chan, u32 dev, u32 freq);
extern BOOL EXIDeselect(s32 chan);
extern BOOL EXILock(s32 chan, u32 dev, EXICallback unlockedCallback);
extern BOOL EXIUnlock(s32 chan);
extern BOOL fn_801FA768(s32 chan, void* buf, s32 len, u32 mode);

extern u16 OSGetGbsMode(void);
extern void OSSetGbsMode(u16 mode);

static void WriteSramCallback(s32 chan, void* context);
static BOOL WriteSram(void* buffer, u32 offset, u32 size);

// The SRAM image, the low-water mark of what is dirty, and the lock state.
// File local, in the unit's .bss.
static SramControl Scb;

// Runs when the channel frees up: pushes whatever is dirty and, if that
// worked, marks the image clean.
static void WriteSramCallback(s32 chan, void* context)
{
	Scb.sync = WriteSram((u8*)&Scb + Scb.offset, Scb.offset, 0x40 - Scb.offset);
	if (Scb.sync) {
		Scb.offset = 0x40;
	}
}

// Pushes size bytes of the image at offset out to the SRAM device on channel
// zero. Claims the channel, and if it is busy leaves the callback armed so
// the write happens when it frees.
static BOOL WriteSram(void* buffer, u32 offset, u32 size)
{
	BOOL err;
	u32 cmd;

	if (!EXILock(0, 1, WriteSramCallback)) {
		return FALSE;
	}
	if (!EXISelect(0, 1, 3)) {
		EXIUnlock(0);
		return FALSE;
	}

	offset <<= 6;
	cmd = (offset + 0x100) | 0xA0000000;
	err = !EXIImm(0, &cmd, 4, 1, NULL);
	err |= !EXISync(0);
	err |= !fn_801FA768(0, buffer, size, 1);
	err |= !EXIDeselect(0);
	EXIUnlock(0);

	return !err;
}

// Pulls the whole SRAM image in over DMA. Inlined into __OSInitSram, so it
// has no body in the binary.
static inline BOOL ReadSram(void* buffer)
{
	BOOL err = FALSE;
	u32 cmd;

	DCInvalidateRange(buffer, 0x40);

	if (!EXILock(0, 1, NULL)) {
		return FALSE;
	}
	if (!EXISelect(0, 1, 3)) {
		EXIUnlock(0);
		return FALSE;
	}

	cmd = 0x20000100;
	err = !EXIImm(0, &cmd, 4, 1, NULL);
	err |= !EXISync(0);
	err |= !EXIDma(0, buffer, 0x40, 0, NULL);
	err |= !EXISync(0);
	err |= !EXIDeselect(0);
	EXIUnlock(0);

	return !err;
}

void __OSInitSram(void)
{
	Scb.enabled = FALSE;
	Scb.locked  = FALSE;

	Scb.sync   = ReadSram(&Scb);
	Scb.offset = 0x40;

	OSSetGbsMode(OSGetGbsMode());
}

// Claims the image for a caller. Inlined into both lock entry points, so it
// has no body in the binary.
static inline u8* LockSram(u32 offset)
{
	BOOL enabled;

	enabled = OSDisableInterrupts();

	if (Scb.locked != FALSE) {
		OSRestoreInterrupts(enabled);
		return NULL;
	}

	Scb.enabled = enabled;
	Scb.locked  = TRUE;

	return (u8*)&Scb + offset;
}

u8* __OSLockSram(void)
{
	return LockSram(0);
}

u8* __OSLockSramEx(void)
{
	return LockSram(0x14);
}

// UnlockSram in the SDK: recomputes the checksum when the plain SRAM half was
// touched, widens the dirty window, sanitises the GBS halfword, and starts
// the write if the whole window is dirty enough to need one.
BOOL fn_801D5788(BOOL commit, u32 offset)
{
	OSSram* sram;
	OSSramEx* sramEx;
	u16* p;

	if (commit) {
		if (offset == 0) {
			sram = &Scb.sram;

			if ((u32)(sram->flags & 3) > 2) {
				sram->flags &= ~3;
			}

			sram->checkSumInv = 0;
			sram->checkSum    = 0;
			for (p = (u16*)&sram->counterBias; p < (u16*)(sram + 1); p++) {
				sram->checkSum += *p;
				sram->checkSumInv += ~*p;
			}
		}

		if (offset < Scb.offset) {
			Scb.offset = offset;
		}

		if (Scb.offset <= 0x14) {
			sramEx = &Scb.sramEx;
			if ((sramEx->gbs & 0x7C00) == 0x5000U || (sramEx->gbs & 0xC0) == 0xC0U) {
				sramEx->gbs = 0;
			}
		}

		Scb.sync = WriteSram((u8*)&Scb + Scb.offset, Scb.offset, 0x40 - Scb.offset);
		if (Scb.sync) {
			Scb.offset = 0x40;
		}
	}

	Scb.locked = FALSE;
	OSRestoreInterrupts(Scb.enabled);
	return Scb.sync;
}

void __OSUnlockSram(BOOL commit)
{
	fn_801D5788(commit, 0);
}

void __OSUnlockSramEx(BOOL commit)
{
	fn_801D5788(commit, 0x14);
}

BOOL __OSSyncSram(void)
{
	return Scb.sync;
}

// The accessor family. Each one takes the lock, reads or rewrites one field
// of the image, and unlocks with a commit only when something changed. The
// unlock calls inline down to the shared core; the lock is spelled out in
// place in each accessor, which is what the original emits.

// OSGetSoundMode in the SDK. The lock is written in place: calling the lock
// function compiles to an extra pointer test the original does not have.
u32 fn_801D5B1C(void)
{
	OSSram* sram;
	u32 mode;

	sram = (OSSram*)__OSLockSram();
	mode = (sram->flags & 0x04) ? 1 : 0;
	__OSUnlockSram(FALSE);
	return mode;
}

// OSSetSoundMode in the SDK.
void fn_801D5B9C(u32 mode)
{
	OSSram* sram;
	// Dead locals: the original frame is 8 bytes larger.
	u32 pad[2];

	mode = (mode & 1) << 2;
	sram = (OSSram*)__OSLockSram();
	if (mode == (sram->flags & 0x04)) {
		__OSUnlockSram(FALSE);
		return;
	}

	sram->flags &= ~0x04;
	sram->flags |= mode;
	__OSUnlockSram(TRUE);
}

// OSGetProgressiveMode in the SDK. The lock is written in place: calling the lock
// function compiles to an extra pointer test the original does not have.
u32 fn_801D5C40(void)
{
	OSSram* sram;
	u32 mode;

	sram = (OSSram*)__OSLockSram();
	mode = (sram->flags & 0x80) >> 7;
	__OSUnlockSram(FALSE);
	return mode;
}

// OSSetProgressiveMode in the SDK.
void fn_801D5CB0(u32 mode)
{
	OSSram* sram;
	// Dead locals: the original frame is 8 bytes larger.
	u32 pad[2];

	mode = (mode & 1) << 7;
	sram = (OSSram*)__OSLockSram();
	if (mode == (sram->flags & 0x80)) {
		__OSUnlockSram(FALSE);
		return;
	}

	sram->flags &= ~0x80;
	sram->flags |= mode;
	__OSUnlockSram(TRUE);
}

// OSGetEuRgb60Mode in the SDK. The lock is written in place: calling the lock
// function compiles to an extra pointer test the original does not have.
u32 fn_801D5D54(void)
{
	OSSram* sram;
	u32 mode;

	sram = (OSSram*)__OSLockSram();
	mode = (sram->ntd & 0x40) >> 6;
	__OSUnlockSram(FALSE);
	return mode;
}

// OSSetEuRgb60Mode in the SDK.
void fn_801D5DC4(u32 mode)
{
	OSSram* sram;
	// Dead locals: the original frame is 8 bytes larger.
	u32 pad[2];

	mode = (mode & 1) << 6;
	sram = (OSSram*)__OSLockSram();
	if (mode == (sram->ntd & 0x40)) {
		__OSUnlockSram(FALSE);
		return;
	}

	sram->ntd &= ~0x40;
	sram->ntd |= mode;
	__OSUnlockSram(TRUE);
}

// OSGetWirelessID in the SDK.
u16 fn_801D5E68(s32 chan)
{
	OSSramEx* sram;
	u16 id;

	sram = (OSSramEx*)__OSLockSramEx();
	id   = sram->wirelessPadID[chan];
	__OSUnlockSramEx(FALSE);
	return id;
}

// OSSetWirelessID in the SDK.
// OSSetWirelessID in the SDK. The wirelessPadID slot address must form
// through a pointer bump fused into the dereference: the update-form load
// (lhzu) only appears for *(p += n), while the plain field access folds the
// offset into two displacements and never matches. 0xE halfwords is
// offsetof(OSSramEx, wirelessPadID).
void fn_801D5EEC(s32 chan, u16 id)
{
	OSSramEx* sram;
	u16* p;

	sram = (OSSramEx*)__OSLockSramEx();
	p    = (u16*)sram + chan;
	if (*(p += 0xE) != id) {
		*p = id;
		__OSUnlockSramEx(TRUE);
		return;
	}

	__OSUnlockSramEx(FALSE);
}

u16 OSGetGbsMode(void)
{
	OSSramEx* sram;
	u16 mode;

	sram = (OSSramEx*)__OSLockSramEx();
	mode = sram->gbs;
	__OSUnlockSramEx(FALSE);
	return mode;
}

void OSSetGbsMode(u16 mode)
{
	OSSramEx* sram;
	// Dead locals: the original frame is 8 bytes larger.
	u32 pad[2];

	if ((mode & 0x7C00) == 0x5000U || (mode & 0xC0) == 0xC0U) {
		mode = 0;
	}

	sram = (OSSramEx*)__OSLockSramEx();
	if (mode == sram->gbs) {
		__OSUnlockSramEx(FALSE);
		return;
	}

	sram->gbs = mode;
	__OSUnlockSramEx(TRUE);
}
