// EventScript::pushGameLightData (the PS2 build's name): it saves main's light
// table, which the event's lights replace. LoadScript does the same copy.

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

extern "C" u8 lbl_802D5E80[];

void EventScript::pushGameLightData()
{
	memcpy(saveLightBuffer, lbl_802D5E80 + 0x20, 0x340);
}
