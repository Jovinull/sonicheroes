#include "types.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

typedef struct TEnemyParalysis TEnemyParalysis;
extern "C" double fabs(double);

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef s32 RwOpCombineType;

typedef struct sParalysisParam {
	s32 activeFrames;
	s32 recoveryFrames;
	u32 offset[3];
} sParalysisParam;

typedef struct RwFrame {
	/* 0x0 */ f32 unk0; /* inferred */
} RwFrame;              /* size >= 0x4 */

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
	/* 0x0EC */ void* unkEC;      /* inferred */
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
	/* 0x250 */ char pad250[0x28]; /* maybe part of unk24C[0xB]? */
	/* 0x278 */ f32 unk278;        /* inferred */
	/* 0x27C */ s32 unk27C;        /* inferred */
	/* 0x280 */ s32 unk280;        /* inferred */
	/* 0x284 */ s32 unk284;        /* inferred */
	/* 0x288 */ void* unk288;      /* inferred */
	/* 0x28C */ s32 unk28C;        /* inferred */
	/* 0x290 */ s32 unk290;        /* inferred */
	/* 0x294 */ f32 unk294;        /* inferred */
	/* 0x298 */ f32 unk298;        /* inferred */
	/* 0x29C */ f32 unk29C;        /* inferred */
	/* 0x2A0 */ f32 unk2A0;        /* inferred */
	/* 0x2A4 */ f32 unk2A4;        /* inferred */
	/* 0x2A8 */ f32 unk2A8;        /* inferred */
	/* 0x2AC */ f32 unk2AC;        /* inferred */
	/* 0x2B0 */ s32 unk2B0;        /* inferred */
	/* 0x2B4 */ s32 unk2B4;        /* inferred */
	/* 0x2B8 */ s32 unk2B8;        /* inferred */
	/* 0x2BC */ s32 unk2BC;        /* inferred */
	/* 0x2C0 */ s32 unk2C0;        /* inferred */
	/* 0x2C4 */ char pad2C4[4];
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
	/* 0x304 */ RwFrame* unk304;         /* inferred */
	/* 0x308 */ u32 unk308;              /* inferred */
	/* 0x30C */ u32 unk30C;              /* inferred */
	/* 0x310 */ void* unk310;            /* inferred */
	/* 0x314 */ void* unk314;            /* inferred */
	/* 0x318 */ s32 unk318;              /* inferred */
	/* 0x31C */ s32 unk31C;              /* inferred */
} TObject;                               /* size >= 0x320 */

extern "C" {

M2C_UNK SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(...);               /* extern */
M2C_UNK Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(...);        /* extern */
void* __ct__10HAnimClassFv(...);                                           /* extern */
TEnemyParalysis* __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(...); /* extern */
void* __ct__15sParalysisParamFv(...);                                      /* extern */
void* __dt__10HAnimClassFv(...);                                           /* extern */
M2C_UNK fn_800189A4(s32, void*);                                           /* extern */
TEnemyParalysis* fn_80018A34(s32, M2C_UNK);                                /* extern */
M2C_UNK fn_8003C200(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);                 /* extern */
M2C_UNK** fn_80057644(M2C_UNK);                                            /* extern */
s32 fn_8005B8D8(void**);                                                   /* extern */
M2C_UNK fn_8005D5C8(void*, s32);                                           /* extern */
s32 fn_8005D9A0(void*, M2C_UNK);                                           /* extern */
u32 fn_8005DEEC(RwFrame*, M2C_UNK);                                        /* extern */
M2C_UNK fn_8005E00C(M2C_UNK);                                              /* extern */
void* fn_800628D0(M2C_UNK, f32*, s32*);                                    /* extern */
M2C_UNK fn_800A7088(void*, M2C_UNK);                                       /* extern */
M2C_UNK fn_800A714C();                                                     /* extern */
s32 fn_800AF3AC(...);                                                      /* extern */
M2C_UNK fn_800AFB50(...);                                                  /* extern */
f32 fn_800D71DC(...);                                                      /* extern */
M2C_UNK fn_800D735C(M2C_UNK*, M2C_UNK, s32*);                              /* extern */
s32 fn_800D7920(f32*, f32*, f32*, f32);                                    /* extern */
s32 fn_800D7A94(...);                                                      /* extern */
f32 fn_800D7AE4(s32);                                                      /* extern */
f32 fn_800D7B00(...);                                                      /* extern */
M2C_UNK** fn_800FD8A0(TObject*, s32);                                      /* extern */
M2C_UNK fn_800FE248(M2C_UNK, M2C_UNK*);                                    /* extern */
M2C_UNK fn_800FE274(M2C_UNK, M2C_UNK*);                                    /* extern */
u32 fn_80100328(u32, M2C_UNK, M2C_UNK);                                    /* extern */
s32 fn_8010037C(u32, M2C_UNK, M2C_UNK);                                    /* extern */
M2C_UNK fn_801007F4(u32, M2C_UNK);                                         /* extern */
M2C_UNK fn_8010096C(...);                                                  /* extern */
M2C_UNK fn_80100AAC();                                                     /* extern */
s32 fn_80103324(void*, f32*, f32);                                         /* extern */
M2C_UNK fn_80139784(void*, void*, void*);                                  /* extern */
void* fn_80139984(M2C_UNK, M2C_UNK, M2C_UNK);                              /* extern */
void* fn_80150588(s32);                                                    /* extern */
M2C_UNK fn_80150958();                                                     /* extern */
M2C_UNK fn_80195790(M2C_UNK*, M2C_UNK*, M2C_UNK, f32, f32);                /* extern */
M2C_UNK fn_80196050(M2C_UNK*, void*, M2C_UNK);                             /* extern */
M2C_UNK fn_801990E0(...);                                                  /* extern */
M2C_UNK fn_8019941C(f32*, f32*, M2C_UNK, M2C_UNK*);                        /* extern */
M2C_UNK* fn_8019E8EC(...);                                                 /* extern */
M2C_UNK fn_8019EB94(RwFrame*, void*, M2C_UNK);                             /* extern */
M2C_UNK fn_8019ECCC(RwFrame*, M2C_UNK*, M2C_UNK);                          /* extern */
M2C_UNK fn_8019ED68(...);                                                  /* extern */
s32 fn_801C28D8();                                                         /* extern */
M2C_UNK fn_8_6BE14(s32, M2C_UNK*);                                         /* extern */
M2C_UNK fn_8_B52F4();                                                      /* extern */
M2C_UNK fn_8_B5308();                                                      /* extern */
M2C_UNK fn_8_B5620(TObject*);                                              /* extern */
M2C_UNK** fn_8_B5B3C();                                                    /* extern */
extern M2C_UNK lbl_80239978;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_8029C310;
extern M2C_UNK lbl_802AD090;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C380;
extern u32 lbl_8042C590;
extern s32 lbl_8_bss_1030;
extern M2C_UNK lbl_8_bss_1A50;
extern void* lbl_8_bss_1A5C;
extern M2C_UNK lbl_8_data_16BB0;
extern M2C_UNK lbl_8_data_16C18;
extern M2C_UNK lbl_8_data_16CA8;
extern M2C_UNK lbl_8_data_16CB4;
extern M2C_UNK lbl_8_data_16CC0;
extern M2C_UNK lbl_8_data_16CD0;
extern M2C_UNK lbl_8_data_16CE0;
extern M2C_UNK lbl_8_rodata_1B94;
extern M2C_UNK lbl_8_rodata_1BA0;
extern M2C_UNK lbl_8_rodata_1BAC;
extern f32 lbl_8_rodata_1BD0;
extern f32 lbl_8_rodata_1BDC;
extern f32 lbl_8_rodata_1BE4;
extern f32 lbl_8_rodata_1BE8;
extern f32 lbl_8_rodata_1C04;
extern f32 lbl_8_rodata_1C08;
extern f32 lbl_8_rodata_1C0C;
extern f32 lbl_8_rodata_1C10;
extern f32 lbl_8_rodata_1C20;
extern f32 lbl_8_rodata_1C24;
extern f32 lbl_8_rodata_1C28;
extern RwFrame lbl_8_rodata_1C2C;
extern f32 lbl_8_rodata_1C30;
extern f32 lbl_8_rodata_1C34;
extern f32 lbl_8_rodata_1C38;
extern f32 lbl_8_rodata_1C3C;
extern f32 lbl_8_rodata_1C40;
extern f32 lbl_8_rodata_1C44;
extern f32 lbl_8_rodata_1C48;
extern s32 lbl_8_rodata_1C4C;
extern s32 lbl_8_rodata_1C50;
extern const char* rinolinerObjectFieldNames[];
static M2C_UNK lbl_8_data_16DA4; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16DB0; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_16DB8[2] = { "STANDARD", "ATTACK" };
static M2C_UNK lbl_8_data_16DC0; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_16DC8[2] = { "STANDARD", "LOOP" };
static M2C_UNK lbl_8_data_16DD0; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16DE4; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_16DF8[2] = { "IRONBALL HOMING ON", "IRONBALL HOMING OFF" };
static u8 lbl_8_data_16E00             = 0;
static u8 lbl_8_data_16E01             = 1;
static u8 lbl_8_data_16E02             = 0;
static u8 lbl_8_data_16E03             = 1;
static u8 lbl_8_data_16E04             = 0;
static u8 lbl_8_data_16E05             = 1;
static f32 lbl_8_data_16E08            = 0.0f;
static f32 lbl_8_data_16E0C            = 100.0f;
static f32 lbl_8_data_16E10            = 0.0f;
static f32 lbl_8_data_16E14            = 100.0f;
static f32 lbl_8_data_16E18            = 0.0f;
static f32 lbl_8_data_16E1C            = 100.0f;
static M2C_UNK lbl_8_data_16E20; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_16E34 = "TObjEnemyRinoliner";
static M2C_UNK lbl_8_data_16E38; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16FA0; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17060; /* unable to generate initializer: unknown type */

void fn_8_B2BB4(void* arg0)
{
	M2C_UNK sp10C;
	f32 spF0;
	f32 spEC;
	f32 spE8;
	f32 spE4;
	f32 spAC;
	f32 spA8;
	f32 spA4;
	s16 spD4;
	f32 spA0;
	M2C_UNK sp90;
	M2C_UNK sp50;
	s32 sp44;
	s32 sp4C;
	s32 sp48;
	s32 sp40;
	s32 sp3C;
	s32 sp38;
	s32 sp34;
	s32 sp30;
	f32 sp2C;
	s32 sp28;
	s32 sp24;
	f32 sp20;
	M2C_UNK sp14;
	M2C_UNK sp8;
	f32* temp_r30;
	f32 temp_f0;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f2;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 var_f31;
	f32 var_f31_2;
	s16** var_r27;
	s16** var_r27_2;
	s16* temp_r28;
	s16* temp_r3;
	s16* temp_r3_2;
	s16* temp_r3_3;
	s16* temp_r3_4;
	s16* temp_r3_5;
	s16* var_r29;
	s16* var_r29_2;
	s16* var_r4;
	s32 temp_cr0_eq;
	s32 var_r0;
	s32 var_r30;

	if (((s32)M2C_FIELD(arg0, s32*, 0x2E0) != 0)
	    && (temp_r3 = M2C_FIELD(arg0, s16**, 0x24C), temp_cr0_eq = temp_r3 == NULL,
	        (temp_cr0_eq == 0))) {
		temp_f2 = M2C_FIELD(arg0, f32*, 0x248);
		spE4    = temp_f2;
		if (temp_cr0_eq != 0) {
			var_r0 = 0;
		} else if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) != 0) {
			if (lbl_8_rodata_1BD0 == temp_f2) {
				var_r0 = 1;
			} else {
				var_r0 = 0;
			}
		} else if (temp_f2 == (M2C_FIELD(temp_r3, f32*, 4) - lbl_8_rodata_1C04)) {
			var_r0 = 1;
		} else {
			var_r0 = 0;
		}
		if (var_r0 != 0) {
			if (fn_800AF3AC(&spD4) == 1) {
				M2C_FIELD(arg0, f32*, 0x140) = spE8;
				M2C_FIELD(arg0, f32*, 0x144) = spEC;
				M2C_FIELD(arg0, f32*, 0x148) = spF0;
				sp44                         = 0;
				fn_800D735C(&sp10C, 0, &sp44);
				if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) != 0) {
					M2C_FIELD(arg0, s32*, 0x14C) = sp44;
					M2C_FIELD(arg0, s32*, 0x150) = sp48;
					M2C_FIELD(arg0, s32*, 0x154) = sp4C;
				} else {
					M2C_FIELD(arg0, s32*, 0x14C) = sp44;
					M2C_FIELD(arg0, s32*, 0x150) = (s32)(u16)(sp48 + 0x8000);
					M2C_FIELD(arg0, s32*, 0x154) = (s32)(u16)(sp4C * -1);
				}
			}
		} else if (fn_800AF3AC(&spD4) == 1) {
			M2C_FIELD(arg0, f32*, 0x140) = spE8;
			M2C_FIELD(arg0, f32*, 0x144) = spEC;
			M2C_FIELD(arg0, f32*, 0x148) = spF0;
			sp38                         = 0;
			fn_800D735C(&sp10C, 0, &sp38);
			if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) != 0) {
				M2C_FIELD(arg0, s32*, 0x14C) = sp38;
				M2C_FIELD(arg0, s32*, 0x150)
				    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150), sp3C, M2C_FIELD(arg0, s32*, 0x2B8));
				M2C_FIELD(arg0, s32*, 0x154)
				    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x154), sp40, M2C_FIELD(arg0, s32*, 0x2BC));
			} else {
				M2C_FIELD(arg0, s32*, 0x14C) = sp38;
				M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
				    (s32)(u16)(sp3C + 0x8000), M2C_FIELD(arg0, s32*, 0x2B8));
				M2C_FIELD(arg0, s32*, 0x154) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x154),
				    (s32)(u16)(sp40 * -1), M2C_FIELD(arg0, s32*, 0x2BC));
			}
			if (((s32)M2C_FIELD(arg0, s32*, 0x2C8) != 0)
			    && ((lbl_8_rodata_1C08 * (f32)fn_801C28D8()) < lbl_8_rodata_1C0C)) {
				temp_f31 = fn_800D7B00(-M2C_FIELD(arg0, s32*, 0x154));
				fn_80195790(&sp50, &lbl_80239978, 0,
				    lbl_8_rodata_1C04 - fn_800D7AE4(-M2C_FIELD(arg0, s32*, 0x154)), temp_f31);
				temp_f31_2 = fn_800D7B00(-M2C_FIELD(arg0, s32*, 0x150));
				fn_80195790(&sp50, &lbl_80239984, 2,
				    lbl_8_rodata_1C04 - fn_800D7AE4(-M2C_FIELD(arg0, s32*, 0x150)), temp_f31_2);
				sp2C = M2C_FIELD(&lbl_8_data_16CB4, f32*, 0);
				sp30 = M2C_FIELD(&lbl_8_data_16CB4, s32*, 4);
				sp34 = M2C_FIELD(&lbl_8_data_16CB4, s32*, 8);
				fn_8019941C(&sp2C, &sp2C, 1, &sp50);
				fn_80196050(&sp50, (u8*)arg0 + 0x140, 2);
				sp20 = M2C_FIELD(&lbl_8_data_16CA8, f32*, 0);
				sp24 = M2C_FIELD(&lbl_8_data_16CA8, s32*, 4);
				sp28 = M2C_FIELD(&lbl_8_data_16CA8, s32*, 8);
				fn_8019941C(&sp20, &sp20, 1, &sp50);
				M2C_FIELD(&lbl_8_data_16CE0, f32**, 0)        = &sp20;
				M2C_FIELD(&lbl_8_data_16CE0, f32**, 4)        = &sp2C;
				M2C_FIELD(&lbl_8_data_16CE0, M2C_UNK**, 0x1C) = &lbl_8_data_16CC0;
				M2C_FIELD(&lbl_8_data_16CE0, M2C_UNK**, 0x20) = &lbl_8_data_16CD0;
				fn_8_6BE14(lbl_8_bss_1030, &lbl_8_data_16CE0);
			}
		}
		if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) != 0) {
			M2C_FIELD(arg0, f32*, 0x248)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x248) + M2C_FIELD(arg0, f32*, 0x2FC));
		} else {
			M2C_FIELD(arg0, f32*, 0x248)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x248) - M2C_FIELD(arg0, f32*, 0x2FC));
		}
		fn_80139784(lbl_8_bss_1A5C, arg0, (u8*)arg0 + 0x140);
		temp_r3_2 = M2C_FIELD(arg0, s16**, 0x24C);
		if (temp_r3_2 == NULL) {
			var_r30 = 1;
		} else {
			var_r30 = 0;
			if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) != 0) {
				temp_f0 = M2C_FIELD(temp_r3_2, f32*, 4) - lbl_8_rodata_1C04;
				M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
				if (M2C_FIELD(arg0, f32*, 0x248) == temp_f0) {
					M2C_FIELD(arg0, f32*, 0x248) = temp_f0;
					var_r30                      = 1;
				}
			} else {
				M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
				if (M2C_FIELD(arg0, f32*, 0x248) == lbl_8_rodata_1BD0) {
					M2C_FIELD(arg0, f32*, 0x248) = (f32)lbl_8_rodata_1BD0;
					var_r30                      = 1;
				}
			}
			if (var_r30 != 0) {
				spA0 = M2C_FIELD(arg0, f32*, 0x248);
				if (fn_800AF3AC(M2C_FIELD(arg0, s16**, 0x24C), &sp90) == 1) {
					M2C_FIELD(arg0, f32*, 0x140) = spA4;
					M2C_FIELD(arg0, f32*, 0x144) = spA8;
					M2C_FIELD(arg0, f32*, 0x148) = spAC;
				}
			}
		}
		if (var_r30 != 0) {
			if ((s32)M2C_FIELD(arg0, s32*, 0x2EC) == 0) {
				temp_r30 = (f32*)((u8*)arg0 + 0x140);
				temp_r28 = M2C_FIELD(arg0, s16**, 0x24C);
				var_r29  = NULL;
				var_f31  = lbl_8_rodata_1C10;
				var_r27  = M2C_FIELD(lbl_8042C380, s16***, 0x28);
			loop_46:
				temp_r3_3 = *var_r27;
				if (temp_r3_3 != NULL) {
					if ((temp_r3_3 != temp_r28) && ((s16)M2C_FIELD(temp_r3_3, s16*, 0) == 1)) {
						fn_800AFB50(NULL, &sp14);
						temp_f1 = fn_800D71DC(temp_r30, &sp14);
						if (temp_f1 < var_f31) {
							var_f31                      = temp_f1;
							var_r29                      = *var_r27;
							M2C_FIELD(arg0, s32*, 0x2B4) = 1;
						}
						temp_r3_4 = *var_r27;
						fn_800AFB50(temp_r3_4, M2C_FIELD(temp_r3_4, s16*, 2) - 1, &sp14);
						temp_f1_2 = fn_800D71DC(temp_r30, &sp14);
						if (temp_f1_2 < var_f31) {
							var_f31                      = temp_f1_2;
							var_r29                      = *var_r27;
							M2C_FIELD(arg0, s32*, 0x2B4) = 0;
						}
					}
					var_r27 += 4;
					goto loop_46;
				}
				var_r4 = var_r29;
			} else {
				var_r29_2 = NULL;
				var_f31_2 = lbl_8_rodata_1C10;
				var_r27_2 = M2C_FIELD(lbl_8042C380, s16***, 0x28);
			loop_53:
				temp_r3_5 = *var_r27_2;
				if (temp_r3_5 != NULL) {
					if ((s16)*temp_r3_5 == 1) {
						fn_800AFB50(NULL, &sp8);
						temp_f1_3 = fn_800D71DC((u8*)arg0 + 0x140, &sp8);
						if (temp_f1_3 < var_f31_2) {
							var_f31_2                    = temp_f1_3;
							var_r29_2                    = *var_r27_2;
							M2C_FIELD(arg0, s32*, 0x2B4) = 1;
						}
					}
					var_r27_2 += 4;
					goto loop_53;
				}
				var_r4 = var_r29_2;
			}
			if (var_r4 != NULL) {
				if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) != 0) {
					M2C_FIELD(arg0, f32*, 0x248) = (f32)lbl_8_rodata_1BD0;
				} else {
					M2C_FIELD(arg0, f32*, 0x248)
					    = (f32)(M2C_FIELD(var_r4, f32*, 4) - lbl_8_rodata_1C04);
				}
				M2C_FIELD(arg0, s16**, 0x24C) = var_r4;
				return;
			}
			M2C_FIELD(arg0, f32*, 0x248) = (f32)lbl_8_rodata_1BD0;
			M2C_FIELD(arg0, s32*, 0x240) = 0x1D;
		}
	}
}

void fn_8_B321C(TObject* arg0, void* arg1, s32 arg2)
{
	M2C_UNK sp44;
	f32 sp40;
	f32 sp3C;
	f32 sp38;
	f32 sp34;
	f32 sp30;
	f32 sp2C;
	f32 sp28;
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	M2C_UNK* temp_r28;
	M2C_UNK* temp_r30;
	M2C_UNK* temp_r3_2;
	RwFrame* temp_r28_2;
	RwFrame* temp_r31;
	f32* temp_r3;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f2;
	f32 temp_f31;
	s32 temp_r4;
	void* temp_r4_2;

	if (((RwFrame*)arg0->unk304 != NULL) && ((void*)arg0->unk310 != NULL)) {
		sp38     = M2C_FIELD(&lbl_8_rodata_1BA0, f32*, 0);
		sp3C     = M2C_FIELD(&lbl_8_rodata_1BA0, f32*, 4);
		sp40     = M2C_FIELD(&lbl_8_rodata_1BA0, f32*, 8);
		temp_f31 = fn_800D7B00(-arg0->unk150, &lbl_8_rodata_1BA0);
		fn_80195790(
		    &sp44, &lbl_80239984, 0, lbl_8_rodata_1C04 - fn_800D7AE4(-arg0->unk150), temp_f31);
		fn_8019941C(&sp38, &sp38, 1, &sp44);
		fn_801990E0(&sp38, &sp38);
		sp2C    = M2C_FIELD(&lbl_8_rodata_1BAC, f32*, 0);
		sp30    = M2C_FIELD(&lbl_8_rodata_1BAC, f32*, 4);
		sp34    = M2C_FIELD(&lbl_8_rodata_1BAC, f32*, 8);
		sp2C    = M2C_FIELD(arg1, f32*, 0) - arg0->unk140;
		sp30    = M2C_FIELD(arg1, f32*, 4) - arg0->unk144;
		temp_f1 = M2C_FIELD(arg1, f32*, 8);
		sp34    = temp_f1 - arg0->unk148;
		sp30    = lbl_8_rodata_1BD0;
		fn_801990E0(&sp2C, &sp2C, temp_f1);
		sp20    = sp38;
		sp24    = sp3C;
		sp28    = sp40;
		sp14    = sp2C;
		sp18    = sp30;
		sp1C    = sp34;
		sp24    = lbl_8_rodata_1BD0;
		sp18    = lbl_8_rodata_1BD0;
		sp8     = lbl_8_rodata_1BD0;
		spC     = lbl_8_rodata_1C04;
		sp10    = lbl_8_rodata_1BD0;
		temp_r4 = fn_800D7920(&sp20, &sp14, &sp8, lbl_8_rodata_1BD0);
		if (arg2 != 0) {
			arg0->unk28C = fn_800D7A94(arg0->unk28C, 0x200);
		} else {
			arg0->unk28C = temp_r4;
		}
		temp_r31 = M2C_FIELD(arg0->unk310, RwFrame**, 4);
		temp_r28 = fn_8019E8EC(arg0->unk304);
		fn_8019ED68(
		    temp_r31, &lbl_80239984, 0, lbl_8_rodata_1C20 * (f32)arg0->unk28C, lbl_8_rodata_1C20);
		fn_8019ECCC(temp_r31, temp_r28, 2);
		temp_f2      = M2C_FIELD(arg1, f32*, 0) - M2C_FIELD(temp_r28, f32*, 0x30);
		sp2C         = temp_f2;
		temp_f0      = M2C_FIELD(arg1, f32*, 4) - M2C_FIELD(temp_r28, f32*, 0x34);
		sp30         = temp_f0;
		temp_f1_2    = M2C_FIELD(arg1, f32*, 8);
		temp_f0_2    = temp_f1_2 - M2C_FIELD(temp_r28, f32*, 0x38);
		sp34         = temp_f0_2;
		arg0->unk2A0 = temp_f2;
		arg0->unk2A4 = temp_f0;
		arg0->unk2A8 = temp_f0_2;
		temp_r3      = (f32*)((u8*)arg0 + 0x2A0);
		fn_801990E0(temp_r3, temp_r3, temp_f1_2, temp_f2);
		sp2C = lbl_8_rodata_1BD0;
		fn_801990E0(&sp2C, &sp2C);
		if ((u32)arg0->unk308 != 0U) {
			temp_r4_2 = arg0->unk314;
			if (temp_r4_2 != NULL) {
				temp_r28_2 = M2C_FIELD(temp_r4_2, RwFrame**, 4);
				temp_r30   = fn_8019E8EC();
				fn_8019ED68(temp_r28_2, &lbl_80239978, 0, lbl_8_rodata_1C20 * (f32)arg0->unk290,
				    lbl_8_rodata_1C20);
				fn_8019ECCC(temp_r28_2, temp_r30, 2);
				if (fn_8005DEEC(temp_r28_2, 1) != 0U) {
					temp_r3_2    = fn_8019E8EC();
					arg0->unk294 = M2C_FIELD(temp_r3_2, f32*, 0x30);
					arg0->unk298 = M2C_FIELD(temp_r3_2, f32*, 0x34);
					arg0->unk29C = M2C_FIELD(temp_r3_2, f32*, 0x38);
				}
			}
		}
	}
}

void fn_8_B3598(TObject* arg0)
{
	s32 sp1C;
	s32 sp18;
	f32 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;
	M2C_UNK* temp_r3_7;
	RwFrame* temp_r31;
	TEnemyParalysis* temp_r3_2;
	f32 temp_f2;
	s32 temp_r0;
	s32 temp_r3_3;
	s32 temp_r3_5;
	void* temp_r3;
	void* temp_r3_4;
	void* temp_r3_6;
	void* temp_r4;

	temp_f2 = arg0->unk278;
	if ((f32)fabs(temp_f2) > lbl_8_rodata_1C24) {
		arg0->unk278 = temp_f2 * lbl_8_rodata_1C28;
	}
	temp_r3 = arg0->unkE8;
	if (temp_r3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3, RwFrame**, 4);
		if (((s32)arg0->unk19C == 0x24) && (temp_r3_2 = arg0->unk2D0, ((temp_r3_2 == NULL) == 0))) {
			Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType(
			    temp_r3_2, temp_r31, (RwOpCombineType)0);
			fn_8019ED68(temp_r31, &lbl_80239978, 2, -(lbl_8_rodata_1C20 * (f32)arg0->unk154),
			    lbl_8_rodata_1C20);
			fn_8019ED68(temp_r31, &lbl_80239990, 2, arg0->unk278);
			fn_8019ED68(temp_r31, &lbl_80239984, 2, -(lbl_8_rodata_1C20 * (f32)arg0->unk150),
			    lbl_8_rodata_1C20);
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
			sp14 = M2C_FIELD(&lbl_8_rodata_1B94, f32*, 0);
			sp18 = M2C_FIELD(&lbl_8_rodata_1B94, s32*, 4);
			sp1C = M2C_FIELD(&lbl_8_rodata_1B94, s32*, 8);
			fn_8019941C(&sp14, &sp14, 1, fn_8019E8EC(temp_r31, &lbl_8_rodata_1B94));
			SetPosAng__15TEnemyParalysisFPC5RwV3dPC6sAngle(arg0->unk2D0, (RwV3d*)&sp14, NULL);
		} else {
			fn_8019ED68(temp_r31, &lbl_80239978, 0, -(lbl_8_rodata_1C20 * (f32)arg0->unk154),
			    lbl_8_rodata_1C20);
			fn_8019ED68(temp_r31, &lbl_80239990, 2, arg0->unk278);
			fn_8019ED68(temp_r31, &lbl_80239984, 2, -(lbl_8_rodata_1C20 * (f32)arg0->unk150),
			    lbl_8_rodata_1C20);
			fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
		}
	}
	if ((u32)arg0->unk304 == NULL) {
		temp_r3_3 = fn_8005D9A0(arg0->unkEC, 0x4B0);
		if (temp_r3_3 != -1) {
			arg0->unk304 = M2C_FIELD(
			    (M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_3 * 0x10)), RwFrame**, 0xC);
		}
	}
	if ((u32)arg0->unk308 == 0U) {
		temp_r3_4 = arg0->unk310;
		if (temp_r3_4 != NULL) {
			arg0->unk308 = fn_8005DEEC(M2C_FIELD(temp_r3_4, RwFrame**, 4), 1);
		}
	}
	if ((u32)arg0->unk30C == 0U) {
		temp_r3_5 = fn_8005D9A0(arg0->unkEC, 0x44D);
		if (temp_r3_5 != -1) {
			arg0->unk30C
			    = M2C_FIELD((M2C_FIELD(arg0->unkEC, s32*, 0x10) + (temp_r3_5 * 0x10)), u32*, 0xC);
		}
	}
	if ((s32)arg0->unk2E0 != 0) {
		arg0->unk2CC = fn_80103324((u8*)arg0 + 0x140, &lbl_8_rodata_1BE4, lbl_8_rodata_1BE4);
		temp_r0      = arg0->unk2CC;
		if (temp_r0 != -1) {
			temp_r3_6 = (void*)*(&lbl_802AD090 + (temp_r0 * 4));
			if (temp_r3_6 != NULL) {
				if ((s32)arg0->unk19C != 0x24) {
					arg0->unk2D4 = M2C_FIELD(temp_r3_6, f32*, 0x18);
					arg0->unk2D8 = M2C_FIELD(temp_r3_6, f32*, 0x1C);
					arg0->unk2DC = M2C_FIELD(temp_r3_6, f32*, 0x20);
				}
				fn_8_B321C(arg0, (u8*)arg0 + 0x2D4, 1);
				arg0->unk2C0 = 1;
			}
		}
		if ((void*)arg0->unk288 == NULL) {
			arg0->unk288 = fn_800628D0(0xD, &arg0->unk140, &arg0->unk14C);
		}
		if (((void*)arg0->unk288 != NULL) && ((u32)arg0->unk30C != 0U)) {
			sp8  = -arg0->unk154;
			spC  = -arg0->unk150;
			sp10 = (s32)(lbl_8_rodata_1C2C.unk0 * arg0->unk278);
			temp_r3_7
			    = fn_8019E8EC(&lbl_8_rodata_1C2C, M2C_BITWISE(M2C_UNK*, lbl_8_rodata_1C2C.unk0));
			temp_r4 = arg0->unk288;
			if ((u32)(temp_r3_7 + 0x30) != 0U) {
				M2C_FIELD(temp_r4, f32*, 0x80) = (f32)M2C_FIELD(temp_r3_7, f32*, 0x30);
				M2C_FIELD(temp_r4, f32*, 0x84) = (f32)M2C_FIELD(temp_r3_7, f32*, 0x34);
				M2C_FIELD(temp_r4, f32*, 0x88) = (f32)M2C_FIELD(temp_r3_7, f32*, 0x38);
			}
			M2C_FIELD(temp_r4, s32*, 0x8C) = sp8;
			M2C_FIELD(temp_r4, s32*, 0x90) = spC;
			M2C_FIELD(temp_r4, s32*, 0x94) = sp10;
		}
	}
}

void fn_8_B39E4(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x314) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x314) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x310) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x310) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

void fn_8_B3A54(void* arg0)
{
	void* temp_r31;

	if ((void*)M2C_FIELD(arg0, void**, 0x314) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x314) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x310) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x310) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	temp_r31                       = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 0));
	M2C_FIELD(arg0, void**, 0x310) = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 4));
	M2C_FIELD(arg0, void**, 0x314) = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 8));
	M2C_FIELD(arg0, void**, 0xE8)  = temp_r31;
}

void fn_8_B3B0C(void* arg0)
{
	void* temp_r4;
	void* temp_r5;

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

void fn_8_B3BE0(TObject* arg0)
{
	arg0->unk248 = lbl_8_rodata_1BD0;
	arg0->unk24C = NULL;
	arg0->unk240 = 0;
	arg0->unk244 = NULL;
	arg0->unk278 = lbl_8_rodata_1BD0;
	arg0->unk27C = 0;
	arg0->unk2FC = lbl_8_rodata_1C30;
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
	arg0->unk2DC = lbl_8_rodata_1BD0;
	arg0->unk2D8 = lbl_8_rodata_1BD0;
	arg0->unk2D4 = lbl_8_rodata_1BD0;
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
		M2C_FIELD(arg0, M2C_UNK**, 0x18) = &lbl_8_data_16E38;
		M2C_FIELD(arg0, void**, 0xB4)    = (void*)(&lbl_8_data_16E38 + 0x2C);
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
		temp_r3_3   = M2C_FIELD(arg0, void***, 0x244);
		temp_cr0_eq = temp_r3_3 == NULL;
		if (temp_cr0_eq == 0) {
			if (temp_cr0_eq == 0) {
				M2C_FIELD(*temp_r3_3, M2C_UNK(**)(M2C_UNK), 8)(1);
			}
			M2C_FIELD(arg0, void***, 0x244) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x314) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x314) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x310) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x310) = 0U;
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

TObject* fn_8_B3E0C(TObject* arg0, TObject* arg1)
{
	f32 sp30;
	f32 sp2C;
	f32 sp28;
	sParalysisParam sp20;
	M2C_UNK sp14;
	M2C_UNK sp8;
	M2C_UNK** temp_r3_2;
	M2C_UNK** var_r0;
	M2C_UNK** var_r0_3;
	TEnemyParalysis* temp_r3_7;
	TEnemyParalysis* var_r0_2;
	f32* temp_r30_2;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 var_f31;
	f32 var_f31_2;
	s16** var_r27;
	s16** var_r28;
	s16* temp_r3_3;
	s16* temp_r3_4;
	s16* temp_r3_5;
	s16* temp_r3_6;
	s16* var_r28_2;
	s16* var_r29;
	s32 temp_r0;
	void* temp_r30;
	void* temp_r3;
	void* temp_r4;

	fn_800A714C();
	__ct__10HAnimClassFv((u8*)arg0 + 0x240);
	arg0->unk18 = &lbl_8_data_16E38;
	arg0->unkB4 = &lbl_8_data_16E38 + 0x2C;
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
		fn_80150958();
		arg0->unk314 = NULL;
	}
	if ((void*)arg0->unk310 != NULL) {
		fn_80150958();
		arg0->unk310 = NULL;
	}
	if ((void*)arg0->unkE8 != NULL) {
		fn_80150958();
		arg0->unkE8 = NULL;
	}
	temp_r30     = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 0));
	arg0->unk310 = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 4));
	arg0->unk314 = fn_80150588(M2C_FIELD(&lbl_8_bss_1A50, s32*, 8));
	arg0->unkE8  = temp_r30;
	fn_8_B3598(arg0);
	arg0->unk160 = lbl_8_rodata_1BD0;
	arg0->unk15C = lbl_8_rodata_1BD0;
	arg0->unk158 = lbl_8_rodata_1BD0;
	arg0->unk188 &= 0xFFEFCFFF;
	arg0->unk188 |= 0x10;
	arg0->unk1A4 = lbl_8_rodata_1BDC;
	arg0->unk2E  = 2;
	arg0->unk1A0 = lbl_8_rodata_1C34;
	arg0->unk2C  = 3;
	fn_8005D5C8(arg0->unkE8, ((u32)(M2C_FIELD(arg0->unkB0, s32*, 0x18) & 0x1C0000) >> 0x12U) + 8);
	arg0->unkE4 = &lbl_8_data_16C18;
	arg0->unkD4 = 0;
	if (fn_8005B8D8(&arg0->unkB0) == 0) {
		fn_8003C200(&arg0->unk28, &lbl_8_data_16BB0, 1, 3);
		arg0->unk88 = arg0->unk140;
		arg0->unk8C = arg0->unk144;
		arg0->unk90 = arg0->unk148;
	}
	arg0->unk130 = lbl_8_rodata_1C38;
	arg0->unk134 = lbl_8_rodata_1C3C;
	arg0->unk244 = NULL;
	temp_r0      = arg0->unk2E8;
	switch (temp_r0) { /* irregular */
		case 0:
			var_r0 = fn_80057644(0x20);
			if (var_r0 != NULL) {
				var_r0 = fn_8_B5B3C();
			}
			arg0->unk244 = var_r0;
			break;
		case 1:
			temp_r3_2 = fn_80057644(0x20);
			if (temp_r3_2 != NULL) {
				fn_8_B5B3C();
				*temp_r3_2 = &lbl_8_data_17060;
			}
			arg0->unk244 = temp_r3_2;
			break;
	}
	if ((M2C_UNK**)arg0->unk244 != NULL) {
		fn_8_B5620(arg0);
	}
	if ((s32)arg0->unk2EC == 0) {
		temp_r30_2 = &arg0->unk140;
		var_r29    = NULL;
		var_f31    = lbl_8_rodata_1BE8;
		var_r28    = M2C_FIELD(lbl_8042C380, s16***, 0x28);
	loop_29:
		temp_r3_3 = *var_r28;
		if (temp_r3_3 != NULL) {
			if ((temp_r3_3 != NULL) && ((s16)M2C_FIELD(temp_r3_3, s16*, 0) == 1)) {
				fn_800AFB50(NULL, &sp14);
				temp_f1 = fn_800D71DC(temp_r30_2, &sp14);
				if (temp_f1 < var_f31) {
					var_f31      = temp_f1;
					var_r29      = *var_r28;
					arg0->unk2B4 = 1;
				}
				temp_r3_4 = *var_r28;
				fn_800AFB50(temp_r3_4, M2C_FIELD(temp_r3_4, s16*, 2) - 1, &sp14);
				temp_f1_2 = fn_800D71DC(temp_r30_2, &sp14);
				if (temp_f1_2 < var_f31) {
					var_f31      = temp_f1_2;
					var_r29      = *var_r28;
					arg0->unk2B4 = 0;
				}
			}
			var_r28 += 4;
			goto loop_29;
		}
		arg0->unk24C = var_r29;
	} else {
		var_r28_2 = NULL;
		var_f31_2 = lbl_8_rodata_1BE8;
		var_r27   = M2C_FIELD(lbl_8042C380, s16***, 0x28);
	loop_36:
		temp_r3_5 = *var_r27;
		if (temp_r3_5 != NULL) {
			if ((s16)*temp_r3_5 == 1) {
				fn_800AFB50(NULL, &sp8);
				temp_f1_3 = fn_800D71DC(&arg0->unk140, &sp8);
				if (temp_f1_3 < var_f31_2) {
					var_f31_2    = temp_f1_3;
					var_r28_2    = *var_r27;
					arg0->unk2B4 = 1;
				}
			}
			var_r27 += 4;
			goto loop_36;
		}
		arg0->unk24C = var_r28_2;
	}
	temp_r3_6 = arg0->unk24C;
	if (temp_r3_6 != NULL) {
		if ((s32)arg0->unk2B4 != 0) {
			arg0->unk248 = lbl_8_rodata_1BD0;
		} else {
			arg0->unk248 = M2C_FIELD(temp_r3_6, f32*, 4) - lbl_8_rodata_1C04;
		}
	}
	__ct__15sParalysisParamFv(&sp20);
	sp28      = lbl_8_rodata_1C40;
	sp2C      = lbl_8_rodata_1C40;
	sp30      = lbl_8_rodata_1C40;
	temp_r3_7 = fn_80018A34(lbl_8042C148, 0x74);
	var_r0_2  = temp_r3_7;
	if (var_r0_2 != NULL) {
		var_r0_2
		    = __ct__15TEnemyParalysisFP7TObjectP15sParalysisParam(temp_r3_7, lbl_8042C10C, &sp20);
	}
	arg0->unk2D0 = var_r0_2;
	arg0->unk13C = 1;
	var_r0_3     = fn_80057644(0x20);
	if (var_r0_3 != NULL) {
		var_r0_3 = fn_800FD8A0(arg0, arg0->unk13C);
	}
	arg0->unk228 = var_r0_3;
	return arg0;
}

TEnemyParalysis* fn_8_B4394(void)
{
	TEnemyParalysis* var_r0;

	var_r0 = fn_80018A34(lbl_8042C148, 0x320);
	if (var_r0 != NULL) {
		var_r0 = (TEnemyParalysis*)fn_8_B3E0C((TObject*)var_r0, lbl_8042C10C);
	}
	return var_r0;
}

void fn_8_B43E8(void* arg0, void* arg1)
{
	f32* var_r4_4;
	f32* var_r4_6;
	f32* var_r4_7;
	f32* var_r4_8;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	s32* var_r4_5;
	s32 temp_r5;
	u8* temp_r3;
	u8* var_r4;
	u8* var_r4_2;
	u8* var_r4_3;
	u8 temp_r0;
	u8 temp_r0_2;
	u8 temp_r0_3;

	temp_r3 = M2C_FIELD(arg1, u8**, 0x2C);
	temp_r0 = M2C_FIELD(temp_r3, u8*, 0);
	var_r4  = &lbl_8_data_16E00;
	if ((s8)temp_r0 < (s8)lbl_8_data_16E00) {

	} else {
		var_r4 = &lbl_8_data_16E01;
		if ((s8)temp_r0 > (s8)lbl_8_data_16E01) {

		} else {
			var_r4 = temp_r3;
		}
	}
	M2C_FIELD(temp_r3, u8*, 0) = (u8)(s8)*var_r4;
	temp_r0_2                  = M2C_FIELD(temp_r3, u8*, 1);
	var_r4_2                   = &lbl_8_data_16E02;
	if ((s8)temp_r0_2 < (s8)lbl_8_data_16E02) {

	} else {
		var_r4_2 = &lbl_8_data_16E03;
		if ((s8)temp_r0_2 > (s8)lbl_8_data_16E03) {

		} else {
			var_r4_2 = temp_r3 + 1;
		}
	}
	M2C_FIELD(temp_r3, u8*, 1) = (u8)(s8)*var_r4_2;
	temp_r0_3                  = M2C_FIELD(temp_r3, u8*, 2);
	var_r4_3                   = &lbl_8_data_16E04;
	if ((s8)temp_r0_3 < (s8)lbl_8_data_16E04) {

	} else {
		var_r4_3 = &lbl_8_data_16E05;
		if ((s8)temp_r0_3 > (s8)lbl_8_data_16E05) {

		} else {
			var_r4_3 = temp_r3 + 2;
		}
	}
	M2C_FIELD(temp_r3, u8*, 2) = (u8)(s8)*var_r4_3;
	M2C_FIELD(temp_r3, s8*, 3) = 0;
	temp_f1                    = M2C_FIELD(temp_r3, f32*, 4);
	var_r4_4                   = &lbl_8_rodata_1C44;
	if (temp_f1 < lbl_8_rodata_1C44) {

	} else {
		var_r4_4 = &lbl_8_rodata_1C48;
		if (temp_f1 > lbl_8_rodata_1C48) {

		} else {
			var_r4_4 = (f32*)(temp_r3 + 4);
		}
	}
	M2C_FIELD(temp_r3, f32*, 4) = (f32)*var_r4_4;
	temp_r5                     = M2C_FIELD(temp_r3, s32*, 8);
	var_r4_5                    = &lbl_8_rodata_1C4C;
	if (temp_r5 < (s32)lbl_8_rodata_1C4C) {

	} else {
		var_r4_5 = &lbl_8_rodata_1C50;
		if (temp_r5 > (s32)lbl_8_rodata_1C50) {

		} else {
			var_r4_5 = (s32*)(temp_r3 + 8);
		}
	}
	M2C_FIELD(temp_r3, s32*, 8) = (s32)*var_r4_5;
	temp_f1_2                   = M2C_FIELD(temp_r3, f32*, 0xC);
	var_r4_6                    = &lbl_8_data_16E08;
	if (temp_f1_2 < lbl_8_data_16E08) {

	} else {
		var_r4_6 = &lbl_8_data_16E0C;
		if (temp_f1_2 > lbl_8_data_16E0C) {

		} else {
			var_r4_6 = (f32*)(temp_r3 + 0xC);
		}
	}
	M2C_FIELD(temp_r3, f32*, 0xC) = (f32)*var_r4_6;
	temp_f1_3                     = M2C_FIELD(temp_r3, f32*, 0x10);
	var_r4_7                      = &lbl_8_data_16E10;
	if (temp_f1_3 < lbl_8_data_16E10) {

	} else {
		var_r4_7 = &lbl_8_data_16E14;
		if (temp_f1_3 > lbl_8_data_16E14) {

		} else {
			var_r4_7 = (f32*)(temp_r3 + 0x10);
		}
	}
	M2C_FIELD(temp_r3, f32*, 0x10) = (f32)*var_r4_7;
	temp_f1_4                      = M2C_FIELD(temp_r3, f32*, 0x14);
	var_r4_8                       = &lbl_8_data_16E18;
	if (temp_f1_4 < lbl_8_data_16E18) {

	} else {
		var_r4_8 = &lbl_8_data_16E1C;
		if (temp_f1_4 > lbl_8_data_16E1C) {

		} else {
			var_r4_8 = (f32*)(temp_r3 + 0x14);
		}
	}
	M2C_FIELD(temp_r3, f32*, 0x14) = (f32)*var_r4_8;
	M2C_FIELD(&rinolinerObjectFieldNames, M2C_UNK**, 0)
	    = (M2C_UNK*)lbl_8_data_16DB8[(s8)M2C_FIELD(temp_r3, u8*, 0)];
	M2C_FIELD(&rinolinerObjectFieldNames, M2C_UNK**, 4)
	    = (M2C_UNK*)lbl_8_data_16DC8[(s8)M2C_FIELD(temp_r3, u8*, 1)];
	M2C_FIELD(&rinolinerObjectFieldNames, M2C_UNK**, 8)
	    = (M2C_UNK*)lbl_8_data_16DF8[(s8)M2C_FIELD(temp_r3, u8*, 2)];
}

void rinolinerObjectUnload(void)
{
	if ((void*)lbl_8_bss_1A5C != NULL) {
		M2C_FIELD(lbl_8_bss_1A5C, u16*, 4) = (u16)(M2C_FIELD(lbl_8_bss_1A5C, u16*, 4) | 1);
		lbl_8_bss_1A5C                     = NULL;
	}
	fn_8_B52F4();
	fn_800FE248(3, &lbl_8_data_16C18);
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	fn_801007F4(lbl_8042C590, 3);
}

void rinolinerObjectLoad(void)
{
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	fn_8010096C(lbl_8042C590, 3, "en_rinoliner.one");
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	if (fn_80100328(lbl_8042C590, 3, 8) != 0U) {
		fn_8005E00C(6);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1A50, s32*, 0) = fn_8010037C(lbl_8042C590, 3, 5);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1A50, s32*, 4) = fn_8010037C(lbl_8042C590, 3, 3);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1A50, s32*, 8) = fn_8010037C(lbl_8042C590, 3, 2);
		fn_800FE274(3, &lbl_8_data_16C18);
		fn_8_B5308();
		lbl_8_bss_1A5C = fn_80139984(1, 0x4037, 4);
	}
}

void rinolinerObjectCreate(void)
{
	TEnemyParalysis* temp_r3;

	temp_r3 = fn_80018A34(lbl_8042C148, 0x320);
	if (temp_r3 != NULL) {
		fn_8_B3E0C((TObject*)temp_r3, lbl_8042C10C);
	}
}

typedef struct ObjectEntry {
	const char* name;
	void (*load)(void);
	void (*unload)(void);
	void (*create)(void);
	void (*reset)(void);
	u32 flags;
	u32 unk18;
	s16 unk1C;
	s16 unk1E;
	u8 unk20;
	u8 unk21;
	u8 pad22[2];
	const char* fieldTypes;
	const char** fieldNames;
} ObjectEntry;

extern ObjectEntry rinolinerObjectEntry;
extern char rinolinerObjectDisplayName[];
extern char rinolinerObjectFieldTypes[];
extern const char* rinolinerObjectFieldNames[];

void rinolinerObjectRegister(void)
{
	rinolinerObjectEntry.flags      = 0;
	rinolinerObjectEntry.unk18      = 0;
	rinolinerObjectEntry.name       = rinolinerObjectDisplayName;
	rinolinerObjectEntry.load       = rinolinerObjectLoad;
	rinolinerObjectEntry.unload     = rinolinerObjectUnload;
	rinolinerObjectEntry.create     = rinolinerObjectCreate;
	rinolinerObjectEntry.reset      = NULL;
	rinolinerObjectEntry.flags      = 0x20000;
	rinolinerObjectEntry.unk18      = 0;
	rinolinerObjectEntry.unk20      = 0x1E;
	rinolinerObjectEntry.unk1C      = 0x1590;
	rinolinerObjectEntry.unk1E      = 4;
	rinolinerObjectEntry.unk21      = 0;
	rinolinerObjectEntry.fieldTypes = rinolinerObjectFieldTypes;
	rinolinerObjectEntry.fieldNames = rinolinerObjectFieldNames;
	if (rinolinerObjectFieldTypes != NULL) {
		rinolinerObjectEntry.flags |= 8;
	} else {
		rinolinerObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const rinolinerObjectCtorEntry)(void) = rinolinerObjectRegister;
}
