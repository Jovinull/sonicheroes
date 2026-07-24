#include "types.h"

typedef struct Task Task;

extern "C" s32 lbl_2_bss_40;

extern "C" void* fn_2_1424(u32 size);
extern "C" Task* fn_2_211C(Task* task, void* context);
extern "C" void fn_80130464(s32 type);

extern "C" void fn_2_2294(void* context)
{
	if (context != NULL) {
		if (lbl_2_bss_40 != 0) {
			Task* task = (Task*)fn_2_1424(0x38);
			if (task != NULL) {
				fn_2_211C(task, context);
			}
		} else {
			fn_80130464(2);
		}
	}
}
