// Allocates the first idle slot of the audio pool (see game/audio_system.h) with interrupts
// disabled: clears it, marks it running, sets its ramps idle (ramp A at 0, ramp B at 1) and
// resets its sixteen channels (ResetPoolChannel, inlined as in retail). Returns the slot, or null
// when all eight are running.
#include "game/audio_system.h"

extern "C" {
extern const float lbl_80430090; // 0.0f
extern const float lbl_80430094; // -1.0f
extern const float lbl_80430098; // 1.0f
void* memset(void* dst, int value, unsigned long n);

PoolSlot* fn_80209AA4(void)
{
	PoolSlot* s;
	int i;
	BOOL enabled;
	enabled = OSDisableInterrupts();
	for (i = 0; i < 8; i++) {
		if (!(lbl_8042CF6C->slots[i].active & 0x80000000)) {
			goto found;
		}
	}
	OSRestoreInterrupts(enabled);
	return 0;
found:
	s = &lbl_8042CF6C->slots[i];
	memset(s, 0, sizeof(PoolSlot));
	s->active |= 0x80000000;
	s->rampAValue     = lbl_80430090;
	s->f0C            = lbl_80430090;
	s->rampBValue     = lbl_80430098;
	s->f28            = lbl_80430090;
	s->f10            = lbl_80430098;
	s->rampARemaining = lbl_80430094;
	s->rampBRemaining = lbl_80430094;
	for (i = 0; i < 0x10; i++) {
		s->channels[i].index = i;
		ResetPoolChannel(s, i);
	}
	OSRestoreInterrupts(enabled);
	return s;
}
}
