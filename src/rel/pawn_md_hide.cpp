#include "types.h"

// TObjEnemyPawn::EnemyMD_Hide (the PS2 build's name, by its member order):
// entering it (0) sets the standing motion (0) and moves the pawn to its
// hiding place: the set position pushed back by the hide distance along the
// set heading; the start position becomes the same.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct PawnParams {
	u8 unk00[0xC];
	f32 hideDistance; // 0x0C
	f32 heading;      // 0x10
} PawnParams;

typedef struct PawnSetData {
	u8 unk00[0x2C];
	PawnParams* params; // 0x2C
} PawnSetData;

typedef struct Pawn {
	u8 unk000[0xB0];
	PawnSetData* setData; // 0x0B0
	u8 unk0B4[0x20];
	s32 motion; // 0x0D4
	u8 unk0D8[0x68];
	RwV3d pos; // 0x140
	u8 unk14C[0x74];
	RwV3d setPos;   // 0x1C0
	RwV3d startPos; // 0x1CC
} Pawn;

extern "C" const f32 pawnZero[1];
extern "C" const RwV3d AxisY;

extern "C" void fn_80195A74(RwMatrixTag* matrix, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);

extern "C" void EnemyMD_Hide__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0: {
			RwMatrixTag matrix;
			RwV3d offset;
			PawnParams* params;

			pawn->motion = 0;
			params       = pawn->setData->params;
			fn_80195A74(&matrix, &AxisY, params->heading, 0);
			fn_80196050(&matrix, &pawn->setPos, 2);
			offset.z = -params->hideDistance;
			offset.x = offset.y = pawnZero[0];
			fn_8019941C(&pawn->pos, &offset, 1, &matrix);
			pawn->startPos = pawn->setPos;
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
