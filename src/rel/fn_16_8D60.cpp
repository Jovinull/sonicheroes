#include "types.h"

struct TObjSetObj {
	int OnEdit();
};
extern "C" int fn_16_F20(void* game, int flag);
extern "C" void fn_16_94DC(void* self);
extern "C" void* lbl_8042C180;

extern "C" void fn_16_8D60(char* self)
{
	if (*(s8*)(self + 0x2A) == 1 || ((TObjSetObj*)(self + 0x50))->OnEdit()) {
		if (fn_16_F20(lbl_8042C180, 0x20) == 0) {
			if (fn_16_F20(lbl_8042C180, 0x32) < 0) {
				fn_16_94DC(self);
			}
		}
	}
}
