#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(u32)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

static f32 lbl_8_rodata_1F40;

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
	/* 0x30 */ char pad30[0x10];
	/* 0x40 */ void* unk40;      /* inferred */
	/* 0x44 */ char pad44[0x74]; /* maybe part of unk40[0x1E]? */
	/* 0xB8 */ f32 unkB8;        /* inferred */
	/* 0xBC */ f32 unkBC;        /* inferred */
	/* 0xC0 */ f32 unkC0;        /* inferred */
	/* 0xC4 */ s32 unkC4;        /* inferred */
	/* 0xC8 */ s32 unkC8;        /* inferred */
	/* 0xCC */ s32 unkCC;        /* inferred */
	/* 0xD0 */ f32 unkD0;        /* inferred */
	/* 0xD4 */ s32 unkD4;        /* inferred */
	/* 0xD8 */ void* unkD8;      /* inferred */
	/* 0xDC */ void* unkDC;      /* inferred */
	/* 0xE0 */ void* unkE0;      /* inferred */
} TObject;                       /* size >= 0xE4 */

extern "C" {

void* __ct__7TObjectFP7TObject(...);                               /* extern */
void* __dt__7TObjectFv(...);                                       /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                             /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                             /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                                /* extern */
u32 fn_80018A34(s32, M2C_UNK);                                     /* extern */
M2C_UNK fn_80021384(M2C_UNK*, ...);                                /* extern */
M2C_UNK fn_8003BC38(void*);                                        /* extern */
M2C_UNK fn_8003C200(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);         /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                                     /* extern */
s32 fn_8005B8BC(s32);                                              /* extern */
s32 fn_8005B8D8(M2C_UNK*);                                         /* extern */
s32 fn_8005B9F0(s32);                                              /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                                     /* extern */
M2C_UNK fn_8005D5C8(s32, s32);                                     /* extern */
M2C_UNK fn_800B4A38(M2C_UNK, f32*, M2C_UNK, M2C_UNK, s8, M2C_UNK); /* extern */
u32 fn_800BB0D4(s32, s32, M2C_UNK*);                               /* extern */
u32 fn_800BB92C(s32, s32, M2C_UNK*);                               /* extern */
s32 fn_800BC6CC(s32, M2C_UNK*);                                    /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                                /* extern */
f32 fn_800D7AE4(s32);                                              /* extern */
f32 fn_800D7B00(s32);                                              /* extern */
M2C_UNK fn_8013F3A4(void*);                                        /* extern */
void* fn_8013F484(...);                                            /* extern */
M2C_UNK fn_8013FC30(void*);                                        /* extern */
M2C_UNK fn_8014FFBC(void*, void* (*)(void*, s32), void*);          /* extern */
s32 fn_80150588(u32);                                              /* extern */
M2C_UNK fn_80150958(...);                                          /* extern */
M2C_UNK fn_8015BB08(s32, void*);                                   /* extern */
M2C_UNK fn_8015BBF8(s32);                                          /* extern */
M2C_UNK fn_80195790(s32, M2C_UNK*, M2C_UNK, f32, f32);             /* extern */
M2C_UNK fn_8019E880(s32);                                          /* extern */
M2C_UNK fn_8019EB10(s32, s32 (*)(s32, void**), void**);            /* extern */
M2C_UNK fn_8019EB94(s32, f32*, M2C_UNK);                           /* extern */
M2C_UNK fn_8019EC30(s32, f32*, M2C_UNK);                           /* extern */
M2C_UNK fn_801A4C84();                                             /* extern */
M2C_UNK fn_8020C2D8();                                             /* extern */
M2C_UNK fn_8020C72C(void**, u32);                                  /* extern */
M2C_UNK fn_8020CC18(void**, M2C_UNK*, f32);                        /* extern */
M2C_UNK fn_8020D02C(void**, f32, f32);                             /* extern */
M2C_UNK fn_80226440(void*, s32);                                   /* extern */
u32 fn_80226468(s32);                                              /* extern */
TObject* fn_8_C46C4(TObject* arg0, TObject* arg1);                 /* static */
void* fn_8_C4AA8(void* arg0, s32 arg1);                            /* static */
s32 fn_8_C4B58(s32 arg0, void** arg1);                             /* static */
void treeObjectCreate();                                           /* static */
void treeObjectLoad();                                             /* static */
void treeObjectUnload();                                           /* static */
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_802FF5A0;
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u32 lbl_8042C388;
static u32 lbl_8_data_18298 = 0U;
static M2C_UNK lbl_8_data_182A0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000182AF_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_182B0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000182BF_data; /* unable to generate initializer: unknown type */
static M2C_UNK treeObjectFieldNames; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_182C8;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000182D9_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_182DC[2] = { &lbl_8_data_182B0, &lbl_8_data_182C8 };
static M2C_UNK lbl_8_data_182E4;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18314;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001831D_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_18320 = &lbl_8_data_18314;
static M2C_UNK lbl_8_data_18324;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18360;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18370;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018381_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18384;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018395_data;  /* unable to generate initializer: unknown type */
static M2C_UNK treeObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK treeObjectFieldTypes;  /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000183A7_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_183A8;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000183BD_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_183C0;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000183D5_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_183D8;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000183ED_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_183F0;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018405_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18408;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001841D_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18420;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018435_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18438;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001844D_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18450;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018465_data;  /* unable to generate initializer: unknown type */
static u8 lbl_8_bss_1C40;
static M2C_UNK gap_05_00001C41_bss;
static u32 lbl_8_bss_1C44;
static M2C_UNK treeObjectEntry;
static M2C_UNK grass2ObjectEntry;

void fn_8_C3FF8(void* arg0)
{
	M2C_UNK* temp_r4;

	if ((s32)M2C_FIELD(arg0, s32*, 0xD4) == 1) {
		M2C_FIELD(M2C_FIELD(arg0, M2C_UNK**, 0x40), f32*, 0xC)
		    = (f32)(-M2C_FIELD(&lbl_8_data_182E4, f32*, 0xC) * M2C_FIELD(arg0, f32*, 0xD0));
	} else {
		M2C_FIELD(M2C_FIELD(arg0, M2C_UNK**, 0x40), f32*, 0xC)
		    = (f32)(M2C_FIELD(&lbl_8_data_182E4, f32*, 0xC) * M2C_FIELD(arg0, f32*, 0xD0));
	}
	M2C_FIELD(M2C_FIELD(arg0, M2C_UNK**, 0x40), f32*, 0x14)
	    = (f32)(M2C_FIELD(&lbl_8_data_182E4, f32*, 0x14) * M2C_FIELD(arg0, f32*, 0xD0));
	temp_r4 = M2C_FIELD(arg0, M2C_UNK**, 0x40);
	M2C_FIELD(temp_r4, f32*, 0x18)
	    = (f32)(M2C_FIELD(&lbl_8_data_182E4, f32*, 0x18) * M2C_FIELD(arg0, f32*, 0xD0));
	fn_80021384((M2C_UNK*)((u8*)arg0 + 0x30), temp_r4, &lbl_8_data_182E4,
	    M2C_FIELD(&lbl_8_data_182E4, f32*, 0x18));
}

void fn_8_C4098(void* arg0)
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
	M2C_FIELD(arg0, s32*, 0xD4) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 4);
	M2C_FIELD(arg0, f32*, 0xD0) = (f32)(1.0f + M2C_FIELD(temp_r5, f32*, 0));
}

void fn_8_C4108(void* arg0)
{
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f30;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	s32 temp_r0;
	s32 temp_r28;
	s32 var_r31;
	void** temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r4;
	void* var_r27;

	if ((fn_8005B9F0((s32)((u8*)arg0 + 0x28)) != 0)
	    || (fn_8005B8BC((s32)((u8*)arg0 + 0x28)) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	temp_r3  = M2C_FIELD(M2C_FIELD(arg0, void**, 0xE0), void***, 0x20);
	temp_f30 = 60.0f * M2C_FIELD(*temp_r3, f32*, 0xC);
	temp_r0  = M2C_FIELD(lbl_8042C180, s32*, 0x30);
	temp_f31 = (f32)temp_r0 - (temp_f30 * (f32)(s32)((f32)temp_r0 / temp_f30));
	fn_8020D02C(temp_r3, temp_f31 / 60.0f, 60.0f);
	fn_8013FC30(M2C_FIELD(arg0, void**, 0xE0));
	if (fn_8005B8D8((M2C_UNK*)((u8*)arg0 + 0x28)) != 0) {
		temp_r3_2                   = M2C_FIELD(arg0, void**, 0x28);
		temp_r4                     = M2C_FIELD(temp_r3_2, void**, 0x2C);
		M2C_FIELD(arg0, f32*, 0xB8) = (f32)M2C_FIELD(temp_r3_2, f32*, 0);
		M2C_FIELD(arg0, f32*, 0xBC) = (f32)M2C_FIELD(temp_r3_2, f32*, 4);
		M2C_FIELD(arg0, f32*, 0xC0) = (f32)M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3_3                   = M2C_FIELD(arg0, void**, 0x28);
		M2C_FIELD(arg0, s32*, 0xC4) = (s32)M2C_FIELD(temp_r3_3, s32*, 0xC);
		M2C_FIELD(arg0, s32*, 0xC8) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x10);
		M2C_FIELD(arg0, s32*, 0xCC) = (s32)M2C_FIELD(temp_r3_3, s32*, 0x14);
		var_r31                     = 0;
		M2C_FIELD(arg0, s32*, 0xCC) = 0;
		M2C_FIELD(arg0, s32*, 0xC4) = 0;
		M2C_FIELD(arg0, s32*, 0xD4) = (s32)(s8)M2C_FIELD(temp_r4, u8*, 4);
		M2C_FIELD(arg0, f32*, 0xD0) = (f32)(1.0f + M2C_FIELD(temp_r4, f32*, 0));
		temp_f0                     = M2C_FIELD(arg0, f32*, 0xD0);
		sp10                        = temp_f0;
		spC                         = temp_f0;
		sp8                         = temp_f0;
		var_r27                     = arg0;
		do {
			temp_r28 = M2C_FIELD(M2C_FIELD(var_r27, void**, 0xD8), s32*, 4);
			fn_8019EB94(temp_r28, (f32*)((u8*)arg0 + 0xB8), 0);
			temp_f31_2 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
			fn_80195790(temp_r28 + 0x10, &lbl_80239984, 1,
			    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f31_2);
			fn_8019E880(temp_r28);
			if ((s32)M2C_FIELD(arg0, s32*, 0xD4) == 1) {
				temp_f31_3 = fn_800D7B00(0x8000);
				fn_80195790(
				    temp_r28 + 0x10, &lbl_80239990, 1, 1.0f - fn_800D7AE4(0x8000), temp_f31_3);
				fn_8019E880(temp_r28);
			}
			fn_8019EC30(temp_r28, &sp8, 1);
			var_r27 = (u8*)var_r27 + 4;
			var_r31 += 1;
		} while (var_r31 < 2);
		return;
	}
	if (temp_f31 < temp_f30) {
		M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
		if (temp_f30 == (1.0f + temp_f31)) {
			sp14 = M2C_FIELD(arg0, f32*, 0xB8);
			sp18 = M2C_FIELD(arg0, f32*, 0xBC);
			sp1C = M2C_FIELD(arg0, f32*, 0xC0);
			sp18 += 15.0f * M2C_FIELD(arg0, f32*, 0xD0);
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x5A17, &sp14, 0, 1, (s8)lbl_8_bss_1C40, 0);
			}
		}
	}
	M2C_FIELD(arg0, f32*, 0xAC) = (f32)M2C_FIELD(arg0, f32*, 0x90);
	M2C_FIELD(arg0, f32*, 0xB0) = (f32)M2C_FIELD(arg0, f32*, 0x94);
	M2C_FIELD(arg0, f32*, 0xB4) = (f32)M2C_FIELD(arg0, f32*, 0x98);
	M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0xB8);
	M2C_FIELD(arg0, f32*, 0x94) = (f32)M2C_FIELD(arg0, f32*, 0xBC);
	M2C_FIELD(arg0, f32*, 0x98) = (f32)M2C_FIELD(arg0, f32*, 0xC0);
	M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(arg0, s32*, 0xC4);
	M2C_FIELD(arg0, s32*, 0xA0) = (s32)M2C_FIELD(arg0, s32*, 0xC8);
	M2C_FIELD(arg0, s32*, 0xA4) = (s32)M2C_FIELD(arg0, s32*, 0xCC);
	fn_8003BC38((void*)((u8*)arg0 + 0x30));
}

void fn_8_C4474(void* arg0)
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
		temp_r28 = M2C_FIELD(M2C_FIELD(var_r30, void**, 0xD8), s32*, 4);
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
	} while (var_r29 < 2);
}

TObject* fn_8_C45B4(TObject* arg0, s16 arg1)
{
	TObject* var_r31;
	s32 var_r30;

	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_18324;
		arg0->unk2C = &lbl_8_data_18324 + 0x2C;
		var_r30     = 0;
		var_r31     = arg0;
		do {
			if ((void*)var_r31->unkD8 != NULL) {
				if (var_r30 == 0) {
					fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
				} else {
					fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284));
				}
				fn_80150958(var_r31->unkD8);
				var_r31->unkD8 = NULL;
			}
			var_r31 += 4;
			var_r30 += 1;
		} while (var_r30 < 2);
		dtor_8003C52C((void*)((u8*)arg0 + 0x30), 0);
		dtor_8005BD3C((void*)((u8*)arg0 + 0x28), 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_C46C4(TObject* arg0, TObject* arg1)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	void* sp8;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	s32 temp_r31;
	s32 var_r27;
	s32 var_r28_2;
	s32 var_r30;
	s32 var_r31;
	u32* var_r28;
	void* temp_r30;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r4;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	fn_8003C618(&arg0->unk30);
	arg0->unk18 = &lbl_8_data_18324;
	arg0->unk2C = &lbl_8_data_18324 + 0x2C;
	arg0->unk0  = lbl_8_data_18320;
	arg0->unk1E = 0xE4;
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
	arg0->unkD4 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 4);
	arg0->unkD0 = 1.0f + M2C_FIELD(temp_r4, f32*, 0);
	var_r30     = 0;
	var_r28     = &lbl_8_data_18298;
	do {
		*(u32*)((u8*)arg0 + var_r31 + 0xD8) = fn_80150588(*var_r28);
		if (var_r30 == 0) {
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C), arg0->unkD8);
		} else {
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284), arg0->unkDC);
		}
		fn_8005D5C8(*(u32*)((u8*)arg0 + var_r31 + 0xD8),
		    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U) + 4);
		var_r28 += 4;
		var_r31 += 4;
		var_r30 += 1;
	} while (var_r30 < 2);
	temp_r30  = arg0->unkDC;
	sp8       = NULL;
	temp_r3_3 = fn_8013F484(M2C_FIELD(temp_r30, s32*, 4));
	sp8       = temp_r3_3;
	if (temp_r3_3 == NULL) {
		fn_8019EB10(M2C_FIELD(temp_r30, s32*, 4), fn_8_C4B58, &sp8);
	}
	arg0->unkE0 = sp8;
	fn_8014FFBC(arg0->unkDC, fn_8_C4AA8, arg0->unkE0);
	temp_r3_4                     = arg0->unkE0;
	M2C_FIELD(temp_r3_4, s32*, 0) = (s32)(M2C_FIELD(temp_r3_4, s32*, 0) | 0x3000);
	fn_8020C72C(M2C_FIELD(arg0->unkE0, void***, 0x20), lbl_8_bss_1C44);
	fn_8013F3A4(arg0->unkE0);
	fn_8013FC30(arg0->unkE0);
	fn_8020D02C(M2C_FIELD(arg0->unkE0, void***, 0x20), (f32)(u32)&lbl_8_rodata_1F40, 0.0f);
	fn_8020CC18(M2C_FIELD(arg0->unkE0, void***, 0x20), (M2C_UNK*)&lbl_8_rodata_1F40, 0.0f);
	temp_f0   = arg0->unkD0;
	sp14      = temp_f0;
	sp10      = temp_f0;
	spC       = temp_f0;
	var_r28_2 = 0;
	var_r27   = 0;
	do {
		temp_r31 = M2C_FIELD(*(u32*)((u8*)arg0 + var_r27 + 0xD8), s32*, 4);
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
		var_r28_2 += 1;
	} while (var_r28_2 < 2);
	if (fn_8005B8D8(&arg0->unk28) == 0) {
		fn_8003C200(&arg0->unk30, &lbl_8_data_182E4, 1, 4);
		if ((s32)arg0->unkD4 == 1) {
			M2C_FIELD(arg0->unk40, f32*, 0xC)
			    = (f32)(-M2C_FIELD(&lbl_8_data_182E4, f32*, 0xC) * arg0->unkD0);
		} else {
			M2C_FIELD(arg0->unk40, f32*, 0xC)
			    = (f32)(M2C_FIELD(&lbl_8_data_182E4, f32*, 0xC) * arg0->unkD0);
		}
		M2C_FIELD(arg0->unk40, f32*, 0x14)
		    = (f32)(M2C_FIELD(&lbl_8_data_182E4, f32*, 0x14) * arg0->unkD0);
		M2C_FIELD(arg0->unk40, f32*, 0x18)
		    = (f32)(M2C_FIELD(&lbl_8_data_182E4, f32*, 0x18) * arg0->unkD0);
		fn_80021384(&arg0->unk30, &lbl_8_data_182E4,
		    M2C_BITWISE(M2C_UNK*, M2C_FIELD(&lbl_8_data_182E4, f32*, 0x18)));
	}
	return arg0;
}

void* fn_8_C4AA8(void* arg0, s32 arg1)
{
	if (fn_80226468(M2C_FIELD(arg0, s32*, 0x18)) != 0U) {
		fn_80226440(arg0, arg1);
	}
	return arg0;
}

void* fn_8_C4AFC(void* arg0)
{
	void* sp8;
	void* temp_r3;

	sp8     = NULL;
	temp_r3 = fn_8013F484(M2C_FIELD(arg0, s32*, 4));
	sp8     = temp_r3;
	if (temp_r3 == NULL) {
		fn_8019EB10(M2C_FIELD(arg0, s32*, 4), fn_8_C4B58, &sp8);
	}
	return sp8;
}

s32 fn_8_C4B58(s32 arg0, void** arg1)
{
	void* temp_r3;

	temp_r3 = fn_8013F484();
	if (temp_r3 == NULL) {
		fn_8019EB10(arg0, fn_8_C4B58, arg1);
		return arg0;
	}
	*arg1 = temp_r3;
	return 0;
}

void fn_8_C4BBC(void* arg1)
{
	void* temp_r3;

	temp_r3 = M2C_FIELD(arg1, void**, 0x2C);
	if ((s8)M2C_FIELD(temp_r3, u8*, 4) < 0) {
		M2C_FIELD(temp_r3, u8*, 4) = 0U;
	}
	if ((s8)M2C_FIELD(temp_r3, u8*, 4) > 1) {
		M2C_FIELD(temp_r3, u8*, 4) = 1U;
	}
	M2C_FIELD(&treeObjectFieldNames, M2C_UNK**, 4)
	    = (M2C_UNK*)lbl_8_data_182DC[(s8)M2C_FIELD(temp_r3, u8*, 4)];
}

void treeObjectUnload(void)
{
	s32 var_r29;
	u32* var_r30;

	var_r29 = 0;
	var_r30 = &lbl_8_data_18298;
	do {
		if ((u32)*var_r30 != 0U) {
			fn_80150958();
			*var_r30 = 0U;
		}
		var_r30 += 4;
		var_r29 += 1;
	} while (var_r29 < 2);
	if ((u32)lbl_8_bss_1C44 != 0U) {
		fn_8020C2D8();
		lbl_8_bss_1C44 = 0U;
	}
}

void treeObjectLoad(void)
{
	s32 temp_r31;

	if ((u32)M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18) != 0U) {
		fn_801A4C84();
		temp_r31 = M2C_FIELD(lbl_8042C298, s32*, 0xA50);
		fn_800BC9F4(temp_r31, &lbl_802FF5A0);
		M2C_FIELD(&lbl_8_data_18298, u32*, 0)
		    = fn_800BB92C(temp_r31, fn_800BC6CC(temp_r31, &lbl_8_data_18360), &lbl_802FF5A0);
		M2C_FIELD(&lbl_8_data_18298, u32*, 4)
		    = fn_800BB92C(temp_r31, fn_800BC6CC(temp_r31, &lbl_8_data_18370), &lbl_802FF5A0);
		lbl_8_bss_1C44
		    = fn_800BB0D4(temp_r31, fn_800BC6CC(temp_r31, &lbl_8_data_18384), &lbl_802FF5A0);
	}
}

void treeObjectCreate(void)
{
	TObject* object = (TObject*)fn_80018A34(lbl_8042C148, 0xE4);
	if (object != NULL) {
		fn_8_C46C4(object, lbl_8042C110);
	}
}

void treeObjectRegister(void)
{
	M2C_FIELD(&treeObjectEntry, s32*, 0x14)       = 0;
	M2C_FIELD(&treeObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&treeObjectEntry, M2C_UNK**, 0)     = &treeObjectDisplayName;
	M2C_FIELD(&treeObjectEntry, void (**)(), 4)   = treeObjectLoad;
	M2C_FIELD(&treeObjectEntry, void (**)(), 8)   = treeObjectUnload;
	M2C_FIELD(&treeObjectEntry, void (**)(), 0xC) = treeObjectCreate;
	M2C_FIELD(&treeObjectEntry, s32*, 0x10)       = 0;
	M2C_FIELD(&treeObjectEntry, s32*, 0x14)       = 0x20000;
	M2C_FIELD(&treeObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&treeObjectEntry, s8*, 0x20)        = 0x1E;
	M2C_FIELD(&treeObjectEntry, s16*, 0x1C)       = 0x118A;
	M2C_FIELD(&treeObjectEntry, s16*, 0x1E)       = 2;
	M2C_FIELD(&treeObjectEntry, s8*, 0x21)        = 0;
	M2C_FIELD(&treeObjectEntry, M2C_UNK**, 0x24)  = &treeObjectFieldTypes;
	M2C_FIELD(&treeObjectEntry, M2C_UNK**, 0x28)  = &treeObjectFieldNames;
	if (&treeObjectFieldTypes != NULL) {
		M2C_FIELD(&treeObjectEntry, s32*, 0x14) = 0x20008;
		return;
	}
	M2C_FIELD(&treeObjectEntry, s32*, 0x14) = 0x20000;
}

__declspec(section ".ctors") void (*const treeObjectCtorEntry)(void) = treeObjectRegister;
}
