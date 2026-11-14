// Runs the plugin copy callbacks of the registry from src to dst in registration order
// (HYPOTHESIS: _rwPluginRegistryCopyObject). Returns the registry.
// NonMatching: the retail prologue loads the first registry entry right after saving r31, before
// the other callee-saved registers; this source schedules that load after them (5-7 words differ,
// same instructions). Loop forms, const/volatile qualifiers, C mode, -O2/-O3 and compilers
// GC/1.2.5n-2.6 did not move it.
#include "game/rw_engine.h"

extern "C" {
RwPluginRegistry* fn_80198E70(RwPluginRegistry* registry, void* dst, const void* src)
{
	RwPluginRegEntry* entry = registry->firstRegEntry;
	while (entry != 0) {
		entry->copyCB(dst, src, entry->offset, entry->size);
		entry = entry->nextRegEntry;
	}
	return registry;
}
}
