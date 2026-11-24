#include "types.h"

// Card operation step (HYPOTHESIS: waiting for CARDCreate): when the card is ready (fn_801276A8)
// and the result code is not CARD_RESULT_BUSY (-1), a success enters state 6, marks the file open
// (bit 1 of 0x20) and copies the work block's word 0x28 to 0x38; EXIST (-7) ends with result 10,
// NOENT/INSSPACE (-8/-9) with 7 and NAMETOOLONG (-12) with 2 (fn_80127808); any other error goes
// through fn_80127760.

struct CardWork80126F14 {
	u8 pad0[0x28];
	s32 f28; // 0x28
	u8 pad2C[0x38 - 0x2C];
	s32 f38; // 0x38
};

struct Card80126F14 {
	CardWork80126F14* work; // 0x0
	s32 chan;               // 0x4
	u8 pad8[0x1C - 0x8];
	s32 result; // 0x1C
	u32 flags;  // 0x20
};

extern "C" {
s32 CARDGetResultCode(s32 chan);
s32 fn_801276A8(Card80126F14* card);
void fn_80127760(Card80126F14* card, s32 cardResult);
void fn_80127808(Card80126F14* card);
void fn_80127904(Card80126F14* card, s32 state);

void fn_80126F14(Card80126F14* card)
{
	s32 r;

	if (fn_801276A8(card) == 0) {
		r = CARDGetResultCode(card->chan);
		if (r != -1) {
			if (r == 0) {
				fn_80127904(card, 6);
				card->flags |= 2;
				card->work->f38 = card->work->f28;
				return;
			}
			switch (r) {
				case -7:
					card->result = 10;
					fn_80127808(card);
					break;
				case -8:
				case -9:
					card->result = 7;
					fn_80127808(card);
					break;
				case -12:
					card->result = 2;
					fn_80127808(card);
					break;
				default:
					fn_80127760(card, r);
					break;
			}
		}
	}
}
}
