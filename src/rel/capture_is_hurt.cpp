#include "types.h"

// Whether the capture enemy has lost life (captureIsHurt here), the same in
// the seven stage modules that carry the capture.

typedef struct Capture {
	u8 unk000[0x1A4];
	f32 life; // 0x1A4
	u8 unk1A8[0xA8];
	f32 maxLife; // 0x250
} Capture;

extern "C" s32 captureIsHurt(Capture* object)
{
	return object->maxLife != object->life;
}
