#include "types.h"

// The game's heap. Sits right before main in the DOL and is the block main
// hands to fn_8001234C: that function fills a four-word vtable at 0x8029BBC0
// with this file's alloc, free, realloc and calloc, which is the same 0x10
// bytes main.c calls through. So this is the allocator the whole game runs on.
//
// The translation unit runs from fn_8001234C at 0x8001234C to the end of
// fn_80012BE0 at 0x80012C08, and owns 0x20 bytes of .sbss at 0x8042C0A0. The
// bound is argued, since the disc ships no map:
//
//   Every function in the range reads lbl_8042C0A8, and the seven words at
//   0x8042C0A0 through 0x8042C0B8 are named by nobody outside it. main, the
//   only caller of fn_8001234C, is the unit after; the unit before ends where
//   its own shared data (a different cluster) stops. fn_80012BE0 closes this
//   one: the only function in the binary that names it is fn_8001234C, which is
//   in this file.
//
// The design is two pools. A low pool of 0x200000 bytes starting at the heap
// base, and a high pool over the rest. A cell's address decides its pool: below
// the high pool's base (kept in gAllocHigh) it is low, at or above it is high.
// Each pool keeps a doubly ended free list, so removing the head or the tail is
// a store to one of four roots rather than a walk.
//
// Names are the dtk ones. The evidence fixes where the file is and what its
// data means, not what the original called any of it. The cell fields are named
// from how they are used: 0x0/0x4 thread the free list, 0x8/0xc thread the
// physical neighbours for coalescing, 0x10 is the size.
//
// Built with exception tables enabled and propagation and scheduling disabled.
// The original also disables the peephole pass locally around realloc and free;
// those scopes preserve the entry comparisons and free-list selection branches.

typedef struct Cell {
	struct Cell* next; // 0x0  next in the free list
	struct Cell* prev; // 0x4  prev in the free list
	struct Cell* hi;   // 0x8  physical neighbour above
	struct Cell* lo;   // 0xc  physical neighbour below
	u32 size;          // 0x10 total size including this 0x20 header
	u8 pad[0xC];       // 0x14
} Cell;                // 0x20

// OS arena calls the init borrows the heap from.
extern u8* OSGetArenaLo(void);
extern u8* OSGetArenaHi(void);
extern u8* OSInitAlloc(void* lo, void* hi, int maxHeaps);
extern void OSSetArenaLo(void* lo);

extern void* memcpy(void* dst, const void* src, u32 n);
extern void* memset(void* dst, int c, u32 n);

// The vtable slots this file writes into the block main passes to the init.
typedef struct AllocVtable {
	void* (*alloc)(u32);          // 0x0  fn_800125F0
	void (*free)(void*);          // 0x4  fn_80012BE0
	void* (*realloc)(void*, u32); // 0x8  fn_8001247C
	void* (*calloc)(u32, u32);    // 0xC  fn_80012560
} AllocVtable;

// The two free lists, head and tail per pool, plus the heap bounds. Low pool
// roots are gLowHead/gLowTail, high pool roots are gHighHead/gHighTail, and
// gAllocHigh is the high pool base that sorts a cell into one list or the other.
static struct {
	Cell* value;
	u32 unused;
} gAllocHigh;           // 0x8042C0B8
static Cell* gLowTail;  // 0x8042C0B4
static Cell* gLowHead;  // 0x8042C0B0
static Cell* gHighTail; // 0x8042C0AC
static Cell* gHighHead; // 0x8042C0A8
static u32 gHeapSize;   // 0x8042C0A4
static u32 gHeapBase;   // 0x8042C0A0

Cell* fn_80012A94(u32 size, Cell* list);
void* fn_800129B4(register u32 size);
void fn_80012740(void* ptr);
void* fn_800125F0(u32 size);
void* fn_80012560(u32 n, u32 size);
void* fn_8001247C(void* ptr, u32 size);
void fn_80012BE0(void* ptr);
void fn_80012994(u32 size);

// Rounds a byte count up to a whole number of 0x20 cells, with one cell of
// header on top, which is the +0x3f before the mask.
#define CELL_ROUND(n) (((n) + 0x3F) & ~0x1F)

// The pool cutover: requests up to 0x100 cells try the low pool first.
#define POOL_SPLIT 0x100

// Sets up the two pools out of the OS arena and installs the vtable. The low
// pool is a single free cell of 0x200000, the high pool a single free cell of
// whatever is left.
int fn_8001234C(AllocVtable* vtable)
{
	u8* lo;
	u8* hi;

	lo = OSGetArenaLo();
	hi = OSGetArenaHi();
	lo = OSInitAlloc(lo, hi, 1);
	OSSetArenaLo(lo);

	gHeapBase = ((u32)lo + 0x1F) & ~0x1F;
	gHeapSize = ((u32)hi & ~0x1F) - gHeapBase;

	gLowHead       = (Cell*)gHeapBase;
	gLowHead->next = NULL;
	gLowHead->prev = NULL;
	gLowHead->hi   = NULL;
	gLowHead->lo   = NULL;
	gLowHead->size = 0x200000;
	gLowTail       = gLowHead;

	gHighHead        = (Cell*)(gHeapBase + 0x200000);
	gHighHead->next  = NULL;
	gHighHead->prev  = NULL;
	gHighHead->hi    = NULL;
	gHighHead->lo    = NULL;
	gHighHead->size  = gHeapSize - 0x200000;
	gHighTail        = gHighHead;
	gAllocHigh.value = gHighHead;

	OSSetArenaLo(hi);

	vtable->alloc   = (void* (*)(u32))fn_800125F0;
	vtable->calloc  = (void* (*)(u32, u32))fn_80012560;
	vtable->realloc = (void* (*)(void*, u32))fn_8001247C;
	vtable->free    = (void (*)(void*))fn_80012BE0;

	return 1;
}

// Grows or shrinks a block, copying the smaller of the old and new sizes.
#pragma peephole off
void* fn_8001247C(void* ptr, u32 size)
{
	u32 want;
	u32 oldSize;
	void* out;

	oldSize = ((u32)ptr != 0) ? ((Cell*)((u8*)ptr - 0x20))->size : 0;

	out  = NULL;
	want = CELL_ROUND(size);
	if (want <= POOL_SPLIT) {
		out = (void*)fn_80012A94(want, gLowHead);
	}
	if (out == NULL) {
		out = (void*)fn_80012A94(want, gHighHead);
	}
	want = (u32)out;

	if (want != 0) {
		if (oldSize < size) {
			if (ptr != NULL) {
				memcpy((void*)want, ptr, oldSize);
			}
		} else if (ptr != NULL) {
			memcpy((void*)want, ptr, size);
		}
		if (ptr != NULL) {
			if (ptr != NULL) {
				fn_80012740(ptr);
			}
		}
	}

	return (void*)want;
}
#pragma peephole on

// Allocates n * size bytes cleared to zero.
void* fn_80012560(u32 n, u32 size)
{
	void* out;
	u32 want;
	u32 total;

	out   = NULL;
	total = n * size;
	want  = CELL_ROUND(total);
	if (want <= POOL_SPLIT) {
		out = (void*)fn_80012A94(want, gLowHead);
	}
	if (out == NULL) {
		out = (void*)fn_80012A94(want, gHighHead);
	}
	if (out != NULL) {
		memset(out, 0, total);
	}
	return out;
}

// Plain allocation. Low pool first for small requests, high pool otherwise.
void* fn_800125F0(u32 size)
{
	void* out;
	u32 want;

	out  = NULL;
	want = CELL_ROUND(size);
	if (want <= POOL_SPLIT) {
		out = (void*)fn_80012A94(want, gLowHead);
	}
	if (out == NULL) {
		out = (void*)fn_80012A94(want, gHighHead);
	}
	return out;
}

// Reports total free bytes and the largest free block across both pools.
void fn_80012654(u32* totalOut, u32* largestOut)
{
	Cell* c;
	u32 largest;
	u32 total;

	c       = gHighHead;
	largest = 0;
	total   = 0;
	while (c != NULL) {
		u32 cellSize = c->size;
		if (largest < cellSize) {
			largest = cellSize;
		}
		total += cellSize;
		c = c->next;
	}
	c = gLowHead;
	while (c != NULL) {
		u32 cellSize = c->size;
		if (largest < cellSize) {
			largest = cellSize;
		}
		total += cellSize;
		c = c->next;
	}
	if (totalOut != NULL) {
		*totalOut = total;
	}
	if (largestOut != NULL) {
		*largestOut = largest;
	}
}

// Frees a block, then if the high pool's head and tail are the one cell that
// now sits right after the arena boundary, splices it to the tail of the list.
void fn_800126C8(void* ptr)
{
	Cell* head;

	fn_80012740(ptr);

	head = gHighHead;
	if (head != gHighTail && (u8*)ptr == (u8*)head + 0x20) {
		gHighHead->next->prev = NULL;
		gHighHead             = gHighHead->next;
		gHighTail->next       = head;
		head->prev            = gHighTail;
		head->next            = NULL;
		gHighTail             = head;
	}
}

// A cell is on a free list when either of its list links is set. An allocated
// cell has both cleared, so this tells a free neighbour from a busy one.
#define CELL_IS_FREE(c) ((c)->next != NULL || (c)->prev != NULL)

// Frees a block, coalescing with whichever physical neighbours are also free
// and re-seating the merged cell in its pool's free list.
#pragma opt_propagation on
#pragma peephole off
void fn_80012740(void* ptr)
{
	Cell* cell;
	Cell* hi;
	Cell* c;
	Cell* lo;
	Cell** head;
	int i;

	cell = (Cell*)ptr - 1;
	lo   = cell->lo;
	hi   = cell->hi;

	if (lo != NULL && CELL_IS_FREE(lo)) {
		// Merge cell down into the free neighbour below it.
		if (hi != NULL) {
			hi->lo = lo;
		}
		lo->hi = hi;
		lo->size += cell->size;
		if (hi == NULL) {
			return;
		}
		if (!CELL_IS_FREE(hi)) {
			return;
		}
		// hi is free too: pull it out of the list and fold it in as well.
		if (hi->hi != NULL) {
			hi->hi->lo = lo;
		}
		lo->hi = hi->hi;
		lo->size += hi->size;
		if (hi->next != NULL) {
			hi->next->prev = hi->prev;
		} else if (hi->prev < gAllocHigh.value) {
			gLowTail = hi->prev;
		} else {
			gHighTail = hi->prev;
		}
		if (hi->prev != NULL) {
			hi->prev->next = hi->next;
		} else if (hi->next < gAllocHigh.value) {
			gLowHead = hi->next;
		} else {
			gHighHead = hi->next;
		}
		return;
	}

	if (hi != NULL && CELL_IS_FREE(hi)) {
		// Neighbour above is free: absorb this cell into it, in place.
		cell->next = hi->next;
		cell->prev = hi->prev;
		if (cell->prev != NULL) {
			cell->prev->next = cell;
		} else if (cell < gAllocHigh.value) {
			gLowHead = cell;
		} else {
			gHighHead = cell;
		}
		if (cell->next != NULL) {
			cell->next->prev = cell;
		} else if (cell < gAllocHigh.value) {
			gLowTail = cell;
		} else {
			gHighTail = cell;
		}
		cell->hi = hi->hi;
		if (cell->hi != NULL) {
			cell->hi->lo = cell;
		}
		if (cell->lo != NULL) {
			cell->lo->hi = cell;
		}
		cell->size += hi->size;
		return;
	}

	// No free neighbour: thread the cell back into its pool's list. Walk down
	// the physical neighbours to find one that is already free and splice in
	// after it, keeping the list in address order; if none is found within the
	// bounded walk, push it at the head.
	if (cell < gAllocHigh.value) {
		head = &gLowHead;
	} else {
		head = &gHighHead;
	}

	if (*head != NULL) {
		c = cell;
		for (i = 0x20; i != 0; i--) {
			Cell* nb = c->lo;
			if (nb == NULL) {
				break;
			}
			if (nb->next != NULL) {
				Cell* next = nb->next;
				nb->next   = cell;
				next->prev = cell;
				cell->next = next;
				cell->prev = nb;
				return;
			}
			c = nb;
		}

		(*head)->prev = cell;
		cell->prev    = NULL;
		cell->next    = *head;
		*head         = cell;
	} else {
		cell->next = NULL;
		cell->prev = NULL;
		*head      = cell;
	}
}
#pragma peephole on
#pragma opt_propagation off

// Wrapper the vtable does not use directly.
void fn_80012994(u32 size)
{
	fn_800129B4(size);
}

// The size query and expand path on the high list: walks it for the last cell
// large enough, then either takes it whole or carves the tail off it.
void* fn_800129B4(register u32 size)
{
	u32 want;
	Cell* c;
	Cell* found;

	want  = CELL_ROUND(size);
	found = NULL;
	for (c = gHighTail; c != NULL; c = c->prev) {
		if (c->size >= want) {
			found = c;
			break;
		}
	}
	if (found != NULL) {
		if (found->size == want) {
			Cell* fn = found->next;
			Cell* fp = found->prev;
			if (fn != NULL) {
				fn->prev = fp;
			} else {
				gHighTail = fp;
			}
			if (fp != NULL) {
				fp->next = fn;
			} else {
				gHighHead = fn;
			}
			found->next = NULL;
			found->prev = NULL;
			return (u8*)found + 0x20;
		}

		{
			Cell* split;
			split       = (Cell*)((u8*)found + found->size - want);
			split->next = NULL;
			split->prev = NULL;
			split->hi   = found->hi;
			split->lo   = found;
			split->size = want;
			found->size -= want;
			if (found->hi != NULL) {
				found->hi->lo = split;
			}
			found->hi = split;
			return (u8*)split + 0x20;
		}
	}
	return NULL;
}

// The core allocator: walks a free list from its head for a cell of the exact
// size or one cell larger, or a bigger cell it can split from the front.
Cell* fn_80012A94(u32 size, Cell* list)
{
	Cell* c;

	for (c = list; c != NULL; c = c->next) {
		if (c->size == size || c->size == size + 0x20) {
			Cell* cn = c->next;
			Cell* cp = c->prev;
			if (cn != NULL) {
				cn->prev = cp;
			} else if (cp < gAllocHigh.value) {
				gLowTail = cp;
			} else {
				gHighTail = cp;
			}
			if (cp != NULL) {
				cp->next = cn;
			} else if (cn < gAllocHigh.value) {
				gLowHead = cn;
			} else {
				gHighHead = cn;
			}
			c->next = NULL;
			c->prev = NULL;
			return (Cell*)((u8*)c + 0x20);
		}
		if (c->size > size) {
			Cell* cn   = c->next;
			Cell* cp   = c->prev;
			Cell* rest = (Cell*)((u8*)c + size);
			rest->next = cn;
			rest->prev = cp;
			rest->hi   = c->hi;
			rest->lo   = c;
			rest->size = c->size - size;
			c->size    = size;
			if (c->hi != NULL) {
				c->hi->lo = rest;
			}
			c->hi = rest;
			if (cn != NULL) {
				cn->prev = rest;
			} else if (rest < gAllocHigh.value) {
				gLowTail = rest;
			} else {
				gHighTail = rest;
			}
			if (cp != NULL) {
				cp->next = rest;
			} else if (rest < gAllocHigh.value) {
				gLowHead = rest;
			} else {
				gHighHead = rest;
			}
			c->next = NULL;
			c->prev = NULL;
			return (Cell*)((u8*)c + 0x20);
		}
	}
	return NULL;
}

// Frees only when the pointer is non-null.
void fn_80012BE0(void* ptr)
{
	if (ptr != NULL) {
		fn_80012740(ptr);
	}
}
