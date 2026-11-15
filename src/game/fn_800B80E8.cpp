#include "types.h"

// Sets up one of the special textures of a team (see fn_800BE56C): needs a texture (+0x20) and
// +0x30, a slot (+0x0) and a team (+0x1). With the stage object lbl_8042C398 its fn_801439D8
// block gets the team's alpha (+0x2E..+0x31 for teams 0, 1, 2 and others): for a distance between
// lbl_8042DD74 and lbl_8042DD70 it is lbl_8042DD58 times sqrt(lbl_8042DD78 * (lbl_8042DD70 - d))
// capped at lbl_8042DD4C, else 0. The object is then stored in lbl_80253A34[slot], the team's
// lbl_80304000 entry gets the texture (fn_801A45A0) and the team's frame lbl_802539C4 is placed at
// +0x2C's +0x10 (fn_8019ECCC). sqrtf is MSL's inline with the shared constants. HYPOTHESIS: the
// roles are UNKNOWN.

struct Holder800B80E8 {
	u8 pad0[0x10];
	u8 matrix[0x40]; // 0x10
};

struct Object800B80E8 {
	s8 slot; // 0x0
	s8 team; // 0x1
	u8 pad2[0x20 - 0x2];
	void* texture; // 0x20
	u8 pad24[0x2C - 0x24];
	Holder800B80E8* holder; // 0x2C
	void* unknown30;        // 0x30
};

struct Alpha800B80E8 {
	u8 pad0[0x2E];
	u8 alpha[4]; // 0x2E
};

extern "C" {
extern void* lbl_8042C398;
extern Object800B80E8* lbl_80253A34[8];
extern void* lbl_80304000[8];
extern void* lbl_802539C4[4];
extern const f32 lbl_8042DD48[1]; // 0.0f
extern const f32 lbl_8042DD4C;
extern const f32 lbl_8042DD58;
extern const f32 lbl_8042DD70;
extern const f32 lbl_8042DD74;
extern const f32 lbl_8042DD78;
extern const f64 lbl_8042DD80[1]; // 0.5
extern const f64 lbl_8042DD88[1]; // 3.0
Alpha800B80E8* fn_801439D8(void* stage);
void fn_801A45A0(void* entry, void* texture);
void fn_8019ECCC(void* frame, void* matrix, s32 combine);
}

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

extern "C" void fn_800B80E8(Object800B80E8* object, f32 distance)
{
	if (object->texture == NULL || object->unknown30 == NULL) {
		return;
	}
	if (object->slot == -1 || object->team == -1) {
		return;
	}
	if (lbl_8042C398 != NULL) {
		Alpha800B80E8* block = fn_801439D8(lbl_8042C398);
		u8 alpha;
		if (distance < lbl_8042DD70 && distance > lbl_8042DD74) {
			f32 value  = Sqrtf(lbl_8042DD78 * (lbl_8042DD70 - distance));
			f32 capped = value;
			if (value > lbl_8042DD4C) {
				capped = lbl_8042DD4C;
			}
			alpha = lbl_8042DD58 * capped;
		} else {
			alpha = 0;
		}
		switch (object->team) {
			case 0:
				block->alpha[0] = alpha;
				break;
			case 1:
				block->alpha[1] = alpha;
				break;
			case 2:
				block->alpha[2] = alpha;
				break;
			default:
				block->alpha[3] = alpha;
				break;
		}
	}
	lbl_80253A34[object->slot] = object;
	fn_801A45A0(lbl_80304000[object->team + 1], object->texture);
	fn_8019ECCC(lbl_802539C4[object->team], object->holder->matrix, 0);
}
