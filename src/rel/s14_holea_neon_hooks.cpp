#include "types.h"

// The s14HoleaNeon family's Unload and Load hooks (s14HoleaNeonUnload and s14HoleaNeonLoad
// here): its model files are released; when the module's texture dictionary is there, it is made
// current, the module's model archive is read and each model file loaded. Both run only once
// in a row, through the family's loaded and unloaded flags.

typedef struct ModelFile {
	u32 words[9];
	void** resource;
	char* filename;
} ModelFile; // 0x2C

extern "C" ModelFile s14HoleaNeonModels[9];
extern "C" s32 s14HoleaNeonLoaded;
extern "C" s32 s14HoleaNeonUnloaded;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void fn_9_76448(ModelFile* file);
extern "C" void fn_9_765CC(ModelFile* file, s32 flags);

extern "C" void s14HoleaNeonUnload(void)
{
	if (s14HoleaNeonUnloaded == 1) {
		return;
	}
	ModelFile* file = s14HoleaNeonModels;

	for (u8 i = 0; i < 9; i++) {
		fn_9_76448(file);
		file++;
	}
	s14HoleaNeonUnloaded = 1;
	s14HoleaNeonLoaded   = 0;
}

extern "C" void s14HoleaNeonLoad(void)
{
	if (s14HoleaNeonLoaded == 1) {
		return;
	}
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* file = s14HoleaNeonModels;

	for (u8 i = 0; i < 9; i++) {
		fn_9_765CC(file, 0);
		file++;
	}
	s14HoleaNeonLoaded   = 1;
	s14HoleaNeonUnloaded = 0;
}
