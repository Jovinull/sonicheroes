#include "game/effect/eff_bomb.h"
#include "game/object.h"

// ENEMY_SHOT::Cancel, ENEMY_SHOT::Create and SetEnemyShot (the PS2 build's
// names). Cancel removes the shot with a number from the enemy root; Create fires a
// shot under the enemy root and hands back its number (from the live shot
// count); SetEnemyShot fires an enemy shot of the given kind
// from a point with a velocity, under the given parent (else the effect root,
// else the object root). The shot (ENEMY_SHOT) is a moving object with a
// collision sphere sized to its step, faces along its velocity, and plays the
// shot sound 0x4061 where it starts. Its destructor is rel/enemy_shot_dtor.cpp.

#include "src/rel/enemy_shot.inc"

void ENEMY_SHOT::Cancel(u16 id)
{
	KillTask(lbl_8042C10C, id);
}

int ENEMY_SHOT::Create(u16& id, int kind, RwV3d* vel, RwV3d* pos)
{
	ENEMY_SHOT* shot = new ENEMY_SHOT(lbl_8042C10C);

	if (shot != NULL) {
		shot->Tag = enemyShotCount++;
		if (kind) {
			shot->SetFlagToCheckGround();
		} else {
			shot->ClearFlagToCheckGround();
		}
		shot->Init(pos, vel);
		if (lbl_8042C388 != NULL) {
			fn_800B4A38(lbl_8042C388, 0x4061, pos, NULL, 1, 2, 0);
		}
		id = shot->Tag;
		return 1;
	}
	return 0;
}

ENEMY_SHOT* SetEnemyShot(TObject* parent, int kind, RwV3d* vel, RwV3d* pos)
{
	ENEMY_SHOT* shot;

	if (parent == NULL) {
		parent = lbl_8042C2A0;
		if (parent == NULL) {
			parent = lbl_8042C114;
		}
	}
	shot = new ENEMY_SHOT(parent);
	if (shot != NULL) {
		if (kind) {
			shot->SetFlagToCheckGround();
		} else {
			shot->ClearFlagToCheckGround();
		}
		shot->Init(pos, vel);
		if (lbl_8042C388 != NULL) {
			fn_800B4A38(lbl_8042C388, 0x4061, pos, NULL, 1, 2, 0);
		}
	}
	return shot;
}
