#include "types.h"

// Three of TObjWeight's checks (the PS2 build's names CheckPressTimeOver,
// CheckWaitTimeOver and CheckSwitchOn; weight* here). The two timer checks
// answer 0 while the game is paused, else whether the weight's timer has
// gone past the pressed or the waiting time. The switch check answers 0 for the
// kinds 0 to 2, else whether every switch of the weight's group is on.

typedef struct Weight {
	u8 unk00[0xB8]; // 0x00
	s8 kind;        // 0xB8
	u8 group;       // 0xB9
	s16 waitTime;   // 0xBA
	s16 pressTime;  // 0xBC
	u8 unkBE[0xE];  // 0xBE
	s32 timer;      // 0xCC
} Weight;

extern "C" u8* lbl_8042C180;
extern "C" s32 objGroupAllSet(u8 group);

extern "C" s32 weightCheckPressTimeOver(Weight* object)
{
	if ((s8)lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	return object->timer > object->pressTime;
}

extern "C" s32 weightCheckWaitTimeOver(Weight* object)
{
	if ((s8)lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	return object->timer > object->waitTime;
}

extern "C" s32 weightCheckSwitchOn(Weight* object)
{
	if (object->kind == 0 || object->kind == 1 || object->kind == 2) {
		return 0;
	}
	return objGroupAllSet(object->group) != 0;
}
