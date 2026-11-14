// Resets channel `ch` of an audio pool slot to its defaults (see ResetPoolChannel in
// game/audio_system.h).
#include "game/audio_system.h"

extern "C" {
void fn_80209C48(PoolSlot* s, int ch)
{
	ResetPoolChannel(s, ch);
}
}
