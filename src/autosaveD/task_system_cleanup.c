#include "types.h"

extern "C" s32 lbl_2_bss_40;
extern "C" u8 lbl_2_data_398[];

extern "C" void fn_2_3FAC(void);
extern "C" void fn_8012CFA4(void* resource);

extern "C" void fn_2_22FC(void)
{
	if (lbl_2_bss_40 != 0) {
		fn_2_3FAC();
		fn_8012CFA4(lbl_2_data_398);
	}
}
