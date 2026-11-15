#include "types.h"

extern "C" {

struct DMorphFrame {
	u8 pad[8];
	f32 duration;
	u8 pad2[8];
};

struct DMorphAnim {
	u8 pad[4];
	u8* f4;
};

f32 RpDMorphAnimationFrameGetDuration(DMorphAnim* a, s32 target, s32 frame)
{
	s32 index           = target * 8;
	DMorphFrame* frames = *(DMorphFrame**)(a->f4 + index + 4);
	return frames[frame].duration;
}
}
