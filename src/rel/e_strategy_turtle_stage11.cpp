#include "types.h"

// The turtle's strategy (TEnemyTurtle_Strategy in the PS2 symbols), its own translation unit
// in front of the turtle object: its code touches only this unit's .data (its
// vtables and mode jump tables), it carries its own copies of the strategy
// base's constructor, destructor and virtuals, and its .rodata is only the
// unreferenced {0, 1.5, 0} vector every Stage 11 object unit opens with.

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
} TObject;                  /* size >= 0x320 */

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

extern "C" {
void Debug__7TObjectFv(void);
void Error__7TObjectFPc(void);
void ImmAftSetRaster__7TObjectFv(void);
void PDisp__7TObjectFv(void);
void Render__7TObjectFv(void);
void fn_800A2C6C(void);
void fn_800A2F88(void);
void fn_800A3148(void);
void fn_800A314C(void);
void fn_800A31A0(void);
void fn_800A321C(void);
void fn_800A324C(void);
void fn_800A327C(void);
void fn_800A3D6C(void);
void fn_800A6D60(void);
void fn_800A6DD4(void);
void fn_800A6EA8(void);
void fn_800A6F38(void);
void fn_8_33D90(void);
void fn_8_33D94(void);
void fn_8_33D98(void);
void fn_8_33DA0(void);
void fn_8_33DA4(void);
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
M2C_UNK fn_800A3D48(TObject*);                                               /* extern */
s32 fn_800A3E10(TObjEffTornadoSpin*, TObjEffTornadoSpin*);                   /* extern */
s32 fn_800A3ED4(void*);                                                      /* extern */
M2C_UNK fn_800A4630(TObjEffTornadoSpin*, s32);                               /* extern */
M2C_UNK fn_800A4668(void*);                                                  /* extern */
M2C_UNK fn_800A4A8C(void*, M2C_UNK*, f32);                                   /* extern */
s32 fn_800A5888(void*, M2C_UNK*, f32);                                       /* extern */
s32 fn_800A5998(void*);                                                      /* extern */
s32 fn_800A5A54(void*);                                                      /* extern */
f32 fn_800A5AC0();                                                           /* extern */
M2C_UNK fn_800A5B34(TObject*);                                               /* extern */
M2C_UNK fn_800A5B50(void*, M2C_UNK);                                         /* extern */
M2C_UNK fn_800A5C6C(void*, M2C_UNK);                                         /* extern */
s32 fn_800A6334(void*);                                                      /* extern */
M2C_UNK fn_800A7088(void*, M2C_UNK);                                         /* extern */
M2C_UNK fn_800A714C(TObject*, TObject*);                                     /* extern */
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
void** __ct__11ObjEnemyKeyFP9TObjEnemy8ENEMY_ID(void**, TObject*, s32);      /* extern */
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
    s32, f32*, s32*, s32*, void*, f32, f32, s32, s16, u32);               /* extern */
s32 GetTeamNoFromPlayerNum__13nSearchPlayerFi(s32);                       /* extern */
s32 GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(void*, M2C_UNK*, f32); /* extern */
s32 IsOn__13TEnemyIconManFv(u32);                                         /* extern */
M2C_UNK Close__13TEnemyIconManFv(void*);                                  /* extern */
M2C_UNK Change__13TEnemyIconManF10eEnemyIcon(u32, s32);                   /* extern */
M2C_UNK Off__13TEnemyIconManFv(u32);                                      /* extern */
M2C_UNK On__13TEnemyIconManFffi(u32, f32, f32, s32);                      /* extern */
M2C_UNK On__13TEnemyIconManFff(u32, f32, f32);                            /* extern */
M2C_UNK SetPos__13TEnemyIconManFPC5RwV3dPC5RwV3d(u32, void*, void*);      /* extern */
s32 Create__13TEnemyIconManF10eEnemyIcon(M2C_UNK);                        /* extern */
M2C_UNK SetLightNum__7nRenderFUi();                                       /* extern */
M2C_UNK PreDisp__16TEnemyMatTextureFi(M2C_UNK*, s32);                     /* extern */
M2C_UNK End__16TEnemyMatTextureFv(M2C_UNK*);                              /* extern */
M2C_UNK Init__16TEnemyMatTextureFP15RwTexDictionaryP7RpClumpP10sEnTexturei(
    M2C_UNK*, u32, u32, M2C_UNK*, M2C_UNK);                 /* extern */
M2C_UNK __ct__16TEnemyMatTextureFv(M2C_UNK*);               /* extern */
M2C_UNK __ct__15sRingLaserParamFv(void*);                   /* extern */
M2C_UNK fn_8011C13C(u32);                                   /* extern */
M2C_UNK ParalyzeEnemy__14TEnemyScoreManFi(u32, s32);        /* extern */
M2C_UNK TornadoEnemy__14TEnemyScoreManFi(u32, s32);         /* extern */
M2C_UNK AddScore__14TEnemyScoreManFii(u32, s32, M2C_UNK);   /* extern */
M2C_UNK CreateInstance__14TEnemyScoreManFv();               /* extern */
M2C_UNK fn_80139784(void*, TObject*, f32*);                 /* extern */
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
void fn_8_BDF6C(TObject* arg0, void* arg1);                 /* static */
void** fn_8_BE528(void* arg0);                              /* static */
s32 fn_8_BF340(void* arg0);                                 /* static */
s32 fn_8_BF524(s32 arg0);                                   /* static */
s32 fn_8_BF5AC(void* arg0);                                 /* static */
void fn_8_BFF94(void* arg0, s32 arg1);                      /* static */
void fn_8_C08C8(void* arg0, s32 arg1);                      /* static */
void fn_8_C14B4(TObject* arg0);                             /* static */
void fn_8_C1BCC(TObject* arg0);                             /* static */
TObject* fn_8_C2018(TObject* arg0, TObject* arg1);          /* static */
void turtleObjectCreate();                                  /* static */
void turtleObjectLoad();                                    /* static */
void turtleObjectUnload();                                  /* static */
extern M2C_UNK __dt__16TEnemyMatTextureFv;
extern RwFrame AxisX;
extern RwFrame AxisY;
extern RwFrame AxisZ;
extern M2C_UNK lbl_802AD090;
extern M2C_UNK lbl_80303DC8;
extern TObject* lbl_8042C10C;
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
void fn_8_BE644(void* arg0, s32 arg1);
void fn_8_BE80C(void* arg0, void* arg1);
void fn_8_BE8B8(void* arg0);
void fn_8_BE978(void* arg0);
s32 fn_8_BEDDC(TObjEffTornadoSpin* arg0);
s32 fn_8_BF858(void* arg0, f32 farg0);
void fn_8_BF8D4(void* arg0);
void fn_8_BF9A4(void);
void fn_8_BF9A8(void* arg0);
void fn_8_BF9FC(TObject* arg0);
void fn_8_BFA30(TObject* arg0);
void fn_8_C0D74(void* arg0, u32 arg1, s32 arg2);
void* fn_8_C1ED8(void* arg0, s16 arg1);
void fn_8_C2398(void* arg0, void* arg1);

static TFunc lbl_8_data_17BB0[16] = {
	NULL,
	NULL,
	(TFunc)fn_8_BE4C4,
	(TFunc)fn_8_BE5AC,
	(TFunc)fn_8_BE39C,
	(TFunc)fn_8_BE044,
	(TFunc)fn_8_BDEB8,
	(TFunc)fn_8_BDE04,
	(TFunc)fn_8_BDD50,
	(TFunc)fn_8_BDC9C,
	(TFunc)fn_8_BDC7C,
	(TFunc)fn_8_BDC5C,
	(TFunc)fn_8_BDB4C,
	(TFunc)fn_8_BDB2C,
	(TFunc)fn_8_BDB0C,
	(TFunc)fn_8_BDA50,
};
/* The strategy unit's .rodata holds only the {0, 1.5, 0} vector that heads
 * every enemy unit's .rodata; nothing here references it. */
#pragma force_active on
static const f32 strategyRodataHead[3] = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

void fn_8_BDA50(void* arg0, s32 arg1)
{
	s32 temp_r31;
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			break;
		case 1:
			temp_r0                     = M2C_FIELD(arg0, s32*, 0x18) - 1;
			M2C_FIELD(arg0, s32*, 0x18) = temp_r0;
			if (temp_r0 < 0) {
				temp_r31                 = M2C_FIELD(arg0, s32*, 8);
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = temp_r31;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_BDB0C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x1A;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_BDB2C(void* arg0, s32 arg1)
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

void fn_8_BDB4C(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18)
			    = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x318);
			M2C_FIELD(arg0, s32*, 0x10) = 0x1F;
			break;
		case 1:
			temp_r0                     = M2C_FIELD(arg0, s32*, 0x18) - 1;
			M2C_FIELD(arg0, s32*, 0x18) = temp_r0;
			if (temp_r0 < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 7;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			if (fn_800A6334(M2C_FIELD(arg0, void**, 0x14)) == 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_BDC5C(void* arg0, s32 arg1)
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

void fn_8_BDC7C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x29;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_BDC9C(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x28;
			break;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_BF524(M2C_FIELD(arg0, s32*, 0x14)) == 0)) {
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

void fn_8_BDD50(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x2A;
			break;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_BF340((void*)M2C_FIELD(arg0, u32*, 0x14)) != 0)) {
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

void fn_8_BDE04(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			break;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_BF340((void*)M2C_FIELD(arg0, u32*, 0x14)) != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 6;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_BDEB8(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x78;
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			break;
		case 1:
			temp_r0                     = M2C_FIELD(arg0, s32*, 0x18) - 1;
			M2C_FIELD(arg0, s32*, 0x18) = temp_r0;
			if (temp_r0 < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_BDF6C(TObject* arg0, void* arg1)
{
	void* temp_r4;
	s32 temp_r0;

	arg0->unk14 = arg1;
	temp_r4     = arg0->unk14;
	if (temp_r4 != NULL) {
		temp_r0 = M2C_FIELD(temp_r4, s32*, 0x314);
		switch (temp_r0) { /* irregular */
			case 0:
				arg0->unkC  = 2;
				arg0->unk10 = 0;
				arg0->unk4  = 2;
				((TObjectDispatch*)arg0)->Release((s32)arg0->unk4, 0);
				if ((s32)arg0->unk10 != 0) {
					fn_800A31B8(arg0->unk14, (s32)arg0->unk10);
					return;
				}
				break;
			case 1:
				arg0->unkC  = 1;
				arg0->unk10 = 0;
				arg0->unk4  = 1;
				((TObjectDispatch*)arg0)->Release((s32)arg0->unk4, 0);
				if ((s32)arg0->unk10 != 0) {
					fn_800A31B8(arg0->unk14, (s32)arg0->unk10);
				}
				break;
		}
	}
}

s32 fn_8_BE044(void* arg0)
{
	s32 temp_r30;
	s32 temp_r3_3;
	s32 var_r3;
	void* temp_r3;
	void* temp_r3_2;
	s32 temp_r0;
	s32 var_r0;

	temp_r3  = M2C_FIELD(arg0, void**, 0x14);
	temp_r30 = M2C_FIELD(temp_r3, s32*, 0x19C);
	if ((fn_800A3ED4(temp_r3) != 0) && (temp_r30 != 0x1D)) {
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 5;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	if (fn_8_BF5AC(M2C_FIELD(arg0, void**, 0x14)) != 0) {
		if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
			var_r0 = 0;
		} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
			var_r0 = 0;
		} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
			var_r0 = 0;
		} else {
			var_r0 = 1;
		}
		if (var_r0 != 0) {
			switch (temp_r30) {
				case 1:
				case 2:
				case 0x1F:
					break;
				default:
					goto block_18;
			}
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 3;
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			return 1;
		}
		goto block_18;
	}
block_18:
	temp_r3_2 = M2C_FIELD(arg0, void**, 0x14);
	temp_r0   = M2C_FIELD(temp_r3_2, s32*, 0x248);
	if (temp_r0 != 0) {
		var_r3 = 0;
		switch (temp_r0) { /* switch 1; irregular */
			case 31:       /* switch 1 */
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 6;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 41: /* switch 1 */
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 4;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x248) = 0;
		return var_r3;
	}
	temp_r3_3 = M2C_FIELD(temp_r3_2, s32*, 0x18C);
	if ((u32)(temp_r3_3 & 0x1000) != 0) {
		switch (temp_r30) { /* switch 2 */
			case 26:        /* switch 2 */
			case 29:        /* switch 2 */
			case 36:        /* switch 2 */
			case 41:        /* switch 2 */
				return 0;
			default: /* switch 2 */
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 8;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				return 1;
		}
	} else {
		if ((u32)(temp_r3_3 & 0x2000) != 0) {
			switch (temp_r30) {
				case 2:
				case 0x1F:
					break;
				default:
					goto block_37;
			}
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 9;
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			return 1;
		}
	block_37:
		return 0;
	}
}

void fn_8_BE39C(void** arg0, u32 arg1, s32 arg2)
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
			/* fallthrough */
		default:
			return;
	}
}

static TFunc lbl_8_data_17C58[6] = {
	NULL,
	NULL,
	(TFunc)fn_8_BE55C,
	(TFunc)fn_8_BE5AC,
	NULL,
	NULL,
};
/* The state-machine base's destructor body, inlined into the derived
 * destructor: it re-tests the same pointer and so reuses the first compare. */
static inline void DestroyStateBase(M2C_UNK** self)
{
	if (self != NULL) {
		*self = (M2C_UNK*)lbl_8_data_17C58;
	}
}

M2C_UNK** fn_8_BE4C4(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_17BB0;
		DestroyStateBase(arg0);
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void** fn_8_BE528(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_17C58;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_17BB0;
	return (void**)arg0;
}

M2C_UNK** fn_8_BE55C(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_17C58;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_BE5AC(void* arg0, void* arg1)
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
