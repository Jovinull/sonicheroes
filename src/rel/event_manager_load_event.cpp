// EventManager::LoadEvent (the PS2 build's name): it ends the event loaded
// before (ReleaseEvent, inlined), copies the new event's scenes into ARAM
// (loadEventToAMem) and, when it found any, loads the event's script. It
// answers whether the event was loaded.

#include "src/rel/event_manager_class.inc"

extern "C" void fn_80018C4C();

s32 EventManager::LoadEvent(s32 event)
{
	if (event < 0) {
		return 0;
	}
	ReleaseEvent();
	unk28 = event;
	if (loadEventToAMem()) {
		unkE50 = 0;
		lbl_8042C6E0->LoadScript(event);
		fn_80018C4C();
		return 1;
	}
	return 0;
}
