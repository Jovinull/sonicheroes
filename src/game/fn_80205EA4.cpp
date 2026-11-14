// Loads sequence bank `id` from a "gcaxMSB " chunk (see game/audio_system.h): the chunk data is
// copied into a fresh heap block that replaces the previous one, then, when `notify` is set, the
// callback runs with `arg` (callback -1 means none). Returns 0, -1 for a bad chunk tag or -2 when
// the heap is full.
#include "game/audio_system.h"

extern "C" {
void* memcpy(void* dst, const void* src, unsigned long n);
void fn_80205C10(void* p);
void* fn_80205CBC(unsigned int size);

int fn_80205EA4(
    int id, PoolChunk* chunk, PoolRequestCallback callback, unsigned int arg, int notify)
{
	if (chunk->tag0 != 0x67636178 || chunk->tag1 != 0x4D534220) {
		return -1;
	}
	if (callback == (PoolRequestCallback)-1) {
		notify   = 0;
		callback = 0;
	}
	if (lbl_8042CF6C->sequences[id].data != 0) {
		fn_80205C10(lbl_8042CF6C->sequences[id].data);
	}
	lbl_8042CF6C->sequences[id].data = (unsigned char*)fn_80205CBC(chunk->size);
	if (lbl_8042CF6C->sequences[id].data == 0) {
		return -2;
	}
	lbl_8042CF6C->sequences[id].size = chunk->size;
	memcpy(lbl_8042CF6C->sequences[id].data, chunk + 1, chunk->size);
	if (notify != 0) {
		callback(arg);
	}
	return 0;
}
}
