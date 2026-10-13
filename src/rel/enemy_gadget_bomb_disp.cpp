#include "types.h"

// TEnemyGadgetBomb::CanDisp and Disp (the PS2 build's names): the searcher's
// bomb shows only with a model and in the camera's view; Disp then draws it
// with its light set.

typedef struct RpClump RpClump;

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwSphere {
	RwV3d center; // 0x00
	f32 radius;   // 0x0C
} RwSphere;

typedef struct GadgetBomb {
	u8 unk00[0xB8];
	RpClump* clump; // 0xB8
	RwV3d pos;      // 0xBC
	u8 unkC8[0x18];
	u32 light; // 0xE0
} GadgetBomb;

namespace nRender
{
void SetLightNum(u32 num);
}

extern "C" void** lbl_8042C9A4;
extern "C" const f32 gadgetBombViewRadius[1];

extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
extern "C" void fn_8014FF2C(RpClump* clump);

// CanDisp. The out-of-line copy reads as `!= 0`; the copy Disp inlines keeps
// the two branches (if/else on the frustum test), so each is written its way.
extern "C" s32 CanDisp__16TEnemyGadgetBombFv(GadgetBomb* object)
{
	RwSphere sphere;

	if (object->clump == NULL) {
		return 0;
	}
	sphere.center = object->pos;
	sphere.radius = gadgetBombViewRadius[0];
	return fn_8019CE34(*lbl_8042C9A4, &sphere) != 0;
}

static inline s32 gadgetBombCanDisp(GadgetBomb* object)
{
	RwSphere sphere;

	if (object->clump == NULL) {
		return 0;
	}
	sphere.center = object->pos;
	sphere.radius = gadgetBombViewRadius[0];
	if (fn_8019CE34(*lbl_8042C9A4, &sphere) == 0) {
		return 0;
	} else {
		return 1;
	}
}

extern "C" void Disp__16TEnemyGadgetBombFv(GadgetBomb* object)
{
	if (gadgetBombCanDisp(object)) {
		nRender::SetLightNum(object->light);
		fn_8014FF2C(object->clump);
	}
}
