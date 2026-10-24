#include "types.h"

// The waves' Unload and Load hooks (waveUnload and waveLoad here): each wave's
// model (with the atomic its callback found) and morph animation are released;
// when the module's texture dictionary is there, it is kept and made current,
// the number of waves is set from the game mode (one in two modes, three
// otherwise), the module's model archive is read and each wave's model loaded,
// its atomics going through the family's callback with the wave's index and
// where to keep its atomic. Then each wave's morph animation is loaded, with
// its frame count and the step that plays it in one second kept.

// what the family's callback gets: the wave's index and where to keep the
// atomic it finds
typedef struct WaveCallbackData {
	s8 index;
	void** atomic; // 0x04
} WaveCallbackData;

// the game state (only the mode is read here)
typedef struct WaveGameState {
	u8 unk00[0x2C];
	s32 mode; // 0x2C
} WaveGameState;

extern "C" WaveGameState lbl_8029C310;
extern "C" void* waveModels[3];
extern "C" void* waveAtomics[3];
extern "C" void* waveMorphs[3];
extern "C" char* waveModelNames[3];
extern "C" char* waveMorphNames[3];
extern "C" void* waveDictionary;
extern "C" f32 waveMorphFrames[3];
extern "C" f32 waveMorphStep[3];
extern "C" s8 waveCount;
extern "C" const WaveCallbackData lbl_3_rodata_1618;
extern "C" const f32 lbl_3_rodata_1660;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_8042C340[];
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8013BD74(void* animation);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_3_885A4(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadDeltaMorphEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void* anim, void* morph);

extern "C" void waveUnload(void)
{
	for (s8 i = 0; i < waveCount; i++) {
		if (waveModels[i] != NULL) {
			fn_80150958(waveModels[i]);
			waveModels[i]  = NULL;
			waveAtomics[i] = NULL;
		}
		if (waveMorphs[i] != NULL) {
			fn_8013BD74(waveMorphs[i]);
			waveMorphs[i] = NULL;
		}
	}
}

extern "C" void waveLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		waveDictionary = resource;
		fn_801A4C84(resource);
	} else {
		return;
	}
	s32 mode = lbl_8029C310.mode;
	if (mode == 0x10 || mode == 0x2B) {
		waveCount = 1;
	} else {
		waveCount = 3;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	for (s32 i = 0; i < waveCount; i++) {
		waveModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), waveModelNames[i]),
		    lbl_802FF5A0);
		if (waveModels[i] != NULL) {
			WaveCallbackData data = lbl_3_rodata_1618;

			data.index  = i;
			data.atomic = &waveAtomics[i];
			fn_8014FFBC(waveModels[i], fn_3_885A4, &data);
		}
	}
	for (s8 i = 0; i < waveCount; i++) {
		waveMorphs[i] = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), waveMorphNames[i]),
		    lbl_802FF5A0);
		if (waveMorphs[i] != NULL) {
			waveMorphFrames[i]
			    = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(lbl_8042C340, waveMorphs[i]);
			waveMorphStep[i] = lbl_3_rodata_1660 / waveMorphFrames[i];
		}
	}
}
