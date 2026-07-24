#include "types.h"

struct Archive;

extern Archive* lbl_2_bss_50;
extern u32 lbl_2_bss_54[5];

extern "C" void fn_801A46D0(Archive* archive);

extern "C" void fn_2_3E4C(void)
{
	u32* asset = lbl_2_bss_54;
	s32 i;

	for (i = 0; i != 5; i++) {
		*asset++ = 0;
	}

	if (lbl_2_bss_50 != NULL) {
		fn_801A46D0(lbl_2_bss_50);
		lbl_2_bss_50 = NULL;
	}
}
