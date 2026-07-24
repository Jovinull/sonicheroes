#include "types.h"

struct RenderParams {
	u32 unk0;
	u32 unk4;
	u32 unk8;
	u32 unkC;
	u32 unk10;
	f32 unk14;
	f32 unk18;
	f32 unk1C;
	f32 unk20;
	f32 unk24;
	u32 unk28;
	u32 unk2C;
	u32 tick0;
	u32 tick1;
	u32 unk38;
	u32 unk3C;
	u32 unk40;
};

struct SharedState {
	u32 unk0;
	u32 tick0;
	u32 tick1;
};

extern "C" const f32 lbl_2_rodata_348;
extern "C" SharedState lbl_8029BB80;

extern "C" void fn_2_4004(RenderParams* params)
{
	params->unk0  = 0;
	params->unk4  = 0;
	params->unk8  = 0;
	params->unkC  = 0;
	params->unk10 = 0;
	params->unk14 = lbl_2_rodata_348;
	params->unk18 = lbl_2_rodata_348;
	params->unk1C = lbl_2_rodata_348;
	params->unk20 = lbl_2_rodata_348;
	params->unk24 = lbl_2_rodata_348;
	params->unk28 = 0;
	params->unk2C = 0;
	params->tick0 = lbl_8029BB80.tick0;
	params->tick1 = lbl_8029BB80.tick1;
	params->unk38 = 0;
	params->unk40 = 1;
	params->unk3C = 1;
}
