#include "types.h"

// TObjEnemyPawn::CheckDirectionOfPlayerRangeIn (the PS2 build's name, by its
// member order): returns 0 when the targeted player lies within a quarter turn
// of the pawn's facing (the pawn's back axis turned by its heading against the
// player's normalized position), 1 otherwise or without a target.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct BobsleighPlayerState {
	u8 unk00[0x18];
	RwV3d pos; // 0x18
} PawnPlayerState;

typedef struct Pawn {
	u8 unk000[0x150];
	s32 heading; // 0x150
} Pawn;

extern "C" PawnPlayerState* lbl_802AD090[];
extern "C" const f32 pawnOne[1];
extern "C" const RwV3d AxisY;
extern "C" const RwV3d pawnFacing;
extern "C" const RwV3d pawnNoTarget;
extern "C" const RwV3d pawnAngleUp;

extern "C" int fn_800A5844(Pawn* pawn);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" void fn_801990E0(RwV3d* out, RwV3d* in);
int VectorAngle(RwV3d* a, RwV3d* b, RwV3d* up);

extern "C" int CheckDirectionOfPlayerRangeIn__13TObjEnemyPawnFv(Pawn* pawn)
{
	int player = fn_800A5844(pawn);
	int angle;

	if (player == -1) {
		return 1;
	}
	RwMatrixTag matrix;
	RwV3d facing = pawnFacing;

	fn_80195790(&matrix, &AxisY, pawnOne[0] - fn_800D7AE4(pawn->heading + 0x8000),
	    fn_800D7B00(pawn->heading + 0x8000), 0);
	fn_8019941C(&facing, &facing, 1, &matrix);
	RwV3d target = pawnNoTarget;

	if (lbl_802AD090[player] != NULL) {
		target = lbl_802AD090[player]->pos;
	}
	fn_801990E0(&target, &target);
	RwV3d up = pawnAngleUp;

	angle = VectorAngle(&facing, &target, &up);
	if (angle >= 0 && angle <= 0x4000) {
		return 0;
	}
	return 1;
}
