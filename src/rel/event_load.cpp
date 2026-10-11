// _loadEvent (the PS2 build's name), one of the event hooks stageInit puts in
// main's table: it has the manager load the event (LoadEvent, inlined) and
// answers whether it did; 0 with no manager.

#include "src/rel/event_manager_class.inc"

s32 _loadEvent(s32 event)
{
	if (lbl_8042C6E4 != NULL) {
		return lbl_8042C6E4->LoadEvent(event);
	}
	return 0;
}
