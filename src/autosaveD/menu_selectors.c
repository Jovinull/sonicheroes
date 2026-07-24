#include "types.h"

typedef struct Selector {
	s32 items[32];
	s32 count;
	s32 index;
	s32 wrap;
} Selector;

extern u8 lbl_80303EC8[];

extern s32 fn_800A92E0(void* input, s32 button, s32 port);
extern void fn_2_40F0(Selector* selector);

s32 fn_2_4344(Selector* selector, s32 port)
{
	if (port == -1) {
		port = 0;
	}

	switch (selector->index) {
		case 0:
			if (fn_800A92E0(lbl_80303EC8, 2, port)) {
				selector->index = 2;
			}
			if (fn_800A92E0(lbl_80303EC8, 4, port)) {
				selector->index = 1;
			}
			break;
		case 1:
			if (fn_800A92E0(lbl_80303EC8, 8, port)) {
				selector->index = 0;
			}
			if (fn_800A92E0(lbl_80303EC8, 2, port)) {
				selector->index = 3;
			}
			break;
		case 2:
			if (fn_800A92E0(lbl_80303EC8, 1, port)) {
				selector->index = 0;
			}
			if (fn_800A92E0(lbl_80303EC8, 4, port)) {
				selector->index = 3;
			}
			break;
		case 3:
			if (fn_800A92E0(lbl_80303EC8, 8, port)) {
				selector->index = 2;
			}
			if (fn_800A92E0(lbl_80303EC8, 1, port)) {
				selector->index = 1;
			}
			break;
	}

	fn_2_40F0(selector);

	if (selector->index == -1) {
		return -1;
	}

	return selector->items[selector->index];
}

s32 fn_2_4500(Selector* selector, s32 port)
{
	if (port == -1) {
		port = 0;
	}

	if (fn_800A92E0(lbl_80303EC8, 1, port)) {
		selector->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 2, port)) {
		selector->index++;
	}

	fn_2_40F0(selector);

	if (selector->index == -1) {
		return -1;
	}

	return selector->items[selector->index];
}

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
