#include "autosaveD/ADV_WINDOW.hpp"
#include "game/TNECFont.hpp"

struct GlobalState {
	u32 unk_0x0;
	u32 tick_high;
	u32 tick_low;
};

struct AutosaveState {
	s32 unk_0x0;
	s32 unk_0x4;
	s32 unk_0x8;
	s32 unk_0xC;
	s32 unk_0x10;
	f32 unk_0x14;
	f32 unk_0x18;
	f32 unk_0x1C;
	f32 unk_0x20;
	f32 unk_0x24;
	s32 unk_0x28;
	u32 unk_0x2C;
	u32 tick_high;
	u32 tick_low;
	s32 unk_0x38;
	s32 unk_0x3C;
	s32 unk_0x40;
};

struct Selector {
	s32 items[32];
	s32 count;
	s32 index;
	s32 wrap;
};

extern u8 lbl_80303EC8[];
extern GlobalState lbl_8029BB80;
extern const f32 lbl_2_rodata_348;

extern "C" void fn_801301C8(void* resource);
extern "C" s32 fn_800A92E0(void* input, s32 button, s32 port);
extern "C" void fn_2_40F0(Selector* selector);

//TODO: Move those
void ADV_WINDOW::Finalize()
{
	NECFont.Finalize();
	FinalizeCore();
}

void ADV_WINDOW::Initialize()
{
	InitializeCore();
	NECFont.Initialize();
}

extern "C" void fn_2_4004(AutosaveState* state)
{
	state->unk_0x0   = 0;
	state->unk_0x4   = 0;
	state->unk_0x8   = 0;
	state->unk_0xC   = 0;
	state->unk_0x10  = 0;
	state->unk_0x14  = lbl_2_rodata_348;
	state->unk_0x18  = lbl_2_rodata_348;
	state->unk_0x1C  = lbl_2_rodata_348;
	state->unk_0x20  = lbl_2_rodata_348;
	state->unk_0x24  = lbl_2_rodata_348;
	state->unk_0x28  = 0;
	state->unk_0x2C  = 0;
	state->tick_high = lbl_8029BB80.tick_high;
	state->tick_low  = lbl_8029BB80.tick_low;
	state->unk_0x38  = 0;
	state->unk_0x3C = state->unk_0x40 = 1;
}

extern "C" void fn_2_4070(void* window) { }
