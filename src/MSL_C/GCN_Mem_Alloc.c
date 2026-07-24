#include "types.h"

// Order follows the original binary, which for this compiler is source order.

typedef s32 OSHeapHandle;

extern OSHeapHandle __OSCurrHeap;

void OSReport(const char* msg, ...);
void* OSGetArenaLo(void);
void* OSGetArenaHi(void);
void* OSInitAlloc(void* arenaStart, void* arenaEnd, s32 maxHeaps);
void OSSetArenaLo(void* newLo);
OSHeapHandle OSCreateHeap(void* start, void* end);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap);
void* OSAllocFromHeap(OSHeapHandle heap, u32 size);
void OSFreeToHeap(OSHeapHandle heap, void* ptr);

static inline void InitDefaultHeap(void)
{
	void* arenaLo;
	void* arenaHi;

	OSReport("GCN_Mem_Alloc.c : InitDefaultHeap. No Heap Available\n");
	OSReport("Metrowerks CW runtime library initializing default heap\n");

	arenaLo = OSGetArenaLo();
	arenaHi = OSGetArenaHi();

	arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
	OSSetArenaLo(arenaLo);

	arenaLo = (void*)(((u32)arenaLo + 0x1f) & ~0x1f);
	arenaHi = (void*)((u32)arenaHi & ~0x1f);

	OSSetCurrentHeap(OSCreateHeap(arenaLo, arenaHi));
	OSSetArenaLo(arenaHi);
}

void free(void* ptr)
{
	if (__OSCurrHeap == -1)
		InitDefaultHeap();

	OSFreeToHeap(__OSCurrHeap, ptr);
}

void* malloc(u32 size)
{
	if (__OSCurrHeap == -1)
		InitDefaultHeap();

	return OSAllocFromHeap(__OSCurrHeap, size);
}
