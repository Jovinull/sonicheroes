#include "types.h"

typedef s32 M2C_UNK;
extern "C" void* memcpy(void*, const void*, u32);
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(u32)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value)        (*(type*)&(value))
#define M2C_STRUCT_COPY(dst, src, size) memcpy((dst), (src), (size))

typedef struct DAnimClass DAnimClass;
typedef struct RpDMorphAnimation RpDMorphAnimation;

typedef struct TObject {
	/* 0x00 */ M2C_UNK* unk0;   /* inferred */
	/* 0x04 */ char pad4[0x14]; /* maybe part of unk0[6]? */
	/* 0x18 */ M2C_UNK* unk18;  /* inferred */
	/* 0x1C */ char pad1C[2];
	/* 0x1E */ s16 unk1E;     /* inferred */
	/* 0x20 */ char pad20[8]; /* maybe part of unk1E[5]? */
	/* 0x28 */ M2C_UNK unk28; /* inferred */
	/* 0x2C */ void* unk2C;   /* inferred */
	/* 0x30 */ M2C_UNK unk30; /* inferred */
	/* 0x34 */ char pad34[0x5C];
	/* 0x90 */ f32 unk90;        /* inferred */
	/* 0x94 */ f32 unk94;        /* inferred */
	/* 0x98 */ f32 unk98;        /* inferred */
	/* 0x9C */ s32 unk9C;        /* inferred */
	/* 0xA0 */ s32 unkA0;        /* inferred */
	/* 0xA4 */ s32 unkA4;        /* inferred */
	/* 0xA8 */ char padA8[0x10]; /* maybe part of unkA4[5]? */
	/* 0xB8 */ s32 unkB8;        /* inferred */
	/* 0xBC */ void* unkBC;      /* inferred */
	/* 0xC0 */ void* unkC0;      /* inferred */
	/* 0xC4 */ void* unkC4;      /* inferred */
	/* 0xC8 */ M2C_UNK* unkC8;   /* inferred */
	/* 0xCC */ void* unkCC;      /* inferred */
	/* 0xD0 */ void* unkD0;      /* inferred */
	/* 0xD4 */ M2C_UNK* unkD4;   /* inferred */
	/* 0xD8 */ f32* unkD8;       /* inferred */
	/* 0xDC */ s32* unkDC;       /* inferred */
	/* 0xE0 */ s32* unkE0;       /* inferred */
	/* 0xE4 */ s32 unkE4;        /* inferred */
	/* 0xE8 */ f32 unkE8;        /* inferred */
	/* 0xEC */ s32 unkEC;        /* inferred */
} TObject;                       /* size >= 0xF0 */

struct _struct_lbl_8_data_18B68_0x8 {
	/* 0x0 */ void* unk0; /* inferred */
	/* 0x4 */ char pad4[4];
}; /* size = 0x8 */

extern "C" {

f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void*, void*); /* extern */
void* __ct__7TObjectFP7TObject(void*, void*);                       /* extern */
void* __dt__7TObjectFv(void*, s32);                                 /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                              /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                              /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                                 /* extern */
u32 fn_80018A34(s32, M2C_UNK);                                      /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                                      /* extern */
s32 fn_8005B8BC(void*);                                             /* extern */
s32 fn_8005B8D8(void*);                                             /* extern */
s32 fn_8005B9F0(void*);                                             /* extern */
M2C_UNK fn_8005BE6C(M2C_UNK*);                                      /* extern */
M2C_UNK fn_8005D5C8(void*, M2C_UNK);                                /* extern */
void* fn_8005E394(void*, M2C_UNK);                                  /* extern */
void** fn_8005F4E8();                                               /* extern */
M2C_UNK fn_8005F50C(void*, void***, M2C_UNK);                       /* extern */
RpDMorphAnimation* fn_800BB39C(s32, s32, M2C_UNK*);                 /* extern */
void* fn_800BB92C(s32, s32, M2C_UNK*);                              /* extern */
s32 fn_800BC6CC(s32, M2C_UNK*);                                     /* extern */
M2C_UNK fn_800BC9F4(s32, M2C_UNK*);                                 /* extern */
f32 fn_800D7AE4(s32);                                               /* extern */
f32 fn_800D7B00(s32);                                               /* extern */
M2C_UNK fn_8013BD74(void*);                                         /* extern */
M2C_UNK fn_8013D344(void*, RpDMorphAnimation*);                     /* extern */
M2C_UNK fn_8013D5C8(void*, f32*, f32);                              /* extern */
s32 fn_8014F1B0(s32 arg0);                                          /* extern */
M2C_UNK fn_8014F854(void*);                                         /* extern */
M2C_UNK fn_8014FFBC(void*, s32 (*)(void*, void**), void**);         /* extern */
void* fn_80150588(s32, ...);                                        /* extern */
M2C_UNK fn_80150958(void*);                                         /* extern */
M2C_UNK fn_8015BB08(s32);                                           /* extern */
M2C_UNK fn_8015BBF8(M2C_UNK, void*);                                /* extern */
M2C_UNK fn_8015BD78(void*);                                         /* extern */
M2C_UNK fn_80195790(s32, M2C_UNK*, M2C_UNK, f32, f32);              /* extern */
M2C_UNK fn_8019E880(s32);                                           /* extern */
M2C_UNK fn_8019EB94(s32, void*, M2C_UNK);                           /* extern */
M2C_UNK fn_8019EC30(s32, f32*, M2C_UNK);                            /* extern */
M2C_UNK fn_801A4C84(u32);                                           /* extern */
M2C_UNK fn_8_C7128(s32);                                            /* extern */
s32 fn_8_C7550(void* arg0, void** arg1);                            /* static */
s32 fn_8_C7580(s32 arg0);                                           /* static */
s32 fn_8_C787C(void* arg0, void** arg1);                            /* static */
TObject* fn_8_C8688(TObject* arg0, TObject* arg1);                  /* static */
void s11FlagCreate();                                               /* static */
void s11FlagLoad(M2C_UNK arg_sp0);                                  /* static */
void s11FlagUnload(M2C_UNK arg_sp0);                                /* static */
extern M2C_UNK lbl_80239978;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_802FF5A0;
extern TObject* lbl_8042C110;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern DAnimClass lbl_8042C340;
extern u32 lbl_8_bss_1CD8;
extern M2C_UNK (*lbl_8_bss_1CDC)(void*, ...);
extern f32 lbl_8_bss_1CE0;
extern M2C_UNK lbl_8_bss_1CE4;
extern M2C_UNK lbl_8_rodata_1F78;
extern M2C_UNK lbl_8_rodata_1F84;
extern f32 lbl_8_rodata_1F90;
extern f32 lbl_8_rodata_1F94;
static char lbl_8_data_18AA8[] = "s11_pnw_flagl.dma";
static M2C_UNK gap_04_00018ABA_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_18ABC[] = "s11_pnw_flagd.dma";
static M2C_UNK gap_04_00018ACE_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18AD0[2] = { lbl_8_data_18AA8, lbl_8_data_18ABC };
static char lbl_8_data_18AD8[]         = "s11_pnw_flagl.dff";
static M2C_UNK gap_04_00018AEA_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_18AEC[] = "s11_pnw_flagd.dff";
static M2C_UNK gap_04_00018AFE_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18B00[2] = { lbl_8_data_18AD8, lbl_8_data_18AEC };
static char lbl_8_data_18B08[]         = "s11_on_flagl_a.dff";
static M2C_UNK gap_04_00018B1B_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_18B1C[] = "s11_on_flagl_b.dff";
static M2C_UNK gap_04_00018B2F_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_18B30[] = "s11_on_flagd_a.dff";
static M2C_UNK gap_04_00018B43_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_18B44[] = "s11_on_flagd_b.dff";
static M2C_UNK gap_04_00018B57_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18B58[4] = {
	lbl_8_data_18B08,
	lbl_8_data_18B1C,
	lbl_8_data_18B30,
	lbl_8_data_18B44,
};
static struct _struct_lbl_8_data_18B68_0x8 lbl_8_data_18B68[2] = { { NULL }, { NULL } };
static u32 lbl_8_data_18B78[2]                                 = { 0x00000000, 0x00000000 };
static void* lbl_8_data_18B80[2]                               = { NULL, NULL };
static RpDMorphAnimation* lbl_8_data_18B88[2]                  = { NULL, NULL };
static s32 lbl_8_data_18B90[2]                                 = { 0, 0 };
static s32 lbl_8_data_18B98[2]                                 = { 0, 0 };
static char lbl_8_data_18BA0[]                                 = "type      : light";
static M2C_UNK gap_04_00018BB2_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18BB4;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018BB9_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_18BBC[] = "direction : up";
static M2C_UNK gap_04_00018BCB_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_18BCC;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00018BDB_data; /* unable to generate initializer: unknown type */
static M2C_UNK s11FlagFieldNames;    /* unable to generate initializer: unknown type */
static char lbl_8_data_18BEC[] = "type      : dark";
static M2C_UNK gap_04_00018BFD_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18C00[2] = { lbl_8_data_18BA0, lbl_8_data_18BEC };
static char lbl_8_data_18C08[]         = "direction : down";
static M2C_UNK gap_04_00018C19_data; /* unable to generate initializer: unknown type */
static const char* lbl_8_data_18C1C[2] = { lbl_8_data_18BBC, lbl_8_data_18C08 };
static char lbl_8_data_18C24[]         = "TObjS11Flag";
static const char* lbl_8_data_18C30    = lbl_8_data_18C24;
static M2C_UNK lbl_8_data_18C34; /* unable to generate initializer: unknown type */
static char s11FlagDisplayName[] = "S11 FLAG";
static M2C_UNK gap_04_00018C79_data; /* unable to generate initializer: unknown type */
static char s11FlagFieldTypes[] = "cccF";
static M2C_UNK gap_04_00018C81_data; /* unable to generate initializer: unknown type */
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
	u8 pad2C[4];             /* 0x2C */
} ObjectEntry;               /* 0x30 */

static ObjectEntry s11FlagEntry;
extern const f32 lbl_8_rodata_2010[12] = { 0.0f, 1.401298464324817e-45f, 2.802596928649634e-45f,
	4.203895392974451e-45f, 5.605193857299268e-45f, 7.006492321624085e-45f, 8.407790785948902e-45f,
	9.80908925027372e-45f, 1.1210387714598537e-44f, 1.2611686178923354e-44f, 1.401298464324817e-44f,
	1.5414283107572988e-44f };
extern const f32 lbl_8_rodata_2040[3]  = { 1.0f, 0.009999999776482582f, 1.0f };
extern const f32 lbl_8_rodata_204C[1]  = { 100.0f };
extern const f32 lbl_8_rodata_2050[1]  = { 1.0f };
extern const f32 lbl_8_rodata_2054[1]  = { 0.016666699200868607f };
extern const f64 lbl_8_rodata_2058[1]  = { 4503601774854144.0 };
extern const f32 lbl_8_rodata_2060[2]  = { 0.10000000149011612f, 0.0f };
extern const f32 lbl_8_rodata_2068[1]  = { 0.004999999888241291f };
extern const f32 lbl_8_rodata_206C[1]  = { 0.1550000011920929f };
extern const f32 lbl_8_rodata_2070[1]  = { 0.0f };
extern const f32 lbl_8_rodata_2074[1]  = { 0.1599999964237213f };
extern const f32 lbl_8_rodata_2078[1]  = { -1000000.0f };
extern const f32 lbl_8_rodata_207C[1]  = { 21.0f };
extern const f32 lbl_8_rodata_2080[1]  = { 0.0f };
extern const f32 lbl_8_rodata_2084[1]  = { 20.0f };
extern const f32 lbl_8_rodata_2088[1]  = { 1.0f };
extern const f32 lbl_8_rodata_208C[1]  = { 10.0f };
extern const f32 lbl_8_rodata_2090[1]  = { 100.0f };
extern const f32 lbl_8_rodata_2094[1]  = { 0.699999988079071f };
extern const f32 lbl_8_rodata_2098[1]  = { 1.2000000476837158f };
extern const f32 lbl_8_rodata_209C[1]  = { 3.0517578125e-05f };
extern const f32 lbl_8_rodata_20A0[1]  = { -0.10000000149011612f };
extern const f32 lbl_8_rodata_20A4[1]  = { -2.0f };
extern const f64 lbl_8_rodata_20A8[1]  = { 4503601774854144.0 };
extern const f32 lbl_8_rodata_20B0[2]  = { 0.0f, 0.0f };
extern const f32 lbl_8_rodata_20B8[5]  = { 0.0f, 0.0f, 0.0f, 1.5f, 0.0f };
extern const f32 lbl_8_rodata_20CC[1]  = { 0.0f };
extern const f32 lbl_8_rodata_20D0[1]  = { 20.0f };
extern const f64 lbl_8_rodata_20D8[1]  = { 4503601774854144.0 };
extern const f32 lbl_8_rodata_20E0[2]  = { 100.0f, 0.0f };
extern const f32 lbl_8_rodata_20E8[1]  = { 10430.380859375f };

void fn_8_C7548(s32 arg0)
{
	fn_8_C7128(arg0 - 0x28);
}

s32 fn_8_C7550(void* arg0, void** arg1)
{
	*arg1                               = arg0;
	M2C_FIELD(arg0, s32(**)(s32), 0x48) = fn_8_C7580;
	if (((s32 (*)(s32))M2C_FIELD(arg0, s32(**)(s32), 0x48)) == NULL) {
		M2C_FIELD(arg0, s32(**)(s32), 0x48) = fn_8014F1B0;
	}
	return 0;
}

s32 fn_8_C7580(s32 arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32* temp_r4_2;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r30;
	void* temp_r31;
	void* temp_r4;

	temp_r31 = *fn_8005F4E8();
	if (temp_r31 == NULL) {
		return arg0;
	}
	temp_r0 = *M2C_FIELD(temp_r31, s32**, 0x10);
	temp_r4 = lbl_8_data_18B80[temp_r0];
	if ((temp_r4 == NULL) || ((RpDMorphAnimation*)lbl_8_data_18B88[temp_r0] == NULL)) {
		return arg0;
	}
	temp_r30 = M2C_FIELD(temp_r4, s32*, 4);
	sp8      = M2C_FIELD(&lbl_8_rodata_1F84, f32*, 0);
	spC      = M2C_FIELD(&lbl_8_rodata_1F84, f32*, 4);
	sp10     = M2C_FIELD(&lbl_8_rodata_1F84, f32*, 8);
	temp_f0  = *M2C_FIELD(temp_r31, f32**, 0xC);
	sp8      = temp_f0;
	spC      = temp_f0;
	sp10     = temp_f0;
	fn_8019EC30(temp_r30, &sp8, 0);
	if ((s32)*M2C_FIELD(temp_r31, s32**, 0x14) == 1) {
		temp_f31 = fn_800D7B00(0x8000);
		fn_80195790(
		    temp_r30 + 0x10, &lbl_80239978, 2, lbl_8_rodata_1F90 - fn_800D7AE4(0x8000), temp_f31);
		fn_8019E880(temp_r30);
	}
	temp_f31_2 = fn_800D7B00(M2C_FIELD(M2C_FIELD(temp_r31, void**, 4), s32*, 4));
	fn_80195790(temp_r30 + 0x10, &lbl_80239984, 2,
	    lbl_8_rodata_1F90 - fn_800D7AE4(M2C_FIELD(M2C_FIELD(temp_r31, void**, 4), s32*, 4)),
	    temp_f31_2);
	fn_8019E880(temp_r30);
	temp_f31_3 = fn_800D7B00(M2C_FIELD(M2C_FIELD(temp_r31, void**, 4), s32*, 0));
	fn_80195790(temp_r30 + 0x10, &lbl_80239978, 2,
	    lbl_8_rodata_1F90 - fn_800D7AE4(M2C_FIELD(M2C_FIELD(temp_r31, void**, 4), s32*, 0)),
	    temp_f31_3);
	fn_8019E880(temp_r30);
	temp_f31_4 = fn_800D7B00(M2C_FIELD(M2C_FIELD(temp_r31, void**, 4), s32*, 8));
	fn_80195790(temp_r30 + 0x10, &lbl_80239990, 2,
	    lbl_8_rodata_1F90 - fn_800D7AE4(M2C_FIELD(M2C_FIELD(temp_r31, void**, 4), s32*, 8)),
	    temp_f31_4);
	fn_8019E880(temp_r30);
	fn_8019EB94(temp_r30, M2C_FIELD(temp_r31, void**, 0), 2);
	temp_r0_2 = *M2C_FIELD(temp_r31, s32**, 0x10);
	if ((s32)lbl_8_data_18B98[temp_r0_2] == 0) {
		fn_8013D344(lbl_8_data_18B80[temp_r0_2], lbl_8_data_18B88[temp_r0_2]);
		temp_r4_2 = M2C_FIELD(temp_r31, f32**, 8);
		fn_8013D5C8(lbl_8_data_18B80[*M2C_FIELD(temp_r31, s32**, 0x10)], temp_r4_2, *temp_r4_2);
		lbl_8_data_18B98[*M2C_FIELD(temp_r31, s32**, 0x10)] = 1;
		lbl_8_data_18B90[*M2C_FIELD(temp_r31, s32**, 0x10)] = 0;
	}
	lbl_8_bss_1CDC(lbl_8_data_18B80[*M2C_FIELD(temp_r31, s32**, 0x10)], &lbl_8_bss_1CDC);
	return arg0;
}

s32 fn_8_C787C(void* arg0, void** arg1)
{
	*arg1          = arg0;
	lbl_8_bss_1CDC = M2C_FIELD(arg0, M2C_UNK(**)(void*, ...), 0x48);
	return 0;
}

void fn_8_C7898(void* arg0)
{
	void* temp_r31;
	void* temp_r31_2;

	temp_r31 = M2C_FIELD(arg0, void**, 0xBC);
	if (temp_r31 != NULL) {
		fn_8015BBF8(fn_8015BD78(temp_r31), temp_r31);
		fn_80150958(M2C_FIELD(arg0, void**, 0xBC));
		M2C_FIELD(arg0, void**, 0xBC) = NULL;
	}
	temp_r31_2 = M2C_FIELD(arg0, void**, 0xC0);
	if (temp_r31_2 != NULL) {
		fn_8015BBF8(fn_8015BD78(temp_r31_2), temp_r31_2);
		fn_80150958(M2C_FIELD(arg0, void**, 0xC0));
		M2C_FIELD(arg0, void**, 0xC0) = NULL;
		M2C_FIELD(arg0, s32*, 0xC4)   = 0;
	}
}

void fn_8_C7924(void* arg0)
{
	void* temp_r31;
	void* temp_r30;
	s32 temp_r0;

	if ((void*)M2C_FIELD(arg0, void**, 0xBC) == NULL) {
		temp_r0                       = M2C_FIELD(arg0, s32*, 0xB8);
		M2C_FIELD(arg0, void**, 0xBC) = fn_80150588(
		    M2C_FIELD(&lbl_8_data_18B68[temp_r0] + (M2C_FIELD(arg0, s32*, 0xEC) * 4), s32*, 0),
		    temp_r0 * 8);
		if ((void*)M2C_FIELD(arg0, void**, 0xBC) != NULL) {
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x7260));
			fn_8005D5C8(M2C_FIELD(arg0, void**, 0xBC), 0x10);
		}
	}
	if ((void*)M2C_FIELD(arg0, void**, 0xC0) == NULL) {
		M2C_FIELD(arg0, void**, 0xC0) = fn_80150588(M2C_FIELD(lbl_8042C1D0, s32*, 0xB08));
		if ((void*)M2C_FIELD(arg0, void**, 0xC0) != NULL) {
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x7278));
			temp_r31 = fn_8005E394(M2C_FIELD(arg0, void**, 0xC0), 0);
			fn_8014FFBC(M2C_FIELD(arg0, void**, 0xC0), fn_8_C7550, (void**)((u8*)arg0 + 0xC4));
			if ((s32)(M2C_FIELD(lbl_8_data_18B80[M2C_FIELD(arg0, s32*, 0xB8)], s32*, 0x4C) & 2)
			    != 0) {
				fn_8014F854(temp_r31);
			}
			temp_r30 = lbl_8_data_18B80[M2C_FIELD(arg0, s32*, 0xB8)];
			if ((s32)(M2C_FIELD(temp_r31, s32*, 0x4C) & 2) != 0) {
				fn_8014F854(temp_r31);
			}
			M2C_STRUCT_COPY(temp_r31, temp_r30, 0xC);
			M2C_FIELD(temp_r31, f32*, 0x28) = (f32)M2C_FIELD(temp_r30, f32*, 0x28);
		}
	}
}

void fn_8_C7A90(void* arg0)
{
	void** sp8;

	M2C_FIELD(arg0, s32*, 0xCC)   = (s32)M2C_FIELD(arg0, s32*, 0x28);
	M2C_FIELD(arg0, s32*, 0xD0)   = (s32)(M2C_FIELD(arg0, s32*, 0x28) + 0xC);
	M2C_FIELD(arg0, s32*, 0xD4)   = (s32)M2C_FIELD(arg0, s32*, 0xC8);
	M2C_FIELD(arg0, void**, 0xD8) = (u8*)arg0 + 0xE8;
	M2C_FIELD(arg0, void**, 0xDC) = (u8*)arg0 + 0xB8;
	M2C_FIELD(arg0, void**, 0xE0) = (u8*)arg0 + 0xE4;
	sp8                           = (void**)((u8*)arg0 + 0xCC);
	fn_8005F50C(M2C_FIELD(arg0, void**, 0xC4), &sp8, 4);
}

void fn_8_C7AF8(void* arg0)
{
	void* temp_r5;
	void* temp_r4;
	void* temp_r4_2;

	temp_r4                     = M2C_FIELD(arg0, void**, 0x28);
	temp_r5                     = M2C_FIELD(temp_r4, void**, 0x2C);
	M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(temp_r4, f32*, 0);
	M2C_FIELD(arg0, f32*, 0x94) = (f32)M2C_FIELD(temp_r4, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x98) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	temp_r4_2                   = M2C_FIELD(arg0, void**, 0x28);
	M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(temp_r4_2, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0xA0) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0xA4) = (s32)M2C_FIELD(temp_r4_2, s32*, 0x14);
	M2C_FIELD(arg0, s32*, 0xE4) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 2);
	M2C_FIELD(arg0, s32*, 0xB8) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 0);
	M2C_FIELD(arg0, s32*, 0xEC) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 1);
	M2C_FIELD(arg0, f32*, 0xE8) = (f32)(lbl_8_rodata_1F90 + M2C_FIELD(temp_r5, f32*, 4));
}

void fn_8_C7B74(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
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
	void* temp_r3;
	void* temp_r3_2;

	temp_r3 = M2C_FIELD(arg0, void**, 0xBC);
	if (temp_r3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3, s32*, 4);
		sp8      = M2C_FIELD(&lbl_8_rodata_1F78, f32*, 0);
		spC      = M2C_FIELD(&lbl_8_rodata_1F78, f32*, 4);
		sp10     = M2C_FIELD(&lbl_8_rodata_1F78, f32*, 8);
		temp_f0  = M2C_FIELD(arg0, f32*, 0xE8);
		sp8      = temp_f0;
		spC      = temp_f0;
		sp10     = temp_f0;
		fn_8019EC30(temp_r31, &sp8, 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0xE4) == 1) {
			temp_f31 = fn_800D7B00(0x8000);
			fn_80195790(temp_r31 + 0x10, &lbl_80239978, 2, lbl_8_rodata_1F90 - fn_800D7AE4(0x8000),
			    temp_f31);
			fn_8019E880(temp_r31);
		}
		temp_f31_2 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10));
		fn_80195790(temp_r31 + 0x10, &lbl_80239984, 2,
		    lbl_8_rodata_1F90 - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10)),
		    temp_f31_2);
		fn_8019E880(temp_r31);
		temp_f31_3 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC));
		fn_80195790(temp_r31 + 0x10, &lbl_80239978, 2,
		    lbl_8_rodata_1F90 - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC)),
		    temp_f31_3);
		fn_8019E880(temp_r31);
		temp_f31_4 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14));
		fn_80195790(temp_r31 + 0x10, &lbl_80239990, 2,
		    lbl_8_rodata_1F90 - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14)),
		    temp_f31_4);
		fn_8019E880(temp_r31);
		fn_8019EB94(temp_r31, M2C_FIELD(arg0, void**, 0x28), 2);
		temp_r3_2 = M2C_FIELD(arg0, void**, 0xC0);
		if (temp_r3_2 != NULL) {
			temp_r31_2 = M2C_FIELD(temp_r3_2, s32*, 4);
			fn_8019EC30(temp_r31_2, &sp8, 0);
			if ((s32)M2C_FIELD(arg0, s32*, 0xE4) == 1) {
				temp_f31_5 = fn_800D7B00(0x8000);
				fn_80195790(temp_r31_2 + 0x10, &lbl_80239978, 2,
				    lbl_8_rodata_1F90 - fn_800D7AE4(0x8000), temp_f31_5);
				fn_8019E880(temp_r31_2);
			}
			temp_f31_6 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10));
			fn_80195790(temp_r31_2 + 0x10, &lbl_80239984, 2,
			    lbl_8_rodata_1F90
			        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10)),
			    temp_f31_6);
			fn_8019E880(temp_r31_2);
			temp_f31_7 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC));
			fn_80195790(temp_r31_2 + 0x10, &lbl_80239978, 2,
			    lbl_8_rodata_1F90
			        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC)),
			    temp_f31_7);
			fn_8019E880(temp_r31_2);
			temp_f31_8 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14));
			fn_80195790(temp_r31_2 + 0x10, &lbl_80239990, 2,
			    lbl_8_rodata_1F90
			        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14)),
			    temp_f31_8);
			fn_8019E880(temp_r31_2);
			fn_8019EB94(temp_r31_2, M2C_FIELD(arg0, void**, 0x28), 2);
		}
	}
}

void fn_8_C7EBC(void* arg0)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	void** sp8;
	f32* temp_r4_2;
	f32* temp_r4_3;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	f32 temp_f31_5;
	f32 temp_f31_6;
	f32 temp_f31_7;
	f32 temp_f31_8;
	s32 temp_r0;
	s32 temp_r31_2;
	s32 temp_r31_3;
	s32 temp_r5;
	s32 temp_r6;
	void* temp_r29;
	void* temp_r29_2;
	void* temp_r29_3;
	void* temp_r31;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r4;

	if ((fn_8005B9F0((u8*)arg0 + 0x28) != 0) || (fn_8005B8BC((u8*)arg0 + 0x28) != 0)) {
		M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
		return;
	}
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) == 0) {
		if (fn_8005B8D8((u8*)arg0 + 0x28) != 0) {
			temp_r5                     = M2C_FIELD(arg0, s32*, 0xB8);
			temp_r6                     = M2C_FIELD(arg0, s32*, 0xEC);
			temp_r3                     = M2C_FIELD(arg0, void**, 0x28);
			temp_r4                     = M2C_FIELD(temp_r3, void**, 0x2C);
			M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(temp_r3, f32*, 0);
			M2C_FIELD(arg0, f32*, 0x94) = (f32)M2C_FIELD(temp_r3, f32*, 4);
			M2C_FIELD(arg0, f32*, 0x98) = (f32)M2C_FIELD(temp_r3, f32*, 8);
			temp_r3_2                   = M2C_FIELD(arg0, void**, 0x28);
			M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(temp_r3_2, s32*, 0xC);
			M2C_FIELD(arg0, s32*, 0xA0) = (s32)M2C_FIELD(temp_r3_2, s32*, 0x10);
			M2C_FIELD(arg0, s32*, 0xA4) = (s32)M2C_FIELD(temp_r3_2, s32*, 0x14);
			M2C_FIELD(arg0, s32*, 0xE4) = (s32)(s8)M2C_FIELD(temp_r4, u8*, 2);
			M2C_FIELD(arg0, s32*, 0xB8) = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0);
			M2C_FIELD(arg0, s32*, 0xEC) = (s32)(s8)M2C_FIELD(temp_r4, u8*, 1);
			M2C_FIELD(arg0, f32*, 0xE8) = (f32)(lbl_8_rodata_1F90 + M2C_FIELD(temp_r4, f32*, 4));
			if (((s32)M2C_FIELD(arg0, s32*, 0xB8) != temp_r5)
			    || ((s32)M2C_FIELD(arg0, s32*, 0xEC) != temp_r6)) {
				temp_r29 = M2C_FIELD(arg0, void**, 0xBC);
				if (temp_r29 != NULL) {
					fn_8015BBF8(fn_8015BD78(temp_r29), temp_r29);
					fn_80150958(M2C_FIELD(arg0, void**, 0xBC));
					M2C_FIELD(arg0, void**, 0xBC) = NULL;
				}
				temp_r29_2 = M2C_FIELD(arg0, void**, 0xC0);
				if (temp_r29_2 != NULL) {
					fn_8015BBF8(fn_8015BD78(temp_r29_2), temp_r29_2);
					fn_80150958(M2C_FIELD(arg0, void**, 0xC0));
					M2C_FIELD(arg0, void**, 0xC0) = NULL;
					M2C_FIELD(arg0, void**, 0xC4) = NULL;
				}
				if ((void*)M2C_FIELD(arg0, void**, 0xBC) == NULL) {
					temp_r0                       = M2C_FIELD(arg0, s32*, 0xB8);
					M2C_FIELD(arg0, void**, 0xBC) = fn_80150588(
					    M2C_FIELD(&lbl_8_data_18B68[temp_r0] + (M2C_FIELD(arg0, s32*, 0xEC) * 4),
					        s32*, 0),
					    temp_r0 * 8);
					if ((void*)M2C_FIELD(arg0, void**, 0xBC) != NULL) {
						fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x7260));
						fn_8005D5C8(M2C_FIELD(arg0, void**, 0xBC), 0x10);
					}
				}
				if ((void*)M2C_FIELD(arg0, void**, 0xC0) == NULL) {
					M2C_FIELD(arg0, void**, 0xC0)
					    = fn_80150588(M2C_FIELD(lbl_8042C1D0, s32*, 0xB08));
					if ((void*)M2C_FIELD(arg0, void**, 0xC0) != NULL) {
						fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x7278));
						temp_r31 = fn_8005E394(M2C_FIELD(arg0, void**, 0xC0), 0);
						fn_8014FFBC(
						    M2C_FIELD(arg0, void**, 0xC0), fn_8_C7550, (void**)((u8*)arg0 + 0xC4));
						if ((s32)(M2C_FIELD(
						              lbl_8_data_18B80[M2C_FIELD(arg0, s32*, 0xB8)], s32*, 0x4C)
						        & 2)
						    != 0) {
							fn_8014F854(lbl_8_data_18B80[M2C_FIELD(arg0, s32*, 0xB8)]);
						}
						temp_r29_3 = lbl_8_data_18B80[M2C_FIELD(arg0, s32*, 0xB8)];
						if ((s32)(M2C_FIELD(temp_r31, s32*, 0x4C) & 2) != 0) {
							fn_8014F854(temp_r31);
						}
						M2C_STRUCT_COPY(temp_r31, temp_r29_3, 0xC);
						M2C_FIELD(temp_r31, f32*, 0x28) = (f32)M2C_FIELD(temp_r29_3, f32*, 0x28);
					}
				}
				M2C_FIELD(arg0, void**, 0xCC) = (void*)M2C_FIELD(arg0, void**, 0x28);
				M2C_FIELD(arg0, void**, 0xD0) = (u8*)M2C_FIELD(arg0, void**, 0x28) + 0xC;
				M2C_FIELD(arg0, f32**, 0xD4)  = (f32*)M2C_FIELD(arg0, f32**, 0xC8);
				M2C_FIELD(arg0, void**, 0xD8) = (u8*)arg0 + 0xE8;
				M2C_FIELD(arg0, void**, 0xDC) = (u8*)arg0 + 0xB8;
				M2C_FIELD(arg0, void**, 0xE0) = (u8*)arg0 + 0xE4;
				sp8                           = (void**)((u8*)arg0 + 0xCC);
				fn_8005F50C(M2C_FIELD(arg0, void**, 0xC4), &sp8, 4);
			}
			temp_r3_3 = M2C_FIELD(arg0, void**, 0xBC);
			if (temp_r3_3 != NULL) {
				temp_r31_2 = M2C_FIELD(temp_r3_3, s32*, 4);
				spC        = M2C_FIELD(&lbl_8_rodata_1F78, f32*, 0);
				sp10       = M2C_FIELD(&lbl_8_rodata_1F78, f32*, 4);
				sp14       = M2C_FIELD(&lbl_8_rodata_1F78, f32*, 8);
				temp_f0    = M2C_FIELD(arg0, f32*, 0xE8);
				spC        = temp_f0;
				sp10       = temp_f0;
				sp14       = temp_f0;
				fn_8019EC30(temp_r31_2, &spC, 0);
				if ((s32)M2C_FIELD(arg0, s32*, 0xE4) == 1) {
					temp_f31 = fn_800D7B00(0x8000);
					fn_80195790(temp_r31_2 + 0x10, &lbl_80239978, 2,
					    lbl_8_rodata_1F90 - fn_800D7AE4(0x8000), temp_f31);
					fn_8019E880(temp_r31_2);
				}
				temp_f31_2 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10));
				fn_80195790(temp_r31_2 + 0x10, &lbl_80239984, 2,
				    lbl_8_rodata_1F90
				        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10)),
				    temp_f31_2);
				fn_8019E880(temp_r31_2);
				temp_f31_3 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC));
				fn_80195790(temp_r31_2 + 0x10, &lbl_80239978, 2,
				    lbl_8_rodata_1F90
				        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC)),
				    temp_f31_3);
				fn_8019E880(temp_r31_2);
				temp_f31_4 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14));
				fn_80195790(temp_r31_2 + 0x10, &lbl_80239990, 2,
				    lbl_8_rodata_1F90
				        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14)),
				    temp_f31_4);
				fn_8019E880(temp_r31_2);
				fn_8019EB94(temp_r31_2, M2C_FIELD(arg0, void**, 0x28), 2);
				temp_r3_4 = M2C_FIELD(arg0, void**, 0xC0);
				if (temp_r3_4 != NULL) {
					temp_r31_3 = M2C_FIELD(temp_r3_4, s32*, 4);
					fn_8019EC30(temp_r31_3, &spC, 0);
					if ((s32)M2C_FIELD(arg0, s32*, 0xE4) == 1) {
						temp_f31_5 = fn_800D7B00(0x8000);
						fn_80195790(temp_r31_3 + 0x10, &lbl_80239978, 2,
						    lbl_8_rodata_1F90 - fn_800D7AE4(0x8000), temp_f31_5);
						fn_8019E880(temp_r31_3);
					}
					temp_f31_6 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10));
					fn_80195790(temp_r31_3 + 0x10, &lbl_80239984, 2,
					    lbl_8_rodata_1F90
					        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10)),
					    temp_f31_6);
					fn_8019E880(temp_r31_3);
					temp_f31_7 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC));
					fn_80195790(temp_r31_3 + 0x10, &lbl_80239978, 2,
					    lbl_8_rodata_1F90
					        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC)),
					    temp_f31_7);
					fn_8019E880(temp_r31_3);
					temp_f31_8 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14));
					fn_80195790(temp_r31_3 + 0x10, &lbl_80239990, 2,
					    lbl_8_rodata_1F90
					        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14)),
					    temp_f31_8);
					fn_8019E880(temp_r31_3);
					fn_8019EB94(temp_r31_3, M2C_FIELD(arg0, void**, 0x28), 2);
				}
			}
		}
		temp_r4_2 = M2C_FIELD(arg0, f32**, 0xC8);
		if ((temp_r4_2 != NULL) && ((s32)lbl_8_data_18B90[M2C_FIELD(arg0, s32*, 0xB8)] == 0)) {
			*temp_r4_2 += lbl_8_rodata_1F94;
			temp_r4_3 = M2C_FIELD(arg0, f32**, 0xC8);
			temp_f0_2 = *temp_r4_3;
			if (temp_f0_2 >= lbl_8_bss_1CE0) {
				*temp_r4_3 = temp_f0_2 - lbl_8_bss_1CE0;
			}
			lbl_8_data_18B90[M2C_FIELD(arg0, s32*, 0xB8)] = 1;
			lbl_8_data_18B98[M2C_FIELD(arg0, s32*, 0xB8)] = 0;
		}
		fn_8005B8D8((u8*)arg0 + 0x28);
	}
}

TObject* fn_8_C858C(TObject* arg0, s16 arg1)
{
	void* temp_r31;
	void* temp_r31_2;

	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_18C34;
		arg0->unk2C = (u8*)&lbl_8_data_18C34 + 0x2C;
		temp_r31    = arg0->unkBC;
		if (temp_r31 != NULL) {
			fn_8015BBF8(fn_8015BD78(temp_r31), temp_r31);
			fn_80150958(arg0->unkBC);
			arg0->unkBC = NULL;
		}
		temp_r31_2 = arg0->unkC0;
		if (temp_r31_2 != NULL) {
			fn_8015BBF8(fn_8015BD78(temp_r31_2), temp_r31_2);
			fn_80150958(arg0->unkC0);
			arg0->unkC0 = NULL;
			arg0->unkC4 = NULL;
		}
		dtor_8003C52C((u8*)arg0 + 0x30, 0);
		dtor_8005BD3C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_C8688(TObject* arg0, TObject* arg1)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	void** sp8;
	f32 temp_f0;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f31_3;
	f32 temp_f31_4;
	f32 temp_f31_5;
	f32 temp_f31_6;
	f32 temp_f31_7;
	f32 temp_f31_8;
	s32 temp_r0;
	s32 temp_r31_2;
	s32 temp_r31_3;
	void* temp_r29;
	void* temp_r31;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r4;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8005BE6C(&arg0->unk28);
	fn_8003C618(&arg0->unk30);
	arg0->unk18 = &lbl_8_data_18C34;
	arg0->unk2C = (u8*)&lbl_8_data_18C34 + 0x2C;
	arg0->unk0  = (M2C_UNK*)lbl_8_data_18C30;
	arg0->unk1E = 0xF0;
	arg0->unkC8 = &lbl_8_bss_1CE4;
	temp_r3     = M2C_FIELD(arg0, void**, 0x28);
	temp_r4     = M2C_FIELD(temp_r3, void**, 0x2C);
	arg0->unk90 = M2C_FIELD(temp_r3, f32*, 0);
	arg0->unk94 = M2C_FIELD(temp_r3, f32*, 4);
	arg0->unk98 = M2C_FIELD(temp_r3, f32*, 8);
	temp_r3_2   = M2C_FIELD(arg0, void**, 0x28);
	arg0->unk9C = M2C_FIELD(temp_r3_2, s32*, 0xC);
	arg0->unkA0 = M2C_FIELD(temp_r3_2, s32*, 0x10);
	arg0->unkA4 = M2C_FIELD(temp_r3_2, s32*, 0x14);
	arg0->unkE4 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 2);
	arg0->unkB8 = (s32)(s8)M2C_FIELD(temp_r4, u8*, 0);
	arg0->unkEC = (s32)(s8)M2C_FIELD(temp_r4, u8*, 1);
	arg0->unkE8 = lbl_8_rodata_1F90 + M2C_FIELD(temp_r4, f32*, 4);
	arg0->unkBC = NULL;
	arg0->unkC0 = NULL;
	if ((void*)arg0->unkBC == NULL) {
		temp_r0     = arg0->unkB8;
		arg0->unkBC = fn_80150588(
		    M2C_FIELD(&lbl_8_data_18B68[temp_r0] + (arg0->unkEC * 4), s32*, 0), temp_r0 * 8);
		if ((void*)arg0->unkBC != NULL) {
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x7260));
			fn_8005D5C8(arg0->unkBC, 0x10);
		}
	}
	if ((void*)arg0->unkC0 == NULL) {
		arg0->unkC0 = fn_80150588(M2C_FIELD(lbl_8042C1D0, s32*, 0xB08));
		if ((void*)arg0->unkC0 != NULL) {
			fn_8015BB08(M2C_FIELD(lbl_8042C1D0, s32*, 0x7278));
			temp_r31 = fn_8005E394(arg0->unkC0, 0);
			fn_8014FFBC(arg0->unkC0, fn_8_C7550, &arg0->unkC4);
			if ((s32)(M2C_FIELD(lbl_8_data_18B80[arg0->unkB8], s32*, 0x4C) & 2) != 0) {
				fn_8014F854(lbl_8_data_18B80[arg0->unkB8]);
			}
			temp_r29 = lbl_8_data_18B80[arg0->unkB8];
			if ((s32)(M2C_FIELD(temp_r31, s32*, 0x4C) & 2) != 0) {
				fn_8014F854(temp_r31);
			}
			M2C_STRUCT_COPY(temp_r31, temp_r29, 0xC);
			M2C_FIELD(temp_r31, f32*, 0x28) = (f32)M2C_FIELD(temp_r29, f32*, 0x28);
		}
	}
	arg0->unkCC = M2C_FIELD(arg0, void**, 0x28);
	arg0->unkD0 = (u8*)M2C_FIELD(arg0, void**, 0x28) + 0xC;
	arg0->unkD4 = arg0->unkC8;
	arg0->unkD8 = &arg0->unkE8;
	arg0->unkDC = &arg0->unkB8;
	arg0->unkE0 = &arg0->unkE4;
	sp8         = &arg0->unkCC;
	fn_8005F50C(arg0->unkC4, &sp8, 4);
	temp_r3_3 = arg0->unkBC;
	if (temp_r3_3 != NULL) {
		temp_r31_2 = M2C_FIELD(temp_r3_3, s32*, 4);
		spC        = M2C_FIELD(&lbl_8_rodata_1F78, f32*, 0);
		sp10       = M2C_FIELD(&lbl_8_rodata_1F78, f32*, 4);
		sp14       = M2C_FIELD(&lbl_8_rodata_1F78, f32*, 8);
		temp_f0    = arg0->unkE8;
		spC        = temp_f0;
		sp10       = temp_f0;
		sp14       = temp_f0;
		fn_8019EC30(temp_r31_2, &spC, 0);
		if ((s32)arg0->unkE4 == 1) {
			temp_f31 = fn_800D7B00(0x8000);
			fn_80195790(temp_r31_2 + 0x10, &lbl_80239978, 2,
			    lbl_8_rodata_1F90 - fn_800D7AE4(0x8000), temp_f31);
			fn_8019E880(temp_r31_2);
		}
		temp_f31_2 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10));
		fn_80195790(temp_r31_2 + 0x10, &lbl_80239984, 2,
		    lbl_8_rodata_1F90 - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10)),
		    temp_f31_2);
		fn_8019E880(temp_r31_2);
		temp_f31_3 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC));
		fn_80195790(temp_r31_2 + 0x10, &lbl_80239978, 2,
		    lbl_8_rodata_1F90 - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC)),
		    temp_f31_3);
		fn_8019E880(temp_r31_2);
		temp_f31_4 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14));
		fn_80195790(temp_r31_2 + 0x10, &lbl_80239990, 2,
		    lbl_8_rodata_1F90 - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14)),
		    temp_f31_4);
		fn_8019E880(temp_r31_2);
		fn_8019EB94(temp_r31_2, M2C_FIELD(arg0, void**, 0x28), 2);
		temp_r3_4 = arg0->unkC0;
		if (temp_r3_4 != NULL) {
			temp_r31_3 = M2C_FIELD(temp_r3_4, s32*, 4);
			fn_8019EC30(temp_r31_3, &spC, 0);
			if ((s32)arg0->unkE4 == 1) {
				temp_f31_5 = fn_800D7B00(0x8000);
				fn_80195790(temp_r31_3 + 0x10, &lbl_80239978, 2,
				    lbl_8_rodata_1F90 - fn_800D7AE4(0x8000), temp_f31_5);
				fn_8019E880(temp_r31_3);
			}
			temp_f31_6 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10));
			fn_80195790(temp_r31_3 + 0x10, &lbl_80239984, 2,
			    lbl_8_rodata_1F90
			        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x10)),
			    temp_f31_6);
			fn_8019E880(temp_r31_3);
			temp_f31_7 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC));
			fn_80195790(temp_r31_3 + 0x10, &lbl_80239978, 2,
			    lbl_8_rodata_1F90
			        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0xC)),
			    temp_f31_7);
			fn_8019E880(temp_r31_3);
			temp_f31_8 = fn_800D7B00(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14));
			fn_80195790(temp_r31_3 + 0x10, &lbl_80239990, 2,
			    lbl_8_rodata_1F90
			        - fn_800D7AE4(M2C_FIELD(M2C_FIELD(arg0, void**, 0x28), s32*, 0x14)),
			    temp_f31_8);
			fn_8019E880(temp_r31_3);
			fn_8019EB94(temp_r31_3, M2C_FIELD(arg0, void**, 0x28), 2);
		}
	}
	return arg0;
}

void fn_8_C8C34(void* arg0, void* arg1)
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
	if ((s8)M2C_FIELD(temp_r5, u8*, 1) >= 2) {
		M2C_FIELD(temp_r5, u8*, 1) = 1U;
	}
	if ((s8)M2C_FIELD(temp_r5, u8*, 2) < 0) {
		M2C_FIELD(temp_r5, u8*, 2) = 0U;
	}
	if ((s8)M2C_FIELD(temp_r5, u8*, 2) > 1) {
		M2C_FIELD(temp_r5, u8*, 2) = 1U;
	}
	M2C_FIELD(&s11FlagFieldNames, M2C_UNK**, 0)
	    = (M2C_UNK*)lbl_8_data_18C00[(s8)M2C_FIELD(temp_r5, u8*, 0)];
	M2C_FIELD(&s11FlagFieldNames, M2C_UNK**, 8)
	    = (M2C_UNK*)lbl_8_data_18C1C[(s8)M2C_FIELD(temp_r5, u8*, 2)];
}

void s11FlagUnload(M2C_UNK arg_sp0)
{
	s32 var_r31;
	void** var_r29;
	struct _struct_lbl_8_data_18B68_0x8* var_r28;
	void** var_r27;
	void** var_r26;
	RpDMorphAnimation** var_r25;
	s32 var_r24;

	var_r31 = 0;
	var_r28 = lbl_8_data_18B68;
	var_r27 = (void**)lbl_8_data_18B78;
	var_r26 = lbl_8_data_18B80;
	var_r25 = lbl_8_data_18B88;
	do {
		var_r24 = 0;
		var_r29 = (void**)var_r28;
	loop_2:
		if (*var_r29 != NULL) {
			fn_80150958(*var_r29);
			*var_r29 = NULL;
		}
		var_r29 += 1;
		var_r24 += 1;
		if (var_r24 < 2) {
			goto loop_2;
		}
		if ((void*)*var_r27 != NULL) {
			fn_80150958(*var_r27);
			*var_r27 = NULL;
			*var_r26 = NULL;
		}
		if ((RpDMorphAnimation*)*var_r25 != NULL) {
			fn_8013BD74(*var_r25);
			*var_r25 = NULL;
		}
		var_r28 += 1;
		var_r27 += 1;
		var_r26 += 1;
		var_r25 += 1;
		var_r31 += 1;
	} while (var_r31 < 2);
}

void s11FlagLoad(M2C_UNK arg_sp0)
{
	s32 var_r31;
	s32 temp_r30;
	const char** var_r26;
	struct _struct_lbl_8_data_18B68_0x8* var_r25;
	const char** var_r24;
	void** var_r23;
	void** var_r22;
	const char** var_r21;
	RpDMorphAnimation** var_r20;
	const char** var_r19;
	void** var_r18;
	s32 var_r17;
	RpDMorphAnimation* temp_r4;
	u32 temp_r3;

	temp_r3 = M2C_FIELD(lbl_8042C1D0, u32*, 0x8C18);
	if (temp_r3 != 0U) {
		lbl_8_bss_1CD8 = temp_r3;
	} else {
		return;
	}
	fn_801A4C84(temp_r3);
	temp_r30 = M2C_FIELD(lbl_8042C298, s32*, 0xA50);
	fn_800BC9F4(temp_r30, &lbl_802FF5A0);
	var_r31 = 0;
	var_r26 = lbl_8_data_18B58;
	var_r25 = lbl_8_data_18B68;
	var_r24 = lbl_8_data_18B00;
	var_r23 = (void**)lbl_8_data_18B78;
	var_r22 = lbl_8_data_18B80;
	var_r21 = lbl_8_data_18AD0;
	var_r20 = lbl_8_data_18B88;
	do {
		var_r17 = 0;
		var_r19 = var_r26;
		var_r18 = (void**)var_r25;
	loop_5:
		*var_r18 = fn_800BB92C(temp_r30, fn_800BC6CC(temp_r30, (M2C_UNK*)*var_r19), &lbl_802FF5A0);
		var_r19 += 1;
		var_r18 += 1;
		var_r17 += 1;
		if (var_r17 < 2) {
			goto loop_5;
		}
		*var_r23 = fn_800BB92C(temp_r30, fn_800BC6CC(temp_r30, (M2C_UNK*)*var_r24), &lbl_802FF5A0);
		fn_8014FFBC(*var_r23, fn_8_C787C, var_r22);
		*var_r20 = fn_800BB39C(temp_r30, fn_800BC6CC(temp_r30, (M2C_UNK*)*var_r21), &lbl_802FF5A0);
		temp_r4  = *var_r20;
		if (temp_r4 != NULL) {
			lbl_8_bss_1CE0
			    = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(&lbl_8042C340, temp_r4);
		}
		var_r26 += 2;
		var_r25 += 1;
		var_r24 += 1;
		var_r23 += 1;
		var_r22 += 1;
		var_r21 += 1;
		var_r20 += 1;
		var_r31 += 1;
	} while (var_r31 < 2);
}

void s11FlagCreate(void)
{
	TObject* object = (TObject*)fn_80018A34(lbl_8042C148, 0xF0);
	if (object != NULL) {
		fn_8_C8688(object, lbl_8042C110);
	}
}

void s11FlagRegister(void)
{
	s11FlagEntry.flags      = 0;
	s11FlagEntry.unk18      = 0;
	s11FlagEntry.name       = (const char*)s11FlagDisplayName;
	s11FlagEntry.load       = (void (*)(void))s11FlagLoad;
	s11FlagEntry.unload     = (void (*)(void))s11FlagUnload;
	s11FlagEntry.create     = (void (*)(void))s11FlagCreate;
	s11FlagEntry.unk10      = (void*)0;
	s11FlagEntry.flags      = 0x21000;
	s11FlagEntry.unk18      = 0;
	s11FlagEntry.unk20      = 0x14;
	s11FlagEntry.unk1C      = 0x1188;
	s11FlagEntry.unk1E      = 2;
	s11FlagEntry.unk21      = 0;
	s11FlagEntry.fieldTypes = (const char*)s11FlagFieldTypes;
	s11FlagEntry.fieldNames = (const char**)&s11FlagFieldNames;
	if ((const char*)s11FlagFieldTypes != NULL) {
		s11FlagEntry.flags |= 8;
	} else {
		s11FlagEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s11FlagCtorEntry)(void) = s11FlagRegister;
}
