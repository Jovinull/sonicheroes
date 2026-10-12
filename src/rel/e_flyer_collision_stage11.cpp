#include "types.h"

// What stays here of stage11D's flyer collision run: the three small functions
// in front of it (fn_8_A6D1C/A6D24/A6D2C, which stage05D keeps right after its
// flyer register) and the run's data. The TObjFlyerCollision code itself is the
// shared rel/flyer_collision_*.cpp and rel/flyer_col_register.cpp units, so the
// data keeps the names those units use.

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)

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

M2C_UNK fn_800A31B8(void*, s32);     /* extern */
M2C_UNK fn_8_A6728(s32);             /* extern */
static M2C_UNK flyerColCclInfo;      /* unable to generate initializer: unknown type */
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
static M2C_UNK* flyerColKindNames[6] = {
	&lbl_8_data_1636C,
	&lbl_8_data_16374,
	&lbl_8_data_16378,
	&lbl_8_data_16380,
	&lbl_8_data_16388,
	&lbl_8_data_16394,
};
static u8 flyerColKindMin = 0;
static u8 flyerColKindMax = 5;
static M2C_UNK gap_04_000163B6_data; /* unable to generate initializer: unknown type */
static M2C_UNK lbl_8_data_163B8;     /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_000163CB_data; /* unable to generate initializer: unknown type */
static M2C_UNK* CL_TObjFlyerCollision = &lbl_8_data_163B8;
static M2C_UNK __vt__18TObjFlyerCollision; /* unable to generate initializer: unknown type */
static M2C_UNK flyerColObjectDisplayName;  /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001641D_data;       /* unable to generate initializer: unknown type */
static M2C_UNK flyerColObjectFieldTypes;   /* unable to generate initializer: unknown type */
static M2C_UNK gap_04_0001642A_data;       /* unable to generate initializer: unknown type */
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

static ObjectEntry flyerColObjectEntry;
extern const f32 flyerColZero[1]     = { 0.0f };
extern const s32 flyerColUnk14Min[1] = { 0 };
extern const s32 flyerColUnk14Max[4] = { 0x100, 0, 0x3FC00000, 0 };

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
	if (((TObjectDispatch*)arg0)->vslot5() != 0) {
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 2);
	}
	((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
		fn_800A31B8((void*)M2C_FIELD(arg0, s32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
	}
}
}
