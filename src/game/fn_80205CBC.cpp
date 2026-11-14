// Allocates `size` bytes (rounded up to 32) from the audio heap (see game/audio_system.h): first
// fit over the free ("MF") blocks, splitting off the rest when it can hold another header, and
// marking the block used ("MB"). Returns the memory after the 0x20-byte header, or null after an
// OSReport of lbl_8023D528 with the request and the total free size.
#include "game/audio_system.h"

extern "C" {
#include "dolphin/os.h"

extern char lbl_8023D528[];
static inline unsigned int PoolHeapFreeSize(void)
{
	unsigned int total = 0;
	BOOL enabled       = OSDisableInterrupts();
	PoolHeapBlock* next;
	PoolHeapBlock* blk;
	if (lbl_8042CF6C != 0 && (blk = (PoolHeapBlock*)lbl_8042CF6C->heap) != 0) {
		for (; (next = blk->next) != 0; blk = next) {
			if (blk->tag == 0x4D46) {
				total += (unsigned char*)next - (unsigned char*)blk - sizeof(PoolHeapBlock);
			}
		}
	}
	OSRestoreInterrupts(enabled);
	return total;
}

void* fn_80205CBC(unsigned int size)
{
	PoolHeapBlock* blk = (PoolHeapBlock*)lbl_8042CF6C->heap;
	PoolHeapBlock* next;
	BOOL enabled   = OSDisableInterrupts();
	unsigned int n = (size + 0x1F) & ~0x1F;
	unsigned int avail;
	for (; (next = blk->next) != 0; blk = next) {
		if (blk->tag == 0x4D46) {
			avail = (unsigned char*)next - (unsigned char*)blk - sizeof(PoolHeapBlock);
			if (avail >= n) {
				goto found;
			}
		}
	}
	OSReport(lbl_8023D528, size, PoolHeapFreeSize());
	OSRestoreInterrupts(enabled);
	return 0;
found:
	if (avail > n + 0x20) {
		PoolHeapBlock* rest = (PoolHeapBlock*)((unsigned char*)(blk + 1) + n);
		rest->tag           = 0x4D46;
		rest->f2            = 0;
		rest->next          = next;
		blk->next           = rest;
	}
	blk->tag = 0x4D42;
	OSRestoreInterrupts(enabled);
	return blk + 1;
}
}
