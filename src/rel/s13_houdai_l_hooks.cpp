#include "types.h"

// The large cannon's Unload and Load hooks (s13HoudaiLUnload and
// s13HoudaiLLoad here): its model files are released; when the module's
// texture dictionary is there, it is made current, the module's model archive
// is read and each model file loaded. Both run only once in a row, through the
// family's loaded and unloaded flags, and the Load sets a value that depends on
// the game mode.

typedef struct ModelFile {
	u32 words[9];
	void** resource;
	char* filename;
} ModelFile; // 0x2C

// the game state: only the mode is read here
typedef struct HoudaiLGameState {
	u8 unk00[0x2C];
	s32 mode; // 0x2C
} HoudaiLGameState;

extern "C" ModelFile s13HoudaiLModels[4];
extern "C" s32 s13HoudaiLLoaded;
extern "C" s32 s13HoudaiLUnloaded;
extern "C" s16 s13HoudaiLModeValue;
extern "C" HoudaiLGameState lbl_8029C310;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void fn_9_76448(ModelFile* file);
extern "C" void fn_9_765CC(ModelFile* file, s32 flags);
extern "C" void fn_9_7B778(void);
extern "C" void fn_9_7B808(void);

extern "C" void s13HoudaiLUnload(void)
{
	ModelFile* file = s13HoudaiLModels;

	if (s13HoudaiLUnloaded == 1) {
		return;
	}
	fn_9_7B778();
	for (u8 i = 0; i < 4; i++) {
		fn_9_76448(file);
		file++;
	}
	s13HoudaiLLoaded   = 0;
	s13HoudaiLUnloaded = 1;
}

extern "C" void s13HoudaiLLoad(void)
{
	if (s13HoudaiLLoaded == 1) {
		return;
	}
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* file = s13HoudaiLModels;

	for (u8 i = 0; i < 4; i++) {
		fn_9_765CC(file, 0);
		file++;
	}
	fn_9_7B808();
	s13HoudaiLLoaded   = 1;
	s13HoudaiLUnloaded = 0;
	switch (lbl_8029C310.mode) {
		case 14:
		case 15:
			s13HoudaiLModeValue = 0x5C00;
			break;
		default:
			s13HoudaiLModeValue = 0;
			break;
	}
}
