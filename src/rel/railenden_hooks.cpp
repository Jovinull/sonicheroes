#include "types.h"

// The railenden family's Reset, Unload and Load hooks (railendenReset,
// railendenUnload and railendenLoad here): nothing to reset; the model files'
// models are released; the module's texture dictionary is made current, the
// module's model archive is read and each model file's model loaded, the files
// with a hierarchy index also getting the model's animation hierarchy (through
// fn_800F3074), which then goes through fn_8013F3A4.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, the model once loaded, its animation
// hierarchy and the hierarchy index (negative for none).
struct ModelFile {
	const char* name;   // 0x00
	void* archive;      // 0x04
	s32 world;          // 0x08
	void* model;        // 0x0C
	void* hierarchy;    // 0x10
	s32 hierarchyIndex; // 0x14
	u8 unk18[0x8];      // 0x18
};

extern "C" ModelFile railEndEnModelFiles[4];

extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void* fn_800F3074(void* clump);
extern "C" void fn_8013F3A4(void* hierarchy);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void railendenReset(void) { }

extern "C" void railendenUnload(void)
{
	ModelFile* files = railEndEnModelFiles;

	for (int i = 0; i < 4; i++) {
		if (files[i].model != NULL) {
			fn_80150958(files[i].model);
			files[i].model = NULL;
		}
	}
}

extern "C" void railendenLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* files = railEndEnModelFiles;

	for (int i = 0; i < 4; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		if (files[i].hierarchyIndex >= 0) {
			files[i].hierarchy = fn_800F3074(files[i].model);
			fn_8013F3A4(files[i].hierarchy);
		}
	}
}
