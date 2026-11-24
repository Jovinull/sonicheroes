#include "game/particle_task.h"

// Creates a coloured particle task (CreateColorParticleTask, fn_8009EAA4 inlined) and calls
// fn_80064380 on its material. HYPOTHESIS: the PS2 build's
// Construct_PtclTask_Common_ColorChange_TimeStop, which on PS2 calls the ColorChange constructor
// helper.

extern "C" void fn_80064380(void* material);

extern "C" PtclColorTask* fn_8009E9BC(u32 kind, RwV3d* pos, sAngle* ang, RwRGBA* color)
{
	PtclColorTask* task = CreateColorParticleTask(kind, pos, ang, color);
	if (task != NULL) {
		fn_80064380(task->material);
	}
	return task;
}
