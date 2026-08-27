#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(u32)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

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
	/* 0xB8 */ f32 unkB8;   /* inferred */
	/* 0xBC */ f32 unkBC;   /* inferred */
	/* 0xC0 */ f32 unkC0;   /* inferred */
	/* 0xC4 */ s32 unkC4;   /* inferred */
	/* 0xC8 */ s32 unkC8;   /* inferred */
	/* 0xCC */ s32 unkCC;   /* inferred */
	/* 0xD0 */ f32 unkD0;   /* inferred */
	/* 0xD4 */ f32 unkD4;   /* inferred */
	/* 0xD8 */ s32 unkD8;   /* inferred */
	/* 0xDC */ s32 unkDC;   /* inferred */
	/* 0xE0 */ void* unkE0; /* inferred */
	/* 0xE4 */ void* unkE4; /* inferred */
} TObject;                  /* size >= 0xE8 */

extern "C" {

void* __ct__7TObjectFP7TObject(void*, void*);                       /* extern */
void* __dt__7TObjectFv(void*, s32);                                 /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                              /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                              /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                                 /* extern */
u32 fn_80018A34(s32, M2C_UNK);                                      /* extern */
M2C_UNK fn_80021384(void*, void*, M2C_UNK*, f32);                   /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                                      /* extern */
s32 fn_8005B8BC(void*);                                             /* extern */
s32 fn_8005B8D8(void*);                                             /* extern */
s32 fn_8005B9F0(void*);                                             /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                                      /* extern */
M2C_UNK fn_8005D5C8(void*, s32);                                    /* extern */
M2C_UNK fn_800B4A38(M2C_UNK, void*, M2C_UNK, M2C_UNK, s8, M2C_UNK); /* extern */
u32 fn_800BB0D4(s32, s32, M2C_UNK*);                                /* extern */
u32 fn_800BB92C(s32, s32, M2C_UNK*);                                /* extern */
s32 fn_800BC6CC(s32, M2C_UNK*);                                     /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                                 /* extern */
f32 fn_800D7AE4(s32);                                               /* extern */
f32 fn_800D7B00(s32);                                               /* extern */
M2C_UNK fn_8013F3A4(void*);                                         /* extern */
void* fn_8013F484(s32);                                             /* extern */
M2C_UNK fn_8013FC30(void*);                                         /* extern */
M2C_UNK fn_8014FFBC(void*, void* (*)(void*, s32), void*);           /* extern */
void* fn_80150588(u32);                                             /* extern */
M2C_UNK fn_80150958(void*);                                         /* extern */
M2C_UNK fn_8015BB08(s32);                                           /* extern */
M2C_UNK fn_8015BBF8(s32);                                           /* extern */
M2C_UNK fn_80195790(s32, M2C_UNK*, M2C_UNK, f32, f32);              /* extern */
M2C_UNK fn_8019E880(s32);                                           /* extern */
M2C_UNK fn_8019EB10(s32, s32 (*)(s32, void**), void**);             /* extern */
M2C_UNK fn_8019EB94(s32, f32*, M2C_UNK);                            /* extern */
M2C_UNK fn_8019EC30(s32, f32*, M2C_UNK);                            /* extern */
M2C_UNK fn_801A4C84();                                              /* extern */
M2C_UNK fn_8020C2D8(u32);                                           /* extern */
M2C_UNK fn_8020C72C(void**, u32);                                   /* extern */
M2C_UNK fn_8020CC18(void**, f32*, f32);                             /* extern */
M2C_UNK fn_8020D02C(void**, ...);                                   /* extern */
M2C_UNK fn_80226440(void*, s32);                                    /* extern */
u32 fn_80226468(s32);                                               /* extern */
M2C_UNK fn_8_C8C34(s32);                                            /* extern */
TObject* fn_8_C9A7C(TObject* arg0, TObject* arg1);                  /* static */
void* fn_8_C9DCC(void* arg0, s32 arg1);                             /* static */
s32 fn_8_C9E7C(s32 arg0, void** arg1);                              /* static */
void maskObjectCreate();                                            /* static */
void maskObjectLoad();                                              /* static */
void maskObjectUnload();                                            /* static */
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_802FF5A0;
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u32 lbl_8042C388;
extern f32 lbl_8_rodata_1F98;
extern f32 lbl_8_rodata_1F9C;
extern f32 lbl_8_rodata_1FA0;
extern f64 lbl_8_rodata_1FA8;
static u8 lbl_8_data_18C88 = 0x20;
static M2C_UNK gap_04_00018C89_data; /* unable to generate initializer: unknown type */
static u32 lbl_8_data_18C8C[2] = { 0U, 0U };
static u32 lbl_8_data_18C94[2] = { 0U, 0U };
static M2C_UNK lbl_8_data_18C9C;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018CA1_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18CA4;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018CB3_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18CB4;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018CCD_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18CD0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018CDF_data; /* unable to generate initializer: unknown type */
static M2C_UNK maskObjectFieldNames; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18CF0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018D01_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18D04[2] = { "direction : up", "direction : down" };
static M2C_UNK lbl_8_data_18D0C;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18D3C;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018D45_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18D48 = "TObjMask";
static M2C_UNK lbl_8_data_18D4C;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18D88;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018D99_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18D9C;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018DAD_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18DB0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018DC1_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18DC4;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018DD5_data; /* unable to generate initializer: unknown type */
static const char maskObjectDisplayName[] = "MASK OBJECT";
static const char maskObjectFieldTypes[]  = "iFFc";
static M2C_UNK gap_04_00018DEC_data; /* unable to generate initializer: unknown type */
static M2C_UNK maskObjectEntry;
static M2C_UNK lbl_8_bss_1D48;
static M2C_UNK lbl_8_rodata_20F0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_2104; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_2108; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_2110; /* unable to generate initializer: unknown type; const */

void fn_8_C907C(s32 arg0)
{
	fn_8_C8C34(arg0 - 0x28);
}

void fn_8_C9084(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0xE0) != NULL) {
		fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
		fn_80150958(M2C_FIELD(arg0, void**, 0xE0));
		M2C_FIELD(arg0, void**, 0xE0) = NULL;
	}
}

void fn_8_C90DC(void* arg0)
{
	void* sp8;
	void* temp_r30;
	void* temp_r3;
	void* temp_r3_2;

	if ((void*)M2C_FIELD(arg0, void**, 0xE0) == NULL) {
		M2C_FIELD(arg0, void**, 0xE0) = fn_80150588(lbl_8_data_18C8C[M2C_FIELD(arg0, s32*, 0xDC)]);
		if ((void*)M2C_FIELD(arg0, void**, 0xE0) != NULL) {
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
			fn_8005D5C8(M2C_FIELD(arg0, void**, 0xE0),
			    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
			        + 4);
			temp_r30 = M2C_FIELD(arg0, void**, 0xE0);
			sp8      = NULL;
			temp_r3  = fn_8013F484(M2C_FIELD(temp_r30, s32*, 4));
			sp8      = temp_r3;
			if (temp_r3 == NULL) {
				fn_8019EB10(M2C_FIELD(temp_r30, s32*, 4), fn_8_C9E7C, &sp8);
			}
			M2C_FIELD(arg0, void**, 0xE4) = sp8;
			fn_8014FFBC(M2C_FIELD(arg0, void**, 0xE0), fn_8_C9DCC, M2C_FIELD(arg0, void**, 0xE4));
			temp_r3_2                     = M2C_FIELD(arg0, void**, 0xE4);
			M2C_FIELD(temp_r3_2, s32*, 0) = (s32)(M2C_FIELD(temp_r3_2, s32*, 0) | 0x3000);
			fn_8020C72C(M2C_FIELD(M2C_FIELD(arg0, void**, 0xE4), void***, 0x20),
			    lbl_8_data_18C94[M2C_FIELD(arg0, s32*, 0xDC)]);
			fn_8013F3A4(M2C_FIELD(arg0, void**, 0xE4));
			fn_8013FC30(M2C_FIELD(arg0, void**, 0xE4));
			fn_8020D02C(M2C_FIELD(M2C_FIELD(arg0, void**, 0xE4), void***, 0x20), &lbl_8_rodata_1F98,
			    lbl_8_rodata_1F98);
			fn_8020CC18(M2C_FIELD(M2C_FIELD(arg0, void**, 0xE4), void***, 0x20), &lbl_8_rodata_1F98,
			    lbl_8_rodata_1F98);
		}
	}
}

void fn_8_C9230(void* arg0)
{
	void* temp_r4;

	if ((s32)M2C_FIELD(arg0, s32*, 0xD8) == 1) {
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x40), f32*, 8)
		    = (f32)(-M2C_FIELD(&lbl_8_data_18D0C, f32*, 0xC) * M2C_FIELD(arg0, f32*, 0xD4));
	} else {
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x40), f32*, 8)
		    = (f32)(M2C_FIELD(&lbl_8_data_18D0C, f32*, 0xC) * M2C_FIELD(arg0, f32*, 0xD4));
	}
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x40), f32*, 0x14)
	    = (f32)(M2C_FIELD(&lbl_8_data_18D0C, f32*, 0x14) * M2C_FIELD(arg0, f32*, 0xD4));
	temp_r4 = M2C_FIELD(arg0, void**, 0x40);
	M2C_FIELD(temp_r4, f32*, 0x18)
	    = (f32)(M2C_FIELD(&lbl_8_data_18D0C, f32*, 0x18) * M2C_FIELD(arg0, f32*, 0xD4));
	fn_80021384(
	    (u8*)arg0 + 0x30, temp_r4, &lbl_8_data_18D0C, M2C_FIELD(&lbl_8_data_18D0C, f32*, 0x18));
}

void fn_8_C92D0(void* arg0)
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
	M2C_FIELD(arg0, s32*, 0xD8) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 0xC);
	M2C_FIELD(arg0, f32*, 0xD4) = (f32)(lbl_8_rodata_1F9C + M2C_FIELD(temp_r5, f32*, 4));
	M2C_FIELD(arg0, f32*, 0xD0) = (f32)(lbl_8_rodata_1F9C + M2C_FIELD(temp_r5, f32*, 8));
	M2C_FIELD(arg0, s32*, 0xDC) = (s32)M2C_FIELD(temp_r5, s32*, 0);
}

void fn_8_C9354(void* arg0)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	void* sp8;
	f32 temp_f0;
	f32 temp_f2;
	f32 temp_f30;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	f32 temp_f31_5;
	s32 temp_r30_2;
	s32 temp_r5;
	void** temp_r3;
	void* temp_r30;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;
	void* temp_r3_6;
	void* temp_r4;

	if ((fn_8005B9F0((u8*)arg0 + 0x28) != 0) || (fn_8005B8BC((u8*)arg0 + 0x28) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	temp_r3  = M2C_FIELD(M2C_FIELD(arg0, void**, 0xE4), void***, 0x20);
	temp_f31 = lbl_8_rodata_1FA0 * M2C_FIELD(*temp_r3, f32*, 0xC);
	temp_f2  = M2C_FIELD(arg0, f32*, 0xD0) * (f32)M2C_FIELD(lbl_8042C180, s32*, 0x30);
	temp_f30 = temp_f2 - (temp_f31 * (f32)(s32)(temp_f2 / temp_f31));
	fn_8020D02C(temp_r3, &temp_f30, temp_f2, lbl_8_rodata_1FA0);
	fn_8013FC30(M2C_FIELD(arg0, void**, 0xE4));
	if (fn_8005B8D8((u8*)arg0 + 0x28) != 0) {
		temp_r5                     = M2C_FIELD(arg0, s32*, 0xDC);
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
		M2C_FIELD(arg0, s32*, 0xD8) = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0xC);
		M2C_FIELD(arg0, f32*, 0xD4) = (f32)(lbl_8_rodata_1F9C + M2C_FIELD(temp_r4, f32*, 4));
		M2C_FIELD(arg0, f32*, 0xD0) = (f32)(lbl_8_rodata_1F9C + M2C_FIELD(temp_r4, f32*, 8));
		M2C_FIELD(arg0, s32*, 0xDC) = (s32)M2C_FIELD(temp_r4, s32*, 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0xDC) != temp_r5) {
			if ((void*)M2C_FIELD(arg0, void**, 0xE0) != NULL) {
				fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
				fn_80150958(M2C_FIELD(arg0, void**, 0xE0));
				M2C_FIELD(arg0, void**, 0xE0) = NULL;
			}
			if ((void*)M2C_FIELD(arg0, void**, 0xE0) == NULL) {
				M2C_FIELD(arg0, void**, 0xE0)
				    = fn_80150588(lbl_8_data_18C8C[M2C_FIELD(arg0, s32*, 0xDC)]);
				if ((void*)M2C_FIELD(arg0, void**, 0xE0) != NULL) {
					fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
					fn_8005D5C8(M2C_FIELD(arg0, void**, 0xE0),
					    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000)
					        >> 0x12U)
					        + 4);
					temp_r30  = M2C_FIELD(arg0, void**, 0xE0);
					sp8       = NULL;
					temp_r3_4 = fn_8013F484(M2C_FIELD(temp_r30, s32*, 4));
					sp8       = temp_r3_4;
					if (temp_r3_4 == NULL) {
						fn_8019EB10(M2C_FIELD(temp_r30, s32*, 4), fn_8_C9E7C, &sp8);
					}
					M2C_FIELD(arg0, void**, 0xE4) = sp8;
					fn_8014FFBC(
					    M2C_FIELD(arg0, void**, 0xE0), fn_8_C9DCC, M2C_FIELD(arg0, void**, 0xE4));
					temp_r3_5                     = M2C_FIELD(arg0, void**, 0xE4);
					M2C_FIELD(temp_r3_5, s32*, 0) = (s32)(M2C_FIELD(temp_r3_5, s32*, 0) | 0x3000);
					fn_8020C72C(M2C_FIELD(M2C_FIELD(arg0, void**, 0xE4), void***, 0x20),
					    lbl_8_data_18C94[M2C_FIELD(arg0, s32*, 0xDC)]);
					fn_8013F3A4(M2C_FIELD(arg0, void**, 0xE4));
					fn_8013FC30(M2C_FIELD(arg0, void**, 0xE4));
					fn_8020D02C(M2C_FIELD(M2C_FIELD(arg0, void**, 0xE4), void***, 0x20),
					    &lbl_8_rodata_1F98, lbl_8_rodata_1F98);
					fn_8020CC18(M2C_FIELD(M2C_FIELD(arg0, void**, 0xE4), void***, 0x20),
					    &lbl_8_rodata_1F98, lbl_8_rodata_1F98);
				}
			}
		}
		temp_r3_6 = M2C_FIELD(arg0, void**, 0xE0);
		if (temp_r3_6 != NULL) {
			temp_f0    = M2C_FIELD(arg0, f32*, 0xD4);
			sp14       = temp_f0;
			sp10       = temp_f0;
			spC        = temp_f0;
			temp_r30_2 = M2C_FIELD(temp_r3_6, s32*, 4);
			fn_8019EB94(temp_r30_2, (f32*)((u8*)arg0 + 0xB8), 0);
			temp_f31_2 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
			fn_80195790(temp_r30_2 + 0x10, &lbl_80239984, 1,
			    lbl_8_rodata_1F9C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f31_2);
			fn_8019E880(temp_r30_2);
			if ((s32)M2C_FIELD(arg0, s32*, 0xD8) == 1) {
				temp_f31_3 = fn_800D7B00(0x4000);
				fn_80195790(temp_r30_2 + 0x10, &lbl_80239990, 1,
				    lbl_8_rodata_1F9C - fn_800D7AE4(0x4000), temp_f31_3);
				fn_8019E880(temp_r30_2);
			} else {
				temp_f31_4 = fn_800D7B00(-0x4000);
				fn_80195790(temp_r30_2 + 0x10, &lbl_80239990, 1,
				    lbl_8_rodata_1F9C - fn_800D7AE4(-0x4000), temp_f31_4);
				fn_8019E880(temp_r30_2);
			}
			fn_8019EC30(temp_r30_2, &spC, 1);
		}
	} else {
		if (temp_f30 < temp_f31) {
			M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
			if ((temp_f31 == (lbl_8_rodata_1F9C + temp_f30)) && ((u32)lbl_8042C388 != 0U)) {
				fn_800B4A38(0x5A18, (u8*)arg0 + 0xB8, 0, 1, (s8)lbl_8_data_18C88, 0);
			}
		}
		temp_f31_5 = (f32)((f64)temp_f31 * lbl_8_rodata_1FA8);
		if (temp_f30 < temp_f31_5) {
			M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
			if ((temp_f31_5 == (lbl_8_rodata_1F9C + temp_f30)) && ((u32)lbl_8042C388 != 0U)) {
				fn_800B4A38(0x5A19, (u8*)arg0 + 0xB8, 0, 1, (s8)lbl_8_data_18C88, 0);
			}
		}
	}
}

void fn_8_C9858(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	s32 temp_r31;
	void* temp_r3;

	temp_r3 = M2C_FIELD(arg0, void**, 0xE0);
	if (temp_r3 != NULL) {
		temp_f0  = M2C_FIELD(arg0, f32*, 0xD4);
		sp10     = temp_f0;
		spC      = temp_f0;
		sp8      = temp_f0;
		temp_r31 = M2C_FIELD(temp_r3, s32*, 4);
		fn_8019EB94(temp_r31, (f32*)((u8*)arg0 + 0xB8), 0);
		temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
		fn_80195790(temp_r31 + 0x10, &lbl_80239984, 1,
		    lbl_8_rodata_1F9C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f31);
		fn_8019E880(temp_r31);
		if ((s32)M2C_FIELD(arg0, s32*, 0xD8) == 1) {
			temp_f31_2 = fn_800D7B00(0x4000);
			fn_80195790(temp_r31 + 0x10, &lbl_80239990, 1, lbl_8_rodata_1F9C - fn_800D7AE4(0x4000),
			    temp_f31_2);
			fn_8019E880(temp_r31);
		} else {
			temp_f31_3 = fn_800D7B00(-0x4000);
			fn_80195790(temp_r31 + 0x10, &lbl_80239990, 1, lbl_8_rodata_1F9C - fn_800D7AE4(-0x4000),
			    temp_f31_3);
			fn_8019E880(temp_r31);
		}
		fn_8019EC30(temp_r31, &sp8, 1);
	}
}

TObject* fn_8_C99B4(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_18D4C;
		arg0->unk2C = &lbl_8_data_18D4C + 0x2C;
		if ((void*)arg0->unkE0 != NULL) {
			fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
			fn_80150958(arg0->unkE0);
			arg0->unkE0 = NULL;
		}
		dtor_8003C52C((u8*)arg0 + 0x30, 0);
		dtor_8005BD3C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_C9A7C(TObject* arg0, TObject* arg1)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	void* sp8;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	s32 temp_r30_2;
	void* temp_r30;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;
	void* temp_r5;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	fn_8003C618(&arg0->unk30);
	arg0->unk18 = &lbl_8_data_18D4C;
	arg0->unk2C = &lbl_8_data_18D4C + 0x2C;
	arg0->unk0  = (M2C_UNK*)lbl_8_data_18D48;
	arg0->unk1E = 0xE8;
	temp_r3     = M2C_FIELD(arg0, void**, 0x28);
	temp_r5     = M2C_FIELD(temp_r3, void**, 0x2C);
	arg0->unkB8 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unkBC = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unkC0 = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2   = M2C_FIELD(arg0, void**, 0x28);
	arg0->unkC4 = M2C_FIELD(temp_r3_2, s32*, 0xC);
	arg0->unkC8 = M2C_FIELD(temp_r3_2, s32*, 0x10);
	arg0->unkCC = M2C_FIELD(temp_r3_2, s32*, 0x14);
	arg0->unkCC = 0;
	arg0->unkC4 = 0;
	arg0->unkD8 = (s32)(s8)M2C_FIELD(temp_r5, u8*, 0xC);
	arg0->unkD4 = lbl_8_rodata_1F9C + M2C_FIELD(temp_r5, f32*, 4);
	arg0->unkD0 = lbl_8_rodata_1F9C + M2C_FIELD(temp_r5, f32*, 8);
	arg0->unkDC = M2C_FIELD(temp_r5, s32*, 0);
	arg0->unkE0 = NULL;
	if ((void*)arg0->unkE0 == NULL) {
		arg0->unkE0 = fn_80150588(lbl_8_data_18C8C[arg0->unkDC]);
		if ((void*)arg0->unkE0 != NULL) {
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
			fn_8005D5C8(arg0->unkE0,
			    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
			        + 4);
			temp_r30  = arg0->unkE0;
			sp8       = NULL;
			temp_r3_3 = fn_8013F484(M2C_FIELD(temp_r30, s32*, 4));
			sp8       = temp_r3_3;
			if (temp_r3_3 == NULL) {
				fn_8019EB10(M2C_FIELD(temp_r30, s32*, 4), fn_8_C9E7C, &sp8);
			}
			arg0->unkE4 = sp8;
			fn_8014FFBC(arg0->unkE0, fn_8_C9DCC, arg0->unkE4);
			temp_r3_4                     = arg0->unkE4;
			M2C_FIELD(temp_r3_4, s32*, 0) = (s32)(M2C_FIELD(temp_r3_4, s32*, 0) | 0x3000);
			fn_8020C72C(M2C_FIELD(arg0->unkE4, void***, 0x20), lbl_8_data_18C94[arg0->unkDC]);
			fn_8013F3A4(arg0->unkE4);
			fn_8013FC30(arg0->unkE4);
			fn_8020D02C(
			    M2C_FIELD(arg0->unkE4, void***, 0x20), &lbl_8_rodata_1F98, lbl_8_rodata_1F98);
			fn_8020CC18(
			    M2C_FIELD(arg0->unkE4, void***, 0x20), &lbl_8_rodata_1F98, lbl_8_rodata_1F98);
		}
	}
	temp_r3_5 = arg0->unkE0;
	if (temp_r3_5 != NULL) {
		temp_f0    = arg0->unkD4;
		sp14       = temp_f0;
		sp10       = temp_f0;
		spC        = temp_f0;
		temp_r30_2 = M2C_FIELD(temp_r3_5, s32*, 4);
		fn_8019EB94(temp_r30_2, &arg0->unkB8, 0);
		temp_f31 = fn_800D7B00(arg0->unkC8);
		fn_80195790(temp_r30_2 + 0x10, &lbl_80239984, 1,
		    lbl_8_rodata_1F9C - fn_800D7AE4(arg0->unkC8), temp_f31);
		fn_8019E880(temp_r30_2);
		if ((s32)arg0->unkD8 == 1) {
			temp_f31_2 = fn_800D7B00(0x4000);
			fn_80195790(temp_r30_2 + 0x10, &lbl_80239990, 1,
			    lbl_8_rodata_1F9C - fn_800D7AE4(0x4000), temp_f31_2);
			fn_8019E880(temp_r30_2);
		} else {
			temp_f31_3 = fn_800D7B00(-0x4000);
			fn_80195790(temp_r30_2 + 0x10, &lbl_80239990, 1,
			    lbl_8_rodata_1F9C - fn_800D7AE4(-0x4000), temp_f31_3);
			fn_8019E880(temp_r30_2);
		}
		fn_8019EC30(temp_r30_2, &spC, 1);
	}
	fn_8005B8D8(&arg0->unk28);
	return arg0;
}

void* fn_8_C9DCC(void* arg0, s32 arg1)
{
	if (fn_80226468(M2C_FIELD(arg0, s32*, 0x18)) != 0U) {
		fn_80226440(arg0, arg1);
	}
	return arg0;
}

void* fn_8_C9E20(void* arg0)
{
	void* sp8;
	void* temp_r3;

	sp8     = NULL;
	temp_r3 = fn_8013F484(M2C_FIELD(arg0, s32*, 4));
	sp8     = temp_r3;
	if (temp_r3 == NULL) {
		fn_8019EB10(M2C_FIELD(arg0, s32*, 4), fn_8_C9E7C, &sp8);
	}
	return sp8;
}

s32 fn_8_C9E7C(s32 arg0, void** arg1)
{
	void* temp_r3;

	temp_r3 = fn_8013F484(arg0);
	if (temp_r3 == NULL) {
		fn_8019EB10(arg0, fn_8_C9E7C, arg1);
		return arg0;
	}
	*arg1 = temp_r3;
	return 0;
}

void fn_8_C9EE0(void* arg0, void* arg1)
{
	void* temp_r3;

	temp_r3 = M2C_FIELD(arg1, void**, 0x2C);
	if ((s32)M2C_FIELD(temp_r3, s32*, 0) < 0) {
		M2C_FIELD(temp_r3, s32*, 0) = 0;
	}
	if ((s32)M2C_FIELD(temp_r3, s32*, 0) > 1) {
		M2C_FIELD(temp_r3, s32*, 0) = 1;
	}
	if ((s8)M2C_FIELD(temp_r3, u8*, 0xC) < 0) {
		M2C_FIELD(temp_r3, u8*, 0xC) = 0U;
	}
	if ((s8)M2C_FIELD(temp_r3, u8*, 0xC) > 1) {
		M2C_FIELD(temp_r3, u8*, 0xC) = 1U;
	}
	M2C_FIELD(&maskObjectFieldNames, M2C_UNK**, 0xC)
	    = (M2C_UNK*)lbl_8_data_18D04[(s8)M2C_FIELD(temp_r3, u8*, 0xC)];
}

void maskObjectUnload(void)
{
	s32 var_r28;
	u32* var_r29;
	u32* var_r30;

	var_r28 = 0;
	var_r30 = lbl_8_data_18C8C;
	var_r29 = lbl_8_data_18C94;
	do {
		if ((u32)*var_r30 != 0U) {
			fn_80150958((void*)*var_r30);
			*var_r30 = 0U;
		}
		if ((u32)*var_r29 != 0U) {
			fn_8020C2D8(*var_r29);
			*var_r29 = 0U;
		}
		var_r30 += 4;
		var_r29 += 4;
		var_r28 += 1;
	} while (var_r28 < 2);
}

void maskObjectLoad(void)
{
	s32 temp_r31;

	if ((u32)M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18) != 0U) {
		fn_801A4C84();
		temp_r31 = M2C_FIELD(lbl_8042C298, s32*, 0xA50);
		fn_800BC9F4(temp_r31, &lbl_802FF5A0);
		M2C_FIELD(lbl_8_data_18C8C, u32*, 0) = fn_800BB92C(
		    temp_r31, fn_800BC6CC(temp_r31, (M2C_UNK*)"s11_on_maska.dff"), &lbl_802FF5A0);
		lbl_8_data_18C8C[1] = fn_800BB92C(
		    temp_r31, fn_800BC6CC(temp_r31, (M2C_UNK*)"s11_on_maskb.dff"), &lbl_802FF5A0);
		M2C_FIELD(lbl_8_data_18C94, u32*, 0) = fn_800BB0D4(
		    temp_r31, fn_800BC6CC(temp_r31, (M2C_UNK*)"s11_on_maska.anm"), &lbl_802FF5A0);
		lbl_8_data_18C94[1] = fn_800BB0D4(
		    temp_r31, fn_800BC6CC(temp_r31, (M2C_UNK*)"s11_on_maskb.anm"), &lbl_802FF5A0);
	}
}

void maskObjectCreate(void)
{
	TObject* object = (TObject*)fn_80018A34(lbl_8042C148, 0xE8);
	if (object != NULL) {
		fn_8_C9A7C(object, lbl_8042C110);
	}
}

void maskObjectRegister(void)
{
	s32 flags;
	M2C_UNK* temp_r3;

	M2C_FIELD(&maskObjectEntry, s32*, 0x14)       = 0;
	M2C_FIELD(&maskObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&maskObjectEntry, M2C_UNK**, 0)     = (M2C_UNK*)maskObjectDisplayName;
	M2C_FIELD(&maskObjectEntry, void (**)(), 4)   = maskObjectLoad;
	M2C_FIELD(&maskObjectEntry, void (**)(), 8)   = maskObjectUnload;
	M2C_FIELD(&maskObjectEntry, void (**)(), 0xC) = maskObjectCreate;
	M2C_FIELD(&maskObjectEntry, s32*, 0x10)       = 0;
	flags                                         = 0x20000;
	M2C_FIELD(&maskObjectEntry, s32*, 0x14)       = flags;
	M2C_FIELD(&maskObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&maskObjectEntry, s8*, 0x20)        = 0x1E;
	M2C_FIELD(&maskObjectEntry, s16*, 0x1C)       = 0x118D;
	M2C_FIELD(&maskObjectEntry, s16*, 0x1E)       = 2;
	M2C_FIELD(&maskObjectEntry, s8*, 0x21)        = 0;
	temp_r3                                       = (M2C_UNK*)maskObjectFieldTypes;
	M2C_FIELD(&maskObjectEntry, M2C_UNK**, 0x24)  = temp_r3;
	M2C_FIELD(&maskObjectEntry, M2C_UNK**, 0x28)  = &maskObjectFieldNames;
	if (temp_r3 != NULL) {
		M2C_FIELD(&maskObjectEntry, s32*, 0x14) = flags | 8;
		return;
	}
	M2C_FIELD(&maskObjectEntry, s32*, 0x14) = flags & ~8;
}

__declspec(section ".ctors") void (*const maskObjectCtorEntry)(void) = maskObjectRegister;
}
