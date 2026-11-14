// Tests a 2-D point against the object's 2-D region (HYPOTHESIS): only for objects flagged with
// bit 0x4 at 0x8, lifts the point to 3-D with the .sdata2 constant lbl_8042F4A8 as z, transforms
// it by the matrix at 0xC0 (fn_8019941C, HYPOTHESIS: RwV3dTransformPoints) and passes the
// transformed x/y with the object's data at 0xAC to fn_80171EB8. Returns its result, or 0 for
// unflagged objects. Field names are inferred from this function only.
// NonMatching: the retail code copies the point through f0 one component at a time; ours loads
// both components before storing them (8 words differ).
#include "game/rw_engine.h"

struct Vec2_80173668 {
	f32 x;
	f32 y;
};

struct Object80173668 {
	u8 pad0[0x8];
	s32 flags; // 0x8
	u8 padC[0xAC - 0xC];
	void* region; // 0xAC
	u8 padB0[0xC0 - 0xB0];
	RwMatrix matrix; // 0xC0
};

extern "C" {
extern f32 lbl_8042F4A8;

RwV3d* fn_8019941C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrix* matrix);
s32 fn_80171EB8(Vec2_80173668* point, void* region);

s32 fn_80173668(Object80173668* object, const Vec2_80173668* point)
{
	Vec2_80173668 projected;
	RwV3d in;
	RwV3d out;

	if ((object->flags & 0x4) == 0x4) {
		in.x = point->x;
		in.y = point->y;
		in.z = lbl_8042F4A8;
		fn_8019941C(&out, &in, 1, &object->matrix);
		projected.x = out.x;
		projected.y = out.y;
		return fn_80171EB8(&projected, object->region);
	}
	return 0;
}
}
