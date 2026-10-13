#include "game/miscs.h"
#include "types.h"

// stage11D's TObjEnemyFlyerIronBall (named by the PS2 build's symbols): the
// iron ball the flyer (rel/e_flyer_stage11.cpp) drops, which falls under
// gravity to its shadow and bursts.
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
struct sFlyerIronBall {
	/* 0x00 */ RwV3d pos;
	/* 0x0C */ RwV3d vel;
	/* 0x18 */ sAngle ang;
	/* 0x24 */ s32 life;
	/* 0x28 */ s32 light;
};

struct FlyerIronBall : FlyerWeaponHdr {
	/* 0xB0 */ sFlyerIronBall param;
	/* 0xDC */ s32 mode;
	/* 0xE0 */ void* clump;
	/* 0xE4 */ f32 fallSpeed;
	/* 0xE8 */ RwV3d shadow;
}; /* 0xF4 */

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
struct FlyerIronBall;
void fn_8_A82A8(FlyerIronBall*);
void fn_8_A8334(FlyerIronBall*);
void fn_8_A8384(FlyerIronBall*);
void fn_8_A8584(FlyerIronBall*);
void fn_8_A8590(FlyerIronBall*);
FlyerIronBall* fn_8_A8938(FlyerIronBall*, s16);
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
u32 lbl_8_data_16430[12] = { 0x00002521, 0x00000400, 0x00000000, 0x00000000, 0x00000000, 0x41000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
char lbl_8_data_16460[]  = "TObjEnemyFlyerIronBall";
M2C_UNK* lbl_8_data_16478  = (M2C_UNK*)&lbl_8_data_16460;
void* lbl_8_data_1647C[11] = {
	NULL,
	NULL,
	(void*)fn_8_A8938,
	(void*)fn_8_A8590,
	(void*)fn_8_A82A8,
	(void*)TDisp__7TObjectFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
};

/* The ball's model clump, found at load (Initialize) and dropped at
 * unload (Finalize). */
static struct {
	void* p;
	void* unk4;
} lbl_8_bss_19B8;

/* The vector the stage 11 units carry unreferenced at the head of their
 * .rodata (see e_capture_collision_stage11.cpp). */
#pragma force_active on
static const f32 lbl_8_rodata_1998[3] = { 0.0f, 1.5f, 0.0f };
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

/* TObjEnemyFlyerIronBall::Disp: drawn when its bounding sphere is in view. */
void fn_8_A82A8(FlyerIronBall* self)
{
	f32 sphere[4];

	if (self->clump != NULL) {
		sphere[0] = self->param.pos.x;
		sphere[1] = self->param.pos.y;
		sphere[2] = self->param.pos.z;
		sphere[3] = 20.0f;
		if (fn_8019CE34(*lbl_8042C9A4, sphere) != 0) {
			SetLightNum__7nRenderFUi(self->param.light);
			fn_8014FF2C((s32)self->clump);
		}
	}
}

/* TObjEnemyFlyerIronBall::ModeExit */
void fn_8_A8334(FlyerIronBall* self)
{
	SetEffectBomb__FP7TObjectP5RwV3dP6sAngle18ENUM_EFF_BOMB_TYPEi(
	    NULL, &self->param.pos, NULL, 1, -1);
	self->signal |= 1;
}

/* TObjEnemyFlyerIronBall::ModeExec: the ball falls under gravity until its
 * life runs out or it passes below its shadow, then explodes. */
void fn_8_A8384(FlyerIronBall* self)
{
	sAngle shadowAng;
	s32 frame;

	if (--self->param.life < 0) {
		self->mode = 2;
		return;
	}
	self->fallSpeed += -0.06f;
	self->param.pos.x += self->param.vel.x;
	self->param.pos.y += self->fallSpeed;
	self->param.pos.z += self->param.vel.z;
	if (-1000000.0f != self->shadow.y && self->shadow.y > self->param.pos.y) {
		self->mode = 2;
		return;
	}
	self->shadow.x = self->param.pos.x;
	self->shadow.y = 4.0f + GetShadowPos__FP5RwV3dP6sAnglei(&self->param.pos, &shadowAng, 1);
	self->shadow.z = self->param.pos.z;
	if (self->clump != NULL) {
		frame = ((s32*)self->clump)[1];
		fn_8019ED68(frame, &AxisZ, 0.0054931640625f * (f32)self->param.ang.z, 0);
		fn_8019ED68(frame, &AxisX, 0.0054931640625f * (f32)self->param.ang.x, 2);
		fn_8019ED68(frame, &AxisY, 0.0054931640625f * (f32)self->param.ang.y, 2);
		fn_8019EB94(frame, &self->param.pos, 2);
	}
}

/* TObjEnemyFlyerIronBall::ModeInit */
void fn_8_A8584(FlyerIronBall* self)
{
	self->mode = 1;
}

/* TObjEnemyFlyerIronBall::Exec */
void fn_8_A8590(FlyerIronBall* self)
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
			fn_8_A8584(self);
			break;
		case 1:
			fn_8_A8384(self);
			break;
		case 2:
			fn_8_A8334(self);
			break;
	}
	if (fn_80017800(self) != 0 && self->colliInfo != NULL) {
		self->colliPrePos = self->colliPos;
		self->colliPos    = self->param.pos;
		self->colliAng    = self->param.ang;
		Entry__7C_COLLIFv(self->colli);
	}
}

/* TObjEnemyFlyerIronBall::~TObjEnemyFlyerIronBall */
FlyerIronBall* fn_8_A8938(FlyerIronBall* self, s16 flags)
{
	if (self != NULL) {
		self->vtable = lbl_8_data_1647C;
		if (self->clump != NULL) {
			fn_80150958(self->clump);
			self->clump = NULL;
		}
		__dt__7C_COLLIFv(self->colli, 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, self);
		}
	}
	return self;
}

static inline FlyerIronBall* flyerIronBallCtor(
    FlyerIronBall* self, const sFlyerIronBall* data, TObject* parent)
{
	sAngle shadowAng;

	__ct__7TObjectFP7TObject(self, parent);
	__ct__7C_COLLIFv(self->colli);
	self->vtable      = lbl_8_data_1647C;
	self->param.pos.x = self->param.pos.y = self->param.pos.z = 0.0f;
	self->param.vel.x = self->param.vel.y = self->param.vel.z = 0.0f;
	self->param.ang.x = self->param.ang.y = self->param.ang.z = 0;
	self->param.life                                          = 300;
	self->param.light                                         = 8;
	self->className                                           = (char*)lbl_8_data_16478;
	self->dispTime                                            = sizeof(FlyerIronBall);
	self->clump                                               = NULL;
	self->mode                                                = 0;
	self->param                                               = *data;
	self->fallSpeed                                           = 0.0f;
	Init__7C_COLLIFP8CCL_INFOiUc(self->colli, lbl_8_data_16430, 1, 3);
	self->colliPos = self->param.pos;
	self->shadow.x = self->param.pos.x;
	self->shadow.y = 4.0f + GetShadowPos__FP5RwV3dP6sAnglei(&self->param.pos, &shadowAng, 1);
	self->shadow.z = self->param.pos.z;
	self->clump    = fn_80150588(lbl_8_bss_19B8.p);
	return self;
}

/* Create's new-expression constructs this same-sized stand-in, whose
 * destructor-bearing base gives the null-checked compiler temporary retail
 * keeps the constructed object in (see e_capture_collision_stage11.cpp). */
struct FlyerObjectStorage {
	~FlyerObjectStorage();
};

struct FlyerIronBallStorage : FlyerObjectStorage {
	u8 data[sizeof(FlyerIronBall)];

	FlyerIronBallStorage(const sFlyerIronBall* param)
	{
		flyerIronBallCtor((FlyerIronBall*)this, param, lbl_8042C10C);
	}
	static void* operator new(unsigned long size, s32 heap)
	{
		return Malloc__9THeapCtrlFUi(heap, size);
	}
};

/* TObjEnemyFlyerIronBall::TObjEnemyFlyerIronBall(const sFlyerIronBall*, TObject*) */
FlyerIronBall* fn_8_A89D4(FlyerIronBall* self, const sFlyerIronBall* data, TObject* parent)
{
	return flyerIronBallCtor(self, data, parent);
}

#pragma optimization_level 3
/* TObjEnemyFlyerIronBall::Create(const sFlyerIronBall*) */
FlyerIronBall* fn_8_A8B60(const sFlyerIronBall* data)
{
	return (FlyerIronBall*)new (lbl_8042C148) FlyerIronBallStorage(data);
}
#pragma optimization_level reset

/* TObjEnemyFlyerIronBall::Finalize */
void fn_8_A8D1C(void)
{
	lbl_8_bss_19B8.p = NULL;
}

/* TObjEnemyFlyerIronBall::Initialize */
void fn_8_A8D30(void)
{
	if (mpDataBase__14TEnemyDataBase == 0 && __nw__FUl(0x70) != 0) {
		__ct__14TEnemyDataBaseFv();
	}
	lbl_8_bss_19B8.p
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 5, 8);
}
}
