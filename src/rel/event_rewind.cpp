// _eventRewind (the PS2 build's name), the event hook ACTION calls through
// slot 4 of main's table (see rel/stage_init.cpp): it runs the manager's
// EventRewind, inlined (event_manager_class.inc), and answers whether there is
// a manager.

#include "src/rel/event_manager_class.inc"

s32 _eventRewind()
{
	if (lbl_8042C6E4 != NULL) {
		lbl_8042C6E4->EventRewind();
		return 1;
	}
	return 0;
}
