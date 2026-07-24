#include "types.h"

typedef struct Task {
	u8 padding[0x2C];
	void* callback;
} Task;

extern "C" void fn_8012CC20(void* callback);

extern "C" void fn_2_1FB4(Task* task)
{
	if (task->callback != NULL) {
		fn_8012CC20(task->callback);
	}
}
