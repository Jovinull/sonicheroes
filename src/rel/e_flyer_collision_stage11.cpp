#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)

typedef struct TObject {
	/* 0x00 */ M2C_UNK* unk0;   /* inferred */
	/* 0x04 */ char pad4[0x14]; /* maybe part of unk0[6]? */
	/* 0x18 */ M2C_UNK* unk18;  /* inferred */
	/* 0x1C */ char pad1C[2];
	/* 0x1E */ s16 unk1E;     /* inferred */
	/* 0x20 */ char pad20[8]; /* maybe part of unk1E[5]? */
	/* 0x28 */ M2C_UNK unk28; /* inferred */
	/* 0x28 */ char pad28[0x10];
	/* 0x38 */ void* unk38;      /* inferred */
	/* 0x3C */ char pad3C[0x4C]; /* maybe part of unk38[0x14]? */
	/* 0x88 */ f32 unk88;        /* inferred */
	/* 0x8C */ f32 unk8C;        /* inferred */
	/* 0x90 */ f32 unk90;        /* inferred */
	/* 0x94 */ char pad94[0x1C]; /* maybe part of unk90[8]? */
	/* 0xB0 */ M2C_UNK unkB0;    /* inferred */
	/* 0xB0 */ char padB0[4];
	/* 0xB4 */ void* unkB4;   /* inferred */
	/* 0xB8 */ f32 unkB8;     /* inferred */
	/* 0xBC */ f32 unkBC;     /* inferred */
	/* 0xC0 */ f32 unkC0;     /* inferred */
	/* 0xC4 */ s32 unkC4;     /* inferred */
	/* 0xC8 */ s32 unkC8;     /* inferred */
	/* 0xCC */ s32 unkCC;     /* inferred */
	/* 0xD0 */ u8 unkD0;      /* inferred */
	/* 0xD1 */ char padD1[3]; /* maybe part of unkD0[4]? */
	/* 0xD4 */ s32 unkD4;     /* inferred */
	/* 0xD8 */ f32 unkD8;     /* inferred */
	/* 0xDC */ f32 unkDC;     /* inferred */
	/* 0xE0 */ f32 unkE0;     /* inferred */
} TObject;                    /* size >= 0xE4 */

void* __ct__7TObjectFP7TObject(TObject* self, TObject* arg0); /* extern */
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);       /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                        /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                        /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                           /* extern */
TObject* fn_80018A34(s32, M2C_UNK);                           /* extern */
void* fn_800211A8(void*);                                     /* extern */
M2C_UNK fn_80021384(void*);                                   /* extern */
M2C_UNK fn_80021824(M2C_UNK*);                                /* extern */
M2C_UNK fn_8003BC38(void*);                                   /* extern */
M2C_UNK fn_8003C200(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                                /* extern */
s32 fn_8005B8BC(void*);                                       /* extern */
M2C_UNK fn_8005BC04(void*);                                   /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                                /* extern */
M2C_UNK fn_800A31B8(s32);                                     /* extern */
M2C_UNK fn_80100D24(s8*, void*, ...);                         /* extern */
M2C_UNK fn_8_A6728(s32);                                      /* extern */
void flyerColObjectCreate();                                  /* static */
void flyerColObjectLoad();                                    /* static */
void flyerColObjectUnload();                                  /* static */
s32 fn_8_A74CC(void* arg0);                                   /* static */
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern M2C_UNK lbl_8042C1A4;
extern s32 lbl_8042C298;
static M2C_UNK lbl_8_data_162C8;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_162F8;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016303_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16304;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001630F_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16310;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016317_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16318;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016321_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16324;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001632D_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16330;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016339_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1633C;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016345_data; /* unable to generate initializer: unknown type */
static M2C_UNK* flyerColObjectFieldNames[9] = {
	&lbl_8_data_162F8,
	&lbl_8_data_16304,
	&lbl_8_data_16304,
	&lbl_8_data_16304,
	&lbl_8_data_16310,
	&lbl_8_data_16318,
	&lbl_8_data_16324,
	&lbl_8_data_16330,
	&lbl_8_data_1633C,
};
static M2C_UNK lbl_8_data_1636C;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016372_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16374;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16378;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001637D_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16380;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16388;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16394;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016399_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_1639C[6] = {
	&lbl_8_data_1636C,
	&lbl_8_data_16374,
	&lbl_8_data_16378,
	&lbl_8_data_16380,
	&lbl_8_data_16388,
	&lbl_8_data_16394,
};
static u8 lbl_8_data_163B4 = 0;
static u8 lbl_8_data_163B5 = 5;
static M2C_UNK gap_04_000163B6_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_163B8;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000163CB_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_163CC = &lbl_8_data_163B8;
static M2C_UNK lbl_8_data_163D0;          /* unable to generate initializer: unknown type */
static M2C_UNK flyerColObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001641D_data;      /* unable to generate initializer: unknown type */
static M2C_UNK flyerColObjectFieldTypes;  /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001642A_data;      /* unable to generate initializer: unknown type */
static M2C_UNK flyerColObjectEntry;
static f32 lbl_8_rodata_198C;
static s32 lbl_8_rodata_1990    = 0;                           /* const */
static s32 lbl_8_rodata_1994[4] = { 0x100, 0, 0x3FC00000, 0 }; /* const */

void fn_8_A6D1C(s32 arg0)
{
	fn_8_A6728(arg0 - 0xB0);
}

s32 fn_8_A6D24(s32 arg0)
{
	return arg0 + 0x268;
}

void fn_8_A6D2C(void* arg0, s32 arg1)
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

s32 fn_8_A6DC4(void* arg0)
{
	void* temp_r0;
	void* var_r3;

	if (fn_8005B8BC((u8*)arg0 + 0xB0) != 0) {
		return 1;
	}
	temp_r0 = M2C_FIELD(
	    (lbl_8042C298 + (M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A) * 4)), void**, 0x30);
	var_r3 = temp_r0;
	if (temp_r0 == NULL) {
		return 1;
	}
loop_8:
	if (var_r3 == NULL) {
		return 1;
	}
	if ((u16)M2C_FIELD(var_r3, u16*, 0x28) == 0x1530) {
		return 0;
	}
	var_r3 = M2C_FIELD(var_r3, void**, 0x38);
	goto loop_8;
}

s32 fn_8_A6E60(void* arg0)
{
	s16 temp_r0;
	s16 var_ctr;
	void* temp_r4;
	void* var_r3;

	var_r3 = arg0;
	if ((s32)(M2C_FIELD(var_r3, u16*, 0x30) & 1) != 0) {
		temp_r0 = M2C_FIELD(var_r3, s16*, 0x2A);
		var_ctr = temp_r0;
		if (temp_r0 > 0) {
		loop_2:
			temp_r4 = M2C_FIELD(var_r3, void**, 0x40);
			if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x18)) {
				return 1;
			}
			var_r3 = (u8*)var_r3 + 8;
			var_ctr -= 1;
			if (var_ctr == 0) {
				/* Duplicate return node #6. Try simplifying control flow for better match */
				return 0;
			}
			goto loop_2;
		}
	}
	return 0;
}

s32 fn_8_A6EB4(void* arg0)
{
	u32 var_r0;
	void* temp_r3;

	if ((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0) {
		fn_80021824(&lbl_8042C1A4);
		temp_r3 = fn_800211A8((u8*)arg0 + 0x28);
		if (temp_r3 != NULL) {
			var_r0 = M2C_FIELD(temp_r3, u32*, 4);
		} else {
			var_r0 = 0U;
		}
		if (var_r0 != 0U) {
			return 1;
		}
		goto block_6;
	}
block_6:
	return 0;
}

s32 fn_8_A6F28(void* arg0)
{
	s32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	s32 spC;
	u8 sp9;
	s8 sp8;
	s16 temp_r0;
	s16 var_ctr;
	s32 var_r31;
	void* temp_r4;
	void* temp_r6;
	void* var_r5;

	if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
	    && (var_r5 = arg0, temp_r0 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr = temp_r0,
	        ((temp_r0 > 0) != 0))) {
	loop_2:
		temp_r4 = M2C_FIELD(var_r5, void**, 0x40);
		if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x18)) {
			var_r31 = 1;
		} else {
			var_r5 = (u8*)var_r5 + 8;
			var_ctr -= 1;
			if (var_ctr == 0) {
				goto block_6;
			}
			goto loop_2;
		}
	} else {
	block_6:
		var_r31 = 0;
	}
	if (var_r31 != 0) {
		temp_r6 = M2C_FIELD(arg0, void**, 0xB0);
		if (temp_r6 != NULL) {
			sp8  = 0;
			sp9  = 0;
			sp8  = 5;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp1C = M2C_FIELD(arg0, s32*, 0xD4);
			sp9  = M2C_FIELD(temp_r6, u8*, 0x2A);
			spC  = 6;
			fn_80100D24(&sp8, &lbl_8_rodata_198C, 0);
		}
	}
	return var_r31;
}

s32 fn_8_A700C(void* arg0)
{
	s32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	s32 spC;
	u8 sp9;
	s8 sp8;
	s16 temp_r0;
	s16 var_ctr;
	s32 var_r31;
	void* temp_r4;
	void* temp_r6;
	void* var_r5;

	if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
	    && (var_r5 = arg0, temp_r0 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr = temp_r0,
	        ((temp_r0 > 0) != 0))) {
	loop_2:
		temp_r4 = M2C_FIELD(var_r5, void**, 0x40);
		if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x18)) {
			var_r31 = 1;
		} else {
			var_r5 = (u8*)var_r5 + 8;
			var_ctr -= 1;
			if (var_ctr == 0) {
				goto block_6;
			}
			goto loop_2;
		}
	} else {
	block_6:
		var_r31 = 0;
	}
	if (var_r31 != 0) {
		temp_r6 = M2C_FIELD(arg0, void**, 0xB0);
		if (temp_r6 != NULL) {
			sp8  = 0;
			sp9  = 0;
			sp8  = 5;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp1C = M2C_FIELD(arg0, s32*, 0xD4);
			sp9  = M2C_FIELD(temp_r6, u8*, 0x2A);
			spC  = 5;
			sp10 = M2C_FIELD(arg0, f32*, 0xD8);
			sp14 = M2C_FIELD(arg0, f32*, 0xDC);
			sp18 = M2C_FIELD(arg0, f32*, 0xE0);
			fn_80100D24(&sp8, &lbl_8_rodata_198C, 5);
		}
	}
	return var_r31;
}

s32 fn_8_A7104(void* arg0)
{
	s32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	s32 spC;
	u8 sp9;
	s8 sp8;
	s16 temp_r0;
	s16 var_ctr;
	s32 var_r31;
	void* temp_r4;
	void* temp_r6;
	void* var_r5;

	if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
	    && (var_r5 = arg0, temp_r0 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr = temp_r0,
	        ((temp_r0 > 0) != 0))) {
	loop_2:
		temp_r4 = M2C_FIELD(var_r5, void**, 0x40);
		if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x18)) {
			var_r31 = 1;
		} else {
			var_r5 = (u8*)var_r5 + 8;
			var_ctr -= 1;
			if (var_ctr == 0) {
				goto block_6;
			}
			goto loop_2;
		}
	} else {
	block_6:
		var_r31 = 0;
	}
	if (var_r31 != 0) {
		temp_r6 = M2C_FIELD(arg0, void**, 0xB0);
		if (temp_r6 != NULL) {
			sp8  = 0;
			sp9  = 0;
			sp8  = 5;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp9  = M2C_FIELD(temp_r6, u8*, 0x2A);
			sp1C = M2C_FIELD(arg0, s32*, 0xD4);
			spC  = 4;
			sp10 = M2C_FIELD(arg0, f32*, 0xD8);
			sp14 = M2C_FIELD(arg0, f32*, 0xDC);
			sp18 = M2C_FIELD(arg0, f32*, 0xE0);
			fn_80100D24(&sp8, &lbl_8_rodata_198C, 0);
		}
	}
	return var_r31;
}

s32 fn_8_A7200(void* arg0)
{
	s32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	s32 spC;
	u8 sp9;
	s8 sp8;
	s16 temp_r0;
	s16 var_ctr;
	s32 var_r31;
	void* temp_r4;
	void* temp_r6;
	void* var_r5;

	if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
	    && (var_r5 = arg0, temp_r0 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr = temp_r0,
	        ((temp_r0 > 0) != 0))) {
	loop_2:
		temp_r4 = M2C_FIELD(var_r5, void**, 0x40);
		if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x18)) {
			var_r31 = 1;
		} else {
			var_r5 = (u8*)var_r5 + 8;
			var_ctr -= 1;
			if (var_ctr == 0) {
				goto block_6;
			}
			goto loop_2;
		}
	} else {
	block_6:
		var_r31 = 0;
	}
	if (var_r31 != 0) {
		temp_r6 = M2C_FIELD(arg0, void**, 0xB0);
		if (temp_r6 != NULL) {
			sp8  = 0;
			sp9  = 0;
			sp8  = 5;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp9  = M2C_FIELD(temp_r6, u8*, 0x2A);
			sp1C = M2C_FIELD(arg0, s32*, 0xD4);
			spC  = 3;
			sp10 = M2C_FIELD(arg0, f32*, 0xD8);
			sp14 = M2C_FIELD(arg0, f32*, 0xDC);
			sp18 = M2C_FIELD(arg0, f32*, 0xE0);
			fn_80100D24(&sp8, &lbl_8_rodata_198C, 0);
		}
	}
	return var_r31;
}

s32 fn_8_A72FC(void* arg0)
{
	s32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	s32 spC;
	u8 sp9;
	s8 sp8;
	s32 var_r31;
	u32 var_r0;
	void* temp_r3;
	void* temp_r5;

	if ((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0) {
		fn_80021824(&lbl_8042C1A4);
		temp_r3 = fn_800211A8((u8*)arg0 + 0x28);
		if (temp_r3 != NULL) {
			var_r0 = M2C_FIELD(temp_r3, u32*, 4);
		} else {
			var_r0 = 0U;
		}
		if (var_r0 != 0U) {
			var_r31 = 1;
		} else {
			goto block_6;
		}
	} else {
	block_6:
		var_r31 = 0;
	}
	if (var_r31 != 0) {
		temp_r5 = M2C_FIELD(arg0, void**, 0xB0);
		if (temp_r5 != NULL) {
			sp8  = 0;
			sp9  = 0;
			sp8  = 5;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp9  = M2C_FIELD(temp_r5, u8*, 0x2A);
			sp1C = M2C_FIELD(arg0, s32*, 0xD4);
			spC  = 2;
			fn_80100D24(&sp8, NULL);
		}
	}
	return var_r31;
}

s32 fn_8_A73E4(void* arg0)
{
	s32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	s32 spC;
	u8 sp9;
	s8 sp8;
	s32 var_r31;
	u32 var_r0;
	void* temp_r3;
	void* temp_r5;

	if ((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0) {
		fn_80021824(&lbl_8042C1A4);
		temp_r3 = fn_800211A8((u8*)arg0 + 0x28);
		if (temp_r3 != NULL) {
			var_r0 = M2C_FIELD(temp_r3, u32*, 4);
		} else {
			var_r0 = 0U;
		}
		if (var_r0 != 0U) {
			var_r31 = 1;
		} else {
			goto block_6;
		}
	} else {
	block_6:
		var_r31 = 0;
	}
	if (var_r31 != 0) {
		temp_r5 = M2C_FIELD(arg0, void**, 0xB0);
		if (temp_r5 != NULL) {
			sp8  = 0;
			sp9  = 0;
			sp8  = 5;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp9  = M2C_FIELD(temp_r5, u8*, 0x2A);
			sp1C = M2C_FIELD(arg0, s32*, 0xD4);
			spC  = 1;
			fn_80100D24(&sp8, NULL);
		}
	}
	return var_r31;
}

s32 fn_8_A74CC(void* arg0)
{
	s32 sp94;
	f32 sp90;
	f32 sp8C;
	f32 sp88;
	s32 sp84;
	u8 sp81;
	s8 sp80;
	s32 sp7C;
	f32 sp78;
	f32 sp74;
	f32 sp70;
	s32 sp6C;
	u8 sp69;
	s8 sp68;
	s32 sp64;
	f32 sp60;
	f32 sp5C;
	f32 sp58;
	s32 sp54;
	u8 sp51;
	s8 sp50;
	s32 sp4C;
	f32 sp48;
	f32 sp44;
	f32 sp40;
	s32 sp3C;
	u8 sp39;
	s8 sp38;
	s32 sp34;
	f32 sp30;
	f32 sp2C;
	f32 sp28;
	s32 sp24;
	u8 sp21;
	s8 sp20;
	s32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	s32 spC;
	u8 sp9;
	s8 sp8;
	s16 temp_r0_2;
	s16 temp_r0_3;
	s16 temp_r0_4;
	s16 temp_r0_5;
	s16 var_ctr;
	s16 var_ctr_2;
	s16 var_ctr_3;
	s16 var_ctr_4;
	s32 var_r30;
	s32 var_r30_2;
	s32 var_r30_3;
	s32 var_r30_4;
	s32 var_r30_5;
	s32 var_r30_6;
	u32 var_r0;
	u32 var_r0_2;
	u8 temp_r0;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;
	void* temp_r3_6;
	void* temp_r5;
	void* temp_r5_2;
	void* temp_r5_3;
	void* temp_r5_4;
	void* temp_r5_5;
	void* temp_r5_6;
	void* var_r4;
	void* var_r4_2;
	void* var_r4_3;
	void* var_r4_4;

	temp_r0 = M2C_FIELD(arg0, u8*, 0xD0);
	switch ((s8)temp_r0) { /* irregular */
		case 0:
			if ((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0) {
				fn_80021824(&lbl_8042C1A4);
				temp_r3 = fn_800211A8((u8*)arg0 + 0x28);
				if (temp_r3 != NULL) {
					var_r0 = M2C_FIELD(temp_r3, u32*, 4);
				} else {
					var_r0 = 0U;
				}
				if (var_r0 != 0U) {
					var_r30 = 1;
				} else {
					goto block_15;
				}
			} else {
			block_15:
				var_r30 = 0;
			}
			if (var_r30 != 0) {
				temp_r5 = M2C_FIELD(arg0, void**, 0xB0);
				if (temp_r5 != NULL) {
					sp80 = 0;
					sp81 = 0;
					sp80 = 5;
					sp84 = 0;
					sp90 = 0.0f;
					sp8C = 0.0f;
					sp88 = 0.0f;
					sp94 = 0;
					sp81 = M2C_FIELD(temp_r5, u8*, 0x2A);
					sp94 = M2C_FIELD(arg0, s32*, 0xD4);
					sp84 = 1;
					fn_80100D24(&sp80, NULL);
				}
			}
			return var_r30;
		case 1:
			if ((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0) {
				fn_80021824(&lbl_8042C1A4);
				temp_r3_2 = fn_800211A8((u8*)arg0 + 0x28);
				if (temp_r3_2 != NULL) {
					var_r0_2 = M2C_FIELD(temp_r3_2, u32*, 4);
				} else {
					var_r0_2 = 0U;
				}
				if (var_r0_2 != 0U) {
					var_r30_2 = 1;
				} else {
					goto block_26;
				}
			} else {
			block_26:
				var_r30_2 = 0;
			}
			if (var_r30_2 != 0) {
				temp_r5_2 = M2C_FIELD(arg0, void**, 0xB0);
				if (temp_r5_2 != NULL) {
					sp68 = 0;
					sp69 = 0;
					sp68 = 5;
					sp6C = 0;
					sp78 = 0.0f;
					sp74 = 0.0f;
					sp70 = 0.0f;
					sp7C = 0;
					sp69 = M2C_FIELD(temp_r5_2, u8*, 0x2A);
					sp7C = M2C_FIELD(arg0, s32*, 0xD4);
					sp6C = 2;
					fn_80100D24(&sp68, NULL);
				}
			}
			return var_r30_2;
		case 2:
			if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
			    && (var_r4 = arg0, temp_r0_2 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr = temp_r0_2,
			        ((temp_r0_2 > 0) != 0))) {
			loop_33:
				temp_r3_3 = M2C_FIELD(var_r4, void**, 0x40);
				if ((temp_r3_3 != NULL) && ((u8)*M2C_FIELD(temp_r3_3, u8**, 0x10) == 0x18)) {
					var_r30_3 = 1;
				} else {
					var_r4 = (u8*)var_r4 + 8;
					var_ctr -= 1;
					if (var_ctr == 0) {
						goto block_37;
					}
					goto loop_33;
				}
			} else {
			block_37:
				var_r30_3 = 0;
			}
			if (var_r30_3 != 0) {
				temp_r5_3 = M2C_FIELD(arg0, void**, 0xB0);
				if (temp_r5_3 != NULL) {
					sp50 = 0;
					sp51 = 0;
					sp50 = 5;
					sp54 = 0;
					sp60 = 0.0f;
					sp5C = 0.0f;
					sp58 = 0.0f;
					sp64 = 0;
					sp51 = M2C_FIELD(temp_r5_3, u8*, 0x2A);
					sp64 = M2C_FIELD(arg0, s32*, 0xD4);
					sp54 = 3;
					sp58 = M2C_FIELD(arg0, f32*, 0xD8);
					sp5C = M2C_FIELD(arg0, f32*, 0xDC);
					sp60 = M2C_FIELD(arg0, f32*, 0xE0);
					fn_80100D24(&sp50, NULL);
				}
			}
			return var_r30_3;
		case 3:
			if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
			    && (var_r4_2 = arg0, temp_r0_3 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr_2 = temp_r0_3,
			        ((temp_r0_3 > 0) != 0))) {
			loop_44:
				temp_r3_4 = M2C_FIELD(var_r4_2, void**, 0x40);
				if ((temp_r3_4 != NULL) && ((u8)*M2C_FIELD(temp_r3_4, u8**, 0x10) == 0x18)) {
					var_r30_4 = 1;
				} else {
					var_r4_2 = (u8*)var_r4_2 + 8;
					var_ctr_2 -= 1;
					if (var_ctr_2 == 0) {
						goto block_48;
					}
					goto loop_44;
				}
			} else {
			block_48:
				var_r30_4 = 0;
			}
			if (var_r30_4 != 0) {
				temp_r5_4 = M2C_FIELD(arg0, void**, 0xB0);
				if (temp_r5_4 != NULL) {
					sp38 = 0;
					sp39 = 0;
					sp38 = 5;
					sp3C = 0;
					sp48 = 0.0f;
					sp44 = 0.0f;
					sp40 = 0.0f;
					sp4C = 0;
					sp39 = M2C_FIELD(temp_r5_4, u8*, 0x2A);
					sp4C = M2C_FIELD(arg0, s32*, 0xD4);
					sp3C = 4;
					sp40 = M2C_FIELD(arg0, f32*, 0xD8);
					sp44 = M2C_FIELD(arg0, f32*, 0xDC);
					sp48 = M2C_FIELD(arg0, f32*, 0xE0);
					fn_80100D24(&sp38, NULL);
				}
			}
			return var_r30_4;
		case 4:
			if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
			    && (var_r4_3 = arg0, temp_r0_4 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr_3 = temp_r0_4,
			        ((temp_r0_4 > 0) != 0))) {
			loop_55:
				temp_r3_5 = M2C_FIELD(var_r4_3, void**, 0x40);
				if ((temp_r3_5 != NULL) && ((u8)*M2C_FIELD(temp_r3_5, u8**, 0x10) == 0x18)) {
					var_r30_5 = 1;
				} else {
					var_r4_3 = (u8*)var_r4_3 + 8;
					var_ctr_3 -= 1;
					if (var_ctr_3 == 0) {
						goto block_59;
					}
					goto loop_55;
				}
			} else {
			block_59:
				var_r30_5 = 0;
			}
			if (var_r30_5 != 0) {
				temp_r5_5 = M2C_FIELD(arg0, void**, 0xB0);
				if (temp_r5_5 != NULL) {
					sp20 = 0;
					sp21 = 0;
					sp20 = 5;
					sp24 = 0;
					sp30 = 0.0f;
					sp2C = 0.0f;
					sp28 = 0.0f;
					sp34 = 0;
					sp34 = M2C_FIELD(arg0, s32*, 0xD4);
					sp21 = M2C_FIELD(temp_r5_5, u8*, 0x2A);
					sp24 = 5;
					sp28 = M2C_FIELD(arg0, f32*, 0xD8);
					sp2C = M2C_FIELD(arg0, f32*, 0xDC);
					sp30 = M2C_FIELD(arg0, f32*, 0xE0);
					fn_80100D24(&sp20, (M2C_UNK*)5);
				}
			}
			return var_r30_5;
		case 5:
			if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
			    && (var_r4_4 = arg0, temp_r0_5 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr_4 = temp_r0_5,
			        ((temp_r0_5 > 0) != 0))) {
			loop_66:
				temp_r3_6 = M2C_FIELD(var_r4_4, void**, 0x40);
				if ((temp_r3_6 != NULL) && ((u8)*M2C_FIELD(temp_r3_6, u8**, 0x10) == 0x18)) {
					var_r30_6 = 1;
				} else {
					var_r4_4 = (u8*)var_r4_4 + 8;
					var_ctr_4 -= 1;
					if (var_ctr_4 == 0) {
						goto block_70;
					}
					goto loop_66;
				}
			} else {
			block_70:
				var_r30_6 = 0;
			}
			if (var_r30_6 != 0) {
				temp_r5_6 = M2C_FIELD(arg0, void**, 0xB0);
				if (temp_r5_6 != NULL) {
					sp8  = 0;
					sp9  = 0;
					sp8  = 5;
					spC  = 0;
					sp18 = 0.0f;
					sp14 = 0.0f;
					sp10 = 0.0f;
					sp1C = 0;
					sp1C = M2C_FIELD(arg0, s32*, 0xD4);
					sp9  = M2C_FIELD(temp_r5_6, u8*, 0x2A);
					spC  = 6;
					fn_80100D24(&sp8, NULL);
				}
			}
			return var_r30_6;
		default:
			return 0;
	}
}

void fn_8_A7A08(void) { }

void fn_8_A7A0C(void) { }

void fn_8_A7A10(void* arg0)
{
	s32 var_r0;
	void* var_r3;

	if (fn_8005B8BC((u8*)arg0 + 0xB0) != 0) {
		var_r0 = 1;
	} else {
		var_r3
		    = M2C_FIELD((lbl_8042C298 + (M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A) * 4)),
		        void**, 0x30);
		if (var_r3 == NULL) {
			var_r0 = 1;
		} else {
		loop_8:
			if (var_r3 == NULL) {
				var_r0 = 1;
			} else if ((u16)M2C_FIELD(var_r3, u16*, 0x28) == 0x1530) {
				var_r0 = 0;
			} else {
				var_r3 = M2C_FIELD(var_r3, void**, 0x38);
				goto loop_8;
			}
		}
	}
	if (var_r0 != 0) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	if (fn_8_A74CC(arg0) != 0) {
		fn_8005BC04((u8*)arg0 + 0xB0);
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x38) != 0U) {
		M2C_FIELD(arg0, f32*, 0xA4) = (f32)M2C_FIELD(arg0, f32*, 0x88);
		M2C_FIELD(arg0, f32*, 0xA8) = (f32)M2C_FIELD(arg0, f32*, 0x8C);
		M2C_FIELD(arg0, f32*, 0xAC) = (f32)M2C_FIELD(arg0, f32*, 0x90);
		M2C_FIELD(arg0, f32*, 0x88) = (f32)M2C_FIELD(arg0, f32*, 0xB8);
		M2C_FIELD(arg0, f32*, 0x8C) = (f32)M2C_FIELD(arg0, f32*, 0xBC);
		M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0xC0);
		M2C_FIELD(arg0, s32*, 0x94) = (s32)M2C_FIELD(arg0, s32*, 0xC4);
		M2C_FIELD(arg0, s32*, 0x98) = (s32)M2C_FIELD(arg0, s32*, 0xC8);
		M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(arg0, s32*, 0xCC);
		fn_8003BC38((u8*)arg0 + 0x28);
	}
}

void fn_8_A7B4C(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0x38) != NULL) {
		M2C_FIELD(arg0, f32*, 0x88) = (f32)M2C_FIELD(arg0, f32*, 0xB8);
		M2C_FIELD(arg0, f32*, 0x8C) = (f32)M2C_FIELD(arg0, f32*, 0xBC);
		M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0xC0);
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x38), f32*, 0x14)
		    = (f32)M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), void**, 0x2C), f32*, 4);
	}
	fn_80021384((u8*)arg0 + 0x28);
}

void fn_8_A7BA8(void* arg0)
{
	void* temp_r4;
	void* temp_r4_2;
	void* temp_r4_3;

	temp_r4                     = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), void**, 0x2C);
	M2C_FIELD(arg0, u8*, 0xD0)  = (u8)M2C_FIELD(temp_r4, u8*, 0);
	M2C_FIELD(arg0, s32*, 0xD4) = (s32)M2C_FIELD(temp_r4, s32*, 0x14);
	M2C_FIELD(arg0, f32*, 0xD8) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	M2C_FIELD(arg0, f32*, 0xDC) = (f32)M2C_FIELD(temp_r4, f32*, 0xC);
	M2C_FIELD(arg0, f32*, 0xE0) = (f32)M2C_FIELD(temp_r4, f32*, 0x10);
	temp_r4_2                   = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, f32*, 0xB8) = (f32)M2C_FIELD(temp_r4_2, f32*, 0);
	M2C_FIELD(arg0, f32*, 0xBC) = (f32)M2C_FIELD(temp_r4_2, f32*, 4);
	M2C_FIELD(arg0, f32*, 0xC0) = (f32)M2C_FIELD(temp_r4_2, f32*, 8);
	temp_r4_3                   = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, s32*, 0xC4) = (s32)M2C_FIELD(temp_r4_3, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0xC8) = (s32)M2C_FIELD(temp_r4_3, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0xCC) = (s32)M2C_FIELD(temp_r4_3, s32*, 0x14);
}

void fn_8_A7C14(void* arg0)
{
	M2C_FIELD(arg0, s8*, 0xD0)  = 0;
	M2C_FIELD(arg0, s32*, 0xD4) = 0;
	M2C_FIELD(arg0, f32*, 0xE0) = 0.0f;
	M2C_FIELD(arg0, f32*, 0xDC) = 0.0f;
	M2C_FIELD(arg0, f32*, 0xD8) = 0.0f;
}

TObject* fn_8_A7C3C(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_163D0;
		arg0->unkB4 = &lbl_8_data_163D0 + 0x2C;
		dtor_8005BD3C((u8*)arg0 + 0xB0, 0);
		dtor_8003C52C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_A7CD4(TObject* arg0, TObject* arg1)
{
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8003C618(&arg0->unk28);
	fn_8005BE6C(&arg0->unkB0);
	arg0->unk18 = &lbl_8_data_163D0;
	arg0->unkB4 = &lbl_8_data_163D0 + 0x2C;
	arg0->unk0  = lbl_8_data_163CC;
	arg0->unk1E = 0xE4;
	arg0->unkD0 = 0;
	arg0->unkD4 = 0;
	arg0->unkE0 = 0.0f;
	arg0->unkDC = 0.0f;
	arg0->unkD8 = 0.0f;
	temp_r3     = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), void**, 0x2C);
	arg0->unkD0 = M2C_FIELD(temp_r3, u8*, 0);
	arg0->unkD4 = M2C_FIELD(temp_r3, s32*, 0x14);
	arg0->unkD8 = M2C_FIELD(temp_r3, f32*, 8);
	arg0->unkDC = M2C_FIELD(temp_r3, f32*, 0xC);
	arg0->unkE0 = M2C_FIELD(temp_r3, f32*, 0x10);
	temp_r3_2   = M2C_FIELD(arg0, void**, 0xB0);
	arg0->unkB8 = M2C_FIELD(temp_r3_2, f32*, 0);
	arg0->unkBC = M2C_FIELD(temp_r3_2, f32*, 4);
	arg0->unkC0 = M2C_FIELD(temp_r3_2, f32*, 8);
	temp_r3_3   = M2C_FIELD(arg0, void**, 0xB0);
	arg0->unkC4 = M2C_FIELD(temp_r3_3, s32*, 0xC);
	arg0->unkC8 = M2C_FIELD(temp_r3_3, s32*, 0x10);
	arg0->unkCC = M2C_FIELD(temp_r3_3, s32*, 0x14);
	fn_8003C200(&arg0->unk28, &lbl_8_data_162C8, 1, 4);
	if ((void*)arg0->unk38 != NULL) {
		arg0->unk88 = arg0->unkB8;
		arg0->unk8C = arg0->unkBC;
		arg0->unk90 = arg0->unkC0;
		M2C_FIELD(arg0->unk38, f32*, 0x14)
		    = (f32)M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), void**, 0x2C), f32*, 4);
	}
	fn_80021384(&arg0->unk28);
	return arg0;
}

TObject* fn_8_A7E24(void)
{
	TObject* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;

	temp_r3 = fn_80018A34(lbl_8042C148, 0xE4);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		fn_8003C618(&temp_r3->unk28);
		fn_8005BE6C(&temp_r3->unkB0);
		temp_r3->unk18 = &lbl_8_data_163D0;
		temp_r3->unkB4 = &lbl_8_data_163D0 + 0x2C;
		temp_r3->unk0  = lbl_8_data_163CC;
		temp_r3->unk1E = 0xE4;
		temp_r3->unkD0 = 0;
		temp_r3->unkD4 = 0;
		temp_r3->unkE0 = 0.0f;
		temp_r3->unkDC = 0.0f;
		temp_r3->unkD8 = 0.0f;
		temp_r3_2      = M2C_FIELD(M2C_FIELD(temp_r3, void**, 0xB0), void**, 0x2C);
		temp_r3->unkD0 = M2C_FIELD(temp_r3_2, u8*, 0);
		temp_r3->unkD4 = M2C_FIELD(temp_r3_2, s32*, 0x14);
		temp_r3->unkD8 = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3->unkDC = M2C_FIELD(temp_r3_2, f32*, 0xC);
		temp_r3->unkE0 = M2C_FIELD(temp_r3_2, f32*, 0x10);
		temp_r3_3      = M2C_FIELD(temp_r3, void**, 0xB0);
		temp_r3->unkB8 = M2C_FIELD(temp_r3_3, f32*, 0);
		temp_r3->unkBC = M2C_FIELD(temp_r3_3, f32*, 4);
		temp_r3->unkC0 = M2C_FIELD(temp_r3_3, f32*, 8);
		temp_r3_4      = M2C_FIELD(temp_r3, void**, 0xB0);
		temp_r3->unkC4 = M2C_FIELD(temp_r3_4, s32*, 0xC);
		temp_r3->unkC8 = M2C_FIELD(temp_r3_4, s32*, 0x10);
		temp_r3->unkCC = M2C_FIELD(temp_r3_4, s32*, 0x14);
		fn_8003C200(&temp_r3->unk28, &lbl_8_data_162C8, 1, 4);
		if ((void*)temp_r3->unk38 != NULL) {
			temp_r3->unk88                        = temp_r3->unkB8;
			temp_r3->unk8C                        = temp_r3->unkBC;
			temp_r3->unk90                        = temp_r3->unkC0;
			M2C_FIELD(temp_r3->unk38, f32*, 0x14) = (f32)M2C_FIELD(
			    M2C_FIELD(M2C_FIELD(temp_r3, void**, 0xB0), void**, 0x2C), f32*, 4);
		}
		fn_80021384(&temp_r3->unk28);
	}
	return temp_r3;
}

void fn_8_A7FA4(void* arg1)
{
	s32* var_r5_2;
	s32 temp_r6;
	u8* temp_r3;
	u8* var_r5;
	u8 temp_r0;

	temp_r3 = M2C_FIELD(arg1, u8**, 0x2C);
	temp_r0 = M2C_FIELD(temp_r3, u8*, 0);
	var_r5  = &lbl_8_data_163B4;
	if ((s8)temp_r0 < (s8)lbl_8_data_163B4) {

	} else {
		var_r5 = &lbl_8_data_163B5;
		if ((s8)temp_r0 > (s8)lbl_8_data_163B5) {

		} else {
			var_r5 = temp_r3;
		}
	}
	M2C_FIELD(temp_r3, u8*, 0) = (u8)(s8)*var_r5;
	temp_r6                    = M2C_FIELD(temp_r3, s32*, 0x14);
	var_r5_2                   = &lbl_8_rodata_1990;
	if (temp_r6 < (s32)lbl_8_rodata_1990) {

	} else {
		var_r5_2 = lbl_8_rodata_1994;
		if (temp_r6 > (s32)*lbl_8_rodata_1994) {

		} else {
			var_r5_2 = (s32*)(temp_r3 + 0x14);
		}
	}
	M2C_FIELD(temp_r3, s32*, 0x14) = (s32)*var_r5_2;
	*flyerColObjectFieldNames      = lbl_8_data_1639C[(s8)M2C_FIELD(temp_r3, u8*, 0)];
	M2C_FIELD(temp_r3, f32*, 8)    = (f32)M2C_FIELD(arg1, f32*, 0);
	M2C_FIELD(temp_r3, f32*, 0xC)  = (f32)M2C_FIELD(arg1, f32*, 4);
	M2C_FIELD(temp_r3, f32*, 0x10) = (f32)M2C_FIELD(arg1, f32*, 8);
}

void flyerColObjectUnload(void) { }

void flyerColObjectLoad(void) { }

void flyerColObjectCreate(void)
{
	TObject* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;

	temp_r3 = fn_80018A34(lbl_8042C148, 0xE4);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		fn_8003C618(&temp_r3->unk28);
		fn_8005BE6C(&temp_r3->unkB0);
		temp_r3->unk18 = &lbl_8_data_163D0;
		temp_r3->unkB4 = &lbl_8_data_163D0 + 0x2C;
		temp_r3->unk0  = lbl_8_data_163CC;
		temp_r3->unk1E = 0xE4;
		temp_r3->unkD0 = 0;
		temp_r3->unkD4 = 0;
		temp_r3->unkE0 = 0.0f;
		temp_r3->unkDC = 0.0f;
		temp_r3->unkD8 = 0.0f;
		temp_r3_2      = M2C_FIELD(M2C_FIELD(temp_r3, void**, 0xB0), void**, 0x2C);
		temp_r3->unkD0 = M2C_FIELD(temp_r3_2, u8*, 0);
		temp_r3->unkD4 = M2C_FIELD(temp_r3_2, s32*, 0x14);
		temp_r3->unkD8 = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3->unkDC = M2C_FIELD(temp_r3_2, f32*, 0xC);
		temp_r3->unkE0 = M2C_FIELD(temp_r3_2, f32*, 0x10);
		temp_r3_3      = M2C_FIELD(temp_r3, void**, 0xB0);
		temp_r3->unkB8 = M2C_FIELD(temp_r3_3, f32*, 0);
		temp_r3->unkBC = M2C_FIELD(temp_r3_3, f32*, 4);
		temp_r3->unkC0 = M2C_FIELD(temp_r3_3, f32*, 8);
		temp_r3_4      = M2C_FIELD(temp_r3, void**, 0xB0);
		temp_r3->unkC4 = M2C_FIELD(temp_r3_4, s32*, 0xC);
		temp_r3->unkC8 = M2C_FIELD(temp_r3_4, s32*, 0x10);
		temp_r3->unkCC = M2C_FIELD(temp_r3_4, s32*, 0x14);
		fn_8003C200(&temp_r3->unk28, &lbl_8_data_162C8, 1, 4);
		if ((void*)temp_r3->unk38 != NULL) {
			temp_r3->unk88                        = temp_r3->unkB8;
			temp_r3->unk8C                        = temp_r3->unkBC;
			temp_r3->unk90                        = temp_r3->unkC0;
			M2C_FIELD(temp_r3->unk38, f32*, 0x14) = (f32)M2C_FIELD(
			    M2C_FIELD(M2C_FIELD(temp_r3, void**, 0xB0), void**, 0x2C), f32*, 4);
		}
		fn_80021384(&temp_r3->unk28);
	}
}

void flyerColObjectRegister(void)
{
	M2C_FIELD(&flyerColObjectEntry, s32*, 0x14)       = 0;
	M2C_FIELD(&flyerColObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&flyerColObjectEntry, M2C_UNK**, 0)     = &flyerColObjectDisplayName;
	M2C_FIELD(&flyerColObjectEntry, void (**)(), 4)   = flyerColObjectLoad;
	M2C_FIELD(&flyerColObjectEntry, void (**)(), 8)   = flyerColObjectUnload;
	M2C_FIELD(&flyerColObjectEntry, void (**)(), 0xC) = flyerColObjectCreate;
	M2C_FIELD(&flyerColObjectEntry, s32*, 0x10)       = 0;
	M2C_FIELD(&flyerColObjectEntry, s32*, 0x14)       = 0x20000;
	M2C_FIELD(&flyerColObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&flyerColObjectEntry, s8*, 0x20)        = 0x1E;
	M2C_FIELD(&flyerColObjectEntry, s16*, 0x1C)       = 0x63;
	M2C_FIELD(&flyerColObjectEntry, s16*, 0x1E)       = 4;
	M2C_FIELD(&flyerColObjectEntry, s8*, 0x21)        = 0;
	M2C_FIELD(&flyerColObjectEntry, M2C_UNK**, 0x24)  = &flyerColObjectFieldTypes;
	M2C_FIELD(&flyerColObjectEntry, M2C_UNK***, 0x28) = flyerColObjectFieldNames;
	if (&flyerColObjectFieldTypes != NULL) {
		M2C_FIELD(&flyerColObjectEntry, s32*, 0x14) = 0x20008;
		return;
	}
	M2C_FIELD(&flyerColObjectEntry, s32*, 0x14) = 0x20000;
}
