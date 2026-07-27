#include "types.h"

// Reconstruction fragment for fn_80013010. Its exact code range ends at
// 0x80013038; the corresponding extab/extabindex entries do not establish an
// original translation-unit boundary.
//
// This is the GameCube counterpart of the RenderWare platform camera-raster
// callback. The PS2 callback has C linkage inside a C++-compiled platform
// unit.

extern "C" void fn_8019CF74(void*, u32, u32);

extern "C" void fn_80013010(void* task)
{
	fn_8019CF74(task, 0, 0);
}
