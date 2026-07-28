// Reconstruction fragment for fn_80012FC8. Its exact code range ends at
// 0x80013010; the corresponding extab/extabindex entries do not establish an
// original translation-unit boundary.
//
// This is the GameCube counterpart of the RenderWare platform timer callback.
// The PS2 callback has C linkage inside a C++-compiled platform unit.
extern "C" {
#include "dolphin/os.h"
}

#define OS_BUS_CLOCK   (*(u32*)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)

extern "C" u32 fn_80012FC8(void)
{
	return OSGetTime() / (OS_TIMER_CLOCK / 1000);
}
