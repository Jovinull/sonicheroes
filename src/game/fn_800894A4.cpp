#include "types.h"

struct Entry800894A4 {
	u8 pad0[0xC];
	s32 kind; // 0xC
};

struct Member800894A4 {
	u8 pad0[0x628];
	s32 state; // 0x628
};

struct Team800894A4 {
	u8 pad0[0x34];
	s32 variant; // 0x34
	u8 pad38[0x2];
	s8 self; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Member800894A4* members[4]; // 0x114
	u8 pad124[0x140 - 0x124];
	s32 group; // 0x140
};

struct Obj800894A4 {
	u8 pad0[0x9B0];
	s32 f9B0;
	u8 pad9B4[4];
	Team800894A4* team; // 0x9B8
};

extern "C" {
extern Entry800894A4 lbl_8024E440[][4][2];

s32 fn_800894A4(Obj800894A4* obj)
{
	Team800894A4* team = obj->team;
	Entry800894A4* entry;
	s32 level;

	if (team->members[team->self] == (Member800894A4*)obj) {
		return 0;
	}
	level = obj->f9B0;
	if (level == 0) {
		level = 1;
	}
	level--;
	entry = &lbl_8024E440[team->group][team->variant][level];
	if (entry->kind == 3) {
		return 6;
	}
	return 4;
}
}
