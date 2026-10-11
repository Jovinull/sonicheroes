// EventManager::getPlayerBodyClump (the PS2 build's name): the body model of
// an event's player. The event players 10 and 12 have theirs in their scene
// slot, 13 is main's, and the others are the game's players
// (getPlayerNumber, inlined).

#include "src/rel/event_manager_class.inc"

extern "C" struct RpClump* lbl_8042B708;

struct RpClump* EventManager::getPlayerBodyClump(s32 player)
{
	switch (player) {
		case 10:
		case 12:
			return slots[player].clump;
		case 13:
			return lbl_8042B708;
		default:
			return lbl_802AD0D0[getPlayerNumber(player, 0)]->clump;
	}
}
