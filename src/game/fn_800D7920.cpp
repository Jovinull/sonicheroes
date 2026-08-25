#include "types.h"

// Converts the angle between two normalized vectors to the engine's unsigned
// 16-bit turn representation. The optional orientation vector selects the
// winding direction.

struct Fn800D7920Vec {
	f32 x;
	f32 y;
	f32 z;
};

extern "C" double acos(double);
extern "C" const f32 lbl_8042E008;
extern "C" const f32 lbl_8042E00C;
extern "C" const f32 lbl_8042E030;
extern "C" const f32 lbl_8042E038;

static f32 fn_800D7920Dot(const Fn800D7920Vec& left, const Fn800D7920Vec& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

extern "C" s32 fn_800D7920(
    const Fn800D7920Vec* first, const Fn800D7920Vec* second, const Fn800D7920Vec* orientation)
{
	f32 dot = fn_800D7920Dot(*first, *second);
	if (dot <= lbl_8042E038)
		return 0x8000;
	if (dot >= lbl_8042E00C)
		return 0;

	s32 angle = (s32)(lbl_8042E030 * (f32)acos(dot));
	Fn800D7920Vec cross;
	cross.x = first->y * second->z - first->z * second->y;
	cross.y = first->z * second->x - first->x * second->z;
	cross.z = first->x * second->y - first->y * second->x;
	if (orientation != 0 && lbl_8042E008 > fn_800D7920Dot(*orientation, cross)) {
		return 0x10000 - angle;
	}
	return angle;
}
