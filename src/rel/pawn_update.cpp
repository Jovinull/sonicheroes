#include "game/effect/eff_bomb.h"

// TObjEnemyPawn::Update (the PS2 build's name): the pawn's frame. It follows
// its collision unless told not to once, lets its shield take hits (losing it
// clears the shielded state), runs the enemy's per-frame virtual, its strategy
// and its current mode, plays the footsteps, places the model, eases the
// shoulder back except while aiming, updates the weapon and, when it may be
// hit and is shown, places its second collision and enters the collision.

struct RpHAnimHierarchy;
struct ENEMY_SHIELD {
	u8 unk00[0x4];
	u16 flags; // 0x04
};

class ENEMYMTNMAN
{
public:
	RpHAnimHierarchy* GetActiveHAHPointer();
};

class TObjEnemyPawn;

class TEnemyPawnStrategy
{
public:
	virtual void Virtual08();
	virtual void Exec(TObjEnemyPawn* pawn); // 0x0C
};

struct RwMatrixTag {
	RwV3d right; // 0x00
	u32 flags;   // 0x0C
	RwV3d up;    // 0x10
	u32 pad1;    // 0x1C
	RwV3d at;    // 0x20
	u32 pad2;    // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3;    // 0x3C
};

class TObjEnemyPawn : public TObject, public C_COLLI
{
public:
	virtual void Virtual2C();
	virtual void Virtual30();
	virtual void Virtual34();
	virtual void Virtual38();
	virtual void Virtual3C();
	virtual void Virtual40();
	virtual void Virtual44();
	virtual void Virtual48();
	virtual void Virtual4C();
	virtual void CtrlMode(int mode, int sub); // 0x50

	u8 unk0B0[0x8];
	ENEMYMTNMAN motion; // 0x0B8
	u8 unk0B9[0x87];
	RwV3d position; // 0x140
	sAngle angle;   // 0x14C
	u8 unk158[0x30];
	u32 state; // 0x188
	u8 unk18C[0x10];
	s32 mode; // 0x19C
	u8 unk1A0[0x4];
	f32 hp; // 0x1A4
	u8 unk1A8[0x98];
	TEnemyPawnStrategy* strategy; // 0x240
	u8 unk244[0xB];
	s8 shielded; // 0x24F
	u8 unk250[0x18];
	ENEMY_SHIELD* shield; // 0x268
	u8 unk26C[0x8];
	s32 bone; // 0x274
	u8 unk278[0x74];
	s32 shown;  // 0x2EC
	s32 noSync; // 0x2F0
	u8 unk2F4[0x2C];
	s32 shoulderPitch; // 0x320
	u8 unk324[0x54];
	s32 active; // 0x378
	s32 moving; // 0x37C
};

extern "C" s8* lbl_8042C180;
extern "C" const RwV3d AxisX;
extern "C" const f32 pawnZero[1];
extern "C" const f32 pawnOne[1];
extern "C" const f32 pawnColliTilt[1];
extern "C" const f32 pawnColliReach[1];

int AdjustAngle(int value, int target, int step);
void GetAngleXZ(f32 x, f32 y, f32 z, int* angX, int* angZ);
int EnemyShieldCheckDamage(ENEMY_SHIELD* shield, C_COLLI* colli);
extern "C" void fn_800A5B34(TObjEnemyPawn* pawn);
extern "C" void fn_800A3D48(TObjEnemyPawn* pawn);
extern "C" int fn_80017800(TObjEnemyPawn* pawn);
extern "C" RwMatrixTag* fn_8013F47C(RpHAnimHierarchy* hierarchy);
extern "C" void fn_80195A74(RwMatrixTag* matrix, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8019947C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" void PlaySEForFoot__13TObjEnemyPawnFv(TObjEnemyPawn* pawn);
extern "C" void SetPosition__13TObjEnemyPawnFv(TObjEnemyPawn* pawn);
extern "C" void UpdateWeapon__13TObjEnemyPawnFv(TObjEnemyPawn* pawn);

static inline int pawnActive()
{
	if (lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	if (lbl_8042C180[0x20] != 0) {
		return 0;
	}
	if (lbl_8042C180[0x21] != 0) {
		return 0;
	}
	return 1;
}

static inline int pawnMoving()
{
	if (lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	return 1;
}

// SetCollisionParameter as Update inlines it (rel/pawn_set_collision_parameter.cpp
// has the out-of-line copy): MWCC gives an inlined copy's floats their
// registers in the opposite order, so this copy declares them reversed.
static inline void pawnSetCollisionParameter(TObjEnemyPawn* pawn)
{
	if (pawn->info != NULL && pawn->nbInfo >= 2) {
		int angX;
		int angZ;
		RwV3d up;
		RwMatrixTag tilt;
		f32 dz;
		f32 dy;
		f32 dx;
		f32 reach;
		f32 z;
		f32 y;
		f32 x;

		if (pawn->bone != -1) {
			RwMatrixTag* bones = fn_8013F47C(pawn->motion.GetActiveHAHPointer());
			int i              = pawn->bone + 1;
			RwV3d* at          = (RwV3d*)((u8*)bones + i * 0x40 + 0x30);

			x    = at->x;
			y    = at->y;
			z    = at->z;
			up.x = up.z = pawnZero[0];
			up.y        = pawnOne[0];
			tilt        = bones[i];
			fn_80195A74(&tilt, &AxisX, pawnColliTilt[0], 1);
			fn_8019947C(&up, &up, 1, &tilt);
		} else {
			x    = pawn->position.x;
			y    = pawn->position.y;
			z    = pawn->position.z;
			up.x = up.z = pawnZero[0];
			up.y        = pawnOne[0];
		}
		GetAngleXZ(up.x, up.y, up.z, &angX, &angZ);
		reach                  = pawnColliReach[0];
		dy                     = reach * up.y;
		dz                     = reach * up.z;
		dx                     = reach * up.x;
		pawn->info[1].center.x = x + dx;
		pawn->info[1].center.y = y + dy;
		pawn->info[1].center.z = z + dz;
		pawn->info[1].angx     = angX;
		pawn->info[1].angz     = angZ;
	}
}

extern "C" void Update__13TObjEnemyPawnFv(TObjEnemyPawn* pawn)
{
	pawn->active = pawnActive();
	pawn->moving = pawnMoving();
	if (pawn->info != NULL && pawn->noSync == 0) {
		pawn->position = pawn->pos;
	}
	pawn->noSync = 0;
	fn_800A5B34(pawn);
	if (pawn->shield != NULL && pawn->shielded != 0) {
		if (EnemyShieldCheckDamage(pawn->shield, pawn)) {
			pawn->shield->flags |= 1;
			pawn->shield   = NULL;
			pawn->vitality = pawn->hp;
			pawn->shielded = 0;
			pawn->state &= ~0x100;
			pawn->info->attr &= ~0x800;
			pawn->info->kind = 0;
		}
	}
	pawn->Virtual38();
	if (pawn->strategy != NULL) {
		pawn->strategy->Exec(pawn);
	}
	pawn->CtrlMode(pawn->mode, 1);
	if (pawn->moving != 0) {
		PlaySEForFoot__13TObjEnemyPawnFv(pawn);
	}
	SetPosition__13TObjEnemyPawnFv(pawn);
	fn_800A3D48(pawn);
	switch (pawn->mode) {
		case 0x16:
		case 0x18:
		case 0x19:
			break;
		case 0x17:
		default:
			pawn->shoulderPitch = AdjustAngle(pawn->shoulderPitch, 0, 0x100);
			break;
	}
	UpdateWeapon__13TObjEnemyPawnFv(pawn);
	if (fn_80017800(pawn) && pawn->info != NULL && pawn->shown != 0) {
		pawnSetCollisionParameter(pawn);
		pawn->pre_pos = pawn->pos;
		pawn->pos     = pawn->position;
		pawn->ang     = pawn->angle;
		pawn->Entry();
	}
}
