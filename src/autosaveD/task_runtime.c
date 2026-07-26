#include "autosaveD/ADV_WINDOW.hpp"

struct Task {
	u8 padding[4];
	u16 flags;
};

extern "C" u8 lbl_2_data_A8[0x18];
extern "C" void* lbl_8042C148;

extern "C" void fn_80126254(void);
extern "C" void fn_801262DC(void);
extern "C" void fn_8012CA94(void* state);
extern "C" void fn_8012CB70(void* state);
extern "C" void fn_800189A4(void* heap, void* memory);
extern "C" void* fn_80018A34(void* heap, u32 size);

extern "C" void fn_2_136C(void)
{
	ADV_WINDOW::Finalize();
	fn_80126254();
	fn_8012CA94(lbl_2_data_A8);
}

extern "C" void fn_2_139C(void)
{
	fn_8012CB70(lbl_2_data_A8);
	fn_801262DC();
	ADV_WINDOW::Initialize();
}

extern "C" void fn_2_13CC() { }

// Purposely stubbed functions for this rel
void TObject::PDisp() { }
void TObject::ImmAftSetRaster() { }
void TObject::Debug() { }
void TObject::Render() { }

extern "C" void fn_2_13E0(Task* task)
{
	task->flags |= 1;
}

extern "C" void fn_2_13F4(void* memory)
{
	fn_800189A4(lbl_8042C148, memory);
}

extern "C" void* fn_2_1424(u32 size)
{
	return fn_80018A34(lbl_8042C148, size);
}
