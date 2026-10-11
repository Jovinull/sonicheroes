// EventManager::loadEventTexdict (the PS2 build's name), out of line: it loads
// the texture dictionary of the manager's event (event%04d.txd). EventRewind
// inlines it, so this copy has no caller and is kept with force_active.

#define EVENT_TEXDICT_INLINE

#include "src/rel/event_manager_class.inc"
