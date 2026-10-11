// EventManager::connectCurrentMabuta (the PS2 build's name), out of line: it
// swaps the player's eyelid clump shown in the world, taking the current one
// out (removeClump) and adding the new one (addClump), both inlined.
// showHidePlayer inlines it (event_manager_class.inc).

#define EVENT_MABUTA_INLINE

#include "src/rel/event_manager_class.inc"
