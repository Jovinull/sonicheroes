#include "types.h"

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
	u8 data[8];
} sParalysisParam;
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
    TEnemyParalysis*, void*, sParalysisParam*);                                  /* extern */
void* __ct__15sParalysisParamFv(void*);                                          /* extern */
void* __ct__7TObjectFP7TObject(void*, void*);                                    /* extern */
M2C_UNK __dl__FPv(void* arg0);                                                   /* extern */
void* __dt__10HAnimClassFv(void*, s32);                                          /* extern */
void* __dt__7TObjectFv(void*, s32);                                              /* extern */
M2C_UNK __register_global_object(M2C_UNK*, M2C_UNK*);                            /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                                           /* extern */
s32 fn_80017800(TObject*);                                                       /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                                              /* extern */
TObject* fn_80018A34(s32, M2C_UNK);                                              /* extern */
u32 fn_800209C8(void*, M2C_UNK);                                                 /* extern */
u32 fn_80020BD8(void*, M2C_UNK);                                                 /* extern */
M2C_UNK fn_80021384(void*);                                                      /* extern */
M2C_UNK fn_80021824(M2C_UNK*);                                                   /* extern */
M2C_UNK fn_8003BC38(M2C_UNK*);                                                   /* extern */
M2C_UNK fn_8003BE78(void*);                                                      /* extern */
M2C_UNK fn_8003C200(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);                       /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                                                   /* extern */
M2C_UNK fn_8004D5F4(s32, M2C_UNK, f32);                                          /* extern */
void** fn_80057644(M2C_UNK);                                                     /* extern */
s32 fn_8005B8D8(f32*);                                                           /* extern */
M2C_UNK fn_8005BC04(void*);                                                      /* extern */
M2C_UNK fn_8005BF5C(void*, u32*);                                                /* extern */
M2C_UNK fn_8005D5C8(void*, s32);                                                 /* extern */
s32 fn_8005D9A0(void*, M2C_UNK);                                                 /* extern */
M2C_UNK fn_8005DA34();                                                           /* extern */
M2C_UNK fn_8005DABC(s32*, s32*);                                                 /* extern */
M2C_UNK fn_8005E00C(M2C_UNK);                                                    /* extern */
M2C_UNK fn_8006298C(M2C_UNK, f32*, s32*);                                        /* extern */
s32 fn_800A2D50();                                                               /* extern */
M2C_UNK fn_800A31B8(void*);                                                      /* extern */
s32 fn_800A3684();                                                               /* extern */
M2C_UNK fn_800A3D48(TObject*);                                                   /* extern */
s32 fn_800A3ED4(void*);                                                          /* extern */
M2C_UNK fn_800A3F60(void*);                                                      /* extern */
M2C_UNK fn_800A4668(TObject*);                                                   /* extern */
M2C_UNK fn_800A4A8C(TObject*, f32);                                              /* extern */
s32 fn_800A5888(TObject*, f32*, f32);                                            /* extern */
s32 fn_800A5998(TObject*);                                                       /* extern */
s32 fn_800A5A54(TObject*);                                                       /* extern */
f32 fn_800A5AC0(TObject*);                                                       /* extern */
M2C_UNK fn_800A5B34(TObject*);                                                   /* extern */
M2C_UNK fn_800A5C6C(TObject*, M2C_UNK);                                          /* extern */
s32 fn_800A6334();                                                               /* extern */
M2C_UNK fn_800A7088(TObject*, M2C_UNK);                                          /* extern */
M2C_UNK fn_800A714C();                                                           /* extern */
M2C_UNK fn_800B4A38(u32, M2C_UNK, f32*, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);     /* extern */
M2C_UNK fn_800B7514(f32*, s32*, f32*, f32);                                      /* extern */
M2C_UNK fn_800B7820();                                                           /* extern */
M2C_UNK fn_800B7864(M2C_UNK);                                                    /* extern */
f32 fn_800D71DC(void*, s32);                                                     /* extern */
f32 fn_800D7218(f32*, M2C_UNK*);                                                 /* extern */
s32 fn_800D7A94(s32, s32, s32);                                                  /* extern */
f32 fn_800D7B00(u32);                                                            /* extern */
f32 fn_800D8BC4(f32*, s32*, M2C_UNK);                                            /* extern */
void** fn_800FD8A0(TObject*, s32);                                               /* extern */
M2C_UNK fn_800FE248(M2C_UNK, M2C_UNK*);                                          /* extern */
M2C_UNK fn_800FE274(M2C_UNK, M2C_UNK*);                                          /* extern */
u32 fn_80100280(u32, M2C_UNK, M2C_UNK);                                          /* extern */
u32 fn_80100328(u32, M2C_UNK, M2C_UNK);                                          /* extern */
u32 fn_8010037C(u32, M2C_UNK, M2C_UNK);                                          /* extern */
M2C_UNK fn_801007F4(u32, M2C_UNK);                                               /* extern */
M2C_UNK fn_8010096C(u32, M2C_UNK, M2C_UNK*);                                     /* extern */
M2C_UNK fn_80100AAC();                                                           /* extern */
M2C_UNK fn_80102C50(s32, f32*, s32*, s32*, M2C_UNK, M2C_UNK, M2C_UNK, f32, f32); /* extern */
s32 fn_80103324(void*, f32*, f32);                                               /* extern */
s32 fn_8010AFB0();                                                               /* extern */
M2C_UNK fn_8010AFE4();                                                           /* extern */
M2C_UNK fn_8010AFF8(u32, s32);                                                   /* extern */
M2C_UNK fn_8010B074(u32);                                                        /* extern */
M2C_UNK fn_8010B0AC(u32, s32, f32, f32);                                         /* extern */
M2C_UNK fn_8010B208(u32, f32, f32);                                              /* extern */
M2C_UNK fn_8010B350(f32*, M2C_UNK*);                                             /* extern */
u32 fn_8010B708(M2C_UNK);                                                        /* extern */
M2C_UNK fn_80113874(s32);                                                        /* extern */
M2C_UNK fn_801138B4();                                                           /* extern */
M2C_UNK fn_801138F4();                                                           /* extern */
M2C_UNK fn_80113940();                                                           /* extern */
M2C_UNK fn_8011398C(M2C_UNK*, s32);                                              /* extern */
M2C_UNK fn_80113A68(M2C_UNK*);                                                   /* extern */
M2C_UNK fn_80113AA8(M2C_UNK*, s32, void*, M2C_UNK*, M2C_UNK);                    /* extern */
M2C_UNK fn_80113C7C(M2C_UNK*);                                                   /* extern */
M2C_UNK fn_8011B418(f32*);                                                       /* extern */
M2C_UNK fn_8011B594(f32*);                                                       /* extern */
M2C_UNK fn_8011B844(u32, f32*, f32);                                             /* extern */
M2C_UNK fn_8011C0E8(u32);                                                        /* extern */
M2C_UNK fn_8011C188(u32, s32);                                                   /* extern */
M2C_UNK fn_8011C1DC(u32, s32);                                                   /* extern */
M2C_UNK fn_8011C1F8(u32, s32, M2C_UNK);                                          /* extern */
M2C_UNK fn_8011C6EC();                                                           /* extern */
M2C_UNK fn_8011C9A0(void*, s8);                                                  /* extern */
M2C_UNK fn_8011CE44();                                                           /* extern */
M2C_UNK fn_80137FE8(s32*);                                                       /* extern */
M2C_UNK fn_80138050(s32*);                                                       /* extern */
M2C_UNK fn_8014FF2C(s32*);                                                       /* extern */
M2C_UNK fn_8014FFBC(void*, M2C_UNK*, u32*);                                      /* extern */
void* fn_80150588(void*);                                                        /* extern */
M2C_UNK fn_80150958(void*);                                                      /* extern */
M2C_UNK fn_80196050(M2C_UNK*, void*, M2C_UNK);                                   /* extern */
M2C_UNK fn_801990E0(f32*, f32*, f32);                                            /* extern */
M2C_UNK fn_8019941C(f32*, f32*, M2C_UNK, M2C_UNK*);                              /* extern */
s32 fn_8019CE34(s32, f32*);                                                      /* extern */
M2C_UNK* fn_8019E8EC(u32);                                                       /* extern */
M2C_UNK fn_8019EB94(RwFrame*, void*, M2C_UNK);                                   /* extern */
M2C_UNK fn_8019ECCC(s32, M2C_UNK*, M2C_UNK);                                     /* extern */
M2C_UNK fn_8019ED68(RwFrame*, M2C_UNK*, M2C_UNK, f32);                           /* extern */
M2C_UNK fn_8_90B10(s32);                                                         /* extern */
M2C_UNK fn_8_B6F14(s32);                                                         /* extern */
void fn_8_B7C50(TObject* arg0, void* arg1);                                      /* static */
void fn_8_B81B0(void* arg0);                                                     /* static */
void fn_8_B9904(TObject* arg0, s32 arg1);                                        /* static */
s32 fn_8_B9BA0(void* arg0);                                                      /* static */
s32 fn_8_B9BBC(void* arg0);                                                      /* static */
s32 fn_8_B9CD4(void* arg0);                                                      /* static */
s32 fn_8_B9E40(void* arg0);                                                      /* static */
void fn_8_BA8E0(TObject* arg0, s32 arg1);                                        /* static */
void fn_8_BAF00(TObject* arg0, s32 arg1);                                        /* static */
void fn_8_BB294(TObject* arg0, s32 arg1);                                        /* static */
void fn_8_BB5E4(TObject* arg0, s32 arg1);                                        /* static */
void fn_8_BBF90(TObject* arg0);                                                  /* static */
void fn_8_BC2CC(TObject* arg0);                                                  /* static */
void fn_8_BCB60(TObject* arg0);                                                  /* static */
void fn_8_BCD58(TObject* arg0);                                                  /* static */
TObject* fn_8_BCF88(TObject* arg0);                                              /* static */
void wallObjectCreate();                                                         /* static */
void wallObjectLoad();                                                           /* static */
void wallObjectUnload();                                                         /* static */
extern M2C_UNK fn_8005BF88;
extern M2C_UNK fn_80113C2C;
extern M2C_UNK lbl_80239978;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
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
extern u32 lbl_8042C590;
extern u32 lbl_8042C6D0;
extern s32* lbl_8042C9A4;
extern M2C_UNK lbl_8_rodata_1CB8;
extern M2C_UNK lbl_8_rodata_1CC4;
extern M2C_UNK lbl_8_rodata_1CD0;
extern M2C_UNK lbl_8_rodata_1CDC;
extern M2C_UNK lbl_8_rodata_1CE8;
extern M2C_UNK lbl_8_rodata_1CF4;
extern s32 lbl_8_rodata_1D00;
extern M2C_UNK lbl_8_rodata_1D10;
extern M2C_UNK lbl_8_rodata_1D1C;
extern M2C_UNK lbl_8_rodata_1D2C;
extern M2C_UNK lbl_8_rodata_1D3C;
extern M2C_UNK lbl_8_rodata_1D48;
extern f32 lbl_8_rodata_1D54;
extern f32 lbl_8_rodata_1D58;
extern f32 lbl_8_rodata_1D5C;
extern f32 lbl_8_rodata_1D60;
extern f32 lbl_8_rodata_1D64;
extern f32 lbl_8_rodata_1D68;
extern f32 lbl_8_rodata_1D6C;
extern f32 lbl_8_rodata_1D70;
extern f32 lbl_8_rodata_1D74;
extern f32 lbl_8_rodata_1D78;
extern f32 lbl_8_rodata_1D7C;
extern f32 lbl_8_rodata_1D80;
extern f32 lbl_8_rodata_1D84;
extern f32 lbl_8_rodata_1D88;
extern f32 lbl_8_rodata_1D98;
extern f32 lbl_8_rodata_1D9C;
extern f32 lbl_8_rodata_1DA0;
extern f32 lbl_8_rodata_1DA4;
extern f32 lbl_8_rodata_1DA8;
extern f32 lbl_8_rodata_1DAC;
extern f32 lbl_8_rodata_1DB0;
extern f32 lbl_8_rodata_1DB4;
extern f32 lbl_8_rodata_1DB8;
extern f32 lbl_8_rodata_1DBC;
extern f32 lbl_8_rodata_1DC0;
extern f32 lbl_8_rodata_1DC4;
extern f32 lbl_8_rodata_1DC8;
extern f32 lbl_8_rodata_1DCC;
extern f32 lbl_8_rodata_1DD0;
extern f32 lbl_8_rodata_1DD4;
extern f32 lbl_8_rodata_1DD8;
extern f32 lbl_8_rodata_1DDC;
extern f32 lbl_8_rodata_1DE0;
extern f32 lbl_8_rodata_1DE4;
extern f32 lbl_8_rodata_1DE8;
extern f32 lbl_8_rodata_1DEC;
extern f32 lbl_8_rodata_1DF0;
extern f32 lbl_8_rodata_1DF4;
extern f32 lbl_8_rodata_1DF8;
extern f32 lbl_8_rodata_1DFC;
extern f32 lbl_8_rodata_1E00;
extern f32 lbl_8_rodata_1E04;
extern f32 lbl_8_rodata_1E08;
extern f32 lbl_8_rodata_1E0C;
extern f32 lbl_8_rodata_1E10;
extern s32 lbl_8_rodata_1E14;
extern s32 lbl_8_rodata_1E18;
extern f32 lbl_8_rodata_1E1C;
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
static TFunc lbl_8_data_17378[6] = {
	NULL,
	NULL,
	(TFunc)fn_8_B81E4,
	(TFunc)fn_8_B8234,
	NULL,
	NULL,
};
static char lbl_8_data_17390[] = "en_wall_stand.anm";
static M2C_UNK gap_04_000173A2_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_173A4[] = "en_wall_walk.anm";
static M2C_UNK gap_04_000173B5_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_173B8[] = "en_wall_ata0.anm";
static M2C_UNK gap_04_000173C9_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_173CC[] = "en_wall_ata1.anm";
static M2C_UNK gap_04_000173DD_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_173E0[] = "en_wall_atb0.anm";
static M2C_UNK gap_04_000173F1_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_173F4[] = "en_wall_atb1.anm";
static M2C_UNK gap_04_00017405_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17408[] = "en_wall_atb5.anm";
static M2C_UNK gap_04_00017419_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_1741C[] = "en_wall_dam0.anm";
static M2C_UNK gap_04_0001742D_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17430[] = "en_wall_dam1.anm";
static M2C_UNK gap_04_00017441_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17444[] = "en_wall_damloop.anm";
static char lbl_8_data_17458[] = "en_wall_fall.anm";
static M2C_UNK gap_04_00017469_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_1746C[] = "en_wall_fallstand.anm";
static M2C_UNK gap_04_00017482_data; /* unable to generate initializer: unknown type */
typedef struct sWallAnimDef {
	u32 unk0;
	u32 unk4;
	u32 unk8;
	u32 unkC;
	u32 unk10;
	u32 unk14;
	u32 unk18;
	char* unk1C;
	u32 unk20;
} sWallAnimDef;

static sWallAnimDef lbl_8_data_17484[14] = {
	{ 0x00000000, 0x00000003, 0x00000001, 0x00000000, 0xBF800000, 0x3D800000, 0x3F800000,
	    lbl_8_data_17390, 0x00000015 },
	{ 0x00000000, 0x00000003, 0x00000001, 0x00000000, 0xBF800000, 0x3D800000, 0x3F800000,
	    lbl_8_data_173A4, 0x00000016 },
	{ 0x00000000, 0x00000004, 0x00000003, 0x00000000, 0xBF800000, 0x3D800000, 0x3F800000,
	    lbl_8_data_173B8, 0x0000000A },
	{ 0x00000000, 0x00000005, 0x00000001, 0x00000000, 0x41F00000, 0x3D800000, 0x40200000,
	    lbl_8_data_173CC, 0x0000000B },
	{ 0x00000000, 0x00000004, 0x00000005, 0x00000000, 0xBF800000, 0x3D800000, 0x3F800000,
	    lbl_8_data_173E0, 0x0000000C },
	{ 0x00000000, 0x00000003, 0x00000001, 0x00000000, 0xBF800000, 0x3F000000, 0x3F800000,
	    lbl_8_data_173F4, 0x0000000D },
	{ 0x00000000, 0x00000003, 0x00000001, 0x00000000, 0xBF800000, 0x3D800000, 0x3F800000,
	    lbl_8_data_17408, 0x0000000E },
	{ 0x00000000, 0x00000004, 0x00000009, 0x00000000, 0xBF800000, 0x3F800000, 0x3F800000,
	    lbl_8_data_1741C, 0x0000000F },
	{ 0x00000000, 0x00000004, 0x00000000, 0x00000000, 0xBF800000, 0x3D800000, 0x3F800000,
	    lbl_8_data_17430, 0x00000010 },
	{ 0x00000000, 0x00000003, 0x00000001, 0x00000000, 0xBF800000, 0x3F800000, 0x3F800000,
	    lbl_8_data_17444, 0x00000011 },
	{ 0x00000000, 0x00000003, 0x00000001, 0x00000000, 0xBF800000, 0x3F800000, 0x3F800000,
	    lbl_8_data_17458, 0x00000012 },
	{ 0x00000000, 0x00000004, 0x00000000, 0x00000000, 0xBF800000, 0x3F800000, 0x40400000,
	    lbl_8_data_1746C, 0x00000013 },
	{ 0x00000000, 0x0000000B, 0x00000001, 0x00000000, 0xBF800000, 0x3E800000, 0x3F800000,
	    lbl_8_data_173A4, 0x00000016 },
	{ 0x00000000, 0x0000000E, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	    0x00000000, 0x00000000 },
};
static u32 lbl_8_data_1767C[120] = {
	0x0000FF21,
	0x00000420,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41200000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0000FF21,
	0x00000420,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0000FF21,
	0x00000420,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0000FF21,
	0x00000420,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0000FF21,
	0x00000420,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0000FF21,
	0x00000420,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41700000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0000FF2B,
	0x00000020,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41700000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0000FF2B,
	0x00000020,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41700000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0000FF21,
	0x00000020,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0000FF21,
	0x00000020,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
};
static char lbl_8_data_1785C[] = "o_on";
static M2C_UNK gap_04_00017861_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17864[] = "o_on2";
static M2C_UNK gap_04_0001786A_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_1786C[] = "o_on3";
static M2C_UNK gap_04_00017872_data; /* unable to generate initializer: unknown type */
static char* lbl_8_data_17874[9]
    = { lbl_8_data_1785C, NULL, NULL, lbl_8_data_17864, NULL, NULL, lbl_8_data_1786C, NULL, NULL };
static char lbl_8_data_17898[] = "WALL TYPE";
static M2C_UNK gap_04_000178A2_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_178A4[] = "APPEAR TYPE";
static char lbl_8_data_178B0[] = "Not in use";
static M2C_UNK gap_04_000178BB_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_178BC[] = "MOVE SPEED";
static M2C_UNK gap_04_000178C7_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_178C8[] = "MOVE RANGE";
static M2C_UNK gap_04_000178D3_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_178D4[] = "SCOPE RANGE";
static char lbl_8_data_178E0[] = "SCOPE OFFSET";
static M2C_UNK gap_04_000178ED_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_178F0[] = "ATTACK INTERVAL";
static char lbl_8_data_17900[] = "WEAPON SPEED";
static M2C_UNK gap_04_0001790D_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17910[] = "FALL DISTANCE";
static M2C_UNK gap_04_0001791E_data; /* unable to generate initializer: unknown type */
static char* wallObjectFieldNames[11] = { lbl_8_data_17898, lbl_8_data_178A4, lbl_8_data_178B0,
	lbl_8_data_178B0, lbl_8_data_178BC, lbl_8_data_178C8, lbl_8_data_178D4, lbl_8_data_178E0,
	lbl_8_data_178F0, lbl_8_data_17900, lbl_8_data_17910 };
static char lbl_8_data_1794C[]        = "NORMAL";
static M2C_UNK gap_04_00017953_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17954[]   = "SPECIAL";
static char* lbl_8_data_1795C[2] = { lbl_8_data_1794C, lbl_8_data_17954 };
static char lbl_8_data_17964[]   = "WAIT";
static M2C_UNK gap_04_00017969_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_1796C[] = "FALL";
static M2C_UNK gap_04_00017971_data; /* unable to generate initializer: unknown type */
static char* lbl_8_data_17974[2] = { lbl_8_data_17964, lbl_8_data_1796C };
static u8 lbl_8_data_1797C       = 0;
static u8 lbl_8_data_1797D       = 1;
static u8 lbl_8_data_1797E       = 0;
static u8 lbl_8_data_1797F       = 1;
static char lbl_8_data_17980[]   = "TObjEnemyWall";
static M2C_UNK gap_04_0001798E_data; /* unable to generate initializer: unknown type */
static char* lbl_8_data_17990   = lbl_8_data_17980;
static u32 lbl_8_data_17994[12] = {
	0x00000F00,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x41200000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
};
static char lbl_8_data_179C4[]    = "TObjEnemyWallHelmet";
static char* lbl_8_data_179D8     = lbl_8_data_179C4;
static TFunc lbl_8_data_179DC[11] = {
	NULL,
	NULL,
	(TFunc)fn_8_B8F34,
	(TFunc)fn_8_B8970,
	(TFunc)fn_8_B8504,
	(TFunc)fn_8_B82CC,
	(TFunc)PDisp__7TObjectFv,
	(TFunc)ImmAftSetRaster__7TObjectFv,
	(TFunc)Debug__7TObjectFv,
	(TFunc)Error__7TObjectFPc,
	(TFunc)Render__7TObjectFv,
};
static char lbl_8_data_17AE0[]    = "en_wall.one";
static TFunc lbl_8_data_17AEC[42] = {
	NULL,
	NULL,
	(TFunc)fn_8_BCE1C,
	(TFunc)fn_800A6F38,
	(TFunc)fn_800A6EA8,
	(TFunc)fn_800A6DD4,
	(TFunc)PDisp__7TObjectFv,
	(TFunc)ImmAftSetRaster__7TObjectFv,
	(TFunc)Debug__7TObjectFv,
	(TFunc)Error__7TObjectFPc,
	(TFunc)Render__7TObjectFv,
	NULL,
	NULL,
	(TFunc)fn_8_BDA48,
	(TFunc)fn_8_B9B20,
	(TFunc)fn_8_B956C,
	(TFunc)fn_8_B93A4,
	(TFunc)fn_800A327C,
	(TFunc)fn_800A324C,
	(TFunc)fn_800A321C,
	(TFunc)fn_8_BBAD0,
	(TFunc)fn_8_BA3A4,
	(TFunc)fn_8_BA370,
	(TFunc)fn_8_BA2B0,
	(TFunc)fn_8_BA1EC,
	(TFunc)fn_8_BA0D4,
	(TFunc)fn_8_33D90,
	(TFunc)fn_8_33D94,
	(TFunc)fn_800A314C,
	(TFunc)fn_800A6D60,
	(TFunc)fn_800A6D58,
	(TFunc)fn_8_B986C,
	(TFunc)fn_800A3D6C,
	(TFunc)fn_800A2C6C,
	(TFunc)fn_8_B9548,
	(TFunc)fn_8_33D98,
	(TFunc)fn_800A31A0,
	(TFunc)fn_8_B97C0,
	(TFunc)fn_800A3148,
	(TFunc)fn_8_33DA0,
	(TFunc)fn_8_33DA4,
	(TFunc)fn_8_BD380,
};
static char wallObjectDisplayName[] = "WALL OBJECT";
static char wallObjectFieldTypes[]  = "ccccffffiff";
static M2C_UNK gap_04_00017BAC_data; /* unable to generate initializer: unknown type */
static void* lbl_8_bss_1AC8[5];
static u32 lbl_8_bss_1ADC;
static u32 lbl_8_bss_1AE0[0x11];
static s32 lbl_8_bss_1B24;
static M2C_UNK wallObjectGlobalAChain;
static M2C_UNK wallObjectGlobalA;
static M2C_UNK wallObjectEntry;
static f32 lbl_8_rodata_1E20[6] = { 10000.0f, 0.0f, 0.0f, 1.5f, 0.0f, 0.0f }; /* const */

void fn_8_B7210(s32 arg0)
{
	fn_8_B6F14(arg0 - 0xB0);
}

void fn_8_B7218(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x78;
			M2C_FIELD(arg0, s32*, 0x10) = 0x35;
			return;
		case 1:
			fn_80137FE8((M2C_UNK*)((u8*)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
	}
}

void fn_8_B72D0(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x168;
			M2C_FIELD(arg0, s32*, 0x10) = 0x34;
			return;
		case 1:
			fn_80137FE8((M2C_UNK*)((u8*)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xF;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
	}
}

void fn_8_B7388(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x12C;
			M2C_FIELD(arg0, s32*, 0x10) = 0x33;
			return;
		case 1:
			fn_80137FE8((M2C_UNK*)((u8*)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			if (fn_8_B9BA0(M2C_FIELD(arg0, void**, 0x14)) != 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xE;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
	}
}

void fn_8_B7498(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x12C;
			M2C_FIELD(arg0, s32*, 0x10) = 0x32;
			return;
		case 1:
			fn_80137FE8((M2C_UNK*)((u8*)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xD;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
	}
}

void fn_8_B7550(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x55;
			M2C_FIELD(arg0, s32*, 0x10) = 0x31;
			return;
		case 1:
			fn_80137FE8((M2C_UNK*)((u8*)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xA;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
	}
}

void fn_8_B7608(void* arg0, s32 arg1)
{
	s32 temp_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x30;
			return;
		case 1:
			temp_r4 = M2C_FIELD(arg0, s32*, 0x1C);
			if (temp_r4 < 3) {
				M2C_FIELD(arg0, s32*, 0x1C) = (s32)(temp_r4 + 1);
				M2C_FIELD(arg0, s32*, 8)    = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xB;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				return;
			}
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
			    M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 0;
			M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
			    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			return;
		case 4:
			return;
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
			return;
		case 1:
			fn_80137FE8((M2C_UNK*)((u8*)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
	}
}

void fn_8_B77D4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x1A;
			return;
		case 1:
			fn_80138050((M2C_UNK*)((u8*)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) > 1) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 4;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
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
			return;
		case 1:
			if (((void*)M2C_FIELD(arg0, void**, 0x14) != NULL) && (fn_800A6334() == 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				return;
			}
			fn_80137FE8((M2C_UNK*)((u8*)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				temp_r3 = fn_8_B9CD4(M2C_FIELD(arg0, void**, 0x14));
				if (temp_r3 == 1) {
					M2C_FIELD(arg0, s32*, 0x1C) = 0;
					M2C_FIELD(arg0, s32*, 8)    = (s32)M2C_FIELD(arg0, s32*, 4);
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 0xA;
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 0);
					return;
				}
				if (temp_r3 == 2) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 0xC;
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 0);
					return;
				}
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 4;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			} else {
				return;
			}
			break;
		case 4:
			break;
	}
}

void fn_8_B7AA4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x78;
			M2C_FIELD(arg0, s32*, 0x10) = 8;
			return;
		case 1:
			fn_80137FE8((M2C_UNK*)((u8*)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
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
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_B9E40((void*)M2C_FIELD(arg0, u32*, 0x14)) != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 4;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
	}
}

void fn_8_B7C50(TObject* arg0, void* arg1)
{
	s32 temp_r0;
	void* temp_r4;

	arg0->unk14 = arg1;
	temp_r4     = arg0->unk14;
	if (temp_r4 != NULL) {
		temp_r0 = M2C_FIELD(temp_r4, s32*, 0x308);
		switch (temp_r0) { /* irregular */
			case 0:
				arg0->unkC  = 0;
				arg0->unk10 = 0;
				arg0->unk4  = 0;
				M2C_FIELD(arg0->unk0, M2C_UNK(**)(s32, M2C_UNK), 0x10)(arg0->unk4, 0);
				if ((s32)arg0->unk10 != 0) {
					fn_800A31B8(arg0->unk14);
					return;
				}
				break;
			case 1:
				arg0->unkC  = 2;
				arg0->unk10 = 0;
				arg0->unk4  = 2;
				M2C_FIELD(arg0->unk0, M2C_UNK(**)(s32, M2C_UNK), 0x10)(arg0->unk4, 0);
				if ((s32)arg0->unk10 != 0) {
					fn_800A31B8(arg0->unk14);
				}
				break;
		}
	}
}

s32 fn_8_B7D24(void* arg0)
{
	s32 temp_r0;
	s32 temp_r0_2;
	s32 var_r3;
	void* temp_r3;

	fn_8_B9BBC(M2C_FIELD(arg0, void**, 0x14));
	if ((fn_800A3ED4(M2C_FIELD(arg0, void**, 0x14)) != 0)
	    && ((s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x19C) != 0x1D)) {
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 5;
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	temp_r3 = M2C_FIELD(arg0, void**, 0x14);
	temp_r0 = M2C_FIELD(temp_r3, s32*, 0x248);
	if (temp_r0 != 0) {
		var_r3 = 0;
		switch (temp_r0) { /* irregular */
			case 1:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 2:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 8:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x248) = 0;
		return var_r3;
	}
	if (((s32)M2C_FIELD(temp_r3, s32*, 0x304) == 0)
	    && ((u32)(M2C_FIELD(temp_r3, s32*, 0x18C) & 0x2000) != 0)) {
		temp_r0_2 = M2C_FIELD(temp_r3, s32*, 0x19C);
		if (temp_r0_2 != 0x2C) {
			if ((temp_r0_2 < 0x2C) && (temp_r0_2 < 3)) {
				if (temp_r0_2 < 1) {
					goto block_22;
				}
				goto block_21;
			}
		block_22:
			return 0;
		}
	block_21:
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 8;
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	return 0;
}

void fn_8_B7F94(void** arg0, u32 arg1, s32 arg2)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x18)(arg2);
			return;
		case 1:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x1C)(arg2);
			return;
		case 2:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x20)(arg2);
			return;
		case 3:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x24)(arg2);
			return;
		case 4:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x28)(arg2);
			return;
		case 5:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x2C)(arg2);
			return;
		case 6:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x30)(arg2);
			return;
		case 7:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x34)(arg2);
			return;
		case 8:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x38)(arg2);
			return;
		case 9:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x3C)(arg2);
			return;
		case 11:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x44)(arg2);
			return;
		case 10:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x40)(arg2);
			return;
		case 12:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x48)(arg2);
			return;
		case 13:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x4C)(arg2);
			return;
		case 14:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x50)(arg2);
			return;
		case 15:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x54)(arg2);
			/* fallthrough */
		default:
			return;
	}
}

M2C_UNK** fn_8_B814C(M2C_UNK** arg0, s16 arg1)
{
	s32 temp_cr0_eq;

	temp_cr0_eq = arg0 == NULL;
	if (temp_cr0_eq == 0) {
		*arg0 = (M2C_UNK*)lbl_8_data_172E0;
		if (temp_cr0_eq == 0) {
			*arg0 = (M2C_UNK*)lbl_8_data_17378;
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_B81B0(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_17378;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_172E0;
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
	if (M2C_FIELD(M2C_FIELD(arg0, void**, 0), s32(**)(), 0x14)() != 0) {
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 2);
	}
	M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
	    arg0, M2C_FIELD(arg0, s32*, 4), 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
		fn_800A31B8(M2C_FIELD(arg0, void**, 0x14));
	}
}

void fn_8_B82CC(void* arg0)
{
	sVec4 sp50;
	sVec4 sp40;
	RwV3d sp34;
	sVec4 sp24;
	RwV3d sp18;
	RwV3d spC;
	f32 sp8;
	f32* var_r3;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;

	if ((s32*)M2C_FIELD(arg0, s32**, 0xE0) != NULL) {
		if (M2C_FIELD(arg0, f32*, 0xE4) < lbl_8_rodata_1D5C) {
			sp50.x = M2C_FIELD(arg0, f32*, 0xB0);
			sp50.y = M2C_FIELD(arg0, f32*, 0xB4);
			sp50.z = M2C_FIELD(arg0, f32*, 0xB8);
			sp50.w = lbl_8_rodata_1D60;
			if (fn_8019CE34(*lbl_8042C9A4, &sp50.x) != 0) {
				M2C_FIELD(&sp40, M2C_BLOCK16*, 0) = M2C_FIELD(&lbl_8_rodata_1D2C, M2C_BLOCK16*, 0);
				sp40.w                            = M2C_FIELD(arg0, f32*, 0xE4);
				fn_8005DABC(M2C_FIELD(arg0, s32**, 0xE0), (s32*)&sp40);
				fn_80113940();
				fn_801138B4();
				fn_80113874(M2C_FIELD(arg0, s32*, 0xD8));
				fn_8014FF2C(M2C_FIELD(arg0, s32**, 0xE0));
				fn_801138F4();
			}
		} else {
			M2C_FIELD(&sp34, M2C_BLOCK12*, 0) = M2C_FIELD(arg0, M2C_BLOCK12*, 0xB0);
			temp_f1                           = M2C_FIELD(arg0, f32*, 0xC8);
			sp34.y                            = temp_f1;
			sp24.x                            = sp34.x;
			sp24.y                            = temp_f1;
			sp24.z                            = sp34.z;
			sp24.w                            = lbl_8_rodata_1D60;
			if (fn_8019CE34(*lbl_8042C9A4, &sp24.x) != 0) {
				M2C_FIELD(&sp18, M2C_BLOCK12*, 0) = M2C_FIELD(&lbl_8_rodata_1D3C, M2C_BLOCK12*, 0);
				temp_f1_2                         = lbl_8_rodata_1D5C
				    - (lbl_8_rodata_1D64
				        * (M2C_FIELD(arg0, f32*, 0xB4) - M2C_FIELD(arg0, f32*, 0xC8)));
				sp8    = temp_f1_2;
				var_r3 = &lbl_8_rodata_1D54;
				if (temp_f1_2 < lbl_8_rodata_1D54) {

				} else {
					var_r3 = &lbl_8_rodata_1D58;
					if (temp_f1_2 > lbl_8_rodata_1D58) {

					} else {
						var_r3 = &sp8;
					}
				}
				sp8                              = *var_r3;
				M2C_FIELD(&spC, M2C_BLOCK12*, 0) = M2C_FIELD(&lbl_8_rodata_1D48, M2C_BLOCK12*, 0);
				temp_f1_3                        = sp34.y;
				sp34.y                           = temp_f1_3 + lbl_8_rodata_1D5C;
				fn_800B7864(0);
				fn_800B7514(&sp34.x, (s32*)&spC, &sp18.x, sp8);
				fn_800B7820();
			}
		}
	}
}

void fn_8_B8504(void* arg0)
{
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	s32 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;

	if ((s32*)M2C_FIELD(arg0, s32**, 0xE0) != NULL) {
		M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
		if (M2C_FIELD(arg0, f32*, 0xE4) == lbl_8_rodata_1D5C) {
			sp18 = M2C_FIELD(arg0, f32*, 0xB0);
			sp1C = M2C_FIELD(arg0, f32*, 0xB4);
			sp20 = M2C_FIELD(arg0, f32*, 0xB8);
			sp24 = lbl_8_rodata_1D60;
			if (fn_8019CE34(*lbl_8042C9A4, &sp18) != 0) {
				sp8  = M2C_FIELD(&lbl_8_rodata_1D1C, s32*, 0);
				spC  = M2C_FIELD(&lbl_8_rodata_1D1C, s32*, 4);
				sp10 = M2C_FIELD(&lbl_8_rodata_1D1C, s32*, 8);
				sp14 = M2C_FIELD(&lbl_8_rodata_1D1C, s32*, 0xC);
				fn_8005DABC(M2C_FIELD(arg0, s32**, 0xE0), &sp8);
				fn_80113874(M2C_FIELD(arg0, s32*, 0xD8));
				fn_8014FF2C(M2C_FIELD(arg0, s32**, 0xE0));
			}
		}
	}
}

void fn_8_B85E0(void* arg0)
{
	RwFrame* temp_r30;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f2_3;
	f32 temp_f2_4;
	void* temp_r3;

	temp_f2 = M2C_FIELD(arg0, f32*, 0xF0);
	if ((f32)__fabs(temp_f2) > lbl_8_rodata_1D68) {
		M2C_FIELD(arg0, f32*, 0xF0) = (f32)(temp_f2 * lbl_8_rodata_1D6C);
	}
	temp_f2_2 = M2C_FIELD(arg0, f32*, 0xF4);
	if ((f32)__fabs(temp_f2_2) > lbl_8_rodata_1D68) {
		M2C_FIELD(arg0, f32*, 0xF4) = (f32)(temp_f2_2 * lbl_8_rodata_1D6C);
	}
	temp_r3 = M2C_FIELD(arg0, void**, 0xE0);
	if (temp_r3 != NULL) {
		temp_r30 = M2C_FIELD(temp_r3, RwFrame**, 4);
		fn_8019ED68(temp_r30, &lbl_80239990, 0, M2C_FIELD(arg0, f32*, 0xF4));
		fn_8019ED68(temp_r30, &lbl_80239978, 2, M2C_FIELD(arg0, f32*, 0xF0));
		fn_8019ED68(
		    temp_r30, &lbl_80239984, 2, lbl_8_rodata_1D70 * (f32)M2C_FIELD(arg0, s32*, 0xC0));
		fn_8019EB94(temp_r30, (u8*)arg0 + 0xB0, 2);
	}
	temp_f1                     = M2C_FIELD(arg0, f32*, 0xCC);
	M2C_FIELD(arg0, f32*, 0xCC) = (f32)(temp_f1 + (lbl_8_rodata_1D74 * -temp_f1));
	temp_f2_3                   = M2C_FIELD(arg0, f32*, 0xD0);
	M2C_FIELD(arg0, f32*, 0xD0)
	    = (f32)(temp_f2_3 + ((lbl_8_rodata_1D78 * -temp_f2_3) - lbl_8_rodata_1D7C));
	temp_f1_2                   = M2C_FIELD(arg0, f32*, 0xD4);
	M2C_FIELD(arg0, f32*, 0xD4) = (f32)(temp_f1_2 + (lbl_8_rodata_1D74 * -temp_f1_2));
	M2C_FIELD(arg0, f32*, 0xB0) = (f32)(M2C_FIELD(arg0, f32*, 0xB0) + M2C_FIELD(arg0, f32*, 0xCC));
	M2C_FIELD(arg0, f32*, 0xB4) = (f32)(M2C_FIELD(arg0, f32*, 0xB4) + M2C_FIELD(arg0, f32*, 0xD0));
	M2C_FIELD(arg0, f32*, 0xB8) = (f32)(M2C_FIELD(arg0, f32*, 0xB8) + M2C_FIELD(arg0, f32*, 0xD4));
	temp_f2_4                   = M2C_FIELD(arg0, f32*, 0xC8);
	if ((temp_f2_4 > M2C_FIELD(arg0, f32*, 0xB4))
	    && (M2C_FIELD(arg0, f32*, 0xD0) < lbl_8_rodata_1D80)) {
		M2C_FIELD(arg0, f32*, 0xB4) = temp_f2_4;
		M2C_FIELD(arg0, f32*, 0xCC) = (f32)(M2C_FIELD(arg0, f32*, 0xCC) * lbl_8_rodata_1D84);
		M2C_FIELD(arg0, f32*, 0xD0) = (f32)(M2C_FIELD(arg0, f32*, 0xD0) * lbl_8_rodata_1D88);
		M2C_FIELD(arg0, f32*, 0xD4) = (f32)(M2C_FIELD(arg0, f32*, 0xD4) * lbl_8_rodata_1D84);
	}
}

void fn_8_B8810(void* arg0)
{
	RwFrame* temp_r30;
	f32 temp_f2;
	u32 temp_r3_2;
	void* temp_r3;

	temp_r3 = M2C_FIELD(arg0, void**, 0xE0);
	if (temp_r3 != NULL) {
		temp_r30 = M2C_FIELD(temp_r3, RwFrame**, 4);
		fn_8019ED68(temp_r30, &lbl_80239990, 0, M2C_FIELD(arg0, f32*, 0xF4));
		fn_8019ED68(temp_r30, &lbl_80239978, 2, M2C_FIELD(arg0, f32*, 0xF0));
		fn_8019ED68(
		    temp_r30, &lbl_80239984, 2, lbl_8_rodata_1D70 * (f32)M2C_FIELD(arg0, s32*, 0xC0));
		fn_8019EB94(temp_r30, (u8*)arg0 + 0xB0, 2);
	}
	M2C_FIELD(arg0, f32*, 0xB4) = (f32)(M2C_FIELD(arg0, f32*, 0xB4) + lbl_8_rodata_1D98);
	temp_f2                     = M2C_FIELD(arg0, f32*, 0xC8);
	M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
	if ((M2C_FIELD(arg0, f32*, 0xB4) - temp_f2) == lbl_8_rodata_1D9C) {
		M2C_FIELD(arg0, f32*, 0xB4) = (f32)(lbl_8_rodata_1D9C + temp_f2);
	}
	M2C_FIELD(arg0, u32*, 0xEC) = (u32)(M2C_FIELD(arg0, u32*, 0xEC) + 0x800);
	M2C_FIELD(arg0, f32*, 0xF0)
	    = (f32)(lbl_8_rodata_1D60 * fn_800D7B00(M2C_FIELD(arg0, u32*, 0xEC)));
	temp_r3_2                   = M2C_FIELD(arg0, u32*, 0xEC);
	M2C_FIELD(arg0, f32*, 0xF4) = (f32)(lbl_8_rodata_1D60
	    * fn_800D7B00((u32)((s32)((temp_r3_2 >> 0x1FU) + temp_r3_2) >> 1)));
}

void fn_8_B8970(TObject* arg0)
{
	RwFrame* temp_r30;
	RwFrame* temp_r30_2;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f2_3;
	f32 temp_f2_4;
	f32 temp_f2_5;
	s32 temp_r0;
	s32 temp_r3;
	s32 var_r0;
	u32 temp_r3_3;
	u8 var_r5;
	u8 var_r6;
	void* temp_r3_2;
	void* temp_r3_4;

	var_r5  = 1;
	var_r6  = 1;
	temp_r3 = M2C_FIELD(&lbl_8029C310, s32*, 0x18) - 1;
	if ((u32)((u32)((1 | ~temp_r3) - ((u32)(1 - temp_r3) >> 1U)) >> 0x1FU) == 0) {
		var_r6 = 0;
	}
	if ((var_r6 == 0) && ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x18) != 3)) {
		var_r5 = 0;
	}
	if ((s32)var_r5 != 0) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	if ((s32)arg0->unkE8 != 3) {
		if (fn_800D71DC((u8*)arg0 + 0xB0, lbl_8042C208) > lbl_8_rodata_1DA0) {
			arg0->unkE8 = 3;
		}
		fn_80137FE8((M2C_UNK*)((u8*)arg0 + 0xDC));
		if ((s32)arg0->unkDC < 0) {
			arg0->unkE8 = 3;
		}
	}
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	if (var_r0 == 0) {
		fn_8003BE78((u8*)arg0 + 0x28);
		return;
	}
	temp_r0 = arg0->unkE8;
	switch (temp_r0) { /* irregular */
		case 4:
			break;
		case 0:
			arg0->unkE8 = 1;
			break;
		case 1:
			temp_r3_2 = arg0->unkE0;
			if (temp_r3_2 != NULL) {
				temp_r30 = M2C_FIELD(temp_r3_2, RwFrame**, 4);
				fn_8019ED68(temp_r30, &lbl_80239990, 0, arg0->unkF4);
				fn_8019ED68(temp_r30, &lbl_80239978, 2, arg0->unkF0);
				fn_8019ED68(temp_r30, &lbl_80239984, 2, lbl_8_rodata_1D70 * (f32)arg0->unkC0);
				fn_8019EB94(temp_r30, (u8*)arg0 + 0xB0, 2);
			}
			arg0->unkB4 += lbl_8_rodata_1D98;
			temp_f2 = arg0->unkC8;
			M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
			if ((arg0->unkB4 - temp_f2) == lbl_8_rodata_1D9C) {
				arg0->unkB4 = lbl_8_rodata_1D9C + temp_f2;
			}
			arg0->unkEC += 0x800;
			arg0->unkF0 = lbl_8_rodata_1D60 * fn_800D7B00(arg0->unkEC);
			temp_r3_3   = arg0->unkEC;
			arg0->unkF4 = lbl_8_rodata_1D60
			    * fn_800D7B00((u32)((s32)((temp_r3_3 >> 0x1FU) + temp_r3_3) >> 1));
			break;
		case 2:
			temp_f2_2 = arg0->unkF0;
			if ((f32)__fabs(temp_f2_2) > lbl_8_rodata_1D68) {
				arg0->unkF0 = temp_f2_2 * lbl_8_rodata_1D6C;
			}
			temp_f2_3 = arg0->unkF4;
			if ((f32)__fabs(temp_f2_3) > lbl_8_rodata_1D68) {
				arg0->unkF4 = temp_f2_3 * lbl_8_rodata_1D6C;
			}
			temp_r3_4 = arg0->unkE0;
			if (temp_r3_4 != NULL) {
				temp_r30_2 = M2C_FIELD(temp_r3_4, RwFrame**, 4);
				fn_8019ED68(temp_r30_2, &lbl_80239990, 0, arg0->unkF4);
				fn_8019ED68(temp_r30_2, &lbl_80239978, 2, arg0->unkF0);
				fn_8019ED68(temp_r30_2, &lbl_80239984, 2, lbl_8_rodata_1D70 * (f32)arg0->unkC0);
				fn_8019EB94(temp_r30_2, (u8*)arg0 + 0xB0, 2);
			}
			temp_f1     = arg0->unkCC;
			arg0->unkCC = temp_f1 + (lbl_8_rodata_1D74 * -temp_f1);
			temp_f2_4   = arg0->unkD0;
			arg0->unkD0 = temp_f2_4 + ((lbl_8_rodata_1D78 * -temp_f2_4) - lbl_8_rodata_1D7C);
			temp_f1_2   = arg0->unkD4;
			arg0->unkD4 = temp_f1_2 + (lbl_8_rodata_1D74 * -temp_f1_2);
			arg0->unkB0 += arg0->unkCC;
			arg0->unkB4 += arg0->unkD0;
			arg0->unkB8 += arg0->unkD4;
			temp_f2_5 = arg0->unkC8;
			if ((temp_f2_5 > arg0->unkB4) && (arg0->unkD0 < lbl_8_rodata_1D80)) {
				arg0->unkB4 = temp_f2_5;
				arg0->unkCC *= lbl_8_rodata_1D84;
				arg0->unkD0 *= lbl_8_rodata_1D88;
				arg0->unkD4 *= lbl_8_rodata_1D84;
			}
			break;
		case 3:
			arg0->unkE4 -= lbl_8_rodata_1DA4;
			if (arg0->unkE4 < lbl_8_rodata_1D80) {
				arg0->unkE4              = lbl_8_rodata_1D80;
				M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			}
			break;
	}
	if ((s32)arg0->unkE8 != 3) {
		fn_80021824(&lbl_8042C1A4);
		if (fn_80020BD8((u8*)arg0 + 0x28, 0xA) != 0U) {
			arg0->unkE8 = 1;
		} else {
			arg0->unkE8 = 2;
			arg0->unkEC = 0;
		}
	}
	if (fn_80017800(arg0) != 0) {
		arg0->unkA4 = arg0->unk88;
		arg0->unkA8 = arg0->unk8C;
		arg0->unkAC = arg0->unk90;
		arg0->unk88 = arg0->unkB0;
		arg0->unk8C = arg0->unkB4;
		arg0->unk90 = arg0->unkB8;
		arg0->unk94 = arg0->unkBC;
		arg0->unk98 = arg0->unkC0;
		arg0->unk9C = arg0->unkC4;
		fn_8003BC38(&arg0->unk28);
	}
}

TObject* fn_8_B8F34(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = (M2C_UNK*)lbl_8_data_179DC;
		if ((u32)arg0->unkE0 != NULL) {
			fn_80150958((void*)arg0->unkE0);
			arg0->unkE0 = NULL;
		}
		dtor_8003C52C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_B8FD0(TObject* arg0, TObject* arg1, void* arg2)
{
	s32 sp8;
	f32 temp_f0;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8003C618(&arg0->unk28);
	temp_f0     = lbl_8_rodata_1D80;
	arg0->unk18 = (M2C_UNK*)lbl_8_data_179DC;
	arg0->unkB8 = temp_f0;
	arg0->unkB4 = temp_f0;
	arg0->unkB0 = temp_f0;
	arg0->unkC4 = 0;
	arg0->unkC0 = 0;
	arg0->unkBC = 0;
	arg0->unkC8 = temp_f0;
	arg0->unkD4 = temp_f0;
	arg0->unkCC = temp_f0;
	arg0->unkD0 = lbl_8_rodata_1DA8;
	arg0->unkD8 = 8;
	arg0->unkDC = 0x4B0;
	arg0->unk0  = (M2C_UNK*)lbl_8_data_179D8;
	arg0->unk1E = 0xF8;
	arg0->unkE8 = 0;
	arg0->unkB0 = M2C_FIELD(arg2, f32*, 0);
	arg0->unkB4 = M2C_FIELD(arg2, f32*, 4);
	arg0->unkB8 = M2C_FIELD(arg2, f32*, 8);
	arg0->unkBC = M2C_FIELD(arg2, s32*, 0xC);
	arg0->unkC0 = M2C_FIELD(arg2, s32*, 0x10);
	arg0->unkC4 = M2C_FIELD(arg2, s32*, 0x14);
	arg0->unkC8 = M2C_FIELD(arg2, f32*, 0x18);
	arg0->unkCC = M2C_FIELD(arg2, f32*, 0x1C);
	arg0->unkD0 = M2C_FIELD(arg2, f32*, 0x20);
	arg0->unkD4 = M2C_FIELD(arg2, f32*, 0x24);
	arg0->unkD8 = M2C_FIELD(arg2, s32*, 0x28);
	arg0->unkDC = M2C_FIELD(arg2, s32*, 0x2C);
	arg0->unkEC = 0;
	arg0->unkF4 = temp_f0;
	arg0->unkF0 = temp_f0;
	arg0->unkE4 = lbl_8_rodata_1D5C;
	arg0->unkC8 = fn_800D8BC4(&arg0->unkB0, &sp8, 1);
	arg0->unkE0 = fn_80150588(lbl_8_bss_1AC8[2]);
	fn_8003C200(&arg0->unk28, (M2C_UNK*)lbl_8_data_17994, 1, 3);
	arg0->unk88 = arg0->unkB0;
	arg0->unk8C = arg0->unkB4;
	arg0->unk90 = arg0->unkB8;
	arg0->unk30 &= 0xFFFFFFBF;
	return arg0;
}

#pragma inline_max_size(5000)
static inline TObject* wallCreateObject(void* arg0)
{
	s32 sp8;
	TObject* temp_r3;
	f32 temp_f1;

	temp_r3 = fn_80018A34(lbl_8042C148, 0xF8);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		fn_8003C618(&temp_r3->unk28);
		temp_f1                        = lbl_8_rodata_1D80;
		temp_r3->unk18                 = (M2C_UNK*)lbl_8_data_179DC;
		temp_r3->unkB8                 = temp_f1;
		temp_r3->unkB4                 = temp_f1;
		temp_r3->unkB0                 = temp_f1;
		temp_r3->unkC4                 = 0;
		temp_r3->unkC0                 = 0;
		temp_r3->unkBC                 = 0;
		temp_r3->unkC8                 = temp_f1;
		temp_r3->unkD4                 = temp_f1;
		temp_r3->unkCC                 = temp_f1;
		temp_r3->unkD0                 = lbl_8_rodata_1DA8;
		temp_r3->unkD8                 = 8;
		temp_r3->unkDC                 = 0x4B0;
		temp_r3->unk0                  = (M2C_UNK*)lbl_8_data_179D8;
		temp_r3->unk1E                 = 0xF8;
		temp_r3->unkE8                 = 0;
		M2C_FIELD(temp_r3, s32*, 0xB0) = M2C_FIELD(arg0, s32*, 0);
		M2C_FIELD(temp_r3, s32*, 0xB4) = M2C_FIELD(arg0, s32*, 4);
		M2C_FIELD(temp_r3, s32*, 0xB8) = M2C_FIELD(arg0, s32*, 8);
		temp_r3->unkBC                 = M2C_FIELD(arg0, s32*, 0xC);
		temp_r3->unkC0                 = M2C_FIELD(arg0, s32*, 0x10);
		temp_r3->unkC4                 = M2C_FIELD(arg0, s32*, 0x14);
		temp_r3->unkC8                 = M2C_FIELD(arg0, f32*, 0x18);
		M2C_FIELD(temp_r3, s32*, 0xCC) = M2C_FIELD(arg0, s32*, 0x1C);
		M2C_FIELD(temp_r3, s32*, 0xD0) = M2C_FIELD(arg0, s32*, 0x20);
		M2C_FIELD(temp_r3, s32*, 0xD4) = M2C_FIELD(arg0, s32*, 0x24);
		temp_r3->unkD8                 = M2C_FIELD(arg0, s32*, 0x28);
		temp_r3->unkDC                 = M2C_FIELD(arg0, s32*, 0x2C);
		temp_r3->unkEC                 = 0;
		temp_r3->unkF4                 = temp_f1;
		temp_r3->unkF0                 = temp_f1;
		temp_r3->unkE4                 = lbl_8_rodata_1D5C;
		temp_r3->unkC8                 = fn_800D8BC4(&temp_r3->unkB0, &sp8, 1);
		temp_r3->unkE0                 = fn_80150588(lbl_8_bss_1AC8[2]);
		fn_8003C200(&temp_r3->unk28, (M2C_UNK*)lbl_8_data_17994, 1, 3);
		temp_r3->unk88 = temp_r3->unkB0;
		temp_r3->unk8C = temp_r3->unkB4;
		temp_r3->unk90 = temp_r3->unkB8;
		temp_r3->unk30 &= 0xFFFFFFBF;
	}
	return temp_r3;
}

TObject* fn_8_B9174(void* arg0)
{
	return wallCreateObject(arg0);
}

void fn_8_B934C(void* arg0)
{
	f32 temp_f0;

	temp_f0                     = lbl_8_rodata_1D80;
	M2C_FIELD(arg0, f32*, 8)    = (f32)temp_f0;
	M2C_FIELD(arg0, f32*, 4)    = (f32)temp_f0;
	M2C_FIELD(arg0, f32*, 0)    = (f32)temp_f0;
	M2C_FIELD(arg0, s32*, 0x14) = 0;
	M2C_FIELD(arg0, s32*, 0x10) = 0;
	M2C_FIELD(arg0, s32*, 0xC)  = 0;
	M2C_FIELD(arg0, f32*, 0x18) = (f32)temp_f0;
	M2C_FIELD(arg0, f32*, 0x24) = (f32)temp_f0;
	M2C_FIELD(arg0, f32*, 0x1C) = (f32)temp_f0;
	M2C_FIELD(arg0, f32*, 0x20) = (f32)lbl_8_rodata_1DA8;
	M2C_FIELD(arg0, s32*, 0x28) = 8;
	M2C_FIELD(arg0, s32*, 0x2C) = 0x4B0;
}

void fn_8_B93A4(void* arg0)
{
	sAngle sp8;
	sAngle sp14;
	RwV3d sp20;
	s32 temp_cr0_eq;

	M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x200);
	temp_cr0_eq                  = (u32)(M2C_FIELD(arg0, s32*, 0x188) & 0x10) == 0;
	if (temp_cr0_eq == 0) {
		M2C_FIELD(&sp20, M2C_BLOCK12*, 0) = M2C_FIELD(arg0, M2C_BLOCK12*, 0x140);
		sp20.y += lbl_8_rodata_1D60;
		M2C_FIELD(&sp14, M2C_BLOCK12*, 0) = M2C_FIELD(arg0, M2C_BLOCK12*, 0x14C);
		if (temp_cr0_eq == 0) {
			fn_8006298C(6, &sp20.x, &sp14.x);
			fn_8006298C(2, &sp20.x, &sp14.x);
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0xE017, &sp20.x, 0, 1, 2, 0);
			}
			fn_8006298C(0xF, &sp20.x, &sp14.x);
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
				fn_80100AAC();
			}
			if (fn_8010037C(lbl_8042C590, 8, 2) != 0U) {
				M2C_FIELD(&sp8, M2C_BLOCK12*, 0) = M2C_FIELD(&lbl_8_rodata_1CB8, M2C_BLOCK12*, 0);
				sp14.y += 0x8000;
				fn_80102C50(lbl_8042C2A0, &sp20.x, &sp14.x, &sp8.x, 0, 0, 0, lbl_8_rodata_1DAC,
				    lbl_8_rodata_1D80);
			}
		}
	}
}

void fn_8_B9548(void* arg0, s32 arg1)
{
	fn_8_90B10(arg1);
}

void fn_8_B956C(void* arg0)
{
	s32 temp_r0_2;
	u8 temp_r0;
	void* temp_r30;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;

	if (fn_800A2D50() != 0) {
		temp_r3                        = M2C_FIELD(arg0, void**, 0xB0);
		M2C_FIELD(temp_r3, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3, s32*, 0x18) | 0x01000000);
	}
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(void*), 0x7C)(arg0);
	temp_r0 = M2C_FIELD(lbl_8042C180, u8*, 0x24);
	if ((((s8)temp_r0 == 4) || ((s8)temp_r0 == 8))
	    && (((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 4)
	        || ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 5))) {
		temp_r3_2                        = M2C_FIELD(arg0, void**, 0xB0);
		M2C_FIELD(temp_r3_2, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3_2, s32*, 0x18) | 0x10000000);
		temp_r3_3                        = M2C_FIELD(arg0, void**, 0xB0);
		M2C_FIELD(temp_r3_3, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3_3, s32*, 0x18) | 0x200);
	}
	fn_8005BC04((u8*)arg0 + 0xB0);
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(void*), 0x40)(arg0);
	temp_r0_2 = M2C_FIELD(arg0, s32*, 0x230);
	if (temp_r0_2 != -1) {
		temp_r3_4 = (void*)(u32) * (&lbl_802AD070 + (temp_r0_2 * 4));
		if (temp_r3_4 != NULL) {
			temp_r30 = (void*)(u32) * (&lbl_80303DC8 + ((s8)M2C_FIELD(temp_r3_4, u8*, 0x9BC) * 4));
			if (temp_r30 != NULL) {
				fn_8011CE44();
				fn_8011C9A0((u8*)arg0 + 0x140,
				    (s8)M2C_FIELD(
				        ((u8*)temp_r30 + (s8)M2C_FIELD(temp_r30, u8*, 0x3A)), u8*, 0x110));
				M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(void*, void*), 0x88)(
				    arg0, (u8*)arg0 + 0x140);
			}
		}
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x230) != -1) {
		if ((u32)lbl_8042C6D0 == 0U) {
			fn_8011C6EC();
		}
		fn_8011C1DC(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x230));
	}
	if ((u32)lbl_8042C6D0 == 0U) {
		fn_8011C6EC();
	}
	fn_8011C0E8(lbl_8042C6D0);
}

void fn_8_B9724(void* arg0, void* arg1)
{
	f32 temp_f0;
	f32 var_f1;

	var_f1  = M2C_FIELD(arg1, f32*, 0x14) + M2C_FIELD(arg0, f32*, 0x1A4);
	temp_f0 = M2C_FIELD(arg0, f32*, 0x264);
	if (var_f1 > temp_f0) {
		var_f1 = temp_f0;
	}
	M2C_FIELD(arg0, f32*, 0x1A4) = var_f1;
	M2C_FIELD(arg0, s16*, 0x2E)  = (s16)var_f1;
	M2C_FIELD(arg0, f32*, 0x260) = (f32)M2C_FIELD(arg0, f32*, 0x1A4);
	if ((u32)M2C_FIELD(arg0, u32*, 0x26C) != 0U) {
		fn_8010B074(M2C_FIELD(arg0, u32*, 0x26C));
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x268) != 0U) {
		fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x268), 6);
		fn_8010B208(M2C_FIELD(arg0, u32*, 0x268), lbl_8_rodata_1D80, lbl_8_rodata_1D80);
	}
}

void fn_8_B97C0(void* arg0, void* arg1)
{
	f32 temp_f1;
	f32 var_f0;

	if ((s32)M2C_FIELD(arg1, u8*, 0) != 3) {
		return;
	}
	var_f0  = M2C_FIELD(arg1, f32*, 0x14) + M2C_FIELD(arg0, f32*, 0x1A4);
	temp_f1 = M2C_FIELD(arg0, f32*, 0x264);
	if (var_f0 > temp_f1) {
		var_f0 = temp_f1;
	}
	M2C_FIELD(arg0, f32*, 0x1A4) = var_f0;
	M2C_FIELD(arg0, s16*, 0x2E)  = (s16)var_f0;
	M2C_FIELD(arg0, f32*, 0x260) = (f32)M2C_FIELD(arg0, f32*, 0x1A4);
	if ((u32)M2C_FIELD(arg0, u32*, 0x26C) != 0U) {
		fn_8010B074(M2C_FIELD(arg0, u32*, 0x26C));
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x268) != 0U) {
		fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x268), 6);
		fn_8010B208(M2C_FIELD(arg0, u32*, 0x268), lbl_8_rodata_1D80, lbl_8_rodata_1D80);
	}
}

void fn_8_B986C(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x304) == 0) {
		if ((u32)lbl_8042C6D0 == 0U) {
			fn_8011C6EC();
		}
		fn_8011C1F8(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x230), 0x1F4);
		return;
	}
	if ((u32)lbl_8042C6D0 == 0U) {
		fn_8011C6EC();
	}
	fn_8011C1F8(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x230), 0x3E8);
}

void fn_8_B9904(TObject* arg0, s32 arg1)
{
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r4;
	void* temp_r4_10;
	void* temp_r4_11;
	void* temp_r4_12;
	void* temp_r4_2;
	void* temp_r4_3;
	void* temp_r4_4;
	void* temp_r4_5;
	void* temp_r4_6;
	void* temp_r4_7;
	void* temp_r4_8;
	void* temp_r4_9;
	void* temp_r5;

	temp_r5 = arg0->unk38;
	if (temp_r5 != NULL) {
		switch (arg1) { /* irregular */
			case 0:
				if (temp_r5 != NULL) {
					M2C_FIELD(temp_r5, s32*, 4) = (s32)(M2C_FIELD(temp_r5, s32*, 4) & 0xFFFDFFFF);
				}
				temp_r4 = (u8*)arg0->unk38 + 0x30;
				if (temp_r4 != NULL) {
					M2C_FIELD(temp_r4, s32*, 4) = (s32)(M2C_FIELD(temp_r4, s32*, 4) & 0xFFFDFFFF);
				}
				temp_r4_2 = (u8*)arg0->unk38 + 0x60;
				if (temp_r4_2 != NULL) {
					M2C_FIELD(temp_r4_2, s32*, 4)
					    = (s32)(M2C_FIELD(temp_r4_2, s32*, 4) & 0xFFFDFFFF);
				}
				temp_r4_3 = (u8*)arg0->unk38 + 0x90;
				if (temp_r4_3 != NULL) {
					M2C_FIELD(temp_r4_3, s32*, 4)
					    = (s32)(M2C_FIELD(temp_r4_3, s32*, 4) & 0xFFFDFFFF);
				}
				temp_r4_4 = (u8*)arg0->unk38 + 0xC0;
				if (temp_r4_4 != NULL) {
					M2C_FIELD(temp_r4_4, s32*, 4)
					    = (s32)(M2C_FIELD(temp_r4_4, s32*, 4) & 0xFFFDFFFF);
				}
				temp_r3 = (u8*)arg0->unk38 + 0xF0;
				if (temp_r3 != NULL) {
					M2C_FIELD(temp_r3, s32*, 4) = (s32)(M2C_FIELD(temp_r3, s32*, 4) & 0xFFFDFFFF);
					return;
				}
				break;
			case 1:
				if (temp_r5 != NULL) {
					M2C_FIELD(temp_r5, s32*, 4) = (s32)(M2C_FIELD(temp_r5, s32*, 4) | 0x20000);
				}
				temp_r4_5 = (u8*)arg0->unk38 + 0x30;
				if (temp_r4_5 != NULL) {
					M2C_FIELD(temp_r4_5, s32*, 4) = (s32)(M2C_FIELD(temp_r4_5, s32*, 4) | 0x20000);
				}
				temp_r4_6 = (u8*)arg0->unk38 + 0x60;
				if (temp_r4_6 != NULL) {
					M2C_FIELD(temp_r4_6, s32*, 4) = (s32)(M2C_FIELD(temp_r4_6, s32*, 4) | 0x20000);
				}
				temp_r4_7 = (u8*)arg0->unk38 + 0x90;
				if (temp_r4_7 != NULL) {
					M2C_FIELD(temp_r4_7, s32*, 4) = (s32)(M2C_FIELD(temp_r4_7, s32*, 4) | 0x20000);
				}
				temp_r4_8 = (u8*)arg0->unk38 + 0xC0;
				if (temp_r4_8 != NULL) {
					M2C_FIELD(temp_r4_8, s32*, 4) = (s32)(M2C_FIELD(temp_r4_8, s32*, 4) | 0x20000);
				}
				temp_r3_2 = (u8*)arg0->unk38 + 0xF0;
				if (temp_r3_2 != NULL) {
					M2C_FIELD(temp_r3_2, s32*, 4) = (s32)(M2C_FIELD(temp_r3_2, s32*, 4) | 0x20000);
					return;
				}
				break;
			case 2:
				if (temp_r5 != NULL) {
					M2C_FIELD(temp_r5, s32*, 4) = (s32)(M2C_FIELD(temp_r5, s32*, 4) | 0x20000);
				}
				temp_r4_9 = (u8*)arg0->unk38 + 0x30;
				if (temp_r4_9 != NULL) {
					M2C_FIELD(temp_r4_9, s32*, 4) = (s32)(M2C_FIELD(temp_r4_9, s32*, 4) | 0x20000);
				}
				temp_r4_10 = (u8*)arg0->unk38 + 0x60;
				if (temp_r4_10 != NULL) {
					M2C_FIELD(temp_r4_10, s32*, 4)
					    = (s32)(M2C_FIELD(temp_r4_10, s32*, 4) | 0x20000);
				}
				temp_r4_11 = (u8*)arg0->unk38 + 0x90;
				if (temp_r4_11 != NULL) {
					M2C_FIELD(temp_r4_11, s32*, 4)
					    = (s32)(M2C_FIELD(temp_r4_11, s32*, 4) | 0x20000);
				}
				temp_r4_12 = (u8*)arg0->unk38 + 0xC0;
				if (temp_r4_12 != NULL) {
					M2C_FIELD(temp_r4_12, s32*, 4)
					    = (s32)(M2C_FIELD(temp_r4_12, s32*, 4) | 0x20000);
				}
				temp_r3_3 = (u8*)arg0->unk38 + 0xF0;
				if (temp_r3_3 != NULL) {
					M2C_FIELD(temp_r3_3, s32*, 4)
					    = (s32)(M2C_FIELD(temp_r3_3, s32*, 4) & 0xFFFDFFFF);
					return;
				}
				break;
		}
	}
}

void fn_8_B9B20(void* arg0)
{
	s32 temp_r3;

	if (((s32)M2C_FIELD(arg0, s32*, 0x19C) == 0x33) && ((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
	    && (fn_800209C8((u8*)arg0 + 0x28, 5) != 0U)) {
		M2C_FIELD(arg0, s32*, 0x280) = (s32)(M2C_FIELD(arg0, s32*, 0x280) + 1);
	}
	temp_r3 = M2C_FIELD(arg0, s32*, 0x284);
	if (temp_r3 > 0) {
		M2C_FIELD(arg0, s32*, 0x284) = (s32)(temp_r3 - 1);
	}
	fn_800A3F60(arg0);
}

s32 fn_8_B9BA0(void* arg0)
{
	return M2C_FIELD(arg0, s32*, 0x280) >= 3;
}

s32 fn_8_B9BBC(void* arg0)
{
	RwV3d sp8;
	M2C_UNK* temp_r3;
	f32 temp_f1;
	s32 var_r31;

	var_r31 = 0;
	temp_f1 = M2C_FIELD(arg0, f32*, 0x1A4);
	if (temp_f1 != M2C_FIELD(arg0, f32*, 0x260)) {
		M2C_FIELD(arg0, f32*, 0x260) = temp_f1;
		if ((u32)M2C_FIELD(arg0, u32*, 0x26C) != 0U) {
			if ((s32)M2C_FIELD(arg0, s32*, 0x19C) == 0x24) {
				fn_8010B0AC(
				    M2C_FIELD(arg0, u32*, 0x26C), 0x5A, temp_f1, M2C_FIELD(arg0, f32*, 0x264));
			} else {
				fn_8010B208(M2C_FIELD(arg0, u32*, 0x26C), temp_f1, M2C_FIELD(arg0, f32*, 0x264));
			}
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x268) != 0U) {
			fn_8010B074(M2C_FIELD(arg0, u32*, 0x268));
		}
		var_r31 = 1;
	}
	M2C_FIELD(&sp8, M2C_BLOCK12*, 0) = M2C_FIELD(arg0, M2C_BLOCK12*, 0x140);
	if ((u32)M2C_FIELD(arg0, u32*, 0x2C4) != 0U) {
		temp_r3 = fn_8019E8EC(M2C_FIELD(arg0, u32*, 0x2C4));
		sp8.x   = M2C_FIELD(temp_r3, f32*, 0x30);
		sp8.y   = M2C_FIELD(temp_r3, f32*, 0x34);
		sp8.z   = M2C_FIELD(temp_r3, f32*, 0x38);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x26C) != 0U) {
		fn_8010B350(&sp8.x, &lbl_8_rodata_1CC4);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x268) != 0U) {
		fn_8010B350(&sp8.x, &lbl_8_rodata_1CC4);
	}
	if (var_r31 != 0) {
		M2C_FIELD(arg0, s32*, 0x28C) = 0x78;
	}
	return var_r31;
}

s32 fn_8_B9CD4(void* arg0)
{
	f32 temp_f1;
	s32 temp_r0;
	u32 temp_r4;

	temp_r0 = M2C_FIELD(arg0, s32*, 0x270);
	if (temp_r0 != -1) {
		temp_r4 = *(&lbl_802AD090 + (temp_r0 * 4));
		if (temp_r4 != 0U) {
			temp_f1 = fn_800D71DC((u8*)arg0 + 0x140, temp_r4 + 0x18);
			M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
			if (temp_f1 == lbl_8_rodata_1DB0) {
				return 1;
			}
			M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
			if (temp_f1 == lbl_8_rodata_1DB4) {
				return 2;
			}
			return 0;
		}
	}
	return 0;
}

s32 fn_8_B9D6C(TObject* arg0)
{
	s32 temp_r31;
	s32 var_r0;

	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	if (var_r0 == 0) {
		return 0;
	}
	temp_r31     = fn_800A5A54(arg0);
	arg0->unk150 = fn_800D7A94(arg0->unk150, arg0->unk174, arg0->unk180);
	if (temp_r31 < 0x80) {
		arg0->unk150 = arg0->unk174;
		return 1;
	}
	return 0;
}

s32 fn_8_B9E40(void* arg0)
{
	s32 temp_r3;

	temp_r3 = fn_800A6334();
	if ((temp_r3 == 1) && ((u32)M2C_FIELD(arg0, u32*, 0x268) != 0U)
	    && (((u32)M2C_FIELD(arg0, u32*, 0x26C) == 0U) || (fn_8010AFB0() == 0))) {
		fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x268), 1);
		fn_8010B208(M2C_FIELD(arg0, u32*, 0x268), lbl_8_rodata_1D80, lbl_8_rodata_1D80);
	}
	return temp_r3;
}

s32 fn_8_B9ECC(TObject* arg0, f32 farg0, f32 farg1)
{
	s32 temp_r29;
	s32 var_r0;
	s32 var_r31;

	var_r31 = 1;
	if ((s32)arg0->unk294 == 0) {
		return 1;
	}
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
		temp_r29     = fn_800A5A54(arg0);
		arg0->unk150 = fn_800D7A94(arg0->unk150, arg0->unk174, arg0->unk180);
		if (temp_r29 < 0x80) {
			arg0->unk150 = arg0->unk174;
		}
	}
	if ((fn_800A5AC0(arg0) < farg1) || ((s32)(arg0->unk106 & 4) != 0)) {
		fn_800A4668(arg0);
		var_r31 = 0;
	} else {
		fn_800A4A8C(arg0, farg0);
	}
	fn_800A5C6C(arg0, 0xF00);
	fn_800A5C6C(arg0, 0x200);
	if (((s32)(arg0->unk106 & 2) != 0) && (arg0->unk15C < (lbl_8_rodata_1DB8 * arg0->unk1A8))) {
		arg0->unk15C = lbl_8_rodata_1D80;
	}
	if (fn_800A5888(arg0, &lbl_8_rodata_1DA8, lbl_8_rodata_1DA8) != 0) {
		var_r31 = 0;
	} else if ((((s32)(arg0->unk106 & 4) != 0)
	               || (fn_800D7218(&arg0->unk140, &arg0->unk1E4) < lbl_8_rodata_1D78))
	    && (fn_800A5998(arg0) <= 0)) {
		var_r31 = 0;
	}
	return var_r31;
}

void fn_8_BA0D4(void* arg0)
{
	RwV3d spC;
	f32 sp8;
	f32* var_r3;
	f32 temp_f1;
	f32 temp_f1_2;

	fn_800B7864(0);
	M2C_FIELD(&spC, M2C_BLOCK12*, 0) = M2C_FIELD(&lbl_8_rodata_1D10, M2C_BLOCK12*, 0);
	temp_f1                          = lbl_8_rodata_1D5C
	    - (lbl_8_rodata_1D64 * (M2C_FIELD(arg0, f32*, 0x144) - M2C_FIELD(arg0, f32*, 0x2D8)));
	sp8    = temp_f1;
	var_r3 = &lbl_8_rodata_1D54;
	if (temp_f1 < lbl_8_rodata_1D54) {

	} else {
		var_r3 = &lbl_8_rodata_1D58;
		if (temp_f1 > lbl_8_rodata_1D58) {

		} else {
			var_r3 = &sp8;
		}
	}
	temp_f1_2 = *var_r3;
	sp8       = temp_f1_2;
	fn_800B7514((f32*)((u8*)arg0 + 0x2D4), (s32*)((u8*)arg0 + 0x2F8), &spC.x, temp_f1_2);
	spC.x = lbl_8_rodata_1DBC;
	spC.z = lbl_8_rodata_1D60;
	fn_800B7514((f32*)((u8*)arg0 + 0x2E0), (s32*)((u8*)arg0 + 0x2F8), &spC.x, sp8);
	fn_800B7514((f32*)((u8*)arg0 + 0x2EC), (s32*)((u8*)arg0 + 0x2F8), &spC.x, sp8);
	fn_800B7820();
}

void fn_8_BA1EC(void* arg0)
{
	s32 temp_r4;

	if ((s32)M2C_FIELD(arg0, s32*, 0x29C) == 1) {
		fn_80113940();
		fn_801138B4();
		fn_80113874(M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), s32(**)(void*), 0x90)(arg0));
		temp_r4 = M2C_FIELD(lbl_8042C180, s32*, 0x30);
		if ((s32)lbl_8_bss_1B24 != temp_r4) {
			lbl_8_bss_1B24 = temp_r4;
			fn_8011B844(lbl_8_bss_1ADC, &lbl_8_rodata_1D5C, lbl_8_rodata_1D5C);
			fn_8014FFBC(lbl_8_bss_1AC8[4], &fn_8005BF88, lbl_8_bss_1AE0);
		}
		fn_8014FF2C(M2C_FIELD(arg0, s32**, 0x2D0));
		fn_801138F4();
	}
}

void fn_8_BA2B0(void* arg0)
{
	sVec4i sp8;

	fn_80113874(M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), s32(**)(), 0x90)());
	fn_8014FF2C(M2C_FIELD(arg0, s32**, 0xE8));
	if (((s32)M2C_FIELD(arg0, s32*, 0x288) != 0) && ((s32*)M2C_FIELD(arg0, s32**, 0x2C8) != NULL)) {
		M2C_FIELD(&sp8, M2C_BLOCK16*, 0) = M2C_FIELD(&lbl_8_rodata_1D00, M2C_BLOCK16*, 0);
		fn_8005DABC(&sp8.x, &lbl_8_rodata_1D00);
		fn_8014FF2C(M2C_FIELD(arg0, s32**, 0x2C8));
	}
	if ((s32*)M2C_FIELD(arg0, s32**, 0x2CC) != NULL) {
		fn_80113874(0x10);
		fn_8011398C(&wallObjectGlobalA, M2C_FIELD(arg0, s32*, 0x290));
		fn_8014FF2C(M2C_FIELD(arg0, s32**, 0x2CC));
	}
}

void fn_8_BA370(TObject* arg0)
{
	fn_8_BCB60(arg0);
	fn_8_BC2CC(arg0);
}

void fn_8_BA3A4(TObject* arg0)
{
	sWallObjParam sp14;
	M2C_UNK* temp_r3_2;
	s32 temp_r0;
	s32 temp_r30;
	s32 temp_r3_3;
	s32 var_r0;
	s32 var_r0_2;
	void** temp_r3;
	void* temp_r4;

	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	arg0->unk294 = var_r0;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0_2 = 0;
	} else {
		var_r0_2 = 1;
	}
	arg0->unk298 = var_r0_2;
	if ((void*)arg0->unk38 != NULL) {
		arg0->unk140 = arg0->unk88;
		arg0->unk144 = arg0->unk8C;
		arg0->unk148 = arg0->unk90;
	}
	fn_800A5B34(arg0);
	M2C_FIELD(arg0->unk18, M2C_UNK(**)(TObject*), 0x38)(arg0);
	temp_r3 = arg0->unk240;
	if (temp_r3 != NULL) {
		M2C_FIELD(*temp_r3, M2C_UNK(**)(TObject*), 0xC)(arg0);
	}
	if (((s32)arg0->unk288 != 0) && ((void*)arg0->unk2C8 != NULL)
	    && ((u32)(arg0->unk18C & 0x1000) != 0)) {
		temp_r0 = arg0->unk19C;
		if (temp_r0 != 0x2C) {
			if ((temp_r0 < 0x2C) && (temp_r0 < 3)) {
				if (temp_r0 < 1) {

				} else {
					goto block_22;
				}
			}
		} else {
		block_22:
			sp14.unk8  = lbl_8_rodata_1D80;
			sp14.unk4  = lbl_8_rodata_1D80;
			sp14.unk0  = lbl_8_rodata_1D80;
			sp14.unk14 = 0;
			sp14.unk10 = 0;
			sp14.unkC  = 0;
			sp14.unk18 = lbl_8_rodata_1D80;
			sp14.unk24 = lbl_8_rodata_1D80;
			sp14.unk1C = lbl_8_rodata_1D80;
			sp14.unk20 = lbl_8_rodata_1DA8;
			sp14.unk28 = 8;
			sp14.unk2C = 0x4B0;
			temp_r3_2  = fn_8019E8EC(arg0->unk2C4);
			sp14.unk0  = M2C_FIELD(temp_r3_2, f32*, 0x30);
			sp14.unk4  = M2C_FIELD(temp_r3_2, f32*, 0x34);
			sp14.unk8  = M2C_FIELD(temp_r3_2, f32*, 0x38);
			sp14.unkC  = arg0->unk14C;
			temp_r3_3  = arg0->unk150;
			sp14.unk10 = temp_r3_3;
			sp14.unk14 = arg0->unk154;
			sp14.unk10 = temp_r3_3 + 0x8000;
			sp14.unk28 = M2C_FIELD(arg0->unk18, s32(**)(TObject*), 0x90)(arg0);
			wallCreateObject(&sp14);
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0x4024, &arg0->unk140, 0, 1, 0, 0);
			}
			fn_8_B9904(arg0, 2);
			arg0->unk288 = 0;
		}
	}
	M2C_FIELD(arg0->unk18, M2C_UNK(**)(TObject*, s32, M2C_UNK), 0x50)(arg0, arg0->unk19C, 1);
	fn_8_BC2CC(arg0);
	fn_800A3D48(arg0);
	if ((u32)arg0->unk2C0 != 0U) {
		temp_r4 = arg0->unk2D0;
		if (temp_r4 != NULL) {
			temp_r30 = M2C_FIELD(temp_r4, s32*, 4);
			fn_8019ECCC(temp_r30, fn_8019E8EC(arg0->unk2C0), 0);
		}
	}
	fn_8_BBF90(arg0);
	if ((s32)arg0->unk304 == 1) {
		if ((s32)arg0->unk28C < 0) {
			arg0->unk290 = 0;
		} else {
			fn_80137FE8(&arg0->unk28C);
			fn_80138050(&arg0->unk290);
			arg0->unk290 %= 3;
		}
	}
	if ((fn_80017800(arg0) != 0) && ((void*)arg0->unk38 != NULL)) {
		arg0->unkA4 = arg0->unk88;
		arg0->unkA8 = arg0->unk8C;
		arg0->unkAC = arg0->unk90;
		arg0->unk88 = arg0->unk140;
		arg0->unk8C = arg0->unk144;
		arg0->unk90 = arg0->unk148;
		arg0->unk94 = arg0->unk14C;
		arg0->unk98 = arg0->unk150;
		arg0->unk9C = arg0->unk154;
		fn_8003BC38(&arg0->unk28);
	}
}

void fn_8_BA8C0(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 8;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_BA8E0(TObject* arg0, s32 arg1)
{
	sWallObjParam sp20;
	RwV3d sp14;
	M2C_UNK* temp_r3;
	f32 temp_f0;
	f32 temp_f1;
	f32 temp_f1_2;
	s32 temp_r0;
	s32 temp_r3_2;

	switch (arg1) { /* irregular */
		case 0:
			arg0->unk274                = 0x19;
			M2C_FIELD(arg0, s32*, 0xD4) = 7;
			return;
		case 1:
			if ((s32)arg0->unk294 != 0) {
				temp_r0      = arg0->unk274 - 1;
				arg0->unk274 = temp_r0;
				if (temp_r0 == 0) {
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x4023, (f32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
					}
					if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1E) == 0) {
						fn_8004D5F4(lbl_8042C1F8, 0x32, lbl_8_rodata_1DC0);
					}
					if (((s32)arg0->unk288 != 0) && ((u32)arg0->unk2C8 != NULL)) {
						sp20.unk8  = lbl_8_rodata_1D80;
						sp20.unk4  = lbl_8_rodata_1D80;
						sp20.unk0  = lbl_8_rodata_1D80;
						sp20.unk14 = 0;
						sp20.unk10 = 0;
						sp20.unkC  = 0;
						sp20.unk18 = lbl_8_rodata_1D80;
						sp20.unk24 = lbl_8_rodata_1D80;
						sp20.unk1C = lbl_8_rodata_1D80;
						sp20.unk20 = lbl_8_rodata_1DA8;
						sp20.unk28 = 8;
						sp20.unk2C = 0x4B0;
						temp_r3    = fn_8019E8EC(arg0->unk2C4);
						sp20.unk0  = M2C_FIELD(temp_r3, f32*, 0x30);
						sp20.unk4  = M2C_FIELD(temp_r3, f32*, 0x34);
						sp20.unk8  = M2C_FIELD(temp_r3, f32*, 0x38);
						sp20.unkC  = arg0->unk14C;
						temp_r3_2  = arg0->unk150;
						sp20.unk10 = temp_r3_2;
						sp20.unk14 = arg0->unk154;
						sp20.unk10 = temp_r3_2 + 0x8000;
						sp20.unk28 = M2C_FIELD(arg0->unk18, s32(**)(TObject*), 0x90)(arg0);
						sp14.x     = sp20.unk0;
						sp14.y     = sp20.unk4;
						sp14.z     = sp20.unk8;
						sp14.x -= arg0->unk140;
						sp14.y -= arg0->unk144;
						temp_f1 = sp14.z;
						sp14.z  = temp_f1 - arg0->unk148;
						fn_801990E0(&sp14.x, &sp14.x, temp_f1);
						temp_f1_2 = lbl_8_rodata_1DC4 * sp14.x;
						sp14.x    = temp_f1_2;
						sp14.y *= lbl_8_rodata_1DC4;
						temp_f0    = lbl_8_rodata_1DC4 * sp14.z;
						sp14.z     = temp_f0;
						sp20.unk1C = temp_f1_2;
						sp20.unk24 = temp_f0;
						wallCreateObject(&sp20);
						fn_8_B9904(arg0, 2);
					}
					arg0->unk288 = 0;
				}
			}
			return;
		case 4:
			return;
	}
}

void fn_8_BACD4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, u32*, 0x274) = 0U;
			M2C_FIELD(arg0, s32*, 0x280) = 0;
			M2C_FIELD(arg0, s32*, 0xD4)  = 6;
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x294) != 0) {
				M2C_FIELD(arg0, u32*, 0x274) = (u32)(M2C_FIELD(arg0, u32*, 0x274) + 0x550);
				M2C_FIELD(arg0, f32*, 0x278)
				    = (f32)(lbl_8_rodata_1DC0 * fn_800D7B00(M2C_FIELD(arg0, u32*, 0x274)));
				M2C_FIELD(arg0, f32*, 0x27C) = (f32)(lbl_8_rodata_1DC0
				    * fn_800D7B00(
				        (u32)(s32)(lbl_8_rodata_1DC8 * (f32)M2C_FIELD(arg0, u32*, 0x274))));
			}
			return;
		case 4:
			return;
	}
}

void fn_8_BADC4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4)  = 4;
			M2C_FIELD(arg0, s32*, 0x274) = 0;
			M2C_FIELD(arg0, s32*, 0x29C) = 0;
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0x4020, (f32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
				return;
			}
		case 2:
			return;
		case 1:
			if (((s32)M2C_FIELD(arg0, s32*, 0x294) != 0)
			    && ((s32)M2C_FIELD(arg0, s32*, 0xD0) == 5)) {
				M2C_FIELD(arg0, s32*, 0x29C) = 1;
				if ((M2C_FIELD(arg0, f32*, 0xB8) > lbl_8_rodata_1DCC)
				    && ((s32)M2C_FIELD(arg0, s32*, 0x274) == 0)) {
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x4021, (f32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
					}
					M2C_FIELD(arg0, s32*, 0x274) = 1;
				}
				if ((u32)(M2C_FIELD(arg0, s32*, 0xC8) & 2) != 0) {
					M2C_FIELD(arg0, s32*, 0x29C) = 0;
					M2C_FIELD(arg0, s32*, 0x274) = 0;
					return;
				}
			}
			break;
		case 3:
			M2C_FIELD(arg0, s32*, 0x29C) = 0;
			break;
	}
}

void fn_8_BAF00(TObject* arg0, s32 arg1)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	M2C_UNK* temp_r3_2;
	s32 temp_r0;
	s32 temp_r30;
	s32 var_r0;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			arg0->unk274                = 0;
			M2C_FIELD(arg0, s32*, 0xD4) = 2;
			temp_r0                     = arg0->unk270;
			if (temp_r0 != -1) {
				temp_r3 = (void*)(u32) * (&lbl_802AD090 + (temp_r0 * 4));
				if (temp_r3 != NULL) {
					arg0->unk1CC = M2C_FIELD(temp_r3, f32*, 0x18);
					arg0->unk1D0 = M2C_FIELD(temp_r3, f32*, 0x1C);
					arg0->unk1D4 = M2C_FIELD(temp_r3, f32*, 0x20);
					return;
				}
			}
			return;
		case 1:
			if ((s32)arg0->unk294 != 0) {
				if ((s32)arg0->unkD4 == 2) {
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
						temp_r30     = fn_800A5A54(arg0);
						arg0->unk150 = fn_800D7A94(arg0->unk150, arg0->unk174, arg0->unk180);
						if (temp_r30 < 0x80) {
							arg0->unk150 = arg0->unk174;
						}
					}
				}
				if ((M2C_BITWISE(s32, arg0->unkD4) == 3) && ((s32)arg0->unk274 == 0)) {
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x401E, &arg0->unk140, 0, 1, 0, 0);
					}
					arg0->unk274 = 1;
				}
				if ((M2C_BITWISE(s32, arg0->unkD4) == 3)
				    && ((u32)(M2C_BITWISE(s32, arg0->unkC8) & 2) != 0)
				    && ((s32)arg0->unk274 == 1)) {
					if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1E) == 0) {
						fn_8004D5F4(lbl_8042C1F8, 0x1E, lbl_8_rodata_1DC0);
					}
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x401F, &arg0->unk140, 0, 1, 0, 0);
					}
					fn_8011B594(&sp8);
					temp_r3_2 = fn_8019E8EC(arg0->unk2BC);
					sp8       = M2C_FIELD(temp_r3_2, f32*, 0x30);
					spC       = M2C_FIELD(temp_r3_2, f32*, 0x34);
					sp10      = M2C_FIELD(temp_r3_2, f32*, 0x38);
					spC       = fn_800D8BC4(&sp8, NULL, 1);
					fn_8011B418(&sp8);
					arg0->unk274 = 2;
				}
			}
			break;
		case 4:
			break;
	}
}

void fn_8_BB178(void) { }

void fn_8_BB17C(void) { }

void fn_8_BB180(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x274) = 0x5A;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0xC;
			if ((u32)lbl_8042C6D0 == 0U) {
				fn_8011C6EC();
			}
			fn_8011C188(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x238));
			M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) | 0x200);
			return;
		case 1:
			temp_r0                      = M2C_FIELD(arg0, s32*, 0x274) - 1;
			M2C_FIELD(arg0, s32*, 0x274) = temp_r0;
			if (temp_r0 == 0) {
				if ((u32)M2C_FIELD(arg0, u32*, 0x26C) != 0U) {
					fn_8010B074(M2C_FIELD(arg0, u32*, 0x26C));
				}
				if ((u32)M2C_FIELD(arg0, u32*, 0x268) != 0U) {
					fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x268), 2);
					fn_8010B208(M2C_FIELD(arg0, u32*, 0x268), lbl_8_rodata_1D80, lbl_8_rodata_1D80);
					return;
				}
			} else {
				case 2:
					return;
			}
			break;
		case 3:
			M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) & 0xFFFFFDFF);
			if ((u32)M2C_FIELD(arg0, u32*, 0x268) != 0U) {
				fn_8010B074(M2C_FIELD(arg0, u32*, 0x268));
			}
			break;
	}
}

void fn_8_BB294(TObject* arg0, s32 arg1)
{
	sWallObjParam sp14;
	M2C_UNK* temp_r3;
	s32 temp_r3_2;

	switch (arg1) {
		case 0:
			if (((s32)arg0->unk288 != 0) && ((u32)arg0->unk2C8 != NULL)) {
				sp14.unk8  = lbl_8_rodata_1D80;
				sp14.unk4  = lbl_8_rodata_1D80;
				sp14.unk0  = lbl_8_rodata_1D80;
				sp14.unk14 = 0;
				sp14.unk10 = 0;
				sp14.unkC  = 0;
				sp14.unk18 = lbl_8_rodata_1D80;
				sp14.unk24 = lbl_8_rodata_1D80;
				sp14.unk1C = lbl_8_rodata_1D80;
				sp14.unk20 = lbl_8_rodata_1DA8;
				sp14.unk28 = 8;
				sp14.unk2C = 0x4B0;
				temp_r3    = fn_8019E8EC(arg0->unk2C4);
				sp14.unk0  = M2C_FIELD(temp_r3, f32*, 0x30);
				sp14.unk4  = M2C_FIELD(temp_r3, f32*, 0x34);
				sp14.unk8  = M2C_FIELD(temp_r3, f32*, 0x38);
				sp14.unkC  = arg0->unk14C;
				temp_r3_2  = arg0->unk150;
				sp14.unk10 = temp_r3_2;
				sp14.unk14 = arg0->unk154;
				sp14.unk10 = temp_r3_2 + 0x8000;
				sp14.unk28 = M2C_FIELD(arg0->unk18, s32(**)(TObject*), 0x90)(arg0);
				wallCreateObject(&sp14);
				if ((u32)lbl_8042C388 != 0U) {
					fn_800B4A38(lbl_8042C388, 0x4024, (f32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
				}
				fn_8_B9904(arg0, 2);
			}
			arg0->unk288 = 0;
			break;
		case 4:
			break;
	}
}

void fn_8_BB580(void) { }

void fn_8_BB584(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x3C)();
			return;
		case 1:
			M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			return;
		case 4:
			return;
	}
}

void fn_8_BB5E4(TObject* arg0, s32 arg1)
{
	f32 temp_f31;
	s32 temp_r0;
	s32 temp_r30;
	s32 var_r0;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			arg0->unk274 = 0;
			arg0->unkD4  = 1;
			return;
		case 1:
			if ((s32)arg0->unk294 != 0) {
				arg0->unk270
				    = fn_80103324((u8*)arg0 + 0x140, &lbl_8_rodata_1DD0, lbl_8_rodata_1DD0);
				temp_r0 = arg0->unk270;
				if (temp_r0 != -1) {
					temp_r3 = (void*)(u32) * (&lbl_802AD090 + (temp_r0 * 4));
					if (temp_r3 != NULL) {
						arg0->unk1CC = M2C_FIELD(temp_r3, f32*, 0x18);
						arg0->unk1D0 = M2C_FIELD(temp_r3, f32*, 0x1C);
						arg0->unk1D4 = M2C_FIELD(temp_r3, f32*, 0x20);
					}
				}
				if ((s32)arg0->unkD4 == 1) {
					if ((arg0->unkB8 > lbl_8_rodata_1DD4) && ((s32)arg0->unk274 == 0)) {
						if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1E) == 0) {
							fn_8004D5F4(lbl_8042C1F8, 0xF, lbl_8_rodata_1DB8);
						}
						if ((u32)lbl_8042C388 != 0U) {
							fn_800B4A38(
							    lbl_8042C388, 0x4025, (f32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
						}
						arg0->unk274 = 1;
					}
					if ((arg0->unkB8 > lbl_8_rodata_1DD8) && ((s32)arg0->unk274 == 1)) {
						if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1E) == 0) {
							fn_8004D5F4(lbl_8042C1F8, 0xF, lbl_8_rodata_1DB8);
						}
						if ((u32)lbl_8042C388 != 0U) {
							fn_800B4A38(
							    lbl_8042C388, 0x4025, (f32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
						}
						arg0->unk274 = 2;
					}
					if ((M2C_BITWISE(u32, arg0->unkC8) & 2U) != 0U) {
						arg0->unk274 = 0;
					}
				}
				temp_f31 = arg0->unk314;
				if ((s32)arg0->unk294 != 0) {
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
						temp_r30     = fn_800A5A54(arg0);
						arg0->unk150 = fn_800D7A94(arg0->unk150, arg0->unk174, arg0->unk180);
						if (temp_r30 < 0x80) {
							arg0->unk150 = arg0->unk174;
						}
					}
					if ((fn_800A5AC0(arg0) < lbl_8_rodata_1DDC) || ((s32)(arg0->unk106 & 4) != 0)) {
						fn_800A4668(arg0);
					} else {
						fn_800A4A8C(arg0, temp_f31);
					}
					fn_800A5C6C(arg0, 0xF00);
					fn_800A5C6C(arg0, 0x200);
					if (((s32)(arg0->unk106 & 2) != 0)
					    && (arg0->unk15C < (lbl_8_rodata_1DB8 * arg0->unk1A8))) {
						arg0->unk15C = lbl_8_rodata_1D80;
					}
					if ((fn_800A5888(arg0, &lbl_8_rodata_1DA8, lbl_8_rodata_1DA8) == 0)
					    && (((s32)(arg0->unk106 & 4) != 0)
					        || (fn_800D7218(&arg0->unk140, &arg0->unk1E4) < lbl_8_rodata_1D78))) {
						fn_800A5998(arg0);
					}
				}
			}
			return;
		case 4:
			return;
	}
}

void fn_8_BB99C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 0xB;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_BB9BC(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 0xA;
			return;
		case 1:
			if (fn_800A3684() != 0) {
				if ((u32)lbl_8042C388 != 0U) {
					fn_800B4A38(lbl_8042C388, 0x401D, (f32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
				}
				if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1E) == 0) {
					fn_8004D5F4(lbl_8042C1F8, 0x32, lbl_8_rodata_1DC0);
				}
				M2C_FIELD(arg0, s32*, 0x248) = 8;
			}
			return;
		case 4:
			return;
	}
}

void fn_8_BBA90(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 1;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_BBAB0(void* arg0, s32 arg1)
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

void fn_8_BBAD0(void* arg0, u32 arg1, s32 arg2)
{
	s32 temp_r0;

	switch (arg1) { /* switch 1 */
		case 0x1:   /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
				return;
			}
			M2C_FIELD(arg0, s32*, 0xD4) = 0;
			return;
		case 0x2: /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 1;
				return;
			}
			break;
		case 0x7:           /* switch 1 */
			switch (arg2) { /* switch 2; irregular */
				case 0:     /* switch 2 */
					M2C_FIELD(arg0, s32*, 0xD4) = 0xA;
					return;
				case 1: /* switch 2 */
					if (fn_800A3684() != 0) {
						if ((u32)lbl_8042C388 != 0U) {
							fn_800B4A38(
							    lbl_8042C388, 0x401D, (f32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
						}
						if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1E) == 0) {
							fn_8004D5F4(lbl_8042C1F8, 0x32, lbl_8_rodata_1DC0);
						}
						M2C_FIELD(arg0, s32*, 0x248) = 8;
						return;
					}
					break;
			}
			break;
		case 0x8: /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 0xB;
				return;
			}
			break;
		case 0x2C: /* switch 1 */
			fn_8_BB5E4((TObject*)arg0, arg2);
			return;
		case 0x1D:          /* switch 1 */
			switch (arg2) { /* switch 3; irregular */
				case 0:     /* switch 3 */
					M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x3C)();
					return;
				case 1: /* switch 3 */
					M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
					return;
			}
			break;
		case 0x1A: /* switch 1 */
			fn_8_BB294((TObject*)arg0, arg2);
			return;
		case 0x24:          /* switch 1 */
			switch (arg2) { /* switch 4; irregular */
				case 0:     /* switch 4 */
					M2C_FIELD(arg0, s32*, 0x274) = 0x5A;
					M2C_FIELD(arg0, s32*, 0xD4)  = 0xC;
					if ((u32)lbl_8042C6D0 == 0U) {
						fn_8011C6EC();
					}
					fn_8011C188(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x238));
					M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) | 0x200);
					return;
				case 1: /* switch 4 */
					temp_r0                      = M2C_FIELD(arg0, s32*, 0x274) - 1;
					M2C_FIELD(arg0, s32*, 0x274) = temp_r0;
					if (temp_r0 == 0) {
						if ((u32)M2C_FIELD(arg0, u32*, 0x26C) != 0U) {
							fn_8010B074(M2C_FIELD(arg0, u32*, 0x26C));
						}
						if ((u32)M2C_FIELD(arg0, u32*, 0x268) != 0U) {
							fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x268), 2);
							fn_8010B208(
							    M2C_FIELD(arg0, u32*, 0x268), lbl_8_rodata_1D80, lbl_8_rodata_1D80);
							return;
						}
					}
					break;
				case 3: /* switch 4 */
					M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) & 0xFFFFFDFF);
					if ((u32)M2C_FIELD(arg0, u32*, 0x268) != 0U) {
						fn_8010B074(M2C_FIELD(arg0, u32*, 0x268));
						return;
					}
					break;
			}
			break;
		case 0x31: /* switch 1 */
			fn_8_BAF00((TObject*)arg0, arg2);
			return;
		case 0x32:          /* switch 1 */
			switch (arg2) { /* switch 5; irregular */
				case 0:     /* switch 5 */
					M2C_FIELD(arg0, s32*, 0xD4)  = 4;
					M2C_FIELD(arg0, s32*, 0x274) = 0;
					M2C_FIELD(arg0, s32*, 0x29C) = 0;
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x4020, (f32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
						return;
					}
					break;
				case 1: /* switch 5 */
					if (((s32)M2C_FIELD(arg0, s32*, 0x294) != 0)
					    && ((s32)M2C_FIELD(arg0, s32*, 0xD0) == 5)) {
						M2C_FIELD(arg0, s32*, 0x29C) = 1;
						if ((M2C_FIELD(arg0, f32*, 0xB8) > lbl_8_rodata_1DCC)
						    && ((s32)M2C_FIELD(arg0, s32*, 0x274) == 0)) {
							if ((u32)lbl_8042C388 != 0U) {
								fn_800B4A38(
								    lbl_8042C388, 0x4021, (f32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
							}
							M2C_FIELD(arg0, s32*, 0x274) = 1;
						}
						if ((u32)(M2C_FIELD(arg0, s32*, 0xC8) & 2) != 0) {
							M2C_FIELD(arg0, s32*, 0x29C) = 0;
							M2C_FIELD(arg0, s32*, 0x274) = 0;
							return;
						}
					}
					break;
				case 3: /* switch 5 */
					M2C_FIELD(arg0, s32*, 0x29C) = 0;
					return;
			}
			break;
		case 0x33:          /* switch 1 */
			switch (arg2) { /* switch 6; irregular */
				case 0:     /* switch 6 */
					M2C_FIELD(arg0, s32*, 0x274) = 0;
					M2C_FIELD(arg0, s32*, 0x280) = 0;
					M2C_FIELD(arg0, s32*, 0xD4)  = 6;
					return;
				case 1: /* switch 6 */
					if ((s32)M2C_FIELD(arg0, s32*, 0x294) != 0) {
						M2C_FIELD(arg0, s32*, 0x274) = (s32)(M2C_FIELD(arg0, s32*, 0x274) + 0x550);
						M2C_FIELD(arg0, f32*, 0x278) = (f32)(lbl_8_rodata_1DC0
						    * fn_800D7B00((u32)M2C_FIELD(arg0, s32*, 0x274)));
						M2C_FIELD(arg0, f32*, 0x27C) = (f32)(lbl_8_rodata_1DC0
						    * fn_800D7B00(
						        (u32)(s32)(lbl_8_rodata_1DC8 * (f32)M2C_FIELD(arg0, s32*, 0x274))));
						return;
					}
					break;
			}
			break;
		case 0x34: /* switch 1 */
			fn_8_BA8E0((TObject*)arg0, arg2);
			return;
		case 0x35: /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 8;
			}
			break;
		case 4:
			break;
	}
}

void fn_8_BBF90(TObject* arg0)
{
	RwV3d sp8;
	RwV3d sp14;
	RwV3d sp20;
	RwV3d sp2C;
	M2C_UNK* temp_r3;
	M2C_UNK* temp_r3_2;
	M2C_UNK* temp_r3_3;
	M2C_UNK* temp_r3_4;
	M2C_UNK* temp_r3_5;
	M2C_UNK* temp_r3_6;
	void* temp_r30;
	void* temp_r30_10;
	void* temp_r30_2;
	void* temp_r30_3;
	void* temp_r30_4;
	void* temp_r30_5;
	void* temp_r30_6;
	void* temp_r30_7;
	void* temp_r30_8;
	void* temp_r30_9;

	temp_r30 = arg0->unk38;
	if (temp_r30 != NULL) {
		if (((u32)arg0->unk2A0 != 0U) && (temp_r30 != NULL)) {
			temp_r3                         = fn_8019E8EC(arg0->unk2A0);
			M2C_FIELD(temp_r30, f32*, 8)    = (f32)M2C_FIELD(temp_r3, f32*, 0x30);
			M2C_FIELD(temp_r30, f32*, 0xC)  = (f32)M2C_FIELD(temp_r3, f32*, 0x34);
			M2C_FIELD(temp_r30, f32*, 0x10) = (f32)M2C_FIELD(temp_r3, f32*, 0x38);
		}
		if ((u32)arg0->unk2C4 != 0U) {
			temp_r30_2 = (u8*)arg0->unk38 + 0xF0;
			if (temp_r30_2 != NULL) {
				temp_r3_2                         = fn_8019E8EC(arg0->unk2C4);
				M2C_FIELD(temp_r30_2, f32*, 8)    = (f32)M2C_FIELD(temp_r3_2, f32*, 0x30);
				M2C_FIELD(temp_r30_2, f32*, 0xC)  = (f32)M2C_FIELD(temp_r3_2, f32*, 0x34);
				M2C_FIELD(temp_r30_2, f32*, 0x10) = (f32)M2C_FIELD(temp_r3_2, f32*, 0x38);
			}
		}
		if ((u32)arg0->unk2AC != 0U) {
			temp_r30_3 = (u8*)arg0->unk38 + 0x30;
			if (temp_r30_3 != NULL) {
				temp_r3_3                         = fn_8019E8EC(arg0->unk2AC);
				M2C_FIELD(temp_r30_3, f32*, 8)    = (f32)M2C_FIELD(temp_r3_3, f32*, 0x30);
				M2C_FIELD(temp_r30_3, f32*, 0xC)  = (f32)M2C_FIELD(temp_r3_3, f32*, 0x34);
				M2C_FIELD(temp_r30_3, f32*, 0x10) = (f32)M2C_FIELD(temp_r3_3, f32*, 0x38);
			}
		}
		if ((u32)arg0->unk2B0 != 0U) {
			temp_r30_4 = (u8*)arg0->unk38 + 0x60;
			if (temp_r30_4 != NULL) {
				temp_r3_4                         = fn_8019E8EC(arg0->unk2B0);
				M2C_FIELD(temp_r30_4, f32*, 8)    = (f32)M2C_FIELD(temp_r3_4, f32*, 0x30);
				M2C_FIELD(temp_r30_4, f32*, 0xC)  = (f32)M2C_FIELD(temp_r3_4, f32*, 0x34);
				M2C_FIELD(temp_r30_4, f32*, 0x10) = (f32)M2C_FIELD(temp_r3_4, f32*, 0x38);
			}
		}
		if ((u32)arg0->unk2B4 != 0U) {
			temp_r30_5 = (u8*)arg0->unk38 + 0x90;
			if (temp_r30_5 != NULL) {
				M2C_FIELD(&sp2C, M2C_BLOCK12*, 0) = M2C_FIELD(&lbl_8_rodata_1CD0, M2C_BLOCK12*, 0);
				fn_8019941C(&sp2C.x, &sp2C.x, 1, fn_8019E8EC(arg0->unk2B4));
				M2C_FIELD(temp_r30_5, f32*, 8)    = sp2C.x;
				M2C_FIELD(temp_r30_5, f32*, 0xC)  = sp2C.y;
				M2C_FIELD(temp_r30_5, f32*, 0x10) = sp2C.z;
			}
		}
		if ((u32)arg0->unk2B8 != 0U) {
			temp_r30_6 = (u8*)arg0->unk38 + 0xC0;
			if (temp_r30_6 != NULL) {
				M2C_FIELD(&sp20, M2C_BLOCK12*, 0) = M2C_FIELD(&lbl_8_rodata_1CDC, M2C_BLOCK12*, 0);
				fn_8019941C(&sp20.x, &sp20.x, 1, fn_8019E8EC(arg0->unk2B8));
				M2C_FIELD(temp_r30_6, f32*, 8)    = sp20.x;
				M2C_FIELD(temp_r30_6, f32*, 0xC)  = sp20.y;
				M2C_FIELD(temp_r30_6, f32*, 0x10) = sp20.z;
			}
		}
		if ((u32)arg0->unk2BC != 0U) {
			temp_r30_7 = (u8*)arg0->unk38 + 0x120;
			if (temp_r30_7 != NULL) {
				temp_r3_5                         = fn_8019E8EC(arg0->unk2BC);
				M2C_FIELD(temp_r30_7, f32*, 8)    = (f32)M2C_FIELD(temp_r3_5, f32*, 0x30);
				M2C_FIELD(temp_r30_7, f32*, 0xC)  = (f32)M2C_FIELD(temp_r3_5, f32*, 0x34);
				M2C_FIELD(temp_r30_7, f32*, 0x10) = (f32)M2C_FIELD(temp_r3_5, f32*, 0x38);
			}
		}
		if ((u32)arg0->unk2C0 != 0U) {
			temp_r30_8 = (u8*)arg0->unk38 + 0x150;
			if (temp_r30_8 != NULL) {
				temp_r3_6                         = fn_8019E8EC(arg0->unk2C0);
				M2C_FIELD(temp_r30_8, f32*, 8)    = (f32)M2C_FIELD(temp_r3_6, f32*, 0x30);
				M2C_FIELD(temp_r30_8, f32*, 0xC)  = (f32)M2C_FIELD(temp_r3_6, f32*, 0x34);
				M2C_FIELD(temp_r30_8, f32*, 0x10) = (f32)M2C_FIELD(temp_r3_6, f32*, 0x38);
			}
		}
		if ((u32)arg0->unk2A4 != 0U) {
			temp_r30_9 = (u8*)arg0->unk38 + 0x180;
			if (temp_r30_9 != NULL) {
				M2C_FIELD(&sp14, M2C_BLOCK12*, 0) = M2C_FIELD(&lbl_8_rodata_1CE8, M2C_BLOCK12*, 0);
				fn_8019941C(&sp14.x, &sp14.x, 1, fn_8019E8EC(arg0->unk2A4));
				M2C_FIELD(temp_r30_9, f32*, 8)    = sp14.x;
				M2C_FIELD(temp_r30_9, f32*, 0xC)  = sp14.y;
				M2C_FIELD(temp_r30_9, f32*, 0x10) = sp14.z;
			}
		}
		if ((u32)arg0->unk2A8 != 0U) {
			temp_r30_10 = (u8*)arg0->unk38 + 0x1B0;
			if (temp_r30_10 != NULL) {
				M2C_FIELD(&sp8, M2C_BLOCK12*, 0) = M2C_FIELD(&lbl_8_rodata_1CF4, M2C_BLOCK12*, 0);
				fn_8019941C(&sp8.x, &sp8.x, 1, fn_8019E8EC(arg0->unk2A8));
				M2C_FIELD(temp_r30_10, f32*, 8)    = sp8.x;
				M2C_FIELD(temp_r30_10, f32*, 0xC)  = sp8.y;
				M2C_FIELD(temp_r30_10, f32*, 0x10) = sp8.z;
			}
		}
		fn_80021384((u8*)arg0 + 0x28);
	}
}

void fn_8_BC2CC(TObject* arg0)
{
	RwV3d sp14;
	s32 sp8;
	s32 sp10;
	M2C_UNK* temp_r31_2;
	M2C_UNK* temp_r3_15;
	M2C_UNK* temp_r3_16;
	RwFrame* temp_r31;
	TEnemyParalysis* temp_r3_2;
	f32 temp_f0;
	f32 temp_f1;
	f32 temp_f2;
	f32 temp_f2_2;
	s32 temp_r3_10;
	s32 temp_r3_11;
	s32 temp_r3_12;
	s32 temp_r3_13;
	s32 temp_r3_14;
	s32 temp_r3_5;
	s32 temp_r3_6;
	s32 temp_r3_7;
	s32 temp_r3_8;
	s32 temp_r3_9;
	void* temp_r3;
	void* temp_r3_3;
	void* temp_r3_4;

	if ((s32)arg0->unk294 != 0) {
		temp_f2 = arg0->unk278;
		if ((f32)__fabs(temp_f2) > lbl_8_rodata_1D68) {
			arg0->unk278 = temp_f2 * lbl_8_rodata_1D6C;
		}
		temp_f2_2 = arg0->unk27C;
		if ((f32)__fabs(temp_f2_2) > lbl_8_rodata_1D68) {
			arg0->unk27C = temp_f2_2 * lbl_8_rodata_1D6C;
		}
	}
	temp_r3 = (void*)(u32)arg0->unkE8;
	if (temp_r3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3, RwFrame**, 4);
		if (((s32)arg0->unk19C == 0x24) && (temp_r3_2 = arg0->unk244, ((temp_r3_2 == NULL) == 0))) {
			Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(
			    temp_r3_2, temp_r31, (RwOpCombineType)0);
			fn_8019ED68(temp_r31, &lbl_80239984, 2,
			    lbl_8_rodata_1DE0 + (lbl_8_rodata_1D70 * (f32)arg0->unk150));
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
			M2C_FIELD(&sp14, M2C_BLOCK12*, 0) = M2C_FIELD(arg0, M2C_BLOCK12*, 0x140);
			sp14.y += lbl_8_rodata_1DE4;
			SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(
			    arg0->unk244, (RwV3d*)&sp14.x, (u8*)arg0 + 0x14C);
		} else {
			fn_8019ED68(temp_r31, &lbl_80239990, 0, arg0->unk27C);
			fn_8019ED68(temp_r31, &lbl_80239978, 2, arg0->unk278);
			fn_8019ED68(temp_r31, &lbl_80239984, 2,
			    lbl_8_rodata_1DE0 + (lbl_8_rodata_1D70 * (f32)arg0->unk150));
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
		}
	}
	if ((u32)arg0->unk2C4 != 0U) {
		temp_r31_2 = fn_8019E8EC(arg0->unk2C4);
		temp_r3_3  = (void*)(u32)arg0->unk2C8;
		if (temp_r3_3 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_3, s32*, 4), temp_r31_2, 0);
		}
		temp_r3_4 = (void*)(u32)arg0->unk2CC;
		if (temp_r3_4 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_4, s32*, 4), temp_r31_2, 0);
		}
	}
	if ((u32)arg0->unk2C4 == 0U) {
		temp_r3_5 = fn_8005D9A0((void*)arg0->unkEC, 0x3E8);
		if (temp_r3_5 != -1) {
			arg0->unk2C4
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_5 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk2A0 == 0U) {
		temp_r3_6 = fn_8005D9A0((void*)arg0->unkEC, 0x3F2);
		if (temp_r3_6 != -1) {
			arg0->unk2A0
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_6 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk2A4 == 0U) {
		temp_r3_7 = fn_8005D9A0((void*)arg0->unkEC, 0x3FB);
		if (temp_r3_7 != -1) {
			arg0->unk2A4
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_7 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk2A8 == 0U) {
		temp_r3_8 = fn_8005D9A0((void*)arg0->unkEC, 0x3F7);
		if (temp_r3_8 != -1) {
			arg0->unk2A8
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_8 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk2AC == 0U) {
		temp_r3_9 = fn_8005D9A0((void*)arg0->unkEC, 0x3F8);
		if (temp_r3_9 != -1) {
			arg0->unk2AC
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_9 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk2B0 == 0U) {
		temp_r3_10 = fn_8005D9A0((void*)arg0->unkEC, 0x3F4);
		if (temp_r3_10 != -1) {
			arg0->unk2B0
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_10 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk2B4 == 0U) {
		temp_r3_11 = fn_8005D9A0((void*)arg0->unkEC, 0x401);
		if (temp_r3_11 != -1) {
			arg0->unk2B4
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_11 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk2B8 == 0U) {
		temp_r3_12 = fn_8005D9A0((void*)arg0->unkEC, 0x3FE);
		if (temp_r3_12 != -1) {
			arg0->unk2B8
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_12 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk2BC == 0U) {
		temp_r3_13 = fn_8005D9A0((void*)arg0->unkEC, 0x406);
		if (temp_r3_13 != -1) {
			arg0->unk2BC
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_13 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk2C0 == 0U) {
		temp_r3_14 = fn_8005D9A0((void*)arg0->unkEC, 0x407);
		if (temp_r3_14 != -1) {
			arg0->unk2C0
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_14 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)(M2C_FIELD(M2C_BITWISE(u32, arg0->unkB0), s32*, 0x18) & 0x20000) != 0) {
		if ((s32)(arg0->unk106 & 2) != 0) {
			arg0->unk2F8 = arg0->unk118;
			arg0->unk300 = arg0->unk120;
			arg0->unk2D8 = lbl_8_rodata_1DE8 + arg0->unk144;
		} else {
			temp_f1      = fn_800D8BC4((f32*)((u8*)arg0 + 0x140), &sp8, 1);
			arg0->unk2D8 = temp_f1;
			if (lbl_8_rodata_1DEC != temp_f1) {
				arg0->unk2D4 = arg0->unk140;
				arg0->unk2D8 += lbl_8_rodata_1DE8;
				arg0->unk2DC = arg0->unk148;
				arg0->unk2F8 = lbl_8_rodata_1D70 * (f32)sp8;
				arg0->unk300 = lbl_8_rodata_1D70 * (f32)sp10;
			}
		}
		arg0->unk2FC = lbl_8_rodata_1DE0 + (lbl_8_rodata_1D70 * (f32)arg0->unk150);
		arg0->unk2D4 = arg0->unk140;
		arg0->unk2DC = arg0->unk148;
		if ((u32)arg0->unk2A4 != 0U) {
			temp_r3_15   = fn_8019E8EC(arg0->unk2A4);
			arg0->unk2E0 = M2C_FIELD(temp_r3_15, f32*, 0x30);
			arg0->unk2E4 = M2C_FIELD(temp_r3_15, f32*, 0x34);
			arg0->unk2E8 = M2C_FIELD(temp_r3_15, f32*, 0x38);
			arg0->unk2E4 = arg0->unk2D8;
		}
		if ((u32)arg0->unk2A8 != 0U) {
			temp_r3_16   = fn_8019E8EC(arg0->unk2A8);
			arg0->unk2EC = M2C_FIELD(temp_r3_16, f32*, 0x30);
			arg0->unk2F0 = M2C_FIELD(temp_r3_16, f32*, 0x34);
			arg0->unk2F4 = M2C_FIELD(temp_r3_16, f32*, 0x38);
			arg0->unk2F0 = arg0->unk2D8;
		}
	}
}

void fn_8_BC924(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x2D0) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2D0));
		M2C_FIELD(arg0, u32*, 0x2D0) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2CC) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2CC));
		M2C_FIELD(arg0, u32*, 0x2CC) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2C8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0x2C8));
		M2C_FIELD(arg0, u32*, 0x2C8) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958((void*)M2C_FIELD(arg0, u32*, 0xE8));
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

void fn_8_BC9AC(void* arg0)
{
	void* var_r30;

	if ((void*)M2C_FIELD(arg0, void**, 0x2D0) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0x2D0));
		M2C_FIELD(arg0, void**, 0x2D0) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x2CC) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0x2CC));
		M2C_FIELD(arg0, void**, 0x2CC) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x2C8) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0x2C8));
		M2C_FIELD(arg0, void**, 0x2C8) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958((void*)M2C_FIELD(arg0, void**, 0xE8));
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x304) == 1) {
		var_r30                        = fn_80150588(lbl_8_bss_1AC8[1]);
		M2C_FIELD(arg0, void**, 0x2C8) = fn_80150588(lbl_8_bss_1AC8[2]);
		M2C_FIELD(arg0, void**, 0x2CC) = fn_80150588(lbl_8_bss_1AC8[3]);
	} else {
		var_r30 = fn_80150588(lbl_8_bss_1AC8[0]);
	}
	M2C_FIELD(arg0, void**, 0xE8)  = var_r30;
	M2C_FIELD(arg0, void**, 0x2D0) = fn_80150588(lbl_8_bss_1AC8[4]);
}

void fn_8_BCAB4(void* arg0)
{
	RwV3d sp8;
	u8 sp14[0x40];
	void* temp_r31;

	temp_r31 = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), void**, 0x2C);
	fn_80196050((M2C_UNK*)sp14, (u8*)arg0 + 0x1C0, 0);
	sp8.z = lbl_8_rodata_1D80;
	sp8.x = lbl_8_rodata_1D80;
	sp8.y = M2C_FIELD(temp_r31, f32*, 0x1C);
	fn_8019941C(&sp8.x, &sp8.x, 1, (M2C_UNK*)sp14);
	M2C_FIELD(arg0, f32*, 0x140) = sp8.x;
	M2C_FIELD(arg0, f32*, 0x144) = sp8.y;
	M2C_FIELD(arg0, f32*, 0x148) = sp8.z;
	M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x1C0);
	M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x1C4);
	M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x1C8);
}

void fn_8_BCB5C(void) { }

void fn_8_BCB60(TObject* arg0)
{
	RwV3d sp8;
	u8 sp14[0x40];
	void* temp_r30;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r4;

	temp_r4      = M2C_FIELD(M2C_BITWISE(u32, arg0->unkB0), void**, 0x2C);
	arg0->unk304 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0);
	arg0->unk308 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 1);
	arg0->unk30C = M2C_FIELD(temp_r4, s32*, 0x14);
	arg0->unk310 = M2C_FIELD(temp_r4, f32*, 0x18);
	arg0->unk314 = M2C_FIELD(temp_r4, f32*, 4);
	arg0->unk20C = M2C_FIELD(temp_r4, f32*, 0xC);
	arg0->unk210 = M2C_FIELD(temp_r4, f32*, 8);
	arg0->unk214 = M2C_FIELD(temp_r4, f32*, 0xC);
	arg0->unk1D8 = lbl_8_rodata_1D80;
	arg0->unk1DC = lbl_8_rodata_1D80;
	arg0->unk1E0 = M2C_FIELD(temp_r4, f32*, 0x10);
	temp_r3      = (void*)M2C_BITWISE(u32, arg0->unkB0);
	arg0->unk140 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unk144 = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unk148 = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2    = (void*)M2C_BITWISE(u32, arg0->unkB0);
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
	arg0->unk1B8 = lbl_8_rodata_1D7C;
	if ((s32)arg0->unk308 != 1) {

	} else {
		temp_r30 = M2C_FIELD(M2C_BITWISE(u32, arg0->unkB0), void**, 0x2C);
		fn_80196050((M2C_UNK*)sp14, (u8*)arg0 + 0x1C0, 0);
		sp8.z = lbl_8_rodata_1D80;
		sp8.x = lbl_8_rodata_1D80;
		sp8.y = M2C_FIELD(temp_r30, f32*, 0x1C);
		fn_8019941C(&sp8.x, &sp8.x, 1, (M2C_UNK*)sp14);
		arg0->unk140 = sp8.x;
		arg0->unk144 = sp8.y;
		arg0->unk148 = sp8.z;
		arg0->unk1CC = arg0->unk1C0;
		arg0->unk1D0 = arg0->unk1C4;
		arg0->unk1D4 = arg0->unk1C8;
	}
	arg0->unk24C = -arg0->unk210;
	arg0->unk254 = arg0->unk1CC;
	arg0->unk258 = arg0->unk1D0;
	arg0->unk25C = arg0->unk1D4;
	arg0->unk180 = 0x50;
	arg0->unk264 = lbl_8_rodata_1DF0;
	arg0->unk260 = arg0->unk264;
}

void fn_8_BCD58(TObject* arg0)
{
	f32 temp_f0;

	arg0->unk248                 = 0;
	arg0->unk26C                 = 0U;
	arg0->unk268                 = 0U;
	arg0->unk270                 = -1;
	temp_f0                      = lbl_8_rodata_1D80;
	arg0->unk314                 = temp_f0;
	arg0->unk2A0                 = 0U;
	arg0->unk2A4                 = 0U;
	arg0->unk2A8                 = 0U;
	arg0->unk2AC                 = 0U;
	arg0->unk2B0                 = 0U;
	arg0->unk2B4                 = 0U;
	arg0->unk2B8                 = 0U;
	M2C_FIELD(arg0, s32*, 0x2BC) = 0;
	arg0->unk2C0                 = 0U;
	arg0->unk2C4                 = 0U;
	arg0->unk2C8                 = NULL;
	arg0->unk2CC                 = NULL;
	arg0->unk27C                 = temp_f0;
	arg0->unk278                 = temp_f0;
	arg0->unk2DC                 = temp_f0;
	arg0->unk2D8                 = temp_f0;
	arg0->unk2D4                 = temp_f0;
	arg0->unk2E8                 = temp_f0;
	arg0->unk2E4                 = temp_f0;
	arg0->unk2E0                 = temp_f0;
	arg0->unk2F4                 = temp_f0;
	arg0->unk2F0                 = temp_f0;
	arg0->unk2EC                 = temp_f0;
	arg0->unk300                 = temp_f0;
	arg0->unk2FC                 = temp_f0;
	arg0->unk2F8                 = temp_f0;
	arg0->unk280                 = 0;
	arg0->unk284                 = 0x14;
	arg0->unk28C                 = -1;
	arg0->unk290                 = 0;
	arg0->unk288                 = 1;
	arg0->unk294                 = 1;
	arg0->unk298                 = 1;
	arg0->unk244                 = NULL;
	arg0->unk2D0                 = NULL;
	arg0->unk29C                 = 0;
}

TObject* fn_8_BCE1C(TObject* arg0, s16 arg1)
{
	TEnemyParalysis* temp_r3;
	s32 temp_cr0_eq;
	void** temp_r3_2;

	if (arg0 != NULL) {
		arg0->unk18                 = (M2C_UNK*)lbl_8_data_17AEC;
		M2C_FIELD(arg0, u32*, 0xB4) = (u32)((u8*)(M2C_UNK*)lbl_8_data_17AEC + 0x2C);
		temp_r3                     = arg0->unk244;
		if (temp_r3 != NULL) {
			temp_r3->unk4 |= 1;
			arg0->unk244 = NULL;
		}
		if ((u32)arg0->unk26C != 0U) {
			fn_8010AFE4();
			arg0->unk26C = 0U;
		}
		if ((u32)arg0->unk268 != 0U) {
			fn_8010AFE4();
			arg0->unk268 = 0U;
		}
		temp_r3_2   = arg0->unk240;
		temp_cr0_eq = temp_r3_2 == NULL;
		if (temp_cr0_eq == 0) {
			if (temp_cr0_eq == 0) {
				M2C_FIELD(*temp_r3_2, M2C_UNK(**)(M2C_UNK), 8)(1);
			}
			arg0->unk240 = NULL;
		}
		if ((u32)arg0->unk2D0 != NULL) {
			fn_80150958((void*)arg0->unk2D0);
			arg0->unk2D0 = NULL;
		}
		if ((u32)arg0->unk2CC != NULL) {
			fn_80150958((void*)arg0->unk2CC);
			arg0->unk2CC = NULL;
		}
		if ((u32)arg0->unk2C8 != NULL) {
			fn_80150958((void*)arg0->unk2C8);
			arg0->unk2C8 = NULL;
		}
		if ((u32)arg0->unkE8 != 0U) {
			fn_80150958((void*)arg0->unkE8);
			arg0->unkE8 = 0U;
		}
		__dt__10HAnimClassFv((u8*)arg0 + 0x240, 0);
		fn_800A7088(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_BCF88(TObject* arg0)
{
	f32 sp18;
	f32 sp14;
	f32 sp10;
	sParalysisParam sp8;
	TObject* temp_r3;
	TObject* var_r0_2;
	f32 temp_f0;
	f32 temp_f1;
	void** var_r0;
	void** var_r0_3;
	void* var_r30;

	fn_800A714C();
	__ct__10HAnimClassFv((u8*)arg0 + 0x240);
	arg0->unk18                 = (M2C_UNK*)lbl_8_data_17AEC;
	M2C_FIELD(arg0, u32*, 0xB4) = (u32)((u8*)(M2C_UNK*)lbl_8_data_17AEC + 0x2C);
	arg0->unk0                  = (M2C_UNK*)lbl_8_data_17990;
	arg0->unk1E                 = 0x318;
	fn_8_BCD58(arg0);
	fn_8_BCB60(arg0);
	arg0->unk188 &= 0xFFFF3FFF;
	arg0->unk188 |= 0x4000;
	temp_f1      = lbl_8_rodata_1D80;
	arg0->unk160 = temp_f1;
	arg0->unk15C = temp_f1;
	arg0->unk158 = temp_f1;
	arg0->unk188 &= 0xFFEFCFFF;
	arg0->unk188 |= 0x100000;
	arg0->unk188 |= 0x10;
	temp_f0      = arg0->unk260;
	arg0->unk1A4 = temp_f0;
	arg0->unk2E  = (s16)temp_f0;
	arg0->unk1A0 = lbl_8_rodata_1D98;
	arg0->unk2C  = 3;
	arg0->unk188 |= 0x20000;
	if ((void*)arg0->unk2D0 != NULL) {
		fn_80150958((void*)arg0->unk2D0);
		arg0->unk2D0 = NULL;
	}
	if ((void*)arg0->unk2CC != NULL) {
		fn_80150958((void*)arg0->unk2CC);
		arg0->unk2CC = NULL;
	}
	if ((void*)arg0->unk2C8 != NULL) {
		fn_80150958((void*)arg0->unk2C8);
		arg0->unk2C8 = NULL;
	}
	if ((u32)arg0->unkE8 != 0U) {
		fn_80150958((void*)arg0->unkE8);
		arg0->unkE8 = 0;
	}
	if ((s32)arg0->unk304 == 1) {
		var_r30      = fn_80150588(lbl_8_bss_1AC8[1]);
		arg0->unk2C8 = fn_80150588(lbl_8_bss_1AC8[2]);
		arg0->unk2CC = fn_80150588(lbl_8_bss_1AC8[3]);
	} else {
		var_r30 = fn_80150588(lbl_8_bss_1AC8[0]);
	}
	arg0->unkE8  = (s32)var_r30;
	arg0->unk2D0 = fn_80150588(lbl_8_bss_1AC8[4]);
	fn_8_BC2CC(arg0);
	fn_8005D5C8((void*)arg0->unkE8,
	    ((u32)(M2C_FIELD(M2C_BITWISE(u32, arg0->unkB0), s32*, 0x18) & 0x1C0000) >> 0x12U) + 8);
	M2C_FIELD(arg0, u32*, 0xE4) = (u32)lbl_8_data_17484;
	M2C_FIELD(arg0, s32*, 0xD4) = 1;
	if (fn_8005B8D8(&arg0->unkB0) == 0) {
		fn_8003C200(&arg0->unk28, (M2C_UNK*)lbl_8_data_1767C, 0xA, 3);
		arg0->unk88 = arg0->unk140;
		arg0->unk8C = arg0->unk144;
		arg0->unk90 = arg0->unk148;
		arg0->unk30 |= 0x80;
		if ((s32)arg0->unk304 == 0) {
			fn_8_B9904(arg0, 0);
		} else {
			fn_8_B9904(arg0, 1);
		}
	}
	arg0->unk130 = lbl_8_rodata_1DF4;
	arg0->unk134 = lbl_8_rodata_1DF8;
	var_r0       = fn_80057644(0x20);
	if (var_r0 != NULL) {
		fn_8_B81B0(var_r0);
	}
	arg0->unk240 = var_r0;
	if ((void**)arg0->unk240 != NULL) {
		fn_8_B7C50((TObject*)arg0->unk240, arg0);
	}
	arg0->unk268 = fn_8010B708(1);
	arg0->unk26C = fn_8010B708(0);
	arg0->unk220 = lbl_8_rodata_1DFC;
	__ct__15sParalysisParamFv(&sp8);
	sp18     = lbl_8_rodata_1E00;
	sp14     = lbl_8_rodata_1E00;
	sp10     = lbl_8_rodata_1E00;
	temp_r3  = fn_80018A34(lbl_8042C148, 0x74);
	var_r0_2 = temp_r3;
	if (var_r0_2 != NULL) {
		var_r0_2 = __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(
		    (TEnemyParalysis*)temp_r3, lbl_8042C10C, &sp8);
	}
	arg0->unk244 = (TEnemyParalysis*)var_r0_2;
	arg0->unk13C = 1;
	var_r0_3     = fn_80057644(0x20);
	if (var_r0_3 != NULL) {
		var_r0_3 = fn_800FD8A0(arg0, arg0->unk13C);
	}
	arg0->unk228 = var_r0_3;
	return arg0;
}

TObject* fn_8_BD32C(void)
{
	TObject* var_r0;

	var_r0 = fn_80018A34(lbl_8042C148, 0x318);
	if (var_r0 != NULL) {
		var_r0 = fn_8_BCF88(lbl_8042C10C);
	}
	return var_r0;
}

void fn_8_BD380(void* arg0, void* arg1)
{
	f32* var_r4_3;
	f32* var_r4_4;
	f32* var_r4_6;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	s32* var_r4_5;
	s32 temp_r5;
	u8* temp_r3;
	u8* var_r4;
	u8* var_r4_2;
	u8 temp_r0;
	u8 temp_r0_2;

	temp_r3 = M2C_FIELD(arg1, u8**, 0x2C);
	temp_r0 = M2C_FIELD(temp_r3, u8*, 0);
	var_r4  = &lbl_8_data_1797C;
	if ((s8)temp_r0 < (s8)lbl_8_data_1797C) {

	} else {
		var_r4 = &lbl_8_data_1797D;
		if ((s8)temp_r0 > (s8)lbl_8_data_1797D) {

		} else {
			var_r4 = temp_r3;
		}
	}
	M2C_FIELD(temp_r3, u8*, 0) = (u8)(s8)*var_r4;
	temp_r0_2                  = M2C_FIELD(temp_r3, u8*, 1);
	var_r4_2                   = &lbl_8_data_1797E;
	if ((s8)temp_r0_2 < (s8)lbl_8_data_1797E) {

	} else {
		var_r4_2 = &lbl_8_data_1797F;
		if ((s8)temp_r0_2 > (s8)lbl_8_data_1797F) {

		} else {
			var_r4_2 = temp_r3 + 1;
		}
	}
	M2C_FIELD(temp_r3, u8*, 1) = (u8)(s8)*var_r4_2;
	temp_f1                    = M2C_FIELD(temp_r3, f32*, 8);
	var_r4_3                   = &lbl_8_rodata_1E04;
	if (temp_f1 < lbl_8_rodata_1E04) {

	} else {
		var_r4_3 = &lbl_8_rodata_1E08;
		if (temp_f1 > lbl_8_rodata_1E08) {

		} else {
			var_r4_3 = (f32*)(temp_r3 + 8);
		}
	}
	M2C_FIELD(temp_r3, f32*, 8) = (f32)*var_r4_3;
	temp_f1_2                   = M2C_FIELD(temp_r3, f32*, 0xC);
	var_r4_4                    = &lbl_8_rodata_1E0C;
	if (temp_f1_2 < lbl_8_rodata_1E0C) {

	} else {
		var_r4_4 = &lbl_8_rodata_1E10;
		if (temp_f1_2 > lbl_8_rodata_1E10) {

		} else {
			var_r4_4 = (f32*)(temp_r3 + 0xC);
		}
	}
	M2C_FIELD(temp_r3, f32*, 0xC) = (f32)*var_r4_4;
	temp_r5                       = M2C_FIELD(temp_r3, s32*, 0x14);
	var_r4_5                      = &lbl_8_rodata_1E14;
	if (temp_r5 < (s32)lbl_8_rodata_1E14) {

	} else {
		var_r4_5 = &lbl_8_rodata_1E18;
		if (temp_r5 > (s32)lbl_8_rodata_1E18) {

		} else {
			var_r4_5 = (s32*)(temp_r3 + 0x14);
		}
	}
	M2C_FIELD(temp_r3, s32*, 0x14) = (s32)*var_r4_5;
	temp_f1_3                      = M2C_FIELD(temp_r3, f32*, 0x18);
	var_r4_6                       = &lbl_8_rodata_1E1C;
	if (temp_f1_3 < lbl_8_rodata_1E1C) {

	} else {
		var_r4_6 = lbl_8_rodata_1E20;
		if (temp_f1_3 > 10000.0f) {

		} else {
			var_r4_6 = (f32*)(temp_r3 + 0x18);
		}
	}
	M2C_FIELD(temp_r3, f32*, 0x18) = (f32)*var_r4_6;
	M2C_FIELD((M2C_UNK*)wallObjectFieldNames, M2C_UNK**, 0)
	    = (M2C_UNK*)lbl_8_data_1795C[(s8)M2C_FIELD(temp_r3, u8*, 0)];
	M2C_FIELD((M2C_UNK*)wallObjectFieldNames, M2C_UNK**, 4)
	    = (M2C_UNK*)lbl_8_data_17974[(s8)M2C_FIELD(temp_r3, u8*, 1)];
}

void wallObjectUnload(void)
{
	fn_80113A68(&wallObjectGlobalA);
	fn_800FE248(8, (M2C_UNK*)lbl_8_data_17484);
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	fn_801007F4(lbl_8042C590, 8);
}

void wallObjectLoad(void)
{
	u32 temp_r3;
	u32 temp_r3_2;

	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	fn_8010096C(lbl_8042C590, 8, (M2C_UNK*)"en_wall.one");
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	temp_r3 = fn_80100328(lbl_8042C590, 8, 9);
	if (temp_r3 != 0U) {
		fn_8005E00C(6);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		lbl_8_bss_1AC8[0] = (void*)fn_8010037C(lbl_8042C590, 8, 8);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		lbl_8_bss_1AC8[1] = (void*)fn_8010037C(lbl_8042C590, 8, 0x14);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		lbl_8_bss_1AC8[2] = (void*)fn_8010037C(lbl_8042C590, 8, 7);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		lbl_8_bss_1AC8[3] = (void*)fn_8010037C(lbl_8042C590, 8, 4);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		lbl_8_bss_1AC8[4] = (void*)fn_8010037C(lbl_8042C590, 8, 5);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		temp_r3_2      = fn_80100280(lbl_8042C590, 8, 6);
		lbl_8_bss_1ADC = temp_r3_2;
		if ((lbl_8_bss_1AC8[4] != NULL) && (temp_r3_2 != 0U)) {
			*lbl_8_bss_1AE0 = temp_r3_2;
			fn_8005BF5C(lbl_8_bss_1AC8[4], lbl_8_bss_1AE0);
		}
		lbl_8_bss_1B24 = 0;
		fn_800FE274(8, (M2C_UNK*)lbl_8_data_17484);
		if (lbl_8_bss_1AC8[3] != NULL) {
			fn_8005DA34();
			fn_80113AA8(
			    &wallObjectGlobalA, temp_r3, lbl_8_bss_1AC8[3], (M2C_UNK*)lbl_8_data_17874, 3);
		}
	}
}

void wallObjectCreate(void)
{
	if (fn_80018A34(lbl_8042C148, 0x318) != NULL) {
		fn_8_BCF88(lbl_8042C10C);
	}
}

void fn_8_BD938(void* arg0, s32 arg1)
{
	if (arg0 != NULL) {
		M2C_FIELD(arg0, s32*, 4) = (s32)(M2C_FIELD(arg0, s32*, 4) & ~arg1);
	}
}

void fn_8_BD950(void* arg0, s32 arg1)
{
	if (arg0 != NULL) {
		M2C_FIELD(arg0, s32*, 4) = (s32)(M2C_FIELD(arg0, s32*, 4) | arg1);
	}
}

void wallObjectRegister(void)
{
	s32 flags;
	M2C_UNK* temp_r3;

	fn_80113C7C(&wallObjectGlobalA);
	__register_global_object(&fn_80113C2C, &wallObjectGlobalAChain);
	M2C_FIELD(&wallObjectEntry, s32*, 0x14)       = 0;
	M2C_FIELD(&wallObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&wallObjectEntry, M2C_UNK**, 0)     = (M2C_UNK*)wallObjectDisplayName;
	M2C_FIELD(&wallObjectEntry, void (**)(), 4)   = wallObjectLoad;
	M2C_FIELD(&wallObjectEntry, void (**)(), 8)   = wallObjectUnload;
	M2C_FIELD(&wallObjectEntry, void (**)(), 0xC) = wallObjectCreate;
	M2C_FIELD(&wallObjectEntry, s32*, 0x10)       = 0;
	flags                                         = 0x20000;
	M2C_FIELD(&wallObjectEntry, s32*, 0x14)       = flags;
	M2C_FIELD(&wallObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&wallObjectEntry, s8*, 0x20)        = 0x1E;
	M2C_FIELD(&wallObjectEntry, s16*, 0x1C)       = 0x1540;
	M2C_FIELD(&wallObjectEntry, s16*, 0x1E)       = 4;
	M2C_FIELD(&wallObjectEntry, s8*, 0x21)        = 0;
	temp_r3                                       = (M2C_UNK*)wallObjectFieldTypes;
	M2C_FIELD(&wallObjectEntry, M2C_UNK**, 0x24)  = temp_r3;
	M2C_FIELD(&wallObjectEntry, M2C_UNK**, 0x28)  = (M2C_UNK*)wallObjectFieldNames;
	if (temp_r3 != NULL) {
		M2C_FIELD(&wallObjectEntry, s32*, 0x14) = flags | 8;
		return;
	}
	M2C_FIELD(&wallObjectEntry, s32*, 0x14) = flags & ~8;
}

__declspec(section ".ctors") void (*const wallObjectCtorEntry)(void) = wallObjectRegister;
}
