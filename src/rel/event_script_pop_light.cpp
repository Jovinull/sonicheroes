// EventScript::popGameLightData (the PS2 build's name): it puts back main's
// light table saved by pushGameLightData. ReleaseScript does the same copy.

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

extern "C" u8 lbl_802D5E80[];

void EventScript::popGameLightData()
{
	memcpy(lbl_802D5E80 + 0x20, saveLightBuffer, 0x340);
}
