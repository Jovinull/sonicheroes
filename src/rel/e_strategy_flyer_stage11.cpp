#include "types.h"

typedef s32 M2C_UNK;
typedef struct HAnimClass HAnimClass;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_STRUCT_COPY(dst, src, size)                                                            \
	(*(struct _struct_lbl_8_data_15E0C_0xC*)(dst) = *(struct _struct_lbl_8_data_15E0C_0xC*)(src))
#define M2C_ERROR(...)

typedef struct TObject {
	/* 0x000 */ const char* unk0; /* inferred */
	/* 0x004 */ char pad4[0x14];  /* maybe part of unk0[6]? */
	/* 0x018 */ M2C_UNK* unk18;   /* inferred */
	/* 0x01C */ char pad1C[2];
	/* 0x01E */ s16 unk1E;         /* inferred */
	/* 0x020 */ char pad20[8];     /* maybe part of unk1E[5]? */
	/* 0x028 */ s32 unk28;         /* inferred */
	/* 0x02C */ s32 unk2C;         /* inferred */
	/* 0x030 */ s32 unk30;         /* inferred */
	/* 0x034 */ s8 unk34;          /* inferred */
	/* 0x035 */ char pad35[0x7B];  /* maybe part of unk34[0x7C]? */
	/* 0x0B0 */ void* unkB0;       /* inferred */
	/* 0x0B4 */ void* unkB4;       /* inferred */
	/* 0x0B8 */ char padB8[0x1C];  /* maybe part of unkB4[8]? */
	/* 0x0D4 */ s32 unkD4;         /* inferred */
	/* 0x0D8 */ char padD8[0xC];   /* maybe part of unkD4[4]? */
	/* 0x0E4 */ M2C_UNK* unkE4;    /* inferred */
	/* 0x0E8 */ void* unkE8;       /* inferred */
	/* 0x0EC */ char padEC[0x54];  /* maybe part of unkE8[0x16]? */
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
	/* 0x184 */ char pad184[0x18]; /* maybe part of unk180[7]? */
	/* 0x19C */ s32 unk19C;        /* inferred */
	/* 0x1A0 */ char pad1A0[0x20]; /* maybe part of unk19C[9]? */
	/* 0x1C0 */ f32 unk1C0;        /* inferred */
	/* 0x1C4 */ f32 unk1C4;        /* inferred */
	/* 0x1C8 */ f32 unk1C8;        /* inferred */
	/* 0x1CC */ f32 unk1CC;        /* inferred */
	/* 0x1D0 */ f32 unk1D0;        /* inferred */
	/* 0x1D4 */ f32 unk1D4;        /* inferred */
	/* 0x1D8 */ char pad1D8[0x68]; /* maybe part of unk1D4[0x1B]? */
	/* 0x240 */ void** unk240;     /* inferred */
	/* 0x244 */ s32 unk244;        /* inferred */
	/* 0x248 */ u32 unk248;        /* inferred */
	/* 0x24C */ f32 unk24C;        /* inferred */
	/* 0x250 */ f32 unk250;        /* inferred */
	/* 0x254 */ f32 unk254;        /* inferred */
	/* 0x258 */ f32 unk258;        /* inferred */
	/* 0x25C */ f32 unk25C;        /* inferred */
	/* 0x260 */ s32 unk260;        /* inferred */
	/* 0x264 */ s32 unk264;        /* inferred */
	/* 0x268 */ s32 unk268;        /* inferred */
	/* 0x26C */ s32 unk26C;        /* inferred */
	/* 0x270 */ char pad270[4];
	/* 0x274 */ s32 unk274;       /* inferred */
	/* 0x278 */ s32 unk278;       /* inferred */
	/* 0x27C */ void* unk27C;     /* inferred */
	/* 0x280 */ void* unk280;     /* inferred */
	/* 0x284 */ void* unk284;     /* inferred */
	/* 0x288 */ u32 unk288;       /* inferred */
	/* 0x28C */ char pad28C[0xC]; /* maybe part of unk288[4]? */
	/* 0x298 */ s32 unk298;       /* inferred */
	/* 0x29C */ s32 unk29C;       /* inferred */
	/* 0x2A0 */ s32 unk2A0;       /* inferred */
	/* 0x2A4 */ void* unk2A4;     /* inferred */
	/* 0x2A8 */ void* unk2A8;     /* inferred */
	/* 0x2AC */ void* unk2AC;     /* inferred */
	/* 0x2B0 */ void** unk2B0;    /* inferred */
} TObject;                        /* size >= 0x2B4 */

struct _struct_lbl_8_data_15E0C_0xC {
	/* 0x0 */ s32 unk0; /* inferred */
	/* 0x4 */ s32 unk4; /* inferred */
	/* 0x8 */ s32 unk8; /* inferred */
}; /* size = 0xC */

struct _struct_lbl_8_rodata_17F4_0xC {
	/* 0x0 */ f32 unk0; /* inferred */
	/* 0x4 */ f32 unk4; /* inferred */
	/* 0x8 */ f32 unk8; /* inferred */
}; /* size = 0xC */

void* __ct__10HAnimClassFv(void* self);                                   /* extern */
void* __ct__7TObjectFP7TObject(TObject* self, TObject* arg0);             /* extern */
M2C_UNK __dl__FPv(void* arg0);                                            /* extern */
void* __dt__10HAnimClassFv(void* self, s16 destroyFlag);                  /* extern */
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);                   /* extern */
M2C_UNK dtor_800FE334(M2C_UNK);                                           /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                                       /* extern */
TObject* fn_80018A34(s32, M2C_UNK);                                       /* extern */
M2C_UNK fn_80018C4C(M2C_UNK*);                                            /* extern */
M2C_UNK fn_80018C64(M2C_UNK*);                                            /* extern */
s32 fn_80018C98();                                                        /* extern */
M2C_UNK fn_80019898(M2C_UNK*, M2C_UNK);                                   /* extern */
M2C_UNK fn_8003C640();                                                    /* extern */
void** fn_80057644(M2C_UNK);                                              /* extern */
s32 fn_8005B8BC(s32);                                                     /* extern */
M2C_UNK fn_8005BC04(void*);                                               /* extern */
M2C_UNK fn_8005BF5C(u32*);                                                /* extern */
M2C_UNK fn_8005DA34();                                                    /* extern */
M2C_UNK fn_8005E00C(M2C_UNK);                                             /* extern */
s32 fn_800A2BE0(u8);                                                      /* extern */
M2C_UNK fn_800A31B8(void*);                                               /* extern */
M2C_UNK fn_800A3D48(void*);                                               /* extern */
s32 fn_800A3ED4(void*);                                                   /* extern */
s32 fn_800A5A54(...);                                                     /* extern */
s32 fn_800A6334();                                                        /* extern */
M2C_UNK fn_800A7088(TObject*, M2C_UNK);                                   /* extern */
M2C_UNK fn_800A714C();                                                    /* extern */
s32 fn_800AF3AC(M2C_UNK*);                                                /* extern */
M2C_UNK fn_800B4A38(M2C_UNK, void*, void*, M2C_UNK, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK fn_800CCC6C(const char*);                                         /* extern */
s32 fn_800D7A94(s32, s32, s32);                                           /* extern */
f32 fn_800D7B00(s32);                                                     /* extern */
M2C_UNK fn_800F46B0();                                                    /* extern */
M2C_UNK fn_800FE248(M2C_UNK, M2C_UNK*);                                   /* extern */
M2C_UNK fn_800FE274(M2C_UNK, M2C_UNK*);                                   /* extern */
void** fn_800FE3FC();                                                     /* extern */
M2C_UNK fn_800FE464();                                                    /* extern */
s32 fn_8010022C(u32, M2C_UNK, M2C_UNK);                                   /* extern */
u32 fn_80100280(u32, M2C_UNK, M2C_UNK);                                   /* extern */
u32 fn_80100328(u32, M2C_UNK, M2C_UNK);                                   /* extern */
u32 fn_8010037C(u32, M2C_UNK, M2C_UNK);                                   /* extern */
M2C_UNK fn_801007F4(u32, M2C_UNK);                                        /* extern */
M2C_UNK fn_8010096C(u32, M2C_UNK, const void*);                           /* extern */
M2C_UNK fn_80100AAC();                                                    /* extern */
s32 fn_80100BF8(u8);                                                      /* extern */
s32 fn_80100C88(u8);                                                      /* extern */
s32 fn_80103178(M2C_UNK);                                                 /* extern */
M2C_UNK fn_80111260(void*, M2C_UNK);                                      /* extern */
M2C_UNK fn_80113874(M2C_UNK);                                             /* extern */
M2C_UNK fn_801138B4();                                                    /* extern */
M2C_UNK fn_801138F4();                                                    /* extern */
M2C_UNK fn_80113940();                                                    /* extern */
u32 fn_8011B5A8(s32, s32);                                                /* extern */
M2C_UNK fn_8011B844(u32, void*, f32);                                     /* extern */
M2C_UNK fn_8012D9D0();                                                    /* extern */
s32 fn_8012DA08();                                                        /* extern */
M2C_UNK fn_80130B40(u8);                                                  /* extern */
f32 fn_80132958(M2C_UNK);                                                 /* extern */
M2C_UNK fn_801329AC();                                                    /* extern */
M2C_UNK fn_80133090(M2C_UNK*, M2C_UNK*);                                  /* extern */
M2C_UNK fn_80137FE8(void*);                                               /* extern */
M2C_UNK fn_8014FF2C(...);                                                 /* extern */
M2C_UNK fn_8014FFBC(u32, M2C_UNK*, u32*);                                 /* extern */
void* fn_80150588(...);                                                   /* extern */
M2C_UNK fn_80150958();                                                    /* extern */
M2C_UNK fn_80194234(M2C_UNK, M2C_UNK);                                    /* extern */
void* fn_8019E8EC();                                                      /* extern */
M2C_UNK fn_8019EB94(s32, void*, M2C_UNK);                                 /* extern */
M2C_UNK fn_8019ECCC(s32, void*, M2C_UNK);                                 /* extern */
M2C_UNK fn_8019ED68(...);                                                 /* extern */
M2C_UNK fn_801B95EC(s32, struct _struct_lbl_8_data_15E0C_0xC (*)[], s32); /* extern */
s32 fn_801C28D8();                                                        /* extern */
s32 fn_8_9832C(s32);                                                      /* extern */
s32 fn_8_98464();                                                         /* extern */
M2C_UNK fn_8_98480(void*);                                                /* extern */
M2C_UNK fn_8_9897C();                                                     /* extern */
s32 fn_8_98B08();                                                         /* extern */
s32 fn_8_98B94();                                                         /* extern */
M2C_UNK fn_8_9D81C(s32);                                                  /* extern */
M2C_UNK fn_8_A2A00(TObject*);                                             /* extern */
M2C_UNK fn_8_A2A78(TObject*);                                             /* extern */
void** fn_8_A31D4();                                                      /* extern */
M2C_UNK fn_8_D06B8(u32);                                                  /* extern */
M2C_UNK fn_8_D07F4(u32);                                                  /* extern */
s32 fn_8_D2190();                                                         /* extern */
M2C_UNK fn_8_D8E90(M2C_UNK, M2C_UNK, M2C_UNK);                            /* extern */
extern M2C_UNK fn_8005BF88;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_8029BBD0;
extern M2C_UNK lbl_8029C310;
extern void* lbl_80303DC8;
extern TObject* lbl_8042C0FC;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C380;
extern u32 lbl_8042C388;
extern u32 lbl_8042C590;
extern void* lbl_8042C610;
extern u32 lbl_8042C6E4;
extern M2C_UNK lbl_8_rodata_17DC;
extern s32 lbl_8_rodata_17E8;
static M2C_UNK lbl_8_data_15A70; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15B0C; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15B24; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15B78; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15BF0; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15D24; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15DC0; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15DC4; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_15DD8 = "TObjEnemyEggMobile";
static M2C_UNK lbl_8_data_15DDC; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15DE8; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15DF4; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15E00; /* unable to generate initializer: unknown type */
static struct _struct_lbl_8_data_15E0C_0xC lbl_8_data_15E0C[4]
    = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
static M2C_UNK lbl_8_data_15E3C; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_15E4C = "TZakoRushCtrl";
static M2C_UNK lbl_8_data_15E50; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15E7C; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15E8C; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15EA4; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15EBC; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15F64; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15F78; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_bss_18A8;
static u32 lbl_8_bss_18C4;
static u32 lbl_8_bss_18C8[0x11];
static s32 lbl_8_bss_190C;
static s32 lbl_8_bss_1910;
static TObject* lbl_8_bss_1914;
static M2C_UNK lbl_8_bss_1918;
static struct _struct_lbl_8_rodata_17F4_0xC lbl_8_rodata_17F4[6] = {
	{ 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f },
	{ 10000.0f, 0.0f, 0.0f },
	{ 10000.0f, -500.0f, -4000.0f },
	{ 0.0f, 0.0f, -4000.0f },
	{ 0.0f, 0.0f, -8000.0f },
}; /* const */
static M2C_UNK lbl_8_rodata_183C;
static M2C_UNK lbl_8_rodata_1854; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_186C; /* unable to generate initializer: unknown type; const */
static f32 lbl_8_rodata_1874;
static f32 lbl_8_rodata_1878;
static f32 lbl_8_rodata_187C;
static f32 lbl_8_rodata_1880;
static f32 lbl_8_rodata_1884;
static f32 lbl_8_rodata_1888;
static f64 lbl_8_rodata_1890;
static f32 lbl_8_rodata_1898;
static f32 lbl_8_rodata_189C[4];

extern "C" {

void fn_8_9DA00(s32 arg0)
{
	fn_8_9D81C(arg0 - 0x28);
}

void fn_8_9DA08(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 0x15;
}

void fn_8_9DA28(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 0x2F;
}

void fn_8_9DA48(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x2E;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				if (fn_8_9832C(M2C_FIELD(arg0, s32*, 0x14)) != 0) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 0xE;
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 0);
					return;
				}
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xF;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			} else {
				return;
			}
			break;
	}
}

void fn_8_9DB5C(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* switch 1; irregular */
		case 0:     /* switch 1 */
			M2C_FIELD(arg0, s32*, 0x18) = 0x258;
			M2C_FIELD(arg0, s32*, 0x10) = 0x2D;
			return;
		case 1: /* switch 1 */
			temp_r0 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x570);
			switch (temp_r0) { /* switch 2; irregular */
				case 1:        /* switch 2 */
					fn_80137FE8((u8*)arg0 + 0x18);
					if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
						M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 3);
						M2C_FIELD(arg0, s32*, 4) = 7;
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 0);
						return;
					}
					return;
				case 2: /* switch 2 */
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
					    M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 0xD;
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 0);
					break;
			}
			break;
	}
}

M2C_UNK** fn_8_9DC74(M2C_UNK** arg0, s16 arg1)
{
	s32 temp_cr0_eq;

	temp_cr0_eq = arg0 == NULL;
	if (temp_cr0_eq == 0) {
		*arg0 = &lbl_8_data_15A70;
		if (temp_cr0_eq == 0) {
			*arg0 = &lbl_8_data_15B24;
			if (temp_cr0_eq == 0) {
				*arg0 = &lbl_8_data_15B0C;
			}
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_9DCE8(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_15B0C;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_15B24;
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_15A70;
}

void fn_8_9DD28(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 6;
}

void fn_8_9DD48(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xB4;
			M2C_FIELD(arg0, s32*, 0x10) = 9;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0x11;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_9DE00(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x258;
			M2C_FIELD(arg0, s32*, 0x10) = 0x2D;
			return;
		case 1:
			if ((s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x570) == 1) {
				fn_80137FE8((u8*)arg0 + 0x18);
				if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 7;
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				}
			}
			return;
	}
}

void fn_8_9DEC8(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x2C;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) && (fn_800A6334() == 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_9DF7C(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 0x25;
}

void fn_8_9DF9C(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xA;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_9E054(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 0x1A;
}

void fn_8_9E074(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x20;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_9E12C(void* arg0, s32 arg1)
{
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			temp_r3 = M2C_FIELD(arg0, void**, 0x14);
			if (temp_r3 != NULL) {
				M2C_FIELD(arg0, s32*, 0x18) = (s32)M2C_FIELD(temp_r3, s32*, 0x584);
			}
			M2C_FIELD(arg0, s32*, 0x10) = 0x1F;
			return;
		case 1:
			if (((void*)M2C_FIELD(arg0, void**, 0x14) != NULL) && (fn_8_98B08() == 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 7;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_9E250(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 0x1D;
}

void fn_8_9E270(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) && (fn_8_98B08() != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xB;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_9E324(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) && (fn_8_98B94() != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				return;
			}
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) && (fn_8_98464() != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_9E43C(void* arg0, void* arg1)
{
	s32 temp_r0;
	void* temp_r4;

	M2C_FIELD(arg0, void**, 0x14) = arg1;
	temp_r4                       = M2C_FIELD(arg0, void**, 0x14);
	if (temp_r4 != NULL) {
		temp_r0 = M2C_FIELD(temp_r4, s32*, 0x580);
		switch (temp_r0) { /* irregular */
			case 0:
				M2C_FIELD(arg0, s32*, 0xC)  = 0;
				M2C_FIELD(arg0, s32*, 0x10) = 0;
				M2C_FIELD(arg0, s32*, 4)    = 0;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 0);
				if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
					fn_800A31B8(M2C_FIELD(arg0, void**, 0x14));
					return;
				}
				break;
			case 1:
				M2C_FIELD(arg0, s32*, 0xC)  = 1;
				M2C_FIELD(arg0, s32*, 0x10) = 0;
				M2C_FIELD(arg0, s32*, 4)    = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 0);
				if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
					fn_800A31B8(M2C_FIELD(arg0, void**, 0x14));
				}
				break;
		}
	}
}

s32 fn_8_9E510(void* arg0)
{
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r30;
	s32 temp_r3_3;
	s32 temp_r4;
	s32 var_r3;
	void* temp_r3;
	void* temp_r3_2;

	fn_8_98480(M2C_FIELD(arg0, void**, 0x14));
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
	if ((s32)M2C_FIELD(temp_r3, s32*, 0x280) != 0) {
		temp_r0 = M2C_FIELD(temp_r3, s32*, 0x19C);
		if (temp_r0 != 9) {
			if (temp_r0 < 9) {
				if (temp_r0 != 6) {
					if ((temp_r0 < 6) && (temp_r0 < 3)) {
						if (temp_r0 < 1) {
							goto block_14;
						}
						goto block_13;
					}
					goto block_14;
				}
				goto block_13;
			}
			if (temp_r0 != 0x2C) {
			block_14:
				fn_8_9897C();
				goto block_15;
			}
			goto block_13;
		}
	block_13:
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 0xC;
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
block_15:
	temp_r3_2 = M2C_FIELD(arg0, void**, 0x14);
	temp_r0_2 = M2C_FIELD(temp_r3_2, s32*, 0x248);
	if (temp_r0_2 != 0) {
		var_r3 = 0;
		switch (temp_r0_2) { /* irregular */
			case 2:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 46:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xD;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 9:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0x10;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x248) = 0;
		return var_r3;
	}
	temp_r4 = M2C_FIELD(temp_r3_2, s32*, 0x18C);
	if ((u32)(temp_r4 & 0x1000) != 0) {
		temp_r0_3 = M2C_FIELD(temp_r3_2, s32*, 0x19C);
		if (temp_r0_3 != 0x1D) {
			if (temp_r0_3 < 0x1D) {
				if (temp_r0_3 != 0x1A) {
					goto block_35;
				}
				goto block_34;
			}
			if (temp_r0_3 < 0x26) {
				if (temp_r0_3 < 0x24) {
					goto block_35;
				}
				goto block_34;
			}
		block_35:
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
			    arg0, M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 8;
			M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
			    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			return 1;
		}
	block_34:
		return 0;
	}
	temp_r3_3 = M2C_FIELD(temp_r3_2, s32*, 0x19C);
	if (temp_r3_3 != 0x1A) {
		if ((u32)(temp_r4 & 0x2000) != 0) {
			if (temp_r3_3 != 9) {
				if (temp_r3_3 < 9) {
					if (temp_r3_3 != 6) {
						if ((temp_r3_3 < 6) && (temp_r3_3 < 3)) {
							if (temp_r3_3 < 1) {
								goto block_50;
							}
							goto block_49;
						}
						goto block_50;
					}
					goto block_49;
				}
				if (temp_r3_3 != 0x2C) {
				block_50:
					return 0;
				}
				goto block_49;
			}
		block_49:
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
			    arg0, M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 9;
			M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
			    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			return 1;
		}
		return 0;
	}
	temp_r30                 = M2C_FIELD(arg0, s32*, 8);
	M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
	M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
	    arg0, M2C_FIELD(arg0, s32*, 4), 3);
	M2C_FIELD(arg0, s32*, 4) = temp_r30;
	M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
	    arg0, M2C_FIELD(arg0, s32*, 4), 0);
	return 1;
}

void fn_8_9E924(void** arg0, u32 arg1, s32 arg2)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x18)(arg2);
			return;
		case 1:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x1C)(arg2);
			return;
		case 5:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x20)(arg2);
			return;
		case 6:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x24)(arg2);
			return;
		case 7:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x28)(arg2);
			return;
		case 8:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x2C)(arg2);
			return;
		case 9:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x30)(arg2);
			return;
		case 10:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x34)(arg2);
			return;
		case 11:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x38)(arg2);
			return;
		case 12:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x3C)(arg2);
			return;
		case 13:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x40)(arg2);
			return;
		case 14:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x44)(arg2);
			return;
		case 15:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x48)(arg2);
			return;
		case 17:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x50)(arg2);
			return;
		case 16:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x4C)(arg2);
			/* fallthrough */
		default:
			return;
	}
}

M2C_UNK** fn_8_9EAC4(M2C_UNK** arg0, s16 arg1)
{
	s32 temp_cr0_eq;

	temp_cr0_eq = arg0 == NULL;
	if (temp_cr0_eq == 0) {
		*arg0 = &lbl_8_data_15B24;
		if (temp_cr0_eq == 0) {
			*arg0 = &lbl_8_data_15B0C;
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_9EB28(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_15B0C;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_15B24;
}

M2C_UNK** fn_8_9EB5C(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = &lbl_8_data_15B0C;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_9EBAC(void) { }

void fn_8_9EBB0(void) { }

void fn_8_9EBB4(void) { }

void fn_8_9EBB8(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2C) = 1;
			return;
		case 1:
			if (((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) == 0)
			    && ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) == 0)) {
				if ((TObject*)lbl_8_bss_1914 != NULL) {
					lbl_8_bss_1914->unk260 = 0x5C;
				}
				M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
				return;
			}
			return;
	}
}

void fn_8_9EC40(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			if (fn_80100BF8(M2C_FIELD(arg0, u8*, 0x34)) == 0) {
				M2C_FIELD(arg0, s32*, 0x28) = 3;
				M2C_FIELD(arg0, s32*, 0x2C) = 0;
				return;
			}
			fn_80130B40(M2C_FIELD(arg0, u8*, 0x34));
			M2C_FIELD(arg0, s32*, 0x2C) = 1;
			return;
		case 1:
			if (fn_80100C88(M2C_FIELD(arg0, u8*, 0x34)) != 0) {
				M2C_FIELD(arg0, u8*, 0x34)  = (u8)(M2C_FIELD(arg0, u8*, 0x34) + 1);
				M2C_FIELD(arg0, s32*, 0x30) = 0xF0;
				M2C_FIELD(arg0, s32*, 0x2C) = 2;
				return;
			}
			return;
		case 2:
			fn_80137FE8((u8*)arg0 + 0x30);
			if ((s32)M2C_FIELD(arg0, s32*, 0x30) < 0) {
				M2C_FIELD(arg0, s32*, 0x2C) = 0;
			}
			break;
	}
}

void fn_8_9ED10(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2C) = 1;
			return;
		case 1:
			M2C_FIELD(arg0, s32*, 0x2C) = 2;
			return;
		case 2:
			M2C_FIELD(arg0, s32*, 0x28) = 2;
			M2C_FIELD(arg0, s32*, 0x2C) = 0;
			return;
	}
}

void fn_8_9ED60(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2C) = 1;
			return;
		case 1:
			M2C_FIELD(arg0, s32*, 0x2C) = 2;
			return;
		case 2:
			M2C_FIELD(arg0, s32*, 0x28) = 1;
			M2C_FIELD(arg0, s32*, 0x2C) = 0;
			return;
	}
}

void fn_8_9EDB0(void) { }

void fn_8_9EDB4(void* arg0)
{
	s32 temp_r4;
	u8 var_r6;
	u8 var_r7;

	var_r6  = 1;
	var_r7  = 1;
	temp_r4 = M2C_FIELD(&lbl_8029C310, s32*, 0x18) - 1;
	if ((u32)((u32)((1 | ~temp_r4) - ((u32)(1 - temp_r4) >> 1U)) >> 0x1FU) == 0) {
		var_r7 = 0;
	}
	if ((var_r7 == 0) && ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x18) != 3)) {
		var_r6 = 0;
	}
	if ((s32)var_r6 != 0) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	fn_801B95EC(M2C_FIELD(arg0, s32*, 0x2C),
	    (struct _struct_lbl_8_data_15E0C_0xC(*)[])lbl_8_data_15E0C,
	    M2C_FIELD(arg0, s32*, 0x28) * 0xC);
}

TObject* fn_8_9EE60(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_15E50;
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_9EED4(TObject* arg0, TObject* arg1)
{
	__ct__7TObjectFP7TObject(arg0, arg1);
	arg0->unk18 = &lbl_8_data_15E50;
	arg0->unk0  = lbl_8_data_15E4C;
	arg0->unk1E = 0x38;
	arg0->unk30 = 0;
	arg0->unk34 = 0;
	arg0->unk28 = 0;
	arg0->unk2C = 0;
	return arg0;
}

void fn_8_9EF3C(void)
{
	TObject* temp_r3;

	temp_r3 = fn_80018A34(lbl_8042C148, 0x38);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C0FC);
		temp_r3->unk18 = &lbl_8_data_15E50;
		temp_r3->unk0  = lbl_8_data_15E4C;
		temp_r3->unk1E = 0x38;
		temp_r3->unk30 = 0;
		temp_r3->unk34 = 0;
		temp_r3->unk28 = 0;
		temp_r3->unk2C = 0;
	}
}

void fn_8_9EFC8(void* arg0)
{
	M2C_UNK* var_r29;
	s32 temp_r31;
	s32 temp_r3;
	s32 temp_r3_2;
	s32 var_r4;
	u8 var_r3;
	u8 var_r3_2;

	temp_r31 = M2C_FIELD(&lbl_8029C310, s32*, 0x2C);
	var_r4   = 0;
	if (((void*)lbl_80303DC8 != NULL) && ((s32)M2C_FIELD(lbl_80303DC8, s32*, 0x34) == 2)) {
		var_r4 = 1;
	}
	if (temp_r31 == 0x15) {
		if (var_r4 != 0) {
			var_r29 = &lbl_8_rodata_186C + 6;
		} else {
			var_r29 = &lbl_8_rodata_186C + 2;
		}
	} else if (var_r4 != 0) {
		var_r29 = &lbl_8_rodata_186C + 4;
	} else {
		var_r29 = &lbl_8_rodata_186C;
	}
	if (((u32)(M2C_FIELD(arg0, s32*, 0x278) & 8) == 0)
	    && (fn_80100C88(M2C_FIELD(var_r29, u8*, 0)) != 0)) {
		M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) | 8);
		if (fn_80103178(0) != -1) {
			if (temp_r31 == 0x15) {
				fn_80111260(lbl_8042C610, 0x92);
			} else {
				fn_80111260(lbl_8042C610, 0x92);
			}
		}
	}
	if (((u32)(M2C_FIELD(arg0, s32*, 0x278) & 0x10) == 0)
	    && (fn_80100C88(M2C_FIELD(var_r29, u8*, 1)) != 0)) {
		M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) | 0x10);
		if (fn_80103178(0) != -1) {
			if (temp_r31 == 0x15) {
				fn_80111260(lbl_8042C610, 0x93);
			} else {
				fn_80111260(lbl_8042C610, 0x93);
			}
		}
	}
	temp_r3 = M2C_FIELD(arg0, s32*, 0x278);
	if (((u32)(temp_r3 & 8) != 0) && ((u32)(temp_r3 & 1) == 0)) {
		var_r3 = 0;
		if (((s32)M2C_FIELD(lbl_8042C610, s32*, 0x30) == 0)
		    && ((s32)M2C_FIELD(lbl_8042C610, s32*, 0x3C) == 0)
		    && ((s32)M2C_FIELD(lbl_8042C610, s32*, 0x58) == -1)) {
			var_r3 = 1;
		}
		if (var_r3 != 0) {
			M2C_FIELD(arg0, s32*, 0x260) = 0x43;
			M2C_FIELD(arg0, s32*, 0x274) = 1;
			M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) | 1);
		}
	}
	temp_r3_2 = M2C_FIELD(arg0, s32*, 0x278);
	if (((u32)(temp_r3_2 & 0x10) != 0) && ((u32)(temp_r3_2 & 2) == 0)) {
		var_r3_2 = 0;
		if (((s32)M2C_FIELD(lbl_8042C610, s32*, 0x30) == 0)
		    && ((s32)M2C_FIELD(lbl_8042C610, s32*, 0x3C) == 0)
		    && ((s32)M2C_FIELD(lbl_8042C610, s32*, 0x58) == -1)) {
			var_r3_2 = 1;
		}
		if (var_r3_2 != 0) {
			M2C_FIELD(arg0, s32*, 0x260) = 0x43;
			M2C_FIELD(arg0, s32*, 0x274) = 2;
			M2C_FIELD(arg0, s32*, 0x278) = (s32)(M2C_FIELD(arg0, s32*, 0x278) | 2);
		}
	}
}

s32 fn_8_9F268(void* arg0)
{
	s32 var_r31;
	void* temp_r3;
	void* temp_r5;

	var_r31 = 0;
	temp_r5 = M2C_FIELD(arg0, void**, 0xB0);
	if (((s32)((M2C_FIELD(temp_r5, s32*, 0x18) & 0x04000000) != 0) == 1)
	    && (fn_800A2BE0(M2C_FIELD(temp_r5, u8*, 0x2A)) != 0)) {
		temp_r3                        = M2C_FIELD(arg0, void**, 0xB0);
		M2C_FIELD(temp_r3, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3, s32*, 0x18) & 0xFBFFFFFF);
		var_r31                        = 1;
	}
	return var_r31;
}

void fn_8_9F2E4(void* arg0)
{
	if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
		M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 0xC);
		M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 0x10);
		M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 0x14);
		M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0xC);
		M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0x10);
		M2C_FIELD(arg0, s32*, 0x154) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0x14);
		return;
	}
	M2C_FIELD(arg0, f32*, 0x140) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 8);
	M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0);
	M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 4);
	M2C_FIELD(arg0, s32*, 0x154) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 8);
}

void fn_8_9F380(void* arg0)
{
	struct _struct_lbl_8_rodata_17F4_0xC* temp_r4;
	struct _struct_lbl_8_rodata_17F4_0xC* temp_r4_2;

	if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
		temp_r4                      = &lbl_8_rodata_17F4[M2C_FIELD(arg0, s32*, 0x244) + 1];
		M2C_FIELD(arg0, f32*, 0x1CC) = (f32)temp_r4->unk0;
		M2C_FIELD(arg0, f32*, 0x1D0) = (f32)temp_r4->unk4;
		M2C_FIELD(arg0, f32*, 0x1D4) = (f32)temp_r4->unk8;
		return;
	}
	temp_r4_2                    = &lbl_8_rodata_17F4[M2C_FIELD(arg0, s32*, 0x244)];
	M2C_FIELD(arg0, f32*, 0x1CC) = (f32)temp_r4_2->unk0;
	M2C_FIELD(arg0, f32*, 0x1D0) = (f32)temp_r4_2->unk4;
	M2C_FIELD(arg0, f32*, 0x1D4) = (f32)temp_r4_2->unk8;
}

s32 fn_8_9F3F8(void* arg0)
{
	s32 temp_r31;

	temp_r31                     = fn_800A5A54();
	M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(
	    M2C_FIELD(arg0, s32*, 0x150), M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
	if (temp_r31 < 0x80) {
		M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
		return 1;
	}
	return 0;
}

void fn_8_9F460(void* arg0)
{
	s32 temp_r30;
	s32 var_r29;
	void* temp_r31;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r4;
	u8* var_r31;

	if ((u32)M2C_FIELD(arg0, u32*, 0x288) != 0U) {
		temp_r31 = fn_8019E8EC();
		temp_r3  = M2C_FIELD(arg0, void**, 0x27C);
		if (temp_r3 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3, s32*, 4), temp_r31, 0);
		}
		temp_r3_2 = M2C_FIELD(arg0, void**, 0x280);
		if (temp_r3_2 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_2, s32*, 4), temp_r31, 0);
		}
		temp_r3_3 = M2C_FIELD(arg0, void**, 0x284);
		if (temp_r3_3 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_3, s32*, 4), temp_r31, 0);
		}
		M2C_FIELD(arg0, f32*, 0x254) = (f32)M2C_FIELD(temp_r31, f32*, 0x30);
		M2C_FIELD(arg0, f32*, 0x258) = (f32)M2C_FIELD(temp_r31, f32*, 0x34);
		M2C_FIELD(arg0, f32*, 0x25C) = (f32)M2C_FIELD(temp_r31, f32*, 0x38);
	}
	var_r29 = 0;
	var_r31 = (u8*)arg0;
	do {
		if ((u32)M2C_FIELD(var_r31, u32*, 0x298) != 0U) {
			temp_r4 = M2C_FIELD(var_r31, void**, 0x2A4);
			if (temp_r4 != NULL) {
				temp_r30 = M2C_FIELD(temp_r4, s32*, 4);
				fn_8019ECCC(temp_r30, fn_8019E8EC(), 0);
			}
		}
		var_r31 += 4;
		var_r29 += 1;
	} while (var_r29 < 3);
}

void fn_8_9F560(void* arg0)
{
	f32 sp18;
	f32 sp1C;
	f32 sp20;
	f32 sp24;
	M2C_UNK sp8;

	if ((void*)M2C_FIELD(arg0, void**, 0x248) != NULL) {
		sp18 = M2C_FIELD(arg0, f32*, 0x24C);
		if (fn_800AF3AC(&sp8) != 0) {
			M2C_FIELD(arg0, f32*, 0x140) = sp1C;
			M2C_FIELD(arg0, f32*, 0x144) = sp20;
			M2C_FIELD(arg0, f32*, 0x148) = sp24;
		}
		if (M2C_FIELD(arg0, f32*, 0x24C) > M2C_FIELD(M2C_FIELD(arg0, void**, 0x248), f32*, 4)) {
			M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
		}
	}
	M2C_FIELD(arg0, s32*, 0x26C) = (s32)(M2C_FIELD(arg0, s32*, 0x26C) + 0x100);
	M2C_FIELD(arg0, f32*, 0x144)
	    = (f32)(M2C_FIELD(arg0, f32*, 0x144) + (4.0f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x26C))));
}

void fn_8_9F618(void* arg0)
{
	f32 sp18;
	f32 sp1C;
	f32 sp20;
	f32 sp24;
	M2C_UNK sp8;

	if ((void*)M2C_FIELD(arg0, void**, 0x248) != NULL) {
		sp18 = M2C_FIELD(arg0, f32*, 0x24C);
		if (fn_800AF3AC(&sp8) != 0) {
			M2C_FIELD(arg0, f32*, 0x140) = sp1C;
			M2C_FIELD(arg0, f32*, 0x144) = sp20;
			M2C_FIELD(arg0, f32*, 0x148) = sp24;
		}
		M2C_FIELD(arg0, f32*, 0x24C)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x24C) + M2C_FIELD(arg0, f32*, 0x250));
		if (M2C_FIELD(arg0, f32*, 0x24C) > M2C_FIELD(M2C_FIELD(arg0, void**, 0x248), f32*, 4)) {
			M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
		}
	}
	M2C_FIELD(arg0, s32*, 0x26C) = (s32)(M2C_FIELD(arg0, s32*, 0x26C) + 0x100);
	M2C_FIELD(arg0, f32*, 0x144)
	    = (f32)(M2C_FIELD(arg0, f32*, 0x144) + (4.0f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x26C))));
}

s32 fn_8_9F6E0(void)
{
	return 1;
}

void fn_8_9F6E8(void* arg0)
{
	s32 temp_r4;

	fn_80113940();
	if ((u32)M2C_FIELD(arg0, u32*, 0x280) != 0U) {
		fn_80194234(0x14, 1);
		fn_80113874(4);
		fn_8014FF2C(M2C_FIELD(arg0, u32*, 0x280));
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x284) != 0U) {
		fn_801138B4();
		fn_80113874(0x10);
		temp_r4 = M2C_FIELD(lbl_8042C180, s32*, 0x30);
		if ((s32)lbl_8_bss_190C != temp_r4) {
			lbl_8_bss_190C = temp_r4;
			fn_8011B844(lbl_8_bss_18C4, &lbl_8_rodata_187C, 1.0f);
			fn_8014FFBC(M2C_FIELD(arg0, u32*, 0x284), &fn_8005BF88, lbl_8_bss_18C8);
		}
		fn_8014FF2C(M2C_FIELD(arg0, u32*, 0x284));
	}
	fn_801138F4();
}

void fn_8_9F7BC(void* arg0)
{
	s32 var_r30;
	u8* var_r31;

	var_r31 = (u8*)arg0;
	fn_80113874(4);
	fn_8014FF2C(M2C_FIELD(var_r31, u32*, 0xE8));
	if (((u32)M2C_FIELD(var_r31, u32*, 0x27C) != 0U)
	    && ((s32)M2C_FIELD(var_r31, s32*, 0x19C) != 0x42)) {
		fn_8014FF2C();
	}
	var_r30 = 0;
	do {
		if ((u32)M2C_FIELD(var_r31, u32*, 0x2A4) != 0U) {
			fn_8014FF2C();
		}
		var_r31 += 4;
		var_r30 += 1;
	} while (var_r30 < 3);
}

void fn_8_9F83C(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	s32* var_r28;
	s32 temp_r0;
	s32 temp_r31;
	s32 var_r29;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	u8* var_r30;

	var_r30                         = (u8*)arg0;
	M2C_FIELD(var_r30, f32*, 0x250) = 0.5f;
	temp_r3                         = M2C_FIELD(var_r30, void**, 0xB0);
	M2C_FIELD(var_r30, f32*, 0x140) = (f32)M2C_FIELD(temp_r3, f32*, 0);
	M2C_FIELD(var_r30, f32*, 0x144) = (f32)M2C_FIELD(temp_r3, f32*, 4);
	M2C_FIELD(var_r30, f32*, 0x148) = (f32)M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2                       = M2C_FIELD(var_r30, void**, 0xB0);
	M2C_FIELD(var_r30, s32*, 0x14C) = (s32)M2C_FIELD(temp_r3_2, s32*, 0xC);
	M2C_FIELD(var_r30, s32*, 0x150) = (s32)M2C_FIELD(temp_r3_2, s32*, 0x10);
	M2C_FIELD(var_r30, s32*, 0x154) = (s32)M2C_FIELD(temp_r3_2, s32*, 0x14);
	M2C_FIELD(var_r30, f32*, 0x1C0) = (f32)M2C_FIELD(var_r30, f32*, 0x140);
	M2C_FIELD(var_r30, f32*, 0x1C4) = (f32)M2C_FIELD(var_r30, f32*, 0x144);
	M2C_FIELD(var_r30, f32*, 0x1C8) = (f32)M2C_FIELD(var_r30, f32*, 0x148);
	M2C_FIELD(var_r30, f32*, 0x1CC) = (f32)M2C_FIELD(var_r30, f32*, 0x140);
	M2C_FIELD(var_r30, f32*, 0x1D0) = (f32)M2C_FIELD(var_r30, f32*, 0x144);
	M2C_FIELD(var_r30, f32*, 0x1D4) = (f32)M2C_FIELD(var_r30, f32*, 0x148);
	M2C_FIELD(var_r30, f32*, 0x1C0) = (f32)M2C_FIELD(var_r30, f32*, 0x140);
	M2C_FIELD(var_r30, f32*, 0x1C4) = (f32)M2C_FIELD(var_r30, f32*, 0x144);
	M2C_FIELD(var_r30, f32*, 0x1C8) = (f32)M2C_FIELD(var_r30, f32*, 0x148);
	sp8                             = M2C_FIELD(&lbl_8_rodata_17DC, f32*, 0);
	spC                             = M2C_FIELD(&lbl_8_rodata_17DC, f32*, 4);
	sp10                            = M2C_FIELD(&lbl_8_rodata_17DC, f32*, 8);
	M2C_FIELD(var_r30, f32*, 0x1CC) = sp8;
	M2C_FIELD(var_r30, f32*, 0x1D0) = spC;
	M2C_FIELD(var_r30, f32*, 0x1D4) = sp10;
	M2C_FIELD(var_r30, s32*, 0x180) = 0x200;
	temp_r3_3                       = M2C_FIELD(var_r30, void**, 0xE8);
	if (temp_r3_3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3_3, s32*, 4);
		temp_r0  = M2C_FIELD(var_r30, s32*, 0x19C);
		if (temp_r0 != 0x43) {
			if ((temp_r0 < 0x43) && (temp_r0 < 3)) {
				if (temp_r0 < 1) {
					goto block_7;
				}
				goto block_6;
			}
		block_7:
			fn_8019ED68(temp_r31, &lbl_80239984, 0,
			    0.005493164f * (f32)M2C_FIELD(var_r30, s32*, 0x150), 0.005493164f);
		} else {
		block_6:
			fn_8019ED68(temp_r31, &lbl_80239984, 0,
			    180.0f + (0.005493164f * (f32)M2C_FIELD(var_r30, s32*, 0x150)), 0.005493164f,
			    180.0f);
		}
		fn_8019EB94(temp_r31, var_r30 + 0x140, 2);
		if ((u32)M2C_FIELD(var_r30, u32*, 0x288) == 0U) {
			M2C_FIELD(var_r30, u32*, 0x288) = fn_8011B5A8(temp_r31, 0xC1D);
		}
		var_r29 = 0;
		var_r28 = &lbl_8_rodata_17E8;
		do {
			if ((u32)M2C_FIELD(var_r30, u32*, 0x298) == 0U) {
				M2C_FIELD(var_r30, u32*, 0x298) = fn_8011B5A8(temp_r31, *var_r28);
			}
			var_r30 += 4;
			var_r28 += 4;
			var_r29 += 1;
		} while (var_r29 < 3);
	}
}

void fn_8_9FA94(void* arg0, M2C_UNK arg_sp0)
{
	s32* var_r27;
	s32 temp_r0;
	s32 temp_r31;
	s32 temp_r31_2;
	s32 var_r0;
	s32 var_r0_2;
	s32 var_r29;
	s32 var_r29_2;
	void** temp_r3;
	void* temp_r29;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;
	void* temp_r4;
	u8* var_r27_2;
	u8* var_r28;

	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x264) = var_r0;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0_2 = 0;
	} else {
		var_r0_2 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x268) = var_r0_2;
	temp_r3                      = M2C_FIELD(arg0, void***, 0x240);
	if (temp_r3 != NULL) {
		M2C_FIELD(*temp_r3, M2C_UNK(**)(void*), 0xC)(arg0);
	}
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(void*, s32, M2C_UNK), 0x50)(
	    arg0, M2C_FIELD(arg0, s32*, 0x19C), 1);
	temp_r3_2 = M2C_FIELD(arg0, void**, 0xE8);
	if (temp_r3_2 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3_2, s32*, 4);
		temp_r0  = M2C_FIELD(arg0, s32*, 0x19C);
		if (temp_r0 != 0x43) {
			if ((temp_r0 < 0x43) && (temp_r0 < 3)) {
				if (temp_r0 < 1) {
					goto block_19;
				}
				goto block_18;
			}
		block_19:
			fn_8019ED68(temp_r31, &lbl_80239984, 0,
			    0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150), 0.005493164f);
		} else {
		block_18:
			fn_8019ED68(temp_r31, &lbl_80239984, 0,
			    180.0f + (0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150)), 0.005493164f, 180.0f);
		}
		fn_8019EB94(temp_r31, (u8*)arg0 + 0x140, 2);
		if ((u32)M2C_FIELD(arg0, u32*, 0x288) == 0U) {
			M2C_FIELD(arg0, u32*, 0x288) = fn_8011B5A8(temp_r31, 0xC1D);
		}
		var_r29 = 0;
		var_r28 = (u8*)arg0;
		var_r27 = &lbl_8_rodata_17E8;
		do {
			if ((u32)M2C_FIELD(var_r28, u32*, 0x298) == 0U) {
				M2C_FIELD(var_r28, u32*, 0x298) = fn_8011B5A8(temp_r31, *var_r27);
			}
			var_r28 += 4;
			var_r27 += 4;
			var_r29 += 1;
		} while (var_r29 < 3);
	}
	fn_800A3D48(arg0);
	if ((u32)M2C_FIELD(arg0, u32*, 0x288) != 0U) {
		temp_r29  = fn_8019E8EC();
		temp_r3_3 = M2C_FIELD(arg0, void**, 0x27C);
		if (temp_r3_3 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_3, s32*, 4), temp_r29, 0);
		}
		temp_r3_4 = M2C_FIELD(arg0, void**, 0x280);
		if (temp_r3_4 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_4, s32*, 4), temp_r29, 0);
		}
		temp_r3_5 = M2C_FIELD(arg0, void**, 0x284);
		if (temp_r3_5 != NULL) {
			fn_8019ECCC(M2C_FIELD(temp_r3_5, s32*, 4), temp_r29, 0);
		}
		M2C_FIELD(arg0, f32*, 0x254) = (f32)M2C_FIELD(temp_r29, f32*, 0x30);
		M2C_FIELD(arg0, f32*, 0x258) = (f32)M2C_FIELD(temp_r29, f32*, 0x34);
		M2C_FIELD(arg0, f32*, 0x25C) = (f32)M2C_FIELD(temp_r29, f32*, 0x38);
	}
	var_r29_2 = 0;
	var_r27_2 = (u8*)arg0;
	do {
		if ((u32)M2C_FIELD(var_r27_2, u32*, 0x298) != 0U) {
			temp_r4 = M2C_FIELD(var_r27_2, void**, 0x2A4);
			if (temp_r4 != NULL) {
				temp_r31_2 = M2C_FIELD(temp_r4, s32*, 4);
				fn_8019ECCC(temp_r31_2, fn_8019E8EC(), 0);
			}
		}
		var_r27_2 += 4;
		var_r29_2 += 1;
	} while (var_r29_2 < 3);
	if ((u32)M2C_FIELD(arg0, u32*, 0x2B0) != 0U) {
		fn_800FE464();
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x268) != 0) {
		fn_8_9EFC8(arg0);
	}
	if ((u32)lbl_8042C388 != 0U) {
		fn_800B4A38(0x4063, (u8*)arg0 + 0x254, arg0, 3, 0, 2);
	}
}

void fn_8_9FDF8(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 5;
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
				fn_80100AAC();
			}
			M2C_FIELD(&lbl_8_data_15B78, s32*, 8) = fn_8010022C(lbl_8042C590, 0xB, 9);
			fn_80133090(&lbl_8_data_15B78, &lbl_8_data_15B78);
			M2C_FIELD(arg0, f32*, 0x148)                          = 0.0f;
			M2C_FIELD(arg0, f32*, 0x144)                          = 0.0f;
			M2C_FIELD(arg0, f32*, 0x140)                          = 0.0f;
			M2C_FIELD(arg0, s32*, 0x154)                          = 0;
			M2C_FIELD(arg0, s32*, 0x150)                          = 0;
			M2C_FIELD(arg0, s32*, 0x14C)                          = 0;
			M2C_FIELD(M2C_FIELD(arg0, void**, 0x2B0), s32*, 0x1C) = 2;
			fn_8_D8E90(0x17, 0, -1);
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 0;
			fn_80018C4C(&lbl_8029BBD0);
			M2C_FIELD(&lbl_8029C310, s32*, 0x290) = 1;
			return;
		case 1:
			if ((s32)((M2C_FIELD(arg0, s32*, 0xC8) & 1) != 0) == 1) {
				M2C_FIELD(arg0, s32*, 0x260)         = 0x1D;
				M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 1;
				M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 1;
				M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 1;
				M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 1;
				M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 1;
				M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 1;
				fn_80018C64(&lbl_8029BBD0);
				return;
			}
		case 2:
			return;
		case 3:
			fn_801329AC();
			break;
	}
}

void fn_8_9FF78(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			fn_8005BC04((u8*)arg0 + 0xB0);
			return;
		case 1:
			if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) == 0) {
				fn_80019898(&lbl_8029C310, 0);
				M2C_FIELD(&lbl_8029C310, s32*, 0x290) = 0;
				M2C_FIELD(arg0, u16*, 4)              = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			}
			return;
	}
}

void fn_8_A0018(void* arg0, s32 arg1)
{
	u32* temp_r4;

	if (arg1 != 0) {
		if (arg1 >= 0) {
		}
	} else {
		M2C_FIELD(arg0, s32*, 0x244) = (s32)(M2C_FIELD(arg0, s32*, 0x244) + 1);
		M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
		temp_r4                      = M2C_FIELD(lbl_8042C380, u32**, 0x28);
		if ((u32)*temp_r4 != 0U) {
			M2C_FIELD(arg0, s32*, 0x248) = (s32) * (temp_r4 + (M2C_FIELD(arg0, s32*, 0x244) * 4));
		}
	}
}

void fn_8_A0078(void* arg0, s32 arg1)
{
	TObject* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 4;
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
				fn_80100AAC();
			}
			M2C_FIELD(&lbl_8_data_15B78, s32*, 8) = fn_8010022C(lbl_8042C590, 0xB, 6);
			fn_80133090(&lbl_8_data_15B78, &lbl_8_data_15B78);
			M2C_FIELD(arg0, f32*, 0x148)                          = 0.0f;
			M2C_FIELD(arg0, f32*, 0x144)                          = 0.0f;
			M2C_FIELD(arg0, f32*, 0x140)                          = 0.0f;
			M2C_FIELD(arg0, s32*, 0x154)                          = 0;
			M2C_FIELD(arg0, s32*, 0x150)                          = 0;
			M2C_FIELD(arg0, s32*, 0x14C)                          = 0;
			M2C_FIELD(arg0, s32*, 0x28C)                          = 0;
			M2C_FIELD(arg0, s32*, 0x290)                          = 0;
			M2C_FIELD(arg0, s32*, 0x294)                          = 0;
			M2C_FIELD(M2C_FIELD(arg0, void**, 0x2B0), s32*, 0x1C) = 1;
			fn_8_D8E90(0x12, 0, -1);
			fn_800CCC6C("SNG_STG22.adx");
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x28C) == 0) {
				if (((s32)M2C_FIELD(lbl_8042C180, s32*, 0x40) < 0) && (fn_80018C98() == 5)) {
					fn_8012D9D0();
					M2C_FIELD(arg0, s32*, 0x28C) = 1;
					M2C_FIELD(arg0, s32*, 0x290) = 0;
					return;
				}
			} else if ((s32)M2C_FIELD(arg0, s32*, 0x290) == 0) {
				if (fn_8012DA08() != 0) {
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 1;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 1;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 1;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 1;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 1;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 1;
					fn_80018C64(&lbl_8029BBD0);
					M2C_FIELD(arg0, s32*, 0x290) = 1;
					M2C_FIELD(arg0, s32*, 0x260) = 2;
					if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
						if (fn_80103178(0) != -1) {
							fn_80111260(lbl_8042C610, 0xAA);
						}
					} else if (fn_80103178(0) != -1) {
						fn_80111260(lbl_8042C610, 0x91);
					}
				} else {
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 0;
					fn_80018C4C(&lbl_8029BBD0);
				}
				if ((s32)M2C_FIELD(arg0, s32*, 0x294) == 0) {
					M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
					if (fn_80132958(0) == 310.0f) {
						M2C_FIELD(arg0, s32*, 0x294) = 1;
						temp_r3                      = fn_80018A34(lbl_8042C148, 0x38);
						if (temp_r3 != NULL) {
							__ct__7TObjectFP7TObject(temp_r3, lbl_8042C0FC);
							temp_r3->unk18 = &lbl_8_data_15E50;
							temp_r3->unk0  = lbl_8_data_15E4C;
							temp_r3->unk1E = 0x38;
							temp_r3->unk30 = 0;
							temp_r3->unk34 = 0;
							temp_r3->unk28 = 0;
							temp_r3->unk2C = 0;
							return;
						}
					}
				}
			} else {
				case 2:
					return;
			}
			break;
		case 3:
			fn_801329AC();
			break;
	}
}

void fn_8_A0354(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 1;
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
				fn_80100AAC();
			}
			M2C_FIELD(&lbl_8_data_15B78, s32*, 8) = fn_8010022C(lbl_8042C590, 0xB, 0x15);
			fn_80133090(&lbl_8_data_15B78, &lbl_8_data_15B78);
			M2C_FIELD(arg0, f32*, 0x148)         = 0.0f;
			M2C_FIELD(arg0, f32*, 0x144)         = 0.0f;
			M2C_FIELD(arg0, f32*, 0x140)         = 0.0f;
			M2C_FIELD(arg0, s32*, 0x154)         = 0;
			M2C_FIELD(arg0, s32*, 0x150)         = 0;
			M2C_FIELD(arg0, s32*, 0x14C)         = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 0;
			fn_80018C4C(&lbl_8029BBD0);
			return;
		case 1:
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 0;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 0;
			fn_80018C4C(&lbl_8029BBD0);
			return;
		case 3:
			fn_801329AC();
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 1;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 1;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 1;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 1;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 1;
			M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 1;
			fn_80018C64(&lbl_8029BBD0);
			/* fallthrough */
		case 2:
			return;
	}
}

void fn_8_A04A8(void* arg0, s32 arg1)
{
	f32 sp18;
	f32 sp1C;
	f32 sp20;
	f32 sp24;
	M2C_UNK sp8;
	s32 temp_r0;

	switch (arg1) { /* switch 1; irregular */
		case 0:     /* switch 1 */
			temp_r0 = M2C_FIELD(arg0, s32*, 0x274);
			switch (temp_r0) { /* switch 2; irregular */
				case 0:        /* switch 2 */
					if ((0.000030517578f * (f32)fn_801C28D8()) < 0.5f) {
						fn_8_D8E90(0x13, 0, -1);
					} else {
						fn_8_D8E90(0x14, 0, -1);
					}
					break;
				case 1: /* switch 2 */
					fn_8_D8E90(0x15, 0, -1);
					break;
				case 2: /* switch 2 */
					fn_8_D8E90(0x16, 0, -1);
					break;
				case 3: /* switch 2 */
					fn_8_D8E90(0x17, 0, -1);
					break;
			}
			M2C_FIELD(arg0, s32*, 0x274) = 0;
			return;
		case 1: /* switch 1 */
			if ((s32)M2C_FIELD(arg0, s32*, 0x264) != 0) {
				if ((void*)M2C_FIELD(arg0, void**, 0x248) != NULL) {
					sp18 = M2C_FIELD(arg0, f32*, 0x24C);
					if (fn_800AF3AC(&sp8) != 0) {
						M2C_FIELD(arg0, f32*, 0x140) = sp1C;
						M2C_FIELD(arg0, f32*, 0x144) = sp20;
						M2C_FIELD(arg0, f32*, 0x148) = sp24;
					}
					if (M2C_FIELD(arg0, f32*, 0x24C)
					    > M2C_FIELD(M2C_FIELD(arg0, void**, 0x248), f32*, 4)) {
						M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
					}
				}
				M2C_FIELD(arg0, s32*, 0x26C) = (s32)(M2C_FIELD(arg0, s32*, 0x26C) + 0x100);
				M2C_FIELD(arg0, f32*, 0x144) = (f32)(M2C_FIELD(arg0, f32*, 0x144)
				    + (4.0f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x26C))));
			}
			return;
	}
}

void fn_8_A0668(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 2;
			if (((u32)lbl_8042C6E4 != 0U) && (fn_8_D2190() != 0)) {
				fn_8_D06B8(lbl_8042C6E4);
				fn_8_D07F4(lbl_8042C6E4);
			}
			if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
				M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 0xC);
				M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 0x10);
				M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 0x14);
				M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0xC);
				M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0x10);
				M2C_FIELD(arg0, s32*, 0x154) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0x14);
				return;
			}
			M2C_FIELD(arg0, f32*, 0x140) = 0.0f;
			M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 4);
			M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 8);
			M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0);
			M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 4);
			M2C_FIELD(arg0, s32*, 0x154) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 8);
			return;
		case 1:
			if ((s32)M2C_FIELD(lbl_8042C180, s32*, 0x40) < 0) {
				M2C_FIELD(arg0, s32*, 0x260) = 0x44;
			}
			return;
	}
}

void fn_8_A07B4(void* arg0, s32 arg1)
{
	f32 sp5C;
	f32 sp60;
	f32 sp64;
	f32 sp68;
	M2C_UNK sp4C;
	f32 sp18;
	f32 sp1C;
	f32 sp20;
	f32 sp24;
	M2C_UNK sp8;
	f32 temp_f1;
	f32 temp_f1_2;
	s32 temp_r30;
	struct _struct_lbl_8_rodata_17F4_0xC* temp_r3;
	struct _struct_lbl_8_rodata_17F4_0xC* temp_r3_2;

	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
				temp_r3                      = &lbl_8_rodata_17F4[M2C_FIELD(arg0, s32*, 0x244) + 1];
				M2C_FIELD(arg0, f32*, 0x1CC) = (f32)temp_r3->unk0;
				M2C_FIELD(arg0, f32*, 0x1D0) = (f32)temp_r3->unk4;
				M2C_FIELD(arg0, f32*, 0x1D4) = (f32)temp_r3->unk8;
			} else {
				temp_r3_2                    = &lbl_8_rodata_17F4[M2C_FIELD(arg0, s32*, 0x244)];
				M2C_FIELD(arg0, f32*, 0x1CC) = (f32)temp_r3_2->unk0;
				M2C_FIELD(arg0, f32*, 0x1D0) = (f32)temp_r3_2->unk4;
				M2C_FIELD(arg0, f32*, 0x1D4) = (f32)temp_r3_2->unk8;
			}
			M2C_FIELD(arg0, s32*, 0xD4) = 2;
			if ((void*)M2C_FIELD(arg0, void**, 0x248) != NULL) {
				sp5C = M2C_FIELD(arg0, f32*, 0x24C);
				if (fn_800AF3AC(&sp4C) != 0) {
					M2C_FIELD(arg0, f32*, 0x140) = sp60;
					M2C_FIELD(arg0, f32*, 0x144) = sp64;
					M2C_FIELD(arg0, f32*, 0x148) = sp68;
				}
				M2C_FIELD(arg0, f32*, 0x24C)
				    = (f32)(M2C_FIELD(arg0, f32*, 0x24C) + M2C_FIELD(arg0, f32*, 0x250));
				if (M2C_FIELD(arg0, f32*, 0x24C)
				    > M2C_FIELD(M2C_FIELD(arg0, void**, 0x248), f32*, 4)) {
					M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
				}
			}
			M2C_FIELD(arg0, s32*, 0x26C) = (s32)(M2C_FIELD(arg0, s32*, 0x26C) + 0x100);
			temp_f1                      = 4.0f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x26C));
			M2C_FIELD(arg0, f32*, 0x144) = (f32)(M2C_FIELD(arg0, f32*, 0x144) + temp_f1);
			fn_800A5A54(arg0, temp_f1);
			M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x264) != 0) {
				if ((void*)M2C_FIELD(arg0, void**, 0x248) != NULL) {
					sp18 = M2C_FIELD(arg0, f32*, 0x24C);
					if (fn_800AF3AC(&sp8) != 0) {
						M2C_FIELD(arg0, f32*, 0x140) = sp1C;
						M2C_FIELD(arg0, f32*, 0x144) = sp20;
						M2C_FIELD(arg0, f32*, 0x148) = sp24;
					}
					M2C_FIELD(arg0, f32*, 0x24C)
					    = (f32)(M2C_FIELD(arg0, f32*, 0x24C) + M2C_FIELD(arg0, f32*, 0x250));
					if (M2C_FIELD(arg0, f32*, 0x24C)
					    > M2C_FIELD(M2C_FIELD(arg0, void**, 0x248), f32*, 4)) {
						M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
					}
				}
				M2C_FIELD(arg0, s32*, 0x26C) = (s32)(M2C_FIELD(arg0, s32*, 0x26C) + 0x100);
				temp_f1_2                    = 4.0f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x26C));
				M2C_FIELD(arg0, f32*, 0x144) = (f32)(M2C_FIELD(arg0, f32*, 0x144) + temp_f1_2);
				temp_r30                     = fn_800A5A54(arg0, temp_f1_2);
				M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150),
				    M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
				if (temp_r30 < 0x80) {
					M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
				}
			}
			return;
	}
}

void fn_8_A0A10(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0xD4) = 0;
}

void fn_8_A0A30(void* arg0, s32 arg1, s32 arg2)
{
	f32 sp18;
	f32 sp1C;
	f32 sp20;
	f32 sp24;
	M2C_UNK sp8;
	s32 temp_r0;
	u32* temp_r3;

	switch (arg1) { /* switch 1; irregular */
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
			fn_8_A07B4((void*)arg2, 0);
			return;
		case 0x42:          /* switch 1 */
			switch (arg2) { /* switch 2; irregular */
				case 0:     /* switch 2 */
					M2C_FIELD(arg0, s32*, 0xD4) = 2;
					if (((u32)lbl_8042C6E4 != 0U) && (fn_8_D2190() != 0)) {
						fn_8_D06B8(lbl_8042C6E4);
						fn_8_D07F4(lbl_8042C6E4);
					}
					if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
						M2C_FIELD(arg0, f32*, 0x140)
						    = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 0xC);
						M2C_FIELD(arg0, f32*, 0x144)
						    = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 0x10);
						M2C_FIELD(arg0, f32*, 0x148)
						    = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 0x14);
						M2C_FIELD(arg0, s32*, 0x14C)
						    = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0xC);
						M2C_FIELD(arg0, s32*, 0x150)
						    = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0x10);
						M2C_FIELD(arg0, s32*, 0x154)
						    = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0x14);
						return;
					}
					M2C_FIELD(arg0, f32*, 0x140) = 0.0f;
					M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 4);
					M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(&lbl_8_rodata_183C, f32*, 8);
					M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 0);
					M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 4);
					M2C_FIELD(arg0, s32*, 0x154) = (s32)M2C_FIELD(&lbl_8_rodata_1854, s32*, 8);
					return;
				case 1: /* switch 2 */
					if ((s32)M2C_FIELD(lbl_8042C180, s32*, 0x40) < 0) {
						M2C_FIELD(arg0, s32*, 0x260) = 0x44;
						return;
					}
					break;
			}
			break;
		case 0x43:          /* switch 1 */
			switch (arg2) { /* switch 3; irregular */
				case 0:     /* switch 3 */
					temp_r0 = M2C_FIELD(arg0, s32*, 0x274);
					switch (temp_r0) { /* switch 4; irregular */
						case 0:        /* switch 4 */
							if ((0.000030517578f * (f32)fn_801C28D8()) < 0.5f) {
								fn_8_D8E90(0x13, 0, -1);
							} else {
								fn_8_D8E90(0x14, 0, -1);
							}
							break;
						case 1: /* switch 4 */
							fn_8_D8E90(0x15, 0, -1);
							break;
						case 2: /* switch 4 */
							fn_8_D8E90(0x16, 0, -1);
							break;
						case 3: /* switch 4 */
							fn_8_D8E90(0x17, 0, -1);
							break;
					}
					M2C_FIELD(arg0, s32*, 0x274) = 0;
					return;
				case 1: /* switch 3 */
					if ((s32)M2C_FIELD(arg0, s32*, 0x264) != 0) {
						if ((void*)M2C_FIELD(arg0, void**, 0x248) != NULL) {
							sp18 = M2C_FIELD(arg0, f32*, 0x24C);
							if (fn_800AF3AC(&sp8) != 0) {
								M2C_FIELD(arg0, f32*, 0x140) = sp1C;
								M2C_FIELD(arg0, f32*, 0x144) = sp20;
								M2C_FIELD(arg0, f32*, 0x148) = sp24;
							}
							if (M2C_FIELD(arg0, f32*, 0x24C)
							    > M2C_FIELD(M2C_FIELD(arg0, void**, 0x248), f32*, 4)) {
								M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
							}
						}
						M2C_FIELD(arg0, s32*, 0x26C) = (s32)(M2C_FIELD(arg0, s32*, 0x26C) + 0x100);
						M2C_FIELD(arg0, f32*, 0x144) = (f32)(M2C_FIELD(arg0, f32*, 0x144)
						    + (4.0f * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x26C))));
						return;
					}
					break;
			}
			break;
		case 0x41:          /* switch 1 */
			switch (arg2) { /* switch 5; irregular */
				case 0:     /* switch 5 */
					M2C_FIELD(arg0, s32*, 0xD4) = 1;
					if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
						fn_80100AAC();
					}
					M2C_FIELD(&lbl_8_data_15B78, s32*, 8) = fn_8010022C(lbl_8042C590, 0xB, 0x15);
					fn_80133090(&lbl_8_data_15B78, &lbl_8_data_15B78);
					M2C_FIELD(arg0, f32*, 0x148)         = 0.0f;
					M2C_FIELD(arg0, f32*, 0x144)         = 0.0f;
					M2C_FIELD(arg0, f32*, 0x140)         = 0.0f;
					M2C_FIELD(arg0, s32*, 0x154)         = 0;
					M2C_FIELD(arg0, s32*, 0x150)         = 0;
					M2C_FIELD(arg0, s32*, 0x14C)         = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 0;
					fn_80018C4C(&lbl_8029BBD0);
					return;
				case 1: /* switch 5 */
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 0;
					fn_80018C4C(&lbl_8029BBD0);
					return;
				case 3: /* switch 5 */
					fn_801329AC();
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 1;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 1;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 1;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 1;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 1;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 1;
					fn_80018C64(&lbl_8029BBD0);
					return;
			}
			break;
		case 0x44: /* switch 1 */
			fn_8_A0078(arg0, arg2);
			return;
		case 0x26: /* switch 1 */
			if (arg2 != NULL) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0x244) = (s32)(M2C_FIELD(arg0, s32*, 0x244) + 1);
				M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
				temp_r3                      = M2C_FIELD(lbl_8042C380, u32**, 0x28);
				if ((u32)*temp_r3 != 0U) {
					M2C_FIELD(arg0, void**, 0x248)
					    = (void*)*(temp_r3 + (M2C_FIELD(arg0, s32*, 0x244) * 4));
					return;
				}
			}
			break;
		case 0x1D:          /* switch 1 */
			switch (arg2) { /* switch 6; irregular */
				case 0:     /* switch 6 */
					fn_8005BC04((u8*)arg0 + 0xB0);
					return;
				case 1: /* switch 6 */
					if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) == 0) {
						fn_80019898(&lbl_8029C310, 0);
						M2C_FIELD(&lbl_8029C310, s32*, 0x290) = 0;
						M2C_FIELD(arg0, u16*, 4)              = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
						return;
					}
					break;
			}
			break;
		case 0x5C:          /* switch 1 */
			switch (arg2) { /* switch 7; irregular */
				case 0:     /* switch 7 */
					M2C_FIELD(arg0, s32*, 0xD4) = 5;
					if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
						fn_80100AAC();
					}
					M2C_FIELD(&lbl_8_data_15B78, s32*, 8) = fn_8010022C(lbl_8042C590, 0xB, 9);
					fn_80133090(&lbl_8_data_15B78, &lbl_8_data_15B78);
					M2C_FIELD(arg0, f32*, 0x148)                          = 0.0f;
					M2C_FIELD(arg0, f32*, 0x144)                          = 0.0f;
					M2C_FIELD(arg0, f32*, 0x140)                          = 0.0f;
					M2C_FIELD(arg0, s32*, 0x154)                          = 0;
					M2C_FIELD(arg0, s32*, 0x150)                          = 0;
					M2C_FIELD(arg0, s32*, 0x14C)                          = 0;
					M2C_FIELD(M2C_FIELD(arg0, void**, 0x2B0), s32*, 0x1C) = 2;
					fn_8_D8E90(0x17, 0, -1);
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 0;
					M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 0;
					fn_80018C4C(&lbl_8029BBD0);
					M2C_FIELD(&lbl_8029C310, s32*, 0x290) = 1;
					return;
				case 1: /* switch 7 */
					if ((s32)((M2C_FIELD(arg0, s32*, 0xC8) & 1) != 0) == 1) {
						M2C_FIELD(arg0, s32*, 0x260)         = 0x1D;
						M2C_FIELD(&lbl_8029BBD0, s32*, 0x18) = 1;
						M2C_FIELD(&lbl_8029BBD0, s32*, 0x1C) = 1;
						M2C_FIELD(&lbl_8029BBD0, s32*, 0x20) = 1;
						M2C_FIELD(&lbl_8029BBD0, s32*, 0x24) = 1;
						M2C_FIELD(&lbl_8029BBD0, s32*, 0x28) = 1;
						M2C_FIELD(&lbl_8029BBD0, s32*, 0x2C) = 1;
						fn_80018C64(&lbl_8029BBD0);
						return;
					}
					break;
				case 3: /* switch 7 */
					fn_801329AC();
					break;
			}
			break;
	}
}

s32 fn_8_A111C(s32 arg0)
{
	return fn_8005B8BC((s32)((u8*)arg0 + 0xB0)) != 0;
}

void fn_8_A114C(void* arg0)
{
	s32* var_r29;
	s32 temp_r0;
	s32 temp_r31;
	s32 var_r28;
	void* temp_r3;
	u8* var_r30;

	var_r30 = (u8*)arg0;
	temp_r3 = M2C_FIELD(var_r30, void**, 0xE8);
	if (temp_r3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3, s32*, 4);
		temp_r0  = M2C_FIELD(var_r30, s32*, 0x19C);
		if (temp_r0 != 0x43) {
			if ((temp_r0 < 0x43) && (temp_r0 < 3)) {
				if (temp_r0 < 1) {
					goto block_7;
				}
				goto block_6;
			}
		block_7:
			fn_8019ED68(temp_r31, &lbl_80239984, 0,
			    0.005493164f * (f32)M2C_FIELD(var_r30, s32*, 0x150), 0.005493164f);
		} else {
		block_6:
			fn_8019ED68(temp_r31, &lbl_80239984, 0,
			    180.0f + (0.005493164f * (f32)M2C_FIELD(var_r30, s32*, 0x150)), 0.005493164f,
			    180.0f);
		}
		fn_8019EB94(temp_r31, var_r30 + 0x140, 2);
		if ((u32)M2C_FIELD(var_r30, u32*, 0x288) == 0U) {
			M2C_FIELD(var_r30, u32*, 0x288) = fn_8011B5A8(temp_r31, 0xC1D);
		}
		var_r28 = 0;
		var_r29 = &lbl_8_rodata_17E8;
		do {
			if ((u32)M2C_FIELD(var_r30, u32*, 0x298) == 0U) {
				M2C_FIELD(var_r30, u32*, 0x298) = fn_8011B5A8(temp_r31, *var_r29);
			}
			var_r30 += 4;
			var_r29 += 4;
			var_r28 += 1;
		} while (var_r28 < 3);
	}
}

void fn_8_A12D4(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x2B0) != 0U) {
		dtor_800FE334(1);
		M2C_FIELD(arg0, u32*, 0x2B0) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2A4) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x2A4) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2A8) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x2A8) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x2AC) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x2AC) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x284) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x284) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x280) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x280) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x27C) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x27C) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

void fn_8_A13C0(void* arg0)
{
	void** var_r0;

	if ((void**)M2C_FIELD(arg0, void***, 0x2B0) != NULL) {
		dtor_800FE334(1);
		M2C_FIELD(arg0, void***, 0x2B0) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x2A4) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2A4) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x2A8) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2A8) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x2AC) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2AC) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x284) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x284) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x280) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x280) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x27C) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x27C) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	M2C_FIELD(arg0, void**, 0xE8) = fn_80150588(M2C_FIELD(&lbl_8_bss_18A8, s32*, 0));
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4) != 0U) {
		M2C_FIELD(arg0, void**, 0x27C) = fn_80150588();
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 8) != 0U) {
		M2C_FIELD(arg0, void**, 0x280) = fn_80150588();
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC) != 0U) {
		M2C_FIELD(arg0, void**, 0x284) = fn_80150588();
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10) != 0U) {
		M2C_FIELD(arg0, void**, 0x2A4) = fn_80150588();
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, void**, 0x2A8) = fn_80150588();
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18) != 0U) {
		M2C_FIELD(arg0, void**, 0x2AC) = fn_80150588();
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x27C) != NULL) {
		var_r0 = fn_80057644(0x4C);
		if (var_r0 != NULL) {
			var_r0 = fn_800FE3FC();
		}
		M2C_FIELD(arg0, void***, 0x2B0) = var_r0;
		M2C_FIELD(M2C_FIELD(arg0, void***, 0x2B0), void**, 0x30)
		    = (void*)M2C_FIELD(arg0, void**, 0x27C);
		M2C_FIELD(M2C_FIELD(arg0, void***, 0x2B0), M2C_UNK**, 0x2C) = &lbl_8_data_15D24;
		M2C_FIELD(M2C_FIELD(arg0, void***, 0x2B0), s32*, 0x1C)      = 0;
	}
}

void fn_8_A15BC(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	void* temp_r4;
	void* temp_r4_2;

	M2C_FIELD(arg0, f32*, 0x250) = 0.5f;
	temp_r4                      = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(temp_r4, f32*, 0);
	M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	temp_r4_2                    = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(temp_r4_2, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x154) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x14);
	M2C_FIELD(arg0, f32*, 0x1C0) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1C4) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1C8) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x1C0) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1C4) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1C8) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	sp8                          = M2C_FIELD(&lbl_8_rodata_17DC, f32*, 0);
	spC                          = M2C_FIELD(&lbl_8_rodata_17DC, f32*, 4);
	sp10                         = M2C_FIELD(&lbl_8_rodata_17DC, f32*, 8);
	M2C_FIELD(arg0, f32*, 0x1CC) = sp8;
	M2C_FIELD(arg0, f32*, 0x1D0) = spC;
	M2C_FIELD(arg0, f32*, 0x1D4) = sp10;
	M2C_FIELD(arg0, s32*, 0x180) = 0x200;
}

void fn_8_A1698(void* arg0)
{
	M2C_FIELD(arg0, s32*, 0x248) = 0;
	M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x250) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x25C) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x258) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x254) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x27C) = 0;
	M2C_FIELD(arg0, s32*, 0x280) = 0;
	M2C_FIELD(arg0, s32*, 0x284) = 0;
	M2C_FIELD(arg0, s32*, 0x288) = 0;
	M2C_FIELD(arg0, s32*, 0x240) = 0;
	M2C_FIELD(arg0, s32*, 0x260) = 0;
	M2C_FIELD(arg0, s32*, 0x264) = 1;
	M2C_FIELD(arg0, s32*, 0x268) = 1;
	M2C_FIELD(arg0, s32*, 0x244) = 0;
	M2C_FIELD(arg0, s32*, 0x26C) = 0;
	M2C_FIELD(arg0, s32*, 0x298) = 0;
	M2C_FIELD(arg0, s32*, 0x2A4) = 0;
	M2C_FIELD(arg0, s32*, 0x29C) = 0;
	M2C_FIELD(arg0, s32*, 0x2A8) = 0;
	M2C_FIELD(arg0, s32*, 0x2A0) = 0;
	M2C_FIELD(arg0, s32*, 0x2AC) = 0;
	M2C_FIELD(arg0, s32*, 0x2B0) = 0;
	M2C_FIELD(arg0, s32*, 0x274) = 0;
	M2C_FIELD(arg0, s32*, 0x278) = 0;
}

TObject* fn_8_A1714(TObject* arg0, s16 arg1)
{
	s32 temp_cr0_eq;
	void** temp_r3;

	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_15EBC;
		arg0->unkB4 = &lbl_8_data_15EBC + 0x2C;
		temp_r3     = arg0->unk240;
		temp_cr0_eq = temp_r3 == NULL;
		if (temp_cr0_eq == 0) {
			if (temp_cr0_eq == 0) {
				M2C_FIELD(*temp_r3, M2C_UNK(**)(M2C_UNK), 8)(1);
			}
			arg0->unk240 = NULL;
		}
		if ((u32)arg0->unk2B0 != NULL) {
			dtor_800FE334(1);
			arg0->unk2B0 = NULL;
		}
		if ((u32)arg0->unk2A4 != NULL) {
			fn_80150958();
			arg0->unk2A4 = NULL;
		}
		if ((u32)arg0->unk2A8 != NULL) {
			fn_80150958();
			arg0->unk2A8 = NULL;
		}
		if ((u32)arg0->unk2AC != NULL) {
			fn_80150958();
			arg0->unk2AC = NULL;
		}
		if ((u32)arg0->unk284 != NULL) {
			fn_80150958();
			arg0->unk284 = NULL;
		}
		if ((u32)arg0->unk280 != NULL) {
			fn_80150958();
			arg0->unk280 = NULL;
		}
		if ((u32)arg0->unk27C != NULL) {
			fn_80150958();
			arg0->unk27C = NULL;
		}
		if ((u32)arg0->unkE8 != NULL) {
			fn_80150958();
			arg0->unkE8 = NULL;
		}
		lbl_8_bss_1914 = NULL;
		__dt__10HAnimClassFv((u8*)arg0 + 0x240, 0);
		fn_800A7088(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_A18A0(TObject* arg0, M2C_UNK arg_sp0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	s32* var_r27;
	s32 temp_r0;
	s32 temp_r30;
	s32 var_r28;
	s32 var_r29;
	u32 temp_r0_2;
	void** var_r0;
	void** var_r0_2;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;

	fn_800A714C();
	__ct__10HAnimClassFv((u8*)arg0 + 0x240);
	arg0->unk18  = &lbl_8_data_15EBC;
	arg0->unkB4  = &lbl_8_data_15EBC + 0x2C;
	arg0->unk278 = 0;
	arg0->unk0   = lbl_8_data_15DD8;
	arg0->unk1E  = 0x2B4;
	arg0->unk248 = 0U;
	arg0->unk24C = 0.0f;
	arg0->unk250 = 0.0f;
	arg0->unk25C = 0.0f;
	arg0->unk258 = 0.0f;
	arg0->unk254 = 0.0f;
	arg0->unk27C = NULL;
	arg0->unk280 = NULL;
	arg0->unk284 = NULL;
	arg0->unk288 = 0U;
	arg0->unk240 = NULL;
	arg0->unk260 = 0;
	arg0->unk264 = 1;
	arg0->unk268 = 1;
	arg0->unk244 = 0;
	arg0->unk26C = 0;
	arg0->unk298 = 0;
	arg0->unk2A4 = NULL;
	arg0->unk29C = 0;
	arg0->unk2A8 = NULL;
	arg0->unk2A0 = 0;
	arg0->unk2AC = NULL;
	arg0->unk2B0 = NULL;
	arg0->unk274 = 0;
	arg0->unk278 = 0;
	arg0->unk250 = 0.5f;
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
	sp8          = M2C_FIELD(&lbl_8_rodata_17DC, f32*, 0);
	spC          = M2C_FIELD(&lbl_8_rodata_17DC, f32*, 4);
	sp10         = M2C_FIELD(&lbl_8_rodata_17DC, f32*, 8);
	arg0->unk1CC = sp8;
	arg0->unk1D0 = spC;
	arg0->unk1D4 = sp10;
	arg0->unk180 = 0x200;
	arg0->unk160 = 0.0f;
	arg0->unk15C = 0.0f;
	arg0->unk158 = 0.0f;
	if ((void**)arg0->unk2B0 != NULL) {
		dtor_800FE334(1);
		arg0->unk2B0 = NULL;
	}
	if ((void*)arg0->unk2A4 != NULL) {
		fn_80150958();
		arg0->unk2A4 = NULL;
	}
	if ((void*)arg0->unk2A8 != NULL) {
		fn_80150958();
		arg0->unk2A8 = NULL;
	}
	if ((void*)arg0->unk2AC != NULL) {
		fn_80150958();
		arg0->unk2AC = NULL;
	}
	if ((void*)arg0->unk284 != NULL) {
		fn_80150958();
		arg0->unk284 = NULL;
	}
	if ((void*)arg0->unk280 != NULL) {
		fn_80150958();
		arg0->unk280 = NULL;
	}
	if ((void*)arg0->unk27C != NULL) {
		fn_80150958();
		arg0->unk27C = NULL;
	}
	if ((void*)arg0->unkE8 != NULL) {
		fn_80150958();
		arg0->unkE8 = NULL;
	}
	arg0->unkE8 = fn_80150588(M2C_FIELD(&lbl_8_bss_18A8, s32*, 0));
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4) != 0U) {
		arg0->unk27C = fn_80150588();
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 8) != 0U) {
		arg0->unk280 = fn_80150588();
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC) != 0U) {
		arg0->unk284 = fn_80150588();
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10) != 0U) {
		arg0->unk2A4 = fn_80150588();
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14) != 0U) {
		arg0->unk2A8 = fn_80150588();
	}
	if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18) != 0U) {
		arg0->unk2AC = fn_80150588();
	}
	if ((void*)arg0->unk27C != NULL) {
		var_r0 = fn_80057644(0x4C);
		if (var_r0 != NULL) {
			var_r0 = fn_800FE3FC();
		}
		arg0->unk2B0                             = var_r0;
		M2C_FIELD(arg0->unk2B0, void**, 0x30)    = (void*)arg0->unk27C;
		M2C_FIELD(arg0->unk2B0, M2C_UNK**, 0x2C) = &lbl_8_data_15D24;
		M2C_FIELD(arg0->unk2B0, s32*, 0x1C)      = 0;
	}
	temp_r3_3 = arg0->unkE8;
	if (temp_r3_3 != NULL) {
		temp_r30 = M2C_FIELD(temp_r3_3, s32*, 4);
		temp_r0  = arg0->unk19C;
		if (temp_r0 != 0x43) {
			if ((temp_r0 < 0x43) && (temp_r0 < 3)) {
				if (temp_r0 < 1) {
					goto block_39;
				}
				goto block_38;
			}
		block_39:
			fn_8019ED68(temp_r30, &lbl_80239984, 0, 0.005493164f * (f32)arg0->unk150, 0.005493164f);
		} else {
		block_38:
			fn_8019ED68(temp_r30, &lbl_80239984, 0, 180.0f + (0.005493164f * (f32)arg0->unk150),
			    0.005493164f, 180.0f);
		}
		fn_8019EB94(temp_r30, (u8*)arg0 + 0x140, 2);
		if ((u32)arg0->unk288 == 0U) {
			arg0->unk288 = fn_8011B5A8(temp_r30, 0xC1D);
		}
		var_r29 = 0;
		var_r28 = 0;
		var_r27 = &lbl_8_rodata_17E8;
		do {
			if (M2C_FIELD(arg0, u32*, var_r28 + 0x298) == 0U) {
				M2C_FIELD(arg0, u32*, var_r28 + 0x298) = fn_8011B5A8(temp_r30, *var_r27);
			}
			var_r28 += 4;
			var_r27 += 4;
			var_r29 += 1;
		} while (var_r29 < 3);
	}
	arg0->unkE4 = &lbl_8_data_15BF0;
	arg0->unkD4 = 0;
	temp_r0_2   = *M2C_FIELD(lbl_8042C380, u32**, 0x28);
	if (temp_r0_2 != 0U) {
		arg0->unk248 = temp_r0_2;
	}
	var_r0_2 = fn_80057644(0x20);
	if (var_r0_2 != NULL) {
		var_r0_2 = fn_8_A31D4();
	}
	arg0->unk240 = var_r0_2;
	if ((void**)arg0->unk240 != NULL) {
		if ((s32)lbl_8_bss_1910 == 0) {
			fn_8_A2A78(arg0);
			lbl_8_bss_1910 = 1;
		} else {
			fn_8_A2A00(arg0);
		}
	}
	lbl_8_bss_1914 = arg0;
	return arg0;
}

TObject* fn_8_A1E30(void)
{
	return lbl_8_bss_1914;
}

TObject* fn_8_A1E40(void)
{
	TObject* var_r0;

	var_r0 = fn_80018A34(lbl_8042C148, 0x2B4);
	if (var_r0 != NULL) {
		var_r0 = fn_8_A18A0(lbl_8042C10C, 0);
	}
	return var_r0;
}

void fn_8_A1E94(void) { }

void fn_8_A1E98(void)
{
	fn_8_A1E40();
}

void fn_8_A1EB8(void)
{
	lbl_8_bss_1910 = 0;
	fn_800FE248(0xB, &lbl_8_data_15D24);
	fn_800FE248(0xB, &lbl_8_data_15BF0);
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 0)    = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 4)    = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 8)    = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 0xC)  = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 0x10) = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 0x14) = 0;
	M2C_FIELD(&lbl_8_bss_18A8, s32*, 0x18) = 0;
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	fn_801007F4(lbl_8042C590, 0xB);
}

void fn_8_A1F68(M2C_UNK arg_sp0)
{
	if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		fn_8010096C(lbl_8042C590, 0xB, "en_eggmobile_stg25.one");
	} else {
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		fn_8010096C(lbl_8042C590, 0xB, "en_eggmobile_stg22.one");
	}
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
		fn_80100AAC();
	}
	if (fn_80100328(lbl_8042C590, 0xB, 0xE) != 0U) {
		fn_8005E00C(6);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_18A8, u32*, 0) = fn_8010037C(lbl_8042C590, 0xB, 0x10);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_18A8, u32*, 4) = fn_8010037C(lbl_8042C590, 0xB, 0xD);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_18A8, u32*, 8) = fn_8010037C(lbl_8042C590, 0xB, 0x14);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC) = fn_8010037C(lbl_8042C590, 0xB, 0xA);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10) = fn_8010037C(lbl_8042C590, 0xB, 0x13);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14) = fn_8010037C(lbl_8042C590, 0xB, 0x11);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18) = fn_8010037C(lbl_8042C590, 0xB, 0x12);
		if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4) != 0U) {
			fn_800F46B0();
		}
		if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x10) != 0U) {
			fn_8005DA34();
		}
		if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x14) != 0U) {
			fn_8005DA34();
		}
		if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0x18) != 0U) {
			fn_8005DA34();
		}
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != NULL)) {
			fn_80100AAC();
		}
		lbl_8_bss_18C4 = fn_80100280(lbl_8042C590, 0xB, 0xB);
		if ((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 4) != 0U) {
			fn_8003C640();
		}
		if (((u32)M2C_FIELD(&lbl_8_bss_18A8, u32*, 0xC) != 0U) && ((u32)lbl_8_bss_18C4 != 0U)) {
			*lbl_8_bss_18C8 = lbl_8_bss_18C4;
			fn_8005BF5C(lbl_8_bss_18C8);
		}
		lbl_8_bss_190C = 0;
		fn_800FE274(0xB, &lbl_8_data_15BF0);
		fn_800FE274(0xB, &lbl_8_data_15D24);
		lbl_8_bss_1910 = 0;
	}
}

void fn_8_A23AC(void* arg0, void* arg1)
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

void fn_8_A2444(void) { }

void fn_8_A2448(void) { }

void fn_8_A244C(void) { }

void fn_8_A2450(void) { }

void fn_8_A2454(void)
{
	const char* temp_r3;

	M2C_FIELD(&lbl_8_bss_1918, s32*, 0x14)            = 0;
	M2C_FIELD(&lbl_8_bss_1918, s32*, 0x18)            = 0;
	M2C_FIELD(&lbl_8_bss_1918, const char**, 0)       = "EGGMOBILE OBJECT";
	M2C_FIELD(&lbl_8_bss_1918, void (**)(M2C_UNK), 4) = fn_8_A1F68;
	M2C_FIELD(&lbl_8_bss_1918, void (**)(), 8)        = fn_8_A1EB8;
	M2C_FIELD(&lbl_8_bss_1918, void (**)(), 0xC)      = fn_8_A1E98;
	M2C_FIELD(&lbl_8_bss_1918, s32*, 0x10)            = 0;
	M2C_FIELD(&lbl_8_bss_1918, s32*, 0x14)            = 0x20000;
	M2C_FIELD(&lbl_8_bss_1918, s32*, 0x18)            = 0;
	M2C_FIELD(&lbl_8_bss_1918, s8*, 0x20)             = 0x1E;
	M2C_FIELD(&lbl_8_bss_1918, s16*, 0x1C)            = 0x15D1;
	M2C_FIELD(&lbl_8_bss_1918, s16*, 0x1E)            = 4;
	M2C_FIELD(&lbl_8_bss_1918, s8*, 0x21)             = 0;
	temp_r3                                           = "f";
	M2C_FIELD(&lbl_8_bss_1918, const char**, 0x24)    = temp_r3;
	M2C_FIELD(&lbl_8_bss_1918, M2C_UNK**, 0x28)       = &lbl_8_data_15DC0;
	if (temp_r3 != NULL) {
		M2C_FIELD(&lbl_8_bss_1918, s32*, 0x14) = 0x20008;
	} else {
		M2C_FIELD(&lbl_8_bss_1918, s32*, 0x14) = 0x20000;
	}
	M2C_STRUCT_COPY(lbl_8_data_15E0C, &lbl_8_data_15DDC, 0xC);
	lbl_8_data_15E0C[1].unk0 = M2C_FIELD(&lbl_8_data_15DE8, s32*, 0);
	lbl_8_data_15E0C[1].unk4 = M2C_FIELD(&lbl_8_data_15DE8, s32*, 4);
	lbl_8_data_15E0C[1].unk8 = M2C_FIELD(&lbl_8_data_15DE8, s32*, 8);
	lbl_8_data_15E0C[2].unk0 = M2C_FIELD(&lbl_8_data_15DF4, s32*, 0);
	lbl_8_data_15E0C[2].unk4 = M2C_FIELD(&lbl_8_data_15DF4, s32*, 4);
	lbl_8_data_15E0C[2].unk8 = M2C_FIELD(&lbl_8_data_15DF4, s32*, 8);
	lbl_8_data_15E0C[3].unk0 = M2C_FIELD(&lbl_8_data_15E00, s32*, 0);
	lbl_8_data_15E0C[3].unk4 = M2C_FIELD(&lbl_8_data_15E00, s32*, 4);
	lbl_8_data_15E0C[3].unk8 = M2C_FIELD(&lbl_8_data_15E00, s32*, 8);
}
}
