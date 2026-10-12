#include "types.h"

// stage11D's TEnemyFlyer_Strategy (named by the PS2 build's symbols; the
// functions keep their address names): the strategy the flyer
// (rel/e_flyer_stage11.cpp) runs, its StrategyMode_* handlers, the mode
// transition test (A2AF0), ExecStrategyMode with the unit's one switch table,
// and the strategy's ctor/dtors with its two vtables.
//
// The unit's literals are written in place, so the compiler pools them after
// the named constants in first-use order, which is retail's .rodata layout.

typedef s32 M2C_UNK;
typedef struct HAnimClass HAnimClass;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
/* A field of the given type at a byte offset (layouts not yet given names). */
#define FLD(base, type, offset) (*(type*)((u8*)(base) + (offset)))
#define M2C_ERROR(...)

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

struct RwMatrix {
	RwV3d right;
	u32 flags;
	RwV3d up;
	u32 pad1;
	RwV3d at;
	u32 pad2;
	RwV3d pos;
	u32 pad3;
};

/* The placement's parameter block (setBuffer at SETDATA_PARAM + 0x2C), one
 * field per character of flyerObjectFieldTypes ("ccccfifxi"). */
struct FlyerParam {
	/* 0x00 */ s8 kind;
	/* 0x01 */ s8 pathNum;
	/* 0x02 */ s8 pathType;
	/* 0x03 */ u8 pad03;
	/* 0x04 */ f32 moveSpeed;
	/* 0x08 */ s32 attackInterval;
	/* 0x0C */ f32 weaponSpeed;
	/* 0x10 */ s32 weaponAngleX;
	/* 0x14 */ s32 unk14;
};

template <typename T> static inline const T& flyerClamp(const T& value, const T& low, const T& high)
{
	return value < low ? low : (value > high ? high : value);
}

extern "C" const f32 lbl_8_rodata_1900[1];

/* An enemy command (sEnemyCommand::Send broadcasts it to the enemies whose
 * communication id matches). Field names are descriptive guesses. */
struct sEnemyCommandHeader {
	u8 kind; /* 0x00 */
	u8 team; /* 0x01 */

	sEnemyCommandHeader()
	{
		kind = 0;
		team = 0;
	}
};

struct sEnemyCommand : sEnemyCommandHeader {
	s32 command;     /* 0x04 */
	RwV3d pos;       /* 0x08 */
	sAngle ang;      /* 0x14 */
	s32 id;          /* 0x20 */
	RwMatrix matrix; /* 0x24 */
	s32 sender;      /* 0x64 */

	sEnemyCommand()
	{
		kind    = 6;
		command = 0;
		pos.x = pos.y = pos.z = lbl_8_rodata_1900[0];
		ang.x = ang.y = ang.z = 0;
		id                    = 0;
		sender                = 0;
	}
};

/* The flyer's weapons' launch parameters (rel/e_flyer_path_stage11.cpp). */
struct sFlyerIronBall {
	RwV3d pos;  /* 0x00 */
	RwV3d vel;  /* 0x0C */
	sAngle ang; /* 0x18 */
	s32 life;   /* 0x24 */
	s32 light;  /* 0x28 */

	sFlyerIronBall()
	{
		pos.x = pos.y = pos.z = lbl_8_rodata_1900[0];
		vel.x = vel.y = vel.z = lbl_8_rodata_1900[0];
		ang.x = ang.y = ang.z = 0;
		life                  = 300;
		light                 = 8;
	}
};

struct sFlyerMissile {
	RwV3d pos;    /* 0x00 */
	RwV3d vel;    /* 0x0C */
	RwV3d target; /* 0x18 */
	f32 maxSpeed; /* 0x24 */
	sAngle ang;   /* 0x28 */
	s32 homing;   /* 0x34 */
	s32 life;     /* 0x38 */
	s32 light;    /* 0x3C */

	sFlyerMissile()
	{
		pos.x = pos.y = pos.z = lbl_8_rodata_1900[0];
		vel.x = vel.y = vel.z = lbl_8_rodata_1900[0];
		ang.x = ang.y = ang.z = 0;
		target.x = target.y = target.z = lbl_8_rodata_1900[0];
		maxSpeed                       = lbl_8_rodata_1900[0];
		homing                         = 1;
		life                           = 300;
		light                          = 8;
	}
};

struct FlyerAnimRecord {
	u32 unk0;
	u32 unk4;
	u32 unk8;
	u32 unkC;
	u32 unk10;
	u32 unk14;
	u32 unk18;
	const char* name;
	u32 unk20;
}; /* size = 0x24 */

/* Dispatch view of the object's vtable. The handler at vtable offset 0x10 is
 * reached through genuine virtual dispatch in retail: the target loads the
 * vtable through the already-materialised `this` in r3 and keeps the slot in
 * r12, which manual vtable indexing does not reproduce. Two implicit
 * destructor slots plus the two placeholders below put Release at slot 4. */
class TSubDispatch
{
public:
	virtual void vslot2(M2C_UNK);
	virtual void vslot3(void*);
};

class TObjectDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void Release(s32, s32);
};

/* The renderer class keeps its vtable pointer at object offset 0x18, which is
 * what a polymorphic class derived from a 0x18-byte non-polymorphic base
 * looks like: the base's data is laid out first and `this` is not adjusted,
 * exactly as retail's `lwz r12, 0x18(r3)` reads it. Slot numbers are the
 * retail vtable offsets divided by four, and the two implicit deleting
 * destructor slots occupy 0 and 1, so a method at slot k needs k - 2
 * placeholders ahead of it. */
class TRendererBase
{
public:
	u8 pad0[0x18];
};

class TRenderer : public TRendererBase
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual void vslot7();
	virtual void vslot8();
	virtual void vslot9();
	virtual void vslot10();
	virtual void vslot11();
	virtual void vslot12();
	virtual void vslot13();
	virtual void Slot38();
	virtual void Slot3C();
	virtual void Slot40();
	virtual void vslot17();
	virtual void vslot18();
	virtual void vslot19();
	virtual void Slot50(s32, s32);
	virtual void vslot21();
	virtual void vslot22();
	virtual void vslot23();
	virtual void vslot24();
	virtual void vslot25();
	virtual void vslot26();
	virtual void vslot27();
	virtual void vslot28();
	virtual void vslot29();
	virtual void vslot30();
	virtual void Slot7C();
	virtual void vslot32();
	virtual void vslot33();
	virtual void Slot88(void*);
	virtual void vslot35();
	virtual s32 Slot90();
};

extern "C" {

void* __ct__10HAnimClassFv(void* self);                  /* extern */
M2C_UNK __dl__FPv(void* arg0);                           /* extern */
void* __dt__10HAnimClassFv(void* self, s16 destroyFlag); /* extern */
f64 asin(f32);                                           /* extern */
f64 atan2(f64, f64);
s32 fn_80017800(M2C_UNK*);                                                              /* extern */
M2C_UNK Free__9THeapCtrlFPv(s32, void*);                                                /* extern */
M2C_UNK* Malloc__9THeapCtrlFUi(s32, M2C_UNK);                                           /* extern */
u32 fn_800194C4(M2C_UNK*);                                                              /* extern */
M2C_UNK UnitMatrix__FP11RwMatrixTag(void*);                                             /* extern */
M2C_UNK Entry__7C_COLLIFv(void*);                                                       /* extern */
M2C_UNK Init__7C_COLLIFP8CCL_INFOiUc(void*, M2C_UNK*, M2C_UNK, M2C_UNK);                /* extern */
void* __nw__FUl(u32);                                                                   /* extern */
s32 OnEdit__10TObjSetObjFv(void*);                                                      /* extern */
M2C_UNK SetEnd__10TObjSetObjFv(void*);                                                  /* extern */
M2C_UNK objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(void*, s32); /* extern */
s32 objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(void*, M2C_UNK);      /* extern */
void* objRwFrameGetFrame__FP7RwFramei(void*, s32);                                      /* extern */
M2C_UNK objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(
    u32, M2C_UNK);                                                   /* extern */
M2C_UNK fn_8006298C(M2C_UNK, RwV3d*, sAngle*);                       /* extern */
s32 fn_800A2D50();                                                   /* extern */
M2C_UNK fn_800A31B8(void*, s32);                                     /* extern */
M2C_UNK fn_800A3D48(M2C_UNK*);                                       /* extern */
M2C_UNK fn_800A5B34(M2C_UNK*);                                       /* extern */
s32 CheckCameraFrustumTest__9TObjEnemyFPC5RwV3df(void*, void*, f32); /* extern */
M2C_UNK fn_800A7088(void*, M2C_UNK);                                 /* extern */
void fn_800A714C(void*, void*); /* TObjEnemy::TObjEnemy(TObject*) */ /* extern */
M2C_UNK fn_800B4A38(u32, M2C_UNK, void*, void*, s32, s32, s32);      /* extern */
M2C_UNK fn_800B719C(void*, void*, RwV3d*, f32);                      /* extern */
M2C_UNK fn_800B7820();                                               /* extern */
M2C_UNK fn_800B7864(M2C_UNK);                                        /* extern */
s32 DiffAngle__Fii(s32, s32);                                        /* extern */
f32 fn_800D7AE4(s32);                                                /* extern */
f32 fn_800D7B00(s32);                                                /* extern */
f32 GetShadowPos__FP5RwV3dP6sAnglei(RwV3d*, sAngle*, s32);           /* extern */
void* __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID(void*, void*, s32);   /* extern */
M2C_UNK ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*); /* extern */
M2C_UNK LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*);                                                             /* extern */
M2C_UNK UpdateMotion__11ENEMYMTNMANFv(void*);                                       /* extern */
u32 SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK); /* extern */
u32 SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK Delete__14TEnemyDataBaseF14eEnemyDataBase(u32, M2C_UNK);                    /* extern */
M2C_UNK Add__14TEnemyDataBaseF14eEnemyDataBasePc(u32, M2C_UNK, const void*);        /* extern */
M2C_UNK __ct__14TEnemyDataBaseFv();                                                 /* extern */
s32 IsAnnihilated__19nEnemyCommunicationFUc(u8);                                    /* extern */
struct sEnemyCommand;
M2C_UNK Send__13sEnemyCommandFv(sEnemyCommand*); /* extern */
M2C_UNK SetEffectCrash3D_R__FP7TObjectP5RwV3dP6sAngleP5RwV3dP5RwV3dffisP7RpClump(
    s32, RwV3d*, sAngle*, const RwV3d*, RwV3d*, f32, f32, s32, s16, u32);     /* extern */
M2C_UNK Close__13TEnemyIconManFv(void*);                                      /* extern */
M2C_UNK On__13TEnemyIconManFff(u32, f32, f32);                                /* extern */
M2C_UNK SetPos__13TEnemyIconManFPC5RwV3dPC5RwV3d(u32, void*, void*);          /* extern */
s32 Create__13TEnemyIconManF10eEnemyIcon(s32);                                /* extern */
M2C_UNK SetLightNum__7nRenderFUi();                                           /* extern */
M2C_UNK SetRenderStateForBlendAdd__7nRenderFv();                              /* extern */
M2C_UNK LoadRenderState__7nRenderFv();                                        /* extern */
M2C_UNK SaveRenderState__7nRenderFv();                                        /* extern */
M2C_UNK fn_8011C0E8(u32);                                                     /* extern */
M2C_UNK DestroyEnemy__14TEnemyScoreManFi(u32, s32);                           /* extern */
M2C_UNK AddScore__14TEnemyScoreManFii(u32, s32, M2C_UNK);                     /* extern */
M2C_UNK CreateInstance__14TEnemyScoreManFv();                                 /* extern */
M2C_UNK Entry__18TEnemyPowerCoreManFPC5RwV3di(void*, void*, s32);             /* extern */
void* GetInstance__18TEnemyPowerCoreManFv();                                  /* extern */
u32 GetMtnPathMatrix__13TEnemyMtnPathFv(void*);                               /* extern */
M2C_UNK SetPath__13TEnemyMtnPathFi(void*, s32);                               /* extern */
M2C_UNK ChangePath__13TEnemyMtnPathFi(void*, s32);                            /* extern */
void* __ct__13TEnemyMtnPathFP7TObjectP17TEnemyMtnPathData(void*, void*, u32); /* extern */
M2C_UNK __dt__17TEnemyMtnPathDataFv(M2C_UNK, M2C_UNK);                        /* extern */
u32 __ct__17TEnemyMtnPathDataF14eEnemyDataBase(u32, u32);                     /* extern */
M2C_UNK DecreaseTimer__7nSystemFRi(void*);                                    /* extern */
M2C_UNK fn_8014FF2C(s32);                                                     /* extern */
void* fn_80150588(void*);                                                     /* extern */
M2C_UNK fn_80150958(void*);                                                   /* extern */
void fn_80195790(RwMatrix*, RwV3d*, f32, f32, s32); /* RwMatrixRotateOneMinusCosineSine */
void fn_80195A74(RwMatrix*, RwV3d*, f32, s32);      /* RwMatrixRotate */
void fn_80196050(RwMatrix*, RwV3d*, s32);           /* RwMatrixTranslate */
void fn_801961E8(RwMatrix*, RwMatrix*, s32);        /* RwMatrixTransform */
void fn_80196414(RwMatrix*, RwV3d*, f32*, RwV3d*); /* RwMatrixQueryRotate */ /* extern */
void fn_801990E0(RwV3d*, RwV3d*); /* RwV3dNormalize */                       /* extern */
f32 fn_801991B4(RwV3d*);                                                     /* RwV3dLength */
void fn_8019941C(RwV3d*, RwV3d*, s32, RwMatrix*); /* RwV3dTransformPoints */ /* extern */
RwMatrix* fn_8019E8EC(void*);                                                /* RwFrameGetLTM */
void fn_8019EB94(void*, RwV3d*, s32); /* RwFrameTranslate */                 /* extern */
void fn_8019ECCC(void*, RwMatrix*, s32);                                     /* RwFrameTransform */
void fn_8019ED68(void*, void*, f32, s32);                                    /* RwFrameRotate */
void fn_8019EE04(s32);                          /* RwFrameUpdateObjects */
s32 rand();                                     /* extern */
M2C_UNK fn_8_5EF94(u32, RwV3d*);                /* extern */
M2C_UNK fn_8_5F048(u32, RwV3d*);                /* extern */
M2C_UNK fn_8_5F100(s32);                        /* extern */
void fn_8_5F140(void*);                         /* extern */
s32 fn_8_5F30C(M2C_UNK*, RwV3d*, sAngle*, f32); /* extern */
M2C_UNK fn_8_90B10(s32);                        /* extern */
M2C_UNK fn_8_A1E94(s32);                        /* extern */
struct sFlyerIronBall;
void* fn_8_A8B60(const sFlyerIronBall*); /* TObjEnemyFlyerIronBall::Create */ /* extern */
M2C_UNK fn_8_A8D1C();                                                         /* extern */
M2C_UNK fn_8_A8D30();                                                         /* extern */
struct sFlyerMissile;
void* fn_8_A9C6C(const sFlyerMissile*); /* TObjEnemyFlyerMissile::Create */ /* extern */
M2C_UNK fn_8_A9E18();                                                       /* extern */
M2C_UNK fn_8_A9E2C();                                                       /* extern */
void fn_8_A9E94(u32, RwMatrix*);
void fn_8_AA08C(void*, void*); /* TEnemyFlyer_Strategy::SetUpFirst */       /* extern */
void* fn_8_AA58C(void*); /* TEnemyFlyer_Strategy::TEnemyFlyer_Strategy() */ /* extern */
M2C_UNK pawnReleaseBuffer(void*);                                           /* extern */
s32 sprintf(void*, const char*, ...);                                       /* extern */
void fn_8_A4E44(M2C_UNK* arg0);                                             /* static */
void fn_8_A549C(void* arg0);
extern RwV3d AxisX;
extern RwV3d AxisY;
extern RwV3d AxisZ;
extern M2C_UNK lbl_8029C310;
extern void* lbl_802AD070[];
extern void* lbl_80303DC8[];
extern M2C_UNK* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern s32 lbl_8042C2A0;
extern u32 lbl_8042C388;
extern u32 mpDataBase__14TEnemyDataBase;
extern u32 EnemyScoreMan__14TEnemyScoreMan;
/* The strategy's vtables, defined where retail emits them (around the
 * switch table). */
extern void* lbl_8_data_15F80[6];
extern void* lbl_8_data_15FBC[7];

/* The vector the stage 11 units carry unreferenced at the head of their
 * .rodata (see e_capture_collision_stage11.cpp). */
#pragma force_active on
static const RwV3d lbl_8_rodata_18A0 = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

/* The leader number of each team's summoned group, by team (stage 0x15). */
extern const u8 lbl_8_rodata_18AC[4] = { 2, 5, 8, 11 };

void fn_8_A258C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x5C;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_A25AC(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x1D;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_A25CC(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x1C) = (s32)(M2C_FIELD(arg0, s32*, 0x1C) + 1);
			M2C_FIELD(arg0, s32*, 0x18) = 0x3C;
			M2C_FIELD(arg0, s32*, 0x10) = 0x26;
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_A2690(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x44;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_A26B0(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x41;
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 2;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_A2768(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x12C;
			M2C_FIELD(arg0, s32*, 0x10) = 0x43;
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_A2820(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x42;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_A2840(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = (s32)(1080.0f * (3.0517578125e-05f * (f32)rand()));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0x258) {
				M2C_FIELD(arg0, s32*, 0x18) = 0x258;
			}
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			return;
		case 1:
			if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
				temp_r0 = M2C_FIELD(arg0, s32*, 0x1C);
				if ((temp_r0 < 4)
				    && (IsAnnihilated__19nEnemyCommunicationFUc(lbl_8_rodata_18AC[temp_r0]) == 1)) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 6;
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
					return;
				}
			}
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_A29E0(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_A2A00(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	if ((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, s32*, 0xC)  = 5;
		M2C_FIELD(arg0, s32*, 0x10) = 0;
		M2C_FIELD(arg0, s32*, 4)    = 5;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
			fn_800A31B8((void*)M2C_FIELD(arg0, u32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
		}
	}
}

void fn_8_A2A78(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	if ((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, s32*, 0xC)  = 4;
		M2C_FIELD(arg0, s32*, 0x10) = 0;
		M2C_FIELD(arg0, s32*, 4)    = 4;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
			fn_800A31B8((void*)M2C_FIELD(arg0, u32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
		}
	}
}

s32 fn_8_A2AF0(void* arg0)
{
	s32 var_r4;
	s32 temp_r0;

	temp_r0 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x260);
	if (temp_r0 != 0) {
		var_r4 = 0;
		switch (temp_r0) { /* irregular */
			case 0x42:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 2;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
			case 0x43:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
			case 0x2:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
			case 0x44:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 5;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
			case 0x1D:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 7;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
			case 0x5C:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 8;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x260) = 0;
		return var_r4;
	}
	return 0;
}

/* TEnemyFlyer_Strategy's vtable and its base's: destructor, then the strategy
 * hooks (fn_8_A23AC is the shared one in rel/e_strategy_flyer_stage11.cpp). */
M2C_UNK** fn_8_A3170(M2C_UNK** arg0, s16 arg1);
M2C_UNK** fn_8_A320C(M2C_UNK** arg0, s16 arg1);
void fn_8_A2D48(void* arg0, u32 arg1, s32 arg2);
void fn_8_A23AC();

void* lbl_8_data_15F80[6] = {
	NULL,
	NULL,
	(void*)fn_8_A3170,
	(void*)fn_8_A23AC,
	(void*)fn_8_A2D48,
	(void*)fn_8_A2AF0,
};

/* TEnemyFlyer_Strategy::ExecStrategyMode: runs the given phase of the
 * current mode's StrategyMode_* handler. */
void fn_8_A2D48(void* arg0, u32 arg1, s32 arg2)
{
	switch (arg1) {
		case 0:
			fn_8_A29E0(arg0, arg2);
			break;
		case 1:
			fn_8_A2840(arg0, arg2);
			break;
		case 2:
			fn_8_A2820(arg0, arg2);
			break;
		case 3:
			fn_8_A2768(arg0, arg2);
			break;
		case 4:
			fn_8_A26B0(arg0, arg2);
			break;
		case 5:
			fn_8_A2690(arg0, arg2);
			break;
		case 6:
			fn_8_A25CC(arg0, arg2);
			break;
		case 7:
			fn_8_A25AC(arg0, arg2);
			break;
		case 8:
			fn_8_A258C(arg0, arg2);
			break;
	}
}

void* lbl_8_data_15FBC[7] = { NULL, NULL, (void*)fn_8_A320C, (void*)fn_8_A23AC, NULL, NULL, NULL };

/* The flyer's collision shape (a CCL_INFO): a 13.0 sphere. */
M2C_UNK** fn_8_A3170(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_15F80;
		if (arg0 != NULL) {
			*arg0 = (M2C_UNK*)lbl_8_data_15FBC;
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_A31D4(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_15FBC;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_15F80;
	M2C_FIELD(arg0, s32*, 0x1C)   = 0;
}

M2C_UNK** fn_8_A320C(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_15FBC;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}
}
