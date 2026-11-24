#include "game/particle_task.h"

// Creates a stage particle task (kind + 0x32) like fn_80062720 and sets bit 28 of its flags when
// the byte 0x1F of the game state lbl_8042C180 is set. HYPOTHESIS: one of the PS2 build's
// Construct_PtclTask_Stage_*TimeStop helpers.

struct GameState800628D0 {
	u8 pad0[0x1F];
	s8 f1F; // 0x1F
};

extern "C" GameState800628D0* lbl_8042C180;

extern "C" PARTICLE_TASK* fn_800628D0(u32 kind, RwV3d* pos, sAngle* ang)
{
	PARTICLE_TASK* task = new PARTICLE_TASK(kind + 0x32, pos, ang);
	if (task == NULL) {
		return NULL;
	}
	if (fn_80017800(task) == 0) {
		return NULL;
	}
	if (lbl_8042C180->f1F != 0) {
		task->flags |= 0x10000000;
	}
	return task;
}
