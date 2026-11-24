#include "types.h"

// Starts card command 3 (fn_80127A78) when no request is pending: on success marks the request
// pending (0x14), stores the argument (0x18) and sets the flag at 0x1C; returns 1 when it started.
// Names and roles are inferred.

struct Card801281AC {
	u8 pad0[0x14];
	s32 pending; // 0x14
	s32 arg;     // 0x18
	s32 f1C;     // 0x1C
};

extern "C" {
s32 fn_80127A78(Card801281AC* card, s32 command);

s32 fn_801281AC(Card801281AC* card, s32 arg)
{
	if (card->pending == 0 && fn_80127A78(card, 3) != 0) {
		card->pending = 1;
		card->arg     = arg;
		card->f1C     = 1;
		return 1;
	}
	return 0;
}
}
