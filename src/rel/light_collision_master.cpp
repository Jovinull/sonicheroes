#include "types.h"

// Three of TObjLightColliMaster's static members (the PS2 build's names and
// signatures), over the module's list of light collisions (lightCollisionHead,
// TopLightColli on PS2): SetAllSwitchLightOff turns light `no` off in every
// switch-kind collision that has it on, and SetTopLightColli and
// GetTopLightColli set and read the list's head.

typedef struct LightColli {
	u8 unk00[0x30];
	s8 lights[8]; // 0x30
	s8 unk38;     // 0x38
	s8 kind;      // 0x39
	u8 pad3A[0x2];
	struct LightColli* next; // 0x3C
} LightColli;

extern "C" LightColli* lightCollisionHead;

extern "C" void SetAllSwitchLightOff__20TObjLightColliMasterFSc(s8 no)
{
	LightColli* colli;

	for (colli = lightCollisionHead; colli != NULL; colli = colli->next) {
		if (colli->kind == 1 && colli->lights[no] == 1) {
			colli->lights[no] = 0;
		}
	}
}

extern "C" void SetTopLightColli__20TObjLightColliMasterFP14TObjLightColli(LightColli* colli)
{
	lightCollisionHead = colli;
}

extern "C" LightColli* GetTopLightColli__20TObjLightColliMasterFv(void)
{
	return lightCollisionHead;
}
