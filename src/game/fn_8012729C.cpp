#include "types.h"

// Card operation step (HYPOTHESIS: waiting for the card check/mount result): when the card is
// ready (fn_801276A8) and the result code is not CARD_RESULT_BUSY (-1), a success picks the next
// state from the operation kind at 0x18 (jump table, owned .data): kind 0 ends with result 2
// (fn_80127808), the others enter states 7, 8, 9, 5, 12 or 14 (fn_80127904). CARD_RESULT_BROKEN
// (-6) enters state 7 for kind 1 and otherwise ends with result 6; any other error goes through
// fn_80127760.

struct Card8012729C {
	u8 pad0[0x4];
	s32 chan; // 0x4
	u8 pad8[0x18 - 0x8];
	s32 operation; // 0x18
	s32 result;    // 0x1C
};

extern "C" {
s32 CARDGetResultCode(s32 chan);
s32 fn_801276A8(Card8012729C* card);
void fn_80127760(Card8012729C* card, s32 cardResult);
void fn_80127808(Card8012729C* card);
void fn_80127904(Card8012729C* card, s32 state);

void fn_8012729C(Card8012729C* card)
{
	s32 r;

	if (fn_801276A8(card) == 0) {
		r = CARDGetResultCode(card->chan);
		if (r != -1) {
			if (r == 0) {
				switch (card->operation) {
					case 0:
						card->result = 2;
						fn_80127808(card);
						break;
					case 1:
						fn_80127904(card, 7);
						break;
					case 6:
						fn_80127904(card, 12);
						break;
					case 4:
					case 5:
						fn_80127904(card, 5);
						break;
					case 2:
						fn_80127904(card, 8);
						break;
					case 3:
						fn_80127904(card, 9);
						break;
					case 7:
						fn_80127904(card, 14);
						break;
				}
			} else if (r == -6) {
				if (card->operation == 1) {
					fn_80127904(card, 7);
				} else {
					card->result = 6;
					fn_80127808(card);
				}
			} else {
				fn_80127760(card, r);
			}
		}
	}
}
}
