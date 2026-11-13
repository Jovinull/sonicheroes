#include "types.h"

// Same declaration as src/game/Memory.cpp: the RenderWare engine instance's memory callbacks.
struct MemoryAllocator {
	u8 pad[308];
	void* (*Alloc)(u32 size);
	void (*Free)(void* address);
};

extern MemoryAllocator* lbl_8042C9A4;

// The global operator new allocates through the engine instance, like THeapCtrl::operator new.
void* operator new(unsigned long size)
{
	return lbl_8042C9A4->Alloc(size);
}
