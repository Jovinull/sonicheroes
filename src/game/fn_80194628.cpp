// Frees a heap block descriptor with the engine memory function: its data buffer first when it has
// one and owns it, then the descriptor itself. Always returns 1.
#include "game/rw_engine.h"

// Heap block descriptor; only the fields used here are known.
struct OwnedBuffer80194628 {
	void* data; // 0x0
	s32 f4;
	s32 ownsData; // 0x8
};

extern "C" {
s32 fn_80194628(OwnedBuffer80194628* buffer)
{
	if (buffer->data != 0 && buffer->ownsData != 0) {
		lbl_8042C9A4->rwfree(buffer->data);
		buffer->data     = 0;
		buffer->ownsData = 0;
	}
	lbl_8042C9A4->rwfree(buffer);
	return 1;
}
}
