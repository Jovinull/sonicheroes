#include "types.h"

// stage11D's TObjEnemyTurtle (named by the PS2 build's symbols), with the
// module's register record. Its strategy is
// rel/e_strategy_turtle_stage11.cpp. Retail built this unit with deferred
// inlining: functions are defined here in reverse order, and the compiler's
// vtable lands after the named data and before the jump table and strings.

typedef s32 M2C_UNK;
typedef void (*TFunc)(void);
typedef struct {
	s32 words[3];
} M2C_BLOCK12;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(u32)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

typedef struct TEnemyParalysis TEnemyParalysis;
typedef struct RwFrame RwFrame;

typedef struct sAngle {
	s32 x;
	s32 y;
	s32 z;
} sAngle;

typedef struct sVec4 {
	f32 x;
	f32 y;
	f32 z;
	f32 w;
} sVec4;

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;
typedef s32 RwOpCombineType;
typedef struct sParalysisParam {
	/* 0x00 */ u8 pad0[8];
	/* 0x08 */ RwV3d offset;
} sParalysisParam; /* size 0x14 */

typedef struct TObjEffTornadoSpin {
	/* 0x000 */ char pad0[0x28];
	/* 0x028 */ M2C_UNK unk28; /* inferred */
	/* 0x02C */ char pad2C[2];
	/* 0x02E */ s16 unk2E;         /* inferred */
	/* 0x030 */ u16 unk30;         /* inferred */
	/* 0x032 */ char pad32[0x10A]; /* maybe part of unk30[0x86]? */
	/* 0x13C */ M2C_UNK unk13C;    /* inferred */
	/* 0x140 */ M2C_UNK unk140;    /* inferred */
	/* 0x144 */ char pad144[0x44];
	/* 0x188 */ s32 unk188;       /* inferred */
	/* 0x18C */ s32 unk18C;       /* inferred */
	/* 0x190 */ char pad190[0xC]; /* maybe part of unk18C[4]? */
	/* 0x19C */ s32 unk19C;       /* inferred */
	/* 0x1A0 */ char pad1A0[4];
	/* 0x1A4 */ f32 unk1A4;        /* inferred */
	/* 0x1A8 */ char pad1A8[0x88]; /* maybe part of unk1A4[0x23]? */
	/* 0x230 */ s32 unk230;        /* inferred */
	/* 0x234 */ s32 unk234;        /* inferred */
	/* 0x238 */ char pad238[0x98]; /* maybe part of unk234[0x27]? */
	/* 0x2D0 */ s32 unk2D0;        /* inferred */
	/* 0x2D4 */ char pad2D4[0x3C]; /* maybe part of unk2D0[0x10]? */
	/* 0x310 */ s32 unk310;        /* inferred */
} TObjEffTornadoSpin;              /* size >= 0x314 */

typedef struct TEnemyWork {
	/* 0x000 */ M2C_UNK* unk0; /* inferred */
	/* 0x004 */ s32 unk4;      /* inferred */
	/* 0x008 */ char pad8[4];
	/* 0x00C */ s32 unkC;       /* inferred */
	/* 0x010 */ s32 unk10;      /* inferred */
	/* 0x014 */ void* unk14;    /* inferred */
	/* 0x018 */ M2C_UNK* unk18; /* inferred */
	/* 0x01C */ char pad1C[2];
	/* 0x01E */ s16 unk1E;        /* inferred */
	/* 0x020 */ char pad20[8];    /* maybe part of unk1E[5]? */
	/* 0x028 */ M2C_UNK unk28;    /* inferred */
	/* 0x02C */ s16 unk2C;        /* inferred */
	/* 0x02E */ s16 unk2E;        /* inferred */
	/* 0x030 */ char pad30[8];    /* maybe part of unk2E[5]? */
	/* 0x038 */ u32 unk38;        /* inferred */
	/* 0x03C */ char pad3C[0x4C]; /* maybe part of unk38[0x14]? */
	/* 0x088 */ f32 unk88;        /* inferred */
	/* 0x08C */ f32 unk8C;        /* inferred */
	/* 0x090 */ f32 unk90;        /* inferred */
	/* 0x094 */ s32 unk94;        /* inferred */
	/* 0x098 */ s32 unk98;        /* inferred */
	/* 0x09C */ s32 unk9C;        /* inferred */
	/* 0x0A0 */ char padA0[4];
	/* 0x0A4 */ f32 unkA4;       /* inferred */
	/* 0x0A8 */ f32 unkA8;       /* inferred */
	/* 0x0AC */ f32 unkAC;       /* inferred */
	/* 0x0B0 */ void* unkB0;     /* inferred */
	/* 0x0B4 */ void* unkB4;     /* inferred */
	/* 0x0B8 */ f32 unkB8;       /* inferred */
	/* 0x0BC */ char padBC[0xC]; /* maybe part of unkB8[4]? */
	/* 0x0C8 */ s32 unkC8;       /* inferred */
	/* 0x0CC */ char padCC[4];
	/* 0x0D0 */ s32 unkD0;         /* inferred */
	/* 0x0D4 */ s32 unkD4;         /* inferred */
	/* 0x0D8 */ char padD8[0xC];   /* maybe part of unkD4[4]? */
	/* 0x0E4 */ M2C_UNK* unkE4;    /* inferred */
	/* 0x0E8 */ void* unkE8;       /* inferred */
	/* 0x0EC */ void* unkEC;       /* inferred */
	/* 0x0F0 */ char padF0[0x16];  /* maybe part of unkEC[6]? */
	/* 0x106 */ u16 unk106;        /* inferred */
	/* 0x108 */ char pad108[0x10]; /* maybe part of unk106[9]? */
	/* 0x118 */ f32 unk118;        /* inferred */
	/* 0x11C */ char pad11C[4];
	/* 0x120 */ f32 unk120;       /* inferred */
	/* 0x124 */ char pad124[0xC]; /* maybe part of unk120[4]? */
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
	/* 0x164 */ char pad164[0x1C]; /* maybe part of unk160[8]? */
	/* 0x180 */ s32 unk180;        /* inferred */
	/* 0x184 */ char pad184[4];
	/* 0x188 */ s32 unk188;        /* inferred */
	/* 0x18C */ char pad18C[0x10]; /* maybe part of unk188[5]? */
	/* 0x19C */ s32 unk19C;        /* inferred */
	/* 0x1A0 */ f32 unk1A0;        /* inferred */
	/* 0x1A4 */ f32 unk1A4;        /* inferred */
	/* 0x1A8 */ char pad1A8[0x10]; /* maybe part of unk1A4[5]? */
	/* 0x1B8 */ f32 unk1B8;        /* inferred */
	/* 0x1BC */ char pad1BC[4];
	/* 0x1C0 */ f32 unk1C0;              /* inferred */
	/* 0x1C4 */ f32 unk1C4;              /* inferred */
	/* 0x1C8 */ f32 unk1C8;              /* inferred */
	/* 0x1CC */ f32 unk1CC;              /* inferred */
	/* 0x1D0 */ f32 unk1D0;              /* inferred */
	/* 0x1D4 */ f32 unk1D4;              /* inferred */
	/* 0x1D8 */ f32 unk1D8;              /* inferred */
	/* 0x1DC */ f32 unk1DC;              /* inferred */
	/* 0x1E0 */ f32 unk1E0;              /* inferred */
	/* 0x1E4 */ char pad1E4[0x28];       /* maybe part of unk1E0[0xB]? */
	/* 0x20C */ f32 unk20C;              /* inferred */
	/* 0x210 */ f32 unk210;              /* inferred */
	/* 0x214 */ f32 unk214;              /* inferred */
	/* 0x218 */ char pad218[0x10];       /* maybe part of unk214[5]? */
	/* 0x228 */ void** unk228;           /* inferred */
	/* 0x22C */ char pad22C[0x14];       /* maybe part of unk228[6]? */
	/* 0x240 */ void** unk240;           /* inferred */
	/* 0x244 */ TEnemyParalysis* unk244; /* inferred */
	/* 0x248 */ s32 unk248;              /* inferred */
	/* 0x24C */ s32 unk24C;              /* inferred */
	/* 0x250 */ void** unk250;           /* inferred */
	/* 0x254 */ u32 unk254;              /* inferred */
	/* 0x258 */ void* unk258;            /* inferred */
	/* 0x25C */ s32 unk25C;              /* inferred */
	/* 0x260 */ s32 unk260;              /* inferred */
	/* 0x264 */ s32 unk264;              /* inferred */
	/* 0x268 */ s32 unk268;              /* inferred */
	/* 0x26C */ s32 unk26C;              /* inferred */
	/* 0x270 */ s32 unk270;              /* inferred */
	/* 0x274 */ s32 unk274;              /* inferred */
	/* 0x278 */ s32 unk278;              /* inferred */
	/* 0x27C */ s32 unk27C;              /* inferred */
	/* 0x280 */ s32 unk280;              /* inferred */
	/* 0x284 */ s32 unk284;              /* inferred */
	/* 0x288 */ s32 unk288;              /* inferred */
	/* 0x28C */ s32 unk28C;              /* inferred */
	/* 0x290 */ s32 unk290;              /* inferred */
	/* 0x294 */ s32 unk294;              /* inferred */
	/* 0x298 */ s32 unk298;              /* inferred */
	/* 0x29C */ s32 unk29C;              /* inferred */
	/* 0x2A0 */ f32 unk2A0;              /* inferred */
	/* 0x2A4 */ char pad2A4[4];
	/* 0x2A8 */ f32 unk2A8;       /* inferred */
	/* 0x2AC */ f32 unk2AC;       /* inferred */
	/* 0x2B0 */ f32 unk2B0;       /* inferred */
	/* 0x2B4 */ f32 unk2B4;       /* inferred */
	/* 0x2B8 */ f32 unk2B8;       /* inferred */
	/* 0x2BC */ s32 unk2BC;       /* inferred */
	/* 0x2C0 */ s32 unk2C0;       /* inferred */
	/* 0x2C4 */ s32 unk2C4;       /* inferred */
	/* 0x2C8 */ char pad2C8[8];   /* maybe part of unk2C4[3]? */
	/* 0x2D0 */ s32 unk2D0;       /* inferred */
	/* 0x2D4 */ char pad2D4[0xC]; /* maybe part of unk2D0[4]? */
	/* 0x2E0 */ s32 unk2E0;       /* inferred */
	/* 0x2E4 */ s32 unk2E4;       /* inferred */
	/* 0x2E8 */ char pad2E8[4];
	/* 0x2EC */ s32 unk2EC; /* inferred */
	/* 0x2F0 */ s32 unk2F0; /* inferred */
	/* 0x2F4 */ s32 unk2F4; /* inferred */
	/* 0x2F8 */ f32 unk2F8; /* inferred */
	/* 0x2FC */ f32 unk2FC; /* inferred */
	/* 0x300 */ f32 unk300; /* inferred */
	/* 0x304 */ f32 unk304; /* inferred */
	/* 0x308 */ f32 unk308; /* inferred */
	/* 0x30C */ f32 unk30C; /* inferred */
	/* 0x310 */ s32 unk310; /* inferred */
	/* 0x314 */ s32 unk314; /* inferred */
	/* 0x318 */ s32 unk318; /* inferred */
	/* 0x31C */ f32 unk31C; /* inferred */
} TEnemyWork;               /* size >= 0x320 */

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
class TSubDispatch
{
public:
	virtual void vslot2(M2C_UNK);
	virtual void vslot3(void*);
};

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

/* Dispatch view of the object handed to the state jumptable: retail reads the
 * vtable through the incoming `this` in r3 and calls the slot with the state
 * argument in r4, so the call has to go through a class. Slot numbers are the
 * retail vtable offsets, and the two implicit destructor slots occupy 0 and 4. */
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
};

/* The object's class shape, recovered from the retail vtable (__vt__TObjEnemyTurtle) and
 * the PS2 build's symbols. Only the virtual interface is modelled: the
 * compiler generates the vtable and the TObjSetObj adjustor thunk from these
 * declarations. The method bodies below are written against the object's
 * storage and carry the mangled names the vtable refers to. */
typedef struct SETDATA_PARAM SETDATA_PARAM;
typedef struct sEnemyCommand sEnemyCommand;
enum ENEMY_MD { ENEMY_MD_0 };

struct TObjectHdr {
	u8 pad0[0x18];
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

	u8 pad1C[0xC];
};

/* The object's C_COLLI and remaining TObjEnemy fields up to the set-object
 * base at 0xB0. */
class TObjEnemyBody : public TObject
{
public:
	u8 pad28[0x88];
};

struct SetObjHdr {
	SETDATA_PARAM* frame;
};

class TObjSetObj : public SetObjHdr
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);
};

class TObjEnemy : public TObjEnemyBody, public TObjSetObj
{
public:
	enum eCtrlSMode { CTRL_S_MODE_0 };

	virtual ~TObjEnemy();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual s32 CheckDamage2();
	virtual void DestroyMyself();
	virtual void Explosion();
	virtual void InitMode(ENEMY_MD);
	virtual void ExecMode(ENEMY_MD);
	virtual void ExitMode(ENEMY_MD);
	virtual void CtrlMode(ENEMY_MD, eCtrlSMode) = 0;
	virtual void Update()                       = 0;
	virtual void UpdateOnEdit()                 = 0;
	virtual void DispOpaq()                     = 0;
	virtual void DispTrans()                    = 0;
	virtual void DispShadow()                   = 0;
	virtual void DispOpaqOnEdit();
	virtual void Virtual33D94();
	virtual void KillMySelf();
	virtual s32 CheckCameraFrustumTest(const RwV3d*, f32);
	virtual s32 CheckCameraFrustumTestForShadow(const RwV3d*, f32);
	virtual void AddScore() = 0;
	virtual s32 CanCheckTechnicPointForThunderShoot();
	virtual s32 IsSleep();
	virtual void AddItemBox(RwV3d*) = 0;
	virtual s32 Virtual33D98();
	virtual s32 GetCurrentLightNum();
	virtual void RcvCommand(sEnemyCommand*) = 0;
	virtual void DispEnemySetting();
	virtual void Virtual33DA0();
	virtual void Virtual33DA4();
	virtual void EditOnChange(SETDATA_PARAM*);
};

class TObjEnemyTurtle : public TObjEnemy
{
public:
	inline virtual ~TObjEnemyTurtle();
	inline virtual s32 CheckDamage2();
	inline virtual void Explosion();
	inline virtual void CtrlMode(ENEMY_MD, TObjEnemy::eCtrlSMode);
	inline virtual void Update();
	inline virtual void UpdateOnEdit();
	inline virtual void DispOpaq();
	inline virtual void DispTrans();
	inline virtual void DispShadow();
	inline virtual s32 CheckCameraFrustumTestForShadow(const RwV3d*, f32);
	inline virtual void AddScore();
	inline virtual void AddItemBox(RwV3d*);
	inline virtual void RcvCommand(sEnemyCommand*);
	virtual void EditOnChange(SETDATA_PARAM*);
};

/* The editor clamp: the bounds are passed by reference, so each one is a
 * real constant object that the result can point at. */
template <class T> static inline const T& Clamp(const T& value, const T& lo, const T& hi)
{
	if (value < lo) {
		return lo;
	}
	if (value > hi) {
		return hi;
	}
	return value;
}

extern "C" {
extern void* __vt__15TObjEnemyTurtle[];
void Debug__7TObjectFv(void);
void Error__7TObjectFPc(void);
void ImmAftSetRaster__7TObjectFv(void);
void PDisp__7TObjectFv(void);
void Render__7TObjectFv(void);
void IsSleep__9TObjEnemyFv(void);
void DestroyMyself__9TObjEnemyFv(void);
void DispEnemySetting__9TObjEnemyFv(void);
void KillMySelf__9TObjEnemyFv(void);
void GetCurrentLightNum__9TObjEnemyFv(void);
void ExitMode__9TObjEnemyF8ENEMY_MD(void);
void ExecMode__9TObjEnemyF8ENEMY_MD(void);
void InitMode__9TObjEnemyF8ENEMY_MD(void);
void CanCheckTechnicPointForThunderShoot__9TObjEnemyFv(void);
void CheckCameraFrustumTest__9TObjEnemyFPC5RwV3df(void);
void TDisp__9TObjEnemyFv(void);
void Disp__9TObjEnemyFv(void);
void Exec__9TObjEnemyFv(void);
void DispOpaqOnEdit__9TObjEnemyFv(void);
void Virtual33D94__9TObjEnemyFv(void);
void Virtual33D98__9TObjEnemyFv(void);
void Virtual33DA0__9TObjEnemyFv(void);
void Virtual33DA4__9TObjEnemyFv(void);
void fn_8_C28CC(void);

M2C_UNK SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(void*, void*, void*);      /* extern */
s32 SetPosition__18TObjEffTornadoSpinFv(void*);                                   /* extern */
M2C_UNK Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(void*, void*, s32); /* extern */
void* __ct__10HAnimClassFv(void*);                                                /* extern */
TEnemyParalysis* __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(
    void*, void*, void*);                                                               /* extern */
void* __ct__15sParalysisParamFv(void*);                                                 /* extern */
M2C_UNK __dl__FPv(void* arg0);                                                          /* extern */
void* __dt__10HAnimClassFv(void*, s32);                                                 /* extern */
M2C_UNK __register_global_object(void*, void*, void*);                                  /* extern */
M2C_UNK __dt__11ENEMYMTNMANFv(void*, M2C_UNK);                                          /* extern */
s32 fn_80017800(void*);                                                                 /* extern */
M2C_UNK Free__9THeapCtrlFPv(s32, void*);                                                /* extern */
TEnemyParalysis* Malloc__9THeapCtrlFUi(s32, M2C_UNK);                                   /* extern */
u32 fn_800207C4(M2C_UNK*, M2C_UNK, M2C_UNK);                                            /* extern */
u32 fn_800209C8(M2C_UNK*, M2C_UNK);                                                     /* extern */
void* fn_80020D1C(M2C_UNK*);                                                            /* extern */
M2C_UNK fn_80020EEC(M2C_UNK*);                                                          /* extern */
void* fn_800210C4(M2C_UNK*);                                                            /* extern */
void* fn_800211A8(M2C_UNK*);                                                            /* extern */
M2C_UNK fn_80021824(M2C_UNK*);                                                          /* extern */
M2C_UNK Entry__7C_COLLIFv(M2C_UNK*);                                                    /* extern */
M2C_UNK Init__7C_COLLIFP8CCL_INFOiUc(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);             /* extern */
s32 fn_80041AB0(s32);                                                                   /* extern */
s32 fn_80041B64(s32);                                                                   /* extern */
void** __nw__FUl(M2C_UNK);                                                              /* extern */
s32 OnEdit__10TObjSetObjFv(void**);                                                     /* extern */
M2C_UNK objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(void*, s32); /* extern */
s32 objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(void*, M2C_UNK);      /* extern */
M2C_UNK objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(
    u32, M2C_UNK);                                                           /* extern */
M2C_UNK fn_8005FD8C(void*, M2C_UNK);                                         /* extern */
void* fn_800627BC(M2C_UNK, void*, void*);                                    /* extern */
M2C_UNK fn_8006298C(M2C_UNK, f32*, s32*);                                    /* extern */
M2C_UNK addSFA__9PARAM_SFAFif(M2C_UNK*, s32, f32);                           /* extern */
s32 fn_8009278C(M2C_UNK, s32);                                               /* extern */
s32 fn_800A2B78(TObjEffTornadoSpin*, TObjEffTornadoSpin*);                   /* extern */
s32 fn_800A2D90(void*, void*);                                               /* extern */
M2C_UNK fn_800A31B8(void*, s32);                                             /* extern */
s32 fn_800A37A4();                                                           /* extern */
M2C_UNK fn_800A3CBC(void*);                                                  /* extern */
M2C_UNK fn_800A3D48(TEnemyWork*);                                            /* extern */
s32 fn_800A3E10(TObjEffTornadoSpin*, TObjEffTornadoSpin*);                   /* extern */
s32 fn_800A3ED4(void*);                                                      /* extern */
M2C_UNK fn_800A4630(TObjEffTornadoSpin*, s32);                               /* extern */
M2C_UNK fn_800A4668(void*);                                                  /* extern */
M2C_UNK fn_800A4A8C(void*, f32);                                             /* extern */
s32 fn_800A5888(void*, f32);                                                 /* extern */
s32 fn_800A5998(void*);                                                      /* extern */
s32 fn_800A5A54(void*);                                                      /* extern */
f32 fn_800A5AC0();                                                           /* extern */
M2C_UNK fn_800A5B34(TEnemyWork*);                                            /* extern */
M2C_UNK fn_800A5B50(void*, M2C_UNK);                                         /* extern */
M2C_UNK fn_800A5C6C(void*, M2C_UNK);                                         /* extern */
s32 fn_800A6334(void*);                                                      /* extern */
M2C_UNK fn_800A7088(void*, M2C_UNK);                                         /* extern */
M2C_UNK fn_800A714C(TEnemyWork*, TEnemyWork*);                               /* extern */
s32 fn_800AAFEC(M2C_UNK*, s32*);                                             /* extern */
s32 fn_800AB104(s32);                                                        /* extern */
M2C_UNK fn_800B4A38(u32, M2C_UNK, s32*, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK fn_800B7514(void*, void*, f32*, f32);                                /* extern */
M2C_UNK fn_800B7820();                                                       /* extern */
M2C_UNK fn_800B7864(M2C_UNK);                                                /* extern */
f32 Distance2P2P__FPC5RwV3dPC5RwV3d(s32, s32);                               /* extern */
f32 DistanceP2P__FPC5RwV3dPC5RwV3d(void*, void*);                            /* extern */
s32 VectorAngle__FP5RwV3dP5RwV3dP5RwV3d(f32*, f32*, M2C_UNK*);               /* extern */
s32 AdjustAngle__Fiii(s32, s32, s32);                                        /* extern */
f32 fn_800D7AE4(s32);                                                        /* extern */
f32 fn_800D7B00(s32);                                                        /* extern */
f32 GetShadowPos__FP5RwV3dP6sAnglei(void*, s32*, M2C_UNK);                   /* extern */
void** __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID(void**, TEnemyWork*, s32);   /* extern */
M2C_UNK ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*); /* extern */
M2C_UNK LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*);                                                             /* extern */
void** __ct__11ENEMYMTNMANFv(void*);                                                /* extern */
M2C_UNK UpdateMotion__11ENEMYMTNMANFv(void**);                                      /* extern */
u32 SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK); /* extern */
u32 SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK Delete__14TEnemyDataBaseF14eEnemyDataBase(u32, M2C_UNK);                    /* extern */
M2C_UNK Add__14TEnemyDataBaseF14eEnemyDataBasePc(u32, M2C_UNK, M2C_UNK*);           /* extern */
M2C_UNK __ct__14TEnemyDataBaseFv();                                                 /* extern */
M2C_UNK SetEffectCrash3D_R__FP7TObjectP5RwV3dP6sAngleP5RwV3dP5RwV3dffisP7RpClump(
    s32, f32*, s32*, s32*, void*, f32, f32, s32, s16, u32);          /* extern */
s32 GetTeamNoFromPlayerNum__13nSearchPlayerFi(s32);                  /* extern */
s32 GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(void*, f32);      /* extern */
s32 IsOn__13TEnemyIconManFv(u32);                                    /* extern */
M2C_UNK Close__13TEnemyIconManFv(void*);                             /* extern */
M2C_UNK Change__13TEnemyIconManF10eEnemyIcon(u32, s32);              /* extern */
M2C_UNK Off__13TEnemyIconManFv(u32);                                 /* extern */
M2C_UNK On__13TEnemyIconManFffi(u32, f32, f32, s32);                 /* extern */
M2C_UNK On__13TEnemyIconManFff(u32, f32, f32);                       /* extern */
M2C_UNK SetPos__13TEnemyIconManFPC5RwV3dPC5RwV3d(u32, void*, void*); /* extern */
s32 Create__13TEnemyIconManF10eEnemyIcon(M2C_UNK);                   /* extern */
M2C_UNK SetLightNum__7nRenderFUi();                                  /* extern */
M2C_UNK PreDisp__16TEnemyMatTextureFi(M2C_UNK*, s32);                /* extern */
M2C_UNK End__16TEnemyMatTextureFv(M2C_UNK*);                         /* extern */
M2C_UNK Init__16TEnemyMatTextureFP15RwTexDictionaryP7RpClumpP10sEnTexturei(
    M2C_UNK*, u32, u32, M2C_UNK*, M2C_UNK);                 /* extern */
M2C_UNK __ct__16TEnemyMatTextureFv(M2C_UNK*);               /* extern */
M2C_UNK __ct__15sRingLaserParamFv(void*);                   /* extern */
M2C_UNK fn_8011C13C(u32);                                   /* extern */
M2C_UNK ParalyzeEnemy__14TEnemyScoreManFi(u32, s32);        /* extern */
M2C_UNK TornadoEnemy__14TEnemyScoreManFi(u32, s32);         /* extern */
M2C_UNK AddScore__14TEnemyScoreManFii(u32, s32, M2C_UNK);   /* extern */
M2C_UNK CreateInstance__14TEnemyScoreManFv();               /* extern */
M2C_UNK fn_80139784(void*, TEnemyWork*, f32*);              /* extern */
void* fn_80139984(M2C_UNK, M2C_UNK, M2C_UNK);               /* extern */
M2C_UNK fn_8014FF2C(s32);                                   /* extern */
void* fn_80150588(u32);                                     /* extern */
M2C_UNK fn_80150958(void*);                                 /* extern */
M2C_UNK fn_80195790(M2C_UNK*, RwFrame*, f32, f32, M2C_UNK); /* extern */
M2C_UNK fn_80195A74(void*, RwFrame*, f32, s32);             /* extern */
M2C_UNK fn_80196050(M2C_UNK*, void*, M2C_UNK);              /* extern */
M2C_UNK fn_801990E0(f32*, f32*);                            /* extern */
M2C_UNK fn_8019941C(f32*, f32*, M2C_UNK, M2C_UNK*);         /* extern */
s32 fn_8019CE34(s32, f32*);                                 /* extern */
void* fn_8019E8EC(u32);                                     /* extern */
M2C_UNK fn_8019EB94(RwFrame*, void*, M2C_UNK);              /* extern */
M2C_UNK fn_8019ECCC(void*, s32*, M2C_UNK);                  /* extern */
M2C_UNK fn_8019ED68(void*, RwFrame*, f32, s32);             /* extern */
s32 rand(void);                                             /* extern */
M2C_UNK CreateItemBox__8nItemBoxFP5RwV3d(s32);              /* extern */
void fn_8_BDF6C(TEnemyWork* arg0, void* arg1);              /* static */
void** fn_8_BE528(void* arg0);                              /* static */
s32 fn_8_BF340(void* arg0);                                 /* static */
s32 fn_8_BF524(s32 arg0);                                   /* static */
s32 fn_8_BF5AC(void* arg0);                                 /* static */
void fn_8_BFF94(void* arg0, s32 arg1);                      /* static */
void fn_8_C08C8(void* arg0, s32 arg1);                      /* static */
void fn_8_C14B4(TEnemyWork* arg0);                          /* static */
void fn_8_C1BCC(TEnemyWork* arg0);                          /* static */
TEnemyWork* fn_8_C2018(TEnemyWork* arg0, TEnemyWork* arg1); /* static */
void turtleObjectCreate();                                  /* static */
void turtleObjectLoad();                                    /* static */
void turtleObjectUnload();                                  /* static */
extern M2C_UNK __dt__16TEnemyMatTextureFv;
extern RwFrame AxisX;
extern RwFrame AxisY;
extern RwFrame AxisZ;
extern M2C_UNK lbl_802AD090;
extern M2C_UNK lbl_80303DC8;
extern TEnemyWork* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern M2C_UNK lbl_8042C1A4;
extern s32 lbl_8042C2A0;
extern u32 lbl_8042C388;
extern u32 mpDataBase__14TEnemyDataBase;
extern u32 EnemyScoreMan__14TEnemyScoreMan;
extern s32* lbl_8042C9A4;
/* forward declarations for the dispatch tables below */
void fn_8_BDA50(void* arg0, s32 arg1);
void fn_8_BDB0C(void* arg0, s32 arg1);
void fn_8_BDB2C(void* arg0, s32 arg1);
void fn_8_BDB4C(void* arg0, s32 arg1);
void fn_8_BDC5C(void* arg0, s32 arg1);
void fn_8_BDC7C(void* arg0, s32 arg1);
void fn_8_BDC9C(void* arg0, s32 arg1);
void fn_8_BDD50(void* arg0, s32 arg1);
void fn_8_BDE04(void* arg0, s32 arg1);
void fn_8_BDEB8(void* arg0, s32 arg1);
s32 fn_8_BE044(void* arg0);
void fn_8_BE39C(void** arg0, u32 arg1, s32 arg2);
M2C_UNK** fn_8_BE4C4(M2C_UNK** arg0, s16 arg1);
M2C_UNK** fn_8_BE55C(M2C_UNK** arg0, s16 arg1);
void fn_8_BE5AC(void* arg0, void* arg1);
void AddItemBox__15TObjEnemyTurtleFP5RwV3d(void* arg0, s32 arg1);
void RcvCommand__15TObjEnemyTurtleFP13sEnemyCommand(void* arg0, void* arg1);
void AddScore__15TObjEnemyTurtleFv(void* arg0);
void Explosion__15TObjEnemyTurtleFv(void* arg0);
s32 CheckDamage2__15TObjEnemyTurtleFv(TObjEffTornadoSpin* arg0);
s32 CheckCameraFrustumTestForShadow__15TObjEnemyTurtleFPC5RwV3df(void* arg0, f32 farg0);
void DispShadow__15TObjEnemyTurtleFv(void* arg0);
void DispTrans__15TObjEnemyTurtleFv(void);
void DispOpaq__15TObjEnemyTurtleFv(void* arg0);
void UpdateOnEdit__15TObjEnemyTurtleFv(TEnemyWork* arg0);
void Update__15TObjEnemyTurtleFv(TEnemyWork* arg0);
void CtrlMode__15TObjEnemyTurtleF8ENEMY_MDQ29TObjEnemy10eCtrlSMode(void* arg0, u32 arg1, s32 arg2);
void* __dt__15TObjEnemyTurtleFv(void* arg0, s16 arg1);

static u32 lbl_8_bss_1B78;
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
	u8 pad2C[4];             /* 0x2C */
} ObjectEntry;               /* 0x30 */
extern const f32 lbl_8_rodata_1E38[3] = { 0.0f, 1.5f, 0.0f };
extern const f32 lbl_8_rodata_1E44[3] = { 13.0f, 35.0f, 0.0f };
extern const f32 lbl_8_rodata_1E50[3] = { 24.0f, 1.0f, 24.0f };
extern const f32 lbl_8_rodata_1E5C[3] = { 0.0f, 0.0f, -1.0f };

static char lbl_8_data_17C70[] = "en_turtle.anm";
static char lbl_8_data_17C80[] = "en_turtle_start.anm";
static char lbl_8_data_17C94[] = "en_turtle_walk.anm";
static char lbl_8_data_17CA8[] = "en_turtle_defence.anm";
static char lbl_8_data_17CC0[] = "en_turtle_usided.anm";
typedef struct s17CD8Rec {
	u32 unk0;
	u32 unk4;
	u32 unk8;
	u32 unkC;
	u32 unk10;
	u32 unk14;
	u32 unk18;
	char* unk1C;
	u32 unk20;
} s17CD8Rec;

static s17CD8Rec lbl_8_data_17CD8[6] = {
	{ 0x00000000, 0x00000003, 0x00000000, 0x00000000, 0xBF800000, 0x3D800000, 0x3D4CCCCD,
	    lbl_8_data_17C70, 0x00000003 },
	{ 0x00000000, 0x0000000B, 0x00000000, 0x00000000, 0xBF800000, 0x3D800000, 0x3E4CCCCD,
	    lbl_8_data_17C80, 0x00000007 },
	{ 0x00000000, 0x00000003, 0x00000000, 0x00000000, 0xBF800000, 0x3E800000, 0x3E4CCCCD,
	    lbl_8_data_17C94, 0x00000009 },
	{ 0x00000000, 0x0000000B, 0x00000000, 0x00000000, 0xBF800000, 0x3D800000, 0x3E4CCCCD,
	    lbl_8_data_17CA8, 0x00000007 },
	{ 0x00000000, 0x00000003, 0x00000000, 0x00000000, 0xBF800000, 0x3D800000, 0x3ECCCCCD,
	    lbl_8_data_17CC0, 0x00000008 },
	{ 0x00000000, 0x0000000E, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	    0x00000000, 0x00000000 },
};
static char lbl_8_data_17DB0[] = "en_sub_ttl_shoot.anm";
typedef struct s17DC8Rec {
	u32 unk0;
	u32 unk4;
	u32 unk8;
	u32 unkC;
	u32 unk10;
	u32 unk14;
	u32 unk18;
	char* unk1C;
	u32 unk20;
} s17DC8Rec;

static s17DC8Rec lbl_8_data_17DC8[3] = {
	{ 0x00000000, 0x0000000B, 0x00000000, 0x00000000, 0xBF800000, 0x3F800000, 0x3E4CCCCD,
	    lbl_8_data_17DB0, 0x00000002 },
	{ 0x00000000, 0x00000005, 0x00000000, 0x00000000, 0x41100000, 0x3F800000, 0x3E4CCCCD,
	    lbl_8_data_17DB0, 0x00000002 },
	{ 0x00000000, 0x0000000E, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	    0x00000000, 0x00000000 },
};
static u32 lbl_8_data_17E34[24] = {
	0x0000FF21,
	0x00000400,
	0x00000000,
	0x41200000,
	0x00000000,
	0x41700000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0000FF21,
	0x00000400,
	0x00000000,
	0x40A00000,
	0x41700000,
	0x41000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
};
static char lbl_8_data_17E94[]   = "en_kam1";
static char lbl_8_data_17E9C[]   = "en_kam2";
static char* lbl_8_data_17EA4[6] = { lbl_8_data_17E94, NULL, NULL, lbl_8_data_17E9C, NULL, NULL };
static char lbl_8_data_17EBC[]   = "TURTLE TYPE";
static char lbl_8_data_17EC8[]   = "APPEAR TYPE";
static char lbl_8_data_17ED4[]   = "Not in use";
static char lbl_8_data_17EE0[]   = "MOVE RANGE";
static char lbl_8_data_17EEC[]   = "SCOPE RANGE";
static char lbl_8_data_17EF8[]   = "SCOPE OFFSET";
static char lbl_8_data_17F08[]   = "ATTACK INTERVAL";
static char lbl_8_data_17F18[]   = "WEAPON SPEED";
static char* turtleObjectFieldNames[9]
    = { lbl_8_data_17EBC, lbl_8_data_17EC8, lbl_8_data_17ED4, lbl_8_data_17ED4, lbl_8_data_17EE0,
	      lbl_8_data_17EEC, lbl_8_data_17EF8, lbl_8_data_17F08, lbl_8_data_17F18 };
static char lbl_8_data_17F4C[]      = "NORMAL";
static char lbl_8_data_17F54[]      = "SPECIAL";
static M2C_UNK* lbl_8_data_17F5C[2] = { (M2C_UNK*)lbl_8_data_17F4C, (M2C_UNK*)lbl_8_data_17F54 };
static char lbl_8_data_17F64[]      = "WAIT";
static char lbl_8_data_17F6C[]      = "WALK";
static M2C_UNK* lbl_8_data_17F74[2] = { (M2C_UNK*)lbl_8_data_17F64, (M2C_UNK*)lbl_8_data_17F6C };
#pragma explicit_zero_data on
static s8 lbl_8_data_17F7C = 0;
static s8 lbl_8_data_17F7D = 1;
static s8 lbl_8_data_17F7E = 0;
static s8 lbl_8_data_17F7F = 1;
#pragma explicit_zero_data reset
static char lbl_8_data_17F80[]   = "TObjEnemyTurtle";
static M2C_UNK* lbl_8_data_17F90 = (M2C_UNK*)lbl_8_data_17F80;
static u32 lbl_8_data_17F94[3]   = {
	0x00000000,
	0x3F800000,
	0x00000000,
};

/* The unit's global objects. Their construction is the compiler-generated
 * static initializer that registers TURTLE OBJECT with the editor: it builds
 * the shared material-texture helper (and chains its destructor), then fills
 * the editor record. */
class TEnemyMatTexture
{
public:
	TEnemyMatTexture();
	~TEnemyMatTexture();

	u8 data[0x14];
};

struct TurtleObjectEntry : ObjectEntry {
	TurtleObjectEntry()
	{
		flags      = 0;
		unk18      = 0;
		name       = "TURTLE OBJECT";
		load       = (void (*)(void))turtleObjectLoad;
		unload     = (void (*)(void))turtleObjectUnload;
		create     = (void (*)(void))turtleObjectCreate;
		unk10      = (void*)0;
		flags      = 0x20000;
		unk18      = 0;
		unk20      = 0x1E;
		unk1C      = 0x1570;
		unk1E      = 4;
		unk21      = 0;
		fieldTypes = "ccccfffif";
		fieldNames = (const char**)turtleObjectFieldNames;
		if (fieldTypes != NULL) {
			flags |= 8;
		} else {
			flags &= ~8;
		}
	}
};

static TEnemyMatTexture turtleObjectGlobalA;
static void* lbl_8_bss_1B9C;
TurtleObjectEntry turtleObjectEntry;

/* The int-to-float bias that fn_8_BEB1C first converts with is generated
 * by the compiler at that point; the remaining constants follow it. */

/* The ring laser's launch parameters (e_ringlaser.h). */
typedef struct sRingLaserParam {
	/* 0x00 */ RwV3d pos;
	/* 0x0C */ RwV3d spd;
	/* 0x18 */ sAngle ang;
	/* 0x24 */ f32 scl;
	/* 0x28 */ f32 scl_acc;
	/* 0x2C */ s32 life;
} sRingLaserParam; /* size 0x30 */

M2C_UNK Create__18TObjEnemyRingLaserFPC15sRingLaserParam(sRingLaserParam*); /* extern */

/* Swings the turtle's aim toward the nearest leader, measured in its
 * ground plane. */
static inline void TurtleAimAtLeader(void* arg0)
{
	RwV3d sp8;
	RwV3d sp14;
	u8 sp9C[0x40]; /* an RwMatrix */
	f32 temp_f1;
	f32 temp_f31;
	s32 temp_r0_2;
	void* temp_r30_2;

	if (((s32)M2C_FIELD(arg0, s32*, 0x2F0) != 0) && ((u32)M2C_FIELD(arg0, u32*, 0x258) != 0U)) {
		temp_r0_2 = M2C_FIELD(arg0, s32*, 0x2D4);
		if (temp_r0_2 != -1) {
			temp_r30_2 = (void*)(u32) * (&lbl_802AD090 + temp_r0_2);
			if (temp_r30_2 != NULL) {
				M2C_FIELD(&sp8, M2C_BLOCK12*, 0) = M2C_FIELD(lbl_8_rodata_1E5C, M2C_BLOCK12*, 0);
				temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x150) + 0x8000);
				fn_80195790((s32*)sp9C, &AxisY,
				    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x150) + 0x8000), temp_f31, 0);
				fn_8019941C(&sp8.x, &sp8.x, 1, (s32*)sp9C);
				sp8.y = 0.0f;
				fn_801990E0(&sp8.x, &sp8.x);
				sp14.x  = M2C_FIELD(temp_r30_2, f32*, 0x18) - M2C_FIELD(arg0, f32*, 0x140);
				sp14.y  = M2C_FIELD(temp_r30_2, f32*, 0x1C) - M2C_FIELD(arg0, f32*, 0x144);
				temp_f1 = M2C_FIELD(temp_r30_2, f32*, 0x20);
				sp14.z  = temp_f1 - M2C_FIELD(arg0, f32*, 0x148);
				sp14.y  = 0.0f;
				fn_801990E0(&sp14.x, &sp14.x);
				M2C_FIELD(arg0, s32*, 0x29C) = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x29C),
				    VectorAngle__FP5RwV3dP5RwV3dP5RwV3d(
				        &sp8.x, &sp14.x, (M2C_UNK*)lbl_8_data_17F94),
				    0x200);
			}
		}
	}
}

/* Picks a new roaming target: a point ahead of the turtle, turned by its
 * set-object yaw plus a random spread. Inlined into the mode handlers and
 * also kept as the out-of-line fn_8_C1A88. */
static inline void TurtlePickRoamTarget(void* arg0)
{
	u8 sp14[0x44];
	RwV3d sp8;
	f32 angle;

	sp8.x = 0.0f;
	sp8.y = 0.0f;
	sp8.z = M2C_FIELD(arg0, f32*, 0x2A0);
	angle = (180.0f + (0.005493164f * (f32)M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x10)))
	    + ((160.0f * (0.000030517578f * (f32)rand())) - 80.0f);
	fn_80195A74(sp14, &AxisY, angle, 0);
	fn_80196050((s32*)sp14, M2C_FIELD(arg0, void**, 0xB0), 2);
	fn_8019941C(&sp8.x, &sp8.x, 1, (s32*)sp14);
	M2C_FIELD(arg0, f32*, 0x1CC) = sp8.x;
	M2C_FIELD(arg0, f32*, 0x1D0) = sp8.y;
	M2C_FIELD(arg0, f32*, 0x1D4) = sp8.z;
	M2C_FIELD(arg0, f32*, 0x2A0) *= -1.0f;
}

/* Turns the turtle toward its target heading; true once it is within
 * sixteen angle units and has snapped onto it. */
static inline s32 TurtleTurnToTarget(void* arg0)
{
	s32 diff;

	if ((s32)M2C_FIELD(arg0, s32*, 0x2F0) == 0) {
		return 0;
	}
	diff                         = fn_800A5A54(arg0);
	M2C_FIELD(arg0, s32*, 0x150) = AdjustAngle__Fiii(
	    M2C_FIELD(arg0, s32*, 0x150), M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
	if (diff < 0x10) {
		M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
		return 1;
	}
	return 0;
}

typedef struct RpHAnimNodeInfo {
	s32 nodeID;
	s32 nodeIndex;
	s32 flags;
	u32 pFrame;
} RpHAnimNodeInfo;

typedef struct RwMatrixData {
	RwV3d right;
	u32 flags;
	RwV3d up;
	u32 pad1;
	RwV3d at;
	u32 pad2;
	RwV3d pos;
	u32 pad3;
} RwMatrixData;

/* Retail compiles this unit with deferred inlining, which emits the
 * functions in reverse definition order; they are defined last-first here. */
void AddItemBox__15TObjEnemyTurtleFP5RwV3d(void* arg0, s32 arg1);
void fn_8_BE668(TEnemyWork* arg0);
void fn_8_BE770(void* arg0, void* arg1);
void RcvCommand__15TObjEnemyTurtleFP13sEnemyCommand(void* arg0, void* arg1);
void AddScore__15TObjEnemyTurtleFv(void* arg0);
void Explosion__15TObjEnemyTurtleFv(void* arg0);
void fn_8_BEB1C(void* arg0);
void fn_8_BEBC8(void* arg0);
s32 fn_8_BED48(s32 arg0);
s32 fn_8_BEDA8(s32 arg0);
s32 CheckDamage2__15TObjEnemyTurtleFv(TObjEffTornadoSpin* arg0);
s32 fn_8_BF340(void* arg0);
void fn_8_BF3CC(void* arg0);
s32 fn_8_BF524(s32 arg0);
s32 fn_8_BF5AC(void* arg0);
s32 fn_8_BF684(void* arg0);
s32 fn_8_BF700(void* arg0);
s32 CheckCameraFrustumTestForShadow__15TObjEnemyTurtleFPC5RwV3df(void* arg0, f32 farg0);
void DispShadow__15TObjEnemyTurtleFv(void* arg0);
void DispTrans__15TObjEnemyTurtleFv(void);
void DispOpaq__15TObjEnemyTurtleFv(void* arg0);
void UpdateOnEdit__15TObjEnemyTurtleFv(TEnemyWork* arg0);
void Update__15TObjEnemyTurtleFv(TEnemyWork* arg0);
void fn_8_BFD74(void* arg0, s32 arg1);
void fn_8_BFE68(void* arg0, s32 arg1);
void fn_8_BFF94(void* arg0, s32 arg1);
void fn_8_C0418(void* arg0, s32 arg1);
void fn_8_C0690(void* arg0, s32 arg1);
void fn_8_C06F0(void* arg0, s32 arg1);
void fn_8_C0730(void* arg0, s32 arg1);
void fn_8_C086C(void* arg0, s32 arg1);
void fn_8_C08C8(void* arg0, s32 arg1);
void fn_8_C0C9C(void* arg0, s32 arg1);
void CtrlMode__15TObjEnemyTurtleF8ENEMY_MDQ29TObjEnemy10eCtrlSMode(void* arg0, u32 arg1, s32 arg2);
void fn_8_C14B4(TEnemyWork* arg0);
void fn_8_C19F4(void* arg0);
void fn_8_C1A34(void* arg0);
void fn_8_C1A88(void* arg0);
void fn_8_C1BCC(TEnemyWork* arg0);
void fn_8_C1E90(void* arg0);
void* __dt__15TObjEnemyTurtleFv(void* arg0, s16 arg1);
TEnemyWork* fn_8_C2018(TEnemyWork* arg0, TEnemyWork* arg1);
TEnemyParalysis* fn_8_C2344(void);
void turtleObjectUnload(void);
void turtleObjectLoad(void);
void turtleObjectCreate(void);

void turtleObjectCreate(void)
{
	TEnemyParalysis* object = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x320);
	if (object != NULL) {
		fn_8_C2018((TEnemyWork*)object, lbl_8042C10C);
	}
}

void turtleObjectLoad(void)
{
	u32 temp_r3;

	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	Add__14TEnemyDataBaseF14eEnemyDataBasePc(
	    mpDataBase__14TEnemyDataBase, 4, (M2C_UNK*)"en_turtle.one");
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	temp_r3 = SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(
	    mpDataBase__14TEnemyDataBase, 4, 5);
	if (temp_r3 != 0U) {
		objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(temp_r3, 6);
	} else {
		return;
	}
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	lbl_8_bss_1B78
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 4, 4);
	LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    4, (M2C_UNK*)lbl_8_data_17CD8);
	LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    4, (M2C_UNK*)lbl_8_data_17DC8);
	Init__16TEnemyMatTextureFP15RwTexDictionaryP7RpClumpP10sEnTexturei(
	    (M2C_UNK*)&turtleObjectGlobalA, temp_r3, lbl_8_bss_1B78, (M2C_UNK*)lbl_8_data_17EA4, 2);
	lbl_8_bss_1B9C = fn_80139984(0, 0x402D, 4);
}

void turtleObjectUnload(void)
{
	if ((void*)lbl_8_bss_1B9C != NULL) {
		M2C_FIELD(lbl_8_bss_1B9C, u16*, 4) = (u16)(M2C_FIELD(lbl_8_bss_1B9C, u16*, 4) | 1);
		lbl_8_bss_1B9C                     = NULL;
	}
	End__16TEnemyMatTextureFv((M2C_UNK*)&turtleObjectGlobalA);
	ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    4, (M2C_UNK*)lbl_8_data_17DC8);
	ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    4, (M2C_UNK*)lbl_8_data_17CD8);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != NULL)) {
		__ct__14TEnemyDataBaseFv();
	}
	Delete__14TEnemyDataBaseF14eEnemyDataBase(mpDataBase__14TEnemyDataBase, 4);
}

/* The turtle's set-object parameter block, as the editor fields name it. */
typedef struct sTurtleSetParam {
	/* 0x00 */ s8 turtleType;
	/* 0x01 */ s8 appearType;
	/* 0x02 */ u8 pad2[2];
	/* 0x04 */ f32 moveRange;
	/* 0x08 */ f32 scopeRange;
	/* 0x0C */ f32 scopeOffset;
	/* 0x10 */ s32 attackInterval;
	/* 0x14 */ f32 weaponSpeed;
} sTurtleSetParam;

void TObjEnemyTurtle::EditOnChange(SETDATA_PARAM* arg1)
{
	/* Clamp bounds for the editor's float and integer parameters. */
	static const f32 moveRangeMin   = 0.0f;
	static const f32 moveRangeMax   = 10000.0f;
	static const f32 scopeRangeMin  = 0.0f;
	static const f32 scopeRangeMax  = 10000.0f;
	static const s32 intervalMin    = 0;
	static const s32 intervalMax    = 10000;
	static const f32 weaponSpeedMin = 0.0f;
	static const f32 weaponSpeedMax = 10000.0f;
	u8* temp_r3;
	sTurtleSetParam* param;
	u8* var_r4;
	u8* var_r4_2;
	s8 temp_r0;
	s8 temp_r0_2;

	temp_r3 = M2C_FIELD(arg1, u8**, 0x2C);
	param   = (sTurtleSetParam*)temp_r3;
	temp_r0 = M2C_FIELD(temp_r3, s8*, 0);
	if (temp_r0 < lbl_8_data_17F7C) {
		var_r4 = (u8*)&lbl_8_data_17F7C;
	} else if (temp_r0 > lbl_8_data_17F7D) {
		var_r4 = (u8*)&lbl_8_data_17F7D;
	} else {
		var_r4 = temp_r3;
	}
	M2C_FIELD(temp_r3, s8*, 0) = (s8)*var_r4;
	temp_r0_2                  = M2C_FIELD(temp_r3, s8*, 1);
	if (temp_r0_2 < lbl_8_data_17F7E) {
		var_r4_2 = (u8*)&lbl_8_data_17F7E;
	} else if (temp_r0_2 > lbl_8_data_17F7F) {
		var_r4_2 = (u8*)&lbl_8_data_17F7F;
	} else {
		var_r4_2 = temp_r3 + 1;
	}
	M2C_FIELD(temp_r3, s8*, 1) = (s8)*var_r4_2;
	param->moveRange           = Clamp(param->moveRange, moveRangeMin, moveRangeMax);
	param->scopeRange          = Clamp(param->scopeRange, scopeRangeMin, scopeRangeMax);
	param->attackInterval      = Clamp(param->attackInterval, intervalMin, intervalMax);
	param->weaponSpeed         = Clamp(param->weaponSpeed, weaponSpeedMin, weaponSpeedMax);
	M2C_FIELD((M2C_UNK*)turtleObjectFieldNames, M2C_UNK**, 0)
	    = (M2C_UNK*)lbl_8_data_17F5C[(s8)M2C_FIELD(temp_r3, s8*, 0)];
	M2C_FIELD((M2C_UNK*)turtleObjectFieldNames, M2C_UNK**, 4)
	    = (M2C_UNK*)lbl_8_data_17F74[(s8)M2C_FIELD(temp_r3, s8*, 1)];
}

TEnemyParalysis* fn_8_C2344(void)
{
	TEnemyParalysis* var_r0;

	var_r0 = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x320);
	if (var_r0 != NULL) {
		var_r0 = (TEnemyParalysis*)fn_8_C2018((TEnemyWork*)var_r0, lbl_8042C10C);
	}
	return var_r0;
}

#pragma dont_inline on
TEnemyWork* fn_8_C2018(TEnemyWork* arg0, TEnemyWork* arg1)
{
	u32 setFlags;
	sParalysisParam sp8;
	TEnemyParalysis* temp_r3;
	TEnemyParalysis* var_r0_3;
	f32 temp_f0;
	void** var_r0;
	void** var_r0_2;
	void** var_r0_4;

	fn_800A714C(arg0, arg1);
	__ct__10HAnimClassFv((u8*)arg0 + 0x240);
	arg0->unk18  = (M2C_UNK*)__vt__15TObjEnemyTurtle;
	arg0->unkB4  = (M2C_UNK*)&__vt__15TObjEnemyTurtle[11];
	arg0->unk0   = lbl_8_data_17F90;
	arg0->unk1E  = 0x320;
	arg0->unk248 = 0;
	arg0->unk2C0 = 0;
	arg0->unk2BC = 0;
	arg0->unk24C = -1;
	arg0->unk2C4 = 1;
	arg0->unk254 = 0U;
	arg0->unk2D0 = 0;
	arg0->unk258 = NULL;
	arg0->unk29C = 0;
	arg0->unk244 = NULL;
	arg0->unk2E0 = 0;
	arg0->unk2EC = 0;
	arg0->unk2F0 = 1;
	arg0->unk2F4 = 1;
	fn_8_C1BCC(arg0);
	arg0->unk188 &= 0xFFFF3FFF;
	arg0->unk188 |= 0x4000;
	arg0->unk160 = 0.0f;
	arg0->unk15C = 0.0f;
	arg0->unk158 = 0.0f;
	arg0->unk188 &= 0xFFEFCFFF;
	arg0->unk188 |= 0x100000;
	arg0->unk188 |= 0x10;
	temp_f0      = arg0->unk2B4;
	arg0->unk1A4 = temp_f0;
	arg0->unk2E  = (s16)temp_f0;
	arg0->unk1A0 = 3.0f;
	arg0->unk2C  = 3;
	if ((s32)arg0->unk310 == 0) {
		arg0->unk188 |= 0x10000;
	} else {
		arg0->unk188 |= 0x40000;
	}
	if ((void*)arg0->unkE8 != NULL) {
		fn_80150958((void*)arg0->unkE8);
		arg0->unkE8 = NULL;
	}
	arg0->unkE8 = fn_80150588(lbl_8_bss_1B78);
	var_r0      = __nw__FUl(0x4C);
	if (var_r0 != NULL) {
		var_r0 = __ct__11ENEMYMTNMANFv((void*)var_r0);
	}
	arg0->unk250 = var_r0;
	setFlags     = M2C_FIELD(arg0->unkB0, s32*, 0x18);
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
	    arg0->unkE8, ((setFlags & 0x1C0000) >> 0x12) + 8);
	arg0->unkE4  = (M2C_UNK*)lbl_8_data_17CD8;
	arg0->unkD4  = 0;
	arg0->unk2E4 = 0;
	UpdateMotion__11ENEMYMTNMANFv((void**)&arg0->unkB8);
	fn_8_C14B4(arg0);
	if (OnEdit__10TObjSetObjFv(&arg0->unkB0) == 0) {
		Init__7C_COLLIFP8CCL_INFOiUc(&arg0->unk28, (M2C_UNK*)lbl_8_data_17E34, 2, 3);
		arg0->unk88 = arg0->unk140;
		arg0->unk8C = arg0->unk144;
		arg0->unk90 = arg0->unk148;
	}
	arg0->unk130 = 12.0f;
	arg0->unk134 = 0.8f;
	var_r0_2     = __nw__FUl(0x1C);
	if (var_r0_2 != NULL) {
		var_r0_2 = fn_8_BE528(var_r0_2);
	}
	arg0->unk240 = var_r0_2;
	if ((void**)arg0->unk240 != NULL) {
		fn_8_BDF6C((TEnemyWork*)arg0->unk240, arg0);
	}
	arg0->unk2BC = Create__13TEnemyIconManF10eEnemyIcon(1);
	arg0->unk2C0 = Create__13TEnemyIconManF10eEnemyIcon(0);
	__ct__15sParalysisParamFv(&sp8);
	sp8.offset.z = 12.0f;
	sp8.offset.y = 12.0f;
	sp8.offset.x = 12.0f;
	temp_r3      = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x74);
	var_r0_3     = temp_r3;
	if (var_r0_3 != NULL) {
		var_r0_3 = __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(temp_r3, lbl_8042C10C, &sp8);
	}
	arg0->unk244 = var_r0_3;
	arg0->unk13C = 1;
	var_r0_4     = __nw__FUl(0x20);
	if (var_r0_4 != NULL) {
		var_r0_4 = __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID(var_r0_4, arg0, arg0->unk13C);
	}
	arg0->unk228 = var_r0_4;
	return arg0;
}
#pragma dont_inline reset

void* __dt__15TObjEnemyTurtleFv(void* arg0, s16 arg1)
{
	s32 temp_cr0_eq;
	void** temp_r3_2;
	void* temp_r3;

	if (arg0 != NULL) {
		M2C_FIELD(arg0, M2C_UNK**, 0x18) = (M2C_UNK*)__vt__15TObjEnemyTurtle;
		M2C_FIELD(arg0, void**, 0xB4)    = (void*)((u8*)&__vt__15TObjEnemyTurtle + 0x2C);
		temp_r3                          = M2C_FIELD(arg0, void**, 0x244);
		if (temp_r3 != NULL) {
			M2C_FIELD(temp_r3, u16*, 4)    = (u16)(M2C_FIELD(temp_r3, u16*, 4) | 1);
			M2C_FIELD(arg0, void**, 0x244) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
			Close__13TEnemyIconManFv((void*)M2C_FIELD(arg0, u32*, 0x2C0));
			M2C_FIELD(arg0, u32*, 0x2C0) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
			Close__13TEnemyIconManFv((void*)M2C_FIELD(arg0, u32*, 0x2BC));
			M2C_FIELD(arg0, u32*, 0x2BC) = 0U;
		}
		temp_r3_2 = M2C_FIELD(arg0, void***, 0x240);
		if (temp_r3_2 != NULL) {
			if (temp_r3_2 != NULL) {
				((TSubDispatch*)temp_r3_2)->vslot2(1);
			}
			M2C_FIELD(arg0, void***, 0x240) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x250) != 0U) {
			__dt__11ENEMYMTNMANFv((void*)M2C_FIELD(arg0, u32*, 0x250), 1);
			M2C_FIELD(arg0, u32*, 0x250) = 0U;
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

void fn_8_C1E90(void* arg0)
{
	M2C_FIELD(arg0, s32*, 0x248) = 0;
	M2C_FIELD(arg0, s32*, 0x2C0) = 0;
	M2C_FIELD(arg0, s32*, 0x2BC) = 0;
	M2C_FIELD(arg0, s32*, 0x24C) = -1;
	M2C_FIELD(arg0, s32*, 0x2C4) = 1;
	M2C_FIELD(arg0, s32*, 0x254) = 0;
	M2C_FIELD(arg0, s32*, 0x2D0) = 0;
	M2C_FIELD(arg0, s32*, 0x258) = 0;
	M2C_FIELD(arg0, s32*, 0x29C) = 0;
	M2C_FIELD(arg0, s32*, 0x244) = 0;
	M2C_FIELD(arg0, s32*, 0x2E0) = 0;
	M2C_FIELD(arg0, s32*, 0x2EC) = 0;
	M2C_FIELD(arg0, s32*, 0x2F0) = 1;
	M2C_FIELD(arg0, s32*, 0x2F4) = 1;
}

void fn_8_C1BCC(TEnemyWork* arg0)
{
	s32 temp_r0;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r4;

	temp_r4      = M2C_FIELD(arg0->unkB0, void**, 0x2C);
	arg0->unk310 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0);
	arg0->unk314 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 1);
	arg0->unk318 = M2C_FIELD(temp_r4, s32*, 0x10);
	arg0->unk31C = M2C_FIELD(temp_r4, f32*, 0x14);
	arg0->unk20C = M2C_FIELD(temp_r4, f32*, 8);
	arg0->unk210 = M2C_FIELD(temp_r4, f32*, 4);
	arg0->unk214 = M2C_FIELD(temp_r4, f32*, 8);
	arg0->unk1D8 = 0.0f;
	arg0->unk1DC = 0.0f;
	arg0->unk1E0 = M2C_FIELD(temp_r4, f32*, 0xC);
	temp_r3      = arg0->unkB0;
	arg0->unk140 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unk144 = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unk148 = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2    = arg0->unkB0;
	arg0->unk14C = M2C_FIELD(temp_r3_2, s32*, 0xC);
	arg0->unk150 = M2C_FIELD(temp_r3_2, s32*, 0x10);
	arg0->unk154 = M2C_FIELD(temp_r3_2, s32*, 0x14);
	arg0->unk1C0 = arg0->unk140;
	arg0->unk1C4 = arg0->unk144;
	arg0->unk1C8 = arg0->unk148;
	arg0->unk1CC = arg0->unk140;
	arg0->unk1D0 = arg0->unk144;
	arg0->unk1D4 = arg0->unk148;
	arg0->unk1C0 = arg0->unk140;
	arg0->unk1C4 = arg0->unk144;
	arg0->unk1C8 = arg0->unk148;
	arg0->unk1B8 = 0.2f;
	arg0->unk2A0 = -arg0->unk210;
	TurtlePickRoamTarget(arg0);
	arg0->unk2A8 = arg0->unk1CC;
	arg0->unk2AC = arg0->unk1D0;
	arg0->unk2B0 = arg0->unk1D4;
	arg0->unk180 = 0x50;
	temp_r0      = arg0->unk310;
	switch (temp_r0) {
		case 0:
			arg0->unk2B8 = 3.0f;
			arg0->unk2B4 = arg0->unk2B8;
			break;
		case 1:
			arg0->unk2B8 = 6.0f;
			arg0->unk2B4 = arg0->unk2B8;
			break;
		default:
			arg0->unk2B8 = 3.0f;
			arg0->unk2B4 = arg0->unk2B8;
			break;
	}
}

void fn_8_C1A88(void* arg0)
{
	TurtlePickRoamTarget(arg0);
}

void fn_8_C1A34(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0xE8));
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	M2C_FIELD(arg0, void**, 0xE8) = fn_80150588(lbl_8_bss_1B78);
}

void fn_8_C19F4(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0xE8));
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

void fn_8_C14B4(TEnemyWork* arg0)
{
	sAngle sp8;
	RwFrame* temp_r31;
	f32 temp_f1;
	s32 temp_r3_3;
	s32 temp_r3_4;
	void* temp_r31_2;
	void* temp_r31_3;
	void* temp_r3;
	void* temp_r4;

	temp_r3 = arg0->unkE8;
	if (temp_r3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3, RwFrame**, 4);
		if (((s32)arg0->unk19C == 0x24) && (arg0->unk244 != NULL)) {
			Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(
			    arg0->unk244, temp_r31, (RwOpCombineType)0);
			fn_8019ED68(temp_r31, &AxisZ, 0.005493164f * (f32)arg0->unk154, 2);
			fn_8019ED68(temp_r31, &AxisX, 0.005493164f * (f32)arg0->unk14C, 2);
			fn_8019ED68(temp_r31, &AxisY, 180.0f + (0.005493164f * (f32)arg0->unk150), 2);
			fn_8019EB94(temp_r31, &arg0->unk140, 2);
			SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(
			    arg0->unk244, &arg0->unk140, (u8*)arg0 + 0x14C);
		} else {
			fn_8019ED68(temp_r31, &AxisZ, 0.005493164f * (f32)arg0->unk154, 0);
			fn_8019ED68(temp_r31, &AxisX, 0.005493164f * (f32)arg0->unk14C, 2);
			fn_8019ED68(temp_r31, &AxisY, 180.0f + (0.005493164f * (f32)arg0->unk150), 2);
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
		}
	}
	if ((s32)arg0->unk24C == -1) {
		arg0->unk24C
		    = objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(arg0->unkEC, 0x3E8);
		if ((s32)arg0->unk24C != -1) {
			M2C_FIELD(arg0->unk250, void**, 0x44)    = (void*)arg0->unkEC;
			M2C_FIELD(arg0->unk250, M2C_UNK**, 0x2C) = (M2C_UNK*)lbl_8_data_17DC8;
			M2C_FIELD(arg0->unk250, s32*, 0x40)      = (s32)arg0->unk24C;
			M2C_FIELD(arg0->unk250, s32*, 0x1C)      = 0;
		}
	}
	if ((u32)arg0->unk254 == 0U) {
		temp_r31_2 = arg0->unkEC;
		if (temp_r31_2 != NULL) {
			temp_r3_3
			    = objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(temp_r31_2, 0x3EA);
			if (temp_r3_3 != -1) {
				arg0->unk254 = M2C_FIELD(temp_r31_2, RpHAnimNodeInfo**, 0x10)[temp_r3_3].pFrame;
			}
		}
	}
	if ((void*)arg0->unk258 == NULL) {
		temp_r31_3 = arg0->unkEC;
		if (temp_r31_3 != NULL) {
			temp_r3_4
			    = objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(temp_r31_3, 0x3E9);
			if (temp_r3_4 != -1) {
				arg0->unk258
				    = (void*)M2C_FIELD(temp_r31_3, RpHAnimNodeInfo**, 0x10)[temp_r3_4].pFrame;
				temp_r4 = arg0->unk258;
				if (temp_r4 != NULL) {
					/* the bone frame's modelling matrix */
					M2C_FIELD(arg0, RwMatrixData*, 0x25C) = M2C_FIELD(temp_r4, RwMatrixData*, 0x10);
				}
			}
		}
	}
	if ((u32)(M2C_FIELD(arg0->unkB0, s32*, 0x18) & 0x20000) != 0) {
		if ((s32)(arg0->unk106 & 2) != 0) {
			arg0->unk304 = arg0->unk118;
			arg0->unk30C = arg0->unk120;
			arg0->unk2FC = 0.3f + arg0->unk144;
		} else {
			temp_f1      = GetShadowPos__FP5RwV3dP6sAnglei((f32*)((u8*)arg0 + 0x140), &sp8.x, 1);
			arg0->unk2FC = temp_f1;
			if (-1000000.0f != temp_f1) {
				arg0->unk2F8 = arg0->unk140;
				arg0->unk2FC += 0.3f;
				arg0->unk300 = arg0->unk148;
				arg0->unk304 = 0.005493164f * (f32)sp8.x;
				arg0->unk30C = 0.005493164f * (f32)sp8.z;
			}
		}
		arg0->unk308 = 180.0f + (0.005493164f * (f32)arg0->unk150);
		arg0->unk2F8 = arg0->unk140;
		arg0->unk300 = arg0->unk148;
	}
}

void CtrlMode__15TObjEnemyTurtleF8ENEMY_MDQ29TObjEnemy10eCtrlSMode(void* arg0, u32 arg1, s32 arg2)
{
	RwV3d sp14;
	RwV3d sp8;
	u8 sp20[0x40]; /* an RwMatrix */
	u32 temp_handle;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f31;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r0_4;
	s32 temp_r30;
	s32 var_r0;
	void* temp_r30_2;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;
	void* temp_r3_6;
	void* temp_r3_7;

	switch (arg1) {
		case 1:
			switch (arg2) {
				case 0:
					M2C_FIELD(arg0, s32*, 0x2E8) = 0;
					M2C_FIELD(arg0, s32*, 0xD4)  = 0;
					return;
				case 1:
					if ((s32)M2C_FIELD(arg0, s32*, 0x2E8) == 0) {
						if (M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), f32*, 0) >= 6.0f) {
							M2C_FIELD(arg0, s32*, 0x2E8) = 1;
							if ((u32)lbl_8042C388 != 0U) {
								fn_800B4A38(
								    lbl_8042C388, 0x402C, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
							}
						}
					}
					if ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), s32*, 0x10) & 1) != 0) {
						M2C_FIELD(arg0, s32*, 0x2C4) = 0;
					}
					break;
				case 2:
				case 3:
					break;
			}
			break;
		case 2:
			fn_8_C08C8(arg0, arg2);
			return;
		case 40:
			switch (arg2) {
				case 0:
					temp_r3                        = M2C_FIELD(arg0, void**, 0x38);
					M2C_FIELD(temp_r3, s32*, 0x34) = (s32)(M2C_FIELD(temp_r3, s32*, 0x34) | 0x10);
					M2C_FIELD(arg0, s32*, 0x188)   = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x20000);
					M2C_FIELD(arg0, s32*, 0xD4)    = 3;
					return;
				case 1:
				case 2:
					break;
				case 3:
					M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFFDFFFF);
					temp_r3_2                    = M2C_FIELD(arg0, void**, 0x38);
					M2C_FIELD(temp_r3_2, s32*, 0x34)
					    = (s32)(M2C_FIELD(temp_r3_2, s32*, 0x34) & 0xFFFFFFEF);
					return;
			}
			break;
		case 41:
			switch (arg2) {
				case 0:
					M2C_FIELD(arg0, s32*, 0x2CC) = 0;
					M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFDFFFFF);
					M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFFBFFFF);
					M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x400000);
					return;
				case 1:
					if ((fn_800A37A4() == 1) && ((s32)M2C_FIELD(arg0, s32*, 0x2CC) == 0)) {
						M2C_FIELD(arg0, s32*, 0x2CC) = 1;
						temp_f1                      = M2C_FIELD(arg0, f32*, 0x1A4) - 1.0f;
						M2C_FIELD(arg0, f32*, 0x1A4) = temp_f1;
						if (temp_f1 < 0.0f) {
							M2C_FIELD(arg0, f32*, 0x1A4) = 0.0f;
						}
						M2C_FIELD(arg0, s16*, 0x2E) = (s16)M2C_FIELD(arg0, f32*, 0x1A4);
						if ((u32)lbl_8042C388 != 0U) {
							fn_800B4A38(
							    lbl_8042C388, 0x402F, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
						}
						temp_r0 = M2C_FIELD(arg0, s32*, 0x2DC);
						if ((temp_r0 != -1) && ((u32) * (&lbl_80303DC8 + temp_r0) != 0U)) {
							M2C_FIELD(arg0, s32*, 0x230)
							    = fn_8009278C(*(&lbl_80303DC8 + temp_r0), 0);
							return;
						}
					}
					break;
				case 2:
				case 3:
					break;
			}
			break;
		case 42:
			switch (arg2) {
				case 0:
					M2C_FIELD(arg0, s32*, 0xD4) = 1;
					return;
				case 1:
				case 2:
					break;
				case 3:
					if ((s32)M2C_FIELD(arg0, s32*, 0x24C) != -1) {
						M2C_FIELD(arg0, s32*, 0x2C4)                          = 1;
						M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), s32*, 0x1C) = 1;
						return;
					}
					break;
			}
			break;
		case 29:
			switch (arg2) {
				case 0:
					((TRenderer*)arg0)->Slot3C();
					return;
				case 1:
					M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
					return;
				case 2:
				case 3:
					break;
			}
			break;
		case 31:
			switch (arg2) {
				case 0:
					M2C_FIELD(arg0, s32*, 0xD4) = 2;
					return;
				case 1:
					M2C_FIELD(arg0, s32*, 0x2D4) = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(
					    (void*)((u8*)arg0 + 0x140), 100000000.0f);
					temp_r0_2 = M2C_FIELD(arg0, s32*, 0x2D4);
					if (temp_r0_2 != -1) {
						temp_r3_3 = (void*)(u32) * (&lbl_802AD090 + temp_r0_2);
						if (temp_r3_3 != NULL) {
							M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(temp_r3_3, f32*, 0x18);
							M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(temp_r3_3, f32*, 0x1C);
							M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(temp_r3_3, f32*, 0x20);
						}
					}
					if ((s32)M2C_FIELD(arg0, s32*, 0x2F0) == 0) {
						var_r0 = 0;
					} else {
						temp_r30 = fn_800A5A54(arg0);
						M2C_FIELD(arg0, s32*, 0x150)
						    = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x150),
						        M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
						if (temp_r30 < 0x10) {
							M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
							var_r0                       = 1;
						} else {
							var_r0 = 0;
						}
					}
					if (var_r0 != 0) {
						M2C_FIELD(arg0, s32*, 0xD4) = 0;
					} else {
						M2C_FIELD(arg0, s32*, 0xD4) = 2;
					}
					if (((s32)M2C_FIELD(arg0, s32*, 0x2F0) != 0)
					    && ((u32)M2C_FIELD(arg0, u32*, 0x258) != 0U)) {
						temp_r0_3 = M2C_FIELD(arg0, s32*, 0x2D4);
						if (temp_r0_3 != -1) {
							temp_r30_2 = (void*)(u32) * (&lbl_802AD090 + temp_r0_3);
							if (temp_r30_2 != NULL) {
								M2C_FIELD(&sp8, M2C_BLOCK12*, 0)
								    = M2C_FIELD(lbl_8_rodata_1E5C, M2C_BLOCK12*, 0);
								temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x150) + 0x8000);
								fn_80195790((s32*)sp20, &AxisY,
								    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x150) + 0x8000),
								    temp_f31, 0);
								fn_8019941C(&sp8.x, &sp8.x, 1, (s32*)sp20);
								sp8.y = 0.0f;
								fn_801990E0(&sp8.x, &sp8.x);
								sp14.x = M2C_FIELD(temp_r30_2, f32*, 0x18)
								    - M2C_FIELD(arg0, f32*, 0x140);
								sp14.y = M2C_FIELD(temp_r30_2, f32*, 0x1C)
								    - M2C_FIELD(arg0, f32*, 0x144);
								temp_f1_2 = M2C_FIELD(temp_r30_2, f32*, 0x20);
								sp14.z    = temp_f1_2 - M2C_FIELD(arg0, f32*, 0x148);
								sp14.y    = 0.0f;
								fn_801990E0(&sp14.x, &sp14.x);
								M2C_FIELD(arg0, s32*, 0x29C)
								    = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x29C),
								        VectorAngle__FP5RwV3dP5RwV3dP5RwV3d(
								            &sp8.x, &sp14.x, (M2C_UNK*)lbl_8_data_17F94),
								        0x200);
								return;
							}
						}
					}
					break;
				case 2:
				case 3:
					break;
			}
			break;
		case 32:
			fn_8_BFF94(arg0, arg2);
			return;
		case 26:
			switch (arg2) {
				case 0:
					M2C_FIELD(arg0, s32*, 0x2DC) = (s32)M2C_FIELD(arg0, s32*, 0x234);
					if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
						CreateInstance__14TEnemyScoreManFv();
					}
					TornadoEnemy__14TEnemyScoreManFi(
					    EnemyScoreMan__14TEnemyScoreMan, M2C_FIELD(arg0, s32*, 0x234));
					fn_800A3CBC(arg0);
					M2C_FIELD(arg0, f32*, 0x15C) = 5.0f;
					M2C_FIELD(arg0, s32*, 0xD4)  = 4;
					temp_r3_4                    = M2C_FIELD(arg0, void**, 0x38);
					if (temp_r3_4 != NULL) {
						M2C_FIELD(temp_r3_4, u8*, 3)
						    = (u8)(M2C_FIELD(temp_r3_4, u8*, 3) & 0xFFFFFFDF);
					}
					temp_r3_5 = (u8*)M2C_FIELD(arg0, void**, 0x38) + 0x30;
					if (temp_r3_5 != NULL) {
						M2C_FIELD(temp_r3_5, u8*, 3)
						    = (u8)(M2C_FIELD(temp_r3_5, u8*, 3) & 0xFFFFFFDF);
						return;
					}
					break;
				case 1:
					if (fn_800A37A4() == 1) {
						temp_r3_6 = M2C_FIELD(arg0, void**, 0x38);
						if (temp_r3_6 != NULL) {
							M2C_FIELD(temp_r3_6, u8*, 3)
							    = (u8)(M2C_FIELD(temp_r3_6, u8*, 3) | 0x20);
						}
						temp_r3_7 = (u8*)M2C_FIELD(arg0, void**, 0x38) + 0x30;
						if (temp_r3_7 != NULL) {
							M2C_FIELD(temp_r3_7, u8*, 3)
							    = (u8)(M2C_FIELD(temp_r3_7, u8*, 3) | 0x20);
						}
						M2C_FIELD(arg0, s32*, 0x248) = 0x29;
						return;
					}
					break;
				case 2:
				case 3:
					break;
			}
			break;
		case 36:
			switch (arg2) {
				case 0:
					M2C_FIELD(arg0, s32*, 0x2D8) = 0x5A;
					M2C_FIELD(arg0, s32*, 0xD4)  = 0;
					if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
						CreateInstance__14TEnemyScoreManFv();
					}
					ParalyzeEnemy__14TEnemyScoreManFi(
					    EnemyScoreMan__14TEnemyScoreMan, M2C_FIELD(arg0, s32*, 0x238));
					return;
				case 1:
					temp_r0_4                    = M2C_FIELD(arg0, s32*, 0x2D8) - 1;
					M2C_FIELD(arg0, s32*, 0x2D8) = temp_r0_4;
					if (temp_r0_4 == 0) {
						if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
							Off__13TEnemyIconManFv(M2C_FIELD(arg0, u32*, 0x2C0));
						}
						if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
							Change__13TEnemyIconManF10eEnemyIcon(M2C_FIELD(arg0, u32*, 0x2BC), 2);
							temp_handle = M2C_FIELD(arg0, u32*, 0x2BC);
							On__13TEnemyIconManFff(temp_handle, 0.0f, 0.0f);
							return;
						}
					}
					break;
				case 2:
					break;
				case 3:
					if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
						Off__13TEnemyIconManFv(M2C_FIELD(arg0, u32*, 0x2BC));
					}
					break;
			}
			break;
	}
}

void fn_8_C0C9C(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2E8) = 0;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			break;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x2E8) == 0) {
				if (M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), f32*, 0) >= 6.0f) {
					M2C_FIELD(arg0, s32*, 0x2E8) = 1;
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x402C, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
					}
				}
			}
			if ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), s32*, 0x10) & 1) != 0) {
				M2C_FIELD(arg0, s32*, 0x2C4) = 0;
			}
			break;
		case 2:
		case 3:
			break;
	}
}

static inline s32 TurtleWalkStep(void* arg0, s32 keep)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x2F0) == 0) {
		return keep;
	}
	if ((fn_800A5AC0() < 2.0f) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
		fn_800A4668(arg0);
		keep = 0;
	} else {
		fn_800A4A8C(arg0, 0.15f);
	}
	fn_800A5C6C(arg0, 0xF00);
	if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
	    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
		M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
	}
	if (fn_800A5888(arg0, -1.0f) != 0) {
		fn_800A5B50(arg0, 0xF00);
		keep = 0;
	} else if ((((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)
	               || (DistanceP2P__FPC5RwV3dPC5RwV3d((u8*)arg0 + 0x140, (u8*)arg0 + 0x1E4) < 0.1f))
	    && (fn_800A5998(arg0) <= 0)) {
		keep = 0;
	}
	return keep;
}

void fn_8_C08C8(void* arg0, s32 arg1)
{
	s32 var_r31;

	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x2C4) = 0;
			M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFDFFFFF);
			M2C_FIELD(arg0, s32*, 0xD4)  = 2;
			M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x2A8);
			M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x2AC);
			M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x2B0);
			if (TurtleTurnToTarget(arg0) != 0) {
				M2C_FIELD(arg0, s32*, 0x2A4) = 1;
			} else {
				M2C_FIELD(arg0, s32*, 0x2A4) = 0;
			}
			break;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x2A4) != 0) {
				var_r31 = 1;
				var_r31 = TurtleWalkStep(arg0, var_r31);
				if (var_r31 == 0) {
					TurtlePickRoamTarget(arg0);
					M2C_FIELD(arg0, s32*, 0x2A4) = 0;
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x2A4) == 0) {
				if (TurtleTurnToTarget(arg0) != 0) {
					M2C_FIELD(arg0, s32*, 0x2A4) = 1;
				}
			}
			break;
		case 2:
			break;
		case 3:
			M2C_FIELD(arg0, f32*, 0x2A8) = (f32)M2C_FIELD(arg0, f32*, 0x1CC);
			M2C_FIELD(arg0, f32*, 0x2AC) = (f32)M2C_FIELD(arg0, f32*, 0x1D0);
			M2C_FIELD(arg0, f32*, 0x2B0) = (f32)M2C_FIELD(arg0, f32*, 0x1D4);
			break;
	}
}

void fn_8_C086C(void* arg0, s32 arg1)
{
	void* temp_r4;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			temp_r4                        = M2C_FIELD(arg0, void**, 0x38);
			M2C_FIELD(temp_r4, s32*, 0x34) = (s32)(M2C_FIELD(temp_r4, s32*, 0x34) | 0x10);
			M2C_FIELD(arg0, s32*, 0x188)   = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x20000);
			M2C_FIELD(arg0, s32*, 0xD4)    = 3;
			return;
		case 3:
			M2C_FIELD(arg0, s32*, 0x188)   = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFFDFFFF);
			temp_r3                        = M2C_FIELD(arg0, void**, 0x38);
			M2C_FIELD(temp_r3, s32*, 0x34) = (s32)(M2C_FIELD(temp_r3, s32*, 0x34) & 0xFFFFFFEF);
			return;
	}
}

void fn_8_C0730(void* arg0, s32 arg1)
{
	f32 temp_f1;
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2CC) = 0;
			M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFDFFFFF);
			M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFFBFFFF);
			M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x400000);
			break;
		case 1:
			if ((fn_800A37A4() == 1) && ((s32)M2C_FIELD(arg0, s32*, 0x2CC) == 0)) {
				M2C_FIELD(arg0, s32*, 0x2CC) = 1;
				temp_f1                      = M2C_FIELD(arg0, f32*, 0x1A4) - 1.0f;
				M2C_FIELD(arg0, f32*, 0x1A4) = temp_f1;
				if (temp_f1 < 0.0f) {
					M2C_FIELD(arg0, f32*, 0x1A4) = 0.0f;
				}
				M2C_FIELD(arg0, s16*, 0x2E) = (s16)M2C_FIELD(arg0, f32*, 0x1A4);
				if ((u32)lbl_8042C388 != 0U) {
					fn_800B4A38(lbl_8042C388, 0x402F, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
				}
				temp_r0 = M2C_FIELD(arg0, s32*, 0x2DC);
				if ((temp_r0 != -1) && ((u32) * (&lbl_80303DC8 + temp_r0) != 0U)) {
					M2C_FIELD(arg0, s32*, 0x230) = fn_8009278C(*(&lbl_80303DC8 + temp_r0), 0);
				}
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_C06F0(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 1;
			return;
		case 3:
			if ((s32)M2C_FIELD(arg0, s32*, 0x24C) != -1) {
				M2C_FIELD(arg0, s32*, 0x2C4)                          = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), s32*, 0x1C) = 1;
			}
			break;
	}
}

void fn_8_C0690(void* arg0, s32 arg1)
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

void fn_8_C0418(void* arg0, s32 arg1)
{
	RwV3d sp14;
	RwV3d sp8;
	u8 sp20[0x48];
	f32 temp_f1;
	f32 temp_f31;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r30;
	s32 var_r0;
	void* temp_r30_2;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 2;
			break;
		case 1:
			M2C_FIELD(arg0, s32*, 0x2D4) = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(
			    (void*)((u8*)arg0 + 0x140), 100000000.0f);
			temp_r0 = M2C_FIELD(arg0, s32*, 0x2D4);
			if (temp_r0 != -1) {
				temp_r3 = (void*)(u32) * (&lbl_802AD090 + temp_r0);
				if (temp_r3 != NULL) {
					M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(temp_r3, f32*, 0x18);
					M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(temp_r3, f32*, 0x1C);
					M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(temp_r3, f32*, 0x20);
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x2F0) == 0) {
				var_r0 = 0;
			} else {
				temp_r30                     = fn_800A5A54(arg0);
				M2C_FIELD(arg0, s32*, 0x150) = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x150),
				    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
				if (temp_r30 < 0x10) {
					M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
					var_r0                       = 1;
				} else {
					var_r0 = 0;
				}
			}
			if (var_r0 != 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 2;
			}
			if (((s32)M2C_FIELD(arg0, s32*, 0x2F0) != 0)
			    && ((u32)M2C_FIELD(arg0, u32*, 0x258) != 0U)) {
				temp_r0_2 = M2C_FIELD(arg0, s32*, 0x2D4);
				if (temp_r0_2 != -1) {
					temp_r30_2 = (void*)(u32) * (&lbl_802AD090 + temp_r0_2);
					if (temp_r30_2 != NULL) {
						M2C_FIELD(&sp8, M2C_BLOCK12*, 0)
						    = M2C_FIELD(lbl_8_rodata_1E5C, M2C_BLOCK12*, 0);
						temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x150) + 0x8000);
						fn_80195790((s32*)sp20, &AxisY,
						    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x150) + 0x8000), temp_f31, 0);
						fn_8019941C(&sp8.x, &sp8.x, 1, (s32*)sp20);
						sp8.y = 0.0f;
						fn_801990E0(&sp8.x, &sp8.x);
						sp14.x  = M2C_FIELD(temp_r30_2, f32*, 0x18) - M2C_FIELD(arg0, f32*, 0x140);
						sp14.y  = M2C_FIELD(temp_r30_2, f32*, 0x1C) - M2C_FIELD(arg0, f32*, 0x144);
						temp_f1 = M2C_FIELD(temp_r30_2, f32*, 0x20);
						sp14.z  = temp_f1 - M2C_FIELD(arg0, f32*, 0x148);
						sp14.y  = 0.0f;
						fn_801990E0(&sp14.x, &sp14.x);
						M2C_FIELD(arg0, s32*, 0x29C)
						    = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x29C),
						        VectorAngle__FP5RwV3dP5RwV3dP5RwV3d(
						            &sp8.x, &sp14.x, (M2C_UNK*)lbl_8_data_17F94),
						        0x200);
					}
				}
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_BFF94(void* arg0, s32 arg1)
{
	RwV3d sp20;
	s32 temp_r0;
	s32 temp_r30;
	s32 var_r0;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2C8) = 0;
			if ((void*)M2C_FIELD(arg0, void**, 0x2EC) == NULL) {
				M2C_FIELD(arg0, void**, 0x2EC)
				    = fn_800627BC(0x1F, (u8*)arg0 + 0x140, (u8*)arg0 + 0x14C);
			}
			break;
		case 2:
			break;
		case 1:
			if ((void*)M2C_FIELD(arg0, void**, 0x2EC) != NULL) {
				if (fn_80017800(M2C_FIELD(arg0, void**, 0x2EC)) == 0) {
					M2C_FIELD(arg0, void**, 0x2EC) = NULL;
					return;
				}
				if ((u32)M2C_FIELD(arg0, u32*, 0x254) != 0U) {
					temp_r3                           = fn_8019E8EC(M2C_FIELD(arg0, u32*, 0x254));
					M2C_FIELD(&sp20, M2C_BLOCK12*, 0) = M2C_FIELD(temp_r3, M2C_BLOCK12*, 0x30);
					temp_r4                           = (u8*)arg0 + 0x14C;
					temp_r3_2                         = M2C_FIELD(arg0, void**, 0x2EC);
					M2C_FIELD(temp_r3_2, f32*, 0x80)  = sp20.x;
					M2C_FIELD(temp_r3_2, f32*, 0x84)  = sp20.y;
					M2C_FIELD(temp_r3_2, f32*, 0x88)  = sp20.z;
					if (temp_r4 != NULL) {
						M2C_FIELD(temp_r3_2, s32*, 0x8C) = (s32)M2C_FIELD(temp_r4, s32*, 0);
						M2C_FIELD(temp_r3_2, s32*, 0x90) = (s32)M2C_FIELD(temp_r4, s32*, 4);
						M2C_FIELD(temp_r3_2, s32*, 0x94) = (s32)M2C_FIELD(temp_r4, s32*, 8);
					}
				}
				M2C_FIELD(arg0, s32*, 0x2D4) = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(
				    (void*)((u8*)arg0 + 0x140), 100000000.0f);
				temp_r0 = M2C_FIELD(arg0, s32*, 0x2D4);
				if (temp_r0 != -1) {
					temp_r3_3 = (void*)(u32) * (&lbl_802AD090 + temp_r0);
					if (temp_r3_3 != NULL) {
						M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(temp_r3_3, f32*, 0x18);
						M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(temp_r3_3, f32*, 0x1C);
						M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(temp_r3_3, f32*, 0x20);
					}
				}
				if ((s32)M2C_FIELD(arg0, s32*, 0x2F0) == 0) {
					var_r0 = 0;
				} else {
					temp_r30                     = fn_800A5A54(arg0);
					M2C_FIELD(arg0, s32*, 0x150) = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x150),
					    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
					if (temp_r30 < 0x10) {
						M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
						var_r0                       = 1;
					} else {
						var_r0 = 0;
					}
				}
				if (var_r0 != 0) {
					M2C_FIELD(arg0, s32*, 0xD4) = 0;
				} else {
					M2C_FIELD(arg0, s32*, 0xD4) = 2;
				}
				TurtleAimAtLeader(arg0);
			} else if ((s32)M2C_FIELD(arg0, s32*, 0x2C8) == 0) {
				fn_8_BF3CC(arg0);
				M2C_FIELD(arg0, s32*, 0x2C8) = 1;
				M2C_FIELD(arg0, s32*, 0x248) = 0x1F;
				return;
			}
			break;
		case 3:
			if ((void*)M2C_FIELD(arg0, void**, 0x2EC) != NULL) {
				fn_8005FD8C((void*)M2C_FIELD(arg0, void**, 0x2EC), -1);
				M2C_FIELD(arg0, void**, 0x2EC) = NULL;
			}
			break;
	}
}

void fn_8_BFE68(void* arg0, s32 arg1)
{
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2DC) = (s32)M2C_FIELD(arg0, s32*, 0x234);
			if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
				CreateInstance__14TEnemyScoreManFv();
			}
			TornadoEnemy__14TEnemyScoreManFi(
			    EnemyScoreMan__14TEnemyScoreMan, M2C_FIELD(arg0, s32*, 0x234));
			fn_800A3CBC(arg0);
			M2C_FIELD(arg0, f32*, 0x15C) = 5.0f;
			M2C_FIELD(arg0, s32*, 0xD4)  = 4;
			temp_r3                      = M2C_FIELD(arg0, void**, 0x38);
			if (temp_r3 != NULL) {
				M2C_FIELD(temp_r3, u8*, 3) = (u8)(M2C_FIELD(temp_r3, u8*, 3) & 0xFFFFFFDF);
			}
			temp_r3_2 = (u8*)M2C_FIELD(arg0, void**, 0x38) + 0x30;
			if (temp_r3_2 != NULL) {
				M2C_FIELD(temp_r3_2, u8*, 3) = (u8)(M2C_FIELD(temp_r3_2, u8*, 3) & 0xFFFFFFDF);
				return;
			}
			break;
		case 1:
			if (fn_800A37A4() == 1) {
				temp_r3_3 = M2C_FIELD(arg0, void**, 0x38);
				if (temp_r3_3 != NULL) {
					M2C_FIELD(temp_r3_3, u8*, 3) = (u8)(M2C_FIELD(temp_r3_3, u8*, 3) | 0x20);
				}
				temp_r3_4 = (u8*)M2C_FIELD(arg0, void**, 0x38) + 0x30;
				if (temp_r3_4 != NULL) {
					M2C_FIELD(temp_r3_4, u8*, 3) = (u8)(M2C_FIELD(temp_r3_4, u8*, 3) | 0x20);
				}
				M2C_FIELD(arg0, s32*, 0x248) = 0x29;
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_BFD74(void* arg0, s32 arg1)
{
	u32 temp_handle;
	s32 temp_r0;

	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x2D8) = 0x5A;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
				CreateInstance__14TEnemyScoreManFv();
			}
			ParalyzeEnemy__14TEnemyScoreManFi(
			    EnemyScoreMan__14TEnemyScoreMan, M2C_FIELD(arg0, s32*, 0x238));
			break;
		case 1:
			temp_r0                      = M2C_FIELD(arg0, s32*, 0x2D8) - 1;
			M2C_FIELD(arg0, s32*, 0x2D8) = temp_r0;
			if (temp_r0 == 0) {
				if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
					Off__13TEnemyIconManFv(M2C_FIELD(arg0, u32*, 0x2C0));
				}
				if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
					Change__13TEnemyIconManF10eEnemyIcon(M2C_FIELD(arg0, u32*, 0x2BC), 2);
					temp_handle = M2C_FIELD(arg0, u32*, 0x2BC);
					On__13TEnemyIconManFff(temp_handle, 0.0f, 0.0f);
				}
			}
			break;
		case 2:
			break;
		case 3:
			if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
				Off__13TEnemyIconManFv(M2C_FIELD(arg0, u32*, 0x2BC));
			}
			break;
	}
}

void Update__15TObjEnemyTurtleFv(TEnemyWork* arg0)
{
	f32 temp_f31;
	s32 temp_r3_2;
	s32 var_r0;
	s32 var_r0_2;
	void** temp_r3;

	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	arg0->unk2F0 = var_r0;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0_2 = 0;
	} else {
		var_r0_2 = 1;
	}
	arg0->unk2F4 = var_r0_2;
	if ((u32)arg0->unk38 != 0U) {
		arg0->unk140 = arg0->unk88;
		arg0->unk144 = arg0->unk8C;
		arg0->unk148 = arg0->unk90;
	}
	fn_800A5B34(arg0);
	((TRenderer*)arg0)->Slot38();
	temp_r3 = arg0->unk240;
	if (temp_r3 != NULL) {
		((TSubDispatch*)temp_r3)->vslot3(arg0);
	}
	((TRenderer*)arg0)->Slot50(arg0->unk19C, 1);
	fn_8_C14B4(arg0);
	fn_800A3D48(arg0);
	if ((s32)arg0->unk2F4 != 0) {
		temp_r3_2 = arg0->unkD0;
		if (temp_r3_2 != (s32)arg0->unk2E4) {
			arg0->unk2E0 = 0;
			arg0->unk2E4 = temp_r3_2;
		}
		temp_f31 = arg0->unkB8;
		switch (temp_r3_2) {
			case 2:
				if ((temp_f31 > 0.5f) && ((s32)arg0->unk2E0 == 0)) {
					arg0->unk2E0 = 1;
					fn_80139784(lbl_8_bss_1B9C, arg0, &arg0->unk140);
				}
				if ((temp_f31 > 6.0f) && ((s32)arg0->unk2E0 == 1)) {
					arg0->unk2E0 = 2;
					fn_80139784(lbl_8_bss_1B9C, arg0, &arg0->unk140);
				}
				if (((s32)arg0->unk2E0 != 0) && ((u32)(arg0->unkC8 & 2) != 0)) {
					arg0->unk2E0 = 0;
				}
		}
	}
	if ((s32)arg0->unk2F0 != 0) {
		if ((s32)arg0->unk19C != 0x1F) {
			arg0->unk29C = AdjustAngle__Fiii(arg0->unk29C, 0, 0x220);
		}
		if ((void*)arg0->unk258 != NULL) {
			fn_8019ED68(
			    M2C_FIELD(arg0, void**, 0x258), &AxisY, 0.005493164f * (f32)arg0->unk29C, 0);
			fn_8019ECCC(arg0->unk258, &arg0->unk25C, 2);
		}
	}
	if (((s32)arg0->unk2C4 != 0) && ((s32)arg0->unk24C != -1)) {
		UpdateMotion__11ENEMYMTNMANFv(arg0->unk250);
	}
	if ((fn_80017800(arg0) != 0) && ((u32)arg0->unk38 != 0U)) {
		arg0->unkA4 = arg0->unk88;
		arg0->unkA8 = arg0->unk8C;
		arg0->unkAC = arg0->unk90;
		arg0->unk88 = arg0->unk140;
		arg0->unk8C = arg0->unk144;
		arg0->unk90 = arg0->unk148;
		arg0->unk94 = arg0->unk14C;
		arg0->unk98 = arg0->unk150;
		arg0->unk9C = arg0->unk154;
		Entry__7C_COLLIFv(&arg0->unk28);
	}
}

void UpdateOnEdit__15TObjEnemyTurtleFv(TEnemyWork* arg0)
{
	fn_8_C1BCC(arg0);
	fn_8_C14B4(arg0);
}

void DispOpaq__15TObjEnemyTurtleFv(void* arg0)
{
	((TRenderer*)arg0)->Slot90();
	SetLightNum__7nRenderFUi();
	PreDisp__16TEnemyMatTextureFi((M2C_UNK*)&turtleObjectGlobalA, M2C_FIELD(arg0, s32*, 0x310));
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0xE8));
}

void DispTrans__15TObjEnemyTurtleFv(void) { }

void DispShadow__15TObjEnemyTurtleFv(void* arg0)
{
	static const f32 shadowScaleMin = 0.2f;
	static const f32 shadowScaleMax = 1.0f;
	RwV3d spC;
	f32 sp8;
	f32 temp_f1;
	f32 temp_f2;
	f32 temp_f3;
	f32 temp_f1_2;

	fn_800B7864(0);
	M2C_FIELD(&spC, M2C_BLOCK12*, 0) = M2C_FIELD(lbl_8_rodata_1E50, M2C_BLOCK12*, 0);
	temp_f3                          = 1.0f;
	temp_f2   = 0.004f * (M2C_FIELD(arg0, f32*, 0x144) - M2C_FIELD(arg0, f32*, 0x2FC));
	temp_f1   = temp_f3 - temp_f2;
	sp8       = temp_f1;
	temp_f1_2 = Clamp(sp8, shadowScaleMin, shadowScaleMax);
	sp8       = temp_f1_2;
	fn_800B7514((u8*)arg0 + 0x2F8, (u8*)arg0 + 0x304, &spC.x, temp_f1_2);
	fn_800B7820();
}

s32 CheckCameraFrustumTestForShadow__15TObjEnemyTurtleFPC5RwV3df(void* arg0, f32 farg0)
{
	struct {
		RwV3d pos;
		f32 radius;
	} sphere;
	RwV3d* ground = (RwV3d*)((u8*)arg0 + 0x2F8);

	if (-1000000.0f != ground->y) {
		sphere.pos    = *ground;
		sphere.radius = farg0;
		return fn_8019CE34(*lbl_8042C9A4, &sphere.pos.x) != 0;
	}
	return 0;
}

s32 fn_8_BF700(void* arg0)
{
	s32 var_r31;

	var_r31 = 1;
	if ((s32)M2C_FIELD(arg0, s32*, 0x2F0) == 0) {
		return 1;
	}
	if ((fn_800A5AC0() < 2.0f) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
		fn_800A4668(arg0);
		var_r31 = 0;
	} else {
		fn_800A4A8C(arg0, 0.15f);
	}
	fn_800A5C6C(arg0, 0xF00);
	if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
	    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
		M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
	}
	if (fn_800A5888(arg0, -1.0f) != 0) {
		fn_800A5B50(arg0, 0xF00);
		var_r31 = 0;
	} else if ((((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)
	               || (DistanceP2P__FPC5RwV3dPC5RwV3d((u8*)arg0 + 0x140, (u8*)arg0 + 0x1E4) < 0.1f))
	    && (fn_800A5998(arg0) <= 0)) {
		var_r31 = 0;
	}
	return var_r31;
}

s32 fn_8_BF684(void* arg0)
{
	s32 temp_r31;

	if ((s32)M2C_FIELD(arg0, s32*, 0x2F0) == 0) {
		return 0;
	}
	temp_r31                     = fn_800A5A54(arg0);
	M2C_FIELD(arg0, s32*, 0x150) = AdjustAngle__Fiii(
	    M2C_FIELD(arg0, s32*, 0x150), M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
	if (temp_r31 < 0x10) {
		M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
		return 1;
	}
	return 0;
}

s32 fn_8_BF5AC(void* arg0)
{
	f32 temp_f1;
	s32 var_r31;

	var_r31 = 0;
	temp_f1 = M2C_FIELD(arg0, f32*, 0x1A4);
	if ((s32)M2C_FIELD(arg0, s32*, 0x2D0) != 0) {
		var_r31 = 1;
	}
	if (temp_f1 != M2C_FIELD(arg0, f32*, 0x2B4)) {
		M2C_FIELD(arg0, f32*, 0x2B4) = temp_f1;
		if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
			if ((s32)M2C_FIELD(arg0, s32*, 0x19C) == 0x24) {
				On__13TEnemyIconManFffi(
				    M2C_FIELD(arg0, u32*, 0x2C0), temp_f1, M2C_FIELD(arg0, f32*, 0x2B8), 0x5A);
			} else {
				On__13TEnemyIconManFff(
				    M2C_FIELD(arg0, u32*, 0x2C0), temp_f1, M2C_FIELD(arg0, f32*, 0x2B8));
			}
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
			Off__13TEnemyIconManFv(M2C_FIELD(arg0, u32*, 0x2BC));
		}
		var_r31 = 1;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
		SetPos__13TEnemyIconManFPC5RwV3dPC5RwV3d(
		    M2C_FIELD(arg0, u32*, 0x2C0), (u8*)arg0 + 0x140, (f32*)lbl_8_rodata_1E44);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
		SetPos__13TEnemyIconManFPC5RwV3dPC5RwV3d(
		    M2C_FIELD(arg0, u32*, 0x2BC), (u8*)arg0 + 0x140, (f32*)lbl_8_rodata_1E44);
	}
	return var_r31;
}

s32 fn_8_BF524(s32 arg0)
{
	s32 temp_r3;
	u32 temp_r3_2;

	temp_r3
	    = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df((void*)((u8*)arg0 + 0x140), 100000000.0f);
	if (temp_r3 != -1) {
		temp_r3_2 = *(&lbl_802AD090 + temp_r3);
		if ((temp_r3_2 != 0U)
		    && (Distance2P2P__FPC5RwV3dPC5RwV3d((s32)(temp_r3_2 + 0x18), arg0 + 0x140)
		        < 10000.0f)) {
			return 1;
		}
	}
	return 0;
}

/* Launches a ring laser from the turtle's muzzle node along its aim. The
 * attack mode handler (fn_8_BFF94) inlines this. */
void fn_8_BF3CC(void* arg0)
{
	sRingLaserParam param;
	u8 mtx[0x40]; /* an RwMatrix */
	f32 temp_f31;
	void* temp_r3;

	if ((u32)M2C_FIELD(arg0, u32*, 0x254) != 0U) {
		__ct__15sRingLaserParamFv(&param);
		temp_r3     = fn_8019E8EC(M2C_FIELD(arg0, u32*, 0x254));
		param.pos.x = M2C_FIELD(temp_r3, f32*, 0x30);
		param.pos.y = M2C_FIELD(temp_r3, f32*, 0x34);
		param.pos.z = M2C_FIELD(temp_r3, f32*, 0x38);
		param.ang.y = M2C_FIELD(arg0, s32*, 0x29C) + M2C_FIELD(arg0, s32*, 0x150);
		param.life  = 0x1A4;
		temp_f31    = fn_800D7B00(param.ang.y + 0x8000);
		fn_80195790((s32*)mtx, &AxisY, 1.0f - fn_800D7AE4(param.ang.y + 0x8000), temp_f31, 0);
		fn_8019941C(&param.spd.x, &param.spd.x, 1, (s32*)mtx);
		fn_801990E0(&param.spd.x, &param.spd.x);
		param.spd.x *= M2C_FIELD(arg0, f32*, 0x31C);
		param.spd.y *= M2C_FIELD(arg0, f32*, 0x31C);
		param.spd.z *= M2C_FIELD(arg0, f32*, 0x31C);
		Create__18TObjEnemyRingLaserFPC15sRingLaserParam(&param);
		if ((u32)lbl_8042C388 != 0U) {
			fn_800B4A38(lbl_8042C388, 0x402E, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
		}
	}
}

s32 fn_8_BF340(void* arg0)
{
	u32 temp_handle;
	s32 temp_r3;

	temp_r3 = fn_800A6334((void*)arg0);
	if ((temp_r3 == 1) && ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U)
	    && (((u32)M2C_FIELD(arg0, u32*, 0x2C0) == 0U)
	        || (IsOn__13TEnemyIconManFv(M2C_FIELD(arg0, u32*, 0x2C0)) == 0))) {
		Change__13TEnemyIconManF10eEnemyIcon(M2C_FIELD(arg0, u32*, 0x2BC), 1);
		temp_handle = M2C_FIELD(arg0, u32*, 0x2BC);
		On__13TEnemyIconManFff(temp_handle, 0.0f, 0.0f);
	}
	return temp_r3;
}

s32 CheckDamage2__15TObjEnemyTurtleFv(TObjEffTornadoSpin* arg0)
{
	s32 var_r30;
	void* var_r29_2;
	void* var_r29_3;
	s32 var_r29;
	u32 var_r28;
	s32 temp_r3_4;
	s32 sp8;
	s32 team;
	TObjEffTornadoSpin* var_r3;
	TObjEffTornadoSpin* var_r4;
	TObjEffTornadoSpin* var_r4_2;
	f32 temp_f31;
	f32 temp_f30;
	f32 var_f1;
	f32 var_f30;
	s32 temp_r3;
	s32 temp_r3_11;
	s32 temp_r3_2;
	s32 temp_r3_5;
	s32 temp_r4;
	s32 temp_r4_2;
	s32 var_r0_4;
	s32 var_r3_3;
	s32 var_r3_4;
	u32 var_r0;
	u32 var_r0_2;
	u32 var_r0_3;
	void* temp_r3_10;
	void* temp_r3_3;
	void* temp_r3_6;
	void* temp_r3_7;
	void* temp_r3_8;
	void* temp_r3_9;
	void* var_r3_2;

	if (fn_800A2D90(arg0, (u8*)arg0 + 0x140) != 0) {
		arg0->unk1A4 = 0.0f;
		arg0->unk230 = -1;
		return 1;
	}
	var_r4 = arg0;
	if (arg0 != NULL) {
		var_r4 = (TObjEffTornadoSpin*)((u8*)arg0 + 0x28);
	}
	temp_r3 = fn_800A2B78(arg0, var_r4);
	sp8     = temp_r3;
	if (temp_r3 != -1) {
		arg0->unk1A4 = 0.0f;
		arg0->unk230 = fn_800AB104(sp8);
		return 1;
	}
	sp8       = 0;
	temp_r3_2 = fn_800AAFEC(&arg0->unk140, &sp8);
	if ((temp_r3_2 != 0) && (temp_r3_2 >= 0) && (temp_r3_2 < 5)) {
		var_f1 = arg0->unk1A4 - 30.0f;
		if (var_f1 < 0.0f) {
			var_f1 = 0.0f;
		}
		arg0->unk1A4 = var_f1;
		arg0->unk2E  = (s16)var_f1;
		arg0->unk230 = fn_800AB104(sp8);
		return 1;
	}
	if ((s32)arg0->unk310 == 0) {
		var_r4_2 = arg0;
		if (arg0 != NULL) {
			var_r4_2 = (TObjEffTornadoSpin*)&arg0->unk28;
		}
		if (fn_800A3E10(arg0, var_r4_2) != 0) {
			arg0->unk18C |= 0x2000;
		} else {
			arg0->unk18C &= 0xFFFFDFFF;
		}
	}
	if ((s32)arg0->unk19C != 0x29) {
		var_r3 = arg0;
		if (arg0 != NULL) {
			var_r3 = (TObjEffTornadoSpin*)&arg0->unk28;
		}
		arg0->unk234 = SetPosition__18TObjEffTornadoSpinFv(var_r3);
		if ((s32)arg0->unk234 != -1) {
			arg0->unk18C |= 0x1000;
			return 0;
		}
		arg0->unk18C &= 0xFFFFEFFF;
	}
	arg0->unk2D0 = 0;
	var_r30      = -1;
	if ((s32)(arg0->unk30 & 0x20) != 0) {
		arg0->unk2D0 = 1;
		fn_80021824(&lbl_8042C1A4);
		while ((temp_r3_3   = fn_800211A8(&arg0->unk28),
		           var_r3_2 = (temp_r3_3 != NULL) ? M2C_FIELD(temp_r3_3, void**, 4) : NULL)
		    != NULL) {
			temp_r3_4 = fn_80041B64(M2C_FIELD(var_r3_2, s32*, 0x78));
			if (temp_r3_4 != -1) {
				fn_800A4630(arg0, temp_r3_4);
			}
			temp_r3_5 = temp_r3_4 + 0x191;
			if ((s8) * ((u8*)arg0 + temp_r3_5) <= 0) {
				*((u8*)arg0 + temp_r3_5) = 0x14;
				var_r30                  = temp_r3_4;
			}
		}
		fn_80021824(&lbl_8042C1A4);
		while ((temp_r3_6    = fn_800210C4(&arg0->unk28),
		           var_r29_2 = (temp_r3_6 != NULL) ? M2C_FIELD(temp_r3_6, void**, 4) : NULL)
		    != NULL) {
			var_r3_3 = fn_80041B64(M2C_FIELD(var_r29_2, s32*, 0x78));
			if (var_r3_3 == -1) {
				var_r3_3 = fn_80041AB0(M2C_FIELD(var_r29_2, s32*, 0x78));
			}
			temp_r4 = var_r3_3 + 0x191;
			if ((s8) * ((u8*)arg0 + temp_r4) <= 0) {
				*((u8*)arg0 + temp_r4) = 0x14;
				var_r30                = var_r3_3;
			}
		}
		fn_80021824(&lbl_8042C1A4);
		while ((temp_r3_7    = fn_80020D1C(&arg0->unk28),
		           var_r29_3 = (temp_r3_7 != NULL) ? M2C_FIELD(temp_r3_7, void**, 4) : NULL)
		    != NULL) {
			var_r3_4 = fn_80041B64(M2C_FIELD(var_r29_3, s32*, 0x78));
			if (var_r3_4 == -1) {
				var_r3_4 = fn_80041AB0(M2C_FIELD(var_r29_3, s32*, 0x78));
			}
			temp_r4_2 = var_r3_4 + 0x191;
			if ((s8) * ((u8*)arg0 + temp_r4_2) <= 0) {
				*((u8*)arg0 + temp_r4_2) = 0x14;
				var_r30                  = var_r3_4;
			}
		}
		fn_80021824(&lbl_8042C1A4);
		temp_r3_8 = fn_800211A8(&arg0->unk28);
		if (temp_r3_8 != NULL) {
			var_r0 = M2C_FIELD(temp_r3_8, u32*, 4);
		} else {
			var_r0 = 0U;
		}
		var_r28 = var_r0;
		if (var_r0 == 0U) {
			temp_r3_9 = fn_800210C4(&arg0->unk28);
			if (temp_r3_9 != NULL) {
				var_r0_2 = M2C_FIELD(temp_r3_9, u32*, 4);
			} else {
				var_r0_2 = 0U;
			}
			var_r28 = var_r0_2;
			if (var_r0_2 == 0U) {
				temp_r3_10 = fn_80020D1C(&arg0->unk28);
				if (temp_r3_10 != NULL) {
					var_r0_3 = M2C_FIELD(temp_r3_10, u32*, 4);
				} else {
					var_r0_3 = 0U;
				}
				var_r28 = var_r0_3;
				if (var_r0_3 == 0U) {
					fn_80020EEC(&arg0->unk28);
				}
			}
		}
		temp_r3_11 = arg0->unk188;
		if ((u32)(temp_r3_11 & 0x400000) != 0) {
			var_r29 = 1;
		} else if ((u32)(temp_r3_11 & 0x200000) != 0) {
			var_r29      = 0;
			arg0->unk2D0 = 0;
		} else if ((u32)(temp_r3_11 & 0x40000) != 0) {
			if (fn_800209C8(&arg0->unk28, 1) != 0U) {
				var_r29 = 1;
			} else {
				var_r29 = 0;
			}
		} else {
			if (fn_800209C8(&arg0->unk28, 1) != 0U) {
				var_r0_4 = 1;
			} else if (fn_800207C4(&arg0->unk28, 0, 0xC) != 0U) {
				var_r0_4 = 1;
			} else {
				var_r0_4 = 0;
			}
			var_r29 = var_r0_4;
		}
		if ((u32)(arg0->unk188 & 0x100) == 0) {
			if (var_r28 != 0U) {
				arg0->unk18C |= 0x800;
			}
			if (var_r29 != 0) {
				temp_f31     = arg0->unk1A4;
				arg0->unk1A4 = (f32)arg0->unk2E;
				temp_f30     = arg0->unk1A4;
				if (var_r30 != -1) {
					arg0->unk230 = fn_800AB104(var_r30);
					var_f30      = temp_f31 - temp_f30;
					if (var_f30 < 0.0f) {
						var_f30 = 0.0f;
					}
					team = GetTeamNoFromPlayerNum__13nSearchPlayerFi(arg0->unk230);
					if (team != -1) {
						addSFA__9PARAM_SFAFif(&arg0->unk13C, team, var_f30);
					}
				}
			} else {
				arg0->unk2E = (s16)arg0->unk1A4;
			}
		}
		return var_r29;
	}
	return 0;
}

s32 fn_8_BEDA8(s32 arg0)
{
	return fn_800209C8((s32*)((u8*)arg0 + 0x28), 1) != 0U;
}

s32 fn_8_BED48(s32 arg0)
{
	if (fn_800209C8((s32*)((u8*)arg0 + 0x28), 1) != 0U) {
		return 1;
	}
	return fn_800207C4((s32*)(arg0 + 0x28), 0, 0xC) != 0U;
}

void fn_8_BEBC8(void* arg0)
{
	RwV3d sp14;
	RwV3d sp8;
	u8 sp20[0x48];
	f32 temp_f1;
	f32 temp_f31;
	s32 temp_r0;
	void* temp_r30;

	if ((u32)M2C_FIELD(arg0, u32*, 0x258) != 0U) {
		temp_r0 = M2C_FIELD(arg0, s32*, 0x2D4);
		if (temp_r0 != -1) {
			temp_r30 = (void*)(u32) * (&lbl_802AD090 + temp_r0);
			if (temp_r30 != NULL) {
				M2C_FIELD(&sp14, M2C_BLOCK12*, 0) = M2C_FIELD(lbl_8_rodata_1E5C, M2C_BLOCK12*, 0);
				temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x150) + 0x8000);
				fn_80195790((s32*)sp20, &AxisY,
				    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x150) + 0x8000), temp_f31, 0);
				fn_8019941C(&sp14.x, &sp14.x, 1, (s32*)sp20);
				sp14.y = 0.0f;
				fn_801990E0(&sp14.x, &sp14.x);
				sp8.x   = M2C_FIELD(temp_r30, f32*, 0x18) - M2C_FIELD(arg0, f32*, 0x140);
				sp8.y   = M2C_FIELD(temp_r30, f32*, 0x1C) - M2C_FIELD(arg0, f32*, 0x144);
				temp_f1 = M2C_FIELD(temp_r30, f32*, 0x20);
				sp8.z   = temp_f1 - M2C_FIELD(arg0, f32*, 0x148);
				sp8.y   = 0.0f;
				fn_801990E0(&sp8.x, &sp8.x);
				M2C_FIELD(arg0, s32*, 0x29C) = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x29C),
				    VectorAngle__FP5RwV3dP5RwV3dP5RwV3d(
				        &sp14.x, &sp8.x, (M2C_UNK*)lbl_8_data_17F94),
				    0x200);
			}
		}
	}
}

void fn_8_BEB1C(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x19C) != 0x1F) {
		M2C_FIELD(arg0, s32*, 0x29C) = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x29C), 0, 0x220);
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x258) != NULL) {
		fn_8019ED68(M2C_FIELD(arg0, void**, 0x258), &AxisY,
		    0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x29C), 0);
		fn_8019ECCC(M2C_FIELD(arg0, void**, 0x258), (s32*)((u8*)arg0 + 0x25C), 2);
	}
}

void Explosion__15TObjEnemyTurtleFv(void* arg0)
{
	RwV3d sp20;
	sAngle sp14;
	sAngle sp8;
	u32 clump;

	M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x200);
	if ((M2C_FIELD(arg0, u32*, 0x188) & 0x10) != 0) {
		M2C_FIELD(&sp20, M2C_BLOCK12*, 0) = M2C_FIELD(arg0, M2C_BLOCK12*, 0x140);
		M2C_FIELD(&sp14, M2C_BLOCK12*, 0) = M2C_FIELD(arg0, M2C_BLOCK12*, 0x14C);
		sp20.y += 8.0f;
		if ((M2C_FIELD(arg0, u32*, 0x188) & 0x10) != 0) {
			fn_8006298C(6, &sp20.x, &sp14.x);
			fn_8006298C(2, &sp20.x, &sp14.x);
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0xE017, (s32*)&sp20, 0, 1, 2, 0);
			}
			fn_8006298C(0xF, &sp20.x, &sp14.x);
			if ((u32)mpDataBase__14TEnemyDataBase == 0U) {
				if (__nw__FUl(0x70) != NULL) {
					__ct__14TEnemyDataBaseFv();
				}
			}
			clump = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(
			    mpDataBase__14TEnemyDataBase, 0, 5);
			if (clump != 0U) {
				M2C_FIELD(&sp8, M2C_BLOCK12*, 0) = M2C_FIELD(lbl_8_rodata_1E38, M2C_BLOCK12*, 0);
				sp14.y += 0x8000;
				SetEffectCrash3D_R__FP7TObjectP5RwV3dP6sAngleP5RwV3dP5RwV3dffisP7RpClump(
				    lbl_8042C2A0, &sp20.x, &sp14.x, &sp8.x, NULL, 1.2f, 0.0f, 0, 0, clump);
			}
		}
	}
}

void AddScore__15TObjEnemyTurtleFv(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
			CreateInstance__14TEnemyScoreManFv();
		}
		AddScore__14TEnemyScoreManFii(
		    EnemyScoreMan__14TEnemyScoreMan, M2C_FIELD(arg0, s32*, 0x230), 0xC8);
		return;
	}
	if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
		CreateInstance__14TEnemyScoreManFv();
	}
	AddScore__14TEnemyScoreManFii(
	    EnemyScoreMan__14TEnemyScoreMan, M2C_FIELD(arg0, s32*, 0x230), 0x190);
	if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
		CreateInstance__14TEnemyScoreManFv();
	}
	fn_8011C13C(EnemyScoreMan__14TEnemyScoreMan);
}

void RcvCommand__15TObjEnemyTurtleFP13sEnemyCommand(void* arg0, void* arg1)
{
	u32 temp_handle;
	f32 var_f0;
	f32 temp_f1;

	switch ((s32)M2C_FIELD(arg1, u8*, 0)) {
		case 3:
			break;
		default:
			return;
	}
	var_f0  = M2C_FIELD(arg1, f32*, 0x14) + M2C_FIELD(arg0, f32*, 0x1A4);
	temp_f1 = M2C_FIELD(arg0, f32*, 0x2B8);
	if (var_f0 > temp_f1) {
		var_f0 = temp_f1;
	}
	M2C_FIELD(arg0, f32*, 0x1A4) = var_f0;
	M2C_FIELD(arg0, s16*, 0x2E)  = (s16)var_f0;
	M2C_FIELD(arg0, f32*, 0x2B4) = (f32)M2C_FIELD(arg0, f32*, 0x1A4);
	if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
		Off__13TEnemyIconManFv(M2C_FIELD(arg0, u32*, 0x2C0));
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
		Change__13TEnemyIconManF10eEnemyIcon(M2C_FIELD(arg0, u32*, 0x2BC), 6);
		temp_handle = M2C_FIELD(arg0, u32*, 0x2BC);
		On__13TEnemyIconManFff(temp_handle, 0.0f, 0.0f);
	}
}

void fn_8_BE770(void* arg0, void* arg1)
{
	u32 temp_r3;
	f32 temp_f0;
	f32 var_f1;

	var_f1  = M2C_FIELD(arg1, f32*, 0x14) + M2C_FIELD(arg0, f32*, 0x1A4);
	temp_f0 = M2C_FIELD(arg0, f32*, 0x2B8);
	if (var_f1 > temp_f0) {
		var_f1 = temp_f0;
	}
	M2C_FIELD(arg0, f32*, 0x1A4) = var_f1;
	M2C_FIELD(arg0, s16*, 0x2E)  = (s16)var_f1;
	M2C_FIELD(arg0, f32*, 0x2B4) = (f32)M2C_FIELD(arg0, f32*, 0x1A4);
	if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
		Off__13TEnemyIconManFv(M2C_FIELD(arg0, u32*, 0x2C0));
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
		Change__13TEnemyIconManF10eEnemyIcon(M2C_FIELD(arg0, u32*, 0x2BC), 6);
		temp_r3 = M2C_FIELD(arg0, u32*, 0x2BC);
		On__13TEnemyIconManFff(temp_r3, 0.0f, 0.0f);
	}
}

void fn_8_BE668(TEnemyWork* arg0)
{
	f32 temp_f31;
	s32 temp_r3;

	temp_r3 = arg0->unkD0;
	if (temp_r3 != (s32)arg0->unk2E4) {
		arg0->unk2E0 = 0;
		arg0->unk2E4 = temp_r3;
	}
	temp_f31 = arg0->unkB8;
	switch (temp_r3) {
		case 2:
			break;
		default:
			return;
	}
	if ((temp_f31 > 0.5f) && ((s32)arg0->unk2E0 == 0)) {
		arg0->unk2E0 = 1;
		fn_80139784(lbl_8_bss_1B9C, arg0, (f32*)((u8*)(u8*)arg0 + 0x140));
	}
	if ((temp_f31 > 6.0f) && ((s32)arg0->unk2E0 == 1)) {
		arg0->unk2E0 = 2;
		fn_80139784(lbl_8_bss_1B9C, arg0, &arg0->unk140);
	}
	if (((s32)arg0->unk2E0 != 0) && ((u32)(arg0->unkC8 & 2) != 0)) {
		arg0->unk2E0 = 0;
	}
}

void AddItemBox__15TObjEnemyTurtleFP5RwV3d(void* arg0, s32 arg1)
{
	CreateItemBox__8nItemBoxFP5RwV3d(arg1);
}
}
