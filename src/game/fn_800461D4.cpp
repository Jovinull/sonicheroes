#include "game/rw_types.h"

// Ends a player's jump (HYPOTHESIS: the landing check of action 0xE): returns 0 while the action
// control bits (+0x6F6 & 3) are set, else 1 with a new action (+0x6F0). A player in action 0xE
// standing still (+0x60 at least +0xEC, no movement +0x6C) with its velocity (+0x78) not against
// gravity (lbl_80242B38; below lbl_8042D24C), outside formations 2/3 (+0x258 then +0x140),
// without flags 0x100000 (+0x94) and 0x8000 (+0x20), state +0x14 or a type-0x23 hit
// (fn_80020BD8), and with its ground height (+0x240/+0x23C) within lbl_8042D254 of its position
// (+0x70C) along the vertical gravity, goes to action 5 (fn_800E12FC, fn_8003E2E4, fn_80137D0C
// with sound 8) unless flag 2 (+0x22C) is set. Otherwise action 2 with control flag 0x100, else
// action 4 with the record mode +0x14E 0xD (0x41 in formations 2/3 without flag 0x8000).

struct Gravity800461D4 {
	RwV3d direction; // 0x0
	u8 padC[0x10 - 0xC];
};

struct Team800461D4 {
	u8 pad0[0x140];
	s32 formation; // 0x140
};

struct Record800461D4 {
	s8 number; // 0x0
	s8 player; // 0x1 (HYPOTHESIS: the team-local player index)
	u8 pad2[0x14 - 0x2];
	s16 state; // 0x14
	u8 pad16[0x18 - 0x16];
	s16 unknown18; // 0x18
	u8 pad1A[0x20 - 0x1A];
	s32 flags; // 0x20
	u8 pad24[0x60 - 0x24];
	f32 speed; // 0x60
	u8 pad64[0x6C - 0x64];
	RwV3d movement; // 0x6C
	RwV3d velocity; // 0x78
	u8 pad84[0x94 - 0x84];
	u32 attributes; // 0x94
	u8 pad98[0xEC - 0x98];
	f32 speedLimit; // 0xEC
	u8 padF0[0x14E - 0xF0];
	s16 mode; // 0x14E
	u8 pad150[0x22C - 0x150];
	u32 wallFlags; // 0x22C
	u8 pad230[0x23C - 0x230];
	f32 ceiling; // 0x23C
	f32 ground;  // 0x240
	u8 pad244[0x258 - 0x244];
	Team800461D4* team; // 0x258
};

struct Hit800461D4 {
	u8 pad0[0x4];
	void* object; // 0x4
};

struct Player800461D4 {
	u8 pad0[0x28];
	u8 colli[0x6F0 - 0x28]; // 0x28
	s16 action;             // 0x6F0
	u8 pad6F2[0x6F6 - 0x6F2];
	s16 control; // 0x6F6
	u8 pad6F8[0x6FC - 0x6F8];
	s32 angle[3];   // 0x6FC
	RwV3d position; // 0x708
	u8 pad714[0x720 - 0x714];
	u8 motion[0x760 - 0x720]; // 0x720
	Record800461D4 record;    // 0x760
};

extern "C" {
extern Gravity800461D4 lbl_80242B38;
extern const f32 lbl_8042D1BC; // 0.0f
extern const f32 lbl_8042D24C;
extern const f32 lbl_8042D250;
extern const f32 lbl_8042D254;
extern const f32 lbl_8042D258;
f32 fn_801991B4(RwV3d* v);
Hit800461D4* fn_80020BD8(void* colli, s32 type);
void fn_800E12FC(void* motion, Record800461D4* record);
void fn_8003E2E4(s32 number, s32 unknown, RwV3d* position, s32* angle);
void fn_80137D0C(s32 sound, s32 player, s32 number);
}

static inline void* HitObject(Hit800461D4* hit)
{
	return hit != NULL ? hit->object : NULL;
}

extern "C" s32 fn_800461D4(Player800461D4* player)
{
	void* motion           = player->motion;
	Record800461D4* record = &player->record;

	if (!(player->control & 3)) {
		if (!(record->attributes & 0x100000) && player->action == 0xE && record->state == 0
		    && record->velocity.z * lbl_80242B38.direction.z
		            + (record->velocity.x * lbl_80242B38.direction.x
		                + record->velocity.y * lbl_80242B38.direction.y)
		        < lbl_8042D24C
		    && record->speed >= record->speedLimit && lbl_8042D1BC == fn_801991B4(&record->movement)
		    && record->team->formation != 2 && record->team->formation != 3
		    && !(record->flags & 0x8000) && HitObject(fn_80020BD8(player->colli, 0x23)) == NULL) {
			f32 up = lbl_80242B38.direction.y;
			if (((up < lbl_8042D250 && record->ground <= player->position.y - lbl_8042D254)
			        || (up > lbl_8042D258 && record->ceiling >= lbl_8042D254 + player->position.y))
			    && !(record->wallFlags & 2)) {
				player->action = 5;
				record->mode   = 0x33;
				fn_800E12FC(motion, record);
				fn_8003E2E4(record->number, 2, &player->position, player->angle);
				record->unknown18 = 0;
				fn_80137D0C(8, record->player, record->number);
				return 1;
			}
			goto idle;
		}
		if (player->control & 0x100) {
			player->action = 2;
			return 1;
		}
	idle:
		player->action = 4;
		if (record->flags & 0x8000) {
			record->mode = 0xD;
		} else if (record->team->formation == 2 || record->team->formation == 3) {
			record->mode = 0x41;
		} else {
			record->mode = 0xD;
		}
		return 1;
	}
	return 0;
}
