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
	/* 0x28 */ char pad28[4];
	/* 0x2C */ f32 unk2C;        /* inferred */
	/* 0x30 */ f32 unk30;        /* inferred */
	/* 0x34 */ s32 unk34;        /* inferred */
	/* 0x38 */ s32 unk38;        /* inferred */
	/* 0x3C */ s32 unk3C;        /* inferred */
	/* 0x40 */ f32 unk40;        /* inferred */
	/* 0x44 */ f32 unk44;        /* inferred */
	/* 0x48 */ f32 unk48;        /* inferred */
	/* 0x4C */ void* unk4C;      /* inferred */
	/* 0x50 */ f32 unk50;        /* inferred */
	/* 0x54 */ f32 unk54;        /* inferred */
	/* 0x58 */ f32 unk58;        /* inferred */
	/* 0x5C */ f32 unk5C;        /* inferred */
	/* 0x60 */ f32 unk60;        /* inferred */
	/* 0x64 */ s32 unk64;        /* inferred */
	/* 0x68 */ char pad68[0x20]; /* maybe part of unk64[9]? */
	/* 0x88 */ f32 unk88;        /* inferred */
	/* 0x8C */ f32 unk8C;        /* inferred */
	/* 0x90 */ f32 unk90;        /* inferred */
	/* 0x94 */ char pad94[0x1C]; /* maybe part of unk90[8]? */
	/* 0xB0 */ f32 unkB0;        /* inferred */
	/* 0xB4 */ f32 unkB4;        /* inferred */
	/* 0xB8 */ f32 unkB8;        /* inferred */
	/* 0xBC */ f32 unkBC;        /* inferred */
	/* 0xC0 */ f32 unkC0;        /* inferred */
	/* 0xC4 */ f32 unkC4;        /* inferred */
	/* 0xC8 */ f32 unkC8;        /* inferred */
	/* 0xCC */ f32 unkCC;        /* inferred */
	/* 0xD0 */ f32 unkD0;        /* inferred */
	/* 0xD4 */ f32 unkD4;        /* inferred */
	/* 0xD8 */ s32 unkD8;        /* inferred */
	/* 0xDC */ s32 unkDC;        /* inferred */
	/* 0xE0 */ void* unkE0;      /* inferred */
	/* 0xE4 */ f32 unkE4;        /* inferred */
	/* 0xE8 */ f32 unkE8;        /* inferred */
	/* 0xEC */ f32 unkEC;        /* inferred */
	/* 0xF0 */ f32 unkF0;        /* inferred */
} TObject;                       /* size >= 0xF4 */

extern "C" {

void* __ct__7TObjectFP7TObject(void*, void*); /* extern */
M2C_UNK __dl__FPv(void*);                     /* extern */
void* __dt__7TObjectFv(void*, s32);           /* extern */
f64 asin(...);                                /* extern */
f64 atan2(...);                               /* extern */
M2C_UNK dtor_8003C52C(...);                   /* extern */
s32 fn_80017800(...);                         /* extern */
M2C_UNK fn_800189A4(...);                     /* extern */
TObject* fn_80018A34(...);                    /* extern */
void* fn_800211A8(...);                       /* extern */
M2C_UNK fn_80021824(...);                     /* extern */
M2C_UNK fn_8003BC38(...);                     /* extern */
M2C_UNK fn_8003BE78(...);                     /* extern */
M2C_UNK fn_8003C200(...);                     /* extern */
M2C_UNK fn_8003C618(...);                     /* extern */
u32 fn_80057644(...);                         /* extern */
u32 fn_8005EA04(...);                         /* extern */
M2C_UNK fn_8005FC74(...);                     /* extern */
M2C_UNK fn_800A31B8(...);                     /* extern */
s32 fn_800A3ED4(...);                         /* extern */
M2C_UNK fn_800AFB50(...);                     /* extern */
M2C_UNK fn_800B4A38(...);                     /* extern */
M2C_UNK fn_800BDEA0(...);                     /* extern */
M2C_UNK fn_800D5A64(...);                     /* extern */
f32 fn_800D71DC(...);                         /* extern */
s32 fn_800D7A94(...);                         /* extern */
f32 fn_800D7B00(...);                         /* extern */
f32 fn_800D7BD8(...);                         /* extern */
f32 fn_800D8BC4(...);                         /* extern */
M2C_UNK fn_800E1208(...);                     /* extern */
void* fn_8010037C(...);                       /* extern */
M2C_UNK fn_80100AAC(...);                     /* extern */
s32 fn_80100BF8(...);                         /* extern */
s32 fn_80103324(...);                         /* extern */
M2C_UNK fn_8010AFF8(...);                     /* extern */
M2C_UNK fn_8010B074(...);                     /* extern */
M2C_UNK fn_8010B208(...);                     /* extern */
M2C_UNK fn_80113874(...);                     /* extern */
M2C_UNK fn_80137FE8(...);                     /* extern */
M2C_UNK fn_8014FF2C(...);                     /* extern */
void* fn_80150588(...);                       /* extern */
M2C_UNK fn_80150958(...);                     /* extern */
M2C_UNK fn_801990E0(...);                     /* extern */
f32 fn_801991B4(...);                         /* extern */
M2C_UNK fn_8019941C(...);                     /* extern */
s32 fn_8019CE34(...);                         /* extern */
M2C_UNK fn_8019EB94(...);                     /* extern */
M2C_UNK fn_8019EC30(...);                     /* extern */
M2C_UNK fn_8019ED68(...);                     /* extern */
s32 fn_801C28D8(...);                         /* extern */
M2C_UNK fn_8_90B10(...);                      /* extern */
M2C_UNK fn_8_A353C(...);                      /* extern */
s32 fn_8_A35BC(...);                          /* extern */
M2C_UNK fn_8_A7FA4(...);                      /* extern */
void fn_8_A945C(void* arg0);                  /* static */
extern M2C_UNK lbl_80239978;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_8029C310;
extern M2C_UNK lbl_802AD090;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern M2C_UNK lbl_8042C1A4;
extern u32 lbl_8042C388;
extern u32 lbl_8042C590;
extern s32* lbl_8042C9A4;
extern u32 lbl_8_bss_1A48;
extern f32 lbl_8_rodata_1AAC;
extern f32 lbl_8_rodata_1AB0;
extern f32 lbl_8_rodata_1AB4;
extern f32 lbl_8_rodata_1AB8;
extern f32 lbl_8_rodata_1ABC;
extern f32 lbl_8_rodata_1AC0;
extern f32 lbl_8_rodata_1AC4;
extern f32 lbl_8_rodata_1AC8;
extern f32 lbl_8_rodata_1ACC;
extern f32 lbl_8_rodata_1AD0;
extern f32 lbl_8_rodata_1AE0;
extern f32 lbl_8_rodata_1AE4;
static M2C_UNK lbl_8_data_16430;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16460;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016477_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_16478 = &lbl_8_data_16460;
static M2C_UNK lbl_8_data_1647C;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_164A8;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_164D8;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000164EE_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_164F0 = &lbl_8_data_164D8;
static M2C_UNK lbl_8_data_164F4;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16520;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16538;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16550;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016566_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16568;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16580;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16598;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_165B0;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000165C7_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_165C8;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000165DE_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_165E0;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_165F8;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001660F_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16610;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016627_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16628;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_167FC;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1682C;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016839_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1683C;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016847_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16848;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016853_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16854;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16860;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001686D_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16870;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16880;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001688B_data;     /* unable to generate initializer: unknown type */
static M2C_UNK magicianObjectFieldNames; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_168B0;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000168B7_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_168B8;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_168C0;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_168C8;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_168C9;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000168CA_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_168CC;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000168DE_data;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_168E0;         /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_168E4;         /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000168FA_data;     /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_168FC = &lbl_8_data_168E4;
static M2C_UNK lbl_8_data_16900;       /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1692C;       /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016939_data;   /* unable to generate initializer: unknown type */
static M2C_UNK jumptable_8_data_1693C; /* unable to generate initializer: unknown type */
static void* lbl_8_bss_19B8;
static void* lbl_8_bss_19C0;
static M2C_UNK lbl_8_bss_19C8;
static M2C_UNK lbl_8_bss_19D0;
static M2C_UNK lbl_8_bss_19D4;
static M2C_UNK lbl_8_bss_1A18;
static M2C_UNK magicianObjectEntry;
static M2C_UNK lbl_8_rodata_19B8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_19E0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1A2C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1A38; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1A48; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1A54; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1A60; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1A6C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1A84; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1A94; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1AA0; /* unable to generate initializer: unknown type; const */

void fn_8_A82A0(s32 arg0)
{
	fn_8_A7FA4(arg0 - 0xB0);
}

void fn_8_A82A8(void* arg0)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;

	if ((void*)M2C_FIELD(arg0, void**, 0xE0) != NULL) {
		sp8  = M2C_FIELD(arg0, f32*, 0xB0);
		spC  = M2C_FIELD(arg0, f32*, 0xB4);
		sp10 = M2C_FIELD(arg0, f32*, 0xB8);
		sp14 = 20.0f;
		if (fn_8019CE34(*lbl_8042C9A4, &sp8) != 0) {
			fn_80113874(M2C_FIELD(arg0, s32*, 0xD8));
			fn_8014FF2C(M2C_FIELD(arg0, void**, 0xE0));
		}
	}
}

void fn_8_A8334(void* arg0)
{
	fn_800BDEA0(0, (u8*)arg0 + 0xB0, 0, 1, -1);
	M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
}

void fn_8_A8384(void* arg0)
{
	M2C_UNK sp8;
	f32 temp_f1;
	s32 temp_r0;
	s32 temp_r31;
	void* temp_r3;

	temp_r0                     = M2C_FIELD(arg0, s32*, 0xD4) - 1;
	M2C_FIELD(arg0, s32*, 0xD4) = temp_r0;
	if (temp_r0 < 0) {
		M2C_FIELD(arg0, s32*, 0xDC) = 2;
		return;
	}
	M2C_FIELD(arg0, f32*, 0xE4) = (f32)(M2C_FIELD(arg0, f32*, 0xE4) + -0.06f);
	M2C_FIELD(arg0, f32*, 0xB0) = (f32)(M2C_FIELD(arg0, f32*, 0xB0) + M2C_FIELD(arg0, f32*, 0xBC));
	M2C_FIELD(arg0, f32*, 0xB4) = (f32)(M2C_FIELD(arg0, f32*, 0xB4) + M2C_FIELD(arg0, f32*, 0xE4));
	M2C_FIELD(arg0, f32*, 0xB8) = (f32)(M2C_FIELD(arg0, f32*, 0xB8) + M2C_FIELD(arg0, f32*, 0xC4));
	temp_f1                     = M2C_FIELD(arg0, f32*, 0xEC);
	if ((temp_f1 != -1000000.0f) && (temp_f1 > M2C_FIELD(arg0, f32*, 0xB4))) {
		M2C_FIELD(arg0, s32*, 0xDC) = 2;
		return;
	}
	M2C_FIELD(arg0, f32*, 0xE8) = (f32)M2C_FIELD(arg0, f32*, 0xB0);
	M2C_FIELD(arg0, f32*, 0xEC) = (f32)(4.0f + fn_800D8BC4((u8*)arg0 + 0xB0, &sp8, 1));
	M2C_FIELD(arg0, f32*, 0xF0) = (f32)M2C_FIELD(arg0, f32*, 0xB8);
	temp_r3                     = M2C_FIELD(arg0, void**, 0xE0);
	if (temp_r3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3, s32*, 4);
		fn_8019ED68(temp_r31, &lbl_80239990, 0, 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0xD0),
		    0.005493164f);
		fn_8019ED68(temp_r31, &lbl_80239978, 2, 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0xC8),
		    0.005493164f);
		fn_8019ED68(temp_r31, &lbl_80239984, 2, 0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0xCC),
		    0.005493164f);
		fn_8019EB94(temp_r31, (u8*)arg0 + 0xB0, 2);
	}
}

void fn_8_A8584(void* arg0)
{
	M2C_FIELD(arg0, s32*, 0xDC) = 1;
}

void fn_8_A8590(void* arg0)
{
	M2C_UNK sp8;
	f32 temp_f1;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r31;
	s32 temp_r3;
	s32 var_r0;
	u8 var_r5;
	u8 var_r6;
	void* temp_r3_2;

	var_r5  = 1;
	var_r6  = 1;
	temp_r3 = M2C_FIELD(&lbl_8029C310, s32*, 0x18) - 1;
	if ((u32)((u32)((1 | ~temp_r3) - ((u32)(1 - temp_r3) >> 1U)) >> 0x1FU) == 0) {
		var_r6 = 0;
	}
	if ((var_r6 == 0) && ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x18) != 3)) {
		var_r5 = 0;
	}
	if ((s32)var_r5 != 0) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	if (var_r0 == 0) {
		fn_8003BE78((u8*)arg0 + 0x28);
		return;
	}
	temp_r0 = M2C_FIELD(arg0, s32*, 0xDC);
	switch (temp_r0) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xDC) = 1;
			break;
		case 1:
			temp_r0_2                   = M2C_FIELD(arg0, s32*, 0xD4) - 1;
			M2C_FIELD(arg0, s32*, 0xD4) = temp_r0_2;
			if (temp_r0_2 < 0) {
				M2C_FIELD(arg0, s32*, 0xDC) = 2;
			} else {
				M2C_FIELD(arg0, f32*, 0xE4) = (f32)(M2C_FIELD(arg0, f32*, 0xE4) + -0.06f);
				M2C_FIELD(arg0, f32*, 0xB0)
				    = (f32)(M2C_FIELD(arg0, f32*, 0xB0) + M2C_FIELD(arg0, f32*, 0xBC));
				M2C_FIELD(arg0, f32*, 0xB4)
				    = (f32)(M2C_FIELD(arg0, f32*, 0xB4) + M2C_FIELD(arg0, f32*, 0xE4));
				M2C_FIELD(arg0, f32*, 0xB8)
				    = (f32)(M2C_FIELD(arg0, f32*, 0xB8) + M2C_FIELD(arg0, f32*, 0xC4));
				temp_f1 = M2C_FIELD(arg0, f32*, 0xEC);
				if ((temp_f1 != -1000000.0f) && (temp_f1 > M2C_FIELD(arg0, f32*, 0xB4))) {
					M2C_FIELD(arg0, s32*, 0xDC) = 2;
				} else {
					M2C_FIELD(arg0, f32*, 0xE8) = (f32)M2C_FIELD(arg0, f32*, 0xB0);
					M2C_FIELD(arg0, f32*, 0xEC)
					    = (f32)(4.0f + fn_800D8BC4((u8*)arg0 + 0xB0, &sp8, 1));
					M2C_FIELD(arg0, f32*, 0xF0) = (f32)M2C_FIELD(arg0, f32*, 0xB8);
					temp_r3_2                   = M2C_FIELD(arg0, void**, 0xE0);
					if (temp_r3_2 != NULL) {
						temp_r31 = M2C_FIELD(temp_r3_2, s32*, 4);
						fn_8019ED68(temp_r31, &lbl_80239990, 0,
						    0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0xD0), 0.005493164f);
						fn_8019ED68(temp_r31, &lbl_80239978, 2,
						    0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0xC8), 0.005493164f);
						fn_8019ED68(temp_r31, &lbl_80239984, 2,
						    0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0xCC), 0.005493164f);
						fn_8019EB94(temp_r31, (u8*)arg0 + 0xB0, 2);
					}
				}
			}
			break;
		case 2:
			fn_800BDEA0(0, (u8*)arg0 + 0xB0, 0, 1, -1);
			M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			break;
	}
	if ((fn_80017800(arg0) != 0) && ((u32)M2C_FIELD(arg0, u32*, 0x38) != 0U)) {
		M2C_FIELD(arg0, f32*, 0xA4) = (f32)M2C_FIELD(arg0, f32*, 0x88);
		M2C_FIELD(arg0, f32*, 0xA8) = (f32)M2C_FIELD(arg0, f32*, 0x8C);
		M2C_FIELD(arg0, f32*, 0xAC) = (f32)M2C_FIELD(arg0, f32*, 0x90);
		M2C_FIELD(arg0, f32*, 0x88) = (f32)M2C_FIELD(arg0, f32*, 0xB0);
		M2C_FIELD(arg0, f32*, 0x8C) = (f32)M2C_FIELD(arg0, f32*, 0xB4);
		M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0xB8);
		M2C_FIELD(arg0, s32*, 0x94) = (s32)M2C_FIELD(arg0, s32*, 0xC8);
		M2C_FIELD(arg0, s32*, 0x98) = (s32)M2C_FIELD(arg0, s32*, 0xCC);
		M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(arg0, s32*, 0xD0);
		fn_8003BC38((u8*)arg0 + 0x28);
	}
}

TObject* fn_8_A8938(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_1647C;
		if ((u32)arg0->unkE0 != NULL) {
			fn_80150958();
			arg0->unkE0 = NULL;
		}
		dtor_8003C52C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_A89D4(TObject* arg0, void* arg1, TObject* arg2)
{
	M2C_UNK sp8;

	__ct__7TObjectFP7TObject(arg0, arg2);
	fn_8003C618(&arg0->unk28);
	arg0->unk18 = &lbl_8_data_1647C;
	arg0->unkB8 = 0.0f;
	arg0->unkB4 = 0.0f;
	arg0->unkB0 = 0.0f;
	arg0->unkC4 = 0.0f;
	arg0->unkC0 = 0.0f;
	arg0->unkBC = 0.0f;
	arg0->unkD0 = 0.0f;
	arg0->unkCC = 0.0f;
	arg0->unkC8 = 0.0f;
	arg0->unkD4 = 4.2e-43f;
	arg0->unkD8 = 8;
	arg0->unk0  = lbl_8_data_16478;
	arg0->unk1E = 0xF4;
	arg0->unkE0 = NULL;
	arg0->unkDC = 0;
	arg0->unkB0 = M2C_FIELD(arg1, f32*, 0);
	arg0->unkB4 = M2C_FIELD(arg1, f32*, 4);
	arg0->unkB8 = M2C_FIELD(arg1, f32*, 8);
	arg0->unkBC = M2C_FIELD(arg1, f32*, 0xC);
	arg0->unkC0 = M2C_FIELD(arg1, f32*, 0x10);
	arg0->unkC4 = M2C_FIELD(arg1, f32*, 0x14);
	arg0->unkC8 = M2C_FIELD(arg1, f32*, 0x18);
	arg0->unkCC = M2C_FIELD(arg1, f32*, 0x1C);
	arg0->unkD0 = M2C_FIELD(arg1, f32*, 0x20);
	arg0->unkD4 = M2C_FIELD(arg1, f32*, 0x24);
	arg0->unkD8 = M2C_FIELD(arg1, s32*, 0x28);
	arg0->unkE4 = 0.0f;
	fn_8003C200(&arg0->unk28, &lbl_8_data_16430, 1, 3);
	arg0->unk88 = arg0->unkB0;
	arg0->unk8C = arg0->unkB4;
	arg0->unk90 = arg0->unkB8;
	arg0->unkE8 = arg0->unkB0;
	arg0->unkEC = 4.0f + fn_800D8BC4(&arg0->unkB0, &sp8, 1);
	arg0->unkF0 = arg0->unkB8;
	arg0->unkE0 = fn_80150588(lbl_8_bss_19B8);
	return arg0;
}

TObject* fn_8_A8B60(void* arg0)
{
	M2C_UNK sp8;
	TObject* temp_r3;

	temp_r3 = fn_80018A34(lbl_8042C148, 0xF4);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		fn_8003C618(&temp_r3->unk28);
		temp_r3->unk18 = &lbl_8_data_1647C;
		temp_r3->unkB8 = 0.0f;
		temp_r3->unkB4 = 0.0f;
		temp_r3->unkB0 = 0.0f;
		temp_r3->unkC4 = 0.0f;
		temp_r3->unkC0 = 0.0f;
		temp_r3->unkBC = 0.0f;
		temp_r3->unkD0 = 0.0f;
		temp_r3->unkCC = 0.0f;
		temp_r3->unkC8 = 0.0f;
		temp_r3->unkD4 = 4.2e-43f;
		temp_r3->unkD8 = 8;
		temp_r3->unk0  = lbl_8_data_16478;
		temp_r3->unk1E = 0xF4;
		temp_r3->unkE0 = NULL;
		temp_r3->unkDC = 0;
		temp_r3->unkB0 = M2C_FIELD(arg0, f32*, 0);
		temp_r3->unkB4 = M2C_FIELD(arg0, f32*, 4);
		temp_r3->unkB8 = M2C_FIELD(arg0, f32*, 8);
		temp_r3->unkBC = M2C_FIELD(arg0, f32*, 0xC);
		temp_r3->unkC0 = M2C_FIELD(arg0, f32*, 0x10);
		temp_r3->unkC4 = M2C_FIELD(arg0, f32*, 0x14);
		temp_r3->unkC8 = M2C_FIELD(arg0, f32*, 0x18);
		temp_r3->unkCC = M2C_FIELD(arg0, f32*, 0x1C);
		temp_r3->unkD0 = M2C_FIELD(arg0, f32*, 0x20);
		temp_r3->unkD4 = M2C_FIELD(arg0, f32*, 0x24);
		temp_r3->unkD8 = M2C_FIELD(arg0, s32*, 0x28);
		temp_r3->unkE4 = 0.0f;
		fn_8003C200(&temp_r3->unk28, &lbl_8_data_16430, 1, 3);
		temp_r3->unk88 = temp_r3->unkB0;
		temp_r3->unk8C = temp_r3->unkB4;
		temp_r3->unk90 = temp_r3->unkB8;
		temp_r3->unkE8 = temp_r3->unkB0;
		temp_r3->unkEC = 4.0f + fn_800D8BC4(&temp_r3->unkB0, &sp8, 1);
		temp_r3->unkF0 = temp_r3->unkB8;
		temp_r3->unkE0 = fn_80150588(lbl_8_bss_19B8);
	}
	return temp_r3;
}

void fn_8_A8D1C(void)
{
	lbl_8_bss_19B8 = NULL;
}

void fn_8_A8D30(void)
{
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
		fn_80100AAC();
	}
	lbl_8_bss_19B8 = fn_8010037C(lbl_8042C590, 5, 8);
}

s32 fn_8_A8D98(void* arg0)
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

void fn_8_A8E0C(void* arg0)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	s32 temp_r31;

	if ((void*)lbl_8_bss_19C0 != NULL) {
		sp8  = M2C_FIELD(arg0, f32*, 0xB0);
		spC  = M2C_FIELD(arg0, f32*, 0xB4);
		sp10 = M2C_FIELD(arg0, f32*, 0xB8);
		sp14 = 20.0f;
		if (fn_8019CE34(*lbl_8042C9A4, &sp8) != 0) {
			temp_r31 = M2C_FIELD(lbl_8_bss_19C0, s32*, 4);
			fn_8019ED68(temp_r31, &lbl_80239978, 0,
			    -(0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0xD8)), 0.005493164f);
			fn_8019ED68(temp_r31, &lbl_80239984, 2,
			    180.0f + (0.005493164f * (f32)M2C_FIELD(arg0, s32*, 0xDC)), 0.005493164f, 180.0f);
			fn_8019EB94(temp_r31, (u8*)arg0 + 0xB0, 2);
			fn_80113874(M2C_FIELD(arg0, s32*, 0xEC));
			fn_8014FF2C(lbl_8_bss_19C0);
		}
	}
}

void fn_8_A8F7C(void* arg0)
{
	fn_800BDEA0(0, (u8*)arg0 + 0xB0, 0, 1, -1);
	M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
}

void fn_8_A8FCC(void* arg0)
{
	f32 temp_f1;
	f32 temp_f30;
	f32 temp_f31;

	temp_f1 = fn_801991B4((u8*)arg0 + 0xBC);
	if (temp_f1 > 0.0f) {
		temp_f31 = (f32)asin(-M2C_FIELD(arg0, f32*, 0xC0) / temp_f1);
		temp_f30 = (f32)atan2(M2C_FIELD(arg0, f32*, 0xBC), M2C_FIELD(arg0, f32*, 0xC4));
		M2C_FIELD(arg0, s32*, 0xD8)
		    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0xD8), (s32)(10430.381f * temp_f31), 0x100);
		M2C_FIELD(arg0, s32*, 0xDC)
		    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0xDC), (s32)(10430.381f * temp_f30), 0x100);
		M2C_FIELD(arg0, s32*, 0xE0) = 0;
		return;
	}
	M2C_FIELD(arg0, s32*, 0xD8) = 0;
	M2C_FIELD(arg0, s32*, 0xDC) = 0;
	M2C_FIELD(arg0, s32*, 0xE0) = 0;
}

void fn_8_A90C8(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f30;
	f32 temp_f31;
	void* temp_r3;

	if ((s32)M2C_FIELD(arg0, s32*, 0xE4) != 0) {
		sp8  = M2C_FIELD(arg0, f32*, 0xB0);
		spC  = M2C_FIELD(arg0, f32*, 0xB4);
		sp10 = M2C_FIELD(arg0, f32*, 0xB8);
		M2C_FIELD(arg0, f32*, 0xBC)
		    = (f32)(M2C_FIELD(arg0, f32*, 0xC8) - M2C_FIELD(arg0, f32*, 0xB0));
		M2C_FIELD(arg0, f32*, 0xC0)
		    = (f32)(M2C_FIELD(arg0, f32*, 0xCC) - M2C_FIELD(arg0, f32*, 0xB4));
		temp_f1                     = M2C_FIELD(arg0, f32*, 0xD0);
		M2C_FIELD(arg0, f32*, 0xC4) = (f32)(temp_f1 - M2C_FIELD(arg0, f32*, 0xB8));
		temp_r3                     = (u8*)arg0 + 0xBC;
		fn_801990E0(temp_r3, temp_r3, temp_f1);
		M2C_FIELD(arg0, f32*, 0xFC) = (f32)(M2C_FIELD(arg0, f32*, 0xFC) + 0.2f);
		temp_f1_2                   = M2C_FIELD(arg0, f32*, 0xD4);
		if (M2C_FIELD(arg0, f32*, 0xFC) > temp_f1_2) {
			M2C_FIELD(arg0, f32*, 0xFC) = temp_f1_2;
		}
		M2C_FIELD(arg0, f32*, 0xBC)
		    = (f32)(M2C_FIELD(arg0, f32*, 0xBC) * M2C_FIELD(arg0, f32*, 0xFC));
		M2C_FIELD(arg0, f32*, 0xC0)
		    = (f32)(M2C_FIELD(arg0, f32*, 0xC0) * M2C_FIELD(arg0, f32*, 0xFC));
		M2C_FIELD(arg0, f32*, 0xC4)
		    = (f32)(M2C_FIELD(arg0, f32*, 0xC4) * M2C_FIELD(arg0, f32*, 0xFC));
		M2C_FIELD(arg0, f32*, 0xB0)
		    = (f32)(M2C_FIELD(arg0, f32*, 0xB0) + M2C_FIELD(arg0, f32*, 0xBC));
		M2C_FIELD(arg0, f32*, 0xB4)
		    = (f32)(M2C_FIELD(arg0, f32*, 0xB4) + M2C_FIELD(arg0, f32*, 0xC0));
		temp_f1_3                   = M2C_FIELD(arg0, f32*, 0xB8);
		M2C_FIELD(arg0, f32*, 0xB8) = (f32)(temp_f1_3 + M2C_FIELD(arg0, f32*, 0xC4));
		if (fn_800D7BD8((u8*)arg0 + 0xC8, &sp8, (u8*)arg0 + 0xB0, 0, temp_f1_3) < 2.0f) {
			M2C_FIELD(arg0, s32*, 0xE8) = 0;
		}
	}
	temp_f1_4 = fn_801991B4((u8*)arg0 + 0xBC);
	if (temp_f1_4 > 0.0f) {
		temp_f31 = (f32)asin(-M2C_FIELD(arg0, f32*, 0xC0) / temp_f1_4);
		temp_f30 = (f32)atan2(M2C_FIELD(arg0, f32*, 0xBC), M2C_FIELD(arg0, f32*, 0xC4));
		M2C_FIELD(arg0, s32*, 0xD8)
		    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0xD8), (s32)(10430.381f * temp_f31), 0x100);
		M2C_FIELD(arg0, s32*, 0xDC)
		    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0xDC), (s32)(10430.381f * temp_f30), 0x100);
		M2C_FIELD(arg0, s32*, 0xE0) = 0;
		return;
	}
	M2C_FIELD(arg0, s32*, 0xD8) = 0;
	M2C_FIELD(arg0, s32*, 0xDC) = 0;
	M2C_FIELD(arg0, s32*, 0xE0) = 0;
}

void fn_8_A92E0(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f2;
	f32 temp_f30;
	f32 temp_f31;
	s32 temp_r0;

	M2C_FIELD(arg0, f32*, 0xF8) = (f32)(M2C_FIELD(arg0, f32*, 0xF8) + -0.06f);
	sp8                         = M2C_FIELD(arg0, f32*, 0xBC);
	spC                         = M2C_FIELD(arg0, f32*, 0xC0);
	sp10                        = M2C_FIELD(arg0, f32*, 0xC4);
	temp_f2                     = M2C_FIELD(arg0, f32*, 0xF8);
	spC                         = temp_f2;
	M2C_FIELD(arg0, f32*, 0xB0) = (f32)(M2C_FIELD(arg0, f32*, 0xB0) + sp8);
	M2C_FIELD(arg0, f32*, 0xB4) = (f32)(M2C_FIELD(arg0, f32*, 0xB4) + temp_f2);
	temp_f1                     = M2C_FIELD(arg0, f32*, 0xB8);
	M2C_FIELD(arg0, f32*, 0xB8) = (f32)(temp_f1 + sp10);
	temp_f1_2                   = fn_801991B4((u8*)arg0 + 0xBC, temp_f1, temp_f2);
	if (temp_f1_2 > 0.0f) {
		temp_f31 = (f32)asin(-M2C_FIELD(arg0, f32*, 0xC0) / temp_f1_2);
		temp_f30 = (f32)atan2(M2C_FIELD(arg0, f32*, 0xBC), M2C_FIELD(arg0, f32*, 0xC4));
		M2C_FIELD(arg0, s32*, 0xD8)
		    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0xD8), (s32)(10430.381f * temp_f31), 0x100);
		M2C_FIELD(arg0, s32*, 0xDC)
		    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0xDC), (s32)(10430.381f * temp_f30), 0x100);
		M2C_FIELD(arg0, s32*, 0xE0) = 0;
	} else {
		M2C_FIELD(arg0, s32*, 0xD8) = 0;
		M2C_FIELD(arg0, s32*, 0xDC) = 0;
		M2C_FIELD(arg0, s32*, 0xE0) = 0;
	}
	temp_r0                      = M2C_FIELD(arg0, s32*, 0x100) - 1;
	M2C_FIELD(arg0, s32*, 0x100) = temp_r0;
	if (temp_r0 < 0) {
		M2C_FIELD(arg0, s32*, 0xF4) = 1;
	}
}

void fn_8_A945C(void* arg0)
{
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f1_5;
	f32 temp_f1_6;
	f32 temp_f2;
	f32 temp_f30;
	f32 temp_f30_2;
	f32 temp_f31;
	f32 temp_f31_2;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 var_r0_2;
	u32 var_r0;
	void* temp_r3;
	void* temp_r3_2;

	temp_r0                     = M2C_FIELD(arg0, s32*, 0xE8) - 1;
	M2C_FIELD(arg0, s32*, 0xE8) = temp_r0;
	if (temp_r0 < 0) {
		M2C_FIELD(arg0, s32*, 0xF0) = 2;
		return;
	}
	if ((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0) {
		fn_80021824(&lbl_8042C1A4);
		temp_r3 = fn_800211A8((u8*)arg0 + 0x28);
		if (temp_r3 != NULL) {
			var_r0 = M2C_FIELD(temp_r3, u32*, 4);
		} else {
			var_r0 = 0U;
		}
		if (var_r0 != 0U) {
			var_r0_2 = 1;
		} else {
			goto block_8;
		}
	} else {
	block_8:
		var_r0_2 = 0;
	}
	if (var_r0_2 != 0) {
		M2C_FIELD(arg0, s32*, 0xF0) = 2;
		return;
	}
	temp_r0_2 = M2C_FIELD(arg0, s32*, 0xF4);
	switch (temp_r0_2) { /* irregular */
		case 0:
			M2C_FIELD(arg0, f32*, 0xF8) = (f32)(M2C_FIELD(arg0, f32*, 0xF8) + -0.06f);
			sp14                        = M2C_FIELD(arg0, f32*, 0xBC);
			sp18                        = M2C_FIELD(arg0, f32*, 0xC0);
			sp1C                        = M2C_FIELD(arg0, f32*, 0xC4);
			temp_f2                     = M2C_FIELD(arg0, f32*, 0xF8);
			sp18                        = temp_f2;
			M2C_FIELD(arg0, f32*, 0xB0) = (f32)(M2C_FIELD(arg0, f32*, 0xB0) + sp14);
			M2C_FIELD(arg0, f32*, 0xB4) = (f32)(M2C_FIELD(arg0, f32*, 0xB4) + temp_f2);
			temp_f1                     = M2C_FIELD(arg0, f32*, 0xB8);
			M2C_FIELD(arg0, f32*, 0xB8) = (f32)(temp_f1 + sp1C);
			temp_f1_2                   = fn_801991B4((u8*)arg0 + 0xBC, temp_f1, temp_f2);
			if (temp_f1_2 > 0.0f) {
				temp_f31 = (f32)asin(-M2C_FIELD(arg0, f32*, 0xC0) / temp_f1_2);
				temp_f30 = (f32)atan2(M2C_FIELD(arg0, f32*, 0xBC), M2C_FIELD(arg0, f32*, 0xC4));
				M2C_FIELD(arg0, s32*, 0xD8)
				    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0xD8), (s32)(10430.381f * temp_f31), 0x100);
				M2C_FIELD(arg0, s32*, 0xDC)
				    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0xDC), (s32)(10430.381f * temp_f30), 0x100);
				M2C_FIELD(arg0, s32*, 0xE0) = 0;
			} else {
				M2C_FIELD(arg0, s32*, 0xD8) = 0;
				M2C_FIELD(arg0, s32*, 0xDC) = 0;
				M2C_FIELD(arg0, s32*, 0xE0) = 0;
			}
			temp_r0_3                    = M2C_FIELD(arg0, s32*, 0x100) - 1;
			M2C_FIELD(arg0, s32*, 0x100) = temp_r0_3;
			if (temp_r0_3 < 0) {
				M2C_FIELD(arg0, s32*, 0xF4) = 1;
				return;
			}
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0xE4) != 0) {
				sp8  = M2C_FIELD(arg0, f32*, 0xB0);
				spC  = M2C_FIELD(arg0, f32*, 0xB4);
				sp10 = M2C_FIELD(arg0, f32*, 0xB8);
				M2C_FIELD(arg0, f32*, 0xBC)
				    = (f32)(M2C_FIELD(arg0, f32*, 0xC8) - M2C_FIELD(arg0, f32*, 0xB0));
				M2C_FIELD(arg0, f32*, 0xC0)
				    = (f32)(M2C_FIELD(arg0, f32*, 0xCC) - M2C_FIELD(arg0, f32*, 0xB4));
				temp_f1_3                   = M2C_FIELD(arg0, f32*, 0xD0);
				M2C_FIELD(arg0, f32*, 0xC4) = (f32)(temp_f1_3 - M2C_FIELD(arg0, f32*, 0xB8));
				temp_r3_2                   = (u8*)arg0 + 0xBC;
				fn_801990E0(temp_r3_2, temp_r3_2, temp_f1_3);
				M2C_FIELD(arg0, f32*, 0xFC) = (f32)(M2C_FIELD(arg0, f32*, 0xFC) + 0.2f);
				temp_f1_4                   = M2C_FIELD(arg0, f32*, 0xD4);
				if (M2C_FIELD(arg0, f32*, 0xFC) > temp_f1_4) {
					M2C_FIELD(arg0, f32*, 0xFC) = temp_f1_4;
				}
				M2C_FIELD(arg0, f32*, 0xBC)
				    = (f32)(M2C_FIELD(arg0, f32*, 0xBC) * M2C_FIELD(arg0, f32*, 0xFC));
				M2C_FIELD(arg0, f32*, 0xC0)
				    = (f32)(M2C_FIELD(arg0, f32*, 0xC0) * M2C_FIELD(arg0, f32*, 0xFC));
				M2C_FIELD(arg0, f32*, 0xC4)
				    = (f32)(M2C_FIELD(arg0, f32*, 0xC4) * M2C_FIELD(arg0, f32*, 0xFC));
				M2C_FIELD(arg0, f32*, 0xB0)
				    = (f32)(M2C_FIELD(arg0, f32*, 0xB0) + M2C_FIELD(arg0, f32*, 0xBC));
				M2C_FIELD(arg0, f32*, 0xB4)
				    = (f32)(M2C_FIELD(arg0, f32*, 0xB4) + M2C_FIELD(arg0, f32*, 0xC0));
				temp_f1_5                   = M2C_FIELD(arg0, f32*, 0xB8);
				M2C_FIELD(arg0, f32*, 0xB8) = (f32)(temp_f1_5 + M2C_FIELD(arg0, f32*, 0xC4));
				if (fn_800D7BD8((u8*)arg0 + 0xC8, &sp8, (u8*)arg0 + 0xB0, 0, temp_f1_5) < 2.0f) {
					M2C_FIELD(arg0, s32*, 0xE8) = 0;
				}
			}
			temp_f1_6 = fn_801991B4((u8*)arg0 + 0xBC);
			if (temp_f1_6 > 0.0f) {
				temp_f30_2 = (f32)asin(-M2C_FIELD(arg0, f32*, 0xC0) / temp_f1_6);
				temp_f31_2 = (f32)atan2(M2C_FIELD(arg0, f32*, 0xBC), M2C_FIELD(arg0, f32*, 0xC4));
				M2C_FIELD(arg0, s32*, 0xD8) = fn_800D7A94(
				    M2C_FIELD(arg0, s32*, 0xD8), (s32)(10430.381f * temp_f30_2), 0x100);
				M2C_FIELD(arg0, s32*, 0xDC) = fn_800D7A94(
				    M2C_FIELD(arg0, s32*, 0xDC), (s32)(10430.381f * temp_f31_2), 0x100);
				M2C_FIELD(arg0, s32*, 0xE0) = 0;
				return;
			}
			M2C_FIELD(arg0, s32*, 0xD8) = 0;
			M2C_FIELD(arg0, s32*, 0xDC) = 0;
			M2C_FIELD(arg0, s32*, 0xE0) = 0;
			break;
	}
}

void fn_8_A9848(void* arg0)
{
	M2C_FIELD(arg0, s32*, 0xF0)  = 1;
	M2C_FIELD(arg0, s32*, 0xF4)  = 1;
	M2C_FIELD(arg0, f32*, 0xF8)  = 0.0f;
	M2C_FIELD(arg0, f32*, 0xFC)  = 0.0f;
	M2C_FIELD(arg0, s32*, 0x100) = 0x1E;
}

void fn_8_A9874(void* arg0)
{
	s32 temp_r0;
	s32 temp_r3;
	s32 var_r0;
	u8 var_r5;
	u8 var_r6;

	var_r5  = 1;
	var_r6  = 1;
	temp_r3 = M2C_FIELD(&lbl_8029C310, s32*, 0x18) - 1;
	if ((u32)((u32)((1 | ~temp_r3) - ((u32)(1 - temp_r3) >> 1U)) >> 0x1FU) == 0) {
		var_r6 = 0;
	}
	if ((var_r6 == 0) && ((s32)M2C_FIELD(&lbl_8029C310, s32*, 0x18) != 3)) {
		var_r5 = 0;
	}
	if ((s32)var_r5 != 0) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	if (var_r0 == 0) {
		fn_8003BE78((u8*)arg0 + 0x28);
		return;
	}
	temp_r0 = M2C_FIELD(arg0, s32*, 0xF0);
	switch (temp_r0) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xF0)  = 1;
			M2C_FIELD(arg0, s32*, 0xF4)  = 1;
			M2C_FIELD(arg0, f32*, 0xF8)  = 0.0f;
			M2C_FIELD(arg0, f32*, 0xFC)  = 0.0f;
			M2C_FIELD(arg0, s32*, 0x100) = 0x1E;
			break;
		case 1:
			fn_8_A945C(arg0);
			break;
		case 2:
			fn_800BDEA0(0, (u8*)arg0 + 0xB0, 0, 1, -1);
			M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			break;
	}
	if ((fn_80017800(arg0) != 0) && ((u32)M2C_FIELD(arg0, u32*, 0x38) != 0U)) {
		M2C_FIELD(arg0, f32*, 0xA4) = (f32)M2C_FIELD(arg0, f32*, 0x88);
		M2C_FIELD(arg0, f32*, 0xA8) = (f32)M2C_FIELD(arg0, f32*, 0x8C);
		M2C_FIELD(arg0, f32*, 0xAC) = (f32)M2C_FIELD(arg0, f32*, 0x90);
		M2C_FIELD(arg0, f32*, 0x88) = (f32)M2C_FIELD(arg0, f32*, 0xB0);
		M2C_FIELD(arg0, f32*, 0x8C) = (f32)M2C_FIELD(arg0, f32*, 0xB4);
		M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0xB8);
		M2C_FIELD(arg0, s32*, 0x94) = (s32)M2C_FIELD(arg0, s32*, 0xD8);
		M2C_FIELD(arg0, s32*, 0x98) = (s32)M2C_FIELD(arg0, s32*, 0xDC);
		M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(arg0, s32*, 0xE0);
		fn_8003BC38((u8*)arg0 + 0x28);
	}
}

TObject* fn_8_A9A6C(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_164F4;
		dtor_8003C52C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_A9AF0(TObject* arg0, void* arg1, TObject* arg2)
{
	__ct__7TObjectFP7TObject(arg0, arg2);
	fn_8003C618(&arg0->unk28);
	arg0->unk18 = &lbl_8_data_164F4;
	arg0->unkB8 = 0.0f;
	arg0->unkB4 = 0.0f;
	arg0->unkB0 = 0.0f;
	arg0->unkC4 = 0.0f;
	arg0->unkC0 = 0.0f;
	arg0->unkBC = 0.0f;
	arg0->unkE0 = NULL;
	arg0->unkDC = 0;
	arg0->unkD8 = 0;
	arg0->unkD0 = 0.0f;
	arg0->unkCC = 0.0f;
	arg0->unkC8 = 0.0f;
	arg0->unkD4 = 0.0f;
	arg0->unkE4 = 1e-45f;
	arg0->unkE8 = 4.2e-43f;
	arg0->unkEC = 1.1e-44f;
	arg0->unk0  = lbl_8_data_164F0;
	arg0->unk1E = 0x104;
	arg0->unkF0 = 0.0f;
	arg0->unkB0 = M2C_FIELD(arg1, f32*, 0);
	arg0->unkB4 = M2C_FIELD(arg1, f32*, 4);
	arg0->unkB8 = M2C_FIELD(arg1, f32*, 8);
	arg0->unkBC = M2C_FIELD(arg1, f32*, 0xC);
	arg0->unkC0 = M2C_FIELD(arg1, f32*, 0x10);
	arg0->unkC4 = M2C_FIELD(arg1, f32*, 0x14);
	arg0->unkC8 = M2C_FIELD(arg1, f32*, 0x18);
	arg0->unkCC = M2C_FIELD(arg1, f32*, 0x1C);
	arg0->unkD0 = M2C_FIELD(arg1, f32*, 0x20);
	arg0->unkD4 = M2C_FIELD(arg1, f32*, 0x24);
	arg0->unkD8 = M2C_FIELD(arg1, s32*, 0x28);
	arg0->unkDC = M2C_FIELD(arg1, s32*, 0x2C);
	arg0->unkE0 = M2C_FIELD(arg1, void**, 0x30);
	arg0->unkE4 = M2C_FIELD(arg1, f32*, 0x34);
	arg0->unkE8 = M2C_FIELD(arg1, f32*, 0x38);
	arg0->unkEC = M2C_FIELD(arg1, f32*, 0x3C);
	fn_8003C200(&arg0->unk28, &lbl_8_data_164A8, 1, 4);
	arg0->unk88 = arg0->unkB0;
	arg0->unk8C = arg0->unkB4;
	arg0->unk90 = arg0->unkB8;
	return arg0;
}

TObject* fn_8_A9C6C(void* arg0)
{
	TObject* temp_r3;

	temp_r3 = fn_80018A34(lbl_8042C148, 0x104);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		fn_8003C618(&temp_r3->unk28);
		temp_r3->unk18 = &lbl_8_data_164F4;
		temp_r3->unkB8 = 0.0f;
		temp_r3->unkB4 = 0.0f;
		temp_r3->unkB0 = 0.0f;
		temp_r3->unkC4 = 0.0f;
		temp_r3->unkC0 = 0.0f;
		temp_r3->unkBC = 0.0f;
		temp_r3->unkE0 = NULL;
		temp_r3->unkDC = 0;
		temp_r3->unkD8 = 0;
		temp_r3->unkD0 = 0.0f;
		temp_r3->unkCC = 0.0f;
		temp_r3->unkC8 = 0.0f;
		temp_r3->unkD4 = 0.0f;
		temp_r3->unkE4 = 1e-45f;
		temp_r3->unkE8 = 4.2e-43f;
		temp_r3->unkEC = 1.1e-44f;
		temp_r3->unk0  = lbl_8_data_164F0;
		temp_r3->unk1E = 0x104;
		temp_r3->unkF0 = 0.0f;
		temp_r3->unkB0 = M2C_FIELD(arg0, f32*, 0);
		temp_r3->unkB4 = M2C_FIELD(arg0, f32*, 4);
		temp_r3->unkB8 = M2C_FIELD(arg0, f32*, 8);
		temp_r3->unkBC = M2C_FIELD(arg0, f32*, 0xC);
		temp_r3->unkC0 = M2C_FIELD(arg0, f32*, 0x10);
		temp_r3->unkC4 = M2C_FIELD(arg0, f32*, 0x14);
		temp_r3->unkC8 = M2C_FIELD(arg0, f32*, 0x18);
		temp_r3->unkCC = M2C_FIELD(arg0, f32*, 0x1C);
		temp_r3->unkD0 = M2C_FIELD(arg0, f32*, 0x20);
		temp_r3->unkD4 = M2C_FIELD(arg0, f32*, 0x24);
		temp_r3->unkD8 = M2C_FIELD(arg0, s32*, 0x28);
		temp_r3->unkDC = M2C_FIELD(arg0, s32*, 0x2C);
		temp_r3->unkE0 = M2C_FIELD(arg0, void**, 0x30);
		temp_r3->unkE4 = M2C_FIELD(arg0, f32*, 0x34);
		temp_r3->unkE8 = M2C_FIELD(arg0, f32*, 0x38);
		temp_r3->unkEC = M2C_FIELD(arg0, f32*, 0x3C);
		fn_8003C200(&temp_r3->unk28, &lbl_8_data_164A8, 1, 4);
		temp_r3->unk88 = temp_r3->unkB0;
		temp_r3->unk8C = temp_r3->unkB4;
		temp_r3->unk90 = temp_r3->unkB8;
	}
	return temp_r3;
}

void fn_8_A9E18(void)
{
	lbl_8_bss_19C0 = NULL;
}

void fn_8_A9E2C(void)
{
	if (((u32)lbl_8042C590 == 0U) && (fn_80057644(0x70) != 0U)) {
		fn_80100AAC();
	}
	lbl_8_bss_19C0 = fn_8010037C(lbl_8042C590, 5, 0xA);
}

void fn_8_A9E94(void* arg0, s32 arg1)
{
	M2C_UNK sp14;
	M2C_UNK sp8;
	s32 var_r31;

	if (arg0 != NULL) {
		var_r31 = 0;
	loop_3:
		if (var_r31 < (s32)(M2C_FIELD(arg0, s16*, 2) - 1)) {
			fn_800AFB50(arg0, var_r31, &sp14);
			fn_800AFB50(arg0, var_r31 + 1, &sp8);
			fn_8019941C(&sp14, &sp14, 1, arg1);
			fn_8019941C(&sp8, &sp8, 1, arg1);
			fn_8005FC74(&sp14, &sp8);
			var_r31 += 1;
			goto loop_3;
		}
	}
}

void fn_8_A9F48(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x1D;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_A9F68(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_A9F88(void* arg0, s32 arg1)
{
	s32 temp_r31;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = fn_8_A35BC(M2C_FIELD(arg0, s32*, 0x14));
			M2C_FIELD(arg0, s32*, 0x10) = 0x20;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				temp_r31                 = M2C_FIELD(arg0, s32*, 8);
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = temp_r31;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_AA04C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_AA06C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_AA08C(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	if ((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, s32*, 0xC)  = 0;
		M2C_FIELD(arg0, s32*, 0x10) = 0;
		M2C_FIELD(arg0, s32*, 4)    = 0;
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(s32, M2C_UNK), 0x10)(
		    M2C_FIELD(arg0, s32*, 4), 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
			fn_800A31B8(M2C_FIELD(arg0, u32*, 0x14));
		}
	}
}

s32 fn_8_AA100(void* arg0)
{
	s32 temp_r0;
	s32 temp_r0_2;
	s32 var_r3;
	void* temp_r3;

	fn_8_A353C(M2C_FIELD(arg0, void**, 0x14));
	if ((fn_800A3ED4(M2C_FIELD(arg0, void**, 0x14)) != 0)
	    && ((s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x19C) != 0x1D)) {
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 2;
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	temp_r3 = M2C_FIELD(arg0, void**, 0x14);
	temp_r0 = M2C_FIELD(temp_r3, s32*, 0x25C);
	if (temp_r0 != 0) {
		var_r3 = 0;
		switch (temp_r0) { /* irregular */
			case 1:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 2:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 32:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 29:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 2;
				M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
				    arg0, M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x25C) = 0;
		return var_r3;
	}
	if ((u32)(M2C_FIELD(temp_r3, s32*, 0x18C) & 0x2000) != 0) {
		temp_r0_2 = M2C_FIELD(temp_r3, s32*, 0x19C);
		if (temp_r0_2 != 0x20) {
			if (temp_r0_2 < 0x20) {
				if (temp_r0_2 != 2) {
					goto block_23;
				}
				goto block_22;
			}
		block_23:
			return 0;
		}
	block_22:
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 4;
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK), 0x10)(
		    arg0, M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	return 0;
}

void fn_8_AA3B8(void* arg0, s32 arg1, s32 arg2)
{
	s32 temp_r31;

	switch (arg1) { /* switch 1; irregular */
		case 0:     /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
				return;
			}
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			return;
		case 1: /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0x10) = 2;
				return;
			}
			break;
		case 3:             /* switch 1 */
			switch (arg2) { /* switch 2; irregular */
				case 0:     /* switch 2 */
					M2C_FIELD(arg0, s32*, 0x18) = fn_8_A35BC(M2C_FIELD(arg0, s32*, 0x14));
					M2C_FIELD(arg0, s32*, 0x10) = 0x20;
					return;
				case 1: /* switch 2 */
					fn_80137FE8((u8*)arg0 + 0x18);
					if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
						temp_r31                 = M2C_FIELD(arg0, s32*, 8);
						M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 3);
						M2C_FIELD(arg0, s32*, 4) = temp_r31;
						M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
						    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 0);
						return;
					}
					break;
			}
			break;
		case 2: /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0x10) = 0x1D;
				return;
			}
			break;
		case 4: /* switch 1 */
			if (arg2 != 0) {
				if (arg2 >= 0) {
					return;
				}
			} else {
				M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			}
			break;
	}
}

M2C_UNK** fn_8_AA528(M2C_UNK** arg0, s16 arg1)
{
	s32 temp_cr0_eq;

	temp_cr0_eq = arg0 == NULL;
	if (temp_cr0_eq == 0) {
		*arg0 = &lbl_8_data_16520;
		if (temp_cr0_eq == 0) {
			*arg0 = &lbl_8_data_16538;
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_AA58C(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_16538;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_16520;
}

M2C_UNK** fn_8_AA5C0(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = &lbl_8_data_16538;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_AA610(void* arg0)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;

	if ((void*)M2C_FIELD(arg0, void**, 0x4C) != NULL) {
		sp8  = M2C_FIELD(arg0, f32*, 0x54);
		spC  = M2C_FIELD(arg0, f32*, 0x58);
		sp10 = M2C_FIELD(arg0, f32*, 0x5C);
		sp14 = lbl_8_rodata_1AAC;
		if (fn_8019CE34(*lbl_8042C9A4, &sp8) != 0) {
			fn_80113874(4);
			fn_8014FF2C(M2C_FIELD(arg0, void**, 0x4C));
		}
	}
}

void fn_8_AA69C(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f1;
	f32 temp_f3;
	s32 temp_r30;
	void* temp_r3;

	fn_800D5A64((u8*)arg0 + 0x40, &lbl_8_rodata_1AA0, &lbl_8_rodata_1AB0, lbl_8_rodata_1AB0);
	M2C_FIELD(arg0, f32*, 0x50) = (f32)(M2C_FIELD(arg0, f32*, 0x50) + lbl_8_rodata_1AB4);
	M2C_FIELD(arg0, f32*, 0x60) = (f32)(M2C_FIELD(arg0, f32*, 0x60) + lbl_8_rodata_1AB8);
	if (M2C_FIELD(arg0, f32*, 0x50) > lbl_8_rodata_1ABC) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		if ((u32)lbl_8042C388 != 0U) {
			fn_800B4A38(0x1004, (u8*)arg0 + 0x54, 0, 1, 0, 0);
		}
	} else {
		M2C_FIELD(arg0, s32*, 0x64) = (s32)(M2C_FIELD(arg0, s32*, 0x64) + 0x200);
		temp_f1
		    = (lbl_8_rodata_1AC0 * (lbl_8_rodata_1AC4 * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x64))))
		    - lbl_8_rodata_1AC0;
		sp8                         = M2C_FIELD(arg0, f32*, 0x28);
		spC                         = M2C_FIELD(arg0, f32*, 0x2C);
		sp10                        = M2C_FIELD(arg0, f32*, 0x30);
		temp_f3                     = spC + temp_f1;
		spC                         = temp_f3;
		M2C_FIELD(arg0, f32*, 0x54) = (f32)(M2C_FIELD(arg0, f32*, 0x34) - sp8);
		M2C_FIELD(arg0, f32*, 0x58) = (f32)(M2C_FIELD(arg0, f32*, 0x38) - temp_f3);
		M2C_FIELD(arg0, f32*, 0x5C) = (f32)(M2C_FIELD(arg0, f32*, 0x3C) - sp10);
		M2C_FIELD(arg0, f32*, 0x54)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x54) * M2C_FIELD(arg0, f32*, 0x50));
		M2C_FIELD(arg0, f32*, 0x58)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x58) * M2C_FIELD(arg0, f32*, 0x50));
		M2C_FIELD(arg0, f32*, 0x5C)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x5C) * M2C_FIELD(arg0, f32*, 0x50));
		M2C_FIELD(arg0, f32*, 0x54) = (f32)(M2C_FIELD(arg0, f32*, 0x54) + sp8);
		M2C_FIELD(arg0, f32*, 0x58) = (f32)(M2C_FIELD(arg0, f32*, 0x58) + temp_f3);
		M2C_FIELD(arg0, f32*, 0x5C) = (f32)(M2C_FIELD(arg0, f32*, 0x5C) + sp10);
		temp_r3                     = M2C_FIELD(arg0, void**, 0x4C);
		if (temp_r3 != NULL) {
			temp_r30 = M2C_FIELD(temp_r3, s32*, 4);
			fn_8019EC30(temp_r30, (u8*)arg0 + 0x40, 0);
			fn_8019ED68(temp_r30, &lbl_80239984, 2, M2C_FIELD(arg0, f32*, 0x60));
			fn_8019EB94(temp_r30, (u8*)arg0 + 0x54, 2);
		}
	}
}

void fn_8_AA898(void* arg0)
{
	s32 temp_r31;
	void* temp_r3;

	temp_r3 = M2C_FIELD(arg0, void**, 0x4C);
	if (temp_r3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3, s32*, 4);
		fn_8019EC30(temp_r31, (u8*)arg0 + 0x40, 0);
		fn_8019ED68(temp_r31, &lbl_80239984, 2, M2C_FIELD(arg0, f32*, 0x60));
		fn_8019EB94(temp_r31, (u8*)arg0 + 0x54, 2);
	}
}

void fn_8_AA910(void* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x4C) != 0U) {
		fn_80150958();
		M2C_FIELD(arg0, u32*, 0x4C) = 0U;
	}
}

void fn_8_AA950(void* arg0)
{
	if ((u32)lbl_8_bss_1A48 != 0U) {
		M2C_FIELD(arg0, void**, 0x4C) = fn_80150588();
	}
}

TObject* fn_8_AA994(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_16900;
		if ((u32)arg0->unk4C != NULL) {
			fn_80150958();
			arg0->unk4C = NULL;
		}
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_AAA24(TObject* arg0, TObject* arg1, void* arg2)
{
	s32 temp_r30;
	void* temp_r3;

	__ct__7TObjectFP7TObject(arg0, arg1);
	arg0->unk18                 = &lbl_8_data_16900;
	arg0->unk0                  = lbl_8_data_168FC;
	arg0->unk1E                 = 0x68;
	M2C_FIELD(arg0, f32*, 0x28) = (f32)M2C_FIELD(arg2, f32*, 0);
	arg0->unk2C                 = M2C_FIELD(arg2, f32*, 4);
	arg0->unk30                 = M2C_FIELD(arg2, f32*, 8);
	arg0->unk34                 = M2C_FIELD(arg2, s32*, 0xC);
	arg0->unk38                 = M2C_FIELD(arg2, s32*, 0x10);
	arg0->unk3C                 = M2C_FIELD(arg2, s32*, 0x14);
	arg0->unk40                 = M2C_FIELD(arg2, f32*, 0x18);
	arg0->unk44                 = M2C_FIELD(arg2, f32*, 0x1C);
	arg0->unk48                 = M2C_FIELD(arg2, f32*, 0x20);
	arg0->unk48                 = lbl_8_rodata_1ABC;
	arg0->unk44                 = lbl_8_rodata_1ABC;
	arg0->unk40                 = lbl_8_rodata_1ABC;
	arg0->unk50                 = lbl_8_rodata_1AC8;
	arg0->unk64                 = 0;
	arg0->unk54                 = M2C_FIELD(arg0, f32*, 0x28);
	arg0->unk58                 = arg0->unk2C;
	arg0->unk5C                 = arg0->unk30;
	arg0->unk60                 = lbl_8_rodata_1AC8;
	arg0->unk4C                 = NULL;
	if ((u32)lbl_8_bss_1A48 != 0U) {
		arg0->unk4C = fn_80150588();
	}
	temp_r3 = arg0->unk4C;
	if (temp_r3 != NULL) {
		temp_r30 = M2C_FIELD(temp_r3, s32*, 4);
		fn_8019EC30(temp_r30, &arg0->unk40, 0);
		fn_8019ED68(temp_r30, &lbl_80239984, 2, arg0->unk60);
		fn_8019EB94(temp_r30, &arg0->unk54, 2);
	}
	return arg0;
}

void fn_8_AAB80(void)
{
	lbl_8_bss_1A48 = 0U;
}

void fn_8_AAB94(void)
{
	lbl_8_bss_1A48 = fn_8005EA04(&lbl_8_data_1692C);
}

s32 fn_8_AABC8(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 1) {
		return 2;
	}
	if (fn_80100BF8(M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A)) == 0) {
		return 0;
	}
	return ((lbl_8_rodata_1ACC * (f32)fn_801C28D8()) < lbl_8_rodata_1AD0) == 0;
}

void fn_8_AAC6C(void* arg0, s32 arg1)
{
	fn_8_90B10(arg1);
}

void fn_8_AAC90(void* arg0, void* arg1)
{
	f32 temp_f0;
	f32 var_f1;

	var_f1  = M2C_FIELD(arg1, f32*, 0x14) + M2C_FIELD(arg0, f32*, 0x1A4);
	temp_f0 = M2C_FIELD(arg0, f32*, 0x258);
	if (var_f1 > temp_f0) {
		var_f1 = temp_f0;
	}
	M2C_FIELD(arg0, f32*, 0x1A4) = var_f1;
	M2C_FIELD(arg0, s16*, 0x2E)  = (s16)var_f1;
	M2C_FIELD(arg0, f32*, 0x254) = (f32)M2C_FIELD(arg0, f32*, 0x1A4);
	if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
		fn_8010B074();
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
		fn_8010AFF8(6);
		fn_8010B208(
		    M2C_FIELD(arg0, u32*, 0x31C), &lbl_8_rodata_1AC8, lbl_8_rodata_1AC8, lbl_8_rodata_1AC8);
	}
}

void fn_8_AAD2C(void* arg0, void* arg1)
{
	f32 temp_f1;
	f32 var_f0;

	if ((s32)M2C_FIELD(arg1, u8*, 0) != 3) {
		return;
	}
	var_f0  = M2C_FIELD(arg1, f32*, 0x14) + M2C_FIELD(arg0, f32*, 0x1A4);
	temp_f1 = M2C_FIELD(arg0, f32*, 0x258);
	if (var_f0 > temp_f1) {
		var_f0 = temp_f1;
	}
	M2C_FIELD(arg0, f32*, 0x1A4) = var_f0;
	M2C_FIELD(arg0, s16*, 0x2E)  = (s16)var_f0;
	M2C_FIELD(arg0, f32*, 0x254) = (f32)M2C_FIELD(arg0, f32*, 0x1A4);
	if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
		fn_8010B074();
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
		fn_8010AFF8(6);
		fn_8010B208(
		    M2C_FIELD(arg0, u32*, 0x31C), &lbl_8_rodata_1AC8, lbl_8_rodata_1AC8, lbl_8_rodata_1AC8);
	}
}

s32 fn_8_AADD8(void* arg0)
{
	if ((s32)M2C_FIELD(arg0, s32*, 0x2D0) != -1) {
		fn_800E1208(0xF, 0);
		M2C_FIELD(arg0, s32*, 0x2D0) = -1;
		return 1;
	}
	return 0;
}

s32 fn_8_AAE2C(void* arg0)
{
	s32 temp_r3;

	temp_r3 = fn_80103324((u8*)arg0 + 0x2C4, &lbl_8_rodata_1AE0, lbl_8_rodata_1AE0);
	if (temp_r3 != -1) {
		M2C_FIELD(arg0, s32*, 0x2D0) = temp_r3;
		fn_800E1208(M2C_FIELD(arg0, s32*, 0x2D0), 0x17, 0);
		return 1;
	}
	M2C_FIELD(arg0, s32*, 0x2D0) = -1;
	return 0;
}

s32 fn_8_AAE98(void* arg0)
{
	s32 sp1C;
	f32 sp18;
	s32 sp14;
	s32 sp10;
	f32 spC;
	s32 sp8;
	s32 temp_r0;
	void* temp_r5;

	temp_r0 = M2C_FIELD(arg0, s32*, 0x27C);
	if (temp_r0 != -1) {
		temp_r5 = *(void**)((u8*)&lbl_802AD090 + (temp_r0 * 4));
		if (temp_r5 != NULL) {
			sp14 = M2C_FIELD(arg0, s32*, 0x140);
			sp18 = M2C_FIELD(arg0, f32*, 0x144);
			sp1C = M2C_FIELD(arg0, s32*, 0x148);
			sp18 = lbl_8_rodata_1AC8;
			sp8  = M2C_FIELD(temp_r5, s32*, 0x18);
			spC  = M2C_FIELD(temp_r5, f32*, 0x1C);
			sp10 = M2C_FIELD(temp_r5, s32*, 0x20);
			spC  = lbl_8_rodata_1AC8;
			if (fn_800D71DC(&sp14, &sp8) < lbl_8_rodata_1AE4) {
				return 1;
			}
		}
	}
	return 0;
}

void fn_8_AAF48(void) { }
}
