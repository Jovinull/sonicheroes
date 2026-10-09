// TObjEnemyStg27Sky's Disp: unless the mode object hides the scenery (two
// flags, tested by an inline helper that answers 1 or 0), and with a clump,
// it advances the sky's effect animation by 0.1 once per frame (the frame
// number is kept in enemyStg27SkyLastFrame) and applies it to the model's
// atomics through SetAtomicCustomFXData, then renders the clump. The class is
// shared through enemy_stg27_sky_class.inc.

#define ENEMY_STG27_SKY_CTOR inline
#include "src/rel/enemy_stg27_sky_class.inc"

struct RpAtomic;

// The mode object lbl_8042C180 points at: two flags that hide the scenery and
// the frame counter.
struct SkyMode {
	u8 unk00[0x1F];
	s8 unk1F; // 0x1F
	s8 unk20; // 0x20
	u8 unk21[0xF];
	s32 frame; // 0x30
};

extern "C" SkyMode* lbl_8042C180;
extern "C" s32 enemyStg27SkyLastFrame;
extern "C" void* enemyStg27SkyFxAnim;
extern "C" u8 enemyStg27SkyFxData[];
extern "C" const f32 enemyStg27SkyFxStep[1];
extern "C" void fn_8011B844(void* anim, f32 step);
extern "C" void fn_8014FFBC(void* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
extern "C" void fn_8014FF2C(RpClump* clump);
RpAtomic* SetAtomicCustomFXData(RpAtomic* atomic, void* data);

// Whether the scenery is drawn: neither of the mode's two flags is set.
inline s32 SkyShown()
{
	if (lbl_8042C180->unk1F != 0) {
		return 0;
	}
	if (lbl_8042C180->unk20 != 0) {
		return 0;
	}
	return 1;
}

void TObjEnemyStg27Sky::Disp()
{
	if (SkyShown() && clump != NULL) {
		s32 frame = lbl_8042C180->frame;
		if (enemyStg27SkyLastFrame != frame) {
			enemyStg27SkyLastFrame = frame;
			fn_8011B844(enemyStg27SkyFxAnim, enemyStg27SkyFxStep[0]);
			fn_8014FFBC(enemyStg27SkyModels[0], SetAtomicCustomFXData, enemyStg27SkyFxData);
		}
		fn_8014FF2C(clump);
	}
}
