// EventManager's TDisp and Disp. TDisp lets the event script draw
// (EventScript::ScriptTDisp, empty in this build) while an event is loaded
// (the field at 0x28 is not negative); Disp is empty. The class is shared
// through event_manager_class.inc.

#define EVENT_MANAGER_DTOR_FIRST
#include "src/rel/event_manager_class.inc"

void EventManager::TDisp()
{
	if (unk28 >= 0) {
		lbl_8042C6E0->ScriptTDisp();
	}
}

void EventManager::Disp() { }
