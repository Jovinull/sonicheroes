#include "types.h"

struct GlobalState {
	u32 unk_0x0;
	u32 tick_high;
	u32 tick_low;
};

struct AutosaveState {
	s32 unk_0x0;
	s32 unk_0x4;
	s32 unk_0x8;
	s32 unk_0xC;
	s32 unk_0x10;
	f32 unk_0x14;
	f32 unk_0x18;
	f32 unk_0x1C;
	f32 unk_0x20;
	f32 unk_0x24;
	s32 unk_0x28;
	u32 unk_0x2C;
	u32 tick_high;
	u32 tick_low;
	s32 unk_0x38;
	s32 unk_0x3C;
	s32 unk_0x40;
};

struct Selector {
	s32 items[32];
	s32 count;
	s32 index;
	s32 wrap;
};

extern u8 lbl_803E8150[];
extern u8 lbl_80303EC8[];
extern GlobalState lbl_8029BB80;
extern const f32 lbl_2_rodata_348;

extern "C" void fn_8012FF6C(void* resource);
extern "C" void fn_2_3E4C(void);
extern "C" void fn_2_3EC0(void);
extern "C" void fn_801301C8(void* resource);
extern "C" s32 fn_800A92E0(void* input, s32 button, s32 port);
extern "C" void fn_2_40F0(Selector* selector);

extern "C" void fn_2_3FAC(void)
{
	fn_8012FF6C(lbl_803E8150);
	fn_2_3E4C();
}

extern "C" void fn_2_3FD8(void)
{
	fn_2_3EC0();
	fn_801301C8(lbl_803E8150);
}

extern "C" void fn_2_4004(AutosaveState* state)
{
	state->unk_0x0   = 0;
	state->unk_0x4   = 0;
	state->unk_0x8   = 0;
	state->unk_0xC   = 0;
	state->unk_0x10  = 0;
	state->unk_0x14  = lbl_2_rodata_348;
	state->unk_0x18  = lbl_2_rodata_348;
	state->unk_0x1C  = lbl_2_rodata_348;
	state->unk_0x20  = lbl_2_rodata_348;
	state->unk_0x24  = lbl_2_rodata_348;
	state->unk_0x28  = 0;
	state->unk_0x2C  = 0;
	state->tick_high = lbl_8029BB80.tick_high;
	state->tick_low  = lbl_8029BB80.tick_low;
	state->unk_0x38  = 0;
	state->unk_0x3C = state->unk_0x40 = 1;
}

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
