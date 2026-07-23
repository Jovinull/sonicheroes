#include "types.h"

#define NULL 0

typedef int OSHeapHandle;

typedef struct HeapCell {
	struct HeapCell* prev;
	struct HeapCell* next;
	s32 size;
} HeapCell;

typedef struct HeapDesc {
	s32 size;
	HeapCell* free;
	HeapCell* allocated;
} HeapDesc;

#define HEADERSIZE 0x20
#define MINOBJSIZE 0x40

#define OSRoundUp32B(x)   (((u32)(x) + 31) & ~31)
#define OSRoundDown32B(x) ((u32)(x) & ~31)

static HeapDesc* HeapArray;
static int NumHeaps;
static void* ArenaStart;
static void* ArenaEnd;

volatile OSHeapHandle __OSCurrHeap = -1;

static HeapCell* DLInsert(HeapCell* list, HeapCell* cell)
{
	HeapCell* prev;
	HeapCell* next;

	for (next = list, prev = NULL; next != NULL; prev = next, next = next->next) {
		if (cell <= next) {
			break;
		}
	}
	cell->next = next;
	cell->prev = prev;
	if (next != NULL) {
		next->prev = cell;
		if ((u8*)cell + cell->size == (u8*)next) {
			cell->size += next->size;
			next       = next->next;
			cell->next = next;
			if (next != NULL) {
				next->prev = cell;
			}
		}
	}
	if (prev != NULL) {
		prev->next = cell;
		if ((u8*)prev + prev->size == (u8*)cell) {
			prev->size += cell->size;
			prev->next = next;
			if (next != NULL) {
				next->prev = prev;
			}
		}
		return list;
	}
	return cell;
}

static inline HeapCell* DLExtract(HeapCell* list, HeapCell* cell)
{
	if (cell->next != NULL) {
		cell->next->prev = cell->prev;
	}
	if (cell->prev == NULL) {
		return cell->next;
	}
	cell->prev->next = cell->next;
	return list;
}

void* OSAllocFromHeap(OSHeapHandle heap, u32 size)
{
	HeapDesc* hd = &HeapArray[heap];
	HeapCell* cell;
	HeapCell* newCell;
	HeapCell* alloc;
	u32 leftoverSize;

	size += HEADERSIZE;
	size = OSRoundUp32B(size);
	for (cell = hd->free; cell != NULL; cell = cell->next) {
		if ((s32)size <= cell->size) {
			break;
		}
	}
	if (cell == NULL) {
		return NULL;
	}
	leftoverSize = cell->size - size;
	if (leftoverSize < MINOBJSIZE) {
		hd->free = DLExtract(hd->free, cell);
	} else {
		cell->size    = size;
		newCell       = (HeapCell*)((u8*)cell + size);
		newCell->size = leftoverSize;
		newCell->prev = cell->prev;
		newCell->next = cell->next;
		if (newCell->next != NULL) {
			newCell->next->prev = newCell;
		}
		if (newCell->prev != NULL) {
			newCell->prev->next = newCell;
		} else {
			hd->free = newCell;
		}
	}
	alloc      = hd->allocated;
	cell->next = alloc;
	cell->prev = NULL;
	if (alloc != NULL) {
		alloc->prev = cell;
	}
	hd->allocated = cell;
	return (u8*)cell + HEADERSIZE;
}

void OSFreeToHeap(OSHeapHandle heap, void* ptr)
{
	HeapDesc* hd   = &HeapArray[heap];
	HeapCell* cell = (HeapCell*)((u8*)ptr - HEADERSIZE);

	hd->allocated = DLExtract(hd->allocated, cell);
	hd->free      = DLInsert(hd->free, cell);
}

OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap)
{
	OSHeapHandle old = __OSCurrHeap;
	__OSCurrHeap     = heap;
	return old;
}

void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps)
{
	u32 arraySize = maxHeaps * sizeof(HeapDesc);
	int i;

	HeapArray = arenaStart;
	NumHeaps  = maxHeaps;
	for (i = 0; i < NumHeaps; i++) {
		HeapDesc* hd = &HeapArray[i];
		hd->size     = -1;
		hd->free = hd->allocated = NULL;
	}
	__OSCurrHeap = -1;
	arenaStart   = (u8*)HeapArray + arraySize;
	arenaStart   = (void*)OSRoundUp32B(arenaStart);
	ArenaStart   = arenaStart;
	ArenaEnd     = (void*)OSRoundDown32B(arenaEnd);
	return arenaStart;
}

OSHeapHandle OSCreateHeap(void* start, void* end)
{
	int heap;
	HeapCell* cell = (HeapCell*)OSRoundUp32B(start);

	end = (void*)OSRoundDown32B(end);
	for (heap = 0; heap < NumHeaps; heap++) {
		HeapDesc* hd = &HeapArray[heap];

		if (hd->size < 0) {
			hd->size      = (u8*)end - (u8*)cell;
			cell->prev    = NULL;
			cell->next    = NULL;
			cell->size    = hd->size;
			hd->free      = cell;
			hd->allocated = NULL;
			return heap;
		}
	}
	return -1;
}
