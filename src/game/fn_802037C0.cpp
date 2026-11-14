// Gives an object a fresh 0x408-byte buffer from free list 5 of lbl_8040EB50, with its two
// trailing words cleared (HYPOTHESIS). Returns the object, or null when no buffer is available
// (the object's buffer pointer is then null).
// NonMatching: the final null test branches the other way round (beq to the null return where
// the retail code uses bne to the object return); 3 words differ.
#include "game/free_lists_8040EB50.h"

static inline Buffer8040EB50* BufferInit(Buffer8040EB50* buffer)
{
	buffer->word400 = 0;
	buffer->count   = 0;
	return buffer;
}

static inline Buffer8040EB50* BufferCreate(void)
{
	Buffer8040EB50* buffer = (Buffer8040EB50*)lbl_8042C9A4->freeListAlloc(
	    lbl_8040EB50.lists[FREE_LIST_8040EB50_BUFFER]);
	if (!buffer) {
		return 0;
	}
	// The retail code tests the initialised buffer once more.
	if (!BufferInit(buffer)) {
		return 0;
	}
	return buffer;
}

extern "C" {
BufferOwner8040EB50* fn_802037C0(BufferOwner8040EB50* owner)
{
	Buffer8040EB50* buffer = BufferCreate();

	owner->buffer = buffer;
	if (!buffer) {
		return 0;
	}
	return owner;
}
}
