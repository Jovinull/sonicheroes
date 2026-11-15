// Moves two vectors along the vector at +0x80 of `source`: `a` (its vector at +0x18) by three
// times it, and the x/z components of `b` by twice it. The roles of the three records are
// UNKNOWN (HYPOTHESIS: a position and a camera/target point pushed by a velocity).
#include "types.h"

struct Vec800E6844 {
	f32 x;
	f32 y;
	f32 z;
};

struct A800E6844 {
	u8 pad0[0x18];
	Vec800E6844 v; // 0x18
};

struct Source800E6844 {
	u8 pad0[0x80];
	Vec800E6844 v; // 0x80
};

extern "C" {
extern const f32 lbl_8042E26C; // 2.0f
extern const f32 lbl_8042E2C4; // 3.0f

void fn_800E6844(A800E6844* a, Vec800E6844* b, Source800E6844* source)
{
	a->v.x += lbl_8042E2C4 * source->v.x;
	a->v.y += lbl_8042E2C4 * source->v.y;
	a->v.z += lbl_8042E2C4 * source->v.z;
	b->x += lbl_8042E26C * source->v.x;
	b->z += lbl_8042E26C * source->v.z;
}
}
