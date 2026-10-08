#include "types.h"

struct Task {
	u8 padding[4];
	u16 flags;
};

extern "C" u8 lbl_2_data_A8[0x18];
extern "C" void* lbl_8042C148;

extern "C" void fn_2_3FAC(void);
extern "C" void fn_2_3FD8(void);
extern "C" void fn_80126254(void);
extern "C" void fn_801262DC(void);
extern "C" void fn_8012CA94(void* state);
extern "C" void fn_8012CB70(void* state);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* memory);
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);

extern "C" void fn_2_136C(void)
{
	fn_2_3FAC();
	fn_80126254();
	fn_8012CA94(lbl_2_data_A8);
}

extern "C" void fn_2_139C(void)
{
	fn_8012CB70(lbl_2_data_A8);
	fn_801262DC();
	fn_2_3FD8();
}

extern "C" void fn_2_13CC(void) { }

extern "C" void fn_2_13D0(void) { }

extern "C" void fn_2_13D4(void) { }

extern "C" void fn_2_13D8(void) { }

extern "C" void fn_2_13DC(void) { }

extern "C" void fn_2_13E0(Task* task)
{
	task->flags |= 1;
}

extern "C" void fn_2_13F4(void* memory)
{
	Free__9THeapCtrlFPv(lbl_8042C148, memory);
}

extern "C" void* fn_2_1424(u32 size)
{
	return Malloc__9THeapCtrlFUi(lbl_8042C148, size);
}
