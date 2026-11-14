// Stores v as word 0x3C of an audio pool slot (see game/audio_system.h).
#include "game/audio_system.h"

extern "C" {
void fn_802090B8(PoolSlot* s, float v)
{
	s->f3C = v;
}
}
