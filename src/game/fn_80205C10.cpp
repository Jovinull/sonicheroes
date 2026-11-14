// Frees an audio heap allocation (see game/audio_system.h): the block header 0x20 bytes before p
// becomes free ("MF") and is merged with a free successor and a free predecessor.
#include "game/audio_system.h"

extern "C" {
#include "dolphin/os.h"
static inline PoolHeapBlock* FindPrevHeapBlock(PoolHeapBlock* blk)
{
	PoolHeapBlock* prev = 0;
	PoolHeapBlock* cur;
	for (cur = (PoolHeapBlock*)lbl_8042CF6C->heap; cur->next != 0; cur = cur->next) {
		if (cur == blk) {
			return prev;
		}
		prev = cur;
	}
	return 0;
}

void fn_80205C10(void* p)
{
	BOOL enabled       = OSDisableInterrupts();
	PoolHeapBlock* blk = (PoolHeapBlock*)((unsigned char*)p - 0x20);
	PoolHeapBlock* prev;
	blk->tag = 0x4D46;
	if (blk->next != 0 && blk->next->tag == 0x4D46) {
		blk->next = blk->next->next;
	}
	prev = FindPrevHeapBlock(blk);
	if (prev != 0 && prev->tag == 0x4D46) {
		prev->next = blk->next;
	}
	OSRestoreInterrupts(enabled);
}
}
