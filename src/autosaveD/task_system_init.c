#include "types.h"

struct SaveState {
	u8 padding[0x22];
	u8 interval;
};

extern "C" s32 lbl_2_bss_40;
extern "C" s32 lbl_2_bss_44;
extern "C" u8 lbl_2_data_398[];
extern "C" u8 lbl_80303EC8[];
extern "C" u8 lbl_803E774C[];

extern "C" SaveState* fn_80116D2C(void* state);
extern "C" s32 fn_800A8BF8(void* settings);
extern "C" void fn_800A8C00(void* settings, s32 interval);
extern "C" void fn_8012D3A4(void* resource);
extern "C" void fn_2_3FD8(void);

extern "C" void fn_2_233C(void)
{
	lbl_2_bss_40 = 0;

	s32 interval = fn_80116D2C(lbl_803E774C)->interval;
	if (interval != fn_800A8BF8(lbl_80303EC8)) {
		fn_800A8C00(lbl_80303EC8, interval);
		lbl_2_bss_44 = 0;

		switch (interval) {
			case 20:
				lbl_2_bss_44 = 1;
				break;
			case 40:
				lbl_2_bss_44 = 2;
				break;
			case 60:
				lbl_2_bss_44 = 3;
				break;
			case 80:
				lbl_2_bss_44 = 4;
				break;
			case 100:
				lbl_2_bss_44 = 5;
				break;
			case 120:
				lbl_2_bss_44 = 6;
				break;
		}

		if (lbl_2_bss_44 != 0) {
			lbl_2_bss_40 = 1;
		}
	}

	if (lbl_2_bss_40 != 0) {
		fn_8012D3A4(lbl_2_data_398);
		fn_2_3FD8();
	}
}
