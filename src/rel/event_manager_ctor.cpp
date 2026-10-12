// EventManager's constructor (the PS2 build's name), out of line: it makes the
// manager's 0x40000-byte buffer and the file reader that loads into it, then
// resets the manager (Init, inlined). InitEventManager inlines it, so this copy
// has no caller and is kept with force_active.

#define EVENT_CTOR_INLINE

#include "src/rel/event_manager_class.inc"
