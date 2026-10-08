#include "types.h"

struct Selector {
	s32 items[32];
	s32 count;
	s32 index;
	s32 wrap;
};

extern u8 lbl_80303EC8[];

extern "C" s32 fn_800A92E0(void* input, s32 button, s32 port);
extern "C" void fn_2_40F0(Selector* selector);

extern "C" void fn_2_4070(void* window) { }

extern "C" void fn_2_4074(Selector* selector, s32 index)
{
	if (index <= 0) {
		return;
	}
	if (index >= 3) {
		return;
	}
	selector->index = index;
}

extern "C" void fn_2_408C(Selector* selector)
{
	selector->wrap = 1;
}

extern "C" void fn_2_4098(Selector* selector, s32 value)
{
	s32 i;

	for (i = 0; i != selector->count; i++) {
		if (selector->items[i] == value) {
			selector->index = i;
			fn_2_40F0(selector);
			break;
		}
	}
}

#pragma dont_inline on
extern "C" void fn_2_40F0(Selector* selector)
{
	if (selector->wrap) {
		if (selector->index < 0) {
			selector->index = selector->count - 1;
		}
		if (selector->count > selector->index) {
			return;
		}
		selector->index = 0;
	} else {
		if (selector->index < 0) {
			selector->index = 0;
		}
		if (selector->count > selector->index) {
			return;
		}
		selector->index = selector->count - 1;
	}
}
#pragma dont_inline reset

extern "C" s32 fn_2_4160(Selector* selector, s32 firstRowLength, s32 secondRowLength, s32 port)
{
	s32 currentIndex;

	if (port == -1) {
		port = 0;
	}

	{
		Selector* state  = selector;
		s32 canMoveUp    = 1;
		s32 canMoveDown  = 1;
		s32 canMoveLeft  = 1;
		s32 canMoveRight = 1;
		u32 isFirstRow;

		currentIndex = state->index;
		isFirstRow   = currentIndex < firstRowLength;

		if (isFirstRow) {
			canMoveUp = 0;
		}
		if (!isFirstRow) {
			canMoveDown = 0;
		}
		if (*(volatile s32*)&state->index == 0 || currentIndex == firstRowLength) {
			canMoveLeft = 0;
		}
		if (currentIndex == firstRowLength - 1
		    || currentIndex == firstRowLength + secondRowLength - 1) {
			canMoveRight = 0;
		}

		if (canMoveUp && fn_800A92E0(lbl_80303EC8, 8, port)) {
			state->index -= firstRowLength;
			while (state->index >= firstRowLength) {
				state->index--;
			}
		} else if (canMoveDown && fn_800A92E0(lbl_80303EC8, 4, port)) {
			state->index += firstRowLength;
			while (state->index < firstRowLength) {
				state->index++;
			}
		} else if (canMoveLeft && fn_800A92E0(lbl_80303EC8, 1, port)) {
			state->index--;
		} else if (canMoveRight && fn_800A92E0(lbl_80303EC8, 2, port)) {
			state->index++;
		}

		fn_2_40F0(state);

		if (state->index == -1) {
			return -1;
		}

		return state->items[state->index];
	}
}
