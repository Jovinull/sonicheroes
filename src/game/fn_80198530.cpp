// Runs the rights callback of the plugin registered as pluginID on an object
// (HYPOTHESIS: _rwPluginRegistryInvokeRights). Returns the registry when the plugin exists, has a
// rights callback and that callback succeeds; null otherwise.
// NonMatching: the retail code loads the first registry entry before saving the link register;
// this source (GC/1.3.2 and GC/2.x alike) loads it after the register saves (4 words differ).
#include "game/rw_engine.h"

extern "C" {
RwPluginRegistry* fn_80198530(RwPluginRegistry* registry, u32 pluginID, void* object, u32 extraData)
{
	RwPluginRegEntry* entry = registry->firstRegEntry;
	while (entry != 0) {
		if (entry->pluginID == pluginID) {
			break;
		}
		entry = entry->nextRegEntry;
	}
	if (entry != 0 && entry->rightsCB != 0) {
		if (entry->rightsCB(object, entry->offset, entry->size, extraData)) {
			return registry;
		}
		return 0;
	}
	return 0;
}
}
