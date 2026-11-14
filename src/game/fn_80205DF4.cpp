// Sets up the audio system's heap (see game/audio_system.h) on the 32-byte aligned part of
// [mem, mem + size): one free block ("MF") spanning it, linked to the end marker ("MB") in the
// last 0x20 bytes. Runs with interrupts disabled.
#include "game/audio_system.h"

extern "C" {
#include "dolphin/os.h"

static inline void ResetPoolHeap(void)
{
	BOOL enabled         = OSDisableInterrupts();
	PoolHeapBlock* first = (PoolHeapBlock*)lbl_8042CF6C->heap;
	PoolHeapBlock* last  = (PoolHeapBlock*)(lbl_8042CF6C->heap + lbl_8042CF6C->heapSize - 0x20);
	first->tag           = 0x4D46;
	first->f2            = 0;
	first->next          = last;
	last->tag            = 0x4D42;
	last->f2             = 0;
	last->next           = 0;
	OSRestoreInterrupts(enabled);
}

void fn_80205DF4(void* mem, unsigned int size)
{
	BOOL enabled       = OSDisableInterrupts();
	lbl_8042CF6C->heap = (unsigned char*)(((unsigned int)mem + 0x1F) & ~0x1F);
	size -= (0x20 - ((unsigned int)mem & 0x1F)) & 0x1F;
	lbl_8042CF6C->heapSize = size & ~3;
	ResetPoolHeap();
	OSRestoreInterrupts(enabled);
}
}
