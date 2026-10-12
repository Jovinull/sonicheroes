// UpdateEndianandOthers (the PS2 build's name), the event hook in slot 6 of
// main's table (set by EventScript's constructor), out of line: with a script
// it refreshes the manager's table in the script data and byte-swaps the
// data's words and halfwords for main. LoadScript inlines it
// (event_manager_class.inc).

#define EVENT_SCRIPT_SOURCE
#define EVENT_UPDATE_ENDIAN_INLINE

#include "src/rel/event_manager_class.inc"
