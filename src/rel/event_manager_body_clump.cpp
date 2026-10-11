// EventManager::getPlayerBodyClump (the PS2 build's name), out of line: the
// body model of an event's player. The event players 10 and 12 have theirs in
// their scene slot, 13 is main's (Cheese), and the others are the game's
// players (getPlayerNumber, inlined). releaseScene inlines it
// (event_manager_class.inc).

#define EVENT_BODY_CLUMP_INLINE

#include "src/rel/event_manager_class.inc"
