#include "types.h"

extern "C" void* lbl_8042C148;

extern "C" void fn_800189A4(void* manager, void* task);

extern "C" void fn_2_13F4(void* task)
{
	fn_800189A4(lbl_8042C148, task);
}
