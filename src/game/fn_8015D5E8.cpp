#include "types.h"

struct Ctx15D5E8 {
	u8 pad[8];
	u32 flags; // 0x08
};

struct Globals15D5E8 {
	u8 pad[4];
	Ctx15D5E8* field4; // 0x04
};

extern "C" {
extern Globals15D5E8* lbl_8042C9A4;
extern s32 lbl_8042BD28;

s32 fn_80166484(Ctx15D5E8*, s32, s32, s32);
s32 fn_80166DB4(Ctx15D5E8*, s32, s32, s32);

s32 fn_8015D5E8(s32 arg0, s32* arg1)
{
	// mwcc needs a real copy of the object pointer: the same value is passed as
	// argument 2 (r4), 3 (r5) and, plus 0x34, argument 4 (r6) at every call site.
	s32 a          = (s32)arg0;
	Ctx15D5E8* ctx = lbl_8042C9A4->field4;

	if (ctx->flags & 0x02000000) {
		if (lbl_8042BD28 == 1) {
			*arg1 = fn_80166484(ctx, a, a, a + 0x34);
		} else {
			*arg1 = fn_80166DB4(ctx, a, a, a + 0x34);
		}
	} else {
		*arg1 = fn_80166DB4(ctx, a, a, a + 0x34);
	}
	return arg0;
}
}
