#include "game/effect/eff_bomb.h"
#include "game/object.h"

// SetEnemyShield (the PS2 build's name): builds an enemy's shield (ENEMY_SHIELD)
// under the given parent (else the effect root, else the object root), copies
// the position, normal and angle it is given, its scale (a zero scale turns its
// collision off), and arms its collision by kind: kind 0 takes 6 hits and
// guards, 1 takes 3, 2 takes 9.

#include "src/rel/enemy_shield.inc"

ENEMY_SHIELD* SetEnemyShield(
    TObject* parent, ENEMY_SHIELD_KIND kind, RwV3d* pos, f32 scale, RwV3d* normal, sAngle* ang)
{
	ENEMY_SHIELD* shield;

	if (parent == NULL) {
		parent = lbl_8042C2A0;
		if (parent == NULL) {
			parent = lbl_8042C114;
		}
	}
	shield = new ENEMY_SHIELD(parent);
	if (shield != NULL) {
		shield->Init(kind, pos, scale, normal, ang);
	}
	return shield;
}
