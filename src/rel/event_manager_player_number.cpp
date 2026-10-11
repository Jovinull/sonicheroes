// EventManager::getPlayerNumber (the PS2 build's name): the index of the game's
// player that plays the event's player number (evPlayerNo2playerNo, inlined),
// looking through the eight players for that character; -1 when none does.

#include "src/rel/event_manager_class.inc"

struct EventPlayerWork {
	s8 unk00;       // 0x00
	s8 characterNo; // 0x01
};

extern "C" EventPlayerWork* lbl_802AD0D0[8];

s32 EventManager::getPlayerNumber(s32 player, s32 unused)
{
	s32 character = evPlayerNo2playerNo(player);
	if (character < 0) {
		return -1;
	}
	for (s32 i = 0; i < 8; i++) {
		EventPlayerWork* work = lbl_802AD0D0[i];
		if (work == NULL) {
			return -1;
		}
		if (character == work->characterNo) {
			return i;
		}
	}
	return -1;
}
