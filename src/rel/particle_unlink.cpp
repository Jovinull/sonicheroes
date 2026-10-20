#include "types.h"

// PARTICLE_MATERIAL::UnlinkChainInstance (the PS2 build's name; the stage
// modules carry their own copy): takes an instance out of the material's
// chain (whose top keeps the last instance as its prev), counting it out when
// it was counted in, and clears its links.

struct PARTICLE_INSTANCE {
	u8 unk00[0x24];          // 0x00
	PARTICLE_INSTANCE* prev; // 0x24
	PARTICLE_INSTANCE* next; // 0x28
	s32 counted;             // 0x2C
};

class PARTICLE_MATERIAL
{
public:
	void UnlinkChainInstance(PARTICLE_INSTANCE* instance);

	u8 unk00[0x38];         // 0x00
	s32 instanceNum;        // 0x38
	PARTICLE_INSTANCE* top; // 0x3C
};

void PARTICLE_MATERIAL::UnlinkChainInstance(PARTICLE_INSTANCE* instance)
{
	if (instance->counted == 1) {
		instanceNum--;
	}
	if (top == instance) {
		top = instance->next;
		if (top != NULL) {
			top->prev = instance->prev;
		}
		instance->prev = instance->next = NULL;
		return;
	}
	if (top->prev == instance) {
		PARTICLE_INSTANCE* prev = instance->prev;

		prev->next     = NULL;
		top->prev      = prev;
		instance->prev = instance->next = NULL;
		return;
	}
	PARTICLE_INSTANCE* prev = instance->prev;
	PARTICLE_INSTANCE* next = instance->next;

	prev->next     = next;
	next->prev     = prev;
	instance->prev = instance->next = NULL;
}
