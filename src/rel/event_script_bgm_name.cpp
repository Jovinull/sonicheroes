// EventScript::getEventBgmName (the PS2 build's name): the name of the
// event's stream number `bgm`, from the module's table of 15, or NULL.

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

extern "C" char* eventBgmNames[15];

char* EventScript::getEventBgmName(u16 bgm)
{
	if (bgm < 15) {
		return eventBgmNames[bgm];
	}
	return NULL;
}
