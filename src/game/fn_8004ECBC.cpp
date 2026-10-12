#include "types.h"

extern "C" u8 lbl_802C21E0[];
extern "C" u8 lbl_802D59F0[];
extern "C" char lbl_802428B0[];

extern "C" void* memset(void* arg0, s32 arg1, u32 arg2);
extern "C" s32 sprintf(char* arg0, const char* arg1, ...);
extern "C" s32 fn_80042048(void* arg0, void* arg1);

extern "C" s32 fn_8004ECBC(void* arg0, u32 arg1)
{
	char sp8[0x40];
	(void)arg0;

	memset(lbl_802C21E0, 0, 0x13800);
	if (arg1 != 0) {
		memset(lbl_802D59F0, 0, 0x100);
		sprintf(sp8, lbl_802428B0, arg1);
		return fn_80042048(sp8, lbl_802C21E0);
	}
	return 1;
}
