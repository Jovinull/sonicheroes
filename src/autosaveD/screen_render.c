#include "types.h"

struct RenderState {
	u8 padding[0x10];
	s32 enabled;
};

extern "C" RenderState lbl_2_bss_54;

extern "C" void fn_80194234(s32 id, s32 value);
extern "C" void fn_2_25A8(void* state);
extern "C" void fn_2_2F94(void* state, void* position, void* scale);
extern "C" void fn_2_24FC(void* state);

extern "C" void fn_2_32F8(void* state, void* position, void* scale)
{
	fn_2_25A8(state);
	fn_80194234(1, lbl_2_bss_54.enabled);
	fn_2_2F94(state, position, scale);
	fn_2_24FC(state);
}
