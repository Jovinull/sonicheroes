#include "types.h"

extern "C" void* lbl_8042C148;

extern "C" void fn_80018A34(void* manager, void* task);

extern "C" void fn_2_1424(void* task)
{
	fn_80018A34(lbl_8042C148, task);
}
