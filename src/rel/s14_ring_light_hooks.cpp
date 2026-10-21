#include "types.h"

// The unload and load hooks of s14RingLight (stage13D): the unload releases the
// object's one model file entry, the load makes the stage's texture dictionary
// current, reads the stage's object file and loads the entry from it. Same
// body as blinkLightEnd/blinkLightInit (src/stage13D/o_s13_blinklight.cpp),
// with the module's own entry.

typedef struct ModelFile {
	u32 words[9];
	void** resource;
	char* filename;
} ModelFile;

extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];
extern "C" ModelFile s14RingLightModels[1];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void fn_9_76448(ModelFile* file);
extern "C" void fn_9_765CC(ModelFile* file, s32 flags);

extern "C" void s14RingLightUnload(void)
{
	ModelFile* file = s14RingLightModels;

	for (u8 i = 0; i < 1; i++) {
		fn_9_76448(file);
		file++;
	}
}

extern "C" void s14RingLightLoad(void)
{
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* file = s14RingLightModels;

	for (u8 i = 0; i < 1; i++) {
		fn_9_765CC(file, 0);
		file++;
	}
}
