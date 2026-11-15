// Turns an object's direction vector (0xF8) into angles (HYPOTHESIS; names inferred): when the
// vector is longer than lbl_8042E910, stores the pitch asin(-y / length) and the yaw atan2(x, z),
// both scaled by lbl_8042E930 to integer angle units, and clears the roll; otherwise clears all
// three angles.
#include "game/object.h"

struct Facing8010FBCC {
	u8 pad0[0xF8];
	RwV3d direction; // 0xF8
	s32 pitch;       // 0x104
	s32 yaw;         // 0x108
	s32 roll;        // 0x10C
};

extern "C" {
extern f32 lbl_8042E910;
extern f32 lbl_8042E930;
// HYPOTHESIS: RwV3dLength.
f32 fn_801991B4(const RwV3d* vector);
double asin(double x);
double atan2(double y, double x);

void fn_8010FBCC(Facing8010FBCC* facing)
{
	if (fn_801991B4(&facing->direction) > lbl_8042E910) {
		facing->pitch
		    = lbl_8042E930 * (f32)asin(-facing->direction.y / fn_801991B4(&facing->direction));
		facing->yaw  = lbl_8042E930 * (f32)atan2(facing->direction.x, facing->direction.z);
		facing->roll = 0;
	} else {
		facing->roll  = 0;
		facing->yaw   = 0;
		facing->pitch = 0;
	}
}
}
