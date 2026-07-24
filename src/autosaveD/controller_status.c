#include "types.h"

extern "C" u8 lbl_80303EC8[];

extern "C" s32 fn_800A9398(void* input, s32 controller);

extern "C" s32 fn_2_2488(s32 state)
{
	switch (state) {
		case 1:
			return fn_800A9398(lbl_80303EC8, 0);
		case 2:
			return fn_800A9398(lbl_80303EC8, 1);
		case 0:
		default:
			return fn_800A9398(lbl_80303EC8, -1);
	}
}
