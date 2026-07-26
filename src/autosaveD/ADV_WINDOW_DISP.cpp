#include "autosaveD/ADV_WINDOW.hpp"
#include "game/ADVERTISE.hpp"
#include "game/TNECFont.hpp"
#include "game/ONEFILE.hpp"
#include "game/ADV_LANGUAGE.hpp"
#include "game/IsndSE.hpp"
#include "game/Input.hpp"
#include "game/heap.h"
#include "rwsdk/rwplcore.h"

extern RwTexDictionary* g_TEXDICT;
extern RwTexture* g_TEX[5];

#define SELECT_TEX_1 0
#define SELECT_TEX_2 1
#define WINDOW_WINDOW_TEX 4

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

void ADV_WINDOW::DispWindow(const RwV3d& rVec3, const RwV2d& rVec2) {
	Begin();
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, g_TEX[WINDOW_WINDOW_TEX]);
	RenderQuad4SKY(rVec3, rVec2);
	End();
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
