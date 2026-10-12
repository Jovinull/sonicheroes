#include "types.h"
// This unit was built without the constant pool (-pool off, as every other
// Stage 11 object unit); its configure flags lack it, so say it here.
#pragma pool_data off

// e_magician.cpp: TObjEnemyMagicianRing (the ring-stealing spell), the
// magician's strategy/mode handlers and TObjEnemyMagician itself. Function
// order follows the PS2 build's e_magician.cpp. The TObjEnemyMagician vtable,
// its TObjSetObj adjustor thunk and the object-table static initializer are
// compiler-generated from the class declarations below.

typedef s32 M2C_UNK;
typedef void RwFrame;
typedef s32 RwOpCombineType;
typedef void HAnimClass;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

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

struct HAnimNodeInfo {
	s32 nodeID;
	s32 nodeIndex;
	s32 flags;
	void* pFrame;
};

struct HAnimHierarchy {
	u8 pad00[0x10];
	HAnimNodeInfo* pNodeInfo;
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

typedef struct TEnemyParalysis {
	/* 0x000 */ s32 unk0;        /* inferred */
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
	/* 0x13C */ s32 unk13C; /* inferred */
	/* 0x140 */ RwV3d pos;
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
	/* 0x228 */ u32 unk228;              /* inferred */
	/* 0x22C */ char pad22C[0x14];       /* maybe part of unk228[6]? */
	/* 0x240 */ s32 unk240;              /* inferred */
	/* 0x244 */ void* unk244;            /* inferred */
	/* 0x248 */ u32 unk248;              /* inferred */
	/* 0x24C */ TEnemyParalysis* unk24C; /* inferred */
	/* 0x250 */ s32 unk250;              /* inferred */
	/* 0x254 */ f32 unk254;              /* inferred */
	/* 0x258 */ f32 unk258;              /* inferred */
	/* 0x25C */ f32 unk25C;              /* inferred */
	/* 0x260 */ f32 unk260;              /* inferred */
	/* 0x264 */ f32 unk264;              /* inferred */
	/* 0x268 */ f32 unk268;              /* inferred */
	/* 0x26C */ f32 unk26C;              /* inferred */
	/* 0x270 */ f32 unk270;              /* inferred */
	/* 0x274 */ s32 unk274;              /* inferred */
	/* 0x278 */ s32 unk278;              /* inferred */
	/* 0x27C */ s32 unk27C;              /* inferred */
	/* 0x280 */ f32 unk280;              /* inferred */
	/* 0x284 */ f32 unk284;              /* inferred */
	/* 0x288 */ f32 unk288;              /* inferred */
	/* 0x28C */ f32 unk28C;              /* inferred */
	/* 0x290 */ f32 unk290;              /* inferred */
	/* 0x294 */ f32 unk294;              /* inferred */
	/* 0x298 */ f32 unk298;              /* inferred */
	/* 0x29C */ f32 unk29C;              /* inferred */
	/* 0x2A0 */ f32 unk2A0;              /* inferred */
	/* 0x2A4 */ f32 unk2A4;              /* inferred */
	/* 0x2A8 */ f32 unk2A8;              /* inferred */
	/* 0x2AC */ f32 unk2AC;              /* inferred */
	/* 0x2B0 */ char pad2B0[4];
	/* 0x2B4 */ f32 unk2B4;        /* inferred */
	/* 0x2B8 */ f32 unk2B8;        /* inferred */
	/* 0x2BC */ f32 unk2BC;        /* inferred */
	/* 0x2C0 */ f32 unk2C0;        /* inferred */
	/* 0x2C4 */ char pad2C4[0xC];  /* maybe part of unk2C0[4]? */
	/* 0x2D0 */ s32 unk2D0;        /* inferred */
	/* 0x2D4 */ s32 unk2D4;        /* inferred */
	/* 0x2D8 */ s32 unk2D8;        /* inferred */
	/* 0x2DC */ u32 unk2DC;        /* inferred */
	/* 0x2E0 */ u32 unk2E0;        /* inferred */
	/* 0x2E4 */ char pad2E4[0x14]; /* maybe part of unk2E0[6]? */
	/* 0x2F8 */ s32 unk2F8;        /* inferred */
	/* 0x2FC */ void* unk2FC;      /* inferred */
	/* 0x300 */ f32 unk300;        /* inferred */
	/* 0x304 */ f32 unk304;        /* inferred */
	/* 0x308 */ f32 unk308;        /* inferred */
	/* 0x30C */ char pad30C[4];
	/* 0x310 */ s32 unk310;        /* inferred */
	/* 0x314 */ s32 unk314;        /* inferred */
	/* 0x318 */ s32 unk318;        /* inferred */
	/* 0x31C */ s32 unk31C;        /* inferred */
	/* 0x320 */ void* unk320;      /* inferred */
	/* 0x324 */ s32 unk324;        /* inferred */
	/* 0x328 */ s32 unk328;        /* inferred */
	/* 0x32C */ char pad32C[0x24]; /* maybe part of unk328[0xA]? */
	/* 0x350 */ s32 unk350;        /* inferred */
	/* 0x354 */ s32 unk354;        /* inferred */
	/* 0x358 */ f32 unk358;        /* inferred */
} TEnemyParalysis;                 /* size >= 0x35C */

/* Dispatch view of the object's vtable. The handler at vtable offset 0x10 is
 * reached through genuine virtual dispatch in retail: the target loads the
 * vtable through the already-materialised `this` in r3 and keeps the slot in
 * r12, which manual vtable indexing does not reproduce. Two implicit
 * destructor slots plus the two placeholders below put Release at slot 4. */
/* The magician's editor fields. */
struct MagicianParams {
	s8 type;
	s8 unused[3];
	f32 field04;
	f32 field08;
	u8 pad0C[4];
	s32 field10;
	f32 field14;
};

struct SETDATA_PARAM {
	u8 pad00[0x2C];
	MagicianParams* params;
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

/* A player character: its position at +0x18. */
struct PlayerObj {
	u8 pad00[0x18];
	RwV3d pos;
};

/* An enemy-to-enemy command; this one asks summoned enemies to appear. */
struct sEnemyCommand {
	u8 type;
	u8 id;
	RwV3d pos;
	f32 value;

	sEnemyCommand()
	{
		type  = 0;
		id    = 0;
		pos.x = pos.y = pos.z = 0.0f;
		value                 = 0.0f;
	}
};

struct sEnemyCommandEx : sEnemyCommand {
	f32 range;

	sEnemyCommandEx(u8 t)
	{
		type  = t;
		range = 0.0f;
	}
	void Send();
};

/* A player character's game-side record: its ring counter index. */
struct PlayerCharacter {
	u8 pad000[0x9BC];
	s8 ringIndex;
};

class PARAM_RING
{
public:
	void setRingNum(int, int);
};

struct RwRGBAReal {
	f32 red;
	f32 green;
	f32 blue;
	f32 alpha;
};

/* A player character: its position at +0x18. */

typedef struct MagStrat {
	/* 0x000 */ s32 unk0;        /* inferred */
	/* 0x004 */ char pad4[0x14]; /* maybe part of unk0[6]? */
	/* 0x018 */ M2C_UNK* unk18;  /* inferred */
	/* 0x01C */ char pad1C[2];
	/* 0x01E */ s16 unk1E;        /* inferred */
	/* 0x020 */ char pad20[8];    /* maybe part of unk1E[5]? */
	/* 0x028 */ f32 unk28;        /* inferred */
	/* 0x02C */ f32 unk2C;        /* inferred */
	/* 0x030 */ f32 unk30;        /* inferred */
	/* 0x034 */ f32 unk34;        /* inferred */
	/* 0x038 */ f32 unk38;        /* inferred */
	/* 0x03C */ f32 unk3C;        /* inferred */
	/* 0x040 */ f32 unk40;        /* inferred */
	/* 0x044 */ f32 unk44;        /* inferred */
	/* 0x048 */ f32 unk48;        /* inferred */
	/* 0x04C */ void* unk4C;      /* inferred */
	/* 0x050 */ f32 unk50;        /* inferred */
	/* 0x054 */ f32 unk54;        /* inferred */
	/* 0x058 */ f32 unk58;        /* inferred */
	/* 0x05C */ f32 unk5C;        /* inferred */
	/* 0x060 */ f32 unk60;        /* inferred */
	/* 0x064 */ s32 unk64;        /* inferred */
	/* 0x068 */ char pad68[0x68]; /* maybe part of unk64[0x1B]? */
	/* 0x0D0 */ s32 unkD0;        /* inferred */
	/* 0x0D4 */ s32 unkD4;        /* inferred */
	/* 0x0D8 */ char padD8[0x68]; /* maybe part of unkD4[0x1B]? */
	/* 0x140 */ M2C_UNK unk140;   /* inferred */
	/* 0x144 */ char pad144[0xFC];
	/* 0x240 */ M2C_UNK unk240; /* inferred */
	/* 0x244 */ char pad244[0x30];
	/* 0x274 */ s32 unk274;        /* inferred */
	/* 0x278 */ char pad278[0x4C]; /* maybe part of unk274[0x14]? */
	/* 0x2C4 */ M2C_UNK unk2C4;    /* inferred */
	/* 0x2C8 */ f32 unk2C8;        /* inferred */
	/* 0x2CC */ char pad2CC[4];
	/* 0x2D0 */ s32 unk2D0; /* inferred */
	/* 0x2D4 */ s32 unk2D4; /* inferred */
	/* 0x2D8 */ s32 unk2D8; /* inferred */
	/* 0x2DC */ u32 unk2DC; /* inferred */
	/* 0x2E0 */ char pad2E0[4];
	/* 0x2E4 */ s32 unk2E4;        /* inferred */
	/* 0x2E8 */ char pad2E8[0x10]; /* maybe part of unk2E4[5]? */
	/* 0x2F8 */ s32 unk2F8;        /* inferred */
	/* 0x2FC */ char pad2FC[4];
	/* 0x300 */ f32 unk300;        /* inferred */
	/* 0x304 */ f32 unk304;        /* inferred */
	/* 0x308 */ f32 unk308;        /* inferred */
	/* 0x30C */ s32 unk30C;        /* inferred */
	/* 0x310 */ s32 unk310;        /* inferred */
	/* 0x314 */ char pad314[0x18]; /* maybe part of unk310[7]? */
	/* 0x32C */ f32 unk32C;        /* inferred */
	/* 0x330 */ f32 unk330;        /* inferred */
	/* 0x334 */ f32 unk334;        /* inferred */
	/* 0x338 */ f32 unk338;        /* inferred */
	/* 0x33C */ f32 unk33C;        /* inferred */
	/* 0x340 */ f32 unk340;        /* inferred */
	/* 0x344 */ f32 unk344;        /* inferred */
	/* 0x348 */ f32 unk348;        /* inferred */
	/* 0x34C */ f32 unk34C;        /* inferred */
} MagStrat;                        /* size >= 0x350 */

/* The renderer class keeps its vtable pointer at object offset 0x18, which is
 * what a polymorphic class derived from a 0x18-byte non-polymorphic base
 * looks like: the base's data is laid out first and `this` is not adjusted,
 * exactly as retail's `lwz r12, 0x18(r3)` reads it. Slot numbers are the
 * retail vtable offsets divided by four, and the two implicit deleting
 * destructor slots occupy 0 and 1, so a method at slot k needs k - 2
 * placeholders ahead of it. */

enum eEnemyIcon { ENEMY_ICON_0 };

/* The icon floating over an enemy. */
class TEnemyIconMan
{
public:
	s32 IsOn();
	void Change(eEnemyIcon);
	s32 Off();
	s32 On(f32, f32, s32);
	void On(f32, f32);
	s32 SetPos(const RwV3d*, const RwV3d*);
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

/* The object's class shape, recovered from the retail vtable and the PS2
 * build's symbols (e_magician.cpp). Only the virtual interface is modelled:
 * the compiler generates the vtable and the TObjSetObj adjustor thunk from
 * these declarations. The method bodies below are written against the
 * object's storage and carry the mangled names the vtable refers to. */
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

class TObjEnemyMagician : public TObjEnemy
{
public:
	inline virtual ~TObjEnemyMagician();
	inline virtual void CtrlMode(ENEMY_MD, TObjEnemy::eCtrlSMode);
	inline virtual void Update();
	inline virtual void UpdateOnEdit();
	inline virtual void DispOpaq();
	inline virtual void DispTrans();
	inline virtual void DispShadow();
	inline virtual void AddScore();
	inline virtual void AddItemBox(RwV3d*);
	inline virtual void RcvCommand(sEnemyCommand*);
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" {

M2C_UNK SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(
    void*, const RwV3d*, const void*);                                            /* extern */
M2C_UNK Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(void*, void*, s32); /* extern */
void* __ct__10HAnimClassFv(void*);                                                /* extern */
TEnemyParalysis* __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(
    void*, void*, void*);                                                               /* extern */
void* __dt__10HAnimClassFv(void*, s32);                                                 /* extern */
M2C_UNK Free__9THeapCtrlFPv(s32, void*);                                                /* extern */
TEnemyParalysis* Malloc__9THeapCtrlFUi(s32, u32);                                       /* extern */
M2C_UNK Init__7C_COLLIFP8CCL_INFOiUc(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);             /* extern */
void* __nw__FUl(u32);                                                                   /* extern */
s32 OnEdit__10TObjSetObjFv(void*);                                                      /* extern */
M2C_UNK SetClumpCustomFXTexture__FP7RpClumpP8UVFXInfo(u32, unsigned int[17]);           /* extern */
M2C_UNK objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(void*, s32); /* extern */
s32 objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(
    HAnimHierarchy*, s32);                                                   /* extern */
M2C_UNK objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(void*); /* extern */
M2C_UNK objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(
    u32, M2C_UNK);                           /* extern */
s32 objPointerReadFromClumpAnim__FPc(void*); /* extern */
M2C_UNK fn_8005FD8C(void*, M2C_UNK);         /* extern */
void* fn_8006298C(s32, void*, void*);
M2C_UNK fn_800A31B8(void*, s32);                                              /* extern */
M2C_UNK fn_800A4668(void*);                                                   /* extern */
M2C_UNK fn_800A4A8C(void*, f32);                                              /* extern */
s32 fn_800A5888(void*, f32);                                                  /* extern */
s32 fn_800A5A54(void*);                                                       /* extern */
f32 fn_800A5AC0(void*);                                                       /* extern */
M2C_UNK fn_800A5B50(void*, s32);                                              /* extern */
M2C_UNK fn_800A5C6C(void*, s32);                                              /* extern */
M2C_UNK fn_800A7088(void*, M2C_UNK);                                          /* extern */
M2C_UNK fn_800A714C(TEnemyParalysis*, void*);                                 /* extern */
s32 AdjustAngle__Fiii(s32, s32, s32);                                         /* extern */
f32 fn_800D7B00(s32);                                                         /* extern */
f32 GetShadowPos__FP5RwV3dP6sAnglei(void*, void*, s32);                       /* extern */
M2C_UNK fn_800E1208(s32, s32, s32);                                           /* extern */
void* __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID(void*, TEnemyParalysis*, s32); /* extern */
M2C_UNK ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    s32, void*); /* extern */
M2C_UNK LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    s32, void*);                                                            /* extern */
u32 SearchUVAnim__14TEnemyDataBaseF14eEnemyDataBaseUi(s32, s32, s32);       /* extern */
u32 SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(s32, s32, s32); /* extern */
u32 SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(s32, s32, s32);        /* extern */
M2C_UNK Delete__14TEnemyDataBaseF14eEnemyDataBase(s32, s32);                /* extern */
M2C_UNK Add__14TEnemyDataBaseF14eEnemyDataBasePc(s32, s32, void*);          /* extern */
M2C_UNK __ct__14TEnemyDataBaseFv(void);                                     /* extern */
s32 GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(void*, f32);             /* extern */
M2C_UNK Close__13TEnemyIconManFv(void*);                                    /* extern */
s32 Create__13TEnemyIconManF10eEnemyIcon(s32);                              /* extern */
void* fn_80150588(void*);
M2C_UNK fn_80150958(void*);                                      /* extern */
M2C_UNK fn_80195A74(RwMatrix*, const void*, f32, s32);           /* extern */
M2C_UNK fn_80196050(RwMatrix*, const RwV3d*, s32);               /* extern */
void fn_801990E0(RwV3d* dst, const RwV3d* src);                  /* extern */
M2C_UNK fn_8019941C(RwV3d*, const RwV3d*, s32, const RwMatrix*); /* extern */
RwMatrix* fn_8019E8EC(void*);                                    /* extern */
M2C_UNK fn_8019EB94(void*, u8*, s32);                            /* extern */
M2C_UNK fn_8019EC30(void*, u8*, s32);                            /* extern */
M2C_UNK fn_8019ED68(void*, const void*, f32, s32);
s32 rand();
M2C_UNK fn_8_B0300(void*, TEnemyParalysis*); /* extern */
void* fn_8_B08F0(void*);                     /* extern */
void fn_8_AE604(TEnemyParalysis* arg0);      /* static */
void fn_8_AEB80(TEnemyParalysis* arg0);      /* static */
void fn_8_AEE04(TEnemyParalysis* arg0);      /* static */
TEnemyParalysis* fn_8_AF05C(TEnemyParalysis* arg0, s16 arg1, void* arg2);
void magicianObjectCreate(); /* static */
void magicianObjectLoad();   /* static */
void magicianObjectUnload(); /* static */
extern M2C_UNK AxisX;
extern M2C_UNK AxisY;
extern M2C_UNK AxisZ;
extern PlayerObj* lbl_802AD090[];
extern void* lbl_8042C10C;
extern s32 lbl_8042C148;
extern u32 mpDataBase__14TEnemyDataBase;
void* __ct__7TObjectFP7TObject(void*, void*); /* extern */
s32 fn_80017800(void*);                       /* extern */
M2C_UNK Entry__7C_COLLIFv(void*);             /* extern */
M2C_UNK objRpClumpForAllMaterialsToChangeMaterialColor__FP7RpClumpP10RwRGBAReal(
    s32, RwRGBAReal*);                                                                 /* extern */
M2C_UNK fn_8005FD20(void*);                                                            /* extern */
s32 fn_800A34D0(void*, RwV3d*);                                                        /* extern */
s32 fn_800A3D48(void*);                                                                /* extern */
s32 fn_800A5B34(void*);                                                                /* extern */
s32 fn_800A6334(void*);                                                                /* extern */
s32 fn_800AB104(s32);                                                                  /* extern */
M2C_UNK fn_800B4A38(u32, s32, void*, s32, s32, s32, s32);                              /* extern */
s32 fn_800B7514(void*, void*, RwV3d*, f32);                                            /* extern */
s32 fn_800B7820(void);                                                                 /* extern */
s32 fn_800B7864(s32);                                                                  /* extern */
f32 Distance2P2P__FPC5RwV3dPC5RwV3d(const RwV3d*, const RwV3d*);                       /* extern */
f32 AdjustFloat__Ffff(f32, f32, f32);                                                  /* extern */
s32 IsExistSummonEnemy__19nEnemyCommunicationFUc(s32);                                 /* extern */
M2C_UNK GetNearestLeaderPosition__13nSearchPlayerFPC5RwV3dP5RwV3df(void*, void*, f32); /* extern */
M2C_UNK SetLightNum__7nRenderFUi(s32);                                                 /* extern */
M2C_UNK SetRenderStateForBlendAdd__7nRenderFv();                                       /* extern */
M2C_UNK LoadRenderState__7nRenderFv();                                                 /* extern */
M2C_UNK SaveRenderState__7nRenderFv();                                                 /* extern */
M2C_UNK fn_8011B844(s32, f32);                                                         /* extern */
s32 ParalyzeEnemy__14TEnemyScoreManFi(s32, s32);                                       /* extern */
M2C_UNK CreateInstance__14TEnemyScoreManFv();                                          /* extern */
s32 Create__12TEnemySummonFUc(s32);                                                    /* extern */
s32 DecreaseTimer__7nSystemFRi(void*);                                                 /* extern */
M2C_UNK fn_8014FF2C(void*);
M2C_UNK fn_8014FFBC(s32, void*, void*);
s32 fn_8_90B10(s32);                          /* extern */
M2C_UNK fn_8_A504(s32, void*, s32, f32, f32); /* extern */
void* __dt__17TObjEnemyMagicianFv(void*, s16);
void CtrlMode__17TObjEnemyMagicianF8ENEMY_MDQ29TObjEnemy10eCtrlSMode(void*, s32, s32);
void AddScore__17TObjEnemyMagicianFv(void);
void AddItemBox__17TObjEnemyMagicianFP5RwV3d(void*, s32);
void RcvCommand__17TObjEnemyMagicianFP13sEnemyCommand(void*, void*);
void DispShadow__17TObjEnemyMagicianFv(void*);
void DispTrans__17TObjEnemyMagicianFv(void*);
void DispOpaq__17TObjEnemyMagicianFv(void*);
void UpdateOnEdit__17TObjEnemyMagicianFv(void*);
void Update__17TObjEnemyMagicianFv(void*);
extern M2C_UNK SetAtomicCustomFXData__FP8RpAtomicPv;
extern PlayerCharacter* lbl_802AD070[];
extern s32 num__10PARAM_RING[];
extern void* lbl_8042C180;
extern u32 lbl_8042C388;
extern u32 EnemyScoreMan__14TEnemyScoreMan;
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

/* The two clumps, the UV animation and its FX record, and the frame the
 * UV animation last advanced on. */
u32 lbl_8_bss_19C8[2];
u32 lbl_8_bss_19D0;
u32 lbl_8_bss_19D4[0x11];
s32 lbl_8_bss_1A18;
/* The object table entry; built by the unit's static initializer. */
extern char* magicianObjectFieldNames[9];

struct MagicianObjectEntry : ObjectEntry {
	MagicianObjectEntry()
	{
		flags      = 0;
		unk18      = 0;
		name       = "MAGICIAN OBJECT";
		load       = (void (*)(void))magicianObjectLoad;
		unload     = (void (*)(void))magicianObjectUnload;
		create     = (void (*)(void))magicianObjectCreate;
		unk10      = (void*)0;
		flags      = 0x20000;
		unk18      = 0;
		unk20      = 0x1E;
		unk1C      = 0x15C0;
		unk1E      = 4;
		unk21      = 0;
		fieldTypes = "ccccfffif";
		fieldNames = (const char**)magicianObjectFieldNames;
		if (fieldTypes != NULL) {
			flags |= 8;
		} else {
			flags &= ~8;
		}
	}
};

MagicianObjectEntry magicianObjectEntry;
extern void* __vt__17TObjEnemyMagician[];
/* The ring spell's clump. */
void* lbl_8_bss_1A48;

/* The unreferenced { 0, 1.5, 0 } vector every Stage 11 object unit carries at
 * the head of its .rodata (an internal-linkage const from a shared header). */
#pragma force_active on
static const RwV3d lbl_8_rodata_1A20 = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

const RwV3d lbl_8_rodata_1A2C      = { 13.0f, 20.0f, 0.0f };
const RwRGBAReal lbl_8_rodata_1A38 = { 0.2f, 0.4f, 0.4f, 0.4f };
const sAngle lbl_8_rodata_1A48     = { 0, 0, 0 };
const sAngle lbl_8_rodata_1A54     = { 0, 0, 0 };
const RwV3d lbl_8_rodata_1A60      = { 0.0f, 8.0f, 0.0f };
const RwV3d lbl_8_rodata_1A6C      = { 0.0f, 8.0f, 0.0f };
const RwV3d lbl_8_rodata_1A78      = { 0.0f, 0.0f, 0.0f };
const RwRGBAReal lbl_8_rodata_1A84 = { 1.0f, 1.0f, 1.0f, 1.0f };
const RwV3d lbl_8_rodata_1A94      = { 20.0f, 1.0f, 20.0f };
const RwV3d lbl_8_rodata_1AA0      = { 0.2f, 0.2f, 0.2f };

char lbl_8_data_16550[] = "en_magician_a_fly.anm";
char lbl_8_data_16568[] = "en_magician_a_spl_a.anm";
char lbl_8_data_16580[] = "en_magician_a_spl_b.anm";
char lbl_8_data_16598[] = "en_magician_ab_flip.anm";
char lbl_8_data_165B0[] = "en_magician_b_dash.anm";
char lbl_8_data_165C8[] = "en_magician_b_fly.anm";
char lbl_8_data_165E0[] = "en_magician_b_gaway.anm";
char lbl_8_data_165F8[] = "en_magician_b_spla.anm";
char lbl_8_data_16610[] = "en_magician_b_splb.anm";

/* The motion table. */
EnemyMotion lbl_8_data_16628[13] = {
	{ NULL, 3, 0, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_16550, 7 },
	{ NULL, 4, 0, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_16568, 8 },
	{ NULL, 4, 0, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_16580, 9 },
	{ NULL, 4, 6, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_16598, 6 },
	{ NULL, 6, 0, -1.0f, 0.0f, 0.0625f, 1.0f, lbl_8_data_16598, 6 },
	{ NULL, 4, 6, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_165B0, 10 },
	{ NULL, 3, 6, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_165C8, 11 },
	{ NULL, 4, 6, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_165E0, 12 },
	{ NULL, 4, 9, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_165F8, 13 },
	{ NULL, 3, 6, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_16610, 14 },
	{ NULL, 11, 0, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_16550, 7 },
	{ NULL, 11, 6, 0.0f, -1.0f, 0.0625f, 1.0f, lbl_8_data_165C8, 11 },
	{ NULL, 14, 0, 0.0f, 0.0f, 0.0f, 0.0f, NULL, 0 },
};

/* The magician's collision setup. */
u32 lbl_8_data_167FC[12] = { 0x0000FF21, 0x00000400, 0x00000000, 0x00000000, 0x00000000, 0x41700000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

char lbl_8_data_1682C[] = "CAPTURE TYPE";
char lbl_8_data_1683C[] = "Not in use";
char lbl_8_data_16848[] = "MOVE RANGE";
char lbl_8_data_16854[] = "SCOPE RANGE";
char lbl_8_data_16860[] = "SCOPE OFFSET";
char lbl_8_data_16870[] = "ATTACK INTERVAL";
char lbl_8_data_16880[] = "MOVE SPEED";

char* magicianObjectFieldNames[9] = {
	lbl_8_data_1682C,
	lbl_8_data_1683C,
	lbl_8_data_1683C,
	lbl_8_data_1683C,
	lbl_8_data_16848,
	lbl_8_data_16854,
	lbl_8_data_16860,
	lbl_8_data_16870,
	lbl_8_data_16880,
};

char lbl_8_data_168B0[]   = "NORMAL";
char lbl_8_data_168B8[]   = "SPECIAL";
char* lbl_8_data_168C0[2] = { lbl_8_data_168B0, lbl_8_data_168B8 };

#pragma explicit_zero_data on
s8 lbl_8_data_168C8 = 0;
#pragma explicit_zero_data reset
s8 lbl_8_data_168C9 = 1;

char lbl_8_data_168CC[] = "TObjEnemyMagician";
char* lbl_8_data_168E0  = lbl_8_data_168CC;
char lbl_8_data_168E4[] = "TObjEnemyMagicianRing";
char* lbl_8_data_168FC  = lbl_8_data_168E4;

void TDisp__7TObjectFv();
void PDisp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Error__7TObjectFPc();
void Render__7TObjectFv();
void* __dt__7TObjectFv(void*, s32);
s32 fn_8019CE34(s32, void*);
extern s32* lbl_8042C9A4;
M2C_UNK AdjustPoint__FP5RwV3dPC5RwV3df(RwV3d*, const RwV3d*, f32);
struct RingSpell;
struct RingSpellParam;
RingSpell* fn_8_AAA24(RingSpell* self, MagStrat* parent, RingSpellParam* param);

/* The ring spell's flight: from the staff to the target, and its scale. */
struct RingSpellParam {
	RwV3d to;
	RwV3d from;
	RwV3d scale;
};

/* The spell object, built in place by the attack. */
struct RingSpell {
	u8 hdr[0x18];
	void** vtable;
	u8 pad1C[2];
	s16 objectSize;
	u8 pad20[8];
	RingSpellParam param; /* 0x28 */
	void* clump;          /* 0x4C */
	f32 progress;         /* 0x50 */
	RwV3d pos;            /* 0x54 */
	f32 angle;            /* 0x60 */
	s32 timer;            /* 0x64 */
};

struct ObjectStorage {
	~ObjectStorage();
};

struct RingSpellStorage : ObjectStorage {
	u8 data[0x68];

	RingSpellStorage(MagStrat* parent, RingSpellParam* param)
	{
		fn_8_AAA24((RingSpell*)this, parent, param);
	}
	static void* operator new(unsigned long size, s32 heap)
	{
		return Malloc__9THeapCtrlFUi(heap, size);
	}
};

RingSpell* fn_8_AA994(RingSpell* self, s16 flags);
void fn_8_AA69C(RingSpell* self);
void fn_8_AA610(RingSpell* self);

/* TObjEnemyMagicianRing's vtable. */
void* lbl_8_data_16900[11] = {
	0,
	0,
	(void*)fn_8_AA994,
	(void*)fn_8_AA69C,
	(void*)fn_8_AA610,
	(void*)TDisp__7TObjectFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
};

char lbl_8_data_1692C[] = "OBJ_RING.DFF";

/* TObjEnemyMagicianRing: Disp. */
void fn_8_AA610(RingSpell* self)
{
	struct {
		RwV3d center;
		f32 radius;
	} sphere;

	if (self->clump != NULL) {
		sphere.center = self->pos;
		sphere.radius = 5.0f;
		if (fn_8019CE34(*lbl_8042C9A4, &sphere) != 0) {
			SetLightNum__7nRenderFUi(4);
			fn_8014FF2C(self->clump);
		}
	}
}

/* Push scale, spin and position into the ring's frame. Exec inlines this
 * although its out-of-line body (fn_8_AA898) only follows Exec. */
static inline void RingSpellSetFrame(RingSpell* self)
{
	void* frame;

	if (self->clump != NULL) {
		frame = *(void**)((u8*)self->clump + 4);
		fn_8019EC30(frame, (u8*)&self->param.scale, 0);
		fn_8019ED68(frame, &AxisY, self->angle, 2);
		fn_8019EB94(frame, (u8*)&self->pos, 2);
	}
}

/* Exec: shrink in, spin, and arc from the staff to the target; vanish on
 * arrival. */
void fn_8_AA69C(RingSpell* self)
{
	f32 arc;

	AdjustPoint__FP5RwV3dPC5RwV3df(&self->param.scale, &lbl_8_rodata_1AA0, 0.035f);
	self->progress += 0.03f;
	self->angle += 10.0f;
	if (self->progress > 1.0f) {
		*(u16*)((u8*)self + 4) |= 1;
		if (lbl_8042C388 != 0U) {
			fn_800B4A38(lbl_8042C388, 0x1004, &self->pos, 0, 1, 0, 0);
		}
		return;
	}
	self->timer += 0x200;
	arc      = 15.0f * (2.0f * fn_800D7B00(self->timer)) - 15.0f;
	RwV3d to = self->param.to;
	to.y += arc;
	self->pos.x = self->param.from.x - to.x;
	self->pos.y = self->param.from.y - to.y;
	self->pos.z = self->param.from.z - to.z;
	self->pos.x *= self->progress;
	self->pos.y *= self->progress;
	self->pos.z *= self->progress;
	self->pos.x += to.x;
	self->pos.y += to.y;
	self->pos.z += to.z;
	RingSpellSetFrame(self);
}

/* SetPosition. */
void fn_8_AA898(RingSpell* self)
{
	RingSpellSetFrame(self);
}

/* DestroyClump. */
void fn_8_AA910(RingSpell* self)
{
	if (self->clump != NULL) {
		fn_80150958(self->clump);
		self->clump = NULL;
	}
}

/* CloneClump. */
void fn_8_AA950(RingSpell* self)
{
	if (lbl_8_bss_1A48 != NULL) {
		self->clump = fn_80150588(lbl_8_bss_1A48);
	}
}

/* The destructor. */
RingSpell* fn_8_AA994(RingSpell* self, s16 flags)
{
	if (self != NULL) {
		self->vtable = lbl_8_data_16900;
		fn_8_AA910(self);
		__dt__7TObjectFv(self, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, self);
		}
	}
	return self;
}

/* The constructor. */
RingSpell* fn_8_AAA24(RingSpell* self, MagStrat* parent, RingSpellParam* param)
{
	__ct__7TObjectFP7TObject(self, parent);
	self->vtable        = lbl_8_data_16900;
	*(char**)self       = lbl_8_data_168FC;
	self->objectSize    = 0x68;
	self->param         = *param;
	self->param.scale.x = self->param.scale.y = self->param.scale.z = 1.0f;
	self->progress                                                  = 0.0f;
	self->timer                                                     = 0;
	self->pos                                                       = self->param.to;
	self->angle                                                     = 0.0f;
	self->clump                                                     = NULL;
	fn_8_AA950(self);
	fn_8_AA898(self);
	return self;
}

/* Finalize. */
void fn_8_AAB80(void)
{
	lbl_8_bss_1A48 = NULL;
}

/* Initialize. */
void fn_8_AAB94(void)
{
	lbl_8_bss_1A48 = (void*)objPointerReadFromClumpAnim__FPc(lbl_8_data_1692C);
}

s32 fn_8_AABC8(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 1) {
		return 2;
	}
	if (IsExistSummonEnemy__19nEnemyCommunicationFUc(
	        M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A))
	    == 0) {
		return 0;
	}
	return ((3.0517578125e-05f * (f32)rand()) < 0.5f) == 0;
}

void AddItemBox__17TObjEnemyMagicianFP5RwV3d(void* arg0, s32 arg1)
{
	fn_8_90B10(arg1);
}

void fn_8_AAC90(void* arg0, void* arg1)
{
	f32 temp_f0;
	f32 var_f1;

	var_f1  = M2C_FIELD(arg1, f32*, 0x14) + M2C_FIELD(arg0, f32*, 0x1A4);
	temp_f0 = M2C_FIELD(arg0, f32*, 0x258);
	if (var_f1 > temp_f0) {
		var_f1 = temp_f0;
	}
	M2C_FIELD(arg0, f32*, 0x1A4) = var_f1;
	M2C_FIELD(arg0, s16*, 0x2E)  = (s16)var_f1;
	M2C_FIELD(arg0, f32*, 0x254) = (f32)M2C_FIELD(arg0, f32*, 0x1A4);
	if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
		((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x318))->Off();
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
		((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x31C))->Change((eEnemyIcon)6);
		((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x31C))->On(0.0f, 0.0f);
	}
}

void RcvCommand__17TObjEnemyMagicianFP13sEnemyCommand(void* arg0, void* arg1)
{
	switch (M2C_FIELD(arg1, u8*, 0)) {
		case 3:
			fn_8_AAC90(arg0, arg1);
			break;
	}
}

s32 fn_8_AADD8(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x2D0) != -1) {
		fn_800E1208(M2C_FIELD(arg0, s32*, 0x2D0), 0xF, 0);
		M2C_FIELD(arg0, s32*, 0x2D0) = -1;
		return 1;
	}
	return 0;
}

s32 fn_8_AAE2C(void* arg0)
{
	s32 temp_r3;

	temp_r3 = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df((u8*)arg0 + 0x2C4, 40.0f);
	if (temp_r3 != -1) {
		M2C_FIELD(arg0, s32*, 0x2D0) = temp_r3;
		fn_800E1208(M2C_FIELD(arg0, s32*, 0x2D0), 0x17, 0);
		return 1;
	}
	M2C_FIELD(arg0, s32*, 0x2D0) = -1;
	return 0;
}

/* Whether the nearest leader is within reach on the ground plane. */
s32 fn_8_AAE98(void* arg0)
{
	s32 leader;
	PlayerObj* player;

	leader = M2C_FIELD(arg0, s32*, 0x27C);
	if (leader != -1) {
		player = lbl_802AD090[leader];
		if (player != NULL) {
			RwV3d from = M2C_FIELD(arg0, RwV3d*, 0x140);
			from.y     = 0.0f;
			RwV3d to   = player->pos;
			to.y       = 0.0f;
			if (Distance2P2P__FPC5RwV3dPC5RwV3d(&from, &to) < 1600.0f) {
				return 1;
			}
		}
	}
	return 0;
}

void AddScore__17TObjEnemyMagicianFv(void) { }

s32 fn_8_AAF4C(void* arg0)
{
	f32 temp_f1;
	s32 var_r31;

	var_r31 = 0;
	temp_f1 = M2C_FIELD(arg0, f32*, 0x1A4);
	if (temp_f1 != M2C_FIELD(arg0, f32*, 0x254)) {
		M2C_FIELD(arg0, f32*, 0x254) = temp_f1;
		if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
			if ((s32)M2C_FIELD(arg0, s32*, 0x19C) == 0x24) {
				((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x318))
				    ->On(temp_f1, M2C_FIELD(arg0, f32*, 0x258), 0x5A);
			} else {
				((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x318))
				    ->On(temp_f1, M2C_FIELD(arg0, f32*, 0x258));
			}
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
			((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x31C))->Off();
		}
		var_r31 = 1;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
		((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x318))
		    ->SetPos((RwV3d*)((u8*)arg0 + 0x140), &lbl_8_rodata_1A2C);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
		((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x31C))
		    ->SetPos((RwV3d*)((u8*)arg0 + 0x140), &lbl_8_rodata_1A2C);
	}
	return var_r31;
}

s32 fn_8_AB014(void* arg0)
{
	s32 temp_r3;

	temp_r3 = fn_800A6334((void*)arg0);
	if ((temp_r3 == 1) && ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U)
	    && (((u32)M2C_FIELD(arg0, u32*, 0x318) == 0U)
	        || (((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x318))->IsOn() == 0))) {
		((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x31C))->Change((eEnemyIcon)1);
		((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x31C))->On(0.0f, 0.0f);
	}
	return temp_r3;
}

s32 fn_8_AB0A0(void* arg0)
{
	s32 temp_r31;

	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		return 0;
	}
	temp_r31                     = fn_800A5A54(arg0);
	M2C_FIELD(arg0, s32*, 0x150) = AdjustAngle__Fiii(
	    M2C_FIELD(arg0, s32*, 0x150), M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
	if (temp_r31 < 0x80) {
		M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
		return 1;
	}
	return 0;
}

s32 fn_8_AB11C(void* arg0)
{
	f32 temp_f2;
	s32 var_r5;

	var_r5 = 1;
	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		return 1;
	}
	temp_f2 = M2C_FIELD(arg0, f32*, 0x1C4);
	M2C_FIELD(arg0, f32*, 0x144) += 0.2f;
	if (M2C_FIELD(arg0, f32*, 0x144) >= temp_f2) {
		M2C_FIELD(arg0, f32*, 0x144) = temp_f2;
	} else {
		var_r5 = 0;
	}
	return var_r5;
}

/* Fly toward the target with the move-speed boost; 0 once it lands or
 * loses the target. fn_8_AB174 inlines it ahead of its own out-of-line body. */
static inline s32 FlyBoosted(void* arg0)
{
	s32 var_r31;

	var_r31 = 1;
	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		return 1;
	}
	if ((fn_800A5AC0(arg0) < 2.0f) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
		fn_800A4668(arg0);
		var_r31 = 0;
	} else {
		fn_800A4A8C(arg0, M2C_FIELD(arg0, f32*, 0x358));
	}
	fn_800A5C6C(arg0, 0xF00);
	if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
	    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
		M2C_FIELD(arg0, f32*, 0x15C) = (f32)0.0f;
	}
	if (fn_800A5888(arg0, -1.0f) != 0) {
		fn_800A5B50(arg0, 0xF00);
		var_r31 = 0;
	}
	return var_r31;
}

s32 fn_8_AB174(void* arg0)
{
	s32 leader;
	PlayerObj* player;

	leader = M2C_FIELD(arg0, s32*, 0x27C);
	if (leader != -1) {
		RwV3d dir = M2C_FIELD(arg0, RwV3d*, 0x140);
		player    = lbl_802AD090[leader];
		if (player != NULL) {
			dir.x -= player->pos.x;
			dir.y -= player->pos.y;
			dir.z -= player->pos.z;
		}
		dir.y = 0.0f;
		fn_801990E0(&dir, &dir);
		M2C_FIELD(arg0, RwV3d*, 0x158) = dir;
	}
	return FlyBoosted(arg0);
}

s32 fn_8_AB31C(void* arg0)
{
	s32 var_r31;

	var_r31 = 1;
	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		return 1;
	}
	if ((fn_800A5AC0(arg0) < 2.0f) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
		fn_800A4668(arg0);
		var_r31 = 0;
	} else {
		fn_800A4A8C(arg0, 2.0f);
	}
	fn_800A5C6C(arg0, 0xF00);
	if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
	    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
		M2C_FIELD(arg0, f32*, 0x15C) = (f32)0.0f;
	}
	if (fn_800A5888(arg0, -1.0f) != 0) {
		fn_800A5B50(arg0, 0xF00);
		var_r31 = 0;
	}
	return var_r31;
}

/* Out of line the early exit returns its constant directly. */
s32 fn_8_AB424(void* arg0)
{
	s32 var_r31;

	var_r31 = 1;
	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		return 1;
	}
	if ((fn_800A5AC0(arg0) < 2.0f) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
		fn_800A4668(arg0);
		var_r31 = 0;
	} else {
		fn_800A4A8C(arg0, M2C_FIELD(arg0, f32*, 0x358));
	}
	fn_800A5C6C(arg0, 0xF00);
	if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
	    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
		M2C_FIELD(arg0, f32*, 0x15C) = (f32)0.0f;
	}
	if (fn_800A5888(arg0, -1.0f) != 0) {
		fn_800A5B50(arg0, 0xF00);
		var_r31 = 0;
	}
	return var_r31;
}

/* The ground-shadow scale bounds AB52C clamps by reference. */
const f32 lbl_8_rodata_1AF4[1] = { 0.2f };
const f32 lbl_8_rodata_1AF8[1] = { 1.0f };

#pragma opt_common_subs off
void DispShadow__17TObjEnemyMagicianFv(void* arg0)
{
	if (M2C_FIELD(arg0, f32*, 0x2B8) <= 0.0f) {
		return;
	}
	fn_800B7864(0);
	RwV3d scale = lbl_8_rodata_1A94;
	f32 size    = 1.0f - 0.004f * (M2C_FIELD(arg0, f32*, 0x144) - M2C_FIELD(arg0, f32*, 0x284));
	size        = Clamp(size, lbl_8_rodata_1AF4[0], lbl_8_rodata_1AF8[0]);
	fn_800B7514((u8*)arg0 + 0x280, (u8*)arg0 + 0x2A4, &scale, size);
	scale.x = 6.0f;
	scale.z = 6.0f;
	fn_800B7514((u8*)arg0 + 0x28C, (u8*)arg0 + 0x2A4, &scale, size);
	fn_800B7514((u8*)arg0 + 0x298, (u8*)arg0 + 0x2A4, &scale, size);
	fn_800B7820();
}
#pragma opt_common_subs reset

void DispTrans__17TObjEnemyMagicianFv(void* arg0)
{
	f32 fade;
	s32 frame;

	if (M2C_FIELD(arg0, f32*, 0x2B8) <= 0.0f) {
		return;
	}
	fade = M2C_FIELD(arg0, f32*, 0x2B4);
	if (!(fade <= 0.2f) && fade < 1.0f) {
		SaveRenderState__7nRenderFv();
		SetRenderStateForBlendAdd__7nRenderFv();
		SetLightNum__7nRenderFUi(0x10);
		RwRGBAReal color = lbl_8_rodata_1A38;
		color.alpha      = M2C_FIELD(arg0, f32*, 0x2B4);
		objRpClumpForAllMaterialsToChangeMaterialColor__FP7RpClumpP10RwRGBAReal(
		    M2C_FIELD(arg0, s32*, 0xE8), &color);
		fn_8014FF2C(M2C_FIELD(arg0, void**, 0xE8));
		LoadRenderState__7nRenderFv();
	}
	if (M2C_FIELD(arg0, s32*, 0x2F8) != 0) {
		frame = M2C_FIELD(lbl_8042C180, s32*, 0x30);
		if (lbl_8_bss_1A18 != frame) {
			lbl_8_bss_1A18 = frame;
			fn_8011B844(lbl_8_bss_19D0, 1.0f);
			fn_8014FFBC(M2C_FIELD(&lbl_8_bss_19C8, s32*, 4), &SetAtomicCustomFXData__FP8RpAtomicPv,
			    lbl_8_bss_19D4);
		}
		SaveRenderState__7nRenderFv();
		SetRenderStateForBlendAdd__7nRenderFv();
		SetLightNum__7nRenderFUi(0x10);
		fn_8014FF2C(M2C_FIELD(arg0, void**, 0x2FC));
		LoadRenderState__7nRenderFv();
	}
}

void DispOpaq__17TObjEnemyMagicianFv(void* arg0)
{
	if (M2C_FIELD(arg0, f32*, 0x2B8) <= 0.0f) {
		return;
	}
	if (M2C_FIELD(arg0, f32*, 0x2B4) >= 1.0f) {
		SetLightNum__7nRenderFUi(((TRenderer*)arg0)->Slot90());
		RwRGBAReal color = lbl_8_rodata_1A84;
		objRpClumpForAllMaterialsToChangeMaterialColor__FP7RpClumpP10RwRGBAReal(
		    M2C_FIELD(arg0, s32*, 0xE8), &color);
		fn_8014FF2C(M2C_FIELD(arg0, void**, 0xE8));
	}
}

void UpdateOnEdit__17TObjEnemyMagicianFv(void* arg0)
{
	fn_8_AEB80((TEnemyParalysis*)arg0);
	fn_8_AE604((TEnemyParalysis*)arg0);
}

void Update__17TObjEnemyMagicianFv(void* arg0)
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
	M2C_FIELD(arg0, s32*, 0x310) = var_r0;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0_2 = 0;
	} else {
		var_r0_2 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x314) = var_r0_2;
	if ((u32)M2C_FIELD(arg0, u32*, 0x38) != 0U) {
		M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(arg0, f32*, 0x88);
		M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(arg0, f32*, 0x8C);
		M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(arg0, f32*, 0x90);
	}
	fn_800A5B34(arg0);
	((TRenderer*)arg0)->Slot38();
	temp_r3 = M2C_FIELD(arg0, void***, 0x248);
	if (temp_r3 != NULL) {
		((TSubDispatch*)temp_r3)->vslot3(arg0);
	}
	((TRenderer*)arg0)->Slot50(M2C_FIELD(arg0, s32*, 0x19C), 1);
	fn_8_AE604((TEnemyParalysis*)arg0);
	fn_800A3D48(arg0);
	if ((fn_80017800(arg0) != 0) && ((u32)M2C_FIELD(arg0, u32*, 0x38) != 0U)) {
		M2C_FIELD(arg0, f32*, 0xA4) = (f32)M2C_FIELD(arg0, f32*, 0x88);
		M2C_FIELD(arg0, f32*, 0xA8) = (f32)M2C_FIELD(arg0, f32*, 0x8C);
		M2C_FIELD(arg0, f32*, 0xAC) = (f32)M2C_FIELD(arg0, f32*, 0x90);
		M2C_FIELD(arg0, f32*, 0x88) = (f32)M2C_FIELD(arg0, f32*, 0x140);
		M2C_FIELD(arg0, f32*, 0x8C) = (f32)M2C_FIELD(arg0, f32*, 0x144);
		M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0x148);
		M2C_FIELD(arg0, s32*, 0x94) = (s32)M2C_FIELD(arg0, s32*, 0x14C);
		M2C_FIELD(arg0, s32*, 0x98) = (s32)M2C_FIELD(arg0, s32*, 0x150);
		M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(arg0, s32*, 0x154);
		Entry__7C_COLLIFv((u8*)arg0 + 0x28);
	}
}

/* Rise back to the hover height; true once there (or when grounded). */
static inline s32 Rise(void* self)
{
	s32 done = 1;
	f32 top;

	if (M2C_FIELD(self, s32*, 0x310) == 0) {
		return 1;
	}
	top = M2C_FIELD(self, f32*, 0x1C4);
	M2C_FIELD(self, f32*, 0x144) += 0.2f;
	if (M2C_FIELD(self, f32*, 0x144) >= top) {
		M2C_FIELD(self, f32*, 0x144) = top;
	} else {
		done = 0;
	}
	return done;
}

void fn_8_ABA38(void* arg0, s32 arg1)
{
	f32 temp_f2;
	s32 var_r4;

	switch (arg1) { /* irregular */
		case 0:
			if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
				((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x31C))->Off();
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
				return;
			}
			M2C_FIELD(arg0, s32*, 0xD4) = 6;
			return;
		case 1:
			var_r4 = Rise(arg0);
			if (var_r4 != 0) {
				M2C_FIELD(arg0, s32*, 0x250) = 0x1F;
			}
			return;
		case 2:
		case 3:
			break;
	}
}

/* Mode handler: paralysed. CtrlMode inlines it although the compiler
 * would not inline a body this large on its own. */
static inline void ModeParalysis(void* arg0, s32 arg1)
{
	s32 temp_r0;
	f32 life;

	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0xA;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 0xB;
			}
			M2C_FIELD(arg0, s32*, 0x2F0) = 0x5A;
			M2C_FIELD(arg0, s32*, 0x2F4) = (s32)M2C_FIELD(arg0, s32*, 0x238);
			if ((u32)EnemyScoreMan__14TEnemyScoreMan == 0U) {
				CreateInstance__14TEnemyScoreManFv();
			}
			ParalyzeEnemy__14TEnemyScoreManFi(
			    EnemyScoreMan__14TEnemyScoreMan, M2C_FIELD(arg0, s32*, 0x238));
			M2C_FIELD(arg0, s32*, 0x2EC) = 0;
			M2C_FIELD(arg0, u16*, 0x30)  = (u16)(M2C_FIELD(arg0, u16*, 0x30) | 0x200);
			return;
		case 1:
			temp_r0                      = M2C_FIELD(arg0, s32*, 0x2F0) - 1;
			M2C_FIELD(arg0, s32*, 0x2F0) = temp_r0;
			if (temp_r0 == 0) {
				if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
					((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x318))->Off();
				}
				if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
					((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x31C))->Change((eEnemyIcon)2);
					((TEnemyIconMan*)M2C_FIELD(arg0, u32*, 0x31C))->On(0.0f, 0.0f);
				}
			}
			{
				RwV3d point = M2C_FIELD(arg0, RwV3d*, 0x280);
				point.y += 10.0f;
				if (fn_800A34D0(arg0, &point) != 0 && M2C_FIELD(arg0, s32*, 0x2EC) == 0) {
					M2C_FIELD(arg0, s32*, 0x2EC) = 1;
					life                         = M2C_FIELD(arg0, f32*, 0x1A4) - 1.0f;
					M2C_FIELD(arg0, f32*, 0x1A4) = life;
					if (life < 0.0f) {
						M2C_FIELD(arg0, f32*, 0x1A4) = 0.0f;
					}
					M2C_FIELD(arg0, s16*, 0x2E)  = (s16)M2C_FIELD(arg0, f32*, 0x1A4);
					M2C_FIELD(arg0, s32*, 0x230) = fn_800AB104(M2C_FIELD(arg0, s32*, 0x2F4));
				}
			}
			break;
		case 2:
			break;
		case 3:
			M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) & 0xFFFFFDFF);
			break;
	}
}

void fn_8_ABB10(void* arg0, s32 arg1)
{
	ModeParalysis(arg0, arg1);
}

void fn_8_ABCE4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 6;
			}
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0x404D, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
			}
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0x404C, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
			}
			break;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
				M2C_FIELD(arg0, s32*, 0x150) += 5632.0f;
				M2C_FIELD(arg0, f32*, 0x2B8)
				    = AdjustFloat__Ffff(M2C_FIELD(arg0, f32*, 0x2B8), 1.5f, 0.04f);
				M2C_FIELD(arg0, f32*, 0x2BC)
				    = AdjustFloat__Ffff(M2C_FIELD(arg0, f32*, 0x2BC), 1.5f, 0.05f);
				M2C_FIELD(arg0, f32*, 0x2C0)
				    = AdjustFloat__Ffff(M2C_FIELD(arg0, f32*, 0x2C0), 1.5f, 0.04f);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_ABE70(void* arg0, s32 arg1)
{
	f32 dx;
	f32 range;
	f32 r;
	f32 dz;

	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 6;
			}
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0x404C, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
			}
			M2C_FIELD(arg0, s32*, 0x2E4) = 0;
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
				M2C_FIELD(arg0, s32*, 0x150) += 5632.0f;
				M2C_FIELD(arg0, f32*, 0x2B8)
				    = AdjustFloat__Ffff(M2C_FIELD(arg0, f32*, 0x2B8), 0.0f, 0.04f);
				M2C_FIELD(arg0, f32*, 0x2BC)
				    = AdjustFloat__Ffff(M2C_FIELD(arg0, f32*, 0x2BC), 4.0f, 0.05f);
				M2C_FIELD(arg0, f32*, 0x2C0)
				    = AdjustFloat__Ffff(M2C_FIELD(arg0, f32*, 0x2C0), 0.0f, 0.04f);
				if (((s32)M2C_FIELD(arg0, s32*, 0x2E4) == 0)
				    && (0.0f == M2C_FIELD(arg0, f32*, 0x2B8))) {
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x404D, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
					}
					M2C_FIELD(arg0, s32*, 0x2E4) = 1;
					range                        = M2C_FIELD(arg0, f32*, 0x210);
					r                            = range * (3.0517578125e-05f * (f32)rand());
					dx                           = (2.0f * r) - range;
					dz = (2.0f * (range * (3.0517578125e-05f * (f32)rand()))) - range;
					M2C_FIELD(arg0, f32*, 0x140) = (f32)(dx + M2C_FIELD(arg0, f32*, 0x1C0));
					M2C_FIELD(arg0, f32*, 0x148) = (f32)(dz + M2C_FIELD(arg0, f32*, 0x1C8));
				}
			}
			return;
		case 2:
		case 3:
			break;
	}
}

#pragma opt_common_subs off
void fn_8_AC10C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			if (M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 6;
			}
			M2C_FIELD(arg0, s32*, 0x274) = 0x28;
			M2C_FIELD(arg0, f32*, 0x1B8) = 2.0f;
			return;
		case 1:
			if (fn_8_AB174(arg0) == 0) {
				M2C_FIELD(arg0, s32*, 0x250) = 0x3B;
			}
			DecreaseTimer__7nSystemFRi((u8*)arg0 + 0x274);
			if (M2C_FIELD(arg0, s32*, 0x274) < 0) {
				M2C_FIELD(arg0, s32*, 0x250) = 0x3B;
			}
			return;
		case 2:
		case 3:
			break;
	}
}
#pragma opt_common_subs reset

void fn_8_AC338(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			if (M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0x350) = 1;
				M2C_FIELD(arg0, s32*, 0xD4)  = 3;
				if (lbl_8042C388 != 0U) {
					fn_800B4A38(lbl_8042C388, 0x404E, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
				}
			} else {
				M2C_FIELD(arg0, s32*, 0x350) = 0;
				M2C_FIELD(arg0, s32*, 0xD4)  = 4;
				if (lbl_8042C388 != 0U) {
					fn_800B4A38(lbl_8042C388, 0x404F, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
				}
				if (M2C_FIELD(arg0, s32*, 0x2D4) > 0) {
					fn_8_A504(M2C_FIELD(arg0, s32*, 0x2D4), (u8*)arg0 + 0x140, 0, 0.5f, 2.0f);
					M2C_FIELD(arg0, s32*, 0x2D4) = 0;
					M2C_FIELD(arg0, s32*, 0x2D8) = 0;
				}
			}
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

/* Mode handler: the ring-stealing attack. A spell travels from the staff
 * to the nearest leader, who then drops rings into the magician's stock. */
void fn_8_AC440(MagStrat* arg0, s32 arg1)
{
	sAngle shadowAng;
	s32 leader;
	PlayerCharacter* chara;
	PlayerObj* player;
	s32 index;
	s32 rings;
	f32 pulse;

	switch (arg1) {
		case 0:
			arg0->unk2F8 = 0;
			arg0->unk2E4 = 0;
			arg0->unk274 = 0x28;
			arg0->unk2D8 = 0;
			arg0->unk2D0 = -1;
			GetNearestLeaderPosition__13nSearchPlayerFPC5RwV3dP5RwV3df(
			    (void*)&arg0->unk140, (void*)&arg0->unk2C4, 100000000.0f);
			arg0->unk2C8 += 100.0f;
			arg0->unk2C8 = GetShadowPos__FP5RwV3dP6sAnglei(&arg0->unk2C4, &shadowAng, 1);
			if (arg0->unk2DC != 0U) {
				*(RwV3d*)&arg0->unk338 = fn_8019E8EC((void*)arg0->unk2DC)->pos;
			}
			if (lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0x4049, &arg0->unk140, NULL, 1, 0, 0);
			}
			arg0->unk300 = 0.0f;
			arg0->unk304 = 1.0f;
			arg0->unk308 = 0.0f;
			arg0->unk30C = 0;
			break;
		case 1:
			if (arg0->unk310 == 0 || -1000000.0f == arg0->unk2C8) {
				break;
			}
			if (arg0->unk2E4 == 0 && --arg0->unk274 < 0) {
				arg0->unk274 = 0xA;
				arg0->unkD4  = 8;
				arg0->unk2F8 = 1;
				arg0->unk2E4 = 1;
				break;
			}
			if (arg0->unkD0 == 9) {
				if (arg0->unk2D0 == -1) {
					leader
					    = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df((u8*)arg0 + 0x2C4, 40.0f);
					if (leader != -1) {
						arg0->unk2D0 = leader;
						fn_800E1208(arg0->unk2D0, 0x17, 0);
					} else {
						arg0->unk2D0 = -1;
					}
				}
				if (arg0->unk2D0 != -1 && --arg0->unk274 < 0) {
					chara = lbl_802AD070[arg0->unk2D0];
					if (chara != NULL && num__10PARAM_RING[chara->ringIndex] != 0) {
						player = lbl_802AD090[arg0->unk2D0];
						if (player != NULL) {
							*(RwV3d*)&arg0->unk32C = player->pos;
							new (lbl_8042C148)
							    RingSpellStorage(arg0, (RingSpellParam*)&arg0->unk32C);
						}
					}
					arg0->unk274 = 0xA;
				}
				if (lbl_8042C388 != 0U) {
					fn_800B4A38(lbl_8042C388, 0x404A, (void*)&arg0->unk140, (int)arg0, 3, 0, 2);
				}
			}
			arg0->unk30C += 0x600;
			arg0->unk300 = AdjustFloat__Ffff(arg0->unk300, 1.0f, 0.02f);
			pulse        = 1.2f * fn_800D7B00(arg0->unk30C);
			arg0->unk304 = 1.0f + pulse;
			arg0->unk308 = AdjustFloat__Ffff(arg0->unk308, 1.0f, 0.02f);
			break;
		case 2:
			break;
		case 3:
			arg0->unk2F8 = 0;
			if (arg0->unk2D0 != -1) {
				chara = lbl_802AD070[arg0->unk2D0];
				if (chara != NULL) {
					index = chara->ringIndex;
					rings = num__10PARAM_RING[index];
					if (rings != 0) {
						if (rings >= 0x14) {
							arg0->unk2D4 = 0x14;
							arg0->unk2D8 = arg0->unk2D4;
							((PARAM_RING*)&arg0->unk240)->setRingNum(index, rings - 0x14);
							if (lbl_8042C388 != 0U) {
								fn_800B4A38(lbl_8042C388, 0x404B, &arg0->unk140, NULL, 1, 0, 0);
							}
						} else {
							arg0->unk2D4 = rings;
							arg0->unk2D8 = arg0->unk2D4;
							((PARAM_RING*)&arg0->unk240)->setRingNum(index, 0);
							if (lbl_8042C388 != 0U) {
								fn_800B4A38(lbl_8042C388, 0x404B, &arg0->unk140, NULL, 1, 0, 0);
							}
						}
					}
				}
				if (arg0->unk2D0 != -1) {
					fn_800E1208(arg0->unk2D0, 0xF, 0);
					arg0->unk2D0 = -1;
				}
			}
			break;
	}
}

void fn_8_AC9D8(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2E4) = 0;
			M2C_FIELD(arg0, s32*, 0x2E8) = 0;
			M2C_FIELD(arg0, s32*, 0x274) = 0x28;
			if ((u32)lbl_8042C388 == 0U) {
				return;
			}
			fn_800B4A38(lbl_8042C388, 0x4046, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x274));
			if (((s32)M2C_FIELD(arg0, s32*, 0x2E4) == 0)
			    && ((s32)M2C_FIELD(arg0, s32*, 0x274) < 0)) {
				M2C_FIELD(arg0, s32*, 0xD4)  = 1;
				M2C_FIELD(arg0, s32*, 0x2E4) = 1;
			}
			if (((s32)M2C_FIELD(arg0, s32*, 0x2E8) == 0)
			    && ((s32)M2C_FIELD(arg0, s32*, 0xD0) == 1)) {
				if (M2C_FIELD(arg0, f32*, 0xB8) >= 24.0f) {
					Create__12TEnemySummonFUc(M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A));
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x4047, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
					}
					M2C_FIELD(arg0, s32*, 0x2E8) = 1;
				}
			}
			break;
		case 2:
		case 3:
			break;
	}
}

/* Mode handler: summon. Calls up the summoned enemies once the wind-up
 * animation passes its frame, with a glow on the staff meanwhile. */
#pragma opt_common_subs off
void fn_8_ACB0C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x2E4) = 0;
			M2C_FIELD(arg0, s32*, 0x2E8) = 0;
			M2C_FIELD(arg0, s32*, 0x274) = 0x28;
			if (lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0x4043, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
			}
			break;
		case 1:
			DecreaseTimer__7nSystemFRi((u8*)arg0 + 0x274);
			if (M2C_FIELD(arg0, s32*, 0x2E4) == 0 && M2C_FIELD(arg0, s32*, 0x274) < 0) {
				M2C_FIELD(arg0, s32*, 0xD4)  = 2;
				M2C_FIELD(arg0, s32*, 0x2E4) = 1;
				if (M2C_FIELD(arg0, void**, 0x324) == NULL) {
					sAngle ang  = lbl_8_rodata_1A54;
					RwV3d point = lbl_8_rodata_1A60;
					fn_8019941C(&point, &point, 1, fn_8019E8EC(M2C_FIELD(arg0, void**, 0x2E0)));
					M2C_FIELD(arg0, void**, 0x324) = fn_8006298C(0x27, &point, &ang);
					fn_8005FD20(M2C_FIELD(arg0, void**, 0x324));
				}
			}
			if (M2C_FIELD(arg0, s32*, 0x2E8) == 0 && M2C_FIELD(arg0, s32*, 0xD0) == 2) {
				if (M2C_FIELD(arg0, f32*, 0xB8) >= 28.0f) {
					sEnemyCommandEx cmd(3);
					cmd.id    = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A);
					cmd.range = 100.0f;
					cmd.pos   = M2C_FIELD(arg0, RwV3d*, 0x140);
					cmd.value = M2C_FIELD(arg0, f32*, 0x214);
					cmd.Send();
					if (lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x4044, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
					}
					M2C_FIELD(arg0, s32*, 0x2E8) = 1;
				}
			}
			if (M2C_FIELD(arg0, void**, 0x324) != NULL) {
				RwV3d glow = lbl_8_rodata_1A6C;
				fn_8019941C(&glow, &glow, 1, fn_8019E8EC(M2C_FIELD(arg0, void**, 0x2E0)));
				M2C_FIELD(M2C_FIELD(arg0, void**, 0x324), RwV3d*, 0x80) = glow;
			}
			break;
		case 2:
			break;
		case 3:
			if (M2C_FIELD(arg0, void**, 0x324) != NULL) {
				fn_8005FD8C(M2C_FIELD(arg0, void**, 0x324), -1);
				M2C_FIELD(arg0, void**, 0x324) = NULL;
			}
			break;
	}
}
#pragma opt_common_subs reset

void fn_8_ACDC0(void) { }

void fn_8_ACDC4(void* arg0, s32 arg1)
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

/* The bob while flying: the height is the base plus two sine waves. */
static inline void Hover(void* self)
{
	f32 wave;

	if (M2C_FIELD(self, s32*, 0x310) != 0) {
		M2C_FIELD(self, s32*, 0x278) += 0x100;
		wave = 2.0f * fn_800D7B00(M2C_FIELD(self, s32*, 0x278) * 2)
		    + 2.0f * fn_800D7B00(M2C_FIELD(self, s32*, 0x278) * 4);
		M2C_FIELD(self, f32*, 0x144) = wave + M2C_FIELD(self, f32*, 0x1C4);
	}
}

/* Mode handler: chase the nearest leader. */
#pragma opt_common_subs off
void fn_8_ACE24(void* arg0, s32 arg1)
{
	s32 leader;
	s32 turn;
	PlayerObj* player;

	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, f32*, 0x1B8) = 4.0f;
			return;
		case 1:
			M2C_FIELD(arg0, s32*, 0x27C) = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(
			    &((TEnemyParalysis*)arg0)->pos, 100000000.0f);
			if (M2C_FIELD(arg0, s32*, 0x27C) != -1) {
				player = lbl_802AD090[M2C_FIELD(arg0, s32*, 0x27C)];
				if (player != NULL) {
					M2C_FIELD(arg0, RwV3d*, 0x1CC) = player->pos;
				}
			}
			if (M2C_FIELD(arg0, s32*, 0x310) != 0) {
				turn                         = fn_800A5A54(arg0);
				M2C_FIELD(arg0, s32*, 0x150) = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x150),
				    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
				if (turn < 0x80) {
					M2C_FIELD(arg0, s32*, 0x150) = M2C_FIELD(arg0, s32*, 0x174);
				}
			}
			leader = M2C_FIELD(arg0, s32*, 0x27C);
			if (leader != -1) {
				RwV3d dir = ((TEnemyParalysis*)arg0)->pos;
				player    = lbl_802AD090[leader];
				if (player != NULL) {
					dir.x -= player->pos.x;
					dir.y -= player->pos.y;
					dir.z -= player->pos.z;
				}
				dir.y = 0.0f;
				fn_801990E0(&dir, &dir);
				M2C_FIELD(arg0, RwV3d*, 0x158) = dir;
			}
			if (M2C_FIELD(arg0, s32*, 0x310) != 0) {
				if (fn_800A5AC0(arg0) < 2.0f || (M2C_FIELD(arg0, u16*, 0x106) & 4) != 0) {
					fn_800A4668(arg0);
				} else {
					fn_800A4A8C(arg0, M2C_FIELD(arg0, f32*, 0x358));
				}
				fn_800A5C6C(arg0, 0xF00);
				if ((M2C_FIELD(arg0, u16*, 0x106) & 2) != 0
				    && M2C_FIELD(arg0, f32*, 0x15C) < 1.5f * M2C_FIELD(arg0, f32*, 0x1A8)) {
					M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
				}
				if (fn_800A5888(arg0, -1.0f) != 0) {
					fn_800A5B50(arg0, 0xF00);
				}
			}
			Hover(arg0);
			return;
		case 2:
		case 3:
			break;
	}
}
#pragma opt_common_subs reset

void fn_8_AD0EC(void* arg0, s32 arg1)
{
	s32 temp_r0;
	s32 temp_r30;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
				return;
			}
			M2C_FIELD(arg0, s32*, 0xD4) = 6;
			return;
		case 1:
			M2C_FIELD(arg0, s32*, 0x27C)
			    = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df((u8*)arg0 + 0x140, 100000000.0f);
			temp_r0 = M2C_FIELD(arg0, s32*, 0x27C);
			if (temp_r0 != -1) {
				temp_r3 = *(void**)((u8*)&lbl_802AD090 + (temp_r0 * 4));
				if (temp_r3 != NULL) {
					M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(temp_r3, f32*, 0x18);
					M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(temp_r3, f32*, 0x1C);
					M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(temp_r3, f32*, 0x20);
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
				temp_r30                     = fn_800A5A54(arg0);
				M2C_FIELD(arg0, s32*, 0x150) = AdjustAngle__Fiii(M2C_FIELD(arg0, s32*, 0x150),
				    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
				if (temp_r30 < 0x80) {
					M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
				}
			}
			Hover(arg0);
			return;
		case 2:
		case 3:
			break;
	}
}

/* Turn toward the target heading; true once facing it. */
static inline s32 TurnToTarget(void* self)
{
	s32 turn;

	if (M2C_FIELD(self, s32*, 0x310) == 0) {
		return 0;
	}
	turn                         = fn_800A5A54(self);
	M2C_FIELD(self, s32*, 0x150) = AdjustAngle__Fiii(
	    M2C_FIELD(self, s32*, 0x150), M2C_FIELD(self, s32*, 0x174), M2C_FIELD(self, s32*, 0x180));
	if (turn < 0x80) {
		M2C_FIELD(self, s32*, 0x150) = M2C_FIELD(self, s32*, 0x174);
		return 1;
	}
	return 0;
}

/* Pick a new spot around the set position to warp to, flipping sides. */
static inline void PickWarpPoint(void* arg0)
{
	RwMatrix m;
	RwV3d point;
	f32 angle;

	point.x = 0.0f;
	point.y = 0.0f;
	point.z = M2C_FIELD(arg0, f32*, 0x25C);
	angle   = 180.0f + 0.0054931640625f * (f32)M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x10)
	    + (160.0f * (3.0517578125e-05f * (f32)rand()) - 80.0f);
	fn_80195A74(&m, &AxisY, angle, 0);
	fn_80196050(&m, M2C_FIELD(arg0, RwV3d**, 0xB0), 2);
	fn_8019941C(&point, &point, 1, &m);
	M2C_FIELD(arg0, RwV3d*, 0x1CC) = point;
	M2C_FIELD(arg0, f32*, 0x25C) *= -1.0f;
}

/* Mode handler: warp around the set position. */
void fn_8_AD260(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, f32*, 0x1B8) = 0.2f;
			if (M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 6;
			}
			M2C_FIELD(arg0, RwV3d*, 0x1CC) = M2C_FIELD(arg0, RwV3d*, 0x260);
			if (TurnToTarget(arg0)) {
				M2C_FIELD(arg0, s32*, 0x2B0) = 1;
			} else {
				M2C_FIELD(arg0, s32*, 0x2B0) = 0;
			}
			return;
		case 1:
			if (M2C_FIELD(arg0, s32*, 0x2B0) != 0 && !FlyBoosted(arg0)) {
				PickWarpPoint(arg0);
				M2C_FIELD(arg0, s32*, 0x2B0) = 0;
			}
			if (M2C_FIELD(arg0, s32*, 0x2B0) == 0 && TurnToTarget(arg0)) {
				M2C_FIELD(arg0, s32*, 0x2B0) = 1;
			}
			Hover(arg0);
			break;
		case 2:
			break;
		case 3:
			M2C_FIELD(arg0, RwV3d*, 0x260) = M2C_FIELD(arg0, RwV3d*, 0x1CC);
			break;
	}
}

void fn_8_AD670(void* arg0, s32 arg1)
{

	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
				return;
			}
			M2C_FIELD(arg0, s32*, 0xD4) = 6;
			return;
		case 1:
			Hover(arg0);
			return;
		case 2:
		case 3:
			break;
	}
}

#pragma opt_common_subs off
/* CtrlMode: run the handler of the given mode for this step (0 enter,
 * 1 update, 2/3 the rest). The small handlers inline here. */
void CtrlMode__17TObjEnemyMagicianF8ENEMY_MDQ29TObjEnemy10eCtrlSMode(void* arg0, s32 mode, s32 step)
{
	switch (mode) {
		case 1:
			fn_8_AD670(arg0, step);
			break;
		case 2:
			fn_8_AD260(arg0, step);
			break;
		case 54:
			fn_8_ACE24(arg0, step);
			break;
		case 31:
			fn_8_AD0EC(arg0, step);
			break;
		case 29:
			fn_8_ACDC4(arg0, step);
			break;
		case 26:
			fn_8_AC338(arg0, step);
			break;
		case 55:
			fn_8_AC9D8(arg0, step);
			break;
		case 56:
			fn_8_ACB0C(arg0, step);
			break;
		case 57:
			fn_8_AC440((MagStrat*)arg0, step);
			break;
		case 58:
			fn_8_AC10C(arg0, step);
			break;
		case 59:
			fn_8_ABE70(arg0, step);
			break;
		case 60:
			fn_8_ABCE4(arg0, step);
			break;
		case 36:
			ModeParalysis(arg0, step);
			break;
		case 37:
			fn_8_ABA38(arg0, step);
			break;
	}
}
#pragma opt_common_subs reset

void fn_8_AE428(void* arg0)
{
	Hover(arg0);
}

void fn_8_AE4C0(void* arg0)
{
	PickWarpPoint(arg0);
}

/* SetPosition: place the body and the staff, find the bones, and set the
 * ground shadow. */
#pragma opt_common_subs off
void fn_8_AE604(TEnemyParalysis* arg0)
{
	sAngle shadowAng;
	RwFrame* frame;
	s32 bone;
	f32 height;
	void* shadow;

	if (arg0->unkE8 != NULL) {
		frame = *(RwFrame**)((u8*)arg0->unkE8 + 4);
		if (arg0->unk19C == 0x24 && arg0->unk24C != NULL) {
			Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(arg0->unk24C, frame, 0);
			fn_8019EC30(frame, (u8*)arg0 + 0x2B8, 2);
			fn_8019ED68(frame, &AxisZ, arg0->unk270, 2);
			fn_8019ED68(frame, &AxisX, arg0->unk26C, 2);
			fn_8019ED68(frame, &AxisY, 180.0f + 0.0054931640625f * (f32)arg0->unk150, 2);
			fn_8019EB94(frame, (u8*)&arg0->pos, 2);
			SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(arg0->unk24C, &arg0->pos, &arg0->unk14C);
		} else {
			fn_8019EC30(frame, (u8*)arg0 + 0x2B8, 0);
			fn_8019ED68(frame, &AxisZ, arg0->unk270, 2);
			fn_8019ED68(frame, &AxisX, arg0->unk26C, 2);
			fn_8019ED68(frame, &AxisY, 180.0f + 0.0054931640625f * (f32)arg0->unk150, 2);
			fn_8019EB94(frame, (u8*)&arg0->pos, 2);
		}
	}
	if (arg0->unk2FC != NULL) {
		frame = *(RwFrame**)((u8*)arg0->unk2FC + 4);
		fn_8019EC30(frame, (u8*)arg0 + 0x300, 0);
		fn_8019EB94(frame, (u8*)arg0 + 0x2C4, 2);
	}
	if (arg0->unk2E0 == 0) {
		bone = objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(arg0->unkEC, 0x3EA);
		if (bone != -1) {
			arg0->unk2E0 = (u32)arg0->unkEC->pNodeInfo[bone].pFrame;
		}
	}
	if (arg0->unk2DC == 0) {
		bone = objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(arg0->unkEC, 0x3E9);
		if (bone != -1) {
			arg0->unk2DC = (u32)arg0->unkEC->pNodeInfo[bone].pFrame;
		}
	}
	if ((M2C_FIELD(arg0->unkB0, u32*, 0x18) & 0x20000) != 0) {
		if ((arg0->unk106 & 2) != 0) {
			arg0->unk2A4 = arg0->unk118;
			arg0->unk2AC = arg0->unk120;
			arg0->unk284 = 0.3f + arg0->pos.y;
		} else {
			height       = GetShadowPos__FP5RwV3dP6sAnglei(&arg0->pos, &shadowAng, 1);
			arg0->unk284 = height;
			if (-1000000.0f != height) {
				arg0->unk280 = arg0->pos.x;
				arg0->unk284 += 0.3f;
				arg0->unk288 = arg0->pos.z;
				arg0->unk2A4 = 0.0054931640625f * (f32)shadowAng.x;
				arg0->unk2AC = 0.0054931640625f * (f32)shadowAng.z;
			}
		}
		arg0->unk2A8 = 180.0f + 0.0054931640625f * (f32)arg0->unk150;
		arg0->unk280 = arg0->pos.x;
		arg0->unk288 = arg0->pos.z;
		if (arg0->unk2E0 != 0) {
			*(RwV3d*)&arg0->unk28C = fn_8019E8EC((void*)arg0->unk2E0)->pos;
			arg0->unk290           = arg0->unk284;
		}
		if (arg0->unk2DC != 0) {
			*(RwV3d*)&arg0->unk298 = fn_8019E8EC((void*)arg0->unk2DC)->pos;
			arg0->unk29C           = arg0->unk284;
		}
		shadow = arg0->unk320;
		if (shadow != NULL) {
			RwV3d pos  = *(RwV3d*)&arg0->unk280;
			sAngle ang = lbl_8_rodata_1A48;
			pos.y -= 0.3f;
			M2C_FIELD(shadow, RwV3d*, 0x80)  = pos;
			M2C_FIELD(shadow, sAngle*, 0x8C) = ang;
		}
	}
}
#pragma opt_common_subs reset

void fn_8_AEAA8(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x2FC) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2FC));
		M2C_FIELD(arg0, u32*, 0x2FC) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0xE8));
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

void fn_8_AEB00(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0x2FC) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0x2FC));
		M2C_FIELD(arg0, void**, 0x2FC) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0xE8));
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	M2C_FIELD(arg0, void**, 0xE8)  = fn_80150588(M2C_FIELD(&lbl_8_bss_19C8, void**, 0));
	M2C_FIELD(arg0, void**, 0x2FC) = fn_80150588(M2C_FIELD(&lbl_8_bss_19C8, void**, 4));
}

void fn_8_AEB80(TEnemyParalysis* arg0)
{
	M2C_UNK sp14;
	f32 sp8[3];
	f32 temp_f3;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r4;

	temp_r4      = M2C_FIELD(arg0->unkB0, void**, 0x2C);
	arg0->unk350 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0);
	arg0->unk354 = M2C_FIELD(temp_r4, s32*, 0x10);
	arg0->unk358 = M2C_FIELD(temp_r4, f32*, 0x14);
	arg0->unk20C = M2C_FIELD(temp_r4, f32*, 8);
	arg0->unk210 = M2C_FIELD(temp_r4, f32*, 4);
	arg0->unk214 = M2C_FIELD(temp_r4, f32*, 8);
	arg0->unk1D8 = 0.0f;
	arg0->unk1DC = 0.0f;
	arg0->unk1E0 = M2C_FIELD(temp_r4, f32*, 0xC);
	temp_r3      = arg0->unkB0;
	arg0->pos.x  = M2C_FIELD(temp_r3, f32*, 0);
	arg0->pos.y  = M2C_FIELD(temp_r3, f32*, 4);
	arg0->pos.z  = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2    = arg0->unkB0;
	arg0->unk14C = M2C_FIELD(temp_r3_2, s32*, 0xC);
	arg0->unk150 = M2C_FIELD(temp_r3_2, s32*, 0x10);
	arg0->unk154 = M2C_FIELD(temp_r3_2, s32*, 0x14);
	arg0->unk1C0 = arg0->pos.x;
	arg0->unk1C4 = arg0->pos.y;
	arg0->unk1C8 = arg0->pos.z;
	arg0->unk1CC = arg0->pos.x;
	arg0->unk1D0 = arg0->pos.y;
	arg0->unk1D4 = arg0->pos.z;
	arg0->unk1C0 = arg0->pos.x;
	arg0->unk1C4 = arg0->pos.y;
	arg0->unk1C8 = arg0->pos.z;
	arg0->unk1B8 = 0.2f;
	arg0->unk25C = -arg0->unk210;
	PickWarpPoint(arg0);
	arg0->unk260 = arg0->unk1CC;
	arg0->unk264 = arg0->unk1D0;
	arg0->unk268 = arg0->unk1D4;
	arg0->unk180 = 0x200;
	if ((s32)arg0->unk350 == 0) {
		arg0->unk258 = 9.0f;
	} else {
		arg0->unk258 = 9.0f;
	}
	arg0->unk254 = arg0->unk258;
}

void fn_8_AEE04(TEnemyParalysis* arg0)
{
	arg0->unk270 = 0.0f;
	arg0->unk26C = 0.0f;
	arg0->unk318 = 0;
	arg0->unk31C = 0;
	arg0->unk24C = NULL;
	arg0->unk248 = 0U;
	arg0->unk274 = 0;
	arg0->unk278 = 0;
	arg0->unk27C = -1;
	arg0->unk254 = 0.0f;
	arg0->unk258 = 0.0f;
	arg0->unk250 = 0;
	arg0->unk2B4 = 1.0f;
	arg0->unk2C0 = 1.5f;
	arg0->unk2BC = 1.5f;
	arg0->unk2B8 = 1.5f;
	arg0->unk2D4 = 0;
	arg0->unk2D8 = 0;
	arg0->unk288 = 0.0f;
	arg0->unk284 = 0.0f;
	arg0->unk280 = 0.0f;
	arg0->unk294 = 0.0f;
	arg0->unk290 = 0.0f;
	arg0->unk28C = 0.0f;
	arg0->unk2A0 = 0.0f;
	arg0->unk29C = 0.0f;
	arg0->unk298 = 0.0f;
	arg0->unk2AC = 0.0f;
	arg0->unk2A8 = 0.0f;
	arg0->unk2A4 = 0.0f;
	arg0->unk320 = NULL;
	arg0->unk324 = 0;
	arg0->unk328 = 0;
	arg0->unk2DC = 0U;
	arg0->unk2E0 = 0U;
	arg0->unk2F8 = 0;
	arg0->unk2FC = NULL;
	arg0->unk308 = 1.0f;
	arg0->unk304 = 1.0f;
	arg0->unk300 = 1.0f;
	arg0->unk310 = 1;
	arg0->unk314 = 1;
	arg0->unk2D0 = -1;
}

void* __dt__17TObjEnemyMagicianFv(void* arg0, s16 arg1)
{
	s32 temp_cr0_eq;
	void** temp_r3_2;
	void* temp_r3;

	if (arg0 != NULL) {
		M2C_FIELD(arg0, void***, 0x18) = __vt__17TObjEnemyMagician;
		M2C_FIELD(arg0, void**, 0xB4)  = (void*)((u8*)&__vt__17TObjEnemyMagician + 0x2C);
		if ((s32)M2C_FIELD(arg0, s32*, 0x2D0) != -1) {
			fn_800E1208(M2C_FIELD(arg0, s32*, 0x2D0), 0xF, 0);
			M2C_FIELD(arg0, s32*, 0x2D0) = -1;
		}
		temp_r3 = M2C_FIELD(arg0, void**, 0x24C);
		if (temp_r3 != NULL) {
			M2C_FIELD(temp_r3, u16*, 4)    = (u16)(M2C_FIELD(temp_r3, u16*, 4) | 1);
			M2C_FIELD(arg0, void**, 0x24C) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x320) != 0U) {
			fn_8005FD8C((void*)M2C_FIELD(arg0, u32*, 0x320), -1);
			M2C_FIELD(arg0, u32*, 0x320) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
			Close__13TEnemyIconManFv((void*)M2C_FIELD(arg0, u32*, 0x318));
			M2C_FIELD(arg0, u32*, 0x318) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
			Close__13TEnemyIconManFv((void*)M2C_FIELD(arg0, u32*, 0x31C));
			M2C_FIELD(arg0, u32*, 0x31C) = 0U;
		}
		temp_r3_2 = M2C_FIELD(arg0, void***, 0x248);
		if (temp_r3_2 != NULL) {
			if (temp_r3_2 != NULL) {
				((TSubDispatch*)temp_r3_2)->vslot2(1);
			}
			M2C_FIELD(arg0, void***, 0x248) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2FC) != 0U) {
			fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2FC));
			M2C_FIELD(arg0, u32*, 0x2FC) = 0U;
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

TEnemyParalysis* fn_8_AF05C(TEnemyParalysis* arg0, s16 arg1, void* arg2)
{
	void* strategy;
	TEnemyParalysis* paralysis;
	void* key;
	u32 setFlags;
	f32 temp_f0;

	if (arg1 != 0) {
		arg0->unk240 = (s32)((u8*)arg0 + 0x35C);
		arg0->unk244 = (u8*)arg0 + 0x35D;
	}
	fn_800A714C(arg0, arg2);
	__ct__10HAnimClassFv((HAnimClass*)&arg0->unk240);
	arg0->unk18 = (M2C_UNK*)__vt__17TObjEnemyMagician;
	arg0->unkB4 = (u8*)&__vt__17TObjEnemyMagician + 0x2C;
	arg0->unk0  = (M2C_UNK)lbl_8_data_168E0;
	arg0->unk1E = 0x360;
	fn_8_AEE04(arg0);
	fn_8_AEB80((TEnemyParalysis*)arg0);
	arg0->unk188 &= 0xFFFF3FFF;
	arg0->unk188 |= 0x8000;
	arg0->unk160 = 0.0f;
	arg0->unk15C = 0.0f;
	arg0->unk158 = 0.0f;
	arg0->unk188 &= 0xFFEFCFFF;
	arg0->unk188 |= 0x100000;
	arg0->unk188 |= 0x800000;
	arg0->unk188 |= 0x10;
	temp_f0      = arg0->unk254;
	arg0->unk1A4 = temp_f0;
	arg0->unk2E  = (s16)temp_f0;
	arg0->unk1A0 = 3.0f;
	arg0->unk2C  = 3;
	if ((void*)arg0->unk2FC != NULL) {
		fn_80150958((void*)arg0->unk2FC);
		arg0->unk2FC = NULL;
	}
	if ((void*)arg0->unkE8 != NULL) {
		fn_80150958((void*)arg0->unkE8);
		arg0->unkE8 = NULL;
	}
	arg0->unkE8  = fn_80150588(M2C_FIELD(&lbl_8_bss_19C8, void**, 0));
	arg0->unk2FC = fn_80150588(M2C_FIELD(&lbl_8_bss_19C8, void**, 4));
	fn_8_AE604((TEnemyParalysis*)arg0);
	setFlags = M2C_FIELD(arg0->unkB0, u32*, 0x18);
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
	    arg0->unkE8, ((setFlags & 0x1C0000) >> 18) + 8);
	arg0->unkE4 = (M2C_UNK*)lbl_8_data_16628;
	arg0->unkD4 = 0;
	if (OnEdit__10TObjSetObjFv(&arg0->unkB0) == 0) {
		Init__7C_COLLIFP8CCL_INFOiUc(&arg0->unk28, (M2C_UNK*)lbl_8_data_167FC, 1, 3);
		arg0->unk88 = arg0->pos.x;
		arg0->unk8C = arg0->pos.y;
		arg0->unk90 = arg0->pos.z;
	}
	arg0->unk130 = 12.0f;
	arg0->unk134 = 0.8f;
	arg0->unk248 = 0U;
	switch (arg0->unk350) {
		case 0:
			strategy = __nw__FUl(0x1C);
			if (strategy != NULL) {
				strategy = fn_8_B08F0(strategy);
			}
			arg0->unk248 = (u32)strategy;
			break;
		case 1:
			strategy = __nw__FUl(0x1C);
			if (strategy != NULL) {
				strategy = fn_8_B08F0(strategy);
			}
			arg0->unk248 = (u32)strategy;
			break;
	}
	if (arg0->unk248 != 0U) {
		fn_8_B0300((void*)arg0->unk248, arg0);
	}
	arg0->unk31C = Create__13TEnemyIconManF10eEnemyIcon(1);
	arg0->unk318 = Create__13TEnemyIconManF10eEnemyIcon(0);
	arg0->unk320 = fn_8006298C(0xD, &arg0->pos.x, &arg0->unk14C);
	paralysis    = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x74);
	if (paralysis != NULL) {
		paralysis
		    = __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(paralysis, lbl_8042C10C, NULL);
	}
	arg0->unk24C = paralysis;
	arg0->unk13C = 1;
	key          = __nw__FUl(0x20);
	if (key != NULL) {
		key = __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID(key, arg0, arg0->unk13C);
	}
	arg0->unk228 = (u32)key;
	return arg0;
}

/* CreateInstance. */
TEnemyParalysis* fn_8_AF390(void)
{
	TEnemyParalysis* magician = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x360);
	if (magician != NULL) {
		magician = fn_8_AF05C(magician, 1, lbl_8042C10C);
	}
	return magician;
}

/* The editor bounds EditOnChange clamps by reference. */
const f32 lbl_8_rodata_1B54 = 0.0f;
const f32 lbl_8_rodata_1B58 = 10000.0f;
const f32 lbl_8_rodata_1B5C = 0.0f;
const f32 lbl_8_rodata_1B60 = 10000.0f;
const s32 lbl_8_rodata_1B64 = 0;
const s32 lbl_8_rodata_1B68 = 10000;
const f32 lbl_8_rodata_1B6C = 0.0f;
const f32 lbl_8_rodata_1B70 = 10000.0f;

/* EditOnChange: clamp the edited fields, then name the chosen type. */
void TObjEnemyMagician::EditOnChange(SETDATA_PARAM* data)
{
	MagicianParams* p = data->params;

	p->type                     = Clamp(p->type, lbl_8_data_168C8, lbl_8_data_168C9);
	p->unused[0]                = 0;
	p->unused[1]                = 0;
	p->unused[2]                = 0;
	p->field04                  = Clamp(p->field04, lbl_8_rodata_1B54, lbl_8_rodata_1B58);
	p->field08                  = Clamp(p->field08, lbl_8_rodata_1B5C, lbl_8_rodata_1B60);
	p->field10                  = Clamp(p->field10, lbl_8_rodata_1B64, lbl_8_rodata_1B68);
	p->field14                  = Clamp(p->field14, lbl_8_rodata_1B6C, lbl_8_rodata_1B70);
	magicianObjectFieldNames[0] = lbl_8_data_168C0[p->type];
}

/* The magician's model archive. */
char lbl_8_data_16A30[] = "en_magician.one";

void magicianObjectUnload(void)
{
	lbl_8_bss_1A48 = 0;
	ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    0xA, lbl_8_data_16628);
	lbl_8_bss_1A18                      = 0;
	lbl_8_bss_19D0                      = 0U;
	M2C_FIELD(&lbl_8_bss_19C8, s32*, 4) = 0;
	M2C_FIELD(&lbl_8_bss_19C8, s32*, 0) = 0;
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != 0U)) {
		__ct__14TEnemyDataBaseFv();
	}
	Delete__14TEnemyDataBaseF14eEnemyDataBase(mpDataBase__14TEnemyDataBase, 0xA);
}

void magicianObjectLoad(void)
{
	u32 temp_r3;

	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != 0U)) {
		__ct__14TEnemyDataBaseFv();
	}
	Add__14TEnemyDataBaseF14eEnemyDataBasePc(mpDataBase__14TEnemyDataBase, 0xA, &lbl_8_data_16A30);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != 0U)) {
		__ct__14TEnemyDataBaseFv();
	}
	temp_r3 = SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(
	    mpDataBase__14TEnemyDataBase, 0xA, 5);
	if (temp_r3 != 0U) {
		objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(temp_r3, 6);
	} else {
		return;
	}
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != 0U)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_19C8, u32*, 0)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xA, 4);
	objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(
	    (void*)M2C_FIELD(&lbl_8_bss_19C8, u32*, 0));
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != 0U)) {
		__ct__14TEnemyDataBaseFv();
	}
	M2C_FIELD(&lbl_8_bss_19C8, u32*, 4)
	    = SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xA, 2);
	if (((u32)mpDataBase__14TEnemyDataBase == 0U) && (__nw__FUl(0x70) != 0U)) {
		__ct__14TEnemyDataBaseFv();
	}
	temp_r3
	    = SearchUVAnim__14TEnemyDataBaseF14eEnemyDataBaseUi(mpDataBase__14TEnemyDataBase, 0xA, 3);
	lbl_8_bss_19D0 = temp_r3;
	if (((u32)M2C_FIELD(&lbl_8_bss_19C8, u32*, 4) != 0U) && (temp_r3 != 0U)) {
		*lbl_8_bss_19D4 = temp_r3;
		SetClumpCustomFXTexture__FP7RpClumpP8UVFXInfo(
		    M2C_FIELD(&lbl_8_bss_19C8, u32*, 4), lbl_8_bss_19D4);
	}
	lbl_8_bss_1A18 = 0;
	LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
	    0xA, lbl_8_data_16628);
	lbl_8_bss_1A48 = (void*)objPointerReadFromClumpAnim__FPc(lbl_8_data_1692C);
}

void magicianObjectCreate(void)
{
	TEnemyParalysis* magician = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x360);
	if (magician != NULL) {
		fn_8_AF05C(magician, 1, lbl_8042C10C);
	}
}

void fn_8_AF86C(void* arg0, s32 arg1)
{
	M2C_FIELD(arg0, s32*, 0x14) = arg1;
	M2C_FIELD(arg0, s32*, 0x10) = 0;
	if (((TObjectDispatch*)arg0)->vslot5() != 0) {
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 2);
	}
	((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
		fn_800A31B8((void*)M2C_FIELD(arg0, s32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
	}
}
}
