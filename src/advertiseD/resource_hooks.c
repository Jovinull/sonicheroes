#include "types.h"

// The pair that hands the module's resource to the loader and takes it back.
//
// The translation unit runs from fn_1_A6C at 0xA6C to the end of fn_1_A94 at
// 0xABC. The descriptor at .data 0x1F8 is left to the module and only
// referenced here, so this unit emits no data of its own.

extern "C" u8 lbl_1_data_1F8[];

extern "C" void fn_8012CFA4(void* resource);
extern "C" void fn_8012D3A4(void* resource);

extern "C" void fn_1_A6C(void)
{
	fn_8012CFA4(lbl_1_data_1F8);
}

extern "C" void fn_1_A94(void)
{
	fn_8012D3A4(lbl_1_data_1F8);
}
