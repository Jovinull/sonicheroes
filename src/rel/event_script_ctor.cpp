// EventScript's constructor (the PS2 build's name), run by InitEventManager.
// It puts three more of the module's event functions in main's table of event
// hooks (see rel/stage_init.cpp for the first five) and makes the message
// board the script writes on, which only the game modes 0 and 6 have.

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

extern "C" void* lbl_803E7F88[];
extern "C" u8* lbl_8042C180;

void UpdateEndianandOthers();
void ScriptDataSetInfo();
void* GetScriptAddress();

EventScript::EventScript()
{
	lbl_803E7F88[7] = (void*)GetScriptAddress;
	lbl_803E7F88[6] = (void*)UpdateEndianandOthers;
	lbl_803E7F88[5] = (void*)ScriptDataSetInfo;
	switch ((s8)lbl_8042C180[0x13]) {
		case 0:
		case 6:
			message = new MESSAGE(NULL);
			break;
		default:
			message = NULL;
			break;
	}
	unk48 = 0;
}
