#include "types.h"

// The small cannon's Unload and Load hooks (s13HoudaiSUnload and
// s13HoudaiSLoad here): its model files are released; when the module's
// texture dictionary is there, it is made current, the module's model archive
// is read and each model file loaded. Both run only once in a row, through the
// family's loaded and unloaded flags; two game modes also release and load
// more, and the Load sets a value that depends on the game mode.

typedef struct ModelFile {
	u32 words[9];
	void** resource;
	char* filename;
} ModelFile; // 0x2C

// the game state: only the mode is read here
typedef struct HoudaiSGameState {
	u8 unk00[0x2C];
	s32 mode; // 0x2C
} HoudaiSGameState;

extern "C" ModelFile s13HoudaiSModels[6];
extern "C" s32 s13HoudaiSLoaded;
extern "C" s32 s13HoudaiSUnloaded;
extern "C" s16 s13HoudaiSModeValue;
extern "C" HoudaiSGameState lbl_8029C310;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void fn_9_76448(ModelFile* file);
extern "C" void fn_9_765CC(ModelFile* file, s32 flags);
extern "C" void fn_9_7B778(void);
extern "C" void fn_9_7B808(void);
extern "C" void fn_9_CEF20(void);
extern "C" void fn_9_CEFB0(void);

extern "C" void s13HoudaiSUnload(void)
{
	ModelFile* file = s13HoudaiSModels;

	if (s13HoudaiSUnloaded == 1) {
		return;
	}
	fn_9_7B778();
	if (lbl_8029C310.mode == 15 || lbl_8029C310.mode == 22) {
		fn_9_CEF20();
	}
	for (u8 i = 0; i < 6; i++) {
		fn_9_76448(file);
		file++;
	}
	s13HoudaiSLoaded   = 0;
	s13HoudaiSUnloaded = 1;
}

extern "C" void s13HoudaiSLoad(void)
{
	if (s13HoudaiSLoaded == 1) {
		return;
	}
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* file = s13HoudaiSModels;

	for (u8 i = 0; i < 6; i++) {
		fn_9_765CC(file, 0);
		file++;
	}
	fn_9_7B808();
	if (lbl_8029C310.mode == 15 || lbl_8029C310.mode == 22) {
		fn_9_CEFB0();
	}
	s13HoudaiSLoaded   = 1;
	s13HoudaiSUnloaded = 0;
	switch (lbl_8029C310.mode) {
		case 14:
		case 15:
			s13HoudaiSModeValue = 0x5C00;
			break;
		default:
			s13HoudaiSModeValue = 0;
			break;
	}
}
