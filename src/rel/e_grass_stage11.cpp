#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(u32)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

typedef struct TObject {
	/* 0x000 */ M2C_UNK* unk0;   /* inferred */
	/* 0x004 */ u16 unk4;        /* inferred */
	/* 0x006 */ char pad6[0x12]; /* maybe part of unk4[0xA]? */
	/* 0x018 */ M2C_UNK* unk18;  /* inferred */
	/* 0x01C */ char pad1C[2];
	/* 0x01E */ s16 unk1E;     /* inferred */
	/* 0x020 */ char pad20[8]; /* maybe part of unk1E[5]? */
	/* 0x028 */ M2C_UNK unk28; /* inferred */
	/* 0x028 */ char pad28[4];
	/* 0x02C */ void* unk2C;   /* inferred */
	/* 0x030 */ M2C_UNK unk30; /* inferred */
	/* 0x030 */ char pad30[0x10];
	/* 0x040 */ void* unk40;      /* inferred */
	/* 0x044 */ char pad44[0x4C]; /* maybe part of unk40[0x14]? */
	/* 0x090 */ f32 unk90;        /* inferred */
	/* 0x094 */ f32 unk94;        /* inferred */
	/* 0x098 */ f32 unk98;        /* inferred */
	/* 0x09C */ s32 unk9C;        /* inferred */
	/* 0x0A0 */ s32 unkA0;        /* inferred */
	/* 0x0A4 */ s32 unkA4;        /* inferred */
	/* 0x0A8 */ char padA8[4];
	/* 0x0AC */ f32 unkAC;         /* inferred */
	/* 0x0B0 */ f32 unkB0;         /* inferred */
	/* 0x0B4 */ f32 unkB4;         /* inferred */
	/* 0x0B8 */ f32 unkB8;         /* inferred */
	/* 0x0BC */ f32 unkBC;         /* inferred */
	/* 0x0C0 */ f32 unkC0;         /* inferred */
	/* 0x0C4 */ s32 unkC4;         /* inferred */
	/* 0x0C8 */ s32 unkC8;         /* inferred */
	/* 0x0CC */ s32 unkCC;         /* inferred */
	/* 0x0D0 */ f32 unkD0;         /* inferred */
	/* 0x0D4 */ s32 unkD4;         /* inferred */
	/* 0x0D8 */ s32 unkD8;         /* inferred */
	/* 0x0DC */ void* unkDC;       /* inferred */
	/* 0x0E0 */ s32 unkE0;         /* inferred */
	/* 0x0E4 */ s32 unkE4;         /* inferred */
	/* 0x0E8 */ s32 unkE8;         /* inferred */
	/* 0x0EC */ s32 unkEC;         /* inferred */
	/* 0x0F0 */ void* unkF0;       /* inferred */
	/* 0x0F4 */ s32 unkF4;         /* inferred */
	/* 0x0F8 */ s32 unkF8;         /* inferred */
	/* 0x0FC */ void* unkFC;       /* inferred */
	/* 0x100 */ char pad100[0x10]; /* maybe part of unkFC[5]? */
	/* 0x110 */ void* unk110;      /* inferred */
} TObject;                         /* size >= 0x114 */

struct _struct_lbl_8_data_18938_0x14 {
	/* 0x00 */ u32 unk0;        /* inferred */
	/* 0x04 */ char pad4[0x10]; /* maybe part of unk0[5]? */
}; /* size = 0x14 */

struct _struct_lbl_8_data_18960_0xC {
	/* 0x0 */ u32 unk0;     /* inferred */
	/* 0x4 */ char pad4[8]; /* maybe part of unk0[3]? */
}; /* size = 0xC */

struct _struct_lbl_8_data_18978_0x14 {
	/* 0x00 */ u32 unk0;        /* inferred */
	/* 0x04 */ char pad4[0x10]; /* maybe part of unk0[5]? */
}; /* size = 0x14 */

extern "C" {

void* __ct__7TObjectFP7TObject(...);                               /* extern */
void* __dt__7TObjectFv(...);                                       /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                             /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                             /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                                /* extern */
u32 fn_80018A34(s32, M2C_UNK);                                     /* extern */
M2C_UNK fn_8003BC38(M2C_UNK*);                                     /* extern */
M2C_UNK fn_8003C200(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK);         /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                                     /* extern */
s32 fn_8005B8BC(void*);                                            /* extern */
s32 fn_8005B8D8(void*);                                            /* extern */
s32 fn_8005B9F0(void*);                                            /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                                     /* extern */
M2C_UNK fn_8005D5C8(void*, s32);                                   /* extern */
M2C_UNK fn_800B4A38(M2C_UNK, f32*, M2C_UNK, M2C_UNK, s8, M2C_UNK); /* extern */
u32 fn_800BB0D4(s32, s32, M2C_UNK*);                               /* extern */
u32 fn_800BB92C(s32, s32, M2C_UNK*);                               /* extern */
s32 fn_800BC6CC(s32, M2C_UNK*);                                    /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                                /* extern */
f32 fn_800D7AE4(s32);                                              /* extern */
f32 fn_800D7B00(s32);                                              /* extern */
M2C_UNK fn_8013F3A4(void*);                                        /* extern */
void* fn_8013F484(s32);                                            /* extern */
M2C_UNK fn_8013FC30(void*);                                        /* extern */
M2C_UNK fn_8014FFBC(void*, void* (*)(void*, s32), void*);          /* extern */
void* fn_80150588(s32, s32);                                       /* extern */
M2C_UNK fn_80150958(void*);                                        /* extern */
M2C_UNK fn_8015BB08(s32, void*);                                   /* extern */
M2C_UNK fn_8015BBF8(s32);                                          /* extern */
M2C_UNK fn_80195790(s32, M2C_UNK*, M2C_UNK, f32, f32);             /* extern */
M2C_UNK fn_8019E880(s32);                                          /* extern */
M2C_UNK fn_8019EB10(s32, s32 (*)(s32, void**), void**);            /* extern */
M2C_UNK fn_8019EB94(s32, f32*, M2C_UNK);                           /* extern */
M2C_UNK fn_8019EC30(s32, f32*, M2C_UNK);                           /* extern */
M2C_UNK fn_801A4C84();                                             /* extern */
M2C_UNK fn_8020C2D8(u32);                                          /* extern */
M2C_UNK fn_8020C72C(void**, s32, s32);                             /* extern */
M2C_UNK fn_8020CC18(void**, M2C_UNK*, f32);                        /* extern */
M2C_UNK fn_8020D02C(void**, M2C_UNK*, f32);                        /* extern */
M2C_UNK fn_80226440(void*, s32);                                   /* extern */
u32 fn_80226468(s32);                                              /* extern */
M2C_UNK fn_8_C5C1C(s32);                                           /* extern */
void fn_8_C606C(TObject* arg0, ...);                               /* static */
TObject* fn_8_C6CAC(TObject* arg0, TObject* arg1);                 /* static */
void* fn_8_C7014(void* arg0, s32 arg1);                            /* static */
s32 fn_8_C70C4(s32 arg0, void** arg1);                             /* static */
void grassObjectCreate();                                          /* static */
void grassObjectLoad(M2C_UNK arg_sp0);                             /* static */
void grassObjectUnload(M2C_UNK arg_sp0);                           /* static */
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_802FF5A0;
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern M2C_UNK* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u32 lbl_8042C388;
extern M2C_UNK lbl_8_data_186B0;
extern M2C_UNK lbl_8_data_186C4;
extern M2C_UNK lbl_8_data_186D8;
extern M2C_UNK lbl_8_data_186EC;
extern M2C_UNK lbl_8_data_18700;
extern M2C_UNK lbl_8_data_18714;
extern M2C_UNK lbl_8_data_18728;
extern M2C_UNK lbl_8_data_1873C;
extern M2C_UNK lbl_8_data_18750;
extern M2C_UNK lbl_8_data_18764;
static M2C_UNK* lbl_8_data_18778[0xA] = {
	&lbl_8_data_186B0,
	&lbl_8_data_186C4,
	&lbl_8_data_186D8,
	&lbl_8_data_186EC,
	&lbl_8_data_18700,
	&lbl_8_data_18714,
	&lbl_8_data_18728,
	&lbl_8_data_1873C,
	&lbl_8_data_18750,
	&lbl_8_data_18764,
};
static M2C_UNK lbl_8_data_187A0; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_187B4; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_187C8; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_187DC; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_187F0; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18804; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18818; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1882C; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18840; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18854; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18868[0xA] = {
	"s11_on_grassa1l.dff",
	"s11_on_grassa2l.dff",
	"s11_on_grassa3l.dff",
	"s11_on_grassa4l.dff",
	"s11_on_grassa5l.dff",
	"s11_on_grassa1d.dff",
	"s11_on_grassa2d.dff",
	"s11_on_grassa3d.dff",
	"s11_on_grassa4d.dff",
	"s11_on_grassa5d.dff",
};
static M2C_UNK lbl_8_data_18890;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000188A5_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_188A8;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000188BD_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_188C0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000188D5_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_188D8;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000188ED_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_188F0;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018905_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18908;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001891D_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18920[6] = {
	"s11_pnw_grassa1l.dff",
	"s11_pnw_grassa2l.dff",
	"s11_pnw_grassa3l.dff",
	"s11_pnw_grassa1d.dff",
	"s11_pnw_grassa2d.dff",
	"s11_pnw_grassa3d.dff",
};
static struct _struct_lbl_8_data_18938_0x14 lbl_8_data_18938[2] = { { 0U }, { 0U } };
static struct _struct_lbl_8_data_18960_0xC lbl_8_data_18960[2]  = { { 0U }, { 0U } };
static struct _struct_lbl_8_data_18978_0x14 lbl_8_data_18978[2] = { { 0U }, { 0U } };
static M2C_UNK lbl_8_data_189A0;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000189B2_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_189B4;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000189C3_data;  /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_189C4;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000189D3_data;  /* unable to generate initializer: unknown type */
static M2C_UNK grassObjectFieldNames; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_189E0;      /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000189F1_data;  /* unable to generate initializer: unknown type */
static const char* lbl_8_data_189F4[2] = { "type      : light", "type      : dark" };
static M2C_UNK lbl_8_data_189FC;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018A0D_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18A10[2] = { "direction : up", "direction : down" };
static M2C_UNK lbl_8_data_18A18;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18A48;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018A52_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18A54 = "TObjGrass";
static M2C_UNK lbl_8_data_18A58;       /* unable to generate initializer: unknown type */
static M2C_UNK grassObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018AA1_data;   /* unable to generate initializer: unknown type */
static M2C_UNK grassObjectFieldTypes;  /* unable to generate initializer: unknown type */
static u8 lbl_8_bss_1CA8;
static M2C_UNK gap_05_00001CA9_bss;
static M2C_UNK grassObjectEntry;
static M2C_UNK lbl_8_bss_1CD8;
static M2C_UNK lbl_8_bss_1CDC;
static M2C_UNK lbl_8_bss_1CE0;
static M2C_UNK lbl_8_bss_1CE4;
static M2C_UNK lbl_8_rodata_1F60;
static M2C_UNK lbl_8_rodata_1F70; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1F78; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1F84; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1F90; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1F94; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1F98; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1F9C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FA0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FA8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FB0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FB8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FC4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FC8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FCC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FD0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FD4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FD8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FF0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FF4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1FF8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_2000; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_2004; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_2008; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_200C; /* unable to generate initializer: unknown type; const */

void fn_8_C5FA4(s32 arg0)
{
	fn_8_C5C1C(arg0 - 0x28);
}

void fn_8_C5FAC(void* arg0, M2C_UNK arg_sp0)
{
	s32 var_r28;
	s32 var_r28_2;
	void* var_r29;
	void* var_r29_2;

	var_r28 = 0;
	var_r29 = arg0;
	do {
		if ((void*)M2C_FIELD(var_r29, void**, 0xDC) != NULL) {
			fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
			fn_80150958(M2C_FIELD(var_r29, void**, 0xDC));
			M2C_FIELD(var_r29, void**, 0xDC) = NULL;
		}
		var_r29 = (u8*)var_r29 + 4;
		var_r28 += 1;
	} while (var_r28 < 5);
	var_r28_2 = 0;
	var_r29_2 = arg0;
	do {
		if ((void*)M2C_FIELD(var_r29_2, void**, 0xF0) != NULL) {
			fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284));
			fn_80150958(M2C_FIELD(var_r29_2, void**, 0xF0));
			M2C_FIELD(var_r29_2, void**, 0xF0) = NULL;
		}
		var_r29_2 = (u8*)var_r29_2 + 4;
		var_r28_2 += 1;
	} while (var_r28_2 < 3);
}

void fn_8_C606C(TObject* arg0, ...)
{
	void* spC;
	void* sp8;
	TObject* var_r30_2;
	TObject* var_r31;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r0_4;
	s32 var_r29;
	s32 var_r29_2;
	s32 var_r30;
	s32 var_r31_2;
	void* temp_r27;
	void* temp_r27_2;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;

	var_r29 = 0;
	var_r31 = arg0;
	var_r30 = 0;
	do {
		if ((void*)var_r31->unkDC == NULL) {
			temp_r0        = arg0->unkD8;
			var_r31->unkDC = fn_80150588(
			    M2C_FIELD(&lbl_8_data_18938[temp_r0] + var_r30, s32*, 0), temp_r0 * 0x14);
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C), var_r31->unkDC);
			fn_8005D5C8(var_r31->unkDC,
			    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
			        + 4);
			temp_r27 = var_r31->unkDC;
			spC      = NULL;
			temp_r3  = fn_8013F484(M2C_FIELD(temp_r27, s32*, 4));
			spC      = temp_r3;
			if (temp_r3 == NULL) {
				fn_8019EB10(M2C_FIELD(temp_r27, s32*, 4), fn_8_C70C4, &spC);
			}
			var_r31->unkFC = spC;
			fn_8014FFBC(var_r31->unkDC, fn_8_C7014, var_r31->unkFC);
			temp_r3_2                     = var_r31->unkFC;
			M2C_FIELD(temp_r3_2, s32*, 0) = (s32)(M2C_FIELD(temp_r3_2, s32*, 0) | 0x3000);
			temp_r0_2                     = arg0->unkD8;
			fn_8020C72C(M2C_FIELD(var_r31->unkFC, void***, 0x20),
			    M2C_FIELD(&lbl_8_data_18978[temp_r0_2] + var_r30, s32*, 0), temp_r0_2 * 0x14);
			fn_8013F3A4(var_r31->unkFC);
			fn_8013FC30(var_r31->unkFC);
			fn_8020D02C(M2C_FIELD(var_r31->unkFC, void***, 0x20), &lbl_8_rodata_1F60, 0.0f);
			fn_8020CC18(M2C_FIELD(var_r31->unkFC, void***, 0x20), &lbl_8_rodata_1F60, 0.0f);
		}
		var_r31 = (TObject*)((u8*)var_r31 + 4);
		var_r30 += 4;
		var_r29 += 1;
	} while (var_r29 < 5);
	var_r29_2 = 0;
	var_r30_2 = arg0;
	var_r31_2 = 0;
	do {
		if ((void*)var_r30_2->unkF0 == NULL) {
			temp_r0_3        = arg0->unkD8;
			var_r30_2->unkF0 = fn_80150588(
			    M2C_FIELD(&lbl_8_data_18960[temp_r0_3] + var_r31_2, s32*, 0), temp_r0_3 * 0xC);
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284), var_r30_2->unkF0);
			fn_8005D5C8(var_r30_2->unkF0,
			    ((u32)(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x18) & 0x1C0000) >> 0x12U)
			        + 4);
			temp_r27_2 = var_r30_2->unkF0;
			sp8        = NULL;
			temp_r3_3  = fn_8013F484(M2C_FIELD(temp_r27_2, s32*, 4));
			sp8        = temp_r3_3;
			if (temp_r3_3 == NULL) {
				fn_8019EB10(M2C_FIELD(temp_r27_2, s32*, 4), fn_8_C70C4, &sp8);
			}
			var_r30_2->unk110 = sp8;
			fn_8014FFBC(var_r30_2->unkF0, fn_8_C7014, var_r30_2->unk110);
			temp_r3_4                     = var_r30_2->unk110;
			M2C_FIELD(temp_r3_4, s32*, 0) = (s32)(M2C_FIELD(temp_r3_4, s32*, 0) | 0x3000);
			temp_r0_4                     = arg0->unkD8;
			fn_8020C72C(M2C_FIELD(var_r30_2->unk110, void***, 0x20),
			    M2C_FIELD(&lbl_8_data_18978[temp_r0_4] + var_r31_2, s32*, 0), temp_r0_4 * 0x14);
			fn_8013F3A4(var_r30_2->unk110);
			fn_8013FC30(var_r30_2->unk110);
			fn_8020D02C(M2C_FIELD(var_r30_2->unk110, void***, 0x20), &lbl_8_rodata_1F60, 0.0f);
			fn_8020CC18(M2C_FIELD(var_r30_2->unk110, void***, 0x20), &lbl_8_rodata_1F60, 0.0f);
		}
		var_r30_2 = (TObject*)((u8*)var_r30_2 + 4);
		var_r31_2 += 4;
		var_r29_2 += 1;
	} while (var_r29_2 < 3);
}

void fn_8_C6324(void* arg0)
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
	M2C_FIELD(arg0, s32*, 0xD4) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 1);
	M2C_FIELD(arg0, s32*, 0xD8) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 0);
	M2C_FIELD(arg0, f32*, 0xD0) = (f32)(1.0f + M2C_FIELD(temp_r5, f32*, 4));
}

void fn_8_C63A0(TObject* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	TObject* var_r27;
	TObject* var_r27_2;
	TObject* var_r27_3;
	TObject* var_r27_4;
	TObject* var_r27_5;
	TObject* var_r27_6;
	f32 temp_f0;
	f32 temp_f28;
	f32 temp_f30;
	f32 temp_f30_2;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r28;
	s32 temp_r28_2;
	s32 temp_r5;
	s32 var_r28;
	s32 var_r28_2;
	s32 var_r29;
	s32 var_r29_2;
	s32 var_r31;
	s32 var_r31_2;
	void** temp_r3;
	void** temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r4;

	if ((fn_8005B9F0((u8*)arg0 + 0x28) != 0) || (fn_8005B8BC((u8*)arg0 + 0x28) != 0)) {
		arg0->unk4 |= 1;
		return;
	}
	var_r31 = 0;
	var_r27 = arg0;
	do {
		temp_r3  = M2C_FIELD(var_r27->unkFC, void***, 0x20);
		temp_f31 = 60.0f * M2C_FIELD(*temp_r3, f32*, 0xC);
		temp_r0  = M2C_FIELD(lbl_8042C180, s32*, 0x30);
		fn_8020D02C(temp_r3, lbl_8042C180,
		    ((f32)temp_r0 - (temp_f31 * (f32)(s32)((f32)temp_r0 / temp_f31))) / 60.0f);
		fn_8013FC30(var_r27->unkFC);
		var_r27 = (TObject*)((u8*)var_r27 + 4);
		var_r31 += 1;
	} while (var_r31 < 5);
	var_r31_2 = 0;
	var_r27_2 = arg0;
	do {
		temp_r3_2  = M2C_FIELD(var_r27_2->unk110, void***, 0x20);
		temp_f31_2 = 60.0f * M2C_FIELD(*temp_r3_2, f32*, 0xC);
		temp_r0_2  = M2C_FIELD(lbl_8042C180, s32*, 0x30);
		temp_f28   = (f32)temp_r0_2 - (temp_f31_2 * (f32)(s32)((f32)temp_r0_2 / temp_f31_2));
		fn_8020D02C(temp_r3_2, lbl_8042C180, temp_f28 / 60.0f);
		fn_8013FC30(var_r27_2->unk110);
		var_r27_2 = (TObject*)((u8*)var_r27_2 + 4);
		var_r31_2 += 1;
	} while (var_r31_2 < 3);
	if (fn_8005B8D8((u8*)arg0 + 0x28) != 0) {
		temp_r5     = arg0->unkD8;
		temp_r3_3   = M2C_FIELD(arg0, void**, 0x28);
		temp_r4     = M2C_FIELD(temp_r3_3, void**, 0x2C);
		arg0->unkB8 = M2C_FIELD(temp_r3_3, f32*, 0);
		arg0->unkBC = M2C_FIELD(temp_r3_3, f32*, 4);
		arg0->unkC0 = M2C_FIELD(temp_r3_3, f32*, 8);
		temp_r3_4   = M2C_FIELD(arg0, void**, 0x28);
		arg0->unkC4 = M2C_FIELD(temp_r3_4, s32*, 0xC);
		arg0->unkC8 = M2C_FIELD(temp_r3_4, s32*, 0x10);
		arg0->unkCC = M2C_FIELD(temp_r3_4, s32*, 0x14);
		arg0->unkCC = 0;
		arg0->unkC4 = 0;
		arg0->unkD4 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 1);
		arg0->unkD8 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0);
		arg0->unkD0 = 1.0f + M2C_FIELD(temp_r4, f32*, 4);
		if ((s32)arg0->unkD8 != temp_r5) {
			var_r28   = 0;
			var_r27_3 = arg0;
			do {
				if ((void*)var_r27_3->unkDC != NULL) {
					fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
					fn_80150958(var_r27_3->unkDC);
					var_r27_3->unkDC = NULL;
				}
				var_r27_3 = (TObject*)((u8*)var_r27_3 + 4);
				var_r28 += 1;
			} while (var_r28 < 5);
			var_r28_2 = 0;
			var_r27_4 = arg0;
			do {
				if ((void*)var_r27_4->unkF0 != NULL) {
					fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284));
					fn_80150958(var_r27_4->unkF0);
					var_r27_4->unkF0 = NULL;
				}
				var_r27_4 = (TObject*)((u8*)var_r27_4 + 4);
				var_r28_2 += 1;
			} while (var_r28_2 < 3);
			fn_8_C606C(arg0);
		}
		temp_f0   = arg0->unkD0;
		sp10      = temp_f0;
		spC       = temp_f0;
		sp8       = temp_f0;
		var_r29   = 0;
		var_r27_5 = arg0;
		do {
			temp_r28 = M2C_FIELD(var_r27_5->unkDC, s32*, 4);
			fn_8019EB94(temp_r28, &arg0->unkB8, 0);
			temp_f30 = fn_800D7B00(arg0->unkC8);
			fn_80195790(
			    temp_r28 + 0x10, &lbl_80239984, 1, 1.0f - fn_800D7AE4(arg0->unkC8), temp_f30);
			fn_8019E880(temp_r28);
			if ((s32)arg0->unkD4 == 1) {
				temp_f30_2 = fn_800D7B00(0x8000);
				fn_80195790(
				    temp_r28 + 0x10, &lbl_80239990, 1, 1.0f - fn_800D7AE4(0x8000), temp_f30_2);
				fn_8019E880(temp_r28);
			}
			fn_8019EC30(temp_r28, &sp8, 1);
			var_r27_5 = (TObject*)((u8*)var_r27_5 + 4);
			var_r29 += 1;
		} while (var_r29 < 5);
		var_r29_2 = 0;
		var_r27_6 = arg0;
		do {
			temp_r28_2 = M2C_FIELD(var_r27_6->unkF0, s32*, 4);
			fn_8019EB94(temp_r28_2, &arg0->unkB8, 0);
			temp_f31_3 = fn_800D7B00(arg0->unkC8);
			fn_80195790(
			    temp_r28_2 + 0x10, &lbl_80239984, 1, 1.0f - fn_800D7AE4(arg0->unkC8), temp_f31_3);
			fn_8019E880(temp_r28_2);
			if ((s32)arg0->unkD4 == 1) {
				temp_f31_4 = fn_800D7B00(0x8000);
				fn_80195790(
				    temp_r28_2 + 0x10, &lbl_80239990, 1, 1.0f - fn_800D7AE4(0x8000), temp_f31_4);
				fn_8019E880(temp_r28_2);
			}
			fn_8019EC30(temp_r28_2, &sp8, 1);
			var_r27_6 = (TObject*)((u8*)var_r27_6 + 4);
			var_r29_2 += 1;
		} while (var_r29_2 < 3);
		return;
	}
	if (temp_f28 < temp_f31_2) {
		M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
		if ((temp_f31_2 == (1.0f + temp_f28)) && ((u32)lbl_8042C388 != 0U)) {
			fn_800B4A38(0x5A14, &arg0->unkB8, 0, 1, (s8)lbl_8_bss_1CA8, 0);
		}
	}
	arg0->unkAC = arg0->unk90;
	arg0->unkB0 = arg0->unk94;
	arg0->unkB4 = arg0->unk98;
	arg0->unk90 = arg0->unkB8;
	arg0->unk94 = arg0->unkBC;
	arg0->unk98 = arg0->unkC0;
	arg0->unk9C = arg0->unkC4;
	arg0->unkA0 = arg0->unkC8;
	arg0->unkA4 = arg0->unkCC;
	fn_8003BC38(&arg0->unk30);
}

void fn_8_C6964(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f30;
	f32 temp_f30_2;
	f32 temp_f31;
	f32 temp_f31_2;
	s32 temp_r27;
	s32 temp_r28;
	s32 var_r27;
	s32 var_r28;
	void* var_r29;
	void* var_r29_2;

	temp_f0 = M2C_FIELD(arg0, f32*, 0xD0);
	sp10    = temp_f0;
	spC     = temp_f0;
	sp8     = temp_f0;
	var_r28 = 0;
	var_r29 = arg0;
	do {
		temp_r27 = M2C_FIELD(M2C_FIELD(var_r29, void**, 0xDC), s32*, 4);
		fn_8019EB94(temp_r27, (f32*)((u8*)arg0 + 0xB8), 0);
		temp_f30 = fn_800D7B00(M2C_FIELD(arg0, s32*, 0xC8));
		fn_80195790(temp_r27 + 0x10, &lbl_80239984, 1,
		    1.0f - fn_800D7AE4(M2C_FIELD(arg0, s32*, 0xC8)), temp_f30);
		fn_8019E880(temp_r27);
		if ((s32)M2C_FIELD(arg0, s32*, 0xD4) == 1) {
			temp_f30_2 = fn_800D7B00(0x8000);
			fn_80195790(temp_r27 + 0x10, &lbl_80239990, 1, 1.0f - fn_800D7AE4(0x8000), temp_f30_2);
			fn_8019E880(temp_r27);
		}
		fn_8019EC30(temp_r27, &sp8, 1);
		var_r29 = (u8*)var_r29 + 4;
		var_r28 += 1;
	} while (var_r28 < 5);
	var_r27   = 0;
	var_r29_2 = arg0;
	do {
		temp_r28 = M2C_FIELD(M2C_FIELD(var_r29_2, void**, 0xF0), s32*, 4);
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
		var_r29_2 = (u8*)var_r29_2 + 4;
		var_r27 += 1;
	} while (var_r27 < 3);
}

TObject* fn_8_C6B84(TObject* arg0, s16 arg1, M2C_UNK arg_sp0)
{
	TObject* var_r26;
	TObject* var_r26_2;
	s32 var_r27;
	s32 var_r27_2;

	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_18A58;
		arg0->unk2C = &lbl_8_data_18A58 + 0x2C;
		var_r27     = 0;
		var_r26     = arg0;
		do {
			if ((void*)var_r26->unkDC != NULL) {
				fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x725C));
				fn_80150958(var_r26->unkDC);
				var_r26->unkDC = NULL;
			}
			var_r26 = (TObject*)((u8*)var_r26 + 4);
			var_r27 += 1;
		} while (var_r27 < 5);
		var_r27_2 = 0;
		var_r26_2 = arg0;
		do {
			if ((void*)var_r26_2->unkF0 != NULL) {
				fn_8015BBF8(M2C_FIELD(lbl_8042C1D0, s32*, 0x7284));
				fn_80150958(var_r26_2->unkF0);
				var_r26_2->unkF0 = NULL;
			}
			var_r26_2 = (TObject*)((u8*)var_r26_2 + 4);
			var_r27_2 += 1;
		} while (var_r27_2 < 3);
		dtor_8003C52C((u8*)arg0 + 0x30, 0);
		dtor_8005BD3C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_C6CAC(TObject* arg0, TObject* arg1)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f30;
	f32 temp_f30_2;
	f32 temp_f31;
	f32 temp_f31_2;
	s32 temp_r28;
	s32 temp_r29;
	s32 var_r27;
	s32 var_r27_2;
	s32 var_r28;
	s32 var_r29;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r5;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	fn_8003C618(&arg0->unk30);
	arg0->unk18 = &lbl_8_data_18A58;
	arg0->unk2C = &lbl_8_data_18A58 + 0x2C;
	arg0->unk0  = (M2C_UNK*)lbl_8_data_18A54;
	arg0->unk1E = 0x11C;
	temp_r3     = M2C_FIELD(arg0, void**, 0x28);
	temp_r5     = M2C_FIELD(temp_r3, void**, 0x2C);
	arg0->unkB8 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unkBC = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unkC0 = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2   = M2C_FIELD(arg0, void**, 0x28);
	arg0->unkC4 = M2C_FIELD(temp_r3_2, s32*, 0xC);
	arg0->unkC8 = M2C_FIELD(temp_r3_2, s32*, 0x10);
	arg0->unkCC = M2C_FIELD(temp_r3_2, s32*, 0x14);
	arg0->unkCC = 0;
	arg0->unkC4 = 0;
	arg0->unkD4 = (s32)(s8)M2C_FIELD(temp_r5, u8*, 1);
	arg0->unkD8 = (s32)(s8)M2C_FIELD(temp_r5, u8*, 0);
	arg0->unkD0 = 1.0f + M2C_FIELD(temp_r5, f32*, 4);
	arg0->unkDC = NULL;
	arg0->unkE0 = 0;
	arg0->unkE4 = 0;
	arg0->unkE8 = 0;
	arg0->unkEC = 0;
	arg0->unkF0 = NULL;
	arg0->unkF4 = 0;
	arg0->unkF8 = 0;
	fn_8_C606C(arg0, 0, temp_r5, 1.0f);
	temp_f0 = arg0->unkD0;
	sp10    = temp_f0;
	spC     = temp_f0;
	sp8     = temp_f0;
	var_r29 = 0;
	var_r27 = 0;
	do {
		temp_r28 = M2C_FIELD(M2C_FIELD(arg0, void**, var_r27 + 0xDC), s32*, 4);
		fn_8019EB94(temp_r28, &arg0->unkB8, 0);
		temp_f30 = fn_800D7B00(arg0->unkC8);
		fn_80195790(temp_r28 + 0x10, &lbl_80239984, 1, 1.0f - fn_800D7AE4(arg0->unkC8), temp_f30);
		fn_8019E880(temp_r28);
		if ((s32)arg0->unkD4 == 1) {
			temp_f30_2 = fn_800D7B00(0x8000);
			fn_80195790(temp_r28 + 0x10, &lbl_80239990, 1, 1.0f - fn_800D7AE4(0x8000), temp_f30_2);
			fn_8019E880(temp_r28);
		}
		fn_8019EC30(temp_r28, &sp8, 1);
		var_r27 += 4;
		var_r29 += 1;
	} while (var_r29 < 5);
	var_r28   = 0;
	var_r27_2 = 0;
	do {
		temp_r29 = M2C_FIELD(M2C_FIELD(arg0, void**, var_r27_2 + 0xF0), s32*, 4);
		fn_8019EB94(temp_r29, &arg0->unkB8, 0);
		temp_f31 = fn_800D7B00(arg0->unkC8);
		fn_80195790(temp_r29 + 0x10, &lbl_80239984, 1, 1.0f - fn_800D7AE4(arg0->unkC8), temp_f31);
		fn_8019E880(temp_r29);
		if ((s32)arg0->unkD4 == 1) {
			temp_f31_2 = fn_800D7B00(0x8000);
			fn_80195790(temp_r29 + 0x10, &lbl_80239990, 1, 1.0f - fn_800D7AE4(0x8000), temp_f31_2);
			fn_8019E880(temp_r29);
		}
		fn_8019EC30(temp_r29, &sp8, 1);
		var_r27_2 += 4;
		var_r28 += 1;
	} while (var_r28 < 3);
	fn_8003C200(&arg0->unk30, &lbl_8_data_18A18, 1, 4);
	M2C_FIELD(arg0->unk40, f32*, 0x14)
	    = (f32)(M2C_FIELD(&lbl_8_data_18A18, f32*, 0x14) * arg0->unkD0);
	M2C_FIELD(arg0->unk40, f32*, 0xC)
	    = (f32)(M2C_FIELD(&lbl_8_data_18A18, f32*, 0xC) * arg0->unkD0);
	M2C_FIELD(arg0->unk40, f32*, 0x10)
	    = (f32)(M2C_FIELD(&lbl_8_data_18A18, f32*, 0x10) * arg0->unkD0);
	return arg0;
}

void* fn_8_C7014(void* arg0, s32 arg1)
{
	if (fn_80226468(M2C_FIELD(arg0, s32*, 0x18)) != 0U) {
		fn_80226440(arg0, arg1);
	}
	return arg0;
}

void* fn_8_C7068(void* arg0)
{
	void* sp8;
	void* temp_r3;

	sp8     = NULL;
	temp_r3 = fn_8013F484(M2C_FIELD(arg0, s32*, 4));
	sp8     = temp_r3;
	if (temp_r3 == NULL) {
		fn_8019EB10(M2C_FIELD(arg0, s32*, 4), fn_8_C70C4, &sp8);
	}
	return sp8;
}

s32 fn_8_C70C4(s32 arg0, void** arg1)
{
	void* temp_r3;

	temp_r3 = fn_8013F484(arg0);
	if (temp_r3 == NULL) {
		fn_8019EB10(arg0, fn_8_C70C4, arg1);
		return arg0;
	}
	*arg1 = temp_r3;
	return 0;
}

void fn_8_C7128(void* arg1)
{
	void* temp_r5;

	temp_r5 = M2C_FIELD(arg1, void**, 0x2C);
	if ((s8)M2C_FIELD(temp_r5, u8*, 0) < 0) {
		M2C_FIELD(temp_r5, u8*, 0) = 0U;
	}
	if ((s8)M2C_FIELD(temp_r5, u8*, 0) > 1) {
		M2C_FIELD(temp_r5, u8*, 0) = 1U;
	}
	if ((s8)M2C_FIELD(temp_r5, u8*, 1) < 0) {
		M2C_FIELD(temp_r5, u8*, 1) = 0U;
	}
	if ((s8)M2C_FIELD(temp_r5, u8*, 1) > 1) {
		M2C_FIELD(temp_r5, u8*, 1) = 1U;
	}
	M2C_FIELD(&grassObjectFieldNames, M2C_UNK**, 0)
	    = (M2C_UNK*)lbl_8_data_189F4[(s8)M2C_FIELD(temp_r5, u8*, 0)];
	M2C_FIELD(&grassObjectFieldNames, M2C_UNK**, 4)
	    = (M2C_UNK*)lbl_8_data_18A10[(s8)M2C_FIELD(temp_r5, u8*, 1)];
}

void grassObjectUnload(M2C_UNK arg_sp0)
{
	s32 var_r25;
	s32 var_r25_2;
	s32 var_r25_3;
	s32 var_r31;
	struct _struct_lbl_8_data_18938_0x14* var_r28;
	struct _struct_lbl_8_data_18938_0x14* var_r29;
	struct _struct_lbl_8_data_18960_0xC* var_r27;
	struct _struct_lbl_8_data_18960_0xC* var_r29_2;
	struct _struct_lbl_8_data_18978_0x14* var_r26;
	struct _struct_lbl_8_data_18978_0x14* var_r29_3;

	var_r31 = 0;
	var_r28 = lbl_8_data_18938;
	var_r27 = lbl_8_data_18960;
	var_r26 = lbl_8_data_18978;
	do {
		var_r25 = 0;
		var_r29 = var_r28;
	loop_2:
		if ((u32)var_r29->unk0 != 0U) {
			fn_80150958((void*)var_r29->unk0);
			var_r29->unk0 = 0U;
		}
		var_r29 += 4;
		var_r25 += 1;
		if (var_r25 < 5) {
			goto loop_2;
		}
		var_r25_2 = 0;
		var_r29_2 = var_r27;
	loop_6:
		if ((u32)var_r29_2->unk0 != 0U) {
			fn_80150958((void*)var_r29_2->unk0);
			var_r29_2->unk0 = 0U;
		}
		var_r29_2 += 4;
		var_r25_2 += 1;
		if (var_r25_2 < 3) {
			goto loop_6;
		}
		var_r25_3 = 0;
		var_r29_3 = var_r26;
	loop_10:
		if ((u32)var_r29_3->unk0 != 0U) {
			fn_8020C2D8(var_r29_3->unk0);
			var_r29_3->unk0 = 0U;
		}
		var_r29_3 += 4;
		var_r25_3 += 1;
		if (var_r25_3 < 5) {
			goto loop_10;
		}
		var_r28 += 0x14;
		var_r27 += 0xC;
		var_r26 += 0x14;
		var_r31 += 1;
	} while (var_r31 < 2);
}

void grassObjectLoad(M2C_UNK arg_sp0)
{
	const char** var_r20_2;
	M2C_UNK** var_r20_3;
	const char** var_r21;
	M2C_UNK** var_r26;
	const char** var_r28;
	const char** var_r30;
	s32 temp_r31;
	s32 var_r19;
	s32 var_r19_2;
	s32 var_r19_3;
	s32 var_r24;
	struct _struct_lbl_8_data_18938_0x14* var_r20;
	struct _struct_lbl_8_data_18938_0x14* var_r29;
	struct _struct_lbl_8_data_18960_0xC* var_r21_2;
	struct _struct_lbl_8_data_18960_0xC* var_r27;
	struct _struct_lbl_8_data_18978_0x14* var_r21_3;
	struct _struct_lbl_8_data_18978_0x14* var_r25;

	if ((u32)M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18) != 0U) {
		fn_801A4C84();
		temp_r31 = M2C_FIELD(lbl_8042C298, s32*, 0xA50);
		fn_800BC9F4(temp_r31, &lbl_802FF5A0);
		var_r24 = 0;
		var_r30 = lbl_8_data_18868;
		var_r29 = lbl_8_data_18938;
		var_r28 = lbl_8_data_18920;
		var_r27 = lbl_8_data_18960;
		var_r26 = lbl_8_data_18778;
		var_r25 = lbl_8_data_18978;
		do {
			var_r19 = 0;
			var_r21 = var_r30;
			var_r20 = var_r29;
		loop_5:
			var_r20->unk0
			    = fn_800BB92C(temp_r31, fn_800BC6CC(temp_r31, (M2C_UNK*)*var_r21), &lbl_802FF5A0);
			var_r21 += 4;
			var_r20 += 4;
			var_r19 += 1;
			if (var_r19 < 5) {
				goto loop_5;
			}
			var_r19_2 = 0;
			var_r20_2 = var_r28;
			var_r21_2 = var_r27;
		loop_7:
			var_r21_2->unk0
			    = fn_800BB92C(temp_r31, fn_800BC6CC(temp_r31, (M2C_UNK*)*var_r20_2), &lbl_802FF5A0);
			var_r20_2 += 4;
			var_r21_2 += 4;
			var_r19_2 += 1;
			if (var_r19_2 < 3) {
				goto loop_7;
			}
			var_r19_3 = 0;
			var_r20_3 = var_r26;
			var_r21_3 = var_r25;
		loop_9:
			var_r21_3->unk0
			    = fn_800BB0D4(temp_r31, fn_800BC6CC(temp_r31, *var_r20_3), &lbl_802FF5A0);
			var_r20_3 += 4;
			var_r21_3 += 4;
			var_r19_3 += 1;
			if (var_r19_3 < 5) {
				goto loop_9;
			}
			var_r30 += 0x14;
			var_r29 += 0x14;
			var_r28 += 0xC;
			var_r27 += 0xC;
			var_r26 += 0x14;
			var_r25 += 0x14;
			var_r24 += 1;
		} while (var_r24 < 2);
	}
}

void grassObjectCreate(void)
{
	TObject* object = (TObject*)fn_80018A34(lbl_8042C148, 0x11C);
	if (object != NULL) {
		fn_8_C6CAC(object, lbl_8042C110);
	}
}

void grassObjectRegister(void)
{
	M2C_UNK* temp_r3;

	M2C_FIELD(&grassObjectEntry, s32*, 0x14)            = 0;
	M2C_FIELD(&grassObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&grassObjectEntry, M2C_UNK**, 0)          = (M2C_UNK*)"GRASS OBJECT";
	M2C_FIELD(&grassObjectEntry, void (**)(M2C_UNK), 4) = grassObjectLoad;
	M2C_FIELD(&grassObjectEntry, void (**)(M2C_UNK), 8) = grassObjectUnload;
	M2C_FIELD(&grassObjectEntry, void (**)(), 0xC)      = grassObjectCreate;
	M2C_FIELD(&grassObjectEntry, s32*, 0x10)            = 0;
	M2C_FIELD(&grassObjectEntry, s32*, 0x14)            = 0x20000;
	M2C_FIELD(&grassObjectEntry, s32*, 0x18)            = 0;
	M2C_FIELD(&grassObjectEntry, s8*, 0x20)             = 0x1E;
	M2C_FIELD(&grassObjectEntry, s16*, 0x1C)            = 0x118B;
	M2C_FIELD(&grassObjectEntry, s16*, 0x1E)            = 2;
	M2C_FIELD(&grassObjectEntry, s8*, 0x21)             = 0;
	temp_r3                                             = (M2C_UNK*)"ccF";
	M2C_FIELD(&grassObjectEntry, M2C_UNK**, 0x24)       = temp_r3;
	M2C_FIELD(&grassObjectEntry, M2C_UNK**, 0x28)       = &grassObjectFieldNames;
	if (temp_r3 != NULL) {
		M2C_FIELD(&grassObjectEntry, s32*, 0x14) = 0x20008;
		return;
	}
	M2C_FIELD(&grassObjectEntry, s32*, 0x14) = 0x20000;
}

__declspec(section ".ctors") void (*const grassObjectCtorEntry)(void) = grassObjectRegister;
}
