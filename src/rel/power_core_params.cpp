#include "types.h"

// sEnemyPowerCore's constructor (the PS2 build's type name), the same in the
// bonus stages (31D-33D): the spawn parameters of a power core, cleared with
// 2.5 at 0x10 (TEnemyPowerCoreMan's constructor inlines the same).

typedef struct sEnemyPowerCore {
	f32 unk00; // 0x00
	f32 unk04; // 0x04
	f32 unk08; // 0x08
	f32 unk0C; // 0x0C
	f32 unk10; // 0x10
	u8 unk14[0x4];
	f32 unk18; // 0x18
	f32 unk1C; // 0x1C
	s32 unk20; // 0x20
} sEnemyPowerCore;

extern "C" const f32 powerCoreManZero;
extern "C" const f32 powerCoreManReach;

extern "C" sEnemyPowerCore* __ct__15sEnemyPowerCoreFv(sEnemyPowerCore* params)
{
	params->unk00 = params->unk04 = params->unk08 = powerCoreManZero;
	params->unk08                                 = powerCoreManZero;
	params->unk0C                                 = powerCoreManZero;
	params->unk10                                 = powerCoreManReach;
	params->unk18                                 = powerCoreManZero;
	params->unk1C                                 = powerCoreManZero;
	params->unk20                                 = 0;
	return params;
}
