#include "game/particle_task.h"

// Creates a common particle task of the given kind. Returns NULL when the allocation fails or the
// new task is not alive (fn_80017800). HYPOTHESIS: the PS2 build's Construct_PtclTask_Common.

extern "C" PARTICLE_TASK* fn_800627BC(u32 kind, RwV3d* pos, sAngle* ang)
{
	PARTICLE_TASK* task = new PARTICLE_TASK(kind, pos, ang);
	if (task == NULL) {
		return NULL;
	}
	if (fn_80017800(task) == 0) {
		return NULL;
	}
	return task;
}
