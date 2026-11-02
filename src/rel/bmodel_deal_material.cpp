#include "types.h"

// BMODEL's DealMaterial render callback (the PS2 build's names, from
// STAGE.BIN), the same in the four stage modules that carry BMODEL. Each
// atomic gets user data (BMODEL_USERDATA_CNGMAT) with its light number, a
// second light number used while the switch it points at is 1, and a
// DealMaterial that, while the switch is on (and fn_80018C7C allows it),
// draws the atomic untextured in the data's color. DestroyDealMaterial takes
// it all down again.

struct RpAtomic;
struct RpClump;

typedef RpAtomic* (*RpAtomicCallBackRender)(RpAtomic* atomic);

struct RpAtomic {
	u8 unk00[0x48];
	RpAtomicCallBackRender renderCallBack; // 0x48
};

struct RwRGBA {
	u8 red, green, blue, alpha;
};

struct OBJ_CUSTOMRENDER {
	void* pData;
	RpAtomicCallBackRender callback;
};

class DealMaterial
{
public:
	DealMaterial(RpAtomic* atomic);
	~DealMaterial();
	void EnableMatFX();
	void DisableMatFX();
	void DefaultColor();
	void SetColor(RwRGBA* color);
	void DefaultTexture();
	void NoTexture();

	u8 unk00[0x14];
};

struct BMODEL_USERDATA_CNGMAT {
	s8 light;               // 0x00
	s8 switchLight;         // 0x01
	s32* sw;                // 0x04
	DealMaterial* material; // 0x08
	RwRGBA color;           // 0x0C
};

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

class BMODEL
{
public:
	static void DestroyDealMaterial(RpClump* clump);
	static void SetupDealMaterialAndCallback(
	    RpAtomic* atomic, s32* sw, s8 light, s8 switchLight, RwRGBA* color);
	static void SetupDealMaterialAndCallback(
	    RpClump* clump, s32* sw, s8 light, s8 switchLight, RwRGBA* color);
};

extern "C" {
extern CLIGHT lbl_802D5E80;
extern RwRGBA bmodelDefaultColor;
OBJ_CUSTOMRENDER* RpAtomicMCCGetCustomRenderCallBack(RpAtomic* atomic);
s32 RpAtomicMCCSetCustomRenderCallBack(RpAtomic* atomic, OBJ_CUSTOMRENDER* render);
RpAtomic* fn_8014F1B0(RpAtomic* atomic);
void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
s32 fn_80018C7C(void);
}

RpAtomic* callbackDestroyDealMaterial(RpAtomic* atomic, void* data);
RpAtomic* callbackCreateDealMaterialAndSetCallback(RpAtomic* atomic, void* data);
RpAtomic* objCallbackRpAtomicRenderToUseDealMaterial(RpAtomic* atomic);

static inline void bmodelUseLight(s8 light)
{
	lbl_802D5E80.SetCurrentNum(light);
	lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
}

void BMODEL::DestroyDealMaterial(RpClump* clump)
{
	fn_8014FFBC(clump, callbackDestroyDealMaterial, NULL);
}

RpAtomic* callbackDestroyDealMaterial(RpAtomic* atomic, void* data)
{
	OBJ_CUSTOMRENDER* cr            = RpAtomicMCCGetCustomRenderCallBack(atomic);
	RpAtomicCallBackRender callback = atomic->renderCallBack;
	BMODEL_USERDATA_CNGMAT* ud;

	if (cr == NULL || callback != objCallbackRpAtomicRenderToUseDealMaterial) {
		return atomic;
	}
	ud = (BMODEL_USERDATA_CNGMAT*)cr->pData;
	if (ud->material != NULL) {
		ud->material->DefaultTexture();
		ud->material->DefaultColor();
		ud->material->EnableMatFX();
		delete ud->material;
	}
	delete ud;
	return atomic;
}

void BMODEL::SetupDealMaterialAndCallback(
    RpAtomic* atomic, s32* sw, s8 light, s8 switchLight, RwRGBA* color)
{
	BMODEL_USERDATA_CNGMAT data;

	data.light       = light;
	data.sw          = sw;
	data.switchLight = switchLight;
	data.material    = NULL;
	data.color       = bmodelDefaultColor;
	if (color == NULL) {
		data.color = bmodelDefaultColor;
	} else {
		data.color = *color;
	}
	if (atomic->renderCallBack == objCallbackRpAtomicRenderToUseDealMaterial) {
		OBJ_CUSTOMRENDER* cr = RpAtomicMCCGetCustomRenderCallBack(atomic);

		if (cr != NULL) {
			BMODEL_USERDATA_CNGMAT* ud = (BMODEL_USERDATA_CNGMAT*)cr->pData;

			if (ud != NULL) {
				ud->light       = data.light;
				ud->switchLight = data.switchLight;
				ud->sw          = data.sw;
				ud->color       = data.color;
			}
		}
	} else {
		BMODEL_USERDATA_CNGMAT* ud = new BMODEL_USERDATA_CNGMAT;

		if (ud != NULL) {
			OBJ_CUSTOMRENDER cr;

			*ud          = data;
			ud->material = new DealMaterial(atomic);
			cr.callback  = atomic->renderCallBack;
			cr.pData     = ud;
			RpAtomicMCCSetCustomRenderCallBack(atomic, &cr);
			atomic->renderCallBack = objCallbackRpAtomicRenderToUseDealMaterial;
			if (!atomic->renderCallBack) {
				atomic->renderCallBack = fn_8014F1B0;
			}
		}
	}
}

void BMODEL::SetupDealMaterialAndCallback(
    RpClump* clump, s32* sw, s8 light, s8 switchLight, RwRGBA* color)
{
	BMODEL_USERDATA_CNGMAT data;

	data.light       = light;
	data.switchLight = switchLight;
	data.sw          = sw;
	data.material    = NULL;
	if (color == NULL) {
		data.color = bmodelDefaultColor;
	} else {
		data.color = *color;
	}
	fn_8014FFBC(clump, callbackCreateDealMaterialAndSetCallback, &data);
}

RpAtomic* callbackCreateDealMaterialAndSetCallback(RpAtomic* atomic, void* data)
{
	BMODEL_USERDATA_CNGMAT* from = (BMODEL_USERDATA_CNGMAT*)data;
	BMODEL_USERDATA_CNGMAT* ud;
	OBJ_CUSTOMRENDER cr;

	if (atomic->renderCallBack == objCallbackRpAtomicRenderToUseDealMaterial) {
		OBJ_CUSTOMRENDER* cur = RpAtomicMCCGetCustomRenderCallBack(atomic);

		if (cur != NULL) {
			ud = (BMODEL_USERDATA_CNGMAT*)cur->pData;
			if (ud != NULL) {
				ud->light       = from->light;
				ud->switchLight = from->switchLight;
				ud->sw          = from->sw;
				ud->color       = from->color;
			}
		}
		return atomic;
	}
	ud = new BMODEL_USERDATA_CNGMAT;
	if (ud == NULL) {
		return atomic;
	}
	*ud          = *from;
	ud->material = new DealMaterial(atomic);
	cr.callback  = atomic->renderCallBack;
	cr.pData     = ud;
	RpAtomicMCCSetCustomRenderCallBack(atomic, &cr);
	atomic->renderCallBack = objCallbackRpAtomicRenderToUseDealMaterial;
	if (!atomic->renderCallBack) {
		atomic->renderCallBack = fn_8014F1B0;
	}
	return atomic;
}

RpAtomic* objCallbackRpAtomicRenderToUseDealMaterial(RpAtomic* atomic)
{
	OBJ_CUSTOMRENDER* cr       = RpAtomicMCCGetCustomRenderCallBack(atomic);
	BMODEL_USERDATA_CNGMAT* ud = (BMODEL_USERDATA_CNGMAT*)cr->pData;
	DealMaterial* material     = ud->material;
	s32 tinted                 = 0;

	if (material != NULL) {
		if (fn_80018C7C() == 0 && ud->sw != NULL && *ud->sw == 1) {
			material->NoTexture();
			material->SetColor(&ud->color);
			material->DisableMatFX();
			tinted = 1;
		}
		if (ud->light >= 0) {
			bmodelUseLight((s8)(s32)ud->light);
		}
	} else if (fn_80018C7C() == 0 && ud->sw != NULL && *ud->sw == 1) {
		if (ud->switchLight >= 0) {
			bmodelUseLight((s8)(s32)ud->switchLight);
		} else if (ud->light >= 0) {
			bmodelUseLight((s8)(s32)ud->light);
		}
	} else if (ud->light >= 0) {
		bmodelUseLight((s8)(s32)ud->light);
	}
	cr->callback(atomic);
	if (tinted == 1 && material != NULL) {
		material->DefaultTexture();
		material->DefaultColor();
		material->EnableMatFX();
	}
	return atomic;
}
