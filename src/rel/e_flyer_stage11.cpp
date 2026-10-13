#include "types.h"

// stage11D's TObjEnemyFlyer (named by the PS2 build's symbols; the functions
// keep their address names), with the module's register record at the end.
// Its strategy is rel/e_flyer_strategy_stage11.cpp.
//
// The unit's literals are written in place, so the compiler pools them after
// the named constants in first-use order, which is retail's .rodata layout.
//
// Retail builds this unit with deferred inlining ("-inline deferred,auto"),
// like rel/e_capture_collision_stage11.cpp: the compiler emits the functions
// in reverse definition order, so they are defined here last to first, and
// the vtable it generates from the class declarations lands after the named
// data and ahead of the data the functions generate (switch tables, string
// literals). The vtable's generation also emits the EditOnChange adjustor
// thunk (the TObjSetObj base at 0xB0) at the end of .text.

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
		pos.x = pos.y = pos.z = 0.0f;
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
		pos.x = pos.y = pos.z = 0.0f;
		vel.x = vel.y = vel.z = 0.0f;
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
		pos.x = pos.y = pos.z = 0.0f;
		vel.x = vel.y = vel.z = 0.0f;
		ang.x = ang.y = ang.z = 0;
		target.x = target.y = target.z = 0.0f;
		maxSpeed                       = 0.0f;
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
	virtual s32 vslot5();
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

/* The class hierarchy, declared so the compiler generates TObjEnemyFlyer's
 * vtable and its EditOnChange adjustor thunk (the TObjSetObj base at 0xB0) the
 * way retail has them. The member functions keep their definitions below
 * under their mangled names, as the other stage 11 object units do. Slot
 * names come from the PS2 build's symbols; Slots without a known name
 * keep the placeholder names the symbol map gives them. */
struct SETDATA_PARAM;
struct sEnemyCommand;
enum ENEMY_MD { ENEMY_MD_0 };

struct TObjectHdr {
	u8 pad00[0x18];
};

class TObject : public TObjectHdr
{
public:
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();

	u8 pad1C[0x94];
};

struct SetObjHdr {
	SETDATA_PARAM* frame;
};

class TObjSetObj : public SetObjHdr
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);
};

class TObjEnemy : public TObject, public TObjSetObj
{
public:
	enum eCtrlSMode { CTRL_SMODE_0 };

	virtual ~TObjEnemy();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void CheckDamage2();
	virtual void DestroyMyself();
	virtual void Explosion();
	virtual void InitMode(ENEMY_MD);
	virtual void ExecMode(ENEMY_MD);
	virtual void ExitMode(ENEMY_MD);
	virtual void CtrlMode(ENEMY_MD, eCtrlSMode) = 0;
	virtual void Update();
	virtual void UpdateOnEdit();
	virtual void DispOpaq();
	virtual void DispTrans();
	virtual void DispShadow();
	virtual void DispOpaqOnEdit();
	virtual void Virtual33D94();
	virtual void KillMySelf();
	virtual s32 CheckCameraFrustumTest(const RwV3d*, f32);
	virtual s32 CheckCameraFrustumTestForShadow(const RwV3d*, f32);
	virtual void AddScore();
	virtual s32 CanCheckTechnicPointForThunderShoot();
	virtual s32 IsSleep();
	virtual void AddItemBox(RwV3d*) = 0;
	virtual RwV3d* Virtual33D98();
	virtual s32 GetCurrentLightNum();
	virtual void RcvCommand(sEnemyCommand*);
	virtual void DispEnemySetting();
	virtual void Virtual33DA0();
	virtual void Virtual33DA4();
};

class TObjEnemyFlyer : public TObjEnemy
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);
	virtual ~TObjEnemyFlyer();
	virtual void DestroyMyself();
	virtual void Explosion();
	virtual void CtrlMode(ENEMY_MD, eCtrlSMode);
	virtual void Update();
	virtual void UpdateOnEdit();
	virtual void DispOpaq();
	virtual void DispTrans();
	virtual void DispShadow();
	virtual void DispOpaqOnEdit();
	virtual s32 CheckCameraFrustumTest(const RwV3d*, f32);
	virtual s32 CheckCameraFrustumTestForShadow(const RwV3d*, f32);
	virtual void AddScore();
	virtual void AddItemBox(RwV3d*);
	virtual RwV3d* Virtual33D98();
	virtual void RcvCommand(sEnemyCommand*);
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
void fn_8019EE04(s32);                                       /* RwFrameUpdateObjects */
s32 rand();                                                  /* extern */
M2C_UNK SetAimPosition__11TMachineGunFPC5RwV3d(u32, RwV3d*); /* extern */
M2C_UNK SetPosition__11TMachineGunFPC5RwV3d(u32, RwV3d*);    /* extern */
M2C_UNK Stop__11TMachineGunFv(s32);                          /* extern */
void Run__11TMachineGunFv(void*);                            /* extern */
s32 fn_8_5F30C(M2C_UNK*, RwV3d*, sAngle*, f32);              /* extern */
M2C_UNK CreateItemBox__8nItemBoxFP5RwV3d(s32);               /* extern */
M2C_UNK fn_8_A1E94(s32);                                     /* extern */
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
typedef struct ObjectEntry {
	const char* name;        /* 0x00 */
	void (*load)(void);      /* 0x04 */
	void (*unload)(void);    /* 0x08 */
	void (*create)(void);    /* 0x0C */
	void* unk10;             /* 0x10 */
	u32 flags;               /* 0x14 */
	u32 unk18;               /* 0x18 */
	s16 unk1C;               /* 0x1C */
	s16 unk1E;               /* 0x1E */
	u8 unk20;                /* 0x20 */
	u8 unk21;                /* 0x21 */
	u8 pad22[2];             /* 0x22 */
	const char* fieldTypes;  /* 0x24 */
	const char** fieldNames; /* 0x28 */
} ObjectEntry;               /* 0x2C */

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
/* The module's data, defined where retail emits it (between the functions
 * whose switch tables it surrounds). */
extern u32 lbl_8_data_15FD8[12];
extern const char* flyerObjectFieldNames[9];
extern const char* lbl_8_data_16180[5];
extern const char* lbl_8_data_161A8[2];
extern s8 lbl_8_data_161B0;
extern s8 lbl_8_data_161B1;
extern s8 lbl_8_data_161B2;
extern s8 lbl_8_data_161B3;
extern char* lbl_8_data_161C4;
extern void* __vt__14TObjEnemyFlyer[];
static u32 lbl_8_bss_1948[4];
static u32 lbl_8_bss_1958;
ObjectEntry flyerObjectEntry;
extern const RwV3d lbl_8_rodata_18C0  = { 0.0f, 1.5f, 0.0f };
extern const f32 lbl_8_rodata_18CC[3] = { 13.0f, 20.0f, 0.0f };
extern const RwV3d lbl_8_rodata_18D8  = { 0.0f, 0.0f, -20.0f };
extern const RwV3d lbl_8_rodata_18E4  = { 0.0f, -20.0f, 0.0f };
extern const RwV3d lbl_8_rodata_18F0  = { 22.0f, 1.0f, 22.0f };

/* False while the game is paused or between scenes (the three flags of the
 * object at lbl_8042C180). */
static inline BOOL flyerIsPlaying()
{
	if (FLD(lbl_8042C180, s8, 0x1F) != 0) {
		return FALSE;
	} else if (FLD(lbl_8042C180, s8, 0x20) != 0) {
		return FALSE;
	} else if (FLD(lbl_8042C180, s8, 0x21) != 0) {
		return FALSE;
	}
	return TRUE;
}

/* The flyer's collision shape (a CCL_INFO): a 13.0 sphere. */
u32 lbl_8_data_15FD8[12] = {
	0x18000F21,
	0x00000400,
	0,
	0,
	0,
	0x41500000,
	0,
	0,
	0,
	0,
	0,
	0,
};

char lbl_8_data_16008[]             = "en_flyer.anm";
FlyerAnimRecord lbl_8_data_16018[2] = {
	{ 0, 3, 0, 0, 0xBF800000, 0x3D800000, 0x3E4CCCCD, lbl_8_data_16008, 0xB },
	{ 0, 0xE, 0, 0, 0, 0, 0, NULL, 0 },
};
char lbl_8_data_16060[]             = "fly_mo_001.anm";
FlyerAnimRecord lbl_8_data_16070[2] = {
	{ 0, 3, 0, 0, 0xBF800000, 0x3D800000, 0x3E4CCCCD, lbl_8_data_16060, 0x10 },
	{ 0, 0xE, 0, 0, 0, 0, 0, NULL, 0 },
};

/* The editor's labels, one per character of flyerObjectFieldTypes;
 * EditOnChange (EditOnChange__14TObjEnemyFlyerFP13SETDATA_PARAM) rewrites the first and third with the names of
 * the chosen weapon and path type. */
char lbl_8_data_160B8[]              = "FLYER TYPE";
char lbl_8_data_160C4[]              = "PATH NUM";
char lbl_8_data_160D0[]              = "PATH TYPE";
char lbl_8_data_160DC[]              = "Not in use";
char lbl_8_data_160E8[]              = "MOVE SPEED";
char lbl_8_data_160F4[]              = "ATTACK INTERVAL";
char lbl_8_data_16104[]              = "WEAPON SPEED";
char lbl_8_data_16114[]              = "WEAPON ANGLE X";
char lbl_8_data_16124[]              = "FLYER ID";
const char* flyerObjectFieldNames[9] = {
	lbl_8_data_160B8,
	lbl_8_data_160C4,
	lbl_8_data_160D0,
	lbl_8_data_160DC,
	lbl_8_data_160E8,
	lbl_8_data_160F4,
	lbl_8_data_16104,
	lbl_8_data_16114,
	lbl_8_data_16124,
};

char lbl_8_data_16154[]         = "NONE";
char lbl_8_data_1615C[]         = "MACHINE GUN";
char lbl_8_data_16168[]         = "MISSILE";
char lbl_8_data_16170[]         = "PAWN";
char lbl_8_data_16178[]         = "BOMB";
const char* lbl_8_data_16180[5] = {
	lbl_8_data_16154,
	lbl_8_data_1615C,
	lbl_8_data_16168,
	lbl_8_data_16170,
	lbl_8_data_16178,
};
char lbl_8_data_16194[]         = "ONE SHOT";
char lbl_8_data_161A0[]         = "LOOP";
const char* lbl_8_data_161A8[2] = { lbl_8_data_16194, lbl_8_data_161A0 };

/* EditOnChange's limits on the weapon kind and the path type. */
#pragma explicit_zero_data on
s8 lbl_8_data_161B0 = 0;
#pragma explicit_zero_data reset
s8 lbl_8_data_161B1 = 4;
#pragma explicit_zero_data on
s8 lbl_8_data_161B2 = 0;
#pragma explicit_zero_data reset
s8 lbl_8_data_161B3 = 1;

char lbl_8_data_161B4[] = "TObjEnemyFlyer";
char* lbl_8_data_161C4  = lbl_8_data_161B4;

/* TEnemyFlyer_Strategy's destructor, with its base's inlined. */
/* The team record behind lbl_80303DC8: the leader's slot and each slot's
 * power-core level. */
struct FlyerPlayerTeam {
	u8 pad00[0x3A];
	s8 leader; /* 0x3A */
	u8 pad3B[0xD5];
	s8 powerCore[4]; /* 0x110 */
};

/* TObjEnemyFlyer::UpdateJetEffect: spins the two jet flames (0x294/0x298)
 * on their bones (0x280/0x284) and plays the jet sound while running. */
static inline void flyerUpdateJetEffect(void* arg0)
{
	void* frame;
	RwMatrix* ltm;

	if (FLD(arg0, void*, 0x280) != NULL) {
		ltm   = fn_8019E8EC(FLD(arg0, void*, 0x280));
		frame = FLD(FLD(arg0, void*, 0x294), void*, 4);
		fn_8019ED68(frame, &AxisZ, FLD(arg0, f32, 0x29C), 0);
		fn_8019ECCC(frame, ltm, 2);
	}
	if (FLD(arg0, void*, 0x284) != NULL) {
		ltm   = fn_8019E8EC(FLD(arg0, void*, 0x284));
		frame = FLD(FLD(arg0, void*, 0x298), void*, 4);
		fn_8019ED68(frame, &AxisZ, FLD(arg0, f32, 0x29C), 0);
		fn_8019ECCC(frame, ltm, 2);
	}
	if (FLD(arg0, s32, 0x3A4) != 0) {
		FLD(arg0, f32, 0x29C) += 75.0f;
		if (FLD(arg0, s32, 0x19C) != 1 && lbl_8042C388 != 0) {
			fn_800B4A38(lbl_8042C388, 0x4016, (u8*)arg0 + 0x268, arg0, 3, 0, 2);
		}
	}
}

/* TObjEnemyFlyer::CarryPawn: tells the carried pawn (command 1) where the
 * hook below the flyer is. */
static inline void flyerCarryPawn(void* arg0)
{
	if (FLD(arg0, void*, 0x288) != NULL) {
		sEnemyCommand cmd;
		cmd.team    = FLD(FLD(arg0, void*, 0xB0), u8, 0x2A);
		cmd.command = 1;
		cmd.id      = FLD(arg0, s32, 0x258);
		RwV3d hook  = lbl_8_rodata_18E4;
		fn_80196050(&FLD(arg0, RwMatrix, 0x360), &hook, 0);
		fn_801961E8(&FLD(arg0, RwMatrix, 0x360), fn_8019E8EC(FLD(arg0, void*, 0x288)), 2);
		cmd.matrix = FLD(arg0, RwMatrix, 0x360);
		cmd.pos    = FLD(arg0, RwMatrix, 0x360).pos;
		cmd.ang    = FLD(arg0, sAngle, 0x14C);
		Send__13sEnemyCommandFv(&cmd);
	}
}

/* The yaw of the hook frame (0x360), as an angle. */
static inline void flyerHookYaw(void* arg0, s32* yaw)
{
	RwV3d axis;
	RwV3d center;
	f32 angle;

	axis = AxisY;
	fn_80196414(&FLD(arg0, RwMatrix, 0x360), &axis, &angle, &center);
	if (axis.y > 0.0f) {
		*yaw = 182.04445f * (180.0f + angle);
	} else {
		*yaw = 182.04445f * (180.0f + (360.0f - angle));
	}
}

/* RpHAnimHierarchy's node array: the frame of the node with the given index. */
struct FlyerHAnimNode {
	s32 nodeID;
	s32 nodeIndex;
	s32 flags;
	void* frame;
};

static inline void flyerFindBoneFrame(void* arg0, s32 boneID, void** frame)
{
	void* hierarchy = FLD(arg0, void*, 0xEC);
	s32 index;

	if (hierarchy != NULL) {
		index = objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(hierarchy, boneID);
		if (index != -1) {
			*frame = FLD(hierarchy, FlyerHAnimNode*, 0x10)[index].frame;
		}
	}
}

/* TObjEnemyFlyer::CloneClump: the body, the two jet flames and the weapon
 * model the flyer carries. */
static inline void flyerCloneClump(void* arg0)
{
	u32 var_r3;
	void* temp_r3;
	u8 temp_r0;

	if ((void*)M2C_FIELD(arg0, void**, 0x2A0) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0x2A0));
		M2C_FIELD(arg0, void**, 0x2A0) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x298) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0x298));
		M2C_FIELD(arg0, void**, 0x298) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x294) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0x294));
		M2C_FIELD(arg0, void**, 0x294) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0xE8));
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	M2C_FIELD(arg0, void**, 0xE8)  = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_1948, s32*, 0));
	M2C_FIELD(arg0, void**, 0x294) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_1948, s32*, 0xC));
	M2C_FIELD(arg0, void**, 0x298) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_1948, s32*, 0xC));
	var_r3                         = 0U;
	temp_r0                        = M2C_FIELD(arg0, u8*, 0x245);
	switch ((s8)temp_r0) { /* irregular */
		case 0:
			break;
		case 1:
			if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
				__ct__14TEnemyDataBaseFv();
			}
			var_r3 = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(
			    mpDataBase__14TEnemyDataBase, 5, 9);
			break;
		case 2:
			if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
				__ct__14TEnemyDataBaseFv();
			}
			var_r3 = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(
			    mpDataBase__14TEnemyDataBase, 5, 0xA);
			break;
		case 4:
			if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
				__ct__14TEnemyDataBaseFv();
			}
			var_r3 = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(
			    mpDataBase__14TEnemyDataBase, 5, 8);
			break;
	}
	if (var_r3 != 0U) {
		M2C_FIELD(arg0, void**, 0x2A0) = fn_80150588((void*)var_r3);
	}
	temp_r3 = M2C_FIELD(arg0, void**, 0xE8);
	if (temp_r3 != NULL) {
		fn_8019EE04(M2C_FIELD(temp_r3, s32*, 4));
	}
}

/* The constructor's view of the object: the sub-objects whose addresses it
 * passes on. */
struct FlyerCtorView {
	u8 pad000[0x28];
	u8 colli[0x88]; /* 0x028: C_COLLI */
	u8 setObj[0x8]; /* 0x0B0: TObjSetObj (its first word is the placement) */
	u8 pad0B8[0x88];
	RwV3d pos;  /* 0x140 */
	sAngle ang; /* 0x14C */
	u8 pad158[0xE8];
	u8 anim[0x4]; /* 0x240: HAnimClass */
};

void DestroyMyself__14TObjEnemyFlyerFv(void* arg0);
void AddItemBox__14TObjEnemyFlyerFP5RwV3d(void* arg0, s32 arg1);
void AddScore__14TObjEnemyFlyerFv(void* arg0);
void RcvCommand__14TObjEnemyFlyerFP13sEnemyCommand(void* arg0, void* arg1);
s32 fn_8_A353C(void* arg0);
s32 fn_8_A35BC(void* arg0);
void Explosion__14TObjEnemyFlyerFv(void* arg0);
s32 CheckCameraFrustumTestForShadow__14TObjEnemyFlyerFPC5RwV3df(void);
s32 CheckCameraFrustumTest__14TObjEnemyFlyerFPC5RwV3df(void* arg0);
void DispOpaqOnEdit__14TObjEnemyFlyerFv(void* arg0);
void DispShadow__14TObjEnemyFlyerFv(void* arg0);
void DispTrans__14TObjEnemyFlyerFv(void* arg0);
void DispOpaq__14TObjEnemyFlyerFv(void* arg0);
void UpdateOnEdit__14TObjEnemyFlyerFv(void* arg0);
void Update__14TObjEnemyFlyerFv(M2C_UNK* arg0);
void fn_8_A4140(void* arg0, s32 arg1);
void fn_8_A4230(void* arg0, s32 arg1);
void fn_8_A4290(M2C_UNK* arg0, s32 arg1);
void fn_8_A4394(void* arg0, s32 arg1);
void fn_8_A4478(void* arg0, s32 arg1);
void CtrlMode__14TObjEnemyFlyerF8ENEMY_MDQ29TObjEnemy10eCtrlSMode(
    M2C_UNK* arg0, s32 arg1, s32 arg2);
void fn_8_A4830(void* arg0, RwV3d* dir, sAngle* ang);
void fn_8_A4AC0(void* arg0, RwV3d* dir, sAngle* ang);
void fn_8_A4B90(M2C_UNK* arg0);
void fn_8_A4CB0(void* arg0);
void fn_8_A4E44(M2C_UNK* arg0);
void fn_8_A53E4(void* arg0);
void fn_8_A549C(void* arg0);
void fn_8_A5A04(void* arg0);
void fn_8_A5A8C(void* arg0);
void fn_8_A5C70(void* arg0);
void fn_8_A5D48(void* arg0);
void* __dt__14TObjEnemyFlyerFv(void* arg0, s16 arg1);
M2C_UNK* fn_8_A5F50(M2C_UNK* arg0, void* arg1);
M2C_UNK* fn_8_A66D4(void);
void TObjEnemyFlyer::EditOnChange(SETDATA_PARAM* data);
void flyerObjectUnload(void);
void flyerObjectLoad(void);
void flyerObjectCreate(void);
void flyerObjectRegister(void);
__declspec(section ".ctors") void (*const flyerObjectCtorEntry)(void) = flyerObjectRegister;

void flyerObjectRegister(void)
{
	flyerObjectEntry.flags      = 0;
	flyerObjectEntry.unk18      = 0;
	flyerObjectEntry.name       = "FLYER OBJECT";
	flyerObjectEntry.load       = (void (*)(void))flyerObjectLoad;
	flyerObjectEntry.unload     = (void (*)(void))flyerObjectUnload;
	flyerObjectEntry.create     = (void (*)(void))flyerObjectCreate;
	flyerObjectEntry.unk10      = (void*)0;
	flyerObjectEntry.flags      = 0;
	flyerObjectEntry.unk18      = 0;
	flyerObjectEntry.unk20      = 0x1E;
	flyerObjectEntry.unk1C      = 0x1530;
	flyerObjectEntry.unk1E      = 4;
	flyerObjectEntry.unk21      = 0;
	flyerObjectEntry.fieldTypes = "ccccfifxi";
	flyerObjectEntry.fieldNames = (const char**)&flyerObjectFieldNames;
	if ("ccccfifxi" != NULL) {
		flyerObjectEntry.flags |= 8;
	} else {
		flyerObjectEntry.flags &= ~8;
	}
}

void flyerObjectCreate(void)
{
	M2C_UNK* temp_r3;

	temp_r3 = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x3C4);
	if (temp_r3 != NULL) {
		fn_8_A5F50(temp_r3, lbl_8042C10C);
	}
}

void flyerObjectLoad(void)
{
	char sp8[0x40];
	s32 temp_r3;
	u32 temp_r5;
	u32 var_r0;

	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	Add__14TEnemyDataBaseF14eEnemyDataBasePc(mpDataBase__14TEnemyDataBase, 5, "en_flyer.one");
	temp_r5 = fn_800194C4(&lbl_8029C310);
	if (temp_r5 != 0U) {
		temp_r3 = sprintf(&sp8, "%s_flyer.one", temp_r5);
		if ((temp_r3 >= 0) && (temp_r3 < 0x40)) {
			if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
				__ct__14TEnemyDataBaseFv();
			}
			Add__14TEnemyDataBaseF14eEnemyDataBasePc(mpDataBase__14TEnemyDataBase, 0xC, &sp8);
		}
	}
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	temp_r3 = SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(
	    mpDataBase__14TEnemyDataBase, 5, 0xD);
	if (temp_r3 != 0U) {
		objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(temp_r3, 6);
	} else {
		return;
	}
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_1948, u32*, 0)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 5, 0xC);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_1948, u32*, 4)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 5, 0xF);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_1948, u32*, 8)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 5, 0xE);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_1948, u32*, 0xC)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 5, 6);
	LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    5, (M2C_UNK*)&lbl_8_data_16018[0]);
	LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    5, (M2C_UNK*)&lbl_8_data_16070[0]);
	fn_8_A9E2C();
	fn_8_A8D30();
	var_r0 = (u32)__nw__FUl(0xC);
	if (var_r0 != 0U) {
		var_r0 = __ct__17TEnemyMtnPathDataF14eEnemyDataBase(var_r0, 0xC);
	}
	lbl_8_bss_1958 = var_r0;
}

void flyerObjectUnload(void)
{
	if ((u32)lbl_8_bss_1958 != 0U) {
		__dt__17TEnemyMtnPathDataFv(lbl_8_bss_1958, 1);
		lbl_8_bss_1958 = 0U;
	}
	fn_8_A8D1C();
	fn_8_A9E18();
	ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    5, (M2C_UNK*)&lbl_8_data_16070[0]);
	ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    5, (M2C_UNK*)&lbl_8_data_16018[0]);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	Delete__14TEnemyDataBaseF14eEnemyDataBase(mpDataBase__14TEnemyDataBase, 0xC);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	Delete__14TEnemyDataBaseF14eEnemyDataBase(mpDataBase__14TEnemyDataBase, 5);
}

/* TObjEnemyFlyer::EditOnChange: clamps the edited fields and names the chosen
 * weapon and path type in the editor's labels. */
void TObjEnemyFlyer::EditOnChange(SETDATA_PARAM* data)
{
	static const f32 minSpeed = 0.0f;
	static const f32 maxSpeed = 1000.0f;
	static const s32 minUnk14 = 0;
	static const s32 maxUnk14 = 0x100;
	FlyerParam* param         = M2C_FIELD(data, FlyerParam**, 0x2C);

	param->kind              = flyerClamp(param->kind, lbl_8_data_161B0, lbl_8_data_161B1);
	param->pathType          = flyerClamp(param->pathType, lbl_8_data_161B2, lbl_8_data_161B3);
	param->moveSpeed         = flyerClamp(param->moveSpeed, minSpeed, maxSpeed);
	param->unk14             = flyerClamp(param->unk14, minUnk14, maxUnk14);
	flyerObjectFieldNames[0] = lbl_8_data_16180[param->kind];
	flyerObjectFieldNames[2] = lbl_8_data_161A8[param->pathType];
}

M2C_UNK* fn_8_A66D4(void)
{
	M2C_UNK* var_r0;

	var_r0 = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x3C4);
	if (var_r0 != NULL) {
		var_r0 = fn_8_A5F50(var_r0, lbl_8042C10C);
	}
	return var_r0;
}

/* TObjEnemyFlyer::TObjEnemyFlyer(TObject*) */
M2C_UNK* fn_8_A5F50(M2C_UNK* arg0, void* arg1)
{
	RwMatrix m;
	void* p;
	f32 sine;
	u32 flag;

	fn_800A714C(arg0, arg1);
	__ct__10HAnimClassFv(((FlyerCtorView*)arg0)->anim);
	FLD(arg0, void*, 0x18) = __vt__14TObjEnemyFlyer;
	FLD(arg0, void*, 0xB4) = (u8*)__vt__14TObjEnemyFlyer + 0x2C;
	FLD(arg0, char*, 0)    = lbl_8_data_161C4;
	FLD(arg0, s16, 0x1E)   = 0x3C4;
	fn_8_A5D48(arg0);
	fn_8_A5C70(arg0);
	FLD(arg0, f32, 0x158) = FLD(arg0, f32, 0x15C) = FLD(arg0, f32, 0x160) = 0.0f;
	FLD(arg0, u32, 0x188) &= ~0x103000;
	FLD(arg0, u32, 0x188) |= 0x100000;
	FLD(arg0, u32, 0x188) |= 0x10;
	FLD(arg0, f32, 0x3C0) = 3.0f;
	FLD(arg0, f32, 0x3BC) = FLD(arg0, f32, 0x3C0);
	FLD(arg0, s16, 0x2E) = FLD(arg0, f32, 0x1A4) = FLD(arg0, f32, 0x3C0);
	FLD(arg0, f32, 0x1A0)                        = 3.0f;
	FLD(arg0, s16, 0x2C)                         = 3;
	flyerCloneClump(arg0);
	/* The light set the placement's flags (bits 18-20) pick, after the eight
	 * the stage keeps for itself. */
	flag = *(volatile u32*)&FLD(FLD(arg0, void*, 0xB0), u32, 0x18);
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
	    FLD(arg0, void*, 0xE8), ((flag & 0x1C0000) >> 18) + 8);
	FLD(arg0, void*, 0xE4) = lbl_8_data_16018;
	FLD(arg0, s32, 0xD4)   = 0;
	UpdateMotion__11ENEMYMTNMANFv((u8*)arg0 + 0xB8);
	fn_8_A549C(arg0);
	flyerUpdateJetEffect(arg0);
	if (OnEdit__10TObjSetObjFv(((FlyerCtorView*)arg0)->setObj) == 0) {
		Init__7C_COLLIFP8CCL_INFOiUc((u8*)arg0 + 0x28, (M2C_UNK*)lbl_8_data_15FD8, 1, 3);
		FLD(arg0, RwV3d, 0x88) = FLD(arg0, RwV3d, 0x140);
	}
	FLD(arg0, f32, 0x130) = 12.0f;
	FLD(arg0, f32, 0x134) = 0.8f;
	p                     = __nw__FUl(0x1C);
	if (p != NULL) {
		p = fn_8_AA58C(p);
	}
	FLD(arg0, void*, 0x240) = p;
	if (FLD(arg0, void*, 0x240) != NULL) {
		fn_8_AA08C(FLD(arg0, void*, 0x240), arg0);
	}
	FLD(arg0, s32, 0x3B8) = Create__13TEnemyIconManF10eEnemyIcon(0);
	FLD(arg0, s32, 0x13C) = 1;
	p                     = __nw__FUl(0x20);
	if (p != NULL) {
		p = __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID(p, arg0, FLD(arg0, s32, 0x13C));
	}
	FLD(arg0, void*, 0x228) = p;
	if (FLD(arg0, s8, 0x245) == 1) {
		FLD(arg0, s32, 0x304) = fn_8_5F30C(
		    lbl_8042C10C, &((FlyerCtorView*)arg0)->pos, &((FlyerCtorView*)arg0)->ang, 200.0f);
		Stop__11TMachineGunFv(FLD(arg0, s32, 0x304));
	}
	p = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xD0);
	if (p != NULL) {
		p = __ct__13TEnemyMtnPathFP7TObjectP17TEnemyMtnPathData(p, arg0, lbl_8_bss_1958);
	}
	FLD(arg0, void*, 0x3B4) = p;
	if (FLD(arg0, void*, 0x3B4) != NULL) {
		sine = fn_800D7B00(FLD(arg0, s32, 0x150));
		fn_80195790(&m, (RwV3d*)&AxisY, 1.0f - fn_800D7AE4(FLD(arg0, s32, 0x150)), sine, 0);
		fn_80196050(&m, &((FlyerCtorView*)arg0)->pos, 2);
		FLD(FLD(arg0, void*, 0x3B4), RwMatrix, 0x7C) = m;
		FLD(FLD(arg0, void*, 0x3B4), f32, 0x34)      = FLD(arg0, f32, 0x248);
		ChangePath__13TEnemyMtnPathFi(FLD(arg0, void*, 0x3B4), FLD(arg0, s8, 0x244));
	}
	return arg0;
}

#pragma opt_common_subs off

void* __dt__14TObjEnemyFlyerFv(void* arg0, s16 arg1)
{
	s32 temp_cr0_eq;
	void** temp_r3;

	if (arg0 != NULL) {
		M2C_FIELD(arg0, M2C_UNK**, 0x18) = (M2C_UNK*)__vt__14TObjEnemyFlyer;
		M2C_FIELD(arg0, void**, 0xB4)    = (void*)((u8*)__vt__14TObjEnemyFlyer + 0x2C);
		if ((u32)M2C_FIELD(arg0, u32*, 0x304) != 0U) {
			pawnReleaseBuffer((void*)M2C_FIELD(arg0, u32*, 0x304));
			M2C_FIELD(arg0, u32*, 0x304) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x3B8) != 0U) {
			Close__13TEnemyIconManFv((void*)M2C_FIELD(arg0, u32*, 0x3B8));
			M2C_FIELD(arg0, u32*, 0x3B8) = 0U;
		}
		temp_r3 = M2C_FIELD(arg0, void***, 0x240);
		if (temp_r3 != NULL) {
			if (temp_r3 != NULL) {
				((TSubDispatch*)temp_r3)->vslot2(1);
			}
			M2C_FIELD(arg0, void***, 0x240) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2A0) != 0U) {
			fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2A0));
			M2C_FIELD(arg0, u32*, 0x2A0) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x298) != 0U) {
			fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x298));
			M2C_FIELD(arg0, u32*, 0x298) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x294) != 0U) {
			fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x294));
			M2C_FIELD(arg0, u32*, 0x294) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
			fn_80150958((void*)M2C_FIELD(arg0, u32*, 0xE8));
			M2C_FIELD(arg0, u32*, 0xE8) = 0U;
		}
		__dt__10HAnimClassFv((u8*)arg0 + 0x240, 0);
		fn_800A7088(arg0, 0);
		if (arg1 > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, arg0);
		}
	}
	return arg0;
}
#pragma opt_common_subs reset

void fn_8_A5D48(void* arg0)
{
	M2C_FIELD(arg0, s32*, 0x240) = 0;
	M2C_FIELD(arg0, s32*, 0x260) = 0;
	M2C_FIELD(arg0, f32*, 0x264) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x280) = 0;
	M2C_FIELD(arg0, s32*, 0x284) = 0;
	M2C_FIELD(arg0, s32*, 0x288) = 0;
	M2C_FIELD(arg0, s32*, 0x28C) = 0;
	M2C_FIELD(arg0, s32*, 0x290) = 0;
	M2C_FIELD(arg0, s32*, 0x294) = 0;
	M2C_FIELD(arg0, s32*, 0x298) = 0;
	M2C_FIELD(arg0, s32*, 0x2A0) = 0;
	M2C_FIELD(arg0, f32*, 0x29C) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x25C) = 0;
	UnitMatrix__FP11RwMatrixTag((u8*)arg0 + 0x2A4);
	M2C_FIELD(arg0, s32*, 0x2E4) = 1;
	M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x250) = 0;
	M2C_FIELD(arg0, s32*, 0x304) = 0;
	M2C_FIELD(arg0, s32*, 0x3AC) = 0;
	M2C_FIELD(arg0, s32*, 0x3B0) = 0;
	M2C_FIELD(arg0, s32*, 0x3B4) = 0;
	M2C_FIELD(arg0, s32*, 0x258) = 0;
	M2C_FIELD(arg0, s32*, 0x3A0) = 1;
	M2C_FIELD(arg0, s32*, 0x3A4) = 1;
	M2C_FIELD(arg0, s32*, 0x3B8) = 0;
	M2C_FIELD(arg0, f32*, 0x3C0) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x3BC) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x3A8) = 0;
}

void fn_8_A5C70(void* arg0)
{
	void* temp_r5;
	void* temp_r4;
	void* temp_r4_2;

	temp_r4                      = M2C_FIELD(arg0, void**, 0xB0);
	temp_r5                      = M2C_FIELD(temp_r4, void**, 0x2C);
	M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(temp_r4, f32*, 0);
	M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	temp_r4_2                    = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(temp_r4_2, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x154) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x14);
	M2C_FIELD(arg0, f32*, 0x1C0) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1C4) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1C8) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x1C0) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1C4) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1C8) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x1B8) = 1.5f;
	M2C_FIELD(arg0, u8*, 0x245)  = (u8)M2C_FIELD(temp_r5, u8*, 0);
	M2C_FIELD(arg0, u8*, 0x244)  = (u8)M2C_FIELD(temp_r5, u8*, 1);
	M2C_FIELD(arg0, u8*, 0x246)  = (u8)M2C_FIELD(temp_r5, u8*, 2);
	M2C_FIELD(arg0, f32*, 0x248) = (f32)M2C_FIELD(temp_r5, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x24C) = (f32)M2C_FIELD(temp_r5, f32*, 0xC);
	M2C_FIELD(arg0, s32*, 0x250) = (s32)M2C_FIELD(temp_r5, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x254) = (s32)M2C_FIELD(temp_r5, s32*, 8);
	M2C_FIELD(arg0, s32*, 0x258) = (s32)M2C_FIELD(temp_r5, s32*, 0x14);
}

void fn_8_A5A8C(void* arg0)
{
	flyerCloneClump(arg0);
}

void fn_8_A5A04(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x2A0) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2A0));
		M2C_FIELD(arg0, u32*, 0x2A0) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x298) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x298));
		M2C_FIELD(arg0, u32*, 0x298) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x294) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x294));
		M2C_FIELD(arg0, u32*, 0x294) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0xE8));
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

#pragma opt_common_subs off

/* TObjEnemyFlyer::SetPosition: places the model, takes the collision
 * position and the velocity from it, finds the bones the effects and the
 * weapon hang from, and updates the shadow. */
void fn_8_A549C(void* arg0)
{
	void* frame;
	RwMatrix* ltm;

	if (FLD(arg0, void*, 0xE8) != NULL) {
		frame = FLD(FLD(arg0, void*, 0xE8), void*, 4);
		fn_8019ED68(frame, &AxisY, 0.0054931640625f * (f32)FLD(arg0, s32, 0x150), 2);
		fn_8019EB94(frame, &FLD(arg0, RwV3d, 0x140), 2);
		RwV3d prev              = FLD(arg0, RwV3d, 0x268);
		FLD(arg0, RwV3d, 0x268) = fn_8019E8EC(frame)->pos;
		FLD(arg0, f32, 0x2EC)   = FLD(arg0, f32, 0x268) - prev.x;
		FLD(arg0, f32, 0x2F0)   = FLD(arg0, f32, 0x26C) - prev.y;
		FLD(arg0, f32, 0x2F4)   = FLD(arg0, f32, 0x270) - prev.z;
		if (0.0f
		    != FLD(arg0, f32, 0x2EC) * FLD(arg0, f32, 0x2EC)
		        + FLD(arg0, f32, 0x2F0) * FLD(arg0, f32, 0x2F0)
		        + FLD(arg0, f32, 0x2F4) * FLD(arg0, f32, 0x2F4)) {
			fn_801990E0(&FLD(arg0, RwV3d, 0x2EC), &FLD(arg0, RwV3d, 0x2EC));
		}
		FLD(arg0, f32, 0x2EC) *= FLD(arg0, f32, 0x248);
		FLD(arg0, f32, 0x2F0) *= FLD(arg0, f32, 0x248);
		FLD(arg0, f32, 0x2F4) *= FLD(arg0, f32, 0x248);
	}
	if (FLD(arg0, void*, 0x288) == NULL) {
		flyerFindBoneFrame(arg0, 0x3F2, &FLD(arg0, void*, 0x288));
	}
	if (FLD(arg0, void*, 0x290) == NULL && FLD(arg0, void*, 0x2A0) != NULL) {
		FLD(arg0, void*, 0x290)
		    = objRwFrameGetFrame__FP7RwFramei(FLD(FLD(arg0, void*, 0x2A0), void*, 4), 1);
		if (FLD(arg0, void*, 0x290) != NULL) {
			FLD(arg0, RwMatrix, 0x308) = FLD(FLD(arg0, void*, 0x290), RwMatrix, 0x10);
		}
	}
	if (FLD(arg0, void*, 0x28C) == NULL && FLD(arg0, void*, 0x2A0) != NULL) {
		FLD(arg0, void*, 0x28C)
		    = objRwFrameGetFrame__FP7RwFramei(FLD(FLD(arg0, void*, 0x2A0), void*, 4), 2);
	}
	if (FLD(arg0, void*, 0x290) != NULL) {
		fn_8019ED68(
		    FLD(arg0, void*, 0x290), &AxisX, 0.0054931640625f * (f32)FLD(arg0, s32, 0x250), 0);
		fn_8019ECCC(FLD(arg0, void*, 0x290), &FLD(arg0, RwMatrix, 0x308), 2);
	}
	if (FLD(arg0, void*, 0x288) != NULL && FLD(arg0, void*, 0x2A0) != NULL) {
		frame = FLD(FLD(arg0, void*, 0x2A0), void*, 4);
		fn_8019ECCC(frame, fn_8019E8EC(FLD(arg0, void*, 0x288)), 0);
	}
	if (FLD(arg0, void*, 0x28C) != NULL && FLD(arg0, u32, 0x304) != 0) {
		ltm          = fn_8019E8EC(FLD(arg0, void*, 0x28C));
		RwV3d muzzle = lbl_8_rodata_18D8;
		fn_8019941C(&muzzle, &muzzle, 1, ltm);
		SetPosition__11TMachineGunFPC5RwV3d(FLD(arg0, u32, 0x304), &ltm->pos);
		SetAimPosition__11TMachineGunFPC5RwV3d(FLD(arg0, u32, 0x304), &muzzle);
	}
	if (FLD(arg0, void*, 0x280) == NULL) {
		flyerFindBoneFrame(arg0, 0x3EA, &FLD(arg0, void*, 0x280));
	}
	if (FLD(arg0, void*, 0x284) == NULL) {
		flyerFindBoneFrame(arg0, 0x3EB, &FLD(arg0, void*, 0x284));
	}
	if (FLD(FLD(arg0, void*, 0xB0), u32, 0x18) & 0x20000) {
		if (FLD(arg0, u16, 0x106) & 2) {
			FLD(arg0, f32, 0x354) = FLD(arg0, f32, 0x118);
			FLD(arg0, f32, 0x35C) = FLD(arg0, f32, 0x120);
			FLD(arg0, f32, 0x34C) = 1.0f + FLD(arg0, f32, 0x26C);
		} else {
			sAngle shadowAng;
			if (-1000000.0f
			    != (FLD(arg0, f32, 0x34C)
			        = GetShadowPos__FP5RwV3dP6sAnglei(&FLD(arg0, RwV3d, 0x268), &shadowAng, 1))) {
				FLD(arg0, f32, 0x348) = FLD(arg0, f32, 0x268);
				FLD(arg0, f32, 0x34C) += 1.0f;
				FLD(arg0, f32, 0x350) = FLD(arg0, f32, 0x270);
				FLD(arg0, f32, 0x354) = 0.0054931640625f * (f32)shadowAng.x;
				FLD(arg0, f32, 0x35C) = 0.0054931640625f * (f32)shadowAng.z;
			}
		}
		FLD(arg0, f32, 0x358) = 180.0f + 0.0054931640625f * (f32)FLD(arg0, s32, 0x150);
		FLD(arg0, f32, 0x348) = FLD(arg0, f32, 0x268);
		FLD(arg0, f32, 0x350) = FLD(arg0, f32, 0x270);
	}
}
#pragma opt_common_subs reset

void fn_8_A53E4(void* arg0)
{
	u32 temp_r4;
	void* temp_r3;

	if ((void*)M2C_FIELD(arg0, void**, 0x3B4) != NULL) {
		temp_r4 = GetMtnPathMatrix__13TEnemyMtnPathFv((void*)M2C_FIELD(arg0, void**, 0x3B4));
		temp_r3 = M2C_FIELD(arg0, void**, 0xE8);
		if ((temp_r3 != NULL) && (temp_r4 != 0U)) {
			fn_8019ECCC(M2C_FIELD(temp_r3, M2C_UNK**, 4), (RwMatrix*)temp_r4, 0);
		}
		if (((s8)M2C_FIELD(arg0, u8*, 0x246) == 0)
		    && ((s32)((M2C_FIELD(M2C_FIELD(arg0, void**, 0x3B4), s32*, 0x38) & 2) != 0) == 1)) {
			if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x24) == 5) {
				M2C_FIELD(arg0, s32*, 0x3A8) = 1;
			}
			M2C_FIELD(arg0, s32*, 0x25C) = 0x1D;
		}
	}
}

#pragma opt_common_subs off

/* TObjEnemyFlyer::FireWeapon: launches a missile or drops an iron ball from
 * the hook, lets the carried pawn go, or fires the machine gun. */
void fn_8_A4E44(M2C_UNK* arg0)
{
	switch (FLD(arg0, s8, 0x245)) {
		case 2: {
			sFlyerMissile missile;
			missile.pos = FLD(arg0, RwV3d, 0x390);
			flyerHookYaw(arg0, &missile.ang.y);
			missile.maxSpeed = FLD(arg0, f32, 0x24C);
			missile.vel      = FLD(arg0, RwV3d, 0x2EC);
			missile.target   = FLD(arg0, RwV3d, 0x2F8);
			missile.light    = ((TRenderer*)arg0)->Slot90();
			fn_8_A9C6C(&missile);
			FLD(arg0, s32, 0x2E4) = 0;
			if (lbl_8042C388 != 0) {
				fn_800B4A38(lbl_8042C388, 0x401A, (u8*)arg0 + 0x268, NULL, 1, 0, 0);
			}
			break;
		}
		case 4: {
			sFlyerIronBall ball;
			ball.pos = FLD(arg0, RwV3d, 0x390);
			flyerHookYaw(arg0, &ball.ang.y);
			ball.vel   = FLD(arg0, RwV3d, 0x2EC);
			ball.light = ((TRenderer*)arg0)->Slot90();
			fn_8_A8B60(&ball);
			FLD(arg0, s32, 0x2E4) = 0;
			break;
		}
		case 3: {
			FLD(arg0, s8, 0x245) = 0;
			sEnemyCommand cmd;
			cmd.team    = FLD(FLD(arg0, void*, 0xB0), u8, 0x2A);
			cmd.command = 3;
			cmd.id      = FLD(arg0, s32, 0x258);
			cmd.matrix  = FLD(arg0, RwMatrix, 0x360);
			cmd.pos     = FLD(arg0, RwV3d, 0x390);
			flyerHookYaw(arg0, &cmd.ang.y);
			Send__13sEnemyCommandFv(&cmd);
			break;
		}
		case 1:
			if (FLD(arg0, void*, 0x304) != NULL) {
				Run__11TMachineGunFv(FLD(arg0, void*, 0x304));
				if (lbl_8042C388 != 0) {
					fn_800B4A38(lbl_8042C388, 0x4018, (u8*)arg0 + 0x268, arg0, 3, 0, 2);
				}
			}
			break;
	}
}
#pragma opt_common_subs reset

#pragma opt_common_subs off

void fn_8_A4CB0(void* arg0)
{
	flyerCarryPawn(arg0);
}
#pragma opt_common_subs reset

void fn_8_A4B90(M2C_UNK* arg0)
{
	flyerUpdateJetEffect(arg0);
}

void fn_8_A4AC0(void* arg0, RwV3d* dir, sAngle* ang)
{
	f32 len = fn_801991B4(dir);
	if (len > 0.0f) {
		ang->x = (s32)(10430.381f * (f32)asin(-dir->y / len));
		ang->y = (s32)(10430.381f * (f32)atan2(dir->x, dir->z));
		ang->z = 0;
		return;
	}
	ang->x = 0;
	ang->y = 0;
	ang->z = 0;
}

/* Turns a direction into the angles that aim along it, snapping near the
 * poles and the vertical, and flips to the equivalent pose closer to the
 * current one (ang at 0x274/0x27C). */
void fn_8_A4830(void* arg0, RwV3d* dir, sAngle* ang)
{
	s32 x;
	s32 z;

	if (dir->z > 0.9658f || (dir->z > 0.95f && (f32)__fabs(dir->y) < 0.0009f)) {
		ang->x = 0x4000;
		ang->z = 0;
		dir->x = 0.0f;
		dir->y = 0.0f;
		dir->z = 1.0f;
	} else if (dir->z < -0.9658f || (dir->z < -0.95f && (f32)__fabs(dir->y) < 0.0009f)) {
		ang->x = 0xC000;
		ang->z = 0;
		dir->x = 0.0f;
		dir->y = 0.0f;
		dir->z = -1.0f;
	} else if (dir->y > 0.99608f) {
		ang->x = 0;
		ang->z = 0;
		dir->x = 0.0f;
		dir->y = 1.0f;
		dir->z = 0.0f;
	} else if (dir->y < -0.99608f) {
		ang->x = 0x8000;
		ang->z = 0;
		dir->x = 0.0f;
		dir->y = -1.0f;
		dir->z = 0.0f;
	} else {
		ang->x = (s32)(10430.381f * (f32)asin(dir->z));
		ang->z = -(s32)(10430.381f * (f32)atan2(dir->x, dir->y));
	}
	x = ang->x;
	z = ang->z;
	DiffAngle__Fii(M2C_FIELD(arg0, s32*, 0x274), x);
	if (DiffAngle__Fii(M2C_FIELD(arg0, s32*, 0x27C), z) > 0x4000) {
		ang->z = z - 0x8000;
		ang->x = 0x8000 - x;
	}
}

/* TObjEnemyFlyer::CtrlMode: runs the given phase of the current mode's
 * EnemyMD_* handler. */
void CtrlMode__14TObjEnemyFlyerF8ENEMY_MDQ29TObjEnemy10eCtrlSMode(M2C_UNK* arg0, s32 arg1, s32 arg2)
{
	switch (arg1) {
		case 0:
			break;
		case 1:
			fn_8_A4478(arg0, arg2);
			break;
		case 2:
			fn_8_A4394(arg0, arg2);
			break;
		case 32:
			fn_8_A4290(arg0, arg2);
			break;
		case 36:
			fn_8_A4230(arg0, arg2);
			break;
		case 29:
			fn_8_A4140(arg0, arg2);
			break;
	}
}

void fn_8_A4478(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 0;
			return;
		case 3:
			if ((u32)M2C_FIELD(arg0, u32*, 0x3B4) != 0U) {
				SetPath__13TEnemyMtnPathFi(
				    M2C_FIELD(arg0, void**, 0x3B4), M2C_FIELD(arg0, s8*, 0x244));
			}
			return;
	}
}

void fn_8_A4394(void* arg0, s32 arg1)
{
	void* temp_r3;
	u32 temp_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 0;
			return;
		case 1:
			if ((void*)M2C_FIELD(arg0, void**, 0x3B4) != NULL) {
				temp_r4
				    = GetMtnPathMatrix__13TEnemyMtnPathFv((void*)M2C_FIELD(arg0, void**, 0x3B4));
				temp_r3 = M2C_FIELD(arg0, void**, 0xE8);
				if ((temp_r3 != NULL) && (temp_r4 != 0U)) {
					fn_8019ECCC(M2C_FIELD(temp_r3, M2C_UNK**, 4), (RwMatrix*)temp_r4, 0);
				}
				if (((s8)M2C_FIELD(arg0, u8*, 0x246) == 0)
				    && ((s32)((M2C_FIELD(M2C_FIELD(arg0, void**, 0x3B4), s32*, 0x38) & 2) != 0)
				        == 1)) {
					if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x24) == 5) {
						M2C_FIELD(arg0, s32*, 0x3A8) = 1;
					}
					M2C_FIELD(arg0, s32*, 0x25C) = 0x1D;
				}
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_A4290(M2C_UNK* arg0, s32 arg1)
{
	void* temp_r3;
	u32 temp_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2E8) = 0;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			return;
		case 1:
			if ((void*)M2C_FIELD(arg0, void**, 0x3B4) != NULL) {
				temp_r4
				    = GetMtnPathMatrix__13TEnemyMtnPathFv((void*)M2C_FIELD(arg0, void**, 0x3B4));
				temp_r3 = M2C_FIELD(arg0, void**, 0xE8);
				if ((temp_r3 != NULL) && (temp_r4 != 0U)) {
					fn_8019ECCC(M2C_FIELD(temp_r3, M2C_UNK**, 4), (RwMatrix*)temp_r4, 0);
				}
				if (((s8)M2C_FIELD(arg0, u8*, 0x246) == 0)
				    && ((s32)((M2C_FIELD(M2C_FIELD(arg0, void**, 0x3B4), s32*, 0x38) & 2) != 0)
				        == 1)) {
					if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x24) == 5) {
						M2C_FIELD(arg0, s32*, 0x3A8) = 1;
					}
					M2C_FIELD(arg0, s32*, 0x25C) = 0x1D;
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x2E8) == 0) {
				M2C_FIELD(arg0, s32*, 0x2E8) = 1;
				fn_8_A4E44(arg0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_A4230(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			((TRenderer*)arg0)->Slot3C();
			break;
		case 1:
			M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			break;
		case 2:
		case 3:
			break;
	}
}

/* TObjEnemyFlyer::EnemyMD_Destroy: a pawn carrier tells its pawns to drop
 * (command 2) before the flyer explodes; the last phase ends the object. */
void fn_8_A4140(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			if (FLD(arg0, s8, 0x245) == 3) {
				sEnemyCommand cmd;
				cmd.team    = FLD(FLD(arg0, void*, 0xB0), u8, 0x2A);
				cmd.command = 2;
				cmd.id      = FLD(arg0, s32, 0x258);
				cmd.sender  = FLD(arg0, s32, 0x230);
				Send__13sEnemyCommandFv(&cmd);
			}
			((TRenderer*)arg0)->Slot3C();
			break;
		case 1:
			FLD(arg0, u16, 4) |= 1;
			break;
		case 2:
		case 3:
			break;
	}
}

#pragma opt_common_subs off

/* TObjEnemyFlyer::Update */
void Update__14TObjEnemyFlyerFv(M2C_UNK* arg0)
{
	FLD(arg0, BOOL, 0x3A0) = flyerIsPlaying();
	FLD(arg0, BOOL, 0x3A4) = FLD(lbl_8042C180, s8, 0x1F) != 0 ? FALSE : TRUE;
	if (FLD(arg0, void*, 0xE8) != NULL) {
		fn_8019EE04(FLD(FLD(arg0, void*, 0xE8), s32, 4));
	}
	fn_800A5B34(arg0);
	((TRenderer*)arg0)->Slot38();
	if (FLD(arg0, void*, 0x240) != NULL) {
		((TSubDispatch*)FLD(arg0, void*, 0x240))->vslot3(arg0);
	}
	((TRenderer*)arg0)->Slot50(FLD(arg0, s32, 0x19C), 1);
	fn_8_A549C(arg0);
	fn_800A3D48(arg0);
	flyerUpdateJetEffect(arg0);
	if (FLD(arg0, s8, 0x245) == 3 && FLD(arg0, s32, 0x19C) != 0x1D) {
		flyerCarryPawn(arg0);
	} else if (FLD(arg0, void*, 0x288) != NULL) {
		FLD(arg0, RwMatrix, 0x360) = *fn_8019E8EC(FLD(arg0, void*, 0x288));
	}
	if (FLD(arg0, s32, 0x19C) != 1 && fn_80017800(arg0) != 0 && FLD(arg0, void*, 0x38) != NULL) {
		FLD(arg0, RwV3d, 0xA4)  = FLD(arg0, RwV3d, 0x88);
		FLD(arg0, RwV3d, 0x88)  = FLD(arg0, RwV3d, 0x268);
		FLD(arg0, sAngle, 0x94) = FLD(arg0, sAngle, 0x14C);
		Entry__7C_COLLIFv((u8*)arg0 + 0x28);
	}
}
#pragma opt_common_subs reset

#pragma opt_common_subs off

/* TObjEnemyFlyer::SetParameter: the placement's position, angle and
 * parameters, and the path's frame. */
void UpdateOnEdit__14TObjEnemyFlyerFv(void* arg0)
{
	RwMatrix m;
	FlyerParam* param = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), FlyerParam**, 0x2C);
	f32 sine;

	FLD(arg0, RwV3d, 0x140)  = FLD(M2C_FIELD(arg0, void**, 0xB0), RwV3d, 0);
	FLD(arg0, sAngle, 0x14C) = FLD(M2C_FIELD(arg0, void**, 0xB0), sAngle, 0xC);
	FLD(arg0, RwV3d, 0x1C0)  = FLD(arg0, RwV3d, 0x140);
	FLD(arg0, RwV3d, 0x1CC)  = FLD(arg0, RwV3d, 0x140);
	FLD(arg0, RwV3d, 0x1C0)  = FLD(arg0, RwV3d, 0x140);
	FLD(arg0, f32, 0x1B8)    = 1.5f;
	FLD(arg0, s8, 0x245)     = param->kind;
	FLD(arg0, s8, 0x244)     = param->pathNum;
	FLD(arg0, s8, 0x246)     = param->pathType;
	FLD(arg0, f32, 0x248)    = param->moveSpeed;
	FLD(arg0, f32, 0x24C)    = param->weaponSpeed;
	FLD(arg0, s32, 0x250)    = param->weaponAngleX;
	FLD(arg0, s32, 0x254)    = param->attackInterval;
	FLD(arg0, s32, 0x258)    = param->unk14;
	fn_8_A549C(arg0);
	if (FLD(arg0, void*, 0x3B4) != NULL) {
		sine = fn_800D7B00(FLD(arg0, s32, 0x150));
		fn_80195790(&m, (RwV3d*)&AxisY, 1.0f - fn_800D7AE4(FLD(arg0, s32, 0x150)), sine, 0);
		fn_80196050(&m, &FLD(arg0, RwV3d, 0x140), 2);
		FLD(FLD(arg0, void*, 0x3B4), RwMatrix, 0x7C) = m;
		FLD(FLD(arg0, void*, 0x3B4), f32, 0x34)      = FLD(arg0, f32, 0x248);
		ChangePath__13TEnemyMtnPathFi(FLD(arg0, void*, 0x3B4), FLD(arg0, s8, 0x244));
	}
}
#pragma opt_common_subs reset

void DispOpaq__14TObjEnemyFlyerFv(void* arg0)
{
	((TRenderer*)arg0)->Slot90();
	SetLightNum__7nRenderFUi();
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0xE8));
	if (((s32)M2C_FIELD(arg0, s32*, 0x2E4) != 0) && ((u32)M2C_FIELD(arg0, u32*, 0x2A0) != 0U)) {
		fn_8014FF2C(M2C_FIELD(arg0, s32*, 0x2A0));
	}
}

void DispTrans__14TObjEnemyFlyerFv(void* arg0)
{
	((TRenderer*)arg0)->Slot90();
	SetLightNum__7nRenderFUi();
	SaveRenderState__7nRenderFv();
	SetRenderStateForBlendAdd__7nRenderFv();
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0x294));
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0x298));
	LoadRenderState__7nRenderFv();
}

/* Draws the shadow, fading it out with the height above the ground. */
void DispShadow__14TObjEnemyFlyerFv(void* arg0)
{
	static const f32 minAlpha = 0.2f;
	static const f32 maxAlpha = 1.0f;
	f32 alpha;

	fn_800B7864(4);
	RwV3d size = lbl_8_rodata_18F0;
	alpha      = 1.0f - 0.004f * (FLD(arg0, f32, 0x144) - FLD(arg0, f32, 0x34C));
	alpha      = flyerClamp(alpha, minAlpha, maxAlpha);
	fn_800B719C((u8*)arg0 + 0x348, (u8*)arg0 + 0x354, &size, alpha);
	fn_800B7820();
}

/* Debug display of the flight path, drawn in the path's frame. */
void DispOpaqOnEdit__14TObjEnemyFlyerFv(void* arg0)
{
	RwMatrix m;

	if (M2C_FIELD(arg0, void**, 0x260) != NULL) {
		fn_80195A74(&m, (RwV3d*)&AxisZ, 0.0054931640625f * (f32)M2C_FIELD(arg0, s32*, 0x154), 0);
		fn_80195A74(&m, (RwV3d*)&AxisX, 0.0054931640625f * (f32)M2C_FIELD(arg0, s32*, 0x14C), 2);
		fn_80195A74(
		    &m, (RwV3d*)&AxisY, 180.0f + 0.0054931640625f * (f32)M2C_FIELD(arg0, s32*, 0x150), 2);
		fn_80196050(&m, (RwV3d*)((u8*)arg0 + 0x140), 2);
		fn_8_A9E94(M2C_FIELD(arg0, u32*, 0x260), &m);
	}
}

s32 CheckCameraFrustumTest__14TObjEnemyFlyerFPC5RwV3df(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x19C) == 1) {
		return 0;
	}
	return CheckCameraFrustumTest__9TObjEnemyFPC5RwV3df(arg0, (u8*)arg0 + 0x268, 30.0f);
}

s32 CheckCameraFrustumTestForShadow__14TObjEnemyFlyerFPC5RwV3df(void)
{
	return 0;
}

/* TObjEnemyFlyer::Explosion: the destroyed flyer's effects, sound and
 * falling wreck. */
void Explosion__14TObjEnemyFlyerFv(void* arg0)
{
	u32 clump;

	FLD(arg0, u32, 0x188) |= 0x200;
	if (FLD(arg0, u32, 0x188) & 0x10) {
		RwV3d pos  = FLD(arg0, RwV3d, 0x268);
		sAngle ang = FLD(arg0, sAngle, 0x14C);
		/* Retail tests the flag again here; the compiler reuses the first
		 * test's condition register. */
		if (!(FLD(arg0, u32, 0x188) & 0x10)) {
			return;
		}
		fn_8006298C(6, &pos, &ang);
		fn_8006298C(2, &pos, &ang);
		if (lbl_8042C388 != 0) {
			fn_800B4A38(lbl_8042C388, 0xE017, &pos, NULL, 1, 2, 0);
		}
		fn_8006298C(0xF, &pos, &ang);
		if (mpDataBase__14TEnemyDataBase == 0 && __nw__FUl(0x70) != NULL) {
			__ct__14TEnemyDataBaseFv();
		}
		clump
		    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0, 5);
		if (clump != 0) {
			RwV3d up = lbl_8_rodata_18C0;
			ang.y += 0x8000;
			SetEffectCrash3D_R__FP7TObjectP5RwV3dP6sAngleP5RwV3dP5RwV3dffisP7RpClump(
			    lbl_8042C2A0, &pos, &ang, &up, NULL, 1.2f, 0.0f, 0, 0, clump);
		}
	}
}

s32 fn_8_A35BC(void* arg0)
{
	if ((s8)M2C_FIELD(arg0, u8*, 0x245) != 1) {
		return 1;
	}
	return M2C_FIELD(arg0, s32*, 0x254);
}

s32 fn_8_A353C(void* arg0)
{
	f32 temp_f1;
	s32 var_r31;

	var_r31 = 0;
	temp_f1 = M2C_FIELD(arg0, f32*, 0x1A4);
	if (temp_f1 != M2C_FIELD(arg0, f32*, 0x3BC)) {
		M2C_FIELD(arg0, f32*, 0x3BC) = temp_f1;
		if ((u32)M2C_FIELD(arg0, u32*, 0x3B8) != 0U) {
			On__13TEnemyIconManFff(
			    M2C_FIELD(arg0, u32*, 0x3B8), temp_f1, M2C_FIELD(arg0, f32*, 0x3C0));
		}
		var_r31 = 1;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x3B8) != 0U) {
		SetPos__13TEnemyIconManFPC5RwV3dPC5RwV3d(
		    M2C_FIELD(arg0, u32*, 0x3B8), (u8*)arg0 + 0x268, (s32*)lbl_8_rodata_18CC);
	}
	return var_r31;
}

/* TObjEnemyFlyer::RcvCommand: commands of kind 5 addressed to this flyer's
 * id request a mode change (0x25C), the fourth with a target position. */
void RcvCommand__14TObjEnemyFlyerFP13sEnemyCommand(void* arg0, void* arg1)
{
	if (FLD(arg1, u8, 0) == 5 && FLD(arg1, s32, 0x14) == FLD(arg0, s32, 0x258)) {
		switch (FLD(arg1, u32, 4)) {
			case 0:
				break;
			case 1:
				FLD(arg0, s32, 0x25C) = 2;
				break;
			case 2:
				FLD(arg0, s32, 0x25C) = 1;
				break;
			case 3:
				FLD(arg0, s32, 0x25C) = 0x20;
				break;
			case 4:
				FLD(arg0, RwV3d, 0x2F8) = FLD(arg1, RwV3d, 8);
				FLD(arg0, s32, 0x25C)   = 0x20;
				break;
			case 5:
				FLD(arg0, s32, 0x25C) = 0x20;
				break;
			case 6:
				FLD(arg0, s32, 0x25C) = 0x20;
				break;
		}
	}
}

void AddScore__14TObjEnemyFlyerFv(void* arg0)
{
	if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
		CreateInstance__14TEnemyScoreManFv();
	}
	AddScore__14TEnemyScoreManFii(
	    EnemyScoreMan__14TEnemyScoreMan, M2C_FIELD(arg0, s32*, 0x230), 0xC8);
}

void AddItemBox__14TObjEnemyFlyerFP5RwV3d(void* arg0, s32 arg1)
{
	CreateItemBox__8nItemBoxFP5RwV3d(arg1);
}

#pragma opt_common_subs off

void DestroyMyself__14TObjEnemyFlyerFv(void* arg0)
{
	void* temp_r30;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	s32 temp_r0_2;
	u8 temp_r0;

	if (fn_800A2D50() != 0) {
		temp_r3                        = M2C_FIELD(arg0, void**, 0xB0);
		M2C_FIELD(temp_r3, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3, s32*, 0x18) | 0x01000000);
	}
	((TRenderer*)arg0)->Slot7C();
	temp_r0 = M2C_FIELD(lbl_8042C180, u8*, 0x24);
	if ((((s8)temp_r0 == 4) || ((s8)temp_r0 == 8))
	    && (((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 4)
	        || ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 5))) {
		temp_r3_2                        = M2C_FIELD(arg0, void**, 0xB0);
		M2C_FIELD(temp_r3_2, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3_2, s32*, 0x18) | 0x10000000);
		temp_r3_3                        = M2C_FIELD(arg0, void**, 0xB0);
		M2C_FIELD(temp_r3_3, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3_3, s32*, 0x18) | 0x200);
	}
	SetEnd__10TObjSetObjFv((u8*)((u32)arg0 + 0xB0));
	((TRenderer*)arg0)->Slot40();
	temp_r0_2 = M2C_FIELD(arg0, s32*, 0x230);
	if (temp_r0_2 != -1) {
		temp_r3_4 = lbl_802AD070[temp_r0_2];
		if (temp_r3_4 != NULL) {
			temp_r30 = lbl_80303DC8[(s8)M2C_FIELD(temp_r3_4, u8*, 0x9BC)];
			if (temp_r30 != NULL) {
				Entry__18TEnemyPowerCoreManFPC5RwV3di(GetInstance__18TEnemyPowerCoreManFv(),
				    (u8*)arg0 + 0x140,
				    ((s8*)((u8*)temp_r30 + 0x110))[((FlyerPlayerTeam*)temp_r30)->leader]);
				((TRenderer*)arg0)->Slot88((u8*)arg0 + 0x140);
			}
		}
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x230) != -1) {
		if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
			CreateInstance__14TEnemyScoreManFv();
		}
		DestroyEnemy__14TEnemyScoreManFi(
		    EnemyScoreMan__14TEnemyScoreMan, M2C_FIELD(arg0, s32*, 0x230));
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x3A8) == 0) {
		if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
			CreateInstance__14TEnemyScoreManFv();
		}
		fn_8011C0E8(EnemyScoreMan__14TEnemyScoreMan);
	}
}
#pragma opt_common_subs reset
}
