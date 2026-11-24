#include "types.h"

// Card operation step (HYPOTHESIS: opening the save file): when the card is ready (fn_801276A8)
// it polls the pending result if the file is already marked open (bit 1 of 0x20), otherwise
// calls CARDOpen with the work block's file name (0x4) and file handle (0x24). Unless the result
// is CARD_RESULT_BUSY (-1): a success marks the file open, copies the handle's file number to the
// work block's 0x38 and, by the operation kind at 0x18, enters state 6 (kinds 4 and 5) or ends
// with result 2 (fn_80127808); an error goes through fn_80127760.

struct CardFileInfo801271AC {
	s32 chan;
	s32 fileNo;
	s32 offset;
	s32 length;
	u16 iBlock;
};

struct CardWork801271AC {
	u8* buffer;                    // 0x0
	char fileName[0x20];           // 0x4
	CardFileInfo801271AC fileInfo; // 0x24
	s32 fileNo;                    // 0x38
};

struct Card801271AC {
	CardWork801271AC* work; // 0x0
	s32 chan;               // 0x4
	u8 pad8[0x18 - 0x8];
	s32 operation; // 0x18
	s32 result;    // 0x1C
	u32 flags;     // 0x20
};

extern "C" {
s32 CARDGetResultCode(s32 chan);
s32 CARDOpen(s32 chan, const char* fileName, CardFileInfo801271AC* fileInfo);
s32 fn_801276A8(Card801271AC* card);
void fn_80127760(Card801271AC* card, s32 cardResult);
void fn_80127808(Card801271AC* card);
void fn_80127904(Card801271AC* card, s32 state);

void fn_801271AC(Card801271AC* card)
{
	s32 r;

	if (fn_801276A8(card) == 0) {
		if (card->flags & 2) {
			r = CARDGetResultCode(card->chan);
		} else {
			r = CARDOpen(card->chan, card->work->fileName, &card->work->fileInfo);
		}
		if (r != -1) {
			if (r == 0) {
				card->flags |= 2;
				card->work->fileNo = card->work->fileInfo.fileNo;
				switch (card->operation) {
					case 0:
					case 1:
					case 3:
					case 6:
					default:
						card->result = 2;
						fn_80127808(card);
						break;
					case 4:
					case 5:
						fn_80127904(card, 6);
						break;
				}
			} else {
				fn_80127760(card, r);
			}
		}
	}
}
}
