#include "types.h"

struct Member80090E00 {
	u8 pad0[0x6F0];
	s16 state; // 0x6F0
};

struct Team80090E00 {
	u8 pad0[0x114];
	Member80090E00* members[3]; // 0x114, 0x118, 0x11C
};

extern "C" {
s32 fn_80090E00(Team80090E00* team)
{
	s32 count = 0;
	s32 i;

	for (i = 0; i < 3; i++) {
		if (team->members[i] != 0 && team->members[i]->state == 0x27) {
			count += 1;
		}
	}
	return count;
}
}
