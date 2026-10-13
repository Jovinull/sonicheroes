#include "types.h"

// TEnemyGadgetLaser::DispTrans and DispOpaq (the PS2 build's names): while it
// readies its beam (pre-attack) the laser draws its three charge sparks (when
// on) and the beam additively without light 0x15; opaque, its body with the
// scene's light count.

#include "src/rel/searcher.inc"

typedef struct GadgetLaser GadgetLaser;

struct GadgetLaser {
	TEnemyGadget base;
	u8 unk38[0x88];
	TObjEnemy* enemy; // 0xC0
	u8 unkC4[0x30];
	s32 sparksOn; // 0xF4
	u8 unkF8[0x24];
	RpClump* sparks[3]; // 0x11C
};

namespace nRender
{
void SaveRenderState();
void LoadRenderState();
void SetRenderStateForBlendAdd();
void DisableLight(int light);
void EnableLight(int light);
void SetLightNum(u32 count);
} // namespace nRender

extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" void DispLaserBeam__17TEnemyGadgetLaserFv(GadgetLaser* gadget);

extern "C" void DispTrans__17TEnemyGadgetLaserFv(GadgetLaser* gadget)
{
	if (gadget->base.gmode == TEnemyGadget::E_GM_PREATTACK) {
		nRender::SaveRenderState();
		nRender::SetRenderStateForBlendAdd();
		nRender::DisableLight(0x15);
		if (gadget->sparksOn) {
			if (gadget->sparks[0] != NULL) {
				fn_8014FF2C(gadget->sparks[0]);
			}
			if (gadget->sparks[1] != NULL) {
				fn_8014FF2C(gadget->sparks[1]);
			}
			if (gadget->sparks[2] != NULL) {
				fn_8014FF2C(gadget->sparks[2]);
			}
		}
		DispLaserBeam__17TEnemyGadgetLaserFv(gadget);
		nRender::EnableLight(0x15);
		nRender::LoadRenderState();
	}
}

extern "C" void DispOpaq__17TEnemyGadgetLaserFv(GadgetLaser* gadget)
{
	nRender::SetLightNum(gadget->enemy->GetCurrentLightNum());
	fn_8014FF2C(gadget->base.pClump);
}
