// Starts ramp A of an audio pool slot (see game/audio_system.h) from its
// current value towards target over duration, with interrupts disabled; a
// non-positive duration jumps straight to the target and leaves the ramp idle.
// The first step is applied at once, as in fn_802092A8.
#include "game/audio_system.h"

extern "C" {
extern const float lbl_80430090; // 0.0f
extern const float lbl_80430094; // -1.0f
extern const float lbl_80430098; // 1.0f

void fn_802091EC(PoolSlot* s, float target, float duration)
{
	BOOL enabled      = OSDisableInterrupts();
	s->rampAStart     = s->rampAValue;
	s->rampATarget    = target;
	s->rampADuration  = duration;
	s->rampARemaining = duration;
	if (s->rampARemaining <= lbl_80430090) {
		s->rampAValue     = s->rampATarget;
		s->rampADuration  = lbl_80430090;
		s->rampARemaining = lbl_80430094;
	} else {
		s->rampAValue = (s->rampATarget - s->rampAStart)
		        * (lbl_80430098 - s->rampARemaining / s->rampADuration)
		    + s->rampAStart;
	}
	OSRestoreInterrupts(enabled);
}
}
