#include "types.h"

// Selection state embedded in autosaveD's menu object. This routine processes
// both controller ports before returning the entry at the resulting index.
typedef struct Selector {
	s32 items[33];
	s32 index;
} Selector;

extern u8 lbl_80303EC8[];

extern s32 fn_800A92E0(void* input, s32 button, s32 port);
extern void fn_2_40F0(Selector* selector);

s32 fn_2_45B8(Selector* selector)
{
	if (fn_800A92E0(lbl_80303EC8, 8, 0)) {
		selector->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 4, 0)) {
		selector->index++;
	}

	fn_2_40F0(selector);

	if (fn_800A92E0(lbl_80303EC8, 8, 1)) {
		selector->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 4, 1)) {
		selector->index++;
	}

	fn_2_40F0(selector);

	if (selector->index == -1) {
		return -1;
	}

	return selector->items[selector->index];
}
