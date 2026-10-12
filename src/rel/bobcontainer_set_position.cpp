// TObjBobcontainer::SetPosition (the PS2 build's name): it moves the crate's
// model to its position and turns it about Z, X and Y by its angles, updating
// the frame after each turn (the rotation call is RenderWare's
// RwMatrixRotateOneMinusCosineSine, as in rel/s13_partition_class.inc). The
// class is in game/obj_container.h.

#include "game/obj_container.h"

extern "C" const f32 bobcontainerOne[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8019E880(void* frame);

#pragma opt_common_subs off
void TObjBobcontainer::SetPosition()
{
	if (clump != NULL) {
		void* frame = *(void**)((u8*)clump + 4);
		fn_8019EB94(frame, &pos, 0);
		f32 sin = fn_800D7B00(ang.z);
		fn_80195790((u8*)frame + 0x10, &AxisZ, bobcontainerOne[0] - fn_800D7AE4(ang.z), sin, 1);
		fn_8019E880(frame);
		sin = fn_800D7B00(ang.x);
		fn_80195790((u8*)frame + 0x10, &AxisX, bobcontainerOne[0] - fn_800D7AE4(ang.x), sin, 1);
		fn_8019E880(frame);
		sin = fn_800D7B00(ang.y);
		fn_80195790((u8*)frame + 0x10, &AxisY, bobcontainerOne[0] - fn_800D7AE4(ang.y), sin, 1);
		fn_8019E880(frame);
	}
}
#pragma opt_common_subs reset
