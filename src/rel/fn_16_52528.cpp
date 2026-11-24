#include "types.h"

extern "C" {
void* fn_16_528A4(s32, u8, void*, s32, s32, s32, s32);
void fn_16_525F0(void*, u8, s32);
}

extern "C" void fn_16_52528(
    s32 arg0, u8 arg1, u8 arg2, void* arg3, s32 arg4, s32 arg5, u32 arg6, register u8 arg7)
{
	s32 i;
	for (i = 0; i < arg2; i++) {
		void* p = fn_16_528A4(arg0, (u8)(arg1 + i), arg3, arg4, arg5, arg6, 1);
		if (p != 0 && arg7 != 0xFF) {
			fn_16_525F0(p, arg7, 1);
		}
	}
}
