// EventManager::showHidePlayer (the PS2 build's name): it shows or hides the
// game's player behind an event's player number (getPlayerNumber, inlined).
// Shown, the player task is told so and the slot's two models go into the
// world (addClump); hidden, the task is told, the models and every eyelid
// clump leave the world (removeClump) and no eyelid stays current
// (connectCurrentMabuta with -1). All three are inlined.

#include "src/rel/event_manager_class.inc"

// The game's player task: two more virtuals past TObject's.
class EventPlayerTask : public TObject
{
public:
	virtual void EventShow();
	virtual void EventHide();
};

extern "C" EventPlayerTask* lbl_802AD070[8];

void EventManager::showHidePlayer(s32 player, s32 show)
{
	s32 no = getPlayerNumber(player, 0);
	if (no >= 0) {
		SceneMemPlayerObj* object = (SceneMemPlayerObj*)&slots[player];
		if (show) {
			lbl_802AD070[no]->EventShow();
			addClump(object->body);
			addClump(object->head);
		} else {
			lbl_802AD070[no]->EventHide();
			removeClump(object->body);
			removeClump(object->head);
			for (s32 i = 0; i < object->mabutaCount; i++) {
				removeClump(object->mabuta[i]);
				connectCurrentMabuta(object, -1);
			}
		}
	}
}
