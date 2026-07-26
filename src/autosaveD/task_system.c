#include "autosaveD/ADV_WINDOW.hpp"

struct Task;

struct SaveState {
	u8 padding[0x22];
	u8 interval;
};

struct AutosaveState {
	u8 padding[0x810];
	s32 parameters[10];
};

extern "C" s32 lbl_2_bss_40;
extern "C" s32 lbl_2_bss_44;
extern "C" u8 lbl_2_data_398[];
extern "C" u8 lbl_80303EC8[];
extern "C" u8 lbl_803E774C[];

extern "C" void* fn_2_1424(u32 size);
extern "C" Task* fn_2_211C(Task* task, void* context);
extern "C" void fn_80130464(s32 type);
extern "C" void fn_2_3FAC(void);
extern "C" void fn_8012CFA4(void* resource);
extern "C" SaveState* fn_80116D2C(void* state);
extern "C" s32 fn_800A8BF8(void* settings);
extern "C" void fn_800A8C00(void* settings, s32 interval);
extern "C" void fn_8012D3A4(void* resource);
extern "C" s32 fn_800A9398(void* input, s32 controller);
extern "C" void fn_80194234(s32 id, s32 value);
extern "C" void fn_80194294(s32 id, s32* value);

extern "C" void fn_2_2294(void* context)
{
	if (context != NULL) {
		if (lbl_2_bss_40 != 0) {
			Task* task = (Task*)fn_2_1424(0x38);
			if (task != NULL) {
				fn_2_211C(task, context);
			}
		} else {
			fn_80130464(2);
		}
	}
}

extern "C" void fn_2_22FC(void)
{
	if (lbl_2_bss_40 != 0) {
		ADV_WINDOW::Finalize();
		fn_8012CFA4(lbl_2_data_398);
	}
}

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
		ADV_WINDOW::Initialize();
	}
}
