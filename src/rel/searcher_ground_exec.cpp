#include "types.h"

// The Disp and Exec of the object each searcher builds into its +0x2F0 field
// (rel/searcher_ground_ctor.cpp), the same in the thirteen stage modules that
// share the engine core. Disp draws nothing. Exec moves the object
// (searcherGroundMove, still assembly); when its owner has died it marks the
// placement and asks to be killed. Otherwise its collision volume is entered
// while the object is alive, and cleared while the game state's three pause
// flags (0x1F to 0x21) are not all clear.

typedef struct GameState {
	u8 unk00[0x1F];
	s8 unk1F; // 0x1F
	s8 unk20; // 0x20
	s8 unk21; // 0x21
} GameState;

typedef struct Placement {
	u8 unk00[0x4];
	u32 flags; // 0x04
} Placement;

typedef struct SearcherGround {
	u8 unk00[0x4];
	u16 signal; // 0x04
	u8 unk06[0xA];
	void* unk10; // 0x10
	u8 unk14[0x4C];
	u8 volume[0x10];      // 0x60
	Placement* placement; // 0x70
} SearcherGround;

extern "C" GameState* lbl_8042C180;
extern "C" void searcherGroundMove(SearcherGround* object);
extern "C" s32 fn_80017800(void* object);
extern "C" void ClearInfo__7C_COLLIFv(void* volume);
extern "C" void Entry__7C_COLLIFv(void* volume);

static inline s32 searcherGroundCanCollide(void)
{
	if (lbl_8042C180->unk1F != 0) {
		return 0;
	}
	if (lbl_8042C180->unk20 != 0) {
		return 0;
	}
	if (lbl_8042C180->unk21 != 0) {
		return 0;
	}
	return 1;
}

extern "C" void searcherGroundDisp(SearcherGround* object) { }

extern "C" void searcherGroundExec(SearcherGround* object)
{
	searcherGroundMove(object);
	if (object->unk10 != NULL && fn_80017800(object->unk10) == 0) {
		object->placement->flags |= 0x10;
		object->signal |= 1;
		return;
	}
	if (searcherGroundCanCollide() == 0) {
		ClearInfo__7C_COLLIFv(object->volume);
		return;
	}
	if (object->placement != NULL && fn_80017800(object) != 0) {
		Entry__7C_COLLIFv(object->volume);
	}
}
