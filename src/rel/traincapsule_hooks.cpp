#include "types.h"

// The train capsule's Unload and Load hooks (traincapsuleUnload and
// traincapsuleLoad here): each of its four models and the four extra models
// are released; the module's texture dictionary is made current, the module's
// model archive is read, each model is loaded from its own archive and the
// four extra (wrecked) models by their names.

// one of the family's models: its file name and archive, and the model once
// loaded
typedef struct TraincapsuleModel {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 unk08;
	void* model; // 0x0C
} TraincapsuleModel;

extern "C" TraincapsuleModel traincapsuleModels[4];
extern "C" void* traincapsuleWreckModels[4];
extern "C" char traincapsuleWreckName[];
extern "C" char traincapsuleOutWreckName[];
extern "C" char traincapsuleWreckGlassName[];
extern "C" char traincapsuleOutWreckGlassName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void traincapsuleUnload(void)
{
	for (s32 i = 0; i < 4; i++) {
		if (traincapsuleModels[i].model != NULL) {
			fn_80150958(traincapsuleModels[i].model);
			traincapsuleModels[i].model = NULL;
		}
		if (traincapsuleWreckModels[i] != NULL) {
			fn_80150958(traincapsuleWreckModels[i]);
			traincapsuleWreckModels[i] = NULL;
		}
	}
}

extern "C" void traincapsuleLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	for (s32 i = 0; i < 4; i++) {
		traincapsuleModels[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), traincapsuleModels[i].name),
		    traincapsuleModels[i].archive);
	}
	traincapsuleWreckModels[0] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), traincapsuleWreckName),
	    lbl_802FF5A0);
	traincapsuleWreckModels[2] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), traincapsuleOutWreckName),
	    lbl_802FF5A0);
	traincapsuleWreckModels[1] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), traincapsuleWreckGlassName),
	    lbl_802FF5A0);
	traincapsuleWreckModels[3] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), traincapsuleOutWreckGlassName),
	    lbl_802FF5A0);
}
