// Reads the plugin data of an object (HYPOTHESIS: _rwPluginRegistryReadDataChunks): finds the
// extension chunk (library versions 0x31000 to 0x35000, otherwise error 0x80000004 of plugin 1),
// hands each contained chunk to the plugin registered for its type (skipping chunks with no
// reader), then runs every plugin's always callback. Returns the registry, or null on failure.
#include "game/rw_engine.h"

#define RW_ID_EXTENSION          3
#define RW_CHUNK_HEADER_SIZE     12
#define RW_ERROR_BAD_VERSION     ((s32)0x80000004)
#define RW_STREAM_VERSION_OLDEST 0x31000
#define RW_STREAM_VERSION_NEWEST 0x35000

extern "C" {
// HYPOTHESIS: RwStreamFindChunk, _rwStreamReadChunkHeader and RwStreamSkip.
s32 fn_80192F38(void* stream, u32 type, u32* length, u32* version);
s32 fn_80192D88(void* stream, u32* type, u32* length, u32* version, u32* buildNum);
void* fn_80197D70(void* stream, u32 offset);

const RwPluginRegistry* fn_8019836C(const RwPluginRegistry* registry, void* stream, void* object)
{
	u32 length;
	u32 version;
	RwPluginRegEntry* entry;

	if (!fn_80192F38(stream, RW_ID_EXTENSION, &length, &version)) {
		return 0;
	}
	if (version >= RW_STREAM_VERSION_OLDEST && version <= RW_STREAM_VERSION_NEWEST) {
		while (length != 0) {
			u32 type;
			u32 size;

			if (!fn_80192D88(stream, &type, &size, 0, 0)) {
				return 0;
			}
			entry = registry->firstRegEntry;
			while (entry != 0) {
				if (entry->pluginID == type) {
					break;
				}
				entry = entry->nextRegEntry;
			}
			if (entry != 0 && entry->readCB != 0) {
				if (entry->readCB(stream, size, object, entry->offset, entry->size) == 0) {
					return 0;
				}
			} else if (fn_80197D70(stream, size) == 0) {
				return 0;
			}
			length -= size + RW_CHUNK_HEADER_SIZE;
		}
		for (entry = registry->firstRegEntry; entry != 0; entry = entry->nextRegEntry) {
			if (entry->alwaysCB != 0 && !entry->alwaysCB(object, entry->offset, entry->size)) {
				return 0;
			}
		}
		return registry;
	} else {
		RwError error;
		error.pluginID  = 1;
		error.errorCode = fn_8019408C(RW_ERROR_BAD_VERSION);
		fn_80193FE8(&error);
		return 0;
	}
}
}
