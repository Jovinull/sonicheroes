#include "types.h"

// TObjEnemySearcher::CtrlWaitPos and CtrlGadget (the PS2 build's names): the
// bob (see rel/searcher.inc), and, while a mode runs, the collision follows
// the gadget: on while it attacks, off otherwise.

#define SEARCHER_CTRL_WAIT_POS_INLINE
#include "src/rel/searcher.inc"

extern "C" void CtrlGadget__17TObjEnemySearcherFi(Searcher* searcher, s32 sub)
{
	if (searcher->gadget == NULL) {
		return;
	}
	if (sub != 1) {
		return;
	}
	if (searcher->gadget->gmode == TEnemyGadget::E_GM_ATTACK) {
		searcher->colli->flags &= ~0x10;
	} else {
		searcher->colli->flags |= 0x10;
	}
}
