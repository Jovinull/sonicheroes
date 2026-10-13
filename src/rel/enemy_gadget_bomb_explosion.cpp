#include "game/effect/eff_bomb.h"
#include "game/enemy/e_database.h"

// TEnemyGadgetBomb::Explosion (the PS2 build's name): the bomb blows up where
// it is (a small bomb effect and sound 0xE017), scatters the enemy database's
// bomb pieces (model 5) as a crash effect, and goes to state 3.

typedef struct GadgetBomb {
	u8 unk00[0xBC];
	RwV3d pos; // 0xBC
	u8 unkC8[0x28];
	s32 state; // 0xF0
} GadgetBomb;

extern "C" void* lbl_8042C388;
extern "C" TObject* lbl_8042C2A0;
extern "C" const RwV3d gadgetBombPieceSpeed;
extern "C" const sAngle gadgetBombPieceSpin;
extern "C" const RwV3d gadgetBombPieceScale;
extern "C" const f32 gadgetBombPieceGravity[1];
extern "C" const f32 gadgetBombScaleXZ[1];

void SetEffectCrash3D_R(TObject*, RwV3d*, sAngle*, RwV3d*, RwV3d*, f32, f32, s32, s16, RpClump*);
extern "C" void fn_800B4A38(
    void* sound, u16 id, RwV3d* pos, void* object, s32 kind, s32 arg5, s32 range);

extern "C" void Explosion__16TEnemyGadgetBombFv(GadgetBomb* object)
{
	RpClump* clump;

	SetEffectBomb(NULL, &object->pos, NULL, ENUM_EFF_BOMB_TYPE_LBOMB, -1);
	if (lbl_8042C388 != NULL) {
		fn_800B4A38(lbl_8042C388, 0xE017, &object->pos, NULL, 1, 0, 0);
	}
	clump = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)0, 5);
	if (clump != NULL) {
		RwV3d scale = gadgetBombPieceScale;
		sAngle spin = gadgetBombPieceSpin;
		RwV3d speed = gadgetBombPieceSpeed;

		SetEffectCrash3D_R(lbl_8042C2A0, &object->pos, &spin, &speed, &scale,
		    gadgetBombPieceGravity[0], gadgetBombScaleXZ[0], 0, 0, clump);
	}
	object->state = 3;
}
