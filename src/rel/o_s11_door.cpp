#include "types.h"

// Complete o_s11_door.cpp translation unit. The GameCube object boundary is
// independently corroborated by the PS2 TObjS11Door method family and ends at
// the following celestial-sphere object's first function.

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
	/* 0xD0 */ s32 unkD0;        /* inferred */
	/* 0xD4 */ s32 unkD4;        /* inferred */
	/* 0xD8 */ s32 unkD8;        /* inferred */
	/* 0xDC */ s32 unkDC;        /* inferred */
	/* 0xE0 */ s32 unkE0;        /* inferred */
	/* 0xE4 */ s32 unkE4;        /* inferred */
	/* 0xE8 */ s32 unkE8;        /* inferred */
	/* 0xEC */ s32 unkEC;        /* inferred */
	/* 0xF0 */ s32 unkF0;        /* inferred */
	/* 0xF4 */ void* unkF4;      /* inferred */
	/* 0xF8 */ void* unkF8;      /* inferred */
} TObject;                       /* size >= 0xFC */

extern "C" {

void* __ct__7TObjectFP7TObject(TObject* self, TObject* arg0); /* extern */
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);       /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                        /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                        /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                           /* extern */
u32 fn_80018A34(s32, M2C_UNK);                                /* extern */
M2C_UNK fn_80021384(void*);                                   /* extern */
M2C_UNK fn_8003BC38(void*);                                   /* extern */
M2C_UNK fn_8003C200(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                                /* extern */
s32 fn_8005B8BC(void*);                                       /* extern */
s32 fn_8005B8D8(M2C_UNK*);                                    /* extern */
s32 fn_8005B9F0(void*);                                       /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                                /* extern */
M2C_UNK fn_8005D5C8(u32, s32);                                /* extern */
M2C_UNK fn_800B52E8(M2C_UNK, s8, M2C_UNK);                    /* extern */
u32 fn_800BB92C(s32, s32, M2C_UNK*);                          /* extern */
s32 fn_800BC6CC(s32, s32);                                    /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                           /* extern */
f32 fn_800D7AE4(s32);                                         /* extern */
f32 fn_800D7B00(s32);                                         /* extern */
s32 fn_80100C88(u8);                                          /* extern */
u32 fn_80150588(u32);                                         /* extern */
M2C_UNK fn_80150958(void*);                                   /* extern */
M2C_UNK fn_8015BB08(s32, u32);                                /* extern */
M2C_UNK fn_8015BBF8(s32);                                     /* extern */
M2C_UNK fn_80195790(s32, M2C_UNK*, M2C_UNK, f32, f32);        /* extern */
M2C_UNK fn_8019E880(s32);                                     /* extern */
M2C_UNK fn_8019EB94(s32, f32*, M2C_UNK);                      /* extern */
M2C_UNK fn_801A4C84();                                        /* extern */
M2C_UNK fn_8_94F2C(s32);                                      /* extern */
s32 objGroupAllActive();                                      /* extern */
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_802FF5A0;
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u32 lbl_8042C388;
extern u8 lbl_8_data_15130;
extern u8 lbl_8_data_15131;
extern u32 lbl_8_data_15134;
extern s32 lbl_8_data_15164;
extern M2C_UNK lbl_8_data_1516C;
extern s32 lbl_8_data_15174;
extern f32 lbl_8_data_15178;
extern f32 lbl_8_data_1517C;
extern f32 lbl_8_data_15180;
extern f32 lbl_8_data_15184;
extern s32 lbl_8_data_15188;
extern M2C_UNK lbl_8_data_151B4;
extern M2C_UNK lbl_8_data_151BC;
extern M2C_UNK lbl_8_data_1524C;
extern s32 lbl_8_data_152E8;
extern M2C_UNK lbl_8_rodata_1634;
extern f32 lbl_8_rodata_164C;
extern f32 lbl_8_rodata_1650;
extern M2C_UNK s11doorObjectDisplayName;
extern M2C_UNK s11doorObjectEntry;
extern s32 s11doorObjectFieldNames;
extern M2C_UNK s11doorObjectFieldTypes;
extern M2C_UNK s11doorObjectVtable;

void fn_8_95240(s32 arg0)
{
	fn_8_94F2C(arg0 - 0x28);
}

void fn_8_95248(void* arg0)
{
	s32 var_r28;
	void* var_r29;

	var_r28 = 0;
	var_r29 = arg0;
	do {
		if ((void*)M2C_FIELD(var_r29, void**, 0xF4) != NULL) {
			fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
			fn_80150958(M2C_FIELD(var_r29, void**, 0xF4));
			M2C_FIELD(var_r29, void**, 0xF4) = NULL;
		}
		var_r29 = (u8*)var_r29 + 4;
		var_r28 += 1;
	} while (var_r28 < 2);
}

void fn_8_952CC(void* arg0, M2C_UNK arg_sp0)
{
	s32 var_r28;
	u32* var_r29;
	void* var_r30;

	var_r28 = 0;
	var_r30 = arg0;
	var_r29 = &lbl_8_data_15134;
	do {
		if ((u32)M2C_FIELD(var_r30, u32*, 0xF4) == 0U) {
			M2C_FIELD(var_r30, u32*, 0xF4) = fn_80150588(*var_r29);
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C), M2C_FIELD(var_r30, u32*, 0xF4));
			fn_8005D5C8(M2C_FIELD(var_r30, u32*, 0xF4),
			    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
			        + 4);
		}
		var_r30 = (u8*)var_r30 + 4;
		var_r29 += 4;
		var_r28 += 1;
	} while (var_r28 < 2);
}

void fn_8_9536C(void* arg0)
{
	s32 sp1C;
	s32 sp18;
	f32 sp14;
	s32 sp10;
	s32 spC;
	f32 sp8;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	f32 temp_f31_5;
	f32 temp_f31_6;
	s32 temp_r30;
	s32 temp_r30_2;

	sp8      = M2C_FIELD(&lbl_8_rodata_1634, f32*, 0);
	spC      = M2C_FIELD(&lbl_8_rodata_1634, s32*, 4);
	sp10     = M2C_FIELD(&lbl_8_rodata_1634, s32*, 8);
	sp14     = M2C_FIELD(&lbl_8_rodata_1634, f32*, 0xC);
	sp18     = M2C_FIELD(&lbl_8_rodata_1634, s32*, 0x10);
	sp1C     = M2C_FIELD(&lbl_8_rodata_1634, s32*, 0x14);
	temp_r30 = M2C_FIELD(M2C_FIELD(arg0, void**, 0xF4), s32*, 4);
	fn_8019EB94(temp_r30, (f32*)((u8*)arg0 + 0xB8), 0);
	temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
	fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1,
	    lbl_8_rodata_164C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f31);
	fn_8019E880(temp_r30);
	if ((s32)M2C_FIELD(arg0, s32*, 0xD8) == 1) {
		temp_f31_2 = fn_800D7B00(0x8000);
		fn_80195790(
		    temp_r30 + 0x10, &lbl_80239990, 1, lbl_8_rodata_164C - fn_800D7AE4(0x8000), temp_f31_2);
		fn_8019E880(temp_r30);
	}
	fn_8019EB94(temp_r30, &sp8, 1);
	temp_f31_3 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xEC));
	fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1,
	    lbl_8_rodata_164C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xEC)), temp_f31_3);
	fn_8019E880(temp_r30);
	temp_r30_2 = M2C_FIELD(M2C_FIELD(arg0, void**, 0xF8), s32*, 4);
	fn_8019EB94(temp_r30_2, (f32*)((u8*)arg0 + 0xB8), 0);
	temp_f31_4 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
	fn_80195790(temp_r30_2 + 0x10, &lbl_80239984, 1,
	    lbl_8_rodata_164C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f31_4);
	fn_8019E880(temp_r30_2);
	if ((s32)M2C_FIELD(arg0, s32*, 0xD8) == 1) {
		temp_f31_5 = fn_800D7B00(0x8000);
		fn_80195790(temp_r30_2 + 0x10, &lbl_80239990, 1, lbl_8_rodata_164C - fn_800D7AE4(0x8000),
		    temp_f31_5);
		fn_8019E880(temp_r30_2);
	}
	fn_8019EB94(temp_r30_2, &sp14, 1);
	temp_f31_6 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xF0));
	fn_80195790(temp_r30_2 + 0x10, &lbl_80239984, 1,
	    lbl_8_rodata_164C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xF0)), temp_f31_6);
	fn_8019E880(temp_r30_2);
}

void fn_8_955F4(void* arg0)
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
	if ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x10000) != 0) {
		M2C_FIELD(arg0, s32*, 0xD0) = 2;
	} else {
		M2C_FIELD(arg0, s32*, 0xD0) = 0;
	}
	M2C_FIELD(arg0, s32*, 0xD8) = (s32)(s8)*M2C_FIELD(temp_r4, u8**, 0x2C);
	M2C_FIELD(arg0, s32*, 0xD4) = 0;
}

void fn_8_95678(void) { }

u8 fn_8_9567C(void* arg0)
{
	u8 var_r3;
	void* temp_r4;
	void* temp_r5;

	temp_r5 = M2C_FIELD(arg0, void**, 0x28);
	temp_r4 = M2C_FIELD(((u8*)lbl_8042C298 + (M2C_FIELD(temp_r5, u8*, 0x2A) * 4)), void**, 0x30);
	var_r3  = 0;
	if ((temp_r4 == temp_r5) && ((u32)M2C_FIELD(temp_r4, u32*, 0x38) == 0U)) {
		var_r3 = 1;
	}
	return var_r3;
}

void fn_8_956C0(void* arg0)
{
	s32 sp1C;
	s32 sp18;
	f32 sp14;
	s32 sp10;
	s32 spC;
	f32 sp8;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	f32 temp_f31_5;
	f32 temp_f31_6;
	s32 temp_r0;
	s32 temp_r30;
	s32 temp_r30_2;
	u8 var_r4;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;
	void* temp_r5;
	void* temp_r6;

	if ((fn_8005B9F0((u8*)arg0 + 0x28) != 0) || (fn_8005B8BC((u8*)arg0 + 0x28) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	temp_r0 = M2C_FIELD(arg0, s32*, 0xD0);
	switch (temp_r0) { /* irregular */
		case 0:
			temp_r6 = M2C_FIELD(arg0, void**, 0x28);
			temp_r5 = M2C_FIELD(
			    ((u8*)lbl_8042C298 + (M2C_FIELD(temp_r6, u8*, 0x2A) * 4)), void**, 0x30);
			var_r4 = 0;
			if ((temp_r5 == temp_r6) && ((u32)M2C_FIELD(temp_r5, u32*, 0x38) == 0U)) {
				var_r4 = 1;
			}
			if (((var_r4 != 0) || (objGroupAllActive() != 0))
			    && (fn_80100C88(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), u8*, 0x2A)) != 0)) {
				M2C_FIELD(arg0, s32*, 0xD0) = 1;
				if ((u32)lbl_8042C388 != 0U) {
					fn_800B52E8(0x5A02, (s8)lbl_8_data_15130, 0);
				}
				temp_r3                        = M2C_FIELD(arg0, void**, 0x28);
				M2C_FIELD(temp_r3, s32*, 0x18) = (s32)(M2C_FIELD(temp_r3, s32*, 0x18) | 0x10000);
				M2C_FIELD(arg0, s32*, 0xD4)    = 0;
			}
			break;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0xDC) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = (s32)(M2C_FIELD(arg0, s32*, 0xD4) + 1);
				if ((s32)M2C_FIELD(arg0, s32*, 0xD4) == (s32)lbl_8_data_15188) {
					temp_r3_2                     = M2C_FIELD(arg0, void**, 0x40);
					M2C_FIELD(temp_r3_2, s32*, 4) = (s32)(M2C_FIELD(temp_r3_2, s32*, 4) | 0x10);
					temp_r3_3                     = M2C_FIELD(arg0, void**, 0x40);
					M2C_FIELD(temp_r3_3, s32*, 0x34)
					    = (s32)(M2C_FIELD(temp_r3_3, s32*, 0x34) & 0xFFFFFFEF);
					fn_80021384((u8*)arg0 + 0x30);
				}
				M2C_FIELD(arg0, s32*, 0xE4) = (s32)(M2C_FIELD(arg0, s32*, 0xE4) - lbl_8_data_15174);
				M2C_FIELD(arg0, s32*, 0xE4)
				    = (s32)((f32)M2C_FIELD(arg0, s32*, 0xE4) * lbl_8_data_15178);
				M2C_FIELD(arg0, s32*, 0xEC)
				    = (s32)(M2C_FIELD(arg0, s32*, 0xEC) + M2C_FIELD(arg0, s32*, 0xE4));
				if ((s32)M2C_FIELD(arg0, s32*, 0xEC) < (s32)M2C_FIELD(&lbl_8_data_1516C, s32*, 0)) {
					M2C_FIELD(arg0, s32*, 0xDC) = 1;
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B52E8(0x5A03, (s8)lbl_8_data_15131, 0);
					}
					M2C_FIELD(arg0, s32*, 0xE4)
					    = (s32)((f32)M2C_FIELD(arg0, s32*, 0xE4) * lbl_8_data_1517C);
					M2C_FIELD(arg0, s32*, 0xD4) = 0;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0xE4) = (s32)((f32)M2C_FIELD(arg0, s32*, 0xE4)
				    + (lbl_8_data_15180
				        * (f32)(M2C_FIELD(arg0, s32*, 0xEC)
				            - M2C_FIELD(&lbl_8_data_1516C, s32*, 0))));
				M2C_FIELD(arg0, s32*, 0xE4)
				    = (s32)((f32)M2C_FIELD(arg0, s32*, 0xE4) * lbl_8_data_15184);
				M2C_FIELD(arg0, s32*, 0xEC)
				    = (s32)(M2C_FIELD(arg0, s32*, 0xEC) + M2C_FIELD(arg0, s32*, 0xE4));
				M2C_FIELD(arg0, s32*, 0xD4) = (s32)(M2C_FIELD(arg0, s32*, 0xD4) + 1);
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0xE0) == 0) {
				if ((s32)M2C_FIELD(arg0, s32*, 0xD4) == (s32)lbl_8_data_15188) {
					temp_r3_4                     = M2C_FIELD(arg0, void**, 0x40);
					M2C_FIELD(temp_r3_4, s32*, 4) = (s32)(M2C_FIELD(temp_r3_4, s32*, 4) | 0x10);
					temp_r3_5                     = M2C_FIELD(arg0, void**, 0x40);
					M2C_FIELD(temp_r3_5, s32*, 0x64)
					    = (s32)(M2C_FIELD(temp_r3_5, s32*, 0x64) & 0xFFFFFFEF);
					fn_80021384((u8*)arg0 + 0x30);
				}
				M2C_FIELD(arg0, s32*, 0xE8) = (s32)(M2C_FIELD(arg0, s32*, 0xE8) + lbl_8_data_15174);
				M2C_FIELD(arg0, s32*, 0xE8)
				    = (s32)((f32)M2C_FIELD(arg0, s32*, 0xE8) * lbl_8_data_15178);
				M2C_FIELD(arg0, s32*, 0xF0)
				    = (s32)(M2C_FIELD(arg0, s32*, 0xF0) + M2C_FIELD(arg0, s32*, 0xE8));
				if ((s32)M2C_FIELD(arg0, s32*, 0xF0) > (s32)M2C_FIELD(&lbl_8_data_1516C, s32*, 4)) {
					M2C_FIELD(arg0, s32*, 0xE0) = 1;
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B52E8(0x5A03, (s8)lbl_8_data_15131, 0);
					}
					M2C_FIELD(arg0, s32*, 0xE8)
					    = (s32)((f32)M2C_FIELD(arg0, s32*, 0xE8) * lbl_8_data_1517C);
				}
			} else {
				M2C_FIELD(arg0, s32*, 0xE8) = (s32)((f32)M2C_FIELD(arg0, s32*, 0xE8)
				    + (lbl_8_data_15180
				        * (f32)(M2C_FIELD(arg0, s32*, 0xF0)
				            - M2C_FIELD(&lbl_8_data_1516C, s32*, 4))));
				M2C_FIELD(arg0, s32*, 0xE8)
				    = (s32)((f32)M2C_FIELD(arg0, s32*, 0xE8) * lbl_8_data_15184);
				M2C_FIELD(arg0, s32*, 0xF0)
				    = (s32)(M2C_FIELD(arg0, s32*, 0xF0) + M2C_FIELD(arg0, s32*, 0xE8));
			}
			if ((f32)M2C_FIELD(arg0, s32*, 0xD4) > lbl_8_rodata_1650) {
				M2C_FIELD(arg0, s32*, 0xD0) = 2;
			}
			sp8      = M2C_FIELD(&lbl_8_rodata_1634, f32*, 0);
			spC      = M2C_FIELD(&lbl_8_rodata_1634, s32*, 4);
			sp10     = M2C_FIELD(&lbl_8_rodata_1634, s32*, 8);
			sp14     = M2C_FIELD(&lbl_8_rodata_1634, f32*, 0xC);
			sp18     = M2C_FIELD(&lbl_8_rodata_1634, s32*, 0x10);
			sp1C     = M2C_FIELD(&lbl_8_rodata_1634, s32*, 0x14);
			temp_r30 = M2C_FIELD(M2C_FIELD(arg0, void**, 0xF4), s32*, 4);
			fn_8019EB94(temp_r30, (f32*)((u8*)arg0 + 0xB8), 0);
			temp_f31 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
			fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1,
			    lbl_8_rodata_164C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f31);
			fn_8019E880(temp_r30);
			if ((s32)M2C_FIELD(arg0, s32*, 0xD8) == 1) {
				temp_f31_2 = fn_800D7B00(0x8000);
				fn_80195790(temp_r30 + 0x10, &lbl_80239990, 1,
				    lbl_8_rodata_164C - fn_800D7AE4(0x8000), temp_f31_2);
				fn_8019E880(temp_r30);
			}
			fn_8019EB94(temp_r30, &sp8, 1);
			temp_f31_3 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xEC));
			fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1,
			    lbl_8_rodata_164C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xEC)), temp_f31_3);
			fn_8019E880(temp_r30);
			temp_r30_2 = M2C_FIELD(M2C_FIELD(arg0, void**, 0xF8), s32*, 4);
			fn_8019EB94(temp_r30_2, (f32*)((u8*)arg0 + 0xB8), 0);
			temp_f31_4 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
			fn_80195790(temp_r30_2 + 0x10, &lbl_80239984, 1,
			    lbl_8_rodata_164C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f31_4);
			fn_8019E880(temp_r30_2);
			if ((s32)M2C_FIELD(arg0, s32*, 0xD8) == 1) {
				temp_f31_5 = fn_800D7B00(0x8000);
				fn_80195790(temp_r30_2 + 0x10, &lbl_80239990, 1,
				    lbl_8_rodata_164C - fn_800D7AE4(0x8000), temp_f31_5);
				fn_8019E880(temp_r30_2);
			}
			fn_8019EB94(temp_r30_2, &sp14, 1);
			temp_f31_6 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xF0));
			fn_80195790(temp_r30_2 + 0x10, &lbl_80239984, 1,
			    lbl_8_rodata_164C - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xF0)), temp_f31_6);
			fn_8019E880(temp_r30_2);
			break;
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
	fn_8003BC38((u8*)arg0 + 0x30);
}

TObject* s11doorObjectDtor(TObject* arg0, s16 arg1, M2C_UNK arg_sp0)
{
	TObject* var_r28;
	s32 var_r29;

	if (arg0 != NULL) {
		arg0->unk18 = &s11doorObjectVtable;
		arg0->unk2C = &s11doorObjectVtable + 0x2C;
		var_r29     = 0;
		var_r28     = arg0;
		do {
			if ((void*)var_r28->unkF4 != NULL) {
				fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
				fn_80150958(var_r28->unkF4);
				var_r28->unkF4 = NULL;
			}
			var_r28 = (TObject*)((u8*)var_r28 + 4);
			var_r29 += 1;
		} while (var_r29 < 2);
		dtor_8003C52C((u8*)arg0 + 0x30, 0);
		dtor_8005BD3C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_96018(TObject* arg0, TObject* arg1)
{
	s32 sp1C;
	s32 sp18;
	f32 sp14;
	s32 sp10;
	s32 spC;
	f32 sp8;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	f32 temp_f31_5;
	f32 temp_f31_6;
	s32 temp_r0;
	s32 temp_r28;
	s32 temp_r30;
	s32 var_r29;
	s32 var_r30;
	u32* var_r28;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	fn_8003C618(&arg0->unk30);
	arg0->unk18 = &s11doorObjectVtable;
	arg0->unk2C = &s11doorObjectVtable + 0x2C;
	arg0->unk0  = lbl_8_data_152E8;
	arg0->unk1E = 0xFC;
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
	if ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x10000) != 0) {
		arg0->unkD0 = 2;
	} else {
		arg0->unkD0 = 0;
	}
	arg0->unkD8 = (s32)(s8)*M2C_FIELD(temp_r3, u8**, 0x2C);
	arg0->unkD4 = 0;
	arg0->unkF8 = NULL;
	arg0->unkF4 = NULL;
	arg0->unkE8 = 0;
	arg0->unkE4 = 0;
	arg0->unkE0 = 0;
	arg0->unkDC = 0;
	if ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x10000) != 0) {
		arg0->unkEC = M2C_FIELD(&lbl_8_data_1516C, s32*, 0);
		arg0->unkF0 = M2C_FIELD(&lbl_8_data_1516C, s32*, 4);
	} else {
		arg0->unkF0 = 0;
		arg0->unkEC = 0;
	}
	var_r30 = 0;
	var_r29 = 0;
	var_r28 = &lbl_8_data_15134;
	do {
		if (M2C_FIELD(arg0, u32*, var_r29 + 0xF4) == 0U) {
			temp_r0                        = var_r29 + 0xF4;
			M2C_FIELD(arg0, u32*, temp_r0) = fn_80150588(*var_r28);
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C), M2C_FIELD(arg0, u32*, temp_r0));
			fn_8005D5C8(M2C_FIELD(arg0, u32*, var_r29 + 0xF4),
			    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
			        + 4);
		}
		var_r29 += 4;
		var_r28 += 4;
		var_r30 += 1;
	} while (var_r30 < 2);
	sp8      = M2C_FIELD(&lbl_8_rodata_1634, f32*, 0);
	spC      = M2C_FIELD(&lbl_8_rodata_1634, s32*, 4);
	sp10     = M2C_FIELD(&lbl_8_rodata_1634, s32*, 8);
	sp14     = M2C_FIELD(&lbl_8_rodata_1634, f32*, 0xC);
	sp18     = M2C_FIELD(&lbl_8_rodata_1634, s32*, 0x10);
	sp1C     = M2C_FIELD(&lbl_8_rodata_1634, s32*, 0x14);
	temp_r30 = M2C_FIELD(arg0->unkF4, s32*, 4);
	fn_8019EB94(temp_r30, &arg0->unkB8, 0);
	temp_f31 = fn_800D7B00(arg0->unkC8);
	fn_80195790(
	    temp_r30 + 0x10, &lbl_80239984, 1, lbl_8_rodata_164C - fn_800D7AE4(arg0->unkC8), temp_f31);
	fn_8019E880(temp_r30);
	if ((s32)arg0->unkD8 == 1) {
		temp_f31_2 = fn_800D7B00(0x8000);
		fn_80195790(
		    temp_r30 + 0x10, &lbl_80239990, 1, lbl_8_rodata_164C - fn_800D7AE4(0x8000), temp_f31_2);
		fn_8019E880(temp_r30);
	}
	fn_8019EB94(temp_r30, &sp8, 1);
	temp_f31_3 = fn_800D7B00(arg0->unkEC);
	fn_80195790(temp_r30 + 0x10, &lbl_80239984, 1, lbl_8_rodata_164C - fn_800D7AE4(arg0->unkEC),
	    temp_f31_3);
	fn_8019E880(temp_r30);
	temp_r28 = M2C_FIELD(arg0->unkF8, s32*, 4);
	fn_8019EB94(temp_r28, &arg0->unkB8, 0);
	temp_f31_4 = fn_800D7B00(arg0->unkC8);
	fn_80195790(temp_r28 + 0x10, &lbl_80239984, 1, lbl_8_rodata_164C - fn_800D7AE4(arg0->unkC8),
	    temp_f31_4);
	fn_8019E880(temp_r28);
	if ((s32)arg0->unkD8 == 1) {
		temp_f31_5 = fn_800D7B00(0x8000);
		fn_80195790(
		    temp_r28 + 0x10, &lbl_80239990, 1, lbl_8_rodata_164C - fn_800D7AE4(0x8000), temp_f31_5);
		fn_8019E880(temp_r28);
	}
	fn_8019EB94(temp_r28, &sp14, 1);
	temp_f31_6 = fn_800D7B00(arg0->unkF0);
	fn_80195790(temp_r28 + 0x10, &lbl_80239984, 1, lbl_8_rodata_164C - fn_800D7AE4(arg0->unkF0),
	    temp_f31_6);
	fn_8019E880(temp_r28);
	if (fn_8005B8D8(&arg0->unk28) == 0) {
		if ((s32)arg0->unkD8 == 1) {
			fn_8003C200(&arg0->unk30, &lbl_8_data_1524C, 3, 4);
		} else {
			fn_8003C200(&arg0->unk30, &lbl_8_data_151BC, 3, 4);
		}
		if ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x10000) != 0) {
			temp_r3_3                        = arg0->unk40;
			M2C_FIELD(temp_r3_3, s32*, 4)    = (s32)(M2C_FIELD(temp_r3_3, s32*, 4) | 0x10);
			temp_r3_4                        = arg0->unk40;
			M2C_FIELD(temp_r3_4, s32*, 0x34) = (s32)(M2C_FIELD(temp_r3_4, s32*, 0x34) & 0xFFFFFFEF);
			temp_r3_5                        = arg0->unk40;
			M2C_FIELD(temp_r3_5, s32*, 0x64) = (s32)(M2C_FIELD(temp_r3_5, s32*, 0x64) & 0xFFFFFFEF);
			fn_80021384(&arg0->unk30);
		}
	}
	return arg0;
}

void fn_8_964DC(void* arg1)
{
	u8* temp_r3;

	temp_r3 = M2C_FIELD(arg1, u8**, 0x2C);
	if ((s8)*temp_r3 < 0) {
		*temp_r3 = 0;
	}
	if ((s8)*temp_r3 > 1) {
		*temp_r3 = 1;
	}
	s11doorObjectFieldNames = *(&lbl_8_data_151B4 + ((s8)*temp_r3 * 4));
}

void s11doorObjectUnload(void)
{
	s32 var_r29;
	u32* var_r30;

	var_r29 = 0;
	var_r30 = &lbl_8_data_15134;
	do {
		if ((u32)*var_r30 != 0U) {
			fn_80150958((void*)*var_r30);
			*var_r30 = 0U;
		}
		var_r30 += 4;
		var_r29 += 1;
	} while (var_r29 < 2);
}

void s11doorObjectLoad(M2C_UNK arg_sp0)
{
	s32* var_r29;
	s32 var_r27;
	u32* var_r28;

	if ((u32)M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18) != 0U) {
		fn_801A4C84();
		fn_800BC9F4(M2C_FIELD(lbl_8042C298, s32*, 0xA50), &lbl_802FF5A0);
		var_r27 = 0;
		var_r29 = &lbl_8_data_15164;
		var_r28 = &lbl_8_data_15134;
		do {
			*var_r28 = fn_800BB92C(M2C_FIELD(lbl_8042C298, s32*, 0xA50),
			    fn_800BC6CC(M2C_FIELD(lbl_8042C298, s32*, 0xA50), *var_r29), &lbl_802FF5A0);
			var_r29 += 4;
			var_r28 += 4;
			var_r27 += 1;
		} while (var_r27 < 2);
	}
}

void s11doorObjectCreate(void)
{
	TObject* object = (TObject*)fn_80018A34(lbl_8042C148, 0xFC);
	if (object != NULL) {
		fn_8_96018(object, lbl_8042C110);
	}
}

void s11doorObjectRegister(void)
{
	s32 flags;

	M2C_FIELD(&s11doorObjectEntry, s32*, 0x14)            = 0;
	M2C_FIELD(&s11doorObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&s11doorObjectEntry, M2C_UNK**, 0)          = &s11doorObjectDisplayName;
	M2C_FIELD(&s11doorObjectEntry, void (**)(M2C_UNK), 4) = s11doorObjectLoad;
	M2C_FIELD(&s11doorObjectEntry, void (**)(), 8)        = s11doorObjectUnload;
	M2C_FIELD(&s11doorObjectEntry, void (**)(), 0xC)      = s11doorObjectCreate;
	M2C_FIELD(&s11doorObjectEntry, s32*, 0x10)            = 0;
	flags                                                 = 0x20000;
	M2C_FIELD(&s11doorObjectEntry, s32*, 0x14)            = flags;
	M2C_FIELD(&s11doorObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&s11doorObjectEntry, s8*, 0x20)             = 0x1E;
	M2C_FIELD(&s11doorObjectEntry, s16*, 0x1C)            = 0x1101;
	M2C_FIELD(&s11doorObjectEntry, s16*, 0x1E)            = 2;
	M2C_FIELD(&s11doorObjectEntry, s8*, 0x21)             = 0;
	M2C_FIELD(&s11doorObjectEntry, M2C_UNK**, 0x24)       = &s11doorObjectFieldTypes;
	M2C_FIELD(&s11doorObjectEntry, s32**, 0x28)           = &s11doorObjectFieldNames;
	if (&s11doorObjectFieldTypes != NULL) {
		M2C_FIELD(&s11doorObjectEntry, s32*, 0x14) = flags | 8;
		return;
	}
	M2C_FIELD(&s11doorObjectEntry, s32*, 0x14) = flags & ~8;
}
}
