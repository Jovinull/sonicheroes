#include "types.h"

typedef struct AutosaveState {
	u8 padding[0x44];
	void* task;
} AutosaveState;

extern "C" void fn_2_13E0(void* task);

extern "C" void fn_2_2E8(AutosaveState* state)
{
	if (state->task != NULL) {
		fn_2_13E0(state->task);
		state->task = NULL;
	}
}
