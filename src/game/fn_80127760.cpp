#include "types.h"

// Translates a Dolphin CARD_RESULT_* code into the memory card menu result stored at 0x1C, then
// calls fn_80127808 on the card controller. The CARD_RESULT names are the Dolphin SDK values; the
// meaning of the menu results is UNKNOWN.

struct Card80127760 {
	u8 pad0[0x1C];
	s32 result; // 0x1C
};

extern "C" {
void fn_80127808(Card80127760* card);

void fn_80127760(Card80127760* card, s32 cardResult)
{
	s32 result;

	switch (cardResult) {
		case -128: // CARD_RESULT_FATAL_ERROR
		case -10:  // CARD_RESULT_NOPERM
			result = 2;
			break;
		case -2: // CARD_RESULT_WRONGDEVICE
			result = 4;
			break;
		case -3: // CARD_RESULT_NOCARD
			result = 3;
			break;
		case -5: // CARD_RESULT_IOERROR
		case -6: // CARD_RESULT_BROKEN
			result = 5;
			break;
		case -13: // CARD_RESULT_ENCODING
			result = 12;
			break;
		case -4: // CARD_RESULT_NOFILE
			result = 9;
			break;
		default:
			result = 2;
			break;
	}
	card->result = result;
	fn_80127808(card);
}
}
