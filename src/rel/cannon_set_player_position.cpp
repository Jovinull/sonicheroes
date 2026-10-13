#include "types.h"

// TObjCannon::SetPlayerPosition (cannonSetPlayerPosition here), the
// out-of-line copy nothing calls. It builds the barrel's matrix: the module's
// barrel pitch about X, the cannon's yaw (turned half round) about Y, then the
// barrel angles about Z, X and Y; moves it to the cannon raised by the barrel
// height, and puts the player at the muzzle, the barrel length down its -Z axis.
//
// The position copy is a block copy (word loads and stores), as a copy of a
// 12-byte struct without float members gives.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct CannonWords {
	u32 w[3];
} CannonWords;

typedef struct CannonPlayerWork {
	u8 unk00[0x10];
	RwV3d pos; // 0x10
	u8 unk1C[0x28];
} CannonPlayerWork; // 0x44

typedef struct Cannon {
	u8 unk00[0xBC];
	RwV3d pos;   // 0xBC
	s32 barrelX; // 0xC8
	s32 barrelY; // 0xCC
	s32 barrelZ; // 0xD0
	u8 unkD4[0x2C];
	s32 yaw; // 0x100
} Cannon;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" CannonPlayerWork lbl_803EA4E8[];
extern "C" s32 cannonBarrelPitch;
extern "C" f32 cannonBarrelLength;
extern "C" f32 cannonBarrelHeight;
extern "C" const f32 cannonZero[1];
extern "C" const f32 cannonOne[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* point, RwV3d* out);

extern "C" void cannonSetPlayerPosition(Cannon* object, s32 player)
{
	RwMatrixTag matrix;
	RwV3d muzzle;
	RwV3d pos;
	f32 sin;

	sin = fn_800D7B00(cannonBarrelPitch);
	fn_80195790(&matrix, &AxisX, cannonOne[0] - fn_800D7AE4(cannonBarrelPitch), sin, 0);
	sin = fn_800D7B00(object->yaw ^ 0x8000);
	fn_80195790(&matrix, &AxisY, cannonOne[0] - fn_800D7AE4(object->yaw ^ 0x8000), sin, 2);
	sin = fn_800D7B00(object->barrelZ);
	fn_80195790(&matrix, &AxisZ, cannonOne[0] - fn_800D7AE4(object->barrelZ), sin, 2);
	sin = fn_800D7B00(object->barrelX);
	fn_80195790(&matrix, &AxisX, cannonOne[0] - fn_800D7AE4(object->barrelX), sin, 2);
	sin = fn_800D7B00(object->barrelY);
	fn_80195790(&matrix, &AxisY, cannonOne[0] - fn_800D7AE4(object->barrelY), sin, 2);

	*(CannonWords*)&pos = *(CannonWords*)&object->pos;
	pos.y += cannonBarrelHeight;
	fn_80196050(&matrix, &pos, 2);

	muzzle.x = muzzle.y = cannonZero[0];
	muzzle.z            = -cannonBarrelLength;
	CalcPoint(&matrix, &muzzle, &lbl_803EA4E8[player].pos);
}
