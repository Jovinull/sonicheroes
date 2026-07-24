#include "types.h"

struct AutosaveState {
	u8 padding[0x6C];
	s32 result;
};

extern "C" s32 fn_2_3404(AutosaveState* state)
{
	return state->result;
}
