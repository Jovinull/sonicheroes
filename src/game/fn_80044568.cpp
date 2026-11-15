// Starts action 0x29 for a player unless it is locked in state 0x3F with flag 0x1000
// (+0x6F6/+0x6F4): sets the flag and state, clears +0x670, and stores the distance (+0x674) and the
// 16-bit heading (+0x672) from the team's leader (players at +0x114 of the team record +0x9B8,
// leader +0x3A) to the player. HYPOTHESIS: a formation "catch up" action; the names are UNKNOWN.
#include "types.h"

struct Vec80044568 {
	f32 x;
	f32 y;
	f32 z;
};

struct Team80044568;

struct Player80044568 {
	u8 pad0[0x670];
	s16 unknown670; // 0x670
	s16 heading;    // 0x672
	f32 distance;   // 0x674
	u8 pad678[0x6F4 - 0x678];
	s16 state; // 0x6F4
	s16 flags; // 0x6F6
	u8 pad6F8[0x708 - 0x6F8];
	Vec80044568 position; // 0x708
	u8 pad714[0x9B8 - 0x714];
	Team80044568* team; // 0x9B8
};

struct Team80044568 {
	u8 pad0[0x3A];
	s8 leader; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player80044568* players[3]; // 0x114
};

extern "C" {
extern f32 lbl_8042D200; // 65536 / (2 pi)
f32 fn_801991B4(Vec80044568* v);
double atan2(double y, double x);

void fn_80044568(Player80044568* p)
{
	if ((p->flags & 0x1000) && p->state == 0x3F) {
		return;
	}
	p->flags |= 0x1000;
	p->state      = 0x29;
	p->unknown670 = 0;
	{
		Vec80044568 leader = p->team->players[p->team->leader]->position;
		Vec80044568 d;

		d.x         = p->position.x - leader.x;
		d.y         = p->position.y - leader.y;
		d.z         = p->position.z - leader.z;
		p->distance = fn_801991B4(&d);
		p->heading  = (s32)(lbl_8042D200 * (f32)atan2(d.z, d.x));
	}
}
}
