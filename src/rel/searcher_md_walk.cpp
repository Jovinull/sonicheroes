#include "types.h"

// TObjEnemySearcher::EnemyMD_Turn, EnemyMD_WalkWithAttack, EnemyMD_Walk,
// EnemyMD_Wait and EnemyMD_Idle (the PS2 build's names):
// - Turn does nothing;
// - Walk goes back to the aim it left (turning toward it first), walks to it
//   and then picks the next aim (SetUpAimPositionFirst, inline: the walk goes
//   to and fro), bobbing all the while; leaving, it keeps the aim;
// - WalkWithAttack readies the gadget's attack (and ends it), turns the kind-1
//   searcher's collision on while it runs, and walks (Walk is called);
// - Wait and Idle only bob.
// Built with deferred inlining like the rest of the searcher's file, so the
// functions are defined last to first; without fused multiply-add, as the
// retail is.

#include "src/rel/searcher.inc"

#include "src/rel/searcher_aim_first.inc"
#include "src/rel/searcher_turn_to_aim.inc"
#include "src/rel/searcher_walk_to_aim.inc"

extern "C" void EnemyMD_Idle__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
    Searcher* searcher, s32 sub)
{
	switch (sub) {
		case 0:
			break;
		case 1:
			CtrlWaitPos__17TObjEnemySearcherFv(searcher);
			break;
		case 2:
		case 3:
			break;
	}
}

extern "C" void EnemyMD_Wait__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
    Searcher* searcher, s32 sub)
{
	switch (sub) {
		case 0:
			break;
		case 1:
			CtrlWaitPos__17TObjEnemySearcherFv(searcher);
			break;
		case 2:
		case 3:
			break;
	}
}

extern "C" void EnemyMD_Walk__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
    Searcher* searcher, s32 sub)
{
	switch (sub) {
		case 0:
			searcher->aimPos = searcher->savedAim;
			if (TurnToAimForSearcher__17TObjEnemySearcherFv(searcher)) {
				searcher->walking = 1;
			} else {
				searcher->walking = 0;
			}
			break;
		case 1:
			if (searcher->walking) {
				if (!WalkToAim__17TObjEnemySearcherFv(searcher)) {
					SetUpAimPositionFirst__17TObjEnemySearcherFv(searcher);
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
			break;
		case 3:
			searcher->savedAim = searcher->aimPos;
			break;
	}
}

extern "C" void EnemyMD_WalkWithAttack__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
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
	EnemyMD_Walk__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(searcher, sub);
}

extern "C" void EnemyMD_Turn__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
    Searcher* searcher, s32 sub)
{
}
