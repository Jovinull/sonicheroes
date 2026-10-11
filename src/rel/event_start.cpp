// _eventStart (the PS2 build's name), the event hook ACTION calls through slot
// 3 of main's table (see rel/stage_init.cpp): it runs the manager's
// EventStart, inlined (event_manager_class.inc), and answers whether there is
// a manager.

#include "src/rel/event_manager_class.inc"

s32 _eventStart()
{
	EventManager* manager = lbl_8042C6E4;

	if (manager != NULL) {
		manager->EventStart();
		return 1;
	}
	return 0;
}
