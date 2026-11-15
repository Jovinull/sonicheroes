#include "types.h"

struct Obj800A0A4C {
	u8 pad[0x98];
	s32 arr[4];
};

extern "C" {
extern Obj800A0A4C* lbl_8042C314;
void addVictory__13PARAM_VICTORYFii(void*, s32, s32);

void fn_800A0A4C(s32 arg0)
{
	Obj800A0A4C* o = lbl_8042C314;
	s32 i;

	addVictory__13PARAM_VICTORYFii((u8*)o + 0x30, arg0, 1);
	o->arr[arg0] = 1;
	i            = 1;
	if (arg0 != 0) {
		i = 0;
	} else {
		i = 1;
	}
	o->arr[i] = 0;
}
}
