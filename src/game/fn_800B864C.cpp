#include "game/rw_types.h"

// Atomic callback (sibling of fn_800B899C): takes the positions of the three frames of
// lbl_802539C4 (fn_8019E8EC gives each frame's matrix, position at +0x30) and passes the atomic to
// fn_801491A8 as soon as one of them is within its world bounding sphere
// (fn_8014F9C4: centre, radius +0xC) grown by lbl_8042DD90, within the radius grown by
// lbl_8042DD94 on XZ, and above the centre. Otherwise it clears the atomic's slot at the offset
// fn_801521F4(0x120) and stores fn_8015BF40(0) at +0x6C. sqrtf is MSL's inline with this code's
// shared constants. HYPOTHESIS: RwFrameGetLTM and RpAtomicGetWorldBoundingSphere.
// NonMatching (8 words, registers only): in the frame loop retail keeps the counter in r29 and the
// point pointer in r31; MWCC swaps them. Tried: the loop inline or in place, pointer walks, a
// per-point inline and declaration orders (perm.py). Same family as fn_8004EF98.

struct Matrix800B864C {
	u8 pad0[0x30];
	RwV3d position; // 0x30
};

struct Sphere800B864C {
	RwV3d center; // 0x0
	f32 radius;   // 0xC
};

struct Atomic800B864C {
	u8 pad0[0x6C];
	void* unknown6C; // 0x6C
};

extern "C" {
extern void* lbl_802539C4[3];
extern const f32 lbl_8042DD48[1]; // 0.0f
extern const f64 lbl_8042DD80[1]; // 0.5
extern const f64 lbl_8042DD88[1]; // 3.0
extern const f32 lbl_8042DD90;
extern const f32 lbl_8042DD94;
Matrix800B864C* fn_8019E8EC(void* frame);
Sphere800B864C* fn_8014F9C4(Atomic800B864C* atomic);
s32 fn_801521F4(s32 id);
void* fn_8015BF40(void* value);
void fn_801491A8(Atomic800B864C* atomic);
}

f32 DistanceP2P(const RwV3d* first, const RwV3d* second);
double __frsqrte(double x);

static inline f32 Sqrtf(f32 x)
{
	volatile f32 y;

	if (x > lbl_8042DD48[0]) {
		double guess = __frsqrte((double)x);
		double half  = lbl_8042DD80[0];
		double three;
		guess = half * guess * ((three = lbl_8042DD88[0]) - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		y     = (f32)(x * guess);
		return y;
	}
	return x;
}

static inline void GetPoints(RwV3d* points)
{
	for (s32 i = 0; i < 3; i++) {
		Matrix800B864C* matrix = fn_8019E8EC(lbl_802539C4[i]);
		points[i].x            = matrix->position.x;
		points[i].y            = matrix->position.y;
		points[i].z            = matrix->position.z;
	}
}

extern "C" void fn_800B864C(Atomic800B864C* atomic)
{
	RwV3d points[3];
	RwV3d* point;
	Sphere800B864C* sphere;
	s32 i;

	GetPoints(points);
	sphere = fn_8014F9C4(atomic);
	i      = 0;
	point  = points;
	for (; i < 3; point++, i++) {
		f32 distance = DistanceP2P(&sphere->center, point);
		f32 xz       = Sqrtf((point->x - sphere->center.x) * (point->x - sphere->center.x)
		    + (point->z - sphere->center.z) * (point->z - sphere->center.z));
		if (distance < lbl_8042DD90 + sphere->radius && xz < lbl_8042DD94 + sphere->radius
		    && point->y > sphere->center.y) {
			fn_801491A8(atomic);
			return;
		}
	}
	s32* slot         = (s32*)((u8*)atomic + fn_801521F4(0x120));
	*slot             = 0;
	atomic->unknown6C = fn_8015BF40(NULL);
}
