// EventManager::Init (the PS2 build's name), out of line: it marks the manager
// as having no event and clears its counters, slots and entries. The
// constructor inlines it, so this copy has no caller and is kept with
// force_active.

#define EVENT_INIT_INLINE

#include "src/rel/event_manager_class.inc"
