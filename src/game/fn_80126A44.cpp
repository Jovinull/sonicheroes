#include "types.h"

// Card operation step (HYPOTHESIS: counting this game's save files): walks the card directory
// from the file number at work 0xAC up to 127 with CARDGetStatus into the work block's CARDStat
// (0x3C). An entry of this game (company code at work 0xB0, game code at 0xB2) whose name contains
// the save name (0x4) increments the count at 0xA8; CARD_RESULT_NOFILE (-4) entries are skipped,
// and any other error clears the count and goes through fn_80127760. CARD_RESULT_BUSY (-1) waits
// for the next call. After the last entry it finishes with fn_80127884.

struct CardStat80126A44 {
	char fileName[0x20]; // 0x00
	u32 length;          // 0x20
	u32 time;            // 0x24
	u8 gameName[4];      // 0x28
	u8 company[2];       // 0x2C
	u8 pad2E[0x6C - 0x2E];
};

struct CardWork80126A44 {
	u8* buffer;            // 0x00
	char fileName[0x20];   // 0x04
	u8 pad24[0x3C - 0x24]; // 0x24: CARDFileInfo
	CardStat80126A44 stat; // 0x3C
	s32 count;             // 0xA8
	s32 fileNo;            // 0xAC
	u8 company[2];         // 0xB0
	u8 gameName[4];        // 0xB2
};

struct Card80126A44 {
	CardWork80126A44* work; // 0x0
	s32 chan;               // 0x4
};

extern "C" {
s32 memcmp(const void* lhs, const void* rhs, u32 size);
char* strstr(const char* string, const char* pattern);
s32 CARDGetStatus(s32 chan, s32 fileNo, CardStat80126A44* stat);
s32 fn_801276A8(Card80126A44* card);
void fn_80127760(Card80126A44* card, s32 cardResult);
void fn_80127884(Card80126A44* card);

void fn_80126A44(Card80126A44* card)
{
	s32 r;

	if (fn_801276A8(card) != 0) {
		return;
	}
	while (card->work->fileNo != 127) {
		CardWork80126A44* work = card->work;
		r                      = CARDGetStatus(card->chan, work->fileNo, &work->stat);
		if (r == -1) {
			return;
		}
		if (memcmp(card->work->company, card->work->stat.company, 2) == 0
		    && memcmp(card->work->gameName, card->work->stat.gameName, 4) == 0) {
			switch (r) {
				case 0:
					if (strstr(card->work->stat.fileName, card->work->fileName) != NULL) {
						card->work->count++;
					}
					break;
				case -4:
					break;
				default:
					card->work->count = 0;
					fn_80127760(card, r);
					return;
			}
		}
		card->work->fileNo++;
	}
	if (card->work->fileNo == 127) {
		fn_80127884(card);
	}
}
}
