// Keeps an enemy within a circle around its home point (+0x1C0) in the x/z plane: with a radius
// below 0 (lbl_8042DAD0 is -0.0) the enemy's own (+0x210) is used; returns 0 while the enemy
// (+0x140) is inside, otherwise pulls it back onto the circle (x and z only) and returns 1.
// HYPOTHESIS: territory clamping.
#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct Enemy800A5888 {
	u8 pad0[0x140];
	RwV3d position; // 0x140
	u8 pad14C[0x1C0 - 0x14C];
	RwV3d home; // 0x1C0
	u8 pad1CC[0x210 - 0x1CC];
	f32 radius; // 0x210
};

extern "C" {
extern f32 lbl_8042DAD0;
extern f32 lbl_8042DA74; // 0.0f
f32 fn_801991B4(RwV3d* v);
void fn_801990E0(RwV3d* out, const RwV3d* in);

s32 fn_800A5888(Enemy800A5888* e, f32 radius)
{
	if (radius < lbl_8042DAD0) {
		radius = e->radius;
	}
	RwV3d d = e->position;

	d.x -= e->home.x;
	d.y -= e->home.y;
	d.z -= e->home.z;
	d.y = lbl_8042DA74;
	if (fn_801991B4(&d) < radius) {
		return 0;
	}
	fn_801990E0(&d, &d);
	d.x *= radius;
	d.z *= radius;
	d.x += e->home.x;
	d.y += e->home.y;
	d.z += e->home.z;
	e->position.x = d.x;
	e->position.z = d.z;
	return 1;
}
}
