// Forwards (a, b) to the callback stored at +0x2C of the texture module globals and reports whether
// it returned a non-null result. The callback's role is UNKNOWN (a texture-module hook).
#include "game/rw_engine.h"

typedef void* (*RwTextureHook2C801A4E80)(void* a, void* b);

extern "C" {
s32 fn_801A4E80(void* a, void* b)
{
	return (*(RwTextureHook2C801A4E80*)(RW_TEXTURE_GLOBALS + 0x2C))(a, b) != 0;
}
}
