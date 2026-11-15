// Builds a 2D transform from a sprite's placement (HYPOTHESIS; names inferred): rotation by the
// angle at 0x8 in the upper-left 2x2 block (first row scaled by the factor at 0x14) and the
// position at 0xC/0x10 as translation. Only these matrix words are written.
#include "types.h"

struct Placement8011C01C {
	u8 pad0[0x8];
	f32 angle; // 0x8
	f32 x;     // 0xC
	f32 y;     // 0x10
	f32 scale; // 0x14
};

struct Transform8011C01C {
	f32 m00; // 0x0
	f32 m01; // 0x4
	u8 pad8[0x10 - 0x8];
	f32 m10; // 0x10
	f32 m11; // 0x14
	u8 pad18[0x30 - 0x18];
	f32 tx; // 0x30
	f32 ty; // 0x34
};

extern "C" {
double cos(double x);
double sin(double x);

void fn_8011C01C(Transform8011C01C* out, Placement8011C01C* placement)
{
	out->m00 = cos(placement->angle);
	out->m01 = -sin(placement->angle);
	out->m10 = sin(placement->angle);
	out->m11 = cos(placement->angle);
	out->m00 *= placement->scale;
	out->m01 *= placement->scale;
	out->tx = placement->x;
	out->ty = placement->y;
}
}
