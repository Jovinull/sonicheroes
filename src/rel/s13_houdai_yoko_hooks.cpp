#include "types.h"

// The s13HoudaiYoko family's Unload and Load hooks (s13HoudaiYokoUnload and s13HoudaiYokoLoad
// here): its model files are released; when the module's texture dictionary is there, it is made
// current, the module's model archive is read and each model file loaded.

typedef struct ModelFile {
	u32 words[9];
	void** resource;
	char* filename;
} ModelFile; // 0x2C

extern "C" ModelFile s13HoudaiYokoModels[4];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void fn_9_76448(ModelFile* file);
extern "C" void fn_9_765CC(ModelFile* file, s32 flags);
extern "C" void fn_9_7B778(void);
extern "C" void fn_9_7B808(void);

extern "C" void s13HoudaiYokoUnload(void)
{
	ModelFile* file = s13HoudaiYokoModels;
	fn_9_7B778();

	for (u8 i = 0; i < 4; i++) {
		fn_9_76448(file);
		file++;
	}
}

extern "C" void s13HoudaiYokoLoad(void)
{
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* file = s13HoudaiYokoModels;

	for (u8 i = 0; i < 4; i++) {
		fn_9_765CC(file, 0);
		file++;
	}
	fn_9_7B808();
}
