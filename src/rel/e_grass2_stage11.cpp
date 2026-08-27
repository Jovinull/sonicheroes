#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(u32)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

static M2C_UNK lbl_8_rodata_1F48;

typedef struct TObject {
	/* 0x00 */ M2C_UNK* unk0;   /* inferred */
	/* 0x04 */ char pad4[0x14]; /* maybe part of unk0[6]? */
	/* 0x18 */ M2C_UNK* unk18;  /* inferred */
	/* 0x1C */ char pad1C[2];
	/* 0x1E */ s16 unk1E;     /* inferred */
	/* 0x20 */ char pad20[8]; /* maybe part of unk1E[5]? */
	/* 0x28 */ M2C_UNK unk28; /* inferred */
	/* 0x28 */ char pad28[4];
	/* 0x2C */ void* unk2C;   /* inferred */
	/* 0x30 */ M2C_UNK unk30; /* inferred */
	/* 0x30 */ char pad30[0x88];
	/* 0xB8 */ f32 unkB8; /* inferred */
	/* 0xBC */ f32 unkBC; /* inferred */
	/* 0xC0 */ f32 unkC0; /* inferred */
	/* 0xC4 */ s32 unkC4; /* inferred */
	/* 0xC8 */ s32 unkC8; /* inferred */
	/* 0xCC */ s32 unkCC; /* inferred */
	/* 0xD0 */ f32 unkD0; /* inferred */
	/* 0xD4 */ s32 unkD4; /* inferred */
	/* 0xD8 */ s32 unkD8; /* inferred */
	/* 0xDC */ u32 unkDC; /* inferred */
	/* 0xE0 */ s32 unkE0; /* inferred */
	/* 0xE4 */ s32 unkE4; /* inferred */
	/* 0xE8 */ s32 unkE8; /* inferred */
} TObject;                /* size >= 0xEC */

struct _struct_lbl_8_data_18568_0x10 {
	/* 0x00 */ u32 unk0;       /* inferred */
	/* 0x04 */ char pad4[0xC]; /* maybe part of unk0[4]? */
}; /* size = 0x10 */

struct _struct_lbl_8_data_18588_0x10 {
	/* 0x00 */ u32 unk0;       /* inferred */
	/* 0x04 */ char pad4[0xC]; /* maybe part of unk0[4]? */
}; /* size = 0x10 */

extern "C" {

void* __ct__7TObjectFP7TObject(void*, void*);              /* extern */
void* __dt__7TObjectFv(void*, s32);                        /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                     /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                     /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                        /* extern */
u32 fn_80018A34(s32, M2C_UNK);                             /* extern */
M2C_UNK fn_8003BF04(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                             /* extern */
s32 fn_8005B8BC(s32);                                      /* extern */
s32 fn_8005B8D8(void*);                                    /* extern */
s32 fn_8005B9F0(s32);                                      /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                             /* extern */
M2C_UNK fn_8005D5C8(void*, s32);                           /* extern */
u32 fn_800BB0D4(s32, s32, M2C_UNK*);                       /* extern */
u32 fn_800BB92C(s32, s32, M2C_UNK*);                       /* extern */
s32 fn_800BC6CC(s32, M2C_UNK*);                            /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                        /* extern */
f32 fn_800D7AE4(s32);                                      /* extern */
f32 fn_800D7B00(s32);                                      /* extern */
M2C_UNK fn_8013F3A4(void*);                                /* extern */
void* fn_8013F484(s32);                                    /* extern */
M2C_UNK fn_8013FC30(void*);                                /* extern */
M2C_UNK fn_8014FFBC(void*, void* (*)(void*, s32), void*);  /* extern */
void* fn_80150588(s32, s32);                               /* extern */
M2C_UNK fn_80150958(u32);                                  /* extern */
M2C_UNK fn_8015BB08(s32, void*);                           /* extern */
M2C_UNK fn_8015BBF8(s32);                                  /* extern */
M2C_UNK fn_80195790(s32, M2C_UNK*, M2C_UNK, f32, f32);     /* extern */
M2C_UNK fn_8019E880(s32);                                  /* extern */
M2C_UNK fn_8019EB10(s32, s32 (*)(s32, void**), void**);    /* extern */
M2C_UNK fn_8019EB94(s32, f32*, M2C_UNK);                   /* extern */
M2C_UNK fn_8019EC30(s32, f32*, M2C_UNK);                   /* extern */
M2C_UNK fn_801A4C84();                                     /* extern */
M2C_UNK fn_8020C2D8(u32);                                  /* extern */
M2C_UNK fn_8020C72C(void**, s32, s32);                     /* extern */
M2C_UNK fn_8020CC18(void**, M2C_UNK*, f32);                /* extern */
M2C_UNK fn_8020D02C(void**, ...);                          /* extern */
M2C_UNK fn_80226440(void*, s32);                           /* extern */
u32 fn_80226468(s32);                                      /* extern */
M2C_UNK fn_8_C4BBC(s32);                                   /* extern */
TObject* fn_8_C577C(TObject* arg0, TObject* arg1);         /* static */
void* fn_8_C5B08(void* arg0, s32 arg1);                    /* static */
s32 fn_8_C5BB8(s32 arg0, void** arg1);                     /* static */
void grass2ObjectCreate();                                 /* static */
void grass2ObjectLoad(M2C_UNK arg_sp0);                    /* static */
void grass2ObjectUnload(M2C_UNK arg_sp0);                  /* static */
extern M2C_UNK grass2ObjectEntry;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_802FF5A0;
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern M2C_UNK* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern M2C_UNK lbl_8_data_183A8;
extern M2C_UNK lbl_8_data_183C0;
extern M2C_UNK lbl_8_data_183D8;
extern M2C_UNK lbl_8_data_183F0;
extern M2C_UNK lbl_8_data_18408;
extern M2C_UNK lbl_8_data_18420;
extern M2C_UNK lbl_8_data_18438;
extern M2C_UNK lbl_8_data_18450;
static M2C_UNK* lbl_8_data_18468[8] = {
	&lbl_8_data_183A8,
	&lbl_8_data_183C0,
	&lbl_8_data_183D8,
	&lbl_8_data_183F0,
	&lbl_8_data_18408,
	&lbl_8_data_18420,
	&lbl_8_data_18438,
	&lbl_8_data_18450,
};
static M2C_UNK lbl_8_data_18488;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001849D_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_184A0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000184B5_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_184B8;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000184CD_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_184D0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000184E5_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_184E8;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000184FD_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18500;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018515_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18518;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001852D_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18530;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018545_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_18548[8] = {
	&lbl_8_data_18488,
	&lbl_8_data_184A0,
	&lbl_8_data_184B8,
	&lbl_8_data_184D0,
	&lbl_8_data_184E8,
	&lbl_8_data_18500,
	&lbl_8_data_18518,
	&lbl_8_data_18530,
};
static struct _struct_lbl_8_data_18568_0x10 lbl_8_data_18568[2] = { { 0U }, { 0U } };
static struct _struct_lbl_8_data_18588_0x10 lbl_8_data_18588[2] = { { 0U }, { 0U } };
static M2C_UNK lbl_8_data_185A8;       /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000185BA_data;   /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_185BC;       /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000185CB_data;   /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_185CC;       /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000185DB_data;   /* unable to generate initializer: unknown type */
static M2C_UNK grass2ObjectFieldNames; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_185E8;       /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000185F9_data;   /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_185FC[2] = { &lbl_8_data_185A8, &lbl_8_data_185E8 };
static M2C_UNK lbl_8_data_18604;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018615_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_18618[2] = { &lbl_8_data_185BC, &lbl_8_data_18604 };
static M2C_UNK lbl_8_data_18620;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18650;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001865B_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_1865C = &lbl_8_data_18650;
static M2C_UNK lbl_8_data_18660;        /* unable to generate initializer: unknown type */
static M2C_UNK grass2ObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000186AA_data;    /* unable to generate initializer: unknown type */
static M2C_UNK grass2ObjectFieldTypes;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_186B0;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_186C4;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_186D8;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_186EC;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18700;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18714;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18728;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1873C;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18750;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18764;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_rodata_1F58;       /* unable to generate initializer: unknown type; const */

void fn_8_C4E94(s32 arg0)
{
	fn_8_C4BBC(arg0 - 0x28);
}

void fn_8_C4E9C(void* arg0)
{
	s32 var_r28;
	void* var_r29;

	var_r28 = 0;
	var_r29 = arg0;
	do {
		if ((u32)M2C_FIELD(var_r29, u32*, 0xDC) != 0U) {
			fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284));
			fn_80150958(M2C_FIELD(var_r29, u32*, 0xDC));
			M2C_FIELD(var_r29, u32*, 0xDC) = 0U;
		}
		var_r29 = (u8*)var_r29 + 4;
		var_r28 += 1;
	} while (var_r28 < 4);
}

void fn_8_C4F20(void* arg0, M2C_UNK arg_sp0)
{
	void* sp8;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 var_r29;
	s32 var_r30;
	void* temp_r27;
	void* temp_r3;
	void* temp_r3_2;
	void* var_r31;

	var_r29 = 0;
	var_r31 = arg0;
	var_r30 = 0;
	do {
		if ((void*)M2C_FIELD(var_r31, void**, 0xDC) == NULL) {
			temp_r0                          = M2C_FIELD(arg0, s32*, 0xD8);
			M2C_FIELD(var_r31, void**, 0xDC) = fn_80150588(
			    M2C_FIELD(&lbl_8_data_18568[temp_r0 + var_r30], s32*, 0), temp_r0 * 0x10);
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284), M2C_FIELD(var_r31, void**, 0xDC));
			fn_8005D5C8(M2C_FIELD(var_r31, void**, 0xDC),
			    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
			        + 4);
			temp_r27 = M2C_FIELD(var_r31, void**, 0xDC);
			sp8      = NULL;
			temp_r3  = fn_8013F484(M2C_FIELD(temp_r27, s32*, 4));
			sp8      = temp_r3;
			if (temp_r3 == NULL) {
				fn_8019EB10(M2C_FIELD(temp_r27, s32*, 4), fn_8_C5BB8, &sp8);
			}
			M2C_FIELD(var_r31, void**, 0xEC) = sp8;
			fn_8014FFBC(
			    M2C_FIELD(var_r31, void**, 0xDC), fn_8_C5B08, M2C_FIELD(var_r31, void**, 0xEC));
			temp_r3_2                     = M2C_FIELD(var_r31, void**, 0xEC);
			M2C_FIELD(temp_r3_2, s32*, 0) = (s32)(M2C_FIELD(temp_r3_2, s32*, 0) | 0x3000);
			temp_r0_2                     = M2C_FIELD(arg0, s32*, 0xD8);
			fn_8020C72C(M2C_FIELD(M2C_FIELD(var_r31, void**, 0xEC), void***, 0x20),
			    M2C_FIELD(&lbl_8_data_18588[temp_r0_2 + var_r30], s32*, 0), temp_r0_2 * 0x10);
			fn_8013F3A4(M2C_FIELD(var_r31, void**, 0xEC));
			fn_8013FC30(M2C_FIELD(var_r31, void**, 0xEC));
			fn_8020D02C(M2C_FIELD(M2C_FIELD(var_r31, void**, 0xEC), void***, 0x20),
			    &lbl_8_rodata_1F48, 0.0f);
			fn_8020CC18(M2C_FIELD(M2C_FIELD(var_r31, void**, 0xEC), void***, 0x20),
			    &lbl_8_rodata_1F48, 0.0f);
		}
		var_r31 = (u8*)var_r31 + 4;
		var_r30 += 4;
		var_r29 += 1;
	} while (var_r29 < 4);
}

void fn_8_C5094(void* arg0)
{
	void* temp_r4;
	void* temp_r4_2;
	void* temp_r5;

	temp_r4                     = M2C_FIELD(arg0, void**, 0x28);
	temp_r5                     = M2C_FIELD(temp_r4, void**, 0x2C);
	M2C_FIELD(arg0, f32*, 0xB8) = (f32)M2C_FIELD(temp_r4, f32*, 0);
	M2C_FIELD(arg0, f32*, 0xBC) = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0xC0) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	temp_r4_2                   = M2C_FIELD(arg0, void**, 0x28);
	M2C_FIELD(arg0, s32*, 0xC4) = (s32)M2C_FIELD(temp_r4_2, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0xC8) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0xCC) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x14);
	M2C_FIELD(arg0, s32*, 0xCC) = 0;
	M2C_FIELD(arg0, s32*, 0xC4) = 0;
	M2C_FIELD(arg0, s32*, 0xD4) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 1);
	M2C_FIELD(arg0, s32*, 0xD8) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 0);
	M2C_FIELD(arg0, f32*, 0xD0) = (f32)(1.0f + M2C_FIELD(temp_r5, f32*, 4));
}

void fn_8_C5110(void* arg0)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	void* sp8;
	f32 temp_f0;
	f32 temp_f2;
	f32 temp_f31;
	f32 temp_f31_2;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r30;
	s32 temp_r5;
	s32 var_r29;
	s32 var_r29_2;
	s32 var_r31;
	s32 var_r31_2;
	s32 var_r31_3;
	void** temp_r3;
	void* temp_r27;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;
	void* temp_r4;
	void* var_r27;
	void* var_r27_2;
	void* var_r27_3;
	void* var_r30;

	if ((fn_8005B9F0((s32)((u8*)arg0 + 0x28)) != 0)
	    || (fn_8005B8BC((s32)((u8*)arg0 + 0x28)) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	var_r29 = 0;
	var_r27 = arg0;
	do {
		temp_r3 = M2C_FIELD(M2C_FIELD(var_r27, void**, 0xEC), void***, 0x20);
		temp_f2 = 60.0f * M2C_FIELD(*temp_r3, f32*, 0xC);
		temp_r0 = M2C_FIELD(lbl_8042C180, s32*, 0x30);
		fn_8020D02C(temp_r3, lbl_8042C180,
		    ((f32)temp_r0 - (temp_f2 * (f32)(s32)((f32)temp_r0 / temp_f2))) / 60.0f, temp_f2);
		fn_8013FC30(M2C_FIELD(var_r27, void**, 0xEC));
		var_r27 = (u8*)var_r27 + 4;
		var_r29 += 1;
	} while (var_r29 < 4);
	if (fn_8005B8D8((M2C_UNK*)((u8*)arg0 + 0x28)) != 0) {
		temp_r5                     = M2C_FIELD(arg0, s32*, 0xD8);
		temp_r3_2                   = M2C_FIELD(arg0, void**, 0x28);
		temp_r4                     = M2C_FIELD(temp_r3_2, void**, 0x2C);
		M2C_FIELD(arg0, f32*, 0xB8) = (f32)M2C_FIELD(temp_r3_2, f32*, 0);
		M2C_FIELD(arg0, f32*, 0xBC) = (f32)M2C_FIELD(temp_r3_2, f32*, 4);
		M2C_FIELD(arg0, f32*, 0xC0) = (f32)M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3_3                   = M2C_FIELD(arg0, void**, 0x28);
		M2C_FIELD(arg0, s32*, 0xC4) = (s32)M2C_FIELD(temp_r3_3, s32*, 0xC);
		M2C_FIELD(arg0, s32*, 0xC8) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x10);
		M2C_FIELD(arg0, s32*, 0xCC) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x14);
		M2C_FIELD(arg0, s32*, 0xCC) = 0;
		M2C_FIELD(arg0, s32*, 0xC4) = 0;
		M2C_FIELD(arg0, s32*, 0xD4) = (s32)(s8)M2C_FIELD(temp_r4, u8*, 1);
		M2C_FIELD(arg0, s32*, 0xD8) = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0);
		M2C_FIELD(arg0, f32*, 0xD0) = (f32)(1.0f + M2C_FIELD(temp_r4, f32*, 4));
		if ((s32)M2C_FIELD(arg0, s32*, 0xD8) != temp_r5) {
			var_r31   = 0;
			var_r27_2 = arg0;
			do {
				if ((u32)M2C_FIELD(var_r27_2, u32*, 0xDC) != 0U) {
					fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284));
					fn_80150958(M2C_FIELD(var_r27_2, u32*, 0xDC));
					M2C_FIELD(var_r27_2, u32*, 0xDC) = 0U;
				}
				var_r27_2 = (u8*)var_r27_2 + 4;
				var_r31 += 1;
			} while (var_r31 < 4);
			var_r31_2 = 0;
			var_r30   = arg0;
			var_r29_2 = 0;
			do {
				if ((void*)M2C_FIELD(var_r30, void**, 0xDC) == NULL) {
					temp_r0_2 = M2C_FIELD(arg0, s32*, 0xD8);
					M2C_FIELD(var_r30, void**, 0xDC)
					    = fn_80150588(M2C_FIELD(&lbl_8_data_18568[temp_r0_2 + var_r29_2], s32*, 0),
					        temp_r0_2 * 0x10);
					fn_8015BB08(
					    M2C_FIELD(lbl_8042C1D0, s32*, 0x7284), M2C_FIELD(var_r30, void**, 0xDC));
					fn_8005D5C8(M2C_FIELD(var_r30, void**, 0xDC),
					    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000)
					        >> 0x12U)
					        + 4);
					temp_r27  = M2C_FIELD(var_r30, void**, 0xDC);
					sp8       = NULL;
					temp_r3_4 = fn_8013F484(M2C_FIELD(temp_r27, s32*, 4));
					sp8       = temp_r3_4;
					if (temp_r3_4 == NULL) {
						fn_8019EB10(M2C_FIELD(temp_r27, s32*, 4), fn_8_C5BB8, &sp8);
					}
					M2C_FIELD(var_r30, void**, 0xEC) = sp8;
					fn_8014FFBC(M2C_FIELD(var_r30, void**, 0xDC), fn_8_C5B08,
					    M2C_FIELD(var_r30, void**, 0xEC));
					temp_r3_5                     = M2C_FIELD(var_r30, void**, 0xEC);
					M2C_FIELD(temp_r3_5, s32*, 0) = (s32)(M2C_FIELD(temp_r3_5, s32*, 0) | 0x3000);
					temp_r0_3                     = M2C_FIELD(arg0, s32*, 0xD8);
					fn_8020C72C(M2C_FIELD(M2C_FIELD(var_r30, void**, 0xEC), void***, 0x20),
					    M2C_FIELD(&lbl_8_data_18588[temp_r0_3 + var_r29_2], s32*, 0),
					    temp_r0_3 * 0x10);
					fn_8013F3A4(M2C_FIELD(var_r30, void**, 0xEC));
					fn_8013FC30(M2C_FIELD(var_r30, void**, 0xEC));
					fn_8020D02C(M2C_FIELD(M2C_FIELD(var_r30, void**, 0xEC), void***, 0x20),
					    &lbl_8_rodata_1F48, 0.0f);
					fn_8020CC18(M2C_FIELD(M2C_FIELD(var_r30, void**, 0xEC), void***, 0x20),
					    &lbl_8_rodata_1F48, 0.0f);
				}
				var_r30 = (u8*)var_r30 + 4;
				var_r29_2 += 4;
				var_r31_2 += 1;
			} while (var_r31_2 < 4);
		}
		temp_f0   = M2C_FIELD(arg0, f32*, 0xD0);
		sp14      = temp_f0;
		sp10      = temp_f0;
		spC       = temp_f0;
		var_r31_3 = 0;
		var_r27_3 = arg0;
		do {
			temp_r30 = M2C_FIELD(M2C_FIELD(var_r27_3, void**, 0xDC), s32*, 4);
			fn_8019EB94(temp_r30, (f32*)((u8*)arg0 + 0xB8), 0);
			temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
			fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1,
			    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f31);
			fn_8019E880(temp_r30);
			if ((s32)M2C_FIELD(arg0, s32*, 0xD4) == 1) {
				temp_f31_2 = fn_800D7B00(0x8000);
				fn_80195790(
				    temp_r30 + 0x10, &lbl_80239990, 1, 1.0f - fn_800D7AE4(0x8000), temp_f31_2);
				fn_8019E880(temp_r30);
			}
			fn_8019EC30(temp_r30, &spC, 1);
			var_r27_3 = (u8*)var_r27_3 + 4;
			var_r31_3 += 1;
		} while (var_r31_3 < 4);
	}
}

void fn_8_C555C(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	s32 temp_r28;
	s32 var_r29;
	void* var_r30;

	temp_f0 = M2C_FIELD(arg0, f32*, 0xD0);
	sp10    = temp_f0;
	spC     = temp_f0;
	sp8     = temp_f0;
	var_r29 = 0;
	var_r30 = arg0;
	do {
		temp_r28 = M2C_FIELD(M2C_FIELD(var_r30, void**, 0xDC), s32*, 4);
		fn_8019EB94(temp_r28, (f32*)((u8*)arg0 + 0xB8), 0);
		temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
		fn_80195790(temp_r28 + 0x10, &lbl_80239984, 1,
		    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f31);
		fn_8019E880(temp_r28);
		if ((s32)M2C_FIELD(arg0, s32*, 0xD4) == 1) {
			temp_f31_2 = fn_800D7B00(0x8000);
			fn_80195790(temp_r28 + 0x10, &lbl_80239990, 1, 1.0f - fn_800D7AE4(0x8000), temp_f31_2);
			fn_8019E880(temp_r28);
		}
		fn_8019EC30(temp_r28, &sp8, 1);
		var_r30 = (u8*)var_r30 + 4;
		var_r29 += 1;
	} while (var_r29 < 4);
}

TObject* fn_8_C569C(TObject* arg0, s16 arg1, M2C_UNK arg_sp0)
{
	TObject* var_r28;
	s32 var_r29;

	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_18660;
		arg0->unk2C = &lbl_8_data_18660 + 0x2C;
		var_r29     = 0;
		var_r28     = arg0;
		do {
			if ((u32)var_r28->unkDC != 0U) {
				fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284));
				fn_80150958(var_r28->unkDC);
				var_r28->unkDC = 0U;
			}
			var_r28 += 4;
			var_r29 += 1;
		} while (var_r29 < 4);
		dtor_8003C52C((void*)((u8*)arg0 + 0x30), 0);
		dtor_8005BD3C((void*)((u8*)arg0 + 0x28), 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_C577C(TObject* arg0, TObject* arg1)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	void* sp8;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	s32* temp_r4_2;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r31;
	s32 temp_r3_4;
	s32 var_r27;
	s32 var_r28;
	s32 var_r30;
	s32 var_r31;
	void* temp_r28;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r4;
	void* temp_r5;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	fn_8003C618(&arg0->unk30);
	arg0->unk18 = &lbl_8_data_18660;
	arg0->unk2C = &lbl_8_data_18660 + 0x2C;
	arg0->unk0  = lbl_8_data_1865C;
	arg0->unk1E = 0xFC;
	temp_r3     = M2C_FIELD(arg0, void**, 0x28);
	temp_r4     = M2C_FIELD(temp_r3, void**, 0x2C);
	arg0->unkB8 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unkBC = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unkC0 = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2   = M2C_FIELD(arg0, void**, 0x28);
	arg0->unkC4 = M2C_FIELD(temp_r3_2, s32*, 0xC);
	arg0->unkC8 = M2C_FIELD(temp_r3_2, s32*, 0x10);
	arg0->unkCC = M2C_FIELD(temp_r3_2, s32*, 0x14);
	var_r31     = 0;
	arg0->unkCC = 0;
	arg0->unkC4 = 0;
	arg0->unkD4 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 1);
	arg0->unkD8 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0);
	arg0->unkD0 = 1.0f + M2C_FIELD(temp_r4, f32*, 4);
	arg0->unkDC = 0U;
	arg0->unkE0 = 0;
	arg0->unkE4 = 0;
	arg0->unkE8 = 0;
	var_r30     = 0;
	do {
		if ((u32)M2C_FIELD(arg0, void**, var_r30 + 0xDC) == 0U) {
			temp_r0                        = arg0->unkD8;
			temp_r0_2                      = var_r30 + 0xDC;
			*(u32*)((u8*)arg0 + temp_r0_2) = (u32)fn_80150588(
			    M2C_FIELD(&lbl_8_data_18568[temp_r0 + var_r30], s32*, 0), temp_r0 * 0x10);
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284), M2C_FIELD(arg0, void**, temp_r0_2));
			fn_8005D5C8(M2C_FIELD(arg0, void**, var_r30 + 0xDC),
			    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
			        + 4);
			temp_r28  = M2C_FIELD(arg0, void**, var_r30 + 0xDC);
			sp8       = NULL;
			temp_r3_3 = fn_8013F484(M2C_FIELD(temp_r28, s32*, 4));
			sp8       = temp_r3_3;
			if (temp_r3_3 == NULL) {
				fn_8019EB10(M2C_FIELD(temp_r28, s32*, 4), fn_8_C5BB8, &sp8);
			}
			M2C_FIELD(arg0, void**, var_r30 + 0xEC) = sp8;
			temp_r5                                 = (u8*)arg0 + var_r30;
			fn_8014FFBC(
			    M2C_FIELD(temp_r5, void**, 0xDC), fn_8_C5B08, M2C_FIELD(temp_r5, void**, 0xEC));
			temp_r3_4 = var_r30 + 0xEC;
			temp_r4_2 = M2C_FIELD(arg0, s32**, temp_r3_4);
			*temp_r4_2 |= 0x3000;
			temp_r0_3 = arg0->unkD8;
			fn_8020C72C(M2C_FIELD(*(u32*)((u8*)arg0 + temp_r3_4), void***, 0x20),
			    M2C_FIELD(&lbl_8_data_18588[temp_r0_3 + var_r30], s32*, 0), temp_r0_3 * 0x10);
			fn_8013F3A4(M2C_FIELD(arg0, void**, var_r30 + 0xEC));
			fn_8013FC30(M2C_FIELD(arg0, void**, var_r30 + 0xEC));
			fn_8020D02C(M2C_FIELD(*(u32*)((u8*)arg0 + var_r30 + 0xEC), void***, 0x20),
			    &lbl_8_rodata_1F48, 0.0f);
			fn_8020CC18(M2C_FIELD(M2C_FIELD(arg0, void**, var_r30 + 0xEC), void***, 0x20),
			    &lbl_8_rodata_1F48, 0.0f);
		}
		var_r30 += 4;
		var_r31 += 1;
	} while (var_r31 < 4);
	temp_f0 = arg0->unkD0;
	sp14    = temp_f0;
	sp10    = temp_f0;
	spC     = temp_f0;
	var_r28 = 0;
	var_r27 = 0;
	do {
		temp_r31 = M2C_FIELD(M2C_FIELD(arg0, void**, var_r27 + 0xDC), s32*, 4);
		fn_8019EB94(temp_r31, &arg0->unkB8, 0);
		temp_f31 = fn_800D7B00(arg0->unkC8);
		fn_80195790(temp_r31 + 0x10, &lbl_80239984, 1, 1.0f - fn_800D7AE4(arg0->unkC8), temp_f31);
		fn_8019E880(temp_r31);
		if ((s32)arg0->unkD4 == 1) {
			temp_f31_2 = fn_800D7B00(0x8000);
			fn_80195790(temp_r31 + 0x10, &lbl_80239990, 1, 1.0f - fn_800D7AE4(0x8000), temp_f31_2);
			fn_8019E880(temp_r31);
		}
		fn_8019EC30(temp_r31, &spC, 1);
		var_r27 += 4;
		var_r28 += 1;
	} while (var_r28 < 4);
	fn_8003BF04(&arg0->unk30, &lbl_8_data_18620, 1, 4);
	return arg0;
}

void* fn_8_C5B08(void* arg0, s32 arg1)
{
	if (fn_80226468(M2C_FIELD(arg0, s32*, 0x18)) != 0U) {
		fn_80226440(arg0, arg1);
	}
	return arg0;
}

void* fn_8_C5B5C(void* arg0)
{
	void* sp8;
	void* temp_r3;

	sp8     = NULL;
	temp_r3 = fn_8013F484(M2C_FIELD(arg0, s32*, 4));
	sp8     = temp_r3;
	if (temp_r3 == NULL) {
		fn_8019EB10(M2C_FIELD(arg0, s32*, 4), fn_8_C5BB8, &sp8);
	}
	return sp8;
}

s32 fn_8_C5BB8(s32 arg0, void** arg1)
{
	void* temp_r3;

	temp_r3 = fn_8013F484(arg0);
	if (temp_r3 == NULL) {
		fn_8019EB10(arg0, fn_8_C5BB8, arg1);
		return arg0;
	}
	*arg1 = temp_r3;
	return 0;
}

void fn_8_C5C1C(void* arg1)
{
	void* temp_r5;

	temp_r5 = M2C_FIELD(arg1, void**, 0x2C);
	if ((s8)M2C_FIELD(temp_r5, u8*, 0) < 0) {
		M2C_FIELD(temp_r5, u8*, 0) = 0U;
	}
	if ((s8)M2C_FIELD(temp_r5, u8*, 0) > 1) {
		M2C_FIELD(temp_r5, u8*, 0) = 1U;
	}
	if ((s8)M2C_FIELD(temp_r5, u8*, 1) < 0) {
		M2C_FIELD(temp_r5, u8*, 1) = 0U;
	}
	if ((s8)M2C_FIELD(temp_r5, u8*, 1) > 1) {
		M2C_FIELD(temp_r5, u8*, 1) = 1U;
	}
	M2C_FIELD(&grass2ObjectFieldNames, M2C_UNK**, 0)
	    = (M2C_UNK*)lbl_8_data_185FC[(s8)M2C_FIELD(temp_r5, u8*, 0)];
	M2C_FIELD(&grass2ObjectFieldNames, M2C_UNK**, 4)
	    = (M2C_UNK*)lbl_8_data_18618[(s8)M2C_FIELD(temp_r5, u8*, 1)];
}

void grass2ObjectUnload(M2C_UNK arg_sp0)
{
	s32 var_r26;
	s32 var_r27;
	s32 var_r27_2;
	struct _struct_lbl_8_data_18568_0x10* var_r29;
	struct _struct_lbl_8_data_18568_0x10* var_r30;
	struct _struct_lbl_8_data_18588_0x10* var_r28;
	struct _struct_lbl_8_data_18588_0x10* var_r30_2;

	var_r26 = 0;
	var_r29 = lbl_8_data_18568;
	var_r28 = lbl_8_data_18588;
	do {
		var_r27 = 0;
		var_r30 = var_r29;
	loop_2:
		if ((u32)var_r30->unk0 != 0U) {
			fn_80150958(var_r30->unk0);
			var_r30->unk0 = 0U;
		}
		var_r30 += 4;
		var_r27 += 1;
		if (var_r27 < 4) {
			goto loop_2;
		}
		var_r27_2 = 0;
		var_r30_2 = var_r28;
	loop_6:
		if ((u32)var_r30_2->unk0 != 0U) {
			fn_8020C2D8(var_r30_2->unk0);
			var_r30_2->unk0 = 0U;
		}
		var_r30_2 += 4;
		var_r27_2 += 1;
		if (var_r27_2 < 4) {
			goto loop_6;
		}
		var_r29 += 0x10;
		var_r28 += 0x10;
		var_r26 += 1;
	} while (var_r26 < 2);
}

void grass2ObjectLoad(M2C_UNK arg_sp0)
{
	M2C_UNK** var_r24;
	M2C_UNK** var_r26;
	M2C_UNK** var_r27_2;
	M2C_UNK** var_r28;
	s32 temp_r30;
	s32 var_r22;
	s32 var_r22_2;
	s32 var_r31;
	struct _struct_lbl_8_data_18568_0x10* var_r25;
	struct _struct_lbl_8_data_18568_0x10* var_r27;
	struct _struct_lbl_8_data_18588_0x10* var_r23;
	struct _struct_lbl_8_data_18588_0x10* var_r28_2;

	if ((u32)M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18) != 0U) {
		fn_801A4C84();
		temp_r30 = M2C_FIELD(lbl_8042C298, s32*, 0xA50);
		fn_800BC9F4(temp_r30, &lbl_802FF5A0);
		var_r31 = 0;
		var_r26 = lbl_8_data_18548;
		var_r25 = lbl_8_data_18568;
		var_r24 = lbl_8_data_18468;
		var_r23 = lbl_8_data_18588;
		do {
			var_r22 = 0;
			var_r28 = var_r26;
			var_r27 = var_r25;
		loop_5:
			var_r27->unk0 = fn_800BB92C(temp_r30, fn_800BC6CC(temp_r30, *var_r28), &lbl_802FF5A0);
			var_r28 += 4;
			var_r27 += 4;
			var_r22 += 1;
			if (var_r22 < 4) {
				goto loop_5;
			}
			var_r22_2 = 0;
			var_r27_2 = var_r24;
			var_r28_2 = var_r23;
		loop_7:
			var_r28_2->unk0
			    = fn_800BB0D4(temp_r30, fn_800BC6CC(temp_r30, *var_r27_2), &lbl_802FF5A0);
			var_r27_2 += 4;
			var_r28_2 += 4;
			var_r22_2 += 1;
			if (var_r22_2 < 4) {
				goto loop_7;
			}
			var_r26 += 0x10;
			var_r25 += 0x10;
			var_r24 += 0x10;
			var_r23 += 0x10;
			var_r31 += 1;
		} while (var_r31 < 2);
	}
}

void grass2ObjectCreate(void)
{
	TObject* object = (TObject*)fn_80018A34(lbl_8042C148, 0xFC);
	if (object != NULL) {
		fn_8_C577C(object, lbl_8042C110);
	}
}

void grass2ObjectRegister(void)
{
	s32 flags;

	M2C_FIELD(&grass2ObjectEntry, s32*, 0x14)            = 0;
	M2C_FIELD(&grass2ObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&grass2ObjectEntry, M2C_UNK**, 0)          = &grass2ObjectDisplayName;
	M2C_FIELD(&grass2ObjectEntry, void (**)(M2C_UNK), 4) = grass2ObjectLoad;
	M2C_FIELD(&grass2ObjectEntry, void (**)(M2C_UNK), 8) = grass2ObjectUnload;
	M2C_FIELD(&grass2ObjectEntry, void (**)(), 0xC)      = grass2ObjectCreate;
	M2C_FIELD(&grass2ObjectEntry, s32*, 0x10)            = 0;
	flags                                                = 0x20000;
	M2C_FIELD(&grass2ObjectEntry, s32*, 0x14)            = flags;
	M2C_FIELD(&grass2ObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&grass2ObjectEntry, s8*, 0x20)             = 0x1E;
	M2C_FIELD(&grass2ObjectEntry, s16*, 0x1C)            = 0x118C;
	M2C_FIELD(&grass2ObjectEntry, s16*, 0x1E)            = 2;
	M2C_FIELD(&grass2ObjectEntry, s8*, 0x21)             = 0;
	M2C_FIELD(&grass2ObjectEntry, M2C_UNK**, 0x24)       = &grass2ObjectFieldTypes;
	M2C_FIELD(&grass2ObjectEntry, M2C_UNK**, 0x28)       = &grass2ObjectFieldNames;
	if (&grass2ObjectFieldTypes != NULL) {
		M2C_FIELD(&grass2ObjectEntry, s32*, 0x14) = flags | 8;
		return;
	}
	M2C_FIELD(&grass2ObjectEntry, s32*, 0x14) = flags & ~8;
}

__declspec(section ".ctors") void (*const grass2ObjectCtorEntry)(void) = grass2ObjectRegister;
}
