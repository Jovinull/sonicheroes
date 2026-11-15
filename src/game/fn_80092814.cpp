#include "types.h"

// Loads a team member's movement parameters (the record's +0xC8, as fn_8003EE58 does from
// lbl_80241560) from the team table lbl_8024DDD0 (0x84-byte entries): entry 0 while the stage is
// busy (fn_80018EA8 on lbl_8029C310), else the entry of the leader's character (team +0x114 by
// +0x3B, its +0x761), one value at a time; the last five values (+0x138..+0x148) then come from
// the entry of the record's +0x1. HYPOTHESIS: the parameter names are UNKNOWN.

struct Params80092814 {
	s32 kind;       // 0x0
	f32 values[32]; // 0x4
};

struct Record80092814 {
	u8 pad0[0x1];
	s8 team; // 0x1
	u8 pad2[0xC8 - 0x2];
	Params80092814 params; // 0xC8
};

struct Player80092814 {
	u8 pad0[0x761];
	s8 character; // 0x761
};

struct Team80092814 {
	u8 pad0[0x3B];
	s8 current; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	Player80092814* members[3]; // 0x114
};

extern "C" {
extern Params80092814 lbl_8024DDD0[];
extern u8 lbl_8029C310[];
s32 fn_80018EA8(void* stage);
}

extern "C" void fn_80092814(Team80092814* team, Record80092814* record)
{
	Params80092814* params;

	if (fn_80018EA8(lbl_8029C310)) {
		params = lbl_8024DDD0;
	} else {
		params = &lbl_8024DDD0[team->members[team->current]->character];
	}
	record->params.kind       = params->kind;
	record->params.values[0]  = params->values[0];
	record->params.values[1]  = params->values[1];
	record->params.values[2]  = params->values[2];
	record->params.values[3]  = params->values[3];
	record->params.values[4]  = params->values[4];
	record->params.values[5]  = params->values[5];
	record->params.values[6]  = params->values[6];
	record->params.values[7]  = params->values[7];
	record->params.values[8]  = params->values[8];
	record->params.values[9]  = params->values[9];
	record->params.values[10] = params->values[10];
	record->params.values[11] = params->values[11];
	record->params.values[12] = params->values[12];
	record->params.values[13] = params->values[13];
	record->params.values[14] = params->values[14];
	record->params.values[15] = params->values[15];
	record->params.values[16] = params->values[16];
	record->params.values[17] = params->values[17];
	record->params.values[18] = params->values[18];
	record->params.values[19] = params->values[19];
	record->params.values[20] = params->values[20];
	record->params.values[21] = params->values[21];
	record->params.values[22] = params->values[22];
	record->params.values[23] = params->values[23];
	record->params.values[24] = params->values[24];
	record->params.values[25] = params->values[25];
	record->params.values[26] = params->values[26];
	record->params.values[27] = params->values[27];
	record->params.values[28] = params->values[28];
	record->params.values[29] = params->values[29];
	record->params.values[30] = params->values[30];
	record->params.values[31] = params->values[31];
	params                    = &lbl_8024DDD0[record->team];
	record->params.values[27] = params->values[27];
	record->params.values[28] = params->values[28];
	record->params.values[29] = params->values[29];
	record->params.values[30] = params->values[30];
	record->params.values[31] = params->values[31];
}
