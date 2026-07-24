#include "types.h"

typedef struct Task {
	u8 padding[4];
	u16 flags;
} Task;

extern "C" void fn_2_13E0(Task* task)
{
	task->flags |= 1;
}
