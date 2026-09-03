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
	/* 0x28 */ char pad28[8];
	/* 0x30 */ u16 unk30;        /* inferred */
	/* 0x32 */ char pad32[6];    /* maybe part of unk30[4]? */
	/* 0x38 */ void* unk38;      /* inferred */
	/* 0x3C */ char pad3C[0x4C]; /* maybe part of unk38[0x14]? */
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
	/* 0xCC */ s32 unkCC;        /* inferred */
	/* 0xD0 */ s32 unkD0;        /* inferred */
	/* 0xD4 */ f32 unkD4;        /* inferred */
	/* 0xD8 */ f32 unkD8;        /* inferred */
	/* 0xDC */ f32 unkDC;        /* inferred */
	/* 0xE0 */ s32 unkE0;        /* inferred */
	/* 0xE4 */ s32 unkE4;        /* inferred */
	/* 0xE8 */ f32 unkE8;        /* inferred */
	/* 0xEC */ f32 unkEC;        /* inferred */
	/* 0xF0 */ f32 unkF0;        /* inferred */
} TObject;                       /* size >= 0xF4 */

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
};

extern "C" {

void* __ct__7TObjectFP7TObject(TObject* self, TObject* arg0);   /* extern */
M2C_UNK __dl__FPv(void* arg0);                                  /* extern */
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);         /* extern */
M2C_UNK dtor_8003C52C(void*, M2C_UNK);                          /* extern */
M2C_UNK dtor_8005BD3C(void*, M2C_UNK);                          /* extern */
s32 fn_80017800(void*);                                         /* extern */
M2C_UNK fn_800189A4(s32, TObject*);                             /* extern */
TObject* fn_80018A34(s32, M2C_UNK);                             /* extern */
void* fn_800211A8(void*);                                       /* extern */
M2C_UNK fn_80021384(M2C_UNK*);                                  /* extern */
M2C_UNK fn_80021824(M2C_UNK*);                                  /* extern */
M2C_UNK fn_8003BC38(void*);                                     /* extern */
M2C_UNK fn_8003BE78(void*);                                     /* extern */
M2C_UNK fn_8003C200(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK, ...); /* extern */
M2C_UNK fn_8003C618(M2C_UNK*);                                  /* extern */
s32 fn_8005B8BC(s32);                                           /* extern */
M2C_UNK fn_8005BC04(void*);                                     /* extern */
M2C_UNK fn_8005BE6C(f32*);                                      /* extern */
void* fn_8005EA04(const char*);                                 /* extern */
M2C_UNK fn_800A31B8(u32);                                       /* extern */
s32 fn_800A3ED4(void*);                                         /* extern */
M2C_UNK fn_800D5A64(void*, f32*, M2C_UNK*, f32);                /* extern */
f32 fn_800D71DC(void*, s32);                                    /* extern */
M2C_UNK fn_80100D24(s8*, ...);                                  /* extern */
s32 fn_80103324(void*, M2C_UNK*, f32);                          /* extern */
M2C_UNK fn_80113874(s32);                                       /* extern */
M2C_UNK fn_8014FF2C(void*);                                     /* extern */
M2C_UNK fn_801990E0(f32*, f32*, f32);                           /* extern */
s32 fn_8019CE34(s32, f32*);                                     /* extern */
M2C_UNK fn_8019EB94(s32, void*, M2C_UNK);                       /* extern */
M2C_UNK fn_8019ED68(s32, M2C_UNK*, M2C_UNK, f32);               /* extern */
s32 fn_8_B0A74(void*);                                          /* extern */
M2C_UNK fn_8_B43E8(s32);                                        /* extern */
void fn_8_B4B9C(void* arg0);
s32 fn_8_B63E4(void* arg0);
void rinoColObjectCreate(); /* static */
void rinoColObjectLoad();   /* static */
void rinoColObjectUnload(); /* static */
extern M2C_UNK lbl_80239978;
extern M2C_UNK lbl_80239984;
extern M2C_UNK lbl_80239990;
extern M2C_UNK lbl_8029C310;
extern M2C_UNK lbl_802AD090;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern M2C_UNK lbl_8042C1A4;
extern s32 lbl_8042C298;
extern s32* lbl_8042C9A4;
static M2C_UNK lbl_8_data_16FD8;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17008;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001701A_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_1701C = (M2C_UNK*)"TObjEnemyIronBall";
static M2C_UNK lbl_8_data_17020;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1704C;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001705B_data;    /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17060;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_170B0;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_170C8;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17100;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17130;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001713B_data;    /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1713C;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00017147_data;    /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17148;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00017153_data;    /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17154;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001715B_data;    /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1715C;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00017165_data;    /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17168;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00017171_data;    /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17174;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001717D_data;    /* unable to generate initializer: unknown type */
static M2C_UNK rinoColObjectFieldNames; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_171A0;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000171A6_data;    /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_171A8;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_171AC;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_171B8;        /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_171C8;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000171CF_data;    /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_171D0;        /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000171DB_data;    /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_171DC[7] = {
	(M2C_UNK*)"START",
	(M2C_UNK*)"END",
	(M2C_UNK*)"CHANGE PATH",
	(M2C_UNK*)"CHANGE PATH SET",
	(M2C_UNK*)"ATTACK",
	(M2C_UNK*)"ATTACK SET",
	(M2C_UNK*)"SPEED CTRL",
};
static M2C_UNK lbl_8_data_171F8;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000171FF_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17200;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17208;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17214;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00017225_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17228;     /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_17234[5] = { (M2C_UNK*)"ENABLE", (M2C_UNK*)"DISABLE",
	(M2C_UNK*)"DISABLE MIN", (M2C_UNK*)"DISABLE STANDARD", (M2C_UNK*)"DISABLE MAX" };
static u8 lbl_8_data_17248          = 0;
static u8 lbl_8_data_17249          = 6;
static u8 lbl_8_data_1724A          = 0;
static u8 lbl_8_data_1724B          = 4;
static M2C_UNK lbl_8_data_1724C;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00017263_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_17264 = (M2C_UNK*)"TObjColliCommunication";
static M2C_UNK lbl_8_data_17268;         /* unable to generate initializer: unknown type */
static M2C_UNK rinoColObjectDisplayName; /* unable to generate initializer: unknown type */
static M2C_UNK rinoColObjectFieldTypes;  /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000172D9_data;     /* unable to generate initializer: unknown type */
static void* lbl_8_bss_1A90;
static M2C_UNK rinoColObjectEntry;
static M2C_UNK lbl_8_rodata_1C64;
static M2C_UNK lbl_8_rodata_1C70;
static M2C_UNK lbl_8_rodata_1C74;
static M2C_UNK lbl_8_rodata_1C78;
static M2C_UNK lbl_8_rodata_1C7C;
static M2C_UNK lbl_8_rodata_1C80;
static M2C_UNK lbl_8_rodata_1CA4;
static M2C_UNK lbl_8_rodata_1CB8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CC4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CD0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CDC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CE8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1CF4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D00; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D10; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D1C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D2C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D3C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D48; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D54; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D58; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D5C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D60; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D64; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D68; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D6C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D70; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D74; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D78; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D7C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D80; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D84; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D88; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D90; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D98; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1D9C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DA0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DA4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DA8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DAC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DB0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DB4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DB8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DBC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DC0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DC4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DC8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DCC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DD0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DD4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DD8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DDC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DE0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DE4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DE8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DEC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DF0; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DF4; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DF8; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1DFC; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E00; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E04; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E08; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E0C; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E10; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E14; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E18; /* unable to generate initializer: unknown type; const */
static M2C_UNK lbl_8_rodata_1E1C; /* unable to generate initializer: unknown type; const */

void fn_8_B49D8(s32 arg0)
{
	fn_8_B43E8(arg0 - 0xB0);
}

void fn_8_B49E0(void) { }

void fn_8_B49E4(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	M2C_FIELD(arg0, s32*, 0x10) = 0;
	if (M2C_FIELD(M2C_FIELD(arg0, void**, 0), s32(**)(), 0x14)() != 0) {
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 2);
	}
	((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
		fn_800A31B8(M2C_FIELD(arg0, u32*, 0x14));
	}
}

void fn_8_B4A7C(void* arg0)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	s32 temp_r30;

	if ((void*)lbl_8_bss_1A90 != NULL) {
		sp8  = M2C_FIELD(arg0, f32*, 0xB0);
		spC  = M2C_FIELD(arg0, f32*, 0xB4);
		sp10 = M2C_FIELD(arg0, f32*, 0xB8);
		sp14 = 20.0f;
		if (fn_8019CE34(*lbl_8042C9A4, &sp8) != 0) {
			temp_r30 = M2C_FIELD(lbl_8_bss_1A90, s32*, 4);
			fn_8019ED68(temp_r30, &lbl_80239990, 0, M2C_FIELD(arg0, f32*, 0xF0));
			fn_8019ED68(temp_r30, &lbl_80239978, 2, M2C_FIELD(arg0, f32*, 0xE8));
			fn_8019ED68(temp_r30, &lbl_80239984, 2, M2C_FIELD(arg0, f32*, 0xEC));
			fn_8019EB94(temp_r30, (u8*)arg0 + 0xB0, 2);
			fn_80113874(M2C_FIELD(arg0, s32*, 0xE0));
			fn_8014FF2C(lbl_8_bss_1A90);
		}
	}
}

void fn_8_B4B88(void* arg0)
{
	M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
}

void fn_8_B4B9C(void* arg0)
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
	f32 temp_f2;
	f32 temp_f31;
	f32 temp_f3;
	s32 temp_r0;
	s32 temp_r3;
	void* temp_r30;

	temp_r0                     = M2C_FIELD(arg0, s32*, 0xD8) - 1;
	M2C_FIELD(arg0, s32*, 0xD8) = temp_r0;
	if (temp_r0 < 0) {
		M2C_FIELD(arg0, s32*, 0xE4) = 2;
		return;
	}
	if ((s32)M2C_FIELD(arg0, s32*, 0xDC) != 0) {
		temp_r3 = fn_80103324((u8*)arg0 + 0xB0, &lbl_8_rodata_1C74, 1e8f);
		if (temp_r3 != -1) {
			temp_r30 = *(void**)((u8*)&lbl_802AD090 + (temp_r3 * 4));
			if (temp_r30 != NULL) {
				if (fn_800D71DC((u8*)arg0 + 0xB0, (s32)((u8*)temp_r30 + 0x18)) < 2500.0f) {
					M2C_FIELD(arg0, s32*, 0xDC) = 0;
				}
				sp14    = M2C_FIELD(temp_r30, f32*, 0x18) - M2C_FIELD(arg0, f32*, 0xB0);
				sp18    = M2C_FIELD(temp_r30, f32*, 0x1C) - M2C_FIELD(arg0, f32*, 0xB4);
				temp_f1 = M2C_FIELD(temp_r30, f32*, 0x20);
				sp1C    = temp_f1 - M2C_FIELD(arg0, f32*, 0xB8);
				fn_801990E0(&sp14, &sp14, temp_f1);
				temp_f31 = M2C_FIELD(arg0, f32*, 0xC0);
				if (((M2C_FIELD(arg0, f32*, 0xC4) * sp1C)
				        + ((M2C_FIELD(arg0, f32*, 0xBC) * sp14) + (temp_f31 * sp18)))
				    > 0.0f) {
					fn_800D5A64((u8*)arg0 + 0xBC, &sp14, &lbl_8_rodata_1C80, 0.05f);
					M2C_FIELD(arg0, f32*, 0xC0) = temp_f31;
				} else {
					M2C_FIELD(arg0, s32*, 0xDC) = 0;
				}
			}
		}
	}
	sp8                         = M2C_FIELD(arg0, f32*, 0xBC);
	spC                         = M2C_FIELD(arg0, f32*, 0xC0);
	sp10                        = M2C_FIELD(arg0, f32*, 0xC4);
	temp_f1_2                   = M2C_FIELD(arg0, f32*, 0xC8);
	temp_f3                     = sp8 * temp_f1_2;
	sp8                         = temp_f3;
	temp_f2                     = spC * temp_f1_2;
	spC                         = temp_f2;
	temp_f1_3                   = sp10 * temp_f1_2;
	sp10                        = temp_f1_3;
	M2C_FIELD(arg0, f32*, 0xB0) = (f32)(M2C_FIELD(arg0, f32*, 0xB0) + temp_f3);
	M2C_FIELD(arg0, f32*, 0xB4) = (f32)(M2C_FIELD(arg0, f32*, 0xB4) + temp_f2);
	M2C_FIELD(arg0, f32*, 0xB8) = (f32)(M2C_FIELD(arg0, f32*, 0xB8) + temp_f1_3);
	M2C_FIELD(arg0, f32*, 0xE8) = (f32)(M2C_FIELD(arg0, f32*, 0xE8) + 0.0f);
	M2C_FIELD(arg0, f32*, 0xEC)
	    = (f32)(M2C_FIELD(arg0, f32*, 0xEC) + M2C_FIELD(&lbl_8_rodata_1C64, f32*, 4));
	M2C_FIELD(arg0, f32*, 0xF0)
	    = (f32)(M2C_FIELD(arg0, f32*, 0xF0) + M2C_FIELD(&lbl_8_rodata_1C64, f32*, 8));
}

void fn_8_B4DA4(void* arg0)
{
	M2C_FIELD(arg0, s32*, 0xE4) = 1;
}

void fn_8_B4DB0(void* arg0)
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
	temp_r0 = M2C_FIELD(arg0, s32*, 0xE4);
	switch (temp_r0) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0xE4) = 1;
			break;
		case 1:
			fn_8_B4B9C(arg0);
			break;
		case 2:
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
		M2C_FIELD(arg0, s32*, 0x94) = (s32)M2C_FIELD(arg0, s32*, 0xCC);
		M2C_FIELD(arg0, s32*, 0x98) = (s32)M2C_FIELD(arg0, s32*, 0xD0);
		M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(arg0, s32*, 0xD4);
		fn_8003BC38((u8*)arg0 + 0x28);
	}
}

TObject* fn_8_B4F70(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_17020;
		dtor_8003C52C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_B4FF4(TObject* arg0, TObject* arg1, void* arg2)
{
	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8003C618(&arg0->unk28);
	arg0->unk18 = &lbl_8_data_17020;
	arg0->unkB8 = 0.0f;
	arg0->unkB4 = 0.0f;
	arg0->unkB0 = 0.0f;
	arg0->unkC4 = 0.0f;
	arg0->unkC0 = 0.0f;
	arg0->unkBC = 0.0f;
	arg0->unkD4 = 0.0f;
	arg0->unkD0 = 0;
	arg0->unkCC = 0;
	arg0->unkD8 = 4.2e-43f;
	arg0->unkDC = 1e-45f;
	arg0->unkE0 = 8;
	arg0->unk0  = lbl_8_data_1701C;
	arg0->unk1E = 0xF4;
	arg0->unkE4 = 0;
	arg0->unkB0 = M2C_FIELD(arg2, f32*, 0);
	arg0->unkB4 = M2C_FIELD(arg2, f32*, 4);
	arg0->unkB8 = M2C_FIELD(arg2, f32*, 8);
	arg0->unkBC = M2C_FIELD(arg2, f32*, 0xC);
	arg0->unkC0 = M2C_FIELD(arg2, f32*, 0x10);
	arg0->unkC4 = M2C_FIELD(arg2, f32*, 0x14);
	arg0->unkC8 = M2C_FIELD(arg2, f32*, 0x18);
	arg0->unkCC = M2C_FIELD(arg2, s32*, 0x1C);
	arg0->unkD0 = M2C_FIELD(arg2, s32*, 0x20);
	arg0->unkD4 = M2C_FIELD(arg2, f32*, 0x24);
	arg0->unkD8 = M2C_FIELD(arg2, f32*, 0x28);
	arg0->unkDC = M2C_FIELD(arg2, f32*, 0x2C);
	arg0->unkE0 = M2C_FIELD(arg2, s32*, 0x30);
	arg0->unkF0 = 0.0f;
	arg0->unkEC = 0.0f;
	arg0->unkE8 = 0.0f;
	fn_8003C200(&arg0->unk28, &lbl_8_data_16FD8, 1, 3, 0.0f);
	arg0->unk88 = arg0->unkB0;
	arg0->unk8C = arg0->unkB4;
	arg0->unk90 = arg0->unkB8;
	arg0->unk30 &= 0xFFFFFFBF;
	return arg0;
}

void fn_8_B5160(void* arg0)
{
	TObject* temp_r3;

	temp_r3 = fn_80018A34(lbl_8042C148, 0xF4);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		fn_8003C618(&temp_r3->unk28);
		temp_r3->unk18 = &lbl_8_data_17020;
		temp_r3->unkB8 = 0.0f;
		temp_r3->unkB4 = 0.0f;
		temp_r3->unkB0 = 0.0f;
		temp_r3->unkC4 = 0.0f;
		temp_r3->unkC0 = 0.0f;
		temp_r3->unkBC = 0.0f;
		temp_r3->unkD4 = 0.0f;
		temp_r3->unkD0 = 0;
		temp_r3->unkCC = 0;
		temp_r3->unkD8 = 4.2e-43f;
		temp_r3->unkDC = 1e-45f;
		temp_r3->unkE0 = 8;
		temp_r3->unk0  = lbl_8_data_1701C;
		temp_r3->unk1E = 0xF4;
		temp_r3->unkE4 = 0;
		temp_r3->unkB0 = M2C_FIELD(arg0, f32*, 0);
		temp_r3->unkB4 = M2C_FIELD(arg0, f32*, 4);
		temp_r3->unkB8 = M2C_FIELD(arg0, f32*, 8);
		temp_r3->unkBC = M2C_FIELD(arg0, f32*, 0xC);
		temp_r3->unkC0 = M2C_FIELD(arg0, f32*, 0x10);
		temp_r3->unkC4 = M2C_FIELD(arg0, f32*, 0x14);
		temp_r3->unkC8 = M2C_FIELD(arg0, f32*, 0x18);
		temp_r3->unkCC = M2C_FIELD(arg0, s32*, 0x1C);
		temp_r3->unkD0 = M2C_FIELD(arg0, s32*, 0x20);
		temp_r3->unkD4 = M2C_FIELD(arg0, f32*, 0x24);
		temp_r3->unkD8 = M2C_FIELD(arg0, f32*, 0x28);
		temp_r3->unkDC = M2C_FIELD(arg0, f32*, 0x2C);
		temp_r3->unkE0 = M2C_FIELD(arg0, s32*, 0x30);
		temp_r3->unkF0 = 0.0f;
		temp_r3->unkEC = 0.0f;
		temp_r3->unkE8 = 0.0f;
		fn_8003C200(&temp_r3->unk28, &lbl_8_data_16FD8, 1, 3, 0.0f);
		temp_r3->unk88 = temp_r3->unkB0;
		temp_r3->unk8C = temp_r3->unkB4;
		temp_r3->unk90 = temp_r3->unkB8;
		temp_r3->unk30 &= 0xFFFFFFBF;
	}
}

void fn_8_B52F4(void)
{
	lbl_8_bss_1A90 = NULL;
}

void fn_8_B5308(void)
{
	lbl_8_bss_1A90 = fn_8005EA04("OBJ_SPIKEB.DFF");
}

void fn_8_B533C(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18)
			    = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x2B0);
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			return;
		case 1:
			if (fn_8_B0A74(M2C_FIELD(arg0, void**, 0x14)) != 0) {
				temp_r0                     = M2C_FIELD(arg0, s32*, 0x18) - 1;
				M2C_FIELD(arg0, s32*, 0x18) = temp_r0;
				if (temp_r0 < 0) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 2;
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				}
			}
			return;
	}
}

void fn_8_B5408(void* arg0, s32 arg1)
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

void fn_8_B5428(void* arg0, s32 arg1)
{
	s32 temp_r0;
	s32 temp_r31;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x1C) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			return;
		case 1:
			temp_r0                     = M2C_FIELD(arg0, s32*, 0x1C) - 1;
			M2C_FIELD(arg0, s32*, 0x1C) = temp_r0;
			if (temp_r0 < 0) {
				temp_r31                 = M2C_FIELD(arg0, s32*, 8);
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = temp_r31;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_B54E4(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x26;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B5504(void* arg0, s32 arg1)
{
	s32 temp_r0;
	s32 temp_r31;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 1;
			M2C_FIELD(arg0, s32*, 0x10) = 0x20;
			return;
		case 1:
			temp_r0                     = M2C_FIELD(arg0, s32*, 0x18) - 1;
			M2C_FIELD(arg0, s32*, 0x18) = temp_r0;
			if (temp_r0 < 0) {
				temp_r31                 = M2C_FIELD(arg0, s32*, 8);
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = temp_r31;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_B55C0(void* arg0, s32 arg1)
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

void fn_8_B55E0(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x27;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B5600(void* arg0, s32 arg1)
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

void fn_8_B5620(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	if ((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, s32*, 0xC)  = 0;
		M2C_FIELD(arg0, s32*, 0x10) = 0;
		M2C_FIELD(arg0, s32*, 4)    = 0;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
			fn_800A31B8(M2C_FIELD(arg0, u32*, 0x14));
		}
	}
}

s32 fn_8_B5694(void* arg0)
{
	s32 temp_r0;
	s32 temp_r0_2;
	s32 var_r3;
	void* temp_r3;

	if ((fn_800A3ED4(M2C_FIELD(arg0, void**, 0x14)) != 0)
	    && ((s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x19C) != 0x1D)) {
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 6;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	temp_r3 = M2C_FIELD(arg0, void**, 0x14);
	temp_r0 = M2C_FIELD(temp_r3, s32*, 0x240);
	if (temp_r0 != 0) {
		var_r3 = 0;
		switch (temp_r0) { /* irregular */
			case 1:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 2:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 38:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 29:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 6;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 39:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 4;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 32:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 2;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x240) = 0;
		return var_r3;
	}
	if ((u32)(M2C_FIELD(temp_r3, s32*, 0x18C) & 0x2000) != 0) {
		temp_r0_2 = M2C_FIELD(temp_r3, s32*, 0x19C);
		if (temp_r0_2 < 3) {
			if (temp_r0_2 < 1) {
				goto block_28;
			}
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 5;
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			return 1;
		}
	block_28:
		return 0;
	}
	return 0;
}

void fn_8_B59F8(void** arg0, u32 arg1, s32 arg2)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x18)(arg2);
			return;
		case 4:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x1C)(arg2);
			return;
		case 1:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x20)(arg2);
			return;
		case 3:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x28)(arg2);
			return;
		case 2:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x24)(arg2);
			return;
		case 5:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x2C)(arg2);
			return;
		case 6:
			M2C_FIELD(*arg0, M2C_UNK(**)(s32), 0x30)(arg2);
			/* fallthrough */
		default:
			return;
	}
}

M2C_UNK** fn_8_B5AD8(M2C_UNK** arg0, s16 arg1)
{
	s32 temp_cr0_eq;

	temp_cr0_eq = arg0 == NULL;
	if (temp_cr0_eq == 0) {
		*arg0 = &lbl_8_data_170C8;
		if (temp_cr0_eq == 0) {
			*arg0 = &lbl_8_data_170B0;
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_B5B3C(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_170B0;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_170C8;
	M2C_FIELD(arg0, s32*, 0x18)   = 0;
}

M2C_UNK** fn_8_B5B74(M2C_UNK** arg0, s16 arg1)
{
	s32 temp_cr0_eq;

	temp_cr0_eq = arg0 == NULL;
	if (temp_cr0_eq == 0) {
		*arg0 = &lbl_8_data_17060;
		if (temp_cr0_eq == 0) {
			*arg0 = &lbl_8_data_170C8;
			if (temp_cr0_eq == 0) {
				*arg0 = &lbl_8_data_170B0;
			}
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

M2C_UNK** fn_8_B5BE8(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = &lbl_8_data_170B0;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

s32 fn_8_B5C38(void* arg0)
{
	void* temp_r0;
	void* var_r3;

	if (fn_8005B8BC((s32)((u8*)arg0 + 0xB0)) != 0) {
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
	if ((u16)M2C_FIELD(var_r3, u16*, 0x28) == 0x1590) {
		return 0;
	}
	var_r3 = M2C_FIELD(var_r3, void**, 0x38);
	goto loop_8;
}

s32 fn_8_B5CD4(void* arg0)
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
			if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x16)) {
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

s32 fn_8_B5D28(void* arg0)
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

s32 fn_8_B5D9C(void* arg0)
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
	void* temp_r5;
	void* temp_r6;
	void* var_r5;

	if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
	    && (var_r5 = arg0, temp_r0 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr = temp_r0,
	        ((temp_r0 > 0) != 0))) {
	loop_2:
		temp_r4 = M2C_FIELD(var_r5, void**, 0x40);
		if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x16)) {
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
		temp_r5 = M2C_FIELD(arg0, void**, 0xB0);
		if (temp_r5 != NULL) {
			temp_r6 = M2C_FIELD(temp_r5, void**, 0x2C);
			sp8     = 0;
			sp9     = 0;
			sp8     = 4;
			spC     = 0;
			sp18    = 0.0f;
			sp14    = 0.0f;
			sp10    = 0.0f;
			sp1C    = 0;
			sp9     = M2C_FIELD(temp_r5, u8*, 0x2A);
			spC     = 7;
			sp1C    = (s32)(s8)M2C_FIELD(temp_r6, u8*, 1);
			fn_80100D24(&sp8, NULL, temp_r6);
		}
	}
	return var_r31;
}

s32 fn_8_B5E88(void* arg0)
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
		if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x16)) {
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
			sp8  = 4;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp9  = M2C_FIELD(temp_r6, u8*, 0x2A);
			spC  = 6;
			sp10 = M2C_FIELD(arg0, f32*, 0xD4);
			sp14 = M2C_FIELD(arg0, f32*, 0xD8);
			sp18 = M2C_FIELD(arg0, f32*, 0xDC);
			fn_80100D24(&sp8, &lbl_8_rodata_1CA4, NULL);
		}
	}
	return var_r31;
}

s32 fn_8_B5F7C(void* arg0)
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
	void* temp_r5;
	void* var_r5;

	if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
	    && (var_r5 = arg0, temp_r0 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr = temp_r0,
	        ((temp_r0 > 0) != 0))) {
	loop_2:
		temp_r4 = M2C_FIELD(var_r5, void**, 0x40);
		if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x16)) {
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
		temp_r5 = M2C_FIELD(arg0, void**, 0xB0);
		if (temp_r5 != NULL) {
			sp8  = 0;
			sp9  = 0;
			sp8  = 4;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp9  = M2C_FIELD(temp_r5, u8*, 0x2A);
			spC  = 5;
			fn_80100D24(&sp8, NULL);
		}
	}
	return var_r31;
}

s32 fn_8_B6058(void* arg0)
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
		if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x16)) {
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
			sp8  = 4;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp9  = M2C_FIELD(temp_r6, u8*, 0x2A);
			spC  = 4;
			sp10 = M2C_FIELD(arg0, f32*, 0xD4);
			sp14 = M2C_FIELD(arg0, f32*, 0xD8);
			sp18 = M2C_FIELD(arg0, f32*, 0xDC);
			fn_80100D24(&sp8, &lbl_8_rodata_1CA4, (void*)4);
		}
	}
	return var_r31;
}

s32 fn_8_B6148(void* arg0)
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
	void* temp_r5;
	void* var_r5;

	if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
	    && (var_r5 = arg0, temp_r0 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr = temp_r0,
	        ((temp_r0 > 0) != 0))) {
	loop_2:
		temp_r4 = M2C_FIELD(var_r5, void**, 0x40);
		if ((temp_r4 != NULL) && ((u8)*M2C_FIELD(temp_r4, u8**, 0x10) == 0x16)) {
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
		temp_r5 = M2C_FIELD(arg0, void**, 0xB0);
		if (temp_r5 != NULL) {
			sp8  = 0;
			sp9  = 0;
			sp8  = 4;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp9  = M2C_FIELD(temp_r5, u8*, 0x2A);
			spC  = 3;
			fn_80100D24(&sp8, NULL);
		}
	}
	return var_r31;
}

s32 fn_8_B6224(void* arg0)
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
			sp8  = 4;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp9  = M2C_FIELD(temp_r5, u8*, 0x2A);
			spC  = 2;
			fn_80100D24(&sp8, NULL);
		}
	}
	return var_r31;
}

s32 fn_8_B6304(void* arg0)
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
			sp8  = 4;
			spC  = 0;
			sp18 = 0.0f;
			sp14 = 0.0f;
			sp10 = 0.0f;
			sp1C = 0;
			sp9  = M2C_FIELD(temp_r5, u8*, 0x2A);
			spC  = 1;
			fn_80100D24(&sp8, NULL);
		}
	}
	return var_r31;
}

s32 fn_8_B63E4(void* arg0)
{
	s32 spAC;
	f32 spA8;
	f32 spA4;
	f32 spA0;
	s32 sp9C;
	u8 sp99;
	s8 sp98;
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
	s16 temp_r0_6;
	s16 var_ctr;
	s16 var_ctr_2;
	s16 var_ctr_3;
	s16 var_ctr_4;
	s16 var_ctr_5;
	s32 var_r30;
	s32 var_r30_2;
	s32 var_r30_3;
	s32 var_r30_4;
	s32 var_r30_5;
	s32 var_r30_6;
	s32 var_r30_7;
	u32 var_r0;
	u32 var_r0_2;
	u8 temp_r0;
	void* temp_r3;
	void* temp_r3_2;
	void* temp_r3_3;
	void* temp_r3_4;
	void* temp_r3_5;
	void* temp_r3_6;
	void* temp_r3_7;
	void* temp_r5;
	void* temp_r5_2;
	void* temp_r5_3;
	void* temp_r5_4;
	void* temp_r5_5;
	void* temp_r5_6;
	void* temp_r5_7;
	void* temp_r6;
	void* var_r4;
	void* var_r4_2;
	void* var_r4_3;
	void* var_r4_4;
	void* var_r4_5;

	temp_r0 = M2C_FIELD(arg0, u8*, 0xD0);
	if ((u32)(s8)temp_r0 <= 6U) {
		switch ((s8)temp_r0) {
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
						goto block_8;
					}
				} else {
				block_8:
					var_r30 = 0;
				}
				if (var_r30 != 0) {
					temp_r5 = M2C_FIELD(arg0, void**, 0xB0);
					if (temp_r5 != NULL) {
						sp98 = 0;
						sp99 = 0;
						sp98 = 4;
						sp9C = 0;
						spA8 = 0.0f;
						spA4 = 0.0f;
						spA0 = 0.0f;
						spAC = 0;
						sp99 = M2C_FIELD(temp_r5, u8*, 0x2A);
						sp9C = 1;
						fn_80100D24(&sp98, NULL);
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
						goto block_19;
					}
				} else {
				block_19:
					var_r30_2 = 0;
				}
				if (var_r30_2 != 0) {
					temp_r5_2 = M2C_FIELD(arg0, void**, 0xB0);
					if (temp_r5_2 != NULL) {
						sp80 = 0;
						sp81 = 0;
						sp80 = 4;
						sp84 = 0;
						sp90 = 0.0f;
						sp8C = 0.0f;
						sp88 = 0.0f;
						sp94 = 0;
						sp81 = M2C_FIELD(temp_r5_2, u8*, 0x2A);
						sp84 = 2;
						fn_80100D24(&sp80, NULL);
					}
				}
				return var_r30_2;
			case 2:
				if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
				    && (var_r4 = arg0, temp_r0_2 = M2C_FIELD(arg0, s16*, 0x2A), var_ctr = temp_r0_2,
				        ((temp_r0_2 > 0) != 0))) {
				loop_26:
					temp_r3_3 = M2C_FIELD(var_r4, void**, 0x40);
					if ((temp_r3_3 != NULL) && ((u8)*M2C_FIELD(temp_r3_3, u8**, 0x10) == 0x16)) {
						var_r30_3 = 1;
					} else {
						var_r4 = (u8*)var_r4 + 8;
						var_ctr -= 1;
						if (var_ctr == 0) {
							goto block_30;
						}
						goto loop_26;
					}
				} else {
				block_30:
					var_r30_3 = 0;
				}
				if (var_r30_3 != 0) {
					temp_r5_3 = M2C_FIELD(arg0, void**, 0xB0);
					if (temp_r5_3 != NULL) {
						sp68 = 0;
						sp69 = 0;
						sp68 = 4;
						sp6C = 0;
						sp78 = 0.0f;
						sp74 = 0.0f;
						sp70 = 0.0f;
						sp7C = 0;
						sp69 = M2C_FIELD(temp_r5_3, u8*, 0x2A);
						sp6C = 5;
						fn_80100D24(&sp68, NULL);
					}
				}
				return var_r30_3;
			case 4:
				if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
				    && (var_r4_2 = arg0, temp_r0_3 = M2C_FIELD(arg0, s16*, 0x2A),
				        var_ctr_2 = temp_r0_3, ((temp_r0_3 > 0) != 0))) {
				loop_37:
					temp_r3_4 = M2C_FIELD(var_r4_2, void**, 0x40);
					if ((temp_r3_4 != NULL) && ((u8)*M2C_FIELD(temp_r3_4, u8**, 0x10) == 0x16)) {
						var_r30_4 = 1;
					} else {
						var_r4_2 = (u8*)var_r4_2 + 8;
						var_ctr_2 -= 1;
						if (var_ctr_2 == 0) {
							goto block_41;
						}
						goto loop_37;
					}
				} else {
				block_41:
					var_r30_4 = 0;
				}
				if (var_r30_4 != 0) {
					temp_r5_4 = M2C_FIELD(arg0, void**, 0xB0);
					if (temp_r5_4 != NULL) {
						sp50 = 0;
						sp51 = 0;
						sp50 = 4;
						sp54 = 0;
						sp60 = 0.0f;
						sp5C = 0.0f;
						sp58 = 0.0f;
						sp64 = 0;
						sp51 = M2C_FIELD(temp_r5_4, u8*, 0x2A);
						sp54 = 3;
						fn_80100D24(&sp50, NULL);
					}
				}
				return var_r30_4;
			case 3:
				if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
				    && (var_r4_3 = arg0, temp_r0_4 = M2C_FIELD(arg0, s16*, 0x2A),
				        var_ctr_3 = temp_r0_4, ((temp_r0_4 > 0) != 0))) {
				loop_48:
					temp_r3_5 = M2C_FIELD(var_r4_3, void**, 0x40);
					if ((temp_r3_5 != NULL) && ((u8)*M2C_FIELD(temp_r3_5, u8**, 0x10) == 0x16)) {
						var_r30_5 = 1;
					} else {
						var_r4_3 = (u8*)var_r4_3 + 8;
						var_ctr_3 -= 1;
						if (var_ctr_3 == 0) {
							goto block_52;
						}
						goto loop_48;
					}
				} else {
				block_52:
					var_r30_5 = 0;
				}
				if (var_r30_5 != 0) {
					temp_r5_5 = M2C_FIELD(arg0, void**, 0xB0);
					if (temp_r5_5 != NULL) {
						sp38 = 0;
						sp39 = 0;
						sp38 = 4;
						sp3C = 0;
						sp48 = 0.0f;
						sp44 = 0.0f;
						sp40 = 0.0f;
						sp4C = 0;
						sp39 = M2C_FIELD(temp_r5_5, u8*, 0x2A);
						sp3C = 6;
						sp40 = M2C_FIELD(arg0, f32*, 0xD4);
						sp44 = M2C_FIELD(arg0, f32*, 0xD8);
						sp48 = M2C_FIELD(arg0, f32*, 0xDC);
						fn_80100D24(&sp38, NULL);
					}
				}
				return var_r30_5;
			case 5:
				if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
				    && (var_r4_4 = arg0, temp_r0_5 = M2C_FIELD(arg0, s16*, 0x2A),
				        var_ctr_4 = temp_r0_5, ((temp_r0_5 > 0) != 0))) {
				loop_59:
					temp_r3_6 = M2C_FIELD(var_r4_4, void**, 0x40);
					if ((temp_r3_6 != NULL) && ((u8)*M2C_FIELD(temp_r3_6, u8**, 0x10) == 0x16)) {
						var_r30_6 = 1;
					} else {
						var_r4_4 = (u8*)var_r4_4 + 8;
						var_ctr_4 -= 1;
						if (var_ctr_4 == 0) {
							goto block_63;
						}
						goto loop_59;
					}
				} else {
				block_63:
					var_r30_6 = 0;
				}
				if (var_r30_6 != 0) {
					temp_r5_6 = M2C_FIELD(arg0, void**, 0xB0);
					if (temp_r5_6 != NULL) {
						sp20 = 0;
						sp21 = 0;
						sp20 = 4;
						sp24 = 0;
						sp30 = 0.0f;
						sp2C = 0.0f;
						sp28 = 0.0f;
						sp34 = 0;
						sp21 = M2C_FIELD(temp_r5_6, u8*, 0x2A);
						sp24 = 4;
						sp28 = M2C_FIELD(arg0, f32*, 0xD4);
						sp2C = M2C_FIELD(arg0, f32*, 0xD8);
						sp30 = M2C_FIELD(arg0, f32*, 0xDC);
						fn_80100D24(&sp20, (M2C_UNK*)4);
					}
				}
				return var_r30_6;
			case 6:
				if (((s32)(M2C_FIELD(arg0, u16*, 0x30) & 1) != 0)
				    && (var_r4_5 = arg0, temp_r0_6 = M2C_FIELD(arg0, s16*, 0x2A),
				        var_ctr_5 = temp_r0_6, ((temp_r0_6 > 0) != 0))) {
				loop_70:
					temp_r3_7 = M2C_FIELD(var_r4_5, void**, 0x40);
					if ((temp_r3_7 != NULL) && ((u8)*M2C_FIELD(temp_r3_7, u8**, 0x10) == 0x16)) {
						var_r30_7 = 1;
					} else {
						var_r4_5 = (u8*)var_r4_5 + 8;
						var_ctr_5 -= 1;
						if (var_ctr_5 == 0) {
							goto block_74;
						}
						goto loop_70;
					}
				} else {
				block_74:
					var_r30_7 = 0;
				}
				if (var_r30_7 != 0) {
					temp_r6 = M2C_FIELD(arg0, void**, 0xB0);
					if (temp_r6 != NULL) {
						temp_r5_7 = M2C_FIELD(temp_r6, void**, 0x2C);
						sp8       = 0;
						sp9       = 0;
						sp8       = 4;
						spC       = 0;
						sp18      = 0.0f;
						sp14      = 0.0f;
						sp10      = 0.0f;
						sp1C      = 0;
						sp9       = M2C_FIELD(temp_r6, u8*, 0x2A);
						spC       = 7;
						sp1C      = (s32)(s8)M2C_FIELD(temp_r5_7, u8*, 1);
						fn_80100D24(&sp8, NULL, temp_r5_7);
					}
				}
				return var_r30_7;
		}
	} else {
		return 0;
	}
}

void fn_8_B6990(void) { }

void fn_8_B6994(void) { }

void fn_8_B6998(void* arg0)
{
	s32 var_r0;
	s32 var_r0_2;
	void* var_r3;

	if (fn_8005B8BC((s32)((u8*)arg0 + 0xB0)) != 0) {
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
			} else if ((u16)M2C_FIELD(var_r3, u16*, 0x28) == 0x1590) {
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
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0_2 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0_2 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0_2 = 0;
	} else {
		var_r0_2 = 1;
	}
	if (var_r0_2 == 0) {
		fn_8003BE78((u8*)arg0 + 0x28);
		return;
	}
	if (fn_8_B63E4(arg0) != 0) {
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

void fn_8_B6B40(void* arg0)
{
	if ((void*)M2C_FIELD(arg0, void**, 0x38) != NULL) {
		M2C_FIELD(arg0, f32*, 0x88) = (f32)M2C_FIELD(arg0, f32*, 0xB8);
		M2C_FIELD(arg0, f32*, 0x8C) = (f32)M2C_FIELD(arg0, f32*, 0xBC);
		M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0xC0);
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x38), f32*, 0x14)
		    = (f32)M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), void**, 0x2C), f32*, 4);
	}
	fn_80021384((M2C_UNK*)((u8*)arg0 + 0x28));
}

void fn_8_B6B9C(void* arg0)
{
	void* temp_r4;
	void* temp_r4_2;
	void* temp_r4_3;

	temp_r4                     = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), void**, 0x2C);
	M2C_FIELD(arg0, u8*, 0xD0)  = (u8)M2C_FIELD(temp_r4, u8*, 0);
	M2C_FIELD(arg0, f32*, 0xD4) = (f32)M2C_FIELD(temp_r4, f32*, 8);
	M2C_FIELD(arg0, f32*, 0xD8) = (f32)M2C_FIELD(temp_r4, f32*, 0xC);
	M2C_FIELD(arg0, f32*, 0xDC) = (f32)M2C_FIELD(temp_r4, f32*, 0x10);
	temp_r4_2                   = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, f32*, 0xB8) = (f32)M2C_FIELD(temp_r4_2, f32*, 0);
	M2C_FIELD(arg0, f32*, 0xBC) = (f32)M2C_FIELD(temp_r4_2, f32*, 4);
	M2C_FIELD(arg0, f32*, 0xC0) = (f32)M2C_FIELD(temp_r4_2, f32*, 8);
	temp_r4_3                   = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, s32*, 0xC4) = (s32)M2C_FIELD(temp_r4_3, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0xC8) = (s32)M2C_FIELD(temp_r4_3, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0xCC) = (s32)M2C_FIELD(temp_r4_3, s32*, 0x14);
}

void fn_8_B6C00(void) { }

TObject* fn_8_B6C04(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_17268;
		arg0->unkB4 = (f32)(u32)((u8*)&lbl_8_data_17268 + 0x2C);
		dtor_8005BD3C((u8*)arg0 + 0xB0, 0);
		dtor_8003C52C((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			fn_800189A4(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_B6C9C(TObject* arg0, TObject* arg1)
{
	f32 temp_r3_2;
	f32 temp_r3_3;
	void* temp_r3;

	__ct__7TObjectFP7TObject(arg0, arg1);
	fn_8003C618(&arg0->unk28);
	fn_8005BE6C(&arg0->unkB0);
	arg0->unk18                = &lbl_8_data_17268;
	arg0->unkB4                = (f32)(u32)((u8*)&lbl_8_data_17268 + 0x2C);
	arg0->unk0                 = lbl_8_data_17264;
	arg0->unk1E                = 0xE0;
	temp_r3                    = M2C_FIELD(arg0->unkB0, void**, 0x2C);
	M2C_FIELD(arg0, u8*, 0xD0) = (u8)M2C_FIELD(temp_r3, u8*, 0);
	arg0->unkD4                = M2C_FIELD(temp_r3, f32*, 8);
	arg0->unkD8                = M2C_FIELD(temp_r3, f32*, 0xC);
	arg0->unkDC                = M2C_FIELD(temp_r3, f32*, 0x10);
	temp_r3_2                  = arg0->unkB0;
	arg0->unkB8                = M2C_FIELD(temp_r3_2, f32*, 0);
	arg0->unkBC                = M2C_FIELD(temp_r3_2, f32*, 4);
	arg0->unkC0                = M2C_FIELD(temp_r3_2, f32*, 8);
	temp_r3_3                  = arg0->unkB0;
	arg0->unkC4                = M2C_FIELD(temp_r3_3, f32*, 0xC);
	arg0->unkC8                = M2C_FIELD(temp_r3_3, f32*, 0x10);
	arg0->unkCC                = M2C_FIELD(temp_r3_3, s32*, 0x14);
	fn_8003C200(&arg0->unk28, &lbl_8_data_17100, 1, 4);
	if ((void*)arg0->unk38 != NULL) {
		arg0->unk88 = arg0->unkB8;
		arg0->unk8C = arg0->unkBC;
		arg0->unk90 = arg0->unkC0;
		M2C_FIELD(arg0->unk38, f32*, 0x14)
		    = (f32)M2C_FIELD(M2C_FIELD(arg0->unkB0, void**, 0x2C), f32*, 4);
	}
	fn_80021384(&arg0->unk28);
	return arg0;
}

TObject* fn_8_B6DC0(void)
{
	TObject* temp_r3;
	f32 temp_r3_3;
	f32 temp_r3_4;
	void* temp_r3_2;

	temp_r3 = fn_80018A34(lbl_8042C148, 0xE0);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		fn_8003C618(&temp_r3->unk28);
		fn_8005BE6C(&temp_r3->unkB0);
		temp_r3->unk18                = &lbl_8_data_17268;
		temp_r3->unkB4                = (f32)(u32)((u8*)&lbl_8_data_17268 + 0x2C);
		temp_r3->unk0                 = lbl_8_data_17264;
		temp_r3->unk1E                = 0xE0;
		temp_r3_2                     = M2C_FIELD(temp_r3->unkB0, void**, 0x2C);
		M2C_FIELD(temp_r3, u8*, 0xD0) = (u8)M2C_FIELD(temp_r3_2, u8*, 0);
		temp_r3->unkD4                = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3->unkD8                = M2C_FIELD(temp_r3_2, f32*, 0xC);
		temp_r3->unkDC                = M2C_FIELD(temp_r3_2, f32*, 0x10);
		temp_r3_3                     = temp_r3->unkB0;
		temp_r3->unkB8                = M2C_FIELD(temp_r3_3, f32*, 0);
		temp_r3->unkBC                = M2C_FIELD(temp_r3_3, f32*, 4);
		temp_r3->unkC0                = M2C_FIELD(temp_r3_3, f32*, 8);
		temp_r3_4                     = temp_r3->unkB0;
		temp_r3->unkC4                = M2C_FIELD(temp_r3_4, f32*, 0xC);
		temp_r3->unkC8                = M2C_FIELD(temp_r3_4, f32*, 0x10);
		temp_r3->unkCC                = M2C_FIELD(temp_r3_4, s32*, 0x14);
		fn_8003C200(&temp_r3->unk28, &lbl_8_data_17100, 1, 4);
		if ((void*)temp_r3->unk38 != NULL) {
			temp_r3->unk88 = temp_r3->unkB8;
			temp_r3->unk8C = temp_r3->unkBC;
			temp_r3->unk90 = temp_r3->unkC0;
			M2C_FIELD(temp_r3->unk38, f32*, 0x14)
			    = (f32)M2C_FIELD(M2C_FIELD(temp_r3->unkB0, void**, 0x2C), f32*, 4);
		}
		fn_80021384(&temp_r3->unk28);
	}
	return temp_r3;
}

void fn_8_B6F14(void* arg0, void* arg1)
{
	u8* temp_r3;
	u8* var_r5;
	u8* var_r5_2;
	u8 temp_r0;
	u8 temp_r0_2;

	temp_r3 = M2C_FIELD(arg1, u8**, 0x2C);
	temp_r0 = M2C_FIELD(temp_r3, u8*, 0);
	var_r5  = &lbl_8_data_17248;
	if ((s8)temp_r0 < (s8)lbl_8_data_17248) {

	} else {
		var_r5 = &lbl_8_data_17249;
		if ((s8)temp_r0 > (s8)lbl_8_data_17249) {

		} else {
			var_r5 = temp_r3;
		}
	}
	M2C_FIELD(temp_r3, u8*, 0) = (u8)(s8)*var_r5;
	temp_r0_2                  = M2C_FIELD(temp_r3, u8*, 1);
	var_r5_2                   = &lbl_8_data_1724A;
	if ((s8)temp_r0_2 < (s8)lbl_8_data_1724A) {

	} else {
		var_r5_2 = &lbl_8_data_1724B;
		if ((s8)temp_r0_2 > (s8)lbl_8_data_1724B) {

		} else {
			var_r5_2 = temp_r3 + 1;
		}
	}
	M2C_FIELD(temp_r3, u8*, 1) = (u8)(s8)*var_r5_2;
	M2C_FIELD(&rinoColObjectFieldNames, M2C_UNK**, 0)
	    = (M2C_UNK*)lbl_8_data_171DC[(s8)M2C_FIELD(temp_r3, u8*, 0)];
	M2C_FIELD(&rinoColObjectFieldNames, M2C_UNK**, 4)
	    = (M2C_UNK*)lbl_8_data_17234[(s8)M2C_FIELD(temp_r3, u8*, 1)];
	M2C_FIELD(temp_r3, f32*, 8)    = (f32)M2C_FIELD(arg1, f32*, 0);
	M2C_FIELD(temp_r3, f32*, 0xC)  = (f32)M2C_FIELD(arg1, f32*, 4);
	M2C_FIELD(temp_r3, f32*, 0x10) = (f32)M2C_FIELD(arg1, f32*, 8);
}

void rinoColObjectUnload(void) { }

void rinoColObjectLoad(void) { }

void rinoColObjectCreate(void)
{
	TObject* temp_r3;
	f32 temp_r3_3;
	f32 temp_r3_4;
	void* temp_r3_2;

	temp_r3 = fn_80018A34(lbl_8042C148, 0xE0);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		fn_8003C618(&temp_r3->unk28);
		fn_8005BE6C(&temp_r3->unkB0);
		temp_r3->unk18                = &lbl_8_data_17268;
		temp_r3->unkB4                = (f32)(u32)((u8*)&lbl_8_data_17268 + 0x2C);
		temp_r3->unk0                 = lbl_8_data_17264;
		temp_r3->unk1E                = 0xE0;
		temp_r3_2                     = M2C_FIELD(temp_r3->unkB0, void**, 0x2C);
		M2C_FIELD(temp_r3, u8*, 0xD0) = (u8)M2C_FIELD(temp_r3_2, u8*, 0);
		temp_r3->unkD4                = M2C_FIELD(temp_r3_2, f32*, 8);
		temp_r3->unkD8                = M2C_FIELD(temp_r3_2, f32*, 0xC);
		temp_r3->unkDC                = M2C_FIELD(temp_r3_2, f32*, 0x10);
		temp_r3_3                     = temp_r3->unkB0;
		temp_r3->unkB8                = M2C_FIELD(temp_r3_3, f32*, 0);
		temp_r3->unkBC                = M2C_FIELD(temp_r3_3, f32*, 4);
		temp_r3->unkC0                = M2C_FIELD(temp_r3_3, f32*, 8);
		temp_r3_4                     = temp_r3->unkB0;
		temp_r3->unkC4                = M2C_FIELD(temp_r3_4, f32*, 0xC);
		temp_r3->unkC8                = M2C_FIELD(temp_r3_4, f32*, 0x10);
		temp_r3->unkCC                = M2C_FIELD(temp_r3_4, s32*, 0x14);
		fn_8003C200(&temp_r3->unk28, &lbl_8_data_17100, 1, 4);
		if ((void*)temp_r3->unk38 != NULL) {
			temp_r3->unk88 = temp_r3->unkB8;
			temp_r3->unk8C = temp_r3->unkBC;
			temp_r3->unk90 = temp_r3->unkC0;
			M2C_FIELD(temp_r3->unk38, f32*, 0x14)
			    = (f32)M2C_FIELD(M2C_FIELD(temp_r3->unkB0, void**, 0x2C), f32*, 4);
		}
		fn_80021384(&temp_r3->unk28);
	}
}

void rinoColObjectRegister(void)
{
	M2C_UNK* temp_r3;

	M2C_FIELD(&rinoColObjectEntry, s32*, 0x14)       = 0;
	M2C_FIELD(&rinoColObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&rinoColObjectEntry, M2C_UNK**, 0)     = (M2C_UNK*)"RINO COL OBJECT";
	M2C_FIELD(&rinoColObjectEntry, void (**)(), 4)   = rinoColObjectLoad;
	M2C_FIELD(&rinoColObjectEntry, void (**)(), 8)   = rinoColObjectUnload;
	M2C_FIELD(&rinoColObjectEntry, void (**)(), 0xC) = rinoColObjectCreate;
	M2C_FIELD(&rinoColObjectEntry, s32*, 0x10)       = 0;
	M2C_FIELD(&rinoColObjectEntry, s32*, 0x14)       = 0x20000;
	M2C_FIELD(&rinoColObjectEntry, s32*, 0x18)       = 0;
	M2C_FIELD(&rinoColObjectEntry, s8*, 0x20)        = 0x1E;
	M2C_FIELD(&rinoColObjectEntry, s16*, 0x1C)       = 0x60;
	M2C_FIELD(&rinoColObjectEntry, s16*, 0x1E)       = 4;
	M2C_FIELD(&rinoColObjectEntry, s8*, 0x21)        = 0;
	temp_r3                                          = (M2C_UNK*)"ccccffff";
	M2C_FIELD(&rinoColObjectEntry, M2C_UNK**, 0x24)  = temp_r3;
	M2C_FIELD(&rinoColObjectEntry, M2C_UNK**, 0x28)  = &rinoColObjectFieldNames;
	if (temp_r3 != NULL) {
		M2C_FIELD(&rinoColObjectEntry, s32*, 0x14) = 0x20008;
		return;
	}
	M2C_FIELD(&rinoColObjectEntry, s32*, 0x14) = 0x20000;
}

__declspec(section ".ctors") void (*const rinoColObjectCtorEntry)(void) = rinoColObjectRegister;
}
