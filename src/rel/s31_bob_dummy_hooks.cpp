// The unload and load hooks rel/s31_bob_dummy_register.cpp puts in the editor
// record for the dummy bobsleigh. The load reads its two models out of the
// stage's ONE file, under the stage's texture dictionary (it gives up if the
// world has none), each named by the table row for the state byte at 0x13; the
// unload destroys them.

#include "game/one.h"

struct S31BobGameState {
	u8 pad00[0x13];
	s8 unk13; // 0x13
};

extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" S31BobGameState* lbl_8042C180;
extern "C" char lbl_802FF5A0[];
extern "C" char* s31bobDummyNames[2][7];
extern "C" RpClump* s31bobDummyModels[2];

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_801A4C84(void* dictionary);

extern "C" void s31bobObjectdummyUnload(void)
{
	for (int i = 0; i < 2; i++) {
		if (s31bobDummyModels[i] != NULL) {
			fn_80150958(s31bobDummyModels[i]);
			s31bobDummyModels[i] = NULL;
		}
	}
}

extern "C" void s31bobObjectdummyLoad(void)
{
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);
	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	ONEFILE* one = *(ONEFILE**)(lbl_8042C298 + 0xA50);
	one->LoadOneFile(lbl_802FF5A0);
	for (int i = 0; i < 2; i++) {
		s31bobDummyModels[i] = one->LoadClumpEx(
		    one->CheckFileID(s31bobDummyNames[i][lbl_8042C180->unk13]), lbl_802FF5A0);
	}
}
