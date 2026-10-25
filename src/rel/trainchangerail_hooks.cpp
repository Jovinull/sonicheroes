#include "types.h"

// The change rails' Unload and Load hooks (trainchangerailUnload and
// trainchangerailLoad here), over 32 numbered rails. Each stage leaves some
// rails out (an inline helper decides which, from the game mode); the Unload
// releases both models of the others. The Load makes the module's texture
// dictionary current and, for each rail that is used, reads the module's model
// archive (once) and loads the rail's two models by its number.

// one rail's two models
typedef struct TrainchangerailModels {
	void* model; // 0x00
	void* other; // 0x04
} TrainchangerailModels;

// the game state (only the mode is read here)
typedef struct TrainchangerailGameState {
	u8 unk00[0x2C];
	s32 mode; // 0x2C
} TrainchangerailGameState;

extern "C" TrainchangerailGameState lbl_8029C310;
extern "C" TrainchangerailModels trainchangerailModels[32];
extern "C" char trainchangerailNameFormat[];
extern "C" char trainchangerailOtherNameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

// whether the current stage leaves rail `rail` out
static inline int trainchangerailUnused(u32 rail)
{
	switch (lbl_8029C310.mode) {
		case 0x13:
			if (rail >= 8) {
				return 1;
			}
			break;
		case 8:
			if (rail >= 0xA8) {
				return 1;
			}
			switch (rail) {
				case 9:
				case 10:
					return 1;
			}
			break;
		case 9:
			if (rail >= 0x48) {
				return 1;
			}
			break;
		case 0x24:
			if (rail >= 0xD8) {
				return 1;
			}
			switch (rail) {
				case 9:
				case 10:
					return 1;
			}
			break;
		case 0x31:
			if (rail >= 0xA8) {
				return 1;
			}
			switch (rail) {
				case 0:
				case 1:
				case 2:
				case 9:
				case 10:
					return 1;
			}
			break;
	}
	return 0;
}

extern "C" void trainchangerailUnload(void)
{
	for (int i = 0; i < 32; i++) {
		if (!trainchangerailUnused(i)) {
			if (trainchangerailModels[i].model != NULL) {
				fn_80150958(trainchangerailModels[i].model);
			}
			if (trainchangerailModels[i].other != NULL) {
				fn_80150958(trainchangerailModels[i].other);
			}
		}
	}
}

extern "C" void trainchangerailLoad(void)
{
	char name[0x40];
	int i;
	int opened = 0;

	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	for (i = 0; i < 32; i++) {
		if (!trainchangerailUnused(i)) {
			if (!opened) {
				LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
				opened = 1;
			}
			sprintf(name, trainchangerailNameFormat, i);
			trainchangerailModels[i].model
			    = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			sprintf(name, trainchangerailOtherNameFormat, i);
			trainchangerailModels[i].other
			    = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		}
	}
}
