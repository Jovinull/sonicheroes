// GetScriptAddress (the PS2 build's name), the event hook in slot 7 of main's
// table (set by EventScript's constructor): with a script it copies main's
// light table into the script's data and hands main that data.

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

extern "C" u8 lbl_802D5E80[];
extern "C" void CopyLightData__6CLIGHTFP15REGLIGHT_STRUCT(void* light, void* data);

void* GetScriptAddress()
{
	if (lbl_8042C6E0 != NULL) {
		CopyLightData__6CLIGHTFP15REGLIGHT_STRUCT(lbl_802D5E80, EventScript::scriptData.light);
		return &EventScript::scriptData;
	}
	return NULL;
}
