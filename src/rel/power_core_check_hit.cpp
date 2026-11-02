#include "types.h"

// TEnemyPowerCore::CheckHitCollision (the PS2 build's name), the same in the
// bonus stages (31D-33D): while its collision is on, a hit hands over the
// touching player's number. Returns whether something hit it.

typedef struct PowerCoreHitter {
	u8 unk00[0x78];
	s32 player; // 0x78
} PowerCoreHitter;

typedef struct PowerCoreHit {
	u8 unk00[0x4];
	PowerCoreHitter* hitter; // 0x04
} PowerCoreHit;

typedef struct C_COLLI {
	u8 unk00[0x8];
	u16 flags; // 0x08
	u8 unk0A[0x7E];
} C_COLLI; // 0x88

typedef struct PowerCore {
	u8 unk00[0x28];
	C_COLLI colli; // 0x28
	u8 unkB0[0x2C];
	s32 player; // 0xDC
} PowerCore;

extern "C" u8 lbl_8042C1A4[];

extern "C" void fn_80021824(void* list);
extern "C" PowerCoreHit* fn_800211A8(C_COLLI* colli);

extern "C" s32 CheckHitCollision__15TEnemyPowerCoreFv(PowerCore* object)
{
	if (object->colli.flags & 1) {
		PowerCoreHit* hit;
		PowerCoreHitter* hitter;

		fn_80021824(lbl_8042C1A4);
		hit = fn_800211A8(&object->colli);
		if (hit != NULL) {
			hitter = hit->hitter;
		} else {
			hitter = NULL;
		}
		if (hitter != NULL) {
			object->player = hitter->player;
			return 1;
		}
	}
	return 0;
}
