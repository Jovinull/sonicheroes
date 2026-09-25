#include "types.h"
#include <dolphin/card.h>

#include "__card.h"

// CARDDelete.c of the Dolphin SDK memory card library, 0x801F05AC to 0x801F0760.
// Boundaries: every function was matched by instruction shape against the
// reference compiled with GC/1.2.5n, in the library's link order.
// Reference: doldecomp/dolsdk2004 src/card/CARDDelete.c (public reconstruction of the
// Dolphin SDK); this DOL carries the Apr 17 2003 release build of CARD
// ("<< Dolphin SDK - CARD ... Apr 17 2003 12:34:19 >>"). Compiled with
// GC/1.2.5n like the other SDK units. The original linker smart-stripped
// the functions nothing in the game calls; they are still defined here, as in
// the SDK source, and the linker drops them again.

// prototypes
static void DeleteCallback(s32 chan, s32 result);

static void DeleteCallback(s32 chan, s32 result)
{
	CARDControl* card;
	CARDCallback callback;

	card              = &__CARDBlock[chan];
	callback          = card->apiCallback;
	card->apiCallback = NULL;

	if (result < 0)
		goto error;

	result = __CARDFreeBlock(chan, card->startBlock, callback);
	if (result < 0)
		goto error;
	return;

error:
	__CARDPutControlBlock(card, result);
	if (callback)
		callback(chan, result);
}

s32 CARDFastDeleteAsync(s32 chan, s32 fileNo, CARDCallback callback)
{
	CARDControl* card;
	CARDDir* dir;
	CARDDir* ent;
	s32 result;

	if (fileNo < 0 || CARD_MAX_FILE <= fileNo)
		return CARD_RESULT_FATAL_ERROR;

	result = __CARDGetControlBlock(chan, &card);
	if (result < 0)
		return result;

	dir    = __CARDGetDirBlock(card);
	ent    = &dir[fileNo];
	result = __CARDIsWritable(card, ent);
	if (result < 0)
		return __CARDPutControlBlock(card, result);

	if (__CARDIsOpened(card, fileNo))
		return __CARDPutControlBlock(card, CARD_RESULT_BUSY);

	card->startBlock = ent->startBlock;
	memset(ent, 0xff, sizeof(CARDDir));

	card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
	result            = __CARDUpdateDir(chan, DeleteCallback);
	if (result < 0)
		__CARDPutControlBlock(card, result);
	return result;
}

s32 CARDFastDelete(s32 chan, s32 fileNo)
{
	s32 result = CARDFastDeleteAsync(chan, fileNo, __CARDSyncCallback);
	if (result < 0) {
		return result;
	}

	return __CARDSync(chan);
}

s32 CARDDeleteAsync(s32 chan, const char* fileName, CARDCallback callback)
{
	CARDControl* card;
	s32 fileNo;
	s32 result;
	CARDDir* dir;
	CARDDir* ent;

	result = __CARDGetControlBlock(chan, &card);
	if (result < 0)
		return result;
	result = __CARDGetFileNo(card, fileName, &fileNo);
	if (result < 0)
		return __CARDPutControlBlock(card, result);
	if (__CARDIsOpened(card, fileNo))
		return __CARDPutControlBlock(card, CARD_RESULT_BUSY);

	dir              = __CARDGetDirBlock(card);
	ent              = &dir[fileNo];
	card->startBlock = ent->startBlock;
	memset(ent, 0xff, sizeof(CARDDir));

	card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
	result            = __CARDUpdateDir(chan, DeleteCallback);
	if (result < 0)
		__CARDPutControlBlock(card, result);
	return result;
}

s32 CARDDelete(s32 chan, const char* fileName)
{
	s32 result = CARDDeleteAsync(chan, fileName, __CARDSyncCallback);
	if (result < 0)
		return result;

	return __CARDSync(chan);
}
