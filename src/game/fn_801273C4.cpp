// Memory card step: unless fn_801276A8 handles it, reads the channel's result code and, while it
// is not busy (-1), records in bit 0 of word 0x20 whether it was ready, no card (-6) or wrong
// device (-13). Ready and no-card go to state 4, wrong device in mode 1 (word 0x18) to state 7,
// anything else to fn_80127760 with the code.
#include "types.h"

extern "C" s32 CARDGetResultCode(s32 chan);

struct Card801273C4 {
	unsigned char pad0[0x4];
	int chan;
	unsigned char pad8[0x10];
	int mode; // 0x18
	unsigned char pad1C[0x4];
	unsigned int flags; // 0x20
};

extern "C" {
int fn_801276A8(Card801273C4* c);
void fn_80127904(Card801273C4* c, int state);
void fn_80127760(Card801273C4* c, s32 result);

void fn_801273C4(Card801273C4* c)
{
	s32 result;
	if (fn_801276A8(c) != 0) {
		return;
	}
	result = CARDGetResultCode(c->chan);
	if (result == -1) {
		return;
	}
	switch (result) {
		case 0:
		case -6:
		case -13:
			c->flags |= 1;
			break;
		default:
			c->flags &= ~1;
			break;
	}
	if (result == 0 || result == -6) {
		fn_80127904(c, 4);
	} else if (c->mode == 1 && result == -13) {
		fn_80127904(c, 7);
	} else {
		fn_80127760(c, result);
	}
}
}
