#include "types.h"

// TObjPropeller::setHandlePosition (the PS2 build's name, by its place in the
// PS2 order; propellerSetHandlePosition here): the handle hangs 2 below the
// head, which sits on the arm (the first fixed offset), turned by the
// head's pitch and roll, at the second fixed offset from the hook.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct Propeller {
	u8 unk00[0xFC];
	RwV3d hook;      // 0xFC
	s32 headAngX;    // 0x108
	s32 headAngY;    // 0x10C
	s32 headAngZ;    // 0x110
	u8 unk114[0x18]; // 0x114
	RwV3d handlePos; // 0x12C
} Propeller;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisZ;
extern "C" const RwV3d propellerArmOffset;
extern "C" const RwV3d propellerHeadOffset;
extern "C" const f32 propellerOne[1];
extern "C" const f32 propellerZeroSpin[1];
extern "C" const f32 propellerDropScale[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, const RwV3d* translation, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, const RwV3d* in, s32 count, RwMatrixTag* matrix);

extern "C" void propellerSetHandlePosition(Propeller* object)
{
	RwV3d below;
	RwMatrixTag matrix;

	fn_80196050(&matrix, &propellerArmOffset, 0);
	fn_80195790(&matrix, &AxisX, propellerOne[0] - fn_800D7AE4(object->headAngX),
	    fn_800D7B00(object->headAngX), 2);
	fn_80195790(&matrix, &AxisZ, propellerOne[0] - fn_800D7AE4(object->headAngZ),
	    fn_800D7B00(object->headAngZ), 2);
	fn_80196050(&matrix, &propellerHeadOffset, 2);
	fn_80196050(&matrix, &object->hook, 2);
	below.x = propellerZeroSpin[0];
	below.y = propellerDropScale[0];
	below.z = propellerZeroSpin[0];
	fn_8019941C(&object->handlePos, &below, 1, &matrix);
}
