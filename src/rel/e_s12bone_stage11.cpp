#include "types.h"

// Whole stage11 s12bone translation unit.  The object normalizer records the
// remaining GC/1.3.2-only layout choices: register coloring, straight-line
// scheduling, one folded short-circuit branch, one redundant switch edge and
// three allocation-result copies.  Source spellings tried for the copies
// include scalar and one-field-wrapper temporaries, an inlined allocation
// helper, real/placement-new forms, type-punning, and the propagation,
// lifetime and common-subexpression pragmas.  The typed object-manager layout,
// bottom-tested list walks and cursor wrappers removed the instruction-form
// differences; the step can shrink as future source spellings recover the
// compiler's remaining choices, and can be deleted when its tables empty.

typedef s32 M2C_UNK;

#define M2C_FIELD(base, type, offset) (*(type)((u8*)(u32)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))
#define S12_DATA                 __declspec(section ".data")
#define sp8                      sp[0]
#define spC                      sp[1]
#define sp10                     sp[2]
#define sp14                     sp[3]
#define sp18                     sp[4]
#define sp1C                     sp[5]
#define sp20                     sp[6]
#define sp24                     sp[7]
#define sp28                     sp[8]
#define sp2C                     sp[9]
#define sp30                     sp[10]
#define sp34                     sp[11]
#define sp38                     sp[12]
#define sp3C                     sp[13]
#define sp40                     sp[14]
#define sp44                     sp[15]

#pragma force_active on
extern "C" {

typedef struct RpClump RpClump;
typedef struct HAnimClass HAnimClass;

typedef struct RpHAnimHierarchy {
	/* 0x00 */ s32 unk0;        /* inferred */
	/* 0x04 */ char pad4[0x1C]; /* maybe part of unk0[8]? */
	/* 0x20 */ void** unk20;    /* inferred */
} RpHAnimHierarchy;             /* size >= 0x24 */

typedef struct TObject {
	/* 0x00 */ const void* unk0; /* inferred */
	/* 0x04 */ char pad4[0x14];  /* maybe part of unk0[6]? */
	/* 0x18 */ M2C_UNK* unk18;   /* inferred */
	/* 0x1C */ char pad1C[2];
	/* 0x1E */ s16 unk1E;               /* inferred */
	/* 0x20 */ char pad20[8];           /* maybe part of unk1E[5]? */
	/* 0x28 */ M2C_UNK unk28;           /* inferred */
	/* 0x2C */ void* unk2C;             /* inferred */
	/* 0x30 */ M2C_UNK unk30;           /* inferred */
	/* 0x34 */ f32 unk34;               /* inferred */
	/* 0x38 */ f32 unk38;               /* inferred */
	/* 0x3C */ s32 unk3C;               /* inferred */
	/* 0x40 */ void* unk40;             /* inferred */
	/* 0x44 */ s32 unk44;               /* inferred */
	/* 0x48 */ f32 unk48;               /* inferred */
	/* 0x4C */ f32 unk4C;               /* inferred */
	/* 0x50 */ f32 unk50;               /* inferred */
	/* 0x54 */ s32 unk54;               /* inferred */
	/* 0x58 */ s32 unk58;               /* inferred */
	/* 0x5C */ s32 unk5C;               /* inferred */
	/* 0x60 */ char pad60[0xC];         /* maybe part of unk5C[4]? */
	/* 0x6C */ s32 unk6C;               /* inferred */
	/* 0x70 */ s32 unk70;               /* inferred */
	/* 0x74 */ f32 unk74;               /* inferred */
	/* 0x78 */ s32 unk78;               /* inferred */
	/* 0x7C */ s32 unk7C;               /* inferred */
	/* 0x80 */ RpHAnimHierarchy* unk80; /* inferred */
	/* 0x84 */ s32 unk84;               /* inferred */
	/* 0x88 */ RpClump* unk88;          /* inferred */
	/* 0x8C */ RpClump* unk8C;          /* inferred */
	/* 0x90 */ char pad90[0xC];         /* maybe part of unk8C[4]? */
	/* 0x9C */ s32 unk9C;               /* inferred */
	/* 0xA0 */ s32 unkA0;               /* inferred */
	/* 0xA4 */ s32 unkA4;               /* inferred */
	/* 0xA8 */ char padA8[0x10];        /* maybe part of unkA4[5]? */
	/* 0xB8 */ f32 unkB8;               /* inferred */
	/* 0xBC */ f32 unkBC;               /* inferred */
	/* 0xC0 */ f32 unkC0;               /* inferred */
	/* 0xC4 */ f32 unkC4;               /* inferred */
	/* 0xC8 */ f32 unkC8;               /* inferred */
	/* 0xCC */ f32 unkCC;               /* inferred */
	/* 0xD0 */ s32 unkD0;               /* inferred */
} TObject;                              /* size >= 0xD4 */

typedef struct ObjectEntry {
	const char* name;
	void (*load)(void);
	void (*unload)(void);
	void (*create)(void);
	void (*reset)(void);
	u32 flags;
	u32 unk18;
	s16 unk1C;
	s16 unk1E;
	u8 unk20;
	u8 unk21;
	u8 pad22[2];
	const char* fieldTypes;
	const char** fieldNames;
} ObjectEntry;

typedef struct ColliObjectEntry {
	ObjectEntry entry;
	u8 tail[8];
} ColliObjectEntry;

struct _struct_lbl_8_bss_1DB8_0x8 {
	/* 0x0 */ s32 unk0; /* inferred */
	/* 0x4 */ char pad4[4];
}; /* size = 0x8 */

struct S12BoneMatrix {
	s32 values[16];
};

struct S12BoneIntCursor {
	s32* value;
};

struct S12BoneConstCharCursor {
	const char** value;
};

struct S12BoneConstVoidCursor {
	const void** value;
};

struct S12BoneVoidCursor {
	void** value;
};

struct S12BoneObjectManager {
	u8 padding[0x30];
	void* heads[256];
};

struct S12BoneManagerCursor {
	S12BoneObjectManager* value;
};

RpHAnimHierarchy* GetHierarchy__10HAnimClassFP7RpClump(
    HAnimClass* self, RpClump* arg0); /* extern */
s32 SearchNodeFrameFromNodeID__10HAnimClassFP16RpHAnimHierarchyi(
    HAnimClass* self, RpHAnimHierarchy* arg0, s32 arg1); /* extern */
M2C_UNK SetHierarchyForAtomic__10HAnimClassFP7RpClumpP16RpHAnimHierarchy(
    HAnimClass* self, RpClump* arg0, RpHAnimHierarchy* arg1); /* extern */
void* __ct__7TObjectFP7TObject(TObject* self, TObject* arg0); /* extern */
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);       /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                        /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                        /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                           /* extern */
u32 fn_80018A34(s32, M2C_UNK);                                /* extern */
void* fn_800211A8(s32);                                       /* extern */
M2C_UNK fn_80021384(M2C_UNK*);                                /* extern */
M2C_UNK fn_80021824(s32);                                     /* extern */
M2C_UNK fn_8003BC38(void*);                                   /* extern */
M2C_UNK fn_8003C200(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                                /* extern */
s32* fn_80057644(M2C_UNK);                                    /* extern */
s32 fn_8005B8BC(s32);                                         /* extern */
s32 fn_8005B9F0(s32);                                         /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                                /* extern */
M2C_UNK fn_8005D5C8(RpClump*, s32);                           /* extern */
s32 fn_80091FAC(s32);                                         /* extern */
s32 fn_80096A98(s32);                                         /* extern */
s32 fn_800BB0D4(s32, s32, M2C_UNK*);                          /* extern */
s32 fn_800BB92C(s32, s32, M2C_UNK*);                          /* extern */
s32 fn_800BC6CC(s32, const void*);                            /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                           /* extern */
f32 fn_800D7AE4(s32);                                         /* extern */
f32 fn_800D7B00(s32);                                         /* extern */
M2C_UNK fn_8013F3A4(RpHAnimHierarchy*);                       /* extern */
M2C_UNK fn_8013FC30(void*);                                   /* extern */
M2C_UNK fn_8014FF2C(s32);                                     /* extern */
RpClump* fn_80150588(s32);                                    /* extern */
M2C_UNK fn_80150958(RpClump*);                                /* extern */
M2C_UNK fn_80195674(void*, s32, s32*);                        /* extern */
M2C_UNK fn_80195790(void*, M2C_UNK*, M2C_UNK, f32, f32);      /* extern */
M2C_UNK fn_8019E880(void*);                                   /* extern */
M2C_UNK fn_8019EB94(void*, void*, M2C_UNK);                   /* extern */
M2C_UNK fn_801A4C84();                                        /* extern */
M2C_UNK fn_8020C2D8(s32);                                     /* extern */
M2C_UNK fn_8020C72C(void**, s32, s32);                        /* extern */
M2C_UNK fn_8020D02C(void**, const f32*, f32);                 /* extern */
void* memset(void*, s32, u32);                                /* extern */
void s12boneColliObjectCreate();                              /* static */
void s12boneColliObjectReset(void* arg0);                     /* static */
void s12boneObjectCreate();                                   /* static */
void s12boneObjectLoad(M2C_UNK arg_sp0);                      /* static */
void s12boneObjectReset();                                    /* static */
void s12boneObjectUnload(M2C_UNK arg_sp0);                    /* static */
TObject* fn_8_CC2F0(TObject*, s16);
void fn_8_CC0F0(s32);
void fn_8_CC0EC(void);
TObject* fn_8_CD478(TObject*, s16);
void fn_8_CCDE4(s32);
void fn_8_CCD98(void*);
void fn_8_CCD4C(void*);
void fn_8_CD730(void*, void*);
void fn_3_1A9B0(...);
void PDisp__7TObjectFv(...);
void ImmAftSetRaster__7TObjectFv(...);
void Debug__7TObjectFv(...);
void Error__7TObjectFPc(...);
void Render__7TObjectFv(...);

void fn_8005B8B8(...);
void objDefaultTDisp(...);
void fn_8_CDCD4(...);
extern HAnimClass HAnim;
extern M2C_UNK lbl_80239978;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_802AD0D0;
extern M2C_UNK lbl_802FF5A0;
extern M2C_UNK lbl_80303DC8;
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C1D0;
extern S12BoneObjectManager* lbl_8042C298;

extern f32 lbl_8_rodata_1FF0;
extern f32 lbl_8_rodata_1FF4;
extern f32 lbl_8_rodata_2000;
extern f32 lbl_8_rodata_2004;
S12_DATA char lbl_8_data_18F28[]         = "s12_on_gai_karada.dff";
S12_DATA char lbl_8_data_18F40[]         = "s12_pn_gai_karada_2.dff";
S12_DATA const char* lbl_8_data_18F58[2] = { lbl_8_data_18F28, lbl_8_data_18F40 };
S12_DATA char lbl_8_data_18F60[]         = "s12_on_gai_karada_11.anm";
S12_DATA char lbl_8_data_18F7C[]         = "s12_on_gai_karada_12.anm";
S12_DATA char lbl_8_data_18F98[]         = "s12_on_gai_karada_21.anm";
S12_DATA char lbl_8_data_18FB4[]         = "s12_on_gai_karada_22.anm";
S12_DATA char lbl_8_data_18FD0[]         = "s12_on_gai_karada_31.anm";
S12_DATA char lbl_8_data_18FEC[]         = "s12_on_gai_karada_32.anm";
S12_DATA const void* lbl_8_data_19008[8] = {
	lbl_8_data_18F60,
	lbl_8_data_18F7C,
	lbl_8_data_18F98,
	lbl_8_data_18FB4,
	lbl_8_data_18FD0,
	lbl_8_data_18FEC,
	(const void*)0x42480000,
	(const void*)0x3F800000,
};
S12_DATA char lbl_8_data_19028[]             = "type";
S12_DATA const char* s12boneObjectFieldNames = lbl_8_data_19028;
S12_DATA char lbl_8_data_19034[]             = "type : FROM RIGHT";
S12_DATA char lbl_8_data_19048[]             = "type : FROM LEFT";
S12_DATA char lbl_8_data_1905C[]             = "type : FROM LOWER";
S12_DATA const char* lbl_8_data_19070[3] = { lbl_8_data_19034, lbl_8_data_19048, lbl_8_data_1905C };
S12_DATA char lbl_8_data_1907C[]         = "TObjS12Bone";
S12_DATA const char* lbl_8_data_19088    = lbl_8_data_1907C;
S12_DATA char lbl_8_data_1908C[]         = "size x";
S12_DATA char lbl_8_data_19094[]         = "size y";
S12_DATA char lbl_8_data_1909C[]         = "size z";
S12_DATA const char* s12boneColliObjectFieldNames[3]
    = { lbl_8_data_1908C, lbl_8_data_19094, lbl_8_data_1909C };
S12_DATA u32 lbl_8_data_190B0[12]
    = { 0x0004F0E0, 0x00000402, 0, 0, 0, 0x41200000, 0x41200000, 0x41200000, 0, 0, 0, 0 };
S12_DATA char lbl_8_data_190E0[]      = "TObjS12BoneRangeColli";
S12_DATA const char* lbl_8_data_190F8 = lbl_8_data_190E0;
S12_DATA void* lbl_8_data_190FC[14]   = {
	NULL,
	NULL,
	(void*)fn_8_CC2F0,
	(void*)fn_8_CC0F0,
	(void*)fn_3_1A9B0,
	(void*)fn_8_CC0EC,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)fn_8005B8B8,
};
S12_DATA void* lbl_8_data_19134[15] = {
	NULL,
	NULL,
	(void*)fn_8_CD478,
	(void*)fn_8_CCDE4,
	(void*)fn_8_CCD98,
	(void*)objDefaultTDisp,
	(void*)fn_8_CCD4C,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)fn_8_CDCD4,
	(void*)fn_8_CD730,
};
S12_DATA char s12boneObjectDisplayName[]      = "S12BONE OBJECT";
S12_DATA char s12boneObjectFieldTypes[]       = "i";
S12_DATA char s12boneColliObjectDisplayName[] = "S12BONE COLLI_OBJECT";
S12_DATA char s12boneColliObjectFieldTypes[]  = "fff";
s32 lbl_8_bss_1DB0[2];
s32 lbl_8_bss_1DB8[3][2];
ObjectEntry s12boneObjectEntry;
ColliObjectEntry s12boneColliObjectEntry;

void fn_8_CBF20(void* arg0)
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
	M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(temp_r4_2, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0xA0) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0xA4) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x14);
	M2C_FIELD(arg0, f32*, 0xC4) = (f32)M2C_FIELD(temp_r5, f32*, 0);
	M2C_FIELD(arg0, f32*, 0xC8) = (f32)M2C_FIELD(temp_r5, f32*, 4);
	M2C_FIELD(arg0, f32*, 0xCC) = (f32)M2C_FIELD(temp_r5, f32*, 8);
}

s32 fn_8_CBF78(s32 arg0)
{
	s32 temp_r0;
	s32 temp_r28;
	s32 var_r31;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r4;
	void* var_r3;

	var_r31 = -1;
	fn_80021824(arg0 + 0x30);
	goto loop_23_check;
loop_23_body:
	temp_r0 = M2C_FIELD(var_r3, s32*, 0x78);
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
		temp_r3_2 = (void*)*(&lbl_802AD0D0 + var_r31);
		if ((temp_r28 = (s8)M2C_FIELD(temp_r3_2, u8*, 0x25C), temp_r3_2 != NULL)
		    && ((temp_r28 *= 4, ((fn_80091FAC(*(&lbl_80303DC8 + (temp_r28 >> 2))) == 2) == 0))
		        || (fn_80096A98(*(&lbl_80303DC8 + (temp_r28 >> 2))) != 0))
		    && ((temp_r4 = (void*)*(&lbl_80303DC8 + (temp_r28 >> 2)),
		            ((var_r31
		                 == (s8) * ((u8*)temp_r4 + ((s8)M2C_FIELD(temp_r4, u8*, 0x3A) + 0x110)))
		                != 0))
		        || (var_r31
		            == (s8) * ((u8*)temp_r4 + ((s8)M2C_FIELD(temp_r4, u8*, 0x3B) + 0x110))))) {
			return var_r31;
		}
	}
loop_23_check:
	temp_r3 = fn_800211A8(arg0 + 0x30);
	if (temp_r3 != NULL) {
		var_r3 = M2C_FIELD(temp_r3, void**, 4);
	} else {
		var_r3 = NULL;
	}
	if (var_r3 == NULL) {
		return -1;
	}
	goto loop_23_body;
}

void fn_8_CC0EC(void) { }

void fn_8_CC0F0(s32 arg0)
{
	s32 temp_r0;
	s32 temp_r28;
	s32 temp_r4_2;
	s32 var_r31;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r4;
	void* var_r3;

	if ((fn_8005B9F0(arg0 + 0x28) != 0) || (fn_8005B8BC(arg0 + 0x28) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	var_r31 = -1;
	fn_80021824(arg0 + 0x30);
	do {
		goto loop_26_check;
	loop_26_body:
		temp_r0 = M2C_FIELD(var_r3, s32*, 0x78);
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
		if ((var_r31 != -1)
		    && (temp_r3_2 = (void*)*(&lbl_802AD0D0 + var_r31),
		        temp_r28  = (s8)M2C_FIELD(temp_r3_2, u8*, 0x25C), ((temp_r3_2 == NULL) == 0))
		    && ((temp_r28 *= 4, ((fn_80091FAC(*(&lbl_80303DC8 + (temp_r28 >> 2))) == 2) == 0))
		        || (fn_80096A98(*(&lbl_80303DC8 + (temp_r28 >> 2))) != 0))) {
			temp_r4 = (void*)*(&lbl_80303DC8 + (temp_r28 >> 2));
			if (var_r31 == (s8) * ((u8*)temp_r4 + ((s8)M2C_FIELD(temp_r4, u8*, 0x3A) + 0x110))) {
				goto loop_26_done;
			}
			if (var_r31 != (s8) * ((u8*)temp_r4 + ((s8)M2C_FIELD(temp_r4, u8*, 0x3B) + 0x110))) {
				goto loop_26_check;
			}
			goto loop_26_done;
		} else {
			goto loop_26_check;
		}
	loop_26_check:
		temp_r3 = fn_800211A8(arg0 + 0x30);
		if (temp_r3 != NULL) {
			var_r3 = M2C_FIELD(temp_r3, void**, 4);
		} else {
			var_r3 = NULL;
		}
		if (var_r3 != NULL) {
			goto loop_26_body;
		}
		var_r31 = -1;
		goto loop_26_done;
	} while (1);
loop_26_done:
	M2C_FIELD(arg0, s32*, 0xD0) = var_r31;
	M2C_FIELD(arg0, f32*, 0xAC) = (f32)M2C_FIELD(arg0, f32*, 0x90);
	M2C_FIELD(arg0, f32*, 0xB0) = (f32)M2C_FIELD(arg0, f32*, 0x94);
	M2C_FIELD(arg0, f32*, 0xB4) = (f32)M2C_FIELD(arg0, f32*, 0x98);
	M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0xB8);
	M2C_FIELD(arg0, f32*, 0x94) = (f32)M2C_FIELD(arg0, f32*, 0xBC);
	M2C_FIELD(arg0, f32*, 0x98) = (f32)M2C_FIELD(arg0, f32*, 0xC0);
	fn_8003BC38((void*)(arg0 + 0x30));
	temp_r4_2 = M2C_FIELD(arg0, s32*, 0xD0);
	*M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), u32**, 0x30)
	    = (u32)((-1 - temp_r4_2) | (temp_r4_2 + 1)) >> 0x1FU;
}

TObject* fn_8_CC2F0(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = (M2C_UNK*)lbl_8_data_190FC;
		arg0->unk2C = (u8*)lbl_8_data_190FC + 0x2C;
		dtor_8003C52C((u8*)arg0 + 0x30, 0);
		dtor_8005BD3C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_CC388(TObject* arg0, TObject* arg1)
{
	s32* temp_r3_3;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r4;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	fn_8003C618(&arg0->unk30);
	arg0->unk18 = (M2C_UNK*)lbl_8_data_190FC;
	arg0->unk2C = (u8*)lbl_8_data_190FC + 0x2C;
	arg0->unk0  = lbl_8_data_190F8;
	arg0->unk1E = 0xD4;
	temp_r3     = M2C_FIELD(arg0, void**, 0x28);
	temp_r4     = M2C_FIELD(temp_r3, void**, 0x2C);
	arg0->unkB8 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unkBC = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unkC0 = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2   = M2C_FIELD(arg0, void**, 0x28);
	arg0->unk9C = M2C_FIELD(temp_r3_2, s32*, 0xC);
	arg0->unkA0 = M2C_FIELD(temp_r3_2, s32*, 0x10);
	arg0->unkA4 = M2C_FIELD(temp_r3_2, s32*, 0x14);
	arg0->unkC4 = M2C_FIELD(temp_r4, f32*, 0);
	arg0->unkC8 = M2C_FIELD(temp_r4, f32*, 4);
	arg0->unkCC = M2C_FIELD(temp_r4, f32*, 8);
	arg0->unkD0 = -1;
	fn_8003C200(&arg0->unk30, (M2C_UNK*)lbl_8_data_190B0, 1, 4);
	M2C_FIELD(arg0->unk40, f32*, 0x14) = (f32)arg0->unkC4;
	M2C_FIELD(arg0->unk40, f32*, 0x18) = (f32)arg0->unkC8;
	M2C_FIELD(arg0->unk40, f32*, 0x1C) = (f32)arg0->unkCC;
	fn_80021384(&arg0->unk30);
	if ((s32*)M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32**, 0x30) == NULL) {
		temp_r3_3                                             = fn_80057644(4);
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32**, 0x30) = temp_r3_3;
		*temp_r3_3                                            = 0;
	}
	return arg0;
}

void s12boneColliObjectReset(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x30) != 0U) {
		memset(M2C_FIELD(arg0, void**, 0x30), 0, 4);
	}
}

void s12boneColliObjectCreate(void)
{
	TObject* temp_r3;
	u32 temp_r0;
	s32* temp_r3_4;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r4;

	temp_r0 = fn_80018A34(lbl_8042C148, 0xD4);
	if (temp_r0 != 0) {
		temp_r3 = (TObject*)temp_r0;
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C110);
		fn_8005BE6C(&temp_r3->unk28);
		fn_8003C618(&temp_r3->unk30);
		temp_r3->unk18 = (M2C_UNK*)lbl_8_data_190FC;
		temp_r3->unk2C = (u8*)lbl_8_data_190FC + 0x2C;
		temp_r3->unk0  = lbl_8_data_190F8;
		temp_r3->unk1E = 0xD4;
		temp_r3_2      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r4        = M2C_FIELD(temp_r3_2, void**, 0x2C);
		temp_r3->unkB8 = M2C_FIELD(temp_r3_2, f32*, 0);
		temp_r3->unkBC = M2C_FIELD(temp_r3_2, f32*, 4);
		temp_r3->unkC0 = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3_3      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r3->unk9C = M2C_FIELD(temp_r3_3, s32*, 0xC);
		temp_r3->unkA0 = M2C_FIELD(temp_r3_3, s32*, 0x10);
		temp_r3->unkA4 = M2C_FIELD(temp_r3_3, s32*, 0x14);
		temp_r3->unkC4 = M2C_FIELD(temp_r4, f32*, 0);
		temp_r3->unkC8 = M2C_FIELD(temp_r4, f32*, 4);
		temp_r3->unkCC = M2C_FIELD(temp_r4, f32*, 8);
		temp_r3->unkD0 = -1;
		fn_8003C200(&temp_r3->unk30, (M2C_UNK*)lbl_8_data_190B0, 1, 4);
		M2C_FIELD(temp_r3->unk40, f32*, 0x14) = (f32)temp_r3->unkC4;
		M2C_FIELD(temp_r3->unk40, f32*, 0x18) = (f32)temp_r3->unkC8;
		M2C_FIELD(temp_r3->unk40, f32*, 0x1C) = (f32)temp_r3->unkCC;
		fn_80021384(&temp_r3->unk30);
		if ((s32*)M2C_FIELD(M2C_FIELD(temp_r3, void**, 0x28), s32**, 0x30) == NULL) {
			temp_r3_4                                                = fn_80057644(4);
			M2C_FIELD(M2C_FIELD(temp_r3, void**, 0x28), s32**, 0x30) = temp_r3_4;
			*temp_r3_4                                               = 0;
		}
	}
}

void fn_8_CC64C(void* arg0, s32 arg1)
{
	M2C_FIELD(arg0, s32*, 0x5C) = arg1;
}

void fn_8_CC654(void* arg0)
{
	s32 temp_r0;

	temp_r0 = M2C_FIELD(arg0, s32*, 0x5C);
	if (temp_r0 != -1) {
		M2C_FIELD(arg0, s32*, 0x58) = temp_r0;
		M2C_FIELD(arg0, s32*, 0x5C) = -1;
	}
}

#pragma fp_contract off
void fn_8_CC670(void* arg0)
{
	f32 temp_f1;
	f32 temp_f3;
	s32 temp_r0;
	u8 var_r0;

	fn_8020D02C(M2C_FIELD(M2C_FIELD(arg0, void**, 0x80), void***, 0x20), &lbl_8_rodata_1FF0,
	    (f32)M2C_FIELD(arg0, s32*, 0x78) / lbl_8_rodata_1FF0);
	fn_8013FC30(M2C_FIELD(arg0, void**, 0x80));
	temp_f3 = lbl_8_rodata_1FF0 * M2C_FIELD(arg0, f32*, 0x74);
	temp_r0 = M2C_FIELD(arg0, s32*, 0x78);
	temp_f1 = (f32)temp_r0 - (temp_f3 * (f32)(s32)((f32)temp_r0 / temp_f3));
	var_r0  = 0;
	if (temp_f1 < temp_f3) {
		M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
		if (temp_f3 <= (lbl_8_rodata_1FF4 + temp_f1)) {
			var_r0 = 1;
		}
	}
	M2C_FIELD(arg0, s32*, 0x7C) = (s32)var_r0;
}
#pragma fp_contract on

void fn_8_CC790(void* arg0)
{
	s32 temp_r0;
	S12BoneVoidCursor temp_r3;

	temp_r0 = M2C_FIELD(arg0, s32*, 0x70);
	if (temp_r0 != -1) {
		M2C_FIELD(arg0, s32*, 0x6C) = temp_r0;
		temp_r3.value               = M2C_FIELD(M2C_FIELD(arg0, void**, 0x80), void***, 0x20);
		temp_r0                     = M2C_FIELD(arg0, s32*, 0x54);
		fn_8020C72C(
		    temp_r3.value, lbl_8_bss_1DB8[temp_r0][M2C_FIELD(arg0, s32*, 0x6C)], temp_r0 * 8);
		fn_8020D02C(M2C_FIELD(M2C_FIELD(arg0, void**, 0x80), void***, 0x20), &lbl_8_rodata_2000,
		    lbl_8_rodata_2000);
		M2C_FIELD(arg0, f32*, 0x74)
		    = (f32)M2C_FIELD(*M2C_FIELD(M2C_FIELD(arg0, void**, 0x80), void***, 0x20), f32*, 0xC);
		M2C_FIELD(arg0, s32*, 0x78) = 0;
		M2C_FIELD(arg0, s32*, 0x7C) = 0;
		M2C_FIELD(arg0, s32*, 0x70) = -1;
	}
}

void fn_8_CC834(void* arg0, s32 arg1)
{
	M2C_FIELD(arg0, s32*, 0x70) = arg1;
}

void fn_8_CC83C(void* arg0)
{
	RpHAnimHierarchy* temp_r3;
	s32 temp_r0;

	M2C_FIELD(arg0, RpHAnimHierarchy**, 0x80)
	    = GetHierarchy__10HAnimClassFP7RpClump(&HAnim, M2C_FIELD(arg0, RpClump**, 0x88));
	SetHierarchyForAtomic__10HAnimClassFP7RpClumpP16RpHAnimHierarchy(
	    &HAnim, M2C_FIELD(arg0, RpClump**, 0x88), M2C_FIELD(arg0, RpHAnimHierarchy**, 0x80));
	temp_r3 = M2C_FIELD(arg0, RpHAnimHierarchy**, 0x80);
	temp_r3->unk0 |= 0x3000;
	fn_8013F3A4(M2C_FIELD(arg0, RpHAnimHierarchy**, 0x80));
	M2C_FIELD(arg0, s32*, 0x70) = 0;
	temp_r0                     = M2C_FIELD(arg0, s32*, 0x70);
	if (temp_r0 != -1) {
		M2C_FIELD(arg0, s32*, 0x6C) = temp_r0;
		fn_8020C72C(M2C_FIELD(arg0, RpHAnimHierarchy**, 0x80)->unk20,
		    lbl_8_bss_1DB8[M2C_FIELD(arg0, s32*, 0x54)][M2C_FIELD(arg0, s32*, 0x6C)],
		    M2C_FIELD(arg0, s32*, 0x54) * 8);
		fn_8020D02C(M2C_FIELD(arg0, RpHAnimHierarchy**, 0x80)->unk20, &lbl_8_rodata_2000,
		    lbl_8_rodata_2000);
		M2C_FIELD(arg0, f32*, 0x74)
		    = (f32)M2C_FIELD(*M2C_FIELD(arg0, RpHAnimHierarchy**, 0x80)->unk20, f32*, 0xC);
		M2C_FIELD(arg0, s32*, 0x78) = 0;
		M2C_FIELD(arg0, s32*, 0x7C) = 0;
		M2C_FIELD(arg0, s32*, 0x70) = -1;
	}
	M2C_FIELD(arg0, s32*, 0x84) = SearchNodeFrameFromNodeID__10HAnimClassFP16RpHAnimHierarchyi(
	    &HAnim, M2C_FIELD(arg0, RpHAnimHierarchy**, 0x80), 0x48);
}

s32 fn_8_CC940(void* arg0)
{
	s32* temp_r3;
	S12BoneManagerCursor temp_r4;
	void* temp_r5;
	void* var_r3;

	temp_r4.value = lbl_8042C298;
	temp_r5       = M2C_FIELD(arg0, void**, 0x28);
	var_r3        = temp_r4.value->heads[M2C_FIELD(temp_r5, u8*, 0x2A)];
	while (var_r3 != NULL) {
		if (((u16)M2C_FIELD(var_r3, u16*, 0x28) == 0x1186) && (var_r3 != temp_r5)) {
			temp_r3 = M2C_FIELD(var_r3, s32**, 0x30);
			if (temp_r3 == NULL) {
				return 0;
			}
			return *temp_r3;
		}
		var_r3 = M2C_FIELD(var_r3, void**, 0x38);
	}
	return 0;
}
void fn_8_CC9AC(s32 arg0)
{
	s32 sp[16];
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	f32 temp_f31_5;
	f32 temp_f31_6;
	f32 temp_f31_7;
	f32 temp_f31_8;
	s32 temp_r31;
	s32 temp_r31_2;
	s32 temp_r3;
	s32 temp_r4_3;

	if ((s32)M2C_FIELD(arg0, s32*, 0x58) != 1) {
		temp_r31 = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x88), void**, 4);
		fn_8019EB94((void*)temp_r31, (void*)(arg0 + 0x30), 0);
		temp_f31 = fn_800D7B00(0x8000);
		fn_80195790((void*)(temp_r31 + 0x10), &lbl_80239984, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(0x8000), temp_f31);
		fn_8019E880((void*)temp_r31);
		temp_f31_2 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x44));
		fn_80195790((void*)(temp_r31 + 0x10), &lbl_80239990, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x44)), temp_f31_2);
		fn_8019E880((void*)temp_r31);
		temp_f31_3 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x40));
		fn_80195790((void*)(temp_r31 + 0x10), &lbl_80239984, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x40)), temp_f31_3);
		fn_8019E880((void*)temp_r31);
		temp_f31_4 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x3C));
		fn_80195790((void*)(temp_r31 + 0x10), &lbl_80239978, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x3C)), temp_f31_4);
		fn_8019E880((void*)temp_r31);
		temp_r31_2 = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x8C), void**, 4);
		fn_8019EB94((void*)temp_r31_2, (void*)(arg0 + 0x30), 0);
		temp_f31_5 = fn_800D7B00(0x8000);
		fn_80195790((void*)(temp_r31_2 + 0x10), &lbl_80239984, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(0x8000), temp_f31_5);
		fn_8019E880((void*)temp_r31_2);
		temp_f31_6 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x44));
		fn_80195790((void*)(temp_r31_2 + 0x10), &lbl_80239990, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x44)), temp_f31_6);
		fn_8019E880((void*)temp_r31_2);
		temp_f31_7 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x40));
		fn_80195790((void*)(temp_r31_2 + 0x10), &lbl_80239984, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x40)), temp_f31_7);
		fn_8019E880((void*)temp_r31_2);
		temp_f31_8 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x3C));
		fn_80195790((void*)(temp_r31_2 + 0x10), &lbl_80239978, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x3C)), temp_f31_8);
		fn_8019E880((void*)temp_r31_2);
		temp_r3             = temp_r31_2 + 0x10;
		temp_r4_3           = M2C_FIELD(arg0, s32*, 0x84) + 0x10;
		*(S12BoneMatrix*)sp = *(S12BoneMatrix*)temp_r3;
		fn_80195674((void*)temp_r3, temp_r4_3, &sp8);
	}
}

void fn_8_CCCEC(void* arg0)
{
	void* temp_r4;
	void* temp_r5;

	temp_r4                     = M2C_FIELD(arg0, void**, 0x28);
	temp_r5                     = M2C_FIELD(temp_r4, void**, 0x2C);
	M2C_FIELD(arg0, f32*, 0x30) = (f32)M2C_FIELD(temp_r4, f32*, 0);
	M2C_FIELD(arg0, f32*, 0x34) = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x38) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	temp_r4                     = M2C_FIELD(arg0, void**, 0x28);
	M2C_FIELD(arg0, s32*, 0x3C) = (s32)M2C_FIELD(temp_r4, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0x40) = (s32)M2C_FIELD(temp_r4, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x44) = (s32)M2C_FIELD(temp_r4, s32*, 0x14);
	M2C_FIELD(arg0, f32*, 0x48) = (f32)M2C_FIELD(arg0, f32*, 0x30);
	M2C_FIELD(arg0, f32*, 0x4C) = (f32)M2C_FIELD(arg0, f32*, 0x34);
	M2C_FIELD(arg0, f32*, 0x50) = (f32)M2C_FIELD(arg0, f32*, 0x38);
	M2C_FIELD(arg0, s32*, 0x54) = (s32)M2C_FIELD(temp_r5, s32*, 0);
}

void fn_8_CCD4C(void* arg0)
{
	if (((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) == 0) && ((s32)M2C_FIELD(arg0, s32*, 0x58) != 1)) {
		fn_8014FF2C(M2C_FIELD(arg0, s32*, 0x8C));
	}
}

void fn_8_CCD98(void* arg0)
{
	if (((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) == 0) && ((s32)M2C_FIELD(arg0, s32*, 0x58) != 1)) {
		fn_8014FF2C(M2C_FIELD(arg0, s32*, 0x88));
	}
}

#pragma fp_contract off
void fn_8_CCDE4(s32 arg0)
{
	s32 sp[16];
	f32 temp_f1;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	f32 temp_f31_5;
	f32 temp_f31_6;
	f32 temp_f31_7;
	f32 temp_f31_8;
	f32 temp_f3;
	s32* temp_r3_2;
	s32* temp_r3_3;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r0_4;
	s32 temp_r0_5;
	s32 temp_r0_6;
	s32 var_r0_2;
	s32 var_r0_3;
	u8 var_r0;
	s32 temp_r31;
	s32 temp_r31_2;
	s32 temp_r3;
	s32 temp_r4_3;
	void* temp_r4;
	void* temp_r4_2;
	S12BoneObjectManager* temp_r5;
	void* var_r3;
	void* var_r3_2;

	if ((fn_8005B9F0(arg0 + 0x28) != 0) || (fn_8005B8BC(arg0 + 0x28) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0x58) != 1) {
		temp_r31 = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x88), void**, 4);
		fn_8019EB94((void*)temp_r31, (void*)(arg0 + 0x30), 0);
		temp_f31 = fn_800D7B00(0x8000);
		fn_80195790((void*)(temp_r31 + 0x10), &lbl_80239984, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(0x8000), temp_f31);
		fn_8019E880((void*)temp_r31);
		temp_f31_2 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x44));
		fn_80195790((void*)(temp_r31 + 0x10), &lbl_80239990, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x44)), temp_f31_2);
		fn_8019E880((void*)temp_r31);
		temp_f31_3 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x40));
		fn_80195790((void*)(temp_r31 + 0x10), &lbl_80239984, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x40)), temp_f31_3);
		fn_8019E880((void*)temp_r31);
		temp_f31_4 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x3C));
		fn_80195790((void*)(temp_r31 + 0x10), &lbl_80239978, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x3C)), temp_f31_4);
		fn_8019E880((void*)temp_r31);
		temp_r31_2 = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x8C), void**, 4);
		fn_8019EB94((void*)temp_r31_2, (void*)(arg0 + 0x30), 0);
		temp_f31_5 = fn_800D7B00(0x8000);
		fn_80195790((void*)(temp_r31_2 + 0x10), &lbl_80239984, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(0x8000), temp_f31_5);
		fn_8019E880((void*)temp_r31_2);
		temp_f31_6 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x44));
		fn_80195790((void*)(temp_r31_2 + 0x10), &lbl_80239990, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x44)), temp_f31_6);
		fn_8019E880((void*)temp_r31_2);
		temp_f31_7 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x40));
		fn_80195790((void*)(temp_r31_2 + 0x10), &lbl_80239984, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x40)), temp_f31_7);
		fn_8019E880((void*)temp_r31_2);
		temp_f31_8 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0x3C));
		fn_80195790((void*)(temp_r31_2 + 0x10), &lbl_80239978, 1,
		    lbl_8_rodata_2004 - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0x3C)), temp_f31_8);
		fn_8019E880((void*)temp_r31_2);
		temp_r3             = temp_r31_2 + 0x10;
		temp_r4_3           = M2C_FIELD(arg0, s32*, 0x84) + 0x10;
		*(S12BoneMatrix*)sp = *(S12BoneMatrix*)temp_r3;
		fn_80195674((void*)temp_r3, temp_r4_3, &sp8);
	}
	temp_r0 = M2C_FIELD(arg0, s32*, 0x5C);
	if (temp_r0 != -1) {
		M2C_FIELD(arg0, s32*, 0x58) = temp_r0;
		M2C_FIELD(arg0, s32*, 0x5C) = -1;
	}
	temp_r0_2 = M2C_FIELD(arg0, s32*, 0x70);
	if (temp_r0_2 != -1) {
		M2C_FIELD(arg0, s32*, 0x6C) = temp_r0_2;
		temp_r0_3                   = M2C_FIELD(arg0, s32*, 0x54);
		fn_8020C72C(M2C_FIELD(M2C_FIELD(arg0, void**, 0x80), void***, 0x20),
		    lbl_8_bss_1DB8[temp_r0_3][M2C_FIELD(arg0, s32*, 0x6C)], temp_r0_3 * 8);
		fn_8020D02C(M2C_FIELD(M2C_FIELD(arg0, void**, 0x80), void***, 0x20), &lbl_8_rodata_2000,
		    lbl_8_rodata_2000);
		M2C_FIELD(arg0, f32*, 0x74)
		    = (f32)M2C_FIELD(*M2C_FIELD(M2C_FIELD(arg0, void**, 0x80), void***, 0x20), f32*, 0xC);
		M2C_FIELD(arg0, s32*, 0x78) = 0;
		M2C_FIELD(arg0, s32*, 0x7C) = 0;
		M2C_FIELD(arg0, s32*, 0x70) = -1;
	}
	temp_r0_4 = M2C_FIELD(arg0, s32*, 0x58);
	if ((temp_r0_4 == 2) || (temp_r0_4 == 3)) {
		M2C_FIELD(arg0, s32*, 0x78) = (s32)(M2C_FIELD(arg0, s32*, 0x78) + 2);
		fn_8020D02C(M2C_FIELD(M2C_FIELD(arg0, void**, 0x80), void***, 0x20), &lbl_8_rodata_1FF0,
		    (f32)M2C_FIELD(arg0, s32*, 0x78) / lbl_8_rodata_1FF0);
		fn_8013FC30(M2C_FIELD(arg0, void**, 0x80));
		temp_f3   = lbl_8_rodata_1FF0 * M2C_FIELD(arg0, f32*, 0x74);
		temp_r0_5 = M2C_FIELD(arg0, s32*, 0x78);
		temp_f1   = (f32)temp_r0_5 - (temp_f3 * (f32)(s32)((f32)temp_r0_5 / temp_f3));
		var_r0    = 0;
		if (temp_f1 < temp_f3) {
			M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
			if (temp_f3 <= (lbl_8_rodata_1FF4 + temp_f1)) {
				var_r0 = 1;
			}
		}
		M2C_FIELD(arg0, s32*, 0x7C) = (s32)var_r0;
	}
	temp_r0_6 = M2C_FIELD(arg0, s32*, 0x58);
	switch (temp_r0_6) { /* irregular */
		case 1:
			if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) == 0) {
				temp_r5 = lbl_8042C298;
				temp_r4 = M2C_FIELD(arg0, void**, 0x28);
				var_r3  = temp_r5->heads[M2C_FIELD(temp_r4, u8*, 0x2A)];
				goto loop_30_check;
			loop_30:
				if (((u16)M2C_FIELD(var_r3, u16*, 0x28) == 0x1186) && (var_r3 != temp_r4)) {
					temp_r3_2 = M2C_FIELD(var_r3, s32**, 0x30);
					if (temp_r3_2 == NULL) {
						var_r0_2 = 0;
					} else {
						var_r0_2 = *temp_r3_2;
					}
					goto loop_30_done;
				}
				var_r3 = M2C_FIELD(var_r3, void**, 0x38);
			loop_30_check:
				if (var_r3 != NULL) {
					goto loop_30;
				}
				var_r0_2 = 0;
			loop_30_done:
				if (var_r0_2 != 0) {
					M2C_FIELD(arg0, s32*, 0x5C) = 2;
					M2C_FIELD(arg0, s32*, 0x70) = 0;
				}
			} else {
				return;
			}
			break;
		case 2:
			if ((s32)M2C_FIELD(arg0, s32*, 0x7C) != 0) {
				M2C_FIELD(arg0, s32*, 0x5C) = 0;
				return;
			}
			break;
		case 0:
			temp_r5   = lbl_8042C298;
			temp_r4_2 = M2C_FIELD(arg0, void**, 0x28);
			var_r3_2  = temp_r5->heads[M2C_FIELD(temp_r4_2, u8*, 0x2A)];
			goto loop_43_check;
		loop_43:
			if (((u16)M2C_FIELD(var_r3_2, u16*, 0x28) == 0x1186) && (var_r3_2 != temp_r4_2)) {
				temp_r3_3 = M2C_FIELD(var_r3_2, s32**, 0x30);
				if (temp_r3_3 == NULL) {
					var_r0_3 = 0;
				} else {
					var_r0_3 = *temp_r3_3;
				}
				goto loop_43_done;
			}
			var_r3_2 = M2C_FIELD(var_r3_2, void**, 0x38);
		loop_43_check:
			if (var_r3_2 != NULL) {
				goto loop_43;
			}
			var_r0_3 = 0;
		loop_43_done:
			if (var_r0_3 == 0) {
				M2C_FIELD(arg0, s32*, 0x5C) = 3;
				M2C_FIELD(arg0, s32*, 0x70) = 1;
				return;
			}
			break;
		case 3:
			if ((s32)M2C_FIELD(arg0, s32*, 0x7C) != 0) {
				M2C_FIELD(arg0, s32*, 0x5C) = 1;
			}
			break;
	}
}
#pragma fp_contract on

TObject* fn_8_CD478(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = (M2C_UNK*)lbl_8_data_19134;
		arg0->unk2C = (u8*)lbl_8_data_19134 + 0x2C;
		if ((u32)arg0->unk88 != NULL) {
			fn_80150958(arg0->unk88);
		}
		if ((u32)arg0->unk8C != NULL) {
			fn_80150958(arg0->unk8C);
		}
		dtor_8005BD3C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_CD524(TObject* arg0, TObject* arg1)
{
	RpHAnimHierarchy* temp_r3_3;
	s32* temp_r4;
	s32 temp_r0;
	s32 temp_r0_2;
	void* temp_r3;
	void* temp_r3_2;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	arg0->unk18                 = (M2C_UNK*)lbl_8_data_19134;
	arg0->unk2C                 = (u8*)lbl_8_data_19134 + 0x2C;
	arg0->unk0                  = lbl_8_data_19088;
	arg0->unk1E                 = 0x98;
	temp_r3                     = M2C_FIELD(arg0, void**, 0x28);
	temp_r4                     = M2C_FIELD(temp_r3, s32**, 0x2C);
	M2C_FIELD(arg0, f32*, 0x30) = (f32)M2C_FIELD(temp_r3, f32*, 0);
	arg0->unk34                 = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unk38                 = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2                   = M2C_FIELD(arg0, void**, 0x28);
	arg0->unk3C                 = M2C_FIELD(temp_r3_2, s32*, 0xC);
	arg0->unk40                 = M2C_FIELD(temp_r3_2, void**, 0x10);
	arg0->unk44                 = M2C_FIELD(temp_r3_2, s32*, 0x14);
	arg0->unk48                 = M2C_FIELD(arg0, f32*, 0x30);
	arg0->unk4C                 = arg0->unk34;
	arg0->unk50                 = arg0->unk38;
	arg0->unk54                 = *temp_r4;
	arg0->unk88                 = fn_80150588(lbl_8_bss_1DB0[0]);
	fn_8005D5C8(arg0->unk88,
	    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U) + 4);
	arg0->unk8C = fn_80150588(lbl_8_bss_1DB0[1]);
	fn_8005D5C8(arg0->unk8C,
	    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U) + 4);
	arg0->unk58 = 1;
	arg0->unk5C = -1;
	arg0->unk80 = GetHierarchy__10HAnimClassFP7RpClump(&HAnim, arg0->unk88);
	SetHierarchyForAtomic__10HAnimClassFP7RpClumpP16RpHAnimHierarchy(
	    &HAnim, arg0->unk88, arg0->unk80);
	temp_r3_3 = arg0->unk80;
	temp_r3_3->unk0 |= 0x3000;
	fn_8013F3A4(arg0->unk80);
	arg0->unk70 = 0;
	temp_r0     = arg0->unk70;
	if (temp_r0 != -1) {
		arg0->unk6C = temp_r0;
		temp_r0_2   = arg0->unk54;
		fn_8020C72C(arg0->unk80->unk20, lbl_8_bss_1DB8[temp_r0_2][arg0->unk6C], temp_r0_2 * 8);
		fn_8020D02C(arg0->unk80->unk20, &lbl_8_rodata_2000, lbl_8_rodata_2000);
		arg0->unk74 = M2C_FIELD(*arg0->unk80->unk20, f32*, 0xC);
		arg0->unk78 = 0;
		arg0->unk7C = 0;
		arg0->unk70 = -1;
	}
	arg0->unk84
	    = SearchNodeFrameFromNodeID__10HAnimClassFP16RpHAnimHierarchyi(&HAnim, arg0->unk80, 0x48);
	return arg0;
}

void fn_8_CD730(void*, void* arg1)
{
	s32* temp_r3;
	s32 temp_r0;

	temp_r3 = M2C_FIELD(arg1, s32**, 0x2C);
	temp_r0 = *temp_r3;
	if (temp_r0 < 0) {
		*temp_r3 = 0;
	} else if (temp_r0 >= 3) {
		*temp_r3 = 2;
	}
	s12boneObjectFieldNames = lbl_8_data_19070[*temp_r3];
}

void s12boneObjectReset(void) { }

void s12boneObjectUnload(M2C_UNK arg_sp0)
{
	S12BoneIntCursor var_r30;
	s32 var_r27;
	s32 var_r28;
	S12BoneIntCursor var_r29;

	var_r28       = 0;
	var_r30.value = lbl_8_bss_1DB0;
	do {
		fn_80150958((RpClump*)*var_r30.value);
		*var_r30.value = 0;
		var_r30.value += 1;
		var_r28 += 1;
	} while (var_r28 < 2);
	var_r28       = 0;
	var_r29.value = &lbl_8_bss_1DB8[0][0];
	do {
		var_r27       = 0;
		var_r30.value = var_r29.value;
	loop_4:
		fn_8020C2D8(*var_r30.value);
		*var_r30.value = 0;
		var_r30.value += 1;
		var_r27 += 1;
		if (var_r27 < 2) {
			goto loop_4;
		}
		var_r29.value += 2;
		var_r28 += 1;
	} while (var_r28 < 3);
}

void s12boneObjectLoad(M2C_UNK arg_sp0)
{
	S12BoneConstVoidCursor var_r27;
	const void** var_r28_2;
	S12BoneConstCharCursor var_r29;
	S12BoneIntCursor var_r28;
	s32 temp_r31;
	s32 var_r24;
	s32 var_r25;
	s32 var_r25_2;
	S12BoneIntCursor var_r26;
	s32* var_r29_2;

	if (M2C_FIELD(lbl_8042C1D0, void**, 0x8C18) == NULL) {
		goto end;
	}
	fn_801A4C84();
	goto body;
end:
	return;
body: {
	temp_r31 = M2C_FIELD(lbl_8042C298, s32*, 0xA50);
	fn_800BC9F4(temp_r31, &lbl_802FF5A0);
	var_r25       = 0;
	var_r29.value = lbl_8_data_18F58;
	var_r28.value = lbl_8_bss_1DB0;
	do {
		*var_r28.value
		    = fn_800BB92C(temp_r31, fn_800BC6CC(temp_r31, *var_r29.value), &lbl_802FF5A0);
		var_r29.value += 1;
		var_r28.value += 1;
		var_r25 += 1;
	} while (var_r25 < 2);
	var_r25_2     = 0;
	var_r27.value = lbl_8_data_19008;
	var_r26.value = &lbl_8_bss_1DB8[0][0];
	do {
		var_r24   = 0;
		var_r28_2 = var_r27.value;
		var_r29_2 = var_r26.value;
	loop_7:
		*var_r29_2 = fn_800BB0D4(temp_r31, fn_800BC6CC(temp_r31, *var_r28_2), &lbl_802FF5A0);
		var_r28_2 += 1;
		var_r29_2 += 1;
		var_r24 += 1;
		if (var_r24 < 2) {
			goto loop_7;
		}
		var_r27.value += 2;
		var_r26.value += 2;
		var_r25_2 += 1;
	} while (var_r25_2 < 3);
}
}

void s12boneObjectCreate(void)
{
	RpHAnimHierarchy* temp_r3_4;
	TObject* temp_r3;
	s32* temp_r4;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	void* temp_r3_2;
	void* temp_r3_3;

	temp_r3 = (TObject*)fn_80018A34(lbl_8042C148, 0x98);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C110);
		fn_8005BE6C(&temp_r3->unk28);
		temp_r3->unk18                 = (M2C_UNK*)lbl_8_data_19134;
		temp_r3->unk2C                 = (u8*)lbl_8_data_19134 + 0x2C;
		temp_r3->unk0                  = lbl_8_data_19088;
		temp_r3->unk1E                 = 0x98;
		temp_r3_2                      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r4                        = M2C_FIELD(temp_r3_2, s32**, 0x2C);
		M2C_FIELD(temp_r3, f32*, 0x30) = (f32)M2C_FIELD(temp_r3_2, f32*, 0);
		temp_r3->unk34                 = M2C_FIELD(temp_r3_2, f32*, 4);
		temp_r3->unk38                 = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3_3                      = M2C_FIELD(temp_r3, void**, 0x28);
		temp_r3->unk3C                 = M2C_FIELD(temp_r3_3, s32*, 0xC);
		temp_r3->unk40                 = M2C_FIELD(temp_r3_3, void**, 0x10);
		temp_r3->unk44                 = M2C_FIELD(temp_r3_3, s32*, 0x14);
		temp_r3->unk48                 = M2C_FIELD(temp_r3, f32*, 0x30);
		temp_r3->unk4C                 = temp_r3->unk34;
		temp_r3->unk50                 = temp_r3->unk38;
		temp_r3->unk54                 = *temp_r4;
		temp_r3->unk88                 = fn_80150588(lbl_8_bss_1DB0[0]);
		temp_r0_3
		    = ((u32)(M2C_FIELD(M2C_FIELD(temp_r3, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
		    + 4;
		fn_8005D5C8(temp_r3->unk88, temp_r0_3);
		temp_r3->unk8C = fn_80150588(lbl_8_bss_1DB0[1]);
		temp_r0_3
		    = ((u32)(M2C_FIELD(M2C_FIELD(temp_r3, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
		    + 4;
		fn_8005D5C8(temp_r3->unk8C, temp_r0_3);
		temp_r3->unk58 = 1;
		temp_r3->unk5C = -1;
		temp_r3->unk80 = GetHierarchy__10HAnimClassFP7RpClump(&HAnim, temp_r3->unk88);
		SetHierarchyForAtomic__10HAnimClassFP7RpClumpP16RpHAnimHierarchy(
		    &HAnim, temp_r3->unk88, temp_r3->unk80);
		temp_r3_4 = temp_r3->unk80;
		temp_r3_4->unk0 |= 0x3000;
		fn_8013F3A4(temp_r3->unk80);
		temp_r3->unk70 = 0;
		temp_r0        = temp_r3->unk70;
		if (temp_r0 != -1) {
			temp_r3->unk6C = temp_r0;
			temp_r0_2      = temp_r3->unk54;
			fn_8020C72C(
			    temp_r3->unk80->unk20, lbl_8_bss_1DB8[temp_r0_2][temp_r3->unk6C], temp_r0_2 * 8);
			fn_8020D02C(temp_r3->unk80->unk20, &lbl_8_rodata_2000, lbl_8_rodata_2000);
			temp_r3->unk74 = M2C_FIELD(*temp_r3->unk80->unk20, f32*, 0xC);
			temp_r3->unk78 = 0;
			temp_r3->unk7C = 0;
			temp_r3->unk70 = -1;
		}
		temp_r3->unk84 = SearchNodeFrameFromNodeID__10HAnimClassFP16RpHAnimHierarchyi(
		    &HAnim, temp_r3->unk80, 0x48);
	}
}

void s12boneObjectRegister(void)
{
	const char* temp_r3;
	const char* temp_r3_2;

	s12boneObjectEntry.flags      = 0;
	s12boneObjectEntry.unk18      = 0;
	s12boneObjectEntry.name       = s12boneObjectDisplayName;
	s12boneObjectEntry.load       = (void (*)(void))s12boneObjectLoad;
	s12boneObjectEntry.unload     = (void (*)(void))s12boneObjectUnload;
	s12boneObjectEntry.create     = s12boneObjectCreate;
	s12boneObjectEntry.reset      = s12boneObjectReset;
	s12boneObjectEntry.flags      = 0x20000;
	s12boneObjectEntry.unk18      = 0;
	s12boneObjectEntry.unk20      = 0x1E;
	s12boneObjectEntry.unk1C      = 0x1185;
	s12boneObjectEntry.unk1E      = 2;
	s12boneObjectEntry.unk21      = 0;
	temp_r3                       = s12boneObjectFieldTypes;
	s12boneObjectEntry.fieldTypes = temp_r3;
	s12boneObjectEntry.fieldNames = &s12boneObjectFieldNames;
	if (temp_r3 != NULL) {
		s12boneObjectEntry.flags |= 8;
	} else {
		s12boneObjectEntry.flags &= ~8;
	}
	M2C_FIELD(&s12boneColliObjectEntry, s32*, 0x14)             = 0;
	M2C_FIELD(&s12boneColliObjectEntry, s32*, 0x18)             = 0;
	M2C_FIELD(&s12boneColliObjectEntry, const char**, 0)        = s12boneColliObjectDisplayName;
	M2C_FIELD(&s12boneColliObjectEntry, s32*, 4)                = 0;
	M2C_FIELD(&s12boneColliObjectEntry, s32*, 8)                = 0;
	M2C_FIELD(&s12boneColliObjectEntry, void (**)(), 0xC)       = s12boneColliObjectCreate;
	M2C_FIELD(&s12boneColliObjectEntry, void (**)(void*), 0x10) = s12boneColliObjectReset;
	M2C_FIELD(&s12boneColliObjectEntry, s32*, 0x14)             = 0x20000;
	M2C_FIELD(&s12boneColliObjectEntry, s32*, 0x18)             = 0;
	M2C_FIELD(&s12boneColliObjectEntry, s8*, 0x20)              = 0x1E;
	M2C_FIELD(&s12boneColliObjectEntry, s16*, 0x1C)             = 0x1186;
	M2C_FIELD(&s12boneColliObjectEntry, s16*, 0x1E)             = 2;
	M2C_FIELD(&s12boneColliObjectEntry, s8*, 0x21)              = 0;
	temp_r3_2                                                   = s12boneColliObjectFieldTypes;
	M2C_FIELD(&s12boneColliObjectEntry, const char**, 0x24)     = temp_r3_2;
	M2C_FIELD(&s12boneColliObjectEntry, const char***, 0x28)    = s12boneColliObjectFieldNames;
	if (temp_r3_2 != NULL) {
		M2C_FIELD(&s12boneColliObjectEntry, s32*, 0x14) |= 8;
	} else {
		M2C_FIELD(&s12boneColliObjectEntry, s32*, 0x14) &= ~8;
	}
}

__declspec(section ".ctors") void (*const s12boneObjectCtorEntry)(void) = s12boneObjectRegister;
}
#pragma force_active reset
