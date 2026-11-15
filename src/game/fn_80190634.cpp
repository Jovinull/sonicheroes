#include "types.h"

extern "C" {
void fn_8017C024(void*, void*, u32, s32);
void* fn_8017BE30(void*, s32, s32);
void* memcpy(void*, const void*, u32);

struct Owner80190634 {
	u8 pad0[0xD4];
	void* data; // 0xD4
	s16 count;  // 0xD8
};

struct Rec80190634 {
	u8 pad0[8];
	u32 flags; // 0x08
	u8 padC[0x10 - 0xC];
	void* data; // 0x10
	s16 count;  // 0x14
	u8 pad16[0xB8 - 0x16];
	u32 flagsB8; // 0xB8
};

void fn_80190634(void* owner, struct Rec80190634* rec, void* src, s32 n)
{
	struct Owner80190634* o = (struct Owner80190634*)owner;

	if (owner == 0 || rec == 0) {
		return;
	}
	fn_8017C024(owner, rec, 0x1000, 0);
	o->data = fn_8017BE30(owner, n, 3);
	memcpy(o->data, src, n * 3);
	rec->data  = o->data;
	o->count   = (s16)n;
	rec->count = (s16)n;
	rec->flagsB8 |= 0x1000;
	rec->flags |= 8;
}
}
