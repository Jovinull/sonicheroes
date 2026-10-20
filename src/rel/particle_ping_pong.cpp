#include "types.h"

// A frame counter folded into a ping-pong between 0 and `half` (pingPongFrame
// here), as the burst particles' animation uses it; nothing calls this copy.

extern "C" u32 pingPongFrame(u32 frame, u32 half)
{
	u32 period = half * 2;

	frame %= period;
	if (frame < half) {
		return frame;
	}
	return period - frame;
}
