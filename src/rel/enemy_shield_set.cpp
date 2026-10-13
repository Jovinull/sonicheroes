#include "game/effect/eff_bomb.h"
#include "game/object.h"

// SetEnemyShield (the PS2 build's name): builds an enemy's shield (ENEMY_SHIELD)
// under the given parent (else the effect root, else the object root), copies
// the position, normal and angle it is given, its scale (a zero scale turns its
// collision off), and arms its collision by kind: kind 0 takes 6 hits and
// guards, 1 takes 3, 2 takes 9.

enum ENEMY_SHIELD_KIND {
	ENEMY_SHIELD_KIND_0,
	ENEMY_SHIELD_KIND_1,
	ENEMY_SHIELD_KIND_2,
};

class ENEMY_SHIELD : public TObject, public C_COLLI, public OBJ_MoveOnGround
{
public:
	ENEMY_SHIELD(TObject* parent);
	virtual ~ENEMY_SHIELD();

	s8 hits;   // 0x0E8
	u8 unkE9;  // 0x0E9
	s16 unkEA; // 0x0EA
	s16 unkEC; // 0x0EC
	u8 unkEE[0x2];
	s32 unkF0;    // 0x0F0
	s32 kind;     // 0x0F4
	RwV3d normal; // 0x0F8
	RwV3d pos;    // 0x104
	sAngle ang;   // 0x110
	f32 scale;    // 0x11C
	u8 unk120[0xC];
	RwV3d unk12C; // 0x12C
	u8 unk138[0x48];
	s32 unk180;   // 0x180
	s32 unk184;   // 0x184
	f32 unk188;   // 0x188
	f32 unk18C;   // 0x18C
	RwV3d unk190; // 0x190
	s32 unk19C;   // 0x19C
	f32 unk1A0;   // 0x1A0
};

extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C114;
extern "C" CCL_INFO enemyShieldCclInfo[];
extern "C" const f32 enemyShieldZero[1];
extern "C" const f32 enemyShieldRadius[1];
extern "C" const f32 enemyShieldBound[1];
extern "C" const f32 enemyShieldOne[1];

inline ENEMY_SHIELD::ENEMY_SHIELD(TObject* parent)
    : TObject(parent)
{
	unkF0    = 0;
	unk12C.x = unk12C.y = unk12C.z = enemyShieldZero[0];
	unkEA = unkEC = 0;
	unk180        = 8;
	Init(enemyShieldCclInfo, 1, 3);
	flag &= ~0x40;
	radObject  = enemyShieldRadius[0];
	bound_coef = enemyShieldBound[0];
	unk184     = 1;
	unk18C = unk188 = enemyShieldZero[0];
	unk190.x = unk190.y = unk190.z = enemyShieldZero[0];
	unk19C                         = 0;
	unk1A0                         = enemyShieldOne[0];
}

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
		if (pos != NULL) {
			shield->pos.x = pos->x;
			shield->pos.y = pos->y;
			shield->pos.z = pos->z;
		}
		if (normal != NULL) {
			shield->normal.x = normal->x;
			shield->normal.y = normal->y;
			shield->normal.z = normal->z;
		}
		if (ang != NULL) {
			shield->ang = *ang;
		}
		shield->scale = scale;
		if (enemyShieldZero[0] == scale) {
			shield->info->attr |= 0x10;
		}
		shield->kind = kind;
		switch (shield->kind) {
			case ENEMY_SHIELD_KIND_0:
				shield->hits         = 6;
				shield->info->damage = shield->info->damage & ~3;
				shield->info->damage = shield->info->damage & ~0xC;
				shield->vitality     = 6;
				shield->info->attr |= 0x800;
				break;
			case ENEMY_SHIELD_KIND_1:
				shield->hits         = 3;
				shield->info->damage = shield->info->damage & ~3;
				shield->info->damage = (shield->info->damage & ~0xC) | 4;
				shield->vitality     = 3;
				break;
			case ENEMY_SHIELD_KIND_2:
				shield->hits         = 9;
				shield->info->damage = (shield->info->damage & ~3) | 3;
				shield->info->damage = (shield->info->damage & ~0xC) | 8;
				shield->vitality     = 9;
				break;
		}
	}
	return shield;
}
