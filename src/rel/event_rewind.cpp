// _eventRewind (the PS2 build's name), the event hook ACTION calls through
// slot 4 of main's table (see rel/stage_init.cpp). It runs EventManager's
// EventRewind, which the GameCube build only has inlined here: release the
// scenes, clear the slots and entries, load the event's texture dictionary
// and its first cut, restart the script, start the event as _eventStart does,
// run one Exec and leave the event unpaused. It answers whether there is a
// manager.

#include "src/rel/event_manager_class.inc"

extern "C" void* lbl_8042C180;
extern "C" void* lbl_80303DC8;
extern "C" char eventTexdictFormat[];
extern "C" void SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(
    void* modeSwitch, s32 mode, s32 value);
extern "C" void fn_8009D1F8(void* players);
extern "C" int sprintf(char* buffer, const char* format, ...);
void* texLoadTexDictionaryFile(char* name);

inline void EventManager::EventRewind()
{
	unk2C = 0;
	releaseScene(NULL);
	unk3C = 0;
	memset(slots, 0, sizeof(slots));
	memset(entries, 0, sizeof(entries));
	char name[64];
	sprintf(name, eventTexdictFormat, unk28);
	unk38 = (s32)texLoadTexDictionaryFile(name);
	loadScene(unk2C++);
	lbl_8042C6E0->ScriptInit();
	if (Exist()) {
		SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x32, unk28);
		fn_8009D1F8(lbl_80303DC8);
		unk34 = 1;
	}
	unk30 = 0;
	Exec();
	if (unk28 >= 0) {
		unk34 = 0;
	}
}

s32 _eventRewind()
{
	if (lbl_8042C6E4 != NULL) {
		lbl_8042C6E4->EventRewind();
		return 1;
	}
	return 0;
}
