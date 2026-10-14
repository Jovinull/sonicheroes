#include "types.h"

// TEnemyGadgetBomber::CanDisp, ReqGadgetMode and DispOpaq (the PS2 build's
// names): the bomber shows while its searcher is in the camera and takes a new
// mode only when standing by; it draws its body with the scene's light count,
// and the bomb once it has grown past its first size.

#include "src/rel/searcher.inc"

typedef struct GadgetBomber {
	TEnemyGadget base;
	TObjEnemy* enemy; // 0x38
	u8 unk3C[0x8];
	RpClump* bomb; // 0x44
	f32 bombScale; // 0x48
} GadgetBomber;

namespace nRender
{
void SetLightNum(u32 count);
}

extern "C" const f32 gadgetBombViewRadius;
extern "C" const f32 gadgetBombScaleXZ;

extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" s32 CanDisp__18TEnemyGadgetBomberFv(GadgetBomber* gadget)
{
	return gadget->base.CheckCameraFrustum(
	    &((Searcher*)gadget->base.pOwner)->pos, gadgetBombViewRadius);
}

extern "C" s32 ReqGadgetMode__18TEnemyGadgetBomberFQ212TEnemyGadget11eGadgetMode(
    GadgetBomber* gadget, TEnemyGadget::eGadgetMode mode)
{
	if (gadget->base.gmode == TEnemyGadget::E_GM_STANDBY) {
		gadget->base.gmode = mode;
		return 1;
	}
	return 0;
}

extern "C" void DispOpaq__18TEnemyGadgetBomberFv(GadgetBomber* gadget)
{
	nRender::SetLightNum(gadget->enemy->GetCurrentLightNum());
	fn_8014FF2C(gadget->base.pClump);
	if (gadget->bombScale > gadgetBombScaleXZ) {
		fn_8014FF2C(gadget->bomb);
	}
}
