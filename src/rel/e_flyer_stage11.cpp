#include "types.h"

typedef s32 M2C_UNK;
typedef struct HAnimClass HAnimClass;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)

extern "C" {

void* __ct__10HAnimClassFv(void* self);                                          /* extern */
M2C_UNK __dl__FPv(void* arg0);                                                   /* extern */
void* __dt__10HAnimClassFv(void* self, s16 destroyFlag);                         /* extern */
f64 asin(f32);                                                                   /* extern */
f64 atan2(void*, f32, f32);                                                      /* extern */
f64 fabs(f64);                                                                   /* extern */
s32 fn_80017800(M2C_UNK*);                                                       /* extern */
M2C_UNK fn_800189A4(s32, void*);                                                 /* extern */
M2C_UNK* fn_80018A34(s32, M2C_UNK);                                              /* extern */
u32 fn_800194C4(M2C_UNK*);                                                       /* extern */
M2C_UNK fn_8001F404(void*);                                                      /* extern */
M2C_UNK fn_8003BC38(void*);                                                      /* extern */
M2C_UNK fn_8003C200(void*, M2C_UNK*, M2C_UNK, M2C_UNK);                          /* extern */
u32 fn_80057644(M2C_UNK);                                                        /* extern */
s32 fn_8005B8D8(void*);                                                          /* extern */
M2C_UNK fn_8005BC04(void*);                                                      /* extern */
M2C_UNK fn_8005D5C8(void*, s32);                                                 /* extern */
s32 fn_8005D9A0(void*, M2C_UNK);                                                 /* extern */
M2C_UNK* fn_8005DEEC(M2C_UNK*, M2C_UNK);                                         /* extern */
M2C_UNK fn_8005E00C(M2C_UNK);                                                    /* extern */
M2C_UNK fn_8006298C(M2C_UNK, s32*, s32*);                                        /* extern */
s32 fn_800A2D50();                                                               /* extern */
M2C_UNK fn_800A31B8(u32);                                                        /* extern */
M2C_UNK fn_800A3D48(M2C_UNK*);                                                   /* extern */
M2C_UNK fn_800A5B34(M2C_UNK*);                                                   /* extern */
s32 fn_800A6D60(void*, void*, f32);                                              /* extern */
M2C_UNK fn_800A7088(void*, M2C_UNK);                                             /* extern */
M2C_UNK fn_800A714C();                                                           /* extern */
M2C_UNK fn_800B4A38(M2C_UNK, void*, void*, M2C_UNK, M2C_UNK, M2C_UNK);           /* extern */
M2C_UNK fn_800B719C(void*, void*, s32*, f32);                                    /* extern */
M2C_UNK fn_800B7820();                                                           /* extern */
M2C_UNK fn_800B7864(M2C_UNK);                                                    /* extern */
s32 fn_800D7A54(s32, s32);                                                       /* extern */
f32 fn_800D7AE4(s32);                                                            /* extern */
f32 fn_800D7B00(s32);                                                            /* extern */
f32 fn_800D8BC4(void*, s32*, M2C_UNK);                                           /* extern */
u32 fn_800FD8A0(M2C_UNK*, s32);                                                  /* extern */
M2C_UNK fn_800FE248(M2C_UNK, M2C_UNK*);                                          /* extern */
M2C_UNK fn_800FE274(M2C_UNK, M2C_UNK*);                                          /* extern */
M2C_UNK fn_800FE464(void*);                                                      /* extern */
u32 fn_80100328(u32, M2C_UNK, M2C_UNK);                                          /* extern */
u32 fn_8010037C(u32, M2C_UNK, M2C_UNK);                                          /* extern */
M2C_UNK fn_801007F4(u32, M2C_UNK);                                               /* extern */
M2C_UNK fn_8010096C(u32, M2C_UNK, const void*);                                  /* extern */
M2C_UNK fn_80100AAC();                                                           /* extern */
s32 fn_80100C88(u8);                                                             /* extern */
M2C_UNK fn_80100D24(s8*, ...);                                                   /* extern */
M2C_UNK fn_80102C50(s32, s32*, s32*, s32*, M2C_UNK, M2C_UNK, M2C_UNK, f32, f32); /* extern */
M2C_UNK fn_8010AFE4();                                                           /* extern */
M2C_UNK fn_8010B208(f32);                                                        /* extern */
M2C_UNK fn_8010B350(void*, M2C_UNK*);                                            /* extern */
s32 fn_8010B708(M2C_UNK);                                                        /* extern */
M2C_UNK fn_80113874();                                                           /* extern */
M2C_UNK fn_801138B4();                                                           /* extern */
M2C_UNK fn_801138F4();                                                           /* extern */
M2C_UNK fn_80113940();                                                           /* extern */
M2C_UNK fn_8011C0E8(u32);                                                        /* extern */
M2C_UNK fn_8011C1DC(u32, s32);                                                   /* extern */
M2C_UNK fn_8011C1F8(u32, s32, M2C_UNK);                                          /* extern */
M2C_UNK fn_8011C6EC();                                                           /* extern */
M2C_UNK fn_8011CB64(void*, s8);                                                  /* extern */
M2C_UNK fn_8011CE44();                                                           /* extern */
u32 fn_8011F894();                                                               /* extern */
M2C_UNK fn_8011F8B0(s8);                                                         /* extern */
M2C_UNK fn_8011F900(M2C_UNK*, s8);                                               /* extern */
M2C_UNK* fn_8011FA4C(M2C_UNK*, u32);                                             /* extern */
M2C_UNK fn_8011FD94(M2C_UNK);                                                    /* extern */
u32 fn_8011FE0C(M2C_UNK);                                                        /* extern */
M2C_UNK fn_80137FE8(void*);                                                      /* extern */
M2C_UNK fn_8014FF2C(...);                                                        /* extern */
void* fn_80150588(...);                                                          /* extern */
M2C_UNK fn_80150958();                                                           /* extern */
M2C_UNK fn_80195790(s32*, M2C_UNK*, M2C_UNK, f32, f32);                          /* extern */
M2C_UNK fn_80195A74(s32*, M2C_UNK*, M2C_UNK, f32, f32, ...);                     /* extern */
M2C_UNK fn_80196050(void*, void*, M2C_UNK);                                      /* extern */
M2C_UNK fn_801961E8(void*, void*, M2C_UNK);                                      /* extern */
M2C_UNK fn_80196414(void*, f32*, f32*, M2C_UNK*);                                /* extern */
M2C_UNK fn_801990E0(void*, void*);                                               /* extern */
f32 fn_801991B4(void*);                                                          /* extern */
M2C_UNK fn_8019941C(s32*, s32*, M2C_UNK, void*);                                 /* extern */
void* fn_8019E8EC(...);                                                          /* extern */
M2C_UNK fn_8019EB94(M2C_UNK*, void*, M2C_UNK);                                   /* extern */
M2C_UNK fn_8019ECCC(M2C_UNK*, void*, ...);                                       /* extern */
M2C_UNK fn_8019ED68(M2C_UNK*, M2C_UNK*, f32, f32, ...);                          /* extern */
M2C_UNK fn_8019EE04(s32);                                                        /* extern */
s32 fn_801C28D8();                                                               /* extern */
M2C_UNK fn_8_5EF94(u32, s32*);                                                   /* extern */
M2C_UNK fn_8_5F048(u32, void*);                                                  /* extern */
M2C_UNK fn_8_5F100(s32);                                                         /* extern */
M2C_UNK fn_8_5F140();                                                            /* extern */
s32 fn_8_5F30C(M2C_UNK*, void*, void*, void*, f32);                              /* extern */
M2C_UNK fn_8_90B10(s32);                                                         /* extern */
M2C_UNK fn_8_A1E94(s32);                                                         /* extern */
M2C_UNK fn_8_A8B60(f32*);                                                        /* extern */
M2C_UNK fn_8_A8D1C();                                                            /* extern */
M2C_UNK fn_8_A8D30();                                                            /* extern */
M2C_UNK fn_8_A9C6C(f32*);                                                        /* extern */
M2C_UNK fn_8_A9E18();                                                            /* extern */
M2C_UNK fn_8_A9E2C();                                                            /* extern */
M2C_UNK fn_8_A9E94(u32, s32*);                                                   /* extern */
M2C_UNK fn_8_AA08C(M2C_UNK*);                                                    /* extern */
u32 fn_8_AA58C();                                                                /* extern */
M2C_UNK pawnReleaseBuffer();                                                     /* extern */
s32 sprintf(void*, const char*, ...);                                            /* extern */
void fn_8_A4E44(M2C_UNK* arg0);                                                  /* static */
void fn_8_A549C(void* arg0, ...);                                                /* static */
extern M2C_UNK flyerObjectEntry;
extern M2C_UNK lbl_80239978;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_8029C310;
extern void* lbl_802AD070[];
extern void* lbl_80303DC8[];
extern M2C_UNK* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern s32 lbl_8042C2A0;
extern u32 lbl_8042C388;
extern u32 lbl_8042C590;
extern u32 lbl_8042C6D0;
extern M2C_UNK lbl_8_rodata_18AC;
static M2C_UNK lbl_8_data_15F80;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15FBC;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_15FD8;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16018;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16070;      /* unable to generate initializer: unknown type */
static M2C_UNK flyerObjectFieldNames; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16154;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1615C;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16168;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16170;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16178;      /* unable to generate initializer: unknown type */
static const char* lbl_8_data_16180[5] = { "NONE", "MACHINE GUN", "MISSILE", "PAWN", "BOMB" };
static M2C_UNK lbl_8_data_16194; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_161A0; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_161A8[2] = { "ONE SHOT", "LOOP" };
static u8 lbl_8_data_161B0             = 0;
static u8 lbl_8_data_161B1             = 4;
static u8 lbl_8_data_161B2             = 0;
static u8 lbl_8_data_161B3             = 1;
static M2C_UNK lbl_8_data_161B4; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_161C4 = "TObjEnemyFlyer";
static M2C_UNK lbl_8_data_161C8;       /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1628C;       /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1629C;       /* unable to generate initializer: unknown type */
static M2C_UNK flyerObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK flyerObjectFieldTypes;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_bss_1948;
static u32 lbl_8_bss_1958;
static M2C_UNK lbl_8_rodata_18C0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_18CC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_18D8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_18E4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_18F0; /* unable to generate initializer: unknown type; const */
static f32 lbl_8_rodata_18FC;
static f32 lbl_8_rodata_1900;
static f32 lbl_8_rodata_1904;
static f32 lbl_8_rodata_1908;
static f32 lbl_8_rodata_190C;
static f64 lbl_8_rodata_1910;
static f32 lbl_8_rodata_1918;
static f32 lbl_8_rodata_191C;
static f32 lbl_8_rodata_1920;
static f32 lbl_8_rodata_1924;
static f32 lbl_8_rodata_1928;
static f32 lbl_8_rodata_192C;
static f32 lbl_8_rodata_1930;
static f32 lbl_8_rodata_1934;
static f32 lbl_8_rodata_1938;
static f32 lbl_8_rodata_193C;
static f32 lbl_8_rodata_1940;
static f32 lbl_8_rodata_1944;
static f32 lbl_8_rodata_1948;
static f32 lbl_8_rodata_194C;
static f64 lbl_8_rodata_1950;
static f32 lbl_8_rodata_1958;
static f32 lbl_8_rodata_195C;
static f32 lbl_8_rodata_1960;
static f32 lbl_8_rodata_1964;
static f32 lbl_8_rodata_1968;
static f32 lbl_8_rodata_196C;
static f32 lbl_8_rodata_1970;
static f32 lbl_8_rodata_1974;
static s32 lbl_8_rodata_1978    = 0;                           /* const */
static s32 lbl_8_rodata_197C[4] = { 0x100, 0, 0x3FC00000, 0 }; /* const */

void fn_8_A2584(s32 arg0)
{
	fn_8_A1E94(arg0 - 0xB0);
}

void fn_8_A258C(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 0x5C;
}

void fn_8_A25AC(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 0x1D;
}

void fn_8_A25CC(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x1C) = (s32)(M2C_FIELD(arg0, s32*, 0x1C) + 1);
			M2C_FIELD(arg0, s32*, 0x18) = 0x3C;
			M2C_FIELD(arg0, s32*, 0x10) = 0x26;
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

void fn_8_A2690(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 0x44;
}

void fn_8_A26B0(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x41;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 2;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_A2768(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x12C;
			M2C_FIELD(arg0, s32*, 0x10) = 0x43;
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

void fn_8_A2820(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 0x42;
}

void fn_8_A2840(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = (s32)(1080.0f * (0.000030517578f * (f32)fn_801C28D8()));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0x258) {
				M2C_FIELD(arg0, s32*, 0x18) = 0x258;
			}
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			return;
		case 1:
			if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
				temp_r0 = M2C_FIELD(arg0, s32*, 0x1C);
				if ((temp_r0 < 4) && (fn_80100C88(*(&lbl_8_rodata_18AC + temp_r0)) == 1)) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 6;
					M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
					    arg0, M2C_FIELD(arg0, s32*, 4), 0);
					return;
				}
			}
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_A29E0(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
			return;
		}
		return;
	}
	M2C_FIELD(arg0, s32*, 0x10) = 1;
}

void fn_8_A2A00(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	if ((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, s32*, 0xC)  = 5;
		M2C_FIELD(arg0, s32*, 0x10) = 0;
		M2C_FIELD(arg0, s32*, 4)    = 5;
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
		    M2C_FIELD(arg0, s32*, 4), 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
			fn_800A31B8(M2C_FIELD(arg0, u32*, 0x14));
		}
	}
}

void fn_8_A2A78(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	if ((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, s32*, 0xC)  = 4;
		M2C_FIELD(arg0, s32*, 0x10) = 0;
		M2C_FIELD(arg0, s32*, 4)    = 4;
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
		    M2C_FIELD(arg0, s32*, 4), 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
			fn_800A31B8(M2C_FIELD(arg0, u32*, 0x14));
		}
	}
}

s32 fn_8_A2AF0(void* arg0)
{
	s32 temp_r0;
	s32 var_r4;

	temp_r0 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x260);
	if (temp_r0 != 0) {
		var_r4 = 0;
		switch (temp_r0) { /* irregular */
			case 0x42:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 2;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
			case 0x43:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
			case 0x2:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
			case 0x44:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 5;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
			case 0x1D:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 7;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
			case 0x5C:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
				    M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 8;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r4 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x260) = 0;
		return var_r4;
	}
	return 0;
}

void fn_8_A2D48(void* arg0, u32 arg1, s32 arg2)
{
	s32 temp_r0;

	switch (arg1) { /* switch 1 */
		case 0:     /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
				default: /* switch 1 */
					return;
			}
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			return;
		case 1:             /* switch 1 */
			switch (arg2) { /* switch 2; irregular */
				case 0:     /* switch 2 */
					M2C_FIELD(arg0, s32*, 0x18)
					    = (s32)(1080.0f * (0.000030517578f * (f32)fn_801C28D8()));
					if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0x258) {
						M2C_FIELD(arg0, s32*, 0x18) = 0x258;
					}
					M2C_FIELD(arg0, s32*, 0x10) = 2;
					return;
				case 1: /* switch 2 */
					if ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x2C) == 0x15) {
						temp_r0 = M2C_FIELD(arg0, s32*, 0x1C);
						if ((temp_r0 < 4) && (fn_80100C88(*(&lbl_8_rodata_18AC + temp_r0)) == 1)) {
							M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
							M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
							    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 3);
							M2C_FIELD(arg0, s32*, 4) = 6;
							M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
							    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 0);
							return;
						}
					}
					fn_80137FE8((u8*)arg0 + 0x18);
					if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
						M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 3);
						M2C_FIELD(arg0, s32*, 4) = 3;
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 0);
						return;
					}
					break;
			}
			break;
		case 2: /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0x10) = 0x42;
				return;
			}
			break;
		case 3:             /* switch 1 */
			switch (arg2) { /* switch 3; irregular */
				case 0:     /* switch 3 */
					M2C_FIELD(arg0, s32*, 0x18) = 0x12C;
					M2C_FIELD(arg0, s32*, 0x10) = 0x43;
					return;
				case 1: /* switch 3 */
					fn_80137FE8((u8*)arg0 + 0x18);
					if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
						M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 3);
						M2C_FIELD(arg0, s32*, 4) = 1;
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 0);
						return;
					}
					break;
			}
			break;
		case 4:             /* switch 1 */
			switch (arg2) { /* switch 4; irregular */
				case 0:     /* switch 4 */
					M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
					M2C_FIELD(arg0, s32*, 0x10) = 0x41;
					return;
				case 1: /* switch 4 */
					fn_80137FE8((u8*)arg0 + 0x18);
					if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
						M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 3);
						M2C_FIELD(arg0, s32*, 4) = 2;
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 0);
						return;
					}
					break;
			}
			break;
		case 5: /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0x10) = 0x44;
				return;
			}
			break;
		case 6:             /* switch 1 */
			switch (arg2) { /* switch 5; irregular */
				case 0:     /* switch 5 */
					M2C_FIELD(arg0, s32*, 0x1C) = (s32)(M2C_FIELD(arg0, s32*, 0x1C) + 1);
					M2C_FIELD(arg0, s32*, 0x18) = 0x3C;
					M2C_FIELD(arg0, s32*, 0x10) = 0x26;
					return;
				case 1: /* switch 5 */
					fn_80137FE8((u8*)arg0 + 0x18);
					if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
						M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 3);
						M2C_FIELD(arg0, s32*, 4) = 1;
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 0);
						return;
					}
					break;
			}
			break;
		case 7: /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0x10) = 0x1D;
				return;
			}
			break;
		case 8: /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0x10) = 0x5C;
			}
			break;
	}
}

M2C_UNK** fn_8_A3170(M2C_UNK** arg0, s16 arg1)
{
	s32 temp_cr0_eq;

	temp_cr0_eq = arg0 == NULL;
	if (temp_cr0_eq == 0) {
		*arg0 = &lbl_8_data_15F80;
		if (temp_cr0_eq == 0) {
			*arg0 = &lbl_8_data_15FBC;
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_A31D4(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_15FBC;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_15F80;
	M2C_FIELD(arg0, s32*, 0x1C)   = 0;
}

M2C_UNK** fn_8_A320C(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = &lbl_8_data_15FBC;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_A325C(void* arg0)
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
		temp_r3_4 = lbl_802AD070[temp_r0_2];
		if (temp_r3_4 != NULL) {
			temp_r30 = lbl_80303DC8[(s8)M2C_FIELD(temp_r3_4, u8*, 0x9BC)];
			if (temp_r30 != NULL) {
				fn_8011CE44();
				fn_8011CB64((u8*)arg0 + 0x140,
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
	if ((s32)M2C_FIELD(arg0, s32*, 0x3A8) == 0) {
		if ((u32)lbl_8042C6D0 == 0U) {
			fn_8011C6EC();
		}
		fn_8011C0E8(lbl_8042C6D0);
	}
}

void fn_8_A3420(s32 arg1)
{
	fn_8_90B10(arg1);
}

void fn_8_A3444(void* arg0)
{
	if ((u32)lbl_8042C6D0 == 0U) {
		fn_8011C6EC();
	}
	fn_8011C1F8(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x230), 0xC8);
}

void fn_8_A349C(void* arg0, void* arg1)
{
	u32 temp_r0;

	if (((u8)M2C_FIELD(arg1, u8*, 0) == 5)
	    && ((s32)M2C_FIELD(arg1, s32*, 0x14) == (s32)M2C_FIELD(arg0, s32*, 0x258))) {
		temp_r0 = M2C_FIELD(arg1, u32*, 4);
		switch (temp_r0) {
			case 1:
				M2C_FIELD(arg0, s32*, 0x25C) = 2;
				return;
			case 2:
				M2C_FIELD(arg0, s32*, 0x25C) = 1;
				return;
			case 3:
				M2C_FIELD(arg0, s32*, 0x25C) = 0x20;
				return;
			case 4:
				M2C_FIELD(arg0, f32*, 0x2F8) = (f32)M2C_FIELD(arg1, f32*, 8);
				M2C_FIELD(arg0, f32*, 0x2FC) = (f32)M2C_FIELD(arg1, f32*, 0xC);
				M2C_FIELD(arg0, f32*, 0x300) = (f32)M2C_FIELD(arg1, f32*, 0x10);
				M2C_FIELD(arg0, s32*, 0x25C) = 0x20;
				return;
			case 5:
				M2C_FIELD(arg0, s32*, 0x25C) = 0x20;
				return;
			case 6:
				M2C_FIELD(arg0, s32*, 0x25C) = 0x20;
				/* fallthrough */
				return;
		}
	}
}

s32 fn_8_A353C(void* arg0)
{
	f32 temp_f1;
	s32 var_r31;

	var_r31 = 0;
	temp_f1 = M2C_FIELD(arg0, f32*, 0x1A4);
	if (temp_f1 != M2C_FIELD(arg0, f32*, 0x3BC)) {
		M2C_FIELD(arg0, f32*, 0x3BC) = temp_f1;
		if ((u32)M2C_FIELD(arg0, u32*, 0x3B8) != 0U) {
			fn_8010B208(M2C_FIELD(arg0, f32*, 0x3C0));
		}
		var_r31 = 1;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x3B8) != 0U) {
		fn_8010B350((u8*)arg0 + 0x268, &lbl_8_rodata_18CC);
	}
	return var_r31;
}

s32 fn_8_A35BC(void* arg0)
{
	if ((s8)M2C_FIELD(arg0, u8*, 0x245) != 1) {
		return 1;
	}
	return M2C_FIELD(arg0, s32*, 0x254);
}

void fn_8_A35DC(void* arg0)
{
	s32 sp28;
	s32 sp24;
	s32 sp20;
	s32 sp1C;
	s32 sp18;
	s32 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;
	s32 temp_cr0_eq;

	M2C_FIELD(arg0, s32*, 0x188) = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x200);
	temp_cr0_eq                  = (u32)(M2C_FIELD(arg0, s32*, 0x188) & 0x10) == 0;
	if (temp_cr0_eq == 0) {
		sp20 = M2C_FIELD(arg0, s32*, 0x268);
		sp24 = M2C_FIELD(arg0, s32*, 0x26C);
		sp28 = M2C_FIELD(arg0, s32*, 0x270);
		sp14 = M2C_FIELD(arg0, s32*, 0x14C);
		sp18 = M2C_FIELD(arg0, s32*, 0x150);
		sp1C = M2C_FIELD(arg0, s32*, 0x154);
		if (temp_cr0_eq == 0) {
			fn_8006298C(6, &sp20, &sp14);
			fn_8006298C(2, &sp20, &sp14);
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0xE017, &sp20, NULL, 1, 2, 0);
			}
			fn_8006298C(0xF, &sp20, &sp14);
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
				fn_80100AAC();
			}
			if (fn_8010037C(lbl_8042C590, 0, 5) != 0U) {
				sp8  = M2C_FIELD(&lbl_8_rodata_18C0, s32*, 0);
				spC  = M2C_FIELD(&lbl_8_rodata_18C0, s32*, 4);
				sp10 = M2C_FIELD(&lbl_8_rodata_18C0, s32*, 8);
				sp18 += 0x8000;
				fn_80102C50(lbl_8042C2A0, &sp20, &sp14, &sp8, 0, 0, 0, 1.2f, 0.0f);
			}
		}
	}
}

s32 fn_8_A3768(void)
{
	return 0;
}

s32 fn_8_A3770(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x19C) == 1) {
		return 0;
	}
	return fn_800A6D60((u8*)arg0 + 0x268, &lbl_8_rodata_1904, 30.0f);
}

void fn_8_A37B4(void* arg0)
{
	s32 sp8;

	if ((u32)M2C_FIELD(arg0, u32*, 0x260) != 0U) {
		fn_80195A74(
		    &sp8, &lbl_80239990, 0, 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x154), 0.005493164f);
		fn_80195A74(
		    &sp8, &lbl_80239978, 2, 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x14C), 0.005493164f);
		fn_80195A74(&sp8, &lbl_80239984, 2,
		    180.0f + (0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150)), 0.005493164f, 180.0f);
		fn_80196050(&sp8, (u8*)arg0 + 0x140, 2);
		fn_8_A9E94(M2C_FIELD(arg0, u32*, 0x260), &sp8);
	}
}

void fn_8_A38F8(void* arg0)
{
	s32 sp14;
	s32 sp10;
	s32 spC;
	f32 sp8;
	f32* var_r3;
	f32 temp_f1;
	f32 temp_f1_2;

	fn_800B7864(4);
	spC     = M2C_FIELD(&lbl_8_rodata_18F0, s32*, 0);
	sp10    = M2C_FIELD(&lbl_8_rodata_18F0, s32*, 4);
	sp14    = M2C_FIELD(&lbl_8_rodata_18F0, s32*, 8);
	temp_f1 = 1.0f - (0.004f * (M2C_FIELD(arg0, f32*, 0x144) - M2C_FIELD(arg0, f32*, 0x34C)));
	sp8     = temp_f1;
	var_r3  = &lbl_8_rodata_1918;
	if (temp_f1 < 0.2f) {

	} else {
		var_r3 = &lbl_8_rodata_191C;
		if (temp_f1 > 1.0f) {

		} else {
			var_r3 = &sp8;
		}
	}
	temp_f1_2 = *var_r3;
	sp8       = temp_f1_2;
	fn_800B719C((u8*)arg0 + 0x348, (u8*)arg0 + 0x354, &spC, temp_f1_2);
	fn_800B7820();
}

void fn_8_A39C8(void* arg0)
{
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x90)();
	fn_80113874();
	fn_80113940();
	fn_801138B4();
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0x294));
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0x298));
	fn_801138F4();
}

void fn_8_A3A20(void* arg0)
{
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x90)();
	fn_80113874();
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0xE8));
	if (((s32)M2C_FIELD(arg0, s32*, 0x2E4) != 0) && ((u32)M2C_FIELD(arg0, u32*, 0x2A0) != 0U)) {
		fn_8014FF2C();
	}
}

void fn_8_A3A80(void* arg0)
{
	s32 sp8;
	s32 spC, sp10, sp14, sp18, sp1C, sp20, sp24, sp28;
	s32 sp2C, sp30, sp34, sp38, sp3C, sp40, sp44;
	M2C_UNK* temp_r4_3;
	f32 temp_f31;
	void* temp_r4;
	void* temp_r4_2;
	void* temp_r5;

	temp_r4                      = M2C_FIELD(arg0, void**, 0xB0);
	temp_r5                      = M2C_FIELD(temp_r4, void**, 0x2C);
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
	M2C_FIELD(arg0, f32*, 0x1B8) = 1.5f;
	M2C_FIELD(arg0, u8*, 0x245)  = (u8)M2C_FIELD(temp_r5, u8*, 0);
	M2C_FIELD(arg0, u8*, 0x244)  = (u8)M2C_FIELD(temp_r5, u8*, 1);
	M2C_FIELD(arg0, u8*, 0x246)  = (u8)M2C_FIELD(temp_r5, u8*, 2);
	M2C_FIELD(arg0, f32*, 0x248) = (f32)M2C_FIELD(temp_r5, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x24C) = (f32)M2C_FIELD(temp_r5, f32*, 0xC);
	M2C_FIELD(arg0, s32*, 0x250) = (s32)M2C_FIELD(temp_r5, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x254) = (s32)M2C_FIELD(temp_r5, s32*, 8);
	M2C_FIELD(arg0, s32*, 0x258) = (s32)M2C_FIELD(temp_r5, s32*, 0x14);
	fn_8_A549C(&lbl_8_rodata_1928, temp_r5);
	if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x3B4) != NULL) {
		temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x150));
		fn_80195790(
		    &sp8, &lbl_80239984, 0, 1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x150)), temp_f31);
		fn_80196050(&sp8, (u8*)arg0 + 0x140, 2);
		temp_r4_3                        = M2C_FIELD(arg0, M2C_UNK**, 0x3B4);
		M2C_FIELD(temp_r4_3, s32*, 0x7C) = sp8;
		M2C_FIELD(temp_r4_3, s32*, 0x80) = spC;
		M2C_FIELD(temp_r4_3, s32*, 0x84) = sp10;
		M2C_FIELD(temp_r4_3, s32*, 0x88) = sp14;
		M2C_FIELD(temp_r4_3, s32*, 0x8C) = sp18;
		M2C_FIELD(temp_r4_3, s32*, 0x90) = sp1C;
		M2C_FIELD(temp_r4_3, s32*, 0x94) = sp20;
		M2C_FIELD(temp_r4_3, s32*, 0x98) = sp24;
		M2C_FIELD(temp_r4_3, s32*, 0x9C) = sp28;
		M2C_FIELD(temp_r4_3, s32*, 0xA0) = sp2C;
		M2C_FIELD(temp_r4_3, s32*, 0xA4) = sp30;
		M2C_FIELD(temp_r4_3, s32*, 0xA8) = sp34;
		M2C_FIELD(temp_r4_3, s32*, 0xAC) = sp38;
		M2C_FIELD(temp_r4_3, s32*, 0xB0) = sp3C;
		M2C_FIELD(temp_r4_3, s32*, 0xB4) = sp40;
		M2C_FIELD(temp_r4_3, s32*, 0xB8) = sp44;
		M2C_FIELD(M2C_FIELD(arg0, M2C_UNK**, 0x3B4), f32*, 0x34)
		    = (f32)M2C_FIELD(arg0, f32*, 0x248);
		fn_8011F900(M2C_FIELD(arg0, M2C_UNK**, 0x3B4), (s8)M2C_FIELD(arg0, u8*, 0x244));
	}
}

void fn_8_A3C88(M2C_UNK* arg0)
{
	s32 sp78;
	s32 sp74;
	f32 sp70;
	f32 sp6C;
	f32 sp68;
	s32 sp64;
	s32 sp60;
	s32 sp5C;
	s32 sp58;
	s32 sp54;
	s32 sp50;
	s32 sp4C;
	s32 sp48;
	s32 sp44;
	s32 sp40;
	s32 sp3C;
	s32 sp38;
	s32 sp34;
	s32 sp30;
	s32 sp2C;
	s32 sp28;
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	s32 sp18;
	u8 sp15;
	s8 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;
	M2C_UNK* temp_r29;
	M2C_UNK* temp_r30_2;
	s32 var_r0;
	s32 var_r0_2;
	void** temp_r3_2;
	void* temp_r29_2;
	void* temp_r30;
	void* temp_r3;
	void* temp_r3_3;

	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x3A0) = var_r0;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0_2 = 0;
	} else {
		var_r0_2 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x3A4) = var_r0_2;
	temp_r3                      = M2C_FIELD(arg0, void**, 0xE8);
	if (temp_r3 != NULL) {
		fn_8019EE04(M2C_FIELD(temp_r3, s32*, 4));
	}
	fn_800A5B34(arg0);
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(M2C_UNK*), 0x38)(arg0);
	temp_r3_2 = M2C_FIELD(arg0, void***, 0x240);
	if (temp_r3_2 != NULL) {
		M2C_FIELD(*temp_r3_2, M2C_UNK(**)(M2C_UNK*), 0xC)(arg0);
	}
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(M2C_UNK*, s32, M2C_UNK), 0x50)(
	    arg0, M2C_FIELD(arg0, s32*, 0x19C), 1);
	fn_8_A549C(arg0);
	fn_800A3D48(arg0);
	if ((u32)M2C_FIELD(arg0, u32*, 0x280) != 0U) {
		temp_r30 = fn_8019E8EC();
		temp_r29 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x294), M2C_UNK**, 4);
		fn_8019ED68(temp_r29, &lbl_80239990, 0.0f, M2C_FIELD(arg0, f32*, 0x29C));
		fn_8019ECCC(temp_r29, temp_r30, 2);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x284) != 0U) {
		temp_r29_2 = fn_8019E8EC();
		temp_r30_2 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x298), M2C_UNK**, 4);
		fn_8019ED68(temp_r30_2, &lbl_80239990, 0.0f, M2C_FIELD(arg0, f32*, 0x29C));
		fn_8019ECCC(temp_r30_2, temp_r29_2, 2);
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x3A4) != 0) {
		M2C_FIELD(arg0, f32*, 0x29C) = (f32)(M2C_FIELD(arg0, f32*, 0x29C) + 75.0f);
		if (((s32)M2C_FIELD(arg0, s32*, 0x19C) != 1) && ((u32)lbl_8042C388 != 0U)) {
			fn_800B4A38(0x4016, (u8*)arg0 + 0x268, arg0, 3, 0, 2);
		}
	}
	if (((s8)M2C_FIELD(arg0, u8*, 0x245) == 3) && ((s32)M2C_FIELD(arg0, s32*, 0x19C) != 0x1D)) {
		if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x288) != NULL) {
			sp14 = 0;
			sp15 = 0;
			sp14 = 6;
			sp18 = 0;
			sp24 = 0.0f;
			sp20 = 0.0f;
			sp1C = 0.0f;
			sp30 = 0;
			sp2C = 0;
			sp28 = 0;
			sp34 = 0;
			sp78 = 0;
			sp15 = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A);
			sp18 = 1;
			sp34 = M2C_FIELD(arg0, s32*, 0x258);
			sp8  = M2C_FIELD(&lbl_8_rodata_18E4, s32*, 0);
			spC  = M2C_FIELD(&lbl_8_rodata_18E4, s32*, 4);
			sp10 = M2C_FIELD(&lbl_8_rodata_18E4, s32*, 8);
			fn_80196050((u8*)arg0 + 0x360, &sp8, 0);
			fn_801961E8((u8*)arg0 + 0x360, fn_8019E8EC(M2C_FIELD(arg0, M2C_UNK**, 0x288)), 2);
			sp38 = M2C_FIELD(arg0, s32*, 0x360);
			sp3C = M2C_FIELD(arg0, s32*, 0x364);
			sp40 = M2C_FIELD(arg0, s32*, 0x368);
			sp44 = M2C_FIELD(arg0, s32*, 0x36C);
			sp48 = M2C_FIELD(arg0, s32*, 0x370);
			sp4C = M2C_FIELD(arg0, s32*, 0x374);
			sp50 = M2C_FIELD(arg0, s32*, 0x378);
			sp54 = M2C_FIELD(arg0, s32*, 0x37C);
			sp58 = M2C_FIELD(arg0, s32*, 0x380);
			sp5C = M2C_FIELD(arg0, s32*, 0x384);
			sp60 = M2C_FIELD(arg0, s32*, 0x388);
			sp64 = M2C_FIELD(arg0, s32*, 0x38C);
			sp68 = M2C_FIELD(arg0, f32*, 0x390);
			sp6C = M2C_FIELD(arg0, f32*, 0x394);
			sp70 = M2C_FIELD(arg0, f32*, 0x398);
			sp74 = M2C_FIELD(arg0, s32*, 0x39C);
			sp1C = M2C_FIELD(arg0, f32*, 0x390);
			sp20 = M2C_FIELD(arg0, f32*, 0x394);
			sp24 = M2C_FIELD(arg0, f32*, 0x398);
			sp28 = M2C_FIELD(arg0, s32*, 0x14C);
			sp2C = M2C_FIELD(arg0, s32*, 0x150);
			sp30 = M2C_FIELD(arg0, s32*, 0x154);
			fn_80100D24(&sp14);
		}
	} else if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x288) != NULL) {
		temp_r3_3                    = fn_8019E8EC();
		M2C_FIELD(arg0, s32*, 0x360) = (s32)M2C_FIELD(temp_r3_3, s32*, 0);
		M2C_FIELD(arg0, s32*, 0x364) = (s32)M2C_FIELD(temp_r3_3, s32*, 4);
		M2C_FIELD(arg0, s32*, 0x368) = (s32)M2C_FIELD(temp_r3_3, s32*, 8);
		M2C_FIELD(arg0, s32*, 0x36C) = (s32)M2C_FIELD(temp_r3_3, s32*, 0xC);
		M2C_FIELD(arg0, s32*, 0x370) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x10);
		M2C_FIELD(arg0, s32*, 0x374) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x14);
		M2C_FIELD(arg0, s32*, 0x378) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x18);
		M2C_FIELD(arg0, s32*, 0x37C) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x1C);
		M2C_FIELD(arg0, s32*, 0x380) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x20);
		M2C_FIELD(arg0, s32*, 0x384) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x24);
		M2C_FIELD(arg0, s32*, 0x388) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x28);
		M2C_FIELD(arg0, s32*, 0x38C) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x2C);
		M2C_FIELD(arg0, f32*, 0x390) = (f32)M2C_FIELD(temp_r3_3, f32*, 0x30);
		M2C_FIELD(arg0, f32*, 0x394) = (f32)M2C_FIELD(temp_r3_3, f32*, 0x34);
		M2C_FIELD(arg0, f32*, 0x398) = (f32)M2C_FIELD(temp_r3_3, f32*, 0x38);
		M2C_FIELD(arg0, s32*, 0x39C) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x3C);
	}
	if (((s32)M2C_FIELD(arg0, s32*, 0x19C) != 1) && (fn_80017800(arg0) != 0)
	    && ((u32)M2C_FIELD(arg0, u32*, 0x38) != 0U)) {
		M2C_FIELD(arg0, f32*, 0xA4) = (f32)M2C_FIELD(arg0, f32*, 0x88);
		M2C_FIELD(arg0, f32*, 0xA8) = (f32)M2C_FIELD(arg0, f32*, 0x8C);
		M2C_FIELD(arg0, f32*, 0xAC) = (f32)M2C_FIELD(arg0, f32*, 0x90);
		M2C_FIELD(arg0, f32*, 0x88) = (f32)M2C_FIELD(arg0, f32*, 0x268);
		M2C_FIELD(arg0, f32*, 0x8C) = (f32)M2C_FIELD(arg0, f32*, 0x26C);
		M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0x270);
		M2C_FIELD(arg0, s32*, 0x94) = (s32)M2C_FIELD(arg0, s32*, 0x14C);
		M2C_FIELD(arg0, s32*, 0x98) = (s32)M2C_FIELD(arg0, s32*, 0x150);
		M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(arg0, s32*, 0x154);
		fn_8003BC38((u8*)arg0 + 0x28);
	}
}

void fn_8_A4140(void* arg0, s32 arg1)
{
	s32 sp6C;
	s32 sp28;
	s32 sp24;
	s32 sp20;
	s32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	s32 spC;
	u8 sp9;
	s8 sp8;

	switch (arg1) { /* irregular */
		case 0:
			if ((s8)M2C_FIELD(arg0, u8*, 0x245) == 3) {
				sp8  = 0;
				sp9  = 0;
				sp8  = 6;
				spC  = 0;
				sp18 = 0.0f;
				sp14 = 0.0f;
				sp10 = 0.0f;
				sp24 = 0;
				sp20 = 0;
				sp1C = 0;
				sp28 = 0;
				sp6C = 0;
				sp9  = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A);
				spC  = 2;
				sp28 = M2C_FIELD(arg0, s32*, 0x258);
				sp6C = M2C_FIELD(arg0, s32*, 0x230);
				fn_80100D24(&sp8, 0);
			}
			M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(void*), 0x3C)(arg0);
			return;
		case 1:
			M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			return;
	}
}

void fn_8_A4230(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x3C)();
			return;
		case 1:
			M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			return;
	}
}

void fn_8_A4290(M2C_UNK* arg0, s32 arg1)
{
	u32 temp_r4;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2E8) = 0;
			M2C_FIELD(arg0, s32*, 0xD4)  = 0;
			return;
		case 1:
			if ((void*)M2C_FIELD(arg0, void**, 0x3B4) != NULL) {
				temp_r4 = fn_8011F894();
				temp_r3 = M2C_FIELD(arg0, void**, 0xE8);
				if ((temp_r3 != NULL) && (temp_r4 != 0U)) {
					fn_8019ECCC(M2C_FIELD(temp_r3, M2C_UNK**, 4), NULL);
				}
				if (((s8)M2C_FIELD(arg0, u8*, 0x246) == 0)
				    && ((s32)((M2C_FIELD(M2C_FIELD(arg0, void**, 0x3B4), s32*, 0x38) & 2) != 0)
				        == 1)) {
					if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x24) == 5) {
						M2C_FIELD(arg0, s32*, 0x3A8) = 1;
					}
					M2C_FIELD(arg0, s32*, 0x25C) = 0x1D;
				}
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x2E8) == 0) {
				M2C_FIELD(arg0, s32*, 0x2E8) = 1;
				fn_8_A4E44(arg0);
			}
			return;
	}
}

void fn_8_A4394(void* arg0, s32 arg1)
{
	u32 temp_r4;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 0;
			return;
		case 1:
			if ((void*)M2C_FIELD(arg0, void**, 0x3B4) != NULL) {
				temp_r4 = fn_8011F894();
				temp_r3 = M2C_FIELD(arg0, void**, 0xE8);
				if ((temp_r3 != NULL) && (temp_r4 != 0U)) {
					fn_8019ECCC(M2C_FIELD(temp_r3, M2C_UNK**, 4), NULL);
				}
				if (((s8)M2C_FIELD(arg0, u8*, 0x246) == 0)
				    && ((s32)((M2C_FIELD(M2C_FIELD(arg0, void**, 0x3B4), s32*, 0x38) & 2) != 0)
				        == 1)) {
					if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x24) == 5) {
						M2C_FIELD(arg0, s32*, 0x3A8) = 1;
					}
					M2C_FIELD(arg0, s32*, 0x25C) = 0x1D;
				}
			}
			return;
	}
}

void fn_8_A4478(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xD4) = 0;
			return;
		case 3:
			if ((u32)M2C_FIELD(arg0, u32*, 0x3B4) != 0U) {
				fn_8011F8B0((s8)M2C_FIELD(arg0, u8*, 0x244));
			}
			return;
	}
}

void fn_8_A44D4(M2C_UNK* arg0, s32 arg1, s32 arg2)
{
	s32 sp6C;
	s32 sp28;
	s32 sp24;
	s32 sp20;
	s32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	s32 spC;
	u8 sp9;
	s8 sp8;
	u32 temp_r4;
	u32 temp_r4_2;
	void* temp_r3;
	void* temp_r3_2;

	switch (arg1) {         /* switch 1; irregular */
		case 1:             /* switch 1 */
			switch (arg2) { /* switch 2; irregular */
				case 0:     /* switch 2 */
					M2C_FIELD(arg0, s32*, 0xD4) = 0;
					return;
				case 3: /* switch 2 */
					if ((void*)M2C_FIELD(arg0, void**, 0x3B4) != NULL) {
						fn_8011F8B0((s8)M2C_FIELD(arg0, u8*, 0x244));
						return;
					}
					return;
			}
			break;
		case 2:             /* switch 1 */
			switch (arg2) { /* switch 3; irregular */
				case 0:     /* switch 3 */
					M2C_FIELD(arg0, s32*, 0xD4) = 0;
					return;
				case 1: /* switch 3 */
					if ((void*)M2C_FIELD(arg0, void**, 0x3B4) != NULL) {
						temp_r4 = fn_8011F894();
						temp_r3 = M2C_FIELD(arg0, void**, 0xE8);
						if ((temp_r3 != NULL) && (temp_r4 != 0U)) {
							fn_8019ECCC(M2C_FIELD(temp_r3, M2C_UNK**, 4), NULL);
						}
						if (((s8)M2C_FIELD(arg0, u8*, 0x246) == 0)
						    && ((s32)((M2C_FIELD(M2C_FIELD(arg0, void**, 0x3B4), s32*, 0x38) & 2)
						            != 0)
						        == 1)) {
							if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x24) == 5) {
								M2C_FIELD(arg0, s32*, 0x3A8) = 1;
							}
							M2C_FIELD(arg0, s32*, 0x25C) = 0x1D;
							return;
						}
					}
					break;
			}
			break;
		case 32:            /* switch 1 */
			switch (arg2) { /* switch 4; irregular */
				case 0:     /* switch 4 */
					M2C_FIELD(arg0, s32*, 0x2E8) = 0;
					M2C_FIELD(arg0, s32*, 0xD4)  = 0;
					return;
				case 1: /* switch 4 */
					if ((void*)M2C_FIELD(arg0, void**, 0x3B4) != NULL) {
						temp_r4_2 = fn_8011F894();
						temp_r3_2 = M2C_FIELD(arg0, void**, 0xE8);
						if ((temp_r3_2 != NULL) && (temp_r4_2 != 0U)) {
							fn_8019ECCC(M2C_FIELD(temp_r3_2, M2C_UNK**, 4), NULL);
						}
						if (((s8)M2C_FIELD(arg0, u8*, 0x246) == 0)
						    && ((s32)((M2C_FIELD(M2C_FIELD(arg0, void**, 0x3B4), s32*, 0x38) & 2)
						            != 0)
						        == 1)) {
							if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x24) == 5) {
								M2C_FIELD(arg0, s32*, 0x3A8) = 1;
							}
							M2C_FIELD(arg0, s32*, 0x25C) = 0x1D;
						}
					}
					if ((s32)M2C_FIELD(arg0, s32*, 0x2E8) == 0) {
						M2C_FIELD(arg0, s32*, 0x2E8) = 1;
						fn_8_A4E44(arg0);
						return;
					}
					break;
			}
			break;
		case 36:            /* switch 1 */
			switch (arg2) { /* switch 5; irregular */
				case 0:     /* switch 5 */
					M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x3C)();
					return;
				case 1: /* switch 5 */
					M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
					return;
			}
			break;
		case 29:            /* switch 1 */
			switch (arg2) { /* switch 6; irregular */
				case 0:     /* switch 6 */
					if ((s8)M2C_FIELD(arg0, u8*, 0x245) == 3) {
						sp8  = 0;
						sp9  = 0;
						sp8  = 6;
						spC  = 0;
						sp18 = 0.0f;
						sp14 = 0.0f;
						sp10 = 0.0f;
						sp24 = 0;
						sp20 = 0;
						sp1C = 0;
						sp28 = 0;
						sp6C = 0;
						sp9  = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A);
						spC  = 2;
						sp28 = M2C_FIELD(arg0, s32*, 0x258);
						sp6C = M2C_FIELD(arg0, s32*, 0x230);
						fn_80100D24(&sp8, 0);
					}
					M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(M2C_UNK*), 0x3C)(arg0);
					return;
				case 1: /* switch 6 */
					M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
					break;
			}
			break;
	}
}

void fn_8_A4830(void* arg0, void* arg1, void* arg2)
{
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	s32 temp_r28;
	s32 temp_r30;

	temp_f1 = M2C_FIELD(arg1, f32*, 8);
	if ((temp_f1 > 0.9658f)
	    || ((temp_f1 > 0.95f) && ((f32)fabs(M2C_FIELD(arg1, f32*, 4)) < 0.0009f))) {
		M2C_FIELD(arg2, s32*, 0) = 0x4000;
		M2C_FIELD(arg2, s32*, 8) = 0;
		M2C_FIELD(arg1, f32*, 0) = 0.0f;
		M2C_FIELD(arg1, f32*, 4) = 0.0f;
		M2C_FIELD(arg1, f32*, 8) = 1.0f;
	} else {
		temp_f1_2 = M2C_FIELD(arg1, f32*, 8);
		if ((temp_f1_2 < -0.9658f)
		    || ((temp_f1_2 < -0.95f) && ((f32)fabs(M2C_FIELD(arg1, f32*, 4)) < 0.0009f))) {
			M2C_FIELD(arg2, s32*, 0) = 0xC000;
			M2C_FIELD(arg2, s32*, 8) = 0;
			M2C_FIELD(arg1, f32*, 0) = 0.0f;
			M2C_FIELD(arg1, f32*, 4) = 0.0f;
			M2C_FIELD(arg1, f32*, 8) = -1.0f;
		} else {
			temp_f1_3 = M2C_FIELD(arg1, f32*, 4);
			if (temp_f1_3 > 0.99608f) {
				M2C_FIELD(arg2, s32*, 0) = 0;
				M2C_FIELD(arg2, s32*, 8) = 0;
				M2C_FIELD(arg1, f32*, 0) = 0.0f;
				M2C_FIELD(arg1, f32*, 4) = 1.0f;
				M2C_FIELD(arg1, f32*, 8) = 0.0f;
			} else if (temp_f1_3 < -0.99608f) {
				M2C_FIELD(arg2, s32*, 0) = 0x8000;
				M2C_FIELD(arg2, s32*, 8) = 0;
				M2C_FIELD(arg1, f32*, 0) = 0.0f;
				M2C_FIELD(arg1, f32*, 4) = -1.0f;
				M2C_FIELD(arg1, f32*, 8) = 0.0f;
			} else {
				M2C_FIELD(arg2, s32*, 0) = (s32)(10430.381f * (f32)asin(M2C_FIELD(arg1, f32*, 8)));
				M2C_FIELD(arg2, s32*, 8) = (s32)
				    - (s32)(10430.381f
				        * (f32)atan2(&lbl_8_rodata_1950, M2C_FIELD(arg1, f32*, 0),
				            M2C_FIELD(arg1, f32*, 4)));
			}
		}
	}
	temp_r30 = M2C_FIELD(arg2, s32*, 0);
	temp_r28 = M2C_FIELD(arg2, s32*, 8);
	fn_800D7A54(M2C_FIELD(arg0, s32*, 0x274), temp_r30);
	if (fn_800D7A54(M2C_FIELD(arg0, s32*, 0x27C), temp_r28) > 0x4000) {
		M2C_FIELD(arg2, s32*, 8) = (s32)(temp_r28 - 0x8000);
		M2C_FIELD(arg2, s32*, 0) = (s32)(0x8000 - temp_r30);
	}
}

void fn_8_A4AC0(void* arg1, void* arg2)
{
	f32 temp_f1;

	temp_f1 = fn_801991B4(arg1);
	if (temp_f1 > 0.0f) {
		M2C_FIELD(arg2, s32*, 0)
		    = (s32)(10430.381f * (f32)asin(-M2C_FIELD(arg1, f32*, 4) / temp_f1));
		M2C_FIELD(arg2, s32*, 4) = (s32)(10430.381f
		    * (f32)atan2(&lbl_8_rodata_1950, M2C_FIELD(arg1, f32*, 0), M2C_FIELD(arg1, f32*, 8)));
		M2C_FIELD(arg2, s32*, 8) = 0;
		return;
	}
	M2C_FIELD(arg2, s32*, 0) = 0;
	M2C_FIELD(arg2, s32*, 4) = 0;
	M2C_FIELD(arg2, s32*, 8) = 0;
}

void fn_8_A4B90(M2C_UNK* arg0)
{
	M2C_UNK* temp_r29;
	M2C_UNK* temp_r30_2;
	void* temp_r29_2;
	void* temp_r30;

	if ((u32)M2C_FIELD(arg0, u32*, 0x280) != 0U) {
		temp_r30 = fn_8019E8EC();
		temp_r29 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x294), M2C_UNK**, 4);
		fn_8019ED68(temp_r29, &lbl_80239990, 0.0f, M2C_FIELD(arg0, f32*, 0x29C));
		fn_8019ECCC(temp_r29, temp_r30, 2);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x284) != 0U) {
		temp_r29_2 = fn_8019E8EC();
		temp_r30_2 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x298), M2C_UNK**, 4);
		fn_8019ED68(temp_r30_2, &lbl_80239990, 0.0f, M2C_FIELD(arg0, f32*, 0x29C));
		fn_8019ECCC(temp_r30_2, temp_r29_2, 2);
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x3A4) != 0) {
		M2C_FIELD(arg0, f32*, 0x29C) = (f32)(M2C_FIELD(arg0, f32*, 0x29C) + 75.0f);
		if (((s32)M2C_FIELD(arg0, s32*, 0x19C) != 1) && ((u32)lbl_8042C388 != 0U)) {
			fn_800B4A38(0x4016, (u8*)arg0 + 0x268, arg0, 3, 0, 2);
		}
	}
}

void fn_8_A4CB0(void* arg0)
{
	s32 sp78;
	s32 sp74;
	f32 sp70;
	f32 sp6C;
	f32 sp68;
	s32 sp64;
	s32 sp60;
	s32 sp5C;
	s32 sp58;
	s32 sp54;
	s32 sp50;
	s32 sp4C;
	s32 sp48;
	s32 sp44;
	s32 sp40;
	s32 sp3C;
	s32 sp38;
	s32 sp34;
	s32 sp30;
	s32 sp2C;
	s32 sp28;
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	s32 sp18;
	u8 sp15;
	s8 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;

	if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x288) != NULL) {
		sp14 = 0;
		sp15 = 0;
		sp14 = 6;
		sp18 = 0;
		sp24 = 0.0f;
		sp20 = 0.0f;
		sp1C = 0.0f;
		sp30 = 0;
		sp2C = 0;
		sp28 = 0;
		sp34 = 0;
		sp78 = 0;
		sp15 = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A);
		sp18 = 1;
		sp34 = M2C_FIELD(arg0, s32*, 0x258);
		sp8  = M2C_FIELD(&lbl_8_rodata_18E4, s32*, 0);
		spC  = M2C_FIELD(&lbl_8_rodata_18E4, s32*, 4);
		sp10 = M2C_FIELD(&lbl_8_rodata_18E4, s32*, 8);
		fn_80196050((u8*)arg0 + 0x360, &sp8, 0);
		fn_801961E8((u8*)arg0 + 0x360, fn_8019E8EC(M2C_FIELD(arg0, M2C_UNK**, 0x288)), 2);
		sp38 = M2C_FIELD(arg0, s32*, 0x360);
		sp3C = M2C_FIELD(arg0, s32*, 0x364);
		sp40 = M2C_FIELD(arg0, s32*, 0x368);
		sp44 = M2C_FIELD(arg0, s32*, 0x36C);
		sp48 = M2C_FIELD(arg0, s32*, 0x370);
		sp4C = M2C_FIELD(arg0, s32*, 0x374);
		sp50 = M2C_FIELD(arg0, s32*, 0x378);
		sp54 = M2C_FIELD(arg0, s32*, 0x37C);
		sp58 = M2C_FIELD(arg0, s32*, 0x380);
		sp5C = M2C_FIELD(arg0, s32*, 0x384);
		sp60 = M2C_FIELD(arg0, s32*, 0x388);
		sp64 = M2C_FIELD(arg0, s32*, 0x38C);
		sp68 = M2C_FIELD(arg0, f32*, 0x390);
		sp6C = M2C_FIELD(arg0, f32*, 0x394);
		sp70 = M2C_FIELD(arg0, f32*, 0x398);
		sp74 = M2C_FIELD(arg0, s32*, 0x39C);
		sp1C = M2C_FIELD(arg0, f32*, 0x390);
		sp20 = M2C_FIELD(arg0, f32*, 0x394);
		sp24 = M2C_FIELD(arg0, f32*, 0x398);
		sp28 = M2C_FIELD(arg0, s32*, 0x14C);
		sp2C = M2C_FIELD(arg0, s32*, 0x150);
		sp30 = M2C_FIELD(arg0, s32*, 0x154);
		fn_80100D24(&sp14);
	}
}

void fn_8_A4E44(M2C_UNK* arg0)
{
	s32 sp12C;
	s32 sp128;
	f32 sp124;
	f32 sp120;
	f32 sp11C;
	s32 sp118;
	s32 sp114;
	s32 sp110;
	s32 sp10C;
	s32 sp108;
	s32 sp104;
	s32 sp100;
	s32 spFC;
	s32 spF8;
	s32 spF4;
	s32 spF0;
	s32 spEC;
	s32 spE8;
	s32 spE4;
	s32 spE0;
	s32 spDC;
	f32 spD8;
	f32 spD4;
	f32 spD0;
	s32 spCC;
	u8 spC9;
	s8 spC8;
	s32 spC4;
	s32 spC0;
	s32 spBC;
	s32 spB8;
	s32 spB4;
	s32 spB0;
	f32 spAC;
	f32 spA8;
	f32 spA4;
	f32 spA0;
	f32 sp9C;
	f32 sp98;
	f32 sp94;
	f32 sp90;
	f32 sp8C;
	f32 sp88;
	s32 sp84;
	s32 sp80;
	s32 sp7C;
	s32 sp78;
	s32 sp74;
	f32 sp70;
	f32 sp6C;
	f32 sp68;
	f32 sp64;
	f32 sp60;
	f32 sp5C;
	M2C_UNK sp50;
	f32 sp4C;
	f32 sp48;
	f32 sp44;
	M2C_UNK sp38;
	f32 sp34;
	f32 sp30;
	f32 sp2C;
	M2C_UNK sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	u8 temp_r0;

	temp_r0 = M2C_FIELD(arg0, u8*, 0x245);
	switch ((s8)temp_r0) { /* irregular */
		case 2:
			sp90 = 0.0f;
			sp8C = 0.0f;
			sp88 = 0.0f;
			sp9C = 0.0f;
			sp98 = 0.0f;
			sp94 = 0.0f;
			spB8 = 0;
			spB4 = 0;
			spB0 = 0;
			spA8 = 0.0f;
			spA4 = 0.0f;
			spA0 = 0.0f;
			spAC = 0.0f;
			spBC = 1;
			spC0 = 0x12C;
			spC4 = 8;
			sp88 = M2C_FIELD(arg0, f32*, 0x390);
			sp8C = M2C_FIELD(arg0, f32*, 0x394);
			sp90 = M2C_FIELD(arg0, f32*, 0x398);
			sp44 = M2C_FIELD(&lbl_80239984, f32*, 0);
			sp48 = M2C_FIELD(&lbl_80239984, f32*, 4);
			sp4C = M2C_FIELD(&lbl_80239984, f32*, 8);
			fn_80196414((u8*)arg0 + 0x360, &sp44, &sp10, &sp50);
			if (sp48 > 0.0f) {
				spB4 = (s32)(182.04445f * (180.0f + sp10));
			} else {
				spB4 = (s32)(182.04445f * (180.0f + (360.0f - sp10)));
			}
			spAC = M2C_FIELD(arg0, f32*, 0x24C);
			sp94 = M2C_FIELD(arg0, f32*, 0x2EC);
			sp98 = M2C_FIELD(arg0, f32*, 0x2F0);
			sp9C = M2C_FIELD(arg0, f32*, 0x2F4);
			spA0 = M2C_FIELD(arg0, f32*, 0x2F8);
			spA4 = M2C_FIELD(arg0, f32*, 0x2FC);
			spA8 = M2C_FIELD(arg0, f32*, 0x300);
			spC4 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), s32(**)(M2C_UNK*), 0x90)(arg0);
			fn_8_A9C6C(&sp88);
			M2C_FIELD(arg0, s32*, 0x2E4) = 0;
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x401A, (u8*)arg0 + 0x268, NULL, 1, 0, 0);
				return;
			}
			return;
		case 4:
			sp64 = 0.0f;
			sp60 = 0.0f;
			sp5C = 0.0f;
			sp70 = 0.0f;
			sp6C = 0.0f;
			sp68 = 0.0f;
			sp7C = 0;
			sp78 = 0;
			sp74 = 0;
			sp80 = 0x12C;
			sp84 = 8;
			sp5C = M2C_FIELD(arg0, f32*, 0x390);
			sp60 = M2C_FIELD(arg0, f32*, 0x394);
			sp64 = M2C_FIELD(arg0, f32*, 0x398);
			sp2C = M2C_FIELD(&lbl_80239984, f32*, 0);
			sp30 = M2C_FIELD(&lbl_80239984, f32*, 4);
			sp34 = M2C_FIELD(&lbl_80239984, f32*, 8);
			fn_80196414((u8*)arg0 + 0x360, &sp2C, &spC, &sp38);
			if (sp30 > 0.0f) {
				sp78 = (s32)(182.04445f * (180.0f + spC));
			} else {
				sp78 = (s32)(182.04445f * (180.0f + (360.0f - spC)));
			}
			sp68 = M2C_FIELD(arg0, f32*, 0x2EC);
			sp6C = M2C_FIELD(arg0, f32*, 0x2F0);
			sp70 = M2C_FIELD(arg0, f32*, 0x2F4);
			sp84 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), s32(**)(M2C_UNK*), 0x90)(arg0);
			fn_8_A8B60(&sp5C);
			M2C_FIELD(arg0, s32*, 0x2E4) = 0;
			return;
		case 3:
			M2C_FIELD(arg0, u8*, 0x245) = 0U;
			spC8                        = 0;
			spC9                        = 0;
			spC8                        = 6;
			spCC                        = 0;
			spD8                        = 0.0f;
			spD4                        = 0.0f;
			spD0                        = 0.0f;
			spE4                        = 0;
			spE0                        = 0;
			spDC                        = 0;
			spE8                        = 0;
			sp12C                       = 0;
			spC9                        = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A);
			spCC                        = 3;
			spE8                        = M2C_FIELD(arg0, s32*, 0x258);
			spEC                        = M2C_FIELD(arg0, s32*, 0x360);
			spF0                        = M2C_FIELD(arg0, s32*, 0x364);
			spF4                        = M2C_FIELD(arg0, s32*, 0x368);
			spF8                        = M2C_FIELD(arg0, s32*, 0x36C);
			spFC                        = M2C_FIELD(arg0, s32*, 0x370);
			sp100                       = M2C_FIELD(arg0, s32*, 0x374);
			sp104                       = M2C_FIELD(arg0, s32*, 0x378);
			sp108                       = M2C_FIELD(arg0, s32*, 0x37C);
			sp10C                       = M2C_FIELD(arg0, s32*, 0x380);
			sp110                       = M2C_FIELD(arg0, s32*, 0x384);
			sp114                       = M2C_FIELD(arg0, s32*, 0x388);
			sp118                       = M2C_FIELD(arg0, s32*, 0x38C);
			sp11C                       = M2C_FIELD(arg0, f32*, 0x390);
			sp120                       = M2C_FIELD(arg0, f32*, 0x394);
			sp124                       = M2C_FIELD(arg0, f32*, 0x398);
			sp128                       = M2C_FIELD(arg0, s32*, 0x39C);
			spD0                        = M2C_FIELD(arg0, f32*, 0x390);
			spD4                        = M2C_FIELD(arg0, f32*, 0x394);
			spD8                        = M2C_FIELD(arg0, f32*, 0x398);
			sp14                        = M2C_FIELD(&lbl_80239984, f32*, 0);
			sp18                        = M2C_FIELD(&lbl_80239984, f32*, 4);
			sp1C                        = M2C_FIELD(&lbl_80239984, f32*, 8);
			fn_80196414((u8*)arg0 + 0x360, &sp14, &sp8, &sp20);
			if (sp18 > 0.0f) {
				spE0 = (s32)(182.04445f * (180.0f + sp8));
			} else {
				spE0 = (s32)(182.04445f * (180.0f + (360.0f - sp8)));
			}
			fn_80100D24(&spC8);
			return;
		case 1:
			if ((u32)M2C_FIELD(arg0, u32*, 0x304) != 0U) {
				fn_8_5F140();
				if ((u32)lbl_8042C388 != 0U) {
					fn_800B4A38(0x4018, (u8*)arg0 + 0x268, arg0, 3, 0, 2);
				}
			}
			break;
	}
}

void fn_8_A53E4(void* arg0)
{
	u32 temp_r4;
	void* temp_r3;

	if ((void*)M2C_FIELD(arg0, void**, 0x3B4) != NULL) {
		temp_r4 = fn_8011F894();
		temp_r3 = M2C_FIELD(arg0, void**, 0xE8);
		if ((temp_r3 != NULL) && (temp_r4 != 0U)) {
			fn_8019ECCC(M2C_FIELD(temp_r3, M2C_UNK**, 4), NULL);
		}
		if (((s8)M2C_FIELD(arg0, u8*, 0x246) == 0)
		    && ((s32)((M2C_FIELD(M2C_FIELD(arg0, void**, 0x3B4), s32*, 0x38) & 2) != 0) == 1)) {
			if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x24) == 5) {
				M2C_FIELD(arg0, s32*, 0x3A8) = 1;
			}
			M2C_FIELD(arg0, s32*, 0x25C) = 0x1D;
		}
	}
}

void fn_8_A549C(void* arg0, ...)
{
	f32 sp28;
	f32 sp24;
	f32 sp20;
	s32 sp1C;
	s32 sp18;
	s32 sp14;
	s32 sp10;
	s32 sp8;
	M2C_UNK* temp_r30;
	M2C_UNK* temp_r30_3;
	M2C_UNK* temp_r4;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f0_3;
	f32 temp_f1;
	s32 temp_r3_4;
	s32 temp_r3_7;
	s32 temp_r3_8;
	void* temp_r30_2;
	void* temp_r30_4;
	void* temp_r30_5;
	void* temp_r30_6;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_5;
	void* temp_r3_6;
	void* temp_r4_2;

	temp_r3 = M2C_FIELD(arg0, void**, 0xE8);
	if (temp_r3 != NULL) {
		temp_r30 = M2C_FIELD(temp_r3, M2C_UNK**, 4);
		fn_8019ED68(temp_r30, &lbl_80239984, 3e-45f,
		    0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150), 0.005493164f);
		fn_8019EB94(temp_r30, (u8*)arg0 + 0x140, 2);
		sp20                         = M2C_FIELD(arg0, f32*, 0x268);
		sp24                         = M2C_FIELD(arg0, f32*, 0x26C);
		sp28                         = M2C_FIELD(arg0, f32*, 0x270);
		temp_r3_2                    = fn_8019E8EC(temp_r30);
		M2C_FIELD(arg0, f32*, 0x268) = (f32)M2C_FIELD(temp_r3_2, f32*, 0x30);
		M2C_FIELD(arg0, f32*, 0x26C) = (f32)M2C_FIELD(temp_r3_2, f32*, 0x34);
		M2C_FIELD(arg0, f32*, 0x270) = (f32)M2C_FIELD(temp_r3_2, f32*, 0x38);
		M2C_FIELD(arg0, f32*, 0x2EC) = (f32)(M2C_FIELD(arg0, f32*, 0x268) - sp20);
		M2C_FIELD(arg0, f32*, 0x2F0) = (f32)(M2C_FIELD(arg0, f32*, 0x26C) - sp24);
		M2C_FIELD(arg0, f32*, 0x2F4) = (f32)(M2C_FIELD(arg0, f32*, 0x270) - sp28);
		temp_f0                      = M2C_FIELD(arg0, f32*, 0x2F4);
		temp_f0_2                    = M2C_FIELD(arg0, f32*, 0x2EC);
		temp_f0_3                    = M2C_FIELD(arg0, f32*, 0x2F0);
		if (((temp_f0 * temp_f0) + ((temp_f0_2 * temp_f0_2) + (temp_f0_3 * temp_f0_3))) != 0.0f) {
			temp_r3_3 = (u8*)arg0 + 0x2EC;
			fn_801990E0(temp_r3_3, temp_r3_3);
		}
		M2C_FIELD(arg0, f32*, 0x2EC)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x2EC) * M2C_FIELD(arg0, f32*, 0x248));
		M2C_FIELD(arg0, f32*, 0x2F0)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x2F0) * M2C_FIELD(arg0, f32*, 0x248));
		M2C_FIELD(arg0, f32*, 0x2F4)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x2F4) * M2C_FIELD(arg0, f32*, 0x248));
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x288) == 0U) {
		temp_r30_2 = M2C_FIELD(arg0, void**, 0xEC);
		if (temp_r30_2 != NULL) {
			temp_r3_4 = fn_8005D9A0(temp_r30_2, 0x3F2);
			if (temp_r3_4 != -1) {
				M2C_FIELD(arg0, u32*, 0x288) = (u32)M2C_FIELD(
				    (M2C_FIELD(temp_r30_2, s32*, 0x10) + (temp_r3_4 * 0x10)), u32*, 0xC);
			}
		}
	}
	if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x290) == NULL) {
		temp_r3_5 = M2C_FIELD(arg0, void**, 0x2A0);
		if (temp_r3_5 != NULL) {
			M2C_FIELD(arg0, M2C_UNK**, 0x290) = fn_8005DEEC(M2C_FIELD(temp_r3_5, M2C_UNK**, 4), 1);
			temp_r4                           = M2C_FIELD(arg0, M2C_UNK**, 0x290);
			if (temp_r4 != NULL) {
				M2C_FIELD(arg0, s32*, 0x308) = (s32)M2C_FIELD(temp_r4, s32*, 0x10);
				M2C_FIELD(arg0, s32*, 0x30C) = (s32)M2C_FIELD(temp_r4, s32*, 0x14);
				M2C_FIELD(arg0, s32*, 0x310) = (s32)M2C_FIELD(temp_r4, s32*, 0x18);
				M2C_FIELD(arg0, s32*, 0x314) = (s32)M2C_FIELD(temp_r4, s32*, 0x1C);
				M2C_FIELD(arg0, s32*, 0x318) = (s32)M2C_FIELD(temp_r4, s32*, 0x20);
				M2C_FIELD(arg0, s32*, 0x31C) = (s32)M2C_FIELD(temp_r4, s32*, 0x24);
				M2C_FIELD(arg0, s32*, 0x320) = (s32)M2C_FIELD(temp_r4, s32*, 0x28);
				M2C_FIELD(arg0, s32*, 0x324) = (s32)M2C_FIELD(temp_r4, s32*, 0x2C);
				M2C_FIELD(arg0, s32*, 0x328) = (s32)M2C_FIELD(temp_r4, s32*, 0x30);
				M2C_FIELD(arg0, s32*, 0x32C) = (s32)M2C_FIELD(temp_r4, s32*, 0x34);
				M2C_FIELD(arg0, s32*, 0x330) = (s32)M2C_FIELD(temp_r4, s32*, 0x38);
				M2C_FIELD(arg0, s32*, 0x334) = (s32)M2C_FIELD(temp_r4, s32*, 0x3C);
				M2C_FIELD(arg0, s32*, 0x338) = (s32)M2C_FIELD(temp_r4, s32*, 0x40);
				M2C_FIELD(arg0, s32*, 0x33C) = (s32)M2C_FIELD(temp_r4, s32*, 0x44);
				M2C_FIELD(arg0, s32*, 0x340) = (s32)M2C_FIELD(temp_r4, s32*, 0x48);
				M2C_FIELD(arg0, s32*, 0x344) = (s32)M2C_FIELD(temp_r4, s32*, 0x4C);
			}
		}
	}
	if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x28C) == NULL) {
		temp_r3_6 = M2C_FIELD(arg0, void**, 0x2A0);
		if (temp_r3_6 != NULL) {
			M2C_FIELD(arg0, M2C_UNK**, 0x28C) = fn_8005DEEC(M2C_FIELD(temp_r3_6, M2C_UNK**, 4), 2);
		}
	}
	if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x290) != NULL) {
		fn_8019ED68(
		    &lbl_80239978, NULL, 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x250), 0.005493164f);
		fn_8019ECCC(M2C_FIELD(arg0, M2C_UNK**, 0x290), (u8*)arg0 + 0x308, 2);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x288) != 0U) {
		temp_r4_2 = M2C_FIELD(arg0, void**, 0x2A0);
		if (temp_r4_2 != NULL) {
			temp_r30_3 = M2C_FIELD(temp_r4_2, M2C_UNK**, 4);
			fn_8019ECCC(temp_r30_3, fn_8019E8EC(), 0);
		}
	}
	if (((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x28C) != NULL)
	    && ((u32)M2C_FIELD(arg0, u32*, 0x304) != 0U)) {
		temp_r30_4 = fn_8019E8EC();
		sp14       = M2C_FIELD(&lbl_8_rodata_18D8, s32*, 0);
		sp18       = M2C_FIELD(&lbl_8_rodata_18D8, s32*, 4);
		sp1C       = M2C_FIELD(&lbl_8_rodata_18D8, s32*, 8);
		fn_8019941C(&sp14, &sp14, 1, temp_r30_4);
		fn_8_5F048(M2C_FIELD(arg0, u32*, 0x304), (u8*)temp_r30_4 + 0x30);
		fn_8_5EF94(M2C_FIELD(arg0, u32*, 0x304), &sp14);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x280) == 0U) {
		temp_r30_5 = M2C_FIELD(arg0, void**, 0xEC);
		if (temp_r30_5 != NULL) {
			temp_r3_7 = fn_8005D9A0(temp_r30_5, 0x3EA);
			if (temp_r3_7 != -1) {
				M2C_FIELD(arg0, u32*, 0x280) = (u32)M2C_FIELD(
				    (M2C_FIELD(temp_r30_5, s32*, 0x10) + (temp_r3_7 * 0x10)), u32*, 0xC);
			}
		}
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x284) == 0U) {
		temp_r30_6 = M2C_FIELD(arg0, void**, 0xEC);
		if (temp_r30_6 != NULL) {
			temp_r3_8 = fn_8005D9A0(temp_r30_6, 0x3EB);
			if (temp_r3_8 != -1) {
				M2C_FIELD(arg0, u32*, 0x284) = (u32)M2C_FIELD(
				    (M2C_FIELD(temp_r30_6, s32*, 0x10) + (temp_r3_8 * 0x10)), u32*, 0xC);
			}
		}
	}
	if ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x18) & 0x20000) != 0) {
		if ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0) {
			M2C_FIELD(arg0, f32*, 0x354) = (f32)M2C_FIELD(arg0, f32*, 0x118);
			M2C_FIELD(arg0, f32*, 0x35C) = (f32)M2C_FIELD(arg0, f32*, 0x120);
			M2C_FIELD(arg0, f32*, 0x34C) = (f32)(1.0f + M2C_FIELD(arg0, f32*, 0x26C));
		} else {
			temp_f1                      = fn_800D8BC4((u8*)arg0 + 0x268, &sp8, 1);
			M2C_FIELD(arg0, f32*, 0x34C) = temp_f1;
			if (temp_f1 != -1000000.0f) {
				M2C_FIELD(arg0, f32*, 0x348) = (f32)M2C_FIELD(arg0, f32*, 0x268);
				M2C_FIELD(arg0, f32*, 0x34C) = (f32)(M2C_FIELD(arg0, f32*, 0x34C) + 1.0f);
				M2C_FIELD(arg0, f32*, 0x350) = (f32)M2C_FIELD(arg0, f32*, 0x270);
				M2C_FIELD(arg0, f32*, 0x354) = (f32)(0.005493164f * (f32)sp8);
				M2C_FIELD(arg0, f32*, 0x35C) = (f32)(0.005493164f * (f32)sp10);
			}
		}
		M2C_FIELD(arg0, f32*, 0x358)
		    = (f32)(180.0f + (0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0x150)));
		M2C_FIELD(arg0, f32*, 0x348) = (f32)M2C_FIELD(arg0, f32*, 0x268);
		M2C_FIELD(arg0, f32*, 0x350) = (f32)M2C_FIELD(arg0, f32*, 0x270);
	}
}

void fn_8_A5A04(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x2A0) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x2A0) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x298) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x298) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x294) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x294) = 0U;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0xE8) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0xE8) = 0U;
	}
}

void fn_8_A5A8C(void* arg0)
{
	u32 var_r3;
	u8 temp_r0;
	void* temp_r3;

	if ((void*)M2C_FIELD(arg0, void**, 0x2A0) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2A0) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x298) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x298) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x294) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x294) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	M2C_FIELD(arg0, void**, 0xE8)  = fn_80150588(M2C_FIELD(&lbl_8_bss_1948, s32*, 0));
	M2C_FIELD(arg0, void**, 0x294) = fn_80150588(M2C_FIELD(&lbl_8_bss_1948, s32*, 0xC));
	M2C_FIELD(arg0, void**, 0x298) = fn_80150588(M2C_FIELD(&lbl_8_bss_1948, s32*, 0xC));
	var_r3                         = 0U;
	temp_r0                        = M2C_FIELD(arg0, u8*, 0x245);
	switch ((s8)temp_r0) { /* irregular */
		case 0:
			break;
		case 1:
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
				fn_80100AAC();
			}
			var_r3 = fn_8010037C(lbl_8042C590, 5, 9);
			break;
		case 2:
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
				fn_80100AAC();
			}
			var_r3 = fn_8010037C(lbl_8042C590, 5, 0xA);
			break;
		case 4:
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
				fn_80100AAC();
			}
			var_r3 = fn_8010037C(lbl_8042C590, 5, 8);
			break;
	}
	if (var_r3 != 0U) {
		M2C_FIELD(arg0, void**, 0x2A0) = fn_80150588();
	}
	temp_r3 = M2C_FIELD(arg0, void**, 0xE8);
	if (temp_r3 != NULL) {
		fn_8019EE04(M2C_FIELD(temp_r3, s32*, 4));
	}
}

void fn_8_A5C70(void* arg0)
{
	void* temp_r4;
	void* temp_r4_2;
	void* temp_r5;

	temp_r4                      = M2C_FIELD(arg0, void**, 0xB0);
	temp_r5                      = M2C_FIELD(temp_r4, void**, 0x2C);
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
	M2C_FIELD(arg0, f32*, 0x1B8) = 1.5f;
	M2C_FIELD(arg0, u8*, 0x245)  = (u8)M2C_FIELD(temp_r5, u8*, 0);
	M2C_FIELD(arg0, u8*, 0x244)  = (u8)M2C_FIELD(temp_r5, u8*, 1);
	M2C_FIELD(arg0, u8*, 0x246)  = (u8)M2C_FIELD(temp_r5, u8*, 2);
	M2C_FIELD(arg0, f32*, 0x248) = (f32)M2C_FIELD(temp_r5, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x24C) = (f32)M2C_FIELD(temp_r5, f32*, 0xC);
	M2C_FIELD(arg0, s32*, 0x250) = (s32)M2C_FIELD(temp_r5, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x254) = (s32)M2C_FIELD(temp_r5, s32*, 8);
	M2C_FIELD(arg0, s32*, 0x258) = (s32)M2C_FIELD(temp_r5, s32*, 0x14);
}

void fn_8_A5D48(void* arg0)
{
	M2C_FIELD(arg0, s32*, 0x240) = 0;
	M2C_FIELD(arg0, s32*, 0x260) = 0;
	M2C_FIELD(arg0, f32*, 0x264) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x280) = 0;
	M2C_FIELD(arg0, s32*, 0x284) = 0;
	M2C_FIELD(arg0, s32*, 0x288) = 0;
	M2C_FIELD(arg0, s32*, 0x28C) = 0;
	M2C_FIELD(arg0, s32*, 0x290) = 0;
	M2C_FIELD(arg0, s32*, 0x294) = 0;
	M2C_FIELD(arg0, s32*, 0x298) = 0;
	M2C_FIELD(arg0, s32*, 0x2A0) = 0;
	M2C_FIELD(arg0, f32*, 0x29C) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x25C) = 0;
	fn_8001F404((u8*)arg0 + 0x2A4);
	M2C_FIELD(arg0, s32*, 0x2E4) = 1;
	M2C_FIELD(arg0, f32*, 0x24C) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x250) = 0;
	M2C_FIELD(arg0, s32*, 0x304) = 0;
	M2C_FIELD(arg0, s32*, 0x3AC) = 0;
	M2C_FIELD(arg0, s32*, 0x3B0) = 0;
	M2C_FIELD(arg0, s32*, 0x3B4) = 0;
	M2C_FIELD(arg0, s32*, 0x258) = 0;
	M2C_FIELD(arg0, s32*, 0x3A0) = 1;
	M2C_FIELD(arg0, s32*, 0x3A4) = 1;
	M2C_FIELD(arg0, s32*, 0x3B8) = 0;
	M2C_FIELD(arg0, f32*, 0x3C0) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x3BC) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x3A8) = 0;
}

void* fn_8_A5E08(void* arg0, s16 arg1)
{
	s32 temp_cr0_eq;
	void** temp_r3;

	if (arg0 != NULL) {
		M2C_FIELD(arg0, M2C_UNK**, 0x18) = &lbl_8_data_161C8;
		M2C_FIELD(arg0, void**, 0xB4)    = (void*)(&lbl_8_data_161C8 + 0x2C);
		if ((u32)M2C_FIELD(arg0, u32*, 0x304) != 0U) {
			pawnReleaseBuffer();
			M2C_FIELD(arg0, u32*, 0x304) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x3B8) != 0U) {
			fn_8010AFE4();
			M2C_FIELD(arg0, u32*, 0x3B8) = 0U;
		}
		temp_r3     = M2C_FIELD(arg0, void***, 0x240);
		temp_cr0_eq = temp_r3 == NULL;
		if (temp_cr0_eq == 0) {
			if (temp_cr0_eq == 0) {
				M2C_FIELD(*temp_r3, M2C_UNK(**)(M2C_UNK), 8)(1);
			}
			M2C_FIELD(arg0, void***, 0x240) = NULL;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x2A0) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x2A0) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x298) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x298) = 0U;
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x294) != 0U) {
			fn_80150958();
			M2C_FIELD(arg0, u32*, 0x294) = 0U;
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

M2C_UNK* fn_8_A5F50(M2C_UNK* arg0)
{
	s32 sp8;
	s32 spC, sp10, sp14, sp18, sp1C, sp20, sp24, sp28;
	s32 sp2C, sp30, sp34, sp38, sp3C, sp40, sp44;
	M2C_UNK* temp_r29;
	M2C_UNK* temp_r30_2;
	M2C_UNK* temp_r4_2;
	M2C_UNK* var_r0_3;
	f32 temp_f0;
	f32 temp_f31;
	u32 var_r0;
	u32 var_r0_2;
	u32 var_r3;
	u8 temp_r0;
	void* temp_r29_2;
	void* temp_r30;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r4;

	fn_800A714C();
	__ct__10HAnimClassFv((u8*)arg0 + 0x240);
	M2C_FIELD(arg0, M2C_UNK**, 0x18) = &lbl_8_data_161C8;
	M2C_FIELD(arg0, void**, 0xB4)    = (void*)(&lbl_8_data_161C8 + 0x2C);
	M2C_FIELD(arg0, M2C_UNK**, 0)    = (M2C_UNK*)lbl_8_data_161C4;
	M2C_FIELD(arg0, s16*, 0x1E)      = 0x3C4;
	M2C_FIELD(arg0, u32*, 0x240)     = 0U;
	M2C_FIELD(arg0, s32*, 0x260)     = 0;
	M2C_FIELD(arg0, f32*, 0x264)     = 0.0f;
	M2C_FIELD(arg0, u32*, 0x280)     = 0U;
	M2C_FIELD(arg0, u32*, 0x284)     = 0U;
	M2C_FIELD(arg0, s32*, 0x288)     = 0;
	M2C_FIELD(arg0, s32*, 0x28C)     = 0;
	M2C_FIELD(arg0, s32*, 0x290)     = 0;
	M2C_FIELD(arg0, void**, 0x294)   = NULL;
	M2C_FIELD(arg0, void**, 0x298)   = NULL;
	M2C_FIELD(arg0, void**, 0x2A0)   = NULL;
	M2C_FIELD(arg0, f32*, 0x29C)     = 0.0f;
	M2C_FIELD(arg0, s32*, 0x25C)     = 0;
	fn_8001F404((u8*)arg0 + 0x2A4);
	M2C_FIELD(arg0, s32*, 0x2E4)      = 1;
	M2C_FIELD(arg0, f32*, 0x24C)      = 0.0f;
	M2C_FIELD(arg0, s32*, 0x250)      = 0;
	M2C_FIELD(arg0, s32*, 0x304)      = 0;
	M2C_FIELD(arg0, s32*, 0x3AC)      = 0;
	M2C_FIELD(arg0, s32*, 0x3B0)      = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0x3B4) = NULL;
	M2C_FIELD(arg0, s32*, 0x258)      = 0;
	M2C_FIELD(arg0, s32*, 0x3A0)      = 1;
	M2C_FIELD(arg0, s32*, 0x3A4)      = 1;
	M2C_FIELD(arg0, s32*, 0x3B8)      = 0;
	M2C_FIELD(arg0, f32*, 0x3C0)      = 0.0f;
	M2C_FIELD(arg0, f32*, 0x3BC)      = 0.0f;
	M2C_FIELD(arg0, s32*, 0x3A8)      = 0;
	temp_r3                           = M2C_FIELD(arg0, void**, 0xB0);
	temp_r4                           = M2C_FIELD(temp_r3, void**, 0x2C);
	M2C_FIELD(arg0, f32*, 0x140)      = (f32)M2C_FIELD(temp_r3, f32*, 0);
	M2C_FIELD(arg0, f32*, 0x144)      = (f32)M2C_FIELD(temp_r3, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x148)      = (f32)M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2                         = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, s32*, 0x14C)      = (s32)M2C_FIELD(temp_r3_2, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0x150)      = (s32)M2C_FIELD(temp_r3_2, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x154)      = (s32)M2C_FIELD(temp_r3_2, s32*, 0x14);
	M2C_FIELD(arg0, f32*, 0x1C0)      = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1C4)      = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1C8)      = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x1CC)      = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1D0)      = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1D4)      = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x1C0)      = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1C4)      = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1C8)      = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x1B8)      = 1.5f;
	M2C_FIELD(arg0, u8*, 0x245)       = (u8)M2C_FIELD(temp_r4, u8*, 0);
	M2C_FIELD(arg0, u8*, 0x244)       = (u8)M2C_FIELD(temp_r4, u8*, 1);
	M2C_FIELD(arg0, u8*, 0x246)       = (u8)M2C_FIELD(temp_r4, u8*, 2);
	M2C_FIELD(arg0, f32*, 0x248)      = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x24C)      = (f32)M2C_FIELD(temp_r4, f32*, 0xC);
	M2C_FIELD(arg0, s32*, 0x250)      = (s32)M2C_FIELD(temp_r4, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x254)      = (s32)M2C_FIELD(temp_r4, s32*, 8);
	M2C_FIELD(arg0, s32*, 0x258)      = (s32)M2C_FIELD(temp_r4, s32*, 0x14);
	M2C_FIELD(arg0, f32*, 0x160)      = 0.0f;
	M2C_FIELD(arg0, f32*, 0x15C)      = 0.0f;
	M2C_FIELD(arg0, f32*, 0x158)      = 0.0f;
	M2C_FIELD(arg0, s32*, 0x188)      = (s32)(M2C_FIELD(arg0, s32*, 0x188) & 0xFFEFCFFF);
	M2C_FIELD(arg0, s32*, 0x188)      = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x100000);
	M2C_FIELD(arg0, s32*, 0x188)      = (s32)(M2C_FIELD(arg0, s32*, 0x188) | 0x10);
	M2C_FIELD(arg0, f32*, 0x3C0)      = 3.0f;
	M2C_FIELD(arg0, f32*, 0x3BC)      = (f32)M2C_FIELD(arg0, f32*, 0x3C0);
	temp_f0                           = M2C_FIELD(arg0, f32*, 0x3C0);
	M2C_FIELD(arg0, f32*, 0x1A4)      = temp_f0;
	M2C_FIELD(arg0, s16*, 0x2E)       = (s16)temp_f0;
	M2C_FIELD(arg0, f32*, 0x1A0)      = 3.0f;
	M2C_FIELD(arg0, s16*, 0x2C)       = 3;
	if ((void*)M2C_FIELD(arg0, void**, 0x2A0) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x2A0) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x298) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x298) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0x294) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0x294) = NULL;
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xE8) != NULL) {
		fn_80150958();
		M2C_FIELD(arg0, void**, 0xE8) = NULL;
	}
	M2C_FIELD(arg0, void**, 0xE8)  = fn_80150588(M2C_FIELD(&lbl_8_bss_1948, s32*, 0));
	M2C_FIELD(arg0, void**, 0x294) = fn_80150588(M2C_FIELD(&lbl_8_bss_1948, s32*, 0xC));
	M2C_FIELD(arg0, void**, 0x298) = fn_80150588(M2C_FIELD(&lbl_8_bss_1948, s32*, 0xC));
	var_r3                         = 0U;
	temp_r0                        = M2C_FIELD(arg0, u8*, 0x245);
	switch ((s8)temp_r0) { /* irregular */
		case 0:
			break;
		case 1:
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
				fn_80100AAC();
			}
			var_r3 = fn_8010037C(lbl_8042C590, 5, 9);
			break;
		case 2:
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
				fn_80100AAC();
			}
			var_r3 = fn_8010037C(lbl_8042C590, 5, 0xA);
			break;
		case 4:
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
				fn_80100AAC();
			}
			var_r3 = fn_8010037C(lbl_8042C590, 5, 8);
			break;
	}
	if (var_r3 != 0U) {
		M2C_FIELD(arg0, void**, 0x2A0) = fn_80150588();
	}
	temp_r3_3 = M2C_FIELD(arg0, void**, 0xE8);
	if (temp_r3_3 != NULL) {
		fn_8019EE04(M2C_FIELD(temp_r3_3, s32*, 4));
	}
	fn_8005D5C8(M2C_FIELD(arg0, void**, 0xE8),
	    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), s32*, 0x18) & 0x1C0000) >> 0x12U) + 8);
	M2C_FIELD(arg0, M2C_UNK**, 0xE4) = &lbl_8_data_16018;
	M2C_FIELD(arg0, s32*, 0xD4)      = 0;
	fn_800FE464((u8*)arg0 + 0xB8);
	fn_8_A549C(arg0);
	if ((u32)M2C_FIELD(arg0, u32*, 0x280) != 0U) {
		temp_r30 = fn_8019E8EC();
		temp_r29 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x294), M2C_UNK**, 4);
		fn_8019ED68(temp_r29, &lbl_80239990, 0.0f, M2C_FIELD(arg0, f32*, 0x29C));
		fn_8019ECCC(temp_r29, temp_r30, 2);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x284) != 0U) {
		temp_r29_2 = fn_8019E8EC();
		temp_r30_2 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x298), M2C_UNK**, 4);
		fn_8019ED68(temp_r30_2, &lbl_80239990, 0.0f, M2C_FIELD(arg0, f32*, 0x29C));
		fn_8019ECCC(temp_r30_2, temp_r29_2, 2);
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x3A4) != 0) {
		M2C_FIELD(arg0, f32*, 0x29C) = (f32)(M2C_FIELD(arg0, f32*, 0x29C) + 75.0f);
		if (((s32)M2C_FIELD(arg0, s32*, 0x19C) != 1) && ((u32)lbl_8042C388 != 0U)) {
			fn_800B4A38(0x4016, (u8*)arg0 + 0x268, arg0, 3, 0, 2);
		}
	}
	if (fn_8005B8D8((u8*)arg0 + 0xB0) == 0) {
		fn_8003C200((u8*)arg0 + 0x28, &lbl_8_data_15FD8, 1, 3);
		M2C_FIELD(arg0, f32*, 0x88) = (f32)M2C_FIELD(arg0, f32*, 0x140);
		M2C_FIELD(arg0, f32*, 0x8C) = (f32)M2C_FIELD(arg0, f32*, 0x144);
		M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	}
	M2C_FIELD(arg0, f32*, 0x130) = 12.0f;
	M2C_FIELD(arg0, f32*, 0x134) = 0.8f;
	var_r0                       = fn_80057644(0x1C);
	if (var_r0 != 0U) {
		var_r0 = fn_8_AA58C();
	}
	M2C_FIELD(arg0, u32*, 0x240) = var_r0;
	if ((u32)M2C_FIELD(arg0, u32*, 0x240) != 0U) {
		fn_8_AA08C(arg0);
	}
	M2C_FIELD(arg0, s32*, 0x3B8) = fn_8010B708(0);
	M2C_FIELD(arg0, s32*, 0x13C) = 1;
	var_r0_2                     = fn_80057644(0x20);
	if (var_r0_2 != 0U) {
		var_r0_2 = fn_800FD8A0(arg0, M2C_FIELD(arg0, s32*, 0x13C));
	}
	M2C_FIELD(arg0, u32*, 0x228) = var_r0_2;
	if ((s8)M2C_FIELD(arg0, u8*, 0x245) == 1) {
		M2C_FIELD(arg0, s32*, 0x304) = fn_8_5F30C(
		    lbl_8042C10C, (u8*)arg0 + 0x140, (u8*)arg0 + 0x14C, &lbl_8_rodata_196C, 200.0f);
		fn_8_5F100(M2C_FIELD(arg0, s32*, 0x304));
	}
	var_r0_3 = fn_80018A34(lbl_8042C148, 0xD0);
	if (var_r0_3 != NULL) {
		var_r0_3 = fn_8011FA4C(arg0, lbl_8_bss_1958);
	}
	M2C_FIELD(arg0, M2C_UNK**, 0x3B4) = var_r0_3;
	if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x3B4) != NULL) {
		temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x150));
		fn_80195790(
		    &sp8, &lbl_80239984, 0, 1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x150)), temp_f31);
		fn_80196050(&sp8, (u8*)arg0 + 0x140, 2);
		temp_r4_2                        = M2C_FIELD(arg0, M2C_UNK**, 0x3B4);
		M2C_FIELD(temp_r4_2, s32*, 0x7C) = sp8;
		M2C_FIELD(temp_r4_2, s32*, 0x80) = spC;
		M2C_FIELD(temp_r4_2, s32*, 0x84) = sp10;
		M2C_FIELD(temp_r4_2, s32*, 0x88) = sp14;
		M2C_FIELD(temp_r4_2, s32*, 0x8C) = sp18;
		M2C_FIELD(temp_r4_2, s32*, 0x90) = sp1C;
		M2C_FIELD(temp_r4_2, s32*, 0x94) = sp20;
		M2C_FIELD(temp_r4_2, s32*, 0x98) = sp24;
		M2C_FIELD(temp_r4_2, s32*, 0x9C) = sp28;
		M2C_FIELD(temp_r4_2, s32*, 0xA0) = sp2C;
		M2C_FIELD(temp_r4_2, s32*, 0xA4) = sp30;
		M2C_FIELD(temp_r4_2, s32*, 0xA8) = sp34;
		M2C_FIELD(temp_r4_2, s32*, 0xAC) = sp38;
		M2C_FIELD(temp_r4_2, s32*, 0xB0) = sp3C;
		M2C_FIELD(temp_r4_2, s32*, 0xB4) = sp40;
		M2C_FIELD(temp_r4_2, s32*, 0xB8) = sp44;
		M2C_FIELD(M2C_FIELD(arg0, M2C_UNK**, 0x3B4), f32*, 0x34)
		    = (f32)M2C_FIELD(arg0, f32*, 0x248);
		fn_8011F900(M2C_FIELD(arg0, M2C_UNK**, 0x3B4), (s8)M2C_FIELD(arg0, u8*, 0x244));
	}
	return arg0;
}

M2C_UNK* fn_8_A66D4(void)
{
	M2C_UNK* var_r0;

	var_r0 = fn_80018A34(lbl_8042C148, 0x3C4);
	if (var_r0 != NULL) {
		var_r0 = fn_8_A5F50(lbl_8042C10C);
	}
	return var_r0;
}

void fn_8_A6728(void* arg1)
{
	f32* var_r4_3;
	f32 temp_f1;
	s32* var_r4_4;
	s32 temp_r5;
	u8* temp_r3;
	u8* var_r4;
	u8* var_r4_2;
	u8 temp_r0;
	u8 temp_r0_2;

	temp_r3 = M2C_FIELD(arg1, u8**, 0x2C);
	temp_r0 = M2C_FIELD(temp_r3, u8*, 0);
	var_r4  = &lbl_8_data_161B0;
	if ((s8)temp_r0 < (s8)lbl_8_data_161B0) {

	} else {
		var_r4 = &lbl_8_data_161B1;
		if ((s8)temp_r0 > (s8)lbl_8_data_161B1) {

		} else {
			var_r4 = temp_r3;
		}
	}
	M2C_FIELD(temp_r3, u8*, 0) = (u8)(s8)*var_r4;
	temp_r0_2                  = M2C_FIELD(temp_r3, u8*, 2);
	var_r4_2                   = &lbl_8_data_161B2;
	if ((s8)temp_r0_2 < (s8)lbl_8_data_161B2) {

	} else {
		var_r4_2 = &lbl_8_data_161B3;
		if ((s8)temp_r0_2 > (s8)lbl_8_data_161B3) {

		} else {
			var_r4_2 = temp_r3 + 2;
		}
	}
	M2C_FIELD(temp_r3, u8*, 2) = (u8)(s8)*var_r4_2;
	temp_f1                    = M2C_FIELD(temp_r3, f32*, 4);
	var_r4_3                   = &lbl_8_rodata_1970;
	if (temp_f1 < 0.0f) {

	} else {
		var_r4_3 = &lbl_8_rodata_1974;
		if (temp_f1 > 1000.0f) {

		} else {
			var_r4_3 = (f32*)(temp_r3 + 4);
		}
	}
	M2C_FIELD(temp_r3, f32*, 4) = (f32)*var_r4_3;
	temp_r5                     = M2C_FIELD(temp_r3, s32*, 0x14);
	var_r4_4                    = &lbl_8_rodata_1978;
	if (temp_r5 < (s32)lbl_8_rodata_1978) {

	} else {
		var_r4_4 = lbl_8_rodata_197C;
		if (temp_r5 > (s32)*lbl_8_rodata_197C) {

		} else {
			var_r4_4 = (s32*)(temp_r3 + 0x14);
		}
	}
	M2C_FIELD(temp_r3, s32*, 0x14) = (s32)*var_r4_4;
	M2C_FIELD(&flyerObjectFieldNames, M2C_UNK**, 0)
	    = (M2C_UNK*)lbl_8_data_16180[(s8)M2C_FIELD(temp_r3, u8*, 0)];
	M2C_FIELD(&flyerObjectFieldNames, M2C_UNK**, 8)
	    = (M2C_UNK*)lbl_8_data_161A8[(s8)M2C_FIELD(temp_r3, u8*, 2)];
}

void flyerObjectUnload(void)
{
	if ((u32)lbl_8_bss_1958 != 0U) {
		fn_8011FD94(1);
		lbl_8_bss_1958 = 0U;
	}
	fn_8_A8D1C();
	fn_8_A9E18();
	fn_800FE248(5, &lbl_8_data_16070);
	fn_800FE248(5, &lbl_8_data_16018);
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
		fn_80100AAC();
	}
	fn_801007F4(lbl_8042C590, 0xC);
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
		fn_80100AAC();
	}
	fn_801007F4(lbl_8042C590, 5);
}

void flyerObjectLoad(void)
{
	M2C_UNK sp8;
	s32 temp_r3;
	u32 var_r0;

	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
		fn_80100AAC();
	}
	fn_8010096C(lbl_8042C590, 5, "en_flyer.one");
	if (fn_800194C4(&lbl_8029C310) != 0U) {
		temp_r3 = sprintf(&sp8, "%s_flyer.one");
		if ((temp_r3 >= 0) && (temp_r3 < 0x40)) {
			if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
				fn_80100AAC();
			}
			fn_8010096C(lbl_8042C590, 0xC, &sp8);
		}
	}
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
		fn_80100AAC();
	}
	if (fn_80100328(lbl_8042C590, 5, 0xD) != 0U) {
		fn_8005E00C(6);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1948, u32*, 0) = fn_8010037C(lbl_8042C590, 5, 0xC);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1948, u32*, 4) = fn_8010037C(lbl_8042C590, 5, 0xF);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1948, u32*, 8) = fn_8010037C(lbl_8042C590, 5, 0xE);
		if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
			fn_80100AAC();
		}
		M2C_FIELD(&lbl_8_bss_1948, u32*, 0xC) = fn_8010037C(lbl_8042C590, 5, 6);
		fn_800FE274(5, &lbl_8_data_16018);
		fn_800FE274(5, &lbl_8_data_16070);
		fn_8_A9E2C();
		fn_8_A8D30();
		var_r0 = fn_80057644(0xC);
		if (var_r0 != 0U) {
			var_r0 = fn_8011FE0C(0xC);
		}
		lbl_8_bss_1958 = var_r0;
	}
}

void flyerObjectCreate(void)
{
	if (fn_80018A34(lbl_8042C148, 0x3C4) != NULL) {
		fn_8_A5F50(lbl_8042C10C);
	}
}

void flyerObjectRegister(void)
{
	const char* temp_r3;

	M2C_FIELD(&flyerObjectEntry, s32*, 0x14)         = 0;
	M2C_FIELD(&flyerObjectEntry, s32*, 0x18)         = 0;
	M2C_FIELD(&flyerObjectEntry, const char**, 0)    = "FLYER OBJECT";
	M2C_FIELD(&flyerObjectEntry, void (**)(), 4)     = flyerObjectLoad;
	M2C_FIELD(&flyerObjectEntry, void (**)(), 8)     = flyerObjectUnload;
	M2C_FIELD(&flyerObjectEntry, void (**)(), 0xC)   = flyerObjectCreate;
	M2C_FIELD(&flyerObjectEntry, s32*, 0x10)         = 0;
	M2C_FIELD(&flyerObjectEntry, s32*, 0x14)         = 0;
	M2C_FIELD(&flyerObjectEntry, s32*, 0x18)         = 0;
	M2C_FIELD(&flyerObjectEntry, s8*, 0x20)          = 0x1E;
	M2C_FIELD(&flyerObjectEntry, s16*, 0x1C)         = 0x1530;
	M2C_FIELD(&flyerObjectEntry, s16*, 0x1E)         = 4;
	M2C_FIELD(&flyerObjectEntry, s8*, 0x21)          = 0;
	temp_r3                                          = "ccccfifxi";
	M2C_FIELD(&flyerObjectEntry, const char**, 0x24) = temp_r3;
	M2C_FIELD(&flyerObjectEntry, M2C_UNK**, 0x28)    = &flyerObjectFieldNames;
	if (temp_r3 != NULL) {
		M2C_FIELD(&flyerObjectEntry, s32*, 0x14) = 8;
		return;
	}
	M2C_FIELD(&flyerObjectEntry, s32*, 0x14) = 0;
}
}
