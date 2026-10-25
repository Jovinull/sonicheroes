#include "types.h"

// The watersurface family's Reset, Unload and Load hooks (watersurfaceReset,
// watersurfaceUnload and watersurfaceLoad here): nothing to reset; the model
// file's model is released; the module's texture dictionary is made current
// and the model file's model loaded, then put through fn_800BDF30. The
// dictionary also goes through fn_800BE274 before the model and fn_800BE1F4
// after it.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile waterSurfaceModelFile[1];

extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_800BDF30(void* clump);
extern "C" void fn_800BE1F4(void* resource);
extern "C" void fn_800BE274(void* resource);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void watersurfaceReset(void) { }

extern "C" void watersurfaceUnload(void)
{
	ModelFile* files = waterSurfaceModelFile;

	for (int i = 0; i < 1; i++) {
		if (files[i].model != NULL) {
			fn_80150958(files[i].model);
			files[i].model = NULL;
		}
	}
}

extern "C" void watersurfaceLoad(void)
{
	fn_800BE274(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	ModelFile* files = waterSurfaceModelFile;

	for (int i = 0; i < 1; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		fn_800BDF30(files[i].model);
	}
	fn_800BE1F4(*(void**)(lbl_8042C1D0 + 0x8C18));
}
