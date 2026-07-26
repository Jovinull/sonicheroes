#include "types.h"

// Rebuilds the three emitters that mark the current selection.
//
// The translation unit is the single function fn_1_922C, .text 0x922C to
// 0x92D0. The table of offsets it reads sits at .rodata 0xCD8 with three rows
// of a Vec3 per selection; it is named rather than written out, so this unit
// claims no .rodata of its own.
//
// It is the same shape as fn_1_F38C in choice_widget.c, with two differences
// the original has: the release is inline here rather than through a helper,
// and each emitter is given a count of one instead of three.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Emitter {
	s32 frame;   // 0x00
	Vec3 offset; // 0x04
	s32 count;   // 0x10
} Emitter;

typedef struct Selection {
	u8 unk0[0x228]; // 0x000
	s32 index;      // 0x228
	u8 unk22C[0x4]; // 0x22C
	void* marker;   // 0x230
} Selection;

extern "C" const Vec3 lbl_1_rodata_CD8[][3];

extern "C" void fn_8001867C(void* marker);
extern "C" void fn_1_5994(Vec3* dst, const Vec3* src);
extern "C" void fn_1_63A8(void* marker, Emitter* emitter);
extern "C" void fn_1_6ABC(Emitter* emitter);

extern "C" void fn_1_922C(Selection* selection)
{
	Emitter emitter;
	s32 i;

	if (selection->marker != NULL) {
		fn_8001867C(selection->marker);
		for (i = 0; i != 3; i++) {
			fn_1_6ABC(&emitter);
			emitter.frame = i + selection->index * 3;
			fn_1_5994(&emitter.offset, &lbl_1_rodata_CD8[selection->index][i]);
			emitter.count = 1;
			fn_1_63A8(selection->marker, &emitter);
		}
	}
}
