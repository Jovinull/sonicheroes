#include "types.h"

// The seagulls' Unload and Load hooks (kamomeUnload and kamomeLoad here): the
// body model and each of the 45 wing models are released, with the data the
// wing callback gets cleared; the name prefix is "s02" in one game mode and
// the current stage's otherwise; when the module's texture dictionary is
// there, it is kept and made current, the module's model archive is read, the
// body model is loaded (its atomics going through the body callback) and then
// the numbered wing models, each through the wing callback with its own data.

// the game state (only the mode is read here)
typedef struct KamomeGameState {
	u8 unk00[0x2C];
	s32 mode; // 0x2C
} KamomeGameState;

extern "C" KamomeGameState lbl_8029C310;
extern "C" void* kamomeDictionary;
extern "C" void* kamomeBodyModel;
extern "C" void* kamomeWingModels[45];
extern "C" u32 kamomeWingData[45];
extern "C" char* lbl_3_bss_1544;
extern "C" s8 lbl_3_bss_1548;
extern "C" char kamomeStagePrefix[];
extern "C" char kamomeBodyNameFormat[];
extern "C" char kamomeWingName[];
extern "C" char kamomeWingNameFormat1[];
extern "C" char kamomeWingNameFormat2[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" char* fn_800194C4(KamomeGameState* state);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_3_8239C(void* atomic);
extern "C" void* fn_3_823B4(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void kamomeUnload(void)
{
	if (kamomeBodyModel != NULL) {
		fn_80150958(kamomeBodyModel);
		kamomeBodyModel = NULL;
	}
	for (u8 i = 0; i < 45; i++) {
		if (kamomeWingModels[i] != NULL) {
			fn_80150958(kamomeWingModels[i]);
			kamomeWingModels[i] = NULL;
			if (kamomeWingData[i] != 0) {
				kamomeWingData[i] = 0;
			}
		}
	}
}

extern "C" void kamomeLoad(void)
{
	char stageName[8];
	char bodyName[0x40];
	char name[0x40];
	char* prefix;

	if (lbl_8029C310.mode == 0x2A) {
		sprintf(stageName, kamomeStagePrefix);
		prefix = stageName;
	} else {
		prefix = fn_800194C4(&lbl_8029C310);
	}
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		kamomeDictionary = resource;
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	sprintf(bodyName, kamomeBodyNameFormat, prefix);
	if ((kamomeBodyModel = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	         CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), bodyName), lbl_802FF5A0))
	    != NULL) {
		fn_8014FFBC(kamomeBodyModel, fn_3_8239C, NULL);
	}
	if (lbl_3_bss_1548 == 0) {
		lbl_3_bss_1544 = kamomeWingName;
		lbl_3_bss_1548 = 1;
	}
	for (u8 i = 0; i < 45; i++) {
		if (i + 1 < 10) {
			sprintf(name, kamomeWingNameFormat1, prefix, lbl_3_bss_1544, i + 1);
		} else {
			sprintf(name, kamomeWingNameFormat2, prefix, lbl_3_bss_1544, i + 1);
		}
		kamomeWingModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (kamomeWingModels[i] != NULL) {
			fn_8014FFBC(kamomeWingModels[i], fn_3_823B4, &kamomeWingData[i]);
		}
	}
}
