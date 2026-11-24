#include "game/particle_task.h"

// Creates a stage particle task: kind + 0x32 (stage particle kinds start at 0x32, see
// src/rel/s13_cloud_ptcl_ctor.cpp). Returns NULL when the allocation fails or the new task is not
// alive (fn_80017800). HYPOTHESIS: the PS2 build's Construct_PtclTask_Stage.

extern "C" PARTICLE_TASK* fn_80062720(u32 kind, RwV3d* pos, sAngle* ang)
{
	PARTICLE_TASK* task = new PARTICLE_TASK(kind + 0x32, pos, ang);
	if (task == NULL) {
		return NULL;
	}
	if (fn_80017800(task) == 0) {
		return NULL;
	}
	return task;
}
