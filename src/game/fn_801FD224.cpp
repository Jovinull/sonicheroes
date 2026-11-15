// Reports the slot of one type for an object's plugin data (HYPOTHESIS): the data block is the
// pointer at object + lbl_8042CF48; when its mask (+0xA0) lacks the type bit the result is
// cleared and 0 returned. Otherwise the type's (pointer, value) pair is copied out (types 0x1 to
// 0x100, one bit each), a nonzero override at +0x9C replaces the value, and a set pointer with
// flag 0x40000000 records flags | type in the block's used mask (+0x3C). Returns 1. Names are
// inferred from this function only.
// NonMatching: C++ copies each (pointer, value) pair field by field through r0, while retail loads
// both words before storing them (block copy). The same source compiled with -lang=c is EXACT
// (100/100 words); see fn_8014F854 for the C-boundary evidence.
#include "types.h"

struct Slot801FD224 {
	void* pointer; // 0x0
	u32 value;     // 0x4
};

struct Data801FD224 {
	u8 pad0[0x3C];
	u32 usedMask; // 0x3C
	u8 pad40[0x4C - 0x40];
	Slot801FD224 slot1;   // 0x4C
	Slot801FD224 slot8;   // 0x54
	Slot801FD224 slot10;  // 0x5C
	Slot801FD224 slot4;   // 0x64
	Slot801FD224 slot2;   // 0x6C
	Slot801FD224 slot40;  // 0x74
	Slot801FD224 slot20;  // 0x7C
	Slot801FD224 slot80;  // 0x84
	Slot801FD224 slot100; // 0x8C
	u8 pad94[0x9C - 0x94];
	s32 valueOverride; // 0x9C
	u32 mask;          // 0xA0
};

#define SLOT_801FD224_RECORD_USE 0x40000000

extern "C" {
extern s32 lbl_8042CF48;

s32 fn_801FD224(u8* object, Slot801FD224* out, s32 type, u32 flags)
{
	Data801FD224* data = *(Data801FD224**)(object + lbl_8042CF48);

	if (!(data->mask & type)) {
		out->pointer = 0;
		out->value   = 0;
		return 0;
	}
	switch (type) {
		case 0x1:
			*out = data->slot1;
			break;
		case 0x2:
			*out = data->slot2;
			break;
		case 0x4:
			*out = data->slot4;
			break;
		case 0x8:
			*out = data->slot8;
			break;
		case 0x10:
			*out = data->slot10;
			break;
		case 0x20:
			*out = data->slot20;
			break;
		case 0x40:
			*out = data->slot40;
			break;
		case 0x80:
			*out = data->slot80;
			break;
		case 0x100:
			*out = data->slot100;
			break;
	}
	if (data->valueOverride != 0) {
		out->value = data->valueOverride;
	}
	if (out->pointer != 0 && (flags & SLOT_801FD224_RECORD_USE) == SLOT_801FD224_RECORD_USE) {
		(*(Data801FD224**)(object + lbl_8042CF48))->usedMask |= flags | type;
	}
	return 1;
}
}
