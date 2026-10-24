#include "types.h"

// TObjPropeller::SnatchPlayer (the PS2 build's name, by its place in the PS2
// order; propellerSnatchPlayer here), static: the first propeller (task kind
// 0x28) holding the player lets go of it; whether one did.

typedef struct SnatchHold {
	u8 unk0[0x4];
	s8* holder; // 0x04
} SnatchHold;

typedef struct SnatchTask {
	u8 unk00[0x28];
	u16 kind;         // 0x28
	u8 unk2A[0x6];    // 0x2A
	SnatchHold* hold; // 0x30
	u8 unk34[0x4];    // 0x34
	SnatchTask* next; // 0x38
} SnatchTask;

typedef struct SnatchTasks {
	u8 unk000[0x210];
	SnatchTask* first; // 0x210
} SnatchTasks;

extern "C" SnatchTasks* lbl_8042C298;

extern "C" s32 propellerSnatchPlayer(s32 player)
{
	for (SnatchTask* task = lbl_8042C298->first; task != NULL; task = task->next) {
		if (task->kind == 0x28 && task->hold != NULL && task->hold->holder != NULL
		    && *task->hold->holder == player) {
			*task->hold->holder = -1;
			return 1;
		}
	}
	return 0;
}
