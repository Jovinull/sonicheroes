#include "types.h"

// The destructible rail's Load hook (destructrailLoad here): the rail layout
// for the current stage is picked, then the module's texture dictionary is
// made current, the module's model archive is read and each model file's
// model loaded from it.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

// the game state (only the stage record is read here)
typedef struct DestructrailGameState {
	u8 unk00[0x34];
	s32* stage; // 0x34: the stage id is its second word
} DestructrailGameState;

extern "C" DestructrailGameState lbl_8029C310;
extern "C" ModelFile destructRailModelFiles[2];
extern "C" void* destructrailLayout;
extern "C" u8 lbl_6_data_7CF8[];
extern "C" u8 lbl_6_data_7D58[];
extern "C" u8 lbl_6_data_7DC8[];
extern "C" u8 lbl_6_data_7E38[];
extern "C" u8 lbl_6_data_7E48[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void destructrailLoad(void)
{
	switch (lbl_8029C310.stage[1]) {
		case 7:
			destructrailLayout = lbl_6_data_7CF8;
			break;
		case 8:
			destructrailLayout = lbl_6_data_7D58;
			break;
		case 0x32:
			destructrailLayout = lbl_6_data_7DC8;
			break;
		case 0x46:
			destructrailLayout = lbl_6_data_7E38;
			break;
		case 0x48:
			destructrailLayout = lbl_6_data_7E48;
			break;
	}
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* files = destructRailModelFiles;

	for (int i = 0; i < 2; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
	}
}
