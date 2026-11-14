// Advances ramp A of an audio pool slot (see game/audio_system.h) by one step
// of 5: on the last step the value snaps to the target, the duration is cleared
// and the ramp goes idle (-1); otherwise the value is interpolated by the
// elapsed fraction.
#include "game/audio_system.h"

extern "C" {
extern const float lbl_80430090; // 0.0f
extern const float lbl_80430094; // -1.0f
extern const float lbl_80430098; // 1.0f
extern const float lbl_8043009C; // 5.0f

void fn_802092A8(PoolSlot* s)
{
	if (s->rampARemaining >= lbl_80430090) {
		s->rampARemaining -= lbl_8043009C;
		if (s->rampARemaining <= lbl_80430090) {
			s->rampAValue     = s->rampATarget;
			s->rampADuration  = lbl_80430090;
			s->rampARemaining = lbl_80430094;
		} else {
			s->rampAValue = (s->rampATarget - s->rampAStart)
			        * (lbl_80430098 - s->rampARemaining / s->rampADuration)
			    + s->rampAStart;
		}
	}
}
}
