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
// Built with -opt noschedule, like main and EXIBios: without it the
// instructions are right and their order is not.
//
// Eight of the eleven functions match. The rest are written and produce the
// right instructions in the right count; what still differs is register
// numbering inside the free-list splice and coalesce paths, where the compiler
// reads a cell's links back from memory in a different order than the original.
//
// fn_80012654 is the one that has been taken all the way, and what it took is
// worth repeating on the rest. Three things had to hold at once, and no two of
// them were enough: the locals are declared largest before total, which is what
// decides that largest lives in r0 and the loaded size in r7 rather than the
// other way round; the walk pointer is set before the two counters are zeroed,
// which is what puts the gHighHead load first; and each loop reads c->size into
// a named local rather than naming the field twice, which the original does as
// one load feeding both the compare and the add. Writing the first loop's three
// initialisers in its for clause and setting them in three statements ahead of
// a bare for are indistinguishable here; the for clause is what stands.
//
// fn_8001234C came out of the same reading. It sets the two roots up through
// the globals rather than through a local cell pointer, which is what makes the
// compiler read each root back before every field store: the store can alias
// the root. It also calls OSSetArenaLo a second time, with the arena top rather
// than the value OSInitAlloc returned, which leaves the OS arena empty. That
// call is the heap claiming the whole arena for itself, and it is the reason
// nothing else in the game allocates through OSAlloc.
//
// fn_80012A94 took two more of the same kind. Its split path tests the two
// links through the locals it already read out of the cell, not through
// rest->next and rest->prev, which is what stops the compiler reading them back
// out of the cell it has just written; and rest is declared inside that block
// after the two links rather than at the top of the function, which is what
// gives it r7 and leaves r5 and r6 to them.
//
//   fn_800125F0  100%   alloc
//   fn_80012560  100%   calloc
//   fn_80012994  100%   the find-block wrapper
//   fn_800126C8  100%   free and trim
//   fn_80012BE0  100%   free if non-null
//   fn_80012654  100%   heap info
//   fn_8001234C  100%   init
//   fn_80012A94  100%   the core allocator
//   fn_80012740   87%   free; the coalesce arms re-read links out of order
//   fn_8001247C   77%   realloc
//   fn_800129B4   71%   the high-list allocator, same shape as fn_80012A94

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
static u32 gHeapBase;    // 0x8042C0A0
static u32 gHeapSize;    // 0x8042C0A4
static Cell* gHighHead;  // 0x8042C0A8
static Cell* gHighTail;  // 0x8042C0AC
static Cell* gLowHead;   // 0x8042C0B0
static Cell* gLowTail;   // 0x8042C0B4
static Cell* gAllocHigh; // 0x8042C0B8, plus one more word

Cell* fn_80012A94(u32 size, Cell* list);
void* fn_800129B4(u32 size);
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

	// Written through the globals rather than a local, which is what makes the
	// compiler read each root back before the next field store: a store through
	// the pointer can alias the root itself.
	gLowHead       = (Cell*)gHeapBase;
	gLowHead->next = NULL;
	gLowHead->prev = NULL;
	gLowHead->hi   = NULL;
	gLowHead->lo   = NULL;
	gLowHead->size = 0x200000;
	gLowTail       = gLowHead;

	gHighHead       = (Cell*)(gHeapBase + 0x200000);
	gHighHead->next = NULL;
	gHighHead->prev = NULL;
	gHighHead->hi   = NULL;
	gHighHead->lo   = NULL;
	gHighHead->size = gHeapSize - 0x200000;
	gHighTail       = gHighHead;
	gAllocHigh      = gHighHead;

	// The heap takes the whole arena: nothing is left for OSAlloc after this.
	OSSetArenaLo(hi);

	vtable->alloc   = (void* (*)(u32))fn_800125F0;
	vtable->calloc  = (void* (*)(u32, u32))fn_80012560;
	vtable->realloc = (void* (*)(void*, u32))fn_8001247C;
	vtable->free    = (void (*)(void*))fn_80012BE0;

	return 1;
}

// Grows or shrinks a block, copying the smaller of the old and new sizes.
void* fn_8001247C(void* ptr, u32 size)
{
	u32 oldSize;
	u32 want;
	void* out;

	oldSize = (ptr != NULL) ? ((Cell*)((u8*)ptr - 0x20))->size : 0;

	out  = NULL;
	want = CELL_ROUND(size);
	if (want <= POOL_SPLIT) {
		out = (void*)fn_80012A94(want, gLowHead);
	}
	if (out == NULL) {
		out = (void*)fn_80012A94(want, gHighHead);
	}

	if (out != NULL) {
		if (oldSize < size) {
			if (ptr != NULL) {
				memcpy(out, ptr, oldSize);
			}
		} else if (ptr != NULL) {
			memcpy(out, ptr, size);
		}
		if (ptr != NULL) {
			fn_80012740(ptr);
		}
	}

	return out;
}

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

	for (c = gHighHead, largest = 0, total = 0; c != NULL; c = c->next) {
		u32 size = c->size;
		if (largest < size) {
			largest = size;
		}
		total += size;
	}
	for (c = gLowHead; c != NULL; c = c->next) {
		u32 size = c->size;
		if (largest < size) {
			largest = size;
		}
		total += size;
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

// The size query and expand path on the high list: walks it for the last cell
// large enough, then either takes it whole or carves the tail off it.
void* fn_800129B4(u32 size)
{
	Cell* c;
	Cell* found;
	Cell* split;
	u32 want;

	want  = CELL_ROUND(size);
	found = NULL;
	for (c = gHighTail; c != NULL; c = c->prev) {
		if (c->size >= want) {
			found = c;
			break;
		}
	}
	if (found == NULL) {
		return NULL;
	}

	if (found->size == want) {
		Cell* fn = found->next;
		Cell* fp = found->prev;
		if (fn != NULL) {
			fn->prev = fp;
		} else if ((Cell*)fp < gAllocHigh) {
			gLowTail = fp;
		} else {
			gHighTail = fp;
		}
		if (fp != NULL) {
			fp->next = fn;
		} else if ((Cell*)fn < gAllocHigh) {
			gLowHead = fn;
		} else {
			gHighHead = fn;
		}
		found->next = NULL;
		found->prev = NULL;
		return (u8*)found + 0x20;
	}

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
			} else if (cp < gAllocHigh) {
				gLowTail = cp;
			} else {
				gHighTail = cp;
			}
			if (cp != NULL) {
				cp->next = cn;
			} else if (cn < gAllocHigh) {
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
			// Tested through the locals rather than through rest->next and
			// rest->prev, which is what keeps the two links in registers
			// instead of reading them back out of the cell just written.
			if (cn != NULL) {
				cn->prev = rest;
			} else if (rest < gAllocHigh) {
				gLowTail = rest;
			} else {
				gHighTail = rest;
			}
			if (cp != NULL) {
				cp->next = rest;
			} else if (rest < gAllocHigh) {
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

// A cell is on a free list when either of its list links is set. An allocated
// cell has both cleared, so this tells a free neighbour from a busy one.
#define CELL_IS_FREE(c) ((c)->next != NULL || (c)->prev != NULL)

// Inserts cell as the new head of its pool's free list.
static void ListPush(Cell* cell, Cell** head, Cell** tail)
{
	if (*head != NULL) {
		(*head)->prev = cell;
	} else {
		*tail = cell;
	}
	cell->prev = NULL;
	cell->next = *head;
	*head      = cell;
}

// Frees a block, coalescing with whichever physical neighbours are also free
// and re-seating the merged cell in its pool's free list.
void fn_80012740(void* ptr)
{
	Cell* cell;
	Cell* lo;
	Cell* hi;
	Cell** head;
	Cell** tail;
	Cell* c;
	int i;

	cell = (Cell*)((u8*)ptr - 0x20);
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
		} else if (hi->prev < gAllocHigh) {
			gLowTail = hi->prev;
		} else {
			gHighTail = hi->prev;
		}
		if (hi->prev != NULL) {
			hi->prev->next = hi->next;
		} else if (hi->next < gAllocHigh) {
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
		} else if (cell < gAllocHigh) {
			gLowHead = cell;
		} else {
			gHighHead = cell;
		}
		if (cell->next != NULL) {
			cell->next->prev = cell;
		} else if (cell < gAllocHigh) {
			gLowTail = cell;
		} else {
			gHighTail = cell;
		}
		cell->hi = hi->hi;
		if (cell->hi != NULL) {
			cell->hi->lo = cell;
		}
		if (hi->lo != NULL) {
			hi->lo->hi = cell;
		}
		cell->size += hi->size;
		return;
	}

	// No free neighbour: thread the cell back into its pool's list. Walk down
	// the physical neighbours to find one that is already free and splice in
	// after it, keeping the list in address order; if none is found within the
	// bounded walk, push it at the head.
	if (cell < gAllocHigh) {
		head = &gLowHead;
		tail = &gLowTail;
	} else {
		head = &gHighHead;
		tail = &gHighTail;
	}

	if (*head == NULL) {
		cell->next = NULL;
		cell->prev = NULL;
		*head      = cell;
		*tail      = cell;
		return;
	}

	c = cell;
	for (i = 0x20; i != 0; i--) {
		Cell* nb = c->lo;
		if (nb == NULL) {
			break;
		}
		if (nb->next != NULL) {
			nb->next->prev = cell;
			cell->next     = nb->next;
			nb->next       = cell;
			cell->prev     = nb;
			return;
		}
		c = nb;
	}

	ListPush(cell, head, tail);
}

// Wrapper the vtable does not use directly.
void fn_80012994(u32 size)
{
	fn_800129B4(size);
}

// Frees only when the pointer is non-null.
void fn_80012BE0(void* ptr)
{
	if (ptr != NULL) {
		fn_80012740(ptr);
	}
}
