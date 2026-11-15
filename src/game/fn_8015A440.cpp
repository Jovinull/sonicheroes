// Copy constructor of the world plugin (offset lbl_8042C918): clears the destination's first three
// words and, when the source's plugin data has an owner (+0xC), hands the owner to fn_8015B8E8.
// Returns the destination. Field names are UNKNOWN.
#include "types.h"

struct Ext8015A440 {
	s32 f0;      // 0x0
	s32 f4;      // 0x4
	s32 f8;      // 0x8
	void* owner; // 0xC
};

extern "C" {
extern s32 lbl_8042C918;
void* fn_8015B8E8(void* object, void* world);

s32 fn_8015A440(s32 dst, s32 src)
{
	s32 off          = lbl_8042C918;
	Ext8015A440* ext = (Ext8015A440*)((u8*)dst + off);
	void* owner;

	ext->f0 = 0;
	owner   = (void*)((s32*)((u8*)src + off))[0xC / 4];
	ext->f4 = 0;
	ext->f8 = 0;
	if (owner != 0) {
		fn_8015B8E8(owner, (void*)dst);
	}
	return dst;
}
}
