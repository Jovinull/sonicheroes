#include "types.h"

// TObjEnemySearcher::EnemyMD_WanderWithAttack and EnemyMD_Wander (the PS2
// build's names): wandering turns toward the aim, then walks to it (asking the
// strategy for a search, 0x1E, once there), bobbing all the while; with an
// attack the gadget readies its attack (and ends it), and the kind-1 searcher
// turns its collision on while it runs. Built with deferred inlining like the
// rest of the searcher's file (WanderWithAttack inlines Wander, defined after
// it), so the functions are defined last to first; without fused
// multiply-add, as the retail is.

#include "src/rel/searcher.inc"

#include "src/rel/searcher_turn_to_aim.inc"
#include "src/rel/searcher_walk_to_aim.inc"

extern "C" void EnemyMD_Wander__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
    Searcher* searcher, s32 sub)
{
	switch (sub) {
		case 0:
			break;
		case 1:
			if (searcher->walking) {
				if (!WalkToAim__17TObjEnemySearcherFv(searcher)) {
					searcher->request = 0x1E;
					searcher->walking = 0;
				}
			} else {
				if (TurnToAimForSearcher__17TObjEnemySearcherFv(searcher)) {
					searcher->walking = 1;
				}
			}
			CtrlWaitPos__17TObjEnemySearcherFv(searcher);
			break;
		case 2:
		case 3:
			break;
	}
}

extern "C" void EnemyMD_WanderWithAttack__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
    Searcher* searcher, s32 sub)
{
	switch (sub) {
		case 0:
			if (searcher->gadget != NULL) {
				searcher->gadget->ReqGadgetMode(TEnemyGadget::E_GM_PREATTACK);
			}
			break;
		case 1:
			if (searcher->kind == 1) {
				searcher->colli->flags &= ~0x10;
			}
			break;
		case 2:
			break;
		case 3:
			if (searcher->gadget != NULL) {
				searcher->gadget->ReqGadgetMode(TEnemyGadget::E_GM_POSTATTACK);
			}
			if (searcher->kind == 1) {
				searcher->colli->flags |= 0x10;
			}
			break;
	}
	EnemyMD_Wander__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(searcher, sub);
}
