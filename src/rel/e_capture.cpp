#include "types.h"

typedef s32 M2C_UNK;
extern double fabs(double);
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_BITWISE(type, value)      (*(type*)&(value))
#define M2C_ERROR(...)

typedef struct HAnimClass HAnimClass;
typedef struct RwFrame RwFrame;
typedef struct RwV3d RwV3d;
typedef struct TEnemyParalysis TEnemyParalysis;
typedef struct sAngle sAngle;
typedef struct sParalysisParam sParalysisParam;
typedef s32 RwOpCombineType;

typedef struct TObject {
	/* 0x000 */ M2C_UNK* unk0;   /* inferred */
	/* 0x004 */ char pad4[0x14]; /* maybe part of unk0[6]? */
	/* 0x018 */ M2C_UNK* unk18;  /* inferred */
	/* 0x01C */ char pad1C[2];
	/* 0x01E */ s16 unk1E;     /* inferred */
	/* 0x020 */ char pad20[8]; /* maybe part of unk1E[5]? */
	/* 0x028 */ M2C_UNK unk28; /* inferred */
	/* 0x028 */ char pad28[4];
	/* 0x02C */ s16 unk2C;        /* inferred */
	/* 0x02E */ s16 unk2E;        /* inferred */
	/* 0x030 */ char pad30[8];    /* maybe part of unk2E[5]? */
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
	/* 0x0B0 */ void* unkB0;       /* inferred */
	/* 0x0B4 */ void* unkB4;       /* inferred */
	/* 0x0B8 */ char padB8[0x1C];  /* maybe part of unkB4[8]? */
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
	/* 0x24C */ f32 unk24C;              /* inferred */
	/* 0x250 */ f32 unk250;              /* inferred */
	/* 0x254 */ f32 unk254;              /* inferred */
	/* 0x258 */ f32 unk258;              /* inferred */
	/* 0x25C */ f32 unk25C;              /* inferred */
	/* 0x260 */ f32 unk260;              /* inferred */
	/* 0x264 */ char pad264[4];
	/* 0x268 */ u32 unk268; /* inferred */
	/* 0x26C */ u32 unk26C; /* inferred */
	/* 0x270 */ u32 unk270; /* inferred */
	/* 0x274 */ s32 unk274; /* inferred */
	/* 0x278 */ s32 unk278; /* inferred */
	/* 0x27C */ f32 unk27C; /* inferred */
	/* 0x280 */ s32 unk280; /* inferred */
	/* 0x284 */ s32 unk284; /* inferred */
	/* 0x288 */ f32 unk288; /* inferred */
	/* 0x28C */ s32 unk28C; /* inferred */
	/* 0x290 */ char pad290[4];
	/* 0x294 */ f32 unk294;         /* inferred */
	/* 0x298 */ f32 unk298;         /* inferred */
	/* 0x29C */ char pad29C[0x18];  /* maybe part of unk298[7]? */
	/* 0x2B4 */ s32 unk2B4;         /* inferred */
	/* 0x2B8 */ char pad2B8[0x1C];  /* maybe part of unk2B4[8]? */
	/* 0x2D4 */ s32 unk2D4;         /* inferred */
	/* 0x2D8 */ void* unk2D8;       /* inferred */
	/* 0x2DC */ void* unk2DC;       /* inferred */
	/* 0x2E0 */ void* unk2E0;       /* inferred */
	/* 0x2E4 */ void* unk2E4;       /* inferred */
	/* 0x2E8 */ void* unk2E8;       /* inferred */
	/* 0x2EC */ u32 unk2EC;         /* inferred */
	/* 0x2F0 */ u32 unk2F0;         /* inferred */
	/* 0x2F4 */ u32 unk2F4;         /* inferred */
	/* 0x2F8 */ f32 unk2F8;         /* inferred */
	/* 0x2FC */ f32 unk2FC;         /* inferred */
	/* 0x300 */ f32 unk300;         /* inferred */
	/* 0x304 */ f32 unk304;         /* inferred */
	/* 0x308 */ f32 unk308;         /* inferred */
	/* 0x30C */ f32 unk30C;         /* inferred */
	/* 0x310 */ f32 unk310;         /* inferred */
	/* 0x314 */ f32 unk314;         /* inferred */
	/* 0x318 */ f32 unk318;         /* inferred */
	/* 0x31C */ f32 unk31C;         /* inferred */
	/* 0x320 */ f32 unk320;         /* inferred */
	/* 0x324 */ f32 unk324;         /* inferred */
	/* 0x328 */ s32 unk328;         /* inferred */
	/* 0x32C */ s32 unk32C;         /* inferred */
	/* 0x330 */ f32 unk330;         /* inferred */
	/* 0x334 */ f32 unk334;         /* inferred */
	/* 0x338 */ f32 unk338;         /* inferred */
	/* 0x33C */ f32 unk33C;         /* inferred */
	/* 0x340 */ f32 unk340;         /* inferred */
	/* 0x344 */ f32 unk344;         /* inferred */
	/* 0x348 */ f32 unk348;         /* inferred */
	/* 0x34C */ f32 unk34C;         /* inferred */
	/* 0x350 */ f32 unk350;         /* inferred */
	/* 0x354 */ f32 unk354;         /* inferred */
	/* 0x358 */ f32 unk358;         /* inferred */
	/* 0x35C */ f32 unk35C;         /* inferred */
	/* 0x360 */ f32 unk360;         /* inferred */
	/* 0x364 */ f32 unk364;         /* inferred */
	/* 0x368 */ f32 unk368;         /* inferred */
	/* 0x36C */ f32 unk36C;         /* inferred */
	/* 0x370 */ f32 unk370;         /* inferred */
	/* 0x374 */ f32 unk374;         /* inferred */
	/* 0x378 */ f32 unk378;         /* inferred */
	/* 0x37C */ f32 unk37C;         /* inferred */
	/* 0x380 */ f32 unk380;         /* inferred */
	/* 0x384 */ f32 unk384;         /* inferred */
	/* 0x388 */ f32 unk388;         /* inferred */
	/* 0x38C */ f32 unk38C;         /* inferred */
	/* 0x390 */ f32 unk390;         /* inferred */
	/* 0x394 */ f32 unk394;         /* inferred */
	/* 0x398 */ f32 unk398;         /* inferred */
	/* 0x39C */ f32 unk39C;         /* inferred */
	/* 0x3A0 */ f32 unk3A0;         /* inferred */
	/* 0x3A4 */ f32 unk3A4;         /* inferred */
	/* 0x3A8 */ f32 unk3A8;         /* inferred */
	/* 0x3AC */ f32 unk3AC;         /* inferred */
	/* 0x3B0 */ f32 unk3B0;         /* inferred */
	/* 0x3B4 */ f32 unk3B4;         /* inferred */
	/* 0x3B8 */ f32 unk3B8;         /* inferred */
	/* 0x3BC */ f32 unk3BC;         /* inferred */
	/* 0x3C0 */ char pad3C0[0x1B0]; /* maybe part of unk3BC[0x6D]? */
	/* 0x570 */ s32 unk570;         /* inferred */
	/* 0x574 */ s32 unk574;         /* inferred */
	/* 0x578 */ s32 unk578;         /* inferred */
	/* 0x57C */ s32 unk57C;         /* inferred */
	/* 0x580 */ s32 unk580;         /* inferred */
	/* 0x584 */ s32 unk584;         /* inferred */
	/* 0x588 */ f32 unk588;         /* inferred */
} TObject;                          /* size >= 0x58C */

M2C_UNK SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(
    TEnemyParalysis* self, RwV3d* arg0, sAngle* arg1); /* extern */
M2C_UNK Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(
    TEnemyParalysis* self, RwFrame* arg0, RwOpCombineType arg1);           /* extern */
M2C_UNK __construct_array(M2C_UNK*, M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK); /* extern */
void* __ct__10HAnimClassFv(HAnimClass* self);                              /* extern */
TEnemyParalysis* __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(
    TEnemyParalysis* self, TObject* arg0, sParalysisParam* arg1); /* extern */
M2C_UNK __destroy_arr(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);      /* extern */
void* __dt__10HAnimClassFv(HAnimClass* self, s16 destroyFlag);    /* extern */
M2C_UNK __register_global_object(M2C_UNK, void (*)(), M2C_UNK*);  /* extern */
s32 fn_80017800(TObject*);                                        /* extern */
M2C_UNK fn_800189A4(s32, void*);                                  /* extern */
TEnemyParalysis* fn_80018A34(s32, M2C_UNK);                       /* extern */
M2C_UNK fn_8003BC38(M2C_UNK*);                                    /* extern */
M2C_UNK fn_8003C200(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK fn_80043DEC();                                            /* extern */
M2C_UNK fn_80043F28(u32);                                         /* extern */
void** fn_80057644(M2C_UNK);                                      /* extern */
s32 fn_8005B8D8(void**);                                          /* extern */
M2C_UNK fn_8005BC04(void*);                                       /* extern */
M2C_UNK fn_8005D5C8(void*, s32);                                  /* extern */
s32 fn_8005D9A0(void*, M2C_UNK);                                  /* extern */
M2C_UNK fn_8005D9F4(u32, ...);                                    /* extern */
M2C_UNK fn_8005DA34();                                            /* extern */
M2C_UNK fn_8005DABC(u32, s32*);                                   /* extern */
M2C_UNK fn_8005E00C(M2C_UNK);                                     /* extern */
s32 fn_80089204(u32);                                             /* extern */
s32 fn_800A34D0(void*, s32*, f32);                                /* extern */
M2C_UNK fn_800A3D48(TObject*);                                    /* extern */
M2C_UNK fn_800A3D94(TObject*);                                    /* extern */
M2C_UNK fn_800A4668(void*);                                       /* extern */
M2C_UNK fn_800A4A8C(void*, f32);                                  /* extern */
s32 fn_800A5844(s32);                                             /* extern */
s32 fn_800A5888(void*, f32*, f32);                                /* extern */
s32 fn_800A5A54(...);                                             /* extern */
f32 fn_800A5AC0(...);                                             /* extern */
M2C_UNK fn_800A5B34(TObject*);                                    /* extern */
M2C_UNK fn_800A5B50(void*, M2C_UNK);                              /* extern */
M2C_UNK fn_800A5C6C(void*, M2C_UNK);                              /* extern */
s32 fn_800A6334();                                                /* extern */
M2C_UNK fn_800A7088(void*, M2C_UNK);                              /* extern */
M2C_UNK fn_800A714C();                                            /* extern */
s32 fn_800AB104(s32);                                             /* extern */
s32 fn_800AB25C();                                                /* extern */
s32 fn_800AB2E0(u32);                                             /* extern */
M2C_UNK fn_800B4A38(M2C_UNK, void*, ...);                         /* extern */
M2C_UNK fn_800B7514(void*, void*, f32*, f32);                     /* extern */
M2C_UNK fn_800B7820();                                            /* extern */
M2C_UNK fn_800B7864(M2C_UNK);                                     /* extern */
s32 fn_800D5A64(void*, void*, ...);                               /* extern */
s32 fn_800D7A94(s32, s32, s32);                                   /* extern */
f32 fn_800D7B00(s32, ...);                                        /* extern */
f32 fn_800D8BC4(void*, s32*, M2C_UNK);                            /* extern */
M2C_UNK fn_800E1208(s32, ...);                                    /* extern */
void** fn_800FD8A0(TObject*, s32);                                /* extern */
M2C_UNK fn_800FE248(M2C_UNK, M2C_UNK*);                           /* extern */
M2C_UNK fn_800FE274(M2C_UNK, M2C_UNK*);                           /* extern */
u32 fn_80100328(u32, M2C_UNK, M2C_UNK);                           /* extern */
u32 fn_8010037C(u32, M2C_UNK, M2C_UNK);                           /* extern */
M2C_UNK fn_801007F4(u32, M2C_UNK);                                /* extern */
M2C_UNK fn_8010096C(u32, M2C_UNK, const char*);                   /* extern */
M2C_UNK fn_80100AAC();                                            /* extern */
s32 fn_801031D8();                                                /* extern */
s32 fn_80103284(f32*, f32*, f32);                                 /* extern */
s32 fn_80103324(void*, f32*, f32);                                /* extern */
s32 fn_8010AFB0();                                                /* extern */
M2C_UNK fn_8010AFE4();                                            /* extern */
M2C_UNK fn_8010AFF8(M2C_UNK*, ...);                               /* extern */
M2C_UNK fn_8010B074();                                            /* extern */
M2C_UNK fn_8010B0AC(M2C_UNK, f32);                                /* extern */
M2C_UNK fn_8010B208(void*, ...);                                  /* extern */
M2C_UNK fn_8010B350(void*, M2C_UNK*);                             /* extern */
u32 fn_8010B708(M2C_UNK);                                         /* extern */
M2C_UNK fn_80113874(...);                                         /* extern */
M2C_UNK fn_801138B4();                                            /* extern */
M2C_UNK fn_801138F4();                                            /* extern */
M2C_UNK fn_80113940();                                            /* extern */
M2C_UNK fn_8011398C(M2C_UNK*, s32);                               /* extern */
M2C_UNK fn_80113A68(void*);                                       /* extern */
M2C_UNK fn_80113AA8(M2C_UNK*, u32, u32, M2C_UNK*, M2C_UNK);       /* extern */
u32 fn_8011B5A8(RwFrame*, M2C_UNK);                               /* extern */
M2C_UNK fn_8011C188(u32, s32);                                    /* extern */
M2C_UNK fn_8011C1F8(u32, s32, M2C_UNK);                           /* extern */
M2C_UNK fn_8011C6EC();                                            /* extern */
M2C_UNK fn_8014FF2C(...);                                         /* extern */
void* fn_80150588(s32);                                           /* extern */
M2C_UNK fn_80150958();                                            /* extern */
M2C_UNK fn_80195A74(M2C_UNK*, M2C_UNK*, M2C_UNK, f32, f32, f32);  /* extern */
M2C_UNK fn_80196050(M2C_UNK*, void*, M2C_UNK);                    /* extern */
M2C_UNK fn_8019941C(f32*, f32*, M2C_UNK, M2C_UNK*);               /* extern */
void* fn_8019E8EC(...);                                           /* extern */
M2C_UNK fn_8019EB94(RwFrame*, void*, M2C_UNK);                    /* extern */
M2C_UNK fn_8019EC30(RwFrame*, f32*, M2C_UNK);                     /* extern */
M2C_UNK fn_8019ECCC(RwFrame*, void*, M2C_UNK);                    /* extern */
M2C_UNK fn_8019ED68(RwFrame*, M2C_UNK*, ...);                     /* extern */
s32 fn_801C28D8(void*, ...);                                      /* extern */
M2C_UNK fn_8_90B10(s32);                                          /* extern */
void** fn_8_9DCE8();                                              /* extern */
M2C_UNK fn_8_9E43C(TObject*);                                     /* extern */
void** fn_8_9EB28();                                              /* extern */
void captureObjectGlobalArrayDtor();                              /* static */
void fn_8_9B920(TObject* arg0);                                   /* static */
void fn_8_9C054(TObject* arg0);                                   /* static */
extern M2C_UNK fn_80113C2C;
extern M2C_UNK fn_80113C7C;
extern M2C_UNK fn_8_9D45C;
extern M2C_UNK lbl_80239978;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_802AD070;
extern M2C_UNK lbl_802AD090;
extern M2C_UNK lbl_802AD0D0;
extern M2C_UNK lbl_80303DC8;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern s32 lbl_8042C298;
extern u32 lbl_8042C388;
extern u32 lbl_8042C590;
extern u32 lbl_8042C6D0;
extern f32 lbl_8_rodata_1704;
extern f32 lbl_8_rodata_16B0;
extern f32 lbl_8_rodata_1708;
extern f32 lbl_8_rodata_170C;
extern f32 lbl_8_rodata_1710;
extern f32 lbl_8_rodata_1714;
extern f32 lbl_8_rodata_1718;
extern f32 lbl_8_rodata_171C;
extern f32 lbl_8_rodata_1720;
extern f32 lbl_8_rodata_1724;
extern f32 lbl_8_rodata_1728;
extern f32 lbl_8_rodata_172C;
extern f32 lbl_8_rodata_1730;
extern f32 lbl_8_rodata_1734;
extern f32 lbl_8_rodata_1738;
extern f32 lbl_8_rodata_173C;
extern f32 lbl_8_rodata_1740;
extern f32 lbl_8_rodata_1744;
extern f32 lbl_8_rodata_1748;
extern f32 lbl_8_rodata_174C;
extern f32 lbl_8_rodata_1750;
extern f32 lbl_8_rodata_1754;
extern f32 lbl_8_rodata_1758;
extern f32 lbl_8_rodata_1760;
extern f32 lbl_8_rodata_1764;
extern f32 lbl_8_rodata_1768;
extern f32 lbl_8_rodata_176C;
extern f32 lbl_8_rodata_1770;
extern f32 lbl_8_rodata_1774;
extern f32 lbl_8_rodata_1778;
extern f32 lbl_8_rodata_177C;
extern f32 lbl_8_rodata_1780;
extern f32 lbl_8_rodata_1784;
extern f32 lbl_8_rodata_1788;
extern f32 lbl_8_rodata_178C;
extern f32 lbl_8_rodata_1790;
extern f32 lbl_8_rodata_1794;
extern f32 lbl_8_rodata_1798;
extern f32 lbl_8_rodata_17A4;
static M2C_UNK lbl_8_data_15608;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_156BC;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1572C;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1575C;        /* unable to generate initializer: unknown type */
static M2C_UNK captureObjectFieldNames; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15808;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15810;        /* unable to generate initializer: unknown type */
static const char* lbl_8_data_15818[2] = { "NORMAL", "SPECIAL" };
static M2C_UNK lbl_8_data_15820; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15828; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_15830[2] = { "WAIT", "WALK" };
static u8 lbl_8_data_15838             = 0;
static u8 lbl_8_data_15839             = 1;
static u8 lbl_8_data_1583A             = 0;
static u8 lbl_8_data_1583B             = 1;
static M2C_UNK lbl_8_data_1583C; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_15850 = "TObjEnemyCapture";
static M2C_UNK lbl_8_data_15854;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_159BC;         /* unable to generate initializer: unknown type */
static M2C_UNK captureObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK captureObjectFieldTypes;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_bss_1780;
static M2C_UNK captureObjectGlobalArrayChain;
static M2C_UNK captureObjectGlobalArray;
static M2C_UNK captureObjectEntry;
static M2C_UNK lbl_8_rodata_16A4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_16BC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_16CC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_16D8; /* unable to generate initializer: unknown type; const */
static s32 lbl_8_rodata_16E4[8] = { 0, 1, 2, 3, 4, 5, 6, -1 };          /* const */
static s32 lbl_8_rodata_179C    = 0;                                    /* const */
static s32 lbl_8_rodata_17A0    = 0x2710;                               /* const */
static f32 lbl_8_rodata_17A8[5] = { 10000.0f, 0.0f, 0.0f, 1.5f, 0.0f }; /* const */

void fn_8_98060(void* arg0)
{
	s16 var_r0;
	s32 temp_r3;
	void* temp_r3_2;

	if ((s32)M2C_FIELD(arg0, s32*, 0x278) != -1) {
		temp_r3 = fn_801031D8();
		if (temp_r3 != -1) {
			temp_r3_2 = *(void**)((u8*)&lbl_80303DC8 + (temp_r3 * 4));
			if (temp_r3_2 != NULL) {
				if ((s32)M2C_FIELD(temp_r3_2, s32*, 0x154) != 9) {
					var_r0 = -1;
				} else {
					var_r0 = M2C_FIELD(temp_r3_2, s16*, 0x14E);
				}
				if ((var_r0 != -1) && ((s32)M2C_FIELD(arg0, s32*, 0x278) != -1)) {
					fn_800E1208(0xF, 0);
					M2C_FIELD(arg0, s32*, 0x278) = -1;
				}
			}
		}
	}
}

void fn_8_980F8(s32 arg1)
{
	fn_8_90B10(arg1);
}

void fn_8_9811C(void* arg0, void* arg1)
{
	f32 temp_f0;
	f32 var_f1;

	var_f1  = M2C_FIELD(arg1, f32*, 0x14) + M2C_FIELD(arg0, f32*, 0x1A4);
	temp_f0 = M2C_FIELD(arg0, f32*, 0x250);
	if (var_f1 > temp_f0) {
		var_f1 = temp_f0;
	}
	M2C_FIELD(arg0, f32*, 0x1A4) = var_f1;
	M2C_FIELD(arg0, s16*, 0x2E)  = (s16)var_f1;
	M2C_FIELD(arg0, f32*, 0x24C) = (f32)M2C_FIELD(arg0, f32*, 0x1A4);
	if ((u32)M2C_FIELD(arg0, u32*, 0x2F0) != 0U) {
		fn_8010B074();
	}
	if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x2F4) != NULL) {
		fn_8010AFF8((M2C_UNK*)6U);
		fn_8010B208(M2C_FIELD(arg0, M2C_UNK**, 0x2F4), &lbl_8_rodata_1704, 0.0f, 0.0f);
	}
}

void fn_8_981B8(void* arg0, void* arg1)
{
	f32 temp_f1;
	f32 var_f0;
	u8 temp_r0;

	temp_r0 = M2C_FIELD(arg1, u8*, 0);
	switch ((s32)temp_r0) { /* irregular */
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x19C) == 1) {
				M2C_FIELD(arg0, s32*, 0x248) = 2;
				return;
			}
		case 2:
			return;
		case 3:
			var_f0  = M2C_FIELD(arg1, f32*, 0x14) + M2C_FIELD(arg0, f32*, 0x1A4);
			temp_f1 = M2C_FIELD(arg0, f32*, 0x250);
			if (var_f0 > temp_f1) {
				var_f0 = temp_f1;
			}
			M2C_FIELD(arg0, f32*, 0x1A4) = var_f0;
			M2C_FIELD(arg0, s16*, 0x2E)  = (s16)var_f0;
			M2C_FIELD(arg0, f32*, 0x24C) = (f32)M2C_FIELD(arg0, f32*, 0x1A4);
			if ((u32)M2C_FIELD(arg0, u32*, 0x2F0) != 0U) {
				fn_8010B074();
			}
			if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x2F4) != NULL) {
				fn_8010AFF8((M2C_UNK*)6U);
				fn_8010B208(M2C_FIELD(arg0, M2C_UNK**, 0x2F4), &lbl_8_rodata_1704, 0.0f, 0.0f);
			}
			break;
	}
}

void fn_8_98294(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x57C) == 0) {
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
}

s32 fn_8_9832C(void* arg0)
{
	s32* temp_r4;
	s32 var_r0;
	void* var_r5;

	var_r5 = M2C_FIELD(
	    (lbl_8042C298 + (M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A) * 4)), void**, 0x30);
	if (var_r5 == NULL) {
		var_r0 = 0;
	} else {
	loop_8:
		if (var_r5 == NULL) {
			var_r0 = 0;
		} else if (((u16)M2C_FIELD(var_r5, u16*, 0x28) == 0x65)
		    && (temp_r4 = M2C_FIELD(var_r5, s32**, 0x2C), ((temp_r4 == NULL) == 0))
		    && ((s32)*temp_r4 == (s32)M2C_FIELD(arg0, s32*, 0x2B4))) {
			M2C_FIELD(arg0, f32*, 0x2A8) = (f32)M2C_FIELD(var_r5, f32*, 0);
			M2C_FIELD(arg0, f32*, 0x2AC) = (f32)M2C_FIELD(var_r5, f32*, 4);
			M2C_FIELD(arg0, f32*, 0x2B0) = (f32)M2C_FIELD(var_r5, f32*, 8);
			var_r0                       = 1;
		} else {
			var_r5 = M2C_FIELD(var_r5, void**, 0x38);
			goto loop_8;
		}
	}
	M2C_FIELD(arg0, f32*, 0x2AC) = (f32)(M2C_FIELD(arg0, f32*, 0x2AC) + 40.0f);
	return var_r0;
}

s32 fn_8_983D8(void* arg1, s32 arg2, u8 arg3)
{
	s32* temp_r6;
	void* temp_r0;
	void* var_r3;

	temp_r0 = M2C_FIELD((lbl_8042C298 + (arg3 * 4)), void**, 0x30);
	var_r3  = temp_r0;
	if (temp_r0 == NULL) {
		return 0;
	}
loop_8:
	if (var_r3 == NULL) {
		return 0;
	}
	if ((u16)M2C_FIELD(var_r3, u16*, 0x28) == 0x65) {
		temp_r6 = M2C_FIELD(var_r3, s32**, 0x2C);
		if ((temp_r6 != NULL) && ((s32)*temp_r6 == arg2)) {
			M2C_FIELD(arg1, f32*, 0) = (f32)M2C_FIELD(var_r3, f32*, 0);
			M2C_FIELD(arg1, f32*, 4) = (f32)M2C_FIELD(var_r3, f32*, 4);
			M2C_FIELD(arg1, f32*, 8) = (f32)M2C_FIELD(var_r3, f32*, 8);
			return 1;
		}
	}
	var_r3 = M2C_FIELD(var_r3, void**, 0x38);
	goto loop_8;
}

s32 fn_8_98464(void* arg0)
{
	return M2C_FIELD(arg0, f32*, 0x250) != M2C_FIELD(arg0, f32*, 0x1A4);
}

s32 fn_8_98480(void* arg0)
{
	f32 temp_f1;
	s32 var_r31;

	var_r31 = 0;
	temp_f1 = M2C_FIELD(arg0, f32*, 0x1A4);
	if (temp_f1 != M2C_FIELD(arg0, f32*, 0x24C)) {
		M2C_FIELD(arg0, f32*, 0x24C) = temp_f1;
		if ((u32)M2C_FIELD(arg0, u32*, 0x2F0) != 0U) {
			if ((s32)M2C_FIELD(arg0, s32*, 0x19C) == 0x24) {
				fn_8010B0AC(0x5A, M2C_FIELD(arg0, f32*, 0x250));
			} else {
				fn_8010B208(M2C_BITWISE(M2C_UNK*, M2C_FIELD(arg0, f32*, 0x250)));
			}
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2F4) != 0U) {
			fn_8010B074();
		}
		var_r31 = 1;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2F0) != 0U) {
		fn_8010B350((u8*)arg0 + 0x140, &lbl_8_rodata_16A4);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2F4) != 0U) {
		fn_8010B350((u8*)arg0 + 0x140, &lbl_8_rodata_16A4);
	}
	return var_r31;
}

void fn_8_98548(void* arg0)
{
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r3_2;
	s32 var_r5;
	s32 var_r7;
	void* temp_r3;
	void* temp_r4;
	void* temp_r4_2;
	u8* var_r4;
	u8* var_r5_2;

	if ((s32)M2C_FIELD(arg0, s32*, 0x574) != 0) {
		temp_r0                      = M2C_FIELD(arg0, s32*, 0x328) - 1;
		M2C_FIELD(arg0, s32*, 0x328) = temp_r0;
		if (temp_r0 < 0) {
			M2C_FIELD(arg0, s32*, 0x328) = 0xA;
			temp_r0_2                    = M2C_FIELD(arg0, s32*, 0x32C);
			if (temp_r0_2 < 0x10) {
				temp_r4                        = (u8*)arg0 + ((temp_r0_2 * 0x24) + 0x330);
				M2C_FIELD(temp_r4, f32*, 8)    = 0.0f;
				M2C_FIELD(temp_r4, f32*, 4)    = 0.0f;
				M2C_FIELD(temp_r4, f32*, 0)    = 0.0f;
				M2C_FIELD(temp_r4, f32*, 0x14) = 0.0f;
				M2C_FIELD(temp_r4, f32*, 0xC)  = 0.0f;
				M2C_FIELD(temp_r4, f32*, 0x10) = -0.4f;
				M2C_FIELD(temp_r4, f32*, 0x18) = 0.0f;
				M2C_FIELD(temp_r4, f32*, 0x1C) = 0.2f;
				M2C_FIELD(temp_r4, f32*, 0x20) = 0.0f;
				temp_r3 = (u8*)arg0 + ((M2C_FIELD(arg0, s32*, 0x32C) * 0x24) + 0x330);
				M2C_FIELD(temp_r3, f32*, 0) = (f32)M2C_FIELD(arg0, f32*, 0x140);
				M2C_FIELD(temp_r3, f32*, 4) = (f32)M2C_FIELD(arg0, f32*, 0x144);
				M2C_FIELD(temp_r3, f32*, 8) = (f32)M2C_FIELD(arg0, f32*, 0x148);
				M2C_FIELD(((u8*)arg0 + (M2C_FIELD(arg0, s32*, 0x32C) * 0x24)), f32*, 0x350)
				    = (f32)(M2C_FIELD(arg0, f32*, 0x144) - 40.0f);
				M2C_FIELD(arg0, s32*, 0x32C) = (s32)(M2C_FIELD(arg0, s32*, 0x32C) + 1);
			}
		}
		var_r5 = 0;
		var_r4 = (u8*)arg0;
	loop_8:
		if (var_r5 < (s32)M2C_FIELD(arg0, s32*, 0x32C)) {
			M2C_FIELD(var_r4, f32*, 0x330) = (f32)M2C_FIELD(arg0, f32*, 0x140);
			M2C_FIELD(var_r4, f32*, 0x338) = (f32)M2C_FIELD(arg0, f32*, 0x148);
			M2C_FIELD(var_r4, f32*, 0x330)
			    = (f32)(M2C_FIELD(var_r4, f32*, 0x330) + M2C_FIELD(var_r4, f32*, 0x33C));
			M2C_FIELD(var_r4, f32*, 0x334)
			    = (f32)(M2C_FIELD(var_r4, f32*, 0x334) + M2C_FIELD(var_r4, f32*, 0x340));
			M2C_FIELD(var_r4, f32*, 0x338)
			    = (f32)(M2C_FIELD(var_r4, f32*, 0x338) + M2C_FIELD(var_r4, f32*, 0x344));
			M2C_FIELD(var_r4, f32*, 0x348)
			    = (f32)(M2C_FIELD(var_r4, f32*, 0x348) + M2C_FIELD(var_r4, f32*, 0x34C));
			if (M2C_FIELD(var_r4, f32*, 0x348) > 3.0f) {
				M2C_FIELD(var_r4, f32*, 0x348) = 3.0f;
			}
			var_r4 += 0x24;
			var_r5 += 1;
			goto loop_8;
		}
		var_r7   = 0;
		var_r5_2 = (u8*)arg0;
	loop_13:
		temp_r3_2 = M2C_FIELD(arg0, s32*, 0x32C);
		if (var_r7 < temp_r3_2) {
			M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
			if (M2C_FIELD(var_r5_2, f32*, 0x334) == M2C_FIELD(var_r5_2, f32*, 0x350)) {
				var_r5_2 += 0x24;
				var_r7 += 1;
			} else {
				temp_r4_2                        = (u8*)arg0 + (((temp_r3_2 - 1) * 0x24) + 0x330);
				M2C_FIELD(var_r5_2, s32*, 0x330) = (s32)M2C_FIELD(temp_r4_2, s32*, 0);
				M2C_FIELD(var_r5_2, f32*, 0x334) = (f32)M2C_FIELD(temp_r4_2, f32*, 4);
				M2C_FIELD(var_r5_2, s32*, 0x338) = (s32)M2C_FIELD(temp_r4_2, s32*, 8);
				M2C_FIELD(var_r5_2, s32*, 0x33C) = (s32)M2C_FIELD(temp_r4_2, s32*, 0xC);
				M2C_FIELD(var_r5_2, s32*, 0x340) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x10);
				M2C_FIELD(var_r5_2, s32*, 0x344) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x14);
				M2C_FIELD(var_r5_2, f32*, 0x348) = (f32)M2C_FIELD(temp_r4_2, f32*, 0x18);
				M2C_FIELD(var_r5_2, f32*, 0x34C) = (f32)M2C_FIELD(temp_r4_2, f32*, 0x1C);
				M2C_FIELD(var_r5_2, f32*, 0x350) = (f32)M2C_FIELD(temp_r4_2, f32*, 0x20);
				M2C_FIELD(arg0, s32*, 0x32C)     = (s32)(M2C_FIELD(arg0, s32*, 0x32C) - 1);
			}
			goto loop_13;
		}
		if ((u32)lbl_8042C388 != 0U) {
			fn_800B4A38(0x4012, (u8*)arg0 + 0x140, 3, 0, 2);
		}
	}
}

s32 fn_8_987A8(void* arg0)
{
	s32 sp10;
	f32 spC;
	f32 sp8;
	s32 temp_r0;
	s32 temp_r0_2;
	u32 temp_r30;

	if ((s32)M2C_FIELD(arg0, s32*, 0x278) != -1) {
		return 0;
	}
	temp_r0 = M2C_FIELD(arg0, s32*, 0x19C);
	if (temp_r0 != 9) {
		if (temp_r0 < 9) {
			if (temp_r0 != 6) {
				if (temp_r0 < 6) {
					if (temp_r0 != 2) {
						goto block_9;
					}
					goto block_10;
				}
				goto block_9;
			}
			goto block_10;
		}
		if (temp_r0 != 0x2C) {
		block_9:
			return 0;
		}
		goto block_10;
	}
block_10:
	sp8  = M2C_FIELD(arg0, f32*, 0x140);
	spC  = M2C_FIELD(arg0, f32*, 0x144);
	sp10 = M2C_FIELD(arg0, s32*, 0x148);
	spC -= 40.0f;
	M2C_FIELD(arg0, s32*, 0x274) = fn_80103284(&sp8, &lbl_8_rodata_1718, 20.0f);
	if (((s32)M2C_FIELD(arg0, s32*, 0x274) != -1) && (fn_800AB25C() == 1)) {
		temp_r0_2 = M2C_FIELD(arg0, s32*, 0x274);
		if (temp_r0_2 != -1) {
			temp_r30 = *(u32*)((u8*)&lbl_802AD070 + (temp_r0_2 * 4));
			if ((temp_r30 != 0U) && (fn_800AB2E0(temp_r30) != 0)) {
				if (fn_80089204(temp_r30) != 0) {
					M2C_FIELD(arg0, s32*, 0x570) = 1;
				} else {
					M2C_FIELD(arg0, s32*, 0x570) = 2;
					fn_80043F28(temp_r30);
				}
				fn_800E1208(M2C_FIELD(arg0, s32*, 0x274), 0x17, 0);
				M2C_FIELD(arg0, s32*, 0x278) = (s32)M2C_FIELD(arg0, s32*, 0x274);
				return 1;
			}
			M2C_FIELD(arg0, s32*, 0x570) = 0;
			goto block_20;
		}
	block_20:
		return 0;
	}
	return 0;
}

void fn_8_98918(void* arg0)
{
	s32 temp_r0;
	void* temp_r3;

	temp_r0 = M2C_FIELD(arg0, s32*, 0x278);
	if (temp_r0 != -1) {
		temp_r3 = *(void**)((u8*)&lbl_802AD070 + (temp_r0 * 4));
		if (temp_r3 != NULL) {
			if ((s16)M2C_FIELD(temp_r3, s16*, 0x6F0) == 0x26) {
				fn_80043DEC();
			}
			M2C_FIELD(arg0, s32*, 0x278) = -1;
		}
	}
}

void fn_8_9897C(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x278) != -1) {
		fn_800E1208(0xF, 0);
		M2C_FIELD(arg0, s32*, 0x278) = -1;
	}
}

void fn_8_989C4(void* arg0)
{
	s32 sp10;
	f32 spC;
	s32 sp8;
	s32 temp_r0;
	u32 temp_r5;

	temp_r0 = M2C_FIELD(arg0, s32*, 0x278);
	if (temp_r0 != -1) {
		temp_r5 = *(u32*)((u8*)&lbl_802AD090 + (temp_r0 * 4));
		if (temp_r5 != 0U) {
			sp8  = M2C_FIELD(arg0, s32*, 0x140);
			spC  = M2C_FIELD(arg0, f32*, 0x144);
			sp10 = M2C_FIELD(arg0, s32*, 0x148);
			spC += -20.0f;
			fn_800D5A64((void*)(temp_r5 + 0x18), &sp8, &lbl_8_rodata_1720, 2.4f);
		}
	}
}

s32 fn_8_98A4C(void* arg0)
{
	s32 temp_r0;
	u32 temp_r31;

	temp_r0 = M2C_FIELD(arg0, s32*, 0x274);
	if (temp_r0 != -1) {
		temp_r31 = *(u32*)((u8*)&lbl_802AD070 + (temp_r0 * 4));
		if ((temp_r31 != 0U) && (fn_800AB2E0(temp_r31) != 0)) {
			if (fn_80089204(temp_r31) != 0) {
				M2C_FIELD(arg0, s32*, 0x570) = 1;
			} else {
				M2C_FIELD(arg0, s32*, 0x570) = 2;
				fn_80043F28(temp_r31);
			}
			fn_800E1208(M2C_FIELD(arg0, s32*, 0x274), 0x17, 0);
			M2C_FIELD(arg0, s32*, 0x278) = (s32)M2C_FIELD(arg0, s32*, 0x274);
			return 1;
		}
		M2C_FIELD(arg0, s32*, 0x570) = 0;
		goto block_8;
	}
block_8:
	return 0;
}

s32 fn_8_98B08(void* arg0)
{
	s32 temp_r3;

	temp_r3 = fn_800A6334();
	if ((temp_r3 == 1) && ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x2F4) != NULL)
	    && (((u32)M2C_FIELD(arg0, u32*, 0x2F0) == 0U) || (fn_8010AFB0() == 0))) {
		fn_8010AFF8(M2C_FIELD(arg0, M2C_UNK**, 0x2F4), 1);
		fn_8010B208(M2C_FIELD(arg0, M2C_UNK**, 0x2F4), &lbl_8_rodata_1704, 0.0f, 0.0f);
	}
	return temp_r3;
}

s32 fn_8_98B94(s32 arg0)
{
	s32* var_r4;
	s32 temp_r3;
	s32 temp_r3_2;
	void* temp_r5;

	if (fn_800A6334() != 0) {
		temp_r3 = fn_800A5844(arg0);
		if (temp_r3 == -1) {
			return 0;
		}
		temp_r5 = *(void**)((u8*)&lbl_802AD0D0 + (temp_r3 * 4));
		if (temp_r5 != NULL) {
			var_r4 = lbl_8_rodata_16E4;
		loop_5:
			temp_r3_2 = *var_r4;
			if (temp_r3_2 != -1) {
				if ((s16)M2C_FIELD(temp_r5, s16*, 0x150) == temp_r3_2) {
					return 0;
				}
				var_r4 += 4;
				goto loop_5;
			}
			return 1;
		}
		goto block_10;
	}
block_10:
	return 0;
}

s32 fn_8_98C34(void* arg0, f32 farg0, f32 farg1)
{
	s32 temp_cr0_eq;
	s32 temp_r31;
	s32 var_r30;

	var_r30     = 1;
	temp_cr0_eq = (s32)M2C_FIELD(arg0, s32*, 0x574) == 0;
	if (temp_cr0_eq != 0) {
		return 1;
	}
	if (temp_cr0_eq == 0) {
		temp_r31                     = fn_800A5A54();
		M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
		    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
		if (temp_r31 < 0x80) {
			M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
		}
	}
	if ((fn_800A5AC0(arg0) < farg1) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
		fn_800A4668(arg0);
		var_r30 = 0;
	} else {
		fn_800A4A8C(arg0, farg0);
	}
	M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
	fn_800A5C6C(arg0, 0xF00);
	if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
	    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
		M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
	}
	if (fn_800A5888(arg0, &lbl_8_rodata_1728, -1.0f) != 0) {
		fn_800A5B50(arg0, 0xF00);
		var_r30 = 0;
	}
	return var_r30;
}

s32 fn_8_98DA4(void* arg0)
{
	f32 temp_f2;
	s32 var_r5;

	var_r5 = 1;
	if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {
		return 1;
	}
	temp_f2                      = M2C_FIELD(arg0, f32*, 0x1C4);
	M2C_FIELD(arg0, f32*, 0x144) = (f32)(M2C_FIELD(arg0, f32*, 0x144) + 0.2f);
	M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
	if (M2C_FIELD(arg0, f32*, 0x144) == temp_f2) {
		M2C_FIELD(arg0, f32*, 0x144) = temp_f2;
	} else {
		var_r5 = 0;
	}
	return var_r5;
}

s32 fn_8_98DFC(void* arg0, f32 farg0, f32 farg1)
{
	s32 var_r31;

	var_r31 = 0;
	if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {
		return 0;
	}
	if ((fn_800A5AC0() < farg1) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
		fn_800A4668(arg0);
		var_r31 = 1;
	} else {
		fn_800A4A8C(arg0, farg0);
	}
	M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
	fn_800A5C6C(arg0, 0xF00);
	if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
	    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
		M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
	}
	if (fn_800A5888(arg0, &lbl_8_rodata_1728, -1.0f) != 0) {
		fn_800A5B50(arg0, 0xF00);
		var_r31 = 2;
	}
	return var_r31;
}

s32 fn_8_98F30(void* arg0)
{
	s32 temp_r31;

	if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {
		return 0;
	}
	temp_r31                     = fn_800A5A54();
	M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(
	    M2C_FIELD(arg0, s32*, 0x150), M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
	if (temp_r31 < 0x80) {
		M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
		return 1;
	}
	return 0;
}

void fn_8_98FAC(void* arg0)
{
	f32 sp14;
	s32 sp10;
	f32 spC;
	f32 sp8;
	f32* var_r3;
	f32 temp_f1;
	f32 temp_f1_2;

	fn_800B7864(0);
	spC     = M2C_FIELD(&lbl_8_rodata_16D8, f32*, 0);
	sp10    = M2C_FIELD(&lbl_8_rodata_16D8, s32*, 4);
	sp14    = M2C_FIELD(&lbl_8_rodata_16D8, f32*, 8);
	temp_f1 = 1.0f - (0.004f * (M2C_FIELD(arg0, f32*, 0x144) - M2C_FIELD(arg0, f32*, 0x2FC)));
	sp8     = temp_f1;
	var_r3  = &lbl_8_rodata_172C;
	if (temp_f1 < 0.2f) {

	} else {
		var_r3 = &lbl_8_rodata_1730;
		if (temp_f1 > 1.0f) {

		} else {
			var_r3 = &sp8;
		}
	}
	temp_f1_2 = *var_r3;
	sp8       = temp_f1_2;
	fn_800B7514((u8*)arg0 + 0x2F8, (u8*)arg0 + 0x31C, &spC, temp_f1_2);
	spC  = 10.0f;
	sp14 = 16.0f;
	fn_800B7514((u8*)arg0 + 0x304, (u8*)arg0 + 0x31C, &spC, sp8);
	fn_800B7514((u8*)arg0 + 0x310, (u8*)arg0 + 0x31C, &spC, sp8);
	fn_800B7820();
}

void fn_8_990C4(void* arg0, M2C_UNK arg_sp0)
{
	f32 sp20;
	s32 sp1C;
	s32 sp18;
	s32 sp14;
	f32 sp10;
	s32 spC;
	f32 sp8;
	M2C_UNK* var_r30;
	RwFrame* temp_r28;
	f32 temp_f0;
	s32 var_r27;
	s32 var_r29;
	u8* var_r29_2;

	if ((s32)M2C_FIELD(arg0, s32*, 0x28C) != 0) {
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x90)();
		fn_80113874();
		fn_80113940();
		fn_801138B4();
		fn_80113874(0x10);
		sp14 = M2C_FIELD(&lbl_8_rodata_16BC, s32*, 0);
		sp18 = M2C_FIELD(&lbl_8_rodata_16BC, s32*, 4);
		sp1C = M2C_FIELD(&lbl_8_rodata_16BC, s32*, 8);
		sp20 = M2C_FIELD(&lbl_8_rodata_16BC, f32*, 0xC);
		sp20 = M2C_FIELD(arg0, f32*, 0x288);
		fn_8005DABC(M2C_FIELD(arg0, u32*, 0x2D8), &sp14);
		fn_8005DABC(M2C_FIELD(arg0, u32*, 0x2DC), &sp14);
		fn_8005DABC(M2C_FIELD(arg0, u32*, 0x2E0), &sp14);
		var_r29 = 2;
		var_r30 = &captureObjectGlobalArray + 0x28;
		do {
			fn_8011398C(var_r30, M2C_FIELD(arg0, s32*, 0x57C));
			var_r30 += 0x14;
			var_r29 += 1;
		} while (var_r29 < 8);
		if ((u32)M2C_FIELD(arg0, u32*, 0x2D8) != 0U) {
			fn_8014FF2C();
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2DC) != 0U) {
			fn_8014FF2C();
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2E0) != 0U) {
			fn_8014FF2C();
		}
		temp_r28  = M2C_FIELD(M2C_FIELD(arg0, void**, 0x2E4), RwFrame**, 4);
		var_r27   = 0;
		var_r29_2 = (u8*)arg0;
	loop_11:
		if (var_r27 < (s32)M2C_FIELD(arg0, s32*, 0x32C)) {
			sp8     = M2C_FIELD(&lbl_8_rodata_16CC, f32*, 0);
			spC     = M2C_FIELD(&lbl_8_rodata_16CC, s32*, 4);
			sp10    = M2C_FIELD(&lbl_8_rodata_16CC, f32*, 8);
			temp_f0 = M2C_FIELD(var_r29_2, f32*, 0x348);
			sp8     = temp_f0;
			sp10    = temp_f0;
			fn_8019EC30(temp_r28, &sp8, 0);
			fn_8019EB94(temp_r28, var_r29_2 + 0x330, 2);
			fn_8014FF2C(M2C_FIELD(arg0, void**, 0x2E4));
			var_r29_2 += 0x24;
			var_r27 += 1;
			goto loop_11;
		}
		fn_801138F4();
	}
}

void fn_8_99254(void* arg0)
{
	M2C_UNK* var_r31;
	s32 var_r30;

	var_r30 = 0;
	var_r31 = &captureObjectGlobalArray;
	do {
		fn_8011398C(var_r31, M2C_FIELD(arg0, s32*, 0x57C));
		var_r31 += 0x14;
		var_r30 += 1;
	} while (var_r30 < 2);
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(void*), 0x90)(arg0);
	fn_80113874();
	fn_8014FF2C(M2C_FIELD(arg0, void**, 0xE8));
	if ((u32)M2C_FIELD(arg0, u32*, 0x2E8) != 0U) {
		fn_8014FF2C();
	}
}

void fn_8_992E4(TObject* arg0)
{
	fn_8_9C054((TObject*)arg0);
	fn_8_9B920(arg0);
}

void fn_8_99318(TObject* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	RwFrame* temp_r30_2;
	RwFrame* temp_r30_3;
	RwFrame* temp_r30_4;
	RwFrame* temp_r30_5;
	s16 var_r0_4;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r3_2;
	s32 var_r0;
	s32 var_r0_2;
	s32 var_r0_3;
	u32 temp_r30;
	void** temp_r3;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;
	void* temp_r4;
	void* temp_r4_2;

	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	arg0->unk574 = var_r0;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0_2 = 0;
	} else {
		var_r0_2 = 1;
	}
	arg0->unk578 = var_r0_2;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) == 1) {
		arg0->unk278 = -1;
	}
	if ((void*)arg0->unk38 != NULL) {
		arg0->unk140 = arg0->unk88;
		arg0->unk144 = arg0->unk8C;
		arg0->unk148 = arg0->unk90;
	}
	fn_800A5B34(arg0);
	M2C_FIELD(arg0->unk18, M2C_UNK(**)(TObject*), 0x38)(arg0);
	fn_800A3D94(arg0);
	if ((s32)arg0->unk574 != 0) {
		if ((s32)arg0->unk278 != -1) {
			var_r0_3 = 0;
		} else {
			temp_r0 = arg0->unk19C;
			if (temp_r0 != 9) {
				if (temp_r0 < 9) {
					if (temp_r0 != 6) {
						if (temp_r0 < 6) {
							if (temp_r0 != 2) {
								goto block_24;
							}
							goto block_25;
						}
						goto block_24;
					}
					goto block_25;
				}
				if (temp_r0 != 0x2C) {
				block_24:
					var_r0_3 = 0;
				} else {
					goto block_25;
				}
			} else {
			block_25:
				sp8  = arg0->unk140;
				spC  = arg0->unk144;
				sp10 = arg0->unk148;
				spC -= 40.0f;
				arg0->unk274 = fn_80103284(&sp8, &lbl_8_rodata_1718, 20.0f);
				if (((s32)arg0->unk274 != -1) && (fn_800AB25C() == 1)) {
					temp_r0_2 = arg0->unk274;
					if (temp_r0_2 != -1) {
						temp_r30 = *(u32*)((u8*)&lbl_802AD070 + (temp_r0_2 * 4));
						if ((temp_r30 != 0U) && (fn_800AB2E0(temp_r30) != 0)) {
							if (fn_80089204(temp_r30) != 0) {
								arg0->unk570 = 1;
							} else {
								arg0->unk570 = 2;
								fn_80043F28(temp_r30);
							}
							fn_800E1208(arg0->unk274, 0x17, 0);
							arg0->unk278 = arg0->unk274;
							var_r0_3     = 1;
						} else {
							arg0->unk570 = 0;
							goto block_35;
						}
					} else {
					block_35:
						var_r0_3 = 0;
					}
				} else {
					var_r0_3 = 0;
				}
			}
		}
		arg0->unk280 = var_r0_3;
	}
	temp_r3 = arg0->unk240;
	if (temp_r3 != NULL) {
		M2C_FIELD(*temp_r3, M2C_UNK(**)(TObject*), 0xC)(arg0);
	}
	M2C_FIELD(arg0->unk18, M2C_UNK(**)(TObject*, s32, M2C_UNK), 0x50)(arg0, arg0->unk19C, 1);
	if ((s32)arg0->unk278 != -1) {
		temp_r3_2 = fn_801031D8();
		if (temp_r3_2 != -1) {
			temp_r3_3 = *(void**)((u8*)&lbl_80303DC8 + (temp_r3_2 * 4));
			if (temp_r3_3 != NULL) {
				if ((s32)M2C_FIELD(temp_r3_3, s32*, 0x154) != 9) {
					var_r0_4 = -1;
				} else {
					var_r0_4 = M2C_FIELD(temp_r3_3, s16*, 0x14E);
				}
				if ((var_r0_4 != -1) && ((s32)arg0->unk278 != -1)) {
					fn_800E1208(0xF, 0);
					arg0->unk278 = -1;
				}
			}
		}
	}
	fn_8_9B920(arg0);
	fn_800A3D48(arg0);
	if (((s32)arg0->unk578 != 0) && ((s32)arg0->unk28C != 0)) {
		temp_r4 = arg0->unk2D8;
		if ((temp_r4 != NULL) && ((u32)arg0->unk270 != 0U)) {
			temp_r30_2 = M2C_FIELD(temp_r4, RwFrame**, 4);
			fn_8019ECCC(temp_r30_2, fn_8019E8EC(), 0);
		}
		temp_r3_4 = arg0->unk2DC;
		if ((temp_r3_4 != NULL) && ((u32)arg0->unk268 != 0U)) {
			temp_r30_3 = M2C_FIELD(temp_r3_4, RwFrame**, 4);
			fn_8019ED68(temp_r30_3, &lbl_80239984, 0, 180.0f);
			fn_8019ECCC(temp_r30_3, fn_8019E8EC(arg0->unk268), 2);
		}
		temp_r3_5 = arg0->unk2E0;
		if ((temp_r3_5 != NULL) && ((u32)arg0->unk26C != 0U)) {
			temp_r30_4 = M2C_FIELD(temp_r3_5, RwFrame**, 4);
			fn_8019ED68(temp_r30_4, &lbl_80239984, 0, 180.0f);
			fn_8019ECCC(temp_r30_4, fn_8019E8EC(arg0->unk26C), 2);
		}
		arg0->unk284 += 0x1000;
		arg0->unk288 = 0.5f + (0.5f * fn_800D7B00(arg0->unk284));
	}
	if ((u32)arg0->unk2EC != 0U) {
		temp_r4_2 = arg0->unk2E8;
		if (temp_r4_2 != NULL) {
			temp_r30_5 = M2C_FIELD(temp_r4_2, RwFrame**, 4);
			fn_8019ECCC(temp_r30_5, fn_8019E8EC(), 0);
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

void fn_8_99800(void* arg0, s32 arg1)
{
	f32 temp_f31;
	s32 temp_r30;
	s32 var_r0;
	s32 var_r30;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, f32*, 0x27C) = 0.15f;
			M2C_FIELD(arg0, f32*, 0x1B8) = (f32)M2C_FIELD(arg0, f32*, 0x27C);
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x1C0);
			M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x1C4);
			M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x1C8);
			M2C_FIELD(arg0, s32*, 0x2D4) = 0;
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x2D4) == 0) {
				if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {
					var_r0 = 0;
				} else {
					temp_r30                     = fn_800A5A54();
					M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
					    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
					if (temp_r30 < 0x80) {
						M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
						var_r0                       = 1;
					} else {
						var_r0 = 0;
					}
				}
				if (var_r0 != 0) {
					M2C_FIELD(arg0, s32*, 0x2D4) = 1;
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x2D4) != 0) {
				temp_f31 = M2C_FIELD(arg0, f32*, 0x27C);
				var_r30  = 0;
				if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {

				} else {
					if ((fn_800A5AC0(arg0) < 2.0f)
					    || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
						fn_800A4668(arg0);
						var_r30 = 1;
					} else {
						fn_800A4A8C(arg0, temp_f31);
					}
					M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
					fn_800A5C6C(arg0, 0xF00);
					if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
					    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
						M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
					}
					if (fn_800A5888(arg0, &lbl_8_rodata_1728, -1.0f) != 0) {
						fn_800A5B50(arg0, 0xF00);
						var_r30 = 2;
					}
				}
				if (var_r30 == 1) {
					M2C_FIELD(arg0, s32*, 0x248) = 2;
				}
			}
			return;
	}
}

void fn_8_99A0C(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
		}
	} else {
		if ((u32)M2C_FIELD(arg0, u32*, 0x2F4) != 0U) {
			fn_8010B074();
		}
		M2C_FIELD(arg0, s32*, 0xD4) = 0;
	}
}

void fn_8_99A60(void* arg0, s32 arg1)
{
	s32 temp_r0;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			temp_r0 = M2C_FIELD(arg0, s32*, 0x278);
			if (temp_r0 != -1) {
				temp_r3 = *(void**)((u8*)&lbl_802AD070 + (temp_r0 * 4));
				if (temp_r3 != NULL) {
					if ((s16)M2C_FIELD(temp_r3, s16*, 0x6F0) == 0x26) {
						fn_80043DEC();
					}
					M2C_FIELD(arg0, s32*, 0x278) = -1;
				}
			}
			M2C_FIELD(arg0, f32*, 0x2C0) = 1.0f;
			M2C_FIELD(arg0, f32*, 0x2BC) = 1.0f;
			M2C_FIELD(arg0, f32*, 0x2B8) = 1.0f;
			M2C_FIELD(arg0, f32*, 0x2CC) = 0.0f;
			M2C_FIELD(arg0, f32*, 0x2C8) = 0.0f;
			M2C_FIELD(arg0, f32*, 0x2C4) = 0.0f;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			return;
		case 1:
			M2C_FIELD(arg0, f32*, 0x2C4) = (f32)(M2C_FIELD(arg0, f32*, 0x2C4) + -0.05f);
			M2C_FIELD(arg0, f32*, 0x2C8)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x2C8) + M2C_FIELD(&lbl_8_rodata_16B0, f32*, 4));
			M2C_FIELD(arg0, f32*, 0x2CC)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x2CC) + M2C_FIELD(&lbl_8_rodata_16B0, f32*, 8));
			M2C_FIELD(arg0, f32*, 0x2B8)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x2B8) + M2C_FIELD(arg0, f32*, 0x2C4));
			M2C_FIELD(arg0, f32*, 0x2BC)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x2BC) + M2C_FIELD(arg0, f32*, 0x2C8));
			M2C_FIELD(arg0, f32*, 0x2C0)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x2C0) + M2C_FIELD(arg0, f32*, 0x2CC));
			if (M2C_FIELD(arg0, f32*, 0x2B8) < 0.0f) {
				fn_8005BC04((u8*)arg0 + 0xB0);
				M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			}
			return;
	}
}

void fn_8_99BB8(void* arg0, s32 arg1)
{
	s32 sp10;
	f32 spC;
	s32 sp8;
	s32 temp_cr0_eq;
	s32 temp_r0;
	s32 temp_r30;
	u32 temp_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, f32*, 0x27C) = (f32)M2C_FIELD(arg0, f32*, 0x588);
			M2C_FIELD(arg0, f32*, 0x1B8) = (f32)M2C_FIELD(arg0, f32*, 0x27C);
			M2C_FIELD(arg0, f32*, 0x210) = 1000000.0f;
			M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x2A8);
			M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x2AC);
			M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x2B0);
			M2C_FIELD(arg0, s32*, 0x2B4) = (s32)(M2C_FIELD(arg0, s32*, 0x2B4) + 1);
			M2C_FIELD(arg0, s32*, 0x28C) = 1;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			return;
		case 1:
			temp_r0 = M2C_FIELD(arg0, s32*, 0x278);
			if (temp_r0 != -1) {
				temp_r4 = *(u32*)((u8*)&lbl_802AD090 + (temp_r0 * 4));
				if (temp_r4 != 0U) {
					sp8  = M2C_FIELD(arg0, s32*, 0x140);
					spC  = M2C_FIELD(arg0, f32*, 0x144);
					sp10 = M2C_FIELD(arg0, s32*, 0x148);
					spC += -20.0f;
					fn_800D5A64((void*)(temp_r4 + 0x18), &sp8, &lbl_8_rodata_1720, 2.4f);
				}
			}
			fn_8_98548(arg0);
			temp_cr0_eq = (s32)M2C_FIELD(arg0, s32*, 0x574) == 0;
			if (temp_cr0_eq == 0) {
				if (temp_cr0_eq == 0) {
					temp_r30                     = fn_800A5A54(arg0);
					M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
					    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
					if (temp_r30 < 0x80) {
						M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
					}
				}
				if (fn_800D5A64((u8*)arg0 + 0x140, (u8*)arg0 + 0x2A8,
				        M2C_BITWISE(M2C_UNK*, M2C_FIELD(arg0, f32*, 0x27C)))
				    != 0) {
					M2C_FIELD(arg0, s32*, 0x248) = 0x2E;
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(0x4015, (u8*)arg0 + 0x140, 0, 1, 0, 0);
					}
				}
			}
			return;
	}
}

void fn_8_99D64(void* arg0, s32 arg1)
{
	s32 sp10;
	f32 spC;
	s32 sp8;
	s32 temp_r0;
	u32 temp_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x28C) = 1;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			return;
		case 1:
			temp_r0 = M2C_FIELD(arg0, s32*, 0x278);
			if (temp_r0 != -1) {
				temp_r4 = *(u32*)((u8*)&lbl_802AD090 + (temp_r0 * 4));
				if (temp_r4 != 0U) {
					sp8  = M2C_FIELD(arg0, s32*, 0x140);
					spC  = M2C_FIELD(arg0, f32*, 0x144);
					sp10 = M2C_FIELD(arg0, s32*, 0x148);
					spC += -20.0f;
					fn_800D5A64((void*)(temp_r4 + 0x18), &sp8, &lbl_8_rodata_1720, 2.4f);
				}
			}
			fn_8_98548(arg0);
			return;
	}
}

void fn_8_99E34(void* arg0, s32 arg1)
{
	f32 temp_f2;
	s32 var_r4;

	switch (arg1) { /* irregular */
		case 0:
			if ((u32)M2C_FIELD(arg0, u32*, 0x2F4) != 0U) {
				fn_8010B074();
			}
			M2C_FIELD(arg0, s32*, 0xD4) = 0;
			return;
		case 1:
			var_r4 = 1;
			if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {

			} else {
				temp_f2                      = M2C_FIELD(arg0, f32*, 0x1C4);
				M2C_FIELD(arg0, f32*, 0x144) = (f32)(M2C_FIELD(arg0, f32*, 0x144) + 0.2f);
				M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
				if (M2C_FIELD(arg0, f32*, 0x144) == temp_f2) {
					M2C_FIELD(arg0, f32*, 0x144) = temp_f2;
				} else {
					var_r4 = 0;
				}
			}
			if (var_r4 != 0) {
				M2C_FIELD(arg0, s32*, 0x248) = 2;
			}
			return;
	}
}

void fn_8_99EF4(void* arg0, s32 arg1)
{
	s32 sp10;
	f32 spC;
	s32 sp8;
	f32 temp_f1;
	f32 temp_f1_2;
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x290) = 0x5A;
			M2C_FIELD(arg0, s32*, 0xD4)  = 3;
			M2C_FIELD(arg0, s32*, 0x2D0) = (s32)M2C_FIELD(arg0, s32*, 0x238);
			if ((u32)lbl_8042C6D0 == 0U) {
				fn_8011C6EC();
			}
			fn_8011C188(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x238));
			M2C_FIELD(arg0, s32*, 0x29C) = 0;
			M2C_FIELD(arg0, u16*, 0x30)  = (u16)(M2C_FIELD(arg0, u16*, 0x30) | 0x200);
			return;
		case 1:
			temp_r0                      = M2C_FIELD(arg0, s32*, 0x290) - 1;
			M2C_FIELD(arg0, s32*, 0x290) = temp_r0;
			if (temp_r0 == 0) {
				if ((u32)M2C_FIELD(arg0, u32*, 0x2F0) != 0U) {
					fn_8010B074();
				}
				if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x2F4) != NULL) {
					fn_8010AFF8((M2C_UNK*)2U);
					fn_8010B208(M2C_FIELD(arg0, M2C_UNK**, 0x2F4), &lbl_8_rodata_1704, 0.0f, 0.0f);
				}
			}
			sp8     = M2C_FIELD(arg0, s32*, 0x2F8);
			spC     = M2C_FIELD(arg0, f32*, 0x2FC);
			sp10    = M2C_FIELD(arg0, s32*, 0x300);
			temp_f1 = spC;
			spC     = temp_f1 + 2.0f;
			if ((fn_800A34D0(arg0, &sp8, temp_f1) != 0)
			    && ((s32)M2C_FIELD(arg0, s32*, 0x29C) == 0)) {
				M2C_FIELD(arg0, s32*, 0x29C) = 1;
				temp_f1_2                    = M2C_FIELD(arg0, f32*, 0x1A4) - 1.0f;
				M2C_FIELD(arg0, f32*, 0x1A4) = temp_f1_2;
				if (temp_f1_2 < 0.0f) {
					M2C_FIELD(arg0, f32*, 0x1A4) = 0.0f;
				}
				M2C_FIELD(arg0, s16*, 0x2E)  = (s16)M2C_FIELD(arg0, f32*, 0x1A4);
				M2C_FIELD(arg0, s32*, 0x230) = fn_800AB104(M2C_FIELD(arg0, s32*, 0x2D0));
				return;
			}
		case 2:
			return;
		case 3:
			M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) & 0xFFFFFDFF);
			break;
	}
}

void fn_8_9A0B0(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x290) = 0;
			return;
		case 1:
			M2C_FIELD(arg0, s32*, 0x290) = (s32)(M2C_FIELD(arg0, s32*, 0x290) + 0x550);
			M2C_FIELD(arg0, f32*, 0x294) = (f32)(20.0f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x290)));
			M2C_FIELD(arg0, f32*, 0x298)
			    = (f32)(20.0f * fn_800D7B00((s32)(0.5f * (f32)M2C_FIELD(arg0, s32*, 0x290)), 0.5f));
			return;
	}
}

void fn_8_9A188(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x278) != -1) {
				fn_800E1208(0xF, 0);
				M2C_FIELD(arg0, s32*, 0x278) = -1;
			}
			M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(void*), 0x3C)(arg0);
			return;
		case 1:
			M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			return;
	}
}

void fn_8_9A218(void* arg0, s32 arg1)
{
	s32 sp10;
	f32 spC;
	s32 sp8;
	s32 temp_r0;
	u32 temp_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x28C) = 1;
			return;
		case 1:
			temp_r0 = M2C_FIELD(arg0, s32*, 0x278);
			if (temp_r0 != -1) {
				temp_r4 = *(u32*)((u8*)&lbl_802AD090 + (temp_r0 * 4));
				if (temp_r4 != 0U) {
					sp8  = M2C_FIELD(arg0, s32*, 0x140);
					spC  = M2C_FIELD(arg0, f32*, 0x144);
					sp10 = M2C_FIELD(arg0, s32*, 0x148);
					spC += -20.0f;
					fn_800D5A64((void*)(temp_r4 + 0x18), &sp8, &lbl_8_rodata_1720, 2.4f);
				}
			}
			fn_8_98548(arg0);
			return;
		case 3:
			M2C_FIELD(arg0, s32*, 0x28C) = 0;
			/* fallthrough */
		case 2:
			return;
	}
}

void fn_8_9A2F4(void* arg0, s32 arg1)
{
	s32 temp_r0;
	void* temp_r3;
	void* temp_r3_2;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2A4) = 0;
			M2C_FIELD(arg0, s32*, 0x2A0) = 0x32;
			M2C_FIELD(arg0, s32*, 0xD4)  = 1;
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x4013, (u8*)arg0 + 0x140, 0, 1, 0, 0);
				return;
			}
		case 2:
			return;
		case 1:
			if (((s32)M2C_FIELD(arg0, s32*, 0x574) != 0)
			    && (temp_r0                      = M2C_FIELD(arg0, s32*, 0x2A0) - 1,
			        M2C_FIELD(arg0, s32*, 0x2A0) = temp_r0, ((temp_r0 < 0) != 0))
			    && ((s32)M2C_FIELD(arg0, s32*, 0x2A4) == 0)) {
				M2C_FIELD(arg0, s32*, 0x2A4) = 1;
				if ((s32)M2C_FIELD(arg0, s32*, 0x278) != -1) {
					fn_800E1208(0xF, 0);
					M2C_FIELD(arg0, s32*, 0x278) = -1;
				}
				temp_r3                        = M2C_FIELD(arg0, void**, 0x38);
				M2C_FIELD(temp_r3, s32*, 0x34) = (s32)(M2C_FIELD(temp_r3, s32*, 0x34) & 0xFFFFFFEF);
				if ((u32)lbl_8042C388 != 0U) {
					fn_800B4A38(0x4014, (u8*)arg0 + 0x140, 0, 1, 0, 0);
					return;
				}
			}
			break;
		case 3:
			temp_r3_2                        = M2C_FIELD(arg0, void**, 0x38);
			M2C_FIELD(temp_r3_2, s32*, 0x34) = (s32)(M2C_FIELD(temp_r3_2, s32*, 0x34) | 0x10);
			break;
	}
}

void fn_8_9A438(void* arg0, s32 arg1)
{
	s32 temp_r0;
	s32 temp_r31;
	void* temp_r3;

	if (arg1 != 1) {
		if (arg1 < 1) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x274) = fn_80103324((u8*)arg0 + 0x140, &lbl_8_rodata_1760, 1e8f);
	temp_r0                      = M2C_FIELD(arg0, s32*, 0x274);
	if (temp_r0 != -1) {
		temp_r3 = *(void**)((u8*)&lbl_802AD090 + (temp_r0 * 4));
		if (temp_r3 != NULL) {
			M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(temp_r3, f32*, 0x18);
			M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(temp_r3, f32*, 0x1C);
			M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(temp_r3, f32*, 0x20);
		}
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x574) != 0) {
		temp_r31                     = fn_800A5A54(arg0);
		M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
		    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
		if (temp_r31 < 0x80) {
			M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
		}
	}
}

void fn_8_9A514(void* arg0, s32 arg1)
{
	f32 temp_f31;
	s32 temp_cr0_eq;
	s32 temp_r0;
	s32 temp_r30;
	s32 var_r29;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, f32*, 0x27C) = (f32)M2C_FIELD(arg0, f32*, 0x588);
			M2C_FIELD(arg0, f32*, 0x1B8) = (f32)M2C_FIELD(arg0, f32*, 0x27C);
			return;
		case 1:
			M2C_FIELD(arg0, s32*, 0x274) = fn_80103324((u8*)arg0 + 0x140, &lbl_8_rodata_1760, 1e8f);
			temp_r0                      = M2C_FIELD(arg0, s32*, 0x274);
			if (temp_r0 != -1) {
				temp_r3 = *(void**)((u8*)&lbl_802AD090 + (temp_r0 * 4));
				if (temp_r3 != NULL) {
					M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(temp_r3, f32*, 0x18);
					M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(temp_r3, f32*, 0x1C);
					M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(temp_r3, f32*, 0x20);
				}
			}
			temp_f31    = M2C_FIELD(arg0, f32*, 0x27C);
			var_r29     = 1;
			temp_cr0_eq = (s32)M2C_FIELD(arg0, s32*, 0x574) == 0;
			if (temp_cr0_eq != 0) {

			} else {
				if (temp_cr0_eq == 0) {
					temp_r30                     = fn_800A5A54(arg0);
					M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
					    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
					if (temp_r30 < 0x80) {
						M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
					}
				}
				if ((fn_800A5AC0(arg0) < 10.0f) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
					fn_800A4668(arg0);
					var_r29 = 0;
				} else {
					fn_800A4A8C(arg0, temp_f31);
				}
				M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
				fn_800A5C6C(arg0, 0xF00);
				if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
				    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
					M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
				}
				if (fn_800A5888(arg0, &lbl_8_rodata_1728, -1.0f) != 0) {
					fn_800A5B50(arg0, 0xF00);
					var_r29 = 0;
				}
			}
			if (var_r29 == 0) {
				M2C_FIELD(arg0, s32*, 0x248) = 9;
			}
			return;
	}
}

void fn_8_9A710(void* arg0, s32 arg1)
{
	M2C_UNK sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f31;
	f32 temp_f3;
	s32 temp_r30;
	s32 temp_r30_2;
	s32 var_r0;
	s32 var_r30;
	s32 var_r4;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, f32*, 0x27C) = 0.15f;
			M2C_FIELD(arg0, f32*, 0x1B8) = (f32)M2C_FIELD(arg0, f32*, 0x27C);
			var_r4                       = 0;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x258);
			M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x25C);
			M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x260);
			if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {

			} else {
				temp_r30                     = fn_800A5A54();
				M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
				    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
				if (temp_r30 < 0x80) {
					M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
					var_r4                       = 1;
				} else {
					var_r4 = 0;
				}
			}
			if (var_r4 != 0) {
				M2C_FIELD(arg0, s32*, 0x264) = 1;
				return;
			}
			M2C_FIELD(arg0, s32*, 0x264) = 0;
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x264) != 0) {
				temp_f31 = M2C_FIELD(arg0, f32*, 0x27C);
				var_r30  = 0;
				if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {

				} else {
					if ((fn_800A5AC0() < 2.0f) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
						fn_800A4668(arg0);
						var_r30 = 1;
					} else {
						fn_800A4A8C(arg0, temp_f31);
					}
					M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
					fn_800A5C6C(arg0, 0xF00);
					if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
					    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
						M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
					}
					if (fn_800A5888(arg0, &lbl_8_rodata_1728, -1.0f) != 0) {
						fn_800A5B50(arg0, 0xF00);
						var_r30 = 2;
					}
				}
				if (var_r30 != 0) {
					sp8     = 0.0f;
					spC     = 0.0f;
					sp10    = M2C_FIELD(arg0, f32*, 0x254);
					temp_f3 = (160.0f * (0.000030517578f * (f32)fn_801C28D8(&lbl_8_rodata_1704)))
					    - 80.0f;
					fn_80195A74(&sp14, &lbl_80239984, 0,
					    180.0f
					        + (0.005493164f
					            * (f32)M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x10))
					        + temp_f3,
					    180.0f, temp_f3);
					fn_80196050(&sp14, M2C_FIELD(arg0, void**, 0xB0), 2);
					fn_8019941C(&sp8, &sp8, 1, &sp14);
					M2C_FIELD(arg0, f32*, 0x1CC) = sp8;
					M2C_FIELD(arg0, f32*, 0x1D0) = spC;
					M2C_FIELD(arg0, f32*, 0x1D4) = sp10;
					M2C_FIELD(arg0, f32*, 0x254) = (f32)(M2C_FIELD(arg0, f32*, 0x254) * -1.0f);
					M2C_FIELD(arg0, s32*, 0x264) = 0;
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x264) == 0) {
				if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {
					var_r0 = 0;
				} else {
					temp_r30_2                   = fn_800A5A54(arg0);
					M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
					    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
					if (temp_r30_2 < 0x80) {
						M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
						var_r0                       = 1;
					} else {
						var_r0 = 0;
					}
				}
				if (var_r0 != 0) {
					M2C_FIELD(arg0, s32*, 0x264) = 1;
					return;
				}
			} else {
				case 2:
					return;
			}
			break;
		case 3:
			M2C_FIELD(arg0, f32*, 0x258) = (f32)M2C_FIELD(arg0, f32*, 0x1CC);
			M2C_FIELD(arg0, f32*, 0x25C) = (f32)M2C_FIELD(arg0, f32*, 0x1D0);
			M2C_FIELD(arg0, f32*, 0x260) = (f32)M2C_FIELD(arg0, f32*, 0x1D4);
			break;
	}
}

void fn_8_9AABC(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			M2C_FIELD(arg0, s32*, 0x2A0) = 0x78;
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x574) != 0) {
				temp_r0                      = M2C_FIELD(arg0, s32*, 0x2A0) - 1;
				M2C_FIELD(arg0, s32*, 0x2A0) = temp_r0;
				if (temp_r0 < 0) {
					M2C_FIELD(arg0, s32*, 0x2A0) = 0x78;
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(0x4011, (u8*)arg0 + 0x140, 0, 1, 0, 0);
					}
				}
			}
			return;
	}
}

void fn_8_9AB68(void* arg0, u32 arg1, s32 arg2)
{
	s32 sp10;
	f32 spC;
	s32 sp8;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f2;
	f32 temp_f31;
	f32 temp_f31_2;
	s32 temp_cr0_eq;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r0_4;
	s32 temp_r0_5;
	s32 temp_r0_6;
	s32 temp_r30;
	s32 temp_r30_2;
	s32 temp_r30_3;
	s32 var_r0;
	s32 var_r29;
	s32 var_r29_2;
	s32 var_r4;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;

	switch (arg1) {         /* switch 1 */
		case 1:             /* switch 1 */
			switch (arg2) { /* switch 2; irregular */
				case 0:     /* switch 2 */
					M2C_FIELD(arg0, s32*, 0xD4)  = 0;
					M2C_FIELD(arg0, s32*, 0x2A0) = 0x78;
					return;
				case 1: /* switch 2 */
					if ((s32)M2C_FIELD(arg0, s32*, 0x574) != 0) {
						temp_r0                      = M2C_FIELD(arg0, s32*, 0x2A0) - 1;
						M2C_FIELD(arg0, s32*, 0x2A0) = temp_r0;
						if (temp_r0 < 0) {
							M2C_FIELD(arg0, s32*, 0x2A0) = 0x78;
							if ((u32)lbl_8042C388 != 0U) {
								fn_800B4A38(0x4011, (u8*)arg0 + 0x140, 0, 1, 0, 0);
								return;
							}
						}
					}
				default: /* switch 1 */
				case 2:  /* switch 4 */
					return;
			}
			break;
		case 2: /* switch 1 */
			fn_8_9A710(arg0, arg2);
			return;
		case 44:            /* switch 1 */
			switch (arg2) { /* switch 3; irregular */
				case 0:     /* switch 3 */
					M2C_FIELD(arg0, f32*, 0x27C) = (f32)M2C_FIELD(arg0, f32*, 0x588);
					M2C_FIELD(arg0, f32*, 0x1B8) = (f32)M2C_FIELD(arg0, f32*, 0x27C);
					return;
				case 1: /* switch 3 */
					M2C_FIELD(arg0, s32*, 0x274)
					    = fn_80103324((u8*)arg0 + 0x140, &lbl_8_rodata_1760, 1e8f);
					temp_r0_2 = M2C_FIELD(arg0, s32*, 0x274);
					if (temp_r0_2 != -1) {
						temp_r3 = *(void**)((u8*)&lbl_802AD090 + (temp_r0_2 * 4));
						if (temp_r3 != NULL) {
							M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(temp_r3, f32*, 0x18);
							M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(temp_r3, f32*, 0x1C);
							M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(temp_r3, f32*, 0x20);
						}
					}
					temp_f31    = M2C_FIELD(arg0, f32*, 0x27C);
					var_r29     = 1;
					temp_cr0_eq = (s32)M2C_FIELD(arg0, s32*, 0x574) == 0;
					if (temp_cr0_eq != 0) {

					} else {
						if (temp_cr0_eq == 0) {
							temp_r30                     = fn_800A5A54(arg0);
							M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
							    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
							if (temp_r30 < 0x80) {
								M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
							}
						}
						if ((fn_800A5AC0(arg0) < 10.0f)
						    || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
							fn_800A4668(arg0);
							var_r29 = 0;
						} else {
							fn_800A4A8C(arg0, temp_f31);
						}
						M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
						fn_800A5C6C(arg0, 0xF00);
						if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
						    && (M2C_FIELD(arg0, f32*, 0x15C)
						        < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
							M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
						}
						if (fn_800A5888(arg0, &lbl_8_rodata_1728, -1.0f) != 0) {
							fn_800A5B50(arg0, 0xF00);
							var_r29 = 0;
						}
					}
					if (var_r29 == 0) {
						M2C_FIELD(arg0, s32*, 0x248) = 9;
						return;
					}
					break;
			}
			break;
		case 31: /* switch 1 */
			if (arg2 != 1) {
				if (arg2 < 1) {
					return;
				}
				return;
			}
			M2C_FIELD(arg0, s32*, 0x274) = fn_80103324((u8*)arg0 + 0x140, &lbl_8_rodata_1760, 1e8f);
			temp_r0_3                    = M2C_FIELD(arg0, s32*, 0x274);
			if (temp_r0_3 != -1) {
				temp_r3_2 = *(void**)((u8*)&lbl_802AD090 + (temp_r0_3 * 4));
				if (temp_r3_2 != NULL) {
					M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(temp_r3_2, f32*, 0x18);
					M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(temp_r3_2, f32*, 0x1C);
					M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(temp_r3_2, f32*, 0x20);
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x574) != 0) {
				temp_r30_2                   = fn_800A5A54(arg0);
				M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
				    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
				if (temp_r30_2 < 0x80) {
					M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
					return;
				}
			}
			break;
		case 32:            /* switch 1 */
			switch (arg2) { /* switch 4; irregular */
				case 0:     /* switch 4 */
					M2C_FIELD(arg0, s32*, 0x2A4) = 0;
					M2C_FIELD(arg0, s32*, 0x2A0) = 0x32;
					M2C_FIELD(arg0, s32*, 0xD4)  = 1;
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(0x4013, (u8*)arg0 + 0x140, 0, 1, 0, 0);
						return;
					}
					break;
				case 1: /* switch 4 */
					if (((s32)M2C_FIELD(arg0, s32*, 0x574) != 0)
					    && (temp_r0_4                    = M2C_FIELD(arg0, s32*, 0x2A0) - 1,
					        M2C_FIELD(arg0, s32*, 0x2A0) = temp_r0_4, ((temp_r0_4 < 0) != 0))
					    && ((s32)M2C_FIELD(arg0, s32*, 0x2A4) == 0)) {
						M2C_FIELD(arg0, s32*, 0x2A4) = 1;
						if ((s32)M2C_FIELD(arg0, s32*, 0x278) != -1) {
							fn_800E1208(0xF, 0);
							M2C_FIELD(arg0, s32*, 0x278) = -1;
						}
						temp_r3_3 = M2C_FIELD(arg0, void**, 0x38);
						M2C_FIELD(temp_r3_3, s32*, 0x34)
						    = (s32)(M2C_FIELD(temp_r3_3, s32*, 0x34) & 0xFFFFFFEF);
						if ((u32)lbl_8042C388 != 0U) {
							fn_800B4A38(0x4014, (u8*)arg0 + 0x140, 0, 1, 0, 0);
							return;
						}
					}
					break;
				case 3: /* switch 4 */
					temp_r3_4 = M2C_FIELD(arg0, void**, 0x38);
					M2C_FIELD(temp_r3_4, s32*, 0x34)
					    = (s32)(M2C_FIELD(temp_r3_4, s32*, 0x34) | 0x10);
					return;
			}
			break;
		case 29:            /* switch 1 */
			switch (arg2) { /* switch 5; irregular */
				case 0:     /* switch 5 */
					if ((s32)M2C_FIELD(arg0, s32*, 0x278) != -1) {
						fn_800E1208(0xF, 0);
						M2C_FIELD(arg0, s32*, 0x278) = -1;
					}
					M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(void*), 0x3C)(arg0);
					return;
				case 1: /* switch 5 */
					M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
					return;
			}
			break;
		case 26:            /* switch 1 */
			switch (arg2) { /* switch 6; irregular */
				case 0:     /* switch 6 */
					M2C_FIELD(arg0, s32*, 0x290) = 0;
					return;
				case 1: /* switch 6 */
					M2C_FIELD(arg0, s32*, 0x290) = (s32)(M2C_FIELD(arg0, s32*, 0x290) + 0x550);
					M2C_FIELD(arg0, f32*, 0x294)
					    = (f32)(20.0f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x290)));
					M2C_FIELD(arg0, f32*, 0x298) = (f32)(20.0f
					    * fn_800D7B00((s32)(0.5f * (f32)M2C_FIELD(arg0, s32*, 0x290)), 0.5f));
					return;
			}
			break;
		case 36:            /* switch 1 */
			switch (arg2) { /* switch 7; irregular */
				case 0:     /* switch 7 */
					M2C_FIELD(arg0, s32*, 0x290) = 0x5A;
					M2C_FIELD(arg0, s32*, 0xD4)  = 3;
					M2C_FIELD(arg0, s32*, 0x2D0) = (s32)M2C_FIELD(arg0, s32*, 0x238);
					if ((u32)lbl_8042C6D0 == 0U) {
						fn_8011C6EC();
					}
					fn_8011C188(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x238));
					M2C_FIELD(arg0, s32*, 0x29C) = 0;
					M2C_FIELD(arg0, u16*, 0x30)  = (u16)(M2C_FIELD(arg0, u16*, 0x30) | 0x200);
					return;
				case 1: /* switch 7 */
					temp_r0_5                    = M2C_FIELD(arg0, s32*, 0x290) - 1;
					M2C_FIELD(arg0, s32*, 0x290) = temp_r0_5;
					if (temp_r0_5 == 0) {
						if ((u32)M2C_FIELD(arg0, u32*, 0x2F0) != 0U) {
							fn_8010B074();
						}
						if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x2F4) != NULL) {
							fn_8010AFF8((M2C_UNK*)2U);
							fn_8010B208(
							    M2C_FIELD(arg0, M2C_UNK**, 0x2F4), &lbl_8_rodata_1704, 0.0f, 0.0f);
						}
					}
					sp8     = M2C_FIELD(arg0, s32*, 0x2F8);
					spC     = M2C_FIELD(arg0, f32*, 0x2FC);
					sp10    = M2C_FIELD(arg0, s32*, 0x300);
					temp_f1 = spC;
					spC     = temp_f1 + 2.0f;
					if ((fn_800A34D0(arg0, &sp8, temp_f1) != 0)
					    && ((s32)M2C_FIELD(arg0, s32*, 0x29C) == 0)) {
						M2C_FIELD(arg0, s32*, 0x29C) = 1;
						temp_f1_2                    = M2C_FIELD(arg0, f32*, 0x1A4) - 1.0f;
						M2C_FIELD(arg0, f32*, 0x1A4) = temp_f1_2;
						if (temp_f1_2 < 0.0f) {
							M2C_FIELD(arg0, f32*, 0x1A4) = 0.0f;
						}
						M2C_FIELD(arg0, s16*, 0x2E)  = (s16)M2C_FIELD(arg0, f32*, 0x1A4);
						M2C_FIELD(arg0, s32*, 0x230) = fn_800AB104(M2C_FIELD(arg0, s32*, 0x2D0));
						return;
					}
					break;
				case 3: /* switch 7 */
					M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) & 0xFFFFFDFF);
					return;
			}
			break;
		case 37:            /* switch 1 */
			switch (arg2) { /* switch 8; irregular */
				case 0:     /* switch 8 */
					if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x2F4) != NULL) {
						fn_8010B074();
					}
					M2C_FIELD(arg0, s32*, 0xD4) = 0;
					return;
				case 1: /* switch 8 */
					var_r4 = 1;
					if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {

					} else {
						temp_f2                      = M2C_FIELD(arg0, f32*, 0x1C4);
						M2C_FIELD(arg0, f32*, 0x144) = (f32)(M2C_FIELD(arg0, f32*, 0x144) + 0.2f);
						M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
						if (M2C_FIELD(arg0, f32*, 0x144) == temp_f2) {
							M2C_FIELD(arg0, f32*, 0x144) = temp_f2;
						} else {
							var_r4 = 0;
						}
					}
					if (var_r4 != 0) {
						M2C_FIELD(arg0, s32*, 0x248) = 2;
						return;
					}
					break;
			}
			break;
		case 45: /* switch 1 */
			fn_8_9A218(arg0, arg2);
			return;
		case 46: /* switch 1 */
			fn_8_99D64(arg0, arg2);
			return;
		case 47: /* switch 1 */
			fn_8_99BB8(arg0, arg2);
			return;
		case 21:            /* switch 1 */
			switch (arg2) { /* switch 9; irregular */
				case 0:     /* switch 9 */
					temp_r0_6 = M2C_FIELD(arg0, s32*, 0x278);
					if (temp_r0_6 != -1) {
						temp_r3_5 = *(void**)((u8*)&lbl_802AD070 + (temp_r0_6 * 4));
						if (temp_r3_5 != NULL) {
							if ((s16)M2C_FIELD(temp_r3_5, s16*, 0x6F0) == 0x26) {
								fn_80043DEC();
							}
							M2C_FIELD(arg0, s32*, 0x278) = -1;
						}
					}
					M2C_FIELD(arg0, f32*, 0x2C0) = 1.0f;
					M2C_FIELD(arg0, f32*, 0x2BC) = 1.0f;
					M2C_FIELD(arg0, f32*, 0x2B8) = 1.0f;
					M2C_FIELD(arg0, f32*, 0x2CC) = 0.0f;
					M2C_FIELD(arg0, f32*, 0x2C8) = 0.0f;
					M2C_FIELD(arg0, f32*, 0x2C4) = 0.0f;
					M2C_FIELD(arg0, s32*, 0xD4)  = 0;
					return;
				case 1: /* switch 9 */
					M2C_FIELD(arg0, f32*, 0x2C4) = (f32)(M2C_FIELD(arg0, f32*, 0x2C4) + -0.05f);
					M2C_FIELD(arg0, f32*, 0x2C8) = (f32)(M2C_FIELD(arg0, f32*, 0x2C8)
					    + M2C_FIELD(&lbl_8_rodata_16B0, f32*, 4));
					M2C_FIELD(arg0, f32*, 0x2CC) = (f32)(M2C_FIELD(arg0, f32*, 0x2CC)
					    + M2C_FIELD(&lbl_8_rodata_16B0, f32*, 8));
					M2C_FIELD(arg0, f32*, 0x2B8)
					    = (f32)(M2C_FIELD(arg0, f32*, 0x2B8) + M2C_FIELD(arg0, f32*, 0x2C4));
					M2C_FIELD(arg0, f32*, 0x2BC)
					    = (f32)(M2C_FIELD(arg0, f32*, 0x2BC) + M2C_FIELD(arg0, f32*, 0x2C8));
					M2C_FIELD(arg0, f32*, 0x2C0)
					    = (f32)(M2C_FIELD(arg0, f32*, 0x2C0) + M2C_FIELD(arg0, f32*, 0x2CC));
					if (M2C_FIELD(arg0, f32*, 0x2B8) < 0.0f) {
						fn_8005BC04((u8*)arg0 + 0xB0);
						M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
						return;
					}
					break;
			}
			break;
		case 6:             /* switch 1 */
			switch (arg2) { /* switch 10; irregular */
				case 0:     /* switch 10 */
					M2C_FIELD(arg0, f32*, 0x27C) = 0.15f;
					M2C_FIELD(arg0, f32*, 0x1B8) = (f32)M2C_FIELD(arg0, f32*, 0x27C);
					M2C_FIELD(arg0, s32*, 0xD4)  = 0;
					M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x1C0);
					M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x1C4);
					M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x1C8);
					M2C_FIELD(arg0, s32*, 0x2D4) = 0;
					return;
				case 1: /* switch 10 */
					if ((s32)M2C_FIELD(arg0, s32*, 0x2D4) == 0) {
						if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {
							var_r0 = 0;
						} else {
							temp_r30_3                   = fn_800A5A54();
							M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
							    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
							if (temp_r30_3 < 0x80) {
								M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
								var_r0                       = 1;
							} else {
								var_r0 = 0;
							}
						}
						if (var_r0 != 0) {
							M2C_FIELD(arg0, s32*, 0x2D4) = 1;
						}
					}
					if ((s32)M2C_FIELD(arg0, s32*, 0x2D4) != 0) {
						temp_f31_2 = M2C_FIELD(arg0, f32*, 0x27C);
						var_r29_2  = 0;
						if ((s32)M2C_FIELD(arg0, s32*, 0x574) == 0) {

						} else {
							if ((fn_800A5AC0(arg0) < 2.0f)
							    || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
								fn_800A4668(arg0);
								var_r29_2 = 1;
							} else {
								fn_800A4A8C(arg0, temp_f31_2);
							}
							M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
							fn_800A5C6C(arg0, 0xF00);
							if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
							    && (M2C_FIELD(arg0, f32*, 0x15C)
							        < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
								M2C_FIELD(arg0, f32*, 0x15C) = 0.0f;
							}
							if (fn_800A5888(arg0, &lbl_8_rodata_1728, -1.0f) != 0) {
								fn_800A5B50(arg0, 0xF00);
								var_r29_2 = 2;
							}
						}
						if (var_r29_2 == 1) {
							M2C_FIELD(arg0, s32*, 0x248) = 2;
							return;
						}
					}
					break;
			}
			break;
		case 9: /* switch 1 */
			if (arg2 != NULL) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x2F4) != NULL) {
					fn_8010B074();
				}
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
			}
			break;
	}
}

void fn_8_9B69C(void* arg0)
{
	M2C_UNK sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f3;

	sp8     = 0.0f;
	spC     = 0.0f;
	sp10    = M2C_FIELD(arg0, f32*, 0x254);
	temp_f3 = (160.0f * (0.000030517578f * (f32)fn_801C28D8(&lbl_8_rodata_1704))) - 80.0f;
	fn_80195A74(&sp14, &lbl_80239984, 0,
	    180.0f + (0.005493164f * (f32)M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x10))
	        + temp_f3,
	    180.0f, temp_f3);
	fn_80196050(&sp14, M2C_FIELD(arg0, void**, 0xB0), 2);
	fn_8019941C(&sp8, &sp8, 1, &sp14);
	M2C_FIELD(arg0, f32*, 0x1CC) = sp8;
	M2C_FIELD(arg0, f32*, 0x1D0) = spC;
	M2C_FIELD(arg0, f32*, 0x1D4) = sp10;
	M2C_FIELD(arg0, f32*, 0x254) = (f32)(M2C_FIELD(arg0, f32*, 0x254) * -1.0f);
}

void fn_8_9B7E0(void* arg0)
{
	RwFrame* temp_r30;
	RwFrame* temp_r30_2;
	RwFrame* temp_r30_3;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r4;

	if ((s32)M2C_FIELD(arg0, s32*, 0x28C) != 0) {
		temp_r4 = M2C_FIELD(arg0, void**, 0x2D8);
		if ((temp_r4 != NULL) && ((u32)M2C_FIELD(arg0, u32*, 0x270) != 0U)) {
			temp_r30 = M2C_FIELD(temp_r4, RwFrame**, 4);
			fn_8019ECCC(temp_r30, fn_8019E8EC(), 0);
		}
		temp_r3 = M2C_FIELD(arg0, void**, 0x2DC);
		if ((temp_r3 != NULL) && ((u32)M2C_FIELD(arg0, u32*, 0x268) != 0U)) {
			temp_r30_2 = M2C_FIELD(temp_r3, RwFrame**, 4);
			fn_8019ED68(temp_r30_2, &lbl_80239984, 0, 180.0f);
			fn_8019ECCC(temp_r30_2, fn_8019E8EC(M2C_FIELD(arg0, u32*, 0x268)), 2);
		}
		temp_r3_2 = M2C_FIELD(arg0, void**, 0x2E0);
		if ((temp_r3_2 != NULL) && ((u32)M2C_FIELD(arg0, u32*, 0x26C) != 0U)) {
			temp_r30_3 = M2C_FIELD(temp_r3_2, RwFrame**, 4);
			fn_8019ED68(temp_r30_3, &lbl_80239984, 0, 180.0f);
			fn_8019ECCC(temp_r30_3, fn_8019E8EC(M2C_FIELD(arg0, u32*, 0x26C)), 2);
		}
		M2C_FIELD(arg0, s32*, 0x284) = (s32)(M2C_FIELD(arg0, s32*, 0x284) + 0x1000);
		M2C_FIELD(arg0, f32*, 0x288)
		    = (f32)(0.5f + (0.5f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x284))));
	}
}

void fn_8_9B920(TObject* arg0)
{
	s32 sp10;
	s32 sp8;
	RwFrame* temp_r31;
	TEnemyParalysis* temp_r3_2;
	f32 temp_f1;
	f32 temp_f2;
	f32 temp_f2_2;
	s32 temp_r0;
	s32 temp_r3_3;
	s32 temp_r3_4;
	s32 temp_r3_5;
	void* temp_r3;
	void* temp_r3_6;
	void* temp_r3_7;

	temp_f2 = arg0->unk294;
	if ((f32)fabs(temp_f2) > 0.001f) {
		arg0->unk294 = temp_f2 * 0.98f;
	}
	temp_f2_2 = arg0->unk298;
	if ((f32)fabs(temp_f2_2) > 0.001f) {
		arg0->unk298 = temp_f2_2 * 0.98f;
	}
	temp_r3 = arg0->unkE8;
	if (temp_r3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3, RwFrame**, 4);
		temp_r0  = arg0->unk19C;
		if ((temp_r0 == 0x24) && (temp_r3_2 = arg0->unk244, ((temp_r3_2 == NULL) == 0))) {
			Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(
			    temp_r3_2, temp_r31, (RwOpCombineType)0);
			fn_8019ED68(temp_r31, &lbl_80239990, 2, arg0->unk298);
			fn_8019ED68(temp_r31, &lbl_80239978, 2, arg0->unk294);
			fn_8019ED68(temp_r31, &lbl_80239984, 2, 180.0f + (0.005493164f * (f32)arg0->unk150),
			    0.005493164f, 180.0f);
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
			SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(
			    arg0->unk244, (RwV3d*)((u8*)arg0 + 0x140), (sAngle*)((u8*)arg0 + 0x14C));
		} else if (temp_r0 == 0x15) {
			fn_8019EC30(temp_r31, (f32*)((u8*)arg0 + 0x2B8), 0);
			fn_8019ED68(temp_r31, &lbl_80239990, 2, arg0->unk298);
			fn_8019ED68(temp_r31, &lbl_80239978, 2, arg0->unk294);
			fn_8019ED68(temp_r31, &lbl_80239984, 2, 180.0f + (0.005493164f * (f32)arg0->unk150),
			    0.005493164f, 180.0f);
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
		} else {
			fn_8019ED68(temp_r31, &lbl_80239990, 0, arg0->unk298);
			fn_8019ED68(temp_r31, &lbl_80239978, 2, arg0->unk294);
			fn_8019ED68(temp_r31, &lbl_80239984, 2, 180.0f + (0.005493164f * (f32)arg0->unk150),
			    0.005493164f, 180.0f);
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
		}
		if ((u32)arg0->unk2EC == 0U) {
			arg0->unk2EC = fn_8011B5A8(temp_r31, 0x456);
		}
	}
	if ((u32)arg0->unk268 == 0U) {
		temp_r3_3 = fn_8005D9A0(arg0->unkEC, 0x3EB);
		if (temp_r3_3 != -1) {
			arg0->unk268
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_3 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk26C == 0U) {
		temp_r3_4 = fn_8005D9A0(arg0->unkEC, 0x3EC);
		if (temp_r3_4 != -1) {
			arg0->unk26C
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_4 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk270 == 0U) {
		temp_r3_5 = fn_8005D9A0(arg0->unkEC, 0x3E8);
		if (temp_r3_5 != -1) {
			arg0->unk270
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_5 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)(M2C_FIELD(arg0->unkB0, s32*, 0x18) & 0x20000) != 0) {
		if ((s32)(arg0->unk106 & 2) != 0) {
			arg0->unk31C = arg0->unk118;
			arg0->unk324 = arg0->unk120;
			arg0->unk2FC = 0.3f + arg0->unk144;
		} else {
			temp_f1      = fn_800D8BC4((u8*)arg0 + 0x140, &sp8, 1);
			arg0->unk2FC = temp_f1;
			if (temp_f1 != -1000000.0f) {
				arg0->unk2F8 = arg0->unk140;
				arg0->unk2FC += 0.3f;
				arg0->unk300 = arg0->unk148;
				arg0->unk31C = 0.005493164f * (f32)sp8;
				arg0->unk324 = 0.005493164f * (f32)sp10;
			}
		}
		arg0->unk320 = 180.0f + (0.005493164f * (f32)arg0->unk150);
		arg0->unk2F8 = arg0->unk140;
		arg0->unk300 = arg0->unk148;
		if ((u32)arg0->unk268 != 0U) {
			temp_r3_6    = fn_8019E8EC();
			arg0->unk304 = M2C_FIELD(temp_r3_6, f32*, 0x30);
			arg0->unk308 = M2C_FIELD(temp_r3_6, f32*, 0x34);
			arg0->unk30C = M2C_FIELD(temp_r3_6, f32*, 0x38);
			arg0->unk308 = arg0->unk2FC;
		}
		if ((u32)arg0->unk26C != 0U) {
			temp_r3_7    = fn_8019E8EC();
			arg0->unk310 = M2C_FIELD(temp_r3_7, f32*, 0x30);
			arg0->unk314 = M2C_FIELD(temp_r3_7, f32*, 0x34);
			arg0->unk318 = M2C_FIELD(temp_r3_7, f32*, 0x38);
			arg0->unk314 = arg0->unk2FC;
		}
	}
}

void fn_8_9BE6C(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x2E8) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x2E8) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2E4) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x2E4) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2E0) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x2E0) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2DC) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x2DC) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2D8) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x2D8) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

void fn_8_9BF24(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0x2E8) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2E8) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x2E4) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2E4) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x2E0) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2E0) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x2DC) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2DC) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x2D8) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2D8) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	M2C_FIELD(arg0, void**, 0xE8)  = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 0));
	M2C_FIELD(arg0, void**, 0x2D8) = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 4));
	M2C_FIELD(arg0, void**, 0x2DC) = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 8));
	M2C_FIELD(arg0, void**, 0x2E0) = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 0xC));
	M2C_FIELD(arg0, void**, 0x2E4) = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 0x10));
	M2C_FIELD(arg0, void**, 0x2E8) = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 0x14));
}

void fn_8_9C054(TObject* arg0)
{
	M2C_UNK sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f3;
	s32 temp_r0;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r4;

	temp_r4      = M2C_FIELD(arg0->unkB0, void**, 0x2C);
	arg0->unk57C = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0);
	arg0->unk580 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 1);
	arg0->unk584 = M2C_FIELD(temp_r4, s32*, 0x10);
	arg0->unk588 = M2C_FIELD(temp_r4, f32*, 0x14);
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
	arg0->unk254 = -arg0->unk210;
	sp8          = 0.0f;
	spC          = 0.0f;
	sp10         = arg0->unk254;
	temp_f3 = (160.0f * (0.000030517578f * (f32)fn_801C28D8(&lbl_8_rodata_1710, temp_r4, 0.0f)))
	    - 80.0f;
	fn_80195A74(&sp14, &lbl_80239984, 0,
	    180.0f + (0.005493164f * (f32)M2C_FIELD(arg0->unkB0, s32*, 0x10)) + temp_f3, 180.0f,
	    temp_f3);
	fn_80196050(&sp14, arg0->unkB0, 2);
	fn_8019941C(&sp8, &sp8, 1, &sp14);
	arg0->unk1CC = sp8;
	arg0->unk1D0 = spC;
	arg0->unk1D4 = sp10;
	arg0->unk254 *= -1.0f;
	arg0->unk258 = arg0->unk1CC;
	arg0->unk25C = arg0->unk1D0;
	arg0->unk260 = arg0->unk1D4;
	arg0->unk180 = 0x200;
	temp_r0      = arg0->unk57C;
	switch (temp_r0) { /* irregular */
		case 0:
			arg0->unk250 = 3.0f;
			arg0->unk24C = arg0->unk250;
			return;
		case 1:
			arg0->unk250 = 6.0f;
			arg0->unk24C = arg0->unk250;
			return;
		default:
			arg0->unk250 = 3.0f;
			arg0->unk24C = arg0->unk250;
			return;
	}
}

void fn_8_9C318(TObject* arg0)
{
	TObject* var_r5;
	s32 var_ctr;

	arg0->unk268 = 0U;
	arg0->unk26C = 0U;
	arg0->unk270 = 0U;
	arg0->unk2E4 = NULL;
	arg0->unk300 = 0.0f;
	arg0->unk2FC = 0.0f;
	arg0->unk2F8 = 0.0f;
	arg0->unk30C = 0.0f;
	arg0->unk308 = 0.0f;
	arg0->unk304 = 0.0f;
	arg0->unk318 = 0.0f;
	arg0->unk314 = 0.0f;
	arg0->unk310 = 0.0f;
	arg0->unk324 = 0.0f;
	arg0->unk320 = 0.0f;
	arg0->unk31C = 0.0f;
	arg0->unk274 = -1;
	arg0->unk27C = 0.15f;
	arg0->unk280 = 0;
	arg0->unk2D8 = NULL;
	arg0->unk2DC = NULL;
	arg0->unk2E0 = NULL;
	arg0->unk284 = 0;
	arg0->unk288 = 0.0f;
	arg0->unk28C = 0;
	arg0->unk328 = 0xA;
	arg0->unk32C = 0;
	var_r5       = arg0;
	var_ctr      = 4;
	do {
		var_r5->unk338 = 0.0f;
		var_r5->unk334 = 0.0f;
		var_r5->unk330 = 0.0f;
		var_r5->unk344 = 0.0f;
		var_r5->unk33C = 0.0f;
		var_r5->unk340 = -0.4f;
		var_r5->unk348 = 0.0f;
		var_r5->unk34C = 0.2f;
		var_r5->unk350 = 0.0f;
		var_r5->unk35C = 0.0f;
		var_r5->unk358 = 0.0f;
		var_r5->unk354 = 0.0f;
		var_r5->unk368 = 0.0f;
		var_r5->unk360 = 0.0f;
		var_r5->unk364 = -0.4f;
		var_r5->unk36C = 0.0f;
		var_r5->unk370 = 0.2f;
		var_r5->unk374 = 0.0f;
		var_r5->unk380 = 0.0f;
		var_r5->unk37C = 0.0f;
		var_r5->unk378 = 0.0f;
		var_r5->unk38C = 0.0f;
		var_r5->unk384 = 0.0f;
		var_r5->unk388 = -0.4f;
		var_r5->unk390 = 0.0f;
		var_r5->unk394 = 0.2f;
		var_r5->unk398 = 0.0f;
		var_r5->unk3A4 = 0.0f;
		var_r5->unk3A0 = 0.0f;
		var_r5->unk39C = 0.0f;
		var_r5->unk3B0 = 0.0f;
		var_r5->unk3A8 = 0.0f;
		var_r5->unk3AC = -0.4f;
		var_r5->unk3B4 = 0.0f;
		var_r5->unk3B8 = 0.2f;
		var_r5->unk3BC = 0.0f;
		var_r5 += 0x90;
		var_ctr -= 1;
	} while (var_ctr != 0);
	arg0->unk298 = 0.0f;
	arg0->unk294 = 0.0f;
	arg0->unk2F0 = 0U;
	arg0->unk2F4 = 0U;
	arg0->unk244 = NULL;
	arg0->unk570 = 0;
	arg0->unk240 = NULL;
	arg0->unk2B4 = 0;
	arg0->unk248 = 0;
	arg0->unk2D4 = 0;
	arg0->unk574 = 1;
	arg0->unk578 = 1;
	arg0->unk2E8 = NULL;
	arg0->unk2EC = 0U;
	arg0->unk278 = -1;
}

void* fn_8_9C4BC(void* arg0, s16 arg1)
{
	s32 temp_cr0_eq;
	s32 temp_r0;
	void** temp_r3_3;
	void* temp_r3;
	void* temp_r3_2;

	if (arg0 != NULL) {
		M2C_FIELD(arg0, M2C_UNK**, 0x18) = &lbl_8_data_15854;
		M2C_FIELD(arg0, void**, 0xB4)    = (void*)(&lbl_8_data_15854 + 0x2C);
		temp_r0                          = M2C_FIELD(arg0, s32*, 0x278);
		if (temp_r0 != -1) {
			temp_r3 = *(void**)((u8*)&lbl_802AD070 + (temp_r0 * 4));
			if (temp_r3 != NULL) {
				if ((s16)M2C_FIELD(temp_r3, s16*, 0x6F0) == 0x26) {
					fn_80043DEC();
				}
				M2C_FIELD(arg0, s32*, 0x278) = -1;
			}
		}
		temp_r3_2 = M2C_FIELD(arg0, void**, 0x244);
		if (temp_r3_2 != NULL) {
			M2C_FIELD(temp_r3_2, u16*, 4)  = (u16)(M2C_FIELD(temp_r3_2, u16*, 4) | 1);
			M2C_FIELD(arg0, void**, 0x244) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2F0) != 0U) {
			fn_8010AFE4();
			M2C_FIELD(arg0, u32*, 0x2F0) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2F4) != 0U) {
			fn_8010AFE4();
			M2C_FIELD(arg0, u32*, 0x2F4) = 0U;
		}
		temp_r3_3   = M2C_FIELD(arg0, void***, 0x240);
		temp_cr0_eq = temp_r3_3 == NULL;
		if (temp_cr0_eq == 0) {
			if (temp_cr0_eq == 0) {
				M2C_FIELD(*temp_r3_3, M2C_UNK(**)(M2C_UNK), 8)(1);
			}
			M2C_FIELD(arg0, void***, 0x240) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2E8) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x2E8) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2E4) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x2E4) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2E0) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x2E0) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2DC) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x2DC) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2D8) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x2D8) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0xE8) = 0U;
		}
		__dt__10HAnimClassFv((HAnimClass*)((u8*)arg0 + 0x240), 0);
		fn_800A7088(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_9C694(TObject* arg0)
{
	TEnemyParalysis* temp_r3_2;
	TEnemyParalysis* var_r0_3;
	f32 temp_f0;
	s32 temp_r0;
	void** var_r0;
	void** var_r0_2;
	void** var_r0_4;
	void* temp_r3;

	fn_800A714C();
	__ct__10HAnimClassFv((HAnimClass*)((u8*)arg0 + 0x240));
	arg0->unk18 = &lbl_8_data_15854;
	arg0->unkB4 = &lbl_8_data_15854 + 0x2C;
	__construct_array((M2C_UNK*)((u8*)arg0 + 0x330), &fn_8_9D45C, (M2C_UNK*)NULL, 0x24, 0x10);
	arg0->unk0  = (M2C_UNK*)lbl_8_data_15850;
	arg0->unk1E = 0x58C;
	fn_8_9C318(arg0);
	fn_8_9C054(arg0);
	arg0->unk188 &= 0xFFFF3FFF;
	arg0->unk188 |= 0x8000;
	arg0->unk160 = 0.0f;
	arg0->unk15C = 0.0f;
	arg0->unk158 = 0.0f;
	arg0->unk188 &= 0xFFEFCFFF;
	arg0->unk188 |= 0x100000;
	arg0->unk188 |= 0x10;
	temp_f0      = arg0->unk24C;
	arg0->unk1A4 = temp_f0;
	arg0->unk2E  = (s16)temp_f0;
	arg0->unk1A0 = 3.0f;
	arg0->unk2C  = 3;
	if ((void*)arg0->unk2E8 != NULL) {
		fn_80150958();
		arg0->unk2E8 = NULL;
	}
	if ((void*)arg0->unk2E4 != NULL) {
		fn_80150958();
		arg0->unk2E4 = NULL;
	}
	if ((void*)arg0->unk2E0 != NULL) {
		fn_80150958();
		arg0->unk2E0 = NULL;
	}
	if ((void*)arg0->unk2DC != NULL) {
		fn_80150958();
		arg0->unk2DC = NULL;
	}
	if ((void*)arg0->unk2D8 != NULL) {
		fn_80150958();
		arg0->unk2D8 = NULL;
	}
	if ((void*)arg0->unkE8 != NULL) {
		fn_80150958();
		arg0->unkE8 = NULL;
	}
	arg0->unkE8  = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 0));
	arg0->unk2D8 = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 4));
	arg0->unk2DC = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 8));
	arg0->unk2E0 = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 0xC));
	arg0->unk2E4 = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 0x10));
	arg0->unk2E8 = fn_80150588(M2C_FIELD(&lbl_8_bss_1780, s32*, 0x14));
	fn_8_9B920(arg0);
	fn_8005D5C8(arg0->unkE8, ((u32)(M2C_FIELD(arg0->unkB0, s32*, 0x18) & 0x1C0000) >> 0x12U) + 8);
	arg0->unkE4 = &lbl_8_data_15608;
	arg0->unkD4 = 0;
	if (fn_8005B8D8(&arg0->unkB0) == 0) {
		fn_8003C200(&arg0->unk28, &lbl_8_data_156BC, 2, 3);
		arg0->unk88                    = arg0->unk140;
		arg0->unk8C                    = arg0->unk144;
		arg0->unk90                    = arg0->unk148;
		temp_r3                        = arg0->unk38;
		M2C_FIELD(temp_r3, s32*, 0x34) = (s32)(M2C_FIELD(temp_r3, s32*, 0x34) | 0x10);
	}
	arg0->unk130 = 1.0f;
	arg0->unk134 = 0.8f;
	arg0->unk240 = NULL;
	temp_r0      = arg0->unk57C;
	switch (temp_r0) { /* irregular */
		case 0:
			var_r0 = fn_80057644(0x1C);
			if (var_r0 != NULL) {
				var_r0 = fn_8_9EB28();
			}
			arg0->unk240 = var_r0;
			break;
		case 1:
			var_r0_2 = fn_80057644(0x1C);
			if (var_r0_2 != NULL) {
				var_r0_2 = fn_8_9DCE8();
			}
			arg0->unk240 = var_r0_2;
			break;
	}
	if ((void**)arg0->unk240 != NULL) {
		fn_8_9E43C(arg0);
	}
	if ((s32)arg0->unk580 == 0) {
		arg0->unk2F4 = fn_8010B708(8);
		if ((u32)arg0->unk2F4 != 0U) {
			fn_8010B208(&lbl_8_rodata_1704, NULL, 0.0f);
		}
	} else {
		arg0->unk2F4 = fn_8010B708(1);
	}
	arg0->unk2F0 = fn_8010B708(0);
	temp_r3_2    = fn_80018A34(lbl_8042C148, 0x74);
	var_r0_3     = temp_r3_2;
	if (var_r0_3 != NULL) {
		var_r0_3
		    = __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(temp_r3_2, lbl_8042C10C, NULL);
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

TObject* fn_8_9CA9C(void)
{
	TObject* var_r0;

	var_r0 = (TObject*)fn_80018A34(lbl_8042C148, 0x58C);
	if (var_r0 != NULL) {
		var_r0 = fn_8_9C694(lbl_8042C10C);
	}
	return var_r0;
}

void fn_8_9CAF0(void* arg1)
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
	var_r4  = &lbl_8_data_15838;
	if ((s8)temp_r0 < (s8)lbl_8_data_15838) {

	} else {
		var_r4 = &lbl_8_data_15839;
		if ((s8)temp_r0 > (s8)lbl_8_data_15839) {

		} else {
			var_r4 = temp_r3;
		}
	}
	M2C_FIELD(temp_r3, u8*, 0) = (u8)(s8)*var_r4;
	temp_r0_2                  = M2C_FIELD(temp_r3, u8*, 1);
	var_r4_2                   = &lbl_8_data_1583A;
	if ((s8)temp_r0_2 < (s8)lbl_8_data_1583A) {

	} else {
		var_r4_2 = &lbl_8_data_1583B;
		if ((s8)temp_r0_2 > (s8)lbl_8_data_1583B) {

		} else {
			var_r4_2 = temp_r3 + 1;
		}
	}
	M2C_FIELD(temp_r3, u8*, 1) = (u8)(s8)*var_r4_2;
	temp_f1                    = M2C_FIELD(temp_r3, f32*, 4);
	var_r4_3                   = &lbl_8_rodata_178C;
	if (temp_f1 < 0.0f) {

	} else {
		var_r4_3 = &lbl_8_rodata_1790;
		if (temp_f1 > 10000.0f) {

		} else {
			var_r4_3 = (f32*)(temp_r3 + 4);
		}
	}
	M2C_FIELD(temp_r3, f32*, 4) = (f32)*var_r4_3;
	temp_f1_2                   = M2C_FIELD(temp_r3, f32*, 8);
	var_r4_4                    = &lbl_8_rodata_1794;
	if (temp_f1_2 < 0.0f) {

	} else {
		var_r4_4 = &lbl_8_rodata_1798;
		if (temp_f1_2 > 10000.0f) {

		} else {
			var_r4_4 = (f32*)(temp_r3 + 8);
		}
	}
	M2C_FIELD(temp_r3, f32*, 8) = (f32)*var_r4_4;
	temp_r5                     = M2C_FIELD(temp_r3, s32*, 0x10);
	var_r4_5                    = &lbl_8_rodata_179C;
	if (temp_r5 < (s32)lbl_8_rodata_179C) {

	} else {
		var_r4_5 = &lbl_8_rodata_17A0;
		if (temp_r5 > (s32)lbl_8_rodata_17A0) {

		} else {
			var_r4_5 = (s32*)(temp_r3 + 0x10);
		}
	}
	M2C_FIELD(temp_r3, s32*, 0x10) = (s32)*var_r4_5;
	temp_f1_3                      = M2C_FIELD(temp_r3, f32*, 0x14);
	var_r4_6                       = &lbl_8_rodata_17A4;
	if (temp_f1_3 < 0.0f) {

	} else {
		var_r4_6 = lbl_8_rodata_17A8;
		if (temp_f1_3 > 10000.0f) {

		} else {
			var_r4_6 = (f32*)(temp_r3 + 0x14);
		}
	}
	M2C_FIELD(temp_r3, f32*, 0x14) = (f32)*var_r4_6;
	M2C_FIELD(&captureObjectFieldNames, M2C_UNK**, 0)
	    = (M2C_UNK*)lbl_8_data_15818[(s8)M2C_FIELD(temp_r3, u8*, 0)];
	M2C_FIELD(&captureObjectFieldNames, M2C_UNK**, 4)
	    = (M2C_UNK*)lbl_8_data_15830[(s8)M2C_FIELD(temp_r3, u8*, 1)];
}

void captureObjectUnload(void)
{
	s32 var_r30;
	u8* var_r31;

	var_r30 = 7;
	var_r31 = (u8*)&captureObjectGlobalArray + 0x8C;
	do {
		fn_80113A68(var_r31);
		var_r31 -= 0x14;
		var_r30 -= 1;
	} while (var_r30 >= 0);
	fn_800FE248(7, &lbl_8_data_15608);
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	fn_801007F4(lbl_8042C590, 7);
}

void captureObjectLoad(M2C_UNK arg_sp0)
{
	u32 temp_r3;

	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	fn_8010096C(lbl_8042C590, 7, "en_capture.one");
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	temp_r3 = fn_80100328(lbl_8042C590, 7, 4);
	if (temp_r3 != 0U) {
		fn_8005E00C(6);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1780, u32*, 0) = fn_8010037C(lbl_8042C590, 7, 3);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1780, u32*, 4) = fn_8010037C(lbl_8042C590, 7, 9);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1780, u32*, 8) = fn_8010037C(lbl_8042C590, 7, 0xA);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1780, u32*, 0xC) = fn_8010037C(lbl_8042C590, 7, 0xB);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1780, u32*, 0x10) = fn_8010037C(lbl_8042C590, 7, 0xC);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1780, u32*, 0x14) = fn_8010037C(lbl_8042C590, 7, 7);
		fn_8005D9F4(M2C_FIELD(&lbl_8_bss_1780, u32*, 4), &lbl_8_bss_1780);
		fn_8005D9F4(M2C_FIELD(&lbl_8_bss_1780, u32*, 8));
		fn_8005D9F4(M2C_FIELD(&lbl_8_bss_1780, u32*, 0xC));
		if ((u32)M2C_FIELD(&lbl_8_bss_1780, u32*, 0x14) != 0U) {
			fn_8005DA34();
		}
		fn_800FE274(7, &lbl_8_data_15608);
		fn_80113AA8(&captureObjectGlobalArray, temp_r3, M2C_FIELD(&lbl_8_bss_1780, u32*, 0),
		    &lbl_8_data_1572C, 2);
		fn_80113AA8(&captureObjectGlobalArray + 0x14, temp_r3, M2C_FIELD(&lbl_8_bss_1780, u32*, 0),
		    &lbl_8_data_1575C, 2);
		fn_80113AA8(&captureObjectGlobalArray + 0x28, temp_r3, M2C_FIELD(&lbl_8_bss_1780, u32*, 4),
		    &lbl_8_data_1572C, 2);
		fn_80113AA8(&captureObjectGlobalArray + 0x3C, temp_r3, M2C_FIELD(&lbl_8_bss_1780, u32*, 4),
		    &lbl_8_data_1575C, 2);
		fn_80113AA8(&captureObjectGlobalArray + 0x50, temp_r3, M2C_FIELD(&lbl_8_bss_1780, u32*, 8),
		    &lbl_8_data_1572C, 2);
		fn_80113AA8(&captureObjectGlobalArray + 0x64, temp_r3, M2C_FIELD(&lbl_8_bss_1780, u32*, 8),
		    &lbl_8_data_1575C, 2);
		fn_80113AA8(&captureObjectGlobalArray + 0x78, temp_r3,
		    M2C_FIELD(&lbl_8_bss_1780, u32*, 0xC), &lbl_8_data_1572C, 2);
		fn_80113AA8(&captureObjectGlobalArray + 0x8C, temp_r3,
		    M2C_FIELD(&lbl_8_bss_1780, u32*, 0xC), &lbl_8_data_1575C, 2);
	}
}

void captureObjectCreate(void)
{
	if (fn_80018A34(lbl_8042C148, 0x58C) != NULL) {
		fn_8_9C694(lbl_8042C10C);
	}
}

s32 fn_8_9D1B8(void* arg0)
{
	return (M2C_FIELD(arg0, f32*, 4) < M2C_FIELD(arg0, f32*, 0x20)) == 0;
}

void fn_8_9D1D8(void* arg0)
{
	M2C_FIELD(arg0, f32*, 0)    = (f32)(M2C_FIELD(arg0, f32*, 0) + M2C_FIELD(arg0, f32*, 0xC));
	M2C_FIELD(arg0, f32*, 4)    = (f32)(M2C_FIELD(arg0, f32*, 4) + M2C_FIELD(arg0, f32*, 0x10));
	M2C_FIELD(arg0, f32*, 8)    = (f32)(M2C_FIELD(arg0, f32*, 8) + M2C_FIELD(arg0, f32*, 0x14));
	M2C_FIELD(arg0, f32*, 0x18) = (f32)(M2C_FIELD(arg0, f32*, 0x18) + M2C_FIELD(arg0, f32*, 0x1C));
	if (M2C_FIELD(arg0, f32*, 0x18) > 3.0f) {
		M2C_FIELD(arg0, f32*, 0x18) = 3.0f;
	}
}

void fn_8_9D23C(void* arg0)
{
	M2C_FIELD(arg0, f32*, 8)    = 0.0f;
	M2C_FIELD(arg0, f32*, 4)    = 0.0f;
	M2C_FIELD(arg0, f32*, 0)    = 0.0f;
	M2C_FIELD(arg0, f32*, 0x14) = 0.0f;
	M2C_FIELD(arg0, f32*, 0xC)  = 0.0f;
	M2C_FIELD(arg0, f32*, 0x10) = -0.4f;
	M2C_FIELD(arg0, f32*, 0x18) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x1C) = 0.2f;
	M2C_FIELD(arg0, f32*, 0x20) = 0.0f;
}

void captureObjectRegister(void)
{
	M2C_UNK* temp_r3;

	__construct_array(&captureObjectGlobalArray, &fn_80113C7C, &fn_80113C2C, 0x14, 8);
	__register_global_object(0, captureObjectGlobalArrayDtor, &captureObjectGlobalArrayChain);
	M2C_FIELD(&captureObjectEntry, s32*, 0x14)            = 0;
	M2C_FIELD(&captureObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&captureObjectEntry, M2C_UNK**, 0)          = (M2C_UNK*)"CAPTURE OBJECT";
	M2C_FIELD(&captureObjectEntry, void (**)(M2C_UNK), 4) = captureObjectLoad;
	M2C_FIELD(&captureObjectEntry, void (**)(), 8)        = captureObjectUnload;
	M2C_FIELD(&captureObjectEntry, void (**)(), 0xC)      = captureObjectCreate;
	M2C_FIELD(&captureObjectEntry, s32*, 0x10)            = 0;
	M2C_FIELD(&captureObjectEntry, s32*, 0x14)            = 0x20000;
	M2C_FIELD(&captureObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&captureObjectEntry, s8*, 0x20)             = 0x1E;
	M2C_FIELD(&captureObjectEntry, s16*, 0x1C)            = 0x1520;
	M2C_FIELD(&captureObjectEntry, s16*, 0x1E)            = 4;
	M2C_FIELD(&captureObjectEntry, s8*, 0x21)             = 0;
	temp_r3                                               = (M2C_UNK*)"ccccfffif";
	M2C_FIELD(&captureObjectEntry, M2C_UNK**, 0x24)       = temp_r3;
	M2C_FIELD(&captureObjectEntry, M2C_UNK**, 0x28)       = &captureObjectFieldNames;
	if (temp_r3 != NULL) {
		M2C_FIELD(&captureObjectEntry, s32*, 0x14) = 0x20008;
		return;
	}
	M2C_FIELD(&captureObjectEntry, s32*, 0x14) = 0x20000;
}

void captureObjectGlobalArrayDtor(void)
{
	__destroy_arr(&captureObjectGlobalArray, &fn_80113C2C, 0x14, 8);
}
