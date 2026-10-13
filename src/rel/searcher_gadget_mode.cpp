#include "types.h"

// TObjEnemySearcher::ReqChangeGadgetMode (the PS2 build's name): asks the
// gadget for a mode and passes its answer on (0 without a gadget).

#include "src/rel/searcher.inc"

extern "C" s32 ReqChangeGadgetMode__17TObjEnemySearcherFQ212TEnemyGadget11eGadgetMode(
    Searcher* searcher, s32 mode)
{
	if (searcher->gadget != NULL) {
		return searcher->gadget->ReqGadgetMode(mode);
	}
	return 0;
}
