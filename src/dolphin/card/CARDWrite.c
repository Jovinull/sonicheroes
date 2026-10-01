#include "types.h"
#include <dolphin/card.h>

#include "__card.h"

// CARDWrite.c of the Dolphin SDK memory card library, 0x801F0278 to 0x801F05AC.
// Boundaries: every function was matched by instruction shape against the
// reference compiled with GC/1.2.5n, in the library's link order.
// Reference: doldecomp/dolsdk2004 src/card/CARDWrite.c (public reconstruction of the
// Dolphin SDK); this DOL carries the Apr 17 2003 release build of CARD
// ("<< Dolphin SDK - CARD ... Apr 17 2003 12:34:19 >>"). Compiled with
// GC/1.2.5n like the other SDK units. The original linker smart-stripped
// the functions nothing in the game calls; they are still defined here, as in
// the SDK source, and the linker drops them again.

// prototypes
static void WriteCallback(s32 chan, s32 result);
static void EraseCallback(s32 chan, s32 result);

static void WriteCallback(s32 chan, s32 result)
{
	CARDControl* card;
	CARDCallback callback;
	u16* fat;
	CARDDir* dir;
	CARDDir* ent;
	CARDFileInfo* fileInfo;

	card = &__CARDBlock[chan];
	if (result >= 0) {
		fileInfo = card->fileInfo;
		if (fileInfo->length < 0) {
			result = CARD_RESULT_CANCELED;
			goto after;
		}
		fileInfo->length -= card->sectorSize;
		if (fileInfo->length <= 0) {
			dir               = __CARDGetDirBlock(card);
			ent               = dir + fileInfo->fileNo;
			ent->time         = OSGetTime() / (__OSBusClock / 4);
			callback          = card->apiCallback;
			card->apiCallback = NULL;
			result            = __CARDUpdateDir(chan, callback);
			goto check;
		} else {
			fat = __CARDGetFatBlock(card);
			fileInfo->offset += card->sectorSize;
			fileInfo->iBlock = fat[fileInfo->iBlock];
			if ((fileInfo->iBlock < 5) || (fileInfo->iBlock >= card->cBlock)) {
				result = CARD_RESULT_BROKEN;
				goto after;
			}
			result = __CARDEraseSector(chan, card->sectorSize * fileInfo->iBlock, EraseCallback);
		check:;
			if (result < 0) {
				goto after;
			}
		}
	} else {
	after:;
		callback          = card->apiCallback;
		card->apiCallback = NULL;
		__CARDPutControlBlock(card, result);
		callback(chan, result);
	}
}

static void EraseCallback(s32 chan, s32 result)
{
	CARDControl* card;
	CARDCallback callback;
	CARDFileInfo* fileInfo;

	card = &__CARDBlock[chan];
	if (result >= 0) {
		fileInfo = card->fileInfo;
		result   = __CARDWrite(chan, card->sectorSize * fileInfo->iBlock, card->sectorSize,
		    card->buffer, WriteCallback);
		if (result < 0) {
			goto after;
		}
	} else {
	after:;
		callback          = card->apiCallback;
		card->apiCallback = NULL;
		__CARDPutControlBlock(card, result);
		callback(chan, result);
	}
}

s32 CARDWriteAsync(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset, CARDCallback callback)
{
	CARDControl* card;
	s32 result;
	CARDDir* dir;
	CARDDir* ent;

	result = __CARDSeek(fileInfo, length, offset, &card);
	if (result < 0) {
		return result;
	}

	if (OFFSET(offset, card->sectorSize) != 0 || OFFSET(length, card->sectorSize) != 0)
		return __CARDPutControlBlock(card, CARD_RESULT_FATAL_ERROR);

	dir    = __CARDGetDirBlock(card);
	ent    = &dir[fileInfo->fileNo];
	result = __CARDIsWritable(card, ent);
	if (result < 0)
		return __CARDPutControlBlock(card, result);

	DCStoreRange((void*)buf, (u32)length);
	card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
	card->buffer      = (void*)buf;

	result = __CARDEraseSector(
	    fileInfo->chan, card->sectorSize * (u32)fileInfo->iBlock, EraseCallback);
	if (result < 0)
		__CARDPutControlBlock(card, result);
	return result;
}

s32 CARDWrite(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset)
{
	s32 result = CARDWriteAsync(fileInfo, buf, length, offset, __CARDSyncCallback);
	if (result < 0) {
		return result;
	}

	return __CARDSync(fileInfo->chan);
}
