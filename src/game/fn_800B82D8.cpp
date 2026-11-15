// Places an object: copies the position (+0x8) and angle (+0x14), moves its frame (+0x2C) to the
// position (fn_8019EB94, replace) and stores the scale (+0x4); a scale other than 1 is applied to
// the frame as (s, 1, s) (fn_8019EC30, pre-concatenated). HYPOTHESIS: RwFrameTranslate/RwFrameScale
// on a model frame; the names are UNKNOWN.
#include "types.h"

struct Vec800B82D8 {
	f32 x;
	f32 y;
	f32 z;
};

struct Angle800B82D8 {
	s32 x;
	s32 y;
	s32 z;
};

struct Obj800B82D8 {
	u8 pad0[4];
	f32 scale;            // 0x4
	Vec800B82D8 position; // 0x8
	Angle800B82D8 angle;  // 0x14
	u8 pad20[0x2C - 0x20];
	void* frame; // 0x2C
};

extern "C" {
extern f32 lbl_8042DD4C; // 1.0f
void fn_8019EB94(void* frame, const Vec800B82D8* v, s32 combine);
void fn_8019EC30(void* frame, const Vec800B82D8* v, s32 combine);

void fn_800B82D8(Obj800B82D8* o, Vec800B82D8* position, Angle800B82D8* angle, f32 scale)
{
	o->position = *position;
	o->angle    = *angle;
	fn_8019EB94(o->frame, &o->position, 0);
	o->scale = scale;
	f32 one  = lbl_8042DD4C;
	if (one != o->scale) {
		Vec800B82D8 s;

		s.x = o->scale;
		s.y = one;
		s.z = o->scale;
		fn_8019EC30(o->frame, &s, 1);
	}
}
}
