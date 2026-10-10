// The unload and load hooks rel/wood_container_register.cpp puts in the editor
// record for TObjContWood.
//
// In stages 0x1A to 0x1C the crate's model and its three kinds of debris come
// out of the stage's ONE file, under the stage's texture dictionary (the load
// gives up if the world has none), and unloading destroys them. Elsewhere the
// load reads them as clumps the stage resource manager owns, and unloading only
// forgets them. The stage test names the stage three times, as in
// rel/wood_container_create.cpp. The load's two loops have their own counters,
// which is how the original keeps both in the same register.

#include "game/one.h"

struct GameState {
	u8 pad00[0x2C];
	s32 stage; // 0x2C
};

struct WoodPieceName {
	char* name;
	s32 count;
};

extern "C" GameState lbl_8029C310;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];
extern "C" RpClump* woodContainerResource;
extern "C" RpClump* woodContainerPieces[3];
extern "C" WoodPieceName woodContainerPieceTable[3];
extern "C" WoodPieceName woodContainerOnePieceTable[3];
extern "C" char woodContainerModelName[];
extern "C" char woodContainerOneModelName[];

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_801A4C84(void* dictionary);
RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void woodContainerUnload(void)
{
	s32 i;

	if (lbl_8029C310.stage == 0x1A || lbl_8029C310.stage == 0x1B || lbl_8029C310.stage == 0x1C) {
		if (woodContainerResource != NULL) {
			fn_80150958(woodContainerResource);
		}
		for (i = 0; i < 3; i++) {
			if (woodContainerPieces[i] != NULL) {
				fn_80150958(woodContainerPieces[i]);
			}
		}
	}
	woodContainerResource  = NULL;
	woodContainerPieces[0] = NULL;
	woodContainerPieces[1] = NULL;
	woodContainerPieces[2] = NULL;
}

extern "C" void woodContainerLoad(void)
{
	ONEFILE* one;
	s32 i;
	s32 j;

	if (lbl_8029C310.stage == 0x1A || lbl_8029C310.stage == 0x1B || lbl_8029C310.stage == 0x1C) {
		void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);
		if (dictionary != NULL) {
			fn_801A4C84(dictionary);
		} else {
			return;
		}
		one = *(ONEFILE**)(lbl_8042C298 + 0xA50);
		one->LoadOneFile(lbl_802FF5A0);
		woodContainerResource
		    = one->LoadClumpEx(one->CheckFileID(woodContainerOneModelName), lbl_802FF5A0);
		for (i = 0; i < 3; i++) {
			woodContainerPieces[i] = one->LoadClumpEx(
			    one->CheckFileID(woodContainerOnePieceTable[i].name), lbl_802FF5A0);
		}
	} else {
		woodContainerResource = objPointerReadFromClumpAnim(woodContainerModelName);
		for (j = 0; j < 3; j++) {
			woodContainerPieces[j] = objPointerReadFromClumpAnim(woodContainerPieceTable[j].name);
		}
	}
}
