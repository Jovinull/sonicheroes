#include "types.h"

// Flags the player (bit 4 of 0x6F6) and, the first time (bit 0x800 of 0x770),
// starts its 60-frame timer, reports event 0x2F to its team (fn_80090C70) and
// plays voice 0x1B for its character and player number.

struct Player {
	u8 unk000[0x6AC];
	s32 timer; // 0x6AC
	u8 unk6B0[0x46];
	s16 flags6F6; // 0x6F6
	u8 unk6F8[0x68];
	s8 playerNo;  // 0x760
	s8 character; // 0x761
	u8 unk762[0xE];
	s16 flags770; // 0x770
	u8 unk772[0x246];
	s32 team;    // 0x9B8
	s8 unk9BC;   // 0x9BC
	s8 teamSlot; // 0x9BD
};

extern "C" void fn_80090C70(s32 team, s32 slot, s32 event);
extern "C" void fn_80137D0C(s32 voice, s32 character, s32 player);

extern "C" void fn_800484A4(Player* player)
{
	s16 flags;

	player->flags6F6 |= 4;
	flags = player->flags770;
	if ((flags & 0x800) == 0) {
		player->flags770 = flags | 0x800;
		player->timer    = 0x3C;
		fn_80090C70(player->team, player->teamSlot, 0x2F);
		fn_80137D0C(0x1B, player->character, player->playerNo);
	}
}
