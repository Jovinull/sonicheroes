// TObjEnemy::Explosion (symbol name from the retail map): marks the enemy as exploded (flag
// 0x200 at +0x188) and, when its explosion effects are on (flag 0x10), spawns the particle
// effects 6, 2 and 15 at its position and angle, the sound/effect request 0x405B, and the debris
// of the common clump 5 of the enemy database turned by half a turn. Effect ids and the role of
// lbl_8042C388 are UNKNOWN.
#include "game/enemy/e_obj_enemy.h"
#include "game/enemy/e_database.h"

void SetEffectCrash3D_R(TObject*, RwV3d*, sAngle*, RwV3d*, RwV3d*, f32, f32, s32, s16, RpClump*);

extern "C" {
extern void* lbl_8042C388;
extern TObject* lbl_8042C2A0;
extern const RwV3d lbl_80239F10; // debris scale (UNKNOWN values)
extern f32 lbl_8042DA70;
extern f32 lbl_8042DA74;
void* fn_8006298C(s32, RwV3d*, sAngle*);
void fn_800B4A38(void*, s32, RwV3d*, s32, s32, s32, s32);
}

void TObjEnemy::Explosion()
{
	flags |= 0x200;
	if (flags & 0x10) {
		RwV3d pos  = position;
		sAngle ang = angle;

		// The retail code tests the flag a second time here (a second beq on the same compare);
		// HYPOTHESIS: an inlined helper with its own guard.
		if (flags & 0x10) {
			RpClump* clump;

			fn_8006298C(6, &pos, &ang);
			fn_8006298C(2, &pos, &ang);
			if (lbl_8042C388) {
				fn_800B4A38(lbl_8042C388, 0x405B, &pos, 0, 1, 2, 0);
			}
			fn_8006298C(15, &pos, &ang);
			clump = TEnemyDataBase::GetInstance()->SearchClump(ENEMY_DB_COMMON, 5);
			if (clump) {
				RwV3d scale = lbl_80239F10;

				ang.y += 0x8000;
				SetEffectCrash3D_R(lbl_8042C2A0, &pos, &ang, &scale, NULL, lbl_8042DA70,
				    lbl_8042DA74, 0, 0, clump);
			}
		}
	}
}
