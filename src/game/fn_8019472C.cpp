#include "types.h"

// Returns base + index times the descriptor stride at offset 0x0C.
extern "C" {
struct Data8019472C {
	u8* base;
	u8 pad[8];
	s32 stride;
};

void* fn_8019472C(Data8019472C* data, s32 index)
{
	s32 stride = data->stride;
	u8* base   = data->base;
	return base + stride * index;
}
}
