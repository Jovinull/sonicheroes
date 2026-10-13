#include "types.h"

// The bobsleigh's player placement (bobsleighSetPlayerPosition here; the name is
// ours, after TObjCannon::SetPlayerPosition, which has the same body; the PS2
// build has no TObjBobsleigh member of this shape). It is the out-of-line copy
// nothing calls. It builds the sled's matrix: the module's seat pitch about X,
// the sled's yaw (turned half round) about Y, then its Y, X and Z angles; moves
// it to the sled and puts the riding player (index at 0x19C) at the seat, the
// seat distance down its -Z axis.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct BobsleighPlayerWork {
	u8 unk00[0x10];
	RwV3d pos; // 0x10
	u8 unk1C[0x28];
} BobsleighPlayerWork; // 0x44

typedef struct Bobsleigh {
	u8 unk00[0x104];
	RwV3d pos; // 0x104
	u8 unk110[0x8C];
	s32 player; // 0x19C
	u8 unk1A0[0x60];
	s32 angX; // 0x200
	s32 angY; // 0x204
	s32 angZ; // 0x208
	u8 unk20C[0x18];
	s32 yaw; // 0x224
} Bobsleigh;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" BobsleighPlayerWork lbl_803EA4E8[];
extern "C" s32 bobsleighSeatPitch;
extern "C" f32 bobsleighSeatDistance;
extern "C" const f32 bobsleighZero[1];
extern "C" const f32 bobsleighOne[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* point, RwV3d* out);

extern "C" void bobsleighSetPlayerPosition(Bobsleigh* object)
{
	RwMatrixTag matrix;
	RwV3d seat;
	f32 sin;

	sin = fn_800D7B00(bobsleighSeatPitch);
	fn_80195790(&matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(bobsleighSeatPitch), sin, 0);
	sin = fn_800D7B00(object->yaw ^ 0x8000);
	fn_80195790(&matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->yaw ^ 0x8000), sin, 2);
	sin = fn_800D7B00(object->angY);
	fn_80195790(&matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->angY), sin, 2);
	sin = fn_800D7B00(object->angX);
	fn_80195790(&matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(object->angX), sin, 2);
	sin = fn_800D7B00(object->angZ);
	fn_80195790(&matrix, &AxisZ, bobsleighOne[0] - fn_800D7AE4(object->angZ), sin, 2);
	fn_80196050(&matrix, &object->pos, 2);

	seat.x = seat.y = bobsleighZero[0];
	seat.z          = -bobsleighSeatDistance;
	CalcPoint(&matrix, &seat, &lbl_803EA4E8[object->player].pos);
}
