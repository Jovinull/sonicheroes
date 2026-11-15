#include "types.h"

struct Player8008A510 {
	u8 pad0[0x6F6];
	s16 flags6F6; // 0x6F6
	u8 pad6F8[0x708 - 0x6F8];
	f32 posX; // 0x708
	f32 posY; // 0x70C
	f32 posZ; // 0x710
	u8 pad714[0x720 - 0x714];
	f32 velX; // 0x720
	f32 velY; // 0x724
	f32 velZ; // 0x728
	u8 pad72C[0x760 - 0x72C];
	s8 playerNo; // 0x760
	u8 pad761[0x7CC - 0x761];
	f32 v0a; // 0x7CC
	f32 v0b; // 0x7D0
	f32 v0c; // 0x7D4
	f32 v1a; // 0x7D8
	f32 v1b; // 0x7DC
	f32 v1c; // 0x7E0
};

extern "C" {
extern void* lbl_802AD070[];
extern f32 lbl_8042D878;

void fn_8003E3BC(void*, s32, f32, f32, f32);

void fn_8008A510(Player8008A510* p)
{
	s32 player;

	p->posX += p->velX;
	p->posY += p->velY;
	p->posZ += p->velZ;
	player = p->playerNo;
	fn_8003E3BC((u8*)lbl_802AD070[player] + 0x28, player, p->posX, p->posY, p->posZ);
	p->v1a = p->v1b = p->v1c = p->v0a = p->v0b = p->v0c = lbl_8042D878;
	p->flags6F6                                         = p->flags6F6 & ~1;
}
}
