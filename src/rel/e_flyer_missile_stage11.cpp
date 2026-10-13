#include "game/miscs.h"
#include "types.h"

// stage11D's TObjEnemyFlyerMissile (named by the PS2 build's symbols): the
// missile the flyer (rel/e_flyer_stage11.cpp) fires, which drops, then homes
// on its target until it hits or its life runs out.
//
// The unit's literals are written in place, so the compiler pools them after
// the {0, 1.5, 0} vector in first-use order, which is retail's .rodata layout.

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))

struct TObject;

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

/* The flyer's weapons. PS2 symbols name the two classes
 * TObjEnemyFlyerIronBall and TObjEnemyFlyerMissile, each a TObject with a
 * C_COLLI at 0x28, built from a parameter block (sFlyerIronBall /
 * sFlyerMissile) by Create(const s*). Field names are descriptive guesses. */
struct FlyerWeaponHdr {
	/* 0x00 */ char* className;
	/* 0x04 */ u16 signal;
	/* 0x06 */ u8 pad06[0x12];
	/* 0x18 */ void* vtable;
	/* 0x1C */ u8 pad1C[2];
	/* 0x1E */ s16 dispTime;
	/* 0x20 */ u8 pad20[8];
	/* 0x28 */ u8 colli[8]; /* C_COLLI */
	/* 0x30 */ u16 colliFlag;
	/* 0x32 */ u8 pad32[6];
	/* 0x38 */ void* colliInfo;
	/* 0x3C */ u8 pad3C[0x4C];
	/* 0x88 */ RwV3d colliPos;
	/* 0x94 */ sAngle colliAng;
	/* 0xA0 */ s32 characterId;
	/* 0xA4 */ RwV3d colliPrePos;
};

/* The launch parameters, kept whole in the weapon, which copies the caller's
 * block over its defaults in one assignment. */
struct sFlyerMissile {
	/* 0x00 */ RwV3d pos;
	/* 0x0C */ RwV3d vel;
	/* 0x18 */ RwV3d target;
	/* 0x24 */ f32 maxSpeed;
	/* 0x28 */ sAngle ang;
	/* 0x34 */ s32 homing;
	/* 0x38 */ s32 life;
	/* 0x3C */ s32 light;
};

struct FlyerMissile : FlyerWeaponHdr {
	/* 0x0B0 */ sFlyerMissile param;
	/* 0x0F0 */ s32 mode;
	/* 0x0F4 */ s32 smode;
	/* 0x0F8 */ f32 fallSpeed;
	/* 0x0FC */ f32 speed;
	/* 0x100 */ s32 fallTime;
}; /* 0x104 */

/* Dispatch view of the object's vtable. The handler at vtable offset 0x10 is
 * reached through genuine virtual dispatch in retail: the target loads the
 * vtable through the already-materialised `this` in r3 and keeps the slot in
 * r12, which manual vtable indexing does not reproduce. Two implicit
 * destructor slots plus the two placeholders below put Release at slot 4. */
class TObjectDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void Release(s32, s32);
};

extern "C" {

void* __ct__7TObjectFP7TObject(void*, void*);                   /* extern */
M2C_UNK __dl__FPv(void*);                                       /* extern */
void* __dt__7TObjectFv(void*, s32);                             /* extern */
f64 asin(f32);                                                  /* extern */
double atan2(double, double);                                   /* extern */
M2C_UNK __dt__7C_COLLIFv(void*, M2C_UNK);                       /* extern */
s32 fn_80017800(void*);                                         /* extern */
void Free__9THeapCtrlFPv(s32, void*);                           /* extern */
void* Malloc__9THeapCtrlFUi(s32, u32);                          /* extern */
void* fn_800211A8(void*);                                       /* extern */
void fn_80021824(void*);                                        /* extern */
M2C_UNK Entry__7C_COLLIFv(void*);                               /* extern */
M2C_UNK ClearInfo__7C_COLLIFv(void*);                           /* extern */
void Init__7C_COLLIFP8CCL_INFOiUc(void*, void*, s32, u8);       /* extern */
void __ct__7C_COLLIFv(void*);                                   /* extern */
void* __nw__FUl(u32);                                           /* extern */
u32 objPointerReadFromClumpAnim__FPc(s32*);                     /* extern */
M2C_UNK fn_800A31B8(void*, s32);                                /* extern */
s32 fn_800A3ED4(void*);                                         /* extern */
M2C_UNK fn_800B4A38(u32, M2C_UNK, void*, void*, s32, s32, s32); /* extern */
void SetEffectBomb__FP7TObjectP5RwV3dP6sAngle18ENUM_EFF_BOMB_TYPEi(
    void*, RwV3d*, sAngle*, s32, s32);                                             /* extern */
M2C_UNK AdjustPoint__FP5RwV3dPC5RwV3df(void*, s32, void*, s32);                    /* extern */
f32 Distance2P2P__FPC5RwV3dPC5RwV3d(s32*, s32*);                                   /* extern */
s32 AdjustAngle__Fiii(s32, s32, s32);                                              /* extern */
f32 fn_800D7B00(s32);                                                              /* extern */
f32 GetShadowPos__FP5RwV3dP6sAnglei(RwV3d*, sAngle*, s32);                         /* extern */
M2C_UNK fn_800E1208(s32, s32, s32);                                                /* extern */
void* SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK __ct__14TEnemyDataBaseFv();                                                /* extern */
s32 IsExistSummonEnemy__19nEnemyCommunicationFUc(s32);                             /* extern */
s32 GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(void*, f32*, f32);              /* extern */
M2C_UNK Change__13TEnemyIconManF10eEnemyIcon(void*, s32);                          /* extern */
s32 Off__13TEnemyIconManFv(void*);                                                 /* extern */
M2C_UNK On__13TEnemyIconManFff(u32, f32*, f32, f32);                               /* extern */
M2C_UNK SetLightNum__7nRenderFUi(s32);                                             /* extern */
s32 DecreaseTimer__7nSystemFRi(void*);                                             /* extern */
M2C_UNK fn_8014FF2C(s32);                                                          /* extern */
void* fn_80150588(void*);                                                          /* extern */
M2C_UNK fn_80150958(void*);                                                        /* extern */
void fn_801990E0(RwV3d*, RwV3d*);                           /* RwV3dNormalize */
f32 fn_801991B4(RwV3d*);                                    /* RwV3dLength */
s32 fn_8019CE34(s32, f32*);                                 /* extern */
void fn_8019EB94(s32, RwV3d*, s32); /* RwFrameTranslate */  /* extern */
M2C_UNK fn_8019EC30(s32, void*, s32);                       /* extern */
void fn_8019ED68(s32, void*, f32, s32); /* RwFrameRotate */ /* extern */
s32 rand();                                                 /* extern */
M2C_UNK fn_8_90B10(s32);                                    /* extern */
M2C_UNK fn_8_A353C(void*);                                  /* extern */
s32 fn_8_A35BC(M2C_UNK);                                    /* extern */
struct FlyerMissile;
s32 fn_8_A8D98(FlyerMissile*);
void fn_8_A8E0C(FlyerMissile*);
void fn_8_A8F7C(FlyerMissile*);
void fn_8_A8FCC(FlyerMissile*);
void fn_8_A90C8(FlyerMissile*);
void fn_8_A92E0(FlyerMissile*);
void fn_8_A945C(FlyerMissile*);
void fn_8_A9848(FlyerMissile*);
void fn_8_A9874(FlyerMissile*);
FlyerMissile* fn_8_A9A6C(FlyerMissile*, s16);
extern "C" {
void TDisp__7TObjectFv(void);
void PDisp__7TObjectFv(void);
void ImmAftSetRaster__7TObjectFv(void);
void Debug__7TObjectFv(void);
void Error__7TObjectFPc(char*);
void Render__7TObjectFv(void);
}
extern M2C_UNK AxisX;
extern M2C_UNK AxisY;
extern M2C_UNK AxisZ;
extern M2C_UNK lbl_8029C310;
extern M2C_UNK lbl_802AD090;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern M2C_UNK lbl_8042C1A4;
extern u32 lbl_8042C388;
extern u32 mpDataBase__14TEnemyDataBase;
extern s32* lbl_8042C9A4;
extern u32 lbl_8_bss_1A48;
u32 lbl_8_data_164A8[12] = { 0x00022521, 0x00000600, 0x00000000, 0xC1200000, 0x00000000, 0x40800000,
	0x41A00000, 0x00000000, 0x00000000, 0x00000000, 0x00004000, 0x00004000 };
char lbl_8_data_164D8[]  = "TObjEnemyFlyerMissile";
M2C_UNK* lbl_8_data_164F0  = (M2C_UNK*)&lbl_8_data_164D8;
void* lbl_8_data_164F4[11] = {
	NULL,
	NULL,
	(void*)fn_8_A9A6C,
	(void*)fn_8_A9874,
	(void*)fn_8_A8E0C,
	(void*)TDisp__7TObjectFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
};

/* The missile's model clump, found at load (Initialize) and dropped at
 * unload (Finalize). */
static struct {
	void* p;
	void* unk4;
} lbl_8_bss_19C0;

/* The vector the stage 11 units carry unreferenced at the head of their
 * .rodata (see e_capture_collision_stage11.cpp). */
#pragma force_active on
static const f32 lbl_8_rodata_19C8[3] = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

/* The game-mode test both weapons' Exec start with: the 2P modes (1 and 2)
 * and mode 3 end the weapon at once. Retail compiles it with C++ bool. */
#pragma bool on
static inline bool flyerIsVersusMode(s32 mode)
{
	return mode == 1 || mode == 2;
}

static inline bool flyerIsWeaponOffMode()
{
	s32 mode = M2C_FIELD(&lbl_8029C310, s32*, 0x18);
	return flyerIsVersusMode(mode) || mode == 3;
}
#pragma bool reset

/* False while the game is paused or between scenes (the three flags of the
 * object at lbl_8042C180). */
static inline BOOL flyerIsPlaying()
{
	if (M2C_FIELD(lbl_8042C180, s8*, 0x1F) != 0) {
		return FALSE;
	} else if (M2C_FIELD(lbl_8042C180, s8*, 0x20) != 0) {
		return FALSE;
	} else if (M2C_FIELD(lbl_8042C180, s8*, 0x21) != 0) {
		return FALSE;
	}
	return TRUE;
}

static inline BOOL flyerWeaponKillMyself()
{
	return flyerIsWeaponOffMode();
}

/* Create's new-expression constructs this same-sized stand-in, whose
 * destructor-bearing base gives the null-checked compiler temporary retail
 * keeps the constructed object in (see e_capture_collision_stage11.cpp). */
struct FlyerObjectStorage {
	~FlyerObjectStorage();
};

/* TObjEnemyFlyerMissile::CheckCollision: hit when its collision touched
 * something this frame. */
s32 fn_8_A8D98(FlyerMissile* self)
{
	void* hit;
	u32 other;

	if (self->colliFlag & 1) {
		fn_80021824(&lbl_8042C1A4);
		hit = fn_800211A8(self->colli);
		if (hit != NULL) {
			other = M2C_FIELD(hit, u32*, 4);
		} else {
			other = 0;
		}
		if (other != 0) {
			return 1;
		}
	}
	return 0;
}

/* TObjEnemyFlyerMissile::Disp */
void fn_8_A8E0C(FlyerMissile* self)
{
	f32 sphere[4];
	s32 frame;

	if (lbl_8_bss_19C0.p != NULL) {
		sphere[0] = self->param.pos.x;
		sphere[1] = self->param.pos.y;
		sphere[2] = self->param.pos.z;
		sphere[3] = 20.0f;
		if (fn_8019CE34(*lbl_8042C9A4, sphere) != 0) {
			frame = ((s32*)lbl_8_bss_19C0.p)[1];
			fn_8019ED68(frame, &AxisX, -(0.0054931640625f * (f32)self->param.ang.x), 0);
			fn_8019ED68(frame, &AxisY, 180.0f + 0.0054931640625f * (f32)self->param.ang.y, 2);
			fn_8019EB94(frame, &self->param.pos, 2);
			SetLightNum__7nRenderFUi(self->param.light);
			fn_8014FF2C((s32)lbl_8_bss_19C0.p);
		}
	}
}

/* TObjEnemyFlyerMissile::ModeExit */
void fn_8_A8F7C(FlyerMissile* self)
{
	SetEffectBomb__FP7TObjectP5RwV3dP6sAngle18ENUM_EFF_BOMB_TYPEi(
	    NULL, &self->param.pos, NULL, 1, -1);
	self->signal |= 1;
}

/* The nose follows the velocity: pitch from its height, yaw from its run. */
static inline void flyerMissileFaceVelocity(FlyerMissile* self)
{
	f32 yaw;
	f32 pitch;
	f32 len = fn_801991B4(&self->param.vel);
	if (len > 0.0f) {
		pitch = (f32)asin(-self->param.vel.y / len);
		yaw   = (f32)atan2(self->param.vel.x, self->param.vel.z);
		self->param.ang.x
		    = AdjustAngle__Fiii(self->param.ang.x, (s32)(10430.380859375f * pitch), 0x100);
		self->param.ang.y
		    = AdjustAngle__Fiii(self->param.ang.y, (s32)(10430.380859375f * yaw), 0x100);
		self->param.ang.z = 0;
		return;
	}
	self->param.ang.x = 0;
	self->param.ang.y = 0;
	self->param.ang.z = 0;
}

/* TObjEnemyFlyerMissile::CalcMissileAngle */
void fn_8_A8FCC(FlyerMissile* self)
{
	flyerMissileFaceVelocity(self);
}

/* TObjEnemyFlyerMissile::SModeFire: home on the target, speeding up to the
 * top speed; passing it ends the missile's life. */
void fn_8_A90C8(FlyerMissile* self)
{
	if (self->param.homing != 0) {
		RwV3d prev        = self->param.pos;
		self->param.vel.x = self->param.target.x - self->param.pos.x;
		self->param.vel.y = self->param.target.y - self->param.pos.y;
		self->param.vel.z = self->param.target.z - self->param.pos.z;
		fn_801990E0(&self->param.vel, &self->param.vel);
		self->speed += 0.2f;
		if (self->speed > self->param.maxSpeed) {
			self->speed = self->param.maxSpeed;
		}
		self->param.vel.x *= self->speed;
		self->param.vel.y *= self->speed;
		self->param.vel.z *= self->speed;
		self->param.pos.x += self->param.vel.x;
		self->param.pos.y += self->param.vel.y;
		self->param.pos.z += self->param.vel.z;
		if (DistanceP2SegL(&self->param.target, &prev, &self->param.pos, NULL) < 2.0f) {
			self->param.life = 0;
		}
	}
	fn_8_A8FCC(self);
}

static inline void flyerV3dAdd(RwV3d* dst, const RwV3d* src)
{
	dst->x += src->x;
	dst->y += src->y;
	dst->z += src->z;
}

/* TObjEnemyFlyerMissile::SModeFall: the launch drop before the motor fires. */
void fn_8_A92E0(FlyerMissile* self)
{
	self->fallSpeed += -0.06f;
	RwV3d move = self->param.vel;
	move.y     = self->fallSpeed;
	flyerV3dAdd(&self->param.pos, &move);
	fn_8_A8FCC(self);
	if (--self->fallTime < 0) {
		self->smode = 1;
	}
}

/* TObjEnemyFlyerMissile::ModeExec */
void fn_8_A945C(FlyerMissile* self)
{
	if (--self->param.life < 0) {
		self->mode = 2;
		return;
	}
	if (fn_8_A8D98(self)) {
		self->mode = 2;
		return;
	}
	switch (self->smode) {
		case 0:
			fn_8_A92E0(self);
			break;
		case 1:
			fn_8_A90C8(self);
			break;
	}
}

/* TObjEnemyFlyerMissile::ModeInit */
void fn_8_A9848(FlyerMissile* self)
{
	self->mode      = 1;
	self->smode     = 1;
	self->fallSpeed = 0.0f;
	self->speed     = 0.0f;
	self->fallTime  = 30;
}

/* TObjEnemyFlyerMissile::Exec */
void fn_8_A9874(FlyerMissile* self)
{
	if (flyerWeaponKillMyself()) {
		self->signal |= 1;
		return;
	}
	if (!flyerIsPlaying()) {
		ClearInfo__7C_COLLIFv(self->colli);
		return;
	}
	switch (self->mode) {
		case 0:
			fn_8_A9848(self);
			break;
		case 1:
			fn_8_A945C(self);
			break;
		case 2:
			fn_8_A8F7C(self);
			break;
	}
	if (fn_80017800(self) != 0 && self->colliInfo != NULL) {
		self->colliPrePos = self->colliPos;
		self->colliPos    = self->param.pos;
		self->colliAng    = self->param.ang;
		Entry__7C_COLLIFv(self->colli);
	}
}

/* TObjEnemyFlyerMissile::~TObjEnemyFlyerMissile */
FlyerMissile* fn_8_A9A6C(FlyerMissile* self, s16 flags)
{
	if (self != NULL) {
		self->vtable = lbl_8_data_164F4;
		__dt__7C_COLLIFv(self->colli, 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, self);
		}
	}
	return self;
}

static inline FlyerMissile* flyerMissileCtor(
    FlyerMissile* self, const sFlyerMissile* data, TObject* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	__ct__7C_COLLIFv(self->colli);
	self->vtable      = lbl_8_data_164F4;
	self->param.pos.x = self->param.pos.y = self->param.pos.z = 0.0f;
	self->param.vel.x = self->param.vel.y = self->param.vel.z = 0.0f;
	self->param.ang.x = self->param.ang.y = self->param.ang.z = 0;
	self->param.target.x = self->param.target.y = self->param.target.z = 0.0f;
	self->param.maxSpeed                                               = 0.0f;
	self->param.homing                                                 = 1;
	self->param.life                                                   = 300;
	self->param.light                                                  = 8;
	self->className                                                    = (char*)lbl_8_data_164F0;
	self->dispTime                                                     = sizeof(FlyerMissile);
	self->mode                                                         = 0;
	self->param                                                        = *data;
	Init__7C_COLLIFP8CCL_INFOiUc(self->colli, lbl_8_data_164A8, 1, 4);
	self->colliPos = self->param.pos;
	return self;
}

struct FlyerMissileStorage : FlyerObjectStorage {
	u8 data[sizeof(FlyerMissile)];

	FlyerMissileStorage(const sFlyerMissile* param)
	{
		flyerMissileCtor((FlyerMissile*)this, param, lbl_8042C10C);
	}
	static void* operator new(unsigned long size, s32 heap)
	{
		return Malloc__9THeapCtrlFUi(heap, size);
	}
};

/* TObjEnemyFlyerMissile::TObjEnemyFlyerMissile(const sFlyerMissile*, TObject*) */
FlyerMissile* fn_8_A9AF0(FlyerMissile* self, const sFlyerMissile* data, TObject* parent)
{
	return flyerMissileCtor(self, data, parent);
}

#pragma optimization_level 3
/* TObjEnemyFlyerMissile::Create(const sFlyerMissile*) */
FlyerMissile* fn_8_A9C6C(const sFlyerMissile* data)
{
	return (FlyerMissile*)new (lbl_8042C148) FlyerMissileStorage(data);
}
#pragma optimization_level reset

/* TObjEnemyFlyerMissile::Finalize */
void fn_8_A9E18(void)
{
	lbl_8_bss_19C0.p = NULL;
}

/* TObjEnemyFlyerMissile::Initialize */
void fn_8_A9E2C(void)
{
	if (mpDataBase__14TEnemyDataBase == 0 && __nw__FUl(0x70) != 0) {
		__ct__14TEnemyDataBaseFv();
	}
	lbl_8_bss_19C0.p
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 5, 0xA);
}
}
