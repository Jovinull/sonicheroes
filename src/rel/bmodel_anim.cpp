#include "types.h"

// BMODEL's light and animation helpers (the PS2 build's names, from
// STAGE.BIN, where it has them), the same in the four stage modules that
// carry BMODEL. ChangeRenderCallbackToSetLightNum hands an atomic (or every
// atomic of a clump) the light-pointer render callback. A BMODEL_ANIMDATA
// holds a hierarchy animation and a UV animation; the UV one is advanced and
// applied once per frame (the update flag), the hierarchy one is set up on a
// clump's hierarchy and moved on by time.

struct RpClump;
struct RpGeometry;
struct RtAnimAnimation;
struct RtAnimInterpolator;
struct RpUVAnimation;

typedef struct RpAtomic RpAtomic;
typedef RpAtomic* (*RpAtomicCallBackRender)(RpAtomic* atomic);

struct RpAtomic {
	u8 unk00[0x18];
	RpGeometry* geometry; // 0x18
	u8 unk1C[0x2C];
	RpAtomicCallBackRender renderCallBack; // 0x48
};

struct OBJ_CUSTOMRENDER {
	void* pData;
	RpAtomicCallBackRender callback;
};

struct RpHAnimHierarchy {
	u32 flags; // 0x00
	u8 unk04[0x1C];
	RtAnimInterpolator* interpolator; // 0x20
};

struct BMODEL_ANIMDATA {
	u8 unk00[0x4];
	RtAnimAnimation* hanim; // 0x04
	u8 unk08[0x4];
	s32 updated;         // 0x0C
	RpUVAnimation** uvb; // 0x10
	u8 unk14[0x4];
}; // 0x18

class HAnimClass
{
public:
	RpHAnimHierarchy* GetHierarchy(RpClump* clump);
	void SetHierarchyForAtomic(RpClump* clump, RpHAnimHierarchy* hierarchy);
};

class BMODEL
{
public:
	static void ChangeRenderCallbackToSetLightNum(RpAtomic* atomic, s8* light);
	static void ChangeRenderCallbackToSetLightNum(RpClump* clump, s8* light);
	static void ClrAnimationUpdateFlag(BMODEL_ANIMDATA* anim);
	static void UpdateUVBAnimAdd(RpClump* clump, BMODEL_ANIMDATA* anim, f32 time);
	static void UpdateHAnimAnimation(RpClump* clump, f32 time, s32 update);
	static void SetupHAnimAnimation(RpClump* clump, BMODEL_ANIMDATA* anim);
	static BMODEL_ANIMDATA* GetAnimFromTable(BMODEL_ANIMDATA* table, s16 no);
};

extern HAnimClass HAnim;

RpAtomic* objCallbackRpAtomicRenderToUseLightPointer(RpAtomic* atomic);
RpAtomic* objCallbackRpAtomicToSetRenderCallbackToUseLightPointer(RpAtomic* atomic, void* data);
RpAtomic* SetAtomicCustomFXData(RpAtomic* atomic, void* data);

extern "C" {
extern const f32 bmodelZero;
s32 RpAtomicMCCSetCustomRenderCallBack(RpAtomic* atomic, OBJ_CUSTOMRENDER* render);
RpAtomic* fn_8014F1B0(RpAtomic* atomic);
void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
void fn_8011B844(RpUVAnimation* anim, f32 time);
void fn_8013F3A4(RpHAnimHierarchy* hierarchy);
void fn_8013FC30(RpHAnimHierarchy* hierarchy);
void fn_8020C72C(RtAnimInterpolator* interpolator, RtAnimAnimation* anim);
void fn_8020D02C(RtAnimInterpolator* interpolator, f32 time);
u32 fn_80226468(RpGeometry* geometry);
void fn_80226440(RpAtomic* atomic, void* data);
}

void BMODEL::ChangeRenderCallbackToSetLightNum(RpAtomic* atomic, s8* light)
{
	OBJ_CUSTOMRENDER cr;
	RpAtomicCallBackRender callback = atomic->renderCallBack;

	if (callback == objCallbackRpAtomicRenderToUseLightPointer) {
		cr.pData = light;
		return;
	}
	cr.callback = callback;
	cr.pData    = light;
	RpAtomicMCCSetCustomRenderCallBack(atomic, &cr);
	atomic->renderCallBack = objCallbackRpAtomicRenderToUseLightPointer;
	if (!atomic->renderCallBack) {
		atomic->renderCallBack = fn_8014F1B0;
	}
}

void BMODEL::ChangeRenderCallbackToSetLightNum(RpClump* clump, s8* light)
{
	fn_8014FFBC(clump, objCallbackRpAtomicToSetRenderCallbackToUseLightPointer, light);
}

void BMODEL::ClrAnimationUpdateFlag(BMODEL_ANIMDATA* anim)
{
	if (anim->updated == 1) {
		anim->updated = 0;
	}
}

void BMODEL::UpdateUVBAnimAdd(RpClump* clump, BMODEL_ANIMDATA* anim, f32 time)
{
	if (anim->updated == 0) {
		fn_8011B844(*anim->uvb, time);
		fn_8014FFBC(clump, SetAtomicCustomFXData, anim->uvb);
		anim->updated = 1;
	}
}

void BMODEL::UpdateHAnimAnimation(RpClump* clump, f32 time, s32 update)
{
	RpHAnimHierarchy* hierarchy;

	if (clump != NULL) {
		hierarchy = HAnim.GetHierarchy(clump);
		if (hierarchy != NULL) {
			fn_8020D02C(hierarchy->interpolator, time);
			if (update == 1) {
				fn_8013FC30(hierarchy);
			}
		}
	}
}

void BMODEL::SetupHAnimAnimation(RpClump* clump, BMODEL_ANIMDATA* anim)
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

// Sets the delta morph animation of an atomic whose geometry has targets
// (GC only; nothing calls it).
RpAtomic* callbackSetDMorphAnimation(RpAtomic* atomic, void* data)
{
	if (fn_80226468(atomic->geometry) != 0) {
		fn_80226440(atomic, data);
	}
	return atomic;
}

BMODEL_ANIMDATA* BMODEL::GetAnimFromTable(BMODEL_ANIMDATA* table, s16 no)
{
	return &table[no];
}
