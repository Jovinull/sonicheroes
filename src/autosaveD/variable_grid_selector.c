#include "types.h"

// Selection state embedded in autosaveD's menu object. This entry point moves
// through a two-row grid whose rows may have different lengths.
typedef struct Selector {
	s32 items[33];
	s32 index;
} Selector;

extern u8 lbl_80303EC8[];

extern "C" {
extern s32 fn_800A92E0(void* input, s32 button, s32 port);
extern void fn_2_40F0(Selector* selector);
}

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
