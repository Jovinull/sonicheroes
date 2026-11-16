#include "types.h"

struct Shapes {
	u8 pad[0xBC];
	u8 a[0xC];
	u8 b[1];
};
struct Obj {
	u8 pad00[0x28];
	u8 sub[0x88];
	u8* p;
};
extern "C" {
void fn_80021824(void* w);
s32 fn_80041B64();
void fn_80089204(void* player);
void* fn_16_D10(void* p);
void fn_16_D98(void* p);
void fn_16_1180(void* a, void* b, void* c);
extern u8 lbl_8042C1A4[];
extern void* lbl_802AD070[];

void fn_16_432FC(register Obj* obj)
{
	void* e;
	fn_80021824(lbl_8042C1A4);
	while ((e = fn_16_D10((u8*)obj + 0x28)) != 0) {
		fn_16_D98(e);
		s32 no = fn_80041B64();
		fn_80089204(lbl_802AD070[no]);
	}
	fn_16_1180((u8*)obj + 0x28, obj->p + 0xBC, obj->p + 0xC8);
}
}
