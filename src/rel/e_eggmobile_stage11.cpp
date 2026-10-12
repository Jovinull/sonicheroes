#include "types.h"

// stage11D's TObjEnemyEggMobile and the TZakoRushCtrl helper object
// ("TObjEnemyEggMobile", "TZakoRushCtrl" and "EGGMOBILE OBJECT" are this
// unit's strings; the functions keep their address names). The strategy it
// runs is rel/e_eggmobile_strategy_stage11.cpp. fn_8_A2454 is the module's
// static initialiser (.ctors).
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

/* Retail builds this module without fused multiply-adds. */
#pragma fp_contract off

typedef s32 M2C_UNK;
typedef struct HAnimClass HAnimClass;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)

typedef struct EggObject {
	/* 0x000 */ const char* unk0; /* inferred */
	/* 0x004 */ char pad4[0x14];  /* maybe part of unk0[6]? */
	/* 0x018 */ M2C_UNK* unk18;   /* inferred */
	/* 0x01C */ char pad1C[2];
	/* 0x01E */ s16 unk1E;         /* inferred */
	/* 0x020 */ char pad20[8];     /* maybe part of unk1E[5]? */
	/* 0x028 */ s32 unk28;         /* inferred */
	/* 0x02C */ s32 unk2C;         /* inferred */
	/* 0x030 */ s32 unk30;         /* inferred */
	/* 0x034 */ s8 unk34;          /* inferred */
	/* 0x035 */ char pad35[0x7B];  /* maybe part of unk34[0x7C]? */
	/* 0x0B0 */ void* unkB0;       /* inferred */
	/* 0x0B4 */ void* unkB4;       /* inferred */
	/* 0x0B8 */ char padB8[0x1C];  /* maybe part of unkB4[8]? */
	/* 0x0D4 */ s32 unkD4;         /* inferred */
	/* 0x0D8 */ char padD8[0xC];   /* maybe part of unkD4[4]? */
	/* 0x0E4 */ M2C_UNK* unkE4;    /* inferred */
	/* 0x0E8 */ void* unkE8;       /* inferred */
	/* 0x0EC */ char padEC[0x54];  /* maybe part of unkE8[0x16]? */
	/* 0x140 */ f32 unk140;        /* inferred */
	/* 0x144 */ f32 unk144;        /* inferred */
	/* 0x148 */ f32 unk148;        /* inferred */
	/* 0x14C */ s32 unk14C;        /* inferred */
	/* 0x150 */ s32 unk150;        /* inferred */
	/* 0x154 */ s32 unk154;        /* inferred */
	/* 0x158 */ f32 unk158;        /* inferred */
	/* 0x15C */ f32 unk15C;        /* inferred */
	/* 0x160 */ f32 unk160;        /* inferred */
	/* 0x164 */ char pad164[0x1C]; /* maybe part of unk160[8]? */
	/* 0x180 */ s32 unk180;        /* inferred */
	/* 0x184 */ char pad184[0x18]; /* maybe part of unk180[7]? */
	/* 0x19C */ s32 unk19C;        /* inferred */
	/* 0x1A0 */ char pad1A0[0x20]; /* maybe part of unk19C[9]? */
	/* 0x1C0 */ f32 unk1C0;        /* inferred */
	/* 0x1C4 */ f32 unk1C4;        /* inferred */
	/* 0x1C8 */ f32 unk1C8;        /* inferred */
	/* 0x1CC */ f32 unk1CC;        /* inferred */
	/* 0x1D0 */ f32 unk1D0;        /* inferred */
	/* 0x1D4 */ f32 unk1D4;        /* inferred */
	/* 0x1D8 */ char pad1D8[0x68]; /* maybe part of unk1D4[0x1B]? */
	/* 0x240 */ void** unk240;     /* inferred */
	/* 0x244 */ s32 unk244;        /* inferred */
	/* 0x248 */ u32 unk248;        /* inferred */
	/* 0x24C */ f32 unk24C;        /* inferred */
	/* 0x250 */ f32 unk250;        /* inferred */
	/* 0x254 */ f32 unk254;        /* inferred */
	/* 0x258 */ f32 unk258;        /* inferred */
	/* 0x25C */ f32 unk25C;        /* inferred */
	/* 0x260 */ s32 unk260;        /* inferred */
	/* 0x264 */ s32 unk264;        /* inferred */
	/* 0x268 */ s32 unk268;        /* inferred */
	/* 0x26C */ s32 unk26C;        /* inferred */
	/* 0x270 */ char pad270[4];
	/* 0x274 */ s32 unk274;       /* inferred */
	/* 0x278 */ s32 unk278;       /* inferred */
	/* 0x27C */ void* unk27C;     /* inferred */
	/* 0x280 */ void* unk280;     /* inferred */
	/* 0x284 */ void* unk284;     /* inferred */
	/* 0x288 */ u32 unk288;       /* inferred */
	/* 0x28C */ char pad28C[0xC]; /* maybe part of unk288[4]? */
	/* 0x298 */ s32 unk298;       /* inferred */
	/* 0x29C */ s32 unk29C;       /* inferred */
	/* 0x2A0 */ s32 unk2A0;       /* inferred */
	/* 0x2A4 */ void* unk2A4;     /* inferred */
	/* 0x2A8 */ void* unk2A8;     /* inferred */
	/* 0x2AC */ void* unk2AC;     /* inferred */
	/* 0x2B0 */ void** unk2B0;    /* inferred */
} EggObject;                      /* size >= 0x2B4 */

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

/* PATHINFO: where a path puts a point at a given distance along it. */
struct PathInfo {
	u8 pad00[0x10];
	f32 dist;  /* 0x10 */
	RwV3d pos; /* 0x14 */
	u8 pad20[0x24];
};

/* A pointer to a TZakoRushCtrl handler in the compiler's layout: {this
 * adjustment, vtable offset (-1: not virtual), function}. */
struct EggPtmf {
	s32 word[3];
};

struct Stage11AnimRecord {
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

struct _struct_lbl_8_rodata_17F4_0xC {
	/* 0x0 */ f32 unk0; /* inferred */
	/* 0x4 */ f32 unk4; /* inferred */
	/* 0x8 */ f32 unk8; /* inferred */
}; /* size = 0xC */

/* Dispatch view of the object handed to the state jumptable: retail reads the
 * vtable through the incoming `this` in r3 and calls the slot with the state
 * argument in r4, so the call has to go through a class. Slot numbers are the
 * retail vtable offsets, and the two implicit destructor slots occupy 0 and 4. */
class TSubDispatch
{
public:
	virtual void vslot2(M2C_UNK);
	virtual void vslot3(void*);
};

class TStateDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void Slot18(s32);
	virtual void Slot1C(s32);
	virtual void Slot20(s32);
	virtual void Slot24(s32);
	virtual void Slot28(s32);
	virtual void Slot2C(s32);
	virtual void Slot30(s32);
	virtual void Slot34(s32);
	virtual void Slot38(s32);
	virtual void Slot3C(s32);
	virtual void Slot40(s32);
	virtual void Slot44(s32);
	virtual void Slot48(s32);
	virtual void Slot4C(s32);
	virtual void Slot50(s32);
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

class TObjEnemyEggMobile : public TObjEnemy
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);
	virtual ~TObjEnemyEggMobile();
	virtual void CtrlMode(ENEMY_MD, eCtrlSMode);
	virtual void Update();
	virtual void UpdateOnEdit();
	virtual void DispOpaq();
	virtual void DispTrans();
	virtual void KillMySelf();
	virtual s32 CheckCameraFrustumTest(const RwV3d*, f32);
	virtual void AddScore();
	virtual s32 IsSleep();
	virtual void AddItemBox(RwV3d*);
	virtual void RcvCommand(sEnemyCommand*);
};

extern "C" {
void* __ct__10HAnimClassFv(void* self);                             /* extern */
void* __ct__7TObjectFP7TObject(EggObject* self, EggObject* arg0);   /* extern */
M2C_UNK __dl__FPv(void* arg0);                                      /* extern */
void* __dt__10HAnimClassFv(void* self, s16 destroyFlag);            /* extern */
void* __dt__7TObjectFv(EggObject* self, s16 destroyFlag);           /* extern */
M2C_UNK __dt__11ENEMYMTNMANFv(void*, M2C_UNK);                      /* extern */
M2C_UNK Free__9THeapCtrlFPv(s32, EggObject*);                       /* extern */
EggObject* Malloc__9THeapCtrlFUi(s32, M2C_UNK);                     /* extern */
M2C_UNK fn_80018C4C(M2C_UNK*);                                      /* extern */
M2C_UNK fn_80018C64(M2C_UNK*);                                      /* extern */
s32 fn_80018C98();                                                  /* extern */
M2C_UNK fn_80019898(M2C_UNK*, M2C_UNK);                             /* extern */
M2C_UNK fn_8003C640(void*);                                         /* extern */
void* __nw__FUl(u32);                                               /* extern */
s32 CheckMustKill__10TObjSetObjFv(s32);                             /* extern */
M2C_UNK SetEnd__10TObjSetObjFv(void*);                              /* extern */
M2C_UNK SetClumpCustomFXTexture__FP7RpClumpP8UVFXInfo(u32*);        /* extern */
M2C_UNK objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(void*); /* extern */
M2C_UNK objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(
    u32, M2C_UNK);                        /* extern */
s32 fn_800A2BE0(void*, u8);               /* extern */
M2C_UNK fn_800A31B8(void*, s32);          /* extern */
M2C_UNK fn_800A3D48(void*);               /* extern */
s32 fn_800A3ED4(void*);                   /* extern */
s32 fn_800A5A54(void*);                   /* extern */
s32 fn_800A6334(void*);                   /* extern */
M2C_UNK fn_800A7088(EggObject*, M2C_UNK); /* extern */
void fn_800A714C(void*, void*);           /* TObjEnemy::TObjEnemy(EggObject*) */
struct PathInfo;
s32 GetStatusOnPath__FP7PATHTAGP8PATHINFO(void*, PathInfo*);                /* extern */
M2C_UNK fn_800B4A38(u32, M2C_UNK, void*, void*, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK fn_800CCC6C(const char*);                                           /* extern */
s32 AdjustAngle__Fiii(s32, s32, s32);                                       /* extern */
f32 fn_800D7B00(s32);                                                       /* extern */
M2C_UNK fn_800F46B0(void*);                                                 /* extern */
M2C_UNK ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*); /* extern */
M2C_UNK LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*);                                                             /* extern */
void* __ct__11ENEMYMTNMANFv(void*);                                                 /* extern */
M2C_UNK UpdateMotion__11ENEMYMTNMANFv(void*);                                       /* extern */
s32 SearchCameraMotion__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK); /* extern */
u32 SearchUVAnim__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK);       /* extern */
u32 SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK); /* extern */
u32 SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK Delete__14TEnemyDataBaseF14eEnemyDataBase(u32, M2C_UNK);                    /* extern */
M2C_UNK Add__14TEnemyDataBaseF14eEnemyDataBasePc(u32, M2C_UNK, const void*);        /* extern */
M2C_UNK __ct__14TEnemyDataBaseFv();                                                 /* extern */
s32 IsExistSummonEnemy__19nEnemyCommunicationFUc(u8);                               /* extern */
s32 IsAnnihilated__19nEnemyCommunicationFUc(u8);                                    /* extern */
s32 fn_80103178(M2C_UNK);                                                           /* extern */
M2C_UNK fn_80111260(void*, M2C_UNK, M2C_UNK);                                       /* extern */
M2C_UNK SetLightNum__7nRenderFUi(M2C_UNK);                                          /* extern */
M2C_UNK SetRenderStateForBlendAdd__7nRenderFv();                                    /* extern */
M2C_UNK LoadRenderState__7nRenderFv();                                              /* extern */
M2C_UNK SaveRenderState__7nRenderFv();                                              /* extern */
void* SearchFrameFromFrameID__11nRenderWareFP7RwFramei(s32, s32);                   /* extern */
M2C_UNK fn_8011B844(u32, f32);                                                      /* extern */
M2C_UNK fn_8012D9D0();                                                              /* extern */
s32 fn_8012DA08();                                                                  /* extern */
M2C_UNK Create__12TEnemySummonFUc(u8);                                              /* extern */
f32 fn_80132958(M2C_UNK);                                                           /* extern */
M2C_UNK fn_801329AC();                                                              /* extern */
M2C_UNK fn_80133090(M2C_UNK*, M2C_UNK*);                                            /* extern */
M2C_UNK DecreaseTimer__7nSystemFRi(void*);                                          /* extern */
M2C_UNK fn_8014FF2C(u32);                                                           /* extern */
M2C_UNK fn_8014FFBC(u32, M2C_UNK*, u32*);                                           /* extern */
void* fn_80150588(void*);                                                           /* extern */
M2C_UNK fn_80150958(void*);                                                         /* extern */
M2C_UNK fn_80194234(M2C_UNK, M2C_UNK);                                              /* extern */
void* fn_8019E8EC(void*);                                                           /* extern */
void fn_8019EB94(s32, RwV3d*, s32);       /* RwFrameTranslate */
M2C_UNK fn_8019ECCC(s32, void*, M2C_UNK); /* extern */
void fn_8019ED68(s32, RwV3d*, f32, s32);  /* RwFrameRotate */

s32 rand();                    /* extern */
s32 fn_8_9832C(s32);           /* extern */
s32 fn_8_98464(u32);           /* extern */
M2C_UNK fn_8_98480(void*);     /* extern */
M2C_UNK fn_8_9897C();          /* extern */
s32 fn_8_98B08(u32);           /* extern */
s32 fn_8_98B94(u32);           /* extern */
M2C_UNK fn_8_9D81C(s32);       /* extern */
void fn_8_A2A00(void*, void*); /* TEnemyFlyer_Strategy setup (rel/e_flyer_stage11.cpp) */
void fn_8_A2A78(void*, void*);
void* fn_8_A31D4(void*);                       /* TEnemyFlyer_Strategy::TEnemyFlyer_Strategy() */
M2C_UNK EventRewind__12EventManagerFv(u32);    /* extern */
M2C_UNK EventStart__12EventManagerFv(u32);     /* extern */
s32 Exist__12EventManagerFv(u32);              /* extern */
M2C_UNK fn_8_D8E90(M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
}
extern M2C_UNK SetAtomicCustomFXData__FP8RpAtomicPv;
extern RwV3d AxisY;
extern M2C_UNK lbl_8029BBD0;
extern M2C_UNK lbl_8029C310;
extern void* lbl_80303DC8;
extern EggObject* lbl_8042C0FC;
extern EggObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C380;
extern u32 lbl_8042C388;
extern u32 mpDataBase__14TEnemyDataBase;
extern void* lbl_8042C610;
extern u32 lbl_8042C6E4;
extern "C" {
/* The module's data, defined where retail emits it (around the one switch
 * table, fn_8_9E924's). */
extern void* lbl_8_data_15A70[21];
extern void* lbl_8_data_15B0C[6];
extern void* lbl_8_data_15B24[21];
extern u32 lbl_8_data_15B78[6];
extern const char* lbl_8_data_15DC0;
extern const char* lbl_8_data_15DD8;
extern const char* lbl_8_data_15E4C;
extern void* lbl_8_data_15E50[11];
extern char lbl_8_data_15E7C[];
extern char lbl_8_data_15E8C[];
extern char lbl_8_data_15EA4[];
extern void* __vt__18TObjEnemyEggMobile[];
extern EggPtmf lbl_8_data_15DDC;
extern EggPtmf lbl_8_data_15DE8;
extern EggPtmf lbl_8_data_15DF4;
extern EggPtmf lbl_8_data_15E00;
extern EggPtmf lbl_8_data_15E0C[4];
}
static u32 lbl_8_bss_18A8[7];
static u32 lbl_8_bss_18C4;
static u32 lbl_8_bss_18C8[0x11];
static s32 lbl_8_bss_190C;
static s32 lbl_8_bss_1910;
static EggObject* lbl_8_bss_1914;
/* The {0, 1.5, 0} vector the stage 11 object units carry unreferenced at the
 * head of their .rodata (see e_capture_collision_stage11.cpp). */
#pragma force_active on
static const f32 lbl_8_rodata_17D0[3] = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset
extern const RwV3d lbl_8_rodata_17DC                                   = { 0.0f, 0.0f, 0.0f };
extern const s32 lbl_8_rodata_17E8[3]                                  = { 0xDAE, 0xDAF, 0xDB0 };
extern const struct _struct_lbl_8_rodata_17F4_0xC lbl_8_rodata_17F4[6] = {
	{ 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f },
	{ 10000.0f, 0.0f, 0.0f },
	{ 10000.0f, -500.0f, -4000.0f },
	{ 0.0f, 0.0f, -4000.0f },
	{ 0.0f, 0.0f, -8000.0f },
}; /* const */
/* The egg mobile's start position and angle, the second pair for stage 0x15. */
extern const RwV3d lbl_8_rodata_183C[2]  = { { 0.0f, 20.0f, -179.0f }, { 0.0f, 75.0f, -179.0f } };
extern const sAngle lbl_8_rodata_1854[2] = { { 0, 0x8000, 0 }, { 0, 0x8000, 0 } };
extern const f32 lbl_8_rodata_186C[2]    = { 1.622367668789107e-36f, 9.698406850289945e-38f };

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

extern "C" {

u32 lbl_8_data_15B78[6] = { 0x3F800000, 0, 0, 0, 1, 0 };

char lbl_8_data_15B90[]               = "eggmovile01.anm";
char lbl_8_data_15BA0[]               = "eggmovile_idle.anm";
char lbl_8_data_15BB4[]               = "en_eggmovile.anm";
char lbl_8_data_15BC8[]               = "en_bsz1_egmbl.anm";
char lbl_8_data_15BDC[]               = "en_bsz2_egmbl.anm";
Stage11AnimRecord lbl_8_data_15BF0[7] = {
	{ 0, 0xB, 3, 0, 0xBF800000, 0x3F800000, 0x3F800000, lbl_8_data_15B90, 2 },
	{ 0, 4, 0, 0, 0xBF800000, 0x3F800000, 0x3F800000, lbl_8_data_15B90, 2 },
	{ 0, 3, 3, 0, 0xBF800000, 0x3F800000, 0x3F800000, lbl_8_data_15BA0, 3 },
	{ 0, 3, 3, 0, 0xBF800000, 0x3F800000, 0x3F800000, lbl_8_data_15BB4, 0xF },
	{ 0, 5, 3, 0, 0x43B38000, 0x3F800000, 0x3F800000, lbl_8_data_15BC8, 5 },
	{ 0, 5, 3, 0, 0xBF800000, 0x3F800000, 0x3F800000, lbl_8_data_15BDC, 8 },
	{ 0, 0xE, 0, 0, 0, 0, 0, NULL, 0 },
};
char lbl_8_data_15CEC[]               = "en_eggman.anm";
char lbl_8_data_15CFC[]               = "en_bsz1_egman.anm";
char lbl_8_data_15D10[]               = "en_bsz2_egman.anm";
Stage11AnimRecord lbl_8_data_15D24[4] = {
	{ 0, 3, 0, 0, 0xBF800000, 0x3F800000, 0x3F800000, lbl_8_data_15CEC, 0xC },
	{ 0, 4, 0, 0, 0xBF800000, 0x3F800000, 0x3F800000, lbl_8_data_15CFC, 4 },
	{ 0, 4, 0, 0, 0xBF800000, 0x3F800000, 0x3F800000, lbl_8_data_15D10, 7 },
	{ 0, 0xE, 0, 0, 0, 0, 0, NULL, 0 },
};

char lbl_8_data_15DB4[]      = "MOVE SPEED";
const char* lbl_8_data_15DC0 = lbl_8_data_15DB4;
char lbl_8_data_15DC4[]      = "TObjEnemyEggMobile";
const char* lbl_8_data_15DD8 = lbl_8_data_15DC4;

/* Pointers to the four TZakoRushCtrl handlers ({this adjustment, vtable
 * offset, function}, the compiler's layout); fn_8_A2454 copies them into the
 * table at 15E0C. */
void fn_8_9ED60(void* arg0, s32 arg1);
void fn_8_9ED10(void* arg0, s32 arg1);
void fn_8_9EC40(void* arg0, s32 arg1);
void fn_8_9EBB8(void* arg0, s32 arg1);
EggPtmf lbl_8_data_15DDC = { { 0, -1, (s32)fn_8_9ED60 } };
EggPtmf lbl_8_data_15DE8 = { { 0, -1, (s32)fn_8_9ED10 } };
EggPtmf lbl_8_data_15DF4 = { { 0, -1, (s32)fn_8_9EC40 } };
EggPtmf lbl_8_data_15E00 = { { 0, -1, (s32)fn_8_9EBB8 } };
#pragma explicit_zero_data on
EggPtmf lbl_8_data_15E0C[4] = { 0 };
#pragma explicit_zero_data reset

char lbl_8_data_15E3C[]      = "TZakoRushCtrl";
const char* lbl_8_data_15E4C = lbl_8_data_15E3C;

void fn_8_9EDB0(void);
void fn_8_9EDB4(void*);
EggObject* fn_8_9EE60(EggObject*, s16);
void Disp__7TObjectFv();
void PDisp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Error__7TObjectFPc();
void Render__7TObjectFv();
void* lbl_8_data_15E50[11] = {
	NULL,
	NULL,
	(void*)fn_8_9EE60,
	(void*)fn_8_9EDB4,
	(void*)Disp__7TObjectFv,
	(void*)fn_8_9EDB0,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
};

char lbl_8_data_15E7C[] = "SNG_STG22.adx";
char lbl_8_data_15E8C[] = "en_eggmobile_stg25.one";
char lbl_8_data_15EA4[] = "en_eggmobile_stg22.one";

/* The game-mode test the objects' Exec start with: the 2P modes (1 and 2)
 * and mode 3 end the object at once. Retail compiles it with C++ bool. */
#pragma bool on
static inline bool eggIsVersusMode(s32 mode)
{
	return mode == 1 || mode == 2;
}

static inline bool eggIsObjectOffMode()
{
	s32 mode = M2C_FIELD(&lbl_8029C310, s32*, 0x18);
	return eggIsVersusMode(mode) || mode == 3;
}
#pragma bool reset

static inline BOOL eggKillMyself()
{
	return eggIsObjectOffMode();
}

class TZakoRushCtrl
{
};

typedef void (TZakoRushCtrl::*ZakoRushHandler)(s32);

/* The talk system behind lbl_8042C610: idle when nothing plays or waits. */
#pragma bool on
struct EggTalkMan {
	u8 pad00[0x30];
	s32 playing; /* 0x30 */
	u8 pad34[0x8];
	s32 queued; /* 0x3C */
	u8 pad40[0x18];
	s32 next; /* 0x58 */

	bool IsIdle() { return playing == 0 && queued == 0 && next == -1; }
};
#pragma bool reset

/* The frames the egg mobile's effects hang from. */
struct EggFrameView {
	u8 pad000[0x298];
	void* exhaust[3]; /* 0x298 */
	void* effect[3];  /* 0x2A4 */
};

/* TObjEnemyEggMobile::SetPosition: places the model, facing back in modes
 * 1, 2 and 0x43, and finds the frames the effects hang from. */
static inline void eggSetPosition(void* arg0)
{
	s32 frame;
	s32 i;

	if (M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		frame = M2C_FIELD(M2C_FIELD(arg0, void**, 0xE8), s32*, 4);
		switch (M2C_FIELD(arg0, s32*, 0x19C)) {
			case 1:
			case 2:
			case 0x43:
				fn_8019ED68(
				    frame, &AxisY, 180.0f + 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150), 0);
				break;
			default:
				fn_8019ED68(frame, &AxisY, 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150), 0);
				break;
		}
		fn_8019EB94(frame, &M2C_FIELD(arg0, RwV3d*, 0x140), 2);
		if (M2C_FIELD(arg0, void**, 0x288) == NULL) {
			M2C_FIELD(arg0, void**, 0x288)
			    = SearchFrameFromFrameID__11nRenderWareFP7RwFramei(frame, 0xC1D);
		}
		for (i = 0; i < 3; i++) {
			if (((EggFrameView*)arg0)->exhaust[i] == NULL) {
				((EggFrameView*)arg0)->exhaust[i]
				    = SearchFrameFromFrameID__11nRenderWareFP7RwFramei(frame, lbl_8_rodata_17E8[i]);
			}
		}
	}
}

/* The constructor's inlined SetPosition: same body, but its exhaust-frame loop
 * addresses the slots by a byte offset (retail keeps an i*4 offset IV and
 * indexes off this with lwzx/stwx). */
static inline void eggSetPositionCt(void* arg0)
{
	s32 frame;
	s32 i;

	if (M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		frame = M2C_FIELD(M2C_FIELD(arg0, void**, 0xE8), s32*, 4);
		switch (M2C_FIELD(arg0, s32*, 0x19C)) {
			case 1:
			case 2:
			case 0x43:
				fn_8019ED68(
				    frame, &AxisY, 180.0f + 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150), 0);
				break;
			default:
				fn_8019ED68(frame, &AxisY, 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150), 0);
				break;
		}
		fn_8019EB94(frame, &M2C_FIELD(arg0, RwV3d*, 0x140), 2);
		if (M2C_FIELD(arg0, void**, 0x288) == NULL) {
			M2C_FIELD(arg0, void**, 0x288)
			    = SearchFrameFromFrameID__11nRenderWareFP7RwFramei(frame, 0xC1D);
		}
		for (i = 0; i < 3; i++) {
			s32 off = i * 4;
			if (*(void**)((u8*)arg0 + 0x298 + off) == NULL) {
				*(void**)((u8*)arg0 + 0x298 + off)
				    = SearchFrameFromFrameID__11nRenderWareFP7RwFramei(frame, lbl_8_rodata_17E8[i]);
			}
		}
	}
}

/* Takes the placement's position and angle; the egg mobile starts at rest. */
static inline void eggSetParameter(void* arg0)
{
	M2C_FIELD(arg0, f32*, 0x250)    = 0.5f;
	M2C_FIELD(arg0, RwV3d*, 0x140)  = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), RwV3d*, 0);
	M2C_FIELD(arg0, sAngle*, 0x14C) = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), sAngle*, 0xC);
	M2C_FIELD(arg0, RwV3d*, 0x1C0)  = M2C_FIELD(arg0, RwV3d*, 0x140);
	M2C_FIELD(arg0, RwV3d*, 0x1CC)  = M2C_FIELD(arg0, RwV3d*, 0x140);
	M2C_FIELD(arg0, RwV3d*, 0x1C0)  = M2C_FIELD(arg0, RwV3d*, 0x140);
	RwV3d zero                      = lbl_8_rodata_17DC;
	M2C_FIELD(arg0, RwV3d*, 0x1CC)  = zero;
	M2C_FIELD(arg0, s32*, 0x180)    = 0x200;
}

/* Takes the players' controls away for a scene (the six flags of
 * lbl_8029BBD0), and gives them back. */
static inline void eggLockPlayers()
{
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 0;
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 0;
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 0;
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 0;
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 0;
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 0;
	fn_80018C4C(&lbl_8029BBD0);
}

static inline void eggUnlockPlayers()
{
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 1;
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 1;
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 1;
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 1;
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 1;
	M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 1;
	fn_80018C64(&lbl_8029BBD0);
}

/* Plays one of the egg mobile's camera motions (the record at 15B78). */
static inline void eggPlayCameraMotion(s32 motion)
{
	if (mpDataBase__14TEnemyDataBase == 0U && __nw__FUl(0x70) != NULL) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(lbl_8_data_15B78, s32*, 8) = SearchCameraMotion__14TEnemyDataBaseF14eEnemyDataBaseUi(
	    mpDataBase__14TEnemyDataBase, 0xB, motion);
	fn_80133090((int*)lbl_8_data_15B78, (int*)lbl_8_data_15B78);
}

/* The editor record (SETOBJ_PARAM). */
typedef struct EggObjectEntry {
	const char* name;        /* 0x00 */
	void (*load)(M2C_UNK);   /* 0x04 */
	void (*unload)(void);    /* 0x08 */
	void (*create)(void);    /* 0x0C */
	void (*reset)(void);     /* 0x10 */
	u32 flags;               /* 0x14 */
	u32 unk18;               /* 0x18 */
	s16 unk1C;               /* 0x1C */
	s16 unk1E;               /* 0x1E */
	u8 unk20;                /* 0x20 */
	u8 unk21;                /* 0x21 */
	u8 pad22[2];             /* 0x22 */
	const char* fieldTypes;  /* 0x24 */
	const char** fieldNames; /* 0x28 */
	u8 pad2C[4];             /* 0x2C */
} EggObjectEntry;            /* 0x30 */

EggObjectEntry lbl_8_bss_1918;

void fn_8_9EBB8(void* arg0, s32 arg1);
void fn_8_9EC40(void* arg0, s32 arg1);
void fn_8_9ED10(void* arg0, s32 arg1);
void fn_8_9ED60(void* arg0, s32 arg1);
void fn_8_9EDB0(void);
void fn_8_9EDB4(void* arg0);
EggObject* fn_8_9EE60(EggObject* arg0, s16 arg1);
EggObject* fn_8_9EED4(EggObject* arg0, EggObject* arg1);
void fn_8_9EF3C(void);
void fn_8_9EFC8(void* arg0);
s32 IsSleep__18TObjEnemyEggMobileFv(void* arg0);
void fn_8_9F2E4(void* arg0);
void fn_8_9F380(void* arg0);
s32 fn_8_9F3F8(void* arg0);
void fn_8_9F460(void* arg0);
void fn_8_9F560(void* arg0);
void fn_8_9F618(void* arg0);
s32 CheckCameraFrustumTest__18TObjEnemyEggMobileFPC5RwV3df(void);
void DispTrans__18TObjEnemyEggMobileFv(void* arg0);
void DispOpaq__18TObjEnemyEggMobileFv(void* arg0);
void UpdateOnEdit__18TObjEnemyEggMobileFv(void* arg0);
void Update__18TObjEnemyEggMobileFv(void* arg0, M2C_UNK arg_sp0);
void fn_8_9FDF8(void* arg0, s32 arg1);
void fn_8_9FF78(void* arg0, s32 arg1);
void fn_8_A0018(void* arg0, s32 arg1);
void fn_8_A0078(void* arg0, s32 arg1);
void fn_8_A0354(void* arg0, s32 arg1);
void fn_8_A04A8(void* arg0, s32 arg1);
void fn_8_A0668(void* arg0, s32 arg1);
void fn_8_A07B4(void* arg0, s32 arg1);
void fn_8_A0A10(void* arg0, s32 arg1);
void CtrlMode__18TObjEnemyEggMobileF8ENEMY_MDQ29TObjEnemy10eCtrlSMode(
    void* arg0, s32 arg1, s32 arg2);
s32 KillMySelf__18TObjEnemyEggMobileFv(s32 arg0);
void fn_8_A114C(void* arg0);
void fn_8_A12D4(void* arg0);
void fn_8_A13C0(void* arg0);
void fn_8_A15BC(void* arg0);
void fn_8_A1698(void* arg0);
EggObject* __dt__18TObjEnemyEggMobileFv(EggObject* arg0, s16 arg1);
EggObject* fn_8_A18A0(EggObject* arg0, EggObject* parent);
EggObject* fn_8_A1E30(void);
EggObject* fn_8_A1E40(void);
void TObjEnemyEggMobile::EditOnChange(SETDATA_PARAM*);
void fn_8_A1E98(void);
void fn_8_A1EB8(void);
void fn_8_A1F68(M2C_UNK arg_sp0);
void fn_8_A23AC(void* arg0, void* arg1);
void AddItemBox__18TObjEnemyEggMobileFP5RwV3d(void);
void DispShadow__9TObjEnemyFv(void);
void AddScore__18TObjEnemyEggMobileFv(void);
void RcvCommand__18TObjEnemyEggMobileFP13sEnemyCommand(void);
void fn_8_A2454(void);
__declspec(section ".ctors") void (*const eggMobileCtorEntry)(void) = fn_8_A2454;

/* The module's static initialiser: registers EGGMOBILE OBJECT with the editor
 * and fills TZakoRushCtrl's handler table. */
void fn_8_A2454(void)
{
	EggPtmf* table;

	lbl_8_bss_1918.flags      = 0;
	lbl_8_bss_1918.unk18      = 0;
	lbl_8_bss_1918.name       = "EGGMOBILE OBJECT";
	lbl_8_bss_1918.load       = fn_8_A1F68;
	lbl_8_bss_1918.unload     = fn_8_A1EB8;
	lbl_8_bss_1918.create     = fn_8_A1E98;
	lbl_8_bss_1918.reset      = NULL;
	lbl_8_bss_1918.flags      = 0x20000;
	lbl_8_bss_1918.unk18      = 0;
	lbl_8_bss_1918.unk20      = 0x1E;
	lbl_8_bss_1918.unk1C      = 0x15D1;
	lbl_8_bss_1918.unk1E      = 4;
	lbl_8_bss_1918.unk21      = 0;
	lbl_8_bss_1918.fieldTypes = "f";
	lbl_8_bss_1918.fieldNames = &lbl_8_data_15DC0;
	if (lbl_8_bss_1918.fieldTypes != NULL) {
		lbl_8_bss_1918.flags |= 8;
	} else {
		lbl_8_bss_1918.flags &= ~8;
	}
	table    = lbl_8_data_15E0C;
	table[0] = lbl_8_data_15DDC;
	table[1] = lbl_8_data_15DE8;
	table[2] = lbl_8_data_15DF4;
	table[3] = lbl_8_data_15E00;
}

void RcvCommand__18TObjEnemyEggMobileFP13sEnemyCommand(void) { }

void AddScore__18TObjEnemyEggMobileFv(void) { }

/* TObjEnemy::DispShadow, the base's empty hook: this unit keeps the module's
 * copy (TObjEnemyRinoliner's vtable uses it too). */
void DispShadow__9TObjEnemyFv(void) { }

void AddItemBox__18TObjEnemyEggMobileFP5RwV3d(void) { }

void fn_8_A23AC(void* arg0, void* arg1)
{
	M2C_FIELD(arg0, void**, 0x14) = arg1;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	if (((TObjectDispatch*)arg0)->vslot5() != 0) {
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 2);
	}
	((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
		fn_800A31B8(M2C_FIELD(arg0, void**, 0x14), M2C_FIELD(arg0, s32*, 0x10));
	}
}

void fn_8_A1F68(M2C_UNK arg_sp0)
{
	u32 temp_r3;
	if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
		if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
			__ct__14TEnemyDataBaseFv();
		}
		Add__14TEnemyDataBaseF14eEnemyDataBasePc(
		    mpDataBase__14TEnemyDataBase, 0xB, lbl_8_data_15E8C);
	} else {
		if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
			__ct__14TEnemyDataBaseFv();
		}
		Add__14TEnemyDataBaseF14eEnemyDataBasePc(
		    mpDataBase__14TEnemyDataBase, 0xB, lbl_8_data_15EA4);
	}
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	temp_r3 = SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(
	    mpDataBase__14TEnemyDataBase, 0xB, 0xE);
	if (temp_r3 != 0U) {
		objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(temp_r3, 6);
	} else {
		return;
	}
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_18A8, u32*, 0)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xB, 0x10);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_18A8, u32*, 4)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xB, 0xD);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_18A8, u32*, 8)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xB, 0x14);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xB, 0xA);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xB, 0x13);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xB, 0x11);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xB, 0x12);
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4) != 0U) {
		fn_800F46B0((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10) != 0U) {
		objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(
		    (void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14) != 0U) {
		objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(
		    (void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18) != 0U) {
		objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(
		    (void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18));
	}
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	lbl_8_bss_18C4
	    = SearchUVAnim__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xB, 0xB);
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4) != 0U) {
		fn_8003C640((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4));
	}
	if (((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC) != 0U) && ((u32)lbl_8_bss_18C4 != 0U)) {
		*lbl_8_bss_18C8 = lbl_8_bss_18C4;
		SetClumpCustomFXTexture__FP7RpClumpP8UVFXInfo((u32*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC));
	}
	lbl_8_bss_190C = 0;
	LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    0xB, (M2C_UNK*)&lbl_8_data_15BF0[0]);
	LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    0xB, (M2C_UNK*)&lbl_8_data_15D24[0]);
	lbl_8_bss_1910 = 0;
}

void fn_8_A1EB8(void)
{
	lbl_8_bss_1910 = 0;
	ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    0xB, (M2C_UNK*)&lbl_8_data_15D24[0]);
	ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    0xB, (M2C_UNK*)&lbl_8_data_15BF0[0]);
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 0)    = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 4)    = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 8)    = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 0xC)  = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 0x10) = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 0x14) = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 0x18) = 0;
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	Delete__14TEnemyDataBaseF14eEnemyDataBase(mpDataBase__14TEnemyDataBase, 0xB);
}

/* startObjEnemyEggMobile */
void fn_8_A1E98(void)
{
	fn_8_A1E40();
}

void TObjEnemyEggMobile::EditOnChange(SETDATA_PARAM*) { }

#pragma dont_inline on

/* TObjEnemyEggMobile::CreateInstance */
EggObject* fn_8_A1E40(void)
{
	EggObject* p = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x2B4);
	if (p != NULL) {
		p = fn_8_A18A0(p, lbl_8042C10C);
	}
	return p;
}
#pragma dont_inline reset

EggObject* fn_8_A1E30(void)
{
	return lbl_8_bss_1914;
}

#pragma opt_common_subs off

/* TObjEnemyEggMobile::TObjEnemyEggMobile(EggObject*) */
EggObject* fn_8_A18A0(EggObject* arg0, EggObject* parent)
{
	void* p;
	u32 path;

	fn_800A714C(arg0, parent);
	__ct__10HAnimClassFv((u8*)arg0 + 0x240);
	arg0->unk18  = (M2C_UNK*)__vt__18TObjEnemyEggMobile;
	arg0->unkB4  = (u8*)__vt__18TObjEnemyEggMobile + 0x2C;
	arg0->unk278 = 0;
	arg0->unk0   = lbl_8_data_15DD8;
	arg0->unk1E  = 0x2B4;
	fn_8_A1698(arg0);
	eggSetParameter(arg0);
	arg0->unk158 = arg0->unk15C = arg0->unk160 = 0.0f;
	/* CloneClump, inline */

	if ((u32)M2C_FIELD(arg0, u32*, 0x2B0) != 0U) {
		__dt__11ENEMYMTNMANFv((void*)M2C_FIELD(arg0, u32*, 0x2B0), 1);
		M2C_FIELD(arg0, u32*, 0x2B0) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2A4) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2A4));
		M2C_FIELD(arg0, u32*, 0x2A4) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2A8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2A8));
		M2C_FIELD(arg0, u32*, 0x2A8) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2AC) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2AC));
		M2C_FIELD(arg0, u32*, 0x2AC) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x284) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x284));
		M2C_FIELD(arg0, u32*, 0x284) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x280) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x280));
		M2C_FIELD(arg0, u32*, 0x280) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x27C) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x27C));
		M2C_FIELD(arg0, u32*, 0x27C) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0xE8));
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
	M2C_FIELD(arg0, void**, 0xE8) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, s32*, 0));
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4) != 0U) {
		M2C_FIELD(arg0, void**, 0x27C) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 8) != 0U) {
		M2C_FIELD(arg0, void**, 0x280) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 8));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC) != 0U) {
		M2C_FIELD(arg0, void**, 0x284) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10) != 0U) {
		M2C_FIELD(arg0, void**, 0x2A4) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, void**, 0x2A8) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18) != 0U) {
		M2C_FIELD(arg0, void**, 0x2AC) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18));
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x27C) != NULL) {
		p = __nw__FUl(0x4C);
		if (p != NULL) {
			p = __ct__11ENEMYMTNMANFv((void*)p);
		}
		M2C_FIELD(arg0, void**, 0x2B0) = p;
		M2C_FIELD(M2C_FIELD(arg0, void***, 0x2B0), void**, 0x30)
		    = (void*)M2C_FIELD(arg0, void**, 0x27C);
		M2C_FIELD(M2C_FIELD(arg0, void***, 0x2B0), M2C_UNK**, 0x2C)
		    = (M2C_UNK*)&lbl_8_data_15D24[0];
		M2C_FIELD(M2C_FIELD(arg0, void***, 0x2B0), s32*, 0x1C) = 0;
	}
	eggSetPositionCt(arg0);
	arg0->unkE4 = (M2C_UNK*)lbl_8_data_15BF0;
	arg0->unkD4 = 0;
	path        = *M2C_FIELD(lbl_8042C380, u32**, 0x28);
	if (path != 0) {
		arg0->unk248 = path;
	}
	p = __nw__FUl(0x20);
	if (p != NULL) {
		p = fn_8_A31D4(p);
	}
	arg0->unk240 = (void**)p;
	if (arg0->unk240 != NULL) {
		if (lbl_8_bss_1910 == 0) {
			fn_8_A2A78(arg0->unk240, arg0);
			lbl_8_bss_1910 = 1;
		} else {
			fn_8_A2A00(arg0->unk240, arg0);
		}
	}
	lbl_8_bss_1914 = arg0;
	return arg0;
}
#pragma opt_common_subs reset

EggObject* __dt__18TObjEnemyEggMobileFv(EggObject* arg0, s16 arg1)
{
	s32 temp_cr0_eq;
	void** temp_r3;

	if (arg0 != NULL) {
		arg0->unk18 = (M2C_UNK*)__vt__18TObjEnemyEggMobile;
		arg0->unkB4 = (u8*)__vt__18TObjEnemyEggMobile + 0x2C;
		temp_r3     = arg0->unk240;
		if (temp_r3 != NULL) {
			if (temp_r3 != NULL) {
				((TSubDispatch*)temp_r3)->vslot2(1);
			}
			arg0->unk240 = NULL;
		}
		if ((u32)arg0->unk2B0 != NULL) {
			__dt__11ENEMYMTNMANFv((void*)arg0->unk2B0, 1);
			arg0->unk2B0 = NULL;
		}
		if ((u32)arg0->unk2A4 != NULL) {
			fn_80150958((void*)arg0->unk2A4);
			arg0->unk2A4 = NULL;
		}
		if ((u32)arg0->unk2A8 != NULL) {
			fn_80150958((void*)arg0->unk2A8);
			arg0->unk2A8 = NULL;
		}
		if ((u32)arg0->unk2AC != NULL) {
			fn_80150958((void*)arg0->unk2AC);
			arg0->unk2AC = NULL;
		}
		if ((u32)arg0->unk284 != NULL) {
			fn_80150958((void*)arg0->unk284);
			arg0->unk284 = NULL;
		}
		if ((u32)arg0->unk280 != NULL) {
			fn_80150958((void*)arg0->unk280);
			arg0->unk280 = NULL;
		}
		if ((u32)arg0->unk27C != NULL) {
			fn_80150958((void*)arg0->unk27C);
			arg0->unk27C = NULL;
		}
		if ((u32)arg0->unkE8 != NULL) {
			fn_80150958((void*)arg0->unkE8);
			arg0->unkE8 = NULL;
		}
		lbl_8_bss_1914 = NULL;
		__dt__10HAnimClassFv((u8*)arg0 + 0x240, 0);
		fn_800A7088(arg0, 0);
		if (arg1 > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

void fn_8_A1698(void* arg0)
{
	M2C_FIELD(arg0, s32*, 0x248) = 0;
	M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x250) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x25C) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x258) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x254) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x27C) = 0;
	M2C_FIELD(arg0, s32*, 0x280) = 0;
	M2C_FIELD(arg0, s32*, 0x284) = 0;
	M2C_FIELD(arg0, s32*, 0x288) = 0;
	M2C_FIELD(arg0, s32*, 0x240) = 0;
	M2C_FIELD(arg0, s32*, 0x260) = 0;
	M2C_FIELD(arg0, s32*, 0x264) = 1;
	M2C_FIELD(arg0, s32*, 0x268) = 1;
	M2C_FIELD(arg0, s32*, 0x244) = 0;
	M2C_FIELD(arg0, s32*, 0x26C) = 0;
	M2C_FIELD(arg0, s32*, 0x298) = 0;
	M2C_FIELD(arg0, s32*, 0x2A4) = 0;
	M2C_FIELD(arg0, s32*, 0x29C) = 0;
	M2C_FIELD(arg0, s32*, 0x2A8) = 0;
	M2C_FIELD(arg0, s32*, 0x2A0) = 0;
	M2C_FIELD(arg0, s32*, 0x2AC) = 0;
	M2C_FIELD(arg0, s32*, 0x2B0) = 0;
	M2C_FIELD(arg0, s32*, 0x274) = 0;
	M2C_FIELD(arg0, s32*, 0x278) = 0;
}

/* TObjEnemyEggMobile::SetParameter */
void fn_8_A15BC(void* arg0)
{
	eggSetParameter(arg0);
}

/* TObjEnemyEggMobile::CloneClump */
void fn_8_A13C0(void* arg0)
{
	void* var_r0;

	if ((u32)M2C_FIELD(arg0, u32*, 0x2B0) != 0U) {
		__dt__11ENEMYMTNMANFv((void*)M2C_FIELD(arg0, u32*, 0x2B0), 1);
		M2C_FIELD(arg0, u32*, 0x2B0) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2A4) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2A4));
		M2C_FIELD(arg0, u32*, 0x2A4) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2A8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2A8));
		M2C_FIELD(arg0, u32*, 0x2A8) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2AC) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2AC));
		M2C_FIELD(arg0, u32*, 0x2AC) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x284) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x284));
		M2C_FIELD(arg0, u32*, 0x284) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x280) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x280));
		M2C_FIELD(arg0, u32*, 0x280) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x27C) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x27C));
		M2C_FIELD(arg0, u32*, 0x27C) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0xE8));
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
	M2C_FIELD(arg0, void**, 0xE8) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, s32*, 0));
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4) != 0U) {
		M2C_FIELD(arg0, void**, 0x27C) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 8) != 0U) {
		M2C_FIELD(arg0, void**, 0x280) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 8));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC) != 0U) {
		M2C_FIELD(arg0, void**, 0x284) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10) != 0U) {
		M2C_FIELD(arg0, void**, 0x2A4) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, void**, 0x2A8) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14));
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18) != 0U) {
		M2C_FIELD(arg0, void**, 0x2AC) = fn_80150588((void*)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18));
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x27C) != NULL) {
		var_r0 = __nw__FUl(0x4C);
		if (var_r0 != NULL) {
			var_r0 = __ct__11ENEMYMTNMANFv((void*)var_r0);
		}
		M2C_FIELD(arg0, void**, 0x2B0) = var_r0;
		M2C_FIELD(M2C_FIELD(arg0, void***, 0x2B0), void**, 0x30)
		    = (void*)M2C_FIELD(arg0, void**, 0x27C);
		M2C_FIELD(M2C_FIELD(arg0, void***, 0x2B0), M2C_UNK**, 0x2C)
		    = (M2C_UNK*)&lbl_8_data_15D24[0];
		M2C_FIELD(M2C_FIELD(arg0, void***, 0x2B0), s32*, 0x1C) = 0;
	}
}

/* TObjEnemyEggMobile::DestroyClump */
void fn_8_A12D4(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x2B0) != 0U) {
		__dt__11ENEMYMTNMANFv((void*)M2C_FIELD(arg0, u32*, 0x2B0), 1);
		M2C_FIELD(arg0, u32*, 0x2B0) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2A4) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2A4));
		M2C_FIELD(arg0, u32*, 0x2A4) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2A8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2A8));
		M2C_FIELD(arg0, u32*, 0x2A8) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2AC) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2AC));
		M2C_FIELD(arg0, u32*, 0x2AC) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x284) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x284));
		M2C_FIELD(arg0, u32*, 0x284) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x280) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x280));
		M2C_FIELD(arg0, u32*, 0x280) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x27C) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x27C));
		M2C_FIELD(arg0, u32*, 0x27C) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0xE8));
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

/* TObjEnemyEggMobile::SetPosition, out of line. Its body is written here
 * rather than as a call to eggSetPosition: the inlined call colors the loop
 * counter and the id-table pointer into swapped registers (r29/r28). */
void fn_8_A114C(void* arg0)
{
	s32 frame;
	s32 i;

	if (M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		frame = M2C_FIELD(M2C_FIELD(arg0, void**, 0xE8), s32*, 4);
		switch (M2C_FIELD(arg0, s32*, 0x19C)) {
			case 1:
			case 2:
			case 0x43:
				fn_8019ED68(
				    frame, &AxisY, 180.0f + 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150), 0);
				break;
			default:
				fn_8019ED68(frame, &AxisY, 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150), 0);
				break;
		}
		fn_8019EB94(frame, &M2C_FIELD(arg0, RwV3d*, 0x140), 2);
		if (M2C_FIELD(arg0, void**, 0x288) == NULL) {
			M2C_FIELD(arg0, void**, 0x288)
			    = SearchFrameFromFrameID__11nRenderWareFP7RwFramei(frame, 0xC1D);
		}
		for (i = 0; i < 3; i++) {
			if (((EggFrameView*)arg0)->exhaust[i] == NULL) {
				((EggFrameView*)arg0)->exhaust[i]
				    = SearchFrameFromFrameID__11nRenderWareFP7RwFramei(frame, lbl_8_rodata_17E8[i]);
			}
		}
	}
}

s32 KillMySelf__18TObjEnemyEggMobileFv(s32 arg0)
{
	return CheckMustKill__10TObjSetObjFv((s32)((u8*)arg0 + 0xB0)) != 0;
}

/* TObjEnemyEggMobile::CtrlMode: runs the given phase of the current mode's
 * EnemyMD_* handler. */
void CtrlMode__18TObjEnemyEggMobileF8ENEMY_MDQ29TObjEnemy10eCtrlSMode(
    void* arg0, s32 arg1, s32 arg2)
{
	switch (arg1) {
		case 0:
			break;
		case 1:
			fn_8_A0A10(arg0, arg2);
			break;
		case 2:
			fn_8_A07B4(arg0, arg2);
			break;
		case 0x42:
			fn_8_A0668(arg0, arg2);
			break;
		case 0x43:
			fn_8_A04A8(arg0, arg2);
			break;
		case 0x41:
			fn_8_A0354(arg0, arg2);
			break;
		case 0x44:
			fn_8_A0078(arg0, arg2);
			break;
		case 0x26:
			fn_8_A0018(arg0, arg2);
			break;
		case 0x1D:
			fn_8_9FF78(arg0, arg2);
			break;
		case 0x5C:
			fn_8_9FDF8(arg0, arg2);
			break;
	}
}

void fn_8_A0A10(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 0;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_A07B4(void* arg0, s32 arg1)
{
	s32 temp_r30;
	const struct _struct_lbl_8_rodata_17F4_0xC* temp_r3;
	const struct _struct_lbl_8_rodata_17F4_0xC* temp_r3_2;

	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
				temp_r3                      = &lbl_8_rodata_17F4[M2C_FIELD(arg0, s32*, 0x244) + 1];
				M2C_FIELD(arg0, f32*, 0x1CC) = (f32)temp_r3->unk0;
				M2C_FIELD(arg0, f32*, 0x1D0) = (f32)temp_r3->unk4;
				M2C_FIELD(arg0, f32*, 0x1D4) = (f32)temp_r3->unk8;
			} else {
				temp_r3_2                    = &lbl_8_rodata_17F4[M2C_FIELD(arg0, s32*, 0x244)];
				M2C_FIELD(arg0, f32*, 0x1CC) = (f32)temp_r3_2->unk0;
				M2C_FIELD(arg0, f32*, 0x1D0) = (f32)temp_r3_2->unk4;
				M2C_FIELD(arg0, f32*, 0x1D4) = (f32)temp_r3_2->unk8;
			}
			M2C_FIELD(arg0, s32*, 0xD4) = 2;
			fn_8_9F618(arg0);
			fn_800A5A54(arg0);
			M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x264) != 0) {
				fn_8_9F618(arg0);
				temp_r30                     = fn_800A5A54(arg0);
				M2C_FIELD(arg0, s32*, 0x150) = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x150),
				    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
				if (temp_r30 < 0x80) {
					M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
				}
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_A0668(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 2;
			if (((u32)lbl_8042C6E4 != 0U) && (Exist__12EventManagerFv(lbl_8042C6E4) != 0)) {
				EventRewind__12EventManagerFv(lbl_8042C6E4);
				EventStart__12EventManagerFv(lbl_8042C6E4);
			}
			if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
				M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(lbl_8_rodata_183C, f32*, 0xC);
				M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(lbl_8_rodata_183C, f32*, 0x10);
				M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(lbl_8_rodata_183C, f32*, 0x14);
				M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(lbl_8_rodata_1854, s32*, 0xC);
				M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(lbl_8_rodata_1854, s32*, 0x10);
				M2C_FIELD(arg0, s32*, 0x154) = (s32)M2C_FIELD(lbl_8_rodata_1854, s32*, 0x14);
				return;
			}
			M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(lbl_8_rodata_183C, f32*, 0);
			M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(lbl_8_rodata_183C, f32*, 4);
			M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(lbl_8_rodata_183C, f32*, 8);
			M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(lbl_8_rodata_1854, s32*, 0);
			M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(lbl_8_rodata_1854, s32*, 4);
			M2C_FIELD(arg0, s32*, 0x154) = (s32)M2C_FIELD(lbl_8_rodata_1854, s32*, 8);
			return;
		case 1:
			if ((s32)M2C_FIELD(lbl_8042C180, s32*, 0x40) < 0) {
				M2C_FIELD(arg0, s32*, 0x260) = 0x44;
			}
			return;
		case 2:
		case 3:
			break;
	}
}

/* Plays Eggman's line for the attack just ended (0x274), at random for the
 * first, then follows the path. */
void fn_8_A04A8(void* arg0, s32 arg1)
{
	s32 line;

	switch (arg1) {
		case 0:
			line = M2C_FIELD(arg0, s32*, 0x274);
			if (line == 0) {
				if (0.000030517578f * (f32)rand() < 0.5f) {
					fn_8_D8E90(0x13, 0, -1);
				} else {
					fn_8_D8E90(0x14, 0, -1);
				}
			} else if (line == 1) {
				fn_8_D8E90(0x15, 0, -1);
			} else if (line == 2) {
				fn_8_D8E90(0x16, 0, -1);
			} else if (line == 3) {
				fn_8_D8E90(0x17, 0, -1);
			}
			M2C_FIELD(arg0, s32*, 0x274) = 0;
			break;
		case 1:
			if (M2C_FIELD(arg0, s32*, 0x264) != 0) {
				fn_8_9F560(arg0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_A0354(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 1;
			eggPlayCameraMotion(0x15);
			M2C_FIELD(arg0, f32*, 0x148) = 0.0f;
			M2C_FIELD(arg0, f32*, 0x144) = 0.0f;
			M2C_FIELD(arg0, f32*, 0x140) = 0.0f;
			M2C_FIELD(arg0, s32*, 0x154) = 0;
			M2C_FIELD(arg0, s32*, 0x150) = 0;
			M2C_FIELD(arg0, s32*, 0x14C) = 0;
			eggLockPlayers();
			return;
		case 1:
			eggLockPlayers();
			return;
		case 3:
			fn_801329AC();
			eggUnlockPlayers();
			/* fallthrough */
		case 2:
			return;
	}
}

void fn_8_A0078(void* arg0, s32 arg1)
{
	EggObject* temp_r3;
	s32 temp_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 4;
			eggPlayCameraMotion(6);
			M2C_FIELD(arg0, f32*, 0x148)                          = 0.0f;
			M2C_FIELD(arg0, f32*, 0x144)                          = 0.0f;
			M2C_FIELD(arg0, f32*, 0x140)                          = 0.0f;
			M2C_FIELD(arg0, s32*, 0x154)                          = 0;
			M2C_FIELD(arg0, s32*, 0x150)                          = 0;
			M2C_FIELD(arg0, s32*, 0x14C)                          = 0;
			M2C_FIELD(arg0, s32*, 0x28C)                          = 0;
			M2C_FIELD(arg0, s32*, 0x290)                          = 0;
			M2C_FIELD(arg0, s32*, 0x294)                          = 0;
			M2C_FIELD(M2C_FIELD(arg0, void**, 0x2B0), s32*, 0x1C) = 1;
			fn_8_D8E90(0x12, 0, -1);
			fn_800CCC6C(lbl_8_data_15E7C);
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x28C) == 0) {
				if (((s32)M2C_FIELD(lbl_8042C180, s32*, 0x40) < 0) && (fn_80018C98() == 5)) {
					fn_8012D9D0();
					M2C_FIELD(arg0, s32*, 0x28C) = 1;
					M2C_FIELD(arg0, s32*, 0x290) = 0;
					return;
				}
			} else if ((s32)M2C_FIELD(arg0, s32*, 0x290) == 0) {
				if (fn_8012DA08() != 0) {
					eggUnlockPlayers();
					M2C_FIELD(arg0, s32*, 0x290) = 1;
					M2C_FIELD(arg0, s32*, 0x260) = 2;
					if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
						temp_r4 = fn_80103178(0);
						if (temp_r4 != -1) {
							fn_80111260(lbl_8042C610, temp_r4, 0xAA);
						}
					} else {
						temp_r4 = fn_80103178(0);
						if (temp_r4 != -1) {
							fn_80111260(lbl_8042C610, temp_r4, 0x91);
						}
					}
				} else {
					eggLockPlayers();
				}
				if ((s32)M2C_FIELD(arg0, s32*, 0x294) == 0) {
					if (fn_80132958(0) >= 310.0f) {
						M2C_FIELD(arg0, s32*, 0x294) = 1;
						temp_r3                      = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x38);
						if (temp_r3 != NULL) {
							__ct__7TObjectFP7TObject(temp_r3, lbl_8042C0FC);
							temp_r3->unk18 = (M2C_UNK*)&lbl_8_data_15E50[0];
							temp_r3->unk0  = lbl_8_data_15E4C;
							temp_r3->unk1E = 0x38;
							temp_r3->unk30 = 0;
							temp_r3->unk34 = 0;
							temp_r3->unk28 = 0;
							temp_r3->unk2C = 0;
							return;
						}
					}
				}
			}
			break;
		case 3:
			fn_801329AC();
		case 2:
			return;
	}
}

void fn_8_A0018(void* arg0, s32 arg1)
{
	u32* table;

	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x244) += 1;
			M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
			table                        = M2C_FIELD(lbl_8042C380, u32**, 0x28);
			if (table[0] != 0) {
				M2C_FIELD(arg0, u32*, 0x248) = table[M2C_FIELD(arg0, s32*, 0x244)];
			}
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_9FF78(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			SetEnd__10TObjSetObjFv((u8*)arg0 + 0xB0);
			break;
		case 1:
			if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) == 0) {
				fn_80019898(&lbl_8029C310, 0);
				M2C_FIELD(&lbl_8029C310, s32*, 0x290) = 0;
				M2C_FIELD(arg0, u16*, 4)              = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_9FDF8(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 5;
			eggPlayCameraMotion(9);
			M2C_FIELD(arg0, f32*, 0x148)                          = 0.0f;
			M2C_FIELD(arg0, f32*, 0x144)                          = 0.0f;
			M2C_FIELD(arg0, f32*, 0x140)                          = 0.0f;
			M2C_FIELD(arg0, s32*, 0x154)                          = 0;
			M2C_FIELD(arg0, s32*, 0x150)                          = 0;
			M2C_FIELD(arg0, s32*, 0x14C)                          = 0;
			M2C_FIELD(M2C_FIELD(arg0, void**, 0x2B0), s32*, 0x1C) = 2;
			fn_8_D8E90(0x17, 0, -1);
			eggLockPlayers();
			M2C_FIELD(&lbl_8029C310, s32*, 0x290) = 1;
			return;
		case 1:
			if ((s32)((M2C_FIELD(arg0, s32*, 0xC8) & 1) != 0) == 1) {
				M2C_FIELD(arg0, s32*, 0x260) = 0x1D;
				eggUnlockPlayers();
			}
		case 2:
			return;
		case 3:
			fn_801329AC();
			break;
	}
}

/* Update's body-frame and exhaust-frame attachment steps. They are inline
 * helpers (not open-coded in Update) because their locals must be inline
 * locals to get retail's callee-saved register assignment (r29/r31). */
static inline void eggAttachToBody(void* arg0)
{
	void* temp_r29;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;

	if ((u32)M2C_FIELD(arg0, u32*, 0x288) != 0U) {
		temp_r29  = fn_8019E8EC((void*)M2C_FIELD(arg0, u32*, 0x288));
		temp_r3_3 = M2C_FIELD(arg0, void**, 0x27C);
		if (temp_r3_3 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_3, s32*, 4), temp_r29, 0);
		}
		temp_r3_4 = M2C_FIELD(arg0, void**, 0x280);
		if (temp_r3_4 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_4, s32*, 4), temp_r29, 0);
		}
		temp_r3_5 = M2C_FIELD(arg0, void**, 0x284);
		if (temp_r3_5 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_5, s32*, 4), temp_r29, 0);
		}
		M2C_FIELD(arg0, f32*, 0x254) = (f32)M2C_FIELD(temp_r29, f32*, 0x30);
		M2C_FIELD(arg0, f32*, 0x258) = (f32)M2C_FIELD(temp_r29, f32*, 0x34);
		M2C_FIELD(arg0, f32*, 0x25C) = (f32)M2C_FIELD(temp_r29, f32*, 0x38);
	}
}

static inline void eggAttachExhaust(void* arg0)
{
	s32 temp_r31_2;
	s32 var_r29_2;
	void* temp_r4;

	for (var_r29_2 = 0; var_r29_2 < 3; var_r29_2++) {
		if (((EggFrameView*)arg0)->exhaust[var_r29_2] != NULL) {
			temp_r4 = ((EggFrameView*)arg0)->effect[var_r29_2];
			if (temp_r4 != NULL) {
				temp_r31_2 = M2C_FIELD(temp_r4, s32*, 4);
				fn_8019ECCC(temp_r31_2, fn_8019E8EC(((EggFrameView*)arg0)->exhaust[var_r29_2]), 0);
			}
		}
	}
}

void Update__18TObjEnemyEggMobileFv(void* arg0, M2C_UNK arg_sp0)
{
	void** temp_r3;
	s32 var_r0;
	s32 var_r0_2;

	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x264) = var_r0;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0_2 = 0;
	} else {
		var_r0_2 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x268) = var_r0_2;
	temp_r3                      = M2C_FIELD(arg0, void***, 0x240);
	if (temp_r3 != NULL) {
		((TSubDispatch*)temp_r3)->vslot3(arg0);
	}
	((TRenderer*)arg0)->Slot50(M2C_FIELD(arg0, s32*, 0x19C), 1);
	eggSetPosition(arg0);
	fn_800A3D48(arg0);
	eggAttachToBody(arg0);
	eggAttachExhaust(arg0);
	if ((u32)M2C_FIELD(arg0, u32*, 0x2B0) != 0U) {
		UpdateMotion__11ENEMYMTNMANFv((void*)M2C_FIELD(arg0, u32*, 0x2B0));
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x268) != 0) {
		fn_8_9EFC8(arg0);
	}
	if ((u32)lbl_8042C388 != 0U) {
		fn_800B4A38(lbl_8042C388, 0x4063, (u8*)arg0 + 0x254, arg0, 3, 0, 2);
	}
}

#pragma opt_common_subs off

/* TObjEnemyEggMobile::UpdateOnEdit: back to the placement, at rest. */
void UpdateOnEdit__18TObjEnemyEggMobileFv(void* arg0)
{
	eggSetParameter(arg0);
	eggSetPosition(arg0);
}
#pragma opt_common_subs reset

void DispOpaq__18TObjEnemyEggMobileFv(void* arg0)
{
	u8* var_r31;
	s32 var_r30;

	var_r31 = (u8*)arg0;
	SetLightNum__7nRenderFUi(4);
	fn_8014FF2C(M2C_FIELD(var_r31, u32*, 0xE8));
	if (((u32)M2C_FIELD(var_r31, u32*, 0x27C) != 0U)
	    && ((s32)M2C_FIELD(var_r31, s32*, 0x19C) != 0x42)) {
		fn_8014FF2C(M2C_FIELD(var_r31, u32*, 0x27C));
	}
	var_r30 = 0;
	do {
		if ((u32)M2C_FIELD(var_r31, u32*, 0x2A4) != 0U) {
			fn_8014FF2C((u32)M2C_FIELD(var_r31, u32*, 0x2A4));
		}
		var_r31 += 4;
		var_r30 += 1;
	} while (var_r30 < 3);
}

void DispTrans__18TObjEnemyEggMobileFv(void* arg0)
{
	s32 temp_r4;

	SaveRenderState__7nRenderFv();
	if ((u32)M2C_FIELD(arg0, u32*, 0x280) != 0U) {
		fn_80194234(0x14, 1);
		SetLightNum__7nRenderFUi(4);
		fn_8014FF2C(M2C_FIELD(arg0, u32*, 0x280));
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x284) != 0U) {
		SetRenderStateForBlendAdd__7nRenderFv();
		SetLightNum__7nRenderFUi(0x10);
		temp_r4 = M2C_FIELD(lbl_8042C180, s32*, 0x30);
		if ((s32)lbl_8_bss_190C != temp_r4) {
			lbl_8_bss_190C = temp_r4;
			fn_8011B844(lbl_8_bss_18C4, 1.0f);
			fn_8014FFBC(M2C_FIELD(arg0, u32*, 0x284), &SetAtomicCustomFXData__FP8RpAtomicPv,
			    lbl_8_bss_18C8);
		}
		fn_8014FF2C(M2C_FIELD(arg0, u32*, 0x284));
	}
	LoadRenderState__7nRenderFv();
}

s32 CheckCameraFrustumTest__18TObjEnemyEggMobileFPC5RwV3df(void)
{
	return 1;
}

/* As fn_8_9F560, advancing along the path at the move speed (0x250). */
void fn_8_9F618(void* arg0)
{
	PathInfo info;

	if (M2C_FIELD(arg0, void**, 0x248) != NULL) {
		info.dist = M2C_FIELD(arg0, f32*, 0x24C);
		if (GetStatusOnPath__FP7PATHTAGP8PATHINFO(M2C_FIELD(arg0, void**, 0x248), &info) != 0) {
			M2C_FIELD(arg0, RwV3d*, 0x140) = info.pos;
		}
		M2C_FIELD(arg0, f32*, 0x24C) += M2C_FIELD(arg0, f32*, 0x250);
		if (M2C_FIELD(arg0, f32*, 0x24C) > M2C_FIELD(M2C_FIELD(arg0, void**, 0x248), f32*, 4)) {
			M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
		}
	}
	M2C_FIELD(arg0, s32*, 0x26C) += 0x100;
	M2C_FIELD(arg0, f32*, 0x144) += 4.0f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x26C));
}

/* Follows the path (0x248) at the distance 0x24C, bobbing on a sine. */
void fn_8_9F560(void* arg0)
{
	PathInfo info;

	if (M2C_FIELD(arg0, void**, 0x248) != NULL) {
		info.dist = M2C_FIELD(arg0, f32*, 0x24C);
		if (GetStatusOnPath__FP7PATHTAGP8PATHINFO(M2C_FIELD(arg0, void**, 0x248), &info) != 0) {
			M2C_FIELD(arg0, RwV3d*, 0x140) = info.pos;
		}
		if (M2C_FIELD(arg0, f32*, 0x24C) > M2C_FIELD(M2C_FIELD(arg0, void**, 0x248), f32*, 4)) {
			M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
		}
	}
	M2C_FIELD(arg0, s32*, 0x26C) += 0x100;
	M2C_FIELD(arg0, f32*, 0x144) += 4.0f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x26C));
}

void fn_8_9F460(void* arg0)
{
	void* temp_r31;
	u8* var_r31;
	s32 temp_r30;
	s32 var_r29;
	void* temp_r4;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;

	if ((u32)M2C_FIELD(arg0, u32*, 0x288) != 0U) {
		temp_r31 = fn_8019E8EC((void*)M2C_FIELD(arg0, u32*, 0x288));
		temp_r3  = M2C_FIELD(arg0, void**, 0x27C);
		if (temp_r3 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3, s32*, 4), temp_r31, 0);
		}
		temp_r3_2 = M2C_FIELD(arg0, void**, 0x280);
		if (temp_r3_2 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_2, s32*, 4), temp_r31, 0);
		}
		temp_r3_3 = M2C_FIELD(arg0, void**, 0x284);
		if (temp_r3_3 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_3, s32*, 4), temp_r31, 0);
		}
		M2C_FIELD(arg0, f32*, 0x254) = (f32)M2C_FIELD(temp_r31, f32*, 0x30);
		M2C_FIELD(arg0, f32*, 0x258) = (f32)M2C_FIELD(temp_r31, f32*, 0x34);
		M2C_FIELD(arg0, f32*, 0x25C) = (f32)M2C_FIELD(temp_r31, f32*, 0x38);
	}
	var_r29 = 0;
	var_r31 = (u8*)arg0;
	do {
		if ((u32)M2C_FIELD(var_r31, u32*, 0x298) != 0U) {
			temp_r4 = M2C_FIELD(var_r31, void**, 0x2A4);
			if (temp_r4 != NULL) {
				temp_r30 = M2C_FIELD(temp_r4, s32*, 4);
				fn_8019ECCC(temp_r30, fn_8019E8EC((void*)M2C_FIELD(var_r31, u32*, 0x298)), 0);
			}
		}
		var_r31 += 4;
		var_r29 += 1;
	} while (var_r29 < 3);
}

s32 fn_8_9F3F8(void* arg0)
{
	s32 temp_r31;

	temp_r31                     = fn_800A5A54(arg0);
	M2C_FIELD(arg0, s32*, 0x150) = AdjustAngle__Fiii(
	    M2C_FIELD(arg0, s32*, 0x150), M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
	if (temp_r31 < 0x80) {
		M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
		return 1;
	}
	return 0;
}

void fn_8_9F380(void* arg0)
{
	const struct _struct_lbl_8_rodata_17F4_0xC* temp_r4;
	const struct _struct_lbl_8_rodata_17F4_0xC* temp_r4_2;

	if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
		temp_r4                      = &lbl_8_rodata_17F4[M2C_FIELD(arg0, s32*, 0x244) + 1];
		M2C_FIELD(arg0, f32*, 0x1CC) = (f32)temp_r4->unk0;
		M2C_FIELD(arg0, f32*, 0x1D0) = (f32)temp_r4->unk4;
		M2C_FIELD(arg0, f32*, 0x1D4) = (f32)temp_r4->unk8;
		return;
	}
	temp_r4_2                    = &lbl_8_rodata_17F4[M2C_FIELD(arg0, s32*, 0x244)];
	M2C_FIELD(arg0, f32*, 0x1CC) = (f32)temp_r4_2->unk0;
	M2C_FIELD(arg0, f32*, 0x1D0) = (f32)temp_r4_2->unk4;
	M2C_FIELD(arg0, f32*, 0x1D4) = (f32)temp_r4_2->unk8;
}

/* Puts the egg mobile at its start: stage 0x15 has its own spot. */
void fn_8_9F2E4(void* arg0)
{
	if (M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
		M2C_FIELD(arg0, RwV3d*, 0x140)  = lbl_8_rodata_183C[1];
		M2C_FIELD(arg0, sAngle*, 0x14C) = lbl_8_rodata_1854[1];
		return;
	}
	M2C_FIELD(arg0, RwV3d*, 0x140)  = lbl_8_rodata_183C[0];
	M2C_FIELD(arg0, sAngle*, 0x14C) = lbl_8_rodata_1854[0];
}

s32 IsSleep__18TObjEnemyEggMobileFv(void* arg0)
{
	s32 var_r31;
	void* temp_r5;
	void* temp_r3;

	var_r31 = 0;
	temp_r5 = M2C_FIELD(arg0, void**, 0xB0);
	if (((s32)((M2C_FIELD(temp_r5, s32*, 0x18) & 0x04000000) != 0) == 1)
	    && (fn_800A2BE0(arg0, M2C_FIELD(temp_r5, u8*, 0x2A)) != 0)) {
		temp_r3                        = M2C_FIELD(arg0, void**, 0xB0);
		M2C_FIELD(temp_r3, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3, s32*, 0x18) & 0xFBFFFFFF);
		var_r31                        = 1;
	}
	return var_r31;
}

void fn_8_9EFC8(void* arg0)
{
	s32 temp_r31;
	u8* var_r29;
	s32 var_r4;
	s32 temp_r3;
	s32 temp_r3_2;

	temp_r31 = M2C_FIELD(&lbl_8029C310, s32*, 0x2C);
	var_r4   = 0;
	if (((void*)lbl_80303DC8 != NULL) && ((s32)M2C_FIELD(lbl_80303DC8, s32*, 0x34) == 2)) {
		var_r4 = 1;
	}
	if (temp_r31 == 0x15) {
		if (var_r4 != 0) {
			var_r29 = (u8*)lbl_8_rodata_186C + 6;
		} else {
			var_r29 = (u8*)lbl_8_rodata_186C + 2;
		}
	} else if (var_r4 != 0) {
		var_r29 = (u8*)lbl_8_rodata_186C + 4;
	} else {
		var_r29 = (u8*)lbl_8_rodata_186C;
	}
	if (((u32)(M2C_FIELD(arg0, s32*, 0x278) & 8) == 0)
	    && (IsAnnihilated__19nEnemyCommunicationFUc(M2C_FIELD(var_r29, u8*, 0)) != 0)) {
		M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) | 8);
		temp_r3_2                    = fn_80103178(0);
		if (temp_r3_2 != -1) {
			if (temp_r31 == 0x15) {
				fn_80111260(lbl_8042C610, temp_r3_2, 0x92);
			} else {
				fn_80111260(lbl_8042C610, temp_r3_2, 0x92);
			}
		}
	}
	if (((u32)(M2C_FIELD(arg0, s32*, 0x278) & 0x10) == 0)
	    && (IsAnnihilated__19nEnemyCommunicationFUc(M2C_FIELD(var_r29, u8*, 1)) != 0)) {
		M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) | 0x10);
		temp_r3_2                    = fn_80103178(0);
		if (temp_r3_2 != -1) {
			if (temp_r31 == 0x15) {
				fn_80111260(lbl_8042C610, temp_r3_2, 0x93);
			} else {
				fn_80111260(lbl_8042C610, temp_r3_2, 0x93);
			}
		}
	}
	temp_r3 = M2C_FIELD(arg0, s32*, 0x278);
	if (((u32)(temp_r3 & 8) != 0) && ((u32)(temp_r3 & 1) == 0)) {
		if (((EggTalkMan*)lbl_8042C610)->IsIdle()) {
			M2C_FIELD(arg0, s32*, 0x260) = 0x43;
			M2C_FIELD(arg0, s32*, 0x274) = 1;
			M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) | 1);
		}
	}
	temp_r3_2 = M2C_FIELD(arg0, s32*, 0x278);
	if (((u32)(temp_r3_2 & 0x10) != 0) && ((u32)(temp_r3_2 & 2) == 0)) {
		if (((EggTalkMan*)lbl_8042C610)->IsIdle()) {
			M2C_FIELD(arg0, s32*, 0x260) = 0x43;
			M2C_FIELD(arg0, s32*, 0x274) = 2;
			M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) | 2);
		}
	}
}

void fn_8_9EF3C(void)
{
	EggObject* temp_r3;

	temp_r3 = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x38);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C0FC);
		temp_r3->unk18 = (M2C_UNK*)&lbl_8_data_15E50[0];
		temp_r3->unk0  = lbl_8_data_15E4C;
		temp_r3->unk1E = 0x38;
		temp_r3->unk30 = 0;
		temp_r3->unk34 = 0;
		temp_r3->unk28 = 0;
		temp_r3->unk2C = 0;
	}
}

EggObject* fn_8_9EED4(EggObject* arg0, EggObject* arg1)
{
	__ct__7TObjectFP7TObject(arg0, arg1);
	arg0->unk18 = (M2C_UNK*)&lbl_8_data_15E50[0];
	arg0->unk0  = lbl_8_data_15E4C;
	arg0->unk1E = 0x38;
	arg0->unk30 = 0;
	arg0->unk34 = 0;
	arg0->unk28 = 0;
	arg0->unk2C = 0;
	return arg0;
}

EggObject* fn_8_9EE60(EggObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = (M2C_UNK*)&lbl_8_data_15E50[0];
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

/* TZakoRushCtrl::Exec: ends in the 2P modes, else runs the handler of the
 * current mode (0x28) with its phase (0x2C). */
void fn_8_9EDB4(void* arg0)
{
	if (eggKillMyself()) {
		M2C_FIELD(arg0, u16*, 4) |= 1;
		return;
	}
	(((TZakoRushCtrl*)arg0)->*((ZakoRushHandler*)lbl_8_data_15E0C)[M2C_FIELD(arg0, s32*, 0x28)])(
	    M2C_FIELD(arg0, s32*, 0x2C));
}

void fn_8_9EDB0(void) { }

void fn_8_9ED60(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2C) = 1;
			return;
		case 1:
			M2C_FIELD(arg0, s32*, 0x2C) = 2;
			return;
		case 2:
			M2C_FIELD(arg0, s32*, 0x28) = 1;
			M2C_FIELD(arg0, s32*, 0x2C) = 0;
			return;
	}
}

void fn_8_9ED10(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2C) = 1;
			return;
		case 1:
			M2C_FIELD(arg0, s32*, 0x2C) = 2;
			return;
		case 2:
			M2C_FIELD(arg0, s32*, 0x28) = 2;
			M2C_FIELD(arg0, s32*, 0x2C) = 0;
			return;
	}
}

void fn_8_9EC40(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			if (IsExistSummonEnemy__19nEnemyCommunicationFUc(M2C_FIELD(arg0, u8*, 0x34)) == 0) {
				M2C_FIELD(arg0, s32*, 0x28) = 3;
				M2C_FIELD(arg0, s32*, 0x2C) = 0;
				return;
			}
			Create__12TEnemySummonFUc(M2C_FIELD(arg0, u8*, 0x34));
			M2C_FIELD(arg0, s32*, 0x2C) = 1;
			return;
		case 1:
			if (IsAnnihilated__19nEnemyCommunicationFUc(M2C_FIELD(arg0, u8*, 0x34)) == 0) {
				return;
			}
			M2C_FIELD(arg0, u8*, 0x34)++;
			M2C_FIELD(arg0, s32*, 0x30) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x2C) = 2;
			return;
		case 2:
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x30));
			if ((s32)M2C_FIELD(arg0, s32*, 0x30) < 0) {
				M2C_FIELD(arg0, s32*, 0x2C) = 0;
			}
			return;
	}
}

void fn_8_9EBB8(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x2C) = 1;
			break;
		case 1:
			if (M2C_FIELD(lbl_8042C180, s8*, 0x20) == 0
			    && M2C_FIELD(lbl_8042C180, s8*, 0x1F) == 0) {
				if (lbl_8_bss_1914 != NULL) {
					lbl_8_bss_1914->unk260 = 0x5C;
				}
				M2C_FIELD(arg0, u16*, 4) |= 1;
			}
			break;
		case 2:
			break;
	}
}
}
