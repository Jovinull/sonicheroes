#include "types.h"

extern void* lbl_2_bss_54[2];

extern void fn_2_25A8(void* context, const void* position, const void* size, s32 selected);
extern void fn_80194234(s32 channel, void* resource);
extern void fn_2_2868(void* context, const void* position, const void* size);
extern void fn_2_24FC(void* context);

void fn_2_3368(void* context, const void* position, const void* size, s32 selected)
{
	fn_2_25A8(context, position, size, selected);

	if (selected != 0) {
		fn_80194234(1, lbl_2_bss_54[0]);
	} else {
		fn_80194234(1, lbl_2_bss_54[1]);
	}

	fn_2_2868(context, position, size);
	fn_2_24FC(context);
}
