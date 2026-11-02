// TObjItembaloon::SetPosition (the PS2 build's name), the same in the thirteen
// stage modules that share the engine core: the balloon's frame is scaled by
// its stretch (the Y axis by the first scale, X and Z by the second) times its
// size, turned by its angles (Y, then X, then Z) and moved to its position.
// The class is shared through itembaloon_class.inc.

#define ITEMBALOON_CTOR inline
#include "src/rel/itembaloon_class.inc"
#include "game/object.h"
extern const RwV3d AxisX, AxisY, AxisZ;

extern "C" void fn_8019EC30(RwFrame* frame, const RwV3d* scale, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, const RwV3d* translation, s32 combine);
extern "C" void fn_80195790(
    RwMatrix* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);

void TObjItembaloon::SetPosition()
{
	RwFrame* frame = *(RwFrame**)((u8*)clump + 4);
	RwV3d size3;
	RwV3d add;

	size3.x = AxisY.x * scale.x;
	size3.y = AxisY.y * scale.x;
	size3.z = AxisY.z * scale.x;
	add.x   = AxisX.x * scale.y;
	add.y   = AxisX.y * scale.y;
	add.z   = AxisX.z * scale.y;
	size3.x = size3.x + add.x;
	size3.y = size3.y + add.y;
	size3.z = size3.z + add.z;
	add.x   = AxisZ.x * scale.y;
	add.y   = AxisZ.y * scale.y;
	add.z   = AxisZ.z * scale.y;
	size3.x = size3.x + add.x;
	size3.y = size3.y + add.y;
	size3.z = size3.z + add.z;
	size3.x = size3.x * size;
	size3.y = size3.y * size;
	size3.z = size3.z * size;
	fn_8019EC30(frame, &size3, 0);
	fn_80195790(
	    &frame->modelling, &AxisY, itembaloonOne[0] - fn_800D7AE4(ang.y), fn_800D7B00(ang.y), 2);
	fn_80195790(
	    &frame->modelling, &AxisX, itembaloonOne[0] - fn_800D7AE4(ang.x), fn_800D7B00(ang.x), 2);
	fn_80195790(
	    &frame->modelling, &AxisZ, itembaloonOne[0] - fn_800D7AE4(ang.z), fn_800D7B00(ang.z), 2);
	fn_8019EB94(frame, &pos, 2);
}
