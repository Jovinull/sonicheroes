// Releases an object's 0x408-byte buffer (HYPOTHESIS): clears the buffer's two trailing words and
// returns it to free list 5 of lbl_8040EB50, then clears the object's buffer pointer. Returns the
// object.
#include "game/free_lists_8040EB50.h"

static inline void BufferDestroy(Buffer8040EB50* buffer)
{
	buffer->used  = 0;
	buffer->extra = 0;
	lbl_8042C9A4->freeListFree(lbl_8040EB50.lists[FREE_LIST_8040EB50_BUFFER], buffer);
}

extern "C" {
BufferOwner8040EB50* fn_80203844(BufferOwner8040EB50* owner)
{
	if (owner->buffer) {
		BufferDestroy(owner->buffer);
	}
	owner->buffer = 0;
	return owner;
}
}
