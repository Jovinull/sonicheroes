// Frees block with the engine memory function and returns object unchanged.
#include "game/rw_engine.h"

extern "C" {
void* fn_8019D388(void* object, void* block)
{
	lbl_8042C9A4->rwfree(block);
	return object;
}
}
