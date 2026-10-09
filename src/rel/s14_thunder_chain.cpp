// The chain of thunder sets in stage13D: fn_9_A215C appends a set to the
// list headed by lbl_9_bss_1C30 (the constructor calls it) and fn_9_A20F4
// takes one out (the destructor calls it). Both do nothing while the word at
// lbl_9_bss_1C34 is zero. The unlink tests the head through the global and
// then copies it into the walk's pointer, which is the original's `mr r4, r0`
// before the loop; TObjS23WarpPos's destructor (rel/s23_warppos_dtor.cpp)
// loads the head into the walk's pointer inside the test instead.

#define S14_THUNDER_CTOR inline
#include "src/rel/s14_thunder_class.inc"

extern "C" void* lbl_9_bss_1C34;
extern "C" TObjS14ThunderSet* lbl_9_bss_1C30;

extern "C" void fn_9_A20F4(TObjS14ThunderSet* set)
{
	if (lbl_9_bss_1C34 == NULL) {
		return;
	}
	if (lbl_9_bss_1C30 == NULL) {
		return;
	}

	if (lbl_9_bss_1C30 == set) {
		lbl_9_bss_1C30 = set->next;
	} else {
		TObjS14ThunderSet* prev = lbl_9_bss_1C30;
		while (prev->next != set) {
			prev = prev->next;
		}
		prev->next = set->next;
	}
	set->next = NULL;
}

extern "C" void fn_9_A215C(TObjS14ThunderSet* set)
{
	if (lbl_9_bss_1C34 == NULL) {
		return;
	}

	if (lbl_9_bss_1C30 == NULL) {
		lbl_9_bss_1C30 = set;
	} else {
		TObjS14ThunderSet* last = lbl_9_bss_1C30;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = set;
	}
	set->next = NULL;
}
