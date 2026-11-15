#include "types.h"

// Registers a player object in slot idx of the player tables: the object itself (lbl_802AD070),
// its action state (+0x6F0, lbl_802AD090), its motion block (+0x720, lbl_802AD0B0) and its record
// (+0x760, lbl_802AD0D0). The record's movement parameters (+0xC8, 0x84 bytes) are copied from the
// table lbl_80241560 entry of its character (+0x3) one value at a time, except +0x140, taken from
// the entry of its +0x1; fn_800E12FC(0) then runs on the record and the action's scale (+0x24) becomes
// lbl_8042D0E8. HYPOTHESIS: the parameter names (speeds, accelerations) are UNKNOWN.

struct Params8003EE58 {
	s32 kind;       // 0x0
	f32 values[32]; // 0x4 (values[29] is record +0x140)
};

struct Record8003EE58 {
	u8 pad0[0x1];
	s8 team; // 0x1
	u8 pad2;
	s8 character; // 0x3
	u8 pad4[0xC8 - 0x4];
	Params8003EE58 params; // 0xC8
};

struct Action8003EE58 {
	u8 pad0[0x24];
	f32 scaleX; // 0x24
	f32 scaleY; // 0x28
	f32 scaleZ; // 0x2C
};

struct Player8003EE58 {
	u8 pad0[0x6F0];
	Action8003EE58 action; // 0x6F0
};

extern "C" {
extern void* lbl_802AD070[];
extern Action8003EE58* lbl_802AD090[];
extern void* lbl_802AD0B0[];
extern Record8003EE58* lbl_802AD0D0[];
extern Params8003EE58 lbl_80241560[];
extern const f32 lbl_8042D0E8; // 1.0f
void fn_800E12FC(s32 unknown, Record8003EE58* record);
}

extern "C" void fn_8003EE58(s32 idx, Player8003EE58* player)
{
	Action8003EE58* action = (Action8003EE58*)((u8*)player + 0x6F0);
	Record8003EE58* record = (Record8003EE58*)((u8*)player + 0x760);

	lbl_802AD070[idx]         = player;
	lbl_802AD090[idx]         = action;
	lbl_802AD0B0[idx]         = (u8*)player + 0x720;
	lbl_802AD0D0[idx]         = record;
	Params8003EE58* params    = &lbl_80241560[record->character];
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
	record->params.values[29] = lbl_80241560[record->team].values[29];
	fn_800E12FC(0, record);
	action->scaleX = action->scaleY = action->scaleZ = lbl_8042D0E8;
}
