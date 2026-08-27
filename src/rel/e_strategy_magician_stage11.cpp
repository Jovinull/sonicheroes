#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

static f32 lbl_8_rodata_1AF0;
static f32 lbl_8_rodata_1AF4;
static f32 lbl_8_rodata_1AF8;
static f32 lbl_8_rodata_1B08;
static f32 lbl_8_rodata_1B0C;
static f32 lbl_8_rodata_1B14;
static f32 lbl_8_rodata_1B20;

typedef struct TObject {
	/* 0x000 */ s32 unk0;        /* inferred */
	/* 0x004 */ char pad4[0x14]; /* maybe part of unk0[6]? */
	/* 0x018 */ M2C_UNK* unk18;  /* inferred */
	/* 0x01C */ char pad1C[2];
	/* 0x01E */ s16 unk1E;        /* inferred */
	/* 0x020 */ char pad20[8];    /* maybe part of unk1E[5]? */
	/* 0x028 */ f32 unk28;        /* inferred */
	/* 0x02C */ f32 unk2C;        /* inferred */
	/* 0x030 */ f32 unk30;        /* inferred */
	/* 0x034 */ f32 unk34;        /* inferred */
	/* 0x038 */ f32 unk38;        /* inferred */
	/* 0x03C */ f32 unk3C;        /* inferred */
	/* 0x040 */ f32 unk40;        /* inferred */
	/* 0x044 */ f32 unk44;        /* inferred */
	/* 0x048 */ f32 unk48;        /* inferred */
	/* 0x04C */ void* unk4C;      /* inferred */
	/* 0x050 */ f32 unk50;        /* inferred */
	/* 0x054 */ f32 unk54;        /* inferred */
	/* 0x058 */ f32 unk58;        /* inferred */
	/* 0x05C */ f32 unk5C;        /* inferred */
	/* 0x060 */ f32 unk60;        /* inferred */
	/* 0x064 */ s32 unk64;        /* inferred */
	/* 0x068 */ char pad68[0x68]; /* maybe part of unk64[0x1B]? */
	/* 0x0D0 */ s32 unkD0;        /* inferred */
	/* 0x0D4 */ s32 unkD4;        /* inferred */
	/* 0x0D8 */ char padD8[0x68]; /* maybe part of unkD4[0x1B]? */
	/* 0x140 */ M2C_UNK unk140;   /* inferred */
	/* 0x140 */ char pad140[0x100];
	/* 0x240 */ M2C_UNK unk240; /* inferred */
	/* 0x240 */ char pad240[0x34];
	/* 0x274 */ s32 unk274;        /* inferred */
	/* 0x278 */ char pad278[0x4C]; /* maybe part of unk274[0x14]? */
	/* 0x2C4 */ M2C_UNK unk2C4;    /* inferred */
	/* 0x2C4 */ char pad2C4[4];
	/* 0x2C8 */ f32 unk2C8; /* inferred */
	/* 0x2CC */ char pad2CC[4];
	/* 0x2D0 */ s32 unk2D0; /* inferred */
	/* 0x2D4 */ s32 unk2D4; /* inferred */
	/* 0x2D8 */ s32 unk2D8; /* inferred */
	/* 0x2DC */ u32 unk2DC; /* inferred */
	/* 0x2E0 */ char pad2E0[4];
	/* 0x2E4 */ s32 unk2E4;        /* inferred */
	/* 0x2E8 */ char pad2E8[0x10]; /* maybe part of unk2E4[5]? */
	/* 0x2F8 */ s32 unk2F8;        /* inferred */
	/* 0x2FC */ char pad2FC[4];
	/* 0x300 */ f32 unk300;        /* inferred */
	/* 0x304 */ f32 unk304;        /* inferred */
	/* 0x308 */ f32 unk308;        /* inferred */
	/* 0x30C */ s32 unk30C;        /* inferred */
	/* 0x310 */ s32 unk310;        /* inferred */
	/* 0x314 */ char pad314[0x18]; /* maybe part of unk310[7]? */
	/* 0x32C */ f32 unk32C;        /* inferred */
	/* 0x330 */ f32 unk330;        /* inferred */
	/* 0x334 */ f32 unk334;        /* inferred */
	/* 0x338 */ f32 unk338;        /* inferred */
	/* 0x33C */ f32 unk33C;        /* inferred */
	/* 0x340 */ f32 unk340;        /* inferred */
	/* 0x344 */ f32 unk344;        /* inferred */
	/* 0x348 */ f32 unk348;        /* inferred */
	/* 0x34C */ f32 unk34C;        /* inferred */
} TObject;                         /* size >= 0x350 */

extern "C" {

void* __ct__7TObjectFP7TObject(void*, void*); /* extern */
s32 fn_80017800(void*);                       /* extern */
TObject* fn_80018A34(...);                    /* extern */
M2C_UNK fn_8003BC38(...);                     /* extern */
M2C_UNK fn_8005DABC(...);                     /* extern */
M2C_UNK fn_8005FD20(...);                     /* extern */
M2C_UNK fn_8005FD8C(...);                     /* extern */
void* fn_8006298C(...);                       /* extern */
M2C_UNK fn_80066D20(...);                     /* extern */
s32 fn_800A34D0(void*, void*, f32);           /* extern */
s32 fn_800A3D48(void*);                       /* extern */
s32 fn_800A4668(void*);                       /* extern */
M2C_UNK fn_800A4A8C(...);                     /* extern */
s32 fn_800A5888(void*, void*, f32);           /* extern */
s32 fn_800A5A54(...);                         /* extern */
f32 fn_800A5AC0(...);                         /* extern */
s32 fn_800A5B34(void*);                       /* extern */
s32 fn_800A5B50(void*, s32);                  /* extern */
s32 fn_800A5C6C(void*, s32);                  /* extern */
s32 fn_800A6334(void);                        /* extern */
s32 fn_800AB104(s32);                         /* extern */
M2C_UNK fn_800B4A38(...);                     /* extern */
s32 fn_800B7514(void*, void*, void*, f32);    /* extern */
s32 fn_800B7820(void);                        /* extern */
s32 fn_800B7864(s32);                         /* extern */
f32 fn_800D71DC(...);                         /* extern */
f32 fn_800D7328(...);                         /* extern */
s32 fn_800D7A94(s32, s32, s32);               /* extern */
f32 fn_800D7B00(s32);                         /* extern */
f32 fn_800D8BC4(...);                         /* extern */
M2C_UNK fn_800E1208(...);                     /* extern */
s32 fn_80100BF8(s32);                         /* extern */
M2C_UNK fn_80100CFC(...);                     /* extern */
M2C_UNK fn_80103214(...);                     /* extern */
s32 fn_80103324(void*, void*, f32);           /* extern */
s32 fn_8010AFB0(void);                        /* extern */
M2C_UNK fn_8010AFF8(...);                     /* extern */
s32 fn_8010B074(void);                        /* extern */
s32 fn_8010B0AC(s32, f32);                    /* extern */
M2C_UNK fn_8010B208(...);                     /* extern */
s32 fn_8010B350(void*, void*);                /* extern */
M2C_UNK fn_80113874(...);                     /* extern */
M2C_UNK fn_801138B4(...);                     /* extern */
M2C_UNK fn_801138F4(...);                     /* extern */
M2C_UNK fn_80113940(...);                     /* extern */
M2C_UNK fn_8011B844(...);                     /* extern */
s32 fn_8011C188(s32, s32);                    /* extern */
M2C_UNK fn_8011C6EC(...);                     /* extern */
s32 fn_80130B40(s32);                         /* extern */
s32 fn_80137FE8(void*);                       /* extern */
M2C_UNK fn_8014FF2C(...);                     /* extern */
M2C_UNK fn_8014FFBC(...);                     /* extern */
void* fn_80150588(...);                       /* extern */
M2C_UNK fn_801990E0(...);                     /* extern */
M2C_UNK fn_8019941C(...);                     /* extern */
void* fn_8019E8EC(...);                       /* extern */
M2C_UNK fn_8019EB94(...);                     /* extern */
M2C_UNK fn_8019EC30(...);                     /* extern */
M2C_UNK fn_8019ED68(...);                     /* extern */
s32 fn_801C28D8(...);                         /* extern */
s32 fn_8_90B10(s32);                          /* extern */
M2C_UNK fn_8_A504(...);                       /* extern */
void fn_8_AE604(void*);                       /* extern */
M2C_UNK fn_8_AEB80(...);                      /* extern */
extern M2C_UNK fn_8005BF88;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_802AD070;
extern M2C_UNK lbl_802AD090;
extern M2C_UNK lbl_80303D28;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern u32 lbl_8042C388;
extern u32 lbl_8042C6D0;
extern M2C_UNK lbl_8_bss_19C8;
extern s32 lbl_8_bss_19D0;
extern M2C_UNK lbl_8_bss_19D4;
extern s32 lbl_8_bss_1A18;
extern u32 lbl_8_bss_1A48;
extern s32 lbl_8_data_168FC;
extern M2C_UNK lbl_8_data_16900;
extern M2C_UNK lbl_8_rodata_1A2C;
extern M2C_UNK lbl_8_rodata_1A38;
extern M2C_UNK lbl_8_rodata_1A54;
extern M2C_UNK lbl_8_rodata_1A60;
extern M2C_UNK lbl_8_rodata_1A6C;
extern M2C_UNK lbl_8_rodata_1A84;
extern M2C_UNK lbl_8_rodata_1A94;
extern f32 lbl_8_rodata_1AB8;
extern f32 lbl_8_rodata_1ABC;
extern f32 lbl_8_rodata_1AC4;
extern f32 lbl_8_rodata_1AC8;
extern f32 lbl_8_rodata_1ACC;
extern f32 lbl_8_rodata_1AD0;
extern M2C_UNK lbl_8_rodata_1AD8;
extern f32 lbl_8_rodata_1AE0;
extern f32 lbl_8_rodata_1AE4;
static M2C_UNK lbl_8_data_16A30;          /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16A40;          /* unable to generate initializer: unknown type */
static M2C_UNK magicianObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK magicianObjectFieldTypes;  /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00016B02_data;      /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_16B08;          /* unable to generate initializer: unknown type */
static M2C_UNK jumptable_8_data_16B5C;    /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_rodata_1B30;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B34;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B38;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B3C;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B40;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B44;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B48;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B4C;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B50;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B54;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B58;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B5C;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B60;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B64;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B68;         /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1B6C;         /* unable to generate initializer: unknown type; const */

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
		fn_8010AFF8(6U);
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
		fn_8010AFF8(6U);
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

s32 fn_8_AAF4C(void* arg0)
{
	f32 temp_f1;
	s32 var_r31;

	var_r31 = 0;
	temp_f1 = M2C_FIELD(arg0, f32*, 0x1A4);
	if (temp_f1 != M2C_FIELD(arg0, f32*, 0x254)) {
		M2C_FIELD(arg0, f32*, 0x254) = temp_f1;
		if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
			if ((s32)M2C_FIELD(arg0, s32*, 0x19C) == 0x24) {
				fn_8010B0AC(0x5A, M2C_FIELD(arg0, f32*, 0x258));
			} else {
				fn_8010B208(M2C_BITWISE(u32, M2C_FIELD(arg0, f32*, 0x258)));
			}
		}
		if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
			fn_8010B074();
		}
		var_r31 = 1;
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
		fn_8010B350((u8*)arg0 + 0x140, &lbl_8_rodata_1A2C);
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
		fn_8010B350((u8*)arg0 + 0x140, &lbl_8_rodata_1A2C);
	}
	return var_r31;
}

s32 fn_8_AB014(void* arg0)
{
	s32 temp_r3;

	temp_r3 = fn_800A6334();
	if ((temp_r3 == 1) && ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U)
	    && (((u32)M2C_FIELD(arg0, u32*, 0x318) == 0U) || (fn_8010AFB0() == 0))) {
		fn_8010AFF8(M2C_FIELD(arg0, u32*, 0x31C), 1);
		fn_8010B208(
		    M2C_FIELD(arg0, u32*, 0x31C), &lbl_8_rodata_1AC8, lbl_8_rodata_1AC8, lbl_8_rodata_1AC8);
	}
	return temp_r3;
}

s32 fn_8_AB0A0(void* arg0)
{
	s32 temp_r31;

	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		return 0;
	}
	temp_r31                     = fn_800A5A54();
	M2C_FIELD(arg0, s32*, 0x150) = fn_800D7A94(
	    M2C_FIELD(arg0, s32*, 0x150), M2C_FIELD(arg0, s32*, 0x174), M2C_FIELD(arg0, s32*, 0x180));
	if (temp_r31 < 0x80) {
		M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(arg0, s32*, 0x174);
		return 1;
	}
	return 0;
}

s32 fn_8_AB11C(void* arg0)
{
	f32 temp_f2;
	s32 var_r5;

	var_r5 = 1;
	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		return 1;
	}
	temp_f2                      = M2C_FIELD(arg0, f32*, 0x1C4);
	M2C_FIELD(arg0, f32*, 0x144) = (f32)(M2C_FIELD(arg0, f32*, 0x144) + 0.2f);
	M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
	if (M2C_FIELD(arg0, f32*, 0x144) == temp_f2) {
		M2C_FIELD(arg0, f32*, 0x144) = temp_f2;
	} else {
		var_r5 = 0;
	}
	return var_r5;
}

s32 fn_8_AB174(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	s32 temp_r4;
	s32 var_r30;
	void* temp_r3;

	temp_r4 = M2C_FIELD(arg0, s32*, 0x27C);
	if (temp_r4 != -1) {
		sp8     = M2C_FIELD(arg0, f32*, 0x140);
		spC     = M2C_FIELD(arg0, f32*, 0x144);
		sp10    = M2C_FIELD(arg0, f32*, 0x148);
		temp_r3 = *(void**)((u8*)&lbl_802AD090 + (temp_r4 * 4));
		if (temp_r3 != NULL) {
			sp8 -= M2C_FIELD(temp_r3, f32*, 0x18);
			spC -= M2C_FIELD(temp_r3, f32*, 0x1C);
			sp10 -= M2C_FIELD(temp_r3, f32*, 0x20);
		}
		spC = lbl_8_rodata_1AC8;
		fn_801990E0(&sp8, &sp8);
		M2C_FIELD(arg0, f32*, 0x158) = sp8;
		M2C_FIELD(arg0, f32*, 0x15C) = spC;
		M2C_FIELD(arg0, f32*, 0x160) = sp10;
	}
	var_r30 = 1;
	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {

	} else {
		if ((fn_800A5AC0(arg0) < lbl_8_rodata_1AC4)
		    || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
			fn_800A4668(arg0);
			var_r30 = 0;
		} else {
			fn_800A4A8C(arg0, M2C_FIELD(arg0, f32*, 0x358));
		}
		fn_800A5C6C(arg0, 0xF00);
		if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
		    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
			M2C_FIELD(arg0, f32*, 0x15C) = (f32)lbl_8_rodata_1AC8;
		}
		if (fn_800A5888(arg0, &lbl_8_rodata_1AF0, -1.0f) != 0) {
			fn_800A5B50(arg0, 0xF00);
			var_r30 = 0;
		}
	}
	return var_r30;
}

s32 fn_8_AB31C(void* arg0)
{
	s32 var_r31;

	var_r31 = 1;
	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		return 1;
	}
	if ((fn_800A5AC0() < lbl_8_rodata_1AC4) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
		fn_800A4668(arg0);
		var_r31 = 0;
	} else {
		fn_800A4A8C(arg0, lbl_8_rodata_1AC4);
	}
	fn_800A5C6C(arg0, 0xF00);
	if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
	    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
		M2C_FIELD(arg0, f32*, 0x15C) = (f32)lbl_8_rodata_1AC8;
	}
	if (fn_800A5888(arg0, &lbl_8_rodata_1AF0, -1.0f) != 0) {
		fn_800A5B50(arg0, 0xF00);
		var_r31 = 0;
	}
	return var_r31;
}

s32 fn_8_AB424(void* arg0)
{
	s32 var_r31;

	var_r31 = 1;
	if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {
		return 1;
	}
	if ((fn_800A5AC0() < lbl_8_rodata_1AC4) || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
		fn_800A4668(arg0);
		var_r31 = 0;
	} else {
		fn_800A4A8C(arg0, M2C_FIELD(arg0, f32*, 0x358));
	}
	fn_800A5C6C(arg0, 0xF00);
	if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
	    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
		M2C_FIELD(arg0, f32*, 0x15C) = (f32)lbl_8_rodata_1AC8;
	}
	if (fn_800A5888(arg0, &lbl_8_rodata_1AF0, -1.0f) != 0) {
		fn_800A5B50(arg0, 0xF00);
		var_r31 = 0;
	}
	return var_r31;
}

void fn_8_AB52C(void* arg0)
{
	f32 sp14;
	s32 sp10;
	f32 spC;
	f32 sp8;
	f32* var_r3;
	f32 temp_f1;
	f32 temp_f1_2;

	M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
	if (M2C_FIELD(arg0, f32*, 0x2B8) != lbl_8_rodata_1AC8) {
		fn_800B7864(0);
		spC     = M2C_FIELD(&lbl_8_rodata_1A94, f32*, 0);
		sp10    = M2C_FIELD(&lbl_8_rodata_1A94, s32*, 4);
		sp14    = M2C_FIELD(&lbl_8_rodata_1A94, f32*, 8);
		temp_f1 = lbl_8_rodata_1ABC
		    - (0.004f * (M2C_FIELD(arg0, f32*, 0x144) - M2C_FIELD(arg0, f32*, 0x284)));
		sp8    = temp_f1;
		var_r3 = &lbl_8_rodata_1AF4;
		if (temp_f1 < 0.2f) {

		} else {
			var_r3 = &lbl_8_rodata_1AF8;
			if (temp_f1 > 1.0f) {

			} else {
				var_r3 = &sp8;
			}
		}
		temp_f1_2 = *var_r3;
		sp8       = temp_f1_2;
		fn_800B7514((u8*)arg0 + 0x280, (u8*)arg0 + 0x2A4, &spC, temp_f1_2);
		spC  = 6.0f;
		sp14 = 6.0f;
		fn_800B7514((u8*)arg0 + 0x28C, (u8*)arg0 + 0x2A4, &spC, sp8);
		fn_800B7514((u8*)arg0 + 0x298, (u8*)arg0 + 0x2A4, &spC, sp8);
		fn_800B7820();
	}
}

void fn_8_AB654(void* arg0)
{
	f32 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;
	f32 temp_f1;
	s32 temp_r4;

	M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
	if (M2C_FIELD(arg0, f32*, 0x2B8) != lbl_8_rodata_1AC8) {
		temp_f1 = M2C_FIELD(arg0, f32*, 0x2B4);
		M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
		if ((temp_f1 != 0.2f) && (temp_f1 < lbl_8_rodata_1ABC)) {
			fn_80113940();
			fn_801138B4();
			fn_80113874(0x10);
			sp8  = M2C_FIELD(&lbl_8_rodata_1A38, s32*, 0);
			spC  = M2C_FIELD(&lbl_8_rodata_1A38, s32*, 4);
			sp10 = M2C_FIELD(&lbl_8_rodata_1A38, s32*, 8);
			sp14 = M2C_FIELD(&lbl_8_rodata_1A38, f32*, 0xC);
			sp14 = M2C_FIELD(arg0, f32*, 0x2B4);
			fn_8005DABC(M2C_FIELD(arg0, s32*, 0xE8), &sp8);
			fn_8014FF2C(M2C_FIELD(arg0, s32*, 0xE8));
			fn_801138F4();
		}
		if ((s32)M2C_FIELD(arg0, s32*, 0x2F8) != 0) {
			temp_r4 = M2C_FIELD(lbl_8042C180, s32*, 0x30);
			if ((s32)lbl_8_bss_1A18 != temp_r4) {
				lbl_8_bss_1A18 = temp_r4;
				fn_8011B844(lbl_8_bss_19D0, &lbl_8_rodata_1ABC, lbl_8_rodata_1ABC);
				fn_8014FFBC(M2C_FIELD(&lbl_8_bss_19C8, s32*, 4), &fn_8005BF88, &lbl_8_bss_19D4);
			}
			fn_80113940();
			fn_801138B4();
			fn_80113874(0x10);
			fn_8014FF2C(M2C_FIELD(arg0, s32*, 0x2FC));
			fn_801138F4();
		}
	}
}

void fn_8_AB7AC(void* arg0)
{
	s32 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;

	M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
	if (M2C_FIELD(arg0, f32*, 0x2B8) != lbl_8_rodata_1AC8) {
		M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
		if (M2C_FIELD(arg0, f32*, 0x2B4) == lbl_8_rodata_1ABC) {
			M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x90)();
			fn_80113874();
			sp8  = M2C_FIELD(&lbl_8_rodata_1A84, s32*, 0);
			spC  = M2C_FIELD(&lbl_8_rodata_1A84, s32*, 4);
			sp10 = M2C_FIELD(&lbl_8_rodata_1A84, s32*, 8);
			sp14 = M2C_FIELD(&lbl_8_rodata_1A84, s32*, 0xC);
			fn_8005DABC(M2C_FIELD(arg0, s32*, 0xE8), &sp8);
			fn_8014FF2C(M2C_FIELD(arg0, s32*, 0xE8));
		}
	}
}

void fn_8_AB85C(void* arg0)
{
	fn_8_AEB80();
	fn_8_AE604(arg0);
}

void fn_8_AB890(void* arg0)
{
	s32 var_r0;
	s32 var_r0_2;
	void** temp_r3;

	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x310) = var_r0;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0_2 = 0;
	} else {
		var_r0_2 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x314) = var_r0_2;
	if ((u32)M2C_FIELD(arg0, u32*, 0x38) != 0U) {
		M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(arg0, f32*, 0x88);
		M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(arg0, f32*, 0x8C);
		M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(arg0, f32*, 0x90);
	}
	fn_800A5B34(arg0);
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(void*), 0x38)(arg0);
	temp_r3 = M2C_FIELD(arg0, void***, 0x248);
	if (temp_r3 != NULL) {
		M2C_FIELD(*temp_r3, M2C_UNK(**)(void*), 0xC)(arg0);
	}
	M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(void*, s32, M2C_UNK), 0x50)(
	    arg0, M2C_FIELD(arg0, s32*, 0x19C), 1);
	fn_8_AE604(arg0);
	fn_800A3D48(arg0);
	if ((fn_80017800(arg0) != 0) && ((u32)M2C_FIELD(arg0, u32*, 0x38) != 0U)) {
		M2C_FIELD(arg0, f32*, 0xA4) = (f32)M2C_FIELD(arg0, f32*, 0x88);
		M2C_FIELD(arg0, f32*, 0xA8) = (f32)M2C_FIELD(arg0, f32*, 0x8C);
		M2C_FIELD(arg0, f32*, 0xAC) = (f32)M2C_FIELD(arg0, f32*, 0x90);
		M2C_FIELD(arg0, f32*, 0x88) = (f32)M2C_FIELD(arg0, f32*, 0x140);
		M2C_FIELD(arg0, f32*, 0x8C) = (f32)M2C_FIELD(arg0, f32*, 0x144);
		M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0x148);
		M2C_FIELD(arg0, s32*, 0x94) = (s32)M2C_FIELD(arg0, s32*, 0x14C);
		M2C_FIELD(arg0, s32*, 0x98) = (s32)M2C_FIELD(arg0, s32*, 0x150);
		M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(arg0, s32*, 0x154);
		fn_8003BC38((u8*)arg0 + 0x28);
	}
}

void fn_8_ABA38(void* arg0, s32 arg1)
{
	f32 temp_f2;
	s32 var_r4;

	switch (arg1) { /* irregular */
		case 0:
			if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
				fn_8010B074();
			}
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
				return;
			}
			M2C_FIELD(arg0, s32*, 0xD4) = 6;
			return;
		case 1:
			var_r4 = 1;
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {

			} else {
				temp_f2                      = M2C_FIELD(arg0, f32*, 0x1C4);
				M2C_FIELD(arg0, f32*, 0x144) = (f32)(M2C_FIELD(arg0, f32*, 0x144) + 0.2f);
				M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
				if (M2C_FIELD(arg0, f32*, 0x144) == temp_f2) {
					M2C_FIELD(arg0, f32*, 0x144) = temp_f2;
				} else {
					var_r4 = 0;
				}
			}
			if (var_r4 != 0) {
				M2C_FIELD(arg0, s32*, 0x250) = 0x1F;
			}
			return;
	}
}

void fn_8_ABB10(void* arg0, s32 arg1)
{
	s32 sp10;
	f32 spC;
	s32 sp8;
	f32 temp_f1;
	f32 temp_f1_2;
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0xA;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 0xB;
			}
			M2C_FIELD(arg0, s32*, 0x2F0) = 0x5A;
			M2C_FIELD(arg0, s32*, 0x2F4) = (s32)M2C_FIELD(arg0, s32*, 0x238);
			if ((u32)lbl_8042C6D0 == 0U) {
				fn_8011C6EC();
			}
			fn_8011C188(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x238));
			M2C_FIELD(arg0, s32*, 0x2EC) = 0;
			M2C_FIELD(arg0, u16*, 0x30)  = (u16)(M2C_FIELD(arg0, u16*, 0x30) | 0x200);
			return;
		case 1:
			temp_r0                      = M2C_FIELD(arg0, s32*, 0x2F0) - 1;
			M2C_FIELD(arg0, s32*, 0x2F0) = temp_r0;
			if (temp_r0 == 0) {
				if ((u32)M2C_FIELD(arg0, u32*, 0x318) != 0U) {
					fn_8010B074();
				}
				if ((u32)M2C_FIELD(arg0, u32*, 0x31C) != 0U) {
					fn_8010AFF8(2U);
					fn_8010B208(M2C_FIELD(arg0, u32*, 0x31C), &lbl_8_rodata_1AC8, lbl_8_rodata_1AC8,
					    lbl_8_rodata_1AC8);
				}
			}
			sp8     = M2C_FIELD(arg0, s32*, 0x280);
			spC     = M2C_FIELD(arg0, f32*, 0x284);
			sp10    = M2C_FIELD(arg0, s32*, 0x288);
			temp_f1 = spC;
			spC     = temp_f1 + lbl_8_rodata_1AB8;
			if ((fn_800A34D0(arg0, &sp8, temp_f1) != 0)
			    && ((s32)M2C_FIELD(arg0, s32*, 0x2EC) == 0)) {
				M2C_FIELD(arg0, s32*, 0x2EC) = 1;
				temp_f1_2                    = M2C_FIELD(arg0, f32*, 0x1A4) - lbl_8_rodata_1ABC;
				M2C_FIELD(arg0, f32*, 0x1A4) = temp_f1_2;
				if (temp_f1_2 < lbl_8_rodata_1AC8) {
					M2C_FIELD(arg0, f32*, 0x1A4) = (f32)lbl_8_rodata_1AC8;
				}
				M2C_FIELD(arg0, s16*, 0x2E)  = (s16)M2C_FIELD(arg0, f32*, 0x1A4);
				M2C_FIELD(arg0, s32*, 0x230) = fn_800AB104(M2C_FIELD(arg0, s32*, 0x2F4));
				return;
			}
		case 2:
			return;
		case 3:
			M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) & 0xFFFFFDFF);
			break;
	}
}

void fn_8_ABCE4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 6;
			}
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x404D, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
			}
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x404C, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
				return;
			}
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
				M2C_FIELD(arg0, s32*, 0x150) = (s32)((f32)M2C_FIELD(arg0, s32*, 0x150) + 5632.0f);
				M2C_FIELD(arg0, f32*, 0x2B8)
				    = fn_800D7328(&lbl_8_rodata_1B08, M2C_FIELD(arg0, f32*, 0x2B8), 1.5f, 0.04f);
				M2C_FIELD(arg0, f32*, 0x2BC)
				    = fn_800D7328(&lbl_8_rodata_1B0C, M2C_FIELD(arg0, f32*, 0x2BC), 1.5f, 0.05f);
				M2C_FIELD(arg0, f32*, 0x2C0)
				    = fn_800D7328(&lbl_8_rodata_1B08, M2C_FIELD(arg0, f32*, 0x2C0), 1.5f, 0.04f);
			}
			break;
	}
}

void fn_8_ABE70(void* arg0, s32 arg1)
{
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f30;
	f32 temp_f31;

	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 6;
			}
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x404C, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
			}
			M2C_FIELD(arg0, s32*, 0x2E4) = 0;
			return;
		case 1:
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) != 0) {
				M2C_FIELD(arg0, s32*, 0x150) = (s32)((f32)M2C_FIELD(arg0, s32*, 0x150) + 5632.0f);
				M2C_FIELD(arg0, f32*, 0x2B8) = fn_800D7328(
				    &lbl_8_rodata_1B08, M2C_FIELD(arg0, f32*, 0x2B8), lbl_8_rodata_1AC8, 0.04f);
				M2C_FIELD(arg0, f32*, 0x2BC)
				    = fn_800D7328(&lbl_8_rodata_1B0C, M2C_FIELD(arg0, f32*, 0x2BC), 4.0f, 0.05f);
				M2C_FIELD(arg0, f32*, 0x2C0) = fn_800D7328(
				    &lbl_8_rodata_1B08, M2C_FIELD(arg0, f32*, 0x2C0), lbl_8_rodata_1AC8, 0.04f);
				if (((s32)M2C_FIELD(arg0, s32*, 0x2E4) == 0)
				    && (lbl_8_rodata_1AC8 == M2C_FIELD(arg0, f32*, 0x2B8))) {
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(0x404D, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
					}
					M2C_FIELD(arg0, s32*, 0x2E4) = 1;
					temp_f30                     = M2C_FIELD(arg0, f32*, 0x210);
					temp_f1   = temp_f30 * (lbl_8_rodata_1ACC * (f32)fn_801C28D8());
					temp_f31  = (lbl_8_rodata_1AC4 * temp_f1) - temp_f30;
					temp_f1_2 = (lbl_8_rodata_1AC4
					                * (temp_f30
					                    * (lbl_8_rodata_1ACC
					                        * (f32)fn_801C28D8(
					                            &lbl_8_rodata_1AC4, &lbl_8_rodata_1AD8, temp_f1))))
					    - temp_f30;
					M2C_FIELD(arg0, f32*, 0x140) = (f32)(temp_f31 + M2C_FIELD(arg0, f32*, 0x1C0));
					M2C_FIELD(arg0, f32*, 0x148) = (f32)(temp_f1_2 + M2C_FIELD(arg0, f32*, 0x1C8));
				}
			}
			return;
	}
}

void fn_8_AC10C(void* arg0, s32 arg1)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	s32 temp_r4;
	s32 var_r30;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
				M2C_FIELD(arg0, s32*, 0xD4) = 0;
			} else {
				M2C_FIELD(arg0, s32*, 0xD4) = 6;
			}
			M2C_FIELD(arg0, s32*, 0x274) = 0x28;
			M2C_FIELD(arg0, f32*, 0x1B8) = (f32)lbl_8_rodata_1AC4;
			return;
		case 1:
			temp_r4 = M2C_FIELD(arg0, s32*, 0x27C);
			if (temp_r4 != -1) {
				sp8     = M2C_FIELD(arg0, f32*, 0x140);
				spC     = M2C_FIELD(arg0, f32*, 0x144);
				sp10    = M2C_FIELD(arg0, f32*, 0x148);
				temp_r3 = *(void**)((u8*)&lbl_802AD090 + (temp_r4 * 4));
				if (temp_r3 != NULL) {
					sp8 -= M2C_FIELD(temp_r3, f32*, 0x18);
					spC -= M2C_FIELD(temp_r3, f32*, 0x1C);
					sp10 -= M2C_FIELD(temp_r3, f32*, 0x20);
				}
				spC = lbl_8_rodata_1AC8;
				fn_801990E0(&sp8, &sp8);
				M2C_FIELD(arg0, f32*, 0x158) = sp8;
				M2C_FIELD(arg0, f32*, 0x15C) = spC;
				M2C_FIELD(arg0, f32*, 0x160) = sp10;
			}
			var_r30 = 1;
			if ((s32)M2C_FIELD(arg0, s32*, 0x310) == 0) {

			} else {
				if ((fn_800A5AC0(arg0) < lbl_8_rodata_1AC4)
				    || ((s32)(M2C_FIELD(arg0, u16*, 0x106) & 4) != 0)) {
					fn_800A4668(arg0);
					var_r30 = 0;
				} else {
					fn_800A4A8C(arg0, M2C_FIELD(arg0, f32*, 0x358));
				}
				fn_800A5C6C(arg0, 0xF00);
				if (((s32)(M2C_FIELD(arg0, u16*, 0x106) & 2) != 0)
				    && (M2C_FIELD(arg0, f32*, 0x15C) < (1.5f * M2C_FIELD(arg0, f32*, 0x1A8)))) {
					M2C_FIELD(arg0, f32*, 0x15C) = (f32)lbl_8_rodata_1AC8;
				}
				if (fn_800A5888(arg0, &lbl_8_rodata_1AF0, -1.0f) != 0) {
					fn_800A5B50(arg0, 0xF00);
					var_r30 = 0;
				}
			}
			if (var_r30 == 0) {
				M2C_FIELD(arg0, s32*, 0x250) = 0x3B;
			}
			fn_80137FE8((u8*)arg0 + 0x274);
			if ((s32)M2C_FIELD(arg0, s32*, 0x274) < 0) {
				M2C_FIELD(arg0, s32*, 0x250) = 0x3B;
			}
			return;
	}
}

void fn_8_AC338(void* arg0, s32 arg1)
{
	if (arg1 != 0) {
		if (arg1 >= 0) {
		}
	} else if ((s32)M2C_FIELD(arg0, s32*, 0x350) == 0) {
		M2C_FIELD(arg0, s32*, 0x350) = 1;
		M2C_FIELD(arg0, s32*, 0xD4)  = 3;
		if ((u32)lbl_8042C388 != 0U) {
			fn_800B4A38(0x404E, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
		}
	} else {
		M2C_FIELD(arg0, s32*, 0x350) = 0;
		M2C_FIELD(arg0, s32*, 0xD4)  = 4;
		if ((u32)lbl_8042C388 != 0U) {
			fn_800B4A38(0x404F, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
		}
		if ((s32)M2C_FIELD(arg0, s32*, 0x2D4) > 0) {
			fn_8_A504(
			    (u8*)arg0 + 0x140, 0, &lbl_8_rodata_1AC4, lbl_8_rodata_1AD0, lbl_8_rodata_1AC4);
			M2C_FIELD(arg0, s32*, 0x2D4) = 0;
			M2C_FIELD(arg0, s32*, 0x2D8) = 0;
		}
	}
}

void fn_8_AC440(TObject* arg0, s32 arg1)
{
	M2C_UNK sp8;
	TObject* temp_r3_5;
	f32 temp_f1;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r29;
	s32 temp_r3_2;
	s32 temp_r4;
	s32 temp_r5;
	void* temp_r3;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_6;
	void* temp_r3_7;

	switch (arg1) { /* irregular */
		case 0:
			arg0->unk2F8 = 0;
			arg0->unk2E4 = 0;
			arg0->unk274 = 0x28;
			arg0->unk2D8 = 0;
			arg0->unk2D0 = -1;
			fn_80103214(&arg0->unk140, &arg0->unk2C4, &lbl_8_rodata_1B14, 1e8f);
			temp_f1      = arg0->unk2C8;
			arg0->unk2C8 = temp_f1 + 100.0f;
			arg0->unk2C8 = fn_800D8BC4(&arg0->unk2C4, &sp8, 1, temp_f1);
			if ((u32)arg0->unk2DC != 0U) {
				temp_r3      = fn_8019E8EC();
				arg0->unk338 = M2C_FIELD(temp_r3, f32*, 0x30);
				arg0->unk33C = M2C_FIELD(temp_r3, f32*, 0x34);
				arg0->unk340 = M2C_FIELD(temp_r3, f32*, 0x38);
			}
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x4049, &arg0->unk140, NULL, 1, 0, 0);
			}
			arg0->unk300 = lbl_8_rodata_1AC8;
			arg0->unk304 = lbl_8_rodata_1ABC;
			arg0->unk308 = lbl_8_rodata_1AC8;
			arg0->unk30C = 0;
			return;
		case 1:
			if (((s32)arg0->unk310 != 0) && (arg0->unk2C8 != -1000000.0f)) {
				if ((s32)arg0->unk2E4 == 0) {
					temp_r0      = arg0->unk274 - 1;
					arg0->unk274 = temp_r0;
					if (temp_r0 < 0) {
						arg0->unk274 = 0xA;
						arg0->unkD4  = 8;
						arg0->unk2F8 = 1;
						arg0->unk2E4 = 1;
						return;
					}
				}
				if ((s32)arg0->unkD0 == 9) {
					if ((s32)arg0->unk2D0 == -1) {
						temp_r3_2
						    = fn_80103324((u8*)arg0 + 0x2C4, &lbl_8_rodata_1AE0, lbl_8_rodata_1AE0);
						if (temp_r3_2 != -1) {
							arg0->unk2D0 = temp_r3_2;
							fn_800E1208(arg0->unk2D0, 0x17, 0);
						} else {
							arg0->unk2D0 = -1;
						}
					}
					if ((s32)arg0->unk2D0 != -1) {
						temp_r0_2    = arg0->unk274 - 1;
						arg0->unk274 = temp_r0_2;
						if (temp_r0_2 < 0) {
							temp_r4   = arg0->unk2D0 * 4;
							temp_r3_3 = *(void**)((u8*)&lbl_802AD070 + temp_r4);
							if ((temp_r3_3 != NULL)
							    && ((s32)
							            * (&lbl_80303D28
							                + ((s8)M2C_FIELD(temp_r3_3, u8*, 0x9BC) * 4))
							        != 0)) {
								temp_r3_4 = *(void**)((u8*)&lbl_802AD090 + temp_r4);
								if (temp_r3_4 != NULL) {
									arg0->unk32C = M2C_FIELD(temp_r3_4, f32*, 0x18);
									arg0->unk330 = M2C_FIELD(temp_r3_4, f32*, 0x1C);
									arg0->unk334 = M2C_FIELD(temp_r3_4, f32*, 0x20);
									temp_r3_5    = fn_80018A34(lbl_8042C148, 0x68);
									if (temp_r3_5 != NULL) {
										__ct__7TObjectFP7TObject(temp_r3_5, arg0);
										temp_r3_5->unk18 = &lbl_8_data_16900;
										temp_r3_5->unk0  = lbl_8_data_168FC;
										temp_r3_5->unk1E = 0x68;
										temp_r3_5->unk28 = arg0->unk32C;
										temp_r3_5->unk2C = arg0->unk330;
										temp_r3_5->unk30 = arg0->unk334;
										temp_r3_5->unk34 = arg0->unk338;
										temp_r3_5->unk38 = arg0->unk33C;
										temp_r3_5->unk3C = arg0->unk340;
										temp_r3_5->unk40 = arg0->unk344;
										temp_r3_5->unk44 = arg0->unk348;
										temp_r3_5->unk48 = arg0->unk34C;
										temp_r3_5->unk48 = lbl_8_rodata_1ABC;
										temp_r3_5->unk44 = lbl_8_rodata_1ABC;
										temp_r3_5->unk40 = lbl_8_rodata_1ABC;
										temp_r3_5->unk50 = lbl_8_rodata_1AC8;
										temp_r3_5->unk64 = 0;
										temp_r3_5->unk54 = temp_r3_5->unk28;
										temp_r3_5->unk58 = temp_r3_5->unk2C;
										temp_r3_5->unk5C = temp_r3_5->unk30;
										temp_r3_5->unk60 = lbl_8_rodata_1AC8;
										temp_r3_5->unk4C = NULL;
										if ((u32)lbl_8_bss_1A48 != 0U) {
											temp_r3_5->unk4C = fn_80150588();
										}
										temp_r3_6 = temp_r3_5->unk4C;
										if (temp_r3_6 != NULL) {
											temp_r29 = M2C_FIELD(temp_r3_6, s32*, 4);
											fn_8019EC30(temp_r29, &temp_r3_5->unk40, 0);
											fn_8019ED68(
											    temp_r29, &lbl_80239984, 2, temp_r3_5->unk60);
											fn_8019EB94(temp_r29, &temp_r3_5->unk54, 2);
										}
									}
								}
							}
							arg0->unk274 = 0xA;
						}
					}
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(0x404A, &arg0->unk140, arg0, 3, 0, 2);
					}
				}
				arg0->unk30C += 0x600;
				arg0->unk300
				    = fn_800D7328(&lbl_8_rodata_1B20, arg0->unk300, lbl_8_rodata_1ABC, 0.02f);
				arg0->unk304 = lbl_8_rodata_1ABC + (1.2f * fn_800D7B00(arg0->unk30C));
				arg0->unk308
				    = fn_800D7328(&lbl_8_rodata_1B20, arg0->unk308, lbl_8_rodata_1ABC, 0.02f);
				return;
			}
		case 2:
			return;
		case 3:
			arg0->unk2F8 = 0;
			temp_r0_3    = arg0->unk2D0;
			if (temp_r0_3 != -1) {
				temp_r3_7 = *(void**)((u8*)&lbl_802AD070 + (temp_r0_3 * 4));
				if (temp_r3_7 != NULL) {
					temp_r5 = *(&lbl_80303D28 + ((s8)M2C_FIELD(temp_r3_7, u8*, 0x9BC) * 4));
					if (temp_r5 != 0) {
						if (temp_r5 >= 0x14) {
							arg0->unk2D4 = 0x14;
							arg0->unk2D8 = arg0->unk2D4;
							fn_80066D20(&arg0->unk240, temp_r5 - 0x14);
							if ((u32)lbl_8042C388 != 0U) {
								fn_800B4A38(0x404B, &arg0->unk140, NULL, 1, 0, 0);
							}
						} else {
							arg0->unk2D4 = temp_r5;
							arg0->unk2D8 = arg0->unk2D4;
							fn_80066D20(&arg0->unk240, 0);
							if ((u32)lbl_8042C388 != 0U) {
								fn_800B4A38(0x404B, &arg0->unk140, NULL, 1, 0, 0);
							}
						}
					}
				}
				if ((s32)arg0->unk2D0 != -1) {
					fn_800E1208(0xF, 0);
					arg0->unk2D0 = -1;
				}
			}
			break;
	}
}

void fn_8_AC9D8(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2E4) = 0;
			M2C_FIELD(arg0, s32*, 0x2E8) = 0;
			M2C_FIELD(arg0, s32*, 0x274) = 0x28;
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x4046, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
				return;
			}
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x274);
			if (((s32)M2C_FIELD(arg0, s32*, 0x2E4) == 0)
			    && ((s32)M2C_FIELD(arg0, s32*, 0x274) < 0)) {
				M2C_FIELD(arg0, s32*, 0xD4)  = 1;
				M2C_FIELD(arg0, s32*, 0x2E4) = 1;
			}
			if (((s32)M2C_FIELD(arg0, s32*, 0x2E8) == 0)
			    && ((s32)M2C_FIELD(arg0, s32*, 0xD0) == 1)) {
				M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
				if (M2C_FIELD(arg0, f32*, 0xB8) == 24.0f) {
					fn_80130B40(M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A));
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(0x4047, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
					}
					M2C_FIELD(arg0, s32*, 0x2E8) = 1;
				}
			}
			break;
	}
}

void fn_8_ACB0C(void* arg0, s32 arg1)
{
	f32 sp40;
	f32 sp3C;
	f32 sp38;
	f32 sp34;
	f32 sp30;
	u8 sp2D;
	s8 sp2C;
	s32 sp28;
	s32 sp24;
	s32 sp20;
	s32 sp1C;
	s32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2E4) = 0;
			M2C_FIELD(arg0, s32*, 0x2E8) = 0;
			M2C_FIELD(arg0, s32*, 0x274) = 0x28;
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x4043, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
				return;
			}
		case 2:
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x274);
			if (((s32)M2C_FIELD(arg0, s32*, 0x2E4) == 0)
			    && ((s32)M2C_FIELD(arg0, s32*, 0x274) < 0)) {
				M2C_FIELD(arg0, s32*, 0xD4)  = 2;
				M2C_FIELD(arg0, s32*, 0x2E4) = 1;
				if ((void*)M2C_FIELD(arg0, void**, 0x324) == NULL) {
					sp20 = M2C_FIELD(&lbl_8_rodata_1A54, s32*, 0);
					sp24 = M2C_FIELD(&lbl_8_rodata_1A54, s32*, 4);
					sp28 = M2C_FIELD(&lbl_8_rodata_1A54, s32*, 8);
					sp14 = M2C_FIELD(&lbl_8_rodata_1A60, f32*, 0);
					sp18 = M2C_FIELD(&lbl_8_rodata_1A60, s32*, 4);
					sp1C = M2C_FIELD(&lbl_8_rodata_1A60, s32*, 8);
					fn_8019941C(&sp14, &sp14, 1,
					    fn_8019E8EC(M2C_FIELD(arg0, s32*, 0x2E0), &lbl_8_rodata_1A60));
					M2C_FIELD(arg0, void**, 0x324) = fn_8006298C(0x27, &sp14, &sp20);
					fn_8005FD20(M2C_FIELD(arg0, void**, 0x324));
				}
			}
			if (((s32)M2C_FIELD(arg0, s32*, 0x2E8) == 0)
			    && ((s32)M2C_FIELD(arg0, s32*, 0xD0) == 2)) {
				M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
				if (M2C_FIELD(arg0, f32*, 0xB8) == 28.0f) {
					sp2C = 0;
					sp2D = 0;
					sp38 = lbl_8_rodata_1AC8;
					sp34 = lbl_8_rodata_1AC8;
					sp30 = lbl_8_rodata_1AC8;
					sp3C = lbl_8_rodata_1AC8;
					sp2C = 3;
					sp40 = lbl_8_rodata_1AC8;
					sp2D = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), u8*, 0x2A);
					sp40 = 100.0f;
					sp30 = M2C_FIELD(arg0, f32*, 0x140);
					sp34 = M2C_FIELD(arg0, f32*, 0x144);
					sp38 = M2C_FIELD(arg0, f32*, 0x148);
					sp3C = M2C_FIELD(arg0, f32*, 0x214);
					fn_80100CFC(&sp2C);
					if ((u32)lbl_8042C388 != 0U) {
						fn_800B4A38(0x4044, (u8*)arg0 + 0x140, NULL, 1, 0, 0);
					}
					M2C_FIELD(arg0, s32*, 0x2E8) = 1;
				}
			}
			if ((void*)M2C_FIELD(arg0, void**, 0x324) != NULL) {
				sp8  = M2C_FIELD(&lbl_8_rodata_1A6C, f32*, 0);
				spC  = M2C_FIELD(&lbl_8_rodata_1A6C, f32*, 4);
				sp10 = M2C_FIELD(&lbl_8_rodata_1A6C, f32*, 8);
				fn_8019941C(
				    &sp8, &sp8, 1, fn_8019E8EC(M2C_FIELD(arg0, s32*, 0x2E0), &lbl_8_rodata_1A6C));
				temp_r3                        = M2C_FIELD(arg0, void**, 0x324);
				M2C_FIELD(temp_r3, f32*, 0x80) = sp8;
				M2C_FIELD(temp_r3, f32*, 0x84) = spC;
				M2C_FIELD(temp_r3, f32*, 0x88) = sp10;
				return;
			}
			break;
		case 3:
			if ((void*)M2C_FIELD(arg0, void**, 0x324) != NULL) {
				fn_8005FD8C(-1);
				M2C_FIELD(arg0, void**, 0x324) = NULL;
			}
			break;
	}
}

void fn_8_ACDC0(void) { }

void fn_8_ACDC4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(M2C_FIELD(arg0, void**, 0x18), M2C_UNK(**)(), 0x3C)();
			return;
		case 1:
			M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			return;
	}
}
}
