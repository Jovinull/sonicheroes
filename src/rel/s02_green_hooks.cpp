#include "types.h"

// The greenery's Unload and Load hooks (s02GreenUnload and s02GreenLoad here):
// both models of each of its two kinds are released; the module's texture
// dictionary is made current and each model is loaded by its name, the ones
// whose name is empty being left out (their slot cleared). Each model goes
// through an inline helper, called once per model of a kind.

extern "C" char* s02GreenModelNames[2][2];
extern "C" void* s02GreenModels[2][2];
extern "C" char s02GreenEmptyName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int strcmp(const char* a, const char* b);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

// one model's release
static inline void s02GreenRelease(void** model)
{
	if (*model != NULL) {
		fn_80150958(*model);
		*model = NULL;
	}
}

// one model's load, by its name unless the name is empty
static inline void s02GreenLoadModel(void** model, char** name)
{
	if (strcmp(*name, s02GreenEmptyName) != 0) {
		*model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), *name), lbl_802FF5A0);
	} else {
		*model = NULL;
	}
}

extern "C" void s02GreenUnload(void)
{
	for (u8 i = 0; i < 2; i++) {
		s02GreenRelease(&s02GreenModels[i][0]);
		s02GreenRelease(&s02GreenModels[i][1]);
	}
}

extern "C" void s02GreenLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	for (u8 i = 0; i < 2; i++) {
		s02GreenLoadModel(&s02GreenModels[i][0], &s02GreenModelNames[i][0]);
		s02GreenLoadModel(&s02GreenModels[i][1], &s02GreenModelNames[i][1]);
	}
}
