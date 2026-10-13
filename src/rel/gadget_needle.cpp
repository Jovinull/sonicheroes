#include "types.h"

// TEnemyGadgetNeedle::CanDisp, DispTrans, DispOpaq and ReqGadgetMode (the PS2
// build's names): the needles show once they have grown and while their
// searcher is in the camera; while attacking they are drawn additively, their
// UV animation stepped once a frame for all needle gadgets (needleFx*, ours);
// the body is drawn with the scene's light count; any mode is taken.

#include "src/rel/searcher.inc"

typedef struct RpAtomic RpAtomic;
typedef struct RpUVAnimAnimation RpUVAnimAnimation;

typedef struct GadgetNeedle {
	TEnemyGadget base;
	TObjEnemy* enemy; // 0x38
	f32 growth;       // 0x3C
	RpClump* needles; // 0x40
} GadgetNeedle;

typedef struct GameFrame {
	u8 unk00[0x30];
	s32 frame; // 0x30
} GameFrame;

namespace nRender
{
void SaveRenderState();
void LoadRenderState();
void SetRenderStateForBlendAdd();
void SetLightNum(u32 count);
} // namespace nRender

extern "C" GameFrame* lbl_8042C180;
extern "C" const f32 gadgetBombDragY;
extern "C" const f32 gadgetBombViewRadius;
extern "C" const f32 gadgetBombHardBounce;
extern "C" s32 needleFxFrame;
extern "C" RpUVAnimAnimation* needleFxAnim;
extern "C" RpClump* needleFxClump;
extern "C" u8 needleFxData[];

extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" RpClump* fn_8014FFBC(
    RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
extern "C" s32 fn_8011B844(RpUVAnimAnimation* anim, f32 time);
RpAtomic* SetAtomicCustomFXData(RpAtomic* atomic, void* data);

extern "C" s32 CanDisp__18TEnemyGadgetNeedleFv(GadgetNeedle* gadget)
{
	if (gadget->growth < gadgetBombDragY) {
		return 0;
	}
	return gadget->base.CheckCameraFrustum(
	    &((Searcher*)gadget->base.pOwner)->pos, gadgetBombViewRadius);
}

extern "C" void DispTrans__18TEnemyGadgetNeedleFv(GadgetNeedle* gadget)
{
	if (gadget->base.gmode == TEnemyGadget::E_GM_ATTACK && gadget->needles != NULL) {
		nRender::SaveRenderState();
		nRender::SetRenderStateForBlendAdd();
		s32 frame = lbl_8042C180->frame;

		if (needleFxFrame != frame) {
			needleFxFrame = frame;
			fn_8011B844(needleFxAnim, gadgetBombHardBounce);
			fn_8014FFBC(needleFxClump, SetAtomicCustomFXData, needleFxData);
		}
		fn_8014FF2C(gadget->needles);
		nRender::LoadRenderState();
	}
}

extern "C" void DispOpaq__18TEnemyGadgetNeedleFv(GadgetNeedle* gadget)
{
	nRender::SetLightNum(gadget->enemy->GetCurrentLightNum());
	fn_8014FF2C(gadget->base.pClump);
}

extern "C" s32 ReqGadgetMode__18TEnemyGadgetNeedleFQ212TEnemyGadget11eGadgetMode(
    GadgetNeedle* gadget, TEnemyGadget::eGadgetMode mode)
{
	gadget->base.gmode = mode;
	return 1;
}
