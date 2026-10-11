// EventManager::ReleaseEvent (the PS2 build's name): it ends the loaded event.
// It stops the event's sound when one plays, releases the script and every
// scene with its files and textures (releaseSceneAll, inlined), the event's
// file, and resets the manager (Init, inlined); then it puts the game back:
// the mode switch 0x32 off, the players, the camera and the sound. With no
// event loaded it only turns the mode switch off and answers 0.

#include "src/rel/event_manager_class.inc"

extern "C" void* lbl_8042C1F8;
extern "C" void fn_8004DE10(void* sound, s32 kind);
extern "C" void fn_801329AC();
extern "C" void fn_80018C64();
extern "C" void fn_8009C704(void* players, s32 value);
extern "C" void fn_8004ED48(void* sound);

s32 EventManager::ReleaseEvent()
{
	if (Exist()) {
		if (unkE50 != 0) {
			fn_8004DE10(lbl_8042C1F8, 0xE);
		}
		lbl_8042C6E0->ReleaseScript();
		releaseSceneAll();
		file->ReleaseOneFile();
		Init();
		fn_801329AC();
		SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x32, -1);
		fn_80018C64();
		fn_8009C704(lbl_80303DC8, 0);
		fn_8004ED48(lbl_8042C1F8);
		return 1;
	}
	SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x32, -1);
	return 0;
}
