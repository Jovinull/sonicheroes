#include "types.h"

struct Fn800D7BD8Vec {
	f32 x;
	f32 y;
	f32 z;
};

struct Fn800D7BD8Segment {
	Fn800D7BD8Vec origin;
	Fn800D7BD8Vec direction;
};

extern "C" f64 __frsqrte(f64);
extern "C" f32 fn_800D7044(const Fn800D7BD8Vec*, const Fn800D7BD8Segment*, Fn800D7BD8Vec*);
extern "C" const f32 lbl_8042E060;
extern "C" const f32 lbl_8042E064;
extern "C" const f64 lbl_8042E068;
extern "C" const f64 lbl_8042E070;

static inline f32 fn_800D7BD8Sqrt(f32 value)
{
	if (value > lbl_8042E060) {
		f64 estimate = __frsqrte(value);
		estimate     = lbl_8042E068 * estimate * (lbl_8042E070 - estimate * estimate * value);
		estimate     = lbl_8042E068 * estimate * (lbl_8042E070 - estimate * estimate * value);
		estimate     = lbl_8042E068 * estimate * (lbl_8042E070 - estimate * estimate * value);
		volatile f32 result = (f32)(value * estimate);
		return result;
	}
	return value;
}

extern "C" f32 fn_800D7BD8(const Fn800D7BD8Vec* point, const Fn800D7BD8Vec* first,
    const Fn800D7BD8Vec* second, Fn800D7BD8Vec* closest)
{
	f32 x;
	f32 directionX;
	f32 y;
	f32 z;
	f32 directionY;
	f32 directionZ;
	f32 firstX;
	f32 firstY;
	f32 firstZ;
	f32 pointX;
	f32 secondX;
	f32 pointY;
	f32 secondY;
	f32 pointZ;
	f32 secondZ;

	pointX     = point->x;
	firstX     = first->x;
	x          = pointX - firstX;
	pointY     = point->y;
	firstY     = first->y;
	y          = pointY - firstY;
	pointZ     = point->z;
	firstZ     = first->z;
	z          = pointZ - firstZ;
	secondX    = second->x;
	directionX = secondX - firstX;
	secondY    = second->y;
	directionY = secondY - firstY;
	secondZ    = second->z;
	directionZ = secondZ - firstZ;

	if (x * directionX + y * directionY + z * directionZ < lbl_8042E060) {
		f32 distanceSquared;
		if (closest != 0) {
			closest->x = firstX;
			closest->y = first->y;
			closest->z = first->z;
		}
		distanceSquared = x * x + y * y + z * z;
		if (distanceSquared <= lbl_8042E064) {
			return lbl_8042E060;
		}
		return fn_800D7BD8Sqrt(distanceSquared);
	}

	x = secondX - pointX;
	y = secondY - pointY;
	z = secondZ - pointZ;
	if (directionX * x + directionY * y + directionZ * z < lbl_8042E060) {
		f32 distanceSquared;
		if (closest != 0) {
			closest->x = secondX;
			closest->y = second->y;
			closest->z = second->z;
		}
		distanceSquared = x * x + y * y + z * z;
		if (distanceSquared <= lbl_8042E064) {
			return lbl_8042E060;
		}
		return fn_800D7BD8Sqrt(distanceSquared);
	}

	Fn800D7BD8Segment segment;
	segment.origin.x    = firstX;
	segment.origin.y    = firstY;
	segment.origin.z    = firstZ;
	segment.direction.x = directionX;
	segment.direction.y = directionY;
	segment.direction.z = directionZ;
	return fn_800D7044(point, &segment, closest);
}
