#include "types.h"

// TEnemyGadgetLaser::CanDisp and ReqGadgetMode (the PS2 build's names): the
// laser shows while its emitter is in the camera and takes any mode.

#include "src/rel/searcher.inc"

typedef struct GadgetLaser {
	TEnemyGadget base;
	u8 unk38[0x98];
	RwV3d emitter; // 0xD0
} GadgetLaser;

extern "C" const f32 gadgetLaserViewRadius;

extern "C" s32 CanDisp__17TEnemyGadgetLaserFv(GadgetLaser* gadget)
{
	return gadget->base.CheckCameraFrustum(&gadget->emitter, gadgetLaserViewRadius);
}

extern "C" s32 ReqGadgetMode__17TEnemyGadgetLaserFQ212TEnemyGadget11eGadgetMode(
    GadgetLaser* gadget, TEnemyGadget::eGadgetMode mode)
{
	gadget->base.gmode = mode;
	return 1;
}
