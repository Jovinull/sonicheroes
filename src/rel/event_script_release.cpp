// EventScript::ReleaseScript (the PS2 build's name): it puts back the light
// table saved when the script started, stops the event's stream unless it is
// already what is playing (a sound mode of 1 stops differently), releases the
// message board's font and forgets the script.

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

extern "C" u8 lbl_802D5E80[];
extern "C" s8 lbl_8042C470;
extern "C" char* fn_800CC300(void);
extern "C" void fn_800CA85C(void);
extern "C" void fn_800CCC6C(char* name);
extern "C" int strcmp(const char* a, const char* b);

void EventScript::ReleaseScript()
{
	memcpy(lbl_802D5E80 + 0x20, saveLightBuffer, 0x340);
	char* playing = fn_800CC300();
	if (playing == NULL || strcmp(bgmName, playing) != 0) {
		switch (lbl_8042C470) {
			case 1:
				fn_800CA85C();
				break;
			default:
				fn_800CCC6C(bgmName);
				break;
		}
	}
	if (message != NULL) {
		message->ReleaseFontFile();
	}
	unk48 = 0;
}
