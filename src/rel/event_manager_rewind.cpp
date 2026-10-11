// EventManager::EventRewind (the PS2 build's name), out of line: it releases
// the scenes, clears the slots and entries, loads the event's texture
// dictionary and first cut, restarts the script, starts the event, runs one
// Exec and leaves the event unpaused. _eventRewind inlines it; an event
// object calls this copy.

#define EVENT_REWIND_INLINE

#include "src/rel/event_manager_class.inc"
