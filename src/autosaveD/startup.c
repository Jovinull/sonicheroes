#include "types.h"

extern u8 lbl_803E8150[];

extern "C" void fn_8012FF6C(void* resource);
extern "C" void fn_2_3E4C(void);

extern "C" void fn_2_3FAC(void)
{
	fn_8012FF6C(lbl_803E8150);
	fn_2_3E4C();
}
