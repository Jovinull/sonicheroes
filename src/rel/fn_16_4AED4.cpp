#include "types.h"

typedef struct Obj {
	u8 unk00[0xC8];
	s32 unkC8; // 0xC8
	u8 unkCC[0xC];
	s32 unkD8; // 0xD8
} Obj;

extern "C" {
extern u32 lbl_8042C1F8;
void fn_8004D4B8(u32 unused, s32 i);
void fn_8004D99C(u32 heap);
void fn_80130F78(s32 kind, void* object);

void fn_16_4AED4(Obj* arg0)
{
	if (arg0->unkC8 == 0 && arg0->unkD8 == 0) {
		if (lbl_8042C1F8 != 0) {
			fn_8004D99C(lbl_8042C1F8);
		}
		fn_80130F78(0xA, arg0);
		if (lbl_8042C1F8 != 0) {
			fn_8004D4B8(lbl_8042C1F8, arg0->unkC8);
		}
		arg0->unkD8 = 1;
	}
}
}
