// EventManager's destructor, out of line in every stage module's run: it
// deletes the ONEFILE and frees the 256 KiB buffer that Init gave the manager,
// then sets mode switch 0x32 to -1. The class is shared through
// event_manager_class.inc.

#include "src/rel/event_manager_class.inc"

extern "C" void* lbl_8042C180;
extern "C" void fn_800126C8(void* buffer);
extern "C" void SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(void* modes, s32 mode, s32 value);

EventManager::~EventManager()
{
	delete file;
	fn_800126C8(buffer);
	SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x32, -1);
}
