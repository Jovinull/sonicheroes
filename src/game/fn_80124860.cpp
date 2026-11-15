#include "types.h"

typedef struct {
	u8 unk00[0xB4];
	u8* buffer; // 0xB4
	u8 unkB8[0x18];
	s32 base;      // 0xD0
	s32 stride;    // 0xD4
	s32 status[1]; // 0xD8
} Table80124860;

extern "C" s32 fn_80124860(Table80124860* self, s32 index)
{
	if (self->status[index] == 1) {
		return (s32)(self->buffer + self->stride * index + self->base);
	}
	return 0;
}
