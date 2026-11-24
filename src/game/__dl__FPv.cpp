#include "types.h"

// Same declaration as src/game/Memory.cpp: the RenderWare engine instance's memory callbacks.
struct MemoryAllocator {
	u8 pad[308];
	void* (*Alloc)(u32 size);
	void (*Free)(void* address);
};

extern MemoryAllocator* lbl_8042C9A4;

// The global operator delete frees through the engine instance; the empty exception
// specification is what makes the retail exception table.
void operator delete(void* p) throw()
{
	lbl_8042C9A4->Free(p);
}
