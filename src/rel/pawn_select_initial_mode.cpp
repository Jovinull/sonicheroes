#include "types.h"

// TObjEnemyPawn::SelectInitialMode (the PS2 build's name): picks the first mode
// from the set data's start kind when none is set yet, falling through to the
// next kind's choice otherwise (0: mode 0xD; 2: hidden, mode 0xF, placed back
// along the set angle from home; 3 and 4: modes 0x11 and 0x14, placed above
// home; 5: mode 0x2B; last, 1: walking, mode 0xA).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwMatrixTag {
	u8 data[0x40];
} RwMatrixTag;

typedef struct PawnSetParam {
	u8 unk00[0xC];
	f32 offset; // 0x0C
	f32 angle;  // 0x10
} PawnSetParam;

typedef struct PawnSet {
	u8 unk00[0x2C];
	PawnSetParam* param; // 0x2C
} PawnSet;

typedef struct Pawn {
	u8 unk000[0xB0];
	PawnSet* set; // 0x0B0
	u8 unk0B4[0x20];
	s32 nextMotion; // 0x0D4
	u8 unk0D8[0x68];
	RwV3d pos; // 0x140
	u8 unk14C[0x50];
	s32 mode; // 0x19C
	u8 unk1A0[0x20];
	RwV3d home; // 0x1C0
	RwV3d base; // 0x1CC
	u8 unk1D8[0x74];
	s8 start; // 0x24C
	u8 unk24D[0xB3];
	s32 step; // 0x300
} Pawn;

extern "C" const RwV3d AxisY;
extern "C" const f32 pawnZero[1];

extern "C" void fn_80195A74(RwMatrixTag* matrix, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);

extern "C" void SelectInitialMode__13TObjEnemyPawnFv(Pawn* pawn)
{
	switch (pawn->start) {
		case 0:
			if (pawn->mode == 0) {
				pawn->mode       = 0xD;
				pawn->nextMotion = 1;
				break;
			}
		case 2:
			if (pawn->mode == 0) {
				PawnSetParam* param;
				RwMatrixTag matrix;
				RwV3d offset;

				pawn->mode       = 0xF;
				pawn->nextMotion = 0;
				param            = pawn->set->param;
				fn_80195A74(&matrix, &AxisY, param->angle, 0);
				fn_80196050(&matrix, &pawn->home, 2);
				offset.z = -param->offset;
				offset.x = offset.y = pawnZero[0];
				fn_8019941C(&pawn->pos, &offset, 1, &matrix);
				pawn->base.x = pawn->home.x;
				pawn->base.y = pawn->home.y;
				pawn->base.z = pawn->home.z;
				break;
			}
		case 3:
			if (pawn->mode == 0) {
				PawnSetParam* param;
				RwMatrixTag matrix;
				RwV3d offset;

				pawn->mode       = 0x11;
				pawn->nextMotion = 0;
				param            = pawn->set->param;
				fn_80196050(&matrix, &pawn->home, 0);
				offset.y = param->offset;
				offset.x = offset.z = pawnZero[0];
				fn_8019941C(&pawn->pos, &offset, 1, &matrix);
				pawn->base.x = pawn->home.x;
				pawn->base.y = pawn->home.y;
				pawn->base.z = pawn->home.z;
				break;
			}
		case 4:
			if (pawn->mode == 0) {
				PawnSetParam* param;
				RwMatrixTag matrix;
				RwV3d offset;

				pawn->mode       = 0x14;
				pawn->nextMotion = 0;
				param            = pawn->set->param;
				fn_80196050(&matrix, &pawn->home, 0);
				offset.y = param->offset;
				offset.x = offset.z = pawnZero[0];
				fn_8019941C(&pawn->pos, &offset, 1, &matrix);
				pawn->base.x = pawn->home.x;
				pawn->base.y = pawn->home.y;
				pawn->base.z = pawn->home.z;
				break;
			}
		case 5:
			if (pawn->mode == 0) {
				pawn->mode       = 0x2B;
				pawn->nextMotion = 0x13;
				break;
			}
		case 1:
			pawn->mode       = 0xA;
			pawn->nextMotion = 3;
			pawn->step       = 0;
			break;
	}
}
