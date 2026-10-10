// TObjEnemyStg27Cloud's Disp: unless the mode object hides the scenery, and
// with its first clump, it does the sky's per-frame effect work for its two
// layers (entries 1 and 2 of the arrays rel/enemy_stg27_sky_disp.cpp uses
// entry 0 of: the last frame, the effect animation, which only layer 1
// advances, the models and their effect data), then renders both clumps.
// The class is shared through enemy_stg27_cloud_class.inc.

#define ENEMY_STG27_CLOUD_CTOR inline
#include "src/rel/enemy_stg27_cloud_class.inc"

struct RpAtomic;

// The mode object lbl_8042C180 points at: two flags that hide the scenery and
// the frame counter.
struct CloudMode {
	u8 unk00[0x1F];
	s8 unk1F; // 0x1F
	s8 unk20; // 0x20
	u8 unk21[0xF];
	s32 frame; // 0x30
};

// One model's effect data for SetAtomicCustomFXData.
struct SkyFxData {
	u8 unk00[0x44];
};

extern "C" CloudMode* lbl_8042C180;
extern "C" s32 enemyStg27SkyLastFrame[3];
extern "C" void* enemyStg27SkyFxAnim[3];
extern "C" SkyFxData enemyStg27SkyFxData[3];
extern "C" const f32 enemyStg27SkyFxStep[1];
extern "C" void fn_8011B844(void* anim, f32 step);
extern "C" void fn_8014FFBC(void* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
extern "C" void fn_8014FF2C(RpClump* clump);
RpAtomic* SetAtomicCustomFXData(RpAtomic* atomic, void* data);

// Whether the scenery is drawn: neither of the mode's two flags is set.
inline s32 CloudShown()
{
	if (lbl_8042C180->unk1F != 0) {
		return 0;
	}
	if (lbl_8042C180->unk20 != 0) {
		return 0;
	}
	return 1;
}

void TObjEnemyStg27Cloud::Disp()
{
	if (CloudShown() && clump != NULL) {
		s32 frame = lbl_8042C180->frame;
		if (enemyStg27SkyLastFrame[1] != frame) {
			enemyStg27SkyLastFrame[1] = frame;
			fn_8011B844(enemyStg27SkyFxAnim[1], enemyStg27SkyFxStep[0]);
			fn_8014FFBC(enemyStg27SkyModels[1], SetAtomicCustomFXData, &enemyStg27SkyFxData[1]);
		}
		if (enemyStg27SkyLastFrame[2] != frame) {
			enemyStg27SkyLastFrame[2] = frame;
			fn_8014FFBC(enemyStg27SkyModels[2], SetAtomicCustomFXData, &enemyStg27SkyFxData[2]);
		}
		fn_8014FF2C(clump);
		fn_8014FF2C(clump2);
	}
}
