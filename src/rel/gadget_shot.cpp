#include "types.h"

// TEnemyGadgetShot::Cancel, CanDisp, ReqGadgetMode and DispOpaq (the PS2
// build's names): cancelling takes back the shot it has out; the shot gadget
// shows while its searcher is in the camera, takes any mode and draws its body
// with the scene's light count.

#include "src/rel/searcher.inc"

typedef struct GadgetShot {
	TEnemyGadget base;
	TObjEnemy* enemy; // 0x38
	u8 unk3C[0x8];
	s32 shot; // 0x44, the shot's number, -1 for none
} GadgetShot;

class ENEMY_SHOT
{
public:
	static void Cancel(u16 id);
};

namespace nRender
{
void SetLightNum(u32 count);
}

extern "C" const f32 gadgetBombViewRadius;

extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void Cancel__16TEnemyGadgetShotFv(GadgetShot* gadget)
{
	if (gadget->shot != -1) {
		ENEMY_SHOT::Cancel(gadget->shot);
		gadget->shot = -1;
	}
}

extern "C" s32 CanDisp__16TEnemyGadgetShotFv(GadgetShot* gadget)
{
	return gadget->base.CheckCameraFrustum(
	    &((Searcher*)gadget->base.pOwner)->pos, gadgetBombViewRadius);
}

extern "C" s32 ReqGadgetMode__16TEnemyGadgetShotFQ212TEnemyGadget11eGadgetMode(
    GadgetShot* gadget, TEnemyGadget::eGadgetMode mode)
{
	gadget->base.gmode = mode;
	return 1;
}

extern "C" void DispOpaq__16TEnemyGadgetShotFv(GadgetShot* gadget)
{
	nRender::SetLightNum(gadget->enemy->GetCurrentLightNum());
	fn_8014FF2C(gadget->base.pClump);
}
