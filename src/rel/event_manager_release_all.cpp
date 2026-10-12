// EventManager::releaseSceneAll (the PS2 build's name), out of line: it
// releases every scene, the event's files kept in ARAM and its texture
// dictionary. ReleaseEvent inlines it (event_manager_class.inc); the
// out-of-line copy has no caller and is kept with force_active.

#define EVENT_RELEASE_ALL_INLINE

#include "src/rel/event_manager_class.inc"
