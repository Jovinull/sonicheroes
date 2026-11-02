#include "types.h"

// BMODEL's clump helpers (the PS2 build's names, from STAGE.BIN), the same in
// the four stage modules that carry BMODEL. ClumpSetAnim starts a clump's
// animation (a hierarchy one, as SetupHAnimAnimation does, or for kind 4 a
// delta morph one through fn_801491A8); DestroyClump takes a clump out of its
// world, detaches its hierarchy and frame and destroys it; CloneClump clones
// a BMODEL_DATA entry's clump under a frame, gives it the entry's light and
// shadow callbacks (flag 0x200 with 1 for the shadow and 2 for the light) and
// adds it to the entry's world unless flag 0x400 keeps it out.

struct RpClump;
struct RpAtomic;
struct RpWorld;
struct RtAnimAnimation;
struct RtAnimInterpolator;

struct RwFrame {
	u8 unk00[0x4];
	RwFrame* parent; // 0x04
};

struct RpClumpView {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
};

struct RpHAnimHierarchy {
	u32 flags; // 0x00
	u8 unk04[0x1C];
	RtAnimInterpolator* interpolator; // 0x20
};

struct BMODEL_ANIMDATA {
	s8 kind; // 0x00
	u8 pad01[0x3];
	RtAnimAnimation* hanim; // 0x04
	u8 unk08[0x10];
}; // 0x18

struct BMODEL_DATA {
	u16 flags; // 0x00
	s8 light;  // 0x02
	u8 pad03;
	s32 world;            // 0x04
	RpClump* clump;       // 0x08
	BMODEL_ANIMDATA anim; // 0x0C
	u8 unk24[0x4];
}; // 0x28

struct GameWorld {
	u8 unk0000[0x7250];
	RpWorld* worlds[1]; // 0x7250
};

class HAnimClass
{
public:
	RpHAnimHierarchy* GetHierarchy(RpClump* clump);
	void SetHierarchyForAtomic(RpClump* clump, RpHAnimHierarchy* hierarchy);
};

class BMODEL
{
public:
	static BMODEL_ANIMDATA* ClumpSetAnim(BMODEL_ANIMDATA* anim, RpClump* clump);
	static BMODEL_ANIMDATA* ClumpSetAnim(BMODEL_DATA* data, s16 no, RpClump* clump);
	static void DestroyClump(RpClump** clump);
	static RpClump* CloneClump(BMODEL_DATA* data, s16 no, RpClump** out, RwFrame* parent);
};

extern HAnimClass HAnim;

RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* atomic);
RpAtomic* objCallbackRpAtomicToSetRenderCallbackToUseLightAndShadow(RpAtomic* atomic, void* data);
void objRpClumpForAllAtomicsToSetRenderCallbackToOptimizeShadow(RpClump* clump);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light);

extern "C" {
extern const f32 bmodelZero;
extern GameWorld* lbl_8042C1D0;
void fn_8013F3A4(RpHAnimHierarchy* hierarchy);
void fn_8013F448(RpHAnimHierarchy* hierarchy);
void* fn_8013F484(RwFrame* frame);
void fn_8013FC30(RpHAnimHierarchy* hierarchy);
void fn_8020C72C(RtAnimInterpolator* interpolator, RtAnimAnimation* anim);
void fn_8020D02C(RtAnimInterpolator* interpolator, f32 time);
void fn_801491A8(RpAtomic* atomic);
RpWorld* fn_8015BD78(RpClump* clump);
void fn_8015BBF8(RpWorld* world, RpClump* clump);
void fn_8015BB08(RpWorld* world, RpClump* clump);
void fn_8019EA2C(RwFrame* frame);
void fn_8019E92C(RwFrame* parent, RwFrame* child);
RpClump* fn_80150588(RpClump* clump);
void fn_80150958(RpClump* clump);
void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
}

// BMODEL::SetupHAnimAnimation (rel/bmodel_anim.cpp), inlined.
static inline void bmodelSetupHAnim(RpClump* clump, BMODEL_ANIMDATA* anim)
{
	RpHAnimHierarchy* hierarchy;

	if (clump == NULL || anim->hanim == NULL) {
		return;
	}
	hierarchy = HAnim.GetHierarchy(clump);
	if (hierarchy == NULL) {
		return;
	}
	hierarchy->flags |= 0x3000;
	fn_8013F3A4(hierarchy);
	HAnim.SetHierarchyForAtomic(clump, hierarchy);
	fn_8020C72C(hierarchy->interpolator, anim->hanim);
	fn_8020D02C(hierarchy->interpolator, bmodelZero);
	fn_8013FC30(hierarchy);
}

BMODEL_ANIMDATA* BMODEL::ClumpSetAnim(BMODEL_ANIMDATA* anim, RpClump* clump)
{
	if (clump == NULL) {
		return NULL;
	}
	if (anim->kind == 0) {
		return NULL;
	}
	switch (anim->kind) {
		case 1:
			bmodelSetupHAnim(clump, anim);
			break;
		case 4:
			fn_801491A8(objRpClumpGetAtomic(clump, NULL));
			break;
	}
	return anim;
}

BMODEL_ANIMDATA* BMODEL::ClumpSetAnim(BMODEL_DATA* data, s16 no, RpClump* clump)
{
	BMODEL_DATA* entry = &data[no];
	BMODEL_ANIMDATA* anim;

	if (clump == NULL) {
		return NULL;
	}
	if (entry->anim.kind == 0) {
		return NULL;
	}
	anim = &entry->anim;
	switch (anim->kind) {
		case 1:
			bmodelSetupHAnim(clump, anim);
			break;
	}
	return anim;
}

void BMODEL::DestroyClump(RpClump** pclump)
{
	RpClump* clump = *pclump;

	if (clump != NULL) {
		RpHAnimHierarchy* hierarchy;

		if (fn_8015BD78(clump) != NULL) {
			fn_8015BBF8(fn_8015BD78(clump), clump);
		}
		if (fn_8013F484(((RpClumpView*)clump)->frame) != NULL && clump != NULL
		    && (hierarchy = HAnim.GetHierarchy(clump)) != NULL) {
			fn_8013F448(hierarchy);
		}
		if (((RpClumpView*)clump)->frame->parent != NULL) {
			fn_8019EA2C(((RpClumpView*)clump)->frame);
		}
		fn_80150958(clump);
		*pclump = NULL;
	}
}

RpClump* BMODEL::CloneClump(BMODEL_DATA* data, s16 no, RpClump** out, RwFrame* parent)
{
	BMODEL_DATA* entry = &data[no];
	RpClump* clone     = fn_80150588(entry->clump);

	if (clone != NULL) {
		s32 flags;

		if (parent != NULL) {
			fn_8019E92C(parent, ((RpClumpView*)clone)->frame);
		}
		flags = entry->flags;
		if (flags & 0x200) {
			s32 shadow = flags & 1;

			if (shadow && (flags & 2)) {
				fn_8014FFBC(clone, objCallbackRpAtomicToSetRenderCallbackToUseLightAndShadow,
				    (void*)(s32)entry->light);
			} else if (shadow) {
				objRpClumpForAllAtomicsToSetRenderCallbackToOptimizeShadow(clone);
			} else if (flags & 2) {
				objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clone, entry->light);
			}
		}
		if ((entry->flags & 0x400) == 0) {
			fn_8015BB08(lbl_8042C1D0->worlds[entry->world], clone);
		}
		*out = clone;
	}
	return clone;
}
