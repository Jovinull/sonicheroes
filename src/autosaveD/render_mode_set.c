#include "types.h"

struct RenderState {
	u8 unk0[0x84];
	s32 mode;
};

extern "C" void fn_2_4074(RenderState* state, s32 mode)
{
	if (mode <= 0) {
		return;
	}
	if (mode >= 3) {
		return;
	}
	state->mode = mode;
}
