// TObjContainer::SetPosition (the PS2 build's name): it turns the crate's model
// about Y by the placement's second angle (scaled to degrees) and moves it to
// the crate's position, when the model is there. The class is in
// game/obj_container.h. The angle is converted with the module's shared
// int-to-float bias (containerBias), whose 8 bytes of .rodata this unit owns.

#include "game/obj_container.h"

extern "C" const f32 containerAngleScale[1];
extern "C" const RwV3d AxisY;
extern "C" void fn_8019ED68(void* frame, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

void TObjContainer::SetPosition()
{
	if (clump != NULL) {
		void* frame = *(void**)((u8*)clump + 4);
		fn_8019ED68(frame, &AxisY, containerAngleScale[0] * (f32)ang.y, 0);
		fn_8019EB94(frame, &pos, 2);
	}
}
