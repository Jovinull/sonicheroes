// Runs the plugin destructors of the registry on an object in reverse registration order
// (HYPOTHESIS: _rwPluginRegistryDeInitObject). Returns the registry.
// NonMatching: the retail prologue loads the first registry entry right after saving r31, before
// the other callee-saved registers; this source schedules that load after them (5-7 words differ,
// same instructions). Loop forms, const/volatile qualifiers, C mode, -O2/-O3 and compilers
// GC/1.2.5n-2.6 did not move it.
#include "game/rw_engine.h"

extern "C" {
RwPluginRegistry* fn_80198E04(RwPluginRegistry* registry, void* object)
{
	RwPluginRegEntry* entry = registry->lastRegEntry;
	while (entry != 0) {
		entry->destructCB(object, entry->offset, entry->size);
		entry = entry->prevRegEntry;
	}
	return registry;
}
}
