#include "game/particle_task.h"

// Creates a coloured particle task with the colour copied to 0xB4 and sets bit 4 of its
// PARTICLE_MATERIAL flags; NULL when the allocation fails or the task is not alive. HYPOTHESIS:
// the PS2 build's Construct_PtclTask_Common_ColorChange. The body is the one fn_8009E9BC inlines
// (CreateColorParticleTask); written out here because a wrapper returns through a temporary.

extern "C" PtclColorTask* fn_8009EAA4(u32 kind, RwV3d* pos, sAngle* ang, RwRGBA* color)
{
	PtclColorTask* task = new PtclColorTask(kind, pos, ang, color);
	if (task == NULL) {
		return NULL;
	}
	if (fn_80017800(task) == 0) {
		return NULL;
	}
	fn_800643C0(task->material, fn_800643E8(task->material) | 0x10);
	return task;
}
