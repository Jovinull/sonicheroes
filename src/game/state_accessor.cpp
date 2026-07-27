#include "types.h"

extern "C" {

typedef struct Unknown {
	u8 padding[0x283C];
	void* field_283C;
	void* field_2840;
} Unknown;

#pragma force_active on

s32 fn_800133C8(void)
{
	return -1;
}

bool fn_800133A8(Unknown* obj)
{
	return obj->field_283C >= obj->field_2840;
}

u32 fn_800133A0(void)
{
	return 0;
}

u32 fn_80013398(Unknown* obj)
{
	return (u32)obj->field_283C;
}
}
