#include "types.h"

typedef struct Lists {
	s32 count;     // 0x00
	void** clumps; // 0x04
	s8* worlds;    // 0x08
} Lists;

extern "C" u8* lbl_8042C1D0;
extern "C" void fn_8015BBF8(void* world, void* clump);

extern "C" void fn_16_4DF58(Lists* arg0)
{
	s32 i;

	for (i = 0; i < arg0->count; i++) {
		if (arg0->worlds[i] >= 0) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + arg0->worlds[i] * 4), arg0->clumps[i]);
		}
	}
}
