// Releases the block of a stack buffer descriptor when the descriptor owns it, and returns the
// descriptor. The callers around 0x80151000 read stream data through such a descriptor. Field
// names are inferred from this use only.
#include "game/rw_engine.h"

// HYPOTHESIS: a {data, owned} buffer descriptor; the real RenderWare type name is UNKNOWN.
struct RwOwnedBuffer {
	void* data; // 0x0
	s32 owned;  // 0x4: non-zero when data was allocated for this descriptor
};

extern "C" {
RwOwnedBuffer* fn_8019A218(RwOwnedBuffer* buffer)
{
	if (buffer->owned) {
		lbl_8042C9A4->rwfree(buffer->data);
	}
	return buffer;
}
}
