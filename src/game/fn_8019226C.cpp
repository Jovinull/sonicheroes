// Release callback that ignores its first argument and frees block with the engine memory
// function.
#include "game/rw_engine.h"

extern "C" {
void fn_8019226C(void* unused, void* block)
{
	lbl_8042C9A4->rwfree(block);
}
}
