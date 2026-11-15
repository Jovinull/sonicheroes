// Splits a closed node ring in two (HYPOTHESIS: an Rt2d contour split helper; names inferred):
// allocates a new ring header from the free list at lbl_803EC968 +0x1E8, moves the nodes from
// `from` up to `to` into a first ring and those from `to` back to `from` into a second one,
// closing each with a fresh node (free list +0x1E4) that copies the value of its end node. The
// source header keeps the first ring and the new one takes the second; the counts include the
// closing nodes and the new header copies fields 0x8 and 0x10. Returns the new header, or null.
#include "game/rw_engine.h"

struct RingNode80175EA8 {
	RingNode80175EA8* next; // 0x0
	s32 value;              // 0x4
};

struct Ring80175EA8 {
	RingNode80175EA8* head; // 0x0 (UNKNOWN use)
	RingNode80175EA8* tail; // 0x4: last node; tail->next is the first
	s32 field8;             // 0x8 (UNKNOWN)
	s32 numNodes;           // 0xC
	s32 field10;            // 0x10 (UNKNOWN)
};

struct Globals80175EA8 {
	u8 pad0[0x1E4];
	RwFreeList* nodeFreeList; // 0x1E4
	RwFreeList* ringFreeList; // 0x1E8
};

extern "C" {
extern Globals80175EA8 lbl_803EC968;

Ring80175EA8* fn_80175EA8(Ring80175EA8* src, RingNode80175EA8* from, RingNode80175EA8* to)
{
	RingNode80175EA8* end1;
	RingNode80175EA8* tail1;
	Ring80175EA8* ring;
	RingNode80175EA8* tail2;
	RingNode80175EA8* cur;
	s32 count1 = 0;
	s32 count2 = 0;
	RingNode80175EA8* next;
	RingNode80175EA8* end2;

	ring = (Ring80175EA8*)lbl_8042C9A4->freeListAlloc(lbl_803EC968.ringFreeList);
	if (ring != 0) {
		ring->head     = 0;
		ring->tail     = 0;
		ring->field10  = 0;
		ring->numNodes = 0;
	}
	if (ring != 0) {
		cur   = src->tail;
		tail1 = 0;
		tail2 = 0;
		while (cur != from) {
			cur = cur->next;
		}
		while (cur != to) {
			next = cur->next;
			if (tail1 == 0) {
				cur->next = cur;
			} else {
				cur->next   = tail1->next;
				tail1->next = cur;
			}
			tail1 = cur;
			cur   = next;
			count1++;
		}

		end1 = (RingNode80175EA8*)lbl_8042C9A4->freeListAlloc(lbl_803EC968.nodeFreeList);
		if (end1 != 0) {
			end1->next  = 0;
			end1->value = -1;
		}
		end1->value = to->value;
		if (tail1 == 0) {
			end1->next = end1;
		} else {
			end1->next  = tail1->next;
			tail1->next = end1;
		}

		while (cur != from) {
			next = cur->next;
			if (tail2 == 0) {
				cur->next = cur;
			} else {
				cur->next   = tail2->next;
				tail2->next = cur;
			}
			tail2 = cur;
			cur   = next;
			count2++;
		}

		end2 = (RingNode80175EA8*)lbl_8042C9A4->freeListAlloc(lbl_803EC968.nodeFreeList);
		if (end2 != 0) {
			end2->next  = 0;
			end2->value = -1;
		}
		end2->value = from->value;
		if (tail2 == 0) {
			end2->next = end2;
		} else {
			end2->next  = tail2->next;
			tail2->next = end2;
		}

		src->tail      = end1;
		ring->tail     = end2;
		src->numNodes  = count1 + 1;
		ring->numNodes = count2 + 1;
		ring->field10  = src->field10;
		ring->field8   = src->field8;
	}
	return ring;
}
}
