// EventManager::Exist (the PS2 build's name): whether the manager has an event
// loaded. _eventStart inlines it; the class is in event_manager_class.inc.
//
// Retail's out-of-line copy is the peephole optimiser's branchless form
// (srwi/xori) of the ternary that _eventStart's inlined copy keeps as a
// branch, so this unit turns the optimiser back on.

#pragma peephole on

#define EVENT_EXIST_INLINE

#include "src/rel/event_manager_class.inc"
