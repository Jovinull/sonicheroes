#include "types.h"

// The rail change rail's editor-record hooks (railchangerailReset,
// railchangerailUnload and railchangerailLoad here): nothing to reset; the
// model file's model is released; the module's model archive is read and the
// model file's model loaded from it.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile railChangeRailModelFile;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void railchangerailReset(void) { }

extern "C" void railchangerailUnload(void)
{
	ModelFile* file = &railChangeRailModelFile;

	for (int i = 0; i < 1; i++) {
		if (file[i].model != NULL) {
			fn_80150958(file[i].model);
			file[i].model = NULL;
		}
	}
}

extern "C" void railchangerailLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* file = &railChangeRailModelFile;
	for (int i = 0; i < 1; i++) {
		file[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), file[i].name),
		    file[i].archive);
	}
}
