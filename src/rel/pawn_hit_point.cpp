#include "types.h"

// Two TObjEnemyPawn members (the PS2 build's names, by its member order):
// - CheckDamage: whether the pawn has lost hit points (hp below its maximum);
// - CheckHitPoint: when the hp dropped below the shown value, updates it and
//   shows the hit-point gauge (in its long form when flag 0x2000 is set) and
//   hides the other icon, returning whether it did; then keeps both icons over
//   the pawn.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

class TEnemyIconMan
{
public:
	void On(f32 value, f32 max);
	void On(f32 value, f32 max, int wide);
	void Off();
	void SetPos(const RwV3d* pos, const RwV3d* offset);
};

typedef struct Pawn {
	u8 unk000[0x140];
	RwV3d pos; // 0x140
	u8 unk14C[0x40];
	u32 flags; // 0x18C
	u8 unk190[0x14];
	f32 hp; // 0x1A4
	u8 unk1A8[0x130];
	TEnemyIconMan* gauge; // 0x2D8
	TEnemyIconMan* icon;  // 0x2DC
	f32 shownHp;          // 0x2E0
	u8 unk2E4[0x14];
	f32 maxHp; // 0x2F8
} Pawn;

extern "C" const RwV3d pawnIconOffset;

extern "C" bool CheckDamage__13TObjEnemyPawnFv(Pawn* pawn)
{
	return pawn->maxHp != pawn->hp;
}

extern "C" int CheckHitPoint__13TObjEnemyPawnFv(Pawn* pawn)
{
	int changed = 0;

	if (pawn->hp < pawn->shownHp) {
		pawn->shownHp = pawn->hp;
		if (pawn->gauge != NULL) {
			if (pawn->flags & 0x2000) {
				pawn->gauge->On(pawn->shownHp, pawn->maxHp, 100);
			} else {
				pawn->gauge->On(pawn->shownHp, pawn->maxHp);
			}
		}
		if (pawn->icon != NULL) {
			pawn->icon->Off();
		}
		changed = 1;
	}
	if (pawn->gauge != NULL) {
		pawn->gauge->SetPos(&pawn->pos, &pawnIconOffset);
	}
	if (pawn->icon != NULL) {
		pawn->icon->SetPos(&pawn->pos, &pawnIconOffset);
	}
	return changed;
}
