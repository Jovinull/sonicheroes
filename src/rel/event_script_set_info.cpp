// ScriptDataSetInfo (the PS2 build's name), the event hook in slot 5 of main's
// table (set by EventScript's constructor): with a script and a loaded event
// it fills the script data's header from the game and the manager, and says
// whether it did.

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

extern "C" u8* lbl_8042C180;

s32 ScriptDataSetInfo()
{
	if (lbl_8042C6E0 != NULL && lbl_8042C6E4->Exist()) {
		EventScript::scriptData.unk000C = *(s32*)(lbl_8042C180 + 0x40);
		memcpy(EventScript::scriptData.info, lbl_8042C6E4->objects, 0x140);
		return 1;
	}
	return 0;
}
