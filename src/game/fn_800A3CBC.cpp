#include "types.h"

// Starts the enemy's lift: clears 0x21C, sets 0x218 to 5 and clears the low
// four bits of its status (0x106).

struct Enemy {
	u8 unk000[0x106];
	volatile u16 status; // 0x106
	u8 unk108[0x110];
	s32 liftMode;  // 0x218
	s32 liftTimer; // 0x21C
};

extern "C" void fn_800A3CBC(Enemy* enemy)
{
	u32 status;

	enemy->liftTimer = 0;
	enemy->liftMode  = 5;
	// Keep the explicit u16 narrowing after clearing the low four bits.
	status = enemy->status;
	status &= 0xFFFFFFF0;
	enemy->status = status;
}
