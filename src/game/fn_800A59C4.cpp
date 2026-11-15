// Turns an enemy toward its target point: the heading to the point at +0x1CC (from the position
// at +0x140, in x/z) is stored at +0x174 as a 16-bit angle, and the angle at +0x150 moves toward it
// by at most +0x180 (AdjustAngle). Returns the remaining difference (DiffAngle). Field roles are
// HYPOTHESIS.
#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

// misc.h declares these as returning u16; the callers use the full int result (no zero-extension).
int DiffAngle(int first, int second);
int AdjustAngle(int first, int second, int limit);

struct Enemy800A59C4 {
	u8 pad0[0x140];
	RwV3d position; // 0x140
	u8 pad14C[0x150 - 0x14C];
	s32 angle; // 0x150
	u8 pad154[0x174 - 0x154];
	s32 targetAngle; // 0x174
	u8 pad178[0x180 - 0x178];
	s32 turnSpeed; // 0x180
	u8 pad184[0x1CC - 0x184];
	RwV3d target; // 0x1CC
};

extern "C" {
extern f32 lbl_8042DA7C; // 65536 / (2 pi)
double atan2(double y, double x);

s32 fn_800A59C4(Enemy800A59C4* e)
{
	s32 diff;

	e->targetAngle
	    = lbl_8042DA7C * (f32)atan2(e->target.x - e->position.x, e->target.z - e->position.z);
	diff     = DiffAngle(e->targetAngle, e->angle);
	e->angle = AdjustAngle(e->angle, e->targetAngle, e->turnSpeed);
	return diff;
}
}
