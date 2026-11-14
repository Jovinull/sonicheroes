// Releases the inflate state of a stream (HYPOTHESIS: zlib inflateEnd): frees its block decoder
// through fn_8017A204 (inflate_blocks_free) and the state itself through the stream's zfree. Returns
// Z_STREAM_ERROR (-2) for an incomplete stream, otherwise Z_OK (0).
#include "types.h"

#define Z_OK           0
#define Z_STREAM_ERROR (-2)

struct InflateState801789A8 {
	unsigned char pad0[0x14];
	void* blocks; // 0x14
};

struct ZStream801789A8 {
	unsigned char pad0[0x1C];
	InflateState801789A8* state;                                          // 0x1C
	void* (*zalloc)(void* opaque, unsigned int items, unsigned int size); // 0x20
	void (*zfree)(void* opaque, void* address);                           // 0x24
	void* opaque;                                                         // 0x28
};

extern "C" {
void fn_8017A204(void* blocks, ZStream801789A8* z);

int fn_801789A8(ZStream801789A8* z)
{
	if (z == 0 || z->state == 0 || z->zfree == 0) {
		return Z_STREAM_ERROR;
	}
	if (z->state->blocks != 0) {
		fn_8017A204(z->state->blocks, z);
	}
	z->zfree(z->opaque, z->state);
	z->state = 0;
	return Z_OK;
}
}
