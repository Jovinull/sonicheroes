#include "types.h"

// TObjEnemyPawn::BiteNail (the PS2 build's name, by its member order): returns
// whether the pawn keeps biting its nails. When the enemy base says so
// (fn_800A5DA8) it turns to its target (fn_800A51E4 kind 4). With a target it
// measures the way back to its set position (unused) and stops biting once
// the base says it is done (fn_800A6D44); otherwise, after 0xF0 frames, it
// picks its starting mode again (as it does at once without a target). Then
// it turns, steps, lands and closes a finished turn like the other moves.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct Pawn {
	u8 unk000[0x106];
	u16 status; // 0x106
	u8 unk108[0x54];
	f32 riseSpeed; // 0x15C
	u8 unk160[0x30];
	s8 target; // 0x190
	u8 unk191[0x17];
	f32 fallSpeed; // 0x1A8
	u8 unk1AC[0x14];
	RwV3d setPos; // 0x1C0
	u8 unk1CC[0x84];
	s32 timer; // 0x250
} Pawn;

extern "C" const f32 pawnZero[1];
extern "C" const f32 pawnMinusOne[1];
extern "C" const f32 pawnLandScale[1];

extern "C" int fn_800A5DA8(Pawn* pawn);
extern "C" int fn_800A5844(Pawn* pawn);
extern "C" void fn_800A51E4(Pawn* pawn, int a, int b);
extern "C" RwV3d* fn_800A57F0(Pawn* pawn, int player);
extern "C" int fn_800A6D44(Pawn* pawn);
extern "C" int fn_800A59C4(Pawn* pawn);
extern "C" void fn_800A4668(Pawn* pawn);
extern "C" void fn_800A4F34(Pawn* pawn);
extern "C" void fn_800A5C6C(Pawn* pawn, u32 flags);
extern "C" int fn_800A5888(Pawn* pawn, f32 value);
extern "C" void fn_800A5B50(Pawn* pawn, u32 flags);
extern "C" void SelectInitialMode__13TObjEnemyPawnFv(Pawn* pawn);
f32 DistanceP2P(const RwV3d* a, const RwV3d* b);

extern "C" int BiteNail__13TObjEnemyPawnFv(Pawn* pawn)
{
	int biting = 1;

	if (fn_800A5DA8(pawn)) {
		fn_800A51E4(pawn, 4, fn_800A5844(pawn));
	}
	if (pawn->target != -1) {
		DistanceP2P(fn_800A57F0(pawn, -1), &pawn->setPos);
		if (fn_800A6D44(pawn)) {
			biting = 0;
		} else {
			fn_800A59C4(pawn);
			if (pawn->timer++ > 0xF0) {
				pawn->timer = 0;
				SelectInitialMode__13TObjEnemyPawnFv(pawn);
			}
		}
	} else {
		SelectInitialMode__13TObjEnemyPawnFv(pawn);
	}
	fn_800A4668(pawn);
	fn_800A4F34(pawn);
	fn_800A5C6C(pawn, 0xF00);
	if ((pawn->status & 2) && pawn->riseSpeed < pawnLandScale[0] * pawn->fallSpeed) {
		pawn->riseSpeed = pawnZero[0];
	}
	if (fn_800A5888(pawn, pawnMinusOne[0])) {
		fn_800A5B50(pawn, 0xF00);
	}
	return biting;
}
