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
	/* 0xB8 */ f32 unkB8; /* inferred */
	/* 0xBC */ f32 unkBC; /* inferred */
	/* 0xC0 */ f32 unkC0; /* inferred */
	/* 0xC4 */ s32 unkC4; /* inferred */
	/* 0xC8 */ s32 unkC8; /* inferred */
	/* 0xCC */ s32 unkCC; /* inferred */
	/* 0xD0 */ s32 unkD0; /* inferred */
	/* 0xD4 */ s32 unkD4; /* inferred */
	/* 0xD8 */ char padD8[4];
	/* 0xDC */ f32 unkDC; /* inferred */
	/* 0xE0 */ u32 unkE0; /* inferred */
	/* 0xE4 */ u32 unkE4; /* inferred */
	/* 0xE8 */ u32 unkE8; /* inferred */
	/* 0xEC */ s32 unkEC; /* inferred */
	/* 0xF0 */ s32 unkF0; /* inferred */
	/* 0xF4 */ s32 unkF4; /* inferred */
	/* 0xF8 */ u32 unkF8; /* inferred */
} TObject;                /* size >= 0xFC */

extern "C" {

void* __ct__7TObjectFP7TObject(void*, void*);          /* extern */
void* __dt__7TObjectFv(void*, s32);                    /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                 /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                 /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                    /* extern */
TObject* fn_80018A34(s32, M2C_UNK);                    /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                         /* extern */
u32 fn_80057644(M2C_UNK);                              /* extern */
s32 fn_8005B8BC(s32);                                  /* extern */
s32 fn_8005B9F0(s32);                                  /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                         /* extern */
M2C_UNK fn_8005D5C8(M2C_UNK);                          /* extern */
u32 fn_800BB92C(s32, s32, M2C_UNK*);                   /* extern */
s32 fn_800BC6CC(s32, M2C_UNK*);                        /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                    /* extern */
f32 fn_800D7AE4(s32);                                  /* extern */
f32 fn_800D7B00(s32);                                  /* extern */
M2C_UNK fn_80119618(u32);                              /* extern */
M2C_UNK fn_8011967C(f32*);                             /* extern */
M2C_UNK fn_801197F4(M2C_UNK);                          /* extern */
u32 fn_80119A18(u32);                                  /* extern */
M2C_UNK fn_8014FF2C(u32);                              /* extern */
u32 fn_80150588(u32);                                  /* extern */
M2C_UNK fn_80150958(...);                              /* extern */
M2C_UNK fn_80194234(M2C_UNK, s32);                     /* extern */
M2C_UNK fn_80194294(M2C_UNK, s32*);                    /* extern */
M2C_UNK fn_80195790(s32, M2C_UNK*, M2C_UNK, f32, f32); /* extern */
M2C_UNK fn_8019E880(s32);                              /* extern */
M2C_UNK fn_8019EB94(s32, s32*, ...);                   /* extern */
M2C_UNK fn_801A4C84();                                 /* extern */
s32 fn_801C28D8(f32*);                                 /* extern */
M2C_UNK fn_8_C2398(s32);                               /* extern */
void s11spiderObjectCreate();                          /* static */
void s11spiderObjectLoad(M2C_UNK arg_sp0);             /* static */
void s11spiderObjectUnload();                          /* static */
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_802FF5A0;
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern M2C_UNK lbl_8_data_18120;
extern M2C_UNK lbl_8_data_18138;
extern M2C_UNK lbl_8_data_18150;
extern M2C_UNK lbl_8_data_18168;
static M2C_UNK* lbl_8_data_18180[5] = {
	&lbl_8_data_18120,
	&lbl_8_data_18138,
	&lbl_8_data_18150,
	&lbl_8_data_18168,
	(M2C_UNK*)0x420C0000,
};
static f32 lbl_8_data_18194 = 0.6f;
static f32 lbl_8_data_18198 = 0.8f;
static f32 lbl_8_data_1819C = 0.5f;
static s32 lbl_8_data_181A0 = 5;
static f32 lbl_8_data_181A4 = 0.55f;
static f32 lbl_8_data_181A8 = 0.4f;
static f32 lbl_8_data_181AC = 0.35f;
static M2C_UNK lbl_8_data_181B0;          /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000181B5_data;      /* unable to generate initializer: unknown type */
static M2C_UNK s11spiderObjectFieldNames; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_181BC;          /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000181CA_data;      /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_181CC = &lbl_8_data_181BC;
static M2C_UNK lbl_8_data_181D0;           /* unable to generate initializer: unknown type */
static M2C_UNK s11spiderObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001821D_data;       /* unable to generate initializer: unknown type */
static M2C_UNK s11spiderObjectFieldTypes;  /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018222_data;       /* unable to generate initializer: unknown type */
static u32 lbl_8_bss_1BD0[4];
static M2C_UNK s11spiderObjectEntry;
static M2C_UNK lbl_8_rodata_1F10; /* unable to generate initializer: unknown type; const */

void fn_8_C28CC(s32 arg0)
{
	fn_8_C2398(arg0 - 0xB0);
}

void fn_8_C28D4(void* arg0)
{
	s32 sp10;
	f32 spC;
	s32 sp8;
	f32 temp_f1;
	f32 temp_f30;
	f32 temp_f30_2;
	s32 temp_r27;
	s32 temp_r27_2;
	s32 var_r26;
	void* temp_r3;
	void* var_r28;

	temp_r3 = M2C_FIELD(arg0, void**, 0xE0);
	if (temp_r3 != NULL) {
		temp_r27 = M2C_FIELD(temp_r3, s32*, 4);
		sp8      = M2C_FIELD(arg0, s32*, 0xB8);
		spC      = M2C_FIELD(arg0, f32*, 0xBC);
		sp10     = M2C_FIELD(arg0, s32*, 0xC0);
		fn_8019EB94(temp_r27, (s32*)((u8*)arg0 + 0xB8), 0);
		temp_f30 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
		fn_80195790(temp_r27 + 0x10, &lbl_80239984, 1,
		    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f30);
		fn_8019E880(temp_r27);
		var_r26 = 0;
		var_r28 = arg0;
		do {
			temp_f1    = spC;
			spC        = temp_f1 + lbl_8_data_1819C;
			temp_r27_2 = M2C_FIELD(M2C_FIELD(var_r28, void**, 0xE8), s32*, 4);
			fn_8019EB94(temp_r27_2, &sp8, 0, temp_f1);
			temp_f30_2 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
			fn_80195790(temp_r27_2 + 0x10, &lbl_80239984, 1,
			    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f30_2);
			fn_8019E880(temp_r27_2);
			var_r28 = (u8*)var_r28 + 4;
			var_r26 += 1;
		} while (var_r26 < 4);
	}
}

void fn_8_C2A30(void* arg0)
{
	s32 var_r29;
	void* var_r30;

	var_r30 = arg0;
	if ((u32)M2C_FIELD(var_r30, u32*, 0xE4) != 0U) {
		fn_801197F4(1);
		M2C_FIELD(var_r30, u32*, 0xE4) = 0U;
	}
	if ((u32)M2C_FIELD(var_r30, u32*, 0xE0) != 0U) {
		fn_80150958();
		M2C_FIELD(var_r30, u32*, 0xE0) = 0U;
	}
	var_r29 = 0;
	do {
		if ((u32)M2C_FIELD(var_r30, u32*, 0xF8) != 0U) {
			fn_801197F4(1);
			M2C_FIELD(var_r30, u32*, 0xF8) = 0U;
		}
		if ((u32)M2C_FIELD(var_r30, u32*, 0xE8) != 0U) {
			fn_80150958();
			M2C_FIELD(var_r30, u32*, 0xE8) = 0U;
		}
		var_r30 = (u8*)var_r30 + 4;
		var_r29 += 1;
	} while (var_r29 < 4);
}

void fn_8_C2AE0(void* arg0, u32 arg1)
{
	s32 var_r30;
	u32 var_r0;
	u32 var_r0_2;
	void* var_r31;

	var_r31 = arg0;
	if (arg1 != 0U) {
		if ((u32)M2C_FIELD(var_r31, u32*, 0xE0) == 0U) {
			M2C_FIELD(var_r31, u32*, 0xE0) = fn_80150588(arg1);
			if ((u32)M2C_FIELD(var_r31, u32*, 0xE0) != 0U) {
				fn_8005D5C8(0x10);
				var_r0 = fn_80057644(0x14);
				if (var_r0 != 0U) {
					var_r0 = fn_80119A18(M2C_FIELD(var_r31, u32*, 0xE0));
				}
				M2C_FIELD(var_r31, u32*, 0xE4) = var_r0;
			}
		}
		var_r30 = 0;
		do {
			if ((u32)M2C_FIELD(var_r31, u32*, 0xE8) == 0U) {
				M2C_FIELD(var_r31, u32*, 0xE8) = fn_80150588(arg1);
				if ((u32)M2C_FIELD(var_r31, u32*, 0xE8) != 0U) {
					fn_8005D5C8(0x10);
					var_r0_2 = fn_80057644(0x14);
					if (var_r0_2 != 0U) {
						var_r0_2 = fn_80119A18(M2C_FIELD(var_r31, u32*, 0xE8));
					}
					M2C_FIELD(var_r31, u32*, 0xF8) = var_r0_2;
				}
			}
			var_r31 = (u8*)var_r31 + 4;
			var_r30 += 1;
		} while (var_r30 < 4);
	}
}

void fn_8_C2BD8(void* arg0)
{
	void* temp_r4;
	void* temp_r4_2;

	temp_r4                     = M2C_FIELD(arg0, void**, 0x28);
	M2C_FIELD(arg0, f32*, 0xB8) = (f32)M2C_FIELD(temp_r4, f32*, 0);
	M2C_FIELD(arg0, f32*, 0xBC) = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0xC0) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	temp_r4_2                   = M2C_FIELD(arg0, void**, 0x28);
	M2C_FIELD(arg0, s32*, 0xC4) = (s32)M2C_FIELD(temp_r4_2, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0xC8) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0xCC) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x14);
	M2C_FIELD(arg0, s32*, 0xCC) = 0;
	M2C_FIELD(arg0, s32*, 0xC4) = 0;
	M2C_FIELD(arg0, s32*, 0xD0) = (s32)*M2C_FIELD(temp_r4, s32**, 0x2C);
}

void fn_8_C2C2C(void* arg0)
{
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;
	f32 temp_f0;
	s32 var_r30;
	void* var_r31;

	var_r31 = arg0;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) == 0) {
		temp_f0 = M2C_FIELD(var_r31, f32*, 0xD8);
		sp1C    = temp_f0;
		sp18    = temp_f0;
		sp14    = temp_f0;
		sp20    = 1.0f;
		fn_80194294(0xA, &sp10);
		fn_80194294(0xB, &spC);
		fn_80194294(0x14, &sp8);
		fn_80194234(0xA, 2);
		fn_80194234(0xB, 2);
		fn_80194234(0x14, 1);
		if (((u32)M2C_FIELD(var_r31, u32*, 0xE0) != 0U)
		    && ((u32)M2C_FIELD(var_r31, u32*, 0xE4) != 0U)) {
			fn_8011967C(&sp14);
			fn_8014FF2C(M2C_FIELD(var_r31, u32*, 0xE0));
			fn_80119618(M2C_FIELD(var_r31, u32*, 0xE4));
		}
		var_r30 = 0;
		do {
			if (var_r30 == 0) {
				sp14 *= lbl_8_data_18194;
				sp18 *= lbl_8_data_18194;
				sp1C *= lbl_8_data_18194;
			} else {
				sp14 *= lbl_8_data_18198;
				sp18 *= lbl_8_data_18198;
				sp1C *= lbl_8_data_18198;
			}
			if (((u32)M2C_FIELD(var_r31, u32*, 0xE8) != 0U)
			    && ((u32)M2C_FIELD(var_r31, u32*, 0xF8) != 0U)) {
				fn_8011967C(&sp14);
				fn_8014FF2C(M2C_FIELD(var_r31, u32*, 0xE8));
				fn_80119618(M2C_FIELD(var_r31, u32*, 0xF8));
			}
			var_r31 = (u8*)var_r31 + 4;
			var_r30 += 1;
		} while (var_r30 < 4);
		fn_80194234(0x14, sp8);
		fn_80194234(0xA, sp10);
		fn_80194234(0xB, spC);
	}
}

void fn_8_C2DE4(void* arg0)
{
	s32 sp10;
	f32 spC;
	s32 sp8;
	f32 temp_f1;
	f32 temp_f2;
	f32 temp_f30;
	f32 temp_f30_2;
	f32 temp_f30_3;
	s32 temp_r26;
	s32 temp_r28;
	s32 temp_r4;
	s32 temp_r6;
	s32 var_r28;
	void* temp_r3;
	void* var_r27;

	if ((fn_8005B9F0((s32)((u8*)arg0 + 0x28)) != 0)
	    || (fn_8005B8BC((s32)((u8*)arg0 + 0x28)) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	temp_r3 = M2C_FIELD(arg0, void**, 0xE0);
	if (temp_r3 != NULL) {
		temp_r28 = M2C_FIELD(temp_r3, s32*, 4);
		sp8      = M2C_FIELD(arg0, s32*, 0xB8);
		spC      = M2C_FIELD(arg0, f32*, 0xBC);
		sp10     = M2C_FIELD(arg0, s32*, 0xC0);
		fn_8019EB94(temp_r28, (s32*)((u8*)arg0 + 0xB8), 0);
		temp_f30 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
		fn_80195790(temp_r28 + 0x10, &lbl_80239984, 1,
		    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f30);
		fn_8019E880(temp_r28);
		var_r28 = 0;
		var_r27 = arg0;
		do {
			temp_f1  = spC;
			spC      = temp_f1 + lbl_8_data_1819C;
			temp_r26 = M2C_FIELD(M2C_FIELD(var_r27, void**, 0xE8), s32*, 4);
			fn_8019EB94(temp_r26, &sp8, 0, temp_f1);
			temp_f30_2 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
			fn_80195790(temp_r26 + 0x10, &lbl_80239984, 1,
			    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f30_2);
			fn_8019E880(temp_r26);
			var_r27 = (u8*)var_r27 + 4;
			var_r28 += 1;
		} while (var_r28 < 4);
	}
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) == 0) {
		M2C_FIELD(arg0, s32*, 0xD4) = (s32)(M2C_FIELD(arg0, s32*, 0xD4) + 1);
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0xD4) >= (s32)(lbl_8_data_181A0 * 2)) {
		M2C_FIELD(arg0, s32*, 0xD4) = 0;
		temp_f30_3                  = lbl_8_data_181A4;
		M2C_FIELD(arg0, f32*, 0xDC) = (f32)(temp_f30_3
		    - ((temp_f30_3 - lbl_8_data_181A8)
		        * (0.000030517578f * (f32)fn_801C28D8(&lbl_8_data_181A4))));
	}
	temp_r4 = (s32)M2C_FIELD(arg0, s32*, 0xD4) / (s32)lbl_8_data_181A0;
	temp_r6 = M2C_FIELD(arg0, s32*, 0xD4) % lbl_8_data_181A0;
	temp_f2 = (M2C_FIELD(arg0, f32*, 0xDC) - lbl_8_data_181AC) / (f32)lbl_8_data_181A0;
	switch (temp_r4) { /* irregular */
		case 0:
			M2C_FIELD(arg0, f32*, 0xD8) = (f32)(lbl_8_data_181AC + (temp_f2 * (f32)temp_r6));
			return;
		case 1:
			M2C_FIELD(arg0, f32*, 0xD8)
			    = (f32)(lbl_8_data_181AC + (temp_f2 * (f32)(lbl_8_data_181A0 - temp_r6)));
			return;
	}
}

TObject* fn_8_C30D8(TObject* arg0, s16 arg1, M2C_UNK arg_sp0)
{
	TObject* var_r28;
	s32 var_r29;

	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_181D0;
		arg0->unk2C = &lbl_8_data_181D0 + 0x2C;
		if ((u32)arg0->unkE4 != 0U) {
			fn_801197F4(1);
			arg0->unkE4 = 0U;
		}
		if ((u32)arg0->unkE0 != 0U) {
			fn_80150958();
			arg0->unkE0 = 0U;
		}
		var_r29 = 0;
		var_r28 = arg0;
		do {
			if ((u32)var_r28->unkF8 != 0U) {
				fn_801197F4(1);
				var_r28->unkF8 = 0U;
			}
			if ((u32)var_r28->unkE8 != 0U) {
				fn_80150958();
				var_r28->unkE8 = 0U;
			}
			var_r28 += 4;
			var_r29 += 1;
		} while (var_r29 < 4);
		dtor_8003C52C((u8*)arg0 + 0x30, 0);
		dtor_8005BD3C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_C31F0(TObject* arg0, TObject* arg1)
{
	s32 temp_r0;
	s32 var_r28;
	s32 var_r30;
	u32 temp_r29;
	u32 var_r0;
	u32 var_r4;
	void* temp_r3;
	void* temp_r3_2;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	fn_8003C618(&arg0->unk30);
	arg0->unk18 = &lbl_8_data_181D0;
	arg0->unk2C = &lbl_8_data_181D0 + 0x2C;
	arg0->unk0  = lbl_8_data_181CC;
	arg0->unk1E = 0x108;
	temp_r3     = M2C_FIELD(arg0, void**, 0x28);
	arg0->unkB8 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unkBC = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unkC0 = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2   = M2C_FIELD(arg0, void**, 0x28);
	arg0->unkC4 = M2C_FIELD(temp_r3_2, s32*, 0xC);
	arg0->unkC8 = M2C_FIELD(temp_r3_2, s32*, 0x10);
	arg0->unkCC = M2C_FIELD(temp_r3_2, s32*, 0x14);
	arg0->unkCC = 0;
	arg0->unkC4 = 0;
	arg0->unkD0 = *M2C_FIELD(temp_r3, s32**, 0x2C);
	arg0->unkE0 = 0U;
	arg0->unkE8 = 0U;
	arg0->unkEC = 0;
	arg0->unkF0 = 0;
	arg0->unkF4 = 0;
	arg0->unkD4 = 0;
	arg0->unkDC = 1.0f;
	temp_r29    = lbl_8_bss_1BD0[arg0->unkD0];
	if (temp_r29 != 0U) {
		if ((u32)arg0->unkE0 == 0U) {
			arg0->unkE0 = fn_80150588(temp_r29);
			if ((u32)arg0->unkE0 != 0U) {
				fn_8005D5C8(0x10);
				var_r0 = fn_80057644(0x14);
				if (var_r0 != 0U) {
					var_r0 = fn_80119A18(arg0->unkE0);
				}
				arg0->unkE4 = var_r0;
			}
		}
		var_r30 = 0;
		var_r28 = 0;
		do {
			if (*(u32*)((u8*)arg0 + var_r28 + 0xE8) == 0U) {
				temp_r0                      = var_r28 + 0xE8;
				*(u32*)((u8*)arg0 + temp_r0) = fn_80150588(temp_r29);
				if (*(u32*)((u8*)arg0 + temp_r0) != 0U) {
					fn_8005D5C8(0x10);
					var_r4 = fn_80057644(0x14);
					if (var_r4 != 0U) {
						var_r4 = fn_80119A18(*(u32*)((u8*)arg0 + var_r28 + 0xE8));
					}
					*(u32*)((u8*)arg0 + var_r28 + 0xF8) = var_r4;
				}
			}
			var_r28 += 4;
			var_r30 += 1;
		} while (var_r30 < 4);
	}
	return arg0;
}

void fn_8_C33D0(void* arg0, void* arg1)
{
	s32* temp_r3;

	temp_r3 = M2C_FIELD(arg1, s32**, 0x2C);
	if ((s32)*temp_r3 < 0) {
		*temp_r3 = 0;
	}
	if ((s32)*temp_r3 >= 4) {
		*temp_r3 = 3;
	}
}

void s11spiderObjectUnload(void)
{
	s32 var_r29;
	u32* var_r30;

	var_r29 = 0;
	var_r30 = lbl_8_bss_1BD0;
	do {
		fn_80150958(*var_r30);
		*var_r30 = 0U;
		var_r30 += 4;
		var_r29 += 1;
	} while (var_r29 < 4);
}

void s11spiderObjectLoad(M2C_UNK arg_sp0)
{
	M2C_UNK** var_r29;
	s32 var_r27;
	u32* var_r28;

	if ((u32)M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18) != 0U) {
		fn_801A4C84();
		fn_800BC9F4(M2C_FIELD(lbl_8042C298, s32*, 0xA50), &lbl_802FF5A0);
		var_r27 = 0;
		var_r29 = lbl_8_data_18180;
		var_r28 = lbl_8_bss_1BD0;
		do {
			*var_r28 = fn_800BB92C(M2C_FIELD(lbl_8042C298, s32*, 0xA50),
			    fn_800BC6CC(M2C_FIELD(lbl_8042C298, s32*, 0xA50), *var_r29), &lbl_802FF5A0);
			var_r29 += 4;
			var_r28 += 4;
			var_r27 += 1;
		} while (var_r27 < 4);
	}
}

void s11spiderObjectCreate(void)
{
	TObject* temp_r3;
	s32 temp_r0;
	s32 var_r28;
	s32 var_r30;
	u32 temp_r29;
	u32 var_r0;
	u32 var_r4;
	void* temp_r3_2;
	void* temp_r3_3;

	temp_r3 = fn_80018A34(lbl_8042C148, 0x108);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C110);
		fn_8005BE6C(&temp_r3->unk28);
		fn_8003C618(&temp_r3->unk30);
		temp_r3->unk18 = &lbl_8_data_181D0;
		temp_r3->unk2C = &lbl_8_data_181D0 + 0x2C;
		temp_r3->unk0  = lbl_8_data_181CC;
		temp_r3->unk1E = 0x108;
		temp_r3_2      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r3->unkB8 = M2C_FIELD(temp_r3_2, f32*, 0);
		temp_r3->unkBC = M2C_FIELD(temp_r3_2, f32*, 4);
		temp_r3->unkC0 = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3_3      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r3->unkC4 = M2C_FIELD(temp_r3_3, s32*, 0xC);
		temp_r3->unkC8 = M2C_FIELD(temp_r3_3, s32*, 0x10);
		temp_r3->unkCC = M2C_FIELD(temp_r3_3, s32*, 0x14);
		temp_r3->unkCC = 0;
		temp_r3->unkC4 = 0;
		temp_r3->unkD0 = *M2C_FIELD(temp_r3_2, s32**, 0x2C);
		temp_r3->unkE0 = 0U;
		temp_r3->unkE8 = 0U;
		temp_r3->unkEC = 0;
		temp_r3->unkF0 = 0;
		temp_r3->unkF4 = 0;
		temp_r3->unkD4 = 0;
		temp_r3->unkDC = 1.0f;
		temp_r29       = lbl_8_bss_1BD0[temp_r3->unkD0];
		if (temp_r29 != 0U) {
			if ((u32)temp_r3->unkE0 == 0U) {
				temp_r3->unkE0 = fn_80150588(temp_r29);
				if ((u32)temp_r3->unkE0 != 0U) {
					fn_8005D5C8(0x10);
					var_r0 = fn_80057644(0x14);
					if (var_r0 != 0U) {
						var_r0 = fn_80119A18(temp_r3->unkE0);
					}
					temp_r3->unkE4 = var_r0;
				}
			}
			var_r30 = 0;
			var_r28 = 0;
			do {
				if (*(u32*)((u8*)temp_r3 + var_r28 + 0xE8) == 0U) {
					temp_r0                         = var_r28 + 0xE8;
					*(u32*)((u8*)temp_r3 + temp_r0) = fn_80150588(temp_r29);
					if (*(u32*)((u8*)temp_r3 + temp_r0) != 0U) {
						fn_8005D5C8(0x10);
						var_r4 = fn_80057644(0x14);
						if (var_r4 != 0U) {
							var_r4 = fn_80119A18(*(u32*)((u8*)temp_r3 + var_r28 + 0xE8));
						}
						*(u32*)((u8*)temp_r3 + var_r28 + 0xF8) = var_r4;
					}
				}
				var_r28 += 4;
				var_r30 += 1;
			} while (var_r30 < 4);
		}
	}
}

void s11spiderObjectRegister(void)
{
	s32 flags;

	M2C_FIELD(&s11spiderObjectEntry, s32*, 0x14)            = 0;
	M2C_FIELD(&s11spiderObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&s11spiderObjectEntry, M2C_UNK**, 0)          = &s11spiderObjectDisplayName;
	M2C_FIELD(&s11spiderObjectEntry, void (**)(M2C_UNK), 4) = s11spiderObjectLoad;
	M2C_FIELD(&s11spiderObjectEntry, void (**)(), 8)        = s11spiderObjectUnload;
	M2C_FIELD(&s11spiderObjectEntry, void (**)(), 0xC)      = s11spiderObjectCreate;
	M2C_FIELD(&s11spiderObjectEntry, s32*, 0x10)            = 0;
	flags                                                   = 0x20000;
	M2C_FIELD(&s11spiderObjectEntry, s32*, 0x14)            = flags;
	M2C_FIELD(&s11spiderObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&s11spiderObjectEntry, s8*, 0x20)             = 0x1E;
	M2C_FIELD(&s11spiderObjectEntry, s16*, 0x1C)            = 0x1189;
	M2C_FIELD(&s11spiderObjectEntry, s16*, 0x1E)            = 2;
	M2C_FIELD(&s11spiderObjectEntry, s8*, 0x21)             = 0;
	M2C_FIELD(&s11spiderObjectEntry, M2C_UNK**, 0x24)       = &s11spiderObjectFieldTypes;
	M2C_FIELD(&s11spiderObjectEntry, M2C_UNK**, 0x28)       = &s11spiderObjectFieldNames;
	if (&s11spiderObjectFieldTypes != NULL) {
		M2C_FIELD(&s11spiderObjectEntry, s32*, 0x14) = flags | 8;
		return;
	}
	M2C_FIELD(&s11spiderObjectEntry, s32*, 0x14) = flags & ~8;
}

__declspec(section ".ctors") void (*const s11spiderObjectCtorEntry)(void) = s11spiderObjectRegister;
}
