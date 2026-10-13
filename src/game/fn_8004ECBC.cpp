#include "types.h"

// Clears the 0x13800-byte buffer at lbl_802C21E0 and, given a number, clears
// the 0x100 bytes at lbl_802D59F0 and loads the file whose name the format
// string at lbl_802428B0 builds from it into the buffer (fn_80042048),
// returning that call's result; without a number it returns 1.

extern "C" u8 lbl_802C21E0[];
extern "C" u8 lbl_802D59F0[];
extern "C" char lbl_802428B0[];

extern "C" void* memset(void* dst, s32 value, u32 size);
extern "C" s32 sprintf(char* out, const char* format, ...);
extern "C" s32 fn_80042048(void* name, void* buffer);

extern "C" s32 fn_8004ECBC(void* self, u32 number)
{
	char name[0x40];
	(void)self;

	memset(lbl_802C21E0, 0, 0x13800);
	if (number != 0) {
		memset(lbl_802D59F0, 0, 0x100);
		sprintf(name, lbl_802428B0, number);
		return fn_80042048(name, lbl_802C21E0);
	}
	return 1;
}
