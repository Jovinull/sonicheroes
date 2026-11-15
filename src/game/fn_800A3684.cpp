// Moves an enemy by its velocity (+0x158): gravity (+0x1A8) is added to the vertical speed unless
// it is grounded (flag 0x2 of +0x106; then 0), the horizontal speed is capped at +0x1B8, the
// vertical speed floored at +0x1B4, and the position (+0x140) is moved toward the target point
// (+0x1C0) by the vertical speed's magnitude (AdjustPoint). When the point is reached the velocity
// is cleared and 1 is returned. HYPOTHESIS: the field roles.
#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct Enemy800A3684 {
	u8 pad0[0x106];
	u16 flags106; // 0x106
	u8 pad108[0x140 - 0x108];
	RwV3d position; // 0x140
	u8 pad14C[0x158 - 0x14C];
	RwV3d velocity; // 0x158
	u8 pad164[0x1A8 - 0x164];
	f32 gravity; // 0x1A8
	u8 pad1AC[0x1B4 - 0x1AC];
	f32 minFall;  // 0x1B4
	f32 maxSpeed; // 0x1B8
	u8 pad1BC[0x1C0 - 0x1BC];
	RwV3d target; // 0x1C0
};

s32 AdjustPoint(RwV3d* point, const RwV3d* target, f32 step);

extern "C" {
extern f32 lbl_8042DA74; // 0.0f
extern double __fabs(double x);
f32 fn_801991B4(RwV3d* v);
void fn_801990E0(RwV3d* out, const RwV3d* in);

s32 fn_800A3684(Enemy800A3684* e)
{
	s32 reached = 0;

	if (!(e->flags106 & 2)) {
		e->velocity.y += e->gravity;
	} else {
		e->velocity.y = lbl_8042DA74;
	}
	{
		RwV3d h = e->velocity;

		h.y = lbl_8042DA74;
		if (fn_801991B4(&h) > e->maxSpeed) {
			fn_801990E0(&h, &h);
			h.x *= e->maxSpeed;
			h.y *= e->maxSpeed;
			h.z *= e->maxSpeed;
			e->velocity.x = h.x;
			e->velocity.z = h.z;
		}
	}
	if (e->velocity.y < e->minFall) {
		e->velocity.y = e->minFall;
	}
	f64 step = __fabs(e->velocity.y);

	if (AdjustPoint(&e->position, &e->target, step) != 0) {
		reached       = 1;
		e->velocity.x = e->velocity.y = e->velocity.z = lbl_8042DA74;
	}
	return reached;
}
}
