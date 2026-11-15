// C_COLLI::CalcRange (symbol name from the retail map): computes the bounding range of the
// collision object (+0xC) from its shapes (the 0x30-byte list at +0x10, count at +0xA): for each,
// the distance of its centre (+0x8) plus its extent by kind (+0x1): kind 0 the size x, kind 8 x +
// y, kinds 1-3 and 10-11 the length of (x, y), others the length of (x, y, z). The range is the
// largest of these, scaled by 1.01; when the largest is under 0.1 the range becomes 25. The
// shape-kind meanings (sphere, capsule, ...) are UNKNOWN.
#include "types.h"

struct Vec80021384 {
	f32 x;
	f32 y;
	f32 z;
};

struct Shape80021384 {
	u8 unknown0;
	u8 kind; // 0x1
	u8 pad2[6];
	Vec80021384 center; // 0x8
	Vec80021384 size;   // 0x14
	u8 pad20[0x30 - 0x20];
};

// Local view: only the members CalcRange uses.
class C_COLLI
{
public:
	void CalcRange();

	u8 pad0[0xA];
	u16 shapeCount;        // 0xA
	f32 range;             // 0xC
	Shape80021384* shapes; // 0x10
};

// The TU's pooled constants (0.0f, 0.5, 3.0, 1.01f, 0.1f, 25.0f), named so this unit does not
// emit its own copies.
extern "C" {
extern const f32 lbl_8042D048[1];
extern const f64 lbl_8042D050[1];
extern const f64 lbl_8042D058[1];
extern const f32 lbl_8042D060[1];
extern const f32 lbl_8042D064[1];
extern const f32 lbl_8042D068[1];
f32 fn_801991B4(Vec80021384* v);
}

double __frsqrte(double x);

// MSL's sqrtf, with the pooled constants named (see src/rel/cage_class.inc).
static inline f32 CollSqrtf(f32 x)
{
	volatile f32 y;

	if (x > lbl_8042D048[0]) {
		double guess = __frsqrte((double)x);
		double half  = lbl_8042D050[0];
		double three;
		guess = half * guess * ((three = lbl_8042D058[0]) - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		y     = (f32)(x * guess);
		return y;
	}
	return x;
}

void C_COLLI::CalcRange()
{
	f32 max;
	f32 x;
	f32 y;
	f32 z;
	f32 r;
	Shape80021384* shape;
	Shape80021384* end;

	max = lbl_8042D048[0];
	end = shapes + shapeCount;
	for (shape = shapes; shape < end; shape++) {
		x = shape->size.x;
		y = shape->size.y;
		z = shape->size.z;
		r = fn_801991B4(&shape->center);
		switch (shape->kind) {
			case 0:
				r = r + x;
				break;
			case 8:
				r = r + (x + y);
				break;
			case 1:
			case 2:
			case 3:
			case 10:
			case 11:
				r = r + CollSqrtf(x * x + y * y);
				break;
			default:
				r = r + CollSqrtf(z * z + (x * x + y * y));
				break;
		}
		if (r > max) {
			max = r;
		}
	}
	range = lbl_8042D060[0] * max;
	if (max < lbl_8042D064[0]) {
		range = lbl_8042D068[0];
	}
}
