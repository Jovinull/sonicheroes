#include "types.h"

// What stays here of stage11D's rinoliner collision run: the code in front of
// TObjColliCommunication and the run's data up to the class's jump table. The
// class itself is the shared rel/colli_communication_*.cpp and
// rel/rino_col_register.cpp units (the jump table goes with
// colli_communication_check), and the editor record's two strings after it
// stay unclaimed as in stage05D and stage07D.

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
	/* 0x2C */ char pad2C[0x4];
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
	virtual s32 vslot5();
};

/* Dispatch view of the object handed to the state jumptable: retail reads the
 * vtable through the incoming `this` in r3 and calls the slot with the state
 * argument in r4, so the call has to go through a class. Slot numbers are the
 * retail vtable offsets, and the two implicit destructor slots occupy 0 and 4. */
class TStateDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void Slot18(s32);
	virtual void Slot1C(s32);
	virtual void Slot20(s32);
	virtual void Slot24(s32);
	virtual void Slot28(s32);
	virtual void Slot2C(s32);
	virtual void Slot30(s32);
};

extern "C" {

void* __ct__7TObjectFP7TObject(TObject* self, TObject* arg0);                    /* extern */
M2C_UNK __dl__FPv(void* arg0);                                                   /* extern */
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);                          /* extern */
M2C_UNK __dt__7C_COLLIFv(void*, M2C_UNK);                                        /* extern */
s32 fn_80017800(void*);                                                          /* extern */
M2C_UNK Free__9THeapCtrlFPv(s32, TObject*);                                      /* extern */
TObject* Malloc__9THeapCtrlFUi(s32, M2C_UNK);                                    /* extern */
M2C_UNK Entry__7C_COLLIFv(void*);                                                /* extern */
M2C_UNK ClearInfo__7C_COLLIFv(void*);                                            /* extern */
M2C_UNK Init__7C_COLLIFP8CCL_INFOiUc(M2C_UNK*, M2C_UNK*, M2C_UNK, M2C_UNK, ...); /* extern */
M2C_UNK __ct__7C_COLLIFv(M2C_UNK*);                                              /* extern */
void* objPointerReadFromClumpAnim__FPc(const char*);                             /* extern */
M2C_UNK fn_800A31B8(void*, s32);                                                 /* extern */
s32 fn_800A3ED4(void*);                                                          /* extern */
M2C_UNK AdjustPoint__FP5RwV3dPC5RwV3df(void*, f32*, M2C_UNK*, f32);              /* extern */
f32 Distance2P2P__FPC5RwV3dPC5RwV3d(void*, s32);                                 /* extern */
s32 GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(void*, M2C_UNK*, f32);        /* extern */
M2C_UNK SetLightNum__7nRenderFUi(s32);                                           /* extern */
M2C_UNK fn_8014FF2C(void*);                                                      /* extern */
M2C_UNK fn_801990E0(f32*, f32*, f32);                                            /* extern */
s32 fn_8019CE34(s32, f32*);                                                      /* extern */
M2C_UNK fn_8019EB94(s32, void*, M2C_UNK);                                        /* extern */
M2C_UNK fn_8019ED68(s32, M2C_UNK*, f32, s32);                                    /* extern */
s32 fn_8_B0A74(void*);                                                           /* extern */
M2C_UNK fn_8_B43E8(s32);                                                         /* extern */
void fn_8_B4B9C(void* arg0);
s32 CheckCollision__22TObjColliCommunicationFv(void* arg0);
extern M2C_UNK AxisX;
extern M2C_UNK AxisY;
extern M2C_UNK AxisZ;
extern M2C_UNK lbl_8029C310;
extern M2C_UNK lbl_802AD090;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern s32* lbl_8042C9A4;
static u32 lbl_8_data_16FD8[12] = { 0x17009022, 0x00080000, 0x00000000, 0x00000000, 0x00000000,
	0x41000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
static char lbl_8_data_17008[]  = "TObjEnemyIronBall";
static M2C_UNK gap_04_0001701A_data; /* unable to generate initializer: unknown type */
static M2C_UNK* lbl_8_data_1701C = (M2C_UNK*)lbl_8_data_17008;
static M2C_UNK lbl_8_data_17020; /* unable to generate initializer: unknown type */
static char lbl_8_data_1704C[] = "OBJ_SPIKEB.DFF";
static M2C_UNK gap_04_0001705B_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17060;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_170B0;     /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_170C8;     /* unable to generate initializer: unknown type */
static u32 colliCommunicationCclInfo[12]
    = { 0x0000F000, 0x00708000, 0x00000000, 0x00000000, 0x00000000, 0x41200000, 0x41200000,
	      0x41200000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
static M2C_UNK lbl_8_data_17130;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001713B_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_1713C[] = "SPEED CTRL";
static M2C_UNK gap_04_00017147_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17148;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00017153_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17154;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001715B_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_1715C;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00017165_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17168;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_00017171_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_17174;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001717D_data; /* unable to generate initializer: unknown type */
static M2C_UNK rinoColObjectFieldNames[2] = { 0, 0 };
static char lbl_8_data_171A0[]            = "START";
static M2C_UNK gap_04_000171A6_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_171A8[] = "END";
static char lbl_8_data_171AC[] = "CHANGE PATH";
static char lbl_8_data_171B8[] = "CHANGE PATH SET";
static char lbl_8_data_171C8[] = "ATTACK";
static M2C_UNK gap_04_000171CF_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_171D0[] = "ATTACK SET";
static M2C_UNK gap_04_000171DB_data; /* unable to generate initializer: unknown type */
static M2C_UNK* rinoColKindNames[7] = {
	(M2C_UNK*)lbl_8_data_171A0,
	(M2C_UNK*)lbl_8_data_171A8,
	(M2C_UNK*)lbl_8_data_171AC,
	(M2C_UNK*)lbl_8_data_171B8,
	(M2C_UNK*)lbl_8_data_171C8,
	(M2C_UNK*)lbl_8_data_171D0,
	(M2C_UNK*)lbl_8_data_1713C,
};
static char lbl_8_data_171F8[] = "ENABLE";
static M2C_UNK gap_04_000171FF_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17200[] = "DISABLE";
static char lbl_8_data_17208[] = "DISABLE MIN";
static char lbl_8_data_17214[] = "DISABLE STANDARD";
static M2C_UNK gap_04_00017225_data; /* unable to generate initializer: unknown type */
static char lbl_8_data_17228[]        = "DISABLE MAX";
static M2C_UNK* rinoColActionNames[5] = { (M2C_UNK*)lbl_8_data_171F8, (M2C_UNK*)lbl_8_data_17200,
	(M2C_UNK*)lbl_8_data_17208, (M2C_UNK*)lbl_8_data_17214, (M2C_UNK*)lbl_8_data_17228 };
static u8 rinoColKindMin              = 0;
static u8 rinoColKindMax              = 6;
static u8 rinoColActionMin            = 0;
static u8 rinoColActionMax            = 4;
static char lbl_8_data_1724C[]        = "TObjColliCommunication";
static M2C_UNK gap_04_00017263_data; /* unable to generate initializer: unknown type */
static M2C_UNK* CL_TObjColliCommunication = (M2C_UNK*)lbl_8_data_1724C;
static M2C_UNK __vt__22TObjColliCommunication; /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000172D9_data;           /* unable to generate initializer: unknown type */
static struct {
	void* p;
	void* unk4;
} lbl_8_bss_1A90;
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

static ObjectEntry rinoColObjectEntry;
extern const f32 lbl_8_rodata_1C64[3] = { 0.0f, 2.0f, 0.0f };
extern const f32 lbl_8_rodata_1C70[1] = { 20.0f };
extern const f32 lbl_8_rodata_1C74[1] = { 100000000.0f };
extern const f32 lbl_8_rodata_1C78[1] = { 2500.0f };
extern const f32 lbl_8_rodata_1C7C[1] = { 0.0f };
extern const f32 lbl_8_rodata_1C80[9]
    = { 0.05000000074505806f, 0.0f, 0.0f, 1.5f, 0.0f, 0.0f, 0.0f, 1.5f, 0.0f };
extern const f32 rinoColZero[5]       = { 0.0f, 0.0f, 1.5f, 0.0f, 0.0f };
extern const f32 lbl_8_rodata_1CB8[3] = { 0.0f, 1.5f, 0.0f };
extern const f32 lbl_8_rodata_1CC4[3] = { 16.0f, 18.0f, 0.0f };
extern const f32 lbl_8_rodata_1CD0[3] = { 0.0f, -10.0f, 0.0f };
extern const f32 lbl_8_rodata_1CDC[3] = { 0.0f, -10.0f, 0.0f };
extern const f32 lbl_8_rodata_1CE8[3] = { 0.0f, -10.0f, 0.0f };
extern const f32 lbl_8_rodata_1CF4[3] = { 0.0f, -10.0f, 0.0f };
extern const f32 lbl_8_rodata_1D00[4] = { -1.0f, -1.0f, -1.0f, 1.0f };
extern const f32 lbl_8_rodata_1D10[3] = { 32.0f, 1.0f, 32.0f };
extern const f32 lbl_8_rodata_1D1C[4] = { -1.0f, -1.0f, -1.0f, 1.0f };
extern const f32 lbl_8_rodata_1D2C[4] = { -1.0f, -1.0f, -1.0f, 0.0f };
extern const f32 lbl_8_rodata_1D3C[3] = { 20.0f, 1.0f, 20.0f };
extern const f32 lbl_8_rodata_1D48[3] = { 0.0f, 0.0f, 0.0f };
extern const f32 lbl_8_rodata_1D54[1] = { 0.20000000298023224f };
extern const f32 lbl_8_rodata_1D58[1] = { 1.0f };
extern const f32 lbl_8_rodata_1D5C[1] = { 1.0f };
extern const f32 lbl_8_rodata_1D60[1] = { 20.0f };
extern const f32 lbl_8_rodata_1D64[1] = { 0.004000000189989805f };
extern const f32 lbl_8_rodata_1D68[1] = { 0.0010000000474974513f };
extern const f32 lbl_8_rodata_1D6C[1] = { 0.9800000190734863f };
extern const f32 lbl_8_rodata_1D70[1] = { 0.0054931640625f };
extern const f32 lbl_8_rodata_1D74[1] = { 0.029999999329447746f };
extern const f32 lbl_8_rodata_1D78[1] = { 0.10000000149011612f };
extern const f32 lbl_8_rodata_1D7C[1] = { 0.20000000298023224f };
extern const f32 lbl_8_rodata_1D80[1] = { 0.0f };
extern const f32 lbl_8_rodata_1D84[1] = { 0.8999999761581421f };
extern const f32 lbl_8_rodata_1D88[1] = { -0.8999999761581421f };
extern const f64 lbl_8_rodata_1D90[1] = { 4503601774854144.0 };
extern const f32 lbl_8_rodata_1D98[1] = { 3.0f };
extern const f32 lbl_8_rodata_1D9C[1] = { 80.0f };
extern const f32 lbl_8_rodata_1DA0[1] = { 250000.0f };
extern const f32 lbl_8_rodata_1DA4[1] = { 0.05000000074505806f };
extern const f32 lbl_8_rodata_1DA8[1] = { -1.0f };
extern const f32 lbl_8_rodata_1DAC[1] = { 1.2000000476837158f };
extern const f32 lbl_8_rodata_1DB0[1] = { 1600.0f };
extern const f32 lbl_8_rodata_1DB4[1] = { 6400.0f };
extern const f32 lbl_8_rodata_1DB8[1] = { 1.5f };
extern const f32 lbl_8_rodata_1DBC[1] = { 16.0f };
extern const f32 lbl_8_rodata_1DC0[1] = { 10.0f };
extern const f32 lbl_8_rodata_1DC4[1] = { 8.0f };
extern const f32 lbl_8_rodata_1DC8[1] = { 0.5f };
extern const f32 lbl_8_rodata_1DCC[1] = { 5.0f };
extern const f32 lbl_8_rodata_1DD0[1] = { 100000000.0f };
extern const f32 lbl_8_rodata_1DD4[1] = { 4.0f };
extern const f32 lbl_8_rodata_1DD8[1] = { 42.0f };
extern const f32 lbl_8_rodata_1DDC[1] = { 2.0f };
extern const f32 lbl_8_rodata_1DE0[1] = { 180.0f };
extern const f32 lbl_8_rodata_1DE4[1] = { 15.0f };
extern const f32 lbl_8_rodata_1DE8[1] = { 0.30000001192092896f };
extern const f32 lbl_8_rodata_1DEC[1] = { -1000000.0f };
extern const f32 lbl_8_rodata_1DF0[1] = { 30.0f };
extern const f32 lbl_8_rodata_1DF4[1] = { 12.0f };
extern const f32 lbl_8_rodata_1DF8[1] = { 0.800000011920929f };
extern const f32 lbl_8_rodata_1DFC[1] = { 55.0f };
extern const f32 lbl_8_rodata_1E00[1] = { 24.0f };
extern const f32 lbl_8_rodata_1E04[1] = { 0.0f };
extern const f32 lbl_8_rodata_1E08[1] = { 10000.0f };
extern const f32 lbl_8_rodata_1E0C[1] = { 0.0f };
extern const f32 lbl_8_rodata_1E10[1] = { 10000.0f };
extern const f32 lbl_8_rodata_1E14[1] = { 0.0f };
extern const s32 lbl_8_rodata_1E18[1] = { 0x00002710 };
extern const f32 lbl_8_rodata_1E1C[1] = { 0.0f };

void fn_8_B49D8(s32 arg0)
{
	fn_8_B43E8(arg0 - 0xB0);
}

void fn_8_B49E0(void) { }

void fn_8_B49E4(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	M2C_FIELD(arg0, s32*, 0x10) = 0;
	if (((TObjectDispatch*)arg0)->vslot5() != 0) {
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 2);
	}
	((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
		fn_800A31B8((void*)M2C_FIELD(arg0, u32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
	}
}

void fn_8_B4A7C(void* arg0)
{
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	s32 temp_r30;

	if ((void*)lbl_8_bss_1A90.p != NULL) {
		sp8  = M2C_FIELD(arg0, f32*, 0xB0);
		spC  = M2C_FIELD(arg0, f32*, 0xB4);
		sp10 = M2C_FIELD(arg0, f32*, 0xB8);
		sp14 = 20.0f;
		if (fn_8019CE34(*lbl_8042C9A4, &sp8) != 0) {
			temp_r30 = M2C_FIELD(lbl_8_bss_1A90.p, s32*, 4);
			fn_8019ED68(temp_r30, &AxisZ, M2C_FIELD(arg0, f32*, 0xF0), 0);
			fn_8019ED68(temp_r30, &AxisX, M2C_FIELD(arg0, f32*, 0xE8), 2);
			fn_8019ED68(temp_r30, &AxisY, M2C_FIELD(arg0, f32*, 0xEC), 2);
			fn_8019EB94(temp_r30, (u8*)arg0 + 0xB0, 2);
			SetLightNum__7nRenderFUi(M2C_FIELD(arg0, s32*, 0xE0));
			fn_8014FF2C(lbl_8_bss_1A90.p);
		}
	}
}

void fn_8_B4B88(void* arg0)
{
	M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
}

void fn_8_B4B9C(void* arg0)
{
	f32 sp14[3];
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
		temp_r3 = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(
		    (u8*)arg0 + 0xB0, (s32*)lbl_8_rodata_1C74, 1e8f);
		if (temp_r3 != -1) {
			temp_r30 = *(void**)((u8*)&lbl_802AD090 + (temp_r3 * 4));
			if (temp_r30 != NULL) {
				if (Distance2P2P__FPC5RwV3dPC5RwV3d((u8*)arg0 + 0xB0, (s32)((u8*)temp_r30 + 0x18))
				    < 2500.0f) {
					M2C_FIELD(arg0, s32*, 0xDC) = 0;
				}
				sp14[0] = M2C_FIELD(temp_r30, f32*, 0x18) - M2C_FIELD(arg0, f32*, 0xB0);
				sp14[1] = M2C_FIELD(temp_r30, f32*, 0x1C) - M2C_FIELD(arg0, f32*, 0xB4);
				temp_f1 = M2C_FIELD(temp_r30, f32*, 0x20);
				sp14[2] = temp_f1 - M2C_FIELD(arg0, f32*, 0xB8);
				fn_801990E0(sp14, sp14, temp_f1);
				temp_f31 = M2C_FIELD(arg0, f32*, 0xC0);
				if (((M2C_FIELD(arg0, f32*, 0xC4) * sp14[2])
				        + ((M2C_FIELD(arg0, f32*, 0xBC) * sp14[0]) + (temp_f31 * sp14[1])))
				    > 0.0f) {
					AdjustPoint__FP5RwV3dPC5RwV3df(
					    (u8*)arg0 + 0xBC, sp14, (s32*)lbl_8_rodata_1C80, 0.05f);
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
	    = (f32)(M2C_FIELD(arg0, f32*, 0xEC) + M2C_FIELD(lbl_8_rodata_1C64, f32*, 4));
	M2C_FIELD(arg0, f32*, 0xF0)
	    = (f32)(M2C_FIELD(arg0, f32*, 0xF0) + M2C_FIELD(lbl_8_rodata_1C64, f32*, 8));
}

void fn_8_B4DA4(void* arg0)
{
	M2C_FIELD(arg0, s32*, 0xE4) = 1;
}

void fn_8_B4DB0(void* arg0)
{
	u8 var_r6;
	u8 var_r5;
	s32 temp_r3;
	s32 temp_r0;
	s32 var_r0;

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
		ClearInfo__7C_COLLIFv((u8*)arg0 + 0x28);
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
		Entry__7C_COLLIFv((u8*)arg0 + 0x28);
	}
}

TObject* fn_8_B4F70(TObject* arg0, s16 arg1)
{
	if (arg0 != NULL) {
		arg0->unk18 = &lbl_8_data_17020;
		__dt__7C_COLLIFv((u8*)arg0 + 0x28, 0);
		__dt__7TObjectFv(arg0, 0);
		if (arg1 > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, arg0);
		}
	}
	return arg0;
}

TObject* fn_8_B4FF4(TObject* arg0, TObject* arg1, void* arg2)
{
	__ct__7TObjectFP7TObject(arg0, arg1);
	__ct__7C_COLLIFv(&arg0->unk28);
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
	Init__7C_COLLIFP8CCL_INFOiUc(&arg0->unk28, (int*)lbl_8_data_16FD8, 1, 3, 0.0f);
	arg0->unk88 = arg0->unkB0;
	arg0->unk8C = arg0->unkB4;
	arg0->unk90 = arg0->unkB8;
	arg0->unk30 &= 0xFFFFFFBF;
	return arg0;
}

void fn_8_B5160(void* arg0)
{
	TObject* temp_r3;

	temp_r3 = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xF4);
	if (temp_r3 != NULL) {
		__ct__7TObjectFP7TObject(temp_r3, lbl_8042C10C);
		__ct__7C_COLLIFv(&temp_r3->unk28);
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
		Init__7C_COLLIFP8CCL_INFOiUc(&temp_r3->unk28, (int*)lbl_8_data_16FD8, 1, 3, 0.0f);
		temp_r3->unk88 = temp_r3->unkB0;
		temp_r3->unk8C = temp_r3->unkB4;
		temp_r3->unk90 = temp_r3->unkB8;
		temp_r3->unk30 &= 0xFFFFFFBF;
	}
}

void fn_8_B52F4(void)
{
	lbl_8_bss_1A90.p = NULL;
}

void fn_8_B5308(void)
{
	lbl_8_bss_1A90.p = objPointerReadFromClumpAnim__FPc(lbl_8_data_1704C);
}

void fn_8_B533C(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18)
			    = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x2B0);
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			break;
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
			break;
		case 2:
		case 3:
			break;
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
	s32 temp_r31;
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x1C) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			break;
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
			break;
		case 2:
		case 3:
			break;
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
	s32 temp_r31;
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 1;
			M2C_FIELD(arg0, s32*, 0x10) = 0x20;
			break;
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
			break;
		case 2:
		case 3:
			break;
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
			fn_800A31B8((void*)M2C_FIELD(arg0, u32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
		}
	}
}

s32 fn_8_B5694(void* arg0)
{
	s32 var_r3;
	void* temp_r3;
	s32 temp_r0;
	s32 temp_r0_2;

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
		switch (temp_r0_2) {
			case 1:
			case 2:
				break;
			default:
				goto block_28;
		}
		{
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
			((TStateDispatch*)arg0)->Slot18(arg2);
			return;
		case 4:
			((TStateDispatch*)arg0)->Slot1C(arg2);
			return;
		case 1:
			((TStateDispatch*)arg0)->Slot20(arg2);
			return;
		case 3:
			((TStateDispatch*)arg0)->Slot28(arg2);
			return;
		case 2:
			((TStateDispatch*)arg0)->Slot24(arg2);
			return;
		case 5:
			((TStateDispatch*)arg0)->Slot2C(arg2);
			return;
		case 6:
			((TStateDispatch*)arg0)->Slot30(arg2);
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
}
