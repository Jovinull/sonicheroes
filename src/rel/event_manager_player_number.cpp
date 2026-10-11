// EventManager::getPlayerNumber (the PS2 build's name), out of line: the index
// of the game's player that plays the event's player number (evPlayerNo2playerNo,
// inlined), looking through the eight players for that character; -1 when none
// does. getPlayerBodyClump inlines it (event_manager_class.inc).

#define EVENT_PLAYER_NUMBER_INLINE

#include "src/rel/event_manager_class.inc"
