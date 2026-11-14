// Resumes a running audio pool slot (see game/audio_system.h) inside an update lock with
// interrupts disabled. Without flag bit 1 it only clears the pause bit. Otherwise a paused slot
// adds the time spent paused to its two sequence times, clears the pause bit and, when
// system word 0x44 is 1, resumes its objects (fn_80206770).
#include "game/audio_system.h"

extern "C" {
void fn_80206770(PoolListNode** list);

void fn_8020B5E8(PoolSlot* s)
{
	BOOL enabled;
	BOOL inner;
	if (!(s->active & 0x80000000)) {
		return;
	}
	enabled = OSDisableInterrupts();
	inner   = OSDisableInterrupts();
	lbl_8042CF6C->lock++;
	OSRestoreInterrupts(inner);
	if (!(s->flags4 & 2)) {
		s->flags4 &= ~1;
		inner = OSDisableInterrupts();
		lbl_8042CF6C->lock--;
		OSRestoreInterrupts(inner);
		OSRestoreInterrupts(enabled);
		return;
	}
	if (s->flags4 & 1) {
		s->seq.timeA += lbl_8042CF6C->time - s->pauseTime;
		s->seq.timeB += lbl_8042CF6C->time - s->pauseTime;
		s->flags4 &= ~1;
		if (lbl_8042CF6C->f44 == 1) {
			fn_80206770(&s->objects);
		}
	}
	inner = OSDisableInterrupts();
	lbl_8042CF6C->lock--;
	OSRestoreInterrupts(inner);
	OSRestoreInterrupts(enabled);
}
}
