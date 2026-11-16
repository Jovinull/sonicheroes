#include "types.h"
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8015BBF8(void* world, void* clump);
extern "C" u8* lbl_8042C1D0;

extern "C" void fn_16_6000(u8* self)
{
	s32 i;
	for (i = 0; i < 5; i++) {
		if (*(void**)(self + 0xE0 + i * 4) != NULL) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x725C), *(void**)(self + 0xE0 + i * 4));
			fn_80150958(*(void**)(self + 0xE0 + i * 4));
			*(void**)(self + 0xE0 + i * 4) = NULL;
		}
	}
}
