// Starts a positional entry (HYPOTHESIS: a 3D sound; names inferred): looks up the id's entry like
// fn_800B55E4 (slot from the top nibble, jump table in owned .data; index from the low byte),
// fails with 0 without an entry or a position, starts it with fn_800B5350, and on success sets
// its state word to 5 plus the flags 0x10, 0x40 (unless bit 3 of byte 7 of its data at 0x34 is
// set) and 0x400, stores `b` in bytes 7 and 8, copies the position to 0x20 and `c` to 0x1C.
// Returns 1 when started.
#include "types.h"

struct RwV3d {
	f32 x, y, z;
};

struct Sound800B5118 {
	u8 pad0[0x7];
	s8 f7; // 0x07
	s8 f8; // 0x08
	u8 pad9[0xC - 0x9];
	u32 flags; // 0x0C
	u8 pad10[0x1C - 0x10];
	s32 f1C;   // 0x1C
	RwV3d pos; // 0x20
	u8 pad2C[0x34 - 0x2C];
	u8* f34; // 0x34
};

extern "C" Sound800B5118* fn_800B5350(
    struct Obj800B5118* o, u16 id, struct Item800B5118* item, s32 a, RwV3d* pos);

struct Item800B5118 {
	u8 pad0[0x3];
	s8 f3; // 0x3
	u8 pad4[0xC - 0x4];
};

struct Slot800B5118 {
	s32 count;           // 0x0
	Item800B5118* items; // 0x4
};

struct Obj800B5118 {
	u8 pad0[0x978];
	Slot800B5118 slots[6]; // 0x978
};

static inline s8 GetSlotIndex800B5118(u16 id)
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

static inline Slot800B5118* GetSlot800B5118(Obj800B5118* o, u16 id)
{
	s8 index = GetSlotIndex800B5118(id);
	if (index < 0) {
		return NULL;
	}
	return &o->slots[index];
}

static inline Item800B5118* GetItem800B5118(Obj800B5118* o, u32 id)
{
	Slot800B5118* slot = GetSlot800B5118(o, id);
	u8 index           = id;
	if (slot == NULL) {
		return NULL;
	}
	if (index >= slot->count) {
		return NULL;
	}
	Item800B5118* item = &slot->items[index];
	if (item->f3 < 0) {
		return NULL;
	}
	return item;
}

extern "C" s32 fn_800B5118(Obj800B5118* o, u16 id, RwV3d* pos, s8 b, s32 c)
{
	Item800B5118* item = GetItem800B5118(o, id);
	if (item == NULL) {
		return 0;
	}
	if (pos == NULL) {
		return 0;
	}
	Sound800B5118* sound = fn_800B5350(o, id, item, 0, pos);
	if (sound == NULL) {
		return 0;
	}
	sound->flags = 5;
	if (pos != NULL) {
		sound->flags |= 0x10;
		if (!(sound->f34[7] & 0x8)) {
			sound->flags |= 0x40;
		}
		sound->flags |= 0x400;
	}
	sound->f8 = b;
	sound->f7 = b;
	if (pos != NULL) {
		sound->pos.x = pos->x;
		sound->pos.y = pos->y;
		sound->pos.z = pos->z;
	}
	sound->f1C = c;
	return 1;
}
