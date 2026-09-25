#include "types.h"
#include <dolphin/card.h>

#include "__card.h"

// CARDDir.c of the Dolphin SDK memory card library, 0x801ED114 to 0x801ED378.
// Boundaries: every function was matched by instruction shape against the
// reference compiled with GC/1.2.5n, in the library's link order.
// Reference: doldecomp/dolsdk2004 src/card/CARDDir.c (public reconstruction of the
// Dolphin SDK); this DOL carries the Apr 17 2003 release build of CARD
// ("<< Dolphin SDK - CARD ... Apr 17 2003 12:34:19 >>"). Compiled with
// GC/1.2.5n like the other SDK units. The original linker smart-stripped
// the functions nothing in the game calls; they are still defined here, as in
// the SDK source, and the linker drops them again.
//
// __CARDGetDirBlock reads the pointer into a local before returning it: in
// the callers it is inlined into, that local keeps a stack slot, which is the
// extra 8 bytes of frame the original EraseCallback and __CARDUpdateDir
// carry.

// prototypes
static void WriteCallback(s32 chan, s32 result);
static void EraseCallback(s32 chan, s32 result);

CARDDir* __CARDGetDirBlock(CARDControl* card)
{
	CARDDir* dir = card->currentDir;
	return dir;
}

static void WriteCallback(s32 chan, s32 result)
{
	CARDControl* card = &__CARDBlock[chan];
	CARDCallback callback;

	if (result >= 0) {
		CARDDir* dir0 = (CARDDir*)((u8*)card->workArea + 0x2000);
		CARDDir* dir1 = (CARDDir*)((u8*)card->workArea + 0x4000);

		if (card->currentDir == dir0) {
			card->currentDir = dir1;
			memcpy(dir1, dir0, 0x2000);
		} else {
			card->currentDir = dir0;
			memcpy(dir0, dir1, 0x2000);
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
	CARDDir* dir;
	u32 addr;

	if (result >= 0) {
		dir    = __CARDGetDirBlock(card);
		addr   = ((u32)dir - (u32)card->workArea) / 0x2000 * card->sectorSize;
		result = __CARDWrite(chan, addr, 0x2000, dir, WriteCallback);
		if (result >= 0)
			return;
	}

	if (!card->apiCallback)
		__CARDPutControlBlock(card, result);

	callback = card->eraseCallback;
	if (callback) {
		card->eraseCallback = NULL;
		callback(chan, result);
	}
}

s32 __CARDUpdateDir(s32 chan, CARDCallback callback)
{
	CARDControl* card;
	CARDDirCheck* check;
	u32 addr;
	CARDDir* dir;

	card = &__CARDBlock[chan];
	if (!card->attached)
		return CARD_RESULT_NOCARD;

	dir   = __CARDGetDirBlock(card);
	check = CARDGetDirCheck(dir);
	++check->checkCode;
	__CARDCheckSum(dir, 0x2000 - sizeof(u32), &check->checkSum, &check->checkSumInv);
	DCStoreRange(dir, 0x2000);

	card->eraseCallback = callback;
	addr                = ((u32)dir - (u32)card->workArea) / 0x2000 * card->sectorSize;
	return __CARDEraseSector(chan, addr, EraseCallback);
}
