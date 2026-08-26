#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))

typedef struct TObject {
	/* 0x00 */ s32 unk0;        /* inferred */
	/* 0x04 */ char pad4[0x14]; /* maybe part of unk0[6]? */
	/* 0x18 */ M2C_UNK* unk18;  /* inferred */
	/* 0x1C */ char pad1C[2];
	/* 0x1E */ s16 unk1E;     /* inferred */
	/* 0x20 */ char pad20[8]; /* maybe part of unk1E[5]? */
	/* 0x28 */ M2C_UNK unk28; /* inferred */
	/* 0x28 */ char pad28[4];
	/* 0x2C */ void* unk2C; /* inferred */
	/* 0x30 */ f32 unk30;   /* inferred */
	/* 0x34 */ f32 unk34;   /* inferred */
	/* 0x38 */ f32 unk38;   /* inferred */
	/* 0x3C */ s32 unk3C;   /* inferred */
	/* 0x40 */ s32 unk40;   /* inferred */
	/* 0x44 */ s32 unk44;   /* inferred */
	/* 0x48 */ s32 unk48;   /* inferred */
	/* 0x4C */ s32 unk4C;   /* inferred */
	/* 0x50 */ s32 unk50;   /* inferred */
	/* 0x54 */ f32 unk54;   /* inferred */
	/* 0x58 */ s32 unk58;   /* inferred */
	/* 0x5C */ void* unk5C; /* inferred */
} TObject;                  /* size >= 0x60 */

void* __ct__7TObjectFP7TObject(TObject* self, TObject* arg0); /* extern */
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);       /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                        /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                           /* extern */
TObject* fn_80018A34(s32, M2C_UNK);                           /* extern */
s32 fn_8005B8BC(s32);                                         /* extern */
s32 fn_8005B9F0(s32);                                         /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                                /* extern */
M2C_UNK fn_8005D5C8(void*, M2C_UNK);                          /* extern */
void* fn_800BB92C(s32, s32, M2C_UNK*);                        /* extern */
s32 fn_800BC6CC(s32, s32);                                    /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                           /* extern */
M2C_UNK fn_800BDF30();                                        /* extern */
M2C_UNK fn_800BE1F4(u32);                                     /* extern */
M2C_UNK fn_800BE274(u32);                                     /* extern */
f32 fn_800D7AE4(s32);                                         /* extern */
f32 fn_800D7B00(s32);                                         /* extern */
void* fn_80150588(void*);                                     /* extern */
M2C_UNK fn_80150958(void*);                                   /* extern */
M2C_UNK fn_8015BB08(s32, void*);                              /* extern */
M2C_UNK fn_8015BBF8(s32);                                     /* extern */
M2C_UNK fn_80195790(s32, M2C_UNK*, M2C_UNK, f32, f32);        /* extern */
M2C_UNK fn_8019E880(s32);                                     /* extern */
M2C_UNK fn_8019EB94(s32, f32*, M2C_UNK);                      /* extern */
M2C_UNK fn_8019EC30(s32, f32*, M2C_UNK);                      /* extern */
M2C_UNK fn_801A4C84();                                        /* extern */
M2C_UNK fn_8_964DC(s32);                                      /* extern */
extern M2C_UNK lbl_80239978;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_802FF5A0;
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern void* lbl_8_bss_16D0;
extern s32 lbl_8_data_15370;
extern s32 lbl_8_data_153EC;
extern M2C_UNK lbl_8_data_153F0;
extern f32 lbl_8_rodata_166C;
extern f32 lbl_8_rodata_1670;
extern M2C_UNK s12celestialObjectDisplayName;
extern M2C_UNK s12celestialObjectEntry;
extern M2C_UNK s12celestialObjectFieldNames;
extern M2C_UNK s12celestialObjectFieldTypes;

void fn_8_96760(s32 arg0)
{
	fn_8_964DC(arg0 - 0x28);
}

void fn_8_96768(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0x5C) != NULL) {
		fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x72A0));
		fn_80150958(M2C_FIELD(arg0, void**, 0x5C));
		M2C_FIELD(arg0, void**, 0x5C) = NULL;
	}
}

void fn_8_967C0(void* arg0, s32 arg1)
{
	if ((void*)M2C_FIELD(arg0, void**, 0x5C) == NULL) {
		M2C_FIELD(arg0, void**, 0x5C) = fn_80150588((&lbl_8_bss_16D0)[arg1]);
		fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x72A0), M2C_FIELD(arg0, void**, 0x5C));
		fn_8005D5C8(M2C_FIELD(arg0, void**, 0x5C), 0x10);
	}
}

void fn_8_96830(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	s32 temp_r31;

	temp_f0  = M2C_FIELD(arg0, f32*, 0x54);
	sp10     = temp_f0;
	spC      = temp_f0;
	sp8      = temp_f0;
	temp_r31 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x5C), s32*, 4);
	fn_8019EB94(temp_r31, (f32*)((u8*)arg0 + 0x30), 0);
	temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x44));
	fn_80195790(temp_r31 + 0x10, &lbl_80239990, 1,
	    lbl_8_rodata_166C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x44)), temp_f31);
	fn_8019E880(temp_r31);
	temp_f31_2 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x40));
	fn_80195790(temp_r31 + 0x10, &lbl_80239984, 1,
	    lbl_8_rodata_166C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x40)), temp_f31_2);
	fn_8019E880(temp_r31);
	temp_f31_3 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x3C));
	fn_80195790(temp_r31 + 0x10, &lbl_80239978, 1,
	    lbl_8_rodata_166C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x3C)), temp_f31_3);
	fn_8019E880(temp_r31);
	fn_8019EC30(temp_r31, &sp8, 1);
}

void fn_8_96974(void* arg0)
{
	void* temp_r4;
	void* temp_r5;

	temp_r4                     = M2C_FIELD(arg0, void**, 0x28);
	temp_r5                     = M2C_FIELD(temp_r4, void**, 0x2C);
	M2C_FIELD(arg0, f32*, 0x30) = (f32)M2C_FIELD(temp_r4, f32*, 0);
	M2C_FIELD(arg0, f32*, 0x34) = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x38) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	M2C_FIELD(arg0, s32*, 0x58) = (s32)M2C_FIELD(temp_r5, s32*, 0);
	M2C_FIELD(arg0, s32*, 0x48) = (s32)(lbl_8_rodata_1670 * M2C_FIELD(temp_r5, f32*, 4));
	M2C_FIELD(arg0, s32*, 0x4C) = (s32)(lbl_8_rodata_1670 * M2C_FIELD(temp_r5, f32*, 8));
	M2C_FIELD(arg0, s32*, 0x50) = (s32)(lbl_8_rodata_1670 * M2C_FIELD(temp_r5, f32*, 0xC));
	M2C_FIELD(arg0, f32*, 0x54) = (f32)(lbl_8_rodata_166C + M2C_FIELD(temp_r5, f32*, 0x10));
}

void fn_8_96A14(void) { }

void fn_8_96A18(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	s32 temp_r30;

	if ((fn_8005B9F0((s32)((u8*)arg0 + 0x28)) != 0)
	    || (fn_8005B8BC((s32)((u8*)arg0 + 0x28)) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	M2C_FIELD(arg0, s32*, 0x3C) = (s32)(M2C_FIELD(arg0, s32*, 0x3C) + M2C_FIELD(arg0, s32*, 0x48));
	M2C_FIELD(arg0, s32*, 0x40) = (s32)(M2C_FIELD(arg0, s32*, 0x40) + M2C_FIELD(arg0, s32*, 0x4C));
	M2C_FIELD(arg0, s32*, 0x44) = (s32)(M2C_FIELD(arg0, s32*, 0x44) + M2C_FIELD(arg0, s32*, 0x50));
	temp_f0                     = M2C_FIELD(arg0, f32*, 0x54);
	sp10                        = temp_f0;
	spC                         = temp_f0;
	sp8                         = temp_f0;
	temp_r30                    = M2C_FIELD(M2C_FIELD(arg0, void**, 0x5C), s32*, 4);
	fn_8019EB94(temp_r30, (f32*)((u8*)arg0 + 0x30), 0);
	temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x44));
	fn_80195790(temp_r30 + 0x10, &lbl_80239990, 1,
	    lbl_8_rodata_166C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x44)), temp_f31);
	fn_8019E880(temp_r30);
	temp_f31_2 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x40));
	fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1,
	    lbl_8_rodata_166C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x40)), temp_f31_2);
	fn_8019E880(temp_r30);
	temp_f31_3 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x3C));
	fn_80195790(temp_r30 + 0x10, &lbl_80239978, 1,
	    lbl_8_rodata_166C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x3C)), temp_f31_3);
	fn_8019E880(temp_r30);
	fn_8019EC30(temp_r30, &sp8, 1);
}

TObject* fn_8_96BC0(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_153F0;
		arg0->unk2C = &lbl_8_data_153F0 + 0x2C;
		if ((void*)arg0->unk5C != NULL) {
			fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x72A0));
			fn_80150958(arg0->unk5C);
			arg0->unk5C = NULL;
		}
		dtor_8005BD3C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_96C7C(TObject* arg0, TObject* arg1)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	s32 temp_r30;
	void* temp_r3;
	void* temp_r5;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	arg0->unk18 = &lbl_8_data_153F0;
	arg0->unk2C = &lbl_8_data_153F0 + 0x2C;
	arg0->unk0  = lbl_8_data_153EC;
	arg0->unk1E = 0x60;
	arg0->unk50 = 0;
	arg0->unk4C = 0;
	arg0->unk48 = 0;
	temp_r3     = M2C_FIELD(arg0, void**, 0x28);
	temp_r5     = M2C_FIELD(temp_r3, void**, 0x2C);
	arg0->unk30 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unk34 = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unk38 = M2C_FIELD(temp_r3, f32*, 8);
	arg0->unk58 = M2C_FIELD(temp_r5, s32*, 0);
	arg0->unk48 = (s32)(lbl_8_rodata_1670 * M2C_FIELD(temp_r5, f32*, 4));
	arg0->unk4C = (s32)(lbl_8_rodata_1670 * M2C_FIELD(temp_r5, f32*, 8));
	arg0->unk50 = (s32)(lbl_8_rodata_1670 * M2C_FIELD(temp_r5, f32*, 0xC));
	arg0->unk54 = lbl_8_rodata_166C + M2C_FIELD(temp_r5, f32*, 0x10);
	arg0->unk5C = NULL;
	if ((void*)arg0->unk5C == NULL) {
		arg0->unk5C = fn_80150588((&lbl_8_bss_16D0)[arg0->unk58]);
		fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x72A0), arg0->unk5C);
		fn_8005D5C8(arg0->unk5C, 0x10);
	}
	temp_f0  = arg0->unk54;
	sp10     = temp_f0;
	spC      = temp_f0;
	sp8      = temp_f0;
	temp_r30 = M2C_FIELD(arg0->unk5C, s32*, 4);
	fn_8019EB94(temp_r30, &arg0->unk30, 0);
	temp_f31 = fn_800D7B00(arg0->unk44);
	fn_80195790(
	    temp_r30 + 0x10, &lbl_80239990, 1, lbl_8_rodata_166C - fn_800D7AE4(arg0->unk44), temp_f31);
	fn_8019E880(temp_r30);
	temp_f31_2 = fn_800D7B00(arg0->unk40);
	fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1, lbl_8_rodata_166C - fn_800D7AE4(arg0->unk40),
	    temp_f31_2);
	fn_8019E880(temp_r30);
	temp_f31_3 = fn_800D7B00(arg0->unk3C);
	fn_80195790(temp_r30 + 0x10, &lbl_80239978, 1, lbl_8_rodata_166C - fn_800D7AE4(arg0->unk3C),
	    temp_f31_3);
	fn_8019E880(temp_r30);
	fn_8019EC30(temp_r30, &sp8, 1);
	return arg0;
}

void fn_8_96EF0(void* arg1)
{
	s32* temp_r3;
	s32 temp_r0;

	temp_r3 = M2C_FIELD(arg1, s32**, 0x2C);
	temp_r0 = *temp_r3;
	if (temp_r0 < 0) {
		*temp_r3 = 0;
		return;
	}
	if (temp_r0 >= 2) {
		*temp_r3 = 1;
	}
}

void s12celestialObjectUnload(void)
{
	s32 var_r29;
	void** var_r30;

	var_r29 = 0;
	var_r30 = &lbl_8_bss_16D0;
	do {
		fn_80150958(*var_r30);
		*var_r30 = NULL;
		var_r30 += 4;
		var_r29 += 1;
	} while (var_r29 < 2);
}

void s12celestialObjectLoad(M2C_UNK arg_sp0)
{
	s32* var_r29;
	s32 var_r27;
	void** var_r28;

	if ((u32)M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18) != 0U) {
		fn_801A4C84();
		fn_800BE274(M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18));
		fn_800BC9F4(M2C_FIELD(lbl_8042C298, s32*, 0xA50), &lbl_802FF5A0);
		var_r27 = 0;
		var_r29 = &lbl_8_data_15370;
		var_r28 = &lbl_8_bss_16D0;
		do {
			*var_r28 = fn_800BB92C(M2C_FIELD(lbl_8042C298, s32*, 0xA50),
			    fn_800BC6CC(M2C_FIELD(lbl_8042C298, s32*, 0xA50), *var_r29), &lbl_802FF5A0);
			if ((void*)*var_r28 != NULL) {
				fn_800BDF30();
			}
			var_r29 += 4;
			var_r28 += 4;
			var_r27 += 1;
		} while (var_r27 < 2);
		fn_800BE1F4(M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18));
	}
}

void s12celestialObjectCreate(void)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	TObject* temp_r3;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	s32 temp_r30;
	void* temp_r3_2;
	void* temp_r5;

	temp_r3 = fn_80018A34(lbl_8042C148, 0x60);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C110);
		fn_8005BE6C(&temp_r3->unk28);
		temp_r3->unk18 = &lbl_8_data_153F0;
		temp_r3->unk2C = &lbl_8_data_153F0 + 0x2C;
		temp_r3->unk0  = lbl_8_data_153EC;
		temp_r3->unk1E = 0x60;
		temp_r3->unk50 = 0;
		temp_r3->unk4C = 0;
		temp_r3->unk48 = 0;
		temp_r3_2      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r5        = M2C_FIELD(temp_r3_2, void**, 0x2C);
		temp_r3->unk30 = M2C_FIELD(temp_r3_2, f32*, 0);
		temp_r3->unk34 = M2C_FIELD(temp_r3_2, f32*, 4);
		temp_r3->unk38 = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3->unk58 = M2C_FIELD(temp_r5, s32*, 0);
		temp_r3->unk48 = (s32)(lbl_8_rodata_1670 * M2C_FIELD(temp_r5, f32*, 4));
		temp_r3->unk4C = (s32)(lbl_8_rodata_1670 * M2C_FIELD(temp_r5, f32*, 8));
		temp_r3->unk50 = (s32)(lbl_8_rodata_1670 * M2C_FIELD(temp_r5, f32*, 0xC));
		temp_r3->unk54 = lbl_8_rodata_166C + M2C_FIELD(temp_r5, f32*, 0x10);
		temp_r3->unk5C = NULL;
		if ((void*)temp_r3->unk5C == NULL) {
			temp_r3->unk5C = fn_80150588((&lbl_8_bss_16D0)[temp_r3->unk58]);
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x72A0), temp_r3->unk5C);
			fn_8005D5C8(temp_r3->unk5C, 0x10);
		}
		temp_f0  = temp_r3->unk54;
		sp10     = temp_f0;
		spC      = temp_f0;
		sp8      = temp_f0;
		temp_r30 = M2C_FIELD(temp_r3->unk5C, s32*, 4);
		fn_8019EB94(temp_r30, &temp_r3->unk30, 0);
		temp_f31 = fn_800D7B00(temp_r3->unk44);
		fn_80195790(temp_r30 + 0x10, &lbl_80239990, 1,
		    lbl_8_rodata_166C - fn_800D7AE4(temp_r3->unk44), temp_f31);
		fn_8019E880(temp_r30);
		temp_f31_2 = fn_800D7B00(temp_r3->unk40);
		fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1,
		    lbl_8_rodata_166C - fn_800D7AE4(temp_r3->unk40), temp_f31_2);
		fn_8019E880(temp_r30);
		temp_f31_3 = fn_800D7B00(temp_r3->unk3C);
		fn_80195790(temp_r30 + 0x10, &lbl_80239978, 1,
		    lbl_8_rodata_166C - fn_800D7AE4(temp_r3->unk3C), temp_f31_3);
		fn_8019E880(temp_r30);
		fn_8019EC30(temp_r30, &sp8, 1);
	}
}

void s12celestialObjectRegister(void)
{
	M2C_FIELD(&s12celestialObjectEntry, s32*, 0x14)            = 0;
	M2C_FIELD(&s12celestialObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&s12celestialObjectEntry, M2C_UNK**, 0)          = &s12celestialObjectDisplayName;
	M2C_FIELD(&s12celestialObjectEntry, void (**)(M2C_UNK), 4) = s12celestialObjectLoad;
	M2C_FIELD(&s12celestialObjectEntry, void (**)(), 8)        = s12celestialObjectUnload;
	M2C_FIELD(&s12celestialObjectEntry, void (**)(), 0xC)      = s12celestialObjectCreate;
	M2C_FIELD(&s12celestialObjectEntry, s32*, 0x10)            = 0;
	M2C_FIELD(&s12celestialObjectEntry, s32*, 0x14)            = 0x20000;
	M2C_FIELD(&s12celestialObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&s12celestialObjectEntry, s8*, 0x20)             = 0x1E;
	M2C_FIELD(&s12celestialObjectEntry, s16*, 0x1C)            = 0x1181;
	M2C_FIELD(&s12celestialObjectEntry, s16*, 0x1E)            = 2;
	M2C_FIELD(&s12celestialObjectEntry, s8*, 0x21)             = 0;
	M2C_FIELD(&s12celestialObjectEntry, M2C_UNK**, 0x24)       = &s12celestialObjectFieldTypes;
	M2C_FIELD(&s12celestialObjectEntry, M2C_UNK**, 0x28)       = &s12celestialObjectFieldNames;
	if (&s12celestialObjectFieldTypes != NULL) {
		M2C_FIELD(&s12celestialObjectEntry, s32*, 0x14) = 0x20008;
		return;
	}
	M2C_FIELD(&s12celestialObjectEntry, s32*, 0x14) = 0x20000;
}

void fn_8_973D4(s32 arg0)
{
	fn_8_96EF0((void*)(arg0 - 0x28));
}
