#include "types.h"

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
extern "C" void fn_2_3FD8(void);
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
		fn_2_3FAC();
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
		fn_2_3FD8();
	}
}

extern "C" s32 fn_2_2488(s32 state)
{
	switch (state) {
		case 1:
			return fn_800A9398(lbl_80303EC8, 0);
		case 2:
			return fn_800A9398(lbl_80303EC8, 1);
		case 0:
		default:
			return fn_800A9398(lbl_80303EC8, -1);
	}
}

extern "C" void fn_2_24FC(AutosaveState* state)
{
	fn_80194234(6, state->parameters[0]);
	fn_80194234(8, state->parameters[1]);
	fn_80194234(12, state->parameters[2]);
	fn_80194234(10, state->parameters[3]);
	fn_80194234(11, state->parameters[4]);
	fn_80194234(9, state->parameters[5]);
	fn_80194234(20, state->parameters[6]);
	fn_80194234(3, state->parameters[7]);
	fn_80194234(4, state->parameters[8]);
	fn_80194234(14, state->parameters[9]);
	fn_80194234(1, 0);
}

extern "C" void fn_2_25A8(AutosaveState* state)
{
	fn_80194294(6, &state->parameters[0]);
	fn_80194294(8, &state->parameters[1]);
	fn_80194294(12, &state->parameters[2]);
	fn_80194294(10, &state->parameters[3]);
	fn_80194294(11, &state->parameters[4]);
	fn_80194294(9, &state->parameters[5]);
	fn_80194294(20, &state->parameters[6]);
	fn_80194294(3, &state->parameters[7]);
	fn_80194294(4, &state->parameters[8]);
	fn_80194294(14, &state->parameters[9]);

	fn_80194234(6, 0);
	fn_80194234(8, 0);
	fn_80194234(12, 1);
	fn_80194234(10, 5);
	fn_80194234(11, 6);
	fn_80194234(9, 1);
	fn_80194234(20, 1);
	fn_80194234(3, 3);
	fn_80194234(4, 3);
	fn_80194234(14, 0);
}
