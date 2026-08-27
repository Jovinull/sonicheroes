#include "types.h"

typedef s32 M2C_UNK;
typedef void TObject;
typedef void RwFrame;
typedef s32 RwOpCombineType;
typedef void HAnimClass;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

typedef struct TEnemyParalysis {
	/* 0x000 */ s32 unk0;        /* inferred */
	/* 0x004 */ char pad4[0x14]; /* maybe part of unk0[6]? */
	/* 0x018 */ M2C_UNK* unk18;  /* inferred */
	/* 0x01C */ char pad1C[2];
	/* 0x01E */ s16 unk1E;     /* inferred */
	/* 0x020 */ char pad20[8]; /* maybe part of unk1E[5]? */
	/* 0x028 */ M2C_UNK unk28; /* inferred */
	/* 0x028 */ char pad28[4];
	/* 0x02C */ s16 unk2C;         /* inferred */
	/* 0x02E */ s16 unk2E;         /* inferred */
	/* 0x030 */ char pad30[0x58];  /* maybe part of unk2E[0x2D]? */
	/* 0x088 */ f32 unk88;         /* inferred */
	/* 0x08C */ f32 unk8C;         /* inferred */
	/* 0x090 */ f32 unk90;         /* inferred */
	/* 0x094 */ char pad94[0x1C];  /* maybe part of unk90[8]? */
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

extern "C" {

M2C_UNK SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(void*, void*, void*);      /* extern */
M2C_UNK Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(void*, void*, s32); /* extern */
void* __ct__10HAnimClassFv(void*);                                                /* extern */
TEnemyParalysis* __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(
    void*, void*, void*);                                               /* extern */
void* __dt__10HAnimClassFv(...);                                        /* extern */
M2C_UNK fn_800189A4(...);                                               /* extern */
TEnemyParalysis* fn_80018A34(...);                                      /* extern */
M2C_UNK fn_8003C200(...);                                               /* extern */
u32 fn_80057644(...);                                                   /* extern */
s32 fn_8005B8D8(void*);                                                 /* extern */
M2C_UNK fn_8005BF5C(...);                                               /* extern */
M2C_UNK fn_8005D5C8(...);                                               /* extern */
s32 fn_8005D9A0(...);                                                   /* extern */
M2C_UNK fn_8005D9F4(void*);                                             /* extern */
M2C_UNK fn_8005E00C(...);                                               /* extern */
s32 fn_8005EA04(void*);                                                 /* extern */
M2C_UNK fn_8005FD8C(...);                                               /* extern */
void* fn_8006298C(...);                                                 /* extern */
M2C_UNK fn_800A31B8(...);                                               /* extern */
M2C_UNK fn_800A4668(void*);                                             /* extern */
M2C_UNK fn_800A4A8C(...);                                               /* extern */
s32 fn_800A5888(void*, void*, f32);                                     /* extern */
s32 fn_800A5A54(void*);                                                 /* extern */
f32 fn_800A5AC0(...);                                                   /* extern */
M2C_UNK fn_800A5B50(void*, s32);                                        /* extern */
M2C_UNK fn_800A5C6C(void*, s32);                                        /* extern */
M2C_UNK fn_800A7088(...);                                               /* extern */
M2C_UNK fn_800A714C(...);                                               /* extern */
s32 fn_800D7A94(s32, s32, s32);                                         /* extern */
f32 fn_800D7B00(s32);                                                   /* extern */
f32 fn_800D8BC4(void*, void*, s32);                                     /* extern */
M2C_UNK fn_800E1208(...);                                               /* extern */
u32 fn_800FD8A0(...);                                                   /* extern */
M2C_UNK fn_800FE248(s32, void*);                                        /* extern */
M2C_UNK fn_800FE274(s32, void*);                                        /* extern */
u32 fn_80100280(s32, s32, s32);                                         /* extern */
u32 fn_80100328(s32, s32, s32);                                         /* extern */
u32 fn_8010037C(s32, s32, s32);                                         /* extern */
M2C_UNK fn_801007F4(s32, s32);                                          /* extern */
M2C_UNK fn_8010096C(s32, s32, void*);                                   /* extern */
M2C_UNK fn_80100AAC(void);                                              /* extern */
s32 fn_80103324(void*, void*, f32);                                     /* extern */
M2C_UNK fn_8010AFE4(...);                                               /* extern */
s32 fn_8010B708(s32);                                                   /* extern */
void* fn_80150588(...);                                                 /* extern */
M2C_UNK fn_80150958(...);                                               /* extern */
M2C_UNK fn_80195A74(...);                                               /* extern */
M2C_UNK fn_80196050(...);                                               /* extern */
M2C_UNK fn_801990E0(...);                                               /* extern */
M2C_UNK fn_8019941C(...);                                               /* extern */
void* fn_8019E8EC(...);                                                 /* extern */
M2C_UNK fn_8019EB94(...);                                               /* extern */
M2C_UNK fn_8019EC30(...);                                               /* extern */
M2C_UNK fn_8019ED68(...);                                               /* extern */
s32 fn_801C28D8(...);                                                   /* extern */
M2C_UNK fn_8_B0300(...);                                                /* extern */
u32 fn_8_B08F0(...);                                                    /* extern */
void fn_8_AE604(TEnemyParalysis* arg0);                                 /* static */
void fn_8_AEB80(TEnemyParalysis* arg0);                                 /* static */
void fn_8_AEE04(TEnemyParalysis* arg0);                                 /* static */
TEnemyParalysis* fn_8_AF05C(TEnemyParalysis* arg0, s16 arg1, s32 arg2); /* static */
void magicianObjectCreate();                                            /* static */
void magicianObjectLoad();                                              /* static */
void magicianObjectUnload();                                            /* static */
extern M2C_UNK lbl_80239978;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_802AD090;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern u32 lbl_8042C590;
extern M2C_UNK lbl_8_bss_19C8;
extern u32 lbl_8_bss_19D0;
extern s32 lbl_8_bss_1A48;
extern M2C_UNK lbl_8_data_16628;
extern M2C_UNK lbl_8_data_167FC;
extern M2C_UNK lbl_8_data_168C0;
extern u8 lbl_8_data_168C8;
extern u8 lbl_8_data_168C9;
extern s32 lbl_8_data_168E0;
extern M2C_UNK lbl_8_data_1692C;
extern M2C_UNK lbl_8_data_16A30;
extern M2C_UNK lbl_8_data_16A40;
extern M2C_UNK lbl_8_rodata_1A48;
extern f32 lbl_8_rodata_1ABC;
extern f32 lbl_8_rodata_1AC4;
extern f32 lbl_8_rodata_1AC8;
extern f32 lbl_8_rodata_1ACC;
extern f32 lbl_8_rodata_1AE8;
extern f32 lbl_8_rodata_1AEC;
extern f32 lbl_8_rodata_1AF0;
extern f32 lbl_8_rodata_1B10;
extern f32 lbl_8_rodata_1B14;
extern f32 lbl_8_rodata_1B1C;
extern f32 lbl_8_rodata_1B30;
extern f32 lbl_8_rodata_1B34;
extern f32 lbl_8_rodata_1B38;
extern f32 lbl_8_rodata_1B3C;
extern f32 lbl_8_rodata_1B40;
extern f32 lbl_8_rodata_1B44;
extern f32 lbl_8_rodata_1B48;
extern f32 lbl_8_rodata_1B4C;
extern f32 lbl_8_rodata_1B50;
extern f32 lbl_8_rodata_1B54;
extern f32 lbl_8_rodata_1B58;
extern f32 lbl_8_rodata_1B5C;
extern f32 lbl_8_rodata_1B60;
extern s32 lbl_8_rodata_1B64;
extern s32 lbl_8_rodata_1B68;
extern f32 lbl_8_rodata_1B6C;
extern M2C_UNK magicianObjectDisplayName;
extern s32 magicianObjectFieldNames;
extern M2C_UNK magicianObjectFieldTypes;
static M2C_UNK lbl_8_data_16B98;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16BB0;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16BE0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016BED_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16BF0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016C01_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16C04;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016C16_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16C18;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16CA8;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16CB4;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16CC0;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16CD0;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16CE0;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16D04;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016D09_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16D0C;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016D16_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16D18;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16D28;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016D33_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16D34;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016D41_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16D44;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16D54;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016D63_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16D64;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016D6F_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16D70;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016D7F_data; /* unable to generate initializer: unknown type */
static u32 lbl_8_bss_19D4[0x11];
static s32 lbl_8_bss_1A18;
static M2C_UNK magicianObjectEntry;
static f32 lbl_8_rodata_1B70[9]
    = { 10000.0f, 0.0f, 0.0f, 1.5f, 0.0f, 0.0f, 0.0f, 1.5f, 0.0f }; /* const */
static M2C_UNK lbl_8_rodata_1B94; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BA0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BAC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BB8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BC4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BD0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BD4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BD8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BDC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BE0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BE4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BE8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BEC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BF0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BF4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BF8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1BFC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C00; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C04; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C08; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C0C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C10; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C18; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C20; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C24; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C28; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C2C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C30; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C34; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C38; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C3C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C40; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C44; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C48; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C4C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C50; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C64; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C70; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C74; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C78; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C7C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1C80; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CA4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CB8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CC4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CD0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CDC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CE8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CF4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D00; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D10; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D1C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D2C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D3C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D48; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D54; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D58; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D5C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D60; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D64; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D68; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D6C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D70; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D74; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D78; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D7C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D80; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D84; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D88; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D90; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D98; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D9C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DA0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DA4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DA8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DAC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DB0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DB4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DB8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DBC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DC0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DC4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DC8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DCC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DD0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DD4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DD8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DDC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DE0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DE4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DE8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DEC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DF0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DF4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DF8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DFC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E00; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E04; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E08; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E0C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E10; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E14; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E18; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E1C; /* unable to generate initializer: unknown type; const */

void fn_8_ACE24(void* arg0, s32 arg1)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f31;
	s32 temp_r0;
	s32 temp_r30;
	s32 temp_r4;
	void* temp_r3;
	void* temp_r3_2;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, f32*, 0x1B8) = (f32)lbl_8_rodata_1B10;
			return;
		case 1:
			M2C_FIELD(arg0, s32*, 0x27C)
			    = fn_80103324((u8*)arg0 + 0x140, &lbl_8_rodata_1B14, lbl_8_rodata_1B14);
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
				M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
				    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
				if (temp_r30 < 0x80) {
					M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
				}
			}
			temp_r4 = M2C_FIELD(arg0, s32*, 0x27C);
			if (temp_r4 != -1) {
				sp8       = M2C_FIELD(arg0, f32*, 0x140);
				spC       = M2C_FIELD(arg0, f32*, 0x144);
				sp10      = M2C_FIELD(arg0, f32*, 0x148);
				temp_r3_2 = *(void**)((u8*)&lbl_802AD090 + (temp_r4 * 4));
				if (temp_r3_2 != NULL) {
					sp8 -= M2C_FIELD(temp_r3_2, f32*, 0x18);
					spC -= M2C_FIELD(temp_r3_2, f32*, 0x1C);
					sp10 -= M2C_FIELD(temp_r3_2, f32*, 0x20);
				}
				spC = lbl_8_rodata_1AC8;
				fn_801990E0(&sp8, &sp8);
				M2C_FIELD(arg0, f32*, 0x158) = sp8;
				M2C_FIELD(arg0, f32*, 0x15C) = spC;
				M2C_FIELD(arg0, f32*, 0x160) = sp10;
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
				if ((fn_800A5AC0(arg0) < lbl_8_rodata_1AC4)
				    || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
					fn_800A4668(arg0);
				} else {
					fn_800A4A8C(arg0, M2C_FIELD(arg0, f32*, 0x358));
				}
				fn_800A5C6C(arg0, 0xF00);
				if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
				    && (M2C_FIELD(arg0, f32*, 0x15C)
				        < (lbl_8_rodata_1AEC * M2C_FIELD(arg0, f32*, 0x1A8)))) {
					M2C_FIELD(arg0, f32*, 0x15C) = (f32)lbl_8_rodata_1AC8;
				}
				if (fn_800A5888(arg0, &lbl_8_rodata_1AF0, lbl_8_rodata_1AF0) != 0) {
					fn_800A5B50(arg0, 0xF00);
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
				M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) + 0x100);
				temp_f31 = lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x278) * 4);
				M2C_FIELD(arg0, f32*, 0x144)
				    = (f32)((lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x278) * 2))
				        + temp_f31 + M2C_FIELD(arg0, f32*, 0x1C4));
			}
			return;
	}
}

void fn_8_AD0EC(void* arg0, s32 arg1)
{
	f32 temp_f31;
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
			    = fn_80103324((u8*)arg0 + 0x140, &lbl_8_rodata_1B14, lbl_8_rodata_1B14);
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
				M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
				    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
				if (temp_r30 < 0x80) {
					M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
				M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) + 0x100);
				temp_f31 = lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x278) * 4);
				M2C_FIELD(arg0, f32*, 0x144)
				    = (f32)((lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x278) * 2))
				        + temp_f31 + M2C_FIELD(arg0, f32*, 0x1C4));
			}
			return;
	}
}

void fn_8_AD260(void* arg0, s32 arg1)
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
	s32 var_r0_2;
	s32 var_r30;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, f32*, 0x1B8) = (f32)lbl_8_rodata_1AE8;
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 6;
			}
			M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x260);
			M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x264);
			M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x268);
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
				var_r0 = 0;
			} else {
				temp_r30                     = fn_800A5A54(arg0);
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
				M2C_FIELD(arg0, s32*, 0x2B0) = 1;
				return;
			}
			M2C_FIELD(arg0, s32*, 0x2B0) = 0;
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x2B0) != 0) {
				var_r30 = 1;
				if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {

				} else {
					if ((fn_800A5AC0() < lbl_8_rodata_1AC4)
					    || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
						fn_800A4668(arg0);
						var_r30 = 0;
					} else {
						fn_800A4A8C(arg0, M2C_FIELD(arg0, f32*, 0x358));
					}
					fn_800A5C6C(arg0, 0xF00);
					if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
					    && (M2C_FIELD(arg0, f32*, 0x15C)
					        < (lbl_8_rodata_1AEC * M2C_FIELD(arg0, f32*, 0x1A8)))) {
						M2C_FIELD(arg0, f32*, 0x15C) = (f32)lbl_8_rodata_1AC8;
					}
					if (fn_800A5888(arg0, &lbl_8_rodata_1AF0, lbl_8_rodata_1AF0) != 0) {
						fn_800A5B50(arg0, 0xF00);
						var_r30 = 0;
					}
				}
				if (var_r30 == 0) {
					sp8     = lbl_8_rodata_1AC8;
					spC     = lbl_8_rodata_1AC8;
					sp10    = M2C_FIELD(arg0, f32*, 0x25C);
					temp_f3 = (lbl_8_rodata_1B38
					              * (lbl_8_rodata_1ACC * (f32)fn_801C28D8(&lbl_8_rodata_1AC8)))
					    - lbl_8_rodata_1B3C;
					fn_80195A74(&sp14, &lbl_80239984, 0,
					    lbl_8_rodata_1B30
					        + (lbl_8_rodata_1B34
					            * (f32)M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x10))
					        + temp_f3,
					    lbl_8_rodata_1B30, temp_f3);
					fn_80196050(&sp14, M2C_FIELD(arg0, void**, 0xB0), 2);
					fn_8019941C(&sp8, &sp8, 1, &sp14);
					M2C_FIELD(arg0, f32*, 0x1CC) = sp8;
					M2C_FIELD(arg0, f32*, 0x1D0) = spC;
					M2C_FIELD(arg0, f32*, 0x1D4) = sp10;
					M2C_FIELD(arg0, f32*, 0x25C)
					    = (f32)(M2C_FIELD(arg0, f32*, 0x25C) * lbl_8_rodata_1AF0);
					M2C_FIELD(arg0, s32*, 0x2B0) = 0;
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x2B0) == 0) {
				if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
					var_r0_2 = 0;
				} else {
					temp_r30_2                   = fn_800A5A54(arg0);
					M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
					    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
					if (temp_r30_2 < 0x80) {
						M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
						var_r0_2                     = 1;
					} else {
						var_r0_2 = 0;
					}
				}
				if (var_r0_2 != 0) {
					M2C_FIELD(arg0, s32*, 0x2B0) = 1;
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
				M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) + 0x100);
				temp_f31 = lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x278) * 4);
				M2C_FIELD(arg0, f32*, 0x144)
				    = (f32)((lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x278) * 2))
				        + temp_f31 + M2C_FIELD(arg0, f32*, 0x1C4));
				return;
			}
		case 2:
			return;
		case 3:
			M2C_FIELD(arg0, f32*, 0x260) = (f32)M2C_FIELD(arg0, f32*, 0x1CC);
			M2C_FIELD(arg0, f32*, 0x264) = (f32)M2C_FIELD(arg0, f32*, 0x1D0);
			M2C_FIELD(arg0, f32*, 0x268) = (f32)M2C_FIELD(arg0, f32*, 0x1D4);
			break;
	}
}

void fn_8_AD670(void* arg0, s32 arg1)
{
	f32 temp_f31;

	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
				return;
			}
			M2C_FIELD(arg0, s32*, 0xD4) = 6;
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
				M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) + 0x100);
				temp_f31 = lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x278) * 4);
				M2C_FIELD(arg0, f32*, 0x144)
				    = (f32)((lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x278) * 2))
				        + temp_f31 + M2C_FIELD(arg0, f32*, 0x1C4));
			}
			return;
	}
}

/*
Decompilation failure in function fn_8_AD74C:

Found bctr instruction at e_magician.s line 676, but the corresponding jump table is not provided.

Please include it in the input .s file(s), or in an additional file.

*/

void fn_8_AE428(void* arg0)
{
	f32 temp_f31;

	if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
		M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) + 0x100);
		temp_f31 = lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x278) * 4);
		M2C_FIELD(arg0, f32*, 0x144)
		    = (f32)((lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x278) * 2)) + temp_f31
		        + M2C_FIELD(arg0, f32*, 0x1C4));
	}
}

void fn_8_AE4C0(void* arg0)
{
	M2C_UNK sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f3;

	sp8     = lbl_8_rodata_1AC8;
	spC     = lbl_8_rodata_1AC8;
	sp10    = M2C_FIELD(arg0, f32*, 0x25C);
	temp_f3 = (lbl_8_rodata_1B38 * (lbl_8_rodata_1ACC * (f32)fn_801C28D8(&lbl_8_rodata_1AC8)))
	    - lbl_8_rodata_1B3C;
	fn_80195A74(&sp14, &lbl_80239984, 0,
	    lbl_8_rodata_1B30
	        + (lbl_8_rodata_1B34 * (f32)M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x10))
	        + temp_f3,
	    lbl_8_rodata_1B30, temp_f3);
	fn_80196050(&sp14, M2C_FIELD(arg0, void**, 0xB0), 2);
	fn_8019941C(&sp8, &sp8, 1, &sp14);
	M2C_FIELD(arg0, f32*, 0x1CC) = sp8;
	M2C_FIELD(arg0, f32*, 0x1D0) = spC;
	M2C_FIELD(arg0, f32*, 0x1D4) = sp10;
	M2C_FIELD(arg0, f32*, 0x25C) = (f32)(M2C_FIELD(arg0, f32*, 0x25C) * lbl_8_rodata_1AF0);
}

void fn_8_AE604(TEnemyParalysis* arg0)
{
	s32 sp28;
	s32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;
	RwFrame* temp_r31;
	RwFrame* temp_r31_2;
	TEnemyParalysis* temp_r3_2;
	f32 temp_f1;
	f32 temp_f1_2;
	s32 temp_r3_4;
	s32 temp_r3_5;
	void* temp_r3;
	void* temp_r3_3;
	void* temp_r3_6;
	void* temp_r3_7;
	void* temp_r6;

	temp_r3 = arg0->unkE8;
	if (temp_r3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3, RwFrame**, 4);
		if (((s32)arg0->unk19C == 0x24) && (temp_r3_2 = arg0->unk24C, ((temp_r3_2 == NULL) == 0))) {
			Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(
			    temp_r3_2, temp_r31, (RwOpCombineType)0);
			fn_8019EC30(temp_r31, (u8*)arg0 + 0x2B8, 2);
			fn_8019ED68(temp_r31, &lbl_80239990, 2, arg0->unk270);
			fn_8019ED68(temp_r31, &lbl_80239978, 2, arg0->unk26C);
			fn_8019ED68(temp_r31, &lbl_80239984, 2,
			    lbl_8_rodata_1B30 + (lbl_8_rodata_1B34 * (f32)arg0->unk150), lbl_8_rodata_1B34,
			    lbl_8_rodata_1B30);
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
			SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(
			    arg0->unk24C, (u8*)arg0 + 0x140, (u8*)arg0 + 0x14C);
		} else {
			fn_8019EC30(temp_r31, (u8*)arg0 + 0x2B8, 0);
			fn_8019ED68(temp_r31, &lbl_80239990, 2, arg0->unk270);
			fn_8019ED68(temp_r31, &lbl_80239978, 2, arg0->unk26C);
			fn_8019ED68(temp_r31, &lbl_80239984, 2,
			    lbl_8_rodata_1B30 + (lbl_8_rodata_1B34 * (f32)arg0->unk150), lbl_8_rodata_1B34,
			    lbl_8_rodata_1B30);
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
		}
	}
	temp_r3_3 = arg0->unk2FC;
	if (temp_r3_3 != NULL) {
		temp_r31_2 = M2C_FIELD(temp_r3_3, RwFrame**, 4);
		fn_8019EC30(temp_r31_2, (u8*)arg0 + 0x300, 0);
		fn_8019EB94(temp_r31_2, (u8*)arg0 + 0x2C4, 2);
	}
	if ((u32)arg0->unk2E0 == 0U) {
		temp_r3_4 = fn_8005D9A0(arg0->unkEC, 0x3EA);
		if (temp_r3_4 != -1) {
			arg0->unk2E0
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_4 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)arg0->unk2DC == 0U) {
		temp_r3_5 = fn_8005D9A0(arg0->unkEC, 0x3E9);
		if (temp_r3_5 != -1) {
			arg0->unk2DC
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_5 * 0x10)), u32*, 0xC);
		}
	}
	if ((u32)(M2C_FIELD(arg0->unkB0, s32*, 0x18) & 0x20000) != 0) {
		if ((s32)(arg0->unk106 & 2) != 0) {
			arg0->unk2A4 = arg0->unk118;
			arg0->unk2AC = arg0->unk120;
			arg0->unk284 = lbl_8_rodata_1B40 + arg0->unk144;
		} else {
			temp_f1      = fn_800D8BC4((u8*)arg0 + 0x140, &sp20, 1);
			arg0->unk284 = temp_f1;
			if (lbl_8_rodata_1B1C != temp_f1) {
				arg0->unk280 = arg0->unk140;
				arg0->unk284 += lbl_8_rodata_1B40;
				arg0->unk288 = arg0->unk148;
				arg0->unk2A4 = lbl_8_rodata_1B34 * (f32)sp20;
				arg0->unk2AC = lbl_8_rodata_1B34 * (f32)sp28;
			}
		}
		arg0->unk2A8 = lbl_8_rodata_1B30 + (lbl_8_rodata_1B34 * (f32)arg0->unk150);
		arg0->unk280 = arg0->unk140;
		arg0->unk288 = arg0->unk148;
		if ((u32)arg0->unk2E0 != 0U) {
			temp_r3_6    = fn_8019E8EC();
			arg0->unk28C = M2C_FIELD(temp_r3_6, f32*, 0x30);
			arg0->unk290 = M2C_FIELD(temp_r3_6, f32*, 0x34);
			arg0->unk294 = M2C_FIELD(temp_r3_6, f32*, 0x38);
			arg0->unk290 = arg0->unk284;
		}
		if ((u32)arg0->unk2DC != 0U) {
			temp_r3_7    = fn_8019E8EC();
			arg0->unk298 = M2C_FIELD(temp_r3_7, f32*, 0x30);
			arg0->unk29C = M2C_FIELD(temp_r3_7, f32*, 0x34);
			arg0->unk2A0 = M2C_FIELD(temp_r3_7, f32*, 0x38);
			arg0->unk29C = arg0->unk284;
		}
		temp_r6 = arg0->unk320;
		if (temp_r6 != NULL) {
			sp14                           = arg0->unk280;
			sp18                           = arg0->unk284;
			sp1C                           = arg0->unk288;
			sp8                            = M2C_FIELD(&lbl_8_rodata_1A48, s32*, 0);
			spC                            = M2C_FIELD(&lbl_8_rodata_1A48, s32*, 4);
			sp10                           = M2C_FIELD(&lbl_8_rodata_1A48, s32*, 8);
			temp_f1_2                      = sp18 - lbl_8_rodata_1B40;
			sp18                           = temp_f1_2;
			M2C_FIELD(temp_r6, f32*, 0x80) = sp14;
			M2C_FIELD(temp_r6, f32*, 0x84) = temp_f1_2;
			M2C_FIELD(temp_r6, f32*, 0x88) = sp1C;
			M2C_FIELD(temp_r6, s32*, 0x8C) = (s32)M2C_FIELD(&lbl_8_rodata_1A48, s32*, 0);
			M2C_FIELD(temp_r6, s32*, 0x90) = (s32)M2C_FIELD(&lbl_8_rodata_1A48, s32*, 4);
			M2C_FIELD(temp_r6, s32*, 0x94) = (s32)M2C_FIELD(&lbl_8_rodata_1A48, s32*, 8);
		}
	}
}

void fn_8_AEAA8(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x2FC) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x2FC) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

void fn_8_AEB00(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0x2FC) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2FC) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	M2C_FIELD(arg0, void**, 0xE8)  = fn_80150588(M2C_FIELD(&lbl_8_bss_19C8, s32*, 0));
	M2C_FIELD(arg0, void**, 0x2FC) = fn_80150588(M2C_FIELD(&lbl_8_bss_19C8, s32*, 4));
}

void fn_8_AEB80(TEnemyParalysis* arg0)
{
	M2C_UNK sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
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
	arg0->unk1D8 = lbl_8_rodata_1AC8;
	arg0->unk1DC = lbl_8_rodata_1AC8;
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
	arg0->unk1B8 = lbl_8_rodata_1AE8;
	arg0->unk25C = -arg0->unk210;
	sp8          = lbl_8_rodata_1AC8;
	spC          = lbl_8_rodata_1AC8;
	sp10         = arg0->unk25C;
	temp_f3      = (lbl_8_rodata_1B38
	                   * (lbl_8_rodata_1ACC
	                       * (f32)fn_801C28D8(&lbl_8_rodata_1AE8, temp_r4, lbl_8_rodata_1AC8)))
	    - lbl_8_rodata_1B3C;
	fn_80195A74(&sp14, &lbl_80239984, 0,
	    lbl_8_rodata_1B30 + (lbl_8_rodata_1B34 * (f32)M2C_FIELD(arg0->unkB0, s32*, 0x10)) + temp_f3,
	    lbl_8_rodata_1B30, temp_f3);
	fn_80196050(&sp14, arg0->unkB0, 2);
	fn_8019941C(&sp8, &sp8, 1, &sp14);
	arg0->unk1CC = sp8;
	arg0->unk1D0 = spC;
	arg0->unk1D4 = sp10;
	arg0->unk25C *= lbl_8_rodata_1AF0;
	arg0->unk260 = arg0->unk1CC;
	arg0->unk264 = arg0->unk1D0;
	arg0->unk268 = arg0->unk1D4;
	arg0->unk180 = 0x200;
	if ((s32)arg0->unk350 == 0) {
		arg0->unk258 = lbl_8_rodata_1B44;
	} else {
		arg0->unk258 = lbl_8_rodata_1B44;
	}
	arg0->unk254 = arg0->unk258;
}

void fn_8_AEE04(TEnemyParalysis* arg0)
{
	arg0->unk270 = lbl_8_rodata_1AC8;
	arg0->unk26C = lbl_8_rodata_1AC8;
	arg0->unk318 = 0;
	arg0->unk31C = 0;
	arg0->unk24C = NULL;
	arg0->unk248 = 0U;
	arg0->unk274 = 0;
	arg0->unk278 = 0;
	arg0->unk27C = -1;
	arg0->unk254 = lbl_8_rodata_1AC8;
	arg0->unk258 = lbl_8_rodata_1AC8;
	arg0->unk250 = 0;
	arg0->unk2B4 = lbl_8_rodata_1ABC;
	arg0->unk2C0 = lbl_8_rodata_1AEC;
	arg0->unk2BC = lbl_8_rodata_1AEC;
	arg0->unk2B8 = lbl_8_rodata_1AEC;
	arg0->unk2D4 = 0;
	arg0->unk2D8 = 0;
	arg0->unk288 = lbl_8_rodata_1AC8;
	arg0->unk284 = lbl_8_rodata_1AC8;
	arg0->unk280 = lbl_8_rodata_1AC8;
	arg0->unk294 = lbl_8_rodata_1AC8;
	arg0->unk290 = lbl_8_rodata_1AC8;
	arg0->unk28C = lbl_8_rodata_1AC8;
	arg0->unk2A0 = lbl_8_rodata_1AC8;
	arg0->unk29C = lbl_8_rodata_1AC8;
	arg0->unk298 = lbl_8_rodata_1AC8;
	arg0->unk2AC = lbl_8_rodata_1AC8;
	arg0->unk2A8 = lbl_8_rodata_1AC8;
	arg0->unk2A4 = lbl_8_rodata_1AC8;
	arg0->unk320 = NULL;
	arg0->unk324 = 0;
	arg0->unk328 = 0;
	arg0->unk2DC = 0U;
	arg0->unk2E0 = 0U;
	arg0->unk2F8 = 0;
	arg0->unk2FC = NULL;
	arg0->unk308 = lbl_8_rodata_1ABC;
	arg0->unk304 = lbl_8_rodata_1ABC;
	arg0->unk300 = lbl_8_rodata_1ABC;
	arg0->unk310 = 1;
	arg0->unk314 = 1;
	arg0->unk2D0 = -1;
}

void* fn_8_AEEE4(void* arg0, s16 arg1)
{
	s32 temp_cr0_eq;
	void** temp_r3_2;
	void* temp_r3;

	if (arg0 != NULL) {
		M2C_FIELD(arg0, M2C_UNK**, 0x18) = &lbl_8_data_16A40;
		M2C_FIELD(arg0, void**, 0xB4)    = (void*)(&lbl_8_data_16A40 + 0x2C);
		if ((s32)M2C_FIELD(arg0, s32*, 0x2D0) != -1) {
			fn_800E1208(0xF, 0);
			M2C_FIELD(arg0, s32*, 0x2D0) = -1;
		}
		temp_r3 = M2C_FIELD(arg0, void**, 0x24C);
		if (temp_r3 != NULL) {
			M2C_FIELD(temp_r3, u16*, 4)    = (u16)(M2C_FIELD(temp_r3, u16*, 4) | 1);
			M2C_FIELD(arg0, void**, 0x24C) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x320) != 0U) {
			fn_8005FD8C(-1);
			M2C_FIELD(arg0, u32*, 0x320) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
			fn_8010AFE4();
			M2C_FIELD(arg0, u32*, 0x318) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
			fn_8010AFE4();
			M2C_FIELD(arg0, u32*, 0x31C) = 0U;
		}
		temp_r3_2   = M2C_FIELD(arg0, void***, 0x248);
		temp_cr0_eq = temp_r3_2 == NULL;
		if (temp_cr0_eq == 0) {
			if (temp_cr0_eq == 0) {
				M2C_FIELD(*temp_r3_2, M2C_UNK(**)(M2C_UNK), 8)(1);
			}
			M2C_FIELD(arg0, void***, 0x248) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2FC) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x2FC) = 0U;
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

TEnemyParalysis* fn_8_AF05C(TEnemyParalysis* arg0, s16 arg1, s32 arg2)
{
	TEnemyParalysis* temp_r3;
	TEnemyParalysis* var_r0_3;
	f32 temp_f0;
	s32 temp_r0;
	u32 var_r0;
	u32 var_r0_2;
	u32 var_r0_4;

	if (arg1 != 0) {
		arg0->unk240 = (s32)((u8*)arg0 + 0x35C);
		arg0->unk244 = (u8*)arg0 + 0x35D;
	}
	fn_800A714C(arg0, arg2);
	__ct__10HAnimClassFv((HAnimClass*)&arg0->unk240);
	arg0->unk18 = &lbl_8_data_16A40;
	arg0->unkB4 = &lbl_8_data_16A40 + 0x2C;
	arg0->unk0  = lbl_8_data_168E0;
	arg0->unk1E = 0x360;
	fn_8_AEE04(arg0);
	fn_8_AEB80(arg0);
	arg0->unk188 &= 0xFFFF3FFF;
	arg0->unk188 |= 0x8000;
	arg0->unk160 = lbl_8_rodata_1AC8;
	arg0->unk15C = lbl_8_rodata_1AC8;
	arg0->unk158 = lbl_8_rodata_1AC8;
	arg0->unk188 &= 0xFFEFCFFF;
	arg0->unk188 |= 0x100000;
	arg0->unk188 |= 0x800000;
	arg0->unk188 |= 0x10;
	temp_f0      = arg0->unk254;
	arg0->unk1A4 = temp_f0;
	arg0->unk2E  = (s16)temp_f0;
	arg0->unk1A0 = lbl_8_rodata_1B48;
	arg0->unk2C  = 3;
	if ((void*)arg0->unk2FC != NULL) {
		fn_80150958();
		arg0->unk2FC = NULL;
	}
	if ((void*)arg0->unkE8 != NULL) {
		fn_80150958();
		arg0->unkE8 = NULL;
	}
	arg0->unkE8  = fn_80150588(M2C_FIELD(&lbl_8_bss_19C8, s32*, 0));
	arg0->unk2FC = fn_80150588(M2C_FIELD(&lbl_8_bss_19C8, s32*, 4));
	fn_8_AE604(arg0);
	fn_8005D5C8(arg0->unkE8, ((u32)(M2C_FIELD(arg0->unkB0, s32*, 0x18) & 0x1C0000) >> 0x12U) + 8);
	arg0->unkE4 = &lbl_8_data_16628;
	arg0->unkD4 = 0;
	if (fn_8005B8D8(&arg0->unkB0) == 0) {
		fn_8003C200(&arg0->unk28, &lbl_8_data_167FC, 1, 3);
		arg0->unk88 = arg0->unk140;
		arg0->unk8C = arg0->unk144;
		arg0->unk90 = arg0->unk148;
	}
	arg0->unk130 = lbl_8_rodata_1B4C;
	arg0->unk134 = lbl_8_rodata_1B50;
	arg0->unk248 = 0U;
	temp_r0      = arg0->unk350;
	switch (temp_r0) { /* irregular */
		case 0:
			var_r0 = fn_80057644(0x1C);
			if (var_r0 != 0U) {
				var_r0 = fn_8_B08F0();
			}
			arg0->unk248 = var_r0;
			break;
		case 1:
			var_r0_2 = fn_80057644(0x1C);
			if (var_r0_2 != 0U) {
				var_r0_2 = fn_8_B08F0();
			}
			arg0->unk248 = var_r0_2;
			break;
	}
	if ((u32)arg0->unk248 != 0U) {
		fn_8_B0300(arg0);
	}
	arg0->unk31C = fn_8010B708(1);
	arg0->unk318 = fn_8010B708(0);
	arg0->unk320 = fn_8006298C(0xD, &arg0->unk140, &arg0->unk14C);
	temp_r3      = fn_80018A34(lbl_8042C148, 0x74);
	var_r0_3     = temp_r3;
	if (var_r0_3 != NULL) {
		var_r0_3 = __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(temp_r3, lbl_8042C10C, NULL);
	}
	arg0->unk24C = var_r0_3;
	arg0->unk13C = 1;
	var_r0_4     = fn_80057644(0x20);
	if (var_r0_4 != 0U) {
		var_r0_4 = fn_800FD8A0(arg0, arg0->unk13C);
	}
	arg0->unk228 = var_r0_4;
	return arg0;
}

TEnemyParalysis* fn_8_AF390(void)
{
	TEnemyParalysis* var_r0;

	var_r0 = fn_80018A34(lbl_8042C148, 0x360);
	if (var_r0 != NULL) {
		var_r0 = fn_8_AF05C((TEnemyParalysis*)1U, (s16)lbl_8042C10C, 0);
	}
	return var_r0;
}

void fn_8_AF3E8(void* arg0, void* arg1)
{
	f32* var_r4_2;
	f32* var_r4_3;
	f32* var_r4_5;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	s32* var_r4_4;
	s32 temp_r5;
	u8* temp_r3;
	u8* var_r4;
	u8 temp_r0;

	temp_r3 = M2C_FIELD(arg1, u8**, 0x2C);
	temp_r0 = M2C_FIELD(temp_r3, u8*, 0);
	var_r4  = &lbl_8_data_168C8;
	if ((s8)temp_r0 < (s8)lbl_8_data_168C8) {

	} else {
		var_r4 = &lbl_8_data_168C9;
		if ((s8)temp_r0 > (s8)lbl_8_data_168C9) {

		} else {
			var_r4 = temp_r3;
		}
	}
	M2C_FIELD(temp_r3, u8*, 0) = (u8)(s8)*var_r4;
	M2C_FIELD(temp_r3, s8*, 1) = 0;
	M2C_FIELD(temp_r3, s8*, 2) = 0;
	M2C_FIELD(temp_r3, s8*, 3) = 0;
	temp_f1                    = M2C_FIELD(temp_r3, f32*, 4);
	var_r4_2                   = &lbl_8_rodata_1B54;
	if (temp_f1 < lbl_8_rodata_1B54) {

	} else {
		var_r4_2 = &lbl_8_rodata_1B58;
		if (temp_f1 > lbl_8_rodata_1B58) {

		} else {
			var_r4_2 = (f32*)(temp_r3 + 4);
		}
	}
	M2C_FIELD(temp_r3, f32*, 4) = (f32)*var_r4_2;
	temp_f1_2                   = M2C_FIELD(temp_r3, f32*, 8);
	var_r4_3                    = &lbl_8_rodata_1B5C;
	if (temp_f1_2 < lbl_8_rodata_1B5C) {

	} else {
		var_r4_3 = &lbl_8_rodata_1B60;
		if (temp_f1_2 > lbl_8_rodata_1B60) {

		} else {
			var_r4_3 = (f32*)(temp_r3 + 8);
		}
	}
	M2C_FIELD(temp_r3, f32*, 8) = (f32)*var_r4_3;
	temp_r5                     = M2C_FIELD(temp_r3, s32*, 0x10);
	var_r4_4                    = &lbl_8_rodata_1B64;
	if (temp_r5 < (s32)lbl_8_rodata_1B64) {

	} else {
		var_r4_4 = &lbl_8_rodata_1B68;
		if (temp_r5 > (s32)lbl_8_rodata_1B68) {

		} else {
			var_r4_4 = (s32*)((u8*)temp_r3 + 0x10);
		}
	}
	M2C_FIELD(temp_r3, s32*, 0x10) = (s32)*var_r4_4;
	temp_f1_3                      = M2C_FIELD(temp_r3, f32*, 0x14);
	var_r4_5                       = &lbl_8_rodata_1B6C;
	if (temp_f1_3 < lbl_8_rodata_1B6C) {

	} else {
		var_r4_5 = lbl_8_rodata_1B70;
		if (temp_f1_3 > 10000.0f) {

		} else {
			var_r4_5 = (f32*)((u8*)temp_r3 + 0x14);
		}
	}
	M2C_FIELD(temp_r3, f32*, 0x14) = (f32)*var_r4_5;
	magicianObjectFieldNames       = *(&lbl_8_data_168C0 + ((s8)M2C_FIELD(temp_r3, u8*, 0) * 4));
}

void magicianObjectUnload(void)
{
	lbl_8_bss_1A48 = 0;
	fn_800FE248(0xA, &lbl_8_data_16628);
	lbl_8_bss_1A18                      = 0;
	lbl_8_bss_19D0                      = 0U;
	M2C_FIELD(&lbl_8_bss_19C8, s32*, 4) = 0;
	M2C_FIELD(&lbl_8_bss_19C8, s32*, 0) = 0;
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
		fn_80100AAC();
	}
	fn_801007F4(lbl_8042C590, 0xA);
}

void magicianObjectLoad(void)
{
	u32 temp_r3;

	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
		fn_80100AAC();
	}
	fn_8010096C(lbl_8042C590, 0xA, &lbl_8_data_16A30);
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
		fn_80100AAC();
	}
	if (fn_80100328(lbl_8042C590, 0xA, 5) != 0U) {
		fn_8005E00C(6);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_19C8, u32*, 0) = fn_8010037C(lbl_8042C590, 0xA, 4);
		fn_8005D9F4(&lbl_8_bss_19C8);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_19C8, u32*, 4) = fn_8010037C(lbl_8042C590, 0xA, 2);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
			fn_80100AAC();
		}
		temp_r3        = fn_80100280(lbl_8042C590, 0xA, 3);
		lbl_8_bss_19D0 = temp_r3;
		if (((u32)M2C_FIELD(&lbl_8_bss_19C8, u32*, 4) != 0U) && (temp_r3 != 0U)) {
			*lbl_8_bss_19D4 = temp_r3;
			fn_8005BF5C(M2C_FIELD(&lbl_8_bss_19C8, u32*, 4), lbl_8_bss_19D4);
		}
		lbl_8_bss_1A18 = 0;
		fn_800FE274(0xA, &lbl_8_data_16628);
		lbl_8_bss_1A48 = fn_8005EA04(&lbl_8_data_1692C);
	}
}

void magicianObjectCreate(void)
{
	if (fn_80018A34(lbl_8042C148, 0x360) != NULL) {
		fn_8_AF05C((TEnemyParalysis*)1U, (s16)lbl_8042C10C, 0);
	}
}

void fn_8_AF86C(void* arg0, s32 arg1)
{
	M2C_FIELD(arg0, s32*, 0x14) = arg1;
	M2C_FIELD(arg0, s32*, 0x10) = 0;
	if (M2C_FIELD(M2C_FIELD(arg0, void**, 0), s32(**)(), 0x14)() != 0) {
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 2);
	}
	M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
	    arg0, M2C_FIELD(arg0, s32*, 4), 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
		fn_800A31B8(M2C_FIELD(arg0, s32*, 0x14));
	}
}

void magicianObjectRegister(void)
{
	s32 flags;

	M2C_FIELD(&magicianObjectEntry, s32*, 0x14)       = 0;
	M2C_FIELD(&magicianObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&magicianObjectEntry, M2C_UNK**, 0)     = &magicianObjectDisplayName;
	M2C_FIELD(&magicianObjectEntry, void (**)(), 4)   = magicianObjectLoad;
	M2C_FIELD(&magicianObjectEntry, void (**)(), 8)   = magicianObjectUnload;
	M2C_FIELD(&magicianObjectEntry, void (**)(), 0xC) = magicianObjectCreate;
	M2C_FIELD(&magicianObjectEntry, s32*, 0x10)       = 0;
	flags                                             = 0x20000;
	M2C_FIELD(&magicianObjectEntry, s32*, 0x14)       = flags;
	M2C_FIELD(&magicianObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&magicianObjectEntry, s8*, 0x20)        = 0x1E;
	M2C_FIELD(&magicianObjectEntry, s16*, 0x1C)       = 0x15C0;
	M2C_FIELD(&magicianObjectEntry, s16*, 0x1E)       = 4;
	M2C_FIELD(&magicianObjectEntry, s8*, 0x21)        = 0;
	M2C_FIELD(&magicianObjectEntry, M2C_UNK**, 0x24)  = &magicianObjectFieldTypes;
	M2C_FIELD(&magicianObjectEntry, s32**, 0x28)      = &magicianObjectFieldNames;
	if (&magicianObjectFieldTypes != NULL) {
		M2C_FIELD(&magicianObjectEntry, s32*, 0x14) = flags | 8;
		return;
	}
	M2C_FIELD(&magicianObjectEntry, s32*, 0x14) = flags & ~8;
}
}
