// Frees a block with the engine memory function.
#include "game/rw_engine.h"

extern "C" {
void fn_8020C700(void* block)
{
	lbl_8042C9A4->rwfree(block);
}
}
