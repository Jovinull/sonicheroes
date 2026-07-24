#include "types.h"

struct RenderState {
	s32 enabled[2];
};

extern "C" RenderState lbl_2_bss_54;

extern "C" void fn_80194234(s32 id, s32 value);
extern "C" void fn_2_25A8(void* state);
extern "C" void fn_2_2868(void* state, void* position, void* scale);
extern "C" void fn_2_24FC(void* state);

extern "C" void fn_2_3368(void* state, void* position, void* scale, s32 mode)
{
	fn_2_25A8(state);

	if (mode != 0) {
		fn_80194234(1, lbl_2_bss_54.enabled[0]);
	} else {
		fn_80194234(1, lbl_2_bss_54.enabled[1]);
	}

	fn_2_2868(state, position, scale);
	fn_2_24FC(state);
}
