// TObjChao's constructor (the PS2 build's name) and the three RenderWare
// helpers the module keeps right after it: SetHierarchyForSkinAtomic,
// GetHierarchy and GetChildFrameHierarchy, the same bodies main has in
// nHierarchy (src/game/enemy/e_utility_hierarchy.cpp). Retail's copies are
// file-static, like rel/e_mask_stage11.cpp's; here they get names of their own
// so the out-of-line GetHierarchy, inlined into the constructor and otherwise
// unreferenced, can be kept with force_active.
//
// The chao takes the placement's position, its distance from the cage and its
// spin. One already freed (condition bit 0x10000) gets state 2 and no model.
// Otherwise it makes its clump with the placement's light set, finds the
// animation hierarchy, hands it to the skinned atomics, starts the module's
// animation at time 0, gives the collision its shape and looks for its cage
// outside the editor (SearchCage), and places itself (SetPosition); both are
// inlined from chao_methods.inc. In the stage mode 8 the placement is marked
// with condition bit 0x10000000.
//
// The unit is built with deferred inlining, which emits in reverse definition
// order: the helpers are defined before the constructor and come out after it.

#include "src/rel/chao_class.inc"
#include "src/rel/chao_methods.inc"

struct ChaoParams {
	f32 offset; // 0x00
	f32 spin;   // 0x04
};

extern "C" char* CL_TObjChao;
extern "C" CCL_INFO chaoCclInfo;
extern "C" RpClump* chaoModel;
extern "C" void* chaoAnim;
extern "C" u8* lbl_8042C180;

extern "C" {
RpClump* fn_80150588(RpClump* model);
void* fn_80226468(void* geometry);
void fn_80226440(RpAtomic* atomic, void* hierarchy);
RpHAnimHierarchy* fn_8013F484(RwFrame* frame);
void fn_8019EB10(RwFrame* frame, RwFrame* (*callback)(RwFrame*, void*), void* data);
void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
void fn_8020C72C(void* interpolator, void* animation);
void fn_8013F3A4(RpHAnimHierarchy* hierarchy);
void fn_8013FC30(RpHAnimHierarchy* hierarchy);
void fn_8020D02C(void* interpolator, f32 time);
void fn_8020CC18(void* interpolator, f32 time);
}
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump*, u32);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);

// C_COLLI::InitShare, still fn_8003BF04 in main's symbols; see
// rel/key_object_class.inc for why the base is taken by reference.
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

RwFrame* chaoGetChildFrameHierarchy(RwFrame* frame, void* data)
{
	RpHAnimHierarchy* hierarchy = fn_8013F484(frame);
	if (hierarchy == NULL) {
		fn_8019EB10(frame, chaoGetChildFrameHierarchy, data);
		return frame;
	} else {
		*(RpHAnimHierarchy**)data = hierarchy;
		return NULL;
	}
}

RpHAnimHierarchy* chaoGetHierarchy(RpClump* clump)
{
	RpHAnimHierarchy* hierarchy = NULL;
	hierarchy                   = fn_8013F484((RwFrame*)((RwObject*)clump)->parent);
	if (hierarchy == NULL)
		fn_8019EB10((RwFrame*)((RwObject*)clump)->parent, chaoGetChildFrameHierarchy, &hierarchy);
	return hierarchy;
}

RpAtomic* chaoSetHierarchyForSkinAtomic(RpAtomic* atomic, void* data)
{
	if (fn_80226468(*(void**)((u8*)atomic + 0x18)) != NULL)
		fn_80226440(atomic, data);
	return atomic;
}

TObjChao::TObjChao(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjChao;
	DispTime  = 0xF0;

	pos                = ObjParam->setData.pos;
	ChaoParams* params = (ChaoParams*)ObjParam->setData.setBuffer;
	offset             = params->offset;
	spin               = params->spin;
	unkEC              = NULL;
	unkDC              = 0;
	angle              = chaoZero[0];

	if (ObjParam->setData.condition.Flag & 0x10000) {
		state = 2;
		clump = NULL;
	} else {
		state    = 1;
		clump    = fn_80150588(chaoModel);
		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, ((flag & 0x1C0000) >> 18) + 4);

		hierarchy = chaoGetHierarchy(clump);
		fn_8014FFBC(clump, chaoSetHierarchyForSkinAtomic, hierarchy);
		hierarchy->flags |= 0x3000;
		fn_8020C72C(hierarchy->currentAnim, chaoAnim);
		fn_8013F3A4(hierarchy);
		fn_8013FC30(hierarchy);
		fn_8020D02C(hierarchy->currentAnim, chaoZero[0]);
		fn_8020CC18(hierarchy->currentAnim, chaoZero[0]);

		if (!OnEdit()) {
			InitShare(*this, &chaoCclInfo, 1, 4);
			SearchCage();
		}
		SetPosition();
	}

	if ((s8)lbl_8042C180[0x24] == 8) {
		ObjParam->setData.condition.Flag |= 0x10000000;
	}
}
