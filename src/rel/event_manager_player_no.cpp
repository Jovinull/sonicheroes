// EventManager::evPlayerNo2playerNo (the PS2 build's name): the player an
// event's player number stands for, from the module's table of twelve, or -1
// past it.

#include "src/rel/event_manager_class.inc"

extern "C" const s32 eventPlayerNumbers[12];

s32 EventManager::evPlayerNo2playerNo(s32 player)
{
	if (player >= 12) {
		return -1;
	}
	return eventPlayerNumbers[player];
}
