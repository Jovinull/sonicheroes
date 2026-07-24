#include "types.h"

typedef struct Task {
	u8 padding[0x18];
	void* class_table;
} Task;

extern "C" u8 lbl_2_data_3C0[0x30];

extern "C" void fn_80130464(s32 type);
extern "C" Task* dtor_800186D0(Task* task, s32 flags);
extern "C" void fn_2_13F4(void* memory);

extern "C" Task* fn_2_20A8(Task* task, s16 flags)
{
	if (task != NULL) {
		task->class_table = lbl_2_data_3C0;
		fn_80130464(2);
		dtor_800186D0(task, 0);

		if (flags > 0) {
			fn_2_13F4(task);
		}
	}

	return task;
}
