// Runs the plugin constructors of the registry on a new object in registration order
// (HYPOTHESIS: _rwPluginRegistryInitObject). When one fails, the destructors of that plugin and
// all earlier ones run in reverse order and null is returned; otherwise returns the registry.
// NonMatching: the retail prologue loads the first registry entry right after saving r31, before
// the other callee-saved registers; this source schedules that load after them (5-7 words differ,
// same instructions). Loop forms, const/volatile qualifiers, C mode, -O2/-O3 and compilers
// GC/1.2.5n-2.6 did not move it.
#include "game/rw_engine.h"

extern "C" {
RwPluginRegistry* fn_80198D5C(RwPluginRegistry* registry, void* object)
{
	RwPluginRegEntry* entry = registry->firstRegEntry;
	while (entry != 0) {
		if (entry->constructCB(object, entry->offset, entry->size) == 0) {
			entry = entry->prevRegEntry;
			while (entry != 0) {
				entry->destructCB(object, entry->offset, entry->size);
				entry = entry->prevRegEntry;
			}
			return 0;
		}
		entry = entry->nextRegEntry;
	}
	return registry;
}
}
