// _eventStart (the PS2 build's name), the event hook ACTION calls through slot
// 3 of main's table (see rel/stage_init.cpp): with an event loaded it switches
// the game into the event mode, starts the event on the player side and marks
// the manager as playing. It answers whether there is a manager at all.

#include "src/rel/event_manager_class.inc"

extern "C" void* lbl_8042C180;
extern "C" void* lbl_80303DC8;
extern "C" void SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(
    void* modeSwitch, s32 mode, s32 value);
extern "C" void fn_8009D1F8(void* players);

s32 _eventStart()
{
	EventManager* manager = lbl_8042C6E4;

	if (manager != NULL) {
		if (manager->Exist()) {
			SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x32, manager->unk28);
			fn_8009D1F8(lbl_80303DC8);
			manager->unk34 = 1;
		}
		return 1;
	}
	return 0;
}
