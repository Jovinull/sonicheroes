#include "types.h"

// HERMITCRAB OBJECT's load hook: when the stage has its texture dictionary it
// makes it current (the comma test is rel/e_fan_stage11.cpp's), reads the
// stage's object file and takes the crab's model and its animation from it.

typedef struct RpClump RpClump;

extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern "C" RpClump* hermitcrabModel;
extern "C" void* hermitcrabAnimation;
extern "C" char hermitcrabModelName[];
extern "C" char hermitcrabAnimationName[];
extern "C" void fn_801A4C84(void* dictionary);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, void* name);
extern "C" s32 CheckFileID__7ONEFILEFPc(void* file, const char* name);
extern "C" RpClump* LoadClumpEx__7ONEFILEFUiPc(void* file, s32 id, void* name);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* file, s32 id, void* name);

extern "C" void hermitcrabObjectLoad(void)
{
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);
	if (!(dictionary != NULL && (fn_801A4C84(dictionary), 1))) {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	s32 id = CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), hermitcrabModelName);
	hermitcrabModel = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50), id, lbl_802FF5A0);
	id = CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), hermitcrabAnimationName);
	hermitcrabAnimation
	    = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50), id, lbl_802FF5A0);
}
