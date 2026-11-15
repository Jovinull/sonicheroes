// C_COLLI::Init(CCL_INFO*, int, unsigned char) (symbol name from the retail map): copies `count`
// shape records (0x30 bytes each) into a new array owned by the object (returns -1 when the
// allocation fails), sets the owned-shapes flag 0x8000 and, for kinds 2, 3 and 7, flag 0x40, stores
// the kind and count, clears the hit state (count, flags 0x13F, the shapes' bit 0x10 and the eight
// hit slots) and computes the range (CalcRange, inlined). Returns 0. Flag meanings are UNKNOWN.
#include "types.h"

struct Vec80021384 {
	f32 x;
	f32 y;
	f32 z;
};

// Collision shape record (the mangled name of Init gives the type name).
struct CCL_INFO {
	u8 unknown0;
	u8 kind; // 0x1
	u8 pad2;
	u8 flags; // 0x3
	u8 pad4[4];
	Vec80021384 center; // 0x8
	Vec80021384 size;   // 0x14
	u8 pad20[0x30 - 0x20];
};

class C_COLLI;

struct Hit8003C200 {
	s8 entry;       // 0x0
	s8 otherEntry;  // 0x1
	u16 flags;      // 0x2
	C_COLLI* other; // 0x4
};

// Local view: only the members Init uses.
class C_COLLI
{
public:
	s32 Init(CCL_INFO* info, int count, u8 kind);
	inline void CalcRange();
	inline void ClearInfo();

	u16 kind;     // 0x0
	u16 hitCount; // 0x2
	u8 pad4[4];
	u16 flags;           // 0x8
	u16 shapeCount;      // 0xA
	f32 range;           // 0xC
	CCL_INFO* shapes;    // 0x10
	Hit8003C200 hits[8]; // 0x14
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
void* memmove(void* dst, const void* src, unsigned long n);
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

// Same body as CalcRange__7C_COLLIFv.cpp (inlined here).
inline void C_COLLI::CalcRange()
{
	f32 max;
	f32 x;
	f32 y;
	f32 z;
	f32 r;
	CCL_INFO* shape;
	CCL_INFO* end;

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

// Same body as ClearInfo__7C_COLLIFv.cpp (inlined here).
inline void C_COLLI::ClearInfo()
{
	Hit8003C200* hit;
	Hit8003C200* end;
	u16 n;
	CCL_INFO* shape;

	hit      = hits;
	end      = &hits[8];
	hitCount = 0;
	flags &= ~0x13F;
	n     = shapeCount;
	shape = shapes;
	while (n-- != 0) {
		shape->flags &= ~0x10;
		shape++;
	}
	while (hit != end) {
		hit->flags &= ~3;
		hit->entry      = -1;
		hit->otherEntry = -1;
		hit->other      = NULL;
		hit++;
	}
}

s32 C_COLLI::Init(CCL_INFO* info, int count, u8 kind)
{
	u32 size       = count * sizeof(CCL_INFO);
	CCL_INFO* copy = (CCL_INFO*)new u8[size];

	if (copy == NULL) {
		return -1;
	}
	memmove(copy, info, size);
	shapes = copy;
	flags |= 0x8000;
	if ((u8)(kind - 2) <= 1 || kind == 7) {
		flags |= 0x40;
	}
	this->kind = kind;
	shapeCount = count;
	ClearInfo();
	CalcRange();
	return 0;
}
