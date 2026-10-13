#include "types.h"

// TObjEnemyPawn::CalcStartAndAimForFall and CalcStartAndAimForRun (the PS2
// build's names, by its member order): place the pawn for a fall (its set
// position raised by the set height) or for a run (its set position pushed
// back by the set distance along the set heading); the start position becomes
// the set one. The hiding modes inline the same steps. (MWCC emits these two
// in reverse definition order, hence Run first here.)

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct PawnParams {
	u8 unk00[0xC];
	f32 distance; // 0x0C
	f32 heading;  // 0x10
} PawnParams;

typedef struct PawnSetData {
	u8 unk00[0x2C];
	PawnParams* params; // 0x2C
} PawnSetData;

typedef struct Pawn {
	u8 unk000[0xB0];
	PawnSetData* setData; // 0x0B0
	u8 unk0B4[0x8C];
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

extern "C" void CalcStartAndAimForRun__13TObjEnemyPawnFv(Pawn* pawn)
{
	RwMatrixTag matrix;
	RwV3d offset;
	PawnParams* params = pawn->setData->params;

	fn_80195A74(&matrix, &AxisY, params->heading, 0);
	fn_80196050(&matrix, &pawn->setPos, 2);
	offset.z = -params->distance;
	offset.x = offset.y = pawnZero[0];
	fn_8019941C(&pawn->pos, &offset, 1, &matrix);
	pawn->startPos = pawn->setPos;
}

extern "C" void CalcStartAndAimForFall__13TObjEnemyPawnFv(Pawn* pawn)
{
	RwMatrixTag matrix;
	RwV3d offset;
	PawnParams* params = pawn->setData->params;

	fn_80196050(&matrix, &pawn->setPos, 0);
	offset.y = params->distance;
	offset.x = offset.z = pawnZero[0];
	fn_8019941C(&pawn->pos, &offset, 1, &matrix);
	pawn->startPos = pawn->setPos;
}
