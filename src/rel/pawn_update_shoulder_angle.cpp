#include "types.h"

// TObjEnemyPawn::UpdateShoulderAngle (the PS2 build's name, by its member
// order): with a shoulder frame and a target, eases the shoulder pitch towards
// the angle of the target seen from the shoulder (capped at +-0x1400).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwMatrixTag {
	u8 unk00[0x30];
	RwV3d pos; // 0x30
} RwMatrixTag;

typedef struct RwFrame RwFrame;

typedef struct PawnPlayerState {
	u8 unk00[0x18];
	RwV3d pos; // 0x18
} PawnPlayerState;

typedef struct Pawn {
	u8 unk000[0x304];
	RwFrame* shoulder; // 0x304
	u8 unk308[0x18];
	s32 shoulderPitch; // 0x320
} Pawn;

extern "C" PawnPlayerState* lbl_802AD090[];
extern "C" const RwV3d pawnShoulderNoTarget;
extern "C" const f32 pawnRadToAngle[1];

extern "C" int fn_800A5844(Pawn* pawn);
extern "C" RwMatrixTag* fn_8019E8EC(RwFrame* frame);
extern "C" void fn_801990E0(RwV3d* out, RwV3d* in);
extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" double asin(double x);
int AdjustAngle(int value, int target, int step);

extern "C" void UpdateShoulderAngle__13TObjEnemyPawnFv(Pawn* pawn)
{
	int player;

	if (pawn->shoulder != NULL && (player = fn_800A5844(pawn)) != -1) {
		RwV3d from = fn_8019E8EC(pawn->shoulder)->pos;
		RwV3d to   = pawnShoulderNoTarget;
		RwV3d dir;
		f32 length;
		int angle;

		if (lbl_802AD090[player] != NULL) {
			to = lbl_802AD090[player]->pos;
		}
		dir.x = to.x - from.x;
		dir.y = to.y - from.y;
		dir.z = to.z - from.z;
		fn_801990E0(&dir, &dir);
		length = fn_801991B4(&dir);
		angle  = -(s32)(pawnRadToAngle[0] * (f32)asin(-dir.y / length));
		if (angle < -0x1400) {
			angle = -0x1400;
		}
		if (angle > 0x1400) {
			angle = 0x1400;
		}
		pawn->shoulderPitch = AdjustAngle(pawn->shoulderPitch, angle, 0x100);
	}
}
