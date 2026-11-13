#include "types.h"

// Same declaration as src/game/Memory.cpp: the RenderWare engine instance's memory callbacks.
struct MemoryAllocator {
	u8 pad[308];
	void* (*Alloc)(u32 size);
	void (*Free)(void* address);
};

extern MemoryAllocator* lbl_8042C9A4;

// Frees through the engine instance, the counterpart of operator new (game/__nw__FUl.cpp). That it is
// the global operator delete is a HYPOTHESIS: the symbol keeps its address-based name.
extern "C" void fn_800426B4(void* address)
{
	lbl_8042C9A4->Free(address);
}
