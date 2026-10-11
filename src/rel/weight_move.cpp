#include "types.h"

// TObjWeight's Up and Down (the PS2 build's names; weightUp and weightDown
// here). Unless the game is paused, Up speeds the weight up by weightUpAccel to
// at most weightUpMax and raises it; at its top (base plus range) it stops
// there and answers 1. Down speeds it down by weightDownAccel to at most
// weightDownMax and lowers it; at its base it stops there and answers 1. Both
// answer 0 otherwise.

typedef struct Weight {
	u8 unk00[0xD4]; // 0x00
	f32 speed;      // 0xD4
	u8 unkD8[0x10]; // 0xD8
	f32 height;     // 0xE8
	u8 unkEC[0x10]; // 0xEC
	f32 base;       // 0xFC
	f32 range;      // 0x100
} Weight;

extern "C" u8* lbl_8042C180;
extern "C" f32 weightUpMax;
extern "C" f32 weightDownMax;
extern "C" f32 weightUpAccel;
extern "C" f32 weightDownAccel;
extern "C" const f32 weightZero[1];

extern "C" s32 weightUp(Weight* object)
{
	if ((s8)lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	object->speed += weightUpAccel;
	if (object->speed > weightUpMax) {
		object->speed = weightUpMax;
	}
	object->height += object->speed;
	if (object->height >= object->base + object->range) {
		object->height = object->base + object->range;
		object->speed  = weightZero[0];
		return 1;
	}
	return 0;
}

extern "C" s32 weightDown(Weight* object)
{
	if ((s8)lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	object->speed -= weightDownAccel;
	if (object->speed < -weightDownMax) {
		object->speed = -weightDownMax;
	}
	object->height += object->speed;
	if (object->height <= object->base) {
		object->height = object->base;
		object->speed  = weightZero[0];
		return 1;
	}
	return 0;
}
