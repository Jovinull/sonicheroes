#include "types.h"

// TEnemyGadgetMGun::CanDisp, ReqGadgetMode and DispOpaq (the PS2 build's
// names): the machine gun shows while its searcher is in the camera, takes
// any mode and draws its body with the scene's light count.

#include "src/rel/searcher.inc"

typedef struct GadgetMGun {
	TEnemyGadget base;
	TObjEnemy* enemy; // 0x38
} GadgetMGun;

namespace nRender
{
void SetLightNum(u32 count);
}

extern "C" const f32 gadgetBombViewRadius;

extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" s32 CanDisp__16TEnemyGadgetMGunFv(GadgetMGun* gadget)
{
	return gadget->base.CheckCameraFrustum(
	    &((Searcher*)gadget->base.pOwner)->pos, gadgetBombViewRadius);
}

extern "C" s32 ReqGadgetMode__16TEnemyGadgetMGunFQ212TEnemyGadget11eGadgetMode(
    GadgetMGun* gadget, TEnemyGadget::eGadgetMode mode)
{
	gadget->base.gmode = mode;
	return 1;
}

extern "C" void DispOpaq__16TEnemyGadgetMGunFv(GadgetMGun* gadget)
{
	nRender::SetLightNum(gadget->enemy->GetCurrentLightNum());
	fn_8014FF2C(gadget->base.pClump);
}
