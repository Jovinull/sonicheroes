#include "types.h"

// BMODEL's light-pointer render callback (the PS2 build's names, from
// STAGE.BIN), the same in the four stage modules that carry BMODEL: every
// atomic of a clump renders with the light number the given pointer holds
// at render time, through the material color change plugin's custom render
// slot. The callbacks are global (the PS2 build has them local) as other code
// tests for them.

struct RpAtomic;
struct RpClump;

typedef RpAtomic* (*RpAtomicCallBackRender)(RpAtomic* atomic);

struct RpAtomic {
	u8 unk00[0x48];
	RpAtomicCallBackRender renderCallBack; // 0x48
};

struct OBJ_CUSTOMRENDER {
	void* pData;
	RpAtomicCallBackRender callback;
};

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" {
extern CLIGHT lbl_802D5E80;
OBJ_CUSTOMRENDER* RpAtomicMCCGetCustomRenderCallBack(RpAtomic* atomic);
s32 RpAtomicMCCSetCustomRenderCallBack(RpAtomic* atomic, OBJ_CUSTOMRENDER* render);
RpAtomic* fn_8014F1B0(RpAtomic* atomic);
void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
}

RpAtomic* objCallbackRpAtomicToSetRenderCallbackToUseLightPointer(RpAtomic* atomic, void* data);

void objRpClumpForAllAtomicsToSetRenderCallbackToUseLightPointer(RpClump* clump, s8* light)
{
	fn_8014FFBC(clump, objCallbackRpAtomicToSetRenderCallbackToUseLightPointer, light);
}

RpAtomic* objCallbackRpAtomicRenderToUseLightPointer(RpAtomic* atomic);

RpAtomic* objCallbackRpAtomicToSetRenderCallbackToUseLightPointer(RpAtomic* atomic, void* data)
{
	OBJ_CUSTOMRENDER cr;

	RpAtomicCallBackRender callback = atomic->renderCallBack;

	if (callback == objCallbackRpAtomicRenderToUseLightPointer) {
		cr.pData = data;
		return atomic;
	}
	cr.callback = callback;
	cr.pData    = data;
	RpAtomicMCCSetCustomRenderCallBack(atomic, &cr);
	atomic->renderCallBack = objCallbackRpAtomicRenderToUseLightPointer;
	if (!atomic->renderCallBack) {
		atomic->renderCallBack = fn_8014F1B0;
	}
	return atomic;
}

RpAtomic* objCallbackRpAtomicRenderToUseLightPointer(RpAtomic* atomic)
{
	OBJ_CUSTOMRENDER* cr = RpAtomicMCCGetCustomRenderCallBack(atomic);

	lbl_802D5E80.SetCurrentNum((s8)(s32) * (s8*)cr->pData);
	lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
	cr->callback(atomic);
	return atomic;
}
