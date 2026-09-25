#include "types.h"
#include <dolphin/card.h>

#include "__card.h"

// CARDRdwr.c of the Dolphin SDK memory card library, 0x801ECA90 to 0x801ECD10.
// Boundaries: every function was matched by instruction shape against the
// reference compiled with GC/1.2.5n, in the library's link order.
// Reference: doldecomp/dolsdk2004 src/card/CARDRdwr.c (public reconstruction of the
// Dolphin SDK); this DOL carries the Apr 17 2003 release build of CARD
// ("<< Dolphin SDK - CARD ... Apr 17 2003 12:34:19 >>"). Compiled with
// GC/1.2.5n like the other SDK units. The original linker smart-stripped
// the functions nothing in the game calls; they are still defined here, as in
// the SDK source, and the linker drops them again.
//
// BlockWriteCallback and __CARDWrite follow the older revision with a fixed
// 128-byte page (zeldaret/tww src/dolphin/card/CARDRdwr.c).

// prototypes
static void BlockReadCallback(s32 chan, s32 result);
static void BlockWriteCallback(s32 chan, s32 result);

static void BlockReadCallback(s32 chan, s32 result)
{
	CARDControl* card;
	CARDCallback callback;

	card = &__CARDBlock[chan];

	if ((result >= 0)) {
		card->xferred += 0x200;
		card->addr += 0x200;
		((u8*)card->buffer) += 0x200;

		if (--card->repeat > 0) {
			result = __CARDReadSegment(chan, BlockReadCallback);
			if (result >= 0) {
				return;
			}
		}
	}

	if (!card->apiCallback) {
		__CARDPutControlBlock(card, result);
	}

	callback = card->xferCallback;
	if (callback) {
		card->xferCallback = NULL;
		callback(chan, result);
	}
}

s32 __CARDRead(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback)
{
	CARDControl* card;

	card = &__CARDBlock[chan];
	if (card->attached == 0) {
		return CARD_RESULT_NOCARD;
	}
	card->xferCallback = callback;
	card->repeat       = (length / 512u);
	card->addr         = addr;
	card->buffer       = dst;
	return __CARDReadSegment(chan, BlockReadCallback);
}

static void BlockWriteCallback(s32 chan, s32 result)
{
	CARDControl* card;
	CARDCallback callback;

	card = &__CARDBlock[chan];
	if (result >= 0) {
		card->xferred += 0x80;
		card->addr += 0x80;
		((u8*)card->buffer) += 0x80;

		if (--card->repeat > 0) {
			result = __CARDWritePage(chan, BlockWriteCallback);
			if (result >= 0) {
				return;
			}
		}
	}

	if (!card->apiCallback) {
		__CARDPutControlBlock(card, result);
	}

	callback = card->xferCallback;
	if (callback) {
		card->xferCallback = NULL;
		callback(chan, result);
	}
}

s32 __CARDWrite(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback)
{
	CARDControl* card;
	card = &__CARDBlock[chan];

	if (card->attached == 0) {
		return CARD_RESULT_NOCARD;
	}
	card->xferCallback = callback;
	card->repeat       = (int)(length / 128u);
	card->addr         = addr;
	card->buffer       = dst;
	return __CARDWritePage(chan, BlockWriteCallback);
}

s32 CARDGetXferredBytes(s32 chan)
{
	return __CARDBlock[chan].xferred;
}
