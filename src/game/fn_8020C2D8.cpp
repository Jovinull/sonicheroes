#include "game/rw_engine.h"

// Frees a block through the RenderWare engine's free callback (RwFree) and returns the pointer it
// was given. fn_8011B7CC uses it to destroy a UV animation's RtAnimAnimation; its own name is
// UNKNOWN.

extern "C" void* fn_8020C2D8(void* block)
{
	lbl_8042C9A4->rwfree(block);
	return block;
}
