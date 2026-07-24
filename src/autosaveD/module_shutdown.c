#include "types.h"

extern "C" u8 lbl_2_data_A8[0x18];

extern "C" void fn_8012CB70(void* state);
extern "C" void fn_801262DC(void);
extern "C" void fn_2_3FD8(void);

extern "C" void fn_2_139C(void)
{
	fn_8012CB70(lbl_2_data_A8);
	fn_801262DC();
	fn_2_3FD8();
}
