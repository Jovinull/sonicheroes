#include "types.h"

// Whether the given value is below the enemy's float at 0x210.

struct Enemy {
	u8 unk000[0x210];
	f32 limit; // 0x210
};

extern "C" u32 fn_800A6D44(Enemy* enemy, f32 value)
{
	return value < enemy->limit;
}
