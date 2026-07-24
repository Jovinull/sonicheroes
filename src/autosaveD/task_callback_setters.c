#include "types.h"

typedef struct Task {
	u8 padding_00[0x1C];
	void* callback_1C;
	u8 padding_20[0x0C];
	void* callback_2C;
	void* callback_30;
} Task;

extern "C" void fn_2_1ED4(Task* task, void* callback)
{
	task->callback_1C = callback;
}

extern "C" void fn_2_1EDC(Task* task, void* callback)
{
	task->callback_2C = callback;
}

extern "C" void fn_2_1EE4(Task* task, void* callback)
{
	task->callback_30 = callback;
}

extern "C" void fn_2_1EEC(void) { }
