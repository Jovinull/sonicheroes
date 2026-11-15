#include "types.h"

// Updates a player's offset to its target point: the vector from the position (+0x708) to the
// target (+0x5F0) at +0x610, its horizontal (XZ) length at +0x608 and its full length at +0x60C.
// sqrtf is MSL's inline (see src/rel/cage_class.inc); its constants are the shared .sdata2
// literals of this code. HYPOTHESIS: the field names.

struct Vec800892C4 {
	f32 x;
	f32 y;
	f32 z;
};

struct Player800892C4 {
	u8 pad0[0x5F0];
	Vec800892C4 target; // 0x5F0
	u8 pad5FC[0x608 - 0x5FC];
	f32 distanceXZ;     // 0x608
	f32 distance;       // 0x60C
	Vec800892C4 offset; // 0x610
	u8 pad61C[0x708 - 0x61C];
	Vec800892C4 position; // 0x708
};

extern "C" {
extern const f32 lbl_8042D840[1]; // 0.0f
extern const f64 lbl_8042D848[1]; // 0.5
extern const f64 lbl_8042D850[1]; // 3.0
}

double __frsqrte(double x);

static inline f32 Sqrtf(f32 x)
{
	volatile f32 y;

	if (x > lbl_8042D840[0]) {
		double guess = __frsqrte((double)x);
		double half  = lbl_8042D848[0];
		double three;
		guess = half * guess * ((three = lbl_8042D850[0]) - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		y     = (f32)(x * guess);
		return y;
	}
	return x;
}

extern "C" void fn_800892C4(Player800892C4* p)
{
	p->offset.x   = p->target.x - p->position.x;
	p->offset.y   = p->target.y - p->position.y;
	p->offset.z   = p->target.z - p->position.z;
	p->distanceXZ = Sqrtf(p->offset.x * p->offset.x + p->offset.z * p->offset.z);
	p->distance   = Sqrtf(
	    p->offset.z * p->offset.z + (p->offset.x * p->offset.x + p->offset.y * p->offset.y));
}
