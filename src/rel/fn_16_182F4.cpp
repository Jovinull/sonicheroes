#include "types.h"

typedef struct C_COLLI {
	u8 pad[0xC0];
} C_COLLI;
typedef struct Obj {
	u8 unk00[0x30];
	C_COLLI colli; /* 0x30 */
	s32 mode;      /* 0xF0 */
} Obj;

extern "C" {
extern char lbl_8042C1A4[];
void fn_80021824(void*);
int fn_80041B64();
void fn_16_D98(u32);
u32 fn_16_DC8(void*, int);
}

extern "C" void fn_16_182F4(Obj* obj)
{
	int r = -1;
	u32 hit;

	fn_80021824(lbl_8042C1A4);
	while ((hit = fn_16_DC8(&obj->colli, 0xF)) != 0) {
		fn_16_D98(hit);
		r = fn_80041B64();
	}
	if (r != -1) {
		obj->mode = 3;
	}
}
