// Removes an object's RenderWare parts from a world (HYPOTHESIS; the owner type is UNKNOWN):
// passes each of its two atomics (0x34, 0x38) to fn_8015BD84 and its clump (0x28) to fn_8015B8E8,
// skipping empty slots. The callees are HYPOTHESIS: RpWorldRemoveAtomic and RpWorldRemoveClump.
// Built with the game-unit flags of its neighbours (eventCore.cpp, SeqFlagCtrl.cpp): retail
// restores the saved registers before the link register, as -opt noschedule,nopeephole does.
#include "types.h"

struct Owner8011EF2C {
	u8 pad0[0x28];
	void* clump; // 0x28
	u8 pad2C[0x34 - 0x2C];
	void* atomics[2]; // 0x34
};

extern "C" {
void fn_8015BD84(void* world, void* atomic);
void fn_8015B8E8(void* world, void* clump);

void fn_8011EF2C(Owner8011EF2C* owner, void* world)
{
	s32 i;

	for (i = 0; i != 2; i++) {
		if (owner->atomics[i] != 0) {
			fn_8015BD84(world, owner->atomics[i]);
		}
	}
	if (owner->clump != 0) {
		fn_8015B8E8(world, owner->clump);
	}
}
}
