#include "types.h"

extern "C" {
extern u8* lbl_8042C180;
s32 fn_16_F20(void*, s32);
s32 OnEdit__10TObjSetObjFv(void* setobj);
void fn_8014FF2C(s32);
void fn_16_45854(void*);
}

extern "C" void fn_16_442E8(register u8* obj)
{
	if (fn_16_F20(lbl_8042C180, 0x20) == 0) {
		if (OnEdit__10TObjSetObjFv(obj + 0x28)) {
			fn_8014FF2C(*(s32*)(obj + 0xFC));
		} else {
			if (*(s32*)(obj + 0xB8) == 1) {
				fn_16_45854(obj);
			}
			fn_8014FF2C(*(s32*)(obj + 0xFC));
		}
	}
}
