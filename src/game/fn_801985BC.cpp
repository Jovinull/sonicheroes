// Returns the stream size of an object's plugin data (HYPOTHESIS: _rwPluginRegistryGetSize): the
// sum over plugins with a size callback reporting data of that size plus a 12-byte chunk header.
// Built with GC/2.0 (configure.py): GC/1.3.2 keeps the first-entry load after the register saves
// (3 words differ). HYPOTHESIS: RenderWare was built with GC/2.x (see fn_8019D0CC).
#include "game/rw_engine.h"

#define RW_CHUNK_HEADER_SIZE 12

extern "C" {
s32 fn_801985BC(const RwPluginRegistry* registry, const void* object)
{
	s32 size                = 0;
	RwPluginRegEntry* entry = registry->firstRegEntry;
	while (entry != 0) {
		if (entry->getSizeCB != 0) {
			s32 pluginSize = entry->getSizeCB(object, entry->offset, entry->size);
			if (pluginSize > 0) {
				size += pluginSize + RW_CHUNK_HEADER_SIZE;
			}
		}
		entry = entry->nextRegEntry;
	}
	return size;
}
}
