#include "types.h"

// TObjEnemy::CanCheckTechnicPointForThunderShoot: whether the enemy's state
// (0x19C) is other than 0x24 and 0x25.

struct Enemy {
	u8 unk000[0x19C];
	s32 state; // 0x19C
};

extern "C" s32 CanCheckTechnicPointForThunderShoot__9TObjEnemyFv(Enemy* enemy)
{
	s32 state = enemy->state;
	switch (state) {
		case 0x24:
		case 0x25:
			return 0;
		default:
			return 1;
	}
}
