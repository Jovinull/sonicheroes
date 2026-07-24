#include "types.h"

// Selection state embedded in autosaveD's menu object. The adjustment helper
// below only accesses the entry array and the current index; fn_2_40F0 applies
// the list's bounds after left or right input changes that index.
typedef struct Selector {
	s32 items[33];
	s32 index;
} Selector;

extern u8 lbl_80303EC8[];

extern s32 fn_800A92E0(void* input, s32 button, s32 port);
extern void fn_2_40F0(Selector* selector);

s32 fn_2_46B4(Selector* selector, s32 port)
{
	if (port == -1) {
		port = 0;
	}

	if (fn_800A92E0(lbl_80303EC8, 8, port)) {
		selector->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 4, port)) {
		selector->index++;
	}

	fn_2_40F0(selector);

	if (selector->index == -1) {
		return -1;
	}

	return selector->items[selector->index];
}
