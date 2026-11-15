#include "game/rw_stream_chunk.h"

extern "C" {
s32 fn_80192D88(RwStream* stream, u32* type, u32* size, u32* version, u32* build)
{
	return ChunkHdrRead(stream, type, size, version, build);
}
}
