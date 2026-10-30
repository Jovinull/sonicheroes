// The chain of thunder sets (stage13D, stage27D and stage28D): s14ThunderLink appends a set to the
// list headed by s14ThunderHead (the constructor calls it) and s14ThunderUnlink
// takes one out (the destructor calls it). Both do nothing while the word at
// s14ThunderChainOn is zero. The unlink tests the head through the global and
// then copies it into the walk's pointer, which is the original's `mr r4, r0`
// before the loop; TObjS23WarpPos's destructor (rel/s23_warppos_dtor.cpp)
// loads the head into the walk's pointer inside the test instead.

#define S14_THUNDER_CTOR inline
#include "src/rel/s14_thunder_class.inc"

extern "C" void* s14ThunderChainOn;
extern "C" TObjS14ThunderSet* s14ThunderHead;

extern "C" void s14ThunderUnlink(TObjS14ThunderSet* set)
{
	if (s14ThunderChainOn == NULL) {
		return;
	}
	if (s14ThunderHead == NULL) {
		return;
	}

	if (s14ThunderHead == set) {
		s14ThunderHead = set->next;
	} else {
		TObjS14ThunderSet* prev = s14ThunderHead;
		while (prev->next != set) {
			prev = prev->next;
		}
		prev->next = set->next;
	}
	set->next = NULL;
}

extern "C" void s14ThunderLink(TObjS14ThunderSet* set)
{
	if (s14ThunderChainOn == NULL) {
		return;
	}

	if (s14ThunderHead == NULL) {
		s14ThunderHead = set;
	} else {
		TObjS14ThunderSet* last = s14ThunderHead;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = set;
	}
	set->next = NULL;
}
