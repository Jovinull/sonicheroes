#include "types.h"

// TEnemyGadgetSearchLight::CanDisp, DispTrans, DispOpaq and ReqGadgetMode (the
// PS2 build's names): the search light shows while its searcher is in the
// camera; its beam is drawn additively without light 0x15, the lamp with the
// scene's light count; it takes a new mode only when standing by.

#include "src/rel/searcher.inc"

typedef struct GadgetSearchLight {
	TEnemyGadget base;
	TObjEnemy* enemy; // 0x38
	u8 unk3C[0x10];
	RpClump* lamp; // 0x4C
} GadgetSearchLight;

namespace nRender
{
void SaveRenderState();
void LoadRenderState();
void SetRenderStateForBlendAdd();
void DisableLight(int light);
void EnableLight(int light);
void SetLightNum(u32 count);
} // namespace nRender

extern "C" const f32 gadgetBombViewRadius;

extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" s32 CanDisp__23TEnemyGadgetSearchLightFv(GadgetSearchLight* gadget)
{
	return gadget->base.CheckCameraFrustum(
	    &((Searcher*)gadget->base.pOwner)->pos, gadgetBombViewRadius);
}

extern "C" void DispTrans__23TEnemyGadgetSearchLightFv(GadgetSearchLight* gadget)
{
	nRender::SaveRenderState();
	nRender::SetRenderStateForBlendAdd();
	nRender::DisableLight(0x15);
	fn_8014FF2C(gadget->base.pClump);
	nRender::EnableLight(0x15);
	nRender::LoadRenderState();
}

extern "C" void DispOpaq__23TEnemyGadgetSearchLightFv(GadgetSearchLight* gadget)
{
	if (gadget->lamp != NULL) {
		nRender::SetLightNum(gadget->enemy->GetCurrentLightNum());
		fn_8014FF2C(gadget->lamp);
	}
}

extern "C" s32 ReqGadgetMode__23TEnemyGadgetSearchLightFQ212TEnemyGadget11eGadgetMode(
    GadgetSearchLight* gadget, TEnemyGadget::eGadgetMode mode)
{
	if (gadget->base.gmode == TEnemyGadget::E_GM_STANDBY) {
		gadget->base.gmode = mode;
		return 1;
	}
	return 0;
}
