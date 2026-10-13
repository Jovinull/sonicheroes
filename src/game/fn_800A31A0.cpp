#include "types.h"

// TObjEnemy::GetCurrentLightNum: the enemy's light number, bits 18 to 20 of
// the flags at 0x18 of its set data (0xB0) plus 8.

struct EnemySetData {
	u8 unk00[0x18];
	u32 flags; // 0x18
};

struct Enemy {
	u8 unk00[0xB0];
	EnemySetData* setData; // 0xB0
};

extern "C" s32 GetCurrentLightNum__9TObjEnemyFv(Enemy* enemy)
{
	return ((enemy->setData->flags & 0x1C0000) >> 18) + 8;
}
