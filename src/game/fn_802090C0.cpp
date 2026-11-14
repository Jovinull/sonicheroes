// Starts ramp B of an audio pool slot (see game/audio_system.h) from its
// current value towards target over duration, with interrupts disabled; a
// non-positive duration jumps straight to the target and leaves the ramp idle.
// The first step is applied at once, as in fn_802092A8.
#include "game/audio_system.h"

extern "C" {
extern const float lbl_80430090; // 0.0f
extern const float lbl_80430094; // -1.0f
extern const float lbl_80430098; // 1.0f

void fn_802090C0(PoolSlot* s, float target, float duration)
{
	BOOL enabled      = OSDisableInterrupts();
	s->rampBStart     = s->rampBValue;
	s->rampBTarget    = target;
	s->rampBDuration  = duration;
	s->rampBRemaining = duration;
	if (s->rampBRemaining <= lbl_80430090) {
		s->rampBValue     = s->rampBTarget;
		s->rampBDuration  = lbl_80430090;
		s->rampBRemaining = lbl_80430094;
	} else {
		s->rampBValue = (s->rampBTarget - s->rampBStart)
		        * (lbl_80430098 - s->rampBRemaining / s->rampBDuration)
		    + s->rampBStart;
	}
	OSRestoreInterrupts(enabled);
}
}
