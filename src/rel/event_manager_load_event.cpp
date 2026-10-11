// EventManager::LoadEvent (the PS2 build's name), out of line: it ends the
// event loaded before (ReleaseEvent, inlined), copies the new event's scenes
// into ARAM (loadEventToAMem) and, when it found any, loads the event's script.
// It answers whether the event was loaded. _loadEvent inlines it
// (event_manager_class.inc).

#define EVENT_LOAD_EVENT_INLINE

#include "src/rel/event_manager_class.inc"
