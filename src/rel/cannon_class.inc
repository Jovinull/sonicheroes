// TObjCannon's layout and CalcBarrelPosition, shared by
// rel/cannon_calc_barrel_position.cpp (the out-of-line copy) and the members that
// inline it (rel/cannon_hold_player.cpp). It is inline here and defined plain by
// the unit that emits the copy.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	RwV3d right; // 0x00
	u32 flags;   // 0x0C
	RwV3d up;    // 0x10
	u32 pad1;    // 0x1C
	RwV3d at;    // 0x20
	u32 pad2;    // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3;    // 0x3C
};

typedef struct Cannon {
	u8 unk00[0xB8];
	u8 replace[0x4]; // 0xB8, OBJ_ReplacePlayer
	RwV3d pos;       // 0xBC
	u8 unkC8[0x34];
	s32 barrelPitch; // 0xFC
	s32 barrelYaw;   // 0x100
	u8 unk104[0x38];
	RwV3d tip;  // 0x13C
	RwV3d tip2; // 0x148
} Cannon;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" RwV3d cannonBarrelOffset;
extern "C" const RwV3d cannonBarrelTip;
extern "C" const f32 cannonBarrelDrop[1];
extern "C" const f32 cannonOne[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);

#ifndef CANNON_CALC_BARREL_INLINE
#define CANNON_CALC_BARREL_INLINE inline
#endif

extern "C" CANNON_CALC_BARREL_INLINE void cannonCalcBarrelPosition(
    Cannon* object, s32 angX, s32 angY, RwMatrixTag* out)
{
	RwMatrixTag matrix;
	RwV3d offset = cannonBarrelOffset;
	f32 sin;

	offset.y -= cannonBarrelDrop[0];
	sin = fn_800D7B00(angX);
	fn_80195790(&matrix, &AxisX, cannonOne[0] - fn_800D7AE4(angX), sin, 0);
	sin = fn_800D7B00(angY);
	fn_80195790(&matrix, &AxisY, cannonOne[0] - fn_800D7AE4(angY), sin, 2);
	fn_80196050(&matrix, &offset, 2);
	fn_80196050(&matrix, &object->pos, 2);
	RwV3d tip = cannonBarrelTip;
	fn_8019941C(&object->tip, &tip, 1, &matrix);
	if (out) {
		*out = matrix;
	}

	offset = cannonBarrelOffset;
	sin    = fn_800D7B00(angX);
	fn_80195790(&matrix, &AxisX, cannonOne[0] - fn_800D7AE4(angX), sin, 0);
	sin = fn_800D7B00(angY);
	fn_80195790(&matrix, &AxisY, cannonOne[0] - fn_800D7AE4(angY), sin, 2);
	fn_80196050(&matrix, &offset, 2);
	fn_80196050(&matrix, &object->pos, 2);
	fn_8019941C(&object->tip2, &tip, 1, &matrix);
}
