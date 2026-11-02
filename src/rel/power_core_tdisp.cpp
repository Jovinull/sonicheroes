#include "types.h"

// TEnemyPowerCore::TDisp (the PS2 build's name), the same in the bonus stages
// (31D-33D): a shown core draws its shine additively, tinted by its type's
// color; the shine's UV animation moves on once per game frame for all cores.

struct RpClump;
struct RpAtomic;
struct RpUVAnimAnimation;

typedef struct RwRGBAReal {
	f32 red, green, blue, alpha;
} RwRGBAReal;

typedef struct PowerCoreFX {
	u8 unk00[0x44];
} PowerCoreFX;

typedef struct PowerCoreAnim {
	s32 unk0;  // 0x0
	s32 frame; // 0x4
} PowerCoreAnim;

typedef struct GameInfo {
	u8 unk00[0x30];
	s32 frame; // 0x30
} GameInfo;

typedef struct PowerCore {
	u8 unk00[0xD0];
	s32 type; // 0xD0
	u8 unkD4[0x4];
	RpClump* shine; // 0xD8
	u8 unkDC[0x4];
	s32 shown; // 0xE0
} PowerCore;

namespace nRender
{
void SetLightNum(u32 light);
void SaveRenderState();
void SetRenderStateForBlendAdd();
void LoadRenderState();
}

RpAtomic* SetAtomicCustomFXData(RpAtomic* atomic, void* data);
void objRpClumpForAllMaterialsToChangeMaterialColor(RpClump* clump, RwRGBAReal* color);

extern "C" {
extern GameInfo* lbl_8042C180;
extern PowerCoreAnim powerCoreAnimState;
extern RpUVAnimAnimation* powerCoreUVAnim;
extern RpClump* powerCoreModels[2];
extern PowerCoreFX powerCoreFX[2];
extern RwRGBAReal powerCoreColors[3];
extern const f32 powerCoreUVStep;
void fn_8011B844(RpUVAnimAnimation* anim, f32 time);
void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
void fn_8014FF2C(RpClump* clump);
}

extern "C" void TDisp__15TEnemyPowerCoreFv(PowerCore* object)
{
	if (object->shine != NULL && object->shown != 0) {
		s32 frame;

		nRender::SaveRenderState();
		nRender::SetRenderStateForBlendAdd();
		nRender::SetLightNum(0x10);
		frame = lbl_8042C180->frame;
		if (powerCoreAnimState.frame != frame) {
			powerCoreAnimState.frame = frame;
			fn_8011B844(powerCoreUVAnim, powerCoreUVStep);
			fn_8014FFBC(powerCoreModels[1], SetAtomicCustomFXData, &powerCoreFX[1]);
		}
		objRpClumpForAllMaterialsToChangeMaterialColor(
		    object->shine, &powerCoreColors[object->type]);
		fn_8014FF2C(object->shine);
		nRender::LoadRenderState();
	}
}
