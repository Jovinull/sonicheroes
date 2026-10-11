#include "types.h"

// RING OBJECT's reset hook in its editor record: it clears the placement's
// 0x10-byte work block, when it has one.

typedef struct RingFrame {
	u8 unk00[0x30]; // 0x00
	void* work;     // 0x30
} RingFrame;

extern "C" void* memset(void* destination, s32 value, u32 size);

extern "C" void ringObjectReset(RingFrame* frame)
{
	if (frame->work != NULL) {
		memset(frame->work, 0, 0x10);
	}
}
