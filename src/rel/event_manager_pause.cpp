// EventManager::EventPause (the PS2 build's name), out of line: with an event
// loaded it marks the event as not playing. EventRewind inlines it, so this
// copy has no caller and is kept with force_active.

#define EVENT_PAUSE_INLINE

#include "src/rel/event_manager_class.inc"
