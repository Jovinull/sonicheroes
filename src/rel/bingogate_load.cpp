#include "types.h"

// The bingo gate's Load hook (bingogateLoad here): the module's texture dictionary is
// made current, the module's model archive is read and each model file's model loaded from it;
// each model is then handed to the module's texture setup with the
// family's texture name prefix.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile bingogateModelFiles[19];
extern "C" char bingogateTexturePrefix[];
extern "C" u8 lbl_5_bss_2668[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void fn_5_A0238(void* setup, void* clump, char* prefix, s32 a, s32 b, s32 c);

extern "C" void bingogateLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* files = bingogateModelFiles;
	for (int i = 0; i < 19; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		fn_5_A0238(lbl_5_bss_2668, files[i].model, bingogateTexturePrefix, 1, 3, 30);
	}
}
