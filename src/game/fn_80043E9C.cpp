#include "types.h"

// Lands the player: returns 0 without doing anything while it is in action
// 0x3F with flag 0x1000; otherwise clears the 0x4C00 bits of its motion block
// (0x760), sets action 0x27, updates the block (fn_800E12FC with 0x720),
// clears flags 0x2500 and returns 1.

struct Player {
	u8 unk000[0x6F0];
	s16 action; // 0x6F0
	u8 unk6F2[0x2];
	s16 currentAction; // 0x6F4
	s16 flags;         // 0x6F6
};

extern "C" void fn_800E12FC(u8* a, u8* b);

extern "C" s32 fn_80043E9C(Player* player)
{
	u8* work   = (u8*)player + 0x720;
	u8* motion = (u8*)player + 0x760;
	if ((player->flags & 0x1000) != 0 && player->currentAction == 0x3F) {
		return 0;
	}

	s16 motionFlags        = *(s16*)(motion + 0x10);
	*(s16*)(motion + 0x10) = motionFlags & ~0x4C00;
	player->action         = 0x27;
	fn_800E12FC(work, motion);
	player->flags &= ~0x2500;
	return 1;
}
