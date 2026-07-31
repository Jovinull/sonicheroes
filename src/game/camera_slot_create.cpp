#include "types.h"

// Allocates one entry of the table at 0x803EC350 from the game heap, fills it
// from a caller-supplied parameter block and publishes it in the table.
//
// The claim is .text 0x8013A49C to 0x8013A5F0, extab 0x8000BA88 to 0x8000BA90
// and extabindex 0x80011AAC to 0x80011AB8. It is a fragment, not a translation
// unit: the .sdata2 run at 0x8042F168 is a single constant pool shared with
// fn_80139FC4 ahead of it, and both reach the same table, so the two are one
// original file. Only this half is reconstructed here.
//
// The size argument selects between the two heap entry points rather than being
// passed through: negative asks for the default block, and any other value asks
// for that many bytes. Both are asked for tag 0x1A.
//
// The object sits 0x14 past the allocation. The three float fields at 0x48,
// 0x4C and 0x50 are written twice: once by the straight copy out of the
// parameter block, then again from fields the copy just wrote, which is why the
// entry is read back out of the table for each of them instead of being kept in
// a register.
//
// That second pass is the shape of the unit. All three values are read before
// the first of the three stores, because a store through the table entry could
// reach the object they are read from, and they are read in the reverse of the
// order they are written. Three plain locals produce the reads in write order
// instead, in every one of the six declaration orders, under GC/1.3 through
// GC/2.7 and under each -opt schedule and peephole combination. Sequencing the
// two later reads inside the first store's expression is what puts them in the
// order the original has, and it is why the assignment below is written as one
// expression rather than split.
//
// The 0.0f is the only constant the unit owns. Its four bytes were part of an
// eight byte lbl_8042F190 because nothing referenced the second half; that
// symbol is now two four byte entries so this fragment can claim just its own.

typedef struct Params {
	s32 unk00; // 0x00
	f32 unk04; // 0x04
	f32 unk08; // 0x08
	s32 unk0C; // 0x0C
	u8 unk10;  // 0x10
	u8 unk11;  // 0x11
	u8 pad12[2];
	f32 unk14; // 0x14
	f32 unk18; // 0x18
	s32 unk1C; // 0x1C
	f32 unk20; // 0x20
	f32 unk24; // 0x24
	f32 unk28; // 0x28
	s32 unk2C; // 0x2C
} Params;      // 0x30

typedef struct Slot {
	s32 unk00; // 0x00
	u8 unk04[0x24];
	s32 unk28; // 0x28
	f32 unk2C; // 0x2C
	f32 unk30; // 0x30
	s32 unk34; // 0x34
	u8 unk38;  // 0x38
	u8 unk39;  // 0x39
	u8 pad3A[2];
	f32 unk3C; // 0x3C
	f32 unk40; // 0x40
	s32 unk44; // 0x44
	f32 unk48; // 0x48
	f32 unk4C; // 0x4C
	f32 unk50; // 0x50
	s32 unk54; // 0x54
} Slot;

extern "C" void* lbl_8042C1F8;
extern "C" Slot* lbl_803EC350[];
extern "C" f32 lbl_8042C800;

extern "C" void* fn_8004E2AC(void* heap, s32 tag);
extern "C" void* fn_8004E408(void* heap, s32 size, s32 tag);
extern "C" s32 fn_8004E608(void* heap);
extern "C" void fn_8004DEC0(void* heap, s32 arg, s32 value);

extern "C" s32 cameraSlotCreate(s32 index, Params* params, s32 size)
{
	void* block;
	Slot* slot;

	if (size < 0) {
		block = fn_8004E2AC(lbl_8042C1F8, 0x1A);
	} else {
		block = fn_8004E408(lbl_8042C1F8, size, 0x1A);
	}

	if (block == NULL) {
		return 0;
	}

	fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), params->unk0C);

	slot = (Slot*)((u8*)block + 0x14);

	slot->unk28 = params->unk00;
	slot->unk2C = params->unk04;
	slot->unk30 = params->unk08;
	slot->unk34 = params->unk0C;
	slot->unk38 = params->unk10;
	slot->unk39 = params->unk11;
	slot->unk3C = params->unk14;
	slot->unk40 = params->unk18;
	slot->unk44 = params->unk1C;
	slot->unk48 = params->unk20;
	slot->unk4C = params->unk24;
	slot->unk50 = params->unk28;
	slot->unk54 = params->unk2C;

	slot->unk00 = 0;

	lbl_803EC350[index] = slot;

	f32 b;
	f32 c;

	lbl_803EC350[index]->unk48 = (c = slot->unk3C, b = slot->unk2C, slot->unk30);
	lbl_803EC350[index]->unk4C = b;
	lbl_803EC350[index]->unk50 = c;
	lbl_803EC350[index]->unk54 = 30;

	lbl_8042C800 = 0.0f;

	return 1;
}
