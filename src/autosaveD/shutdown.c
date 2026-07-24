#include "types.h"

extern u8 lbl_803E8150[];

extern "C" void fn_2_3EC0(void);
extern "C" void fn_801301C8(void* resource);

extern "C" void fn_2_3FD8(void)
{
	fn_2_3EC0();
	fn_801301C8(lbl_803E8150);
}
