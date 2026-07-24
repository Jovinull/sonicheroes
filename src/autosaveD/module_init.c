#include "types.h"

extern "C" u8 lbl_2_data_A8[0x18];

extern "C" void fn_2_3FAC(void);
extern "C" void fn_80126254(void);
extern "C" void fn_8012CA94(void* state);

extern "C" void fn_2_136C(void)
{
	fn_2_3FAC();
	fn_80126254();
	fn_8012CA94(lbl_2_data_A8);
}
