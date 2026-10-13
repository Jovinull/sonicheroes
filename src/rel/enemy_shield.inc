// ENEMY_SHIELD (the PS2 build's name): the enemies' shield object, with its
// constructor and Init. SetEnemyShield inlines both; rel/enemy_shield_ctor.cpp
// has the out-of-line copies (ENEMY_SHIELD_INLINE empty).

#ifndef ENEMY_SHIELD_INLINE
#define ENEMY_SHIELD_INLINE inline
#endif

enum ENEMY_SHIELD_KIND {
	ENEMY_SHIELD_KIND_0,
	ENEMY_SHIELD_KIND_1,
	ENEMY_SHIELD_KIND_2,
};

class ENEMY_SHIELD : public TObject, public C_COLLI, public OBJ_MoveOnGround
{
public:
	ENEMY_SHIELD(TObject* parent);
	void Init(ENEMY_SHIELD_KIND kind, const RwV3d* pos, f32 scale, const RwV3d* normal,
	    const sAngle* ang);
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

ENEMY_SHIELD_INLINE ENEMY_SHIELD::ENEMY_SHIELD(TObject* parent)
    : TObject(parent)
{
	unkF0    = 0;
	unk12C.x = unk12C.y = unk12C.z = enemyShieldZero[0];
	unkEA = unkEC = 0;
	unk180        = 8;
	C_COLLI::Init(enemyShieldCclInfo, 1, 3);
	flag &= ~0x40;
	radObject  = enemyShieldRadius[0];
	bound_coef = enemyShieldBound[0];
	unk184     = 1;
	unk18C = unk188 = enemyShieldZero[0];
	unk190.x = unk190.y = unk190.z = enemyShieldZero[0];
	unk19C                         = 0;
	unk1A0                         = enemyShieldOne[0];
}

ENEMY_SHIELD_INLINE void ENEMY_SHIELD::Init(
    ENEMY_SHIELD_KIND kind, const RwV3d* pos, f32 scale, const RwV3d* normal, const sAngle* ang)
{
	if (pos != NULL) {
		this->pos.x = pos->x;
		this->pos.y = pos->y;
		this->pos.z = pos->z;
	}
	if (normal != NULL) {
		this->normal.x = normal->x;
		this->normal.y = normal->y;
		this->normal.z = normal->z;
	}
	if (ang != NULL) {
		this->ang = *ang;
	}
	this->scale = scale;
	if (enemyShieldZero[0] == scale) {
		info->attr |= 0x10;
	}
	this->kind = kind;
	switch (this->kind) {
		case ENEMY_SHIELD_KIND_0:
			hits         = 6;
			info->damage = info->damage & ~3;
			info->damage = info->damage & ~0xC;
			vitality     = 6;
			info->attr |= 0x800;
			break;
		case ENEMY_SHIELD_KIND_1:
			hits         = 3;
			info->damage = info->damage & ~3;
			info->damage = (info->damage & ~0xC) | 4;
			vitality     = 3;
			break;
		case ENEMY_SHIELD_KIND_2:
			hits         = 9;
			info->damage = (info->damage & ~3) | 3;
			info->damage = (info->damage & ~0xC) | 8;
			vitality     = 9;
			break;
	}
}
