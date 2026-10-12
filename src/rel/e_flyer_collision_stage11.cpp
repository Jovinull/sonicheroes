#include "types.h"

// What stays here of stage11D's flyer collision run: its data. The
// TObjFlyerCollision code itself is the shared rel/flyer_collision_*.cpp and
// rel/flyer_col_register.cpp units, so the data keeps the names those units
// use.

extern "C" {

/* The collision volume's shape record, handed to C_COLLI::Init by the
 * constructor (game/obj_flyer_collision.h). The layout is CCL_INFO's. */
typedef struct FlyerColCclInfo {
	u8 kind, form, push, damage; /* 0x00 */
	u32 attr;                    /* 0x04 */
	f32 center[3];               /* 0x08 */
	f32 a, b, c;                 /* 0x14 */
	void* pReactor;              /* 0x20 */
	s32 angx, angy, angz;        /* 0x24 */
} FlyerColCclInfo;               /* 0x30 */

FlyerColCclInfo flyerColCclInfo = {
	0x00,
	0x00,
	0xF0,
	0x00,
	0x00708000,
	{ 0.0f, 0.0f, 0.0f },
	10.0f,
	10.0f,
	10.0f,
	NULL,
	0,
	0,
	0,
};

/* The editor's labels, one per character of flyerColObjectFieldTypes. EditOnChange
 * rewrites the first with the kind's name from flyerColKindNames. */
const char* flyerColObjectFieldNames[9] = {
	"COLLI TYPE",
	"Not in use",
	"Not in use",
	"Not in use",
	"RADIUS",
	"TARGET X",
	"TARGET Y",
	"TARGET Z",
	"FLYER ID",
};

const char* flyerColKindNames[6] = {
	"START",
	"END",
	"BOMB",
	"MISSILE",
	"MACHINE GUN",
	"PAWN",
};

/* EditOnChange's limits on the kind. The lower one is zero but lives in .data
 * beside the upper one. */
#pragma explicit_zero_data on
s8 flyerColKindMin = 0;
#pragma explicit_zero_data reset
s8 flyerColKindMax = 5;

char* CL_TObjFlyerCollision = "TObjFlyerCollision";

/* The class's code is the shared rel/flyer_collision_*.cpp units and the
 * EditOnChange adjustor thunk (fn_8_A82A0) heads stage11D's flyer path run, so
 * nothing in this unit defines the key function that would make the compiler
 * emit the vtable. It is spelled out instead, in the compiler's layout: the
 * TObject vtable with its 8-byte header, then the TObjSetObj one at +0x2C
 * (the second vtable pointer the constructor stores at 0xB4). */
void __dt__18TObjFlyerCollisionFv();
void Exec__18TObjFlyerCollisionFv();
void Disp__7TObjectFv();
void TDisp__18TObjFlyerCollisionFv();
void PDisp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Error__7TObjectFPc();
void Render__7TObjectFv();
void fn_8_A82A0();
void EditOnChange__18TObjFlyerCollisionFP13SETDATA_PARAM();

void* __vt__18TObjFlyerCollision[15] = {
	NULL,
	NULL,
	(void*)__dt__18TObjFlyerCollisionFv,
	(void*)Exec__18TObjFlyerCollisionFv,
	(void*)Disp__7TObjectFv,
	(void*)TDisp__18TObjFlyerCollisionFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)fn_8_A82A0,
	(void*)EditOnChange__18TObjFlyerCollisionFP13SETDATA_PARAM,
};

/* The editor record's strings (rel/flyer_col_register.cpp installs them). */
char flyerColObjectDisplayName[] = "FLYER COL OBJECT";
char flyerColObjectFieldTypes[]  = "ccccffffi";

typedef struct ObjectEntry {
	const char* name;        /* 0x00 */
	void (*load)(void);      /* 0x04 */
	void (*unload)(void);    /* 0x08 */
	void (*create)(void);    /* 0x0C */
	void (*reset)(void);     /* 0x10 */
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

ObjectEntry flyerColObjectEntry;

/* The {0, 1.5, 0} vector the stage 11 object units carry unreferenced at the
 * head of their .rodata (see e_capture_collision_stage11.cpp). */
#pragma force_active on
static const f32 lbl_8_rodata_1980[3] = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset
/* EditOnChange's zero and its limits on the unknown at 0x14. */
extern const f32 flyerColZero[1]     = { 0.0f };
extern const s32 flyerColUnk14Min[1] = { 0 };
extern const s32 flyerColUnk14Max[1] = { 0x100 };
}
