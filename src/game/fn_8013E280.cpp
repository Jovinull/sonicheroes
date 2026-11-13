#include "types.h"

extern "C" s32 fn_8013E280(void* arg0)
{
	s32 size = 0x24;
	return size * *(s32*)((u8*)arg0 + 4);
}
