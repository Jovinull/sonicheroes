#include "types.h"

// TObjEnemySearcher (the PS2 build's names, but for the first, which the PS2
// build lacks): searcherPlaySound plays the searcher's sound 0x4000 where it
// is (what rel/searcher_sound_limit.cpp does for each searcher it collects);
// Cancel cancels the gadget's attack; AddItemBox drops an item box where the
// searcher was destroyed.

#include "src/rel/searcher.inc"

namespace nItemBox
{
void CreateItemBox(RwV3d* pos);
}

extern "C" void* lbl_8042C388;

extern "C" void fn_800B4A38(void* sound, s32 id, void* position, void* owner, s32 a, s32 b, s32 c);

extern "C" void searcherPlaySound(Searcher* searcher)
{
	if (lbl_8042C388 != NULL) {
		fn_800B4A38(lbl_8042C388, 0x4000, &searcher->pos, searcher, 3, 0, 2);
	}
}

extern "C" void Cancel__17TObjEnemySearcherFv(Searcher* searcher)
{
	if (searcher->gadget != NULL) {
		searcher->gadget->Cancel();
	}
}

extern "C" void AddItemBox__17TObjEnemySearcherFP5RwV3d(Searcher* searcher, RwV3d* pos)
{
	nItemBox::CreateItemBox(pos);
}
