#include "types.h"

// TObjEnemySearcher::OnResume, OnSleep and IsSleep (the PS2 build's names):
// waking up shows the body for the light's state (lit: clumps 0 and 2, dark:
// clumps 1 and 3) and wakes the gadget; going to sleep hides all four clumps
// and puts the gadget to sleep; IsSleep keeps the gadget's sleep flag in step
// with the enemy's.

#include "src/rel/searcher.inc"

void objRpClumpForAllAtomicsToRender(RpClump* clump);
void objRpClumpForAllAtomicsToHide(RpClump* clump);

extern "C" int IsSleep__9TObjEnemyFv(Searcher* searcher);

extern "C" void OnResume__17TObjEnemySearcherFv(Searcher* searcher)
{
	if (searcher->gadget != NULL) {
		searcher->gadget->flags &= ~0x10;
	}
	if (searcher->lit) {
		objRpClumpForAllAtomicsToRender(searcher->clumps[0]);
		objRpClumpForAllAtomicsToRender(searcher->clumps[2]);
		objRpClumpForAllAtomicsToHide(searcher->clumps[1]);
		objRpClumpForAllAtomicsToHide(searcher->clumps[3]);
	} else {
		objRpClumpForAllAtomicsToHide(searcher->clumps[0]);
		objRpClumpForAllAtomicsToHide(searcher->clumps[2]);
		objRpClumpForAllAtomicsToRender(searcher->clumps[1]);
		objRpClumpForAllAtomicsToRender(searcher->clumps[3]);
	}
}

extern "C" void OnSleep__17TObjEnemySearcherFv(Searcher* searcher)
{
	s32 i;

	if (searcher->gadget != NULL) {
		searcher->gadget->flags |= 0x10;
	}
	for (i = 0; i < 4; i++) {
		if (searcher->clumps[i] != NULL) {
			objRpClumpForAllAtomicsToHide(searcher->clumps[i]);
		}
	}
}

extern "C" int IsSleep__17TObjEnemySearcherFv(Searcher* searcher)
{
	int sleep = IsSleep__9TObjEnemyFv(searcher);

	if (sleep) {
		if (searcher->gadget != NULL) {
			searcher->gadget->flags |= 0x10;
		}
	} else {
		if (searcher->gadget != NULL) {
			searcher->gadget->flags &= ~0x10;
		}
	}
	return sleep;
}
