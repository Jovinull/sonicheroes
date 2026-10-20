#include "types.h"

// The particle material's instance chain, in the stage modules' own copies
// (whose top keeps the last instance as its prev): the count of instances in
// it (particleChainCount here; the PS2 build has no such member), and
// PARTICLE_MATERIAL::UnlinkChainInstance and LinkChainInstance (the PS2
// build's names), which take an instance out or add it at the end, counting it
// out or in when it is a counted one.

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
	void LinkChainInstance(PARTICLE_INSTANCE* instance);

	u8 unk00[0x38];         // 0x00
	s32 instanceNum;        // 0x38
	PARTICLE_INSTANCE* top; // 0x3C
};

extern "C" s32 particleChainCount(PARTICLE_MATERIAL* material)
{
	PARTICLE_INSTANCE* instance = material->top;
	s32 count                   = 0;

	while (instance != NULL) {
		count++;
		instance = instance->next;
	}
	return count;
}

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

void PARTICLE_MATERIAL::LinkChainInstance(PARTICLE_INSTANCE* instance)
{
	PARTICLE_INSTANCE* last;
	PARTICLE_INSTANCE* first = top;

	if (first == NULL) {
		top            = instance;
		instance->next = NULL;
		instance->prev = instance;
	} else {
		last           = first->prev;
		last->next     = instance;
		first->prev    = instance;
		instance->next = NULL;
		instance->prev = last;
	}
	if (instance->counted == 1) {
		instanceNum++;
	}
}
