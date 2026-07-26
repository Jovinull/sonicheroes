#include "types.h"

// Loads one object into the attract mode, and the pair that opens and closes
// the two resources it needs.
//
// The translation unit runs from fn_1_C8D0 at 0xC8D0 to the end of fn_1_C944
// at 0xC978. The two descriptors it names sit at .data 0x3B3C and 0x3C80 with
// a hundred other objects between them, so the .data is left to the module and
// only referenced here: this unit emits none of its own.
//
// fn_1_C944 closes them in the reverse order fn_1_C910 opens them.

extern "C" u8 lbl_1_data_3B3C[0x18];
extern "C" u8 lbl_1_data_3C80[0x18];

extern "C" void* fn_1_B1C(u32 size);
extern "C" void fn_1_C608(void* object, void* context);
extern "C" void fn_8012CA94(void* resource);
extern "C" void fn_8012CB70(void* resource);

extern "C" void fn_1_C8D0(void* context)
{
	void* object = fn_1_B1C(0x40C);

	if (object != NULL) {
		fn_1_C608(object, context);
	}
}

extern "C" void fn_1_C910(void)
{
	fn_8012CA94(lbl_1_data_3C80);
	fn_8012CA94(lbl_1_data_3B3C);
}

extern "C" void fn_1_C944(void)
{
	fn_8012CB70(lbl_1_data_3B3C);
	fn_8012CB70(lbl_1_data_3C80);
}
