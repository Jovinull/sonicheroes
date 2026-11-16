#include "types.h"
struct Obj {
	char pad[0xB8];
	s8 mode;
};
extern "C" {
s32 fn_16_1CF24(Obj*);
s32 fn_16_1CF50(Obj*);
s32 fn_16_F20(s32, s32);
extern s32 lbl_8042C180;
s32 fn_16_1CF7C(register Obj* obj)
{
	if (fn_16_F20(lbl_8042C180, 0x1F) != 0) {
		return 0;
	}
	switch (obj->mode) {
		case 0:
		case 3:
			return 1;
		case 1:
		case 4:
			return fn_16_1CF24(obj);
		case 2:
		case 5:
			return fn_16_1CF50(obj);
		default:
			return 1;
	}
}
}
