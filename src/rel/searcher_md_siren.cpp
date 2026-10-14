#include "types.h"

// TObjEnemySearcher::EnemyMD_Siren, EnemyMD_Destroy, EnemyMD_Attack and
// EnemyMD_Search (the PS2 build's names), the enemy modes for these sub-steps
// (0 start, 1 run, 3 end):
// - Siren: summons its group's waiting enemies (when there are any) with the
//   siren sound 0x4005, then plays 0x4006 while it bobs;
// - Destroy: clears the search light searcher's group standby and destroys it,
//   then kills the object;
// - Attack: readies the gadget's attack (ends it: post-attack); the kind-1
//   searcher bobs and turns its collision on while attacking;
// - Search: turns its light on while it searches (bobbing).
// Built without fused multiply-add, as the retail is.

#include "src/rel/searcher.inc"

namespace nEnemyCommunication
{
int IsExistSummonEnemy(u8 group);
void DeleteStandByEnemy(u8 group);
} // namespace nEnemyCommunication

class TEnemySummon
{
public:
	static void Create(u8 group);
};

extern "C" void* lbl_8042C388;

extern "C" void fn_800B4A38(void* sound, s32 id, void* position, void* owner, s32 a, s32 b, s32 c);

extern "C" void EnemyMD_Siren__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
    Searcher* searcher, s32 sub)
{
	switch (sub) {
		case 0: {
			u8 group = searcher->set->group;

			if (nEnemyCommunication::IsExistSummonEnemy(group)) {
				TEnemySummon::Create(group);
			}
			if (lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x4005, &searcher->pos, NULL, 1, 0, 0);
			}
			break;
		}
		case 1:
			if (lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x4006, &searcher->pos, searcher, 3, 0, 2);
			}
			CtrlWaitPos__17TObjEnemySearcherFv(searcher);
			break;
		case 2:
		case 3:
			break;
	}
}

extern "C" void EnemyMD_Destroy__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
    Searcher* searcher, s32 sub)
{
	switch (sub) {
		case 0:
			if (searcher->kind == 6) {
				nEnemyCommunication::DeleteStandByEnemy(searcher->set->group);
			}
			searcherEnemy(searcher)->DestroyMyself();
			break;
		case 1:
			searcher->signal |= 1;
			break;
		case 2:
		case 3:
			break;
	}
}

extern "C" void EnemyMD_Attack__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
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
				CtrlWaitPos__17TObjEnemySearcherFv(searcher);
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
}

extern "C" void EnemyMD_Search__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
    Searcher* searcher, s32 sub)
{
	switch (sub) {
		case 0:
			searcher->motion->active = 1;
			break;
		case 1:
			CtrlWaitPos__17TObjEnemySearcherFv(searcher);
			break;
		case 2:
			break;
		case 3:
			searcher->motion->active = 0;
			break;
	}
}
