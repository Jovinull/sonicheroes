// EndEventManager (the PS2 build's name), the event hook ACTION calls through
// slot 1 of main's table when the act ends (see rel/stage_init.cpp): it
// deletes the event manager and its script. It answers whether there was a
// manager.

#include "src/rel/event_manager_class.inc"

s32 EndEventManager()
{
	if (lbl_8042C6E4 != NULL) {
		delete lbl_8042C6E4;
		lbl_8042C6E4 = NULL;
		if (lbl_8042C6E0 != NULL) {
			delete lbl_8042C6E0;
			lbl_8042C6E0 = NULL;
		}
		return 1;
	}
	return 0;
}
