// EventManager::EventStart (the PS2 build's name), out of line: with an event
// loaded it switches the game into the event mode, starts the event on the
// player side and marks it as playing. _eventStart and EventRewind inline it;
// an event object calls this copy.

#define EVENT_START_INLINE

#include "src/rel/event_manager_class.inc"
