#include "game/effect/eff_crash3d.h"
#include "game/enemy/e_database.h"

// TObjEnemyPawn::Explosion (the PS2 build's name): marks the pawn as blown up
// and, when it is shown, sets off the explosion effects (6, 2 and 15) a little
// above it with sound 0xE017, and scatters the enemy database's pieces (model 5)
// as a crash effect turned half a circle.

typedef struct Pawn {
	u8 unk000[0x140];
	RwV3d pos;  // 0x140
	sAngle ang; // 0x14C
	u8 unk158[0x30];
	u32 flags; // 0x188
} Pawn;

extern "C" void* lbl_8042C388;
extern "C" TObject* lbl_8042C2A0;
extern "C" const RwV3d pawnPieceSpeed;
extern "C" const f32 pawnPieceGravity[1];
extern "C" const f32 pawnShieldSpeed[1];
extern "C" const f32 pawnZero[1];

void SetEffectCrash3D_R(TObject*, RwV3d*, sAngle*, RwV3d*, RwV3d*, f32, f32, s32, s16, RpClump*);
extern "C" TObject* fn_8006298C(s32 effect, RwV3d* pos, sAngle* ang);
extern "C" void fn_800B4A38(
    void* sound, u16 id, RwV3d* pos, void* object, s32 kind, s32 arg5, s32 range);

extern "C" void Explosion__13TObjEnemyPawnFv(Pawn* pawn)
{
	pawn->flags |= 0x200;
	if (pawn->flags & 0x10) {
		RwV3d pos  = pawn->pos;
		sAngle ang = pawn->ang;

		pos.y += pawnShieldSpeed[0];
		if (pawn->flags & 0x10) {
			RpClump* clump;

			fn_8006298C(6, &pos, &ang);
			fn_8006298C(2, &pos, &ang);
			if (lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0xE017, &pos, NULL, 1, 2, 0);
			}
			fn_8006298C(0xF, &pos, &ang);
			clump = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)0, 5);
			if (clump != NULL) {
				RwV3d speed = pawnPieceSpeed;

				ang.y += 0x8000;
				SetEffectCrash3D_R(lbl_8042C2A0, &pos, &ang, &speed, NULL, pawnPieceGravity[0],
				    pawnZero[0], 0, 0, clump);
			}
		}
	}
}
