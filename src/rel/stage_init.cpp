#include "types.h"

// stageInit, which the module's prolog (rel/prolog.c) calls last: it fills
// main's table of event hooks with the module's event manager functions. The
// PS2 build names it SetEventFuncAddress and the functions InitEventManager,
// EndEventManager and the local _loadEvent, _eventStart and _eventRewind;
// ACTION calls them through the table (src/game/action.cpp): slot 0 makes the
// manager, slot 1 ends it, slot 2 loads an event, slot 4 rewinds it and slot 3
// starts it.

class EventManager;

extern "C" void* lbl_803E7F88[];

EventManager* InitEventManager();
void EndEventManager();
s32 _loadEvent(s32 event);
s32 _eventStart();
s32 _eventRewind();

extern "C" void stageInit(void)
{
	lbl_803E7F88[0] = (void*)InitEventManager;
	lbl_803E7F88[1] = (void*)EndEventManager;
	lbl_803E7F88[3] = (void*)_eventStart;
	lbl_803E7F88[2] = (void*)_loadEvent;
	lbl_803E7F88[4] = (void*)_eventRewind;
}
