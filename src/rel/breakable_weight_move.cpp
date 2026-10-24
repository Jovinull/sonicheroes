#include "types.h"

// The breakable weight's Up and Down (the PS2 build's TObjWeightExt names;
// breakableWeightUp and breakableWeightDown here; the weight's own are
// rel/weight_move.cpp). Unless the game is paused, Up speeds the weight up to
// at most its top speed and raises it; at its top (base plus range) it stops
// there and answers 1. Down speeds it down to at most its fall speed and lowers
// it; at its base it stops there and answers 1. Both answer 0 otherwise.

typedef struct BreakableWeight {
	u8 unk00[0xF0];  // 0x00
	f32 speed;       // 0xF0
	u8 unkF4[0x14];  // 0xF4
	f32 height;      // 0x108
	u8 unk10C[0x10]; // 0x10C
	f32 base;        // 0x11C
	f32 range;       // 0x120
} BreakableWeight;

extern "C" u8* lbl_8042C180;
extern "C" const f32 breakableWeightUpAccel[1];
extern "C" const f32 breakableWeightUpMax[1];
extern "C" const f32 breakableWeightDownAccel[1];
extern "C" const f32 breakableWeightDownMax[1];
extern "C" const f32 breakableWeightZero[1];

extern "C" s32 breakableWeightUp(BreakableWeight* object)
{
	const f32* limit;

	if ((s8)lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	object->speed += breakableWeightUpAccel[0];
	if (object->speed > *(limit = breakableWeightUpMax)) {
		object->speed = *limit;
	}
	object->height += object->speed;
	if (object->height >= object->base + object->range) {
		object->height = object->base + object->range;
		object->speed  = breakableWeightZero[0];
		return 1;
	}
	return 0;
}

extern "C" s32 breakableWeightDown(BreakableWeight* object)
{
	const f32* limit;

	if ((s8)lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	object->speed -= breakableWeightDownAccel[0];
	if (object->speed < *(limit = breakableWeightDownMax)) {
		object->speed = *limit;
	}
	object->height += object->speed;
	if (object->height <= object->base) {
		object->height = object->base;
		object->speed  = breakableWeightZero[0];
		return 1;
	}
	return 0;
}
