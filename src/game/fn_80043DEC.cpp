// Starts action 0x27 for a player unless it is locked in state 0x3F with flag 0x1000
// (+0x6F6/+0x6F4): clears flags 0x4C00 of +0x770, sets the action (+0x6F0), runs fn_800E12FC on the
// records at +0x720 and +0x760 and clears flags 0x2500 of +0x6F6; then sets flag 0x200 of +0x770
// and returns 1. Returns 0 when locked. HYPOTHESIS: a forced landing/fall action; the names are
// UNKNOWN.
#include "types.h"

struct Info80043DEC {
	u8 pad0[0x10];
	s16 flags; // 0x10 (player +0x770)
};

struct Player80043DEC {
	u8 pad0[0x6F0];
	s16 action; // 0x6F0
	u8 pad6F2[2];
	s16 state; // 0x6F4
	s16 flags; // 0x6F6
	u8 pad6F8[0x720 - 0x6F8];
	u8 motion[0x40];   // 0x720
	Info80043DEC info; // 0x760
};

extern "C" void fn_800E12FC(void* motion, Info80043DEC* info);

static inline s32 StartAction(Player80043DEC* p, void* motion, Info80043DEC* info)
{
	if ((p->flags & 0x1000) && p->state == 0x3F) {
		return 0;
	}
	info->flags &= ~0x4C00;
	p->action = 0x27;
	fn_800E12FC(motion, info);
	p->flags &= ~0x2500;
	return 1;
}

extern "C" s32 fn_80043DEC(Player80043DEC* p)
{
	void* motion       = p->motion;
	Info80043DEC* info = &p->info;

	if (!StartAction(p, motion, info)) {
		return 0;
	}
	p->info.flags |= 0x200;
	return 1;
}
