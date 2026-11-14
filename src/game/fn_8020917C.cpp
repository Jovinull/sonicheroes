// Advances ramp B of an audio pool slot (see game/audio_system.h) by one step
// of 5: on the last step the value snaps to the target, the duration is cleared
// and the ramp goes idle (-1); otherwise the value is interpolated by the
// elapsed fraction.
#include "game/audio_system.h"

extern "C" {
extern const float lbl_80430090; // 0.0f
extern const float lbl_80430094; // -1.0f
extern const float lbl_80430098; // 1.0f
extern const float lbl_8043009C; // 5.0f

void fn_8020917C(PoolSlot* s)
{
	if (s->rampBRemaining >= lbl_80430090) {
		s->rampBRemaining -= lbl_8043009C;
		if (s->rampBRemaining <= lbl_80430090) {
			s->rampBValue     = s->rampBTarget;
			s->rampBDuration  = lbl_80430090;
			s->rampBRemaining = lbl_80430094;
		} else {
			s->rampBValue = (s->rampBTarget - s->rampBStart)
			        * (lbl_80430098 - s->rampBRemaining / s->rampBDuration)
			    + s->rampBStart;
		}
	}
}
}
