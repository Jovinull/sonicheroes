#include "types.h"

// TObjEnemySearcher::DestroyClump (the PS2 build's name): destroys the motion
// manager, the parts and the clumps (taking the four body clumps out of the
// world first) and kills the gadget.

#include "src/rel/searcher.inc"

typedef struct RpWorld RpWorld;

typedef struct GameScene {
	u8 unk0000[0x729C];
	RpWorld* world; // 0x729C
} GameScene;

extern "C" GameScene* lbl_8042C1D0;

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(RpWorld* world, RpClump* clump);

extern "C" void DestroyClump__17TObjEnemySearcherFv(Searcher* searcher)
{
	s32 i;

	if (searcher->motion != NULL) {
		delete searcher->motion;
		searcher->motion = NULL;
	}
	if (searcher->partsClump != NULL) {
		fn_80150958(searcher->partsClump);
		searcher->partsClump = NULL;
	}
	if (searcher->gadget != NULL) {
		searcher->gadget->flags |= 1;
		searcher->gadget = NULL;
	}
	if (searcher->clump != NULL) {
		fn_80150958(searcher->clump);
		searcher->clump = NULL;
	}
	if (searcher->bodyClump != NULL) {
		fn_80150958(searcher->bodyClump);
		searcher->bodyClump = NULL;
	}
	for (i = 0; i < 4; i++) {
		if (searcher->clumps[i] != NULL) {
			fn_8015BBF8(lbl_8042C1D0->world, searcher->clumps[i]);
			fn_80150958(searcher->clumps[i]);
			searcher->clumps[i] = NULL;
		}
	}
}
