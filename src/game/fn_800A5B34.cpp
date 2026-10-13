#include "types.h"

// Copies the enemy's position (0x140) into its aim point (0x1E4).

struct Enemy {
	u8 unk000[0x140];
	f32 pos[3]; // 0x140
	u8 unk14C[0x98];
	f32 aim[3]; // 0x1E4
};

extern "C" void fn_800A5B34(Enemy* enemy)
{
	enemy->aim[0] = enemy->pos[0];
	enemy->aim[1] = enemy->pos[1];
	enemy->aim[2] = enemy->pos[2];
}
