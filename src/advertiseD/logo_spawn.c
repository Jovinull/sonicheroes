#include "types.h"

// Spawns one object into the attract mode, and the pair that opens and closes
// the resource it needs.
//
// The translation unit runs from fn_1_EB80 at 0xEB80 to the end of fn_1_EBE8
// at 0xEC18. The descriptor it names sits at .data 0x60A0, far from anything
// else this run touches, so the .data is left to the module and only
// referenced here: this unit emits none of its own.
//
// fn_1_EBE8 does one thing more than the plain closing half: it releases slot
// 4 before letting the resource go.

extern "C" u8 lbl_1_data_60A0[0x18];

extern "C" void* fn_1_B1C(u32 size);
extern "C" void fn_1_EA48(void* object, void* context);
extern "C" void fn_1_11750(s32 slot);
extern "C" void fn_8012CA94(void* resource);
extern "C" void fn_8012CB70(void* resource);

extern "C" void fn_1_EB80(void* context)
{
	void* object = fn_1_B1C(0x13C);

	if (object != NULL) {
		fn_1_EA48(object, context);
	}
}

extern "C" void fn_1_EBC0(void)
{
	fn_8012CA94(lbl_1_data_60A0);
}

extern "C" void fn_1_EBE8(void)
{
	fn_1_11750(4);
	fn_8012CB70(lbl_1_data_60A0);
}
