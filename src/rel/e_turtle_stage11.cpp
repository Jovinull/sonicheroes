#include "types.h"

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
	u8 data[8];
} sParalysisParam;

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
    void*, void*, void*);                                                        /* extern */
void* __ct__15sParalysisParamFv(void*);                                          /* extern */
M2C_UNK __dl__FPv(void* arg0);                                                   /* extern */
void* __dt__10HAnimClassFv(void*, s32);                                          /* extern */
M2C_UNK __register_global_object(M2C_UNK*, M2C_UNK*);                            /* extern */
M2C_UNK dtor_800FE334(M2C_UNK);                                                  /* extern */
s32 fn_80017800(void*);                                                          /* extern */
M2C_UNK fn_800189A4(s32, void*);                                                 /* extern */
TEnemyParalysis* fn_80018A34(s32, M2C_UNK);                                      /* extern */
u32 fn_800207C4(M2C_UNK*, M2C_UNK, M2C_UNK);                                     /* extern */
u32 fn_800209C8(M2C_UNK*, M2C_UNK);                                              /* extern */
void* fn_80020D1C(M2C_UNK*);                                                     /* extern */
M2C_UNK fn_80020EEC(M2C_UNK*);                                                   /* extern */
void* fn_800210C4(M2C_UNK*);                                                     /* extern */
void* fn_800211A8(M2C_UNK*);                                                     /* extern */
M2C_UNK fn_80021824(M2C_UNK*);                                                   /* extern */
M2C_UNK fn_8003BC38(M2C_UNK*);                                                   /* extern */
M2C_UNK fn_8003C200(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);                       /* extern */
s32 fn_80041AB0(s32);                                                            /* extern */
s32 fn_80041B64(s32);                                                            /* extern */
void** fn_80057644(M2C_UNK);                                                     /* extern */
s32 fn_8005B8D8(void**);                                                         /* extern */
M2C_UNK fn_8005D5C8(void*, s32);                                                 /* extern */
s32 fn_8005D9A0(void*, M2C_UNK);                                                 /* extern */
M2C_UNK fn_8005E00C(M2C_UNK);                                                    /* extern */
M2C_UNK fn_8005FD8C(M2C_UNK);                                                    /* extern */
void* fn_800627BC(M2C_UNK, void*, void*);                                        /* extern */
M2C_UNK fn_8006298C(M2C_UNK, f32*, s32*);                                        /* extern */
M2C_UNK fn_800667B4(M2C_UNK*, f32);                                              /* extern */
s32 fn_8009278C(M2C_UNK);                                                        /* extern */
s32 fn_800A2B78(TObjEffTornadoSpin*, TObjEffTornadoSpin*);                       /* extern */
s32 fn_800A2D90(s32);                                                            /* extern */
M2C_UNK fn_800A31B8(void*);                                                      /* extern */
s32 fn_800A37A4();                                                               /* extern */
M2C_UNK fn_800A3CBC(void*);                                                      /* extern */
M2C_UNK fn_800A3D48(TObject*);                                                   /* extern */
s32 fn_800A3E10(TObjEffTornadoSpin*, TObjEffTornadoSpin*);                       /* extern */
s32 fn_800A3ED4(void*);                                                          /* extern */
M2C_UNK fn_800A4630(TObjEffTornadoSpin*, s32);                                   /* extern */
M2C_UNK fn_800A4668(void*);                                                      /* extern */
M2C_UNK fn_800A4A8C(void*, M2C_UNK*, f32);                                       /* extern */
s32 fn_800A5888(void*, M2C_UNK*, f32);                                           /* extern */
s32 fn_800A5998(void*);                                                          /* extern */
s32 fn_800A5A54(void*);                                                          /* extern */
f32 fn_800A5AC0();                                                               /* extern */
M2C_UNK fn_800A5B34(TObject*);                                                   /* extern */
M2C_UNK fn_800A5B50(void*, M2C_UNK);                                             /* extern */
M2C_UNK fn_800A5C6C(void*, M2C_UNK);                                             /* extern */
s32 fn_800A6334(void*);                                                          /* extern */
M2C_UNK fn_800A7088(void*, M2C_UNK);                                             /* extern */
M2C_UNK fn_800A714C();                                                           /* extern */
s32 fn_800AAFEC(M2C_UNK*, s32*);                                                 /* extern */
s32 fn_800AB104(s32);                                                            /* extern */
M2C_UNK fn_800B4A38(u32, M2C_UNK, s32*, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);     /* extern */
M2C_UNK fn_800B7514(void*, void*, f32*, f32);                                    /* extern */
M2C_UNK fn_800B7820();                                                           /* extern */
M2C_UNK fn_800B7864(M2C_UNK);                                                    /* extern */
f32 fn_800D71DC(s32, s32);                                                       /* extern */
f32 fn_800D7218(void*, void*);                                                   /* extern */
s32 fn_800D7920(f32*, f32*, M2C_UNK*);                                           /* extern */
s32 fn_800D7A94(s32, s32, s32);                                                  /* extern */
f32 fn_800D7AE4(s32);                                                            /* extern */
f32 fn_800D7B00(s32);                                                            /* extern */
f32 fn_800D8BC4(void*, s32*, M2C_UNK);                                           /* extern */
void** fn_800FD8A0(TObject*, s32);                                               /* extern */
M2C_UNK fn_800FE248(M2C_UNK, M2C_UNK*);                                          /* extern */
M2C_UNK fn_800FE274(M2C_UNK, M2C_UNK*);                                          /* extern */
void** fn_800FE3FC();                                                            /* extern */
M2C_UNK fn_800FE464(void**);                                                     /* extern */
u32 fn_80100328(u32, M2C_UNK, M2C_UNK);                                          /* extern */
u32 fn_8010037C(u32, M2C_UNK, M2C_UNK);                                          /* extern */
M2C_UNK fn_801007F4(u32, M2C_UNK);                                               /* extern */
M2C_UNK fn_8010096C(u32, M2C_UNK, M2C_UNK*);                                     /* extern */
M2C_UNK fn_80100AAC();                                                           /* extern */
M2C_UNK fn_80102C50(s32, f32*, s32*, s32*, M2C_UNK, M2C_UNK, M2C_UNK, f32, f32); /* extern */
s32 fn_801031D8(s32);                                                            /* extern */
s32 fn_80103324(void*, M2C_UNK*, f32);                                           /* extern */
s32 fn_8010AFB0();                                                               /* extern */
M2C_UNK fn_8010AFE4();                                                           /* extern */
M2C_UNK fn_8010AFF8(u32, s32);                                                   /* extern */
M2C_UNK fn_8010B074(u32);                                                        /* extern */
M2C_UNK fn_8010B0AC(u32, s32, f32, f32);                                         /* extern */
M2C_UNK fn_8010B208(u32, f32, f32);                                              /* extern */
M2C_UNK fn_8010B350(const void*, const void*);                                   /* extern */
s32 fn_8010B708(M2C_UNK);                                                        /* extern */
M2C_UNK fn_80113874();                                                           /* extern */
M2C_UNK fn_8011398C(M2C_UNK*, s32);                                              /* extern */
M2C_UNK fn_80113A68(M2C_UNK*);                                                   /* extern */
M2C_UNK fn_80113AA8(M2C_UNK*, u32, u32, M2C_UNK*, M2C_UNK);                      /* extern */
M2C_UNK fn_80113C7C(M2C_UNK*);                                                   /* extern */
M2C_UNK fn_801140DC(f32*, f32);                                                  /* extern */
M2C_UNK fn_80114394(f32*);                                                       /* extern */
M2C_UNK fn_8011C13C(u32);                                                        /* extern */
M2C_UNK fn_8011C188(u32, s32);                                                   /* extern */
M2C_UNK fn_8011C1C0(u32, s32);                                                   /* extern */
M2C_UNK fn_8011C1F8(u32, s32, M2C_UNK);                                          /* extern */
M2C_UNK fn_8011C6EC();                                                           /* extern */
M2C_UNK fn_80139784(void*, TObject*, f32*);                                      /* extern */
void* fn_80139984(M2C_UNK, M2C_UNK, M2C_UNK);                                    /* extern */
M2C_UNK fn_8014FF2C(s32);                                                        /* extern */
void* fn_80150588(u32);                                                          /* extern */
M2C_UNK fn_80150958();                                                           /* extern */
M2C_UNK fn_80195790(M2C_UNK*, RwFrame*, M2C_UNK, f32, f32);                      /* extern */
M2C_UNK fn_80195A74(M2C_UNK*, RwFrame*, M2C_UNK, f32, f32, f32);                 /* extern */
M2C_UNK fn_80196050(M2C_UNK*, void*, M2C_UNK);                                   /* extern */
M2C_UNK fn_801990E0(f32*, f32*);                                                 /* extern */
M2C_UNK fn_8019941C(f32*, f32*, M2C_UNK, M2C_UNK*);                              /* extern */
s32 fn_8019CE34(s32, f32*);                                                      /* extern */
void* fn_8019E8EC(u32);                                                          /* extern */
M2C_UNK fn_8019EB94(RwFrame*, void*, M2C_UNK);                                   /* extern */
M2C_UNK fn_8019ECCC(void*, s32*, M2C_UNK);                                       /* extern */
M2C_UNK fn_8019ED68(void*, RwFrame*, s32, f32);                                  /* extern */
s32 fn_801C28D8(f32*);                                                           /* extern */
M2C_UNK fn_8_90B10(s32);                                                         /* extern */
M2C_UNK fn_8_BD380(s32);                                                         /* extern */
void fn_8_BDF6C(TObject* arg0, void* arg1);                                      /* static */
void fn_8_BE528(void* arg0);                                                     /* static */
s32 fn_8_BF340(void* arg0);                                                      /* static */
s32 fn_8_BF524(s32 arg0);                                                        /* static */
s32 fn_8_BF5AC(void* arg0);                                                      /* static */
void fn_8_BFF94(void* arg0, s32 arg1);                                           /* static */
void fn_8_C08C8(void* arg0, s32 arg1);                                           /* static */
void fn_8_C14B4(TObject* arg0);                                                  /* static */
void fn_8_C1BCC(TObject* arg0);                                                  /* static */
TObject* fn_8_C2018(TObject* arg0);                                              /* static */
void turtleObjectCreate();                                                       /* static */
void turtleObjectLoad();                                                         /* static */
void turtleObjectUnload();                                                       /* static */
extern M2C_UNK fn_80113C2C;
extern RwFrame lbl_80239978;
extern RwFrame lbl_80239984;
extern RwFrame lbl_80239990;
extern M2C_UNK lbl_802AD090;
extern M2C_UNK lbl_80303DC8;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern M2C_UNK lbl_8042C1A4;
extern s32 lbl_8042C2A0;
extern u32 lbl_8042C388;
extern u32 lbl_8042C590;
extern u32 lbl_8042C6D0;
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
static TFunc lbl_8_data_17C58[6] = {
	NULL,
	NULL,
	(TFunc)fn_8_BE55C,
	(TFunc)fn_8_BE5AC,
	NULL,
	NULL,
};
static char lbl_8_data_17C70[] = "en_turtle.anm";
static M2C_UNK gap_04_00017C7E_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17C80[] = "en_turtle_start.anm";
static char lbl_8_data_17C94[] = "en_turtle_walk.anm";
static M2C_UNK gap_04_00017CA7_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17CA8[] = "en_turtle_defence.anm";
static M2C_UNK gap_04_00017CBE_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17CC0[] = "en_turtle_usided.anm";
static M2C_UNK gap_04_00017CD5_data; /* unable to generate initializer: unknown type */
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
static M2C_UNK gap_04_00017DC5_data; /* unable to generate initializer: unknown type */
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
static M2C_UNK gap_04_00017EDF_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17EE0[] = "MOVE RANGE";
static M2C_UNK gap_04_00017EEB_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17EEC[] = "SCOPE RANGE";
static char lbl_8_data_17EF8[] = "SCOPE OFFSET";
static M2C_UNK gap_04_00017F05_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17F08[] = "ATTACK INTERVAL";
static char lbl_8_data_17F18[] = "WEAPON SPEED";
static M2C_UNK gap_04_00017F25_data; /* unable to generate initializer: unknown type */
static char* turtleObjectFieldNames[9]
    = { lbl_8_data_17EBC, lbl_8_data_17EC8, lbl_8_data_17ED4, lbl_8_data_17ED4, lbl_8_data_17EE0,
	      lbl_8_data_17EEC, lbl_8_data_17EF8, lbl_8_data_17F08, lbl_8_data_17F18 };
static char lbl_8_data_17F4C[] = "NORMAL";
static M2C_UNK gap_04_00017F53_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17F54[]      = "SPECIAL";
static M2C_UNK* lbl_8_data_17F5C[2] = { (M2C_UNK*)lbl_8_data_17F4C, (M2C_UNK*)lbl_8_data_17F54 };
static char lbl_8_data_17F64[]      = "WAIT";
static M2C_UNK gap_04_00017F69_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17F6C[] = "WALK";
static M2C_UNK gap_04_00017F71_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_17F74[2] = { (M2C_UNK*)lbl_8_data_17F64, (M2C_UNK*)lbl_8_data_17F6C };
static s8 lbl_8_data_17F7C          = 0;
static s8 lbl_8_data_17F7D          = 1;
static s8 lbl_8_data_17F7E          = 0;
static s8 lbl_8_data_17F7F          = 1;
static char lbl_8_data_17F80[]      = "TObjEnemyTurtle";
static M2C_UNK* lbl_8_data_17F90    = (M2C_UNK*)lbl_8_data_17F80;
static u32 lbl_8_data_17F94[3]      = {
	0x00000000,
	0x3F800000,
	0x00000000,
};
static TFunc lbl_8_data_17FA0[42] = {
	NULL,
	NULL,
	(TFunc)fn_8_C1ED8,
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
	(TFunc)fn_8_C28CC,
	(TFunc)fn_8_BEDDC,
	(TFunc)fn_800A2F88,
	(TFunc)fn_8_BE978,
	(TFunc)fn_800A327C,
	(TFunc)fn_800A324C,
	(TFunc)fn_800A321C,
	(TFunc)fn_8_C0D74,
	(TFunc)fn_8_BFA30,
	(TFunc)fn_8_BF9FC,
	(TFunc)fn_8_BF9A8,
	(TFunc)fn_8_BF9A4,
	(TFunc)fn_8_BF8D4,
	(TFunc)fn_8_33D90,
	(TFunc)fn_8_33D94,
	(TFunc)fn_800A314C,
	(TFunc)fn_800A6D60,
	(TFunc)fn_8_BF858,
	(TFunc)fn_8_BE8B8,
	(TFunc)fn_800A3D6C,
	(TFunc)fn_800A2C6C,
	(TFunc)fn_8_BE644,
	(TFunc)fn_8_33D98,
	(TFunc)fn_800A31A0,
	(TFunc)fn_8_BE80C,
	(TFunc)fn_800A3148,
	(TFunc)fn_8_33DA0,
	(TFunc)fn_8_33DA4,
	(TFunc)fn_8_C2398,
};
static char lbl_8_data_180F4[] = "en_turtle.one";
static M2C_UNK gap_04_00018102_data; /* unable to generate initializer: unknown type */
static char turtleObjectDisplayName[] = "TURTLE OBJECT";
static M2C_UNK gap_04_00018112_data; /* unable to generate initializer: unknown type */
static char turtleObjectFieldTypes[] = "ccccfffif";
static M2C_UNK gap_04_0001811E_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_18120[] = "s11_k_spiderlight1.dff";
static M2C_UNK gap_04_00018137_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_18138[] = "s11_k_spiderlight2.dff";
static M2C_UNK gap_04_0001814F_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_18150[] = "s11_k_spiderlight3.dff";
static M2C_UNK gap_04_00018167_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_18168[] = "s11_k_spiderlight4.dff";
static M2C_UNK gap_04_0001817F_data; /* unable to generate initializer: unknown type */
static u32 lbl_8_bss_1B78;
static M2C_UNK turtleObjectGlobalAChain[3];
static M2C_UNK turtleObjectGlobalA[5];
static void* lbl_8_bss_1B9C;
static M2C_UNK turtleObjectEntry[12];
extern const f32 lbl_8_rodata_1E38[3] = { 0.0f, 1.5f, 0.0f };
extern const f32 lbl_8_rodata_1E44[3] = { 13.0f, 35.0f, 0.0f };
extern const f32 lbl_8_rodata_1E50[3] = { 24.0f, 1.0f, 24.0f };
extern const f32 lbl_8_rodata_1E5C[3] = { 0.0f, 0.0f, -1.0f };
extern const f32 lbl_8_rodata_1E68[1] = { 0.5f };
extern const f32 lbl_8_rodata_1E6C[1] = { 6.0f };
extern const f32 lbl_8_rodata_1E70[1] = { 0.0f };
extern const f32 lbl_8_rodata_1E74[1] = { 8.0f };
extern const f32 lbl_8_rodata_1E78[1] = { 1.2f };
extern const f32 lbl_8_rodata_1E7C[1] = { 0.005493164f };
extern const f64 lbl_8_rodata_1E80[1] = { 4503601774854144 };
extern const f32 lbl_8_rodata_1E88[1] = { 1.0f };
extern const f32 lbl_8_rodata_1E8C[1] = { 30.0f };
extern const f32 lbl_8_rodata_1E90[1] = { 100000000.0f };
extern const f32 lbl_8_rodata_1E94[1] = { 10000.0f };
extern const f32 lbl_8_rodata_1E98[1] = { 2.0f };
extern const f32 lbl_8_rodata_1E9C[1] = { 0.15f };
extern const f32 lbl_8_rodata_1EA0[1] = { 1.5f };
extern const f32 lbl_8_rodata_1EA4[1] = { -1.0f };
extern const f32 lbl_8_rodata_1EA8[1] = { 0.1f };
extern const f32 lbl_8_rodata_1EAC[1] = { -1000000.0f };
extern const f32 lbl_8_rodata_1EB0[1] = { 0.2f };
extern const f32 lbl_8_rodata_1EB4[1] = { 1.0f };
extern const f32 lbl_8_rodata_1EB8[1] = { 0.004f };
extern const f32 lbl_8_rodata_1EBC[1] = { 5.0f };
extern const f32 lbl_8_rodata_1EC0[1] = { 180.0f };
extern const f32 lbl_8_rodata_1EC4[1] = { 160.0f };
extern const f32 lbl_8_rodata_1EC8[1] = { 0.000030517578f };
extern const f32 lbl_8_rodata_1ECC[1] = { 80.0f };
extern const f32 lbl_8_rodata_1ED0[1] = { 0.3f };
extern const f32 lbl_8_rodata_1ED4[1] = { 0.2f };
extern const f32 lbl_8_rodata_1ED8[1] = { 3.0f };
extern const f32 lbl_8_rodata_1EDC[1] = { 12.0f };
extern const f32 lbl_8_rodata_1EE0[1] = { 0.8f };
extern const f32 lbl_8_rodata_1EE4[1] = { 0.0f };
extern const f32 lbl_8_rodata_1EE8[1] = { 10000.0f };
extern const f32 lbl_8_rodata_1EEC[1] = { 0.0f };
extern const f32 lbl_8_rodata_1EF0[1] = { 10000.0f };
extern const s32 lbl_8_rodata_1EF4[1] = { 0 };
extern const s32 lbl_8_rodata_1EF8[1] = { 0x2710 };
extern const f32 lbl_8_rodata_1EFC[1] = { 0.0f };
extern const f32 lbl_8_rodata_1F00[2] = { 10000.0f, 0.0f };

void fn_8_BDA48(s32 arg0)
{
	fn_8_BD380(arg0 - 0xB0);
}

void fn_8_BDA50(void* arg0, s32 arg1)
{
	s32 temp_r0;
	s32 temp_r31;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			return;
		case 1:
			temp_r0                     = M2C_FIELD(arg0, s32*, 0x18) - 1;
			M2C_FIELD(arg0, s32*, 0x18) = temp_r0;
			if (temp_r0 < 0) {
				temp_r31                 = M2C_FIELD(arg0, s32*, 8);
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = temp_r31;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
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
			return;
		case 1:
			temp_r0                     = M2C_FIELD(arg0, s32*, 0x18) - 1;
			M2C_FIELD(arg0, s32*, 0x18) = temp_r0;
			if (temp_r0 < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 7;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			if (fn_800A6334(M2C_FIELD(arg0, void**, 0x14)) == 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
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
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_BF524(M2C_FIELD(arg0, s32*, 0x14)) == 0)) {
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

void fn_8_BDD50(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x2A;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_BF340((void*)M2C_FIELD(arg0, u32*, 0x14)) != 0)) {
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

void fn_8_BDE04(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_BF340((void*)M2C_FIELD(arg0, u32*, 0x14)) != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 6;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
	}
}

void fn_8_BDEB8(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x78;
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			return;
		case 1:
			temp_r0                     = M2C_FIELD(arg0, s32*, 0x18) - 1;
			M2C_FIELD(arg0, s32*, 0x18) = temp_r0;
			if (temp_r0 < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 4:
			return;
	}
}

void fn_8_BDF6C(TObject* arg0, void* arg1)
{
	s32 temp_r0;
	void* temp_r4;

	arg0->unk14 = arg1;
	temp_r4     = arg0->unk14;
	if (temp_r4 != NULL) {
		temp_r0 = M2C_FIELD(temp_r4, s32*, 0x314);
		switch (temp_r0) { /* irregular */
			case 0:
				arg0->unkC  = 2;
				arg0->unk10 = 0;
				arg0->unk4  = 2;
				M2C_FIELD(arg0->unk0, M2C_UNK(**)(s32, M2C_UNK), 0x10)(arg0->unk4, 0);
				if ((s32)arg0->unk10 != 0) {
					fn_800A31B8(arg0->unk14);
					return;
				}
				break;
			case 1:
				arg0->unkC  = 1;
				arg0->unk10 = 0;
				arg0->unk4  = 1;
				M2C_FIELD(arg0->unk0, M2C_UNK(**)(s32, M2C_UNK), 0x10)(arg0->unk4, 0);
				if ((s32)arg0->unk10 != 0) {
					fn_800A31B8(arg0->unk14);
				}
				break;
		}
	}
}

s32 fn_8_BE044(void* arg0)
{
	s32 temp_r0;
	s32 temp_r30;
	s32 temp_r3_3;
	s32 var_r0;
	s32 var_r3;
	void* temp_r3;
	void* temp_r3_2;

	temp_r3  = M2C_FIELD(arg0, void**, 0x14);
	temp_r30 = M2C_FIELD(temp_r3, s32*, 0x19C);
	if ((fn_800A3ED4(temp_r3) != 0) && (temp_r30 != 0x1D)) {
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 5;
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 0);
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
			if (temp_r30 != 0x1F) {
				if ((temp_r30 < 0x1F) && (temp_r30 < 3)) {
					if (temp_r30 < 1) {
						goto block_18;
					}
					goto block_17;
				}
				goto block_18;
			}
		block_17:
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
			    arg0, M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 3;
			M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
			    arg0, M2C_FIELD(arg0, s32*, 4), 0);
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
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 6;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 41: /* switch 1 */
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 4;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
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
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 8;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				return 1;
		}
	} else {
		if ((u32)(temp_r3_3 & 0x2000) != 0) {
			if (temp_r30 != 0x1F) {
				if (temp_r30 < 0x1F) {
					if (temp_r30 != 2) {
						goto block_37;
					}
					goto block_36;
				}
				goto block_37;
			}
		block_36:
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
			    arg0, M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 9;
			M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
			    arg0, M2C_FIELD(arg0, s32*, 4), 0);
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
			/* fallthrough */
		default:
			return;
	}
}

M2C_UNK** fn_8_BE4C4(M2C_UNK** arg0, s16 arg1)
{
	s32 temp_cr0_eq;

	temp_cr0_eq = arg0 == NULL;
	if (temp_cr0_eq == 0) {
		*arg0 = (M2C_UNK*)lbl_8_data_17BB0;
		if (temp_cr0_eq == 0) {
			*arg0 = (M2C_UNK*)lbl_8_data_17C58;
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_BE528(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_17C58;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_17BB0;
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

void fn_8_BE644(void* arg0, s32 arg1)
{
	fn_8_90B10(arg1);
}

void fn_8_BE668(TObject* arg0)
{
	f32 temp_f31;
	s32 temp_r3;

	temp_r3 = arg0->unkD0;
	if (temp_r3 != (s32)arg0->unk2E4) {
		arg0->unk2E0 = 0;
		arg0->unk2E4 = temp_r3;
	}
	temp_f31 = arg0->unkB8;
	if (temp_r3 != 2) {
		return;
	}
	if ((temp_f31 > lbl_8_rodata_1E68[0]) && ((s32)arg0->unk2E0 == 0)) {
		arg0->unk2E0 = 1;
		fn_80139784(lbl_8_bss_1B9C, arg0, (f32*)((u8*)(u8*)arg0 + 0x140));
	}
	if ((temp_f31 > lbl_8_rodata_1E6C[0]) && ((s32)arg0->unk2E0 == 1)) {
		arg0->unk2E0 = 2;
		fn_80139784(lbl_8_bss_1B9C, arg0, &arg0->unk140);
	}
	if (((s32)arg0->unk2E0 != 0) && ((u32)(arg0->unkC8 & 2) != 0)) {
		arg0->unk2E0 = 0;
	}
}

void fn_8_BE770(void* arg0, void* arg1)
{
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
		fn_8010B074(M2C_FIELD(arg0, u32*, 0x2C0));
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
		fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x2BC), 6);
		fn_8010B208(M2C_FIELD(arg0, u32*, 0x2BC), lbl_8_rodata_1E70[0], lbl_8_rodata_1E70[0]);
	}
}

void fn_8_BE80C(void* arg0, void* arg1)
{
	f32 temp_f1;
	f32 var_f0;

	if ((s32)M2C_FIELD(arg1, u8*, 0) != 3) {
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
		fn_8010B074(M2C_FIELD(arg0, u32*, 0x2C0));
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
		fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x2BC), 6);
		fn_8010B208(M2C_FIELD(arg0, u32*, 0x2BC), lbl_8_rodata_1E70[0], lbl_8_rodata_1E70[0]);
	}
}

void fn_8_BE8B8(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		if ((u32)lbl_8042C6D0 == 0U) {
			fn_8011C6EC();
		}
		fn_8011C1F8(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x230), 0xC8);
		return;
	}
	if ((u32)lbl_8042C6D0 == 0U) {
		fn_8011C6EC();
	}
	fn_8011C1F8(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x230), 0x190);
	if ((u32)lbl_8042C6D0 == 0U) {
		fn_8011C6EC();
	}
	fn_8011C13C(lbl_8042C6D0);
}

void fn_8_BE978(void* arg0)
{
	RwV3d sp20;
	sAngle sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;

	M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x200);
	if ((u32)(M2C_FIELD(arg0, s32*, 0x188) & 0x10) != 0U) {
		M2C_FIELD(&sp20, M2C_BLOCK12*, 0) = M2C_FIELD(arg0, M2C_BLOCK12*, 0x140);
		M2C_FIELD(&sp14, M2C_BLOCK12*, 0) = M2C_FIELD(arg0, M2C_BLOCK12*, 0x14C);
		sp20.y += lbl_8_rodata_1E74[0];
		if ((u32)(M2C_FIELD(arg0, s32*, 0x188) & 0x10) != 0U) {
			fn_8006298C(6, &sp20.x, &sp14.x);
			fn_8006298C(2, &sp20.x, &sp14.x);
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(lbl_8042C388, 0xE017, (s32*)&sp20, 0, 1, 2, 0);
			}
			fn_8006298C(0xF, &sp20.x, &sp14.x);
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
				fn_80100AAC();
			}
			if (fn_8010037C(lbl_8042C590, 0, 5) != 0U) {
				sp8  = M2C_FIELD((f32*)lbl_8_rodata_1E38, s32*, 0);
				spC  = M2C_FIELD((f32*)lbl_8_rodata_1E38, s32*, 4);
				sp10 = M2C_FIELD((f32*)lbl_8_rodata_1E38, s32*, 8);
				sp14.y += 0x8000;
				fn_80102C50(lbl_8042C2A0, &sp20.x, &sp14.x, &sp8, 0, 0, 0, lbl_8_rodata_1E78[0],
				    lbl_8_rodata_1E70[0]);
			}
		}
	}
}

void fn_8_BEB1C(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x19C) != 0x1F) {
		M2C_FIELD(arg0, s32*, 0x29C) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x29C), 0, 0x220);
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x258) != NULL) {
		fn_8019ED68(M2C_FIELD(arg0, void**, 0x258), &lbl_80239984, 0,
		    lbl_8_rodata_1E7C[0] * (f32)M2C_FIELD(arg0, s32*, 0x29C));
		fn_8019ECCC(M2C_FIELD(arg0, void**, 0x258), (s32*)((u8*)arg0 + 0x25C), 2);
	}
}

void fn_8_BEBC8(void* arg0)
{
	RwV3d sp8;
	RwV3d sp14;
	u8 sp20[0x58];
	f32 temp_f1;
	f32 temp_f31;
	s32 temp_r0;
	void* temp_r30;

	if ((u32)M2C_FIELD(arg0, u32*, 0x258) != 0U) {
		temp_r0 = M2C_FIELD(arg0, s32*, 0x2D4);
		if (temp_r0 != -1) {
			temp_r30 = (void*)(u32) * (&lbl_802AD090 + (temp_r0 * 4));
			if (temp_r30 != NULL) {
				sp14.x   = M2C_FIELD((f32*)lbl_8_rodata_1E5C, f32*, 0);
				sp14.y   = M2C_FIELD((f32*)lbl_8_rodata_1E5C, f32*, 4);
				sp14.z   = M2C_FIELD((f32*)lbl_8_rodata_1E5C, s32*, 8);
				temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x150) + 0x8000);
				fn_80195790((s32*)sp20, &lbl_80239984, 0,
				    lbl_8_rodata_1E88[0] - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x150) + 0x8000),
				    temp_f31);
				fn_8019941C(&sp14.x, &sp14.x, 1, (s32*)sp20);
				sp14.y = lbl_8_rodata_1E70[0];
				fn_801990E0(&sp14.x, &sp14.x);
				sp8.x   = M2C_FIELD(temp_r30, f32*, 0x18) - M2C_FIELD(arg0, f32*, 0x140);
				sp8.y   = M2C_FIELD(temp_r30, f32*, 0x1C) - M2C_FIELD(arg0, f32*, 0x144);
				temp_f1 = M2C_FIELD(temp_r30, f32*, 0x20);
				sp8.z   = temp_f1 - M2C_FIELD(arg0, f32*, 0x148);
				sp8.y   = lbl_8_rodata_1E70[0];
				fn_801990E0(&sp8.x, &sp8.x);
				M2C_FIELD(arg0, s32*, 0x29C) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x29C),
				    fn_800D7920(&sp14.x, &sp8.x, (M2C_UNK*)lbl_8_data_17F94), 0x200);
			}
		}
	}
}

s32 fn_8_BED48(s32 arg0)
{
	if (fn_800209C8((s32*)((u8*)arg0 + 0x28), 1) != 0U) {
		return 1;
	}
	return fn_800207C4((s32*)((u8*)arg0 + 0x28), 0, 0xC) != 0U;
}

s32 fn_8_BEDA8(s32 arg0)
{
	return fn_800209C8((s32*)((u8*)arg0 + 0x28), 1) != 0U;
}

s32 fn_8_BEDDC(TObjEffTornadoSpin* arg0)
{
	s32 sp8;
	TObjEffTornadoSpin* var_r3;
	TObjEffTornadoSpin* var_r4;
	TObjEffTornadoSpin* var_r4_2;
	f32 temp_f30;
	f32 temp_f31;
	f32 var_f1;
	f32 var_f30;
	s32 temp_r3;
	s32 temp_r3_11;
	s32 temp_r3_2;
	s32 temp_r3_4;
	s32 temp_r3_5;
	s32 temp_r4;
	s32 temp_r4_2;
	s32 var_r0_4;
	s32 var_r29;
	s32 var_r30;
	s32 var_r3_3;
	s32 var_r3_4;
	u32 var_r0;
	u32 var_r0_2;
	u32 var_r0_3;
	u32 var_r28;
	void* temp_r3_10;
	void* temp_r3_3;
	void* temp_r3_6;
	void* temp_r3_7;
	void* temp_r3_8;
	void* temp_r3_9;
	void* var_r29_2;
	void* var_r29_3;
	void* var_r3_2;

	if (fn_800A2D90((s32)((u8*)arg0 + 0x140)) != 0) {
		arg0->unk1A4 = lbl_8_rodata_1E70[0];
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
		arg0->unk1A4 = lbl_8_rodata_1E70[0];
		arg0->unk230 = fn_800AB104(sp8);
		return 1;
	}
	sp8       = 0;
	temp_r3_2 = fn_800AAFEC(&arg0->unk140, &sp8);
	if ((temp_r3_2 != 0) && (temp_r3_2 >= 0) && (temp_r3_2 < 5)) {
		var_f1 = arg0->unk1A4 - lbl_8_rodata_1E8C[0];
		if (var_f1 < lbl_8_rodata_1E70[0]) {
			var_f1 = lbl_8_rodata_1E70[0];
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
		goto block_24;
	}
block_24:
	arg0->unk2D0 = 0;
	var_r30      = -1;
	if ((s32)(arg0->unk30 & 0x20) != 0) {
		arg0->unk2D0 = 1;
		fn_80021824(&lbl_8042C1A4);
	loop_30:
		temp_r3_3 = fn_800211A8(&arg0->unk28);
		if (temp_r3_3 != NULL) {
			var_r3_2 = M2C_FIELD(temp_r3_3, void**, 4);
		} else {
			var_r3_2 = NULL;
		}
		if (var_r3_2 != NULL) {
			temp_r3_4 = fn_80041B64(M2C_FIELD(var_r3_2, s32*, 0x78));
			if (temp_r3_4 != -1) {
				fn_800A4630(arg0, temp_r3_4);
			}
			temp_r3_5 = temp_r3_4 + 0x191;
			if ((s8) * ((u8*)arg0 + temp_r3_5) <= 0) {
				*((u8*)arg0 + temp_r3_5) = 0x14;
				var_r30                  = temp_r3_4;
			}
			goto loop_30;
		}
		fn_80021824(&lbl_8042C1A4);
	loop_39:
		temp_r3_6 = fn_800210C4(&arg0->unk28);
		if (temp_r3_6 != NULL) {
			var_r29_2 = M2C_FIELD(temp_r3_6, void**, 4);
		} else {
			var_r29_2 = NULL;
		}
		if (var_r29_2 != NULL) {
			var_r3_3 = fn_80041B64(M2C_FIELD(var_r29_2, s32*, 0x78));
			if (var_r3_3 == -1) {
				var_r3_3 = fn_80041AB0(M2C_FIELD(var_r29_2, s32*, 0x78));
			}
			temp_r4 = var_r3_3 + 0x191;
			if ((s8) * ((u8*)arg0 + temp_r4) <= 0) {
				*((u8*)arg0 + temp_r4) = 0x14;
				var_r30                = var_r3_3;
			}
			goto loop_39;
		}
		fn_80021824(&lbl_8042C1A4);
	loop_48:
		temp_r3_7 = fn_80020D1C(&arg0->unk28);
		if (temp_r3_7 != NULL) {
			var_r29_3 = M2C_FIELD(temp_r3_7, void**, 4);
		} else {
			var_r29_3 = NULL;
		}
		if (var_r29_3 != NULL) {
			var_r3_4 = fn_80041B64(M2C_FIELD(var_r29_3, s32*, 0x78));
			if (var_r3_4 == -1) {
				var_r3_4 = fn_80041AB0(M2C_FIELD(var_r29_3, s32*, 0x78));
			}
			temp_r4_2 = var_r3_4 + 0x191;
			if ((s8) * ((u8*)arg0 + temp_r4_2) <= 0) {
				*((u8*)arg0 + temp_r4_2) = 0x14;
				var_r30                  = var_r3_4;
			}
			goto loop_48;
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
					if (var_f30 < lbl_8_rodata_1E70[0]) {
						var_f30 = lbl_8_rodata_1E70[0];
					}
					if (fn_801031D8(arg0->unk230) != -1) {
						fn_800667B4(&arg0->unk13C, var_f30);
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

s32 fn_8_BF340(void* arg0)
{
	s32 temp_r3;

	temp_r3 = fn_800A6334(arg0);
	if ((temp_r3 == 1) && ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U)
	    && (((u32)M2C_FIELD(arg0, u32*, 0x2C0) == 0U) || (fn_8010AFB0() == 0))) {
		fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x2BC), 1);
		fn_8010B208(M2C_FIELD(arg0, u32*, 0x2BC), lbl_8_rodata_1E70[0], lbl_8_rodata_1E70[0]);
	}
	return temp_r3;
}

void fn_8_BF3CC(void* arg0)
{
	RwV3d sp48;
	RwV3d sp54;
	s32 sp74;
	s32 sp64;
	M2C_UNK sp8;
	f32 temp_f1;
	f32 temp_f31;
	s32 temp_r3_2;
	void* temp_r3;

	if ((u32)M2C_FIELD(arg0, u32*, 0x254) != 0U) {
		fn_80114394(&sp48.x);
		temp_r3   = fn_8019E8EC(M2C_FIELD(arg0, u32*, 0x254));
		sp48.x    = M2C_FIELD(temp_r3, f32*, 0x30);
		sp48.y    = M2C_FIELD(temp_r3, f32*, 0x34);
		sp48.z    = M2C_FIELD(temp_r3, f32*, 0x38);
		temp_r3_2 = M2C_FIELD(arg0, s32*, 0x29C) + M2C_FIELD(arg0, s32*, 0x150);
		sp64      = temp_r3_2;
		sp74      = 0x1A4;
		temp_f31  = fn_800D7B00(temp_r3_2 + 0x8000);
		fn_80195790(&sp8, &lbl_80239984, 0, lbl_8_rodata_1E88[0] - fn_800D7AE4(temp_r3_2 + 0x8000),
		    temp_f31);
		fn_8019941C(&sp54.x, &sp54.x, 1, &sp8);
		fn_801990E0(&sp54.x, &sp54.x);
		temp_f1 = M2C_FIELD(arg0, f32*, 0x31C);
		sp54.x *= temp_f1;
		sp54.y *= temp_f1;
		sp54.z *= temp_f1;
		fn_801140DC(&sp48.x, temp_f1);
		if ((u32)lbl_8042C388 != 0U) {
			fn_800B4A38(lbl_8042C388, 0x402E, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
		}
	}
}

s32 fn_8_BF524(s32 arg0)
{
	s32 temp_r3;
	u32 temp_r3_2;

	temp_r3 = fn_80103324(
	    (void*)((u8*)arg0 + 0x140), (s32*)(f32*)lbl_8_rodata_1E90, lbl_8_rodata_1E90[0]);
	if (temp_r3 != -1) {
		temp_r3_2 = *(&lbl_802AD090 + (temp_r3 * 4));
		if ((temp_r3_2 != 0U)
		    && (fn_800D71DC((s32)(temp_r3_2 + 0x18), (s32)((u8*)arg0 + 0x140))
		        < lbl_8_rodata_1E94[0])) {
			return 1;
		}
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
				fn_8010B0AC(
				    M2C_FIELD(arg0, u32*, 0x2C0), 0x5A, temp_f1, M2C_FIELD(arg0, f32*, 0x2B8));
			} else {
				fn_8010B208(M2C_FIELD(arg0, u32*, 0x2C0), temp_f1, M2C_FIELD(arg0, f32*, 0x2B8));
			}
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
			fn_8010B074(M2C_FIELD(arg0, u32*, 0x2BC));
		}
		var_r31 = 1;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
		fn_8010B350((u8*)arg0 + 0x140, (f32*)lbl_8_rodata_1E44);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
		fn_8010B350((u8*)arg0 + 0x140, (f32*)lbl_8_rodata_1E44);
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
	M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(
	    M2C_FIELD(arg0, s32*, 0x150), M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
	if (temp_r31 < 0x10) {
		M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
		return 1;
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
	if ((fn_800A5AC0() < lbl_8_rodata_1E98[0]) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
		fn_800A4668(arg0);
		var_r31 = 0;
	} else {
		fn_800A4A8C(arg0, (M2C_UNK*)(f32*)lbl_8_rodata_1E9C, lbl_8_rodata_1E9C[0]);
	}
	fn_800A5C6C(arg0, 0xF00);
	if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
	    && (M2C_FIELD(arg0, f32*, 0x15C) < (lbl_8_rodata_1EA0[0] * M2C_FIELD(arg0, f32*, 0x1A8)))) {
		M2C_FIELD(arg0, f32*, 0x15C) = lbl_8_rodata_1E70[0];
	}
	if (fn_800A5888(arg0, (M2C_UNK*)(f32*)lbl_8_rodata_1EA4, lbl_8_rodata_1EA4[0]) != 0) {
		fn_800A5B50(arg0, 0xF00);
		var_r31 = 0;
	} else if ((((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)
	               || (fn_800D7218((u8*)arg0 + 0x140, (u8*)arg0 + 0x1E4) < lbl_8_rodata_1EA8[0]))
	    && (fn_800A5998(arg0) <= 0)) {
		var_r31 = 0;
	}
	return var_r31;
}

s32 fn_8_BF858(void* arg0, f32 farg0)
{
	sVec4 sp8;

	if (M2C_FIELD(arg0, f32*, 0x2FC) != lbl_8_rodata_1EAC[0]) {
		sp8.x = M2C_FIELD(arg0, f32*, 0x2F8);
		sp8.y = M2C_FIELD(arg0, f32*, 0x2FC);
		sp8.z = M2C_FIELD(arg0, f32*, 0x300);
		sp8.w = farg0;
		return fn_8019CE34(*lbl_8042C9A4, &sp8.x) != 0;
	}
	return 0;
}

void fn_8_BF8D4(void* arg0)
{
	RwV3d spC;
	f32 sp8;
	f32* var_r3;
	f32 temp_f1;
	f32 temp_f2;
	f32 temp_f3;
	f32 temp_f1_2;

	fn_800B7864(0);
	M2C_FIELD(&spC, M2C_BLOCK12*, 0) = M2C_FIELD(lbl_8_rodata_1E50, M2C_BLOCK12*, 0);
	temp_f3                          = lbl_8_rodata_1E88[0];
	temp_f2 = lbl_8_rodata_1EB8[0] * (M2C_FIELD(arg0, f32*, 0x144) - M2C_FIELD(arg0, f32*, 0x2FC));
	temp_f1 = temp_f3 - temp_f2;
	sp8     = temp_f1;
	if (temp_f1 < lbl_8_rodata_1EB0[0]) {
		var_r3 = (f32*)lbl_8_rodata_1EB0;
	} else if (temp_f1 > lbl_8_rodata_1EB4[0]) {
		var_r3 = (f32*)lbl_8_rodata_1EB4;
	} else {
		var_r3 = &sp8;
	}
	temp_f1_2 = *var_r3;
	sp8       = temp_f1_2;
	fn_800B7514((u8*)arg0 + 0x2F8, (u8*)arg0 + 0x304, &spC.x, temp_f1_2);
	fn_800B7820();
}

void fn_8_BF9A4(void) { }

void fn_8_BF9A8(void* arg0)
{
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x90)();
	fn_80113874();
	fn_8011398C(turtleObjectGlobalA, M2C_FIELD(arg0, s32*, 0x310));
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0xE8));
}

void fn_8_BF9FC(TObject* arg0)
{
	fn_8_C1BCC(arg0);
	fn_8_C14B4(arg0);
}

void fn_8_BFA30(TObject* arg0)
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
	M2C_FIELD(arg0->unk18, M2C_UNK(**)(TObject*), 0x38)(arg0);
	temp_r3 = arg0->unk240;
	if (temp_r3 != NULL) {
		M2C_FIELD(*temp_r3, M2C_UNK(**)(TObject*), 0xC)(arg0);
	}
	M2C_FIELD(arg0->unk18, M2C_UNK(**)(TObject*, s32, M2C_UNK), 0x50)(arg0, arg0->unk19C, 1);
	fn_8_C14B4(arg0);
	fn_800A3D48(arg0);
	if ((s32)arg0->unk2F4 != 0) {
		temp_r3_2 = arg0->unkD0;
		if (temp_r3_2 != (s32)arg0->unk2E4) {
			arg0->unk2E0 = 0;
			arg0->unk2E4 = temp_r3_2;
		}
		temp_f31 = arg0->unkB8;
		if (temp_r3_2 != 2) {

		} else {
			if ((temp_f31 > lbl_8_rodata_1E68[0]) && ((s32)arg0->unk2E0 == 0)) {
				arg0->unk2E0 = 1;
				fn_80139784(lbl_8_bss_1B9C, arg0, &arg0->unk140);
			}
			if ((temp_f31 > lbl_8_rodata_1E6C[0]) && ((s32)arg0->unk2E0 == 1)) {
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
			arg0->unk29C = fn_800D7A94(arg0->unk29C, 0, 0x220);
		}
		if ((void*)arg0->unk258 != NULL) {
			fn_8019ED68(M2C_FIELD(arg0, void**, 0x258), &lbl_80239984, 0,
			    lbl_8_rodata_1E7C[0] * (f32)arg0->unk29C);
			fn_8019ECCC(arg0->unk258, &arg0->unk25C, 2);
		}
	}
	if (((s32)arg0->unk2C4 != 0) && ((s32)arg0->unk24C != -1)) {
		fn_800FE464(arg0->unk250);
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
		fn_8003BC38(&arg0->unk28);
	}
}

void fn_8_BFD74(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2D8) = 0x5A;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			if ((u32)lbl_8042C6D0 == 0U) {
				fn_8011C6EC();
			}
			fn_8011C188(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x238));
			return;
		case 1:
			temp_r0                      = M2C_FIELD(arg0, s32*, 0x2D8) - 1;
			M2C_FIELD(arg0, s32*, 0x2D8) = temp_r0;
			if (temp_r0 == 0) {
				if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
					fn_8010B074(M2C_FIELD(arg0, u32*, 0x2C0));
				}
				if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
					fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x2BC), 2);
					fn_8010B208(
					    M2C_FIELD(arg0, u32*, 0x2BC), lbl_8_rodata_1E70[0], lbl_8_rodata_1E70[0]);
					return;
				}
			} else {
				case 2:
					return;
			}
			break;
		case 3:
			if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
				fn_8010B074(M2C_FIELD(arg0, u32*, 0x2BC));
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
			if ((u32)lbl_8042C6D0 == 0U) {
				fn_8011C6EC();
			}
			fn_8011C1C0(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x234));
			fn_800A3CBC(arg0);
			M2C_FIELD(arg0, f32*, 0x15C) = lbl_8_rodata_1EBC[0];
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
			return;
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
		case 4:
			break;
	}
}

void fn_8_BFF94(void* arg0, s32 arg1)
{
	RwV3d sp8;
	RwV3d sp14;
	RwV3d sp20;
	RwV3d sp2C;
	RwV3d sp38;
	M2C_UNK sp9C;
	M2C_UNK sp5C;
	s32 sp58;
	s32 sp48;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f31;
	f32 temp_f31_2;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r30;
	s32 temp_r3_5;
	s32 var_r0;
	void* temp_r30_2;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2C8) = 0;
			if ((void*)M2C_FIELD(arg0, void**, 0x2EC) == NULL) {
				M2C_FIELD(arg0, void**, 0x2EC)
				    = fn_800627BC(0x1F, (u8*)arg0 + 0x140, (u8*)arg0 + 0x14C);
				return;
			}
		case 2:
			return;
		case 1:
			if ((void*)M2C_FIELD(arg0, void**, 0x2EC) != NULL) {
				if (fn_80017800(arg0) == 0) {
					M2C_FIELD(arg0, void**, 0x2EC) = NULL;
					return;
				}
				if ((u32)M2C_FIELD(arg0, u32*, 0x254) != 0U) {
					temp_r3                          = fn_8019E8EC(M2C_FIELD(arg0, u32*, 0x254));
					sp20.x                           = M2C_FIELD(temp_r3, f32*, 0x30);
					sp20.y                           = M2C_FIELD(temp_r3, f32*, 0x34);
					sp20.z                           = M2C_FIELD(temp_r3, f32*, 0x38);
					temp_r4                          = (u8*)arg0 + 0x14C;
					temp_r3_2                        = M2C_FIELD(arg0, void**, 0x2EC);
					M2C_FIELD(temp_r3_2, f32*, 0x80) = sp20.x;
					M2C_FIELD(temp_r3_2, f32*, 0x84) = sp20.y;
					M2C_FIELD(temp_r3_2, f32*, 0x88) = sp20.z;
					if (temp_r4 != NULL) {
						M2C_FIELD(temp_r3_2, s32*, 0x8C) = (s32)M2C_FIELD(arg0, s32*, 0x14C);
						M2C_FIELD(temp_r3_2, s32*, 0x90) = (s32)M2C_FIELD(temp_r4, s32*, 4);
						M2C_FIELD(temp_r3_2, s32*, 0x94) = (s32)M2C_FIELD(temp_r4, s32*, 8);
					}
				}
				M2C_FIELD(arg0, s32*, 0x2D4) = fn_80103324((void*)((u8*)arg0 + 0x140),
				    (s32*)(f32*)lbl_8_rodata_1E90, lbl_8_rodata_1E90[0]);
				temp_r0                      = M2C_FIELD(arg0, s32*, 0x2D4);
				if (temp_r0 != -1) {
					temp_r3_3 = (void*)(u32) * (&lbl_802AD090 + (temp_r0 * 4));
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
					M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
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
						temp_r30_2 = (void*)(u32) * (&lbl_802AD090 + (temp_r0_2 * 4));
						if (temp_r30_2 != NULL) {
							sp8.x    = M2C_FIELD((f32*)lbl_8_rodata_1E5C, f32*, 0);
							sp8.y    = M2C_FIELD((f32*)lbl_8_rodata_1E5C, f32*, 4);
							sp8.z    = M2C_FIELD((f32*)lbl_8_rodata_1E5C, s32*, 8);
							temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x150) + 0x8000);
							fn_80195790(&sp9C, &lbl_80239984, 0,
							    lbl_8_rodata_1E88[0]
							        - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x150) + 0x8000),
							    temp_f31);
							fn_8019941C(&sp8.x, &sp8.x, 1, &sp9C);
							sp8.y = lbl_8_rodata_1E70[0];
							fn_801990E0(&sp8.x, &sp8.x);
							sp14.x
							    = M2C_FIELD(temp_r30_2, f32*, 0x18) - M2C_FIELD(arg0, f32*, 0x140);
							sp14.y
							    = M2C_FIELD(temp_r30_2, f32*, 0x1C) - M2C_FIELD(arg0, f32*, 0x144);
							temp_f1 = M2C_FIELD(temp_r30_2, f32*, 0x20);
							sp14.z  = temp_f1 - M2C_FIELD(arg0, f32*, 0x148);
							sp14.y  = lbl_8_rodata_1E70[0];
							fn_801990E0(&sp14.x, &sp14.x);
							M2C_FIELD(arg0, s32*, 0x29C) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x29C),
							    fn_800D7920(&sp8.x, &sp14.x, (M2C_UNK*)lbl_8_data_17F94), 0x200);
							return;
						}
					}
				}
			} else if ((s32)M2C_FIELD(arg0, s32*, 0x2C8) == 0) {
				if ((u32)M2C_FIELD(arg0, u32*, 0x254) != 0U) {
					fn_80114394(&sp2C.x);
					temp_r3_4  = fn_8019E8EC(M2C_FIELD(arg0, u32*, 0x254));
					sp2C.x     = M2C_FIELD(temp_r3_4, f32*, 0x30);
					sp2C.y     = M2C_FIELD(temp_r3_4, f32*, 0x34);
					sp2C.z     = M2C_FIELD(temp_r3_4, f32*, 0x38);
					temp_r3_5  = M2C_FIELD(arg0, s32*, 0x29C) + M2C_FIELD(arg0, s32*, 0x150);
					sp48       = temp_r3_5;
					sp58       = 0x1A4;
					temp_f31_2 = fn_800D7B00(temp_r3_5 + 0x8000);
					fn_80195790(&sp5C, &lbl_80239984, 0,
					    lbl_8_rodata_1E88[0] - fn_800D7AE4(temp_r3_5 + 0x8000), temp_f31_2);
					fn_8019941C(&sp38.x, &sp38.x, 1, &sp5C);
					fn_801990E0(&sp38.x, &sp38.x);
					temp_f1_2 = M2C_FIELD(arg0, f32*, 0x31C);
					sp38.x *= temp_f1_2;
					sp38.y *= temp_f1_2;
					sp38.z *= temp_f1_2;
					fn_801140DC(&sp2C.x, temp_f1_2);
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x402E, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
					}
				}
				M2C_FIELD(arg0, s32*, 0x2C8) = 1;
				M2C_FIELD(arg0, s32*, 0x248) = 0x1F;
				return;
			}
			break;
		case 3:
			if ((void*)M2C_FIELD(arg0, void**, 0x2EC) != NULL) {
				fn_8005FD8C(-1);
				M2C_FIELD(arg0, void**, 0x2EC) = NULL;
			}
			break;
	}
}

void fn_8_C0418(void* arg0, s32 arg1)
{
	RwV3d sp8;
	RwV3d sp14;
	u8 sp20[0x58];
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
			return;
		case 1:
			M2C_FIELD(arg0, s32*, 0x2D4) = fn_80103324(
			    (void*)((u8*)arg0 + 0x140), (s32*)(f32*)lbl_8_rodata_1E90, lbl_8_rodata_1E90[0]);
			temp_r0 = M2C_FIELD(arg0, s32*, 0x2D4);
			if (temp_r0 != -1) {
				temp_r3 = (void*)(u32) * (&lbl_802AD090 + (temp_r0 * 4));
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
				M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
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
					temp_r30_2 = (void*)(u32) * (&lbl_802AD090 + (temp_r0_2 * 4));
					if (temp_r30_2 != NULL) {
						sp8.x    = M2C_FIELD((f32*)lbl_8_rodata_1E5C, f32*, 0);
						sp8.y    = M2C_FIELD((f32*)lbl_8_rodata_1E5C, f32*, 4);
						sp8.z    = M2C_FIELD((f32*)lbl_8_rodata_1E5C, s32*, 8);
						temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x150) + 0x8000);
						fn_80195790((s32*)sp20, &lbl_80239984, 0,
						    lbl_8_rodata_1E88[0]
						        - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x150) + 0x8000),
						    temp_f31);
						fn_8019941C(&sp8.x, &sp8.x, 1, (s32*)sp20);
						sp8.y = lbl_8_rodata_1E70[0];
						fn_801990E0(&sp8.x, &sp8.x);
						sp14.x  = M2C_FIELD(temp_r30_2, f32*, 0x18) - M2C_FIELD(arg0, f32*, 0x140);
						sp14.y  = M2C_FIELD(temp_r30_2, f32*, 0x1C) - M2C_FIELD(arg0, f32*, 0x144);
						temp_f1 = M2C_FIELD(temp_r30_2, f32*, 0x20);
						sp14.z  = temp_f1 - M2C_FIELD(arg0, f32*, 0x148);
						sp14.y  = lbl_8_rodata_1E70[0];
						fn_801990E0(&sp14.x, &sp14.x);
						M2C_FIELD(arg0, s32*, 0x29C) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x29C),
						    fn_800D7920(&sp8.x, &sp14.x, (M2C_UNK*)lbl_8_data_17F94), 0x200);
					}
				}
			}
			return;
		case 4:
			return;
	}
}

void fn_8_C0690(void* arg0, s32 arg1)
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
				return;
			}
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
			return;
		case 1:
			if ((fn_800A37A4() == 1) && ((s32)M2C_FIELD(arg0, s32*, 0x2CC) == 0)) {
				M2C_FIELD(arg0, s32*, 0x2CC) = 1;
				temp_f1                      = M2C_FIELD(arg0, f32*, 0x1A4) - lbl_8_rodata_1E88[0];
				M2C_FIELD(arg0, f32*, 0x1A4) = temp_f1;
				if (temp_f1 < lbl_8_rodata_1E70[0]) {
					M2C_FIELD(arg0, f32*, 0x1A4) = lbl_8_rodata_1E70[0];
				}
				M2C_FIELD(arg0, s16*, 0x2E) = (s16)M2C_FIELD(arg0, f32*, 0x1A4);
				if ((u32)lbl_8042C388 != 0U) {
					fn_800B4A38(lbl_8042C388, 0x402F, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
				}
				temp_r0 = M2C_FIELD(arg0, s32*, 0x2DC);
				if ((temp_r0 != -1) && ((u32) * (&lbl_80303DC8 + (temp_r0 * 4)) != 0U)) {
					M2C_FIELD(arg0, s32*, 0x230) = fn_8009278C(0);
				}
			}
			return;
		case 4:
			return;
	}
}

void fn_8_C086C(void* arg0, s32 arg1)
{
	void* temp_r3;
	void* temp_r4;

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

void fn_8_C08C8(void* arg0, s32 arg1)
{
	u8 sp14[0x44];
	RwV3d sp8;
	f32 temp_f3;
	s32 temp_r31;
	s32 temp_r31_2;
	s32 var_r0;
	s32 var_r31;
	s32 var_r4;

	switch (arg1) { /* irregular */
		case 0:
			var_r4                       = 0;
			M2C_FIELD(arg0, s32*, 0x2C4) = 0;
			M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFDFFFFF);
			M2C_FIELD(arg0, s32*, 0xD4)  = 2;
			M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x2A8);
			M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x2AC);
			M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x2B0);
			if ((s32)M2C_FIELD(arg0, s32*, 0x2F0) == 0) {

			} else {
				temp_r31                     = fn_800A5A54(arg0);
				M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
				    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
				if (temp_r31 < 0x10) {
					M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
					var_r4                       = 1;
				} else {
					var_r4 = 0;
				}
			}
			if (var_r4 != 0) {
				M2C_FIELD(arg0, s32*, 0x2A4) = 1;
				return;
			}
			M2C_FIELD(arg0, s32*, 0x2A4) = 0;
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x2A4) != 0) {
				var_r31 = 1;
				if ((s32)M2C_FIELD(arg0, s32*, 0x2F0) == 0) {

				} else {
					if ((fn_800A5AC0() < lbl_8_rodata_1E98[0])
					    || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
						fn_800A4668(arg0);
						var_r31 = 0;
					} else {
						fn_800A4A8C(arg0, (M2C_UNK*)(f32*)lbl_8_rodata_1E9C, lbl_8_rodata_1E9C[0]);
					}
					fn_800A5C6C(arg0, 0xF00);
					if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
					    && (M2C_FIELD(arg0, f32*, 0x15C)
					        < (lbl_8_rodata_1EA0[0] * M2C_FIELD(arg0, f32*, 0x1A8)))) {
						M2C_FIELD(arg0, f32*, 0x15C) = lbl_8_rodata_1E70[0];
					}
					if (fn_800A5888(arg0, (M2C_UNK*)(f32*)lbl_8_rodata_1EA4, lbl_8_rodata_1EA4[0])
					    != 0) {
						fn_800A5B50(arg0, 0xF00);
						var_r31 = 0;
					} else if ((((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)
					               || (fn_800D7218((u8*)arg0 + 0x140, (u8*)arg0 + 0x1E4)
					                   < lbl_8_rodata_1EA8[0]))
					    && (fn_800A5998(arg0) <= 0)) {
						var_r31 = 0;
					}
				}
				if (var_r31 == 0) {
					sp8.x = lbl_8_rodata_1E70[0];
					sp8.y = lbl_8_rodata_1E70[0];
					sp8.z = M2C_FIELD(arg0, f32*, 0x2A0);
					temp_f3
					    = (lbl_8_rodata_1EC4[0] * (lbl_8_rodata_1EC8[0] * (f32)fn_801C28D8(&sp8.x)))
					    - lbl_8_rodata_1ECC[0];
					fn_80195A74((s32*)sp14, &lbl_80239984, 0,
					    lbl_8_rodata_1EC0[0]
					        + (lbl_8_rodata_1E7C[0]
					            * (f32)M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x10))
					        + temp_f3,
					    lbl_8_rodata_1EC0[0], temp_f3);
					fn_80196050((s32*)sp14, M2C_FIELD(arg0, void**, 0xB0), 2);
					fn_8019941C(&sp8.x, &sp8.x, 1, (s32*)sp14);
					M2C_FIELD(arg0, f32*, 0x1CC) = sp8.x;
					M2C_FIELD(arg0, f32*, 0x1D0) = sp8.y;
					M2C_FIELD(arg0, f32*, 0x1D4) = sp8.z;
					M2C_FIELD(arg0, f32*, 0x2A0)
					    = (f32)(M2C_FIELD(arg0, f32*, 0x2A0) * lbl_8_rodata_1EA4[0]);
					M2C_FIELD(arg0, s32*, 0x2A4) = 0;
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x2A4) == 0) {
				if ((s32)M2C_FIELD(arg0, s32*, 0x2F0) == 0) {
					var_r0 = 0;
				} else {
					temp_r31_2                   = fn_800A5A54(arg0);
					M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
					    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
					if (temp_r31_2 < 0x10) {
						M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
						var_r0                       = 1;
					} else {
						var_r0 = 0;
					}
				}
				if (var_r0 != 0) {
					M2C_FIELD(arg0, s32*, 0x2A4) = 1;
					return;
				}
			} else {
				case 2:
					return;
			}
			break;
		case 3:
			M2C_FIELD(arg0, f32*, 0x2A8) = (f32)M2C_FIELD(arg0, f32*, 0x1CC);
			M2C_FIELD(arg0, f32*, 0x2AC) = (f32)M2C_FIELD(arg0, f32*, 0x1D0);
			M2C_FIELD(arg0, f32*, 0x2B0) = (f32)M2C_FIELD(arg0, f32*, 0x1D4);
			break;
	}
}

void fn_8_C0C9C(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2E8) = 0;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x2E8) == 0) {
				if (M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), f32*, 0) >= lbl_8_rodata_1E6C[0]) {
					M2C_FIELD(arg0, s32*, 0x2E8) = 1;
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(lbl_8042C388, 0x402C, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
					}
				}
			}
			if ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), s32*, 0x10) & 1) != 0) {
				M2C_FIELD(arg0, s32*, 0x2C4) = 0;
			}
			return;
		case 4:
			return;
	}
}

void fn_8_C0D74(void* arg0, u32 arg1, s32 arg2)
{
	RwV3d sp8;
	RwV3d sp14;
	u8 sp20[0x38];
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

	switch (arg1) {         /* switch 1 */
		case 1:             /* switch 1 */
			switch (arg2) { /* switch 2; irregular */
				case 0:     /* switch 2 */
					M2C_FIELD(arg0, s32*, 0x2E8) = 0;
					M2C_FIELD(arg0, s32*, 0xD4)  = 0;
					return;
				case 1: /* switch 2 */
					if ((s32)M2C_FIELD(arg0, s32*, 0x2E8) == 0) {
						M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
						if (M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), f32*, 0)
						    == lbl_8_rodata_1E6C[0]) {
							M2C_FIELD(arg0, s32*, 0x2E8) = 1;
							if ((u32)lbl_8042C388 != 0U) {
								fn_800B4A38(
								    lbl_8042C388, 0x402C, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
							}
						}
					}
					if ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), s32*, 0x10) & 1) != 0) {
						M2C_FIELD(arg0, s32*, 0x2C4) = 0;
						return;
					}
				default: /* switch 1 */
				case 2:  /* switch 9 */
					return;
			}
			break;
		case 2: /* switch 1 */
			fn_8_C08C8(arg0, arg2);
			return;
		case 40:            /* switch 1 */
			switch (arg2) { /* switch 3; irregular */
				case 0:     /* switch 3 */
					temp_r3                        = M2C_FIELD(arg0, void**, 0x38);
					M2C_FIELD(temp_r3, s32*, 0x34) = (s32)(M2C_FIELD(temp_r3, s32*, 0x34) | 0x10);
					M2C_FIELD(arg0, s32*, 0x188)   = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x20000);
					M2C_FIELD(arg0, s32*, 0xD4)    = 3;
					return;
				case 3: /* switch 3 */
					M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFFDFFFF);
					temp_r3_2                    = M2C_FIELD(arg0, void**, 0x38);
					M2C_FIELD(temp_r3_2, s32*, 0x34)
					    = (s32)(M2C_FIELD(temp_r3_2, s32*, 0x34) & 0xFFFFFFEF);
					return;
			}
			break;
		case 41:            /* switch 1 */
			switch (arg2) { /* switch 4; irregular */
				case 0:     /* switch 4 */
					M2C_FIELD(arg0, s32*, 0x2CC) = 0;
					M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFDFFFFF);
					M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFFBFFFF);
					M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x400000);
					return;
				case 1: /* switch 4 */
					if ((fn_800A37A4() == 1) && ((s32)M2C_FIELD(arg0, s32*, 0x2CC) == 0)) {
						M2C_FIELD(arg0, s32*, 0x2CC) = 1;
						temp_f1 = M2C_FIELD(arg0, f32*, 0x1A4) - lbl_8_rodata_1E88[0];
						M2C_FIELD(arg0, f32*, 0x1A4) = temp_f1;
						if (temp_f1 < lbl_8_rodata_1E70[0]) {
							M2C_FIELD(arg0, f32*, 0x1A4) = lbl_8_rodata_1E70[0];
						}
						M2C_FIELD(arg0, s16*, 0x2E) = (s16)M2C_FIELD(arg0, f32*, 0x1A4);
						if ((u32)lbl_8042C388 != 0U) {
							fn_800B4A38(
							    lbl_8042C388, 0x402F, (s32*)((u8*)arg0 + 0x140), 0, 1, 0, 0);
						}
						temp_r0 = M2C_FIELD(arg0, s32*, 0x2DC);
						if ((temp_r0 != -1) && ((u32) * (&lbl_80303DC8 + (temp_r0 * 4)) != 0U)) {
							M2C_FIELD(arg0, s32*, 0x230) = fn_8009278C(0);
							return;
						}
					}
					break;
			}
			break;
		case 42:            /* switch 1 */
			switch (arg2) { /* switch 5; irregular */
				case 0:     /* switch 5 */
					M2C_FIELD(arg0, s32*, 0xD4) = 1;
					return;
				case 3: /* switch 5 */
					if ((s32)M2C_FIELD(arg0, s32*, 0x24C) != -1) {
						M2C_FIELD(arg0, s32*, 0x2C4)                          = 1;
						M2C_FIELD(M2C_FIELD(arg0, void**, 0x250), s32*, 0x1C) = 1;
						return;
					}
					break;
			}
			break;
		case 29:            /* switch 1 */
			switch (arg2) { /* switch 6; irregular */
				case 0:     /* switch 6 */
					M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x3C)();
					return;
				case 1: /* switch 6 */
					M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
					return;
			}
			break;
		case 31:            /* switch 1 */
			switch (arg2) { /* switch 7; irregular */
				case 0:     /* switch 7 */
					M2C_FIELD(arg0, s32*, 0xD4) = 2;
					return;
				case 1: /* switch 7 */
					M2C_FIELD(arg0, s32*, 0x2D4) = fn_80103324((void*)((u8*)arg0 + 0x140),
					    (s32*)(f32*)lbl_8_rodata_1E90, lbl_8_rodata_1E90[0]);
					temp_r0_2                    = M2C_FIELD(arg0, s32*, 0x2D4);
					if (temp_r0_2 != -1) {
						temp_r3_3 = (void*)(u32) * (&lbl_802AD090 + (temp_r0_2 * 4));
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
						M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
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
							temp_r30_2 = (void*)(u32) * (&lbl_802AD090 + (temp_r0_3 * 4));
							if (temp_r30_2 != NULL) {
								sp8.x    = M2C_FIELD((f32*)lbl_8_rodata_1E5C, f32*, 0);
								sp8.y    = M2C_FIELD((f32*)lbl_8_rodata_1E5C, f32*, 4);
								sp8.z    = M2C_FIELD((f32*)lbl_8_rodata_1E5C, s32*, 8);
								temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x150) + 0x8000);
								fn_80195790((s32*)sp20, &lbl_80239984, 0,
								    lbl_8_rodata_1E88[0]
								        - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x150) + 0x8000),
								    temp_f31);
								fn_8019941C(&sp8.x, &sp8.x, 1, (s32*)sp20);
								sp8.y = lbl_8_rodata_1E70[0];
								fn_801990E0(&sp8.x, &sp8.x);
								sp14.x = M2C_FIELD(temp_r30_2, f32*, 0x18)
								    - M2C_FIELD(arg0, f32*, 0x140);
								sp14.y = M2C_FIELD(temp_r30_2, f32*, 0x1C)
								    - M2C_FIELD(arg0, f32*, 0x144);
								temp_f1_2 = M2C_FIELD(temp_r30_2, f32*, 0x20);
								sp14.z    = temp_f1_2 - M2C_FIELD(arg0, f32*, 0x148);
								sp14.y    = lbl_8_rodata_1E70[0];
								fn_801990E0(&sp14.x, &sp14.x);
								M2C_FIELD(arg0, s32*, 0x29C)
								    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x29C),
								        fn_800D7920(&sp8.x, &sp14.x, (M2C_UNK*)lbl_8_data_17F94),
								        0x200);
								return;
							}
						}
					}
					break;
			}
			break;
		case 32: /* switch 1 */
			fn_8_BFF94(arg0, arg2);
			return;
		case 26:            /* switch 1 */
			switch (arg2) { /* switch 8; irregular */
				case 0:     /* switch 8 */
					M2C_FIELD(arg0, s32*, 0x2DC) = (s32)M2C_FIELD(arg0, s32*, 0x234);
					if ((u32)lbl_8042C6D0 == 0U) {
						fn_8011C6EC();
					}
					fn_8011C1C0(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x234));
					fn_800A3CBC(arg0);
					M2C_FIELD(arg0, f32*, 0x15C) = lbl_8_rodata_1EBC[0];
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
				case 1: /* switch 8 */
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
			}
			break;
		case 36:            /* switch 1 */
			switch (arg2) { /* switch 9; irregular */
				case 0:     /* switch 9 */
					M2C_FIELD(arg0, s32*, 0x2D8) = 0x5A;
					M2C_FIELD(arg0, s32*, 0xD4)  = 0;
					if ((u32)lbl_8042C6D0 == 0U) {
						fn_8011C6EC();
					}
					fn_8011C188(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x238));
					return;
				case 1: /* switch 9 */
					temp_r0_4                    = M2C_FIELD(arg0, s32*, 0x2D8) - 1;
					M2C_FIELD(arg0, s32*, 0x2D8) = temp_r0_4;
					if (temp_r0_4 == 0) {
						if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
							fn_8010B074(M2C_FIELD(arg0, u32*, 0x2C0));
						}
						if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
							fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x2BC), 2);
							fn_8010B208(M2C_FIELD(arg0, u32*, 0x2BC), lbl_8_rodata_1E70[0],
							    lbl_8_rodata_1E70[0]);
							return;
						}
					}
					break;
				case 3: /* switch 9 */
					if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
						fn_8010B074(M2C_FIELD(arg0, u32*, 0x2BC));
					}
					break;
			}
			break;
		case 4:
			break;
	}
}

void fn_8_C14B4(TObject* arg0)
{
	s32 sp8;
	s32 sp10;
	RwFrame* temp_r31;
	TEnemyParalysis* temp_r3_2;
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
		if (((s32)arg0->unk19C == 0x24) && (temp_r3_2 = arg0->unk244, ((temp_r3_2 == NULL) == 0))) {
			Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(
			    temp_r3_2, temp_r31, (RwOpCombineType)0);
			fn_8019ED68(temp_r31, &lbl_80239990, 2, lbl_8_rodata_1E7C[0] * (f32)arg0->unk154);
			fn_8019ED68(temp_r31, &lbl_80239978, 2, lbl_8_rodata_1E7C[0] * (f32)arg0->unk14C);
			fn_8019ED68(temp_r31, &lbl_80239984, 2,
			    lbl_8_rodata_1EC0[0] + (lbl_8_rodata_1E7C[0] * (f32)arg0->unk150));
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
			SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(
			    arg0->unk244, (u8*)arg0 + 0x140, (u8*)arg0 + 0x14C);
		} else {
			fn_8019ED68(temp_r31, &lbl_80239990, 0, lbl_8_rodata_1E7C[0] * (f32)arg0->unk154);
			fn_8019ED68(temp_r31, &lbl_80239978, 2, lbl_8_rodata_1E7C[0] * (f32)arg0->unk14C);
			fn_8019ED68(temp_r31, &lbl_80239984, 2,
			    lbl_8_rodata_1EC0[0] + (lbl_8_rodata_1E7C[0] * (f32)arg0->unk150));
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
		}
	}
	if ((s32)arg0->unk24C == -1) {
		arg0->unk24C = fn_8005D9A0(arg0->unkEC, 0x3E8);
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
			temp_r3_3 = fn_8005D9A0(temp_r31_2, 0x3EA);
			if (temp_r3_3 != -1) {
				arg0->unk254 = M2C_FIELD(
				    (M2C_FIELD(temp_r31_2, s32*, 0x10) + (temp_r3_3 * 0x10)), u32*, 0xC);
			}
		}
	}
	if ((void*)arg0->unk258 == NULL) {
		temp_r31_3 = arg0->unkEC;
		if (temp_r31_3 != NULL) {
			temp_r3_4 = fn_8005D9A0(temp_r31_3, 0x3E9);
			if (temp_r3_4 != -1) {
				arg0->unk258 = M2C_FIELD(
				    (M2C_FIELD(temp_r31_3, s32*, 0x10) + (temp_r3_4 * 0x10)), void**, 0xC);
				temp_r4 = arg0->unk258;
				if (temp_r4 != NULL) {
					arg0->unk25C = M2C_FIELD(temp_r4, s32*, 0x10);
					arg0->unk260 = M2C_FIELD(temp_r4, s32*, 0x14);
					arg0->unk264 = M2C_FIELD(temp_r4, s32*, 0x18);
					arg0->unk268 = M2C_FIELD(temp_r4, s32*, 0x1C);
					arg0->unk26C = M2C_FIELD(temp_r4, s32*, 0x20);
					arg0->unk270 = M2C_FIELD(temp_r4, s32*, 0x24);
					arg0->unk274 = M2C_FIELD(temp_r4, s32*, 0x28);
					arg0->unk278 = M2C_FIELD(temp_r4, s32*, 0x2C);
					arg0->unk27C = M2C_FIELD(temp_r4, s32*, 0x30);
					arg0->unk280 = M2C_FIELD(temp_r4, s32*, 0x34);
					arg0->unk284 = M2C_FIELD(temp_r4, s32*, 0x38);
					arg0->unk288 = M2C_FIELD(temp_r4, s32*, 0x3C);
					arg0->unk28C = M2C_FIELD(temp_r4, s32*, 0x40);
					arg0->unk290 = M2C_FIELD(temp_r4, s32*, 0x44);
					arg0->unk294 = M2C_FIELD(temp_r4, s32*, 0x48);
					arg0->unk298 = M2C_FIELD(temp_r4, s32*, 0x4C);
				}
			}
		}
	}
	if ((u32)(M2C_FIELD(arg0->unkB0, s32*, 0x18) & 0x20000) != 0) {
		if ((s32)(arg0->unk106 & 2) != 0) {
			arg0->unk304 = arg0->unk118;
			arg0->unk30C = arg0->unk120;
			arg0->unk2FC = lbl_8_rodata_1ED0[0] + arg0->unk144;
		} else {
			temp_f1      = fn_800D8BC4((f32*)((u8*)arg0 + 0x140), &sp8, 1);
			arg0->unk2FC = temp_f1;
			if (temp_f1 != lbl_8_rodata_1EAC[0]) {
				arg0->unk2F8 = arg0->unk140;
				arg0->unk2FC += lbl_8_rodata_1ED0[0];
				arg0->unk300 = arg0->unk148;
				arg0->unk304 = lbl_8_rodata_1E7C[0] * (f32)sp8;
				arg0->unk30C = lbl_8_rodata_1E7C[0] * (f32)sp10;
			}
		}
		arg0->unk308 = lbl_8_rodata_1EC0[0] + (lbl_8_rodata_1E7C[0] * (f32)arg0->unk150);
		arg0->unk2F8 = arg0->unk140;
		arg0->unk300 = arg0->unk148;
	}
}

void fn_8_C19F4(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

void fn_8_C1A34(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	M2C_FIELD(arg0, void**, 0xE8) = fn_80150588(lbl_8_bss_1B78);
}

void fn_8_C1A88(void* arg0)
{
	u8 sp14[0x44];
	RwV3d sp8;
	f32 temp_f3;

	sp8.x   = lbl_8_rodata_1E70[0];
	sp8.y   = lbl_8_rodata_1E70[0];
	sp8.z   = M2C_FIELD(arg0, f32*, 0x2A0);
	temp_f3 = (lbl_8_rodata_1EC4[0] * (lbl_8_rodata_1EC8[0] * (f32)fn_801C28D8(&sp8.x)))
	    - lbl_8_rodata_1ECC[0];
	fn_80195A74((s32*)sp14, &lbl_80239984, 0,
	    lbl_8_rodata_1EC0[0]
	        + (lbl_8_rodata_1E7C[0] * (f32)M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x10))
	        + temp_f3,
	    lbl_8_rodata_1EC0[0], temp_f3);
	fn_80196050((s32*)sp14, M2C_FIELD(arg0, void**, 0xB0), 2);
	fn_8019941C(&sp8.x, &sp8.x, 1, (s32*)sp14);
	M2C_FIELD(arg0, f32*, 0x1CC) = sp8.x;
	M2C_FIELD(arg0, f32*, 0x1D0) = sp8.y;
	M2C_FIELD(arg0, f32*, 0x1D4) = sp8.z;
	M2C_FIELD(arg0, f32*, 0x2A0) = (f32)(M2C_FIELD(arg0, f32*, 0x2A0) * lbl_8_rodata_1EA4[0]);
}

void fn_8_C1BCC(TObject* arg0)
{
	u8 sp14[0x44];
	RwV3d sp8;
	f32 temp_f3;
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
	arg0->unk1D8 = lbl_8_rodata_1E70[0];
	arg0->unk1DC = lbl_8_rodata_1E70[0];
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
	arg0->unk1B8 = lbl_8_rodata_1ED4[0];
	arg0->unk2A0 = -arg0->unk210;
	sp8.x        = lbl_8_rodata_1E70[0];
	sp8.y        = lbl_8_rodata_1E70[0];
	sp8.z        = arg0->unk2A0;
	temp_f3      = (lbl_8_rodata_1EC4[0] * (lbl_8_rodata_1EC8[0] * (f32)fn_801C28D8(&sp8.x)))
	    - lbl_8_rodata_1ECC[0];
	fn_80195A74((s32*)sp14, &lbl_80239984, 0,
	    lbl_8_rodata_1EC0[0] + (lbl_8_rodata_1E7C[0] * (f32)M2C_FIELD(arg0->unkB0, s32*, 0x10))
	        + temp_f3,
	    lbl_8_rodata_1EC0[0], temp_f3);
	fn_80196050((s32*)sp14, arg0->unkB0, 2);
	fn_8019941C(&sp8.x, &sp8.x, 1, (s32*)sp14);
	arg0->unk1CC = sp8.x;
	arg0->unk1D0 = sp8.y;
	arg0->unk1D4 = sp8.z;
	arg0->unk2A0 *= lbl_8_rodata_1EA4[0];
	arg0->unk2A8 = arg0->unk1CC;
	arg0->unk2AC = arg0->unk1D0;
	arg0->unk2B0 = arg0->unk1D4;
	arg0->unk180 = 0x50;
	temp_r0      = arg0->unk310;
	switch (temp_r0) { /* irregular */
		case 0:
			arg0->unk2B8 = lbl_8_rodata_1ED8[0];
			arg0->unk2B4 = arg0->unk2B8;
			return;
		case 1:
			arg0->unk2B8 = lbl_8_rodata_1E6C[0];
			arg0->unk2B4 = arg0->unk2B8;
			return;
		default:
			arg0->unk2B8 = lbl_8_rodata_1ED8[0];
			arg0->unk2B4 = arg0->unk2B8;
			return;
	}
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

void* fn_8_C1ED8(void* arg0, s16 arg1)
{
	s32 temp_cr0_eq;
	void** temp_r3_2;
	void* temp_r3;

	if (arg0 != NULL) {
		M2C_FIELD(arg0, M2C_UNK**, 0x18) = (M2C_UNK*)lbl_8_data_17FA0;
		M2C_FIELD(arg0, void**, 0xB4)    = (void*)((M2C_UNK*)lbl_8_data_17FA0 + 0x2C);
		temp_r3                          = M2C_FIELD(arg0, void**, 0x244);
		if (temp_r3 != NULL) {
			M2C_FIELD(temp_r3, u16*, 4)    = (u16)(M2C_FIELD(temp_r3, u16*, 4) | 1);
			M2C_FIELD(arg0, void**, 0x244) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2C0) != 0U) {
			fn_8010AFE4();
			M2C_FIELD(arg0, u32*, 0x2C0) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2BC) != 0U) {
			fn_8010AFE4();
			M2C_FIELD(arg0, u32*, 0x2BC) = 0U;
		}
		temp_r3_2   = M2C_FIELD(arg0, void***, 0x240);
		temp_cr0_eq = temp_r3_2 == NULL;
		if (temp_cr0_eq == 0) {
			if (temp_cr0_eq == 0) {
				M2C_FIELD(*temp_r3_2, M2C_UNK(**)(M2C_UNK), 8)(1);
			}
			M2C_FIELD(arg0, void***, 0x240) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x250) != 0U) {
			dtor_800FE334(1);
			M2C_FIELD(arg0, u32*, 0x250) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0xE8) = 0U;
		}
		__dt__10HAnimClassFv((u8*)arg0 + 0x240, 0);
		fn_800A7088(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

#pragma dont_inline on
TObject* fn_8_C2018(TObject* arg0)
{
	RwV3d sp10;
	sParalysisParam sp8;
	TEnemyParalysis* temp_r3;
	TEnemyParalysis* var_r0_3;
	f32 temp_f0;
	void** var_r0;
	void** var_r0_2;
	void** var_r0_4;

	fn_800A714C();
	__ct__10HAnimClassFv((u8*)arg0 + 0x240);
	arg0->unk18  = (M2C_UNK*)lbl_8_data_17FA0;
	arg0->unkB4  = (M2C_UNK*)lbl_8_data_17FA0 + 0x2C;
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
	arg0->unk160 = lbl_8_rodata_1E70[0];
	arg0->unk15C = lbl_8_rodata_1E70[0];
	arg0->unk158 = lbl_8_rodata_1E70[0];
	arg0->unk188 &= 0xFFEFCFFF;
	arg0->unk188 |= 0x100000;
	arg0->unk188 |= 0x10;
	temp_f0      = arg0->unk2B4;
	arg0->unk1A4 = temp_f0;
	arg0->unk2E  = (s16)temp_f0;
	arg0->unk1A0 = lbl_8_rodata_1ED8[0];
	arg0->unk2C  = 3;
	if ((s32)arg0->unk310 == 0) {
		arg0->unk188 |= 0x10000;
	} else {
		arg0->unk188 |= 0x40000;
	}
	if ((void*)arg0->unkE8 != NULL) {
		fn_80150958();
		arg0->unkE8 = NULL;
	}
	arg0->unkE8 = fn_80150588(lbl_8_bss_1B78);
	var_r0      = fn_80057644(0x4C);
	if (var_r0 != NULL) {
		var_r0 = fn_800FE3FC();
	}
	arg0->unk250 = var_r0;
	fn_8005D5C8(arg0->unkE8, ((u32)(M2C_FIELD(arg0->unkB0, s32*, 0x18) & 0x1C0000) >> 0x12U) + 8);
	arg0->unkE4  = (M2C_UNK*)lbl_8_data_17CD8;
	arg0->unkD4  = 0;
	arg0->unk2E4 = 0;
	fn_800FE464((void**)&arg0->unkB8);
	fn_8_C14B4(arg0);
	if (fn_8005B8D8(&arg0->unkB0) == 0) {
		fn_8003C200(&arg0->unk28, (M2C_UNK*)lbl_8_data_17E34, 2, 3);
		arg0->unk88 = arg0->unk140;
		arg0->unk8C = arg0->unk144;
		arg0->unk90 = arg0->unk148;
	}
	arg0->unk130 = lbl_8_rodata_1EDC[0];
	arg0->unk134 = lbl_8_rodata_1EE0[0];
	var_r0_2     = fn_80057644(0x1C);
	if (var_r0_2 != NULL) {
		fn_8_BE528(var_r0_2);
	}
	arg0->unk240 = var_r0_2;
	if ((void**)arg0->unk240 != NULL) {
		fn_8_BDF6C((TObject*)arg0->unk240, arg0);
	}
	arg0->unk2BC = fn_8010B708(1);
	arg0->unk2C0 = fn_8010B708(0);
	__ct__15sParalysisParamFv(&sp8);
	sp10.z   = lbl_8_rodata_1EDC[0];
	sp10.y   = lbl_8_rodata_1EDC[0];
	sp10.x   = lbl_8_rodata_1EDC[0];
	temp_r3  = fn_80018A34(lbl_8042C148, 0x74);
	var_r0_3 = temp_r3;
	if (var_r0_3 != NULL) {
		var_r0_3 = __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(temp_r3, lbl_8042C10C, &sp8);
	}
	arg0->unk244 = var_r0_3;
	arg0->unk13C = 1;
	var_r0_4     = fn_80057644(0x20);
	if (var_r0_4 != NULL) {
		var_r0_4 = fn_800FD8A0(arg0, arg0->unk13C);
	}
	arg0->unk228 = var_r0_4;
	return arg0;
}
#pragma dont_inline reset

TEnemyParalysis* fn_8_C2344(void)
{
	TEnemyParalysis* var_r0;

	var_r0 = fn_80018A34(lbl_8042C148, 0x320);
	if (var_r0 != NULL) {
		var_r0 = (TEnemyParalysis*)fn_8_C2018((TObject*)var_r0);
	}
	return var_r0;
}

void fn_8_C2398(void* arg0, void* arg1)
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
	s8 temp_r0;
	s8 temp_r0_2;

	temp_r3 = M2C_FIELD(arg1, u8**, 0x2C);
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
	temp_f1                    = M2C_FIELD(temp_r3, f32*, 4);
	if (temp_f1 < lbl_8_rodata_1EE4[0]) {
		var_r4_3 = (f32*)lbl_8_rodata_1EE4;
	} else if (temp_f1 > lbl_8_rodata_1EE8[0]) {
		var_r4_3 = (f32*)lbl_8_rodata_1EE8;
	} else {
		var_r4_3 = (f32*)(temp_r3 + 4);
	}
	M2C_FIELD(temp_r3, f32*, 4) = (f32)*var_r4_3;
	temp_f1_2                   = M2C_FIELD(temp_r3, f32*, 8);
	if (temp_f1_2 < lbl_8_rodata_1EEC[0]) {
		var_r4_4 = (f32*)lbl_8_rodata_1EEC;
	} else if (temp_f1_2 > lbl_8_rodata_1EF0[0]) {
		var_r4_4 = (f32*)lbl_8_rodata_1EF0;
	} else {
		var_r4_4 = (f32*)(temp_r3 + 8);
	}
	M2C_FIELD(temp_r3, f32*, 8) = (f32)*var_r4_4;
	temp_r5                     = M2C_FIELD(temp_r3, s32*, 0x10);
	if (temp_r5 < (s32)lbl_8_rodata_1EF4[0]) {
		var_r4_5 = (s32*)(f32*)lbl_8_rodata_1EF4;
	} else if (temp_r5 > (s32)lbl_8_rodata_1EF8[0]) {
		var_r4_5 = (s32*)(f32*)lbl_8_rodata_1EF8;
	} else {
		var_r4_5 = (s32*)(temp_r3 + 0x10);
	}
	M2C_FIELD(temp_r3, s32*, 0x10) = (s32)*var_r4_5;
	temp_f1_3                      = M2C_FIELD(temp_r3, f32*, 0x14);
	if (temp_f1_3 < lbl_8_rodata_1EF4[0]) {
		var_r4_6 = (f32*)lbl_8_rodata_1EFC;
	} else if (temp_f1_3 > lbl_8_rodata_1EF0[0]) {
		var_r4_6 = (f32*)lbl_8_rodata_1F00;
	} else {
		var_r4_6 = (f32*)(temp_r3 + 0x14);
	}
	M2C_FIELD(temp_r3, f32*, 0x14) = (f32)*var_r4_6;
	M2C_FIELD((M2C_UNK*)turtleObjectFieldNames, M2C_UNK**, 0)
	    = (M2C_UNK*)lbl_8_data_17F5C[(s8)M2C_FIELD(temp_r3, s8*, 0)];
	M2C_FIELD((M2C_UNK*)turtleObjectFieldNames, M2C_UNK**, 4)
	    = (M2C_UNK*)lbl_8_data_17F74[(s8)M2C_FIELD(temp_r3, s8*, 1)];
}

void turtleObjectUnload(void)
{
	if ((void*)lbl_8_bss_1B9C != NULL) {
		M2C_FIELD(lbl_8_bss_1B9C, u16*, 4) = (u16)(M2C_FIELD(lbl_8_bss_1B9C, u16*, 4) | 1);
		lbl_8_bss_1B9C                     = NULL;
	}
	fn_80113A68(turtleObjectGlobalA);
	fn_800FE248(4, (M2C_UNK*)lbl_8_data_17DC8);
	fn_800FE248(4, (M2C_UNK*)lbl_8_data_17CD8);
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	fn_801007F4(lbl_8042C590, 4);
}

void turtleObjectLoad(void)
{
	u32 temp_r3;

	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	fn_8010096C(lbl_8042C590, 4, (M2C_UNK*)lbl_8_data_180F4);
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	temp_r3 = fn_80100328(lbl_8042C590, 4, 5);
	if (temp_r3 != 0U) {
		fn_8005E00C(6);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		lbl_8_bss_1B78 = fn_8010037C(lbl_8042C590, 4, 4);
		fn_800FE274(4, (M2C_UNK*)lbl_8_data_17CD8);
		fn_800FE274(4, (M2C_UNK*)lbl_8_data_17DC8);
		fn_80113AA8(turtleObjectGlobalA, temp_r3, lbl_8_bss_1B78, (M2C_UNK*)lbl_8_data_17EA4, 2);
		lbl_8_bss_1B9C = fn_80139984(0, 0x402D, 4);
	}
}

void turtleObjectCreate(void)
{
	TEnemyParalysis* object = fn_80018A34(lbl_8042C148, 0x320);
	if (object != NULL) {
		fn_8_C2018((TObject*)object);
	}
}

void turtleObjectRegister(void)
{
	s32 flags;

	fn_80113C7C(turtleObjectGlobalA);
	__register_global_object(&fn_80113C2C, turtleObjectGlobalAChain);
	M2C_FIELD(turtleObjectEntry, s32*, 0x14)       = 0;
	M2C_FIELD(turtleObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(turtleObjectEntry, M2C_UNK**, 0)     = (M2C_UNK*)turtleObjectDisplayName;
	M2C_FIELD(turtleObjectEntry, void (**)(), 4)   = turtleObjectLoad;
	M2C_FIELD(turtleObjectEntry, void (**)(), 8)   = turtleObjectUnload;
	M2C_FIELD(turtleObjectEntry, void (**)(), 0xC) = turtleObjectCreate;
	M2C_FIELD(turtleObjectEntry, s32*, 0x10)       = 0;
	flags                                          = 0x20000;
	M2C_FIELD(turtleObjectEntry, s32*, 0x14)       = flags;
	M2C_FIELD(turtleObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(turtleObjectEntry, s8*, 0x20)        = 0x1E;
	M2C_FIELD(turtleObjectEntry, s16*, 0x1C)       = 0x1570;
	M2C_FIELD(turtleObjectEntry, s16*, 0x1E)       = 4;
	M2C_FIELD(turtleObjectEntry, s8*, 0x21)        = 0;
	M2C_FIELD(turtleObjectEntry, M2C_UNK**, 0x24)  = (M2C_UNK*)turtleObjectFieldTypes;
	M2C_FIELD(turtleObjectEntry, M2C_UNK**, 0x28)  = (M2C_UNK*)turtleObjectFieldNames;
	if ((M2C_UNK*)turtleObjectFieldTypes != NULL) {
		M2C_FIELD(turtleObjectEntry, s32*, 0x14) = flags | 8;
		return;
	}
	M2C_FIELD(turtleObjectEntry, s32*, 0x14) = flags & ~8;
}

__declspec(section ".ctors") void (*const turtleObjectCtorEntry)(void) = turtleObjectRegister;
}
