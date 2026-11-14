// Allocation callback that ignores its first argument and allocates size bytes with the engine
// memory function.
#include "game/rw_engine.h"

extern "C" {
void* fn_8019223C(void* unused, u32 size)
{
	return lbl_8042C9A4->rwmalloc(size);
}
}
