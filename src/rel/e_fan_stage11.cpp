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
	/* 0x2C */ void* unk2C; /* inferred */
	/* 0x30 */ f32 unk30;   /* inferred */
	/* 0x34 */ f32 unk34;   /* inferred */
	/* 0x38 */ f32 unk38;   /* inferred */
	/* 0x3C */ void* unk3C; /* inferred */
} TObject;                  /* size >= 0x40 */

extern "C" {

void* __ct__7TObjectFP7TObject(...);                   /* extern */
void* __dt__7TObjectFv(...);                           /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                 /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                    /* extern */
TObject* fn_80018A34(s32, M2C_UNK);                    /* extern */
s32 fn_8005B8BC(s32);                                  /* extern */
s32 fn_8005B9F0(s32);                                  /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                         /* extern */
M2C_UNK fn_8005D5C8(void*, s32);                       /* extern */
u32 fn_800BB92C(s32, s32, M2C_UNK*);                   /* extern */
s32 fn_800BC6CC(s32, M2C_UNK*);                        /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                    /* extern */
f32 fn_800D7AE4(s32);                                  /* extern */
f32 fn_800D7B00(s32);                                  /* extern */
void* fn_80150588(u32);                                /* extern */
M2C_UNK fn_80150958(...);                              /* extern */
M2C_UNK fn_8015BB08(s32, void*);                       /* extern */
M2C_UNK fn_8015BBF8(s32);                              /* extern */
M2C_UNK fn_80195790(s32, M2C_UNK*, M2C_UNK, f32, f32); /* extern */
M2C_UNK fn_8019E880(s32);                              /* extern */
M2C_UNK fn_8019EB94(s32, f32*, M2C_UNK);               /* extern */
M2C_UNK fn_801A4C84();                                 /* extern */
M2C_UNK fn_8_C33D0(s32);                               /* extern */
void s12fanObjectCreate();                             /* static */
void s12fanObjectLoad();                               /* static */
void s12fanObjectUnload();                             /* static */
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_802FF5A0;
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
static s32 lbl_8_data_18228 = 0x444;
static M2C_UNK lbl_8_data_1822C;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018237_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_18238 = &lbl_8_data_1822C;
static M2C_UNK lbl_8_data_1823C;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18274;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018283_data;    /* unable to generate initializer: unknown type */
static M2C_UNK s12fanObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018292_data;    /* unable to generate initializer: unknown type */
static u32 lbl_8_bss_1C10;
static M2C_UNK s12fanObjectEntry;

void fn_8_C37E0(s32 arg0)
{
	fn_8_C33D0(arg0 - 0x28);
}

void fn_8_C37E8(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0x3C) != NULL) {
		fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
		fn_80150958(M2C_FIELD(arg0, void**, 0x3C));
		M2C_FIELD(arg0, void**, 0x3C) = NULL;
	}
}

void fn_8_C3840(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0x3C) == NULL) {
		M2C_FIELD(arg0, void**, 0x3C) = fn_80150588(lbl_8_bss_1C10);
		fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C), M2C_FIELD(arg0, void**, 0x3C));
		fn_8005D5C8(M2C_FIELD(arg0, void**, 0x3C),
		    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U) + 4);
	}
}

void fn_8_C38BC(void* arg0)
{
	f32 temp_f31;
	s32 temp_r30;
	s32 temp_r31;

	temp_r30 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x3C), s32*, 4);
	fn_8019EB94(temp_r30, (f32*)((u8*)arg0 + 0x30), 0);
	temp_r31 = M2C_FIELD(lbl_8042C180, s32*, 0x30);
	temp_f31 = fn_800D7B00(lbl_8_data_18228 * temp_r31);
	fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1, 1.0f - fn_800D7AE4(lbl_8_data_18228 * temp_r31),
	    temp_f31);
	fn_8019E880(temp_r30);
}

void fn_8_C3980(void* arg0)
{
	void* temp_r4;

	temp_r4                     = M2C_FIELD(arg0, void**, 0x28);
	M2C_FIELD(arg0, f32*, 0x30) = (f32)M2C_FIELD(temp_r4, f32*, 0);
	M2C_FIELD(arg0, f32*, 0x34) = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x38) = (f32)M2C_FIELD(temp_r4, f32*, 8);
}

void fn_8_C39A0(void* arg0)
{
	f32 temp_f31;
	s32 temp_r30;
	s32 temp_r31;

	if ((fn_8005B9F0((s32)((u8*)arg0 + 0x28)) != 0)
	    || (fn_8005B8BC((s32)((u8*)arg0 + 0x28)) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	temp_r31 = M2C_FIELD(M2C_FIELD(arg0, void**, 0x3C), s32*, 4);
	fn_8019EB94(temp_r31, (f32*)((u8*)arg0 + 0x30), 0);
	temp_r30 = M2C_FIELD(lbl_8042C180, s32*, 0x30);
	temp_f31 = fn_800D7B00(lbl_8_data_18228 * temp_r30);
	fn_80195790(temp_r31 + 0x10, &lbl_80239984, 1, 1.0f - fn_800D7AE4(lbl_8_data_18228 * temp_r30),
	    temp_f31);
	fn_8019E880(temp_r31);
}

TObject* fn_8_C3A98(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_1823C;
		arg0->unk2C = &lbl_8_data_1823C + 0x2C;
		if ((void*)arg0->unk3C != NULL) {
			fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
			fn_80150958(arg0->unk3C);
			arg0->unk3C = NULL;
		}
		dtor_8005BD3C((void*)((u8*)arg0 + 0x28), 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_C3B54(TObject* arg0, TObject* arg1)
{
	f32 temp_f31;
	s32 temp_r29;
	s32 temp_r30;
	void* temp_r3;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	arg0->unk18 = &lbl_8_data_1823C;
	arg0->unk2C = &lbl_8_data_1823C + 0x2C;
	arg0->unk0  = lbl_8_data_18238;
	arg0->unk1E = 0x40;
	temp_r3     = M2C_FIELD(arg0, void**, 0x28);
	arg0->unk30 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unk34 = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unk38 = M2C_FIELD(temp_r3, f32*, 8);
	arg0->unk3C = NULL;
	if ((void*)arg0->unk3C == NULL) {
		arg0->unk3C = fn_80150588(lbl_8_bss_1C10);
		fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C), arg0->unk3C);
		fn_8005D5C8(arg0->unk3C,
		    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U) + 4);
	}
	temp_r30 = M2C_FIELD(arg0->unk3C, s32*, 4);
	fn_8019EB94(temp_r30, &arg0->unk30, 0);
	temp_r29 = M2C_FIELD(lbl_8042C180, s32*, 0x30);
	temp_f31 = fn_800D7B00(lbl_8_data_18228 * temp_r29);
	fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1, 1.0f - fn_800D7AE4(lbl_8_data_18228 * temp_r29),
	    temp_f31);
	fn_8019E880(temp_r30);
	return arg0;
}

void s12fanObjectUnload(void)
{
	if ((u32)lbl_8_bss_1C10 != 0U) {
		fn_80150958();
		lbl_8_bss_1C10 = 0U;
	}
}

void s12fanObjectLoad(void)
{
	if ((u32)M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18) != 0U) {
		fn_801A4C84();
		fn_800BC9F4(M2C_FIELD(lbl_8042C298, s32*, 0xA50), &lbl_802FF5A0);
		lbl_8_bss_1C10 = fn_800BB92C(M2C_FIELD(lbl_8042C298, s32*, 0xA50),
		    fn_800BC6CC(M2C_FIELD(lbl_8042C298, s32*, 0xA50), &lbl_8_data_18274), &lbl_802FF5A0);
	}
}

void s12fanObjectCreate(void)
{
	TObject* temp_r3;
	f32 temp_f31;
	s32 temp_r30;
	s32 temp_r31;
	void* temp_r3_2;

	temp_r3 = fn_80018A34(lbl_8042C148, 0x40);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C110);
		fn_8005BE6C(&temp_r3->unk28);
		temp_r3->unk18 = &lbl_8_data_1823C;
		temp_r3->unk2C = &lbl_8_data_1823C + 0x2C;
		temp_r3->unk0  = lbl_8_data_18238;
		temp_r3->unk1E = 0x40;
		temp_r3_2      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r3->unk30 = M2C_FIELD(temp_r3_2, f32*, 0);
		temp_r3->unk34 = M2C_FIELD(temp_r3_2, f32*, 4);
		temp_r3->unk38 = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3->unk3C = NULL;
		if ((void*)temp_r3->unk3C == NULL) {
			temp_r3->unk3C = fn_80150588(lbl_8_bss_1C10);
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C), temp_r3->unk3C);
			fn_8005D5C8(temp_r3->unk3C,
			    ((u32)(M2C_FIELD(M2C_FIELD(temp_r3, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
			        + 4);
		}
		temp_r30 = M2C_FIELD(temp_r3->unk3C, s32*, 4);
		fn_8019EB94(temp_r30, &temp_r3->unk30, 0);
		temp_r31 = M2C_FIELD(lbl_8042C180, s32*, 0x30);
		temp_f31 = fn_800D7B00(lbl_8_data_18228 * temp_r31);
		fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1,
		    1.0f - fn_800D7AE4(lbl_8_data_18228 * temp_r31), temp_f31);
		fn_8019E880(temp_r30);
	}
}

void s12fanObjectRegister(void)
{
	M2C_FIELD(&s12fanObjectEntry, s32*, 0x14)       = 0;
	M2C_FIELD(&s12fanObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&s12fanObjectEntry, M2C_UNK**, 0)     = &s12fanObjectDisplayName;
	M2C_FIELD(&s12fanObjectEntry, void (**)(), 4)   = s12fanObjectLoad;
	M2C_FIELD(&s12fanObjectEntry, void (**)(), 8)   = s12fanObjectUnload;
	M2C_FIELD(&s12fanObjectEntry, void (**)(), 0xC) = s12fanObjectCreate;
	M2C_FIELD(&s12fanObjectEntry, s32*, 0x10)       = 0;
	M2C_FIELD(&s12fanObjectEntry, s32*, 0x14)       = 0x20000;
	M2C_FIELD(&s12fanObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&s12fanObjectEntry, s8*, 0x20)        = 0x1E;
	M2C_FIELD(&s12fanObjectEntry, s16*, 0x1C)       = 0x1187;
	M2C_FIELD(&s12fanObjectEntry, s16*, 0x1E)       = 2;
	M2C_FIELD(&s12fanObjectEntry, s8*, 0x21)        = 0;
	M2C_FIELD(&s12fanObjectEntry, s32*, 0x24)       = 0;
	M2C_FIELD(&s12fanObjectEntry, s32*, 0x28)       = 0;
	if (0U != 0U) {
		M2C_FIELD(&s12fanObjectEntry, s32*, 0x14) = 0x20008;
		return;
	}
	M2C_FIELD(&s12fanObjectEntry, s32*, 0x14) = 0x20000;
}

__declspec(section ".ctors") void (*const s12fanObjectCtorEntry)(void) = s12fanObjectRegister;
}
