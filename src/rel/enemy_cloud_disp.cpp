// TObjEnemyCloud's Disp: unless the mode object hides the scenery, and with its
// first clump, it does the sky's per-frame effect work for its two layers
// (entries 1 and 2 of the arrays rel/enemy_sky_disp.cpp uses entry 0 of: the
// last frame, the effect animation, which only layer 1 advances, the models and
// their effect data), then renders both clumps. The class is shared through
// enemy_cloud_class.inc.

#define ENEMY_CLOUD_CTOR inline
#include "src/rel/enemy_cloud_class.inc"

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
extern "C" s32 enemySkyLastFrame[3];
extern "C" void* enemySkyFxAnim[3];
extern "C" SkyFxData enemySkyFxData[3];
extern "C" const f32 enemySkyFxStep[1];
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

void TObjEnemyCloud::Disp()
{
	if (CloudShown() && clump != NULL) {
		s32 frame = lbl_8042C180->frame;
		if (enemySkyLastFrame[1] != frame) {
			enemySkyLastFrame[1] = frame;
			fn_8011B844(enemySkyFxAnim[1], enemySkyFxStep[0]);
			fn_8014FFBC(enemySkyModels[1], SetAtomicCustomFXData, &enemySkyFxData[1]);
		}
		if (enemySkyLastFrame[2] != frame) {
			enemySkyLastFrame[2] = frame;
			fn_8014FFBC(enemySkyModels[2], SetAtomicCustomFXData, &enemySkyFxData[2]);
		}
		fn_8014FF2C(clump);
		fn_8014FF2C(clump2);
	}
}
