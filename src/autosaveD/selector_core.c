#include "types.h"

struct RenderState {
	s32 values[32];
	s32 count;
	s32 index;
	s32 wrap_enabled;
};

extern "C" void fn_2_40F0(RenderState* state);

extern "C" void fn_2_4074(RenderState* state, s32 index)
{
	if (index <= 0) {
		return;
	}
	if (index >= 3) {
		return;
	}
	state->index = index;
}

extern "C" void fn_2_408C(RenderState* state)
{
	state->wrap_enabled = 1;
}

extern "C" void fn_2_4098(RenderState* state, s32 value)
{
	for (int index = 0; index != state->count; index++) {
		if (value == state->values[index]) {
			state->index = index;
			fn_2_40F0(state);
			break;
		}
	}
}

extern "C" void fn_2_40F0(RenderState* state)
{
	if (state->wrap_enabled != 0) {
		if (state->index < 0) {
			state->index = state->count - 1;
		}
		if (state->count <= state->index) {
			state->index = 0;
		}
	} else {
		if (state->index < 0) {
			state->index = 0;
		}
		if (state->count <= state->index) {
			state->index = state->count - 1;
		}
	}
}
