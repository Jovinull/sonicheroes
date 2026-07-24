#include "types.h"

extern "C" void* lbl_8042C148;

extern "C" void fn_800189A4(void* heap, void* memory);

extern "C" void fn_2_13F4(void* memory)
{
	fn_800189A4(lbl_8042C148, memory);
}
