// EventManager::connectCurrentMabuta (the PS2 build's name): it swaps the
// player's eyelid clump shown in the world, taking the current one out
// (removeClump) and adding the new one (addClump), both inlined.

#include "src/rel/event_manager_class.inc"

void EventManager::connectCurrentMabuta(SceneMemPlayerObj* player, s32 mabuta)
{
	if (player->mabutaNo >= 0) {
		struct RpClump* clump = player->mabuta[player->mabutaNo];
		if (clump != NULL) {
			removeClump(clump);
		}
	}
	if (mabuta >= 0) {
		struct RpClump* clump = player->mabuta[mabuta];
		if (clump != NULL) {
			addClump(clump);
		}
	}
	player->mabutaNo = mabuta;
}
