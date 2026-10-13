#include "types.h"

// TObjEnemyPawn::ExecShotReady (the PS2 build's name): counts the wait before a
// shot. Once it is over, in the aiming motion (0x10, not finishing), the pawn
// fires a shot along its gun (from the muzzle towards the second frame, at its
// shot speed) when it has none, asks for mode 0x17 with the firing motion when
// its shot is done, or else holds the count; while waiting it keeps its
// shoulder on the target (UpdateShoulderAngle, inlined).

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

typedef struct PawnShot {
	u8 unk00[0xE8];
	s32 done; // 0xE8
} PawnShot;

typedef struct PawnWeapon {
	u8 unk00[0x1C];
	s32 command; // 0x1C
} PawnWeapon;

typedef struct Pawn {
	u8 unk000[0xD0];
	s32 motion;     // 0x0D0
	s32 nextMotion; // 0x0D4
	u8 unk0D8[0x8];
	s32 motionState; // 0x0E0
	u8 unk0E4[0x164];
	s32 nextMode; // 0x248
	u8 unk24C[0x8];
	f32 shotSpeed; // 0x254
	s32 shotTimer; // 0x258
	s32 shotWait;  // 0x25C
	u8 unk260[0x4];
	PawnShot* shot; // 0x264
	u8 unk268[0x18];
	PawnWeapon* weapon; // 0x280
	u8 unk284[0x80];
	RwFrame* shoulder; // 0x304
	u8 unk308[0x4];
	RwFrame* muzzle; // 0x30C
	RwFrame* second; // 0x310
	u8 unk314[0xC];
	s32 shoulderPitch; // 0x320
} Pawn;

extern "C" PawnPlayerState* lbl_802AD090[];
extern "C" const f32 pawnZero[1];
extern "C" const RwV3d pawnShoulderNoTarget;
extern "C" const f32 pawnRadToAngle[1];

extern "C" int fn_800A5844(Pawn* pawn);
extern "C" RwMatrixTag* fn_8019E8EC(RwFrame* frame);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" void fn_801990E0(RwV3d* out, RwV3d* in);
extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" double asin(double x);
int AdjustAngle(int value, int target, int step);
struct TObject;
PawnShot* SetEnemyShot(TObject* parent, int kind, RwV3d* velocity, RwV3d* pos);

namespace nSystem
{
void IncreaseTimer(int& timer);
}

// UpdateShoulderAngle as this function inlines it
// (rel/pawn_update_shoulder_angle.cpp has the out-of-line copy).
static inline void pawnUpdateShoulderAngle(Pawn* pawn)
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

extern "C" void ExecShotReady__13TObjEnemyPawnFv(Pawn* pawn)
{
	nSystem::IncreaseTimer(pawn->shotTimer);
	if (pawn->shotTimer > pawn->shotWait) {
		if (pawn->motion == 0x10 && pawn->motionState != 2) {
			if (pawn->shot == NULL) {
				if (pawn->muzzle != NULL && pawn->second != NULL) {
					RwMatrixTag* ltm = fn_8019E8EC(pawn->muzzle);
					RwV3d from;
					RwV3d dir;

					from.z = from.y = from.x = pawnZero[0];
					fn_8019941C(&from, &from, 1, ltm);
					ltm   = fn_8019E8EC(pawn->second);
					dir.z = dir.y = dir.x = pawnZero[0];
					fn_8019941C(&dir, &dir, 1, ltm);
					dir.x -= from.x;
					dir.y -= from.y;
					dir.z -= from.z;
					fn_801990E0(&dir, &dir);
					dir.x *= pawn->shotSpeed;
					dir.y *= pawn->shotSpeed;
					dir.z *= pawn->shotSpeed;
					pawn->shot = SetEnemyShot((TObject*)pawn, 1, &dir, &from);
				}
			} else if (pawn->shot->done != 0) {
				pawn->nextMode        = 0x17;
				pawn->nextMotion      = 0x11;
				pawn->weapon->command = 3;
				pawn->shotTimer       = 0;
			} else {
				pawn->shotTimer = pawn->shotWait + 1;
			}
		}
	} else {
		pawnUpdateShoulderAngle(pawn);
	}
}
