#include "dolphin/os.h"

#define OS_BUS_CLOCK   (*(u32*)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)

u32 fn_80012FC8(void)
{
	return OSGetTime() / (OS_TIMER_CLOCK / 1000);
}
