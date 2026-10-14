#include "types.h"

// TObjEnemyRinoliner (and its strategy base's destructor and vtable). The
// rinoliner's factory and editor record, which end this run, are the shared
// rel/rinoliner_create.cpp and rel/rinoliner_register.cpp units.
//
// Path-search and path-end helpers appear twice: as static inlines where
// retail inlines them into earlier functions, and as the out-of-line
// fn_8_B1828/fn_8_B193C/fn_8_B2A64/fn_8_B2ACC/fn_8_B28E4 copies retail keeps.
// The unit is built with -fp_contract off: retail never fuses multiply-add
// here.

typedef s32 M2C_UNK;

#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define FIELD(base, type, offset)     (*(type*)((u8*)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

typedef struct TEnemyParalysis TEnemyParalysis;
struct RwFrame;
extern "C" double fabs(double);

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef s32 RwOpCombineType;

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

typedef struct sParalysisParam {
	s32 activeFrames;
	s32 recoveryFrames;
	RwV3d offset;
} sParalysisParam;

/* A path: type 1 paths are the ones enemies ride. */
struct PathTag {
	s16 type;
	s16 numPoints;
	f32 length;
};

/* GetStatusOnPath's result: the point at a distance along the path. */
struct PathInfo {
	u8 pad00[0x10];
	f32 dist;
	RwV3d pos;
	u8 pad20[0x18];
	RwV3d dir;
};

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

/* The iron ball's creation parameters (TObjEnemyIronBall's sEnemyIronBall). */
struct IronBallParam {
	RwV3d pos;
	RwV3d dir;
	f32 speed;
	sAngle angle;
	s32 life;
	s32 homing;
	s32 light;

	IronBallParam()
	{
		pos.x = pos.y = pos.z = 0.0f;
		dir.x = dir.y = dir.z = 0.0f;
		angle.x = angle.y = angle.z = 0;
		life                        = 300;
		homing                      = 1;
		light                       = 8;
	}
};

/* A command from the course's controller to the rinoliner. */
struct RinoCommand {
	u8 type;
	u32 kind;
	RwV3d pos;
	s32 speedMode;
};

/* A player character: its position at +0x18. */
struct PlayerObj {
	u8 pad00[0x18];
	RwV3d pos;
};

struct HAnimNodeInfo {
	s32 nodeID;
	s32 nodeIndex;
	s32 flags;
	RwFrame* pFrame;
};

struct HAnimHierarchy {
	u8 pad00[0x10];
	HAnimNodeInfo* pNodeInfo;
};

/* An effect object placed by position and angle. */
struct EffectObj {
	u8 pad00[0x80];
	RwV3d pos;
	sAngle ang;

	void SetPosAng(const RwV3d* p, const sAngle* a)
	{
		if (p != NULL) {
			pos = *p;
		}
		ang = *a;
	}
};

/* The pause/event flags lbl_8042C180 points at. */
struct GameFlags {
	u8 pad00[0x1F];
	s8 flag1F;
	s8 flag20;
	s8 flag21;
};

struct PathManager {
	u8 pad00[0x28];
	PathTag** tags;
};

typedef struct RwFrame {
	/* 0x0 */ f32 unk0; /* inferred */
} RwFrame;              /* size >= 0x4 */

typedef struct TObject {
	/* 0x000 */ M2C_UNK* unk0;   /* inferred */
	/* 0x004 */ char pad4[0x14]; /* maybe part of unk0[6]? */
	/* 0x018 */ M2C_UNK* unk18;  /* inferred */
	/* 0x01C */ char pad1C[2];
	/* 0x01E */ s16 unk1E;        /* inferred */
	/* 0x020 */ char pad20[8];    /* maybe part of unk1E[5]? */
	/* 0x028 */ M2C_UNK unk28;    /* inferred */
	/* 0x02C */ s16 unk2C;        /* inferred */
	/* 0x02E */ s16 unk2E;        /* inferred */
	/* 0x030 */ char pad30[0x58]; /* maybe part of unk2E[0x2D]? */
	/* 0x088 */ f32 unk88;        /* inferred */
	/* 0x08C */ f32 unk8C;        /* inferred */
	/* 0x090 */ f32 unk90;        /* inferred */
	/* 0x094 */ char pad94[0x1C]; /* maybe part of unk90[8]? */
	/* 0x0B0 */ void* unkB0;      /* inferred */
	/* 0x0B4 */ void* unkB4;      /* inferred */
	/* 0x0B8 */ char padB8[0x1C]; /* maybe part of unkB4[8]? */
	/* 0x0D4 */ s32 unkD4;        /* inferred */
	/* 0x0D8 */ char padD8[0xC];  /* maybe part of unkD4[4]? */
	/* 0x0E4 */ M2C_UNK* unkE4;   /* inferred */
	/* 0x0E8 */ void* unkE8;      /* inferred */
	/* 0x0EC */ HAnimHierarchy* unkEC;
	/* 0x0F0 */ char padF0[0x40]; /* maybe part of unkEC[0x11]? */
	/* 0x130 */ f32 unk130;       /* inferred */
	/* 0x134 */ f32 unk134;       /* inferred */
	/* 0x138 */ char pad138[4];
	/* 0x13C */ s32 unk13C;        /* inferred */
	/* 0x140 */ f32 unk140;        /* inferred */
	/* 0x144 */ f32 unk144;        /* inferred */
	/* 0x148 */ f32 unk148;        /* inferred */
	/* 0x14C */ s32 unk14C;        /* inferred */
	/* 0x150 */ s32 unk150;        /* inferred */
	/* 0x154 */ s32 unk154;        /* inferred */
	/* 0x158 */ f32 unk158;        /* inferred */
	/* 0x15C */ f32 unk15C;        /* inferred */
	/* 0x160 */ f32 unk160;        /* inferred */
	/* 0x164 */ char pad164[0x24]; /* maybe part of unk160[0xA]? */
	/* 0x188 */ s32 unk188;        /* inferred */
	/* 0x18C */ char pad18C[0x10]; /* maybe part of unk188[5]? */
	/* 0x19C */ s32 unk19C;        /* inferred */
	/* 0x1A0 */ f32 unk1A0;        /* inferred */
	/* 0x1A4 */ f32 unk1A4;        /* inferred */
	/* 0x1A8 */ char pad1A8[0x18]; /* maybe part of unk1A4[7]? */
	/* 0x1C0 */ f32 unk1C0;        /* inferred */
	/* 0x1C4 */ f32 unk1C4;        /* inferred */
	/* 0x1C8 */ f32 unk1C8;        /* inferred */
	/* 0x1CC */ f32 unk1CC;        /* inferred */
	/* 0x1D0 */ f32 unk1D0;        /* inferred */
	/* 0x1D4 */ f32 unk1D4;        /* inferred */
	/* 0x1D8 */ char pad1D8[0x50]; /* maybe part of unk1D4[0x15]? */
	/* 0x228 */ M2C_UNK** unk228;  /* inferred */
	/* 0x22C */ char pad22C[0x14]; /* maybe part of unk228[6]? */
	/* 0x240 */ s32 unk240;        /* inferred */
	/* 0x244 */ M2C_UNK** unk244;  /* inferred */
	/* 0x248 */ f32 unk248;        /* inferred */
	/* 0x24C */ s16* unk24C;       /* inferred */
	/* 0x250 */ char pad250[4];
	/* 0x254 */ RwV3d joinPos; /* where the next path is joined */
	/* 0x260 */ RwV3d joinVel;
	/* 0x26C */ sAngle joinAng;
	/* 0x278 */ f32 unk278;   /* inferred */
	/* 0x27C */ s32 unk27C;   /* inferred */
	/* 0x280 */ s32 unk280;   /* inferred */
	/* 0x284 */ s32 unk284;   /* inferred */
	/* 0x288 */ void* unk288; /* inferred */
	/* 0x28C */ s32 unk28C;   /* inferred */
	/* 0x290 */ s32 unk290;   /* inferred */
	/* 0x294 */ RwV3d muzzle; /* the barrel tip */
	/* 0x2A0 */ RwV3d aim;    /* the barrel direction */
	/* 0x2AC */ f32 unk2AC;   /* inferred */
	/* 0x2B0 */ s32 unk2B0;   /* inferred */
	/* 0x2B4 */ s32 unk2B4;   /* inferred */
	/* 0x2B8 */ s32 unk2B8;   /* inferred */
	/* 0x2BC */ s32 unk2BC;   /* inferred */
	/* 0x2C0 */ s32 unk2C0;   /* inferred */
	/* 0x2C4 */ s32 fired;
	/* 0x2C8 */ s32 unk2C8;              /* inferred */
	/* 0x2CC */ s32 unk2CC;              /* inferred */
	/* 0x2D0 */ TEnemyParalysis* unk2D0; /* inferred */
	/* 0x2D4 */ f32 unk2D4;              /* inferred */
	/* 0x2D8 */ f32 unk2D8;              /* inferred */
	/* 0x2DC */ f32 unk2DC;              /* inferred */
	/* 0x2E0 */ s32 unk2E0;              /* inferred */
	/* 0x2E4 */ s32 unk2E4;              /* inferred */
	/* 0x2E8 */ s32 unk2E8;              /* inferred */
	/* 0x2EC */ s32 unk2EC;              /* inferred */
	/* 0x2F0 */ f32 unk2F0;              /* inferred */
	/* 0x2F4 */ f32 unk2F4;              /* inferred */
	/* 0x2F8 */ f32 unk2F8;              /* inferred */
	/* 0x2FC */ f32 unk2FC;              /* inferred */
	/* 0x300 */ s32 unk300;              /* inferred */
	/* 0x304 */ RwFrame* unk304;
	/* 0x308 */ u32 unk308;   /* inferred */
	/* 0x30C */ u32 unk30C;   /* inferred */
	/* 0x310 */ void* unk310; /* inferred */
	/* 0x314 */ void* unk314; /* inferred */
	/* 0x318 */ s32 unk318;   /* inferred */
	/* 0x31C */ s32 unk31C;   /* inferred */
} TObject;                    /* size >= 0x320 */

/* nEnemyMotion's ENEMY_MOTION. */
struct EnemyMotion {
	void* pHAA;
	s32 mtnmode;
	s32 next;
	f32 start;
	f32 end;
	f32 frame;
	f32 racio;
	char* pName;
	u32 uid;
};

/* The spawn record fn_8_6BE14 takes. */
struct EffectParam {
	f32* pos;
	f32* vel;
	f32 unk08;
	s32 unk0C;
	f32 unk10;
	s32 unk14;
	f32 unk18;
	f32* color0;
	f32* color1;
};

typedef struct ObjectEntry {
	const char* name;
	void (*load)(void);
	void (*unload)(void);
	void (*create)(void);
	void* unk10;
	u32 flags;
	u32 unk18;
	s16 unk1C;
	s16 unk1E;
	u8 unk20;
	u8 unk21;
	u8 pad22[2];
	const char* fieldTypes;
	const char** fieldNames;
	u8 pad2C[4];
} ObjectEntry;

/* The rinoliner's editor fields. */
struct RinolinerParams {
	s8 type;
	s8 pathType;
	s8 homing;
	s8 unused;
	f32 weaponSpeed;
	s32 attackInterval;
	f32 speedMin;
	f32 speed;
	f32 speedMax;
};

struct SetData {
	u8 pad00[0x2C];
	RinolinerParams* params;
};

template <typename T> inline const T& Clamp(const T& v, const T& lo, const T& hi)
{
	if (v < lo) {
		return lo;
	}
	if (v > hi) {
		return hi;
	}
	return v;
}

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

class TSubDispatch
{
public:
	virtual void vslot2(M2C_UNK);
	virtual void vslot3(void*);
};

extern "C" {
M2C_UNK SetLightNum__7nRenderFUi(s32);
f32 DistanceP2SegL__FP5RwV3dP5RwV3dP5RwV3dP5RwV3d(RwV3d*, RwV3d*, RwV3d*, RwV3d*);

M2C_UNK __dl__FPv(void*);                                             /* extern */
s32 fn_80017800(void*);                                               /* extern */
void* fn_80020BD8(void*, s32);                                        /* extern */
void fn_80021824(void*);                                              /* extern */
M2C_UNK Entry__7C_COLLIFv(void*);                                     /* extern */
M2C_UNK ClearInfo__7C_COLLIFv(void*);                                 /* extern */
int CheckMustKill__10TObjSetObjFv(void*);                             /* extern */
M2C_UNK fn_8006298C(s32, RwV3d*, sAngle*);                            /* extern */
M2C_UNK fn_800A3D48(void*);                                           /* extern */
s32 CheckDamage2__9TObjEnemyFv(void*);                                /* extern */
M2C_UNK fn_800A5B34(void*);                                           /* extern */
s32 CheckCameraFrustumTest__9TObjEnemyFPC5RwV3df(TObject*, s32, f32); /* extern */
f32 SCPathPntNearToOnpos__FP7PATHTAGP5RwV3dP5RwV3dPff(
    PathTag*, RwV3d*, RwV3d*, f32*, f32);                 /* extern */
M2C_UNK fn_800B4A38(u32, s32, void*, s32, s32, s32, s32); /* extern */
M2C_UNK AddScore__14TEnemyScoreManFii(u32, s32, s32);     /* extern */
M2C_UNK CreateInstance__14TEnemyScoreManFv();             /* extern */
M2C_UNK fn_8014FF2C(void*);                               /* extern */
M2C_UNK CreateItemBox__8nItemBoxFP5RwV3d(s32);            /* extern */
M2C_UNK fn_8_B5160(IronBallParam*);                       /* extern */
extern GameFlags* lbl_8042C180;
extern M2C_UNK lbl_8042C1A4;
extern void* lbl_8042C208;
extern u32 lbl_8042C388;
extern u32 EnemyScoreMan__14TEnemyScoreMan;

M2C_UNK SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(void*, void*, void*);      /* extern */
M2C_UNK Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(void*, void*, s32); /* extern */
void* __ct__10HAnimClassFv(void*);                                                /* extern */
TEnemyParalysis* __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(
    void*, TObject*, sParalysisParam*);                                                 /* extern */
void* __ct__15sParalysisParamFv(void*);                                                 /* extern */
void* __dt__10HAnimClassFv(void*, s32);                                                 /* extern */
M2C_UNK Free__9THeapCtrlFPv(s32, void*);                                                /* extern */
TEnemyParalysis* Malloc__9THeapCtrlFUi(s32, M2C_UNK);                                   /* extern */
M2C_UNK Init__7C_COLLIFP8CCL_INFOiUc(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);             /* extern */
void* __nw__FUl(u32);                                                                   /* extern */
s32 OnEdit__10TObjSetObjFv(void**);                                                     /* extern */
M2C_UNK objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(void*, s32); /* extern */
s32 objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(
    HAnimHierarchy*, s32);                               /* extern */
RwFrame* objRwFrameGetFrame__FP7RwFramei(RwFrame*, s32); /* extern */
M2C_UNK objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(
    u32, M2C_UNK);                                                     /* extern */
void* fn_800628D0(s32, f32*, s32*);                                    /* extern */
M2C_UNK fn_800A7088(void*, M2C_UNK);                                   /* extern */
M2C_UNK fn_800A714C();                                                 /* extern */
s32 GetStatusOnPath__FP7PATHTAGP8PATHINFO(PathTag*, PathInfo*);        /* extern */
M2C_UNK GetPointDataOnPath__FP7PATHTAGiP5RwV3d(PathTag*, s32, RwV3d*); /* extern */
f32 Distance2P2P__FPC5RwV3dPC5RwV3d(const RwV3d*, const RwV3d*);       /* extern */
M2C_UNK GetZYAngleForTheTargetPoint__FPC5RwV3dPC5RwV3dPi(
    const RwV3d*, const RwV3d*, sAngle*);                             /* extern */
s32 VectorAngle__FP5RwV3dP5RwV3dP5RwV3d(RwV3d*, RwV3d*, RwV3d*);      /* extern */
s32 AdjustAngle__Fiii(s32, s32, s32);                                 /* extern */
f32 fn_800D7AE4(s32);                                                 /* extern */
f32 fn_800D7B00(s32);                                                 /* extern */
void* __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID(void*, TObject*, s32); /* extern */
M2C_UNK ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*); /* extern */
M2C_UNK LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*);                                                             /* extern */
u32 SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK); /* extern */
s32 SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK Delete__14TEnemyDataBaseF14eEnemyDataBase(u32, M2C_UNK);                    /* extern */
M2C_UNK Add__14TEnemyDataBaseF14eEnemyDataBasePc(u32, M2C_UNK, const char*);        /* extern */
M2C_UNK __ct__14TEnemyDataBaseFv();                                                 /* extern */
s32 GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(void*, f32);                     /* extern */
M2C_UNK fn_80139784(void*, TObject*, RwV3d*);                                       /* extern */
void* fn_80139984(M2C_UNK, M2C_UNK, M2C_UNK);                                       /* extern */
void* fn_80150588(s32);                                                             /* extern */
M2C_UNK fn_80150958(void*);                                                         /* extern */
M2C_UNK fn_80195790(RwMatrix*, const RwV3d*, f32, f32, s32);                        /* extern */
M2C_UNK fn_80196050(RwMatrix*, const RwV3d*, s32);                                  /* extern */
M2C_UNK fn_801990E0(RwV3d*, const RwV3d*);                                          /* extern */
M2C_UNK fn_8019941C(RwV3d*, const RwV3d*, s32, const RwMatrix*);                    /* extern */
RwMatrix* fn_8019E8EC(RwFrame*);                                                    /* extern */
M2C_UNK fn_8019EB94(RwFrame*, const RwV3d*, s32);                                   /* extern */
M2C_UNK fn_8019ECCC(RwFrame*, RwMatrix*, s32);                                      /* extern */
M2C_UNK fn_8019ED68(RwFrame*, const RwV3d*, f32, s32);                              /* extern */
s32 rand();                                                                         /* extern */
M2C_UNK fn_8_6BE14(s32, EffectParam*);                                              /* extern */
M2C_UNK fn_8_B52F4();                                                               /* extern */
M2C_UNK fn_8_B5308();                                                               /* extern */
M2C_UNK fn_8_B5620(void*, TObject*);                                                /* extern */
void* fn_8_B5B3C(void*);                                                            /* extern */
extern const RwV3d AxisX;
extern const RwV3d AxisY;
extern const RwV3d AxisZ;
extern M2C_UNK lbl_8029C310;
extern PlayerObj* lbl_802AD090[];
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern PathManager* lbl_8042C380;
extern u32 mpDataBase__14TEnemyDataBase;
extern s32 EffSparkTp;

extern void* lbl_8_data_17060[];
void fn_8_B49D8();
void fn_8_B49E0();
void DispShadow__9TObjEnemyFv();
void Virtual33D94__9TObjEnemyFv();
void Virtual33D98__9TObjEnemyFv();
void Virtual33DA0__9TObjEnemyFv();
void Virtual33DA4__9TObjEnemyFv();
void Exec__9TObjEnemyFv();
void Disp__9TObjEnemyFv();
void TDisp__9TObjEnemyFv();
void CheckCameraFrustumTestForShadow__9TObjEnemyFPC5RwV3df();
void DestroyMyself__9TObjEnemyFv();
void Explosion__9TObjEnemyFv();
void InitMode__9TObjEnemyF8ENEMY_MD();
void ExecMode__9TObjEnemyF8ENEMY_MD();
void ExitMode__9TObjEnemyF8ENEMY_MD();
void CanCheckTechnicPointForThunderShoot__9TObjEnemyFv();
void IsSleep__9TObjEnemyFv();
void GetCurrentLightNum__9TObjEnemyFv();
void DispEnemySetting__9TObjEnemyFv();
void PDisp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Error__7TObjectFPc();
void Render__7TObjectFv();
void* fn_8_B3CC4(void* arg0, s16 arg1);
void fn_8_B43E8(void* arg0, SetData* data);

M2C_UNK** fn_8_B0924(M2C_UNK** arg0, s16 arg1);
s32 fn_8_B0974(void* arg0);
void fn_8_B09F8(void* arg0, s32 arg1);
void fn_8_B0A1C(void* arg0);
s32 fn_8_B0B64(s32 arg0);
void fn_8_B1660(TObject* self, RinoCommand* cmd);
void fn_8_B321C(TObject* arg0, const RwV3d* target, s32 adjust);
s32 fn_8_B1A0C(TObject* self, s32 arg1, f32 radius);
void fn_8_B1A90(TObject* self);
void fn_8_B1A94(TObject* self);
extern void* lbl_8_bss_1A50[3];
extern void* lbl_8_bss_1A5C;
void fn_8_B2BB4(TObject* self);
void fn_8_B0D34(TObject* self);
void fn_8_B1AE8(TObject* self);
void fn_8_B1C1C(TObject* self);
void fn_8_B3598(TObject* self);
void fn_8_B2578(TObject* self, s32 mode, s32 phase);
void fn_8_AF86C();

/* The unreferenced { 0, 1.5, 0 } vector every Stage 11 object unit carries at
 * the head of its .rodata, the way an internal-linkage const from a shared
 * header lands in each translation unit that includes it. */
#pragma force_active on
static const RwV3d lbl_8_rodata_1B88 = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

const RwV3d lbl_8_rodata_1B94  = { 0.0f, 5.0f, 0.0f };
const RwV3d lbl_8_rodata_1BA0  = { 0.0f, 0.0f, 1.0f };
const RwV3d lbl_8_rodata_1BAC  = { 0.0f, 0.0f, 1.0f };
const sAngle lbl_8_rodata_1BB8 = { 0, 0, 0 };
const sAngle lbl_8_rodata_1BC4 = { 0, 0, 0 };

/* TEnemyStrategy's vtable (base of the rinoliner strategy): the destructor
 * and the shared SetUp. */
void* lbl_8_data_16B98[6] = { 0, 0, (void*)fn_8_B0924, (void*)fn_8_AF86C, 0, 0 };

/* The rinoliner's collision setup. */
u32 lbl_8_data_16BB0[12] = { 0x1600FF21, 0x00000400, 0x00000000, 0x41400000, 0xC0800000, 0x41500000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

char lbl_8_data_16BE0[] = "en_rhino.anm";
char lbl_8_data_16BF0[] = "en_rhino_fly.anm";
char lbl_8_data_16C04[] = "en_rhino_fly2.anm";

/* The motion table: walk, fly and the second fly loop. */
EnemyMotion lbl_8_data_16C18[4] = {
	{ NULL, 3, 0, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_16BE0, 4 },
	{ NULL, 4, 2, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_16BF0, 6 },
	{ NULL, 3, 0, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_16C04, 7 },
	{ NULL, 14, 0, 0.0f, 0.0f, 0.0f, 0.0f, NULL, 0 },
};

/* The exhaust effect's spawn parameters. */
RwV3d lbl_8_data_16CA8       = { 0.0f, -2.0f, 6.0f };
RwV3d lbl_8_data_16CB4       = { 0.0f, 0.5f, 0.6f };
f32 lbl_8_data_16CC0[4]      = { 1.0f, 1.0f, 0.0f, 1.0f };
f32 lbl_8_data_16CD0[4]      = { 1.0f, 0.01f, 0.01f, 0.5f };
EffectParam lbl_8_data_16CE0 = { NULL, NULL, 0.2f, 1, -300000.0f, 20, 2.25f, NULL, NULL };

char lbl_8_data_16D04[] = "TYPE";
char lbl_8_data_16D0C[] = "PATH TYPE";
char lbl_8_data_16D18[] = "IRONBALL HOMING";
char lbl_8_data_16D28[] = "Not in use";
char lbl_8_data_16D34[] = "WEAPON SPEED";
char lbl_8_data_16D44[] = "ATTACK INTERVAL";
char lbl_8_data_16D54[] = "MOVE SPEED MIN";
char lbl_8_data_16D64[] = "MOVE SPEED";
char lbl_8_data_16D70[] = "MOVE SPEED MAX";

char* rinolinerObjectFieldNames[9] = {
	lbl_8_data_16D04,
	lbl_8_data_16D0C,
	lbl_8_data_16D18,
	lbl_8_data_16D28,
	lbl_8_data_16D34,
	lbl_8_data_16D44,
	lbl_8_data_16D54,
	lbl_8_data_16D64,
	lbl_8_data_16D70,
};

char lbl_8_data_16DA4[]   = "STANDARD";
char lbl_8_data_16DB0[]   = "ATTACK";
char* lbl_8_data_16DB8[2] = { lbl_8_data_16DA4, lbl_8_data_16DB0 };
char lbl_8_data_16DC0[]   = "LOOP";
char* lbl_8_data_16DC8[2] = { lbl_8_data_16DA4, lbl_8_data_16DC0 };
char lbl_8_data_16DD0[]   = "IRONBALL HOMING ON";
char lbl_8_data_16DE4[]   = "IRONBALL HOMING OFF";
char* lbl_8_data_16DF8[2] = { lbl_8_data_16DD0, lbl_8_data_16DE4 };

/* The editor's lower and upper bounds for the three choice fields, then the
 * three speed fields. */
#pragma explicit_zero_data on
s8 lbl_8_data_16E00 = 0;
#pragma explicit_zero_data reset
s8 lbl_8_data_16E01 = 1;
#pragma explicit_zero_data on
s8 lbl_8_data_16E02 = 0;
#pragma explicit_zero_data reset
s8 lbl_8_data_16E03 = 1;
#pragma explicit_zero_data on
s8 lbl_8_data_16E04 = 0;
#pragma explicit_zero_data reset
s8 lbl_8_data_16E05 = 1;
#pragma explicit_zero_data on
f32 lbl_8_data_16E08 = 0.0f;
#pragma explicit_zero_data reset
f32 lbl_8_data_16E0C = 100.0f;
#pragma explicit_zero_data on
f32 lbl_8_data_16E10 = 0.0f;
#pragma explicit_zero_data reset
f32 lbl_8_data_16E14 = 100.0f;
#pragma explicit_zero_data on
f32 lbl_8_data_16E18 = 0.0f;
#pragma explicit_zero_data reset
f32 lbl_8_data_16E1C = 100.0f;

char lbl_8_data_16E20[] = "TObjEnemyRinoliner";
char* lbl_8_data_16E34  = lbl_8_data_16E20;

/* TObjEnemyRinoliner's vtable: the TObject part, then from slot 11 the
 * TObjEnemy part at +0xB0, reached through the fn_8_B49D8 thunk. */
void* lbl_8_data_16E38[42] = {
	0,
	0,
	(void*)fn_8_B3CC4,
	(void*)Exec__9TObjEnemyFv,
	(void*)Disp__9TObjEnemyFv,
	(void*)TDisp__9TObjEnemyFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	0,
	0,
	(void*)fn_8_B49D8,
	(void*)fn_8_B0974,
	(void*)DestroyMyself__9TObjEnemyFv,
	(void*)Explosion__9TObjEnemyFv,
	(void*)InitMode__9TObjEnemyF8ENEMY_MD,
	(void*)ExecMode__9TObjEnemyF8ENEMY_MD,
	(void*)ExitMode__9TObjEnemyF8ENEMY_MD,
	(void*)fn_8_B2578,
	(void*)fn_8_B1C1C,
	(void*)fn_8_B1AE8,
	(void*)fn_8_B1A94,
	(void*)fn_8_B49E0,
	(void*)DispShadow__9TObjEnemyFv,
	(void*)fn_8_B1A90,
	(void*)Virtual33D94__9TObjEnemyFv,
	(void*)fn_8_B0B64,
	(void*)fn_8_B1A0C,
	(void*)CheckCameraFrustumTestForShadow__9TObjEnemyFPC5RwV3df,
	(void*)fn_8_B0A1C,
	(void*)CanCheckTechnicPointForThunderShoot__9TObjEnemyFv,
	(void*)IsSleep__9TObjEnemyFv,
	(void*)fn_8_B09F8,
	(void*)Virtual33D98__9TObjEnemyFv,
	(void*)GetCurrentLightNum__9TObjEnemyFv,
	(void*)fn_8_B1660,
	(void*)DispEnemySetting__9TObjEnemyFv,
	(void*)Virtual33DA0__9TObjEnemyFv,
	(void*)Virtual33DA4__9TObjEnemyFv,
	(void*)fn_8_B43E8,
};

/* GetNearestPathTagALL: the nearest rideable path by either end. Sets the
 * direction flag to 1 when the start is nearer, 0 for the end. */
static inline PathTag* GetNearestPathTagALL(
    TObject* self, PathTag* exclude, const RwV3d* pos, f32 dist)
{
	PathTag** tags;
	PathTag* nearest;
	const RwV3d* from;
	f32 best;
	RwV3d point;
	f32 d;

	from    = pos;
	nearest = NULL;
	best    = dist;
	tags    = lbl_8042C380->tags;

	for (; *tags != NULL; tags++) {
		if (*tags != exclude && (*tags)->type == 1) {
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(*tags, 0, &point);
			d = Distance2P2P__FPC5RwV3dPC5RwV3d(from, &point);
			if (d < best) {
				best         = d;
				nearest      = *tags;
				self->unk2B4 = 1;
			}
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(*tags, (*tags)->numPoints - 1, &point);
			d = Distance2P2P__FPC5RwV3dPC5RwV3d(from, &point);
			if (d < best) {
				best         = d;
				nearest      = *tags;
				self->unk2B4 = 0;
			}
		}
	}
	return nearest;
}

/* GetNearestPathTag: the rideable path whose start is nearest. */
/* The same search from the end of the current path, skipping it. */
static inline PathTag* GetNextPathTagALL(TObject* self, const RwV3d* pos, f32 dist)
{
	PathTag** tags;
	PathTag* current;
	PathTag* nearest;
	const RwV3d* from;
	f32 best;
	RwV3d point;
	f32 d;

	from    = pos;
	current = (PathTag*)self->unk24C;
	nearest = NULL;
	best    = dist;
	tags    = lbl_8042C380->tags;
	for (; *tags != NULL; tags++) {
		if (*tags != current && (*tags)->type == 1) {
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(*tags, 0, &point);
			d = Distance2P2P__FPC5RwV3dPC5RwV3d(from, &point);
			if (d < best) {
				best         = d;
				nearest      = *tags;
				self->unk2B4 = 1;
			}
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(*tags, (*tags)->numPoints - 1, &point);
			d = Distance2P2P__FPC5RwV3dPC5RwV3d(from, &point);
			if (d < best) {
				best         = d;
				nearest      = *tags;
				self->unk2B4 = 0;
			}
		}
	}
	return nearest;
}

static inline PathTag* GetNearestPathTag(TObject* self, const RwV3d* pos, f32 dist)
{
	PathTag** tags;
	PathTag* nearest;
	const RwV3d* from;
	f32 best;
	RwV3d point;
	f32 d;

	from    = pos;
	nearest = NULL;
	best    = dist;
	tags    = lbl_8042C380->tags;

	for (; *tags != NULL; tags++) {
		if ((*tags)->type == 1) {
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(*tags, 0, &point);
			d = Distance2P2P__FPC5RwV3dPC5RwV3d(from, &point);
			if (d < best) {
				best         = d;
				nearest      = *tags;
				self->unk2B4 = 1;
			}
		}
	}
	return nearest;
}

/* The same search as the constructor inlines it (its locals land in a
 * different order). */
static inline PathTag* GetNearestPathTagCtor(TObject* self, const RwV3d* pos, f32 dist)
{
	PathTag** tags;
	const RwV3d* from;
	PathTag* nearest;
	f32 best;
	RwV3d point;
	f32 d;

	from    = pos;
	nearest = NULL;
	best    = dist;
	tags    = lbl_8042C380->tags;

	for (; *tags != NULL; tags++) {
		if ((*tags)->type == 1) {
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(*tags, 0, &point);
			d = Distance2P2P__FPC5RwV3dPC5RwV3d(from, &point);
			if (d < best) {
				best         = d;
				nearest      = *tags;
				self->unk2B4 = 1;
			}
		}
	}
	return nearest;
}

/* GetNearestPathTag again, as MoveOnPath inlines it to pick the next path
 * (its locals land in a different order). */
static inline PathTag* GetNextPathTag(TObject* self, const RwV3d* pos, f32 dist)
{
	PathTag* nearest;
	const RwV3d* from;
	PathTag** tags;
	f32 best;
	RwV3d point;
	f32 d;

	from    = pos;
	nearest = NULL;
	best    = dist;
	tags    = lbl_8042C380->tags;

	for (; *tags != NULL; tags++) {
		if ((*tags)->type == 1) {
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(*tags, 0, &point);
			d = Distance2P2P__FPC5RwV3dPC5RwV3d(from, &point);
			if (d < best) {
				best         = d;
				nearest      = *tags;
				self->unk2B4 = 1;
			}
		}
	}
	return nearest;
}

/* TEnemyStrategy's destructor, emitted with its vtable here. */
M2C_UNK** fn_8_B0924(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_16B98;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

/* CheckDamage2: an electric hit stuns the rinoliner instead of hurting it. */
s32 fn_8_B0974(void* arg0)
{
	void* hit;
	u32 shocked;

	fn_80021824(&lbl_8042C1A4);
	hit = fn_80020BD8((u8*)arg0 + 0x28, 0x16);
	if (hit != NULL) {
		shocked = M2C_FIELD(hit, u32*, 4);
	} else {
		shocked = 0;
	}
	if (shocked != 0) {
		M2C_FIELD(arg0, f32*, 0x1A4) = 0.0f;
		M2C_FIELD(arg0, s32*, 0x230) = -1;
		return 1;
	}
	return CheckDamage2__9TObjEnemyFv(arg0);
}

/* AddItemBox. */
void fn_8_B09F8(void* arg0, s32 arg1)
{
	CreateItemBox__8nItemBoxFP5RwV3d(arg1);
}

/* AddScore. */
void fn_8_B0A1C(void* arg0)
{
	if (EnemyScoreMan__14TEnemyScoreMan == 0U) {
		CreateInstance__14TEnemyScoreManFv();
	}
	AddScore__14TEnemyScoreManFii(
	    EnemyScoreMan__14TEnemyScoreMan, M2C_FIELD(arg0, s32*, 0x230), 0xC8);
}

/* CanFire: the leader is between 1600 and 40000 units away. */
s32 fn_8_B0A74(void* arg0)
{
	f32 dist;
	PlayerObj* player;

	if (M2C_FIELD(arg0, s32*, 0x2CC) != -1) {
		player = lbl_802AD090[M2C_FIELD(arg0, s32*, 0x2CC)];
		if (player != NULL) {
			dist = Distance2P2P__FPC5RwV3dPC5RwV3d(&player->pos, (RwV3d*)((u8*)arg0 + 0x140));
			if (1600.0f <= dist && dist <= 40000.0f) {
				return 1;
			}
		}
	}
	return 0;
}

/* UpdateAdjustAngle: turn faster at low speed. */
void fn_8_B0B00(void* arg0)
{
	f32 speed = M2C_FIELD(arg0, f32*, 0x2FC);

	if (speed < 2.0f) {
		M2C_FIELD(arg0, s32*, 0x2B8) = 0x70;
		M2C_FIELD(arg0, s32*, 0x2BC) = 0x70;
		return;
	}
	if (speed >= 2.0f && speed < 5.0f) {
		M2C_FIELD(arg0, s32*, 0x2B8) = 0x100;
		M2C_FIELD(arg0, s32*, 0x2BC) = 0x100;
		return;
	}
	M2C_FIELD(arg0, s32*, 0x2B8) = 0x400;
	M2C_FIELD(arg0, s32*, 0x2BC) = 0x400;
}

/* KillMySelf. */
s32 fn_8_B0B64(s32 arg0)
{
	return CheckMustKill__10TObjSetObjFv((u8*)arg0 + 0xB0) != 0;
}

/* RwV3dDotProductMacro. */
#define RwV3dDotProduct(a, b) ((((a)->x * (b)->x) + ((a)->y * (b)->y)) + ((a)->z * (b)->z))

/* Whether the nearest far-off leader is ahead along the path: 1 ahead,
 * 0 behind, 2 when there is no such leader. */
s32 fn_8_B0B94(TObject* self)
{
	PathInfo info;
	RwV3d toPlayer;
	s32 leader;
	PlayerObj* player;

	if (self->unk24C == NULL) {
		return 2;
	}
	leader = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(&self->unk140, 100000000.0f);
	if (leader != -1) {
		player = lbl_802AD090[leader];
		if (player != NULL
		    && Distance2P2P__FPC5RwV3dPC5RwV3d(&player->pos, (RwV3d*)&self->unk140) > 10000.0f) {
			toPlayer.x = player->pos.x - self->unk140;
			toPlayer.y = player->pos.y - self->unk144;
			toPlayer.z = player->pos.z - self->unk148;
			fn_801990E0(&toPlayer, &toPlayer);
			info.dist = self->unk248;
			if (GetStatusOnPath__FP7PATHTAGP8PATHINFO((PathTag*)self->unk24C, &info) == 0) {
				return 2;
			}
			RwV3d dir = info.dir;
			if (self->unk2B4 == 0) {
				dir.x *= -1.0f;
				dir.y *= -1.0f;
				dir.z *= -1.0f;
			}
			if (RwV3dDotProduct(&toPlayer, &dir) < 0.0f) {
				return 0;
			}
			return 1;
		}
	}
	return 2;
}

static inline void SpeedDown(TObject* self)
{
	self->unk2FC *= 0.97f;
	if (self->unk2FC < self->unk2F4) {
		self->unk2FC = self->unk2F4;
	}
}

static inline void SpeedUp(TObject* self)
{
	self->unk2FC *= 1.05f;
	if (self->unk2FC > self->unk2F8) {
		self->unk2FC = self->unk2F8;
	}
}

static inline void SpeedKeep(TObject* self)
{
	f32 speed = self->unk2FC;
	f32 base  = self->unk2F0;

	if (speed > base) {
		self->unk2FC *= 0.97f;
	} else if (speed < base) {
		self->unk2FC *= 1.05f;
	} else {
		self->unk2FC = base;
	}
}

#pragma auto_inline off
/* CalcMoveSpeed: slow down when the leader is behind, speed up when ahead. */
void fn_8_B0D34(TObject* self)
{
	s32 mode = self->unk31C;

	if (mode == 0) {
		switch (fn_8_B0B94(self)) {
			case 0:
				SpeedDown(self);
				break;
			case 1:
				SpeedUp(self);
				break;
			case 2:
				SpeedKeep(self);
				break;
		}
	} else if (mode == 1) {
	} else if (mode == 2) {
		SpeedDown(self);
	} else if (mode == 3) {
		SpeedKeep(self);
	} else if (mode == 4) {
		SpeedUp(self);
	}
}
#pragma auto_inline reset

/* Head for the joining point on the new path at the current speed. */
static inline void StartMoveToPath(TObject* self)
{
	FIELD(self, s32, 0x27C) = 0;
	self->joinVel.x         = self->joinPos.x - self->unk140;
	self->joinVel.y         = self->joinPos.y - self->unk144;
	self->joinVel.z         = self->joinPos.z - self->unk148;
	fn_801990E0(&self->joinVel, &self->joinVel);
	self->joinVel.x *= self->unk2FC;
	self->joinVel.y *= self->unk2FC;
	self->joinVel.z *= self->unk2FC;
	self->unkD4 = 1;
	if (lbl_8042C388 != 0U) {
		fn_800B4A38(lbl_8042C388, 0x4038, &self->unk140, 0, 1, 0, 0);
	}
}

/* PreChangePathSet: join the path nearest the commanded point, facing the
 * way that runs toward it. */
void fn_8_B1078(TObject* self)
{
	PathInfo info;
	RwV3d point;
	RwV3d dir;
	sAngle ang;
	f32 t;
	PathTag** tags;
	PathTag* nearest;
	f32 best;
	f32 bestT;
	f32 d;

	nearest = NULL;
	best    = 9999999.0f;
	tags    = lbl_8042C380->tags;
	for (; *tags != NULL; tags++) {
		if ((*tags)->type == 1) {
			d = SCPathPntNearToOnpos__FP7PATHTAGP5RwV3dP5RwV3dPff(
			    *tags, &self->joinPos, &point, &t, 0.0f);
			if (d < best) {
				best    = d;
				nearest = *tags;
				bestT   = t;
			}
		}
	}
	if (nearest == NULL) {
		return;
	}
	self->unk24C = (s16*)nearest;
	info.dist    = bestT;
	if (GetStatusOnPath__FP7PATHTAGP8PATHINFO((PathTag*)self->unk24C, &info) != 1) {
		return;
	}
	dir.x = info.pos.x - self->unk140;
	dir.y = info.pos.y - self->unk144;
	dir.z = info.pos.z - self->unk148;
	fn_801990E0(&dir, &dir);
	if (RwV3dDotProduct(&dir, &info.dir) < 0.0f) {
		self->unk2B4 = 0;
		self->unk248 = bestT;
	} else {
		self->unk2B4 = 1;
		self->unk248 = bestT;
	}
	ang.x = 0;
	GetZYAngleForTheTargetPoint__FPC5RwV3dPC5RwV3dPi(&info.dir, NULL, &ang);
	if (self->unk2B4 != 0) {
		self->joinPos   = info.pos;
		self->joinAng.x = ang.x;
		self->joinAng.y = ang.y;
		self->joinAng.z = ang.z;
	} else {
		self->joinPos   = info.pos;
		self->joinAng.x = ang.x;
		self->joinAng.y = (u16)(ang.y + 0x8000);
		self->joinAng.z = (u16)(ang.z * -1);
	}
	StartMoveToPath(self);
}

/* PreChangePath: join the nearest path at its start. */
void fn_8_B134C(TObject* self)
{
	PathInfo info;

	self->unk24C = (s16*)GetNearestPathTag(self, (RwV3d*)&self->unk140, 9999999.0f);
	if (self->unk24C == NULL) {
		return;
	}
	info.dist = 0.0f;
	if (GetStatusOnPath__FP7PATHTAGP8PATHINFO((PathTag*)self->unk24C, &info) == 1) {
		sAngle ang = lbl_8_rodata_1BC4;
		GetZYAngleForTheTargetPoint__FPC5RwV3dPC5RwV3dPi(&info.dir, NULL, &ang);
		self->joinPos = info.pos;
		self->joinAng = ang;
	}
	self->unk248 = 0.0f;
	StartMoveToPath(self);
}

/* ChangePath: slide over to the joining point, banking as it goes. */
s32 fn_8_B154C(TObject* self)
{
	FIELD(self, s32, 0x27C) += 0x250;
	self->unk278 = 10.0f * fn_800D7B00(FIELD(self, s32, 0x27C));
	self->unk14C = self->joinAng.x;
	self->unk150 = AdjustAngle__Fiii(self->unk150, self->joinAng.y, 0x80);
	self->unk154 = AdjustAngle__Fiii(self->unk154, self->joinAng.z, 0x80);
	RwV3d prev   = *(RwV3d*)&self->unk140;
	self->unk140 = self->joinVel.x + self->unk140;
	self->unk144 = self->joinVel.y + self->unk144;
	self->unk148 = self->joinVel.z + self->unk148;
	if (DistanceP2SegL__FP5RwV3dP5RwV3dP5RwV3dP5RwV3d(
	        &self->joinPos, &prev, (RwV3d*)&self->unk140, NULL)
	    < 2.0f) {
		*(RwV3d*)&self->unk140 = self->joinPos;
		return 1;
	}
	return 0;
}

/* RcvCommand: a command from the course's controller. */
void fn_8_B1660(TObject* self, RinoCommand* cmd)
{
	if (cmd->type == 4) {
		switch (cmd->kind) {
			case 0:
				break;
			case 1:
				if (lbl_8042C388 != 0U) {
					fn_800B4A38(lbl_8042C388, 0x4035, &self->unk140, 0, 1, 0, 0);
				}
				if (lbl_8042C388 != 0U) {
					fn_800B4A38(lbl_8042C388, 0x403E, &self->unk140, 0, 1, 0, 0);
				}
				self->unk240 = 2;
				break;
			case 2:
				self->unk240 = 0x27;
				break;
			case 3:
				self->unk240 = 0x20;
				break;
			case 4:
				self->unk240 = 0x20;
				fn_8_B321C(self, &cmd->pos, 0);
				self->unk2C0 = 0;
				break;
			case 5:
				self->unk318 = 0;
				self->unk240 = 0x26;
				break;
			case 6:
				self->joinPos = cmd->pos;
				self->unk318  = 1;
				self->unk240  = 0x26;
				break;
			case 7:
				switch (cmd->speedMode) {
					case 0:
						self->unk31C = 0;
						self->unk240 = 2;
						break;
					case 1:
						self->unk31C = 1;
						self->unk240 = 2;
						break;
					case 2:
						self->unk31C = 2;
						self->unk240 = 2;
						break;
					case 3:
						self->unk31C = 3;
						self->unk240 = 2;
						break;
					case 4:
						self->unk31C = 4;
						self->unk240 = 2;
						break;
				}
				break;
		}
	}
}

/* GetNearestPathTagALL: the nearest rideable path other than `exclude`, by
 * either end, within `dist` (-1 for no limit). Sets the direction flag to 1
 * when the start is nearer, 0 for the end. */
PathTag* fn_8_B1828(TObject* self, const RwV3d* pos, PathTag* exclude, f32 dist)
{
	PathTag** tags;
	RwV3d point;
	f32 d;
	PathTag* nearest = NULL;
	f32 best         = 9999999.0f;

	if (-1.0f != dist) {
		best = dist * dist;
	}
	for (tags = lbl_8042C380->tags; *tags != NULL; tags++) {
		if (*tags != exclude && (*tags)->type == 1) {
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(*tags, 0, &point);
			d = Distance2P2P__FPC5RwV3dPC5RwV3d(pos, &point);
			if (d < best) {
				best         = d;
				nearest      = *tags;
				self->unk2B4 = 1;
			}
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(*tags, (*tags)->numPoints - 1, &point);
			d = Distance2P2P__FPC5RwV3dPC5RwV3d(pos, &point);
			if (d < best) {
				best         = d;
				nearest      = *tags;
				self->unk2B4 = 0;
			}
		}
	}
	return nearest;
}

/* GetNearestPathTag: the rideable path whose start is nearest. */
PathTag* fn_8_B193C(TObject* self, const RwV3d* pos, f32 dist)
{
	PathTag** tags;
	PathTag* nearest = NULL;
	f32 best         = 9999999.0f;
	RwV3d point;
	f32 d;

	if (-1.0f != dist) {
		best = dist * dist;
	}
	for (tags = lbl_8042C380->tags; *tags != NULL; tags++) {
		if ((*tags)->type == 1) {
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(*tags, 0, &point);
			d = Distance2P2P__FPC5RwV3dPC5RwV3d(pos, &point);
			if (d < best) {
				best         = d;
				nearest      = *tags;
				self->unk2B4 = 1;
			}
		}
	}
	return nearest;
}

/* CheckCameraFrustumTest: in view only while a leader is within 1500. */
s32 fn_8_B1A0C(TObject* self, s32 arg1, f32 radius)
{
	if (Distance2P2P__FPC5RwV3dPC5RwV3d((RwV3d*)lbl_8042C208, (RwV3d*)arg1) > 2250000.0f) {
		return 0;
	}
	return CheckCameraFrustumTest__9TObjEnemyFPC5RwV3df(self, arg1, radius);
}

/* DispOpaqOnEdit. */
void fn_8_B1A90(TObject* self) { }

/* DispOpaq. */
void fn_8_B1A94(TObject* self)
{
	SetLightNum__7nRenderFUi(((TRenderer*)self)->Slot90());
	fn_8014FF2C(self->unkE8);
	fn_8014FF2C(self->unk310);
	fn_8014FF2C(self->unk314);
}

/* SetParameter: take the editor fields and the placed position. */
static inline void SetParameter(void* arg0)
{
	void* temp_r5;
	void* temp_r4;

	temp_r5                      = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), void**, 0x2C);
	M2C_FIELD(arg0, s32*, 0x2E8) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 0);
	M2C_FIELD(arg0, s32*, 0x2EC) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 1);
	M2C_FIELD(arg0, f32*, 0x2F0) = (f32)M2C_FIELD(temp_r5, f32*, 0x10);
	M2C_FIELD(arg0, f32*, 0x2F4) = (f32)M2C_FIELD(temp_r5, f32*, 0xC);
	M2C_FIELD(arg0, f32*, 0x2F8) = (f32)M2C_FIELD(temp_r5, f32*, 0x14);
	M2C_FIELD(arg0, s32*, 0x300) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 2);
	temp_r4                      = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(temp_r4, f32*, 0);
	M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	M2C_FIELD(arg0, f32*, 0x1C0) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1C4) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1C8) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x154) = 0;
	M2C_FIELD(arg0, s32*, 0x14C) = 0;
	M2C_FIELD(arg0, f32*, 0x1C0) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1C4) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1C8) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x2AC) = (f32)M2C_FIELD(temp_r5, f32*, 4);
	M2C_FIELD(arg0, s32*, 0x2B0) = (s32)M2C_FIELD(temp_r5, s32*, 8);
}

/* UpdateOnEdit: follow the edited parameters. */
void fn_8_B1AE8(TObject* self)
{
	if (self->unk2B4 != 0) {
		self->unk248 = 0.0f;
	} else if (self->unk24C != NULL) {
		self->unk248 = ((PathTag*)self->unk24C)->length - 1.0f;
	}
	SetParameter(self);
	fn_8_B3598(self);
}

/* Whether no pause or event flag is up. */
static inline s32 GameRunning()
{
	if (lbl_8042C180->flag1F != 0) {
		return 0;
	} else if (lbl_8042C180->flag20 != 0) {
		return 0;
	} else if (lbl_8042C180->flag21 != 0) {
		return 0;
	}
	return 1;
}

static inline s32 NotPaused()
{
	if (lbl_8042C180->flag1F != 0) {
		return 0;
	}
	return 1;
}

#pragma opt_common_subs off
/* Update. */
void fn_8_B1C1C(TObject* self)
{
	self->unk2E0 = GameRunning();
	self->unk2E4 = NotPaused();
	if (FIELD(self, void*, 0x38) != NULL) {
		*(RwV3d*)&self->unk140 = FIELD(self, RwV3d, 0x88);
	}
	fn_800A5B34(self);
	((TRenderer*)self)->Slot38();
	if (self->unk244 != NULL) {
		((TSubDispatch*)self->unk244)->vslot3(self);
	}
	((TRenderer*)self)->Slot50(self->unk19C, 1);
	fn_8_B3598(self);
	fn_800A3D48(self);
	if (self->unk2E0 != 0) {
		fn_8_B0B00(self);
	}
	if (fn_80017800(self) != 0 && FIELD(self, void*, 0x38) != NULL) {
		ClearInfo__7C_COLLIFv((u8*)self + 0x28);
		FIELD(self, RwV3d, 0xA4)  = FIELD(self, RwV3d, 0x88);
		FIELD(self, RwV3d, 0x88)  = *(RwV3d*)&self->unk140;
		FIELD(self, sAngle, 0x94) = *(sAngle*)&self->unk14C;
		Entry__7C_COLLIFv((u8*)self + 0x28);
	}
}
#pragma opt_common_subs reset

/* EnemyMD_Destroy. */
void fn_8_B1E38(TObject* self, s32 phase)
{
	switch (phase) {
		case 0:
			((TRenderer*)self)->Slot3C();
			break;
		case 1:
			FIELD(self, u16, 4) |= 1;
			break;
		case 2:
		case 3:
			break;
	}
}

/* EnemyMD_ThunderShoot. */
void fn_8_B1E98(TObject* self, s32 phase) { }

/* EnemyMD_ChangePath. */
void fn_8_B1E9C(TObject* self, s32 phase)
{
	switch (phase) {
		case 0:
			switch (self->unk318) {
				case 0:
					fn_8_B134C(self);
					break;
				case 1:
					fn_8_B1078(self);
					break;
			}
			break;
		case 1:
			if (fn_8_B154C(self) == 1) {
				self->unk240 = 2;
				if (lbl_8042C388 != 0U) {
					fn_800B4A38(lbl_8042C388, 0x4039, &self->unk140, 0, 1, 0, 0);
				}
			}
			break;
		case 2:
			break;
		case 3:
			self->unkD4 = 0;
			break;
	}
}

/* CheckPathStart: whether the rinoliner stands at the end of its path it
 * starts from. */
static inline BOOL CheckPathStart(TObject* self, PathTag* path)
{
	if (path == NULL) {
		return FALSE;
	}
	if (self->unk2B4 != 0) {
		return (0.0f == self->unk248) ? TRUE : FALSE;
	}
	return (self->unk248 == path->length - 1.0f) ? TRUE : FALSE;
}

/* CheckPathEnd: clamp the distance to the path's far end and report
 * reaching it. */
static inline BOOL CheckPathEnd(TObject* self)
{
	PathInfo info;
	BOOL end;

	if (self->unk24C == NULL) {
		return TRUE;
	}
	end = FALSE;
	if (self->unk2B4 != 0) {
		if (self->unk248 >= ((PathTag*)self->unk24C)->length - 1.0f) {
			self->unk248 = ((PathTag*)self->unk24C)->length - 1.0f;
			end          = TRUE;
		}
	} else if (self->unk248 <= 0.0f) {
		self->unk248 = 0.0f;
		end          = TRUE;
	}
	if (end) {
		info.dist = self->unk248;
		if (GetStatusOnPath__FP7PATHTAGP8PATHINFO((PathTag*)self->unk24C, &info) == 1) {
			*(RwV3d*)&self->unk140 = info.pos;
		}
	}
	return end;
}

/* FireIronBall: launch an iron ball from the barrel. */
static inline void FireIronBall(TObject* self)
{
	IronBallParam ball;
	ball.pos   = self->muzzle;
	ball.dir   = self->aim;
	ball.speed = self->unk2AC;
	if (self->unk300 == 0) {
		ball.homing = 1;
	} else {
		ball.homing = 0;
	}
	ball.life  = 600;
	ball.light = ((TRenderer*)self)->Slot90();
	fn_8_B5160(&ball);
	sAngle ang = lbl_8_rodata_1BB8;
	fn_8006298C(5, &self->muzzle, &ang);
	if (lbl_8042C388 != 0U) {
		fn_800B4A38(lbl_8042C388, 0x403B, &self->unk140, 0, 1, 0, 0);
	}
}

/* EnemyMD_Attack: fire one iron ball along the barrel. */
void fn_8_B2224(TObject* self, s32 phase)
{
	switch (phase) {
		case 0:
			self->fired = 0;
			break;
		case 1:
			fn_8_B2BB4(self);
			fn_8_B0D34(self);
			if (self->fired == 0) {
				FireIronBall(self);
				self->fired = 1;
			}
			break;
		case 2:
		case 3:
			break;
	}
}

/* EnemyMD_Walk. */
void fn_8_B23BC(TObject* self, s32 phase)
{
	switch (phase) {
		case 0:
			break;
		case 1:
			fn_8_B2BB4(self);
			fn_8_B0D34(self);
			break;
		case 2:
		case 3:
			break;
	}
}

/* EnemyMD_Stop: coast to a halt. */
void fn_8_B240C(TObject* self, s32 phase)
{
	switch (phase) {
		case 0:
			if (lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0x403D, &self->unk140, 0, 1, 0, 0);
			}
			break;
		case 1:
			fn_8_B2BB4(self);
			self->unk2FC *= 0.97f;
			if (self->unk2FC < 0.0f) {
				self->unk2FC = 0.0f;
			}
			break;
		case 2:
		case 3:
			break;
	}
}

/* EnemyMD_Wait: ride on only from the start of the path. */
void fn_8_B24C0(TObject* self, s32 phase)
{
	switch (phase) {
		case 0:
			break;
		case 1:
			if (CheckPathStart(self, (PathTag*)self->unk24C)) {
				fn_8_B2BB4(self);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

/* CtrlMode: run the handler of the current mode. */
void fn_8_B2578(TObject* self, s32 mode, s32 phase)
{
	switch (mode) {
		case 1:
			fn_8_B24C0(self, phase);
			break;
		case 2:
			fn_8_B23BC(self, phase);
			break;
		case 0x20:
			fn_8_B2224(self, phase);
			break;
		case 0x26:
			fn_8_B1E9C(self, phase);
			break;
		case 0x1D:
			fn_8_B1E38(self, phase);
			break;
		case 0x27:
			fn_8_B240C(self, phase);
			break;
		case 0x24:
			fn_8_B1E98(self, phase);
			break;
	}
}

/* The out-of-line copies of the helpers inlined above. */
void fn_8_B28E4(TObject* self)
{
	FireIronBall(self);
}

/* CalcAngleFromPathInfo. */
s32 fn_8_B2A30(TObject* self, PathInfo* info, sAngle* ang)
{
	ang->x = 0;
	GetZYAngleForTheTargetPoint__FPC5RwV3dPC5RwV3dPi(&info->dir, NULL, ang);
	return 1;
}

/* CheckPathStart, out of line. */
BOOL fn_8_B2A64(TObject* self)
{
	PathTag* path = (PathTag*)self->unk24C;

	if (path == NULL) {
		return FALSE;
	}
	if (self->unk2B4 != 0) {
		return 0.0f == self->unk248;
	}
	return self->unk248 == path->length - 1.0f;
}

/* CheckPathEnd, out of line. */
BOOL fn_8_B2ACC(TObject* self)
{
	PathInfo info;
	BOOL end;

	if (self->unk24C == NULL) {
		return TRUE;
	}
	end = FALSE;
	if (self->unk2B4 != 0) {
		if (self->unk248 >= ((PathTag*)self->unk24C)->length - 1.0f) {
			self->unk248 = ((PathTag*)self->unk24C)->length - 1.0f;
			end          = TRUE;
		}
	} else if (self->unk248 <= 0.0f) {
		self->unk248 = 0.0f;
		end          = TRUE;
	}
	if (end) {
		info.dist = self->unk248;
		if (GetStatusOnPath__FP7PATHTAGP8PATHINFO((PathTag*)self->unk24C, &info) == 1) {
			*(RwV3d*)&self->unk140 = info.pos;
		}
	}
	return end;
}

char lbl_8_data_16FA0[]           = "en_rinoliner.one";
char rinolinerObjectDisplayName[] = "RINOLINER OBJECT";
char rinolinerObjectFieldTypes[]  = "ccccfifff";

/* The editor-placed objects' shared clump table and the exhaust emitter. */
void* lbl_8_bss_1A50[3];
void* lbl_8_bss_1A5C;
ObjectEntry rinolinerObjectEntry;

/* MoveOnPath: ride the path, turning to its direction; at its end, change to
 * the nearest other path. */
void fn_8_B2BB4(TObject* self)
{
	PathInfo info;
	RwMatrix rot;
	sAngle ang;
	sAngle turn;

	PathTag* path;
	PathTag* next;

	if (self->unk2E0 != 0 && (path = (PathTag*)self->unk24C) != NULL) {
		info.dist = self->unk248;
		if (CheckPathStart(self, path)) {
			if (GetStatusOnPath__FP7PATHTAGP8PATHINFO(path, &info) == 1) {
				*(RwV3d*)&self->unk140 = info.pos;
				ang.x                  = 0;
				GetZYAngleForTheTargetPoint__FPC5RwV3dPC5RwV3dPi(&info.dir, NULL, &ang);
				if (self->unk2B4 != 0) {
					self->unk14C = ang.x;
					self->unk150 = ang.y;
					self->unk154 = ang.z;
				} else {
					self->unk14C = ang.x;
					self->unk150 = (u16)(ang.y + 0x8000);
					self->unk154 = (u16)(ang.z * -1);
				}
			}
		} else if (GetStatusOnPath__FP7PATHTAGP8PATHINFO(path, &info) == 1) {
			*(RwV3d*)&self->unk140 = info.pos;
			turn.x                 = 0;
			GetZYAngleForTheTargetPoint__FPC5RwV3dPC5RwV3dPi(&info.dir, NULL, &turn);
			if (self->unk2B4 != 0) {
				self->unk14C = turn.x;
				self->unk150 = AdjustAngle__Fiii(self->unk150, turn.y, self->unk2B8);
				self->unk154 = AdjustAngle__Fiii(self->unk154, turn.z, self->unk2BC);
			} else {
				self->unk14C = turn.x;
				self->unk150
				    = AdjustAngle__Fiii(self->unk150, (u16)(turn.y + 0x8000), self->unk2B8);
				self->unk154 = AdjustAngle__Fiii(self->unk154, (u16)(turn.z * -1), self->unk2BC);
			}
			if (self->unk2C8 != 0 && 3.0517578125e-05f * (f32)rand() < 0.12f) {
				fn_80195790(
				    &rot, &AxisX, 1.0f - fn_800D7AE4(-self->unk154), fn_800D7B00(-self->unk154), 0);
				fn_80195790(
				    &rot, &AxisY, 1.0f - fn_800D7AE4(-self->unk150), fn_800D7B00(-self->unk150), 2);
				RwV3d vel = lbl_8_data_16CB4;
				fn_8019941C(&vel, &vel, 1, &rot);
				fn_80196050(&rot, (RwV3d*)&self->unk140, 2);
				RwV3d ofs = lbl_8_data_16CA8;
				fn_8019941C(&ofs, &ofs, 1, &rot);
				lbl_8_data_16CE0.pos    = &ofs.x;
				lbl_8_data_16CE0.vel    = &vel.x;
				lbl_8_data_16CE0.color0 = lbl_8_data_16CC0;
				lbl_8_data_16CE0.color1 = lbl_8_data_16CD0;
				fn_8_6BE14(EffSparkTp, &lbl_8_data_16CE0);
			}
		}
		if (self->unk2B4 != 0) {
			self->unk248 += self->unk2FC;
		} else {
			self->unk248 -= self->unk2FC;
		}
		fn_80139784(lbl_8_bss_1A5C, self, (RwV3d*)&self->unk140);
		if (CheckPathEnd(self)) {
			if (self->unk2EC == 0) {
				next = GetNextPathTagALL(self, (RwV3d*)&self->unk140, 400.0f);
			} else {
				next = GetNextPathTag(self, (RwV3d*)&self->unk140, 400.0f);
			}
			if (next != NULL) {
				if (self->unk2B4 != 0) {
					self->unk248 = 0.0f;
				} else {
					self->unk248 = next->length - 1.0f;
				}
				self->unk24C = (s16*)next;
				return;
			}
			self->unk248 = 0.0f;
			self->unk240 = 0x1D;
		}
	}
}

/* The angle around Y from one direction to another, both flattened. */
static inline s32 FlatAngle(const RwV3d* dir, const RwV3d* target)
{
	RwV3d up;
	RwV3d to;
	RwV3d from;

	from   = *dir;
	to     = *target;
	from.y = 0.0f;
	to.y   = 0.0f;
	up.x   = 0.0f;
	up.y   = 1.0f;
	up.z   = 0.0f;
	return VectorAngle__FP5RwV3dP5RwV3dP5RwV3d(&from, &to, &up);
}

/* CalcCannon: turn the cannon toward the target and aim its barrel. */
void fn_8_B321C(TObject* arg0, const RwV3d* target, s32 adjust)
{
	RwMatrix rot;
	s32 angle;
	RwFrame* frame;
	RwMatrix* ltm;

	if (arg0->unk304 != NULL && arg0->unk310 != NULL) {
		RwV3d front = lbl_8_rodata_1BA0;
		fn_80195790(&rot, &AxisY, 1.0f - fn_800D7AE4(-arg0->unk150), fn_800D7B00(-arg0->unk150), 0);
		fn_8019941C(&front, &front, 1, &rot);
		fn_801990E0(&front, &front);
		RwV3d to = lbl_8_rodata_1BAC;
		to.x     = target->x - arg0->unk140;
		to.y     = target->y - arg0->unk144;
		to.z     = target->z - arg0->unk148;
		to.y     = 0.0f;
		fn_801990E0(&to, &to);
		angle = FlatAngle(&front, &to);
		if (adjust != 0) {
			arg0->unk28C = AdjustAngle__Fiii(arg0->unk28C, angle, 0x200);
		} else {
			arg0->unk28C = angle;
		}
		frame = *(RwFrame**)((u8*)arg0->unk310 + 4);
		ltm   = fn_8019E8EC(arg0->unk304);
		fn_8019ED68(frame, &AxisY, 0.0054931640625f * (f32)arg0->unk28C, 0);
		fn_8019ECCC(frame, ltm, 2);
		to.x      = target->x - ltm->pos.x;
		to.y      = target->y - ltm->pos.y;
		to.z      = target->z - ltm->pos.z;
		arg0->aim = to;
		fn_801990E0(&arg0->aim, &arg0->aim);
		to.x = 0.0f;
		fn_801990E0(&to, &to);
		if (arg0->unk308 != 0 && arg0->unk314 != NULL) {
			RwFrame* barrel = *(RwFrame**)((u8*)arg0->unk314 + 4);
			RwMatrix* mount = fn_8019E8EC((RwFrame*)arg0->unk308);
			fn_8019ED68(barrel, &AxisX, 0.0054931640625f * (f32)arg0->unk290, 0);
			fn_8019ECCC(barrel, mount, 2);
			if ((frame = objRwFrameGetFrame__FP7RwFramei(barrel, 1)) != NULL) {
				arg0->muzzle = fn_8019E8EC(frame)->pos;
			}
		}
	}
}

/* SetPosition: place the clump and the cannon frames, find the bones, and aim
 * at the nearest leader. */
void fn_8_B3598(TObject* self)
{
	RwFrame* frame;
	f32 roll;
	s32 bone;
	PlayerObj* player;

	roll = self->unk278;
	if ((f32)__fabs(roll) > 0.001f) {
		self->unk278 *= 0.98f;
	}
	if (self->unkE8 != NULL) {
		frame = *(RwFrame**)((u8*)self->unkE8 + 4);
		if (self->unk19C == 0x24 && self->unk2D0 != NULL) {
			Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(self->unk2D0, frame, 0);
			fn_8019ED68(frame, &AxisX, -(0.0054931640625f * (f32)self->unk154), 2);
			fn_8019ED68(frame, &AxisZ, self->unk278, 2);
			fn_8019ED68(frame, &AxisY, -(0.0054931640625f * (f32)self->unk150), 2);
			fn_8019EB94(frame, (RwV3d*)&self->unk140, 2);
			RwV3d point = lbl_8_rodata_1B94;
			fn_8019941C(&point, &point, 1, fn_8019E8EC(frame));
			SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(self->unk2D0, &point, NULL);
		} else {
			fn_8019ED68(frame, &AxisX, -(0.0054931640625f * (f32)self->unk154), 0);
			fn_8019ED68(frame, &AxisZ, self->unk278, 2);
			fn_8019ED68(frame, &AxisY, -(0.0054931640625f * (f32)self->unk150), 2);
			fn_8019EB94(frame, (RwV3d*)&self->unk140, 2);
		}
	}
	if (self->unk304 == NULL) {
		bone = objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(self->unkEC, 0x4B0);
		if (bone != -1) {
			self->unk304 = self->unkEC->pNodeInfo[bone].pFrame;
		}
	}
	if (self->unk308 == 0 && self->unk310 != NULL) {
		self->unk308 = (u32)objRwFrameGetFrame__FP7RwFramei(*(RwFrame**)((u8*)self->unk310 + 4), 1);
	}
	if (self->unk30C == 0) {
		bone = objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(self->unkEC, 0x44D);
		if (bone != -1) {
			self->unk30C = (u32)self->unkEC->pNodeInfo[bone].pFrame;
		}
	}
	if (self->unk2E0 != 0) {
		self->unk2CC
		    = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df((u8*)self + 0x140, 100000000.0f);
		if (self->unk2CC != -1) {
			player = lbl_802AD090[self->unk2CC];
			if (player != NULL) {
				if (self->unk19C != 0x24) {
					*(RwV3d*)&self->unk2D4 = player->pos;
				}
				fn_8_B321C(self, (RwV3d*)&self->unk2D4, 1);
				self->unk2C0 = 1;
			}
		}
		if (self->unk288 == NULL) {
			self->unk288 = fn_800628D0(0xD, &self->unk140, &self->unk14C);
		}
		if (self->unk288 != NULL && self->unk30C != 0) {
			/* Kept as an array: retail holds the angle in memory across the
			 * frame lookup instead of in registers. */
			s32 ang[3];
			RwMatrix* ltm;

			ang[0] = -self->unk154;
			ang[1] = -self->unk150;
			ang[2] = (s32)(182.04445f * self->unk278);
			ltm    = fn_8019E8EC((RwFrame*)self->unk30C);
			((EffectObj*)self->unk288)->SetPosAng(&ltm->pos, (sAngle*)ang);
		}
	}
}

void fn_8_B39E4(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x314) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x314));
		M2C_FIELD(arg0, u32*, 0x314) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x310) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x310));
		M2C_FIELD(arg0, u32*, 0x310) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0xE8));
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

void fn_8_B3A54(void* arg0)
{
	void* temp_r31;

	if ((void*)M2C_FIELD(arg0, void**, 0x314) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0x314));
		M2C_FIELD(arg0, void**, 0x314) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x310) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0x310));
		M2C_FIELD(arg0, void**, 0x310) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0xE8));
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	temp_r31                       = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 0));
	M2C_FIELD(arg0, void**, 0x310) = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 4));
	M2C_FIELD(arg0, void**, 0x314) = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 8));
	M2C_FIELD(arg0, void**, 0xE8)  = temp_r31;
}

void fn_8_B3B0C(void* arg0)
{
	SetParameter(arg0);
}

void fn_8_B3BE0(TObject* arg0)
{
	arg0->unk248 = 0.0f;
	arg0->unk24C = NULL;
	arg0->unk240 = 0;
	arg0->unk244 = NULL;
	arg0->unk278 = 0.0f;
	arg0->unk27C = 0;
	arg0->unk2FC = 0.1f;
	arg0->unk304 = NULL;
	arg0->unk308 = 0U;
	arg0->unk30C = 0U;
	arg0->unk280 = 0;
	arg0->unk284 = 0;
	arg0->unk288 = NULL;
	arg0->unk310 = NULL;
	arg0->unk314 = NULL;
	arg0->unk28C = 0;
	arg0->unk290 = 0;
	arg0->unk2B4 = 1;
	arg0->unk318 = 0;
	arg0->unk2B8 = 0x80;
	arg0->unk2BC = 0x80;
	arg0->unk31C = 0;
	arg0->unk2C0 = 1;
	if (((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 8)
	    || ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 9)) {
		arg0->unk2C8 = 0;
	} else {
		arg0->unk2C8 = 0;
	}
	arg0->unk2CC = -1;
	arg0->unk2D0 = NULL;
	arg0->unk2DC = 0.0f;
	arg0->unk2D8 = 0.0f;
	arg0->unk2D4 = 0.0f;
	arg0->unk2E0 = 1;
	arg0->unk2E4 = 1;
}

void* fn_8_B3CC4(void* arg0, s16 arg1)
{
	s32 temp_cr0_eq;
	void** temp_r3_3;
	void* temp_r3;
	void* temp_r3_2;

	if (arg0 != NULL) {
		M2C_FIELD(arg0, M2C_UNK**, 0x18) = (M2C_UNK*)lbl_8_data_16E38;
		M2C_FIELD(arg0, void**, 0xB4)    = (void*)((u8*)lbl_8_data_16E38 + 0x2C);
		temp_r3                          = M2C_FIELD(arg0, void**, 0x2D0);
		if (temp_r3 != NULL) {
			M2C_FIELD(temp_r3, u16*, 4)    = (u16)(M2C_FIELD(temp_r3, u16*, 4) | 1);
			M2C_FIELD(arg0, void**, 0x2D0) = NULL;
		}
		temp_r3_2 = M2C_FIELD(arg0, void**, 0x288);
		if (temp_r3_2 != NULL) {
			M2C_FIELD(temp_r3_2, u16*, 4)  = (u16)(M2C_FIELD(temp_r3_2, u16*, 4) | 1);
			M2C_FIELD(arg0, void**, 0x288) = NULL;
		}
		temp_r3_3 = M2C_FIELD(arg0, void***, 0x244);
		if (temp_r3_3 != NULL) {
			if (temp_r3_3 != NULL) {
				((TSubDispatch*)temp_r3_3)->vslot2(1);
			}
			M2C_FIELD(arg0, void***, 0x244) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x314) != 0U) {
			fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x314));
			M2C_FIELD(arg0, u32*, 0x314) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x310) != 0U) {
			fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x310));
			M2C_FIELD(arg0, u32*, 0x310) = 0U;
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

TObject* rinolinerObjectCtor(TObject* arg0, TObject* arg1)
{
	sParalysisParam param;
	void* strategy;
	void* fire;
	TEnemyParalysis* paralysis;
	void* key;
	PathTag* tag;
	u32 setFlags;
	void* temp_r30;
	void* temp_r3;
	void* temp_r4;

	fn_800A714C();
	__ct__10HAnimClassFv((u8*)arg0 + 0x240);
	arg0->unk18 = (M2C_UNK*)lbl_8_data_16E38;
	arg0->unkB4 = (u8*)lbl_8_data_16E38 + 0x2C;
	arg0->unk0  = (M2C_UNK*)lbl_8_data_16E34;
	arg0->unk1E = 0x320;
	fn_8_B3BE0(arg0);
	temp_r4      = M2C_FIELD(arg0->unkB0, void**, 0x2C);
	arg0->unk2E8 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0);
	arg0->unk2EC = (s32)(s8)M2C_FIELD(temp_r4, u8*, 1);
	arg0->unk2F0 = M2C_FIELD(temp_r4, f32*, 0x10);
	arg0->unk2F4 = M2C_FIELD(temp_r4, f32*, 0xC);
	arg0->unk2F8 = M2C_FIELD(temp_r4, f32*, 0x14);
	arg0->unk300 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 2);
	temp_r3      = arg0->unkB0;
	arg0->unk140 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unk144 = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unk148 = M2C_FIELD(temp_r3, f32*, 8);
	arg0->unk1C0 = arg0->unk140;
	arg0->unk1C4 = arg0->unk144;
	arg0->unk1C8 = arg0->unk148;
	arg0->unk1CC = arg0->unk140;
	arg0->unk1D0 = arg0->unk144;
	arg0->unk1D4 = arg0->unk148;
	arg0->unk150 = M2C_FIELD(arg0->unkB0, s32*, 0x10);
	arg0->unk154 = 0;
	arg0->unk14C = 0;
	arg0->unk1C0 = arg0->unk140;
	arg0->unk1C4 = arg0->unk144;
	arg0->unk1C8 = arg0->unk148;
	arg0->unk2AC = M2C_FIELD(temp_r4, f32*, 4);
	arg0->unk2B0 = M2C_FIELD(temp_r4, s32*, 8);
	arg0->unk188 &= 0xFFFF3FFF;
	arg0->unk188 |= 0x4000;
	if ((void*)arg0->unk314 != NULL) {
		fn_80150958((void*)arg0->unk314);
		arg0->unk314 = NULL;
	}
	if ((void*)arg0->unk310 != NULL) {
		fn_80150958((void*)arg0->unk310);
		arg0->unk310 = NULL;
	}
	if ((void*)arg0->unkE8 != NULL) {
		fn_80150958((void*)arg0->unkE8);
		arg0->unkE8 = NULL;
	}
	temp_r30     = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 0));
	arg0->unk310 = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 4));
	arg0->unk314 = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 8));
	arg0->unkE8  = temp_r30;
	fn_8_B3598(arg0);
	arg0->unk160 = 0.0f;
	arg0->unk15C = 0.0f;
	arg0->unk158 = 0.0f;
	arg0->unk188 &= 0xFFEFCFFF;
	arg0->unk188 |= 0x10;
	arg0->unk1A4 = 2.0f;
	arg0->unk2E  = 2;
	arg0->unk1A0 = 3.0f;
	arg0->unk2C  = 3;
	setFlags     = M2C_FIELD(arg0->unkB0, u32*, 0x18);
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
	    arg0->unkE8, ((setFlags & 0x1C0000) >> 18) + 8);
	arg0->unkE4 = (M2C_UNK*)lbl_8_data_16C18;
	arg0->unkD4 = 0;
	if (OnEdit__10TObjSetObjFv(&arg0->unkB0) == 0) {
		Init__7C_COLLIFP8CCL_INFOiUc(&arg0->unk28, (M2C_UNK*)lbl_8_data_16BB0, 1, 3);
		arg0->unk88 = arg0->unk140;
		arg0->unk8C = arg0->unk144;
		arg0->unk90 = arg0->unk148;
	}
	arg0->unk130 = 50.0f;
	arg0->unk134 = 0.8f;
	arg0->unk244 = NULL;
	switch (arg0->unk2E8) {
		case 0:
			strategy = __nw__FUl(0x20);
			if (strategy != NULL) {
				strategy = fn_8_B5B3C(strategy);
			}
			arg0->unk244 = (M2C_UNK**)strategy;
			break;
		case 1:
			fire = __nw__FUl(0x20);
			if (fire != NULL) {
				fn_8_B5B3C(fire);
				*(void**)fire = lbl_8_data_17060;
			}
			arg0->unk244 = (M2C_UNK**)fire;
			break;
	}
	if (arg0->unk244 != NULL) {
		fn_8_B5620(arg0->unk244, arg0);
	}
	if (arg0->unk2EC == 0) {
		arg0->unk24C = (s16*)GetNearestPathTagALL(arg0, NULL, (RwV3d*)&arg0->unk140, 10000.0f);
	} else {
		arg0->unk24C = (s16*)GetNearestPathTagCtor(arg0, (RwV3d*)&arg0->unk140, 10000.0f);
	}
	tag = (PathTag*)arg0->unk24C;
	if (tag != NULL) {
		if (arg0->unk2B4 != 0) {
			arg0->unk248 = 0.0f;
		} else {
			arg0->unk248 = tag->length - 1.0f;
		}
	}
	__ct__15sParalysisParamFv(&param);
	param.offset.x = 15.0f;
	param.offset.y = 15.0f;
	param.offset.z = 15.0f;
	paralysis      = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x74);
	if (paralysis != NULL) {
		paralysis
		    = __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(paralysis, lbl_8042C10C, &param);
	}
	arg0->unk2D0 = paralysis;
	arg0->unk13C = 1;
	key          = __nw__FUl(0x20);
	if (key != NULL) {
		key = __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID(key, arg0, arg0->unk13C);
	}
	arg0->unk228 = (M2C_UNK**)key;
	return arg0;
}

TEnemyParalysis* fn_8_B4394(void)
{
	TEnemyParalysis* var_r0;

	var_r0 = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x320);
	if (var_r0 != NULL) {
		var_r0 = (TEnemyParalysis*)rinolinerObjectCtor((TObject*)var_r0, lbl_8042C10C);
	}
	return var_r0;
}

/* The weapon speed and attack interval bounds, which EditOnChange clamps by
 * reference. */
extern const f32 lbl_8_rodata_1C44[1] = { 0.1f };
extern const f32 lbl_8_rodata_1C48[1] = { 100.0f };
extern const s32 lbl_8_rodata_1C4C[1] = { 0 };
extern const s32 lbl_8_rodata_1C50[1] = { 216000 };

/* EditOnChange: clamp the edited fields, then point the three choice fields'
 * names at the chosen values. */
void fn_8_B43E8(void* arg0, SetData* data)
{
	RinolinerParams* p = data->params;

	p->type           = Clamp(p->type, lbl_8_data_16E00, lbl_8_data_16E01);
	p->pathType       = Clamp(p->pathType, lbl_8_data_16E02, lbl_8_data_16E03);
	p->homing         = Clamp(p->homing, lbl_8_data_16E04, lbl_8_data_16E05);
	p->unused         = 0;
	p->weaponSpeed    = Clamp(p->weaponSpeed, lbl_8_rodata_1C44[0], lbl_8_rodata_1C48[0]);
	p->attackInterval = Clamp(p->attackInterval, lbl_8_rodata_1C4C[0], lbl_8_rodata_1C50[0]);
	p->speedMin       = Clamp(p->speedMin, lbl_8_data_16E08, lbl_8_data_16E0C);
	p->speed          = Clamp(p->speed, lbl_8_data_16E10, lbl_8_data_16E14);
	p->speedMax       = Clamp(p->speedMax, lbl_8_data_16E18, lbl_8_data_16E1C);
	rinolinerObjectFieldNames[0] = lbl_8_data_16DB8[p->type];
	rinolinerObjectFieldNames[1] = lbl_8_data_16DC8[p->pathType];
	rinolinerObjectFieldNames[2] = lbl_8_data_16DF8[p->homing];
}

void rinolinerObjectUnload(void)
{
	if ((void*)lbl_8_bss_1A5C != NULL) {
		M2C_FIELD(lbl_8_bss_1A5C, u16*, 4) = (u16)(M2C_FIELD(lbl_8_bss_1A5C, u16*, 4) | 1);
		lbl_8_bss_1A5C                     = NULL;
	}
	fn_8_B52F4();
	ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    3, (M2C_UNK*)lbl_8_data_16C18);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	Delete__14TEnemyDataBaseF14eEnemyDataBase(mpDataBase__14TEnemyDataBase, 3);
}

void rinolinerObjectLoad(void)
{
	u32 temp_r3;
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	Add__14TEnemyDataBaseF14eEnemyDataBasePc(mpDataBase__14TEnemyDataBase, 3, lbl_8_data_16FA0);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	temp_r3 = SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(
	    mpDataBase__14TEnemyDataBase, 3, 8);
	if (temp_r3 != 0U) {
		objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(temp_r3, 6);
	} else {
		return;
	}
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_1A50, s32*, 0)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 3, 5);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_1A50, s32*, 4)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 3, 3);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_1A50, s32*, 8)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 3, 2);
	LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    3, (M2C_UNK*)lbl_8_data_16C18);
	fn_8_B5308();
	lbl_8_bss_1A5C = fn_80139984(1, 0x4037, 4);
}
}
