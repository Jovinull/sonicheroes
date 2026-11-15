#include "game/rw_stream_chunk.h"

extern "C" {
// Reads chunk headers until one of type `want`, skipping the others; checks its version range.
s32 fn_80192F38(RwStream* stream, u32 want, u32* outSize, u32* outVersion)
{
	u32 type;
	u32 size;
	u32 version;

	while (ChunkHdrRead(stream, &type, &size, &version, NULL)) {
		if (type == want) {
			if (version < 0x31000) {
				RwError error;
				error.pluginID  = RW_ID_CORE_PLUGIN;
				error.errorCode = fn_8019408C(CHUNK_ERROR_VERSION);
				fn_80193FE8(&error);
				return 0;
			}
			if (version > 0x35000) {
				RwError error;
				error.pluginID  = RW_ID_CORE_PLUGIN;
				error.errorCode = fn_8019408C(CHUNK_ERROR_VERSION);
				fn_80193FE8(&error);
				return 0;
			}
			if (version <= 0x33000) {
				RwError error;
				error.pluginID  = RW_ID_CORE_PLUGIN;
				error.errorCode = fn_8019408C(CHUNK_ERROR_VERSION);
				fn_80193FE8(&error);
			}
			if (outSize != NULL)
				*outSize = size;
			if (outVersion != NULL)
				*outVersion = version;
			return 1;
		}
		if (fn_80197D70(stream, size) == 0)
			return 0;
	}
	return 0;
}
}
