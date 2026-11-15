#include "types.h"

struct Rec8015B8E8 {
	u8 pad0[0x4];
	void* f4; // 0x4
};

struct Ext8015B8E8 {
	s32 f0;      // 0x0
	s32 f4;      // 0x4
	s32 f8;      // 0x8
	void* owner; // 0xC
};

extern "C" {
extern s32 lbl_8042C918;
void fn_8019E880(void* h);

void* fn_8015B8E8(void* owner, Rec8015B8E8* rec)
{
	Ext8015B8E8* ext = (Ext8015B8E8*)((u8*)rec + lbl_8042C918);
	if (rec->f4 != 0) {
		fn_8019E880(rec->f4);
	}
	ext->owner = owner;
	return owner;
}
}
