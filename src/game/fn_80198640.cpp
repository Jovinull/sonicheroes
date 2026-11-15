// Writes the plugin data of an object (HYPOTHESIS: _rwPluginRegistryWriteDataChunks): sums the
// stream sizes the plugins report (each non-empty chunk plus its 12-byte header), writes the
// extension chunk header (type 3, library version 0x35000, build 0xFFFF), then for every plugin
// with data writes its chunk header and lets the plugin write its data. Returns the registry, or
// null when a write fails.
#include "game/rw_engine.h"

#define RW_ID_EXTENSION      3
#define RW_LIBRARY_VERSION   0x35000
#define RW_LIBRARY_BUILD     0xFFFF
#define RW_CHUNK_HEADER_SIZE 12

extern "C" {
// HYPOTHESIS: _rwStreamWriteVersionedChunkHeader; returns the stream, or null.
void* fn_80192ED8(void* stream, u32 type, u32 size, u32 version, u32 buildNum);

const RwPluginRegistry* fn_80198640(
    const RwPluginRegistry* registry, void* stream, const void* object)
{
	RwPluginRegEntry* entry;
	s32 size;

	size = 0;
	for (entry = registry->firstRegEntry; entry != 0; entry = entry->nextRegEntry) {
		if (entry->getSizeCB != 0) {
			s32 chunkSize = entry->getSizeCB(object, entry->offset, entry->size);
			if (chunkSize > 0) {
				size += chunkSize + RW_CHUNK_HEADER_SIZE;
			}
		}
	}

	if (fn_80192ED8(stream, RW_ID_EXTENSION, size, RW_LIBRARY_VERSION, RW_LIBRARY_BUILD) == 0) {
		return 0;
	}

	for (RwPluginRegEntry* plugin = registry->firstRegEntry; plugin != 0;
	    plugin                    = plugin->nextRegEntry) {
		if (plugin->getSizeCB != 0 && plugin->writeCB != 0) {
			s32 chunkSize = plugin->getSizeCB(object, plugin->offset, plugin->size);
			if (chunkSize > 0) {
				if (fn_80192ED8(
				        stream, plugin->pluginID, chunkSize, RW_LIBRARY_VERSION, RW_LIBRARY_BUILD)
				    == 0) {
					return 0;
				}
				if (plugin->writeCB(stream, chunkSize, object, plugin->offset, plugin->size) == 0) {
					return 0;
				}
			}
		}
	}
	return registry;
}
}
