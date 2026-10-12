#include "types.h"

// TObjCannon::CalcBarrelPosition (cannonCalcBarrelPosition here), the
// out-of-line copy nothing calls. It builds the barrel's matrix from the two
// barrel angles (about X, then Y) at the barrel's pivot (the module's offset,
// lowered a little the first time) on the cannon, and turns the barrel tip into
// the cannon's tip position; the matrix goes to the caller when asked for. Then
// it builds it again at the unlowered pivot for the second tip position.
//
// The first offset and the tip are initialised from the module's vectors, which
// MWCC copies as words; the second offset is assigned, which it copies as floats.

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
	u8 unk00[0xBC];
	RwV3d pos; // 0xBC
	u8 unkC8[0x74];
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

extern "C" void cannonCalcBarrelPosition(Cannon* object, s32 angX, s32 angY, RwMatrixTag* out)
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
	if (out != NULL) {
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
