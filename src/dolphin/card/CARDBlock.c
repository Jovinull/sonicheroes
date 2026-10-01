#include "types.h"
#include <dolphin/card.h>

#include "__card.h"

// CARDBlock.c of the Dolphin SDK memory card library, 0x801ECD10 to 0x801ED114.
// Boundaries: every function was matched by instruction shape against the
// reference compiled with GC/1.2.5n, in the library's link order.
// Reference: doldecomp/dolsdk2004 src/card/CARDBlock.c (public reconstruction of the
// Dolphin SDK); this DOL carries the Apr 17 2003 release build of CARD
// ("<< Dolphin SDK - CARD ... Apr 17 2003 12:34:19 >>"). Compiled with
// GC/1.2.5n like the other SDK units. The original linker smart-stripped
// the functions nothing in the game calls; they are still defined here, as in
// the SDK source, and the linker drops them again.
//
// __CARDGetFatBlock reads the pointer into a local before returning it: in
// the callers it is inlined into, that local keeps a stack slot, which is the
// extra 8 bytes of frame the original EraseCallback carries.

// prototypes
static void WriteCallback(s32 chan, s32 result);
static void EraseCallback(s32 chan, s32 result);

void* __CARDGetFatBlock(CARDControl* card)
{
	u16* fat = card->currentFat;
	return fat;
}

static void WriteCallback(s32 chan, s32 result)
{
	CARDControl* card;
	CARDCallback callback;
	u16* fat0;
	u16* fat1;

	card = &__CARDBlock[chan];

	if (result >= 0) {
		fat0 = (u16*)((u8*)card->workArea + 0x6000);
		fat1 = (u16*)((u8*)card->workArea + 0x8000);

		if (card->currentFat == fat0) {
			card->currentFat = fat1;
			memcpy(fat1, fat0, 0x2000);
		} else {
			card->currentFat = fat0;
			memcpy(fat0, fat1, 0x2000);
		}
	}

	if (!card->apiCallback)
		__CARDPutControlBlock(card, result);

	callback = card->eraseCallback;
	if (callback) {
		card->eraseCallback = NULL;
		callback(chan, result);
	}
}

static void EraseCallback(s32 chan, s32 result)
{
	CARDControl* card = &__CARDBlock[chan];
	CARDCallback callback;
	u16* fat;
	u32 addr;

	if (result < 0)
		goto error;

	fat    = __CARDGetFatBlock(card);
	addr   = ((u32)fat - (u32)card->workArea) / CARD_SYSTEM_BLOCK_SIZE * card->sectorSize;
	result = __CARDWrite(chan, addr, CARD_SYSTEM_BLOCK_SIZE, fat, WriteCallback);
	if (result < 0)
		goto error;

	return;

error:
	if (!card->apiCallback)
		__CARDPutControlBlock(card, result);

	callback = card->eraseCallback;
	if (callback) {
		card->eraseCallback = NULL;
		callback(chan, result);
	}
}

s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback)
{
	CARDControl* card;
	u16* fat;
	u16 iBlock;
	u16 startBlock;
	u16 prevBlock;
	u16 count;

	card = &__CARDBlock[chan];
	if (!card->attached)
		return CARD_RESULT_NOCARD;

	fat = __CARDGetFatBlock(card);
	if (fat[3] < cBlock)
		return CARD_RESULT_INSSPACE;

	fat[3] -= cBlock;
	startBlock = 0xFFFF;
	iBlock     = fat[4];
	count      = 0;
	while (0 < cBlock) {
		if (card->cBlock - 5 < ++count)
			return CARD_RESULT_BROKEN;

		iBlock++;
		if (!CARDIsValidBlockNo(card, iBlock))
			iBlock = 5;

		if (fat[iBlock] == 0x0000u) {
			if (startBlock == 0xFFFF)
				startBlock = iBlock;
			else
				fat[prevBlock] = iBlock;
			prevBlock   = iBlock;
			fat[iBlock] = 0xFFFF;
			--cBlock;
		}
	}

	fat[4]           = iBlock;
	card->startBlock = startBlock;
	return __CARDUpdateFatBlock(chan, fat, callback);
}

s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback)
{
	CARDControl* card;
	u16* fat;
	u16 nextBlock;

	card = &__CARDBlock[chan];
	if (!card->attached)
		return CARD_RESULT_NOCARD;

	fat = __CARDGetFatBlock(card);
	while (nBlock != 0xFFFF) {
		if (!CARDIsValidBlockNo(card, nBlock))
			return CARD_RESULT_BROKEN;

		nextBlock   = fat[nBlock];
		fat[nBlock] = 0;
		nBlock      = nextBlock;
		++fat[3];
	}

	return __CARDUpdateFatBlock(chan, fat, callback);
}

s32 __CARDUpdateFatBlock(s32 chan, u16* fat, CARDCallback callback)
{
	CARDControl* card;
	u32 addr;

	card = &__CARDBlock[chan];
	++fat[2];
	__CARDCheckSum(fat + 2, 0x1FFC, fat, fat + 1);
	DCStoreRange(fat, 0x2000);
	card->eraseCallback = callback;
	addr                = (((char*)fat - (char*)card->workArea) / 8192u) * card->sectorSize;
	return __CARDEraseSector(chan, addr, EraseCallback);
}
