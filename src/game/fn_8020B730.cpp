// Pauses a running audio pool slot (see game/audio_system.h): unless already paused, records the
// system time, sets the pause bit and either keeps the slot's handle (fn_802066AC, when system word
// 0x44 is 1) or releases it (fn_80206834). Runs with interrupts disabled inside an update lock.
#include "game/audio_system.h"

extern "C" {
#include "dolphin/os.h"

void fn_802066AC(unsigned int* handle);
void fn_80206834(unsigned int* handle);

void fn_8020B730(PoolSlot* s)
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
	if (!(s->flags4 & 1)) {
		s->pauseTime = lbl_8042CF6C->time;
		s->flags4 |= 1;
		if (s->fA0 != 0) {
			if (lbl_8042CF6C->f44 == 1) {
				fn_802066AC(&s->fA0);
			} else {
				fn_80206834(&s->fA0);
				s->fA0 = 0;
			}
		}
	}
	inner = OSDisableInterrupts();
	lbl_8042CF6C->lock--;
	OSRestoreInterrupts(inner);
	OSRestoreInterrupts(enabled);
}
}
