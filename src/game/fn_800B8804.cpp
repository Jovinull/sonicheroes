// Checks an object's bounding sphere (fn_8014F9C4: centre and radius at +0xC) against the
// positions of the three frames of lbl_802539C4 (their world matrices, fn_8019E8EC): within the
// radius plus 40 of any, it runs fn_801491A8 on the object; otherwise it clears the object's plugin
// word (offset fn_801521F4(0x120)) and sets +0x6C to fn_8015BF40(0). HYPOTHESIS: RenderWare
// plugin/visibility handling of an atomic near the camera; the roles are UNKNOWN.
// NonMatching (register allocation): the retail code does not keep the positions' address across
// the two loops (four saved registers, the margin in f31); MWCC keeps it in a fifth. With
// `#pragma opt_common_subs off` the shape matches but the registers still differ (20 words).
// Tried: pointer-walk loops, inline helpers for either loop, declaration orders.
#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct Matrix800B8804 {
	u8 pad0[0x30];
	RwV3d pos; // 0x30
};

struct Sphere800B8804 {
	RwV3d center; // 0x0
	f32 radius;   // 0xC
};

struct Obj800B8804 {
	u8 pad0[0x6C];
	void* unknown6C; // 0x6C
};

f32 DistanceP2P(const RwV3d* a, const RwV3d* b);

extern "C" {
extern void* lbl_802539C4[3];
extern f32 lbl_8042DD90; // 40.0f
Matrix800B8804* fn_8019E8EC(void* frame);
Sphere800B8804* fn_8014F9C4(Obj800B8804* o);
void fn_801491A8(Obj800B8804* o);
s32 fn_801521F4(s32 id);
void* fn_8015BF40(s32 value);

void fn_800B8804(Obj800B8804* o)
{
	RwV3d positions[3];
	Sphere800B8804* sphere;
	f32 margin;
	int i;

	for (i = 0; i < 3; i++) {
		positions[i] = fn_8019E8EC(lbl_802539C4[i])->pos;
	}
	sphere = fn_8014F9C4(o);
	margin = lbl_8042DD90;
	for (i = 0; i < 3; i++) {
		if (DistanceP2P(&sphere->center, &positions[i]) < margin + sphere->radius) {
			fn_801491A8(o);
			return;
		}
	}
	*(s32*)((u8*)o + fn_801521F4(0x120)) = 0;
	o->unknown6C                         = fn_8015BF40(0);
}
}
