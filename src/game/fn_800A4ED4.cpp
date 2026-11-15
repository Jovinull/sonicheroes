// Blends the vector at +0x158 of an object toward `target`: v = v * w + target * (1 - w), with the
// weight w at +0x1BC (re-read for each component, as the retail code does after every store).
// Field roles are UNKNOWN (HYPOTHESIS: a smoothed position or direction of an enemy).
#include "types.h"

struct Vec800A4ED4 {
	f32 x;
	f32 y;
	f32 z;
};

struct Obj800A4ED4 {
	u8 pad0[0x158];
	Vec800A4ED4 value; // 0x158
	u8 pad164[0x1BC - 0x164];
	f32 weight; // 0x1BC
};

extern "C" {
extern f32 lbl_8042DA9C; // 1.0f

void fn_800A4ED4(Obj800A4ED4* obj, Vec800A4ED4* target)
{
	f32 rest = lbl_8042DA9C - obj->weight;

	obj->value.x = obj->value.x * obj->weight + target->x * rest;
	obj->value.y = obj->value.y * obj->weight + target->y * rest;
	obj->value.z = obj->value.z * obj->weight + target->z * rest;
}
}
