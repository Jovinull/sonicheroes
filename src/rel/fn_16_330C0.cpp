#include "types.h"

typedef struct S330C0Info {
	u8 unk00[0xD];
	u8 mode; // 0xD
} S330C0Info;

typedef struct S330C0Base {
	u8 unk00[0x2C];
	S330C0Info* info; // 0x2C
} S330C0Base;

typedef struct S330C0 {
	u8 unk00[0x28];
	S330C0Base* base; // 0x28
	u8 unk2C[4];
	u8 colli[1]; // 0x30
} S330C0;

extern "C" u8 lbl_8042C1A4[];
extern "C" void fn_80021824(void* collision);
extern "C" u32 fn_16_D10(void* collision);
extern "C" void fn_16_D98(u32 colli);
extern "C" s32 fn_16_D80(u32 team);
extern "C" s32 fn_16_33178(void* collision);
extern "C" s32 fn_80041B64();
extern "C" u32 fn_800924E4(s32 player);

extern "C" s32 fn_16_330C0(S330C0* object)
{
	S330C0Info* info = object->base->info;
	u32 hit;
	s32 player;
	u32 team;

	if (info->mode == 1) {
		fn_80021824(lbl_8042C1A4);
		while ((hit = fn_16_D10(object->colli)) != 0) {
			fn_16_D98(hit);
			player = fn_80041B64();
			team   = fn_800924E4(player);
			if (team != 0 && player == fn_16_D80(team)) {
				return 1;
			}
		}
	} else {
		return fn_16_33178(object->colli);
	}
	return 0;
}
