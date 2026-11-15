// PARTICLE_TASK's Exec (its slot in the vtable lbl_80243B38; the symbol keeps its address name):
// with an edit parameter (+0xB0), and not hidden by the debug byte +0x1F of lbl_8042C180 (only
// tasks with flag 0x10000000 run then), it counts the interval (+0xA8) down; at 0 it either emits
// (fn_800601A4) and reloads the interval from the parameter (+0x10), counting the emissions left
// (+0xA6) down, or, when none are left and the task has no instances (+0x74) and no keep flag 0x8
// (+0xA4), raises its TObject delete signal (bit 0 of +0x4). Flags 0x1 and 0x4 of +0xA4 pause the
// emission. HYPOTHESIS: the field roles.
#include "types.h"

struct EditParam8006228C {
	u8 pad0[0x10];
	s16 interval; // 0x10
};

struct Task8006228C {
	u8 pad0[4];
	u16 signal; // 0x4
	u8 pad6[0x2C - 0x6];
	s32 flags2C; // 0x2C (PARTICLE_MATERIAL flags +0x4)
	u8 pad30[0x74 - 0x30];
	void* instances; // 0x74
	u8 pad78[0xA4 - 0x78];
	u16 flagsA4;  // 0xA4
	s8 emissions; // 0xA6
	u8 padA7;
	s16 timer; // 0xA8
	u8 padAA[0xB0 - 0xAA];
	EditParam8006228C* param; // 0xB0
};

struct Debug8006228C {
	u8 pad0[0x1F];
	s8 enabled; // 0x1F
};

extern "C" {
extern Debug8006228C* lbl_8042C180;
void fn_800601A4(Task8006228C* task);

void fn_8006228C(Task8006228C* task)
{
	if (task->param == NULL) {
		return;
	}
	if (lbl_8042C180->enabled && !(task->flags2C & 0x10000000)) {
		return;
	}
	if (task->timer == 0) {
		if (task->emissions == 0) {
			if (task->instances == NULL && !(task->flagsA4 & 8)) {
				task->signal |= 1;
			}
		} else if (!(task->flagsA4 & 1) && !(task->flagsA4 & 4)) {
			fn_800601A4(task);
			if (task->emissions > 0) {
				task->emissions--;
			}
			task->timer = task->param->interval;
		}
	} else {
		task->timer--;
	}
}
}
