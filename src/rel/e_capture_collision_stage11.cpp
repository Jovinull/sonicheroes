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
	/* 0x2C */ void* unk2C;   /* inferred */
	/* 0x30 */ f32 unk30;     /* inferred */
	/* 0x34 */ f32 unk34;     /* inferred */
	/* 0x38 */ f32 unk38;     /* inferred */
	/* 0x3C */ s32 unk3C;     /* inferred */
	/* 0x40 */ s32 unk40;     /* inferred */
	/* 0x44 */ s32 unk44;     /* inferred */
} TObject;                    /* size >= 0x48 */

extern "C" {
void* __ct__7TObjectFP7TObject(TObject* self, TObject* arg0); /* extern */
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);       /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                        /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                           /* extern */
TObject* fn_80018A34(s32, M2C_UNK);                           /* extern */
s32 fn_8005B8BC(s32);                                         /* extern */
s32 fn_8005B9F0(s32);                                         /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                                /* extern */
M2C_UNK fn_800A31B8(void*, s32);                              /* extern */
M2C_UNK fn_8_9CAF0(s32);                                      /* extern */
}
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern f32 lbl_8_rodata_1704;
extern f32 lbl_8_rodata_170C;
extern f32 lbl_8_rodata_1710;
static M2C_UNK captureCollisionFieldNames; /* unable to generate initializer: unknown type */
DECL_SECT(".data") static s32 lbl_8_data_159F4 = 0;
static s32 lbl_8_data_159F8                    = 0xFF;
static char lbl_8_data_159FC[]                 = "TObjCaptureCollision";
static const char* lbl_8_data_15A14            = lbl_8_data_159FC;
static M2C_UNK lbl_8_data_15A18; /* unable to generate initializer: unknown type */
static char captureCollisionDisplayName[] = "CAPTURE COLLISION";
static char captureCollisionFieldTypes[]  = "i";
typedef struct ObjectEntry {
	const char* name;        /* 0x00 */
	void (*load)(void);      /* 0x04 */
	void (*unload)(void);    /* 0x08 */
	void (*create)(void);    /* 0x0C */
	void* unk10;             /* 0x10 */
	u32 flags;               /* 0x14 */
	u32 unk18;               /* 0x18 */
	s16 unk1C;               /* 0x1C */
	s16 unk1E;               /* 0x1E */
	u8 unk20;                /* 0x20 */
	u8 unk21;                /* 0x21 */
	u8 pad22[2];             /* 0x22 */
	const char* fieldTypes;  /* 0x24 */
	const char** fieldNames; /* 0x28 */
	u8 pad2C[12];            /* 0x2C */
} ObjectEntry;               /* 0x38 */

static ObjectEntry captureCollisionEntry;
extern const f32 lbl_8_rodata_17BC[8] = { 0.0f, 0.0f, 1.5f, 0.0f, 0.0f, 0.0f, 1.5f, 0.0f };
extern const f32 lbl_8_rodata_17DC[3] = { 0.0f, 0.0f, 0.0f };
extern const s32 lbl_8_rodata_17E8[3] = { 0xDAE, 0xDAF, 0xDB0 };

/* Dispatch view of the object's vtable. The handler at vtable offset 0x10 is
 * reached through genuine virtual dispatch in retail: the target loads the
 * vtable through the already-materialised `this` in r3 and keeps the slot in
 * r12, which manual vtable indexing does not reproduce. Two implicit
 * destructor slots plus the two placeholders below put Release at slot 4. */
class TObjectDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void Release(s32, s32);
	virtual s32 vslot5();
};

extern "C" {

void fn_8_9D3BC(s32 arg0)
{
	fn_8_9CAF0(arg0 - 0xB0);
}

void fn_8_9D3C4(void* arg0, s32 arg1)
{
	M2C_FIELD(arg0, s32*, 0x14) = arg1;
	M2C_FIELD(arg0, s32*, 0x10) = 0;
	if (((TObjectDispatch*)arg0)->vslot5() != 0) {
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 2);
	}
	((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
		fn_800A31B8((void*)M2C_FIELD(arg0, s32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
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
		arg0->unk2C = (u8*)&lbl_8_data_15A18 + 0x2C;
		dtor_8005BD3C((u8*)arg0 + 0x28, 0);
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
	arg0->unk2C = (u8*)&lbl_8_data_15A18 + 0x2C;
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
		temp_r3->unk2C = (u8*)&lbl_8_data_15A18 + 0x2C;
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
	s32 temp_r4;
	s32* var_r3;

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
		temp_r3->unk2C = (u8*)&lbl_8_data_15A18 + 0x2C;
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
	captureCollisionEntry.flags      = 0;
	captureCollisionEntry.unk18      = 0;
	captureCollisionEntry.name       = (const char*)captureCollisionDisplayName;
	captureCollisionEntry.load       = (void (*)(void))captureCollisionLoad;
	captureCollisionEntry.unload     = (void (*)(void))captureCollisionUnload;
	captureCollisionEntry.create     = (void (*)(void))captureCollisionCreate;
	captureCollisionEntry.unk10      = (void*)0;
	captureCollisionEntry.flags      = 0x20000;
	captureCollisionEntry.unk18      = 0;
	captureCollisionEntry.unk20      = 0x1E;
	captureCollisionEntry.unk1C      = 0x65;
	captureCollisionEntry.unk1E      = 4;
	captureCollisionEntry.unk21      = 0;
	captureCollisionEntry.fieldTypes = (const char*)captureCollisionFieldTypes;
	captureCollisionEntry.fieldNames = (const char**)&captureCollisionFieldNames;
	if ((const char*)captureCollisionFieldTypes != NULL) {
		captureCollisionEntry.flags |= 8;
	} else {
		captureCollisionEntry.flags &= ~8;
	}
}
}
