// Starts memory card command `command` on the card controller (HYPOTHESIS: the card controller
// of TMemoryCardCtrl; names inferred): every command first waits while CARDProbeEx reports
// CARD_RESULT_BUSY and fails with 0 when the card is not ready; then 3 mounts the card, 4 checks
// it, 5 opens the save file and 6 reads its status (both also record the outcome in bit 1 / bit 2
// of the flags at 0x20), 7 formats, 8 creates, 9 deletes, 10 reads and 11 writes the file, 13
// writes its status, and 12 / 14 only probe. A started command returns nonzero unless the call
// reported CARD_RESULT_BUSY; commands 0-2 and unknown ones return 1. The jump table is owned
// .data (4-byte aligned, hence data_section_alignment=4). Built with -bool off, like the other
// card units: the probe result is returned as an int without bool truncation. The per-command
// inline helpers reproduce the retail stack-slot order of the probe locals.
#include "types.h"

// Local CARD declarations (dolphin/card.h does not parse as C++).
struct CardFileInfo80127A78 {
	s32 chan;
	s32 fileNo;
	s32 offset;
	s32 length;
	u16 iBlock;
};

struct CardStat80127A78 {
	u8 data[0x6C];
};

struct CardWork80127A78 {
	u8* workArea;                  // 0x00
	char fileName[0x20];           // 0x04
	CardFileInfo80127A78 fileInfo; // 0x24
	s32 fileNo;                    // 0x38
	CardStat80127A78 stat;         // 0x3C
};

struct Card80127A78 {
	CardWork80127A78* work; // 0x00
	s32 chan;               // 0x04
	u8 pad8[0x20 - 0x8];
	u32 flags;  // 0x20
	u32 length; // 0x24
	void* data; // 0x28
};

typedef void (*CardCallback80127A78)(s32 chan, s32 result);

extern "C" {
s32 CARDProbeEx(s32 chan, s32* memSize, s32* sectorSize);
s32 CARDMountAsync(
    s32 chan, void* workArea, CardCallback80127A78 detach, CardCallback80127A78 attach);
s32 CARDCheckAsync(s32 chan, CardCallback80127A78 callback);
s32 CARDOpen(s32 chan, const char* fileName, CardFileInfo80127A78* fileInfo);
s32 CARDGetStatus(s32 chan, s32 fileNo, CardStat80127A78* stat);
s32 CARDFormatAsync(s32 chan, CardCallback80127A78 callback);
s32 CARDCreateAsync(s32 chan, const char* fileName, u32 size, CardFileInfo80127A78* fileInfo,
    CardCallback80127A78 callback);
s32 CARDDeleteAsync(s32 chan, const char* fileName, CardCallback80127A78 callback);
s32 CARDReadAsync(CardFileInfo80127A78* fileInfo, void* buffer, s32 length, s32 offset,
    CardCallback80127A78 callback);
s32 CARDWriteAsync(CardFileInfo80127A78* fileInfo, const void* buffer, s32 length, s32 offset,
    CardCallback80127A78 callback);
s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CardStat80127A78* stat, CardCallback80127A78 callback);
}

// Waits while the probe reports CARD_RESULT_BUSY (-1); nonzero when the card is ready.
static inline s32 IsCardReady80127A78(Card80127A78* card)
{
	s32 memSize;
	s32 sectorSize;
	s32 result;
	do {
		result = CARDProbeEx(card->chan, &memSize, &sectorSize);
	} while (result == -1);
	return result == 0;
}

static inline s32 Mount80127A78(Card80127A78* card)
{
	return !IsCardReady80127A78(card)
	    ? 0
	    : (CARDMountAsync(card->chan, card->work->workArea, NULL, NULL) != -1);
}

static inline s32 Check80127A78(Card80127A78* card)
{
	return !IsCardReady80127A78(card) ? 0 : (CARDCheckAsync(card->chan, NULL) != -1);
}

static inline s32 Format80127A78(Card80127A78* card)
{
	return !IsCardReady80127A78(card) ? 0 : (CARDFormatAsync(card->chan, NULL) != -1);
}

static inline s32 Create80127A78(Card80127A78* card)
{
	return !IsCardReady80127A78(card) ? 0
	                                  : (CARDCreateAsync(card->chan, card->work->fileName,
	                                         card->length, &card->work->fileInfo, NULL)
	                                        != -1);
}

static inline s32 Delete80127A78(Card80127A78* card)
{
	return !IsCardReady80127A78(card)
	    ? 0
	    : (CARDDeleteAsync(card->chan, card->work->fileName, NULL) != -1);
}

static inline s32 Read80127A78(Card80127A78* card)
{
	return !IsCardReady80127A78(card)
	    ? 0
	    : (CARDReadAsync(&card->work->fileInfo, card->data, card->length, 0, NULL) != -1);
}

static inline s32 Write80127A78(Card80127A78* card)
{
	return !IsCardReady80127A78(card)
	    ? 0
	    : (CARDWriteAsync(&card->work->fileInfo, card->data, card->length, 0, NULL) != -1);
}

static inline s32 SetStatus80127A78(Card80127A78* card)
{
	return !IsCardReady80127A78(card)
	    ? 0
	    : (CARDSetStatusAsync(card->chan, card->work->fileNo, &card->work->stat, NULL) != -1);
}

static inline s32 Open80127A78(Card80127A78* card)
{
	s32 r;
	if (!IsCardReady80127A78(card)) {
		return 0;
	}
	r = CARDOpen(card->chan, card->work->fileName, &card->work->fileInfo);
	if (r == 0) {
		card->flags |= 2;
	} else {
		card->flags &= ~2;
	}
	return r != -1;
}

static inline s32 GetStatus80127A78(Card80127A78* card)
{
	s32 r;
	if (!IsCardReady80127A78(card)) {
		return 0;
	}
	r = CARDGetStatus(card->chan, card->work->fileNo, &card->work->stat);
	if (r == 0) {
		card->flags |= 4;
	} else {
		card->flags &= ~4;
	}
	return r != -1;
}

static inline s32 Probe80127A78(Card80127A78* card)
{
	return IsCardReady80127A78(card);
}

extern "C" s32 fn_80127A78(Card80127A78* card, u32 command)
{
	s32 result = 1;

	switch (command) {
		case 0:
		case 1:
		case 2:
			break;
		case 3:
			result = Mount80127A78(card);
			break;
		case 4:
			result = Check80127A78(card);
			break;
		case 5:
			result = Open80127A78(card);
			break;
		case 6:
			result = GetStatus80127A78(card);
			break;
		case 7:
			result = Format80127A78(card);
			break;
		case 8:
			result = Create80127A78(card);
			break;
		case 9:
			result = Delete80127A78(card);
			break;
		case 10:
			result = Read80127A78(card);
			break;
		case 11:
			result = Write80127A78(card);
			break;
		case 12:
			result = Probe80127A78(card);
			break;
		case 13:
			result = SetStatus80127A78(card);
			break;
		case 14:
			result = Probe80127A78(card);
			break;
	}
	return result;
}
