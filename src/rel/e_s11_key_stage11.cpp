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
	/* 0xB8 */ f32 unkB8;     /* inferred */
	/* 0xBC */ f32 unkBC;     /* inferred */
	/* 0xC0 */ f32 unkC0;     /* inferred */
	/* 0xC4 */ char padC4[8]; /* maybe part of unkC0[3]? */
	/* 0xCC */ f32 unkCC;     /* inferred */
	/* 0xD0 */ f32 unkD0;     /* inferred */
	/* 0xD4 */ s32 unkD4;     /* inferred */
	/* 0xD8 */ u32 unkD8;     /* inferred */
	/* 0xDC */ s32* unkDC;    /* inferred */
	/* 0xE0 */ s32 unkE0;     /* inferred */
} TObject;                    /* size >= 0xE4 */

extern "C" {

void* __ct__7TObjectFP7TObject(void*, void*);               /* extern */
void* __dt__7TObjectFv(void*, s32);                         /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                      /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                      /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                         /* extern */
TObject* fn_80018A34(s32, M2C_UNK);                         /* extern */
void* fn_80020BD8(void*, M2C_UNK);                          /* extern */
void* fn_800211A8(void*);                                   /* extern */
M2C_UNK fn_80021824(M2C_UNK*);                              /* extern */
M2C_UNK fn_8003BC38(void*, s32, M2C_UNK*);                  /* extern */
M2C_UNK fn_8003BF04(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);  /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                              /* extern */
s32* fn_80057644(M2C_UNK);                                  /* extern */
s32 fn_8005B8BC(void*);                                     /* extern */
s32 fn_8005B8D8(void*);                                     /* extern */
s32 fn_8005B9F0(void*);                                     /* extern */
M2C_UNK fn_8005BC04(void*);                                 /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                              /* extern */
M2C_UNK fn_8005D5C8(s32);                                   /* extern */
M2C_UNK fn_800628D0(M2C_UNK, f32*, M2C_UNK, f32, f32, f32); /* extern */
M2C_UNK fn_80066988(void*, s8, M2C_UNK);                    /* extern */
M2C_UNK fn_80090B00(s32);                                   /* extern */
M2C_UNK fn_800B52E8(M2C_UNK, M2C_UNK, M2C_UNK);             /* extern */
u32 fn_800BB92C(s32, s32, M2C_UNK*);                        /* extern */
s32 fn_800BC6CC(s32, M2C_UNK*);                             /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                         /* extern */
f32 fn_800D71DC(void*, void*);                              /* extern */
f32 fn_800D7AE4(s32, ...);                                  /* extern */
f32 fn_800D7B00(s32, ...);                                  /* extern */
M2C_UNK fn_80119618(u32);                                   /* extern */
M2C_UNK fn_8011967C(u32, f32*);                             /* extern */
M2C_UNK fn_801197F4(M2C_UNK);                               /* extern */
s32* fn_80119A18(u32);                                      /* extern */
M2C_UNK fn_801379A0(M2C_UNK, s8);                           /* extern */
M2C_UNK fn_8014FF2C(u32);                                   /* extern */
u32 fn_80150588(u32);                                       /* extern */
M2C_UNK fn_80150958(u32);                                   /* extern */
M2C_UNK fn_80194234(M2C_UNK, s32);                          /* extern */
M2C_UNK fn_80194294(M2C_UNK, s32*);                         /* extern */
M2C_UNK fn_80195790(s32, M2C_UNK*, M2C_UNK, f32, f32);      /* extern */
M2C_UNK fn_8019E880(s32);                                   /* extern */
M2C_UNK fn_8019EB94(s32, f32*, ...);                        /* extern */
M2C_UNK fn_8019EC30(s32, f32*, M2C_UNK);                    /* extern */
M2C_UNK fn_801A4C84();                                      /* extern */
M2C_UNK fn_8_C9EE0(s32);                                    /* extern */
void s11keyObjectCreate();                                  /* static */
void s11keyObjectLoad();                                    /* static */
void s11keyObjectUnload();                                  /* static */
extern M2C_UNK lbl_80239984;
extern void* lbl_802AD0D0[];
extern M2C_UNK lbl_802FF5A0;
extern void* lbl_80303DC8[];
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern M2C_UNK lbl_8042C1A4;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u32 lbl_8042C388;
extern u32 lbl_8_bss_1D48;
extern M2C_UNK lbl_8_rodata_1FB8;
extern f32 lbl_8_rodata_1FC4;
extern f32 lbl_8_rodata_1FC8;
extern f32 lbl_8_rodata_1FCC;
extern f32 lbl_8_rodata_1FD0;
extern f32 lbl_8_rodata_1FD4;
static f32 lbl_8_data_18DF0 = 0.05f;
static s32 lbl_8_data_18DF4 = 0x40;
static f32 lbl_8_data_18DF8 = 0.015f;
static f32 lbl_8_data_18DFC = 0.015f;
static f32 lbl_8_data_18E00 = 10.0f;
static M2C_UNK lbl_8_data_18E04;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18E34;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018E3F_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18E40 = "TObjS11Key";
static M2C_UNK lbl_8_data_18E44;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18E7C;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018E8E_data;    /* unable to generate initializer: unknown type */
static M2C_UNK s11keyObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018E9E_data;    /* unable to generate initializer: unknown type */
static M2C_UNK s11keyObjectEntry;
static M2C_UNK lbl_8_rodata_2118; /* unable to generate initializer: unknown type; const */

void fn_8_CA210(s32 arg0)
{
	fn_8_C9EE0(arg0 - 0x28);
}

void fn_8_CA218(void* arg0)
{
	f32 temp_f31;
	s32* temp_r3;
	void* temp_r4;
	void* temp_r4_2;
	void* var_r31;

	temp_r4 = M2C_FIELD(arg0, void**, 0x28);
	if ((s32*)M2C_FIELD(temp_r4, s32**, 0x30) == NULL) {
		var_r31  = M2C_FIELD((u8*)lbl_8042C298 + (M2C_FIELD(temp_r4, u8*, 0x2A) * 4), void**, 0x30);
		temp_f31 = lbl_8_rodata_1FC4;
	loop_6:
		if (var_r31 == NULL) {

		} else {
			if (((u16)M2C_FIELD(var_r31, u16*, 0x28) == 0x24)
			    && (fn_800D71DC(M2C_FIELD(arg0, void**, 0x28), var_r31) < temp_f31)) {
				M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32**, 0x30)  = fn_80057644(0x14);
				*M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32**, 0x30) = 0x12345678;
				temp_r4_2                     = M2C_FIELD(arg0, void**, 0x28);
				temp_r3                       = M2C_FIELD(temp_r4_2, s32**, 0x30);
				M2C_FIELD(temp_r3, f32*, 4)   = (f32)M2C_FIELD(temp_r4_2, f32*, 0);
				M2C_FIELD(temp_r3, f32*, 8)   = (f32)M2C_FIELD(temp_r4_2, f32*, 4);
				M2C_FIELD(temp_r3, f32*, 0xC) = (f32)M2C_FIELD(temp_r4_2, f32*, 8);
				return;
			}
			var_r31 = M2C_FIELD(var_r31, void**, 0x38);
			goto loop_6;
		}
	}
}

void fn_8_CA308(void* arg0)
{
	M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
}

s8 fn_8_CA31C(s32 arg0)
{
	s32 temp_r0;
	s32 var_r31;
	s8 var_r3;
	u32 var_r0;
	u32 var_r0_2;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r4;
	void* temp_r5;
	void* var_r3_2;

	var_r31 = -1;
	fn_80021824(&lbl_8042C1A4);
	temp_r3 = fn_80020BD8((u8*)arg0 + 0x30, 0x13);
	if (temp_r3 != NULL) {
		var_r0 = M2C_FIELD(temp_r3, u32*, 4);
	} else {
		var_r0 = 0U;
	}
	if (var_r0 != 0U) {
		return -1;
	}
	fn_80021824(&lbl_8042C1A4);
	temp_r3_2 = fn_80020BD8((u8*)arg0 + 0x30, 1);
	if (temp_r3_2 != NULL) {
		var_r0_2 = M2C_FIELD(temp_r3_2, u32*, 4);
	} else {
		var_r0_2 = 0U;
	}
	if (var_r0_2 != 0U) {
		return -1;
	}
	fn_80021824((M2C_UNK*)((u8*)arg0 + 0x30));
loop_31:
	temp_r3_3 = fn_800211A8((u8*)arg0 + 0x30);
	if (temp_r3_3 != NULL) {
		var_r3_2 = M2C_FIELD(temp_r3_3, void**, 4);
	} else {
		var_r3_2 = NULL;
	}
	if (var_r3_2 == NULL) {
		var_r3 = -1;
		/* Duplicate return node #36. Try simplifying control flow for better match */
		return var_r3;
	}
	temp_r0 = M2C_FIELD(var_r3_2, s32*, 0x78);
	switch (temp_r0) { /* irregular */
		case 1:
			var_r31 = 0;
			break;
		case 2:
			var_r31 = 1;
			break;
		case 3:
			var_r31 = 2;
			break;
		case 4:
			var_r31 = 3;
			break;
		case 5:
			var_r31 = 4;
			break;
		case 6:
			var_r31 = 5;
			break;
	}
	if (var_r31 != -1) {
		temp_r4 = lbl_802AD0D0[var_r31];
		var_r3  = (s8)M2C_FIELD(temp_r4, u8*, 0x25C);
		if (temp_r4 != NULL) {
			temp_r5 = lbl_80303DC8[var_r3];
			if (var_r31 != M2C_FIELD(temp_r5, s8*, (s8)M2C_FIELD(temp_r5, u8*, 0x3B) + 0x110)) {
				if (var_r31 == M2C_FIELD(temp_r5, s8*, (s8)M2C_FIELD(temp_r5, u8*, 0x3A) + 0x110)) {
					return var_r3;
				}
				goto loop_31;
			}
			return var_r3;
		}
	}
	goto loop_31;
}

void fn_8_CA4D4(void* arg0)
{
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	s32 spC;
	s32 sp8;

	if (((u32)M2C_FIELD(arg0, u32*, 0xD8) != 0U) && ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) == 0)
	    && ((s32)M2C_FIELD(arg0, s32*, 0xD4) == 2) && ((u32)M2C_FIELD(arg0, u32*, 0xDC) != 0U)) {
		sp18 = lbl_8_rodata_1FC8;
		sp14 = lbl_8_rodata_1FC8;
		sp10 = lbl_8_rodata_1FC8;
		sp1C = M2C_FIELD(arg0, f32*, 0xD0);
		fn_80194294(0xA, &spC);
		fn_80194294(0xB, &sp8);
		fn_80194234(0xA, 5);
		fn_80194234(0xB, 2);
		fn_8011967C(M2C_FIELD(arg0, u32*, 0xDC), &sp10);
		fn_8014FF2C(M2C_FIELD(arg0, u32*, 0xD8));
		fn_80119618(M2C_FIELD(arg0, u32*, 0xDC));
		fn_80194234(0xA, spC);
		fn_80194234(0xB, sp8);
	}
}

void fn_8_CA5C0(void* arg0)
{
	u32 temp_r5;

	temp_r5 = M2C_FIELD(arg0, u32*, 0xD8);
	if ((temp_r5 != 0U) && ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) == 0)
	    && ((s32)M2C_FIELD(arg0, s32*, 0xD4) == 1)) {
		fn_8014FF2C(temp_r5);
	}
}

void fn_8_CA618(void* arg0)
{
	s32 sp4C;
	s32 sp48;
	s32 sp44;
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
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	f32 temp_f3;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r29;
	s32 temp_r29_2;
	s32 temp_r29_3;
	s32 temp_r31;
	s32 temp_r31_2;
	s32 var_r31;
	s32 var_r4;
	s32 var_r4_2;
	s8 var_r4_3;
	u32 var_r0;
	u32 var_r0_2;
	u8 temp_r28;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;
	void* temp_r3_6;
	void* temp_r3_7;
	void* temp_r5;
	void* temp_r5_2;
	void* temp_r5_3;
	void* var_r3;

	if ((fn_8005B9F0((u8*)arg0 + 0x28) != 0) || (fn_8005B8BC((u8*)arg0 + 0x28) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	if (fn_8005B8D8((u8*)arg0 + 0x28) != 0) {
		temp_r3                     = M2C_FIELD(arg0, void**, 0x28);
		M2C_FIELD(arg0, f32*, 0xB8) = (f32)M2C_FIELD(temp_r3, f32*, 0);
		M2C_FIELD(arg0, f32*, 0xBC) = (f32)M2C_FIELD(temp_r3, f32*, 4);
		M2C_FIELD(arg0, f32*, 0xC0) = (f32)M2C_FIELD(temp_r3, f32*, 8);
		if ((void*)M2C_FIELD(arg0, void**, 0xD8) != NULL) {
			var_r4  = 0;
			temp_r5 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), void**, 0x30);
			if ((temp_r5 != NULL) && ((u32)(M2C_FIELD(temp_r5, s32*, 0) + 0xEDCC0000) == 0x5678U)) {
				M2C_FIELD(arg0, f32*, 0xB8) = (f32)M2C_FIELD(temp_r5, f32*, 4);
				M2C_FIELD(arg0, f32*, 0xBC) = (f32)M2C_FIELD(temp_r5, f32*, 8);
				M2C_FIELD(arg0, f32*, 0xC0) = (f32)M2C_FIELD(temp_r5, f32*, 0xC);
				var_r4                      = 1;
			}
			temp_r31 = M2C_FIELD(M2C_FIELD(arg0, void**, 0xD8), s32*, 4);
			if ((s32)M2C_FIELD(arg0, s32*, 0xD4) == 1) {
				sp20 = M2C_FIELD(arg0, f32*, 0xB8);
				sp24 = M2C_FIELD(arg0, f32*, 0xBC);
				sp28 = M2C_FIELD(arg0, f32*, 0xC0);
				if (var_r4 == 0) {
					sp24 = M2C_FIELD(arg0, f32*, 0xBC)
					    + (lbl_8_rodata_1FCC
					        * (lbl_8_rodata_1FC8
					            + fn_800D7AE4(
					                (s32)(lbl_8_rodata_1FD0
					                    * (f32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 360)),
					                M2C_FIELD(lbl_8042C180, s32*, 0x30), lbl_8_rodata_1FD0)));
				}
				fn_8019EB94(temp_r31, &sp20, 0);
				temp_r29
				    = (s32)(lbl_8_rodata_1FD0 * (f32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 360));
				temp_f31
				    = fn_800D7B00(temp_r29, M2C_FIELD(lbl_8042C180, s32*, 0x30), lbl_8_rodata_1FD0);
				fn_80195790(temp_r31 + 0x10, &lbl_80239984, 1,
				    lbl_8_rodata_1FC8 - fn_800D7AE4(temp_r29), temp_f31);
				fn_8019E880(temp_r31);
				return;
			}
			temp_f0 = lbl_8_rodata_1FC8 + M2C_FIELD(arg0, f32*, 0xCC);
			sp34    = temp_f0;
			sp30    = temp_f0;
			sp2C    = temp_f0;
			fn_8019EB94(temp_r31, (f32*)((u8*)arg0 + 0xB8), 0, lbl_8_rodata_1FC8);
			temp_f31_2 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC4));
			fn_80195790(temp_r31 + 0x10, &lbl_80239984, 1,
			    lbl_8_rodata_1FC8 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC4)), temp_f31_2);
			fn_8019E880(temp_r31);
			fn_8019EC30(temp_r31, &sp2C, 1);
		}
	} else {
		if ((void*)M2C_FIELD(arg0, void**, 0xD8) != NULL) {
			var_r4_2  = 0;
			temp_r5_2 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), void**, 0x30);
			if ((temp_r5_2 != NULL)
			    && ((u32)(M2C_FIELD(temp_r5_2, s32*, 0) + 0xEDCC0000) == 0x5678U)) {
				M2C_FIELD(arg0, f32*, 0xB8) = (f32)M2C_FIELD(temp_r5_2, f32*, 4);
				M2C_FIELD(arg0, f32*, 0xBC) = (f32)M2C_FIELD(temp_r5_2, f32*, 8);
				M2C_FIELD(arg0, f32*, 0xC0) = (f32)M2C_FIELD(temp_r5_2, f32*, 0xC);
				var_r4_2                    = 1;
			}
			temp_r31_2 = M2C_FIELD(M2C_FIELD(arg0, void**, 0xD8), s32*, 4);
			if ((s32)M2C_FIELD(arg0, s32*, 0xD4) == 1) {
				sp8  = M2C_FIELD(arg0, f32*, 0xB8);
				spC  = M2C_FIELD(arg0, f32*, 0xBC);
				sp10 = M2C_FIELD(arg0, f32*, 0xC0);
				if (var_r4_2 == 0) {
					spC = M2C_FIELD(arg0, f32*, 0xBC)
					    + (lbl_8_rodata_1FCC
					        * (lbl_8_rodata_1FC8
					            + fn_800D7AE4(
					                (s32)(lbl_8_rodata_1FD0
					                    * (f32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 360)),
					                M2C_FIELD(lbl_8042C180, s32*, 0x30), lbl_8_rodata_1FD0)));
				}
				fn_8019EB94(temp_r31_2, &sp8, 0);
				temp_r29_2
				    = (s32)(lbl_8_rodata_1FD0 * (f32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 360));
				temp_f31_3 = fn_800D7B00(
				    temp_r29_2, M2C_FIELD(lbl_8042C180, s32*, 0x30), lbl_8_rodata_1FD0);
				fn_80195790(temp_r31_2 + 0x10, &lbl_80239984, 1,
				    lbl_8_rodata_1FC8 - fn_800D7AE4(temp_r29_2), temp_f31_3);
				fn_8019E880(temp_r31_2);
			} else {
				temp_f0_2 = lbl_8_rodata_1FC8 + M2C_FIELD(arg0, f32*, 0xCC);
				sp1C      = temp_f0_2;
				sp18      = temp_f0_2;
				sp14      = temp_f0_2;
				fn_8019EB94(temp_r31_2, (f32*)((u8*)arg0 + 0xB8), 0, lbl_8_rodata_1FC8);
				temp_f31_4 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC4));
				fn_80195790(temp_r31_2 + 0x10, &lbl_80239984, 1,
				    lbl_8_rodata_1FC8 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC4)), temp_f31_4);
				fn_8019E880(temp_r31_2);
				fn_8019EC30(temp_r31_2, &sp14, 1);
			}
		}
		temp_r0 = M2C_FIELD(arg0, s32*, 0xD4);
		switch (temp_r0) { /* switch 1; irregular */
			case 0:        /* switch 1 */
				M2C_FIELD(arg0, s32*, 0xD4) = 1;
				return;
			case 1: /* switch 1 */
				var_r31 = -1;
				fn_80021824(&lbl_8042C1A4);
				temp_r3_2 = fn_80020BD8((u8*)arg0 + 0x30, 0x13);
				if (temp_r3_2 != NULL) {
					var_r0 = M2C_FIELD(temp_r3_2, u32*, 4);
				} else {
					var_r0 = 0U;
				}
				if (var_r0 != 0U) {
					var_r4_3 = -1;
				} else {
					fn_80021824(&lbl_8042C1A4);
					temp_r3_3 = fn_80020BD8((u8*)arg0 + 0x30, 1);
					if (temp_r3_3 != NULL) {
						var_r0_2 = M2C_FIELD(temp_r3_3, u32*, 4);
					} else {
						var_r0_2 = 0U;
					}
					if (var_r0_2 != 0U) {
						var_r4_3 = -1;
					} else {
						fn_80021824((M2C_UNK*)((u8*)arg0 + 0x30));
					loop_60:
						temp_r3_4 = fn_800211A8((u8*)arg0 + 0x30);
						if (temp_r3_4 != NULL) {
							var_r3 = M2C_FIELD(temp_r3_4, void**, 4);
						} else {
							var_r3 = NULL;
						}
						if (var_r3 == NULL) {
							var_r4_3 = -1;
						} else {
							temp_r0_2 = M2C_FIELD(var_r3, s32*, 0x78);
							switch (temp_r0_2) { /* switch 2; irregular */
								case 1:          /* switch 2 */
									var_r31 = 0;
									break;
								case 2: /* switch 2 */
									var_r31 = 1;
									break;
								case 3: /* switch 2 */
									var_r31 = 2;
									break;
								case 4: /* switch 2 */
									var_r31 = 3;
									break;
								case 5: /* switch 2 */
									var_r31 = 4;
									break;
								case 6: /* switch 2 */
									var_r31 = 5;
									break;
							}
							if ((var_r31 != -1)
							    && (temp_r3_5 = lbl_802AD0D0[var_r31],
							        var_r4_3  = (s8)M2C_FIELD(temp_r3_5, u8*, 0x25C),
							        ((temp_r3_5 == NULL) == 0))) {
								temp_r5_3 = lbl_80303DC8[var_r4_3];
								if (var_r31
								    != M2C_FIELD(temp_r5_3, s8*,
								        (s8)M2C_FIELD(temp_r5_3, u8*, 0x3B) + 0x110)) {
									if (var_r31
									    == M2C_FIELD(temp_r5_3, s8*,
									        (s8)M2C_FIELD(temp_r5_3, u8*, 0x3A) + 0x110)) {

									} else {
										goto loop_60;
									}
								}
							} else {
								goto loop_60;
							}
						}
					}
				}
				if (var_r4_3 != -1) {
					M2C_FIELD(arg0, s32*, 0xD4) = 2;
					temp_r3_6                   = M2C_FIELD(arg0, void**, 0x28);
					M2C_FIELD(temp_r3_6, s32*, 0x18)
					    = (s32)(M2C_FIELD(temp_r3_6, s32*, 0x18) | 0x10000);
					temp_r29_3 = var_r4_3 * 4;
					temp_r3_7  = M2C_FIELD(lbl_80303DC8, void**, temp_r29_3);
					temp_r28
					    = M2C_FIELD(temp_r3_7, u8*, (s8)M2C_FIELD(temp_r3_7, u8*, 0x3B) + 0x110);
					fn_80066988((u8*)arg0 + 0x30, (s8)temp_r28, 0x64);
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B52E8(0x1020, 0, 0);
					}
					fn_80090B00((s32)M2C_FIELD(lbl_80303DC8, void**, temp_r29_3));
					fn_801379A0(0x2C, (s8)temp_r28);
					M2C_FIELD(arg0, f32*, 0xBC) = (f32)(M2C_FIELD(arg0, f32*, 0xBC)
					    + (lbl_8_rodata_1FCC
					        * (lbl_8_rodata_1FC8
					            + fn_800D7AE4(
					                (s32)(lbl_8_rodata_1FD0
					                    * (f32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 360)),
					                M2C_FIELD(lbl_8042C180, s32*, 0x30), lbl_8_rodata_1FD0))));
					M2C_FIELD(arg0, s32*, 0xC4) = (s32)(lbl_8_rodata_1FD0
					    * (f32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 360));
					M2C_FIELD(arg0, s32*, 0xC8) = 0xB6;
					return;
				}
				sp44                        = M2C_FIELD(&lbl_8_rodata_1FB8, s32*, 0);
				sp48                        = M2C_FIELD(&lbl_8_rodata_1FB8, s32*, 4);
				sp4C                        = M2C_FIELD(&lbl_8_rodata_1FB8, s32*, 8);
				M2C_FIELD(arg0, f32*, 0xAC) = (f32)M2C_FIELD(arg0, f32*, 0x90);
				M2C_FIELD(arg0, f32*, 0xB0) = (f32)M2C_FIELD(arg0, f32*, 0x94);
				M2C_FIELD(arg0, f32*, 0xB4) = (f32)M2C_FIELD(arg0, f32*, 0x98);
				M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0xB8);
				M2C_FIELD(arg0, f32*, 0x94) = (f32)M2C_FIELD(arg0, f32*, 0xBC);
				M2C_FIELD(arg0, f32*, 0x98) = (f32)M2C_FIELD(arg0, f32*, 0xC0);
				M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(&lbl_8_rodata_1FB8, s32*, 0);
				M2C_FIELD(arg0, s32*, 0xA0) = (s32)M2C_FIELD(&lbl_8_rodata_1FB8, s32*, 4);
				M2C_FIELD(arg0, s32*, 0xA4) = (s32)M2C_FIELD(&lbl_8_rodata_1FB8, s32*, 8);
				fn_8003BC38(
				    (u8*)arg0 + 0x30, M2C_FIELD(&lbl_8_rodata_1FB8, s32*, 0), &lbl_8_rodata_1FB8);
				return;
			case 2: /* switch 1 */
				M2C_FIELD(arg0, f32*, 0xBC) = (f32)(M2C_FIELD(arg0, f32*, 0xBC) + lbl_8_data_18DF0);
				M2C_FIELD(arg0, s32*, 0xC8) = (s32)(M2C_FIELD(arg0, s32*, 0xC8) + lbl_8_data_18DF4);
				M2C_FIELD(arg0, s32*, 0xC4)
				    = (s32)(M2C_FIELD(arg0, s32*, 0xC4) + M2C_FIELD(arg0, s32*, 0xC8));
				M2C_FIELD(arg0, f32*, 0xCC) = (f32)(M2C_FIELD(arg0, f32*, 0xCC) + lbl_8_data_18DF8);
				M2C_FIELD(arg0, f32*, 0xD0) = (f32)(M2C_FIELD(arg0, f32*, 0xD0) - lbl_8_data_18DFC);
				if (((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) == 0)
				    && ((s32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 20) == 0)) {
					sp38    = M2C_FIELD(arg0, f32*, 0xB8);
					sp3C    = M2C_FIELD(arg0, f32*, 0xBC);
					sp40    = M2C_FIELD(arg0, f32*, 0xC0);
					temp_f3 = sp3C;
					sp3C    = temp_f3
					    + (lbl_8_data_18E00 * (lbl_8_rodata_1FC8 + M2C_FIELD(arg0, f32*, 0xCC)));
					fn_800628D0(0xD, &sp38, 0, lbl_8_rodata_1FC8, lbl_8_data_18E00, temp_f3);
				}
				if (M2C_FIELD(arg0, f32*, 0xD0) < lbl_8_rodata_1FD4) {
					M2C_FIELD(arg0, f32*, 0xD0) = (f32)lbl_8_rodata_1FD4;
					M2C_FIELD(arg0, u16*, 4)    = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
				}
				return;
		}
	}
}

s32 fn_8_CB0C8(void)
{
	return (s32)(lbl_8_rodata_1FD0 * (f32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 360));
}

f32 fn_8_CB148(void* arg0)
{
	return M2C_FIELD(arg0, f32*, 0xBC)
	    + (lbl_8_rodata_1FCC
	        * (lbl_8_rodata_1FC8
	            + fn_800D7AE4(
	                (s32)(lbl_8_rodata_1FD0 * (f32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 360)),
	                M2C_FIELD(lbl_8042C180, s32*, 0x30), lbl_8_rodata_1FD0)));
}

void fn_8_CB210(void* arg0)
{
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	s32 temp_r30;
	s32 temp_r31;
	s32 var_r5;
	void* temp_r4;

	if ((void*)M2C_FIELD(arg0, void**, 0xD8) != NULL) {
		var_r5  = 0;
		temp_r4 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), void**, 0x30);
		if ((temp_r4 != NULL) && ((u32)(M2C_FIELD(temp_r4, s32*, 0) + 0xEDCC0000) == 0x5678U)) {
			M2C_FIELD(arg0, f32*, 0xB8) = (f32)M2C_FIELD(temp_r4, f32*, 4);
			M2C_FIELD(arg0, f32*, 0xBC) = (f32)M2C_FIELD(temp_r4, f32*, 8);
			M2C_FIELD(arg0, f32*, 0xC0) = (f32)M2C_FIELD(temp_r4, f32*, 0xC);
			var_r5                      = 1;
		}
		temp_r31 = M2C_FIELD(M2C_FIELD(arg0, void**, 0xD8), s32*, 4);
		if ((s32)M2C_FIELD(arg0, s32*, 0xD4) == 1) {
			sp14 = M2C_FIELD(arg0, f32*, 0xB8);
			sp18 = M2C_FIELD(arg0, f32*, 0xBC);
			sp1C = M2C_FIELD(arg0, f32*, 0xC0);
			if (var_r5 == 0) {
				sp18 = M2C_FIELD(arg0, f32*, 0xBC)
				    + (lbl_8_rodata_1FCC
				        * (lbl_8_rodata_1FC8
				            + fn_800D7AE4((s32)(lbl_8_rodata_1FD0
				                              * (f32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 360)),
				                M2C_FIELD(lbl_8042C180, s32*, 0x30), lbl_8_rodata_1FD0)));
			}
			fn_8019EB94(temp_r31, &sp14, 0);
			temp_r30 = (s32)(lbl_8_rodata_1FD0 * (f32)(M2C_FIELD(lbl_8042C180, s32*, 0x30) % 360));
			temp_f31
			    = fn_800D7B00(temp_r30, M2C_FIELD(lbl_8042C180, s32*, 0x30), lbl_8_rodata_1FD0);
			fn_80195790(temp_r31 + 0x10, &lbl_80239984, 1,
			    lbl_8_rodata_1FC8 - fn_800D7AE4(temp_r30), temp_f31);
			fn_8019E880(temp_r31);
			return;
		}
		temp_f0 = lbl_8_rodata_1FC8 + M2C_FIELD(arg0, f32*, 0xCC);
		sp10    = temp_f0;
		spC     = temp_f0;
		sp8     = temp_f0;
		fn_8019EB94(temp_r31, (f32*)((u8*)arg0 + 0xB8), 0, lbl_8_rodata_1FC8);
		temp_f31_2 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC4));
		fn_80195790(temp_r31 + 0x10, &lbl_80239984, 1,
		    lbl_8_rodata_1FC8 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC4)), temp_f31_2);
		fn_8019E880(temp_r31);
		fn_8019EC30(temp_r31, &sp8, 1);
	}
}

TObject* fn_8_CB4C4(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_18E44;
		arg0->unk2C = &lbl_8_data_18E44 + 0x2C;
		if ((u32)arg0->unkD8 != 0U) {
			if ((u32)arg0->unkDC != NULL) {
				fn_801197F4(1);
				arg0->unkDC = NULL;
			}
			fn_80150958(arg0->unkD8);
			arg0->unkD8 = 0U;
		}
		if ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x10000) != 0) {
			fn_8005BC04((u8*)arg0 + 0x28);
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

TObject* fn_8_CB5B0(TObject* arg0, TObject* arg1)
{
	f32 temp_f31;
	s32* temp_r3_2;
	s32* var_r0;
	void* temp_r3;
	void* temp_r3_3;
	void* temp_r4;
	void* temp_r4_2;
	void* var_r30;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	fn_8003C618(&arg0->unk30);
	arg0->unk18 = &lbl_8_data_18E44;
	arg0->unk2C = &lbl_8_data_18E44 + 0x2C;
	arg0->unk0  = (M2C_UNK*)lbl_8_data_18E40;
	arg0->unk1E = 0xE4;
	temp_r3     = M2C_FIELD(arg0, void**, 0x28);
	arg0->unkB8 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unkBC = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unkC0 = M2C_FIELD(temp_r3, f32*, 8);
	arg0->unkD4 = 0;
	arg0->unkCC = lbl_8_rodata_1FD4;
	arg0->unkD0 = lbl_8_rodata_1FC8;
	arg0->unkDC = NULL;
	arg0->unkE0 = 0;
	arg0->unkD8 = fn_80150588(lbl_8_bss_1D48);
	if ((u32)arg0->unkD8 != 0U) {
		fn_8005D5C8(
		    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U) + 4);
		var_r0 = fn_80057644(0x14);
		if (var_r0 != NULL) {
			var_r0 = fn_80119A18(arg0->unkD8);
		}
		arg0->unkDC = var_r0;
	}
	if (fn_8005B8D8(&arg0->unk28) == 0) {
		fn_8003BF04(&arg0->unk30, &lbl_8_data_18E04, 1, 4);
		temp_r4 = M2C_FIELD(arg0, void**, 0x28);
		if ((s32*)M2C_FIELD(temp_r4, s32**, 0x30) == NULL) {
			var_r30
			    = M2C_FIELD((u8*)lbl_8042C298 + (M2C_FIELD(temp_r4, u8*, 0x2A) * 4), void**, 0x30);
			temp_f31 = lbl_8_rodata_1FC4;
		loop_11:
			if (var_r30 != NULL) {
				if (((u16)M2C_FIELD(var_r30, u16*, 0x28) == 0x24)
				    && (fn_800D71DC(M2C_FIELD(arg0, void**, 0x28), var_r30) < temp_f31)) {
					M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32**, 0x30)  = fn_80057644(0x14);
					*M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32**, 0x30) = 0x12345678;
					temp_r4_2                       = M2C_FIELD(arg0, void**, 0x28);
					temp_r3_2                       = M2C_FIELD(temp_r4_2, s32**, 0x30);
					M2C_FIELD(temp_r3_2, f32*, 4)   = (f32)M2C_FIELD(temp_r4_2, f32*, 0);
					M2C_FIELD(temp_r3_2, f32*, 8)   = (f32)M2C_FIELD(temp_r4_2, f32*, 4);
					M2C_FIELD(temp_r3_2, f32*, 0xC) = (f32)M2C_FIELD(temp_r4_2, f32*, 8);
				} else {
					var_r30 = M2C_FIELD(var_r30, void**, 0x38);
					goto loop_11;
				}
			}
		}
	}
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x24) == 8) {
		temp_r3_3                        = M2C_FIELD(arg0, void**, 0x28);
		M2C_FIELD(temp_r3_3, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3_3, s32*, 0x18) | 0x10000000);
	}
	return arg0;
}

void s11keyObjectUnload(void)
{
	if ((u32)lbl_8_bss_1D48 != 0U) {
		fn_80150958(lbl_8_bss_1D48);
		lbl_8_bss_1D48 = 0U;
	}
}

void s11keyObjectLoad(void)
{
	s32 temp_r31;

	if ((u32)M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18) != 0U) {
		fn_801A4C84();
		temp_r31 = M2C_FIELD(lbl_8042C298, s32*, 0xA50);
		fn_800BC9F4(temp_r31, &lbl_802FF5A0);
		lbl_8_bss_1D48 = fn_800BB92C(
		    temp_r31, fn_800BC6CC(temp_r31, (M2C_UNK*)"s11_o_goalkey.dff"), &lbl_802FF5A0);
	}
}

void s11keyObjectCreate(void)
{
	TObject* temp_r3;
	f32 temp_f31;
	s32* temp_r3_3;
	s32* var_r0;
	void* temp_r3_2;
	void* temp_r3_4;
	void* temp_r4;
	void* temp_r4_2;
	void* var_r30;

	temp_r3 = fn_80018A34(lbl_8042C148, 0xE4);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C110);
		fn_8005BE6C(&temp_r3->unk28);
		fn_8003C618(&temp_r3->unk30);
		temp_r3->unk18 = &lbl_8_data_18E44;
		temp_r3->unk2C = &lbl_8_data_18E44 + 0x2C;
		temp_r3->unk0  = (M2C_UNK*)lbl_8_data_18E40;
		temp_r3->unk1E = 0xE4;
		temp_r3_2      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r3->unkB8 = M2C_FIELD(temp_r3_2, f32*, 0);
		temp_r3->unkBC = M2C_FIELD(temp_r3_2, f32*, 4);
		temp_r3->unkC0 = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3->unkD4 = 0;
		temp_r3->unkCC = lbl_8_rodata_1FD4;
		temp_r3->unkD0 = lbl_8_rodata_1FC8;
		temp_r3->unkDC = NULL;
		temp_r3->unkE0 = 0;
		temp_r3->unkD8 = fn_80150588(lbl_8_bss_1D48);
		if ((u32)temp_r3->unkD8 != 0U) {
			fn_8005D5C8(
			    ((u32)(M2C_FIELD(M2C_FIELD(temp_r3, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
			    + 4);
			var_r0 = fn_80057644(0x14);
			if (var_r0 != NULL) {
				var_r0 = fn_80119A18(temp_r3->unkD8);
			}
			temp_r3->unkDC = var_r0;
		}
		if (fn_8005B8D8(&temp_r3->unk28) == 0) {
			fn_8003BF04(&temp_r3->unk30, &lbl_8_data_18E04, 1, 4);
			temp_r4 = M2C_FIELD(temp_r3, void**, 0x28);
			if ((s32*)M2C_FIELD(temp_r4, s32**, 0x30) == NULL) {
				var_r30 = M2C_FIELD(
				    (u8*)lbl_8042C298 + (M2C_FIELD(temp_r4, u8*, 0x2A) * 4), void**, 0x30);
				temp_f31 = lbl_8_rodata_1FC4;
			loop_12:
				if (var_r30 != NULL) {
					if (((u16)M2C_FIELD(var_r30, u16*, 0x28) == 0x24)
					    && (fn_800D71DC(M2C_FIELD(temp_r3, void**, 0x28), var_r30) < temp_f31)) {
						M2C_FIELD(M2C_FIELD(temp_r3, void**, 0x28), s32**, 0x30)
						    = fn_80057644(0x14);
						*M2C_FIELD(M2C_FIELD(temp_r3, void**, 0x28), s32**, 0x30) = 0x12345678;
						temp_r4_2                       = M2C_FIELD(temp_r3, void**, 0x28);
						temp_r3_3                       = M2C_FIELD(temp_r4_2, s32**, 0x30);
						M2C_FIELD(temp_r3_3, f32*, 4)   = (f32)M2C_FIELD(temp_r4_2, f32*, 0);
						M2C_FIELD(temp_r3_3, f32*, 8)   = (f32)M2C_FIELD(temp_r4_2, f32*, 4);
						M2C_FIELD(temp_r3_3, f32*, 0xC) = (f32)M2C_FIELD(temp_r4_2, f32*, 8);
					} else {
						var_r30 = M2C_FIELD(var_r30, void**, 0x38);
						goto loop_12;
					}
				}
			}
		}
		if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x24) == 8) {
			temp_r3_4                        = M2C_FIELD(temp_r3, void**, 0x28);
			M2C_FIELD(temp_r3_4, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3_4, s32*, 0x18) | 0x10000000);
		}
	}
}

void s11keyObjectRegister(void)
{
	M2C_FIELD(&s11keyObjectEntry, s32*, 0x14)       = 0;
	M2C_FIELD(&s11keyObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&s11keyObjectEntry, M2C_UNK**, 0)     = (M2C_UNK*)"S11KEY OBJECT";
	M2C_FIELD(&s11keyObjectEntry, void (**)(), 4)   = s11keyObjectLoad;
	M2C_FIELD(&s11keyObjectEntry, void (**)(), 8)   = s11keyObjectUnload;
	M2C_FIELD(&s11keyObjectEntry, void (**)(), 0xC) = s11keyObjectCreate;
	M2C_FIELD(&s11keyObjectEntry, s32*, 0x10)       = 0;
	M2C_FIELD(&s11keyObjectEntry, s32*, 0x14)       = 0x20000;
	M2C_FIELD(&s11keyObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&s11keyObjectEntry, s8*, 0x20)        = 0x1E;
	M2C_FIELD(&s11keyObjectEntry, s16*, 0x1C)       = 0x1109;
	M2C_FIELD(&s11keyObjectEntry, s16*, 0x1E)       = 2;
	M2C_FIELD(&s11keyObjectEntry, s8*, 0x21)        = 0;
	M2C_FIELD(&s11keyObjectEntry, s32*, 0x24)       = 0;
	M2C_FIELD(&s11keyObjectEntry, s32*, 0x28)       = 0;
	if (0U != 0U) {
		M2C_FIELD(&s11keyObjectEntry, s32*, 0x14) = 0x20008;
		return;
	}
	M2C_FIELD(&s11keyObjectEntry, s32*, 0x14) = 0x20000;
}

__declspec(section ".ctors") void (*const s11keyObjectCtorEntry)(void) = s11keyObjectRegister;
}
