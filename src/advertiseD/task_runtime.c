#include "types.h"

// The module's allocator pair and the flag that retires a task, plus the two
// empty hooks beside them.
//
// The translation unit runs from fn_1_AD0 at 0xAD0 to the end of fn_1_B1C at
// 0xB4C. It is the same file autosaveD carries at 0x136C, down to the heap
// pointer being a DOL global the two wrappers read rather than take.

typedef struct Task {
	u8 padding[4]; // 0x00
	u16 flags;     // 0x04
} Task;

extern "C" void* lbl_8042C148;

extern "C" void fn_800189A4(void* heap, void* memory);
extern "C" void* fn_80018A34(void* heap, u32 size);

extern "C" void fn_1_AD0(void) { }

extern "C" void fn_1_AD4(void) { }

extern "C" void fn_1_AD8(Task* task)
{
	task->flags |= 1;
}

extern "C" void fn_1_AEC(void* memory)
{
	fn_800189A4(lbl_8042C148, memory);
}

extern "C" void* fn_1_B1C(u32 size)
{
	return fn_80018A34(lbl_8042C148, size);
}
