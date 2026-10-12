// The unload and load hooks rel/unbreakable_bob_container_register.cpp puts in
// the editor record for TObjBobcontUnbreakable, the same as the wood crate's
// (rel/wood_container_hooks.cpp).
//
// In stages 0x1A to 0x1C the crate's model and its three kinds of debris come
// out of the stage's ONE file, under the stage's texture dictionary (the load
// gives up if the world has none), and unloading destroys them. Elsewhere the
// load reads them as clumps the stage resource manager owns, and unloading only
// forgets them. The stage test names the stage three times, as in
// rel/unbr_bobcont_create.cpp. The load's two loops have their own counters,
// which is how the original keeps both in the same register.

#include "game/one.h"

struct GameState {
	u8 pad00[0x2C];
	s32 stage; // 0x2C
};

struct BobcontPieceName {
	char* name;
	s32 count;
};

extern "C" GameState lbl_8029C310;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];
extern "C" RpClump* unbrBobcontResource;
extern "C" RpClump* unbrBobcontPieces[3];
extern "C" BobcontPieceName unbrBobcontPieceTable[3];
extern "C" BobcontPieceName unbrBobcontOnePieceTable[3];
extern "C" char unbrBobcontModelName[];
extern "C" char unbrBobcontOneModelName[];

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_801A4C84(void* dictionary);
RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void unbrBobcontObjectUnload(void)
{
	s32 i;

	if (lbl_8029C310.stage == 0x1A || lbl_8029C310.stage == 0x1B || lbl_8029C310.stage == 0x1C) {
		if (unbrBobcontResource != NULL) {
			fn_80150958(unbrBobcontResource);
		}
		for (i = 0; i < 3; i++) {
			if (unbrBobcontPieces[i] != NULL) {
				fn_80150958(unbrBobcontPieces[i]);
			}
		}
	}
	unbrBobcontResource  = NULL;
	unbrBobcontPieces[0] = NULL;
	unbrBobcontPieces[1] = NULL;
	unbrBobcontPieces[2] = NULL;
}

extern "C" void unbrBobcontObjectLoad(void)
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
		unbrBobcontResource
		    = one->LoadClumpEx(one->CheckFileID(unbrBobcontOneModelName), lbl_802FF5A0);
		for (i = 0; i < 3; i++) {
			unbrBobcontPieces[i] = one->LoadClumpEx(
			    one->CheckFileID(unbrBobcontOnePieceTable[i].name), lbl_802FF5A0);
		}
	} else {
		unbrBobcontResource = objPointerReadFromClumpAnim(unbrBobcontModelName);
		for (j = 0; j < 3; j++) {
			unbrBobcontPieces[j] = objPointerReadFromClumpAnim(unbrBobcontPieceTable[j].name);
		}
	}
}
