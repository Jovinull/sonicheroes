// Loads bank `id` from a bank image (see game/audio_system.h): the "gcaxMPBW" chunk at 0x10 goes
// to the id's ARAM region through fn_80205848 (callback -1 means no callback and a synchronous
// transfer), and the "gcaxMPBP" chunk after it is copied into a fresh heap block that replaces the
// bank's previous one. Returns the ARAM request index, or -1/-3 for a bad chunk tag, -2 when the
// region is too small, -4 when the heap is full.
#include "game/audio_system.h"

extern "C" {
void* memcpy(void* dst, const void* src, unsigned long n);
int fn_80205848(u32 source, u32 destination, u32 length, PoolRequestCallback callback,
    unsigned int arg, int async);
void fn_80205C10(void* p);
void* fn_80205CBC(unsigned int size);

int fn_80205F9C(
    int id, unsigned char* image, PoolRequestCallback callback, unsigned int arg, int async)
{
	PoolChunk* pool;
	PoolChunk* wave = (PoolChunk*)(image + 0x10);
	int request;
	if (wave->tag0 != 0x67636178 || wave->tag1 != 0x4D504257) {
		return -1;
	}
	if (lbl_8042CF6C->regions[id].size < wave->size) {
		return -2;
	}
	if (callback == (PoolRequestCallback)-1) {
		async    = 0;
		callback = 0;
	}
	request = fn_80205848(
	    (u32)(wave + 1), lbl_8042CF6C->regions[id].offset, wave->size, callback, arg, async);
	pool = (PoolChunk*)((u32)wave + wave->size + sizeof(PoolChunk));
	if (pool->tag0 != 0x67636178 || pool->tag1 != 0x4D504250) {
		return -3;
	}
	if (lbl_8042CF6C->banks[id].data != 0) {
		fn_80205C10(lbl_8042CF6C->banks[id].data);
	}
	lbl_8042CF6C->banks[id].data = (unsigned char*)fn_80205CBC(pool->size);
	if (lbl_8042CF6C->banks[id].data == 0) {
		return -4;
	}
	lbl_8042CF6C->banks[id].size = pool->size;
	memcpy(lbl_8042CF6C->banks[id].data, pool + 1, pool->size);
	return request;
}
}
