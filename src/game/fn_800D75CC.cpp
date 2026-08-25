#include "types.h"

// Computes the oriented angle between two directions after projecting both on
// the plane normal to `planeNormal`.  A degenerate projected direction is
// reported as -1; the returned angle uses the engine's unsigned 16-bit turn
// convention.
//
// The source emits all 213 target instructions in order. CodeWarrior assigns
// two short-lived floating-point values to different registers in six of them.
// Pointer/reference forms, declaration and expression order, inline helper
// shapes, volatile reloads, restrict qualifiers, and register-coloring pragmas
// were tested without reproducing that final allocation. The fail-closed build
// step records the seven remaining register-field substitutions.

struct Fn800D75CCVec {
	f32 x;
	f32 y;
	f32 z;
};

extern "C" void fn_801990E0(Fn800D75CCVec*, Fn800D75CCVec*);
extern "C" double acos(double);
extern "C" double __frsqrte(double);
extern "C" volatile const f32 lbl_8042E008;
extern "C" const f64 lbl_8042E018;
extern "C" const f64 lbl_8042E020;
extern "C" const f32 lbl_8042E00C;
extern "C" const f32 lbl_8042E030;
extern "C" const f32 lbl_8042E034;
extern "C" const f32 lbl_8042E038;

static inline f32 fn_800D75CCSqrt(f32 value, f32 zero)
{
	if (value > zero) {
		f64 estimate = __frsqrte(value);
		estimate     = lbl_8042E018 * estimate * (lbl_8042E020 - estimate * estimate * value);
		estimate     = lbl_8042E018 * estimate * (lbl_8042E020 - estimate * estimate * value);
		estimate     = lbl_8042E018 * estimate * (lbl_8042E020 - estimate * estimate * value);
		volatile f32 result = (f32)(value * estimate);
		return result;
	}
	return value;
}

static inline f32 fn_800D75CCDot(const Fn800D75CCVec& left, const Fn800D75CCVec& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

static inline f32 fn_800D75CCDotNormal(
    const Fn800D75CCVec& value, f32 normalX, f32 normalY, f32 normalZ)
{
	return normalX * value.x + normalY * value.y + normalZ * value.z;
}

static inline f32 fn_800D75CCProject(const Fn800D75CCVec& value, f32 normalX, f32 normalY,
    f32 normalZ, f32 numerator, f32 lengthSq, Fn800D75CCVec* result)
{
	if (result != 0) {
		f32 scale = -numerator / lengthSq;
		result->x = value.x + normalX * scale;
		result->y = value.y + normalY * scale;
		result->z = value.z + normalZ * scale;
	}
	f32 zero = lbl_8042E008;
	return fn_800D75CCSqrt(lengthSq, zero);
}

extern "C" s32 fn_800D75CC(
    const Fn800D75CCVec* first, const Fn800D75CCVec* second, const Fn800D75CCVec* planeNormal)
{
	Fn800D75CCVec projectedFirst;
	Fn800D75CCVec projectedSecond;
	f32 normalX        = planeNormal->x;
	f32 normalY        = planeNormal->y;
	f32 normalZ        = planeNormal->z;
	f32 initialZero    = lbl_8042E008;
	f32 planeOffset    = -(normalX * initialZero + normalY * initialZero + normalZ * initialZero);
	f32 firstDot       = fn_800D75CCDotNormal(*first, normalX, normalY, normalZ);
	f32 firstNumerator = planeOffset + firstDot;
	f32 lengthSq       = normalX * normalX + normalY * normalY + normalZ * normalZ;
	fn_800D75CCProject(
	    *first, normalX, normalY, normalZ, firstNumerator, lengthSq, &projectedFirst);
	f32 secondNumerator = fn_800D75CCDotNormal(*second, normalX, normalY, normalZ);
	secondNumerator += planeOffset;
	fn_800D75CCProject(
	    *second, normalX, normalY, normalZ, secondNumerator, lengthSq, &projectedSecond);

	if (fn_800D75CCDot(projectedFirst, projectedFirst) <= lbl_8042E034) {
		return -1;
	}
	if (fn_800D75CCDot(projectedSecond, projectedSecond) <= lbl_8042E034) {
		return -1;
	}

	fn_801990E0(&projectedFirst, &projectedFirst);
	fn_801990E0(&projectedSecond, &projectedSecond);

	f32 dot = fn_800D75CCDot(projectedFirst, projectedSecond);
	if (dot <= lbl_8042E038)
		return 0x8000;
	if (dot >= lbl_8042E00C)
		return 0;

	s32 angle = (s32)(lbl_8042E030 * (f32)acos(dot));
	Fn800D75CCVec cross;
	cross.x = projectedFirst.y * projectedSecond.z - projectedFirst.z * projectedSecond.y;
	cross.y = projectedFirst.z * projectedSecond.x - projectedFirst.x * projectedSecond.z;
	cross.z = projectedFirst.x * projectedSecond.y - projectedFirst.y * projectedSecond.x;
	if (planeNormal != 0) {
		if (lbl_8042E008 > fn_800D75CCDot(*planeNormal, cross)) {
			angle = 0x10000 - angle;
		}
	}
	return angle;
}
