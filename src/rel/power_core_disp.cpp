#include "types.h"

// TEnemyPowerCore::Disp (the PS2 build's name), the same in the bonus stages
// (31D-33D): a core is shown while a sphere of the module's radius at its
// place is in the camera's view; a shown core draws its body tinted by its
// type's color, moving the body's UV animation on once per game frame for
// all cores.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwSphere {
	RwV3d center; // 0x00
	f32 radius;   // 0x0C
} RwSphere;

struct RpClump;
struct RpAtomic;
struct RwCamera;
struct RpUVAnimAnimation;

typedef struct RwRGBAReal {
	f32 red, green, blue, alpha;
} RwRGBAReal;

typedef struct PowerCoreFX {
	u8 unk00[0x44];
} PowerCoreFX;

typedef struct PowerCoreAnim {
	s32 frame;      // 0x0
	s32 shineFrame; // 0x4
} PowerCoreAnim;

typedef struct GameInfo {
	u8 unk00[0x30];
	s32 frame; // 0x30
} GameInfo;

typedef struct RwEngine {
	RwCamera* camera; // 0x00
} RwEngine;

typedef struct PowerCore {
	u8 unk00[0xB0];
	RwV3d pos; // 0xB0
	u8 unkBC[0x14];
	s32 type;       // 0xD0
	RpClump* body;  // 0xD4
	RpClump* shine; // 0xD8
	u8 unkDC[0x4];
	s32 shown; // 0xE0
} PowerCore;

RpAtomic* SetAtomicCustomFXData(RpAtomic* atomic, void* data);
void objRpClumpForAllMaterialsToChangeMaterialColor(RpClump* clump, RwRGBAReal* color);

extern "C" {
extern GameInfo* lbl_8042C180;
extern RwEngine* lbl_8042C9A4;
extern PowerCoreAnim powerCoreAnimState;
extern RpUVAnimAnimation* powerCoreUVAnim;
extern RpClump* powerCoreModels[2];
extern PowerCoreFX powerCoreFX[2];
extern RwRGBAReal powerCoreColors[3];
extern const f32 powerCoreUVStep;
extern const f32 powerCoreRadius;
s32 fn_8019CE34(RwCamera* camera, RwSphere* sphere);
void fn_8011B844(RpUVAnimAnimation* anim, f32 time);
void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
void fn_8014FF2C(RpClump* clump);
}

extern "C" void Disp__15TEnemyPowerCoreFv(PowerCore* object)
{
	RwSphere sphere;

	if (object->body == NULL) {
		object->shown = 0;
		return;
	}
	sphere.center.x = object->pos.x;
	sphere.center.y = object->pos.y;
	sphere.center.z = object->pos.z;
	sphere.radius   = powerCoreRadius;
	if (fn_8019CE34(lbl_8042C9A4->camera, &sphere) == 0) {
		object->shown = 0;
	} else {
		object->shown = 1;
	}
	if (object->shown != 0) {
		s32 frame = lbl_8042C180->frame;

		if (powerCoreAnimState.frame != frame) {
			powerCoreAnimState.frame = frame;
			fn_8011B844(powerCoreUVAnim, powerCoreUVStep);
			fn_8014FFBC(powerCoreModels[0], SetAtomicCustomFXData, &powerCoreFX[0]);
		}
		objRpClumpForAllMaterialsToChangeMaterialColor(
		    object->body, &powerCoreColors[object->type]);
		fn_8014FF2C(object->body);
	}
}
