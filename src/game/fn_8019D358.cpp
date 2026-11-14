// Allocates the number of bytes stored in the first word of request with the engine memory
// function.
#include "game/rw_engine.h"

extern "C" {
void* fn_8019D358(u32* request)
{
	return lbl_8042C9A4->rwmalloc(*request);
}
}
