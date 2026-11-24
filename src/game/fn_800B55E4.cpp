// Looks up the entry of a 16-bit id and runs fn_800B5350 on it, returning its result (0 when the
// id has no entry). The id's top nibble picks one of six slots at 0x978 (8 bytes each; nibble 14
// is slot 0, nibbles 1-5 their own slot, 6 and 7 share slot 5, jump table in owned .data) and its
// low byte indexes the slot's 12-byte entries; an index past the slot's count or an entry whose
// byte 0x3 is negative counts as missing. The inline helpers and their parameter widths reproduce
// the retail register use. The jump table starts on a 4-byte boundary (0x8025385C), hence
// data_section_alignment=4. Names and roles are inferred.
#include "types.h"

struct Item800B55E4 {
	u8 pad0[0x3];
	s8 f3; // 0x3
	u8 pad4[0xC - 0x4];
};

struct Slot800B55E4 {
	s32 count;           // 0x0
	Item800B55E4* items; // 0x4
};

struct Obj800B55E4 {
	u8 pad0[0x978];
	Slot800B55E4 slots[6]; // 0x978
};

extern "C" s32 fn_800B5350(Obj800B55E4* o, u16 id, Item800B55E4* item, s32 a, s32 b);

static inline s8 GetSlotIndex800B55E4(u16 id)
{
	switch ((u8)((id & 0xF000) >> 12)) {
		case 14:
			return 0;
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return 4;
		case 5:
			return 5;
		case 6:
			return 5;
		case 7:
			return 5;
		default:
			return -1;
	}
}

static inline Slot800B55E4* GetSlot800B55E4(Obj800B55E4* o, u16 id)
{
	s8 index = GetSlotIndex800B55E4(id);
	if (index < 0) {
		return NULL;
	}
	return &o->slots[index];
}

static inline Item800B55E4* GetItem800B55E4(Obj800B55E4* o, u32 id)
{
	Slot800B55E4* slot = GetSlot800B55E4(o, id);
	u8 index           = id;
	if (slot == NULL) {
		return NULL;
	}
	if (index >= slot->count) {
		return NULL;
	}
	Item800B55E4* item = &slot->items[index];
	if (item->f3 < 0) {
		return NULL;
	}
	return item;
}

extern "C" s32 fn_800B55E4(Obj800B55E4* o, u16 id, s32 a, s32 b)
{
	Item800B55E4* item = GetItem800B55E4(o, id);
	if (item == NULL) {
		return 0;
	}
	return fn_800B5350(o, id, item, a, b);
}
