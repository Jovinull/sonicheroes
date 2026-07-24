#include "types.h"

extern void* lbl_2_bss_54[5];

extern void fn_2_25A8(void* context, const void* position, const void* size);
extern void fn_80194234(s32 channel, void* resource);
extern void fn_2_2F94(void* context, const void* position, const void* size);
extern void fn_2_24FC(void* context);

void fn_2_32F8(void* context, const void* position, const void* size)
{
	fn_2_25A8(context, position, size);
	fn_80194234(1, lbl_2_bss_54[4]);
	fn_2_2F94(context, position, size);
	fn_2_24FC(context);
}
