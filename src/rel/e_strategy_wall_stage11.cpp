#include "types.h"

// The wall's strategy (TEnemyWall_Strategy in the PS2 symbols), its own translation unit
// in front of the wall object: its code touches only this unit's .data (its
// vtables and mode jump tables), it carries its own copies of the strategy
// base's constructor, destructor and virtuals, and its .rodata is only the
// unreferenced {0, 1.5, 0} vector every Stage 11 object unit opens with.

typedef s32 M2C_UNK;
typedef void (*TFunc)(void);

#define M2C_FIELD(base, type, offset) (*(type)((u8*)(u32)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

typedef struct RwFrame RwFrame;
typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef struct {
	s32 words[3];
} M2C_BLOCK12;
typedef struct {
	s32 words[4];
} M2C_BLOCK16;

typedef struct sAngle {
	s32 x;
	s32 y;
	s32 z;
} sAngle;

typedef struct sVec4i {
	s32 x;
	s32 y;
	s32 z;
	s32 w;
} sVec4i;

typedef struct sVec4 {
	f32 x;
	f32 y;
	f32 z;
	f32 w;
} sVec4;

typedef struct sWallObjParam {
	/* 0x00 */ f32 unk0;
	/* 0x04 */ f32 unk4;
	/* 0x08 */ f32 unk8;
	/* 0x0C */ s32 unkC;
	/* 0x10 */ s32 unk10;
	/* 0x14 */ s32 unk14;
	/* 0x18 */ f32 unk18;
	/* 0x1C */ f32 unk1C;
	/* 0x20 */ f32 unk20;
	/* 0x24 */ f32 unk24;
	/* 0x28 */ s32 unk28;
	/* 0x2C */ s32 unk2C;
} sWallObjParam;
typedef s32 RwOpCombineType;
typedef struct sParalysisParam {
	/* 0x00 */ u8 pad0[8];
	/* 0x08 */ RwV3d offset;
} sParalysisParam; /* size 0x14 */
extern double __fabs(double);

typedef struct TEnemyParalysis {
	/* 0x0 */ char pad0[4];
	/* 0x4 */ u16 unk4; /* inferred */
} TEnemyParalysis;      /* size >= 0x6 */

typedef struct TObject {
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
	/* 0x030 */ u16 unk30;        /* inferred */
	/* 0x032 */ char pad32[6];    /* maybe part of unk30[4]? */
	/* 0x038 */ void* unk38;      /* inferred */
	/* 0x03C */ char pad3C[0x4C]; /* maybe part of unk38[0x14]? */
	/* 0x088 */ f32 unk88;        /* inferred */
	/* 0x08C */ f32 unk8C;        /* inferred */
	/* 0x090 */ f32 unk90;        /* inferred */
	/* 0x094 */ s32 unk94;        /* inferred */
	/* 0x098 */ s32 unk98;        /* inferred */
	/* 0x09C */ s32 unk9C;        /* inferred */
	/* 0x0A0 */ char padA0[4];
	/* 0x0A4 */ f32 unkA4;         /* inferred */
	/* 0x0A8 */ f32 unkA8;         /* inferred */
	/* 0x0AC */ f32 unkAC;         /* inferred */
	/* 0x0B0 */ f32 unkB0;         /* inferred */
	/* 0x0B4 */ f32 unkB4;         /* inferred */
	/* 0x0B8 */ f32 unkB8;         /* inferred */
	/* 0x0BC */ s32 unkBC;         /* inferred */
	/* 0x0C0 */ s32 unkC0;         /* inferred */
	/* 0x0C4 */ s32 unkC4;         /* inferred */
	/* 0x0C8 */ f32 unkC8;         /* inferred */
	/* 0x0CC */ f32 unkCC;         /* inferred */
	/* 0x0D0 */ f32 unkD0;         /* inferred */
	/* 0x0D4 */ f32 unkD4;         /* inferred */
	/* 0x0D8 */ s32 unkD8;         /* inferred */
	/* 0x0DC */ s32 unkDC;         /* inferred */
	/* 0x0E0 */ void* unkE0;       /* inferred */
	/* 0x0E4 */ f32 unkE4;         /* inferred */
	/* 0x0E8 */ s32 unkE8;         /* inferred */
	/* 0x0EC */ u32 unkEC;         /* inferred */
	/* 0x0F0 */ f32 unkF0;         /* inferred */
	/* 0x0F4 */ f32 unkF4;         /* inferred */
	/* 0x0F8 */ char padF8[0xE];   /* maybe part of unkF4[4]? */
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
	/* 0x164 */ char pad164[0x10]; /* maybe part of unk160[5]? */
	/* 0x174 */ s32 unk174;        /* inferred */
	/* 0x178 */ char pad178[8];    /* maybe part of unk174[3]? */
	/* 0x180 */ s32 unk180;        /* inferred */
	/* 0x184 */ char pad184[4];
	/* 0x188 */ s32 unk188;       /* inferred */
	/* 0x18C */ s32 unk18C;       /* inferred */
	/* 0x190 */ char pad190[0xC]; /* maybe part of unk18C[4]? */
	/* 0x19C */ s32 unk19C;       /* inferred */
	/* 0x1A0 */ f32 unk1A0;       /* inferred */
	/* 0x1A4 */ f32 unk1A4;       /* inferred */
	/* 0x1A8 */ f32 unk1A8;       /* inferred */
	/* 0x1AC */ char pad1AC[0xC]; /* maybe part of unk1A8[4]? */
	/* 0x1B8 */ f32 unk1B8;       /* inferred */
	/* 0x1BC */ char pad1BC[4];
	/* 0x1C0 */ f32 unk1C0;     /* inferred */
	/* 0x1C4 */ f32 unk1C4;     /* inferred */
	/* 0x1C8 */ f32 unk1C8;     /* inferred */
	/* 0x1CC */ f32 unk1CC;     /* inferred */
	/* 0x1D0 */ f32 unk1D0;     /* inferred */
	/* 0x1D4 */ f32 unk1D4;     /* inferred */
	/* 0x1D8 */ f32 unk1D8;     /* inferred */
	/* 0x1DC */ f32 unk1DC;     /* inferred */
	/* 0x1E0 */ f32 unk1E0;     /* inferred */
	/* 0x1E4 */ M2C_UNK unk1E4; /* inferred */
	/* 0x1E8 */ char pad1E8[0x24];
	/* 0x20C */ f32 unk20C;     /* inferred */
	/* 0x210 */ f32 unk210;     /* inferred */
	/* 0x214 */ f32 unk214;     /* inferred */
	/* 0x218 */ char pad218[8]; /* maybe part of unk214[3]? */
	/* 0x220 */ f32 unk220;     /* inferred */
	/* 0x224 */ char pad224[4];
	/* 0x228 */ void** unk228;           /* inferred */
	/* 0x22C */ char pad22C[0x14];       /* maybe part of unk228[6]? */
	/* 0x240 */ void** unk240;           /* inferred */
	/* 0x244 */ TEnemyParalysis* unk244; /* inferred */
	/* 0x248 */ s32 unk248;              /* inferred */
	/* 0x24C */ f32 unk24C;              /* inferred */
	/* 0x250 */ char pad250[4];
	/* 0x254 */ f32 unk254;   /* inferred */
	/* 0x258 */ f32 unk258;   /* inferred */
	/* 0x25C */ f32 unk25C;   /* inferred */
	/* 0x260 */ f32 unk260;   /* inferred */
	/* 0x264 */ f32 unk264;   /* inferred */
	/* 0x268 */ u32 unk268;   /* inferred */
	/* 0x26C */ u32 unk26C;   /* inferred */
	/* 0x270 */ s32 unk270;   /* inferred */
	/* 0x274 */ s32 unk274;   /* inferred */
	/* 0x278 */ f32 unk278;   /* inferred */
	/* 0x27C */ f32 unk27C;   /* inferred */
	/* 0x280 */ s32 unk280;   /* inferred */
	/* 0x284 */ s32 unk284;   /* inferred */
	/* 0x288 */ s32 unk288;   /* inferred */
	/* 0x28C */ s32 unk28C;   /* inferred */
	/* 0x290 */ s32 unk290;   /* inferred */
	/* 0x294 */ s32 unk294;   /* inferred */
	/* 0x298 */ s32 unk298;   /* inferred */
	/* 0x29C */ s32 unk29C;   /* inferred */
	/* 0x2A0 */ u32 unk2A0;   /* inferred */
	/* 0x2A4 */ u32 unk2A4;   /* inferred */
	/* 0x2A8 */ u32 unk2A8;   /* inferred */
	/* 0x2AC */ u32 unk2AC;   /* inferred */
	/* 0x2B0 */ u32 unk2B0;   /* inferred */
	/* 0x2B4 */ u32 unk2B4;   /* inferred */
	/* 0x2B8 */ u32 unk2B8;   /* inferred */
	/* 0x2BC */ f32 unk2BC;   /* inferred */
	/* 0x2C0 */ u32 unk2C0;   /* inferred */
	/* 0x2C4 */ u32 unk2C4;   /* inferred */
	/* 0x2C8 */ void* unk2C8; /* inferred */
	/* 0x2CC */ void* unk2CC; /* inferred */
	/* 0x2D0 */ void* unk2D0; /* inferred */
	/* 0x2D4 */ f32 unk2D4;   /* inferred */
	/* 0x2D8 */ f32 unk2D8;   /* inferred */
	/* 0x2DC */ f32 unk2DC;   /* inferred */
	/* 0x2E0 */ f32 unk2E0;   /* inferred */
	/* 0x2E4 */ f32 unk2E4;   /* inferred */
	/* 0x2E8 */ f32 unk2E8;   /* inferred */
	/* 0x2EC */ f32 unk2EC;   /* inferred */
	/* 0x2F0 */ f32 unk2F0;   /* inferred */
	/* 0x2F4 */ f32 unk2F4;   /* inferred */
	/* 0x2F8 */ f32 unk2F8;   /* inferred */
	/* 0x2FC */ f32 unk2FC;   /* inferred */
	/* 0x300 */ f32 unk300;   /* inferred */
	/* 0x304 */ s32 unk304;   /* inferred */
	/* 0x308 */ s32 unk308;   /* inferred */
	/* 0x30C */ s32 unk30C;   /* inferred */
	/* 0x310 */ f32 unk310;   /* inferred */
	/* 0x314 */ f32 unk314;   /* inferred */
} TObject;                    /* size >= 0x318 */

/* Dispatch view of TObject's vtable. The handler at vtable offset 0x10 is
 * reached through genuine virtual dispatch in retail: the target loads the
 * vtable through the already-materialised `this` in r3 and keeps the slot in
 * r12, which manual vtable indexing does not reproduce. Two implicit
 * destructor slots plus the two placeholders below put Release at slot 4. */
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

class TObjectDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void Release(s32, s32);
	virtual s32 vslot5();
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
	virtual void Slot40(s32);
	virtual void Slot44(s32);
	virtual void Slot48(s32);
	virtual void Slot4C(s32);
	virtual void Slot50(s32);
	virtual void Slot54(s32);
};

extern "C" {
void Debug__7TObjectFv(void);
void Error__7TObjectFPc(void);
void ImmAftSetRaster__7TObjectFv(void);
void PDisp__7TObjectFv(void);
void Render__7TObjectFv(void);
void fn_800A2C6C(void);
void fn_800A3148(void);
void fn_800A314C(void);
void fn_800A31A0(void);
void fn_800A321C(void);
void fn_800A324C(void);
void fn_800A327C(void);
void fn_800A3D6C(void);
void fn_800A6D58(void);
void fn_800A6D60(void);
void fn_800A6DD4(void);
void fn_800A6EA8(void);
void fn_800A6F38(void);
void fn_8_33D90(void);
void fn_8_33D94(void);
void fn_8_33D98(void);
void fn_8_33DA0(void);
void fn_8_33DA4(void);
void fn_8_BDA48(void);

M2C_UNK SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(
    TEnemyParalysis*, const RwV3d*, const void*); /* extern */
M2C_UNK Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(
    TEnemyParalysis*, RwFrame*, RwOpCombineType); /* extern */
void* __ct__10HAnimClassFv(void*);                /* extern */
TObject* __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(
    TEnemyParalysis*, void*, sParalysisParam*);                                         /* extern */
void* __ct__15sParalysisParamFv(void*);                                                 /* extern */
void* __ct__7TObjectFP7TObject(void*, void*);                                           /* extern */
M2C_UNK __dl__FPv(void* arg0);                                                          /* extern */
void* __dt__10HAnimClassFv(void*, s32);                                                 /* extern */
void* __dt__7TObjectFv(void*, s32);                                                     /* extern */
M2C_UNK __register_global_object(void*, void*, void*);                                  /* extern */
M2C_UNK __dt__7C_COLLIFv(void*, M2C_UNK);                                               /* extern */
s32 fn_80017800(TObject*);                                                              /* extern */
M2C_UNK Free__9THeapCtrlFPv(s32, TObject*);                                             /* extern */
TObject* Malloc__9THeapCtrlFUi(s32, M2C_UNK);                                           /* extern */
u32 fn_800209C8(void*, M2C_UNK);                                                        /* extern */
u32 fn_80020BD8(void*, M2C_UNK);                                                        /* extern */
M2C_UNK CalcRange__7C_COLLIFv(void*);                                                   /* extern */
M2C_UNK fn_80021824(M2C_UNK*);                                                          /* extern */
M2C_UNK Entry__7C_COLLIFv(M2C_UNK*);                                                    /* extern */
M2C_UNK ClearInfo__7C_COLLIFv(void*);                                                   /* extern */
M2C_UNK Init__7C_COLLIFP8CCL_INFOiUc(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);             /* extern */
M2C_UNK __ct__7C_COLLIFv(M2C_UNK*);                                                     /* extern */
M2C_UNK fn_8004D5F4(s32, f32, M2C_UNK);                                                 /* extern */
void** __nw__FUl(M2C_UNK);                                                              /* extern */
s32 OnEdit__10TObjSetObjFv(f32*);                                                       /* extern */
M2C_UNK SetEnd__10TObjSetObjFv(void*);                                                  /* extern */
M2C_UNK SetClumpCustomFXTexture__FP7RpClumpP8UVFXInfo(void*, u32*);                     /* extern */
M2C_UNK objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(void*, s32); /* extern */
s32 objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(void*, M2C_UNK);      /* extern */
M2C_UNK objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(void*);                     /* extern */
M2C_UNK objRpClumpForAllMaterialsToChangeMaterialColor__FP7RpClumpP10RwRGBAReal(
    s32*, s32*); /* extern */
M2C_UNK objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(
    u32, M2C_UNK);                                                           /* extern */
M2C_UNK fn_8006298C(M2C_UNK, f32*, s32*);                                    /* extern */
s32 fn_800A2D50();                                                           /* extern */
M2C_UNK fn_800A31B8(void*, s32);                                             /* extern */
s32 fn_800A3684();                                                           /* extern */
M2C_UNK fn_800A3D48(TObject*);                                               /* extern */
s32 fn_800A3ED4(void*);                                                      /* extern */
M2C_UNK fn_800A3F60(void*);                                                  /* extern */
M2C_UNK fn_800A4668(TObject*);                                               /* extern */
M2C_UNK fn_800A4A8C(TObject*, f32);                                          /* extern */
s32 fn_800A5888(TObject*, const f32*, f32);                                  /* extern */
s32 fn_800A5998(TObject*);                                                   /* extern */
s32 fn_800A5A54(TObject*);                                                   /* extern */
f32 fn_800A5AC0(TObject*);                                                   /* extern */
M2C_UNK fn_800A5B34(TObject*);                                               /* extern */
M2C_UNK fn_800A5C6C(TObject*, M2C_UNK);                                      /* extern */
s32 fn_800A6334(void*);                                                      /* extern */
M2C_UNK fn_800A7088(TObject*, M2C_UNK);                                      /* extern */
M2C_UNK fn_800A714C(TObject*, TObject*);                                     /* extern */
M2C_UNK fn_800B4A38(u32, M2C_UNK, f32*, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK fn_800B7514(f32*, s32*, f32*, f32);                                  /* extern */
M2C_UNK fn_800B7820();                                                       /* extern */
M2C_UNK fn_800B7864(M2C_UNK);                                                /* extern */
f32 Distance2P2P__FPC5RwV3dPC5RwV3d(void*, s32);                             /* extern */
f32 DistanceP2P__FPC5RwV3dPC5RwV3d(f32*, M2C_UNK*);                          /* extern */
s32 AdjustAngle__Fiii(s32, s32, s32);                                        /* extern */
f32 fn_800D7B00(u32);                                                        /* extern */
f32 GetShadowPos__FP5RwV3dP6sAnglei(f32*, s32*, M2C_UNK);                    /* extern */
void** __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID(void**, TObject*, s32);      /* extern */
M2C_UNK ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*); /* extern */
M2C_UNK LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*);                                                             /* extern */
u32 SearchUVAnim__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK);       /* extern */
u32 SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK); /* extern */
u32 SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK Delete__14TEnemyDataBaseF14eEnemyDataBase(u32, M2C_UNK);                    /* extern */
M2C_UNK Add__14TEnemyDataBaseF14eEnemyDataBasePc(u32, M2C_UNK, M2C_UNK*);           /* extern */
M2C_UNK __ct__14TEnemyDataBaseFv();                                                 /* extern */
M2C_UNK SetEffectCrash3D_R__FP7TObjectP5RwV3dP6sAngleP5RwV3dP5RwV3dffisP7RpClump(
    s32, f32*, s32*, s32*, void*, f32, f32, s32, s16, u32);                 /* extern */
s32 GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(void*, const f32*, f32); /* extern */
s32 IsOn__13TEnemyIconManFv(u32);                                           /* extern */
M2C_UNK Close__13TEnemyIconManFv(void*);                                    /* extern */
M2C_UNK Change__13TEnemyIconManF10eEnemyIcon(u32, s32);                     /* extern */
M2C_UNK Off__13TEnemyIconManFv(u32);                                        /* extern */
M2C_UNK On__13TEnemyIconManFffi(u32, f32, f32, s32);                        /* extern */
M2C_UNK On__13TEnemyIconManFff(u32, f32, f32);                              /* extern */
M2C_UNK SetPos__13TEnemyIconManFPC5RwV3dPC5RwV3d(u32, void*, void*);        /* extern */
u32 Create__13TEnemyIconManF10eEnemyIcon(M2C_UNK);                          /* extern */
M2C_UNK SetLightNum__7nRenderFUi(s32);                                      /* extern */
M2C_UNK SetRenderStateForBlendAdd__7nRenderFv();                            /* extern */
M2C_UNK LoadRenderState__7nRenderFv();                                      /* extern */
M2C_UNK SaveRenderState__7nRenderFv();                                      /* extern */
M2C_UNK PreDisp__16TEnemyMatTextureFi(M2C_UNK*, s32);                       /* extern */
M2C_UNK End__16TEnemyMatTextureFv(M2C_UNK*);                                /* extern */
M2C_UNK Init__16TEnemyMatTextureFP15RwTexDictionaryP7RpClumpP10sEnTexturei(
    M2C_UNK*, s32, void*, M2C_UNK*, M2C_UNK);                         /* extern */
M2C_UNK __ct__16TEnemyMatTextureFv(M2C_UNK*);                         /* extern */
M2C_UNK Create__15TEnemyShockWaveFPC10sShockWave(f32*);               /* extern */
M2C_UNK __ct__10sShockWaveFv(f32*);                                   /* extern */
M2C_UNK fn_8011B844(u32, const f32*, f32);                            /* extern */
M2C_UNK fn_8011C0E8(u32);                                             /* extern */
M2C_UNK ParalyzeEnemy__14TEnemyScoreManFi(u32, s32);                  /* extern */
M2C_UNK DestroyEnemy__14TEnemyScoreManFi(u32, s32);                   /* extern */
M2C_UNK AddScore__14TEnemyScoreManFii(u32, s32, M2C_UNK);             /* extern */
M2C_UNK CreateInstance__14TEnemyScoreManFv();                         /* extern */
M2C_UNK EntryEx__18TEnemyPowerCoreManFPC5RwV3di(void*, void*, s32);   /* extern */
void* GetInstance__18TEnemyPowerCoreManFv();                          /* extern */
M2C_UNK DecreaseTimer__7nSystemFRi(s32*);                             /* extern */
M2C_UNK IncreaseTimer__7nSystemFRi(s32*);                             /* extern */
M2C_UNK fn_8014FF2C(s32*);                                            /* extern */
M2C_UNK fn_8014FFBC(void*, M2C_UNK*, u32*);                           /* extern */
void* fn_80150588(void*);                                             /* extern */
M2C_UNK fn_80150958(void*);                                           /* extern */
M2C_UNK fn_80196050(M2C_UNK*, void*, M2C_UNK);                        /* extern */
M2C_UNK fn_801990E0(f32*, f32*, f32);                                 /* extern */
M2C_UNK fn_8019941C(f32*, f32*, M2C_UNK, M2C_UNK*);                   /* extern */
s32 fn_8019CE34(s32, f32*);                                           /* extern */
M2C_UNK* fn_8019E8EC(u32);                                            /* extern */
M2C_UNK fn_8019EB94(RwFrame*, void*, M2C_UNK);                        /* extern */
M2C_UNK fn_8019ECCC(s32, M2C_UNK*, M2C_UNK);                          /* extern */
M2C_UNK fn_8019ED68(RwFrame*, M2C_UNK*, f32, s32);                    /* extern */
M2C_UNK CreateItemBox__8nItemBoxFP5RwV3d(s32);                        /* extern */
M2C_UNK EditOnChange__22TObjColliCommunicationFP13SETDATA_PARAM(s32); /* extern */
void fn_8_B7C50(TObject* arg0, void* arg1);                           /* static */
void* fn_8_B81B0(void* arg0);                                         /* static */
void fn_8_B9904(TObject* arg0, s32 arg1);                             /* static */
s32 fn_8_B9BA0(void* arg0);                                           /* static */
s32 fn_8_B9BBC(void* arg0);                                           /* static */
s32 fn_8_B9CD4(void* arg0);                                           /* static */
s32 fn_8_B9E40(void* arg0);                                           /* static */
void fn_8_BA8E0(TObject* arg0, s32 arg1);                             /* static */
void fn_8_BAF00(TObject* arg0, s32 arg1);                             /* static */
void fn_8_BB294(TObject* arg0, s32 arg1);                             /* static */
void fn_8_BB5E4(TObject* arg0, s32 arg1);                             /* static */
void fn_8_BBF90(TObject* arg0);                                       /* static */
void fn_8_BC2CC(TObject* arg0);                                       /* static */
void fn_8_BCB60(TObject* arg0);                                       /* static */
void fn_8_BCD58(TObject* arg0);                                       /* static */
TObject* fn_8_BCF88(TObject* arg0, TObject* arg1);                    /* static */
void wallObjectCreate();                                              /* static */
void wallObjectLoad();                                                /* static */
void wallObjectUnload();                                              /* static */
extern M2C_UNK SetAtomicCustomFXData__FP8RpAtomicPv;
extern M2C_UNK __dt__16TEnemyMatTextureFv;
extern M2C_UNK AxisX;
extern M2C_UNK AxisY;
extern M2C_UNK AxisZ;
extern M2C_UNK lbl_8029C310;
extern M2C_UNK lbl_802AD070;
extern M2C_UNK lbl_802AD090;
extern M2C_UNK lbl_80303DC8;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern M2C_UNK lbl_8042C1A4;
extern s32 lbl_8042C1F8;
extern s32 lbl_8042C208;
extern s32 lbl_8042C2A0;
extern u32 lbl_8042C388;
extern u32 mpDataBase__14TEnemyDataBase;
extern u32 EnemyScoreMan__14TEnemyScoreMan;
extern s32* lbl_8042C9A4;
extern const f32 lbl_8_rodata_1CB8[3];
extern const f32 lbl_8_rodata_1CC4[3];
extern const f32 lbl_8_rodata_1CD0[3];
extern const f32 lbl_8_rodata_1CDC[3];
extern const f32 lbl_8_rodata_1CE8[3];
extern const f32 lbl_8_rodata_1CF4[3];
extern const f32 lbl_8_rodata_1D00[4];
extern const f32 lbl_8_rodata_1D10[3];
extern const f32 lbl_8_rodata_1D1C[4];
extern const f32 lbl_8_rodata_1D2C[4];
extern const f32 lbl_8_rodata_1D3C[3];
extern const f32 lbl_8_rodata_1D48[3];
extern const f32 lbl_8_rodata_1D54[1];
extern const f32 lbl_8_rodata_1D58[1];
extern const f32 lbl_8_rodata_1D5C[1];
extern const f32 lbl_8_rodata_1D60[1];
extern const f32 lbl_8_rodata_1D64[1];
extern const f32 lbl_8_rodata_1D68[1];
extern const f32 lbl_8_rodata_1D6C[1];
extern const f32 lbl_8_rodata_1D70[1];
extern const f32 lbl_8_rodata_1D74[1];
extern const f32 lbl_8_rodata_1D78[1];
extern const f32 lbl_8_rodata_1D7C[1];
extern const f32 lbl_8_rodata_1D80[1];
extern const f32 lbl_8_rodata_1D84[1];
extern const f32 lbl_8_rodata_1D88[1];
extern const f32 lbl_8_rodata_1D98[1];
extern const f32 lbl_8_rodata_1D9C[1];
extern const f32 lbl_8_rodata_1DA0[1];
extern const f32 lbl_8_rodata_1DA4[1];
extern const f32 lbl_8_rodata_1DA8[1];
extern const f32 lbl_8_rodata_1DAC[1];
extern const f32 lbl_8_rodata_1DB0[1];
extern const f32 lbl_8_rodata_1DB4[1];
extern const f32 lbl_8_rodata_1DB8[1];
extern const f32 lbl_8_rodata_1DBC[1];
extern const f32 lbl_8_rodata_1DC0[1];
extern const f32 lbl_8_rodata_1DC4[1];
extern const f32 lbl_8_rodata_1DC8[1];
extern const f32 lbl_8_rodata_1DCC[1];
extern const f32 lbl_8_rodata_1DD0[1];
extern const f32 lbl_8_rodata_1DD4[1];
extern const f32 lbl_8_rodata_1DD8[1];
extern const f32 lbl_8_rodata_1DDC[1];
extern const f32 lbl_8_rodata_1DE0[1];
extern const f32 lbl_8_rodata_1DE4[1];
extern const f32 lbl_8_rodata_1DE8[1];
extern const f32 lbl_8_rodata_1DEC[1];
extern const f32 lbl_8_rodata_1DF0[1];
extern const f32 lbl_8_rodata_1DF4[1];
extern const f32 lbl_8_rodata_1DF8[1];
extern const f32 lbl_8_rodata_1DFC[1];
extern const f32 lbl_8_rodata_1E00[1];
extern const f32 lbl_8_rodata_1E04[1];
extern const f32 lbl_8_rodata_1E08[1];
extern const f32 lbl_8_rodata_1E0C[1];
extern const f32 lbl_8_rodata_1E10[1];
extern const s32 lbl_8_rodata_1E14[1];
extern const s32 lbl_8_rodata_1E18[1];
extern const f32 lbl_8_rodata_1E1C[1];
extern const f32 lbl_8_rodata_1E20[1];
/* forward declarations for the dispatch tables below */
void fn_8_B7218(void* arg0, s32 arg1);
void fn_8_B72D0(void* arg0, s32 arg1);
void fn_8_B7388(void* arg0, s32 arg1);
void fn_8_B7498(void* arg0, s32 arg1);
void fn_8_B7550(void* arg0, s32 arg1);
void fn_8_B7608(void* arg0, s32 arg1);
void fn_8_B76FC(void* arg0, s32 arg1);
void fn_8_B771C(void* arg0, s32 arg1);
void fn_8_B77D4(void* arg0, s32 arg1);
void fn_8_B788C(void* arg0, s32 arg1);
void fn_8_B78AC(void* arg0, s32 arg1);
void fn_8_B78CC(void* arg0, s32 arg1);
void fn_8_B7AA4(void* arg0, s32 arg1);
void fn_8_B7B5C(void* arg0, s32 arg1);
void fn_8_B7B7C(void* arg0, s32 arg1);
void fn_8_B7B9C(void* arg0, s32 arg1);
s32 fn_8_B7D24(void* arg0);
void fn_8_B7F94(void** arg0, u32 arg1, s32 arg2);
M2C_UNK** fn_8_B814C(M2C_UNK** arg0, s16 arg1);
M2C_UNK** fn_8_B81E4(M2C_UNK** arg0, s16 arg1);
void fn_8_B8234(void* arg0, void* arg1);
void fn_8_B82CC(void* arg0);
void fn_8_B8504(void* arg0);
void fn_8_B8970(TObject* arg0);
TObject* fn_8_B8F34(TObject* arg0, s16 arg1);
void fn_8_B93A4(void* arg0);
void fn_8_B9548(void* arg0, s32 arg1);
void fn_8_B956C(void* arg0);
void fn_8_B97C0(void* arg0, void* arg1);
void fn_8_B986C(void* arg0);
void fn_8_B9B20(void* arg0);
void fn_8_BA0D4(void* arg0);
void fn_8_BA1EC(void* arg0);
void fn_8_BA2B0(void* arg0);
void fn_8_BA370(TObject* arg0);
void fn_8_BA3A4(TObject* arg0);
void fn_8_BBAD0(void* arg0, u32 arg1, s32 arg2);
TObject* fn_8_BCE1C(TObject* arg0, s16 arg1);
void fn_8_BD380(void* arg0, void* arg1);

static TFunc lbl_8_data_172E0[22] = {
	NULL,
	NULL,
	(TFunc)fn_8_B814C,
	(TFunc)fn_8_B8234,
	(TFunc)fn_8_B7F94,
	(TFunc)fn_8_B7D24,
	(TFunc)fn_8_B7B9C,
	(TFunc)fn_8_B7B7C,
	(TFunc)fn_8_B7B5C,
	(TFunc)fn_8_B7AA4,
	(TFunc)fn_8_B78CC,
	(TFunc)fn_8_B78AC,
	(TFunc)fn_8_B788C,
	(TFunc)fn_8_B77D4,
	(TFunc)fn_8_B771C,
	(TFunc)fn_8_B76FC,
	(TFunc)fn_8_B7608,
	(TFunc)fn_8_B7550,
	(TFunc)fn_8_B7498,
	(TFunc)fn_8_B7388,
	(TFunc)fn_8_B72D0,
	(TFunc)fn_8_B7218,
};
/* The strategy unit's .rodata holds only the {0, 1.5, 0} vector that heads
 * every enemy unit's .rodata; nothing here references it. */
#pragma force_active on
static const f32 strategyRodataHead[3] = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

void fn_8_B7218(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x78;
			M2C_FIELD(arg0, s32*, 0x10) = 0x35;
			break;
		case 1:
			DecreaseTimer__7nSystemFRi((M2C_UNK*)((u8*)((u32)arg0 + 0x18)));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B72D0(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x168;
			M2C_FIELD(arg0, s32*, 0x10) = 0x34;
			break;
		case 1:
			DecreaseTimer__7nSystemFRi((M2C_UNK*)((u8*)((u32)arg0 + 0x18)));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xF;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B7388(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x12C;
			M2C_FIELD(arg0, s32*, 0x10) = 0x33;
			break;
		case 1:
			DecreaseTimer__7nSystemFRi((M2C_UNK*)((u8*)((u32)arg0 + 0x18)));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			if (fn_8_B9BA0(M2C_FIELD(arg0, void**, 0x14)) != 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xE;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B7498(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x12C;
			M2C_FIELD(arg0, s32*, 0x10) = 0x32;
			break;
		case 1:
			DecreaseTimer__7nSystemFRi((M2C_UNK*)((u8*)((u32)arg0 + 0x18)));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xD;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B7550(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x55;
			M2C_FIELD(arg0, s32*, 0x10) = 0x31;
			break;
		case 1:
			DecreaseTimer__7nSystemFRi((M2C_UNK*)((u8*)((u32)arg0 + 0x18)));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xA;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B7608(void* arg0, s32 arg1)
{
	s32 temp_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x30;
			break;
		case 1:
			temp_r4 = M2C_FIELD(arg0, s32*, 0x1C);
			if (temp_r4 < 3) {
				M2C_FIELD(arg0, s32*, 0x1C) = (s32)(temp_r4 + 1);
				M2C_FIELD(arg0, s32*, 8)    = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xB;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				return;
			}
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 0;
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B76FC(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x25;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B771C(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			break;
		case 1:
			DecreaseTimer__7nSystemFRi((M2C_UNK*)((u8*)((u32)arg0 + 0x18)));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B77D4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x1A;
			break;
		case 1:
			IncreaseTimer__7nSystemFRi((M2C_UNK*)((u8*)((u32)arg0 + 0x18)));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) > 1) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 4;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B788C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x20;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B78AC(void* arg0, s32 arg1)
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

void fn_8_B78CC(void* arg0, s32 arg1)
{
	s32 temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18)
			    = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x30C);
			M2C_FIELD(arg0, s32*, 0x10) = 0x2C;
			break;
		case 1:
			if (((void*)M2C_FIELD(arg0, void**, 0x14) != NULL)
			    && (fn_800A6334(M2C_FIELD(arg0, void**, 0x14)) == 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				return;
			}
			DecreaseTimer__7nSystemFRi((M2C_UNK*)((u8*)((u32)arg0 + 0x18)));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				temp_r3 = fn_8_B9CD4(M2C_FIELD(arg0, void**, 0x14));
				if (temp_r3 == 1) {
					M2C_FIELD(arg0, s32*, 0x1C) = 0;
					M2C_FIELD(arg0, s32*, 8)    = (s32)M2C_FIELD(arg0, s32*, 4);
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 0xA;
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
					return;
				}
				if (temp_r3 == 2) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 0xC;
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
					return;
				}
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 4;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			} else {
				return;
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B7AA4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x78;
			M2C_FIELD(arg0, s32*, 0x10) = 8;
			break;
		case 1:
			DecreaseTimer__7nSystemFRi((M2C_UNK*)((u8*)((u32)arg0 + 0x18)));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B7B5C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 7;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B7B7C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B7B9C(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			break;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_B9E40((void*)M2C_FIELD(arg0, u32*, 0x14)) != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 4;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B7C50(TObject* arg0, void* arg1)
{
	void* temp_r4;
	s32 temp_r0;

	arg0->unk14 = arg1;
	temp_r4     = arg0->unk14;
	if (temp_r4 != NULL) {
		temp_r0 = M2C_FIELD(temp_r4, s32*, 0x308);
		switch (temp_r0) { /* irregular */
			case 0:
				arg0->unkC  = 0;
				arg0->unk10 = 0;
				arg0->unk4  = 0;
				((TObjectDispatch*)arg0)->Release((s32)arg0->unk4, 0);
				if ((s32)arg0->unk10 != 0) {
					fn_800A31B8(arg0->unk14, (s32)arg0->unk10);
					return;
				}
				break;
			case 1:
				arg0->unkC  = 2;
				arg0->unk10 = 0;
				arg0->unk4  = 2;
				((TObjectDispatch*)arg0)->Release((s32)arg0->unk4, 0);
				if ((s32)arg0->unk10 != 0) {
					fn_800A31B8(arg0->unk14, (s32)arg0->unk10);
				}
				break;
		}
	}
}

s32 fn_8_B7D24(void* arg0)
{
	s32 var_r3;
	void* temp_r3;
	s32 temp_r0;
	s32 temp_r0_2;

	fn_8_B9BBC(M2C_FIELD(arg0, void**, 0x14));
	if ((fn_800A3ED4(M2C_FIELD(arg0, void**, 0x14)) != 0)
	    && ((s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x19C) != 0x1D)) {
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 5;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	temp_r3 = M2C_FIELD(arg0, void**, 0x14);
	temp_r0 = M2C_FIELD(temp_r3, s32*, 0x248);
	if (temp_r0 != 0) {
		var_r3 = 0;
		switch (temp_r0) { /* irregular */
			case 1:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 2:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 8:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x248) = 0;
		return var_r3;
	}
	if (((s32)M2C_FIELD(temp_r3, s32*, 0x304) == 0)
	    && ((u32)(M2C_FIELD(temp_r3, s32*, 0x18C) & 0x2000) != 0)) {
		temp_r0_2 = M2C_FIELD(temp_r3, s32*, 0x19C);
		switch (temp_r0_2) {
			case 1:
			case 2:
			case 0x2C:
				break;
			default:
				goto block_22;
		}
	block_21:
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 8;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	block_22:
		return 0;
	}
	return 0;
}

void fn_8_B7F94(void** arg0, u32 arg1, s32 arg2)
{
	switch (arg1) {
		case 0:
			((TStateDispatch*)arg0)->Slot18(arg2);
			return;
		case 1:
			((TStateDispatch*)arg0)->Slot1C(arg2);
			return;
		case 2:
			((TStateDispatch*)arg0)->Slot20(arg2);
			return;
		case 3:
			((TStateDispatch*)arg0)->Slot24(arg2);
			return;
		case 4:
			((TStateDispatch*)arg0)->Slot28(arg2);
			return;
		case 5:
			((TStateDispatch*)arg0)->Slot2C(arg2);
			return;
		case 6:
			((TStateDispatch*)arg0)->Slot30(arg2);
			return;
		case 7:
			((TStateDispatch*)arg0)->Slot34(arg2);
			return;
		case 8:
			((TStateDispatch*)arg0)->Slot38(arg2);
			return;
		case 9:
			((TStateDispatch*)arg0)->Slot3C(arg2);
			return;
		case 11:
			((TStateDispatch*)arg0)->Slot44(arg2);
			return;
		case 10:
			((TStateDispatch*)arg0)->Slot40(arg2);
			return;
		case 12:
			((TStateDispatch*)arg0)->Slot48(arg2);
			return;
		case 13:
			((TStateDispatch*)arg0)->Slot4C(arg2);
			return;
		case 14:
			((TStateDispatch*)arg0)->Slot50(arg2);
			return;
		case 15:
			((TStateDispatch*)arg0)->Slot54(arg2);
			/* fallthrough */
		default:
			return;
	}
}

static TFunc lbl_8_data_17378[6] = {
	NULL,
	NULL,
	(TFunc)fn_8_B81E4,
	(TFunc)fn_8_B8234,
	NULL,
	NULL,
};
/* The state-machine base's destructor body, inlined into the derived
 * destructor: it re-tests the same pointer and so reuses the first compare. */
static inline void DestroyStateBase(M2C_UNK** self)
{
	if (self != NULL) {
		*self = (M2C_UNK*)lbl_8_data_17378;
	}
}

M2C_UNK** fn_8_B814C(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_172E0;
		DestroyStateBase(arg0);
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void* fn_8_B81B0(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_17378;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_172E0;
	return arg0;
}

M2C_UNK** fn_8_B81E4(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_17378;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_B8234(void* arg0, void* arg1)
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
}
