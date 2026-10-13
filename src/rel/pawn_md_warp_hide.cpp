#include "types.h"

// TObjEnemyPawn::EnemyMD_WarpHide (the PS2 build's name, by its member order;
// same body as the other hiding mode): entering it (0) sets the standing
// motion (0), puts the pawn at its set position raised by the hide height (the
// start position becomes the set one) and hides its model and shadow.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct RpClump RpClump;

typedef struct PawnParams {
	u8 unk00[0xC];
	f32 hideHeight; // 0x0C
} PawnParams;

typedef struct PawnSetData {
	u8 unk00[0x2C];
	PawnParams* params; // 0x2C
} PawnSetData;

typedef struct PawnShadow {
	u8 unk000[0x184];
	s32 active; // 0x184
} PawnShadow;

typedef struct Pawn {
	u8 unk000[0xB0];
	PawnSetData* setData; // 0x0B0
	u8 unk0B4[0x20];
	s32 motion; // 0x0D4
	u8 unk0D8[0x10];
	RpClump* clump; // 0x0E8
	u8 unk0EC[0x54];
	RwV3d pos; // 0x140
	u8 unk14C[0x74];
	RwV3d setPos;   // 0x1C0
	RwV3d startPos; // 0x1CC
	u8 unk1D8[0x90];
	PawnShadow* shadow; // 0x268
	u8 unk26C[0x80];
	s32 shown; // 0x2EC
} Pawn;

extern "C" const f32 pawnZero[1];

extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
void objRpClumpForAllAtomicsToHide(RpClump* clump);

static inline void pawnHide(Pawn* pawn)
{
	if (pawn->shown != 0) {
		objRpClumpForAllAtomicsToHide(pawn->clump);
		pawn->shown = 0;
		if (pawn->shadow != NULL) {
			pawn->shadow->active = 0;
		}
	}
}

extern "C" void EnemyMD_WarpHide__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0: {
			RwMatrixTag matrix;
			RwV3d offset;
			PawnParams* params;

			pawn->motion = 0;
			params       = pawn->setData->params;
			fn_80196050(&matrix, &pawn->setPos, 0);
			offset.y = params->hideHeight;
			offset.x = offset.z = pawnZero[0];
			fn_8019941C(&pawn->pos, &offset, 1, &matrix);
			pawn->startPos = pawn->setPos;
			pawn->shown    = 1;
			pawnHide(pawn);
			break;
		}
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
