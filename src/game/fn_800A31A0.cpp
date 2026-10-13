#include "types.h"

// The enemy's set-data field (bits 18 to 20 of the flags at 0x18 of its set
// data, 0xB0) plus 8.

struct EnemySetData {
	u8 unk00[0x18];
	u32 flags; // 0x18
};

struct Enemy {
	u8 unk00[0xB0];
	EnemySetData* setData; // 0xB0
};

extern "C" s32 fn_800A31A0(Enemy* enemy)
{
	return ((enemy->setData->flags & 0x1C0000) >> 18) + 8;
}
