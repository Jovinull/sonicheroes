#include "autosaveD/ADV_WINDOW.hpp"
#include "game/ADVERTISE.hpp"
#include "game/TNECFont.hpp"
#include "game/ONEFILE.hpp"
#include "game/ADV_LANGUAGE.hpp"
#include "game/IsndSE.hpp"
#include "game/Input.hpp"
#include "game/heap.h"
#include "rwsdk/rwplcore.h"

const char* WINDOW_FN[5] = {
	"sel_on",
	"sel_of",
	"sel_ok",
	"win_in",
	"corner",
};

TOBJECT_CLASS_NAME_DEF(ADV_WINDOW);

RwTexDictionary* g_TEXDICT;
RwTexture* g_TEX[5];

#define SELECT_TEX_1 0
#define SELECT_TEX_2 1
#define WINDOW_WINDOW_TEX 4

int _GetButton(int port) {
	switch (port) {
		case 1:
			return Advertise.GetButton(0);
		case 2:
			return Advertise.GetButton(1);
		case 0:
		default:
			return Advertise.GetButton(-1);
	}
}

void ADV_WINDOW::End() {
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, mRenderParameters[0]);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, mRenderParameters[1]);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, mRenderParameters[2]);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, mRenderParameters[3]);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, mRenderParameters[4]);
	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, mRenderParameters[5]);
	RwRenderStateSet(rwRENDERSTATECULLMODE, mRenderParameters[6]);
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSU, mRenderParameters[7]);
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSV, mRenderParameters[8]);
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, mRenderParameters[9]);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);
}

void ADV_WINDOW::Begin() {
	RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &mRenderParameters[0]);
	RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &mRenderParameters[1]);
	RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &mRenderParameters[2]);
	RwRenderStateGet(rwRENDERSTATESRCBLEND, &mRenderParameters[3]);
	RwRenderStateGet(rwRENDERSTATEDESTBLEND, &mRenderParameters[4]);
	RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &mRenderParameters[5]);
	RwRenderStateGet(rwRENDERSTATECULLMODE, &mRenderParameters[6]);
	RwRenderStateGet(rwRENDERSTATETEXTUREADDRESSU, &mRenderParameters[7]);
	RwRenderStateGet(rwRENDERSTATETEXTUREADDRESSV, &mRenderParameters[8]);
	RwRenderStateGet(rwRENDERSTATEFOGENABLE, &mRenderParameters[9]);

	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERNEAREST);
	RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSU, (void*)rwTEXTUREADDRESSCLAMP);
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSV, (void*)rwTEXTUREADDRESSCLAMP);
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
}

void ADV_WINDOW::DispPoly(const RwRect& rRect, const RwRGBA& rColor) {
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, 0);
	Begin();
	RwIm2DVertex vertices[4];

	RwReal nearScreenZ = RwIm2DGetNearScreenZ();
	vertices[0].x = rRect.x;
	vertices[0].y = rRect.y;
	vertices[0].z = nearScreenZ;

	vertices[1].x = rRect.x;
	vertices[1].y = rRect.y + rRect.h;
	vertices[1].z = nearScreenZ;

	vertices[2].x = rRect.x + rRect.w;
	vertices[2].y = rRect.y;
	vertices[2].z = nearScreenZ;

	vertices[3].x = rRect.x + rRect.w;
	vertices[3].y = rRect.y + rRect.h;
	vertices[3].z = nearScreenZ;

	for (int i = 0; i < ARRAY_SIZE(vertices); i++) {
		vertices[i].emissiveColor = rColor;
	}
	RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, vertices, ARRAY_SIZE(vertices));
	End();
}


void ADV_WINDOW::DispWindow(const RwV3d& rVec3, const RwV2d& rVec2) {
	Begin();
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, g_TEX[WINDOW_WINDOW_TEX]);
	RenderQuad4SKY(rVec3, rVec2);
	End();
}

void ADV_WINDOW::DispSelect(const RwV3d& rVec3, const RwV2d& rVec2, int param_3) {
	Begin();
	if (param_3 != 0) {
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, g_TEX[SELECT_TEX_1]);
	} else {
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, g_TEX[SELECT_TEX_2]);
	}
	RenderQuad2Herf(rVec3, rVec2);
	End();
}

void ADV_WINDOW::Exec() {
	/*
	window->input_delay = unk_0x70
	window->mode = mParam.mMode
	window->input_mode = mParam.unk_0x3C

	window->play_on_confirm = mParam.unk_0x40

	window->close_on_confirm = mParam.unk_0x38
	window->result = unk_0x6C
	*/
	s32 selection;

	if (unk_0x70 == 0) {
		switch (mParam.mMode) {
			case 0:
			case 2:
				switch(_GetButton(mParam.unk_0x3C)) {
					case 0:
						switch (mParam.unk_0x3C) {
							case 1:
								selection = mMenu.UpdateUD(0);
								break;
							case 2:
								selection = mMenu.UpdateUD(1);
								break;
							case 0:
							default:
								selection = mMenu.UpdateUD(-1);
						}

						if (selection == -1 || selection == mMenuSelection) {
							break;
						}
						mMenuSelection = selection;

						if (SndSE != NULL) {
							SndSE->Play(SOUND_ADV_MENU_SCROLL, 0, 0);
						}
						break;
					case 1:
						break;
					case 2:
						unk_0x6C = mMenuSelection;

						if (mParam.unk_0x40 && SndSE != NULL) {
							SndSE->Play(SOUND_ADV_MENU_CONFIRM, 0, 0);
						}

						if (mParam.unk_0x38) {
							ReflectKeyMap1P();
						}
						break;
				}
				break;
			case 1:
				unk_0x6C = 1;
		}
		return;
	}
	unk_0x70--;
}

ADV_WINDOW::~ADV_WINDOW() {}

ADV_WINDOW::ADV_WINDOW(TObject* pParent, const sADV_WINDOW_PARAM& rParam)
	: TObject(pParent)
{
	TOBJECT_SET_CLASS_DATA(ADV_WINDOW)

	mParam = rParam;
	unk_0x6C = 0;
	mMenuSelection = 1;

	ADV_LANGUAGE::strcpy(unk_0x110, rParam.mTitleText);

	ADV_LANGUAGE::strcpy(unk_0x510, rParam.mOptionText1);
	if (rParam.mOptionText1 != 0) {
		mMenu.Add(1);
		mOptionText1Width = NECFont.GetWidth(rParam.mOptionText1);
	} else {
		mOptionText1Width = 0.0f;
	}

	ADV_LANGUAGE::strcpy(unk_0x560, rParam.mOptionText2);
	if (rParam.mOptionText2 != 0) {
		mMenu.Add(2);
		mOptionText2Width = NECFont.GetWidth(rParam.mOptionText2);
	} else {
		mOptionText2Width = 0.0f;
	}

	ADV_LANGUAGE::strcpy(unk_0x610, rParam.mOptionText3);
	if (rParam.mOptionText3 != 0) {
		mMenu.Add(3);
		mOptionText3Width = NECFont.GetWidth(rParam.mOptionText3);
	} else {
		mOptionText3Width = 0.0f;
	}

	switch (rParam.mMode) {
		case 0:
		case 2:
			unk_0x70 = 0;
			break;
		case 1:
			unk_0x70 = 0;
			break;
	}

	if (mParam.mOptionText1 == ADV_LANGUAGE::GetText(ADV_WINDOW_GROUP_TEXT_ID, ADV_WINDOW_FORMAT_TEXT_ID)
	    || mParam.mOptionText1 == ADV_LANGUAGE::GetText(ADV_WINDOW_GROUP_TEXT_ID, ADV_WINDOW_DELETE_TEXT_ID)) {
		if (mParam.mOptionText3 != 0) {
			mMenuSelection = 3;
			mMenu.SetSelect(2);
		} else {
			mMenuSelection = 2;
			mMenu.SetSelect(1);
		}
	}
}

/*

static inline void copy_pair(Pair* destination, const volatile Pair* source)
{
	u32 first  = source->first;
	u32 second = source->second;

	destination->first  = first;
	destination->second = second;
}

struct Pair {
	u32 first;
	u32 second;
};

struct AutosaveState {
	u16* unk_0x0;
	u16* resource_1;
	u16* resource_2;
	u16* resource_3;
	s32 mode;
	Pair unk_0x14;
	u32 unk_0x1C;
	Pair unk_0x20;
	Pair unk_0x28;
	Pair unk_0x30;
	u32 unk_0x38;
	u32 unk_0x3C;
	u32 unk_0x40;
};

sADV_WINDOW_PARAM::operator=(const sADV_WINDOW_PARAM&)
extern "C" void fn_2_3D64(AutosaveState* destination, const AutosaveState* source)
{
	destination->unk_0x0    = source->unk_0x0;
	destination->resource_1 = source->resource_1;
	destination->resource_2 = source->resource_2;
	destination->resource_3 = source->resource_3;
	destination->mode       = source->mode;
	copy_pair(&destination->unk_0x14, &source->unk_0x14);
	destination->unk_0x1C = source->unk_0x1C;
	copy_pair(&destination->unk_0x20, &source->unk_0x20);
	copy_pair(&destination->unk_0x28, &source->unk_0x28);
	copy_pair(&destination->unk_0x30, &source->unk_0x30);
	destination->unk_0x38 = source->unk_0x38;
	destination->unk_0x3C = source->unk_0x3C;
	destination->unk_0x40 = source->unk_0x40;
}
*/

ADV_WINDOW* ADV_WINDOW::Create(TObject *pParent, const sADV_WINDOW_PARAM &rParam) {
	return new ADV_WINDOW(pParent, rParam);
}

void ADV_WINDOW::FinalizeCore()
{
	for (int i = 0; i != 5; i++) {
		g_TEX[i] = 0;
	}

	if (g_TEXDICT != NULL) {
		RwTexDictionaryDestroy(g_TEXDICT);
		g_TEXDICT = NULL;
	}
}

void ADV_WINDOW::InitializeCore(void)
{
	ONEFILE* resource = new ONEFILE("./advertise/adv_window.one", 0);

	if (resource != NULL) {
		void* buffer = MAlloc_BW(0x300000);
		if (buffer != NULL) {
			g_TEXDICT = resource->OneFileLoadTextureDictionay(2, buffer);
			if (g_TEXDICT != NULL) {
				for (int i = 0; i != 5; i++) {
					RwTexture* entry = RwTexDictionaryFindNamedTexture(g_TEXDICT, WINDOW_FN[i]);
					if (entry != NULL) {
						g_TEX[i] = entry;
					}
				}
			}
			Free_BW(buffer);
		}
		delete resource;
	}
}

void ADV_WINDOW::Finalize()
{
	NECFont.Finalize();
	FinalizeCore();
}

void ADV_WINDOW::Initialize()
{
	InitializeCore();
	NECFont.Initialize();
}


void TObject::TDisp() { }

sADV_WINDOW_PARAM::sADV_WINDOW_PARAM() {
	mTitleText   = 0;
	mOptionText1   = 0;
	mOptionText2   = 0;
	mOptionText3   = 0;
	mMode  = 0;
	unk_0x14.x = 0.0f;
	unk_0x14.y = 0.0f;

	unk_0x1C  = 0.0f;
	unk_0x20  = 0.0f;
	unk_0x24  = 0.0f;

	unk_0x28 = 0;
	unk_0x2C  = 0;
	unk_0x30 = RsGlobal.windowWidth;
	unk_0x34  = RsGlobal.windowHeight;
	unk_0x38  = 0;
	unk_0x3C = unk_0x40 = 1;
}
