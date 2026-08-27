#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))

typedef struct TObject {
	/* 0x00 */ const char* unk0; /* inferred */
	/* 0x04 */ char pad4[0x14];  /* maybe part of unk0[6]? */
	/* 0x18 */ M2C_UNK* unk18;   /* inferred */
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
} TObject;                  /* size >= 0x48 */

void* __ct__7TObjectFP7TObject(TObject* self, TObject* arg0); /* extern */
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);       /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                        /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                           /* extern */
TObject* fn_80018A34(s32, M2C_UNK);                           /* extern */
s32 fn_8005B8BC(s32);                                         /* extern */
s32 fn_8005B9F0(s32);                                         /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                                /* extern */
M2C_UNK fn_800A31B8(s32);                                     /* extern */
M2C_UNK fn_8_9CAF0(s32);                                      /* extern */
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern f32 lbl_8_rodata_1704;
extern f32 lbl_8_rodata_170C;
extern f32 lbl_8_rodata_1710;
static M2C_UNK captureCollisionFieldNames; /* unable to generate initializer: unknown type */
static s32 lbl_8_data_159F4 = 0;
static s32 lbl_8_data_159F8 = 0xFF;
static M2C_UNK lbl_8_data_159FC; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_15A14 = "TObjCaptureCollision";
static M2C_UNK lbl_8_data_15A18; /* unable to generate initializer: unknown type */
static const char captureCollisionDisplayName[] = "CAPTURE COLLISION";
static const char captureCollisionFieldTypes[]  = "i";
static M2C_UNK captureCollisionEntry;

extern "C" {

void fn_8_9D3BC(s32 arg0)
{
	fn_8_9CAF0(arg0 - 0xB0);
}

void fn_8_9D3C4(void* arg0, s32 arg1)
{
	M2C_FIELD(arg0, s32*, 0x14) = arg1;
	M2C_FIELD(arg0, s32*, 0x10) = 0;
	if (M2C_FIELD(M2C_FIELD(arg0, void**, 0), s32(**)(), 0x14)() != 0) {
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 2);
	}
	M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
	    arg0, M2C_FIELD(arg0, s32*, 4), 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
		fn_800A31B8(M2C_FIELD(arg0, s32*, 0x14));
	}
}

void fn_8_9D45C(void* arg0)
{
	M2C_FIELD(arg0, f32*, 8)    = (f32)lbl_8_rodata_1704;
	M2C_FIELD(arg0, f32*, 4)    = (f32)lbl_8_rodata_1704;
	M2C_FIELD(arg0, f32*, 0)    = (f32)lbl_8_rodata_1704;
	M2C_FIELD(arg0, f32*, 0x14) = (f32)lbl_8_rodata_1704;
	M2C_FIELD(arg0, f32*, 0xC)  = (f32)lbl_8_rodata_1704;
	M2C_FIELD(arg0, f32*, 0x10) = (f32)lbl_8_rodata_170C;
	M2C_FIELD(arg0, f32*, 0x18) = (f32)lbl_8_rodata_1704;
	M2C_FIELD(arg0, f32*, 0x1C) = (f32)lbl_8_rodata_1710;
	M2C_FIELD(arg0, f32*, 0x20) = (f32)lbl_8_rodata_1704;
}

s32 fn_8_9D4A8(s32 arg0)
{
	if ((fn_8005B9F0((s32)((u8*)arg0 + 0x28)) != 0)
	    || (fn_8005B8BC((s32)((u8*)arg0 + 0x28)) != 0)) {
		return 1;
	}
	return 0;
}

void fn_8_9D4FC(void) { }

void fn_8_9D500(void* arg0)
{
	s32 var_r0;

	if ((fn_8005B9F0((s32)((u8*)arg0 + 0x28)) != 0)
	    || (fn_8005B8BC((s32)((u8*)arg0 + 0x28)) != 0)) {
		var_r0 = 1;
	} else {
		var_r0 = 0;
	}
	if (var_r0 != 0) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
	}
}

void fn_8_9D56C(void* arg0)
{
	void* temp_r4;
	void* temp_r4_2;

	temp_r4                     = M2C_FIELD(arg0, void**, 0x28);
	M2C_FIELD(arg0, f32*, 0x30) = (f32)M2C_FIELD(temp_r4, f32*, 0);
	M2C_FIELD(arg0, f32*, 0x34) = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x38) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	temp_r4_2                   = M2C_FIELD(arg0, void**, 0x28);
	M2C_FIELD(arg0, s32*, 0x3C) = (s32)M2C_FIELD(temp_r4_2, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0x40) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x44) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x14);
}

void fn_8_9D5A8(void* arg0)
{
	M2C_FIELD(arg0, f32*, 0x38) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x34) = 0.0f;
	M2C_FIELD(arg0, f32*, 0x30) = 0.0f;
	M2C_FIELD(arg0, s32*, 0x44) = 0;
	M2C_FIELD(arg0, s32*, 0x40) = 0;
	M2C_FIELD(arg0, s32*, 0x3C) = 0;
}

TObject* fn_8_9D5D4(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_15A18;
		arg0->unk2C = &lbl_8_data_15A18 + 0x2C;
		dtor_8005BD3C(arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_9D660(TObject* arg0, TObject* arg1)
{
	void* temp_r3;
	void* temp_r3_2;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	arg0->unk18 = &lbl_8_data_15A18;
	arg0->unk2C = &lbl_8_data_15A18 + 0x2C;
	arg0->unk0  = lbl_8_data_15A14;
	arg0->unk1E = 0x48;
	arg0->unk38 = 0.0f;
	arg0->unk34 = 0.0f;
	arg0->unk30 = 0.0f;
	arg0->unk44 = 0;
	arg0->unk40 = 0;
	arg0->unk3C = 0;
	temp_r3     = M2C_FIELD(arg0, void**, 0x28);
	arg0->unk30 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unk34 = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unk38 = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2   = M2C_FIELD(arg0, void**, 0x28);
	arg0->unk3C = M2C_FIELD(temp_r3_2, s32*, 0xC);
	arg0->unk40 = M2C_FIELD(temp_r3_2, s32*, 0x10);
	arg0->unk44 = M2C_FIELD(temp_r3_2, s32*, 0x14);
	return arg0;
}

TObject* fn_8_9D724(void)
{
	TObject* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;

	temp_r3 = fn_80018A34(lbl_8042C148, 0x48);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		fn_8005BE6C(&temp_r3->unk28);
		temp_r3->unk18 = &lbl_8_data_15A18;
		temp_r3->unk2C = &lbl_8_data_15A18 + 0x2C;
		temp_r3->unk0  = lbl_8_data_15A14;
		temp_r3->unk1E = 0x48;
		temp_r3->unk38 = 0.0f;
		temp_r3->unk34 = 0.0f;
		temp_r3->unk30 = 0.0f;
		temp_r3->unk44 = 0;
		temp_r3->unk40 = 0;
		temp_r3->unk3C = 0;
		temp_r3_2      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r3->unk30 = M2C_FIELD(temp_r3_2, f32*, 0);
		temp_r3->unk34 = M2C_FIELD(temp_r3_2, f32*, 4);
		temp_r3->unk38 = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3_3      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r3->unk3C = M2C_FIELD(temp_r3_3, s32*, 0xC);
		temp_r3->unk40 = M2C_FIELD(temp_r3_3, s32*, 0x10);
		temp_r3->unk44 = M2C_FIELD(temp_r3_3, s32*, 0x14);
	}
	return temp_r3;
}

void fn_8_9D81C(void* arg0, void* arg1)
{
	s32* temp_r5;
	s32* var_r3;
	s32 temp_r4;

	temp_r5 = M2C_FIELD(arg1, s32**, 0x2C);
	temp_r4 = *temp_r5;
	var_r3  = &lbl_8_data_159F4;
	if (temp_r4 < (s32)lbl_8_data_159F4) {

	} else {
		var_r3 = &lbl_8_data_159F8;
		if (temp_r4 > (s32)lbl_8_data_159F8) {

		} else {
			var_r3 = temp_r5;
		}
	}
	*temp_r5 = *var_r3;
}

void captureCollisionUnload(void) { }

void captureCollisionLoad(void) { }

void captureCollisionCreate(void)
{
	TObject* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;

	temp_r3 = fn_80018A34(lbl_8042C148, 0x48);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		fn_8005BE6C(&temp_r3->unk28);
		temp_r3->unk18 = &lbl_8_data_15A18;
		temp_r3->unk2C = &lbl_8_data_15A18 + 0x2C;
		temp_r3->unk0  = lbl_8_data_15A14;
		temp_r3->unk1E = 0x48;
		temp_r3->unk38 = 0.0f;
		temp_r3->unk34 = 0.0f;
		temp_r3->unk30 = 0.0f;
		temp_r3->unk44 = 0;
		temp_r3->unk40 = 0;
		temp_r3->unk3C = 0;
		temp_r3_2      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r3->unk30 = M2C_FIELD(temp_r3_2, f32*, 0);
		temp_r3->unk34 = M2C_FIELD(temp_r3_2, f32*, 4);
		temp_r3->unk38 = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3_3      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r3->unk3C = M2C_FIELD(temp_r3_3, s32*, 0xC);
		temp_r3->unk40 = M2C_FIELD(temp_r3_3, s32*, 0x10);
		temp_r3->unk44 = M2C_FIELD(temp_r3_3, s32*, 0x14);
	}
}

void captureCollisionRegister(void)
{
	const char* temp_r3;
	s32 flags;

	M2C_FIELD(&captureCollisionEntry, s32*, 0x14)         = 0;
	M2C_FIELD(&captureCollisionEntry, s32*, 0x18)         = 0;
	M2C_FIELD(&captureCollisionEntry, const char**, 0)    = captureCollisionDisplayName;
	M2C_FIELD(&captureCollisionEntry, void (**)(), 4)     = captureCollisionLoad;
	M2C_FIELD(&captureCollisionEntry, void (**)(), 8)     = captureCollisionUnload;
	M2C_FIELD(&captureCollisionEntry, void (**)(), 0xC)   = captureCollisionCreate;
	M2C_FIELD(&captureCollisionEntry, s32*, 0x10)         = 0;
	flags                                                 = 0x20000;
	M2C_FIELD(&captureCollisionEntry, s32*, 0x14)         = flags;
	M2C_FIELD(&captureCollisionEntry, s32*, 0x18)         = 0;
	M2C_FIELD(&captureCollisionEntry, s8*, 0x20)          = 0x1E;
	M2C_FIELD(&captureCollisionEntry, s16*, 0x1C)         = 0x65;
	M2C_FIELD(&captureCollisionEntry, s16*, 0x1E)         = 4;
	M2C_FIELD(&captureCollisionEntry, s8*, 0x21)          = 0;
	temp_r3                                               = captureCollisionFieldTypes;
	M2C_FIELD(&captureCollisionEntry, const char**, 0x24) = temp_r3;
	M2C_FIELD(&captureCollisionEntry, M2C_UNK**, 0x28)    = &captureCollisionFieldNames;
	if (temp_r3 != NULL) {
		M2C_FIELD(&captureCollisionEntry, s32*, 0x14) = flags | 8;
		return;
	}
	M2C_FIELD(&captureCollisionEntry, s32*, 0x14) = flags & ~8;
}
}
